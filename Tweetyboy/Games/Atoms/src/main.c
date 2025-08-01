
// ****************************************************************************
//
//                              Atoms game
//
// ****************************************************************************

#include "../include.h"

#define TILEW	8		// tile width in pixels
#define TILEH	8		// tile height in pixels
#define MAPW	10		// map width in number of tiles
#define MAPH	10		// map height in number of tiles
#define MAPSIZE	(MAPW*MAPH)	// map size (= 100 tiles)
#define BOARDW	(MAPW*TILEW+1)	// board width in pixels (= 81)
#define BOARDH	(MAPH*TILEH)	// board height in pixels (= 80)
#define BOARDX	0		// board X coordinate
#define BOARDY	0		// board Y coodinate
#define INFOW	(WIDTH-BOARDW-BOARDX) // width of info box in pixels (= 79)
#define INFOX	(BOARDW+BOARDX)	// X coordinate of info box in pixels (= 81)

#define PLAYER_HUMAN	0	// player is human
#define PLAYER_COMP	1	// player is computer

#define PLAYER_NUM	2	// number of players

// crash sound
const sMelodyNote CrashSound[] = {
	{ 1, NOTE_G4 },
	{ 1, NOTE_E4 },
	{ 1, NOTE_C4 },
	{ 0, 0 },
};

// win sound
const sMelodyNote WinSound[] = {
	{ NOTE_LEN8, NOTE_C5 },
	{ NOTE_LEN8, NOTE_E5 },
	{ NOTE_LEN8, NOTE_G5 },
	{ NOTE_LEN4, NOTE_C6 },
	{ 0, 0 },
};

typedef struct {
	u8	type;		// player type PLAYER_*
	u8	start;		// index of start position
	u8	scorey;		// score Y coordinate
	u8	cursor;		// current cursor
	int	atoms;		// number of atoms (0 = player loses and was eliminated from the game)
	u8	color;		// player's color
} sPlayer;

// players
sPlayer	Players[PLAYER_NUM] = {	// players
	{ PLAYER_HUMAN,	3*MAPW+3, 0, 0,	0, COL_RED },
	{ PLAYER_COMP,	3*MAPW+6, 0, 0,	0, COL_YELLOW },
};

int Player;	// current active players
int PlayerNum;	// number of active players
u32 CurTime;	// cursor blinking time
int PlayerHuman; // number of human players

// board
u8	Atoms[MAPSIZE];	// number of atoms
u8	Owner[MAPSIZE]; // owner of field

// player type
const char* const PlayerTypeTxt[2] = {
	"   HUMAN",
	"COMPUTER",
};

// display open screen
void DispOpen()
{
	DrawClear();

	DrawText("Exploding Atoms", (WIDTH - 15*8)/2, 0, COL_WHITE);

	DrawText("LEFT ... Player 1 is", 0, 3*8, COL_RED);
	DrawText(PlayerTypeTxt[Players[0].type], 12*8, 4*8+1, Players[0].color);

	DrawText("RIGHT .. Player 2 is", 0, 6*8, COL_YELLOW);
	DrawText(PlayerTypeTxt[Players[1].type], 12*8, 7*8+1, Players[1].color);

	DrawText("A ...... Start Game", 0, 9*8, COL_GREEN);

	DispUpdate();
}

// open screen (returns False to quit game)
Bool Open()
{
	char ch;

	Player = 0;
	KeyFlush();

	// display open screen
	DispOpen();

	while (True)
	{
		ch = KeyGet();
		switch (ch)
		{
		case KEY_LEFT:
			Players[0].type++;
			if (Players[0].type > 1) Players[0].type = 0;
			DispOpen();
			break;

		case KEY_RIGHT:
			Players[1].type++;
			if (Players[1].type > 1) Players[1].type = 0;
			DispOpen();
			break;

		case KEY_Y:
			ResetToBootLoader();

		case KEY_A:
			return True;
		}
	}
}

// display score of one player
void DispScore(u8 player)
{
	int len;
	int y = Players[player].scorey + 8 + 14;
	u8 col = Players[player].color;

	// clear info box
	DrawRect(INFOX + 2, y, INFOW-4, 8, COL_BLACK);

	// zero - player lost
	if (Players[player].atoms == 0)
	{
		DrawText("-lost-", INFOX + 2*8, y, col);
	}

	// player is winner
	else if (PlayerNum == 1)
	{
		DrawText("WINNER", INFOX + 2*8, y, col);
	}
	else
	{
		// decode number of atoms
		len = DecUNum(DecNumBuf, Players[player].atoms, 0);

		// display score
		DrawText(DecNumBuf, INFOX + 4*8, y, col);
	}
}

char PlayerText[] = "Player 1";

// display score table with selection (blinking on end of game)
void DispScoreSel()
{
	int i, j;
	for (i = 0; i < PLAYER_NUM; i++)
	{
		int y = Players[i].scorey;
		int x = INFOX;

		// display player's name
		PlayerText[7] = i + '1';
		DrawText(PlayerText, x+10, y+8, Players[i].color);
		if (Players[i].type == PLAYER_COMP) DrawImg(ImgTiles, x+2, y+8, 0, TILE_COMP*8, 8, 8, 8);

		// display score
		DispScore(i);

		// display selection
		if (i == Player)
		{
			DrawFrame(INFOX+1, y+1, INFOW-2, 38, COL_GREEN);
		}
		else
		{
			DrawFrame(INFOX+1, y+1, INFOW-2, 38, COL_BLACK);
		}
	}

	// display update
	DispUpdate();
}

// display one tile
void DispTile(u8 inx, Bool cursor)
{
	// prepare number of atoms
	u8 n = Atoms[inx];
	if (n > 4) n = 4;

	// owner
	u8 owner = Owner[inx];

	// coordinates
	int y = inx / MAPW;
	int x = inx - y*MAPW;
	y *= TILEH;
	x *= TILEW;

	// tile index
	int tile = n*4 - 2 + owner*2;
	if (n == 0) tile = 0;
	if (cursor) tile++;

	// draw tile
	DrawImg(ImgTiles, BOARDX+x, BOARDY+y, 0, tile*8, TILEW, TILEH, 8);
}

// display board
void DispBoard()
{
	int i;
	for (i = 0; i < MAPSIZE; i++) DispTile(i, False);
}

// display board grid
void DispGrid()
{
//	DrawHLine(BOARDX, BOARDY+BOARDH-1, BOARDW, COL_WHITE);
	DrawVLine(BOARDX+BOARDW-1, BOARDY, BOARDH, 15); //COL_WHITE);
}

// display cursor of active player (blinking)
void DispCur()
{
	DispTile(Players[Player].cursor, (((Time() - CurTime) >> 22) & 3) == 0);
}

// hide cursor of active player
void DispCurOff()
{
	DispTile(Players[Player].cursor, False);
}

// new game
void NewGame()
{
	int i;

	KeyFlush();
	DrawClear();

	// clear board
	for (i = 0; i < MAPSIZE; i++)
	{
		Atoms[i] = 0;
		Owner[i] = 0;
	}

	// setup start condition
	PlayerNum = 0;
	PlayerHuman = 0;
	Player = 0;
	for (i = 0; i < PLAYER_NUM; i++)
	{
		Players[i].atoms = 1; // number of atoms
		Players[i].scorey = PlayerNum*40; // score Y coordinate
		PlayerNum++;
		Atoms[Players[i].start] = 1; // 1 default atom
		Owner[Players[i].start] = i; // atom owner
		Players[i].cursor = Players[i].start; // cursor
		if (Players[i].type == PLAYER_HUMAN) PlayerHuman++; // count of human players
	}

	// display board grid
	DispGrid();

	// display board
	DispBoard();

	// display score table with selection
	DispScoreSel();

	DispUpdate();
}

// catch neighbour (add 1 own electron)
void Catch(u8 inx)
{
	u8 n = Atoms[inx];
	u8 own = Owner[inx];

	// not empty atom of enemy player
	if ((n > 0) && (own != Player))
	{
		// subtract atoms from enemy
		Players[own].atoms -= n;
		DispScore(own);

		// add atoms to player
		Players[Player].atoms += n;
		DispScore(Player);

		// enemy lost
		if (Players[own].atoms == 0) PlayerNum--;
	}

	// increase atoms
	Atoms[inx] = n+1;
	Owner[inx] = Player;

	// display atom
	DispTile(inx, False);

	// display update
	DispUpdate();
}

// explosions
void Explo()
{
	int x, y, i, n;
	u8 mx;
	do {
		// count exploding atoms (note: player does not need to be tested,
		//	no other player can have an exploding atom at this time)
		n = 0;
		for (y = 0; y < MAPH; y++)
		{
			for (x = 0; x < MAPW; x++)
			{
				// field index
				i = y*MAPW+x;

				// prepare maximum of atom
				mx = 4;
				if ((x == 0) || (x == MAPW-1)) mx--;
				if ((y == 0) || (y == MAPH-1)) mx--;

				// check exploding atom
				if (Atoms[i] >= mx) n++;
			}
		}

		// stop, no explosion
		if (n == 0) break;

		// select random atom to explode
		n = RandS16Max(n - 1);

		// find exploding atom
		for (y = 0; y < MAPH; y++)
		{
			for (x = 0; x < MAPW; x++)
			{
				// field index
				i = y*MAPW+x;

				// prepare maximum of atom
				mx = 4;
				if ((x == 0) || (x == MAPW-1)) mx--;
				if ((y == 0) || (y == MAPH-1)) mx--;

				// found exploding atom
				if (Atoms[i] >= mx)
				{
					n--;
					if (n < 0)
					{
						// decrease this field
						Atoms[i] -= mx;
						DispTile(i, False);

						// catch neighbours
						if (x > 0) Catch(i-1);
						if (x < MAPW-1) Catch(i+1);
						if (y > 0) Catch(i-MAPW);
						if (y < MAPH-1) Catch(i+MAPW);

						// update display
						DispUpdate();
						PlayMelody(CrashSound);
//						WaitMs(80);
						break;
					}
				}
			}
			if (n < 0) break;
		}

	// if 1 player left and board is too full, the explosions might never end
	} while (PlayerNum > 1);
}

// auto-play (search cursor)
void Auto()
{
	u8 bestsize = 0;
	int bestnum = 0;
	int i;
	DispCurOff();

	// find best atom size and count
	for (i = 0; i < MAPSIZE; i++)
	{
		if (Owner[i] == Player)
		{
			if (Atoms[i] > bestsize)
			{
				bestsize= Atoms[i];
				bestnum = 1;
			}
			else if (Atoms[i] == bestsize) bestnum++;			
		}
	}

	// select field
	bestnum = RandU8Max(bestnum-1);
	for (i = 0; ; i++)
	{
		if ((Owner[i] == Player) && (Atoms[i] == bestsize))
		{
			bestnum--;
			if (bestnum < 0) break;
		}
	}

	// set cursor to this field
	Players[Player].cursor = i;

	// display cursor for a while
	DispTile(i, True);

	// display update
	WaitMs(200);
}

// game
void Game()
{
	int cur;
	u8 ch;

	// cursor time
	CurTime = Time();

	while (True)
	{
		// break demo
		if (PlayerHuman == 0)
		{
			if ((ch = KeyGet()) != NOKEY)
			{
#if USE_SCREENSHOT	// 1=use screen shot
				if (ch == KEY_Y) ScreenShot();
#endif
				return;
			}
		}

		// auto player
		if (Players[Player].type == PLAYER_COMP)
		{
			Auto();
			ch = KEY_A;
		}
		else
			ch = KeyGet();

		// keyboard control
		cur = Players[Player].cursor;

		switch (ch)
		{
		// cursor left
		case KEY_LEFT:
			DispCurOff();
			cur--;
			if ((cur < 0) || ((cur % MAPW) == MAPW-1)) cur += MAPW;
			CurTime = Time();
			break;

		// cursor right
		case KEY_RIGHT:
			DispCurOff();
			cur++;
			if ((cur % MAPW) == 0) cur -= MAPW;
			CurTime = Time();
			break;

		// cursor up
		case KEY_UP:
			DispCurOff();
			cur -= MAPW;
			if (cur < 0) cur += MAPSIZE;
			CurTime = Time();
			break;

		// cursor down
		case KEY_DOWN:
			DispCurOff();
			cur += MAPW;
			if (cur >= MAPSIZE) cur -= MAPSIZE;
			CurTime = Time();
			break;

		case KEY_A: // put atom
			// check color
			if ((Atoms[cur] == 0) || (Owner[cur] == Player))
			{
				Owner[cur] = Player;
				Atoms[cur]++;
				Players[Player].atoms++;
				DispTile(cur, False);
				DispScore(Player);

				// explosions
				Explo();

				// end of game
				if (PlayerNum < 2)
				{
					// win sound
					PlayMelody(WinSound);

					// hide cursor of active player
					DispCurOff();

					// report end of game
					KeyFlush();
					int play = Player;
					while (KeyGet() == NOKEY)
					{
						Player = ((((Time() - CurTime) >> 23) & 3) < 2) ? play : -1;

						// display score selection (blinking on end of game)
						DispScoreSel();
					}
					return;
				}

				// change player
				do {
					Player++;
					if (Player >= PLAYER_NUM) Player = 0;
				} while (Players[Player].atoms == 0);

				cur = Players[Player].cursor;

				DispScoreSel();
				CurTime = Time();
			}
			break;

		case KEY_Y:
#if USE_SCREENSHOT	// 1=use screen shot
			ScreenShot();
#endif
			return;

		}
		Players[Player].cursor = cur;

		// blinking cursor
		DispCur();

		// display update
		DispUpdate();
	}
}

int main(void)
{
	char ch;

	// display splash screen
	DrawImg(ImgIntro, 0, 0, 0, 0, WIDTH, HEIGHT, WIDTHBYTE);
	DispUpdate();
	while ((ch = KeyGet()) == NOKEY) {}
#if USE_SCREENSHOT	// 1=use screen shot
	if (ch == KEY_Y) ScreenShot();
#endif
	if (ch == KEY_Y) ResetToBootLoader();
	DrawClear();

	while (True)
	{
		// open screen
		Open();

		// start new game
		NewGame();

		// randomize
		RandSeed += Time();

		// game (check number of selected players)
		if (PlayerNum > 1) Game();
	}
}
