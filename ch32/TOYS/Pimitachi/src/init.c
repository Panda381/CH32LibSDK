
// ****************************************************************************
//
//                                 Initialize
//
// ****************************************************************************

#include "../include.h"

// intro melody
const sTone MusicIntro[] = {
	{ NOTE_LEN2, NOTE_G6 },
	{ NOTE_LEN4, NOTE_F6 },
	{ NOTE_LEN2, NOTE_E6 },
	{ NOTE_LEN4, NOTE_D6 },
	{ NOTE_LEN2, NOTE_G6 },
	{ NOTE_LEN2, NOTE_R },
	{ NOTE_STOP, NOTE_R }
};

// reinitialize
void Reinit(void)
{
	// repaint game screen
	RepaintScreen();

	// randomize
	RandSeed += PetTicks();

	// key flush
	KeyFlush();

	// init animation
	u32 t = Time();
	DirNextTime = t;
	WinkNextTime = t;
	AnimNextTime = t;
	Last = t;
	LastTick = t;
}

// start and initialize
void Init(void)
{
	// Remap PA1 & PA2 pins to OSC_IN & OSC_OUT (default 0)
	//	0 ... pins PA1 & PA2 are used as GPIO ports
	//	1 ... pins PA1 & PA2 are used as crystal pins OSC_IN & OSC_OUT
	GPIO_Remap_PA1PA2(0);

	// load Flash data - clear if not valid
	// check RAM data - load from Flash if not valid
	if (!LoadFlash() || (RamDataCRC(RamData) != RamData->crc32))
	{
		RamData->ticks = 0;
		RamData->state.data[0] = FlashData.pet[0].state.data[0];
		RamData->state.data[1] = FlashData.pet[0].state.data[1];
		RamCrc();
	}

	// watchdog init
	IWDGInit();

	// initialize input key pins
	KeyInit();

	// IWDT reset reason
	if ((ResetReason & RCC_RESETON_IWDG) != 0)
	{
		// shift pet state by 1 tick - sleeping
		PetTick(True);

		// disable SysTick counter
		SysTick_Disable();

		// Enter standby mode, use WFI wakeup
		PWR_EnterStandby();

// Continue here after pressing buttons A or B. Another option is to reset from IWDG.

		// enable SysTick counter
		SysTick_Enable();
	}

	// Display initialize
	DispInit();

	// display splash screen on first start (from normal reset)
	if ((ResetReason & RCC_RESETON_IWDG) == 0) // no IWDT, hard reset
	{
		// clear screen
		DrawClear();

		// draw intro image
		// image width: 38 pixels
		// image height: 39 lines
		DrawImgRleBg(ImgBaby, (WIDTH-38)/2, 8);
		// image width: 26 pixels
		// image height: 8 lines
		// X=7, Y=15
		DrawImgRleBg(ImgBabyEye, (WIDTH-38)/2+7, 8+15);
		// image width: 48 pixels
		// image height: 6 lines
		DrawImgRleBg(ImgTitle, (WIDTH-48)/2, 52);

		// display update
		DispUpdate();

		// intro music (wait)
		PlayMusic(MusicIntro);
	}

	// wake-up from IWDT with key press
	else
	{
		// repaint wake up
		RepaintWakeup();

		// wait 1 second
		WaitMsIWDT(1000);
	}

	// prepare current state
	State = STATE_SEL; // start new pet
	if (PetIsValid() && ((PetType() & TYPE_GONE) == 0)) State = STATE_GAME; // game is in progress

	// reinitialize
	Reinit();
}
