
// ****************************************************************************
//
//                               Repaint
//
// ****************************************************************************

#include "../include.h"

// repaint one game state
void RepaintState1(int inx, int x, int y)
{
	DrawImgRleBg(ImgState, x, y); // draw state indicator - size 32x20 pixels
	u8 w = 30 - 3*PetGetState(inx); // state 0..10 -> with to clear 30..0
	DrawRect(x + 33 - w, y, w, 20, COL_BLACK); // clear state indicator
	DrawImgRleBg(ImgStateList[inx], x, y); // draw state icon - size 14x14 pixels
}

// repaint game state (does not update screen)
void RepaintState(void)
{
	RepaintState1(0, 0, 0);
	RepaintState1(1, 0, 22);
	RepaintState1(2, 0, 44);
	RepaintState1(3, WIDTH-32, 0);
	RepaintState1(4, WIDTH-32, 22);
	RepaintState1(5, WIDTH-32, 44);
}

// repaint one menu
//  image: 14x14
//  text: 24x7, 1 space
//  total: 24x22
void RepaintMenu1(int inx, int x, int y)
{
	// menu icon 14x14 pixels
	DrawImgRleBg(ImgStateList[inx], x+5, y);

	// menu text 24x7 pixels
	DrawImgRleBg(ImgMenuList[inx], x, y+15);

	// cursor
	if (inx == MenuInx) DrawFrame(x-2, y-2, 28, 26, COL_WHITE);
}

// repaint menu
void RepaintMenu(void)
{
#define MENU_X	4
#define MENU_DX	32
#define MENU_Y	2
#define MENU_DY	26

	// 1st row
	RepaintMenu1(0, 0*MENU_DX+MENU_X, 0*MENU_DY+MENU_Y);
	RepaintMenu1(1, 1*MENU_DX+MENU_X, 0*MENU_DY+MENU_Y);
	RepaintMenu1(2, 2*MENU_DX+MENU_X, 0*MENU_DY+MENU_Y);
	RepaintMenu1(3, 3*MENU_DX+MENU_X, 0*MENU_DY+MENU_Y);

	// 2nd row
	RepaintMenu1(4, 0*MENU_DX+MENU_X, 1*MENU_DY+MENU_Y);
	RepaintMenu1(5, 1*MENU_DX+MENU_X, 1*MENU_DY+MENU_Y);
	RepaintMenu1(6, 2*MENU_DX+MENU_X, 1*MENU_DY+MENU_Y);
	RepaintMenu1(7, 3*MENU_DX+MENU_X, 1*MENU_DY+MENU_Y);

	// help
	DrawTextBg("A:\x11 B:OK C:back", (WIDTH-16*8)/2, HEIGHT-8);
}

// repaint game screen
void RepaintScreen(void)
{
	int i, x, y, w, h;
	const u8* img;

	// clear screen
	DrawClear();

	switch (State)
	{
	// select new pet
	case STATE_SEL:

		// draw title
		DrawTextBg("Select your pet", (WIDTH-15*8)/2, 0);

		// draw empty egg
		DrawImgRleBg(ImgEgg, (WIDTH-29)/2, 9);

		// draw pet's footprint
		DrawImgRleBg(ImgEggList[NewPetInx], (WIDTH-29)/2+ImgEggXY[NewPetInx*2], 9+ImgEggXY[NewPetInx*2+1]);

		// draw pet's name
		i = StrLen(PetDefName[NewPetInx]);
		PrintInv = 1;
		DrawTextBg(PetDefName[NewPetInx], (WIDTH-i*8)/2, HEIGHT-16);
		PrintInv = 0;

		// draw help
		DrawTextBg("A:next B:OK", (WIDTH-11*8)/2, HEIGHT-8);
		break;

	// set pet's name
	case STATE_NAME:

		// draw title
		DrawTextBg("Name of the pet?", (WIDTH-16*8)/2, 0);

		// draw current name
		//  9 characters of width 8 + 1 character of width 16 = 88 pixels total width
		x = (WIDTH-88)/2;
		for (i = 0; i < NewPetNameInx; i++)
		{
			// draw left part of the name
			DrawCharBg(NewPetName[i], x, 26);
			x += 8;
		}

		// draw letter with the cursor
		PrintInv = 1;
		DrawChar2Bg(NewPetName[i], x, 18);
		x += 16;
		PrintInv = 0;

		// draw right part of the name
		for (i++ ; i < NAMEMAX-1; i++)
		{
			DrawCharBg(NewPetName[i], x, 26);
			x += 8;
		}

		// draw help
		DrawTextBg("A:\x11 B:OK C:\x12", (WIDTH-12*8)/2, HEIGHT-8);
		break;

	// game is in progress
	case STATE_GAME:

		// draw pet
		i = PetRealType();
		img = ImgPetList[i];
		w = img[0];
		h = img[1];
		x = (WIDTH-w)/2;
		y = (HEIGHT-8-h)/2;

		if (DirRight)
		{
			DrawImgRleBgRev(img, x, y);
			if (Wink) DrawImgRleBgRev(ImgWinkList[i], x+w-ImgWinkList[i][0]-ImgWinkXY[i*2], y+ImgWinkXY[i*2+1]);
			if (Anim) DrawImgRleBgRev(ImgAnimList[i], x+w-ImgAnimList[i][0]-ImgAnimXY[i*2], y+ImgAnimXY[i*2+1]);
		}
		else
		{
			DrawImgRleBg(img, x, y);
			if (Wink) DrawImgRleBg(ImgWinkList[i], x+ImgWinkXY[i*2], y+ImgWinkXY[i*2+1]);
			if (Anim) DrawImgRleBg(ImgAnimList[i], x+ImgAnimXY[i*2], y+ImgAnimXY[i*2+1]);
		}

		// draw dirt
		if (PetClean() <= STATEMAX*2/3)
		{
			DrawImgRleMask(ImgDirt, ImgDirt, WIDTH-32-8-6, HEIGHT-16);
			if (PetClean() <= STATEMAX/3)
			{
				DrawImgRleMask(ImgDirt, ImgDirt, 32+6, HEIGHT-16);
			}
		}

		// draw help
		DrawTextBg("A:menu", (WIDTH-6*8)/2, HEIGHT-8);

		// repaint game state
		RepaintState();	
		break;

	// menu
	case STATE_MENU:
		// repaint menu
		RepaintMenu();
		break;
	}

	// display update
	DispUpdate();
}

