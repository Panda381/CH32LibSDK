
// ****************************************************************************
//
//                               Pianissimo
//
// ****************************************************************************

#include "../include.h"

// pins
#define COL1	PC2		// column 1
#define COL2	PC3		// column 2
#define COL3	PC4		// column 3
#define COL4	PC0		// column 4
#define COL5	PC1		// column 5
#define ROW1	PD7		// row 1
#define ROW2	PD6		// row 2
#define ROW3	PD5		// row 3
#define ROW4	PC6		// row 4
#define ROW5	PC7		// row 5
#define AUDIO	PD4		// audio output

#define TIMESTEP  20		// time step in number of [ms]

#define RECORD_MAX	3750	// size of record buffer in bytes

#define COLNUM	5	// number of columns
const u8 ColPin[COLNUM] = { COL1, COL2, COL3, COL4, COL5 }; // column pins

#define ROWNUM	5	// number of rows
const u8 RowPin[ROWNUM] = { ROW1, ROW2, ROW3, ROW4, ROW5 }; // row pins

#define KEYNUM	(COLNUM*ROWNUM)	// number of keys
#define MODEKEY	(KEYNUM-1)	// index of MODE key

// get divider of the tone in 0.01 Hz (minimum 16 Hz), time base is 1 MHz
#define SND_GET_DIV(hz01) ((100*1000000 + (hz01)/2)/(hz01) - 1)

// tones
#define NOTE_C0		SND_GET_DIV(1635)	// note=C0 (16.3516Hz)
#define NOTE_CS0	SND_GET_DIV(1732)	// note=C#0 (17.3239Hz)
#define NOTE_D0		SND_GET_DIV(1835)	// note=D0 (18.354Hz)
#define NOTE_DS0	SND_GET_DIV(1945)	// note=D#0 (19.4454Hz)
#define NOTE_E0		SND_GET_DIV(2060)	// note=E0 (20.6017Hz)
#define NOTE_F0		SND_GET_DIV(2183)	// note=F0 (21.8268Hz)
#define NOTE_FS0	SND_GET_DIV(2312)	// note=F#0 (23.1247Hz)
#define NOTE_G0		SND_GET_DIV(2450)	// note=G0 (24.4997Hz)
#define NOTE_GS0	SND_GET_DIV(2596)	// note=G#0 (25.9565Hz)
#define NOTE_A0		SND_GET_DIV(2750)	// note=A0 (27.5Hz)
#define NOTE_AS0	SND_GET_DIV(2914)	// note=A#0 (29.1352Hz)
#define NOTE_B0		SND_GET_DIV(3087)	// note=B0 (30.8677Hz)

#define NOTE_C1		SND_GET_DIV(3270)	// note=C1 (32.7032Hz)
#define NOTE_CS1	SND_GET_DIV(3465)	// note=C#1 (34.6478Hz)
#define NOTE_D1		SND_GET_DIV(3671)	// note=D1 (36.7081Hz)
#define NOTE_DS1	SND_GET_DIV(3889)	// note=D#1 (38.8909Hz)
#define NOTE_E1		SND_GET_DIV(4120)	// note=E1 (41.2034Hz)
#define NOTE_F1		SND_GET_DIV(4365)	// note=F1 (43.6535Hz)
#define NOTE_FS1	SND_GET_DIV(4625)	// note=F#1 (46.2493Hz)
#define NOTE_G1		SND_GET_DIV(4900)	// note=G1 (48.9994Hz)
#define NOTE_GS1	SND_GET_DIV(5191)	// note=G#1 (51.9131Hz)
#define NOTE_A1		SND_GET_DIV(5500)	// note=A1 (55Hz)
#define NOTE_AS1	SND_GET_DIV(5827)	// note=A#1 (58.2705Hz)
#define NOTE_B1		SND_GET_DIV(6174)	// note=B1 (61.7354Hz)

#define NOTE_C2		SND_GET_DIV(6541)	// note=C2 (65.4064Hz)
#define NOTE_CS2	SND_GET_DIV(6930)	// note=C#2 (69.2957Hz)
#define NOTE_D2		SND_GET_DIV(7342)	// note=D2 (73.4162Hz)
#define NOTE_DS2	SND_GET_DIV(7778)	// note=D#2 (77.7817Hz)
#define NOTE_E2		SND_GET_DIV(8241)	// note=E2 (82.4069Hz)
#define NOTE_F2		SND_GET_DIV(8731)	// note=F2 (87.3071Hz)
#define NOTE_FS2	SND_GET_DIV(9250)	// note=F#2 (92.4986Hz)
#define NOTE_G2		SND_GET_DIV(9800)	// note=G2 (97.9989Hz)
#define NOTE_GS2	SND_GET_DIV(10383)	// note=G#2 (103.826Hz)
#define NOTE_A2		SND_GET_DIV(11000)	// note=A2 (110Hz)
#define NOTE_AS2	SND_GET_DIV(11654)	// note=A#2 (116.541Hz)
#define NOTE_B2		SND_GET_DIV(12347)	// note=B2 (123.471Hz)

#define NOTE_C3		SND_GET_DIV(13081)	// note=C3 (130.813Hz)
#define NOTE_CS3	SND_GET_DIV(13859)	// note=C#3 (138.591Hz)
#define NOTE_D3		SND_GET_DIV(14683)	// note=D3 (146.832Hz)
#define NOTE_DS3	SND_GET_DIV(15556)	// note=D#3 (155.563Hz)
#define NOTE_E3		SND_GET_DIV(16481)	// note=E3 (164.814Hz)
#define NOTE_F3		SND_GET_DIV(17461)	// note=F3 (174.614Hz)
#define NOTE_FS3	SND_GET_DIV(18500)	// note=F#3 (184.997Hz)
#define NOTE_G3		SND_GET_DIV(19600)	// note=G3 (195.998Hz)
#define NOTE_GS3	SND_GET_DIV(20765)	// note=G#3 (207.652Hz)
#define NOTE_A3		SND_GET_DIV(22000)	// note=A3 (220Hz)
#define NOTE_AS3	SND_GET_DIV(23308)	// note=A#3 (233.082Hz)
#define NOTE_B3		SND_GET_DIV(24694)	// note=B3 (246.942Hz)

#define NOTE_C4		SND_GET_DIV(26163)	// note=C4 (261.626Hz)
#define NOTE_CS4	SND_GET_DIV(27718)	// note=C#4 (277.183Hz)
#define NOTE_D4		SND_GET_DIV(29367)	// note=D4 (293.665Hz)
#define NOTE_DS4	SND_GET_DIV(31113)	// note=D#4 (311.127Hz)
#define NOTE_E4		SND_GET_DIV(32963)	// note=E4 (329.628Hz)
#define NOTE_F4		SND_GET_DIV(34923)	// note=F4 (349.228Hz)
#define NOTE_FS4	SND_GET_DIV(36999)	// note=F#4 (369.994Hz)
#define NOTE_G4		SND_GET_DIV(39200)	// note=G4 (391.995Hz)
#define NOTE_GS4	SND_GET_DIV(41531)	// note=G#4 (415.305Hz)
#define NOTE_A4		SND_GET_DIV(44000)	// note=A4 (440Hz)
#define NOTE_AS4	SND_GET_DIV(46616)	// note=A#4 (466.164Hz)
#define NOTE_B4		SND_GET_DIV(49388)	// note=B4 (493.883Hz)

#define NOTE_C5		SND_GET_DIV(52325)	// note=C5 (523.251Hz)
#define NOTE_CS5	SND_GET_DIV(55437)	// note=C#5 (554.365Hz)
#define NOTE_D5		SND_GET_DIV(58733)	// note=D5 (587.33Hz)
#define NOTE_DS5	SND_GET_DIV(62225)	// note=D#5 (622.254Hz)
#define NOTE_E5		SND_GET_DIV(65926)	// note=E5 (659.255Hz)
#define NOTE_F5		SND_GET_DIV(69846)	// note=F5 (698.456Hz)
#define NOTE_FS5	SND_GET_DIV(73999)	// note=F#5 (739.989Hz)
#define NOTE_G5		SND_GET_DIV(78399)	// note=G5 (783.991Hz)
#define NOTE_GS5	SND_GET_DIV(83061)	// note=G#5 (830.609Hz)
#define NOTE_A5		SND_GET_DIV(88000)	// note=A5 (880Hz)
#define NOTE_AS5	SND_GET_DIV(93233)	// note=A#5 (932.328Hz)
#define NOTE_B5		SND_GET_DIV(98777)	// note=B5 (987.767Hz)

#define NOTE_C6		SND_GET_DIV(104650)	// note=C6 (1046.5Hz)
#define NOTE_CS6	SND_GET_DIV(110873)	// note=C#6 (1108.73Hz)
#define NOTE_D6		SND_GET_DIV(117466)	// note=D6 (1174.66Hz)
#define NOTE_DS6	SND_GET_DIV(124451)	// note=D#6 (1244.51Hz)
#define NOTE_E6		SND_GET_DIV(131851)	// note=E6 (1318.51Hz)
#define NOTE_F6		SND_GET_DIV(139691)	// note=F6 (1396.91Hz)
#define NOTE_FS6	SND_GET_DIV(147998)	// note=F#6 (1479.98Hz)
#define NOTE_G6		SND_GET_DIV(156798)	// note=G6 (1567.98Hz)
#define NOTE_GS6	SND_GET_DIV(166122)	// note=G#6 (1661.22Hz)
#define NOTE_A6		SND_GET_DIV(176000)	// note=A6 (1760Hz)
#define NOTE_AS6	SND_GET_DIV(186466)	// note=A#6 (1864.66Hz)
#define NOTE_B6		SND_GET_DIV(197553)	// note=B6 (1975.53Hz)

#define NOTE_C7		SND_GET_DIV(209300)	// note=C7 (2093Hz)
#define NOTE_CS7	SND_GET_DIV(221746)	// note=C#7 (2217.46Hz)
#define NOTE_D7		SND_GET_DIV(234932)	// note=D7 (2349.32Hz)
#define NOTE_DS7	SND_GET_DIV(248902)	// note=D#7 (2489.02Hz)
#define NOTE_E7		SND_GET_DIV(263702)	// note=E7 (2637.02Hz)
#define NOTE_F7		SND_GET_DIV(279383)	// note=F7 (2793.83Hz)
#define NOTE_FS7	SND_GET_DIV(295996)	// note=F#7 (2959.96Hz)
#define NOTE_G7		SND_GET_DIV(313596)	// note=G7 (3135.96Hz)
#define NOTE_GS7	SND_GET_DIV(332244)	// note=G#7 (3322.44Hz)
#define NOTE_A7		SND_GET_DIV(352000)	// note=A7 (3520Hz)
#define NOTE_AS7	SND_GET_DIV(372931)	// note=A#7 (3729.31Hz)
#define NOTE_B7		SND_GET_DIV(395107)	// note=B7 (3951.07Hz)

#define NOTE_C8		SND_GET_DIV(418601)	// note=C8 (4186.01Hz)
#define NOTE_CS8	SND_GET_DIV(443492)	// note=C#8 (4434.92Hz)
#define NOTE_D8		SND_GET_DIV(469864)	// note=D8 (4698.64Hz)
#define NOTE_DS8	SND_GET_DIV(497803)	// note=D#8 (4978.03Hz)
#define NOTE_E8		SND_GET_DIV(527404)	// note=E8 (5274.04Hz)
#define NOTE_F8		SND_GET_DIV(558765)	// note=F8 (5587.65Hz)
#define NOTE_FS8	SND_GET_DIV(591991)	// note=F#8 (5919.91Hz)
#define NOTE_G8		SND_GET_DIV(627193)	// note=G8 (6271.93Hz)
#define NOTE_GS8	SND_GET_DIV(664488)	// note=G#8 (6644.88Hz)
#define NOTE_A8		SND_GET_DIV(704000)	// note=A8 (7040Hz)
#define NOTE_AS8	SND_GET_DIV(745862)	// note=A#8 (7458.62Hz)
#define NOTE_B8		SND_GET_DIV(790213)	// note=B8 (7902.13Hz)

#define NOTE_C9		SND_GET_DIV(837202)	// note=C9 (8372.02Hz)
#define NOTE_CS9	SND_GET_DIV(886984)	// note=C#9 (8869.84Hz)
#define NOTE_D9		SND_GET_DIV(939727)	// note=D9 (9397.27Hz)
#define NOTE_DS9	SND_GET_DIV(995606)	// note=D#9 (9956.06Hz)
#define NOTE_E9		SND_GET_DIV(1054810)	// note=E9 (10548.1Hz)
#define NOTE_F9		SND_GET_DIV(1117530)	// note=F9 (11175.3Hz)
#define NOTE_FS9	SND_GET_DIV(1183980)	// note=F#9 (11839.8Hz)
#define NOTE_G9		SND_GET_DIV(1254390)	// note=G9 (12543.9Hz)
#define NOTE_GS9	SND_GET_DIV(1328980)	// note=G#9 (13289.8Hz)
#define NOTE_A9		SND_GET_DIV(1408000)	// note=A9 (14080Hz)
#define NOTE_AS9	SND_GET_DIV(1491720)	// note=A#9 (14917.2Hz)
#define NOTE_B9		SND_GET_DIV(1580430)	// note=B9 (15804.3Hz)

// key tones
const u16 KeyTone[KEYNUM-1] = {
	NOTE_F4,
	NOTE_FS4,
	NOTE_G4,
	NOTE_GS4,
	NOTE_A4,
	NOTE_AS4,
	NOTE_B4,

	NOTE_C5,
	NOTE_CS5,
	NOTE_D5,
	NOTE_DS5,
	NOTE_E5,
	NOTE_F5,
	NOTE_FS5,
	NOTE_G5,
	NOTE_GS5,
	NOTE_A5,
	NOTE_AS5,
	NOTE_B5,

	NOTE_C6,
	NOTE_CS6,
	NOTE_D6,
	NOTE_DS6,
	NOTE_E6,
};

// record buffer (1 byte = key, or -1 = pause; 1 step = 20 ms, max. length 75 seconds)
s8 Record[RECORD_MAX];		// record of melody
int RecordNum = 0;		// number of entries in record of melody

// interrupt on key rising edge
HANDLER void EXTI7_0_IRQHandler()
{
	// clear all interrupt requests
	EXTI->INTFR = 0x3ff;
}

int main(void)
{
	int i, col, row, oldkey, key, pin, playing;
	u16 div;
	u32 last;
	Bool mode, oldmode, recording;

	// switch PD7 to GPIO mode, if not already set
	if (((OB->USER >> 3) & 3) != 3)
	{
		OB_t ob;
		Flash_OBRead(&ob);	// read option bytes
		ob.USER |= B3|B4;	// disable RESET function
		Flash_OBWrite(&ob);	// write new option bytes
	}

	// setup pins
	for (col = 0; col < COLNUM; col++) GPIO_Mode(ColPin[col], GPIO_MODE_IN_PD); // column - input with pull-down
	for (row = 0; row < ROWNUM; row++)
	{
		GPIO_Out1(RowPin[row]);	// row - output HIGH
		GPIO_Mode(RowPin[row], GPIO_MODE_IN); // row - input
	}
	GPIO_Mode(AUDIO, GPIO_MODE_AF);		// audio output - uses Timer 1

	// setup Timer1, channel 4 (PD4), mapping 3
	// 3 ... PC2:ETR, PC4:CH1, PC7:CH2, PC5:CH3, PD4:CH4, PC1:BKIN, PC3:CH1N, PD2:CH2N, PC6:CH3N
	GPIO_Remap_TIM1(3);			// Timer 1 mapping 0 (channel 4 on pin PD4)
	TIM1_InitPWM(4, HCLK_PER_US, 1000, 500, True); // PWM output to PC4, timer clock 1 MHz
	TIM1_CC4Disable();			// disable sound output

	// setup EXTI pins, raise interrupt on rising edge
	for (col = 0; col < COLNUM; col++)
	{
		pin = ColPin[col];		// get column gpio
		i = GPIO_PIN(pin);		// get pin index
		GPIO_EXTILine(GPIO_PORTINX(pin), i); // mapping external interrupt input pin
		EXTI_RiseEnable(i);		// enable EXTI on rising edge
		EXTI_Enable(i);			// enable EXTI line interrupt
	}

	// init variables
	oldkey = -1;		// no key was pressed
	oldmode = False;	// no mode was pressed
	playing = -1;		// index of playing melody (-1 = not playing)
	recording = False;	// flag of recording
	last = Time();		// save last pressed time (to check time-out to go sleep)

	// main loop
	while (True)
	{
		// delay - to reduce the effect of button jams
		WaitMs(TIMESTEP);

		// scan keyboard (get highest pressed key, and get MODE key)
		key = -1; // key not pressed
		mode = False; // MODE key not pressed
		for (row = 0; row < ROWNUM; row++) // loop rows
		{
			// set ROW to HIGH
			GPIO_Mode(RowPin[row], GPIO_MODE_OUT); // row - output, out state is HIGH

			// short delay
			WaitUs(10);

			// loop columns
			for (col = 0; col < COLNUM; col++)
			{
				// is key selected? ... we use highest key (not MODE key)
				if (GPIO_In(ColPin[col]) != 0)
				{
					i = row*COLNUM + col;
					if (i == MODEKEY) // MODE key pressed
						mode = True;
					else
						key = i; // key pressed
				}
			}

			// set ROW off
			GPIO_Mode(RowPin[row], GPIO_MODE_IN); // row - input
		}

		// MODE change
		if (mode != oldmode)
		{
			oldmode = mode;

			// release MODE
			if (!mode)
			{
				// stop recording
				if (recording)
				{
					recording = False;
				}
				else
				{
					// start playing
					if (playing < 0)
					{
						if (RecordNum > 0) playing = 0;
					}
					else
					{
						// stop plaing
						playing = -1;
					}
				}
			}
		}

		// start recording
		if (mode && !recording && (key >= 0))
		{
			recording = True;
			RecordNum = 0;
		}

		// record melody
		if (recording)
		{
			if (RecordNum < RECORD_MAX)
			{
				Record[RecordNum++] = (s8)key;
			}
		}

		// play melody
		if (playing >= 0)
		{
			if (key >= 0) // stop playing if press key
				playing = -1;
			else
			{
				key = Record[playing]; // get key from record buffer
				playing++;
				if (playing >= RecordNum) playing = -1; // end of melody
			}
		}

		// play tone
		if (key != oldkey)
		{
			oldkey = key;
			if (key >= 0)
			{
				// sound ON
				div = KeyTone[key];
				TIM1_Load(div);		// set timer reload value
				TIM1_Comp4(div>>1);	// set compare value, channel 4
				TIM1_CC4Enable();	// enable compare output
			}
			else
			{
				// sound OFF
				TIM1_CC4Disable();	// disable sound output
			}
		}

		// something was pressed - save last time (to check time-out to go sleep)
		if ((key >= 0) || mode || (playing >= 0))
		{
			last = Time();		// save last time
		}

		// time-out 5 seconds to go to power off
		else
		{
			if ((u32)(Time() - last) >= 5*1000000*HCLK_PER_US)
			{
				// set all rows to HIGH
				for (row = 0; row < ROWNUM; row++) // loop rows
				{
					GPIO_Mode(RowPin[row], GPIO_MODE_OUT);
				}

				// disable SysTick counter
				SysTick_Disable();

				// clear all interrupt requests
				EXTI->INTFR = 0x3ff;

				// enable EXTI interrupt service
				NVIC_IRQEnable(IRQ_EXTI7);

				// Enter standby mode ... continue after wake-up from EXTI
				PWR_EnterStandby();

				// set all rows OFF
				for (row = 0; row < ROWNUM; row++) // loop rows
				{
					GPIO_Mode(RowPin[row], GPIO_MODE_IN);
				}

				// disable EXTI interrupt
				NVIC_IRQDisable(IRQ_EXTI7);

				// enable SysTick counter
				SysTick_Enable();

				// something was pressed - save last time
				last = Time();
			}
		}
	}
}
