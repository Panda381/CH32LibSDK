
// ****************************************************************************
//
//                               Magic Beater
//
// ****************************************************************************
// Based on RaveBOX v1.0, (c) Vladimir Bartos https://github.com/Mat0ny/RaveBOX

#include "../include.h"

// pins
#define LED	PA1		// output pin to LED
#define AIN	PA2		// ADC input pin
#define KEY_A	PC1		// key A
#define KEY_B	PC2		// key B
#define AUDIO	PC4		// audio output - uses Timer 1, 
#define AINCH	0		// ADC input channel

// setup
#define SUBSEQ	64		// length of sub-sequence
#define SEQLEN	(4*SUBSEQ)	// length of the sequence

// sequence buffers
int	Mem[SEQLEN];		// memory

int main(void)
{
	int i, adc, div;
	int kick = 0;
	int seq = 0;

	// Remap PA1 & PA2 pins to OSC_IN & OSC_OUT (default 0)
	// 0 ... pins PA1 & PA2 are used as GPIO ports
	GPIO_Remap_PA1PA2(0);

	// setup pins
	GPIO_Mode(LED, GPIO_MODE_OUT);		// output pin to LED
	GPIO_Mode(AIN, GPIO_MODE_AIN);		// ADC input pin
	GPIO_Mode(KEY_A, GPIO_MODE_IN_PU);	// key A - input with pull-up
	GPIO_Mode(KEY_B, GPIO_MODE_IN_PU);	// key B - input with pull-up
	GPIO_Mode(AUDIO, GPIO_MODE_AF);		// audio output - uses Timer 1

	// Initialize ADC single conversion mode
	ADC1_InitSingle();

	// setup Timer1, channel 4 (PC4), mapping 0
	// 0 ... PC5:ETR, PD2:CH1, PA1:CH2, PC3:CH3, PC4:CH4, PC2:BKIN, PD0:CH1N, PA2:CH2N, PD1:CH3N
	GPIO_Remap_TIM1(0);			// Timer 1 mapping 0 (channel 4 on pin PC4)
	TIM1_InitPWM(4, HCLK_PER_US, 1000, 500, True); // PWM output to PC4, timer clock 1 MHz
	TIM1_CC4Disable();			// disable sound output

	// main loop
	while (True)
	{
		// ADC input (get 12+4=16 bits)
		adc = ADC1_GetSingleMul(AINCH, 16);

		// save tone
		if (GPIO_In(KEY_A) == 0)
		{
			Mem[seq] = adc;
		}

		// save kick - length is 64/4=16 steps 
		if ((GPIO_In(KEY_B) == 0) || (kick > 0))
		{
			kick += 1500;			// decrease speed
			Mem[seq] = kick;
			if (kick >= 24000) kick = 0;	// stop value = 16*1500 = 24000
		}

		// reset pattern
		if ((GPIO_In(KEY_A) == 0) && (GPIO_In(KEY_B) == 0))
		{
			TIM1_CC4Disable();		// disable sound output
			memset(Mem, 0, sizeof(Mem));	// reset memory
			kick = 0;			// reset kick tone
			while ((GPIO_In(KEY_A) == 0) || (GPIO_In(KEY_B) == 0)) WaitMs(100);
		}

		// set timer
		div = Mem[seq];
		if (div > 0)
		{
			// sound ON
			TIM1_Load(div);		// set timer reload value
			TIM1_Comp4(div>>1);	// set compare value, channel 4
			TIM1_CC4Enable();	// enable compare output
		}
		else
			// sound OFF
			TIM1_CC4Disable();	// disable sound output

		// blinking LED
		i = seq % SUBSEQ;
		if (i == 0) GPIO_Out1(LED);
		if (i == 7) GPIO_Out0(LED);

		// delay
		WaitMs(10);

		// shift sequencer
		seq++;
		if (seq >= SEQLEN) seq = 0;
	}
}
