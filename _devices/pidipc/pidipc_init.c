
// ****************************************************************************
//
//                        PidiPC - Device init
//
// ****************************************************************************

#include "../../includes.h"

// Initialize device
void DevInit()
{
#if USE_KEY		// 1=use keyboard support
	// Initialize keyboard service (should be called before display init)
	KeyInit();

	// CPU synchronization at startup
	CPU_SyncInit();
#endif

#if USE_SOUND		// 1=use sound support
	// Sound initialize
	SoundInit();
#endif

#if USE_SD		// 1=use SD card driver
	// initialize SD card interface
	SD_Init();
#endif

#if USE_DISP		// 1=use display support
	// Initialize videomode
	DispInit();
#endif

#if USE_DRAW || USE_PRINT
	// clear screen
	DrawClear();
#endif
}

// Terminate device
void DevTerm()
{
#if USE_KEY		// 1=use keyboard support
	// wait for no key pressed
	KeyWaitNoPressed();
#endif

#if USE_DISP		// 1=use display support
	// Terminate videomode
	DispTerm();
#endif

#if USE_SD		// 1=use SD card driver
	// Terminate SD card interface
	SD_Term();
#endif

#if USE_SOUND		// 1=use sound support
	// Sound terminate
	SoundTerm();
#endif

#if USE_KEY		// 1=use keyboard support
	// terminate keyboard
	KeyTerm();
#endif
}
