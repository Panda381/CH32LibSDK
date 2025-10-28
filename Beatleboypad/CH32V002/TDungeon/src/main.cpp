
// ****************************************************************************
//
//                                  Tiny-Dungeon
//
// ****************************************************************************

#include "../include.h"

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
	char ch;
	int oldbat;
	int bat;

	// display supply voltage
	if (RunMode == RUNMODE_OLED)
	{
		DrawClear();
		oldbat = -1;
		while (KeyGet() == NOKEY)
		{
			bat = GetSupply() + 50;
			if (oldbat != bat)
			{
				oldbat = bat;
				ch = DecNum(DecNumBuf, bat, '.');
				if (ch == 5)
				{
					DecNumBuf[4] = 'V';
					DrawTextBg(DecNumBuf, (WIDTH-5*8)/2, (HEIGHT-8)/2);
					DispUpdate();
				}
			}
		}
		KeyWaitNoPressed();
	}

	// Game setup
	setup();

	// Main program loop
	loop();

	while (True) {}
}
