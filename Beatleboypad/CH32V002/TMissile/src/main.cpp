
// ****************************************************************************
//
//                                  Tiny-Missile game
//
// ****************************************************************************

#include "../include.h"

//#include "src/spritebank.h"

// play sound tone
void Sound(uint8_t freq, uint8_t dur)
{
	if (freq == 0)
		WaitMs(dur);
	else
	{
// tone period = 510 - 2*freq [us]
// frequency in [Hz] = 1000000/(510-2*freq)
// divider = 1000000 / (1000000/(510-2*freq)) - 1 = 509 - 2*freq
// tone length = dur * (510-2*freq) [us]

		int n = (510 - 2*freq);
		PlayTone(n - 1);
		n *= dur;
		n += n/2; // /2 = a slight prolongation, because the original is slowed down by a “for” loop
		WaitUs(n);
		StopSound();
	}
}

int main(void)
{
	// Game setup
	setup();

	// Main program loop
	loop();
}
