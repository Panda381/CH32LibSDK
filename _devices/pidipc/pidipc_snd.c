
// ****************************************************************************
//
//                             PidiPC - Sound
//
// ****************************************************************************

#include "../../includes.h"

#if USE_SOUND		// 1=use sound support

// pointer to current melody
volatile const sMelodyNote* SoundMelodyPtr;

// pointer to next melody
volatile const sMelodyNote* SoundMelodyNext;

// remaining length of current tone (0 = no melody, -1 = start next melody)
volatile s16 SoundMelodyLen = 0;

/*
// Game sound samples
const sMelodyNote SoundSamp1[] = {
	{ 1, NOTE_C6 },
	{ 1, NOTE_CS6 },
	{ 1, NOTE_D6 },
	{ 1, NOTE_DS6 },
	{ 1, NOTE_E6 },
	{ 1, NOTE_F6 },
	{ 1, NOTE_FS6 },
	{ 1, NOTE_G6 },
	{ 1, NOTE_GS6 },
	{ 1, NOTE_A6 },
	{ 1, NOTE_AS6 },
	{ 1, NOTE_B6 },
	{ 1, NOTE_C7 },
	{ 0, 0 },
};

const sMelodyNote SoundSamp2[] = {
	{ 1, NOTE_C7 },
	{ 1, NOTE_B6 },
	{ 1, NOTE_AS6 },
	{ 1, NOTE_A6 },
	{ 1, NOTE_GS6 },
	{ 1, NOTE_G6 },
	{ 1, NOTE_FS6 },
	{ 1, NOTE_F6 },
	{ 1, NOTE_E6 },
	{ 1, NOTE_DS6 },
	{ 1, NOTE_D6 },
	{ 1, NOTE_CS6 },
	{ 1, NOTE_C6 },

	{ 1, NOTE_B5 },
	{ 1, NOTE_AS5 },
	{ 1, NOTE_A5 },
	{ 1, NOTE_GS5 },
	{ 1, NOTE_G5 },
	{ 1, NOTE_FS5 },
	{ 1, NOTE_F5 },
	{ 1, NOTE_E5 },
	{ 1, NOTE_DS5 },
	{ 1, NOTE_D5 },
	{ 1, NOTE_CS5 },
	{ 1, NOTE_C5 },
	{ 0, 0 },
};

const sMelodyNote SoundSamp3[] = {
	{ 1, NOTE_C4 },
	{ 1, NOTE_CS4 },
	{ 1, NOTE_D4 },
	{ 1, NOTE_DS4 },
	{ 1, NOTE_E4 },
	{ 1, NOTE_F4 },
	{ 1, NOTE_FS4 },
	{ 1, NOTE_G4 },
	{ 1, NOTE_GS4 },
	{ 1, NOTE_A4 },
	{ 1, NOTE_AS4 },
	{ 1, NOTE_B4 },
	{ 1, NOTE_C5 },

	{ 1, NOTE_B4 },
	{ 1, NOTE_AS4 },
	{ 1, NOTE_A4 },
	{ 1, NOTE_GS4 },
	{ 1, NOTE_G4 },
	{ 1, NOTE_FS4 },
	{ 1, NOTE_F4 },
	{ 1, NOTE_E4 },
	{ 1, NOTE_DS4 },
	{ 1, NOTE_D4 },
	{ 1, NOTE_CS4 },
	{ 1, NOTE_C4 },
	{ 0, 0 },
};

const sMelodyNote SoundSamp4[] = {
	{ 1, NOTE_C5 },
	{ 1, NOTE_B5 },
	{ 1, NOTE_CS5 },
	{ 1, NOTE_AS5 },
	{ 1, NOTE_D5 },
	{ 1, NOTE_A5 },
	{ 1, NOTE_DS5 },
	{ 1, NOTE_GS5 },
	{ 1, NOTE_E5 },
	{ 1, NOTE_G5 },
	{ 1, NOTE_F5 },
	{ 1, NOTE_FS5 },
	{ 1, NOTE_F5 },
	{ 0, 0 },
};
*/

// Sound initialize
// The audio output is via PA3 (pin 21), Timer 1 channel 1, mapping 5.
void SoundInit()
{
	// setup output pin
	RCC_AFIClkEnable();
	RCC_PAClkEnable();
	GPIO_Mode(PA3, GPIO_MODE_AF);

	// remap timer 1, use channel 1 on PA3 pin
	// 5 ... PD4:ETR, *PA3:CH1, PB0:CH2, PC3:CH3, PD1:CH4, PB3:BKIN, PA0:CH1N, PA2:CH2N, PD0:CH3N
	GPIO_Remap_TIM1(5);

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

	// set compare value, channel 1
	TIM1_Comp1(500);

	// direction up
	TIM1_DirUp();

	// reload immediately
	TIM1_Update();

	// enable auto-reload of preload compare register
	TIM1_AutoReloadEnable();

	// set compare mode
	TIM1_OC1Mode(TIM_COMP_PWM1);

	// enable preload compare register
	TIM1_OC1PreEnable();

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
	GPIO_PinReset(PA3);
}

// Start playing tone with divider - use macro SND_GET_DIV(hz01) with
//  frequency in 0.01 Hz, minimum 15.26Hz, or use constant NOTE_*
void PlayTone(u32 div)
{
	// set timer reload value
	TIM1_Load(div);

	// set compare value, channel 1
	TIM1_Comp1(div>>1);

	// enable compare output
	TIM1_CC1Enable();
}

// Stop playing tone or melody
void StopSound()
{
	// stop melody
	SoundMelodyLen = 0;

	// disable compare output
	TIM1_CC1Disable();
}

// play melody
//  melody = pointer to array of notes sMelodyNote (terminated with NOTE_STOP)
void PlayMelody(const sMelodyNote* melody)
{
	// set next melody
	SoundMelodyNext = melody;
	cb();

	// request to restart melody
	SoundMelodyLen = -1;
}

#endif // USE_SOUND
