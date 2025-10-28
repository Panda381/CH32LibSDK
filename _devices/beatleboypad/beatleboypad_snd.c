
// ****************************************************************************
//
//                             BeatleBoyPad - Sound
//
// ****************************************************************************

#include "../../includes.h"

#if USE_SOUND		// use sound support 1=tone, 2=melody

#if USE_SOUND == 2	// use sound support 1=tone, 2=melody
// pointer to current melody
const sMelodyNote* volatile SoundMelodyPtr;

// pointer to next melody
const sMelodyNote* volatile SoundMelodyNext;

// remaining length of current tone (0 = no melody, -1 = start next melody)
volatile s16 SoundMelodyLen = 0;

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
#endif // USE_SOUND

// Sound initialize
// The audio output is via PC4, Timer 1, channel 4, mapping 0.
void SoundInit()
{
	// setup output pins
	RCC_AFIClkEnable();
	RCC_PCClkEnable();
	GPIO_Mode(PC4, GPIO_MODE_AF);

	// Remap Timer 1
// V002, V006:	0 ... PC5:ETR, PD2:CH1, PA1:CH2, PC3:CH3, PC4:CH4, PC2:BKIN, PD0:CH1N, PA2:CH2N, PD1:CH3N
// V003:	0 ... PC5:ETR, PD2:CH1, PA1:CH2, PC3:CH3, PC4:CH4, PC2:BKIN, PD0:CH1N, PA2:CH2N, PD1:CH3N
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

	// reset output pins
	GPIO_PinReset(PC4);
}

// Start playing tone with divider - use macro SND_GET_DIV(hz01) with
//  frequency in 0.01 Hz, minimum 15.26Hz, or use constant NOTE_*
void PlayTone(u32 div)
{
	// set timer reload value
	TIM1_Load(div);

	// set compare value, channel 4
	TIM1_Comp4(div>>1);

	// enable compare output
	TIM1_CC4Enable();
}

// Stop playing tone or melody
void StopSound()
{
#if USE_SOUND == 2	// use sound support 1=tone, 2=melody
	// stop melody
	SoundMelodyLen = 0;
#endif

	// disable compare output
	TIM1_CC4Disable();
}

#if USE_SOUND == 2	// use sound support 1=tone, 2=melody
// Sound scan melody
void SoundScan()
{
	// get churrent melody
	int len = SoundMelodyLen;	
	if (len == 0) return; // no melody

	// pointer to current melody
	const sMelodyNote* ptr;

	// start next melody
	if (len < 0)
	{
		// get pointer to next melody
		ptr = SoundMelodyNext;
	}

	// continue melody - decrease counter of current tone
	else
	{
		len--;
		SoundMelodyLen = (s16)len; // save new tone length

		// continue current tone
		if (len > 0) return;

		// shift current melody pointer
		ptr = SoundMelodyPtr;	// get pointer to current melody
		ptr++;			// shift pointer to next tone
	}

	// save new pointer to current melody
	SoundMelodyPtr = ptr;

	// get length of next note
	len = ptr->len;	// get length of the note
	SoundMelodyLen = (s16)len;	// save length of new note

	// end of melody
	if (len == 0)
	{
		// disable compare output
		TIM1_CC4Disable();
	}

	// start new note
	else
	{
		// get note divider
		u16 div = ptr->div;

		// pause
		if (div == 0)
		{
			// disable compare output
			TIM1_CC4Disable();
		}
		else
		{
			// start playing tone
			PlayTone(div);
		}
	}
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

#endif // USE_SOUND
