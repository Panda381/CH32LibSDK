
// ****************************************************************************
//
//                                  Life game
//
// ****************************************************************************

#include "../include.h"

// bit 0..1 (2 bits): current cell
// bit 2..3 (2 bits): save cell state
// bit 4..7 (4 bits): number of neighbors
#define CELL_SHIFT	0	// curent cell shift
#define CELL_MASK	3	// current cell mask
#define SAVE_SHIFT	2	// save cell state shift
#define SAVE_MASK	3	// save cell state mask
#define NEIGH_SHIFT	4	// number of neighbors shift
#define NEIGH_MASK	0x0f	// number of neighbors mask

// game board (=510 B)
u8 Board[MAPSIZE];

// get cell
int GetCell(int x, int y)
{
	return (Board[x + y*MAPW0] >> CELL_SHIFT) & CELL_MASK;
}

// set cell
void SetCell(int x, int y, int cell)
{
	u8* d = &Board[x + y*MAPW0];
	*d = (*d & ~(CELL_MASK << CELL_SHIFT)) | (cell << CELL_SHIFT);
}

// get save cell state
int GetSave(int x, int y)
{
	return (Board[x + y*MAPW0] >> SAVE_SHIFT) & SAVE_MASK;
}

// set save cell state
void SetSave(int x, int y, int save)
{
	u8* d = &Board[x + y*MAPW0];
	*d = (*d & ~(SAVE_MASK << SAVE_SHIFT)) | (save << SAVE_SHIFT);
}

// get number of neighbors
int GetNeigh(int x, int y)
{
	return (Board[x + y*MAPW0] >> NEIGH_SHIFT) & NEIGH_MASK;
}

// set number of neighbors
void SetNeigh(int x, int y, int neigh)
{
	u8* d = &Board[x + y*MAPW0];
	*d = (*d & ~(NEIGH_MASK << NEIGH_SHIFT)) | (neigh << NEIGH_SHIFT);
}

// cursor
int CurX, CurY;

// samples (first 2 bytes = width, height)
const u8 Samples[] = {

	// 0: Life
	5,5,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
/*
	// 1: penta-decathlon
	3,12,
	1,1,1,
	0,1,0,
	0,1,0,
	1,1,1,
	0,0,0,
	1,1,1,
	1,1,1,
	0,0,0,
	1,1,1,
	0,1,0,
	0,1,0,
	1,1,1,

	// 2: R-pentomino
	3,3,
	0,1,1,
	1,1,0,
	0,1,0,

	// 3: Diehard
	8,3,
	0,0,0,0,0,0,1,0,
	1,1,0,0,0,0,0,0,
	0,1,0,0,0,1,1,1,

	// 4. Acorn
	7,3,
	0,1,0,0,0,0,0,
	0,0,0,1,0,0,0,
	1,1,0,0,1,1,1,

	// 5: Glider
	3,3,
	0,0,1,
	1,0,1,
	0,1,1,

	// 6: spaceship
	5,4,
	1,0,0,1,0,
	0,0,0,0,1,
	1,0,0,0,1,
	0,1,1,1,1,

	// 7: pulsar
	15,15,
	0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,0,0,1,1,0,1,1,0,0,1,1,1,
	0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,
	1,1,1,0,0,1,1,0,1,1,0,0,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,

	// 8: Gosper glider gun
	38, 9,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,1,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,1,1,0,0,0,0,0, 0,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,1,0,0,0,1,0,0,0, 0,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,1,1,0,
	0,1,1,0,0,0,0,0,0,0, 0,1,0,0,0,0,0,1,0,0, 0,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,1,1,0,
	0,1,1,0,0,0,0,0,0,0, 0,1,0,0,0,1,0,1,1,0, 0,0,0,1,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,1,0,0,0,0,0,1,0,0, 0,0,0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,1,0,0,0,1,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	// 9: Simkin glider gun
	33,21,
	1,1,0,0,0,0,0,1,1,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	1,1,0,0,0,0,0,1,1,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,1,1,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,1,1,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,1,1,0,1,1,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,1,0,0,0,0,0,1,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,1,0,0,0,0,0,0,1,0, 0,1,1,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,1,1,1,0,0,0,1,0,0, 0,1,1,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 1,1,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,1,1,1,0,0,0,0,0,0, 0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,1,0,0,0,0,0,0, 0,0,0,
*/
};

// draw cell
void DrawCell(int x, int y)
{
	int b = GetCell(x+MAPX, y+MAPY);
	x = x*TILESIZE + BOARDX;
	y = y*TILESIZE + BOARDY;
	switch (b)
	{
	case TILE_EMPTY:	// empty tile
		DrawImgBg(ImgTileEmpty, x, y, TILESIZE, TILESIZE, TILE_WB);
		break;

	case TILE_FULL:		// full tile
		DrawImgBg(ImgTileCell, x, y, TILESIZE, TILESIZE, TILE_WB);
		break;

	case TILE_SELEMPTY:	// selected empty tile
		DrawImgBg(ImgTileEmptySel, x, y, TILESIZE, TILESIZE, TILE_WB);
		break;

	case TILE_SELFULL:	// selected full tile
		DrawImgBg(ImgTileCellSel, x, y, TILESIZE, TILESIZE, TILE_WB);
		break;
	}
}

// draw cell with cursor
void DrawCur()
{
	DrawCell(CurX-MAPX, CurY-MAPY);
}

// draw board
void DrawBoard()
{
	int i, j, x, y, b;
	for (i = 0; i < MAPH; i++)
	{
		for (j = 0; j < MAPW; j++)
		{
			DrawCell(j, i);
		}
	}
	DispUpdate();
}

// set cursor on
void CurOn()
{
	u8 b = GetCell(CurX, CurY);
	if (b == TILE_FULL)
		b = TILE_SELFULL;
	else if (b == TILE_EMPTY)
		b = TILE_SELEMPTY;
	SetCell(CurX, CurY, b);
	DrawCur();
	DispUpdate();
}

// set cursor off
void CurOff()
{
	u8 b = GetCell(CurX, CurY);
	if (b == TILE_SELFULL)
		b = TILE_FULL;
	else if (b == TILE_SELEMPTY)
		b = TILE_EMPTY;
	SetCell(CurX, CurY, b);
	DrawCur();
	DispUpdate();
}

// flip cursor
void CurFlip()
{
	u8 b = GetCell(CurX, CurY);
	if (b == TILE_SELFULL)
		b = TILE_SELEMPTY;
	else if (b == TILE_SELEMPTY)
		b = TILE_SELFULL;
	SetCell(CurX, CurY, b);
	DrawCur();
	DispUpdate();
}

// get cell on coordinates (0 or 1)
int Cell(int x, int y)
{
	while (x < 0) x += MAPW0;
	while (x >= MAPW0) x -= MAPW0;
	while (y < 0) y += MAPH0;
	while (y >= MAPH0) y -= MAPH0;
	u8 b = GetCell(x, y);
	return (b == TILE_FULL) ? 1 : 0;
}

// save current slot
void SaveSlot()
{
	int x, y;
	for (y = 0; y < MAPH0; y++)
	{
		for (x = 0; x < MAPW0; x++)
		{
			SetSave(x, y, GetCell(x, y));
		}
	}
}

// load current slot
void LoadSlot()
{
	int x, y;
	for (y = 0; y < MAPH0; y++)
	{
		for (x = 0; x < MAPW0; x++)
		{
			SetCell(x, y, GetSave(x, y));
		}
	}
}

// run life
void Run()
{
	int x, y;
	u8 b;
	char ch;

	KeyFlush();

	// break with a key
	while (True)
	{
		ch = KeyGet();
		if (ch != NOKEY) break;

		// calculate neighbors
		for (y = 0; y < MAPH0; y++)
		{
			for (x = 0; x < MAPW0; x++)
			{
				SetNeigh(x, y,
					Cell(x-1, y-1) +
					Cell(x  , y-1) +
					Cell(x+1, y-1) +

					Cell(x-1, y  ) +
					Cell(x+1, y  ) +

					Cell(x-1, y+1) +
					Cell(x  , y+1) +
					Cell(x+1, y+1));
			}
		}

		// update cells
		for (y = 0; y < MAPH0; y++)
		{
			for (x = 0; x < MAPW0; x++)
			{
				b = GetNeigh(x, y);

				// 3 -> new cell
				if (b == 3) 
					SetCell(x, y, TILE_FULL);

				// 2 -> unchanged
				else if (b == 2)
					;
				// else -> dead
				else
					SetCell(x, y, TILE_EMPTY);
			}
		}

		DrawBoard();

		// delay
		WaitMs(SPEED);
	}
}

// initialize slots by samples
void InitSlot()
{
	u8 b;
	const u8* s = Samples;
	int i, w, w2, h, x, y, x0;

	// sample dimension
	w = *s++;
	h = *s++;

	// center image
	x0 = (MAPW0-w)/2;
	y = (MAPH0-h)/2;

	// copy sample
	for (; h > 0; h--)
	{
		x = x0;
		for (w2 = w; w2 > 0; w2--)
		{
			SetCell(x, y, *s);
			s++;
			x++;
		}
		y++;
	}
}

int main(void)
{
	int i;
	char ch;
	int oldbat;
	int bat;

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
				DrawTextCond6Bg(DecNumBuf, 0, 0);
				DispUpdate();
			}
		}
	}
	DrawClear();

	// randomize
	RandSeed += Time();

	// clear buffer
	for (i = 0; i < MAPSIZE; i++) Board[i] = TILE_EMPTY;
	CurX = MAPW0/2;
	CurY = MAPH0/2;

	// fill slots with samples
	InitSlot();

	// draw board
	DrawBoard();
	DrawHLine(BOARDX, BOARDY+BOARDH-1, BOARDW, COL_WHITE);
	DrawVLine(BOARDX+BOARDW-1, BOARDY, BOARDH-1, COL_WHITE);

	// set cursor on
	CurOn();

	// loop with demo scene
	while (True)
	{
		// keyboard
		ch = KeyGet();
		if (ch != NOKEY)
		{
			switch (ch)
			{
			// right
			case KEY_RIGHT:
				CurOff(); // set cursor off
				CurX++;
				if (CurX >= MAPX+MAPW) CurX = MAPX;
				CurOn(); // set cursor on
				break;

			// left
			case KEY_LEFT:
				CurOff(); // set cursor off
				CurX--;
				if (CurX < MAPX) CurX = MAPX+MAPW-1;
				CurOn(); // set cursor on
				break;

			// down
			case KEY_DOWN:
				CurOff(); // set cursor off
				CurY++;
				if (CurY >= MAPY+MAPH) CurY = MAPY;
				CurOn(); // set cursor on
				break;

			// up
			case KEY_UP:
				CurOff(); // set cursor off
				CurY--;
				if (CurY < MAPY) CurY = MAPY+MAPH-1;
				CurOn(); // set cursor on
				break;
		
			// toggle
			case KEY_A:
				CurFlip(); // flip cursor
				break;

			// run
			case KEY_B:
				CurOff(); // set cursor off
				SaveSlot(); // save state
				Run(); // run life
				LoadSlot(); // restore state
				CurOn(); // set cursor on
				DrawBoard();
				break;
			}
		}
	}
}
