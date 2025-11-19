
// ****************************************************************************
//
//                                   MiniDice
//
// ****************************************************************************

#include "../include.h"

// display number 1..6
u8 DispNum = 1;

// display phase 0..2
u8 DispPhase = 0;

// key press time
u32 PressTime;

// output and input pins
#define OUT1	PA1
#define OUT2	PA2
#define OUT3	PC1
#define OUT4	PC2
#define IN	PC4

// LED pins
#define LED1H	OUT1
#define LED1L	OUT2
#define LED2H	OUT1
#define LED2L	OUT3
#define LED3H	OUT3
#define LED3L	OUT1
#define LED4H	OUT4
#define LED4L	OUT2
#define LED5H	OUT2
#define LED5L	OUT4
#define LED6H	OUT3
#define LED6L	OUT4
#define LED7H	OUT2
#define LED7L	OUT1

// LED1      LED4
//
// LED2 LED7 LED5
//
// LED3      LED6

// LED stage
#define S0	0	// no LED
#define S1	1	// LED1 + LED6 (left top + right bottom)
#define S2	2	// LED3 + LED4 (left bottom + right top)
#define S3	3	// LED2 + LED5 (left middle + right middle)
#define S4	4	// LED7 (center)

const u8 LedStage[3*6] = {
	S4, S0, S0,	// 1
	S3, S0, S0,	// 2
	S2, S4, S0,	// 3
	S1, S2, S0,	// 4
	S1, S2, S4,	// 5
	S1, S2, S3,	// 6
};

// interrupt to serve LEDs - called from SysTick every 2 ms, whole cycle takes 6ms (=167 Hz)
void KeyScan(void)
{
	// set OFF all outputs
	GPIO_Mode(OUT1, GPIO_MODE_IN);
	GPIO_Mode(OUT2, GPIO_MODE_IN);
	GPIO_Mode(OUT3, GPIO_MODE_IN);
	GPIO_Mode(OUT4, GPIO_MODE_IN);

	// get display number
	int num = DispNum;

	// get display phase, increment it
	int phase = DispPhase + 1;
	if (phase > 2) phase = 0;
	DispPhase = phase;

	// get current stage
	int stage = LedStage[(num - 1)*3 + phase];

	// setup outputs
	switch (stage)
	{
	// S0: no LED
	default:
		break;

	// S1: LED1 + LED6 (left top + right bottom)
	case S1:
		GPIO_Out1(OUT1); GPIO_Mode(OUT1, GPIO_MODE_OUT);
		GPIO_Out0(OUT2); GPIO_Mode(OUT2, GPIO_MODE_OUT);
		GPIO_Out1(OUT3); GPIO_Mode(OUT3, GPIO_MODE_OUT);
		GPIO_Out0(OUT4); GPIO_Mode(OUT4, GPIO_MODE_OUT);
		break;

	// S2: LED3 + LED4 (left bottom + right top)
	case S2:
		GPIO_Out0(OUT1); GPIO_Mode(OUT1, GPIO_MODE_OUT);
		GPIO_Out0(OUT2); GPIO_Mode(OUT2, GPIO_MODE_OUT);
		GPIO_Out1(OUT3); GPIO_Mode(OUT3, GPIO_MODE_OUT);
		GPIO_Out1(OUT4); GPIO_Mode(OUT4, GPIO_MODE_OUT);
		break;

	// S3: LED2 + LED5 (left middle + right middle)
	case S3:
		GPIO_Out1(OUT1); GPIO_Mode(OUT1, GPIO_MODE_OUT);
		GPIO_Out1(OUT2); GPIO_Mode(OUT2, GPIO_MODE_OUT);
		GPIO_Out0(OUT3); GPIO_Mode(OUT3, GPIO_MODE_OUT);
		GPIO_Out0(OUT4); GPIO_Mode(OUT4, GPIO_MODE_OUT);
		break;

	// S4: LED7 (center)
	case S4:
		GPIO_Out0(OUT1); GPIO_Mode(OUT1, GPIO_MODE_OUT);
		GPIO_Out1(OUT2); GPIO_Mode(OUT2, GPIO_MODE_OUT);
		break;
	}
}

int main(void)
{
	int i;

	// Remap PA1 & PA2 pins to OSC_IN & OSC_OUT (default 0)
	// 0 ... pins PA1 & PA2 are used as GPIO ports
	GPIO_Remap_PA1PA2(0);

	// setup key pin
	GPIO_Mode(IN, GPIO_MODE_IN_PU);

#if 0
	// DEBUG: self-test, counts 6..1
	for (i = 6; i >= 1; i--)
	{
		DispNum = i;
		WaitMs(1000);
	}
#endif

	// setup key press time (10 seconds to the past)
	PressTime = Time() - 10*1000000*HCLK_PER_US;

	// main loop
	while (True)
	{
		// key is pressed
		if (GPIO_In(IN) == 0) PressTime = Time();

		// rolling the dice for minimal time 1.5 second after releasing
		if ((u32)(Time() - PressTime) < 1500000*HCLK_PER_US)
		{
			DispNum = RandU8MinMax(1, 6);
			WaitMs(50);
		}
	}
}
