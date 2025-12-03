
// ****************************************************************************
//
//                                 Animation
//
// ****************************************************************************

#include "../include.h"

// return pet to parents
void ExitPet(void)
{
	// close this pet
	IWDG_Reload();
	PetSetType(PetType() | TYPE_GONE);
	State = STATE_SEL;
	RamCrc();
	SaveRamFlash();

	// bye-bye
	IWDG_Reload();
	DrawClear();
	DrawTextBg("Returning", (WIDTH-9*8)/2, 16);
	DrawTextBg("to", (WIDTH-2*8)/2, 24);
	DrawTextBg("parents...", (WIDTH-10*8)/2, 32);
	DrawText2Bg("BYE-BYE!", (WIDTH-8*16)/2+2, 44);
	DispUpdate();

	// animation
	int i;
	for (i = 64; i > -20; i -= 4)
	{
		DrawRect(0, 0, WIDTH, 16, COL_BLACK);
		DrawImgRleBg(ImgStateGiveup, i, 0);
		DispUpdate();
		PlayTone(((i >> 2) & 1) ? NOTE_E6 : NOTE_G6, NOTE_LEN64);
	}
	WaitMsIWDT(1000);

	// flush key
	KeyFlush(); // flush key
	MenuInx = 0;
}

// game animation
void GameAnim(void)
{
	int i;

	// check if game state
	if (State != STATE_GAME) return;

	// need repaint?
	Bool repaint = False;

	// change direction
	if ((s32)(Time() - DirNextTime) >= 0)
	{
		// change direction
		DirRight = !DirRight;

		// repaint screen
		repaint = True;

		// time to next change direction: 2..5 seconds
		DirNextTime = Time() + RandU8MinMax(2, 8)*1000000*HCLK_PER_US;
	}

	// change wink
	if ((s32)(Time() - WinkNextTime) >= 0)
	{
		// change wink
		Wink = !Wink;

		// repaint screen
		repaint = True;

		// time to next wink change: 1..2 seconds, or 0.1 second
		if (Wink)
			WinkNextTime = Time() + 100000*HCLK_PER_US;
		else
			WinkNextTime = Time() + RandU8MinMax(1, 2)*1000000*HCLK_PER_US;
	}

	// change anim
	if ((s32)(Time() - AnimNextTime) >= 0)
	{
		// change anim
		Anim = !Anim;

		// repaint screen
		repaint = True;

		// time to next anim change: 1..5 seconds, or 0.1..0.5 second
		if (Anim)
			AnimNextTime = Time() + RandU8MinMax(1, 5)*100000*HCLK_PER_US;
		else
			AnimNextTime = Time() + RandU8MinMax(1, 5)*1000000*HCLK_PER_US;
	}

	// adult evolution
	if (((PetType() & TYPE_ADULT) == 0) && (PetAge() >= AGEADULT))
	{
		// update type
		IWDG_Reload();
		PetSetType(PetType() | TYPE_ADULT);
		RamCrc();
		SaveRamFlash();

		// animation
		for (i = 15; i > 0; i--)
		{
			IWDG_Reload();
			DrawClear();
			DrawText2Bg("GROWTH!", (WIDTH-7*16)/2, 0);
			DrawImgRleBg(((i & 1) == 0) ? ImgBaby : ImgPetList[PetRealType()], 40, 16);
			DispUpdate();
			PlayTone(NOTE_G6, NOTE_LEN16);
		}
		WaitMsIWDT(600);
		repaint = True;

		// flush keys
		KeyFlush();
	}

	// gone
	if (PetAge() >= PetAgeMax())
	{
		// close this pet
		ExitPet();

		// repaint new screen
		repaint = True;
	}

	// repaint screen
	if (repaint) RepaintScreen();
}
