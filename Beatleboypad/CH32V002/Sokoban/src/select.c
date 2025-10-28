
// ****************************************************************************
//
//                                 Select
//
// ****************************************************************************

#include "../include.h"

#define LEVW	3	// width of one level (3*6 = 18 pixels)
#define ROWLEV	7	// number of level columns per row (7*18 = 126 pixels, start X = 1)
// total 10 rows, 10*6 = 60 lines, start Y = 2
// total 10*7 = 70 levels

// print 1 level
void LevSelect1(int inx)
{
	// prepare coordinates on screen
	int n = inx/ROWLEV;
	int y = n*6 + 2; // Y coordinate
	int x = (inx - n*ROWLEV)*LEVW*6 + 1; // X coordinate

	// prepare number
	char buf[5];
	n = DecNum(buf, inx+1, 0);

	// draw
	if (inx == Level)
	{
		DrawRect(x, y, LEVW*6, 6, COL_WHITE);
		x += 3;
		if (n < 2) x += 3;
		DrawTextCond6(buf, x, y, COL_BLACK);
	}
	else
	{
		DrawRect(x, y, LEVW*6, 6, COL_BLACK);
		x += 3;
		if (n < 2) x += 3;
		DrawTextCond6(buf, x, y, COL_WHITE);
	}
}

// select level (returns True = OK, False = Esc)
Bool LevSelect()
{
	DrawClear();

	// print list of levels
	int i;
	for (i = 0; i < LevNum; i++)
	{
		LevSelect1(i);
	}

	// select
	char c;
	int j;
	for (;;)
	{
		DispUpdate();

		// get character
		c = WaitChar();

		switch (c)
		{
		case KEY_UP:
			i = Level;
			Level = -1;
			LevSelect1(i);
			i -= ROWLEV;
			if (i < 0)
			{
				do i += ROWLEV; while (i < LevNum);
				i -= ROWLEV;
				if (i < 0) i += ROWLEV;
			}
			Level = i;
			LevSelect1(i);

			LevDef = Levels[i*2]; // current level definition
			LevSolve = Levels[i*2+1]; // current level solve
			break;

		case KEY_LEFT:
			i = Level;
			Level = -1;
			LevSelect1(i);
			i--;
			if (i < 0) i = LevNum-1;
			Level = i;
			LevSelect1(i);

			LevDef = Levels[i*2]; // current level definition
			LevSolve = Levels[i*2+1]; // current level solve
			break;

		case KEY_DOWN:
			i = Level;
			Level = -1;
			LevSelect1(i);
			i += ROWLEV;
			if (i >= LevNum)
			{
				do i -= ROWLEV; while (i >= 0);
				i += ROWLEV;
				if (i >= LevNum) i -= ROWLEV;
			}
			Level = i;
			LevSelect1(i);

			LevDef = Levels[i*2]; // current level definition
			LevSolve = Levels[i*2+1]; // current level solve
			break;

		case KEY_RIGHT:
			i = Level;
			Level = -1;
			LevSelect1(i);
			i++;
			if (i > LevNum-1) i = 0;
			Level = i;
			LevSelect1(i);

			LevDef = Levels[i*2]; // current level definition
			LevSolve = Levels[i*2+1]; // current level solve
			break;

		case KEY_A: // select
			LevDef = Levels[i*2]; // current level definition
			LevSolve = Levels[i*2+1]; // current level solve
			return True;

		case KEY_B:
			return False;
		}
	}
}
