
// ****************************************************************************
//
//                                Game engine
//
// ****************************************************************************

#include "../include.h"

// buffers
u8 Board[MAPW*MAPH]; // game board

// current game state
u16 MarkNum;		// number of remaining marks
u8 LevelW, LevelH;	// level width and height
u8 PosX, PosY;		// player coordinates

// display one tile of the board
void DispTile(u8 x, u8 y)
{
	u8 tile = Board[x + y*MAPW];
	DrawImgBg(ImgTiles + tile*TILESIZE, x*TILESIZE+MAPX, y*TILESIZE+MAPY, 6, 6, 1);
}	

// display all tiles
void DispBoard()
{
	int x, y;
	for (y = 0; y < MAPH; y++)
	{
		for (x = 0; x < MAPW; x++) DispTile(x, y);
	}
	DispUpdate();
}

// put tile on the board
void PutTile(u8 x, u8 y, u8 tile)
{
	Board[x + y*MAPW] = tile;
	DispTile(x, y);
}

// get tile
u8 GetTile(u8 x, u8 y)
{
	if (((u32)x >= (u32)MAPW) || ((u32)y >= (u32)MAPH)) return EMPTY;
	return Board[x + y*MAPW];
}

// player ON
void PlayerOn()
{
	u8 b = GetTile(PosX, PosY);
	PutTile(PosX, PosY, (b == FLOOR) ? FACE : FACE_MARK);
}

// player OFF
void PlayerOff()
{
	u8 b = GetTile(PosX, PosY);
	PutTile(PosX, PosY, (b == FACE) ? FLOOR : MARK);
}

// move player in direction
void MovePlayer(u8 dir)
{
	int dx = (dir == DIR_L) ? -1 : ((dir == DIR_R) ? 1 : 0);
	int dy = (dir == DIR_U) ? -1 : ((dir == DIR_D) ? 1 : 0);
	PlayerOff();
	PosX += dx;
	PosY += dy;
	PlayerOn();
//	DispUpdate();
//	WaitMs(MOVESPEED);
}

// clear board
void ClearBoard()
{
	memset(Board, EMPTY, MAPW*MAPH);
}

// detect board dimension
void BoardDim()
{
	LevDef = Levels[Level*2]; // current level definition
	LevSolve = Levels[Level*2+1]; // current level solve

	// get board definition
	const char* s = LevDef;

	// detect board dimension
	LevelW = 1;
	LevelH = 0;
	int i = 0;
	char ch;
	const char* s2 = s;
	while ((ch = *s2++) != 0)
	{
		// next row
		if ((ch == '!') || (ch == '|'))
		{
			LevelH++;
			if (i > LevelW) LevelW = i;
			i = 0;
		}
		else
			i++;
	}
	if (i > LevelW) LevelW = i;
	if (i > 0) LevelH++;
	if (LevelW > MAPW) LevelW = MAPW;
	if (LevelH > MAPH) LevelH = MAPH;
};

// initialize current level
//   x = grass (empty)
//   # = wall
//   ! or | = next row
//   space or _ or - = floor
//   $ or b = box
//   * or B = box on mark
//   . = mark
//   @ or p = player
//   + or P = player on mark
void LevelInit()
{
	// detect board dimension
	BoardDim();

	// board position
	int levx = (MAPW - LevelW)/2;
	int levy = (MAPH - LevelH)/2;

	// clear board
	ClearBoard();

	// decode level
	char ch;
	int x, y;
	MarkNum = 0;
	PosX = MAPW/2;
	PosY = MAPH/2;
	const char* s = LevDef;
	x = levx;
	y = levy;
	u8* d = &Board[x + y*MAPW];
	while ((ch = *s++) != 0)
	{
		// next row
		if ((ch == '!') || (ch == '|'))
		{
			y++;
			if (y >= MAPH) break;
			x = levx;
			d = &Board[x + y*MAPW];
		}
		else
		{
			if (x >= MAPW) continue;
	
			switch (ch)
			{
			// grass (empty)
			case 'x':
				ch = EMPTY;
				break;

			// wall
			case '#':
				ch = WALL;
				break;

			// player
			case 'p':
			case '@':
				PosX = x;
				PosY = y;
				ch = FLOOR;
				break;

			// player on mark
			case 'P':
			case '+':
				PosX = x;
				PosY = y;
				ch = MARK;
				MarkNum++;
				break;

			// box
			case 'b':
			case '$':
				ch = CRATE;
				break;

			// box on mark
			case 'B':
			case '*':
				ch = FULL;
				break;

			// mark
			case '.':
				ch = MARK;
				MarkNum++;
				break;

			// floor
			// case ' ':
			// case '_':
			// case '-':
			default:
				ch = FLOOR;
				break;
			}

			// increase position
			*d++ = ch;
			x++;
		}
	}

	// set player
	PlayerOn();

	// display board
	DispBoard();

	// flush keys
	KeyFlush();
}

// check floor (with or without mark, but no box)
Bool IsFloor(u8 x, u8 y)
{
	u8 tile = GetTile(x, y);
	return (tile == FLOOR) || (tile == MARK);
}

// check box (with or without mark)
Bool IsBox(u8 x, u8 y)
{
	u8 tile = GetTile(x, y);
	return (tile == CRATE) || (tile == FULL);
}

// check mark (with or without box)
Bool IsMark(u8 x, u8 y)
{
	u8 tile = GetTile(x, y);
	return (tile == MARK) || (tile == FULL);
}

// hide box
void HideBox(u8 x, u8 y)
{
	u8 tile = GetTile(x, y);
	if (tile == FULL)
	{
		MarkNum++;
		PutTile(x, y, MARK);
	}
	else
	{
		PutTile(x, y, FLOOR);
	}
}

// show box
void ShowBox(u8 x, u8 y)
{
	u8 tile = GetTile(x, y);
	if (tile == MARK)
	{
		MarkNum--;
		PutTile(x, y, FULL);
	}
	else
	{
		PutTile(x, y, CRATE);
	}
}

// step one level (key = move key, returns False on unsupported key)
Bool Step(char key)
{
	int dx = (key == KEY_LEFT) ? -1 : ((key == KEY_RIGHT) ? 1 : 0);
	int dy = (key == KEY_UP) ? -1 : ((key == KEY_DOWN) ? 1 : 0);
	if (dx + dy == 0) return False;

	if (IsBox(PosX+dx, PosY+dy) && (IsFloor(PosX+2*dx, PosY+2*dy)))
	{
		HideBox(PosX+dx, PosY+dy);
		ShowBox(PosX+2*dx, PosY+2*dy);
	}
	int dir = (key == KEY_LEFT) ? DIR_L :
		((key == KEY_RIGHT) ? DIR_R :
		((key == KEY_UP) ? DIR_U : DIR_D));
	if (IsFloor(PosX+dx, PosY+dy))
	{
		MovePlayer(dir);
		DispUpdate();
		WaitMs(MOVESPEED);
	}

	return True;
}

/*
// step solve animation (return True = break)
Bool StepAnim(char key)
{
	if ((key >= 'a') && (key <= 'z')) key -= 32;
	if (key == 'L')
		Step(KEY_LEFT);
	else if (key == 'R')
		Step(KEY_RIGHT);
	else if (key == 'U')
		Step(KEY_UP);
	else if (key == 'D')
		Step(KEY_DOWN);

	return (KeyGet() != NOKEY);
}

// play subanimation (in brackets; returns True = break)
Bool SubAnim(const char* s)
{
	int i;
	char ch;
	while ((ch = *s++) != 0)
	{
		// end of brackets
		if (ch == ')') break;

		// loop (except last passage of the loop)
		if ((ch >= '0') && (ch <= '9'))
		{
			i = ch - '0';
			for (; i > 1; i--) if (StepAnim(*s)) return True;
			continue;
		}

		if (StepAnim(ch)) return True;
	}
	return False;
}
*/

/*
// play level solve (returns True on break from keyboard)
Bool PlaySolve()
{
	int i;

	// re-initialize current level
	LevelInit();

	// prepare pointer to level solution
	const char* s = LevSolve;

	// macro loop
	char ch;
	while ((ch = *s++) != 0)
	{
		if ((ch == '(') || (ch == ')')) continue;

		// loop (except last passage of the loop)
		if ((ch >= '0') && (ch <= '9'))
		{
			i = ch - '0';
			ch = *s;
			if ((ch >= '0') && (ch <= '9'))
			{
				i = i*10 + (ch - '0');
				s++;
			}

			for (; i > 1; i--)
			{
				if (*s == '(')
				{
					if (SubAnim(s+1)) return True;
				}
				else
					if (StepAnim(*s)) return True;
			}
			continue;
		}

		// step
		if (StepAnim(ch)) return True;
	}

	return False;
}
*/

// display solved animation (returns True if solved)
Bool SolvedAnim()
{
	// check if solved
	if (MarkNum > 0) return False;

	// animation
	int i, j;
	u8 x, y;
	u8 k;
	for (i = 5; i > 0; i--)
	{
		// hide boxes
		for (y = 0; y < MAPH; y++)
		{
			for (x = 0; x < MAPW; x++)
			{
				if (GetTile(x, y) == FULL) PutTile(x, y, MARK);
			}
		}

		// delay
		DispUpdate();
		WaitMs(100);

		// show boxes
		for (y = 0; y < MAPH; y++)
		{
			for (x = 0; x < MAPW; x++)
			{
				if (GetTile(x, y) == MARK) PutTile(x, y, FULL);
			}
		}

		// delay
		DispUpdate();
		WaitMs(100);
	}

	return True;
}

// game loop
void GameLoop()
{
	int i;

	// initialize current level
	LevelInit();

	while (True)
	{
		// get key
		i = KeyGet();

		if (i != NOKEY)
		{
			// Esc return to selection
			if (i == KEY_B)
			{
				return;
			}

/*
			// help solution
			if (i == KEY_A)
			{
				PlaySolve();
				SolvedAnim();
				LevelInit();
			}
*/

/*
			// restart scene
			else if (i == KEY_B)
			{
				LevelInit();
			}
*/
			// step
			else
			{
				// one step
				KeyFlush();
				Step(i);
			}

			// solved
			if (SolvedAnim())
			{
				DispUpdate();
				WaitMs(200);
				ClearBoard();
				DispUpdate();
				WaitMs(100);

				KeyFlush();
				WaitChar();

				// increase scene level
				Level++;
				if (Level >= LevNum) Level = 0;

				// level info
				LevelInit();
			}
		}
	}
}
