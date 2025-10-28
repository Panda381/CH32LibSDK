
// ****************************************************************************
//
//                              Sokoban game
//
// ****************************************************************************

#include "../include.h"

// wait for a character
char WaitChar()
{
	char c;
	while ((c = KeyGet()) == NOKEY) {}
	return c;
}

int main(void)
{
	char ch;
	int oldbat;
	int bat;

restart:
	WaitMs(100);
	KeyFlush();

	// display splash screen
	DrawImgBg(ImgIntro, 0, 0, WIDTH, HEIGHT, WIDTHBYTE);
	DispUpdate();
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
				DrawTextCond6Bg(DecNumBuf, WIDTH-5*6, HEIGHT-6);
				DispUpdate();
			}
		}
	}

	// randomize
	RandSeed += Time();

	// clear display
	DrawClear();

	while (True)
	{
		// select level
		if (!LevSelect()) goto restart;

		// game loop
		GameLoop();
	}
}
