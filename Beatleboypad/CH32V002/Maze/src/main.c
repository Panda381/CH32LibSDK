
// ****************************************************************************
//
//                                  Eggs game
//
// ****************************************************************************
// "wave" maze generator: https://www.itnetwork.cz/navrh/algoritmy/algoritmy-bludiste/algoritmus-tvorba-nahodneho-bludiste
// - MAZEW and MAZEH must be odd numbers!

#include "../include.h"

// tile characters and colors
u8 TileCharCol[TILE_NUM] = {
	' ',		// S_BLACK = 0,		// 0: black tile
	' ',		// S_EMPTY_HIDE,	// 1: hidden empty field (grass)
	' ',		// S_WALL_HIDE,		// 2: hidden wall
	' ',		// S_DOOR_HIDE,		// 3: hidden door
	1,		// S_EMPTY,		// 4: empty field (grass)
	' '+128,	// S_WALL,		// 5: wall
	5,		// S_DOOR,		// 6: door
	9,		// S_FACE,		// 7: face on empty field
};


// game board
u8 Board[MAPSIZE];

// board address
#define BoardAddr(x, y) (&Board[(x) + (y)*MAPW])

u8 StopX, StopY; // stop position
u8 PosX, PosY;	// current position

// direction
#define	L 0	// left
#define	U 1	// up
#define R 2	// right
#define D 3	// down

INLINE int abs(int n) { return (n >= 0) ? n : -n; }

// draw board
void DrawBoard()
{
	int i, j, x, y, b;
	for (i = 0; i < MAPH; i++)
	{
		for (j = 0; j < MAPW; j++)
		{
			b = Board[i*MAPW + j];
			DrawCharCond6Bg(TileCharCol[b], j*TILESIZE+BOARDX, i*TILESIZE+BOARDY);
		}
	}
	DispUpdate();
}

// maze generator
void Gener()
{
	s16 i, s, x, y;

	// clear board with black tile (on right and on down will leave black tiles)
	memset(Board, S_BLACK, MAPSIZE);

	// clear maze - set empty tiles
	for (y = 0; y < MAZEH; y++)
		for (x = 0; x < MAZEW; x++)
			*BoardAddr(x, y) = S_EMPTY_HIDE;

	// add stones - only to odd coordinates (MAZEW and MAZEH must be odd numbers!)
	for (y = 1; y < MAZEH; y += 2)
		for (x = 1; x < MAZEW; x += 2)
			*BoardAddr(x, y) = S_DOOR_HIDE;

	// generator loop
	for (;;)
	{
		// calculate remaining stones
		s = 0;
		for (i = 0; i < MAPSIZE; i++) if (Board[i] == S_DOOR_HIDE) s++;
		if (s == 0) break; // no stones left, end of generation

		// select random stone
		s = RandS16Max(s-1);

		// find stone (only odd coordinates)
		for (y = 1; y < MAZEH; y += 2)
		{
			for (x = 1; x < MAZEW; x += 2)
			{
				if (*BoardAddr(x, y) == S_DOOR_HIDE)
				{
					s--;
					if (s < 0) break;
				}
			}
			if (s < 0) break;
		}

		// select random direction (L=0, U=1, R=2, D=3)
		i = RandU8Max(3);

		// build wall, until we meet another wall
		for (;;)
		{
			// put one wall
			*BoardAddr(x, y) = S_WALL_HIDE;

			// shift coordinates
			switch (i)
			{
			case L: x--; break;
			case U: y--; break;
			case R: x++; break;
			default: y++; break; // D
			}

			// coordinates are out of range
			if ((x < 0) || (x >= MAZEW) || (y < 0) || (y >= MAZEH)) break;

			// check wall on new position
			if (*BoardAddr(x, y) == S_WALL_HIDE) break;
		}
	}
}

// get one tile (returns S_WALL if out of range)
u8 GetTile(s8 x, s8 y)
{
	if ((x < 0) || (x >= MAZEW) || (y < 0) || (y >= MAZEH)) return S_WALL;
	if ((x == PosX) && (y == PosY)) return S_FACE;
	if ((x == StopX) && (y == StopY)) return S_DOOR;
	u8 tile = *BoardAddr(x, y);
	if (tile == S_WALL_HIDE) tile = S_WALL;
	if (tile == S_EMPTY_HIDE) tile = S_EMPTY;
	if (tile == S_DOOR_HIDE) tile = S_DOOR;
	return tile;
}

// hide face
void Hide()
{
	*BoardAddr(PosX, PosY) = S_EMPTY;
}

// show face
void Show()
{
	*BoardAddr(PosX, PosY) = S_FACE;
}

// check if position is free
Bool IsEmpty(s8 x, s8 y)
{
	u8 t = GetTile(x, y);
	return (t == S_EMPTY) || (t == S_DOOR);
}

// show all maze
void ShowAll()
{
	int x, y;
	for (x = 0; x < MAZEW; x++)
	{
		for (y = 0; y < MAZEH; y++)
			*BoardAddr(x, y) = GetTile(x, y);

		DrawBoard();
		WaitMs(40);
	}
}

// look around
void Look()
{
	if (PosX > 0) *BoardAddr(PosX-1, PosY) = GetTile(PosX-1, PosY);
	if (PosX < MAZEW-1) *BoardAddr(PosX+1, PosY) = GetTile(PosX+1, PosY);
	if (PosY > 0) *BoardAddr(PosX, PosY-1) = GetTile(PosX, PosY-1);
	if (PosY < MAZEH-1) *BoardAddr(PosX, PosY+1) = GetTile(PosX, PosY+1);
}

// clear display and start new scene
void Clear()
{
	// generate new maze
	Gener();

	// generate stop position
	for (;;)
	{
		StopX = RandU8Max(MAZEW-1);
		StopY = RandU8Max(MAZEH-1);
		if (*BoardAddr(StopX, StopY) == S_EMPTY_HIDE) break;
	}
	*BoardAddr(StopX, StopY) = S_DOOR_HIDE;

	// generate start position
	for (;;)
	{
		PosX = RandU8Max(MAZEW-1);
		PosY = RandU8Max(MAZEH-1);
		if ((*BoardAddr(PosX, PosY) == S_EMPTY_HIDE) &&
			(abs(PosX - StopX) > 4) && (abs(PosY - StopY) > 4)) break;
	}
	Show();

	// look around
	Look();

	DrawBoard();
}

int main(void)
{
	int i;
	char ch;
	int oldbat;
	int bat;

	while (True)
	{
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
					DrawTextCond6Bg(DecNumBuf, 0, HEIGHT-6);
					DispUpdate();
				}
			}
		}

		// randomize
		RandSeed += Time();

		// clear display and start new scene
		DrawClear();
		Clear();

		// main loop
		while (True)
		{
			// key service
			ch = KeyGet();
			if (ch == KEY_B) break;

			switch (ch)
			{
			// key "A" = show door
			case KEY_A:
				{
					u8 t = *BoardAddr(StopX, StopY);
					int k;
					for (k = 3; k > 0; k--)
					{
						*BoardAddr(StopX, StopY) = S_DOOR;
						DrawBoard();
						WaitMs(100);
						*BoardAddr(StopX, StopY) = S_DOOR_HIDE;
						DrawBoard();
						WaitMs(50);
					}
					*BoardAddr(StopX, StopY) = t;
					DrawBoard();
				}
				KeyFlush();
				break;

			// left
			case KEY_LEFT:
				if ((PosX > 0) && IsEmpty(PosX-1, PosY))
				{
					Hide();
					PosX--;
					Show();
					Look();
					DrawBoard();
				}
				KeyFlush();
				break;

			// right
			case KEY_RIGHT:
				if ((PosX < MAZEW-1) && IsEmpty(PosX+1, PosY))
				{
					Hide();
					PosX++;
					Show();
					Look();
					DrawBoard();
				}
				KeyFlush();
				break;

			// up
			case KEY_UP:
				if ((PosY > 0) && IsEmpty(PosX, PosY-1))
				{
					Hide();
					PosY--;
					Show();
					Look();
					DrawBoard();
				}
				KeyFlush();
				break;

			// down
			case KEY_DOWN:
				if ((PosY < MAZEH-1) && IsEmpty(PosX, PosY+1))
				{
					Hide();
					PosY++;
					Show();
					Look();
					DrawBoard();
				}
				KeyFlush();
				break;

			// no key
			case NOKEY:
				break;

			// invalid key
			default:
				KeyFlush();
				break;
			}

			// SOLVED
			if ((PosX == StopX) && (PosY == StopY))
			{
				// show all maze
				ShowAll();

				// winking
				for (i = 0; i < 5; i++)
				{
					*BoardAddr(PosX, PosY) = S_EMPTY;
					DrawBoard();
					WaitMs(100);
					*BoardAddr(PosX, PosY) = S_FACE;
					DrawBoard();
					WaitMs(100);
				}
				*BoardAddr(StopX, StopY) = S_DOOR;
				DrawBoard();

				// wait for a key press
				KeyFlush();
				while ((ch = KeyGet()) == NOKEY) {}

				// new scene
				break;
			}
		}
	}
}
