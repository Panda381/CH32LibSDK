
// ****************************************************************************
//
//                                  Eggs game
//
// ****************************************************************************

#include "../include.h"

// tiles
#define TILEW	14	// tile width
#define TILEH	14	// tile height

// game board (size 240x240 pixels)
//#define BOARDW0	12	// board width with fence
//#define BOARDH0	12	// board height width fence
//#define BOARDSIZE0 (BOARDW0*BOARDH0) // board size with fence
#define BOARDW	8	// game board width
#define BOARDH	8	// game board height
#define BOARDSIZE (BOARDW*BOARDH) // board size with fence
#define BOARDX	0
#define BOARDY	4

// frame
#define FRAMEW	48	// frame width
#define FRAMEH	120	// frame height
#define FRAMEX	112	// frame X coordinate
#define FRAMEY	0	// player 2 offset

// tiles
#define TILE_BLACK	0	// black

#define TILE_EMPTY	1	// empty
#define TILE_DOT	2	// dot
#define TILE_EGG	3	// egg
#define TILE_CHICKEN	4	// chicken
#define TILE_HEN	5	// hen
#define TILE_EGGWIN	6	// egg win
#define TILE_HENWIN	7	// hen win

#define TILE_EMPTY2	8	// empty with frame
#define TILE_DOT2	9	// dot with frame
#define TILE_EGG2	10	// egg with frame
#define TILE_CHICKEN2	11	// chicken with frame
#define TILE_HEN2	12	// hen with frame
#define TILE_EGGWIN2	13	// egg win with frame
#define TILE_HENWIN2	14	// hen win with frame

#define TILE_NUM	15	// number of tiles

#define TILE_OFFMIN	TILE_EMPTY // first tile without cursor
#define TILE_OFFMAX	TILE_HENWIN // last tile without cursor
#define TILE_ONMIN	TILE_EMPTY2 // first tile without cursor
#define TILE_ONMAX	TILE_HENWIN2 // last tile without cursor

// beep sound
const sMelodyNote BeepSound[] = {
	{ 1, NOTE_C7 },
	{ 0, 0 },
};

// beep sound 2
const sMelodyNote BeepSound2[] = {
	{ 1, NOTE_G6 },
	{ 0, 0 },
};

// fanfare sound
const sMelodyNote FanfareSound[] = {
	{ NOTE_LEN8, NOTE_C4 },
	{ NOTE_LEN8, NOTE_E4 },
	{ NOTE_LEN8, NOTE_G4 },
	{ NOTE_LEN8, NOTE_C5 },
	{ NOTE_LEN8, NOTE_R },
	{ NOTE_LEN8, NOTE_G4 },
	{ NOTE_LEN4, NOTE_C5 },
	{ 0, 0 },
};

// game board
u8 Board[BOARDSIZE]; // playing board
u8 DispBoard[BOARDSIZE]; // displayed board

// directions
const s8 DirX[8] = {  1,  1,  0, -1, -1, -1,  0,  1 };
const s8 DirY[8] = {  0,  1,  1,  1,  0, -1, -1, -1 };

// players
int Stones[2];	// number of stones (player 1: number of eggs, player 2: number of hens)
int Wins[2];	// number of wins
Bool Comp[2];	// player is computer
u8 Player;	// active player (0 or 1, 2=no player)
u8 CurX, CurY;	// cursor position
u8 CurBlink;	// blinking cursor
u8 Pos;		// number of possible positions
u8 Free;	// number of free positions

// draw tile
void DrawTile(s8 x, s8 y)
{
	if ((x < 0) || (y < 0) || (x >= BOARDW) || (y >= BOARDH)) return;
	u8 b = Board[y*BOARDW + x];
	if (b != DispBoard[y*BOARDW + x])
	{
		DispBoard[y*BOARDW + x] = b;
		int xx = x*TILEW+BOARDX;
		int yy = y*TILEH+BOARDY;
		DrawImgBg(ImgTilesGreen + b*TILEH*2, xx, yy, TILEW, TILEH, 2, COL_GREEN);
		DrawImg(ImgTilesRed + b*TILEH*2, xx, yy, TILEW, TILEH, 2, COL_RED);
		DrawImg(ImgTilesWhite + b*TILEH*2, xx, yy, TILEW, TILEH, 2, COL_WHITE);
		DrawImg(ImgTilesYellow + b*TILEH*2, xx, yy, TILEW, TILEH, 2, COL_YELLOW);
	}
}

// draw board
void DrawBoard()
{
	int i, j;
	for (i = 0; i < BOARDH; i++)
	{
		for (j = 0; j < BOARDW; j++)
		{
			DrawTile(j, i);
		}
	}
}

// get board on coordinates
u8 GetBoard(s8 x, s8 y)
{
	if ((x < 0) || (y < 0) || (x >= BOARDW) || (y >= BOARDH)) return TILE_BLACK;
	return Board[x + y*BOARDW];
}

// set board on coordinates (adds game start coordinates)
void SetBoard(s8 x, s8 y, u8 tile)
{
	Board[x + y*BOARDW] = tile;
}

// set cursor on
void CurOn()
{
	u8 c = GetBoard(CurX, CurY);
	if ((c >= TILE_OFFMIN) && (c <= TILE_OFFMAX))
	{
		SetBoard(CurX, CurY, c - TILE_OFFMIN + TILE_ONMIN);
	}
	CurBlink = 0;
}

// set cursor off
void CurOff()
{
	u8 c = GetBoard(CurX, CurY);
	if ((c >= TILE_ONMIN) && (c <= TILE_ONMAX))
	{
		SetBoard(CurX, CurY, c - TILE_ONMIN + TILE_OFFMIN);
	}
}

// discovery stones in one direction (returns number of stones; cursor must be off)
u8 GetStones1(s8 x, s8 y, s8 dx, s8 dy)
{
	u8 c;
	u8 steps = 0;
	u8 stones = 0;
	do {
		// do step
		x += dx;
		y += dy;

		// if chicken, number of steps is valid
		c = GetBoard(x, y);
		if (c == TILE_CHICKEN) stones = steps;

		// increase number of steps
		steps++;

	// while tile is valid
	} while ((c == TILE_EGG) || (c == TILE_CHICKEN) || (c == TILE_HEN));

	return stones;
}

// discovery stones in all directions (returns number of stones; cursor must be off)
u8 GetStones(s8 x, s8 y)
{
	u8 stones = 0;
	int i;
	for (i = 0; i < 8; i++) stones += GetStones1(x, y, DirX[i], DirY[i]);
	return stones;
}

// display possible positions (cursor must be off)
void DispPos()
{
	s8 x, y;
	u8 stones;
	u8 c;

	// clear number of possible positions
	Pos = 0;

	// loop through all game tiles
	for (y = 0; y < BOARDH; y++)
	{
		for (x = 0; x < BOARDW; x++)
		{
			// check if this tile is empty
			c = GetBoard(x, y);
			if ((c == TILE_EMPTY) || (c == TILE_DOT))
			{
				// count number of stones
				if (GetStones(x, y) > 0)
				{
					// increase number of possible positions
					Pos++;
					SetBoard(x, y, TILE_DOT);
				}
				else
					SetBoard(x, y, TILE_EMPTY);
			}
		}
	}
}

// display selected player
void DispSel()
{
	int play;
	int y = 0;
	for (play = 0; play < 2; play++)
	{
		if (play == Player)
			DrawFrame(FRAMEX+3, y+4, FRAMEW-6, 20, COL_MAGENTA);
		else
			DrawFrameClr(FRAMEX+3, y+4, FRAMEW-6, 20);
		y += FRAMEH/2;
	}
}

char NumBuf[20];

// display score
void DispScore()
{
	int play;
	int n;
	for (play = 0; play < 2; play++)
	{
		n = DecNum(NumBuf, Stones[play], 0);
		NumBuf[n++] = ' ';
		NumBuf[n++] = 0;
		DrawText(NumBuf, FRAMEX+16, FRAMEY+30+play*(FRAMEH/2), COL_WHITE);
	}
}

// display wins
void DispWin()
{
	int play;
	int n;
	for (play = 0; play < 2; play++)
	{
		n = DecNum(NumBuf, Wins[play], 0);
		NumBuf[n++] = ' ';
		NumBuf[n++] = ' ';
		NumBuf[n++] = 0;
		DrawText(NumBuf, FRAMEX+16, FRAMEY+45+play*(FRAMEH/2), COL_WHITE);
	}
}

// open game
void OpenGame(Bool comp1, Bool comp2)
{
	int i;

	// copy board template
	for (i = 0; i < BOARDSIZE; i++) Board[i] = TILE_EMPTY;
	for (i = 0; i < BOARDSIZE; i++) DispBoard[i] = TILE_BLACK;
	Board[3*8+3] = TILE_CHICKEN;
	Board[3*8+4] = TILE_CHICKEN;
	Board[4*8+3] = TILE_CHICKEN;
	Board[4*8+4] = TILE_CHICKEN;
	DrawBoard();

	// display bottom border
	for (i = BOARDX; i < BOARDW*TILEW+BOARDX; i += TILEW)
		DrawImgBg(ImgTilesGreen + TILE_EMPTY*TILEH*2, i, BOARDH*TILEH+BOARDY, TILEW, 1, 2, COL_GREEN);

	// draw frame image
	DrawImgBg(ImgFrameRed, FRAMEX, FRAMEY, FRAMEW, FRAMEH, 6, COL_RED);
	DrawImg(ImgFrameCyan, FRAMEX, FRAMEY, FRAMEW, FRAMEH, 6, COL_CYAN);
	DrawImg(ImgFrameWhite, FRAMEX, FRAMEY, FRAMEW, FRAMEH, 6, COL_WHITE);
	DrawImg(ImgFrameYellow, FRAMEX, FRAMEY, FRAMEW, FRAMEH, 6, COL_YELLOW);

	// draw computers
	if (comp1) DrawImg(ImgComputer, FRAMEX+6, FRAMEY+6, 4, 5, 1, COL_CYAN);
	if (comp2) DrawImg(ImgComputer, FRAMEX+6, FRAMEY+6+FRAMEH/2, 4, 5, 1, COL_CYAN);

	// initialize players
	Stones[0] = 0;
	Stones[1] = 0;
	Comp[0] = comp1;
	Comp[1] = comp2;

	// start random player
	Player = RandU8() & 1;

	// cursor position
	CurX = 3;
	CurY = 3;

	// initialize number of free positions
	Free = BOARDW*BOARDH-4;
	Pos = 12;

	// display selected player
	DispSel();

	// display score
	DispScore();

	// display wins
	DispWin();
}

// update stones in one direction
void PutStone1(s8 x, s8 y, s8 dx, s8 dy)
{
	u8 c;

	// check number of stones in this direction
	u8 stones = GetStones1(x, y, dx, dy);
	for (; stones > 0; stones--)
	{
		DrawBoard();

		// play sound and short delay
		PlayMelody(BeepSound);
		WaitMs(100);

		// step
		x += dx;
		y += dy;

		// get tile
		c = GetBoard(x, y);

		// player 2 is active, direction egg -> chicken -> hen
		if (Player == 1)
		{
			// egg -> chicken
			if (c == TILE_EGG)
			{
				Stones[0]--; // decrease number of eggs of player 1
				c = TILE_CHICKEN; // change to chicken
			}

			// hen -> egg
			else if (c == TILE_HEN)
			{
				Stones[1]--; // decrease number of hens of player 2
				Stones[0]++; // increase number of eggs of player 1
				c = TILE_EGG;
			}

			// chicken -> hen
			else
			{
				Stones[1]++; // increase number of hens of player 2
				c = TILE_HEN;
			}
		}

		// player 1 is active, direction hen -> chicken -> egg
		else
		{
			// egg -> hen
			if (c == TILE_EGG)
			{
				Stones[0]--; // decrease number of effs of player 1
				Stones[1]++; // increase number of hens of player 2
				c = TILE_HEN;
			}

			// hen -> chicken
			else if (c == TILE_HEN)
			{
				Stones[1]--; // decrease number of hens of player 2
				c = TILE_CHICKEN;
			}

			// chicken -> egg
			else
			{
				Stones[0]++; // increase number of effs of player 1
				c = TILE_EGG;
			}
		}

		// set tile
		SetBoard(x, y, c);
		DrawBoard();

		// display score
		DispScore();
	}
}

// put stone (cursor must be off and current tile must be 'dot')
void PutStone()
{
	int i;

	// short blink cursor (must leave cursor off)
	for (i = 5; i > 0; i--)
	{
		DrawBoard();
		WaitMs(50);
		CurOn();
		DrawBoard();
		WaitMs(50);
		CurOff();
	}
	DrawBoard();

	// put chicken into current position
	SetBoard(CurX, CurY, TILE_CHICKEN);

	// decrease free positions
	Free--;

	// update stones in all directions
	for (i = 0; i < 8; i++) PutStone1(CurX, CurY, DirX[i], DirY[i]);
}

// get profit in one direction
s8 Profit1(s8 x, s8 y, s8 dx, s8 dy)
{
	u8 c;
	s8 profit = 0;

	// check number of stones in this direction
	u8 stones = GetStones1(x, y, dx, dy);
	for (; stones > 0; stones--)
	{
		// step
		x += dx;
		y += dy;

		// get tile
		c = GetBoard(x, y);

		// player 2 is active (egg -> chicken -> hen)
		if (Player == 1)
		{
			// this player loses hen, opposite gains egg
			if (c == TILE_HEN)
				profit -= 2;

			// this player gains hen or opposite loses egg
			else
				profit++;
		}

		// player 1 is active (hen -> chicken -> egg)
		else
		{
			// this player loses egg, opposite gains hen
			if (c == TILE_EGG)
				profit -= 2;

			// this player gains egg or opposite loses hen
			else
				profit++;
		}
	}
	return profit;
}

// get tile profit
s8 Profit(s8 x, s8 y)
{
	s8 profit = 0;
	int i;
	for (i = 0; i < 8; i++) profit += Profit1(x, y, DirX[i], DirY[i]);
	return profit;
}

// find best position (cursor must be off)
void FindPos()
{
	s8 x, y;
	u8 c;
	s8 bestprofit = -125; // profit of founded tiles
	s8 profit;

	// loop through all game tiles
	for (y = 0; y < BOARDH; y++)
	{
		for (x = 0; x < BOARDW; x++)
		{
			// check if this tile is valid
			c = GetBoard(x, y);
			if (c == TILE_DOT)
			{
				// get profit of this field
				profit = Profit(x, y);

				// check better profit
				if ((profit > bestprofit) ||
					((profit == bestprofit) && (RandU8() < 80)))
				{
					// save new best state
					bestprofit = profit;
					CurX = x;
					CurY = y;
				}
			}
		}
	}
}

// play game
void PlayGame(Bool comp1, Bool comp2)
{
	char ch;
	s8 x, y;

	// randomize
	RandSeed += Time() + DispFrame + DispLine;

	// demo mode
	Bool demo = comp1 && comp2;

	// open game
	OpenGame(comp1, comp2);

	// display possible positions
	DispPos();

	// display cursor on
	CurOn();
	DrawBoard();

	// while there is some possible position
	while ((Pos > 0) && (Free > 0))
	{
		// wait for a key
		ch = KeyGet();

		// break demo
		if (demo && (ch != NOKEY)) return;

		// player is computer
		if (Comp[Player])
		{
			// find position
			CurOff();
			FindPos();
			CurOn();
			DrawBoard();

			// put stone
			if (!demo) KeyFlush();
			ch = KEY_A;
		}

		switch (ch)
		{
		// break game
		case KEY_Y:
			return;

		// right
		case KEY_RIGHT:
			if (CurX < BOARDW-1)
			{
				CurOff();
				CurX++;
				CurOn();
				DrawBoard();
			}
			break;

		// up
		case KEY_UP:
			if (CurY > 0)
			{
				CurOff();
				CurY--;
				CurOn();
				DrawBoard();
			}
			break;

		// left
		case KEY_LEFT:
			if (CurX > 0)
			{
				CurOff();
				CurX--;
				CurOn();
				DrawBoard();
			}
			break;

		// down
		case KEY_DOWN:
			if (CurY < BOARDH-1)
			{
				CurOff();
				CurY++;
				CurOn();
				DrawBoard();
			}
			break;

		// help
		case KEY_X:
//#if USE_SCREENSHOT		// use screen shots
//			ScreenShot();
//#endif
			CurOff();
			FindPos();
			CurOn();
			DrawBoard();
			break;

		// put stone
		case KEY_A:
			CurOff();
			if (GetBoard(CurX, CurY) == TILE_DOT)
			{
				// put stone
				PutStone();

				// update possible positions
				DispPos();

				// change player
				Player ^= 1;

				// display selected player
				DispSel();

				// display score
				DispScore();
			}
			CurOn();
			DrawBoard();
			break;

		// no key, short delay
		case NOKEY:
			WaitMs(50);
			break;

		// invalid key
		default:
			break;
		}

		// blinking cursor
		CurBlink++;
		if (CurBlink == 5)
		{
			CurOff();
			DrawBoard();
		}

		if (CurBlink == 8)
		{
			CurOn();
			DrawBoard();
		}
	}

	// cursor off
	CurOff();

	// select no player
	Player = 2;
	DispSel();

	// player 1 (eggs) wins
	if (Stones[0] > Stones[1])
	{
		// animate
		for (y = 0; y < 8; y++)
		{
			for (x = 0; x < 8; x++)
			{
				if (GetBoard(x, y) == TILE_EGG)
				{
					SetBoard(x, y, TILE_EGGWIN);
					PlayMelody(BeepSound2);
					DrawBoard();
					WaitMs(200);
				}
			}
		}

		// display wins
		Wins[0]++;
		DispWin();

		// fanfare sound
		PlayMelody(FanfareSound);

		// blink winner
		while (True)
		{
			Player = 0;
			DispSel();
			DrawBoard();
			WaitMs(150);
			if (KeyGet() != NOKEY) return;
			Player = 2;
			DispSel();
			DrawBoard();
			WaitMs(150);
			if (KeyGet() != NOKEY) return;
		}
	}

	// player 2 (hens) wins
	else if (Stones[1] > Stones[0])
	{
		// animate
		for (y = 0; y < 8; y++)
		{
			for (x = 0; x < 8; x++)
			{
				if (GetBoard(x, y) == TILE_HEN)
				{
					SetBoard(x, y, TILE_HENWIN);
					PlayMelody(BeepSound2);
					DrawBoard();
					WaitMs(200);
				}
			}
		}

		// display wins
		Wins[1]++;
		DispWin();

		// fanfare sound
		PlayMelody(FanfareSound);

		// blink winner
		while (True)
		{
			Player = 1;
			DispSel();
			DrawBoard();
			WaitMs(150);
			if (KeyGet() != NOKEY) return;
			Player = 2;
			DispSel();
			DrawBoard();
			WaitMs(150);
			if (KeyGet() != NOKEY) return;
		}
	}

	// no winner
	else
	{
		// blink winner
		while (True)
		{
			Player = 0;
			DispSel();
			DrawBoard();
			WaitMs(150);
			if (KeyGet() != NOKEY) return;
			Player = 1;
			DispSel();
			DrawBoard();
			WaitMs(150);
			if (KeyGet() != NOKEY) return;
		}
	}
}

// draw open screen
void OpenDraw()
{
	// clear screen
	DrawClear();

	// title
	PrintTextAt("EGGS", (TEXTWIDTH-4)/2, 2, COL_YELLOW);

	// draw menu
	PrintTextAt("Press key to start:", 0, 5, COL_GREEN);

	PrintTextAt("LEFT", 0, 7, COL_CYAN);
	PrintTextAt("Play for eggs", 6, 7, COL_WHITE);

	PrintTextAt("RIGHT", 0, 8, COL_CYAN);
	PrintTextAt("Play for hens", 6, 8, COL_WHITE);

	PrintTextAt("DOWN", 0, 9, COL_CYAN);
	PrintTextAt("2 players", 6, 9, COL_WHITE);

	PrintTextAt("UP", 0, 10, COL_CYAN);
	PrintTextAt("Demo", 6, 10, COL_WHITE);

	PrintTextAt("Y", 0, 11, COL_CYAN);
	PrintTextAt("Quit", 6, 11, COL_WHITE);
}

int main(void)
{
	int i;

	// display splash screen
	u8 key;
	KeyWaitNoPressed();
	memcpy(FrameBuf, ImgIntro, sizeof(ImgIntro));
	memcpy(AttrBuf, ImgIntro_Attr, sizeof(ImgIntro_Attr));
	while ((key = KeyGet()) == NOKEY) {}
	if (key == KEY_Y) ResetToBootLoader();
	DrawClear();

	// clear players
	Wins[0] = 0;
	Wins[1] = 0;

	// draw open screen
	OpenDraw();

	// select game
	while (True)
	{
		// get key
		switch (KeyGet())
		{
		// player is EGG
		case KEY_LEFT:
			PlayGame(False, True);
			OpenDraw();
			break;

		// player is HEN
		case KEY_RIGHT:
			PlayGame(True, False);
			OpenDraw();
			break;

		// demo
		case KEY_UP:
			PlayGame(True, True);
			OpenDraw();
			break;

		// 2 players
		case KEY_DOWN:
			PlayGame(False, False);
			OpenDraw();
			break;

		// quit
		case KEY_Y: ResetToBootLoader();
		}
	}
}
