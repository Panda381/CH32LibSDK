
// ****************************************************************************
//
//                         Music Player - Keys
//
// ****************************************************************************

#include "../include.h"

#if BABYBEAT		// 1 = use BabyBeat device

// last pressed key
volatile u8 KeyBuf = NOKEY;

// key pressed map
u8 KeyPressCnt[KEY_NUM];	// press counter
u8 KeyReleaseCnt[KEY_NUM];	// release counter
Bool KeyLong[KEY_NUM];		// key is long pressed

// get press button (NOKEY = no key)
u8 KeyGet()
{
	u8 key = KeyBuf;
	if (key != NOKEY) KeyBuf = NOKEY;
	return key;
}

// flush key buffer
void KeyFlush()
{
	KeyBuf = NOKEY;
}

// keyboard interrupt - called every 20ms from SysTick interrupt
void KeyScan()
{
	int i;

	// key loop
	for (i = 0; i < KEY_NUM; i++)
	{
		// check if key is pressed
		if (GPIO_In(PC0 + i) == 0) // key is pressed
		{
			// start of press
			if (KeyReleaseCnt[i] == 0)
			{
				// reset flag of long press
				KeyLong[i] = False;

				// reset press counter
				KeyPressCnt[i] = 0;
			}

			// restart release counter
			KeyReleaseCnt[i] = 4;

			// increase press counter
			KeyPressCnt[i]++;

			// long press >= 500ms (1 step is 20ms)
			if (KeyPressCnt[i] == 25)
			{
				KeyBuf = KEY_PLAY_LONG + i;
				KeyLong[i] = True; // flag - long press
			}

			// repeat 1s
			if (KeyPressCnt[i] >= 50) KeyPressCnt[i] = 0;
		}

		// key is not pressed
		else
		{
			// decrease release counter
			if (KeyReleaseCnt[i] > 0)
			{
				KeyReleaseCnt[i]--;

				// short press
				if ((KeyReleaseCnt[i] == 0) && !KeyLong[i])
				{
					KeyBuf = KEY_PLAY + i;
				}
			}
		}
	}
}

// Initialize keyboard service
void KeyInit()
{
	int i;
	RCC_AFIClkEnable();
	RCC_PCClkEnable();
	for (i = PC0; i <= PC4; i++) GPIO_Mode(i, GPIO_MODE_IN_PU);
	KeyBuf = NOKEY;
}

#endif // BABYBEAT
