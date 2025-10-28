
// ****************************************************************************
//
//                                  Tetris game
//
// ****************************************************************************

#include "../include.h"

#define TILESIZE 4	// tile size in number of pixels
#define MAPW	((WIDTH+TILESIZE-1)/TILESIZE) // board width (=32)
#define MAPH	((HEIGHT+TILESIZE-1)/TILESIZE) // board height (=16)
#define MAPSIZE	(MAPW*MAPH) // board size (=512)

#define GAMEW	10	// width of game field
#define GAMEX	10	// start index X of game field
#define GAMEH	16	// height of game field
#define GAMEY	0	// start index Y of game field

#define TILE_BLACK	0	// black tile
#define TILE_BRICK1	1	// brick 1
#define TILE_BRICK2	2	// brick 2
#define TILE_BRICK3	3	// brick 3
#define TILE_BRICK4	4	// brick 4
#define TILE_BRICK5	5	// brick 5
#define TILE_BRICK6	6	// brick 6
#define TILE_BRICK7	7	// brick 7
#define TILE_EMPTY	8	// empty game tile
#define TILE_WALL	9	// wall

#define BASEBRICKNUM 7	// number of basebricks
#define BRICKTEMPNUM 19	// number of brick templates
#define BRICKTEMPSIZE 16 // size of one brick template

#define LEVELNUM	10	// number of levels

u8 Level;	// current level (1..)
u8 LevelBest;	// best level
u8 Brick;	// current brick (0..18)
u8 NextBrick;	// nextbrick (0..18)
s8 BrickX, BrickY; // brick coordinates
Bool Falling;	// brick is falling
int BrickScore;	// score of current brick
u32 Score;	// game score
u32 ScoreBest;	// best game score
int StepSpeed;	// step speed
int SpeedCnt;	// speed counter
int Lines;	// lines
int LinesBest;	// best lines
int NextLevel; 	// next level
Bool Demo;	// demo mode

// brick sound
const sMelodyNote BrickSound[] = {
	{ 1, NOTE_C3 },
	{ 0, 0 },
};

// line sound
const sMelodyNote LineSound[] = {
	{ 1, NOTE_C3 },
	{ 1, NOTE_D3 },
	{ 1, NOTE_E3 },
	{ 1, NOTE_F3 },
	{ 1, NOTE_G3 },
	{ 1, NOTE_A3 },
	{ 0, 0 },
};

// game over sound
const sMelodyNote GameOverSound[] = {
	{ NOTE_LEN8, NOTE_A4 },
	{ NOTE_LEN8, NOTE_E4 },
	{ NOTE_LEN8, NOTE_C4 },
	{ NOTE_LEN4, NOTE_A3 },
	{ 0, 0 },
};

// Level up sound
const sMelodyNote LevelUpSound[] = {
	{ 4, NOTE_C4 },
	{ 4, NOTE_B4 },
	{ 4, NOTE_CS4 },
	{ 4, NOTE_AS4 },
	{ 4, NOTE_D4 },
	{ 4, NOTE_A4 },
	{ 4, NOTE_DS4 },
	{ 4, NOTE_GS4 },
	{ 4, NOTE_E4 },
	{ 4, NOTE_G4 },
	{ 4, NOTE_F4 },
	{ 4, NOTE_FS4 },
	{ 8, NOTE_F4 },
	{ 0, 0 },
};

int Stat[BASEBRICKNUM]; // brick statistic

// game board (1st tile = high nibble, 2nd tile = low nibble)
u8 Board[MAPSIZE/2];

// board template
const u8 BoardTemp[MAPW*MAPH/2] = {
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x00, 0x00, 0x00, 0x00, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x01, 0x11, 0x10, 0x00, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x00, 0x00, 0x00, 0x00, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x00, 0x00, 0x02, 0x20, 0x09,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x00, 0x00, 0x02, 0x20, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x33, 0x30, 0x00, 0x00, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x30, 0x00, 0x00, 0x00, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x00, 0x00, 0x04, 0x44, 0x09,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x00, 0x00, 0x00, 0x04, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x55, 0x00, 0x00, 0x00, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x05, 0x50, 0x00, 0x00, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x00, 0x00, 0x00, 0x66, 0x09,
	0x99, 0x99, 0x99, 0x99, 0x99, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x00, 0x00, 0x06, 0x60, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x77, 0x70, 0x00, 0x00, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x07, 0x00, 0x00, 0x00, 0x09,
	0x90, 0x00, 0x00, 0x00, 0x09, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90, 0x00, 0x00, 0x00, 0x00, 0x09,
};

// bricks templates (rotations are in counterclockwise direction)
const u8 BrickTemp[BRICKTEMPNUM*BRICKTEMPSIZE] = {
	// 0 (7)
	0, 0, 0, 0,
	1, 1, 1, 1,
	0, 0, 0, 0,
	0, 0, 0, 0,

	// 1
	0, 0, 0, 0,
	0, 2, 2, 0,
	0, 2, 2, 0,
	0, 0, 0, 0,

	// 2 (8) (9) (10)
	0, 0, 0, 0,
	3, 3, 3, 0,
	3, 0, 0, 0,
	0, 0, 0, 0,

	// 3 (11) (12) (13)
	0, 0, 0, 0,
	4, 4, 4, 0,
	0, 0, 4, 0,
	0, 0, 0, 0,

	// 4 (14)
	0, 0, 0, 0,
	5, 5, 0, 0,
	0, 5, 5, 0,
	0, 0, 0, 0,

	// 5 (15)
	0, 0, 0, 0,
	0, 6, 6, 0,
	6, 6, 0, 0,
	0, 0, 0, 0,

	// 6 (16) (17) (18)
	0, 0, 0, 0,
	7, 7, 7, 0,
	0, 7, 0, 0,
	0, 0, 0, 0,

	// (0) 7
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,

	// (2) 8 (9) (10)
	0, 3, 0, 0,
	0, 3, 0, 0,
	0, 3, 3, 0,
	0, 0, 0, 0,

	// (2) (8) 9 (10)
	0, 0, 0, 0,
	0, 0, 3, 0,
	3, 3, 3, 0,
	0, 0, 0, 0,

	// (2) (8) (9) 10
	3, 3, 0, 0,
	0, 3, 0, 0,
	0, 3, 0, 0,
	0, 0, 0, 0,

	// (3) 11 (12) (13)
	0, 4, 4, 0,
	0, 4, 0, 0,
	0, 4, 0, 0,
	0, 0, 0, 0,

	// (3) (11) 12 (13)
	0, 0, 0, 0,
	4, 0, 0, 0,
	4, 4, 4, 0,
	0, 0, 0, 0,

	// (3) (11) (12) 13
	0, 4, 0, 0,
	0, 4, 0, 0,
	4, 4, 0, 0,
	0, 0, 0, 0,

	// (4) 14
	0, 5, 0, 0,
	5, 5, 0, 0,
	5, 0, 0, 0,
	0, 0, 0, 0,

	// (5) 15
	0, 6, 0, 0,
	0, 6, 6, 0,
	0, 0, 6, 0,
	0, 0, 0, 0,

	// (6) 16 (17) (18)
	0, 7, 0, 0,
	0, 7, 7, 0,
	0, 7, 0, 0,
	0, 0, 0, 0,

	// (6) (16) 17 (18)
	0, 0, 0, 0,
	0, 7, 0, 0,
	7, 7, 7, 0,
	0, 0, 0, 0,

	// (6) (16) (17) 18
	0, 7, 0, 0,
	7, 7, 0, 0,
	0, 7, 0, 0,
	0, 0, 0, 0,
};

// brick rotations
const u8 BrickRot[BRICKTEMPNUM] = {
//	0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18
	7,  1,  8, 11, 14, 15, 16,  0,  9, 10,  2, 12, 13,  3,  4,  5, 17, 18,  6,
};

// level score
const int LevScore[LEVELNUM] = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };

// count lines to next level
const int NextLevelTab[LEVELNUM] = { 10, 20, 50, 100, 150, 250, 400, 500, 700, 1000000000 };

#define TIMEDELAY	10 	// base time delay

#define SPEEDFALL	TIMEDELAY // falling speed

// level speed (step delay in [ms] - should be multiply of TIMEDELAY)
const int LevSpeed[LEVELNUM] = { 1000, 700, 500, 350, 250, 200, 180, 150, 120, 100 };

// display one tile of the board
void DispTile(u8 x, u8 y)
{
	int tile = Board[(x >> 1) + y*(MAPW >> 1)];
	if ((x & 1) == 0) tile >>= 4;
	tile &= 0x0f;
	x *= TILESIZE;
	y *= TILESIZE;

	switch (tile)
	{
//	case TILE_BLACK:
//	case TILE_EMPTY:
	default:
		DrawRectClr(x, y, TILESIZE, TILESIZE);
		break;

	case TILE_BRICK1:
	case TILE_BRICK2:
	case TILE_BRICK3:
	case TILE_BRICK4:
	case TILE_BRICK5:
	case TILE_BRICK6:
	case TILE_BRICK7:
		DrawImgBg(ImgTile, x, y, TILESIZE, TILESIZE, 1);
		break;

	case TILE_WALL:
		DrawImgBg(ImgBrick, x, y, TILESIZE, TILESIZE, 1);
		break;
	}
}

// display all tiles
void DispBoard()
{
	int x, y;
	for (y = 0; y < MAPH; y++)
	{
		for (x = 0; x < MAPW; x++) DispTile(x, y);
	}
}

// put tile on the board
void PutTile(u8 x, u8 y, u8 tile)
{
	u8* d = &Board[(x >> 1) + y*(MAPW >> 1)];
	if ((x & 1) == 0)
		*d = (*d & 0x0f) | (tile << 4);
	else
		*d = (*d & 0xf0) | tile;
	DispTile(x, y);
}

// get tile from board
u8 GetTile(u8 x, u8 y)
{
	int tile = Board[(x >> 1) + y*(MAPW >> 1)];
	if ((x & 1) == 0) tile >>= 4;
	tile &= 0x0f;
	return tile;
}

// display number (x = middle coordinate)
char NumBuf[12];
void DispTileNum(int x, int y, int num)
{
	int n = DecNum(NumBuf, num, 0);
	DrawTextCond6Bg(NumBuf, x - n*3, y+1);
}

void DispTileNumL(int x, int y, int num)
{
	int n = DecNum(NumBuf, num, 0);
	DrawTextCond6Bg(NumBuf, x, y+1);
}

void DispTileNumR(int x, int y, int num)
{
	int n = DecNum(NumBuf, num, 0);
	DrawTextCond6Bg(NumBuf, x - n*6, y+1);
}

// display titles
void DispTitle()
{
	// titles
	DrawTextCond6Bg("SCORE", TILESIZE + (8*TILESIZE - 5*6)/2, 6*TILESIZE-4);
	DrawTextCond6Bg("LINE", TILESIZE + (8*TILESIZE - 4*6)/2, 10*TILESIZE-4);
	DrawTextCond6Bg("LEVEL", TILESIZE + (8*TILESIZE - 5*6)/2, 14*TILESIZE-4);
}

// display score
void DispScore()
{
#define SCOREX	(TILESIZE + 4*TILESIZE)
	// display score
	DispTileNum(SCOREX, 6*TILESIZE+1, Score);

	// display lines
	DispTileNum(SCOREX, 10*TILESIZE+1, Lines);

	// display speed
	DispTileNum(SCOREX, 14*TILESIZE+1, Level);
}

// display statistics
void DispStat()
{
	int i;
	DispTileNumL(27*TILESIZE+1, 3, Stat[0]);
	for (i = 1; i < BASEBRICKNUM; i++)
	{
		if ((i & 1) == 0)
			DispTileNumL(25*TILESIZE+1, i*2*TILESIZE+4, Stat[i]);
		else
			DispTileNumR(27*TILESIZE-1, i*2*TILESIZE+4, Stat[i]);
	}
}

// display next brick
void DispNext()
{
	// get brick template
	const u8* s = &BrickTemp[NextBrick*BRICKTEMPSIZE];

	// display brick
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			PutTile(3+j, i, *s++);
		}
	}
}

// display all and update
void DispAll()
{
	DispBoard(); // display board
	DispTitle(); // display titles
	DispScore(); // display score
	DispStat(); // display statistics
	DispNext(); // display next brick
	DispUpdate();
}

// display brick
void DispBrick(s8 x, s8 y, u8 brick)
{
	// get brick template
	const u8* s = &BrickTemp[brick*BRICKTEMPSIZE];

	// rows
	int i, j;
	u8 b;
	for (i = 0; i < 4; i++)
	{
		// columns
		for (j = 0; j < 4; j++)
		{
			b = *s++;
			if (b != 0) PutTile(x+j, y+i, b);
		}
	}
}

// clear brick
void ClearBrick(s8 x, s8 y, u8 brick)
{
	// get brick template
	const u8* s = &BrickTemp[brick*BRICKTEMPSIZE];

	// rows
	int i, j;
	u8 b;
	for (i = 0; i < 4; i++)
	{
		// columns
		for (j = 0; j < 4; j++)
		{
			b = *s++;
			if (b != 0) PutTile(x+j, y+i, TILE_EMPTY);
		}
	}
}

// check brick (output False on check error)
Bool CheckBrick(s8 x, s8 y, u8 brick)
{
	// get brick template
	const u8* s = &BrickTemp[brick*BRICKTEMPSIZE];

	// rows
	int i, j;
	u8 b;
	for (i = 0; i < 4; i++)
	{
		// columns
		for (j = 0; j < 4; j++)
		{
			b = *s++;
			if (b != 0)
			{
				if ((y < 0) || (y >= MAPH) || (GetTile(x+j, y) != TILE_EMPTY))
					return False;
			}
		}
		y++;
	}
	return True;
}

// calculate score of the brick (= sum of Y of stones)
int ScoreBrick(s8 x, s8 y, u8 brick)
{
	// get brick template
	const u8* s = &BrickTemp[brick*BRICKTEMPSIZE];

	// rows
	int i, j;
	int score = 0;
	u8 b;
	for (i = 0; i < 4; i++)
	{
		// columns
		for (j = 0; j < 4; j++)
		{
			b = *s;
			if (b != 0)
			{
				score += (int)y*y;

				if (y > 2)
				{
					// minus score on empty neighbors
					if ((y < MAPH-2) &&
						(GetTile(x+j, y+1) == TILE_EMPTY) && // neighbor on down
						((i == 3) || (s[4] == 0)))
						score -= 10;

					if ((GetTile(x+j-1, y) == TILE_EMPTY) && // neighbor on left
						((j == 0) || (s[-1] == 0)))
						score -= 2;

					if ((GetTile(x+j+1, y) == TILE_EMPTY) && // neighbor on right
						((j == 3) || (s[1] == 0)))
						score -= 2;
				}
			}
			s++;
		}
		y++;
	}
	return score;
}

// delete row of the stones
void DelRow(u8 y)
{
	u8 i, j;

	// sound
	PlayMelody(LineSound);

	// increment lines
	Lines++;
	DispScore();

	// shift full row out
	for (i = GAMEW; i > 0; i--)
	{
		for (j = 0; j < GAMEW-1; j++)
		{
			PutTile(GAMEX+j, y, GetTile(GAMEX+j+1, y));
		}
		PutTile(GAMEX+j, y, TILE_EMPTY);
		DispUpdate();
		WaitMs(50);
	}

	// move higher stones down
	for (; y > 0; y--)
	{
		for (j = 0; j < GAMEW; j++)
		{
			PutTile(GAMEX+j, y, GetTile(GAMEX+j, y-1));
		}
	}

	// empty last row
	for (j = 0; j < GAMEW; j++)
	{
		PutTile(GAMEX+j, 0, TILE_EMPTY);
	}
}

// delete rows
void DelAllRows()
{
	int i, y;
	Bool ok;

	// search full rows
	for (y = MAPH-1; y >= 0; y--)
	{
		ok = True;
		for (i = 0; i < GAMEW; i++)
		{
			if (GetTile(GAMEX+i, y) == TILE_EMPTY)
			{
				ok = False;
				break;
			}
		}

		// delete this row
		if (ok)
		{
			DelRow(y);
			y++; // stay at this row
			NextLevel--;
		}
	}

	// next level
	if ((NextLevel <= 0) && (Level < LEVELNUM) && !Demo)
	{
		// increse level
		Level++;
		DispScore();
		NextLevel = NextLevelTab[Level-1];

		// play sound
		PlayMelody(LevelUpSound);

		// display message
		DrawTextCond6Bg("LEVELUP", GAMEX*TILESIZE + GAMEW*TILESIZE/2 - 7*6/2, HEIGHT/2);

		// wait
		DispUpdate();
		WaitMs(1000);

		// restore board
		DispAll();

		// wait
		KeyFlush();
		DispUpdate();
		WaitMs(200);
	}
}

// generate next brick
void GenBrick()
{
	// catch current brick from next brick
	Brick = NextBrick;

	// update statistics of current brick
	Stat[Brick]++;

	// display statistics
	DispStat();

	// generate next brick
	NextBrick = RandU8Max(BASEBRICKNUM-1);

	// display next brick
	DispNext();

	// brick coordinate
	BrickX = MAPW/2-2;
	BrickY = 0;

	// prepare brick score
	BrickScore = LevScore[Level-1];

	// prepare step speed
	SpeedCnt = StepSpeed;

	// not falling
	Falling = False;
}

// check brick and save new position if OK
Bool CheckBrickSave(s8 x, s8 y, u8 brick)
{
	Bool res = CheckBrick(x, y, brick);
	if (res)
	{
		BrickX = x;
		BrickY = y;
		Brick = brick;
	}
	return res;
}

// check brick with moving to left and right
Bool CheckBrickX(s8 x, s8 y, u8 brick)
{
	if (CheckBrickSave(x, y, brick)) return True;
	if (CheckBrickSave(x-1, y, brick)) return True;
	if (CheckBrickSave(x+1, y, brick)) return True;
	if (CheckBrickSave(x-2, y, brick)) return True;
	return CheckBrickSave(x+2, y, brick);
}

// check brick with moving down
Bool CheckBrickY(s8 x, s8 y, u8 brick)
{
	if (CheckBrickX(x, y, brick)) return True;
	if (CheckBrickX(x, y+1, brick)) return True;
	return CheckBrickX(x, y+2, brick);
}

// start new game
void NewGame()
{
	// initialize board
	int i, j;
	const u8* src;
	memcpy(Board, BoardTemp, sizeof(BoardTemp));
	DispBoard();

	// display titles
	DispTitle();

	// clear variables
	NextBrick = 0;
	Level = 1; // current level (1..)
	NextLevel = NextLevelTab[Level-1]; // next level counter
	Score = 0;	// game score
	Lines = 0;	// lines
	for (i = 0; i < BASEBRICKNUM; i++) Stat[i] = 0;
	StepSpeed = LevSpeed[Level-1];

	// generate this brick
	GenBrick();
	Stat[0]--;

	// generate next brick (and update statistics)
	GenBrick();

	// display score
	DispScore();

	// display current brick
	DispBrick(BrickX, BrickY, Brick);
}

// check end game (returns True to continue)
Bool CheckEnd()
{
	int i;

	// check new brick on start position
	if (!CheckBrick(BrickX, BrickY, Brick))
	{
		// best score
		if (!Demo)
		{
			if (Level > LevelBest) LevelBest = Level;
			if (Score > ScoreBest) ScoreBest = Score;
			if (Lines > LinesBest) LinesBest = Lines;
			DispScore();
		}

		// play sound
		PlayMelody(GameOverSound);

		// loop 2 seconds
		for (i = 10; i > 0; i--)
		{
			// display message
			DrawTextCond6Bg("GAMEOVER", GAMEX*TILESIZE + GAMEW*TILESIZE/2 - 8*6/2, HEIGHT/2);

			// wait
			DispUpdate();
			WaitMs(100);

			// restore board
			DispAll();

			// wait
			WaitMs(100);
		}

		if (Demo) return False;

		// display message
		DrawTextCond6Bg("GAMEOVER", GAMEX*TILESIZE + GAMEW*TILESIZE/2 - 8*6/2, HEIGHT/2);

		// wait for a key
		KeyFlush();
		while (KeyGet() == NOKEY) {}

		// restore board
		DispAll();

		return False;
	}

	// game is OK
	return True;
}

// pause game (returns True = continue, False = timeout)
Bool Pause(Bool timeout)
{
	// display message
	DrawTextCond6Bg("PAUSE", GAMEX*TILESIZE + GAMEW*TILESIZE/2 - 5*6/2, HEIGHT/2);
	DispUpdate();

	// wait key (returns False on timeout)
	KeyFlush();
	int i;
	for (i = (timeout ? 100 : 1000000000) ; i > 0; i--)
	{
		if (KeyGet() != NOKEY) break;
		WaitMs(100);
	}

	// restore board
	DispAll();

	return i > 0; // i > 0 if continue
}

// process game (True = break)
Bool Game()
{
	u8 b;
	char ch;

	// start new game
	NewGame();

	// pause (return on timeout)
	if (!Pause(True)) return False;

	// game loop
	while (True)
	{
		// step counter
		DispUpdate();
		WaitMs(TIMEDELAY);
		SpeedCnt -= TIMEDELAY;
		if (SpeedCnt <= 0)
		{
			// clear current brick
			ClearBrick(BrickX, BrickY, Brick);

			// check new position
			if (!CheckBrick(BrickX, BrickY+1, Brick))
			{
				// display brick
				DispBrick(BrickX, BrickY, Brick);

				// update score
				Score += BrickScore;
				DispScore();

				// sound
				PlayMelody(BrickSound);

				// delete rows
				DelAllRows();

				// short delay
				DispUpdate();
				WaitMs(50);

				// generate new brick
				GenBrick();

				// check end of the game
				if (!CheckEnd())
				{
					// start new game
					NewGame();

					// pause (return on timeout)
					if (!Pause(True)) return False;
				}
				else
					// display new brick
					DispBrick(BrickX, BrickY, Brick);
			}

			// move brick down
			else
			{
				BrickY++;
				DispBrick(BrickX, BrickY, Brick);
				SpeedCnt = Falling ? SPEEDFALL : StepSpeed;
				if (!Falling && (BrickScore > 0)) BrickScore--;
			}
		}

		// key service if not falling
		if (!Falling)
		{
			// keyboard
			ch = KeyGet();
			switch (ch)
			{
			// right
			case KEY_RIGHT:
				// clear current brick
				ClearBrick(BrickX, BrickY, Brick);

				// check new position
				if (CheckBrick(BrickX+1, BrickY, Brick)) BrickX++;
				
				// display brick
				DispBrick(BrickX, BrickY, Brick);
				break;

			// left
			case KEY_LEFT:
				// clear current brick
				ClearBrick(BrickX, BrickY, Brick);

				// check new position
				if (CheckBrick(BrickX-1, BrickY, Brick)) BrickX--;
				
				// display brick
				DispBrick(BrickX, BrickY, Brick);
				break;

			// down - falling
			case KEY_DOWN:
				Falling = True;
				if (SpeedCnt > SPEEDFALL) SpeedCnt = SPEEDFALL;
				break;

			// up - rotate
			case KEY_UP:
			case KEY_A:
				// clear current brick
				ClearBrick(BrickX, BrickY, Brick);

				// get new brick
				b = BrickRot[Brick];

				// try rotate brick, find nearest free space
				CheckBrickY(BrickX, BrickY, b);

				// display brick
				DispBrick(BrickX, BrickY, Brick);
				break;

/*
			// pause
			case KEY_X:
#if USE_SCREENSHOT	// 1=use screen shot
				ScreenShot();
#else
				Pause(False);
#endif
				break;
*/
	
/*
			case KEY_Y:
#if USE_SCREENSHOT	// 1=use screen shot
				ScreenShot();
#endif
				return True;
*/

			case KEY_B:
				return True;

			case NOKEY:
				break;

			// invalid key
			default:
				KeyFlush();
				break;
			}
		}
	}
}

// find demo move
void FindDemo()
{
	int i, rot;
	int score, newbrick; // current score
	int bestscore, bestx, besty, bestbrick; // best move
	int savex, savey, savebrick; // save state

	// clear best score
	bestscore = 0;
	bestx = BrickX;
	besty = BrickY;
	bestbrick = Brick;

	// clear brick
	ClearBrick(BrickX, BrickY, Brick);

	// rotations
	for (rot = 4; rot > 0; rot--)
	{
		// get new brick
		newbrick = BrickRot[Brick];

		// try rotate brick, find nearest free space
		CheckBrickY(BrickX, BrickY, newbrick);

		// move brick left
		while (CheckBrick(BrickX-1, BrickY, Brick)) BrickX--;

		// loop all positions
		while (True)
		{
			// save current state
			savex = BrickX;
			savey = BrickY;
			savebrick = Brick;

			// move down
			while (CheckBrick(BrickX, BrickY+1, Brick)) BrickY++;

			// calculate score
			score = ScoreBrick(BrickX, BrickY, Brick);

			// restore state
			Brick = savebrick;
			BrickX = savex;
			BrickY = savey;

			// found better score
			if ((score > bestscore) || ((score == bestscore) && (RandU8() < 0x50)))
			{
				bestscore = score;
				bestx = savex;
				besty = savey;
				bestbrick = savebrick;
			}

			// increment X position
			if (!CheckBrick(BrickX+1, BrickY, Brick)) break;
			BrickX++;
		}
	}

	// display brick on new best position
	BrickX = bestx;
	BrickY = besty;
	Brick = bestbrick;
	DispBrick(BrickX, BrickY, Brick);
}

// demo mode
void PlayDemo()
{
	u8 ch;

	// start demo moe
	Demo = True;
	
	// start new game
	NewGame();

	// game loop
	while (True)
	{
		// find demo move
		FindDemo();

		// display new brick
		DispUpdate();
		WaitMs(200);

		// break
		ch = KeyGet();
		if (ch != NOKEY) break;

		// move brick down
		while (True)
		{
			// delay
			DispUpdate();
			WaitMs(5*TIMEDELAY);

			// clear current brick
			ClearBrick(BrickX, BrickY, Brick);

			// check new position
			if (!CheckBrick(BrickX, BrickY+1, Brick)) break;

			BrickY++;
			DispBrick(BrickX, BrickY, Brick);
		}

		// display brick
		DispBrick(BrickX, BrickY, Brick);

		// update score
		Score += BrickScore;
		DispScore();

		// sound
		PlayMelody(BrickSound);

		// delete rows
		DelAllRows();

		// short delay
		DispUpdate();
		WaitMs(200);

		// generate new brick
		GenBrick();

		// check end of the game
		if (!CheckEnd()) break;

		// display new brick
		DispBrick(BrickX, BrickY, Brick);

		// display new brick
		DispUpdate();
		WaitMs(200);
	}

	// stop demo mode
	Demo = False;
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
					DrawTextCond6Bg(DecNumBuf, WIDTH-5*6, HEIGHT-6);
					DispUpdate();
				}
			}
		}

		// randomize
		RandSeed += Time();

		// best level
		LevelBest = 1;
		ScoreBest = 0;
		LinesBest = 0;
		Demo = False;

		while (True)
		{
			// game
			if (Game()) break;

			// demo mode
			PlayDemo();
		}
	}
}
