
// ****************************************************************************
//
//                              Reset and Clock Control
//
// ****************************************************************************

#ifndef _SDK_RCC_H
#define _SDK_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

// default frequencies
#ifndef HSI_VALUE
#define HSI_VALUE	24000000	// frequency of HSI internal oscillator 24MHz
#endif

#ifndef HSE_VALUE
#define HSE_VALUE	24000000	// frequency of HSE external oscillator 24MHz (should be 3..32 MHz)
#endif

#ifndef LSI_VALUE
#define LSI_VALUE	128000		// frequency of LSI low-speed internal oscillator 128kHz
#endif

#ifndef SYSCLK_SRC
#define SYSCLK_SRC	4		// System clock source: 1=HSI, 2=HSE, 3=HSE_Bypass, 4=PLL_HSI, 5=PLL_HSE, 6=PLL_HSE_Bypass
#endif

#ifndef SYSCLK_DIV
#define SYSCLK_DIV	1		// System clock divider: 1, 2, 3, 4, 5, 6, 7, 8, 16, 32, 64, 128, 256
#endif

#ifndef ADCCLK_DIV
#define ADCCLK_DIV	1		// ADC clock divider: 1, 2, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128
#endif

// Reset and clock control 0x40021000
typedef struct {
	io32	CTLR;		// 0x00: Clock control register
	io32	CFGR0;		// 0x04: Clock configuration register 0
	io32	INTR;		// 0x08: Clock interrupt register
	io32	APB2PRSTR;	// 0x0C: PB2 peripheral reset register
	io32	APB1PRSTR;	// 0x10: PB1 peripheral reset register
	io32	AHBPCENR;	// 0x14: HB peripheral clock enable register
	io32	APB2PCENR;	// 0x18: PB2 peripheral clock enable register
	io32	APB1PCENR;	// 0x1C: PB1 peripheral clock enable register
	io32	res;		// 0x20: ... reserved
	io32	RSTSCKR;	// 0x24: Control/status register
} RCC_t;
STATIC_ASSERT(sizeof(RCC_t) == 0x28, "Incorrect RCC_t!");
#define RCC	((RCC_t*)RCC_BASE)

// system clock source
#define RCC_SYSCLKSRC_HSI	0	// HSI as system clock (default)
#define RCC_SYSCLKSRC_HSE	1	// HSE as system clock
#define RCC_SYSCLKSRC_PLL	2	// PLL as system clock

// AHB clock divider
#define RCC_SYSCLK_DIV1		0	// prescaler off
//#define RCC_SYSCLK_DIV2	1	// SYSCLK divided by 2
#define RCC_SYSCLK_DIV3		2	// SYSCLK divided by 3
//#define RCC_SYSCLK_DIV4	3	// SYSCLK divided by 4
#define RCC_SYSCLK_DIV5		4	// SYSCLK divided by 5
#define RCC_SYSCLK_DIV6		5	// SYSCLK divided by 6
#define RCC_SYSCLK_DIV7		6	// SYSCLK divided by 7
//#define RCC_SYSCLK_DIV8	7	// SYSCLK divided by 8
#define RCC_SYSCLK_DIV2		8	// SYSCLK divided by 2
#define RCC_SYSCLK_DIV4		9	// SYSCLK divided by 4
#define RCC_SYSCLK_DIV8		10	// SYSCLK divided by 8
#define RCC_SYSCLK_DIV16	11	// SYSCLK divided by 16
#define RCC_SYSCLK_DIV32	12	// SYSCLK divided by 32
#define RCC_SYSCLK_DIV64	13	// SYSCLK divided by 64
#define RCC_SYSCLK_DIV128	14	// SYSCLK divided by 128
#define RCC_SYSCLK_DIV256	15	// SYSCLK divided by 256

// ADC clock divider
#define RCC_ADCCLK_DIV2		0	// AHBCLK divided by 2 as ADC clock
//#define RCC_ADCCLK_DIV2	1	// AHBCLK divided by 2 as ADC clock
//#define RCC_ADCCLK_DIV2	2	// AHBCLK divided by 2 as ADC clock
//#define RCC_ADCCLK_DIV2	3	// AHBCLK divided by 2 as ADC clock
#define RCC_ADCCLK_DIV4		4	// AHBCLK divided by 4 as ADC clock
#define RCC_ADCCLK_DIV8		5	// AHBCLK divided by 8 as ADC clock
#define RCC_ADCCLK_DIV16	6	// AHBCLK divided by 16 as ADC clock
#define RCC_ADCCLK_DIV32	7	// AHBCLK divided by 32 as ADC clock
//#define RCC_ADCCLK_DIV4	8	// AHBCLK divided by 4 as ADC clock
//#define RCC_ADCCLK_DIV4	9	// AHBCLK divided by 4 as ADC clock
//#define RCC_ADCCLK_DIV4	10	// AHBCLK divided by 4 as ADC clock
//#define RCC_ADCCLK_DIV4	11	// AHBCLK divided by 4 as ADC clock
//#define RCC_ADCCLK_DIV8	12	// AHBCLK divided by 8 as ADC clock
//#define RCC_ADCCLK_DIV16	13	// AHBCLK divided by 16 as ADC clock
//#define RCC_ADCCLK_DIV32	14	// AHBCLK divided by 32 as ADC clock
#define RCC_ADCCLK_DIV64	15	// AHBCLK divided by 64 as ADC clock
#define RCC_ADCCLK_DIV6		16	// AHBCLK divided by 6 as ADC clock
//#define RCC_ADCCLK_DIV6	17	// AHBCLK divided by 6 as ADC clock
//#define RCC_ADCCLK_DIV6	18	// AHBCLK divided by 6 as ADC clock
//#define RCC_ADCCLK_DIV6	19	// AHBCLK divided by 6 as ADC clock
#define RCC_ADCCLK_DIV12	20	// AHBCLK divided by 12 as ADC clock
#define RCC_ADCCLK_DIV24	21	// AHBCLK divided by 24 as ADC clock
#define RCC_ADCCLK_DIV48	22	// AHBCLK divided by 48 as ADC clock
#define RCC_ADCCLK_DIV96	23	// AHBCLK divided by 96 as ADC clock
//#define RCC_ADCCLK_DIV8	24	// AHBCLK divided by 8 as ADC clock
//#define RCC_ADCCLK_DIV8	25	// AHBCLK divided by 8 as ADC clock
//#define RCC_ADCCLK_DIV8	26	// AHBCLK divided by 8 as ADC clock
//#define RCC_ADCCLK_DIV8	27	// AHBCLK divided by 8 as ADC clock
//#define RCC_ADCCLK_DIV16	28	// AHBCLK divided by 16 as ADC clock
//#define RCC_ADCCLK_DIV32	29	// AHBCLK divided by 32 as ADC clock
//#define RCC_ADCCLK_DIV64	30	// AHBCLK divided by 64 as ADC clock
#define RCC_ADCCLK_DIV128	31	// AHBCLK divided by 128 as ADC clock

// PLL clock source
#define RCC_PLLSRC_HSI		0	// HSI is fed into PLL
#define RCC_PLLSRC_HSE		1	// HSE is fed into PLL

// MCO pin clock output
#define RCC_MCO_NONE		0	// (0-3) no clock output
#define RCC_MCO_SYSCLK		4	// system clock
#define RCC_MCO_HSI		5	// HSI internal oscillator 24MHz
#define RCC_MCO_HSE		6	// HSE external oscillator
#define RCC_MCO_PLL		7	// PLL clock output

// AHB peripheral clock mask
#define RCC_AHBCLK_DMA1		B0	// DMA1 module clock mask
#define RCC_AHBCLK_SRAM		B2	// SRAM clock mask

// APB2 peripheral clock mask
#define RCC_APB2CLK_AFI		B0	// I/O auxiliary function module clock mask
#define RCC_APB2CLK_PA		B2	// PA port module clock mask
#define RCC_APB2CLK_PB		B3	// PB port module clock mask
#define RCC_APB2CLK_PC		B4	// PC port module clock mask
#define RCC_APB2CLK_PD		B5	// PD port module clock mask
#define RCC_APB2CLK_ADC1	B9	// ADC1 module clock mask
#define RCC_APB2CLK_TIM1	B11	// TIM1 module clock mask
#define RCC_APB2CLK_SPI1	B12	// SPI1 module clock mask
#define RCC_APB2CLK_USART1	B14	// USART1 module clock mask
#define RCC_APB2CLK_USART2	B13	// USART2 module clock mask

// APB1 peripheral clock mask
#define RCC_APB1CLK_TIM2	B0	// TIM2 module clock mask
#define RCC_APB1CLK_TIM3	B2	// TIM3 module clock mask
#define RCC_APB1CLK_WWDG	B11	// Window watchdog clock mask
#define RCC_APB1CLK_I2C1	B21	// I2C1 module clock mask
#define RCC_APB1CLK_PWR		B28	// Power module clock mask

// HSE current supply
#define RCC_HSE_LEVEL0		0	// HSE_LP=0: 1.6mA, HSE_LP=1: 0.8mA
#define RCC_HSE_LEVEL1		1	// HSE_LP=0: 2.0mA, HSE_LP=1: 1.0mA
#define RCC_HSE_LEVEL2		2	// HSE_LP=0: 2.5mA, HSE_LP=1: 1.25mA
#define RCC_HSE_LEVEL3		3	// HSE_LP=0: 1.3mA, HSE_LP=1: 1.5mA

// Reset reason - copy of the RCC->RSTSCKR register on system start (check using RCC_RESETON_* flags)
#define RCC_RESETON_WWDG	B30	// Windows watchdog reset
#define RCC_RESETON_IWDG	B29	// Independent watchdog reset
#define RCC_RESETON_SW		B28	// software reset
#define RCC_RESETON_PWR		B27	// power-on reset
#define RCC_RESETON_RST		B26	// manual reset on NRST pin
#define RCC_RESETON_OPA		B25	// OPA CMP reset
#define RCC_RESETON_ADC		B23	// ADC reset
extern u32 ResetReason;

// AHB clock divider table
extern const u16 RCC_AHBClkDivTab[16];

// ADC clock divider table
extern const u8 RCC_ADCClkDivTab[32];

// Current frequencies
#define CLK_HSI		0	// HSI oscillator frequency index (24MHz)
#define CLK_HSE		1	// HSE oscillator frequency index (24MHz)
#define CLK_LSI		2	// LSI oscillator frequency index (128kHz)
#define CLK_SYSCLK	3	// SYSCLK frequency index (system frequency from clock sources; 48MHz)
#define CLK_HCLK	4	// HCLK frequency index (main clock to periphery and flash, SYSCLK divided; 48MHz)
#define CLK_ADCCLK	5	// ADCCLK frequency index (ADC clock, HCLK divided; 24MHz)

#define CLK_NUM		6	// number of frequency indices

extern u32 RCC_FreqTab[CLK_NUM];	// current frequencies in [Hz]

#define SystemCoreClock RCC_FreqTab[CLK_HCLK] // system core clock

// --- HSI high-speed internal oscillator 24MHz

// Enable/Disable HSI high-speed internal oscillator 24MHz (default enabled)
// - Enabled by hardware when returning from standby mode or when HSE fails.
INLINE void RCC_HSIEnable(void) { RCC->CTLR |= B0; }
INLINE void RCC_HSIDisable(void) { RCC->CTLR &= ~B0; }

// Check if HSI high-speed internal oscillator 24MHz is stable
INLINE Bool RCC_HSIIsStable(void) { return (RCC->CTLR & B1) != 0; }

// Get current adjustment value of the HSI internal high-speed clock 24MHz (0..31; default 16)
//  Clock adjustment value is in range 0..31, with default value 16.
//  Oscillator frequency 24MHz can be adjusted by 60KHz per step.
INLINE u8 RCC_HSIGetTrim(void) { return (u8)((RCC->CTLR >> 3) & 0x1f); }

// Set adjustment value of the HSI internal high-speed clock 24MHz (0..31)
//  Clock adjustment value is in range 0..31, with default value 16.
//  Oscillator frequency 24MHz can be adjusted by 60KHz per step.
INLINE void RCC_HSITrim(int trim) { RCC->CTLR = (RCC->CTLR & ~(0x1f << 3)) | (trim << 3); }

// Get calibration value of the HSI internal high-speed clock 24MHz (0..31)
INLINE u8 RCC_HSIGetCal(void) { return (u8)((RCC->CTLR >> 8) & 0xff); }

// Enable/Disable HSI low-power mode
INLINE void RCC_HSILPEnable(void) { RCC->CTLR |= B2; }
INLINE void RCC_HSILPDisable(void) { RCC->CTLR &= ~B2; }

// --- HSE high-speed external crystal oscillator

// Enable/Disable HSE high-speed external crystal oscillator (default disabled)
// - Disabled by hardware after entering standby low-power mode.
INLINE void RCC_HSEEnable(void) { RCC->CTLR |= B16; }
INLINE void RCC_HSEDisable(void) { RCC->CTLR &= ~B16; }

// Check if HSE high-speed external crystal oscillator is stable
INLINE Bool RCC_HSEIsStable(void) { return (RCC->CTLR & B17) != 0; }

// Enable/Disable bypass HSE high-speed external crystal oscillator (HSE must be disabled)
INLINE void RCC_HSEBypassEnable(void) { RCC->CTLR |= B18; }
INLINE void RCC_HSEBypassDisable(void) { RCC->CTLR &= ~B18; }

// Enable/Disable HSE low-power mode
INLINE void RCC_HSELPEnable(void) { RCC->CTLR |= B20; }
INLINE void RCC_HSELPDisable(void) { RCC->CTLR &= ~B20; }

// Enable/Disable SCM system clock monitoring module
INLINE void RCC_SCMEnable(void) { RCC->CTLR |= B21; }
INLINE void RCC_SCMDisable(void) { RCC->CTLR &= ~B21; }

// Set/Get HSE current supply RCC_HSE_LEVEL*
INLINE void RCC_HSELevel(int level) { RCC->CTLR = (RCC->CTLR & ~(3 << 22)) | (level << 22); }
INLINE int RCC_GetHSELevel(void) { return (RCC->CTLR >> 22) & 3; }

// Start HSE oscillator and wait to be stable (bypass = bypass HSE crystal; returns False on error)
Bool RCC_HSEStart(Bool bypass);

// --- LSI low-speed internall oscillator

// Enable/Disable LSI low speed clock 128KHz
INLINE void RCC_LSIEnable(void) { RCC->RSTSCKR |= B0; }
INLINE void RCC_LSIDisable(void) { RCC->RSTSCKR &= ~B0; }

// Check if LSI low speed clock 128KHz is stable
INLINE Bool RCC_LSIIsStable(void) { return (RCC->RSTSCKR & B1) != 0; }

// --- PLL clock (multiply source clock * 2)

// Enable/Disable PLL clock (default disabled)
// - Disabled by hardware after entering standby low-power mode.
INLINE void RCC_PLLEnable(void) { RCC->CTLR |= B24; }
INLINE void RCC_PLLDisable(void) { RCC->CTLR &= ~B24; }

// Check if PLL clock is ready
INLINE Bool RCC_PLLIsReady(void) { return (RCC->CTLR & B25) != 0; }

// Select PLL clock source RCC_PLLSRC_* (PLL should be off)
INLINE void RCC_PLLSrc(int src) { RCC->CFGR0 = (RCC->CFGR0 & ~B16) | (src << 16); }

// Get PLL clock source RCC_PLLSRC_*
INLINE u8 RCC_GetPLLSrc(void) { return (u8)((RCC->CFGR0 >> 16) & 1); }

// --- Clock source

// Select SYSCLK system clock source RCC_SYSCLKSRC_* (default 0 = HSI)
INLINE void RCC_SysClkSrc(int src) { RCC->CFGR0 = (RCC->CFGR0 & ~3) | src; }

// Get current SYSCLK system clock source RCC_SYSCLKSRC_* (hardware set)
INLINE u8 RCC_SysClk(void) { return (u8)((RCC->CFGR0 >> 2) & 3); }

// Set AHB clock divider RCC_SYSCLK_DIV* to get from SYSCLK (default 2 = divide by 3)
INLINE void RCC_AHBDiv(int div) { RCC->CFGR0 = (RCC->CFGR0 & ~(0x0f << 4)) | (div << 4); }

// Get AHB clock divider RCC_SYSCLK_DIV*
INLINE u8 RCC_GetAHBDiv(void) { return (u8)((RCC->CFGR0 >> 4) & 0x0f); }

// Get AHB clock divider value 1..256
INLINE u16 RCC_GetAHBDivVal(void) { return RCC_AHBClkDivTab[RCC_GetAHBDiv()]; }

// Set ADC clock divider RCC_ADCCLK_DIV* to get from AHB clock (should not exceed 24MHz) (default 0 = divided by 2)
INLINE void RCC_ADCDiv(int div) { RCC->CFGR0 = (RCC->CFGR0 & ~(0x1f << 11)) | (div << 11); }

// Get ADC clock divider RCC_ADCCLK_DIV*
INLINE u8 RCC_GetADCDiv(void) { return (u8)((RCC->CFGR0 >> 11) & 0x1f); }

// Enable/Disable ADC AHB clock divider (AHB clock does not divide frequency, if disabled)
INLINE void RCC_ADCDivEnable(void) { RCC->CFGR0 &= ~B31; }
INLINE void RCC_ADCDivDisable(void) { RCC->CFGR0 |= B31; }
INLINE Bool RCC_GetADCDivEnabled(void) { return (RCC->CFGR0 & B31) != 0; }

// ADC clock duty cycle adjustment to 1/2 or 3/4 high-level
INLINE void RCC_ADCClkAdj12(void) { RCC->CFGR0 &= ~B28; }
INLINE void RCC_ADCClkAdj34(void) { RCC->CFGR0 |= B28; }

// Get ADC clock divider value 2..128
INLINE u8 RCC_GetADCDivVal(void) { return RCC_ADCClkDivTab[RCC_GetADCDiv()]; }

// Set MCO pin clock output source RCC_MCO_* (default 0 = disabled)
INLINE void RCC_MCOClkSrc(int src) { RCC->CFGR0 = (RCC->CFGR0 & ~(7 << 24)) | (src << 24); }

// Get clock frequency in [Hz] from frequency table CLK_*
INLINE u32 RCC_GetFreq(int inx) { return RCC_FreqTab[inx]; }

// Update frequencies in clock frequency table (should be called after change settings)
void RCC_UpdateFreq(void);

// Initialize system clock to default configuration
void RCC_ClockInit(void);

// Reset system clock to default configuration (select HSI oscillator/3)
void RCC_ClockReset(void);

// --- Interrupt (default all disabled)

// LSI clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_LSIIntEnable(void) { RCC->INTR |= B8; }
INLINE void RCC_LSIIntDisable(void) { RCC->INTR &= ~B8; }
INLINE Bool RCC_LSIInt(void) { return (RCC->INTR & B0) != 0; }
INLINE void RCC_LSIIntClear(void) { RCC->INTR |= B16; }

// HSI clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_HSIIntEnable(void) { RCC->INTR |= B10; }
INLINE void RCC_HSIIntDisable(void) { RCC->INTR &= ~B10; }
INLINE Bool RCC_HSIInt(void) { return (RCC->INTR & B2) != 0; }
INLINE void RCC_HSIIntClear(void) { RCC->INTR |= B18; }

// HSE clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_HSEIntEnable(void) { RCC->INTR |= B11; }
INLINE void RCC_HSEIntDisable(void) { RCC->INTR &= ~B11; }
INLINE Bool RCC_HSEInt(void) { return (RCC->INTR & B3) != 0; }
INLINE void RCC_HSEIntClear(void) { RCC->INTR |= B19; }

// PLL clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_PLLIntEnable(void) { RCC->INTR |= B12; }
INLINE void RCC_PLLIntDisable(void) { RCC->INTR &= ~B12; }
INLINE Bool RCC_PLLInt(void) { return (RCC->INTR & B4) != 0; }
INLINE void RCC_PLLIntClear(void) { RCC->INTR |= B20; }

// CSS HSE clock failure Enable/Disable/Flag/Clear
//  - Triggers CSSF and NMI interrupt when HSE fails
INLINE void RCC_CSSEnable(void) { RCC->CTLR |= B19; }
INLINE void RCC_CSSDisable(void) { RCC->CTLR &= ~B19; }
INLINE Bool RCC_CSSInt(void) { return (RCC->INTR & B7) != 0; }
INLINE void RCC_CSSIntClear(void) { RCC->INTR |= B23; }

// SYSCLK fail interrupt Enable/Disable/Flag
INLINE void RCC_SysClkFailEnable(void) { RCC->INTR |= B9; }
INLINE void RCC_SysClkFailDisable(void) { RCC->INTR &= ~B9; }
INLINE Bool RCC_SysClkFailInt(void) { return (RCC->RSTSCKR & B8) != 0; }

// Clear all interrupt flags
INLINE void RCC_IntClear(void) { RCC->INTR |= B16|B18|B19|B20|B23; }

// Disable all interrupt flags
INLINE void RCC_IntDisable(void) { RCC->INTR &= ~(B8|B9|B10|B11|B12); }

// --- Peripheral reset

// I/O auxiliary function module reset ON/OFF/Reset
INLINE void RCC_AFIResetOn(void) { RCC->APB2PRSTR |= B0; cb(); }
INLINE void RCC_AFIResetOff(void) { RCC->APB2PRSTR &= ~B0; cb(); }
INLINE void RCC_AFIReset(void) { RCC_AFIResetOn(); nop(); RCC_AFIResetOff(); }

// PA port module reset ON/OFF/Reset
INLINE void RCC_PAResetOn(void) { RCC->APB2PRSTR |= B2; cb(); }
INLINE void RCC_PAResetOff(void) { RCC->APB2PRSTR &= ~B2; cb(); }
INLINE void RCC_PAReset(void) { RCC_PAResetOn(); nop(); RCC_PAResetOff(); }

// PB port module reset ON/OFF/Reset
INLINE void RCC_PBResetOn(void) { RCC->APB2PRSTR |= B3; cb(); }
INLINE void RCC_PBResetOff(void) { RCC->APB2PRSTR &= ~B3; cb(); }
INLINE void RCC_PBReset(void) { RCC_PBResetOn(); nop(); RCC_PBResetOff(); }

// PC port module reset ON/OFF/Reset
INLINE void RCC_PCResetOn(void) { RCC->APB2PRSTR |= B4; cb(); }
INLINE void RCC_PCResetOff(void) { RCC->APB2PRSTR &= ~B4; cb(); }
INLINE void RCC_PCReset(void) { RCC_PCResetOn(); nop(); RCC_PCResetOff(); }

// PD port module reset ON/OFF/Reset
INLINE void RCC_PDResetOn(void) { RCC->APB2PRSTR |= B5; cb(); }
INLINE void RCC_PDResetOff(void) { RCC->APB2PRSTR &= ~B5; cb(); }
INLINE void RCC_PDReset(void) { RCC_PDResetOn(); nop(); RCC_PDResetOff(); }

// Port module reset (use port index PORT*_INX)
INLINE void RCC_PxResetOn(int portinx) { RCC->APB2PRSTR |= BIT(portinx+2); cb(); }
INLINE void RCC_PxResetOff(int portinx) { RCC->APB2PRSTR &= ~BIT(portinx+2); cb(); }
INLINE void RCC_PxReset(int portinx) { RCC_PxResetOn(portinx); nop(); RCC_PxResetOff(portinx); }

// ADC1 module reset ON/OFF/Reset
INLINE void RCC_ADC1ResetOn(void) { RCC->APB2PRSTR |= B9; cb(); }
INLINE void RCC_ADC1ResetOff(void) { RCC->APB2PRSTR &= ~B9; cb(); }
INLINE void RCC_ADC1Reset(void) { RCC_ADC1ResetOn(); nop(); RCC_ADC1ResetOff(); }

// TIM1 module reset ON/OFF/Reset
INLINE void RCC_TIM1ResetOn(void) { RCC->APB2PRSTR |= B11; cb(); }
INLINE void RCC_TIM1ResetOff(void) { RCC->APB2PRSTR &= ~B11; cb(); }
INLINE void RCC_TIM1Reset(void) { RCC_TIM1ResetOn(); nop(); RCC_TIM1ResetOff(); }

// SPI1 module reset ON/OFF/Reset
INLINE void RCC_SPI1ResetOn(void) { RCC->APB2PRSTR |= B12; cb(); }
INLINE void RCC_SPI1ResetOff(void) { RCC->APB2PRSTR &= ~B12; cb(); }
INLINE void RCC_SPI1Reset(void) { RCC_SPI1ResetOn(); nop(); RCC_SPI1ResetOff(); }

// USART2 module reset ON/OFF/Reset
INLINE void RCC_USART2ResetOn(void) { RCC->APB2PRSTR |= B13; cb(); }
INLINE void RCC_USART2ResetOff(void) { RCC->APB2PRSTR &= ~B13; cb(); }
INLINE void RCC_USART2Reset(void) { RCC_USART2ResetOn(); nop(); RCC_USART2ResetOff(); }

// USART1 module reset ON/OFF/Reset
INLINE void RCC_USART1ResetOn(void) { RCC->APB2PRSTR |= B14; cb(); }
INLINE void RCC_USART1ResetOff(void) { RCC->APB2PRSTR &= ~B14; cb(); }
INLINE void RCC_USART1Reset(void) { RCC_USART1ResetOn(); nop(); RCC_USART1ResetOff(); }

// TIM2 module reset ON/OFF/Reset
INLINE void RCC_TIM2ResetOn(void) { RCC->APB1PRSTR |= B0; cb(); }
INLINE void RCC_TIM2ResetOff(void) { RCC->APB1PRSTR &= ~B0; cb(); }
INLINE void RCC_TIM2Reset(void) { RCC_TIM2ResetOn(); nop(); RCC_TIM2ResetOff(); }

// TIM3 module reset ON/OFF/Reset
INLINE void RCC_TIM3ResetOn(void) { RCC->APB1PRSTR |= B2; cb(); }
INLINE void RCC_TIM3ResetOff(void) { RCC->APB1PRSTR &= ~B2; cb(); }
INLINE void RCC_TIM3Reset(void) { RCC_TIM3ResetOn(); nop(); RCC_TIM3ResetOff(); }

// Window watchdog reset ON/OFF/Reset
INLINE void RCC_WWDGResetOn(void) { RCC->APB1PRSTR |= B11; cb(); }
INLINE void RCC_WWDGResetOff(void) { RCC->APB1PRSTR &= ~B11; cb(); }
INLINE void RCC_WWDGReset(void) { RCC_WWDGResetOn(); nop(); RCC_WWDGResetOff(); }

// I2C1 module reset ON/OFF/Reset
INLINE void RCC_I2C1ResetOn(void) { RCC->APB1PRSTR |= B21; cb(); }
INLINE void RCC_I2C1ResetOff(void) { RCC->APB1PRSTR &= ~B21; cb(); }
INLINE void RCC_I2C1Reset(void) { RCC_I2C1ResetOn(); nop(); RCC_I2C1ResetOff(); }

// Power module reset ON/OFF/Reset
INLINE void RCC_PWRResetOn(void) { RCC->APB1PRSTR |= B28; cb(); }
INLINE void RCC_PWRResetOff(void) { RCC->APB1PRSTR &= ~B28; cb(); }
INLINE void RCC_PWRReset(void) { RCC_PWRResetOn(); nop(); RCC_PWRResetOff(); }

// ADC reset flag ON/OFF
INLINE void RCC_ADCResetOn(void) { RCC->RSTSCKR |= B23; cb(); }
INLINE void RCC_ADCResetOff(void) { RCC->RSTSCKR &= ~B23; cb(); }
INLINE void RCC_ADCReset(void) { RCC_ADCResetOn(); nop(); RCC_ADCResetOff(); }

// OPA_CMP reset flag ON/OFF
INLINE void RCC_OPAResetOn(void) { RCC->RSTSCKR |= B25; cb(); }
INLINE void RCC_OPAResetOff(void) { RCC->RSTSCKR &= ~B25; cb(); }

// --- Peripheral clock

// DMA1 module clock Enable/Disable
INLINE void RCC_DMA1ClkEnable(void) { RCC->AHBPCENR |= B0; cb(); }
INLINE void RCC_DMA1ClkDisable(void) { RCC->AHBPCENR &= ~B0; cb(); }

// SRAM module clock Enable/Disable (enabled by default)
INLINE void RCC_SRAMClkEnable(void) { RCC->AHBPCENR |= B2; cb(); }
INLINE void RCC_SRAMClkDisable(void) { RCC->AHBPCENR &= ~B2; cb(); }

// I/O auxiliary function module clock Enable/Disable
INLINE void RCC_AFIClkEnable(void) { RCC->APB2PCENR |= B0; cb(); }
INLINE void RCC_AFIClkDisable(void) { RCC->APB2PCENR &= ~B0; cb(); }

// Px port (0=PA, 1=PB, ...) module clock Enable/Disable
INLINE void RCC_PxClkEnable(int portinx) { RCC->APB2PCENR |= (1<<(portinx+2)); cb(); }
INLINE void RCC_PxClkDisable(int portinx) { RCC->APB2PCENR &= ~(1<<(portinx+2)); cb(); }

// PA port module clock Enable/Disable
INLINE void RCC_PAClkEnable(void) { RCC->APB2PCENR |= B2; cb(); }
INLINE void RCC_PAClkDisable(void) { RCC->APB2PCENR &= ~B2; cb(); }

// PB port module clock Enable/Disable
INLINE void RCC_PBClkEnable(void) { RCC->APB2PCENR |= B3; cb(); }
INLINE void RCC_PBClkDisable(void) { RCC->APB2PCENR &= ~B3; cb(); }

// PC port module clock Enable/Disable
INLINE void RCC_PCClkEnable(void) { RCC->APB2PCENR |= B4; cb(); }
INLINE void RCC_PCClkDisable(void) { RCC->APB2PCENR &= ~B4; cb(); }

// PD port module clock Enable/Disable
INLINE void RCC_PDClkEnable(void) { RCC->APB2PCENR |= B5; cb(); }
INLINE void RCC_PDClkDisable(void) { RCC->APB2PCENR &= ~B5; cb(); }

// ADC1 module clock Enable/Disable
INLINE void RCC_ADC1ClkEnable(void) { RCC->APB2PCENR |= B9; cb(); }
INLINE void RCC_ADC1ClkDisable(void) { RCC->APB2PCENR &= ~B9; cb(); }

// TIM1 module clock Enable/Disable
INLINE void RCC_TIM1ClkEnable(void) { RCC->APB2PCENR |= B11; cb(); }
INLINE void RCC_TIM1ClkDisable(void) { RCC->APB2PCENR &= ~B11; cb(); }

// SPI1 module clock Enable/Disable
INLINE void RCC_SPI1ClkEnable(void) { RCC->APB2PCENR |= B12; cb(); }
INLINE void RCC_SPI1ClkDisable(void) { RCC->APB2PCENR &= ~B12; cb(); }

// USART2 module clock Enable/Disable
INLINE void RCC_USART2ClkEnable(void) { RCC->APB2PCENR |= B13; cb(); }
INLINE void RCC_USART2ClkDisable(void) { RCC->APB2PCENR &= ~B13; cb(); }

// USART1 module clock Enable/Disable
INLINE void RCC_USART1ClkEnable(void) { RCC->APB2PCENR |= B14; cb(); }
INLINE void RCC_USART1ClkDisable(void) { RCC->APB2PCENR &= ~B14; cb(); }

// TIM2 module clock Enable/Disable
INLINE void RCC_TIM2ClkEnable(void) { RCC->APB1PCENR |= B0; cb(); }
INLINE void RCC_TIM2ClkDisable(void) { RCC->APB1PCENR &= ~B0; cb(); }

// TIM3 module clock Enable/Disable
INLINE void RCC_TIM3ClkEnable(void) { RCC->APB1PCENR |= B2; cb(); }
INLINE void RCC_TIM3ClkDisable(void) { RCC->APB1PCENR &= ~B2; cb(); }

// Window watchdog clock Enable/Disable
INLINE void RCC_WWDGClkEnable(void) { RCC->APB1PCENR |= B11; cb(); }
INLINE void RCC_WWDGClkDisable(void) { RCC->APB1PCENR &= ~B11; cb(); }

// I2C1 module clock Enable/Disable
INLINE void RCC_I2C1ClkEnable(void) { RCC->APB1PCENR |= B21; cb(); }
INLINE void RCC_I2C1ClkDisable(void) { RCC->APB1PCENR &= ~B21; cb(); }

// Power module clock Enable/Disable
INLINE void RCC_PWRClkEnable(void) { RCC->APB1PCENR |= B28; cb(); }
INLINE void RCC_PWRClkDisable(void) { RCC->APB1PCENR &= ~B28; cb(); }

// Multiply AHB peripheral clock Enable/Disable (use combination of RCC_AHBCLK_* flags)
INLINE void RCC_AHBClkEnable(u32 mask) { RCC->AHBPCENR |= mask; cb(); }
INLINE void RCC_AHBClkDisable(u32 mask) { RCC->AHBPCENR &= ~mask; cb(); }

// Multiply APB2 peripheral clock Enable/Disable (use combination of RCC_APB2CLK_* flags)
INLINE void RCC_APB2ClkEnable(u32 mask) { RCC->APB2PCENR |= mask; cb(); }
INLINE void RCC_APB2ClkDisable(u32 mask) { RCC->APB2PCENR &= ~mask; cb(); }

// Multiply APB1 peripheral clock Enable/Disable (use combination of RCC_APB1CLK_* flags)
INLINE void RCC_APB1ClkEnable(u32 mask) { RCC->APB1PCENR |= mask; cb(); }
INLINE void RCC_APB1ClkDisable(u32 mask) { RCC->APB1PCENR &= ~mask; cb(); }

// --- Reset

// Check occurence of NRST pin reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetPinRes(void) { return (RCC->RSTSCKR & B26) != 0; }

// Check occurence of power reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetPwrRes(void) { return (RCC->RSTSCKR & B27) != 0; }

// Check occurence of software reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetSwRes(void) { return (RCC->RSTSCKR & B28) != 0; }

// Check occurence of independent watchdog reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetIwdgRes(void) { return (RCC->RSTSCKR & B29) != 0; }

// Check occurence of window watchdog reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetWwdgRes(void) { return (RCC->RSTSCKR & B30) != 0; }

// Check occurence of low-power reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetLowPwrRes(void) { return (RCC->RSTSCKR & B31) != 0; }

// Clear all reset flags
INLINE void RCC_ClrRes(void) { RCC->RSTSCKR |= B24; }

#ifdef __cplusplus
}
#endif

#endif // _SDK_RCC_H
