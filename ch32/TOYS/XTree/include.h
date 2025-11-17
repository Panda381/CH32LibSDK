
// ****************************************************************************
//                                 
//                              Includes
//
// ****************************************************************************

#include INCLUDES_H		// all includes

#define AUDIO_VOICES_POW2	1	// number of voices as power of 2 (0=1 voice, 1=2 voices, 2=4 voices, 3=8 voices)
#define AUDIO_PORT		PC4	// audio output port
#define AUDIO_VOLUME_SHIFT	1	// additional volume 0..7 (0=normal)

// Configuration
#define	AUDIO_CHANNELS		1	// number of audio channels (1=MONO, 2=STEREO)
#define AUDIO_UPDATE_FREQUENCY_SHIFT 15	// PWM playback frequency as power of 2 ... better to use power of 2 to optimise division
#define AUDIO_UPDATE_FREQUENCY	(1<<AUDIO_UPDATE_FREQUENCY_SHIFT) // PWM playback frequency (= 32768)
#define AUDIO_FIFO_SIZE_POW2	8	// audio FIFO size as power of 2 (8=256 samples=256 bytes)

// Audio noise source, system clock
#define AUDIO_NOISE_SOURCE SysTick_Get() 

// Includes
#include "src/audiolib.h"	// audio library
#include "src/main.h"		// main code
