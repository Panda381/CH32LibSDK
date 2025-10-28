
// ****************************************************************************
//
//                                  Train game
//
// ****************************************************************************

#include "../include.h"

int main(void)
{
	char ch;
	int i;
	int oldbat;
	int bat;

	// set first scene
	Level = LEVFIRST;
	Score = 0;

	while (True)
	{
		// display splash screen
		i = Level;
		Level = 0;
		InitLevel();
		KeyFlush();
		oldbat = -1;
		while ((ch = KeyGet()) == NOKEY)
		{
			bat = GetSupply() + 50;
			if (oldbat != bat)
			{
				oldbat = bat;
				ch = DecNum(DecNumBuf, bat, '.');
				if (ch == 5)
				{
					DecNumBuf[4] = 'V';
					DrawTextCond6Bg(DecNumBuf, WIDTH-5*7, HEIGHT-5);
					DispUpdate();
				}
			}
		}

		// randomize
		RandSeed += Time();

		// clear display
		DrawClear();

		// return current level
		Level = i;
		InitLevel();

		// main loop
		while (True)
		{
			// game loop - called every single game step
			if (GameLoop()) break;

			// wait step
			WaitStep();
		}
	}
}
