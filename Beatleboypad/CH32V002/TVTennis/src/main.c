
// ****************************************************************************
//
//                              TV Tennis game
//
// ****************************************************************************

#include "../include.h"

#define COORD_SHIFT	5	// coordinates shift
#define COORD_MUL	(1<<COORD_SHIFT) // coordinate multiply

#define WIDTHM	(WIDTH*COORD_MUL)
#define HEIGHTM	(HEIGHT*COORD_MUL)

#define DIGW	(8*COORD_MUL)	// digit width in pixels
#define DIGH	(10*COORD_MUL)	// digit height in pixels
#define DIGXL	((6*8-5)*COORD_MUL) // left score X
#define DIGXR	((8*8+4)*COORD_MUL) // right score X
#define MAXSCORE 99		// max. score
#define NETW	(3*COORD_MUL)	// width of middle net
#define DIGNUM	2		// number of digits of one score
#define PADDLEW	(3*COORD_MUL)	// paddle width
#define PADDLEH	(16*COORD_MUL)	// paddle height
#define BALLSIZE (3*COORD_MUL)	// ball size
#define PADDLELX (1*COORD_MUL)	// left paddle X coordinate
#define PADDLERX ((WIDTH-1)*COORD_MUL-PADDLEW) // right paddle X coordinate

#define BALL_IN		0	// ball is in game
#define BALL_L		1	// ball is served by left player
#define BALL_R		2	// ball is served by right player

#define PADDLESPEED 	(2*COORD_MUL-COORD_MUL/2) // paddle speed (number of pixels per frame 17ms)
#define BALLSPEED	(2*COORD_MUL)	// ball speed (number of pixels per frame 17ms)

// time delta in number of ticks
u32 OldTime;
int TimeDelta;

// computer
Bool Comp[2];	// computer flags
int CompX[2];	// X coordinate for delayed computer response
int CompY[2];	// Y coordinate of computer inaccuracy
u32 LastOut;	// last out time (to start new serve)

// current score
u8 Score[2];
Bool Tied;	// tied paddles

// paddle Y coordinate (middle)
int PaddleY[2];

// ball state BALL_*
u8 BallState;
int BallX, BallY, BallDX, BallDY;

// bound sound
const sMelodyNote BoundSound[] = {
	{ 1, NOTE_C7 },
	{ 0, 0 },
};

// paddle sound
const sMelodyNote PaddleSound[] = {
	{ 1, NOTE_C6 },
	{ 0, 0 },
};

// serve sound
const sMelodyNote ServeSound[] = {
	{ 1, NOTE_C5 },
	{ 0, 0 },
};

// out sound
const sMelodyNote OutSound[] = {
	{ 1, NOTE_C5 },
	{ 1, NOTE_CS5 },
	{ 1, NOTE_D5 },
	{ 1, NOTE_DS5 },
	{ 1, NOTE_E5 },
	{ 1, NOTE_F5 },
	{ 1, NOTE_FS5 },
	{ 1, NOTE_G5 },
	{ 1, NOTE_GS5 },
	{ 1, NOTE_A5 },
	{ 1, NOTE_AS5 },
	{ 1, NOTE_B5 },
	{ 1, NOTE_C6 },
	{ 0, 0 },
};

// prepare auto play
void NewAuto()
{
	CompX[0] = WIDTHM/2 + RandU16Max(WIDTHM/4);
	CompY[0] = RandS16MinMax(-(PADDLEH+BALLSIZE/2)/2, (PADDLEH+BALLSIZE/2)/2);

	CompX[1] = RandU16Max(WIDTHM/4);
	CompY[1] = RandS16MinMax(-(PADDLEH+BALLSIZE/2)/2, (PADDLEH+BALLSIZE/2)/2);
}

// new game
void NewGame()
{
	int i;
	for (i = 0; i < 2; i++)
	{
		Score[i] = 0;
		PaddleY[i] = HEIGHTM/2;
	}
	BallState = BALL_L;
	LastOut = Time();
	BallY = HEIGHTM/2;
	NewAuto();
}

// invert middle net
void DispNet()
{
	DrawRectInv(((WIDTHM-NETW)/2)>>COORD_SHIFT, 0, NETW>>COORD_SHIFT, HEIGHT);
}

// invert one score
void DispScore(int inx)
{
	int j, row, col, x, y;
	u8 dig[2], k;
	u16 c;
	const u8* s;

	// decode number (2 digits)
	dig[0] = Score[inx]/10;
	dig[1] = Score[inx] - dig[0]*10;

	// start X coordinate
	x = (inx == 0) ? (DIGXL>>COORD_SHIFT) : (DIGXR>>COORD_SHIFT);

	// decode digits
	DrawImgInv(ImgDigits + dig[0], x, 0, 8, 10, 10);
	DrawImgInv(ImgDigits + dig[1], x+8, 0, 8, 10, 10);
}

// invert both scores
void DispScores()
{
	DispScore(0);
	DispScore(1);
}

// invert one paddle
void DispPaddle(int inx)
{
	int x = (inx == 0) ? (PADDLELX>>COORD_SHIFT) : (PADDLERX>>COORD_SHIFT);
	int y = PaddleY[inx];
	DrawRectInv(x, (y - PADDLEH/2)>>COORD_SHIFT, PADDLEW>>COORD_SHIFT, PADDLEH>>COORD_SHIFT);
}

// invert both paddles
void DispPaddles()
{
	DispPaddle(0);
	DispPaddle(1);
}

// invert ball
void DispBall()
{
	if (BallState == BALL_IN)
	{
		int x = BallX;
		int y = BallY;
		DrawRectInv((x - BALLSIZE/2)>>COORD_SHIFT, (y - BALLSIZE/2)>>COORD_SHIFT,
			BALLSIZE>>COORD_SHIFT, BALLSIZE>>COORD_SHIFT);
	}
}

// display all
void DispAll()
{
	// clear screen
	DrawClear();

	// display middle net
	DispNet();

	// display both scores
	DispScores();

	// display both paddles
	DispPaddles();

	// display ball
	DispBall();

	DispUpdate();
}

// game control
void GameControl()
{
	u8 key0 = NOKEY;	// auto-play of left player
	u8 key1 = NOKEY;	// auto-play of right player
	int autoy;

	// auto play of left player
	if (Comp[0] && (BallX <= CompX[0]))
	{
		autoy = BallY + CompY[0];
		if (PaddleY[0] < autoy-(2<<COORD_SHIFT)) key0 = KEY_DOWN;
		if (PaddleY[0] > autoy+(2<<COORD_SHIFT)) key0 = KEY_UP;
	}

	// auto play of right player
	if (Comp[1] && (BallX >= CompX[1]))
	{
		autoy = BallY + CompY[1];
		if (PaddleY[1] < autoy-(2<<COORD_SHIFT)) key1 = KEY_DOWN;
		if (PaddleY[1] > autoy+(2<<COORD_SHIFT)) key1 = KEY_UP;
	}

	// left player up
	if (	(KeyPressed(KEY_UP) && !Comp[0]) ||	// left player UP
		((Tied || Comp[1]) && KeyPressed(KEY_B) && !Comp[0]) || // use also key B, if not used for right player
		(key0 == KEY_UP)) // auto-play of left player
	{
		int y = PaddleY[0];
		y -= TimeDelta*PADDLESPEED;
		if (y < PADDLEH/2) y = PADDLEH/2;
		if (y != PaddleY[0])
		{
			DispPaddle(0);
			PaddleY[0] = y;
			DispPaddle(0);
		}
	}

	// left player down
	if (	(KeyPressed(KEY_DOWN) && !Comp[0]) ||	// left player down
		((Tied || Comp[1]) && KeyPressed(KEY_A) && !Comp[0]) || // use also key A, if not used for right player
		(key0 == KEY_DOWN)) // auto-play of left player
	{
		int y = PaddleY[0];
		y += TimeDelta*PADDLESPEED;
		if (y > HEIGHTM - PADDLEH/2) y = HEIGHTM - PADDLEH/2;
		if (y != PaddleY[0])
		{
			DispPaddle(0);
			PaddleY[0] = y;
			DispPaddle(0);
		}
	}

	// right player up
	if (	(KeyPressed(KEY_B) && !Comp[1]) ||	// right player up
		((Tied || Comp[0]) && KeyPressed(KEY_UP) && !Comp[1]) || // use also key UP, if not used for left player
		(key1 == KEY_UP)) // auto-play of right player
	{
		int y = PaddleY[1];
		y -= TimeDelta*PADDLESPEED;
		if (y < PADDLEH/2) y = PADDLEH/2;
		if (y != PaddleY[1])
		{
			DispPaddle(1);
			PaddleY[1] = y;
			DispPaddle(1);
		}
	}

	// right player down
	if (	(KeyPressed(KEY_A) && !Comp[1]) ||	// right player down
		((Tied || Comp[0]) && KeyPressed(KEY_DOWN) && !Comp[1]) || // use also DOWN, if not used for left player
		(key1 == KEY_DOWN)) // auto-play of right player
	{
		int y = PaddleY[1];
		y += TimeDelta*PADDLESPEED;
		if (y > HEIGHTM - PADDLEH/2) y = HEIGHTM - PADDLEH/2;
		if (y != PaddleY[1])
		{
			DispPaddle(1);
			PaddleY[1] = y;
			DispPaddle(1);
		}
	}
}

// move ball
void GameBall()
{
	// move ball
	if (BallState == BALL_IN)
	{
		// ball new coordinate
		int ballx = BallX + TimeDelta*BallDX;
		int bally = BallY + TimeDelta*BallDY;

		// bounce off the top edge
		if (bally < BALLSIZE/2)
		{
			bally = BALLSIZE/2;
			BallDY = -BallDY;
			PlayMelody(BoundSound);
		}

		// bounce off the bottom edge
		if (bally > HEIGHTM - BALLSIZE/2)
		{
			bally = HEIGHTM - BALLSIZE/2;
			BallDY = -BallDY;
			PlayMelody(BoundSound);
		}

		// bounce off the left paddle
		//  Note: Using old "BallX" coordinate for case the animation step is too large.
		if (	(ballx - BALLSIZE/2 <= PADDLELX + PADDLEW) && // new X coordinate
			(BallX + BALLSIZE/2 >= PADDLELX) && // old X coordinate
			(bally - BALLSIZE/2 <= PaddleY[0] + PADDLEH/2) &&
			(bally + BALLSIZE/2 >= PaddleY[0] - PADDLEH/2))
		{
			ballx = PADDLELX + PADDLEW + BALLSIZE/2;
			BallDX = BALLSPEED;
			BallDY = RandS16MinMax(-BALLSPEED, +BALLSPEED);
			PlayMelody(PaddleSound);

			// prepare auto play
			NewAuto();
		}

		// bounce off the right paddle
		//  Note: Using old "BallX" coordinate for case the animation step is too large.
		if (	(ballx + BALLSIZE/2 >= PADDLERX) && // new X coordinate
			(BallX - BALLSIZE/2 <= PADDLERX + PADDLEW) && // old X coordinate
			(bally - BALLSIZE/2 <= PaddleY[1] + PADDLEH/2) &&
			(bally + BALLSIZE/2 >= PaddleY[1] - PADDLEH/2))
		{
			ballx = PADDLERX - BALLSIZE/2;
			BallDX = -BALLSPEED;
			BallDY = RandS16MinMax(-BALLSPEED, +BALLSPEED);
			PlayMelody(PaddleSound);

			// prepare auto play
			NewAuto();
		}

		// ball is out left
		if (ballx < -BALLSIZE)
		{
			if (Score[1] < MAXSCORE) Score[1]++;
			BallState = BALL_L;
			PlayMelody(OutSound);
			LastOut = Time();
			bally = HEIGHTM/2;
			NewAuto();
		}

		// ball is out right
		if (ballx > WIDTHM + BALLSIZE)
		{
			if (Score[0] < MAXSCORE) Score[0]++;
			BallState = BALL_R;
			PlayMelody(OutSound);
			LastOut = Time();
			bally = HEIGHTM/2;
			NewAuto();
		}

		// new position
		if ((BallX != ballx) || (BallY != bally))
		{
			DispBall();
			BallX = ballx;
			BallY = bally;
			DispBall();
		}
	}
}

// play on game
void Game(Bool comp1, Bool comp2, Bool tied)
{
	u8 ch;

	// randomize
	RandSeed += Time();

	// store computer flag
	Comp[0] = comp1;
	Comp[1] = comp2;
	Tied = tied;

	// start new game
	NewGame();
	u32 t;

	// wait for key release
	DispAll();
	while (KeyPressed(KEY_LEFT) || KeyPressed(KEY_RIGHT) ||
		KeyPressed(KEY_UP) || KeyPressed(KEY_DOWN) ||
		KeyPressed(KEY_A) || KeyPressed(KEY_B)) {}
	KeyFlush();

	// game loop
	OldTime = Time();
	while (True)
	{
		// get key
		ch = KeyGet();

		// auto serve of computer after 1 second after drop-out
		if ((ch == NOKEY) && ((Time() - LastOut) >= HCLK_PER_MS*1000))
		{
			if (	((BallState == BALL_L) && Comp[0]) ||
				((BallState == BALL_R) && Comp[1]))
				ch = KEY_LEFT;
		}

		// key
		switch (ch)
		{
		// serve ball
		case KEY_LEFT:
		case KEY_RIGHT:
			if (BallState != BALL_IN)
			{
				// left player serves
				if (BallState == BALL_L)
				{
					BallX = PADDLELX + PADDLEW + BALLSIZE/2;
					BallY = PaddleY[0];
					BallDX = BALLSPEED;
					BallDY = RandS16MinMax(-BALLSPEED, +BALLSPEED);
				}
				else
				{
					BallX = PADDLERX - BALLSIZE/2;
					BallY = PaddleY[1];
					BallDX = -BALLSPEED;
					BallDY = RandS16MinMax(-BALLSPEED, +BALLSPEED);
				}
				BallState = BALL_IN;
				PlayMelody(ServeSound);
				DispAll();
			}
			KeyFlush();
			break;

		case NOKEY:
			break;

		case KEY_B:
			if (comp1 && comp2) return;

		default:
			KeyFlush();
			break;
		}

		// time delta
		WaitMs(3);
		if (RunMode == RUNMODE_VGA) WaitMs(16);
		t = Time();
		TimeDelta = 1; //(t - OldTime)/(HCLK_PER_MS*17);
//		if (TimeDelta <= 0) TimeDelta = 1;
		OldTime = t;

		// game control
		GameControl();

		// move ball
		GameBall();

		// game display update
		DispUpdate();
	}
}

// draw open screen
void OpenDraw()
{
	// clear screen
	DrawClear();

	// title
	DrawTextCond("TV Tennis", (WIDTH-9*6)/2, 0*8, COL_WHITE);

	// draw menu
	DrawTextCond("Press key to start:", 0, 2*8, COL_WHITE);
	DrawTextCond("LEFT....Left paddle", 0, 3*8, COL_WHITE);
	DrawTextCond("RIGHT...Right paddle", 0, 4*8, COL_WHITE);
	DrawTextCond("DOWN....2 players", 0, 5*8, COL_WHITE);
	DrawTextCond("UP......Demo", 0, 6*8, COL_WHITE);
	DrawTextCond("A.......Tied paddles", 0, 7*8, COL_WHITE);

	DispUpdate();
}

// Open screen (False=go to intro screen)
Bool Open()
{
	// draw open screen
	OpenDraw();

	// select game
	while (True)
	{
		// get key
		switch (KeyGet())
		{
		case KEY_LEFT:
			// Player + Comp + not-tied
			Game(False, True, False);
			return True;

		case KEY_RIGHT:
			// Comp + Player + not-tied
			Game(True, False, False);
			return True;

		case KEY_DOWN:
			// Player + Player + not-tied
			Game(False, False, False);
			return True;

		case KEY_UP:
			// Comp + Comp + not-tied
			Game(True, True, False);
			return True;

		case KEY_A:
			// Player + Player + tied
			Game(False, False, True);
			return True;

		case KEY_B:
			return False;
		}
	}
}

int main(void)
{
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
					DrawTextCondBg(DecNumBuf, WIDTH-5*6, 0);
					DispUpdate();
				}
			}
		}

		// randomize
		RandSeed += Time();

		while (True)
		{
			// Open screen
			if (!Open()) break;
		}
	}
}
