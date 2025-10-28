
// ****************************************************************************
//
//                              Fifteen game
//
// ****************************************************************************

#include "../include.h"

#define TILEW		24	// tile width in pixels
#define TILEH		16	// tile height in lines
#define TILESXNUM	4	// number of tiles in X direction
#define TILESYNUM	4	// number of tiles in Y direction
#define TILESNUM	(TILESXNUM*TILESYNUM) // number of tiles (= 16)
#define TILE_EMPTY	15	// index of empty tile
#define TILEY		0	// first tile Y coordinate
#define TILEX		((WIDTH-TILEW*TILESXNUM)/2) // first tile X coordinate

// game board
u8 Board[TILESNUM];	// visible board
u8 BoardSave[TILESNUM];	// saved board during game
u8 Pos[TILESNUM];	// position of tiles (including hole)
u8 PosErr; // number of tiles on incorrect position
Bool Locked[TILESNUM]; // solved groups: locked tiles
Bool Solved[TILESNUM]; // solved groups: tiles to solve
int Dist; // current distance of numeric tiles from result position (0 = result is OK)

#define PREDEPTH_MAX 14 // max. depth of pre-solver (must be <= DEPTH_MAX)
#define DEPTH_MAX 17 // max. depth of solver (real depth is max. 19)
s8 Moves[DEPTH_MAX]; // moves
int MovesNum;	// number of moves
int DepthMax;	// current max. depth

s8 BestMoves[DEPTH_MAX]; // best moves
int BestMovesNum;	// number of best moves
int BestDist;	// distance of best moves

// move sound
const sMelodyNote MoveSound[] = {
	{ 1, NOTE_C6 },
	{ 0, 0 },
};

// bump sound
const sMelodyNote BumpSound[] = {
	{ 4, NOTE_C3 },
	{ 0, 0 },
};

// win sound
const sMelodyNote WinSound[] = {
	{ NOTE_LEN4, NOTE_C5 },
	{ NOTE_LEN4, NOTE_E5 },
	{ NOTE_LEN4, NOTE_G5 },
	{ NOTE_LEN2, NOTE_C6 },
	{ 0, 0 },
};

#define Hole Pos[TILE_EMPTY] // position of hole

// get hole X coordinate
INLINE u8 HoleX() { return Hole & 3; }

// get hole Y coordinate
INLINE u8 HoleY() { return Hole >> 2; }

// check goal state
INLINE Bool Check() { return PosErr == 0; }

// solved group table: number of tiles (0 = end mark), list of tiles 1..
const u8 SolverTab[] = {
	1, 1,
	1, 2,
	1, 5,
	1, 6,
	2, 3, 4,
	2, 7, 8,
	2, 9, 13,
	2, 10, 14,
	3, 11, 12, 15,
	0
};

// Draw board
void DrawBoard()
{
	int i, j, x, y, b;
	for (i = 0; i < TILESYNUM; i++)
	{
		for (j = 0; j < TILESXNUM; j++)
		{
			x = j*TILEW + TILEX;
			y = i*TILEH + TILEY;
			b = Board[i*TILESXNUM + j];
			DrawImgBg(ImgTiles + b*TILEH*3, x, y, TILEW, TILEH, 3);
		}
	}
	DispUpdate();
}

// wait icon ON
void WaitOn()
{
	int x = HoleX()*TILEW + TILEX;
	int y = HoleY()*TILEH + TILEY;
	DrawCharCond6Bg(8, x+TILEW/2-3, y+5);
	DispUpdate();
}

// wait icon ON
void WaitOn2()
{
	int x = HoleX()*TILEW + TILEX;
	int y = HoleY()*TILEH + TILEY;
	DrawCharCond6Bg(9, x+TILEW/2-3, y+5);
	DispUpdate();
}

// wait icon OFF
void WaitOff()
{
	int x = HoleX()*TILEW + TILEX;
	int y = HoleY()*TILEH + TILEY;
	int b = Board[HoleX()*TILESXNUM + HoleY()];
	DrawImgBg(ImgTiles + y*TILEW*3, x, y, TILEW, TILEH, 3);
	DispUpdate();
}

// calculate position error
void CalcPos()
{
	int i, x, y, err, dist;
	u8 b;
	err = 0;
	dist = 0;
	for (i = 0; i < TILESNUM; i++)
	{
		b = Board[i];
		if (b != TILE_EMPTY)
		{
			if (Solved[b] && (b != (u8)i)) err++;
			x = (i & 3) - (b & 3);
			y = (i >> 2) - (b >> 2);
			if (Solved[b])
			{
				x *= 4;
				y *= 4;
			}
			dist += x*x + y*y;
		}
		Pos[b] = i;
	}
	PosErr = err;
	Dist = dist;
}

// shift hole (-4, -1, +1, +4), without checking coordinates
void Shift(s8 shift)
{
	int x, y;

	// old index of the hole (= tile new index)
	u8 oldinx = Hole;

	// new index of the hole (= tile old index)
	u8 newinx = oldinx + shift;

	// get tile
	u8 b = Board[newinx];
	if ((b == newinx) && Solved[b]) PosErr++;
	x = (b & 3) - (newinx & 3);
	y = (b >> 2) - (newinx >> 2);
	if (Solved[b])
	{
		x *= 4;
		y *= 4;
	}
	Dist -= x*x + y*y;

	// move tile
	Board[oldinx] = b;
	if ((b == oldinx) && Solved[b]) PosErr--;
	x = (b & 3) - (oldinx & 3);
	y = (b >> 2) - (oldinx >> 2);
	if (Solved[b])
	{
		x *= 4;
		y *= 4;
	}
	Dist += x*x + y*y;
	Pos[b] = oldinx;

	// set hole
	Board[newinx] = TILE_EMPTY;
	Hole = newinx;
}

// initialize new game
void NewGame()
{
	DrawClear();
	int i;

	// initialize new state
	for (i = 0; i < TILESNUM; i++)
	{
		Locked[i] = False;
		Solved[i] = True;
		Board[i] = i;
		Pos[i] = i;
	}
	Dist = 0;
	PosErr = 0;

	// draw board
	DrawBoard();
}

// Shuffle board
void Shuffle()
{
	int i;
	u8 r;

	for (i = 3000; i > 0; i--)
	{
		r = RandU8();
		if (r >= 0x80) // shift in X direction
		{
			if ((r & 1) == 0)
			{
				// shift hole left
				if (HoleX() > 0) Shift(-1);
			}
			else
			{
				// shift hole right
				if (HoleX() < TILESXNUM-1) Shift(1);
			}
		}
		else // shift in Y direction
		{
			if ((r & 1) == 0)
			{
				// shift hole up
				if (HoleY() > 0) Shift(-TILESXNUM);
			}
			else
			{
				// shift hole down
				if (HoleY() < TILESYNUM-1) Shift(TILESXNUM);
			}
		}

		// draw board
		if ((i & 0xff) == 0)
		{
			DrawBoard();
			WaitMs(15);
			PlayTone(5000);
			WaitMs(7);
			StopSound();
		}

		KeyFlush();
	}
	DrawBoard();
	KeyFlush();
}

// pre-solve 1 level
void PreSolve1()
{
	// completed
	if (Dist == 0) return;

	// copy better solution
	if ((Dist < BestDist) || ((Dist == BestDist) && (MovesNum < BestMovesNum)))
	{
		memcpy(BestMoves, Moves, MovesNum);
		BestMovesNum = MovesNum;
		BestDist = Dist;
	}

	// check max. depth
	int movesnum = MovesNum;
	if (movesnum >= DepthMax) return;
	MovesNum = movesnum+1;

	// shift hole left
	if ((HoleX() > 0) && !Locked[Board[Hole - 1]])
	{
		Shift(-1);
		Moves[movesnum] = -1;
		PreSolve1();
		Shift(1);
	}

	// shift hole right
	if ((HoleX() < TILESXNUM-1) && !Locked[Board[Hole + 1]])
	{
		Shift(1);
		Moves[movesnum] = 1;
		PreSolve1();
		Shift(-1);
	}

	// shift hole up
	if ((HoleY() > 0) && !Locked[Board[Hole - TILESXNUM]])
	{
		Shift(-TILESXNUM);
		Moves[movesnum] = -TILESXNUM;
		PreSolve1();
		Shift(TILESXNUM);
	}

	// shift hole down
	if ((HoleY() < TILESYNUM-1) && !Locked[Board[Hole + TILESXNUM]])
	{
		Shift(TILESXNUM);
		Moves[movesnum] = TILESXNUM;
		PreSolve1();
		Shift(-TILESXNUM);
	}

	// return number of moves
	MovesNum = movesnum;
}

// solve 1 level (returns True to completed)
Bool Solve1()
{
	Bool res;

	// completed
	if (PosErr == 0) return True;

	// check max. depth
	int movesnum = MovesNum;
	if (movesnum >= DepthMax) return False;
	MovesNum = movesnum+1;

	// shift hole left
	if ((HoleX() > 0) && !Locked[Board[Hole - 1]])
	{
		Shift(-1);
		Moves[movesnum] = -1;
		res = Solve1();
		Shift(1);
		if (res) return True;
	}

	// shift hole right
	if ((HoleX() < TILESXNUM-1) && !Locked[Board[Hole + 1]])
	{
		Shift(1);
		Moves[movesnum] = 1;
		res = Solve1();
		Shift(-1);
		if (res) return True;
	}

	// shift hole up
	if ((HoleY() > 0) && !Locked[Board[Hole - TILESXNUM]])
	{
		Shift(-TILESXNUM);
		Moves[movesnum] = -TILESXNUM;
		res = Solve1();
		Shift(TILESXNUM);
		if (res) return True;
	}

	// shift hole down
	if ((HoleY() < TILESYNUM-1) && !Locked[Board[Hole + TILESXNUM]])
	{
		Shift(TILESXNUM);
		Moves[movesnum] = TILESXNUM;
		res = Solve1();
		Shift(-TILESXNUM);
		if (res) return True;
	}

	// return number of moves
	MovesNum = movesnum;

	return False;
}

// solver
void Solver()
{
	Bool ok;
	const u8* t = SolverTab;
	int i, j;
	int faster1 = 7; // speed-up pre-solver
	int faster2 = 10; // speed-up solver
	Bool err;

	// clear solved group tabled
	for (i = 0; i < TILESNUM; i++)
	{
		Locked[i] = False;
		Solved[i] = False;
	}

	while (True)
	{
		// prepare next solved group
		MovesNum = 0;
		for (i = 0; i < TILESNUM; i++)
		{
			if (Solved[i]) Locked[i] = True; // lock already solved tiles
		}

		// update positions
		i = *t++; // number of tiles of next solved group
		if (i == 0) break; // end of table
		for (; i > 0; i--) Solved[*t++ - 1] = True;
		CalcPos();

PRE_AGAIN:
		// pre-solver
		err = True;
		WaitOn();

		// pre-solve
		BestMovesNum = 0;
		BestDist = Dist;
		DepthMax = PREDEPTH_MAX - faster1;
		PreSolve1();

		// play moves
		if (BestMovesNum > 0)
		{
			WaitOff();
			for (i = 0; i < BestMovesNum; i++)
			{
				// shift tile
				Shift(BestMoves[i]);
				PlayMelody(MoveSound);
				DrawBoard();

				// wait some time
				WaitMs(100);
				if (KeyGet() != NOKEY) return;
				WaitMs(100);
				if (KeyGet() != NOKEY) return;
			}
			WaitOn();
			err = False;

			// found some solution, so slower solver
			if (faster2 < 10) faster2++;
		}

		// quit
		if (KeyGet() != NOKEY) return;

		// solver
		WaitOn2();
		DepthMax = 0;
		do {
			DepthMax++;
			ok = Solve1();
		} while (!ok && (DepthMax < DEPTH_MAX - faster2));

		// not found, slower down all and repeat all again
		if (!ok && !Check())
		{
			if (err && (faster1 > 0)) faster1--;
			if (err && (faster2 > 0)) faster2--;
			goto PRE_AGAIN; // not found, try pre-solver again
		}

		// play moves
		if (MovesNum > 0)
		{
			WaitOff();
			for (i = 0; i < MovesNum; i++)
			{
				// shift tile
				Shift(Moves[i]);
				PlayMelody(MoveSound);
				DrawBoard();

				// wait some time
				WaitMs(100);
				if (KeyGet() != NOKEY) return;
				WaitMs(100);
				if (KeyGet() != NOKEY) return;
			}
			WaitOn2();
			err = False;

			// found some solution, so slower pre-solver
			if (faster1 < 7) faster1++;
		}

		// error of pre-solver and solver, slower down all
		if (err && (faster1 > 0)) faster1--;
		if (err && (faster2 > 0)) faster2--;
	}

	// initialize new state
	for (i = 0; i < TILESNUM; i++)
	{
		Locked[i] = False;
		Solved[i] = True;
	}
	WaitOff();
	CalcPos();
	DrawBoard();
}

int main(void)
{
	char ch;
	int i;
	int oldbat;
	int bat;

	while (True)
	{
Restart:
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
					DrawTextCond6Bg(DecNumBuf, WIDTH-5*6, 0);
					DispUpdate();
				}
			}
		}
		DrawClear();

		// initialize new game
		NewGame();

		// randomize
		RandSeed += Time();

		// Shuffle board
		Shuffle();

		// game loop
		while (True)
		{
			// key
			switch(KeyGet())
			{
			// right
			case KEY_RIGHT:
				if (HoleX() > 0)
				{
					Shift(-1);
					PlayMelody(MoveSound);
					DrawBoard();
				}
				else
					PlayMelody(BumpSound);
				break;

			// left
			case KEY_LEFT:
				if (HoleX() < TILESXNUM-1)
				{
					Shift(1);
					PlayMelody(MoveSound);
					DrawBoard();
				}
				else
					PlayMelody(BumpSound);
				break;

			// up
			case KEY_UP:
				if (HoleY() < TILESYNUM-1)
				{
					Shift(TILESXNUM);
					PlayMelody(MoveSound);
					DrawBoard();
				}
				else
					PlayMelody(BumpSound);
				break;

			// down
			case KEY_DOWN:
				if (HoleY() > 0)
				{
					Shift(-TILESXNUM);
					PlayMelody(MoveSound);
					DrawBoard();
				}
				else
					PlayMelody(BumpSound);
				break;

			// solver
			case KEY_A:
				Solver();

				for (i = 0; i < TILESNUM; i++)
				{
					Locked[i] = False;
					Solved[i] = True;
				}
				CalcPos();
				break;

			// exit
			case KEY_B:
				goto Restart;
			}

			// check solution
			if (Check())
			{
				// play fanfare
				PlayMelody(WinSound);

				// winning animation
				for (i = 5; i > 0; i--)
				{
					WaitMs(150);
					DrawClear();
					DispUpdate();
					WaitMs(150);
					DrawBoard();
				}

				// flush keyboard
				KeyFlush();
				while (KeyGet() == NOKEY) {}
				WaitMs(200);
				KeyFlush();
				break;
			}
		}
	}
}
