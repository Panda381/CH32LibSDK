
// ****************************************************************************
//
//                                Game Control
//
// ****************************************************************************

#include "../include.h"

// food melody
const sTone MusicFood[] = {
	{ NOTE_LEN16, NOTE_D6 },
	{ NOTE_LEN16, NOTE_G6 },
	{ NOTE_LEN4, NOTE_R },
	{ NOTE_STOP, NOTE_R }
};

// cure melody
const sTone MusicCure[] = {
	{ NOTE_LEN16, NOTE_C6 },
	{ NOTE_LEN4, NOTE_R },
	{ NOTE_STOP, NOTE_R }
};

// game control
NOMEMSET void GameCtrl(u8 key)
{
	int i, j;

	// on first press key A or B - disable SWIO programming pin
	if ((key == KEY_A) || (key == KEY_B))
	{
		// Remap SWD debug interface (default 0)
		// 	0-3 ... SWD (SDI) enabled
		//	4 ... SWD (SDI) disable, pin served as GPIO
		GPIO_Remap_SWD(4);
	}

	// refresh time of last press
	Last = Time();

	// serve keys
	switch (State)
	{
	// select new pet
	case STATE_SEL:

		// A: shift to another pet
		if (key == KEY_A)
		{
			NewPetInx++;
			if (NewPetInx >= BASENUM) NewPetInx = 0;
			RepaintScreen();
		}

		// B: confirm this pet
		else if (key == KEY_B)
		{
			memset(NewPetName, ' ', NAMEMAX-1); // clear name of the pet
			NewPetName[NAMEMAX-1] = 0;
			memcpy(NewPetName, PetDefName[NewPetInx], StrLen(PetDefName[NewPetInx])); // copy default name
			NewPetNameInx = 0;
			State = STATE_NAME; // go to enter name
			RepaintScreen();
		}
		break;

	// set pet's name
	case STATE_NAME:

		// A: shift to next letter
		if (key == KEY_A)
		{
			NewPetNameInx++;
			if (NewPetNameInx >= NAMEMAX-1) NewPetNameInx = 0;
			RepaintScreen();
		}

		// B: confirm this name
		else if (key == KEY_B)
		{
			// update IWDG
			IWDG_Reload();

			// set pet type
			PetSetType(NewPetInx + 1);	// pet type as baby
			PetSetAge(0);			// reset age
			PetSetAgeMax(AGEDEF);		// set max. age
			RamData->state.state[0] = 0x55; // set state to mid. value (=5)
			RamData->state.state[1] = 0x55;
			RamData->state.state[2] = 0x55;
			RamData->ticks = 0;

			// update RAM CRC
			RamCrc();

			// make room in flash for the new slot
			u8* d = (u8*)&FlashData + SLOTSIZE - 1;
			const u8* s = d - sizeof(sPetData);
			i = (PETNUM-1)*sizeof(sPetData);
			for (; i > 0; i--) *d-- = *s--; // do not use memmove - consumes more flash memory
			FlashData.petnum++; // increase number of pets

			// copy name
			memcpy(PetName, NewPetName, NAMEMAX);

			// save RAM to flash
			FlashData.pet[0].state.data[0] = RamData->state.data[0];
			FlashData.pet[0].state.data[1] = RamData->state.data[1];
			if (	!SaveFlash() || !LoadFlash() ||
				(FlashData.pet[0].state.data[0] != RamData->state.data[0]) ||
				(FlashData.pet[0].state.data[1] != RamData->state.data[1]))
			{
				// save error
				DrawClear();
				DrawTextBg("SaveFlash Error", 0, 0);
				DispUpdate();
				WaitMsIWDT(2000);
				State = STATE_SEL; // start new pet
			}
			else
			{
				// start regular game
				State = STATE_GAME;

				// parents' arrival
				for (i = 0; i < 60; i += 4)
				{
					DrawClear();
					DrawImgRleBg(ImgStateGiveup, i, 0);
					DispUpdate();
					PlayTone(((i >> 2) & 1) ? NOTE_E6 : NOTE_G6, NOTE_LEN64);
				}

				// egg down
				for (i = -25; i < 20; i += 8)
				{
					// C7: 477 ... C6: 955
					DrawClear();
					DrawImgRleBg(ImgEgg, (WIDTH-29)/2, i);
					DispUpdate();
					PlayTone((i+30)*10 + 500, NOTE_LEN64);
				}

				// phase 1 - egg
				DrawClear();
				DrawImgRleBg(ImgEgg, (WIDTH-29)/2, 20);
				DispUpdate();
				WaitMsIWDT(400);

				// phase 2 - crack
				DrawImgRleBg(ImgEggCrack, (WIDTH-29)/2+4, 20+2);
				DispUpdate();
				PlayTone(NOTE_C4, NOTE_LEN16);
				WaitMsIWDT(600);

				// phase 3 - born
				DrawImgRleBg(ImgEggBorn, (WIDTH-29)/2+6, 20-4);
				DrawText2Bg("NEWBORN!", 2, 0);
				DispUpdate();
				PlayTone(NOTE_G4, NOTE_LEN16);
				WaitMsIWDT(1400);
			}
			RepaintScreen();

			// flush keys
			KeyFlush();
		}

		// C: change letter
		else if (key == KEY_C)
		{
			char ch = NewPetName[NewPetNameInx] + 1;
			if (NewPetNameInx == 0)
			{
				if (ch == ' '+1) ch = 'A';
				if (ch == 'Z'+1) ch = ' ';
			}
			else
			{
				if (ch == ' '+1) ch = 'a';
				if (ch == 'z'+1) ch = ' ';
			}
			NewPetName[NewPetNameInx] = ch;
			RepaintScreen();
		}
		break;

	// base game
	case STATE_GAME:

		// A: menu
		if (key == KEY_A)
		{
			State = STATE_MENU;
			RepaintScreen();
		}

		// B: sound
		else if (key == KEY_B)
		{
			// set new sound
			SetSoundOff(!GetSoundOff());
			SaveFlash(); // save flash

			// display state
			DrawClear();
			DrawTextBg("sound", (WIDTH-5*8)/2, 18);
			if (GetSoundOff() == 0)
				DrawText2Bg("ON", (WIDTH-2*16)/2, 32);
			else
				DrawText2Bg("OFF", (WIDTH-3*16)/2, 32);
			DispUpdate();
			WaitMsIWDT(600);
			RepaintScreen();
		}
		break;

	// menu
	case STATE_MENU:

		// A: next
		if (key == KEY_A)
		{
			MenuInx++;
			if (MenuInx >= 8) MenuInx = 0;
			RepaintScreen();
		}

		// B: OK
		else if (key == KEY_B)
		{
			// shift state
			State = STATE_GAME;

			// feed
			switch (MenuInx)
			{
			// food
			case STATE_FEED:

				// animate feeding
				for (i = 0; i < 50; i += 6)
				{
					IWDG_Reload(); // update IWDG
					DrawClear(); // clear screen
					DrawImgRleBgRev(ImgPetList[PetRealType()], 64, 8); // draw pet
					DrawImgRleBg(ImgStateFood, i, 20); // draw apple
					DispUpdate(); // display update
				} // last i=48 - apple is 48-62

				// clear apple
				DrawRect(48, 20, 14, 14, COL_BLACK);
				DispUpdate(); // display update

				// food melody
				PlayMusic(MusicFood);

				// increase food
				PetAddFeed(1);

				// decrease clean
				u8 clean = PetClean();
				if (clean > 0) PetSetClean(clean-1);

				// flush keys
				KeyFlush();
				break;

			// cure
			case STATE_HEALTH:

				// animate cure
				for (i = 0; i < 50; i += 6)
				{
					IWDG_Reload(); // update IWDG
					DrawClear(); // clear screen
					DrawImgRleBgRev(ImgPetList[PetRealType()], 64, 8); // draw pet
					DrawImgRleBg(ImgPill, i, 20); // draw pill
					DispUpdate(); // display update
				} // last i=48 - pill is 48-62

				// clear pill
				DrawRect(48, 20, 14, 14, COL_BLACK);
				DispUpdate(); // display update

				// cure melody
				PlayMusic(MusicCure);

				// increase health
				PetAddHealth(1);

				// flush keys
				KeyFlush();
				break;

			// sleep
			case STATE_REST:

				// go sleep
				GoSleep();
				return;

			// game
			case STATE_HAPPY:

				DrawClear(); // clear screen

				// animate game
				for (i = 3; i > 0; i--)
				{
					DrawImgRleBg(ImgPetList[PetRealType()], 40, 8); // draw pet right
					DispUpdate(); // update screen
					PlayTone(NOTE_D6, NOTE_LEN16);
					WaitMsIWDT(500); // wait
					DrawRect(WIDTH-18, 20, 18, 14, COL_BLACK); // clear hand
					DrawImgRleBg(ImgHand, 0, 20); // draw hand left
					DispUpdate(); // update screen
					WaitMsIWDT(500); // wait

					DrawImgRleBgRev(ImgPetList[PetRealType()], 40, 8); // draw pet left
					DispUpdate(); // update screen
					PlayTone(NOTE_G6, NOTE_LEN16);
					WaitMsIWDT(500); // wait
					DrawRect(0, 20, 18, 14, COL_BLACK); // clear hand
					DrawImgRleBgRev(ImgHand, WIDTH-18, 20); // draw hand right
					DispUpdate(); // update screen
					WaitMsIWDT(500); // wait
				}

				// increase happy
				PetAddHappy(1);

				// flush keys
				KeyFlush();
				break;

			// clean
			case STATE_CLEAN:
				for (i = 10; i > 0; i--)
				{
					DrawClear(); // clear display
					DrawImgRleBg(ImgPetList[PetRealType()], 40, 8); // draw pet right
					for (j = 10; j > 0; j--)
					{
						// draw drop
						DrawImgRleMask(ImgStateClean, ImgStateClean, RandU8Max(WIDTH-5), RandU8Max(HEIGHT-5));
					}
					PlayTone(RandU16MinMax(800,2000), NOTE_LEN16);
					DispUpdate(); // display update
					WaitMsIWDT(200); // wait
				}

				// set clean
				PetAddClean(3);

				// flush keys
				KeyFlush();
				break;

			// learn
			case STATE_DISC:

				// animate learning
				for (i = 0; i < 100; i += 6)
				{
					IWDG_Reload(); // update IWDG
					DrawClear(); // clear screen
					DrawImgRleBgRev(ImgPetList[PetRealType()], 64, 8); // draw pet
					DrawImgRleBg(ImgStateLearn, (i >= 50) ? (100-i) : i, 20); // draw book
					if (i == 9*6) PlayTone(NOTE_D4, NOTE_LEN2);
					DispUpdate(); // display update
				}

				// increase discipline
				PetAddDisc(1);

				// flush keys
				KeyFlush();
				break;

			// info
			case 6:
				i = 0; // current pet
				while (True)
				{
					// clear display
					DrawClear();

					// display pet's number
					j = DecUNum(DecNumBuf, i+1, 0)*8;
					DrawTextBg(DecNumBuf, 0, 0);
					DrawCharBg(':', j, 0);
					j += 8;

					// display pet's name
					DrawTextBg(FlashData.pet[i].name, j, 0);

					// display age
					DrawTextBg("Age:", 0, 16);
					DecUNum(DecNumBuf, FlashData.pet[i].state.age, 8);
					DrawTextBg(DecNumBuf, 4*8, 16);

					// display max age
					DrawTextBg("Max:", 0, 24);
					DecUNum(DecNumBuf, FlashData.pet[i].state.agemax, 8);
					DrawTextBg(DecNumBuf, 4*8, 24);

					// gone
					if (i > 0) DrawTextBg("GONE", 0, 32);

					// display pet
					j = FlashData.pet[i].state.type;
					if ((j & TYPE_ADULT) == 0) j = 0; // pet is baby
					j &= TYPE_MASK; // mask pet type
					DrawImgRleBgRev(ImgPetList[j], 64, 8); // draw pet

					// help
					DrawTextBg("A:\x11 B:\x13 C:Back", (WIDTH-14*8)/2, HEIGHT-8);

					// display update
					DispUpdate();

					// get key
					do {
						IWDG_Reload(); // update IWDG
						if (LoopIdle()) return; // loop idle, return if was sleeping
						key = KeyGet();
					} while (key == NOKEY);

					// keys
					if (key == KEY_A)
					{
						i++;
						if ((i >= FlashData.petnum) || (i >= PETNUM)) i = 0;
					}

					else if (key == KEY_B)
					{
						i--;
						if (i < 0) i = FlashData.petnum-1;
						if (i >= PETNUM) i = PETNUM-1;
					}
					else break;
				}
				break;

			// giveup
			case 7:
				// flush keys
				KeyFlush();

				// display prompt
				DrawClear();
				DrawTextBg("Return", (WIDTH-6*8)/2, 10);
				DrawTextBg(PetName, (WIDTH-(NAMEMAX-1)*8)/2, 20);
				DrawTextBg("back to parents?", (WIDTH-16*8)/2, 30);
				DrawTextBg("B:confirm C:back", (WIDTH-16*8)/2, 50);
				DispUpdate();

				// get key
				do {
					IWDG_Reload(); // update IWDG
					if (LoopIdle()) return; // loop idle, return if was sleeping
					key = KeyGet();
				} while ((key == NOKEY) || (key == KEY_A));

				// confirm
				if (key == KEY_B)
				{
					// close this pet
					ExitPet();

					// repaint new screen
					RepaintScreen();
				}
				break;
			}

			// return to the game
			RepaintScreen();
		}

		// C: back
		else if (key == KEY_C)
		{
			State = STATE_GAME;
			RepaintScreen();
		}
		break;
	}
}
