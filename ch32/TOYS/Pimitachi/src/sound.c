
// ****************************************************************************
//
//                                Sound
//
// ****************************************************************************

#include "../include.h"

// Sound initialize
// The audio output is via PC4 (pin 4), Timer 1 channel 4, mapping 0.
void SoundInit()
{
	// setup output pin
	RCC_AFIClkEnable();
	RCC_PCClkEnable();
	GPIO_Mode(PC4, GPIO_MODE_AF);

	// remap timer 1, use channel 4 on PC4 pin
	// 0 ... PC5:ETR, PD2:CH1, PA1:CH2, PC3:CH3, PC4:CH4, PC2:BKIN, PD0:CH1N, PA2:CH2N, PD1:CH3N
	GPIO_Remap_TIM1(0);

	// Enable timer clock source
	TIM1_ClkEnable();

	// Reset timer to default setup
	TIM1_Reset();

	// select input from internal clock CK_INT
	TIM1_InMode(TIM_INMODE_INT);

	// set divider (to get 1 MHz)
	TIM1_Div(SND_TIM_DIV);

	// set timer reload value
	TIM1_Load(1000);

	// set compare value, channel 4
	TIM1_Comp4(500);

	// direction up
	TIM1_DirUp();

	// reload immediately
	TIM1_Update();

	// enable auto-reload of preload compare register
	TIM1_AutoReloadEnable();

	// set compare mode
	TIM1_OC4Mode(TIM_COMP_PWM1);

	// enable preload compare register
	TIM1_OC4PreEnable();

	// enable main output
	TIM1_OCEnable();

	// enable timer
	TIM1_Enable();
}

// Sound terminate
void SoundTerm()
{
	// disable timer
	TIM1_Disable();

	// Reset timer to default setup
	TIM1_Reset();

	// reset output pin
	GPIO_PinReset(PC4);
}

// Start playing tone with divider - use macro SND_GET_DIV(hz01) with
//  frequency in 0.01 Hz, minimum 15.26Hz, or use constant NOTE_*
//  ms = length in [ms]
void PlayTone(u16 div, u16 ms)
{
	// check sound OFF
	if (GetSoundOff() != 0)
	{
		// wait
		WaitMsIWDT(ms);
		return;
	}

	// Sound initialize
	SoundInit();

	// set timer reload value
	TIM1_Load(div);

	// set compare value, channel 4
	TIM1_Comp4(div>>1);

	// enable compare output
	TIM1_CC4Enable();

	// wait
	WaitMsIWDT(ms);

	// disable compare output
	TIM1_CC4Disable();

	// Sound terminate
	SoundTerm();
}

// play melody (mark end of melody with NOTE_STOP)
void PlayMusic(const sTone* m)
{
	while (m->len != NOTE_STOP)
	{
		PlayTone(m->div, m->len);
		m++;
	}
}
