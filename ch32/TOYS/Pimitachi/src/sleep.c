
// ****************************************************************************
//
//                                Sleep
//
// ****************************************************************************

#include "../include.h"

// repaint going to sleep
void RepaintSleep(void)
{
	// clear screen
	DrawClear();

	// draw title
	DrawText2Bg("GO SLEEP", (WIDTH-8*16)/2, 0);

	// draw bed
	DrawImgRleBg(ImgBed, (WIDTH-53)/2, 16);

	// draw animal
	int inx = PetType();
	if (inx > 0)
	{
		// pet real type
		inx = PetRealType();

		// draw animal in bed
		DrawImgRleBg(ImgBedList[inx], (WIDTH-53)/2 + ImgBedXY[2*inx], 16 + ImgBedXY[2*inx+1]);
	}

	// draw Zzz
	DrawImgRleBg(ImgZzz, (WIDTH-53)/2+37, 16+1);

	// display update
	DispUpdate();
}

// repaint wake up
void RepaintWakeup(void)
{
	// clear screen
	DrawClear();

	// draw title
	DrawText2Bg("WAKE-UP!", (WIDTH-8*16)/2+2, 0);

	// draw bed
	DrawImgRleBg(ImgBed, (WIDTH-53)/2, 16);

	// draw animal
	int inx = PetType();
	if (inx > 0)
	{
		// pet real type
		inx = PetRealType();

		// draw animal in bed
		DrawImgRleBg(ImgBedList[inx], (WIDTH-53)/2 + ImgBedXY[2*inx], 16 + ImgBedXY[2*inx+1]);

		// draw animal wakeup
		DrawImgRleBg(ImgWakeupList[inx], (WIDTH-53)/2 + ImgWakeupXY[2*inx], 16 + ImgWakeupXY[2*inx+1]);
	}

	// display update
	DispUpdate();
}

// watchdog init
void IWDGInit()
{
	// start LSI 128kHz oscillator
	RCC_LSIEnable();
	while (!RCC_LSIIsStable()) {}

	// setup IWDG, set time-out to 8 seconds
	IWDG_EnableWrite();			// enable write to IWDG registers
	while (IWDG_PrescBusy()) {}		// wait it prescaler update is busy
	IWDG_SetPresc(IWDG_PRESC_256);		// set prescaler to 1/256, clock 500Hz
	while (IWDG_ReloadBusy()) {}		// wait if reloader update is busy
	IWDG_SetReload(0xfff);			// set reloader to 4095, time out will be 8.192 seconds
	while (IWDG_ReloadBusy()) {}		// wait if reloader update is busy
	IWDG_Reload();				// feed watch dog
	IWDG_Enable();				// enable IWDG, start watchdog
}

// go sleep
void GoSleep()
{
	int i;

	// save state
	SaveRamFlash();

	// repaint going to sleep
	RepaintSleep();

	// wait 1 second
	WaitMsIWDT(1000);

	// display OFF
	DrawClear();
	DispUpdate();
	DispOff();

	// disable SysTick counter
	SysTick_Disable();

	// feed watch dog
	IWDG_Reload();

	// Enter standby mode, use WFI wakeup
	PWR_EnterStandby();

// Continue here after pressing buttons A or B. Another option is to reset from IWDG.

	// enable SysTick counter
	SysTick_Enable();

	// display ON
	DispOn();

	// repaint wake up
	RepaintWakeup();

	// wait 1 second
	WaitMsIWDT(1000);

	// reinitialize
	Reinit();
}
