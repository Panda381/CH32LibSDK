
// ****************************************************************************
//
//                        BeatleBoyPad - Device init
//
// ****************************************************************************

#include "../../includes.h"

// device run mode
u8 RunMode;		// device run mode RUNMODE_* (0=OLED, 1=VGA)

// ADC measure
u8 Pad1AdcChan;		// PAD1 ADC channel (OLED: 6 from PD6, VGA: 5 from PD5)
volatile u8 SupplyVoltageCnt = 0;	// counter of samples of supply voltage
volatile u8 KeyPressOld = 0;		// previous state of presseed keys
volatile u8 KeyPressMap = 0;		// currently pressed keys
volatile u16 PadCnt = 0;		// PAD measure sample counter
volatile u32 SupplyVoltageAcc = 0;	// supply voltage accumulator
volatile u32 SupplyVoltageVal = 0;	// supply voltage value (voltage in [mV] = (1200 << (12 + SUPPLYADC_SHIFT)) / SupplyVoltage)
volatile u32 Pad1Acc = 0;		// PAD1 voltage accumulator
volatile u32 Pad1Val = 0;		// PAD1 value (value size PADADC_SHIFT+12 bits)
volatile u32 Pad2Acc = 0;		// PAD2 voltage accumulator
volatile u32 Pad2Val = 0;		// PAD2 value (value size PADADC_SHIFT+12 bits)

// ADC PAD thresholds (max=4095, R0=4700, R1=4700, R2=10000, R3=2000)
#if CH32V003
#define DIV003	4
#else
#define DIV003	1
#endif
u32 PadThreshold[7] = {
// 0: 0 (no key)
	(0+721)/2*PADADC_NUM/DIV003,		// 0: 0 (start KEY3)
// 1: 721 (KEY3)
	(721+1309)/2*PADADC_NUM/DIV003,		// 1: 4 (start KEY2)
// 2: 1309 (KEY2)
	(1309+1663)/2*PADADC_NUM/DIV003,	// 2: 8 (start KEY3)
// 3: 1663 (KEY2+KEY3)
	(1663+2048)/2*PADADC_NUM/DIV003,	// 3: 12 (start KEY1)
// 4: 2048 (KEY1)
	(2048+2245)/2*PADADC_NUM/DIV003,	// 4: 16 (start KEY3)
// 5: 2245 (KEY1+KEY3)
	(2245+2437)/2*PADADC_NUM/DIV003,	// 5: 20 (start KEY2)
// 6: 2437 (KEY1+KEY2)
	(2437+2569)/2*PADADC_NUM/DIV003,	// 6: 24 (start KEY3)
// 7: 2569 (KEY1+KEY2+KEY3)
};

// Get supply voltage in [mV]
int GetSupply(void)
{
#if CH32V003
	return (1200 << (10 + SUPPLYADC_SHIFT)) / SupplyVoltageVal;
#else
	return (1200 << (12 + SUPPLYADC_SHIFT)) / SupplyVoltageVal;
#endif
}

// Initialize device
void DevInit(void)
{
	// The delay is necessary to prevent transients during cartridge insertion.
	WaitMs(200);

	// disable OSC pins
	GPIO_Remap_PA1PA2(0);

	// initialize ADC single conversion mode
	ADC1_InitSingle();

	// set sampling time to 7.5 cycles
	// Measure time must be shorter than HSYNC time = 31.7 us
// ADC clk = 1 MHz, Tadcclk = 1us
// Conversion time Tconv = (sampling_time + 12.5)*Tadcclk = (7.5 + 12.5)*1 = 20 us
//  ADC0 - get PAD2 from PA2
//  ADC1 - (OLED: get PAD1 from PA1 ... possible XI)
//  ADC5 - VGA: get PAD1 from PD5
//  ADC6 - OLED: get PAD1 from PD6
//  ADC7 - (VGA: get PAD1 from PD4 ... possible SWIO)
//  ADC8 - measure supply voltage, calibration 1.2V
	int i;
	for (i = 0; i <= 8; i++) ADC1_SampTime(i, 1);	// measure supply voltage from channel 8

	// detect device using supply voltage (VGA: 5V, OLED: 3V)
	int n = ADC1_GetSingleMul(8, B10) >> 2; // result value (12+10-2) 20 bits
	SupplyVoltageVal = (n >> 8) << SUPPLYADC_SHIFT;
#if CH32V003
	n = (1200 << 18) / n;
#else
	n = (1200 << 20) / n;
#endif

	// PAD1 and run mode setup
	RunMode = RUNMODE_OLED;
	Pad1AdcChan = 6;	// OLED: ADC6 from (PA1:)PD6
	if (n >= 4100)
	{
		RunMode = RUNMODE_VGA;
		Pad1AdcChan = 5;	// VGA: ADC5 from (PD1:)PD5
	}

	// VGA device - wait to connect VGA cable, to enable re-programming
	if (RunMode == RUNMODE_VGA)
	{
		// initialize VGA output pin PD6 to input with pull-up
		RCC_AFIClkEnable();
		RCC_PDClkEnable();
		GPIO_Mode(PD6, GPIO_MODE_IN_PU);

		// wait to connect VGA cable
		do {
			WaitMs(10);
		} while (GPIO_In(PD6) != 0);

		// disable SWD interface
		GPIO_Remap_SWD(4);
	}

	// initialize PAD1 and PAD2 input pins
	GPIO_Mode((RunMode == RUNMODE_OLED) ? PD6 : PD5, GPIO_MODE_AIN); // PAD1
	GPIO_Mode(PA2, GPIO_MODE_AIN);	// PAD2

	// start PAD1 ADC conversion (it will be 1st value)
	ADC1_RSeq(1, Pad1AdcChan);	// select channel to be converted
	ADC1_SwStart();			// software start conversion
	WaitUs(31);			// short delay to convert

#if USE_KEY		// 1=use keyboard support
	// Initialize keyboard service (should be called before display init)
	KeyInit();
#endif

#if USE_SOUND		// use sound support 1=tone, 2=melody
	// Sound initialize
	SoundInit();
#endif

#if USE_DISP		// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver
	// Display initialize
	DispInit();
#endif

#if USE_DRAW || USE_PRINT
	// clear screen
	DrawClear();
#endif
}

// Terminate device
void DevTerm(void)
{
#if USE_KEY		// 1=use keyboard support
	// wait for no key pressed
	KeyWaitNoPressed();
#endif

#if USE_DISP		// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver
	// Display terminate
	DispTerm();
#endif

#if USE_SOUND		// use sound support 1=tone, 2=melody
	// Sound terminate
	SoundTerm();
#endif

#if USE_KEY		// 1=use keyboard support
	// terminate keyboard
	KeyTerm();
#endif
}
