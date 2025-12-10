
// ****************************************************************************
//
//                              Music Player
//
// ****************************************************************************

#include "../include.h"

// find directory
int DirFindInx;		// current open directory (0 = Root)
int DirFindNum;		// number of directories
sFile DirFind;		// find directory
sFileInfo DirFindInfo;	// find directory info

// find file
int FileFindInx;	// current open file in directory
int FileFindNum;	// number of files in the directors
sFile FileFind;		// find file
sFileInfo FileFindInfo;	// find file info

// enumerate all directories (returns False on error)
Bool DirFindEnum()
{
	// reset number of directories (including Root)
	DirFindNum = 1;

	// open searching
	if (!FindOpen(&DirFind, "/")) return False;

	// enumerate directories
	while (FindNext(&DirFind, &DirFindInfo, ATTR_RO|ATTR_DIR|ATTR_ARCH, "*."))
	{
		// must be directory, and not '.' or '..'
		if (((DirFindInfo.attr & ATTR_DIR) != 0) &&
			(DirFindInfo.name[0] != '.'))
		{
			DirFindNum++;
		}
	}

	// close searching
	FindClose(&DirFind);

	return True;
}

// enumerate all WAV files in current directory (returns False on error)
Bool FileFindEnum()
{
	// reset number of files
	FileFindNum = 0;

	// open searching
	if (!FindOpen(&FileFind, "")) return False;

	// enumerate files
	while (FindNext(&FileFind, &FileFindInfo, ATTR_RO|ATTR_ARCH, "*.WAV")) FileFindNum++;

	// close searching
	FindClose(&FileFind);

	// check number of files
	return FileFindNum > 0;
}

// open directory with index (0=Root; returns False on error)
Bool DirFindOpen(int inx)
{
	// store new directory index
	DirFindInx = inx;

	// Root
	if (inx == 0)
	{
		if (!SetDir("/")) return False;
	}

	// search directory
	else
	{
		// open searching
		if (!FindOpen(&DirFind, "/")) return False;

		// search directory
		while (True)
		{
			// find next directory
			if (!FindNext(&DirFind, &DirFindInfo, ATTR_RO|ATTR_DIR|ATTR_ARCH, "*.")) return False;

			// must be directory, and not '.' or '..'
			if (((DirFindInfo.attr & ATTR_DIR) != 0) &&
				(DirFindInfo.name[0] != '.'))
			{
				inx--;
				if (inx == 0) break;
			}
		}

		// close searching
		FindClose(&DirFind);

		// set this directory
		if (!SetDir("/")) return False;
		if (!SetDir(DirFindInfo.name)) return False;
	}

	// enumerate files in current directory
	return FileFindEnum();
}

// open file with index (returns False on error)
Bool FileFindOpen(int inx)
{
	// store new file index
	FileFindInx = inx;

	// open searching
	if (!FindOpen(&FileFind, "")) return False;

	// search file
	while (True)
	{
		// find next file
		if (!FindNext(&FileFind, &FileFindInfo, ATTR_RO|ATTR_ARCH, "*.WAV")) return False;

		// count index
		inx--;
		if (inx < 0) break;
	}

	// close searching
	FindClose(&FileFind);

	// open this file
	return StartFile(FileFindInfo.name);
}

/*
// DEBUG: report error (code: 0..15)
//  1: (...-) cannot mount SD card
//  2: (..-.) cannot find WAV file
void Error(int code)
{
	NVIC_IRQDisable(IRQ_TIM1_UP);	// disable interrupt service
	GPIO_Mode(AUDIOL_GPIO, GPIO_MODE_OUT);
	GPIO_Mode(AUDIOR_GPIO, GPIO_MODE_OUT);
	TIM1_Reset();
	di();
	GPIO_Out0(AUDIOL_GPIO);
	GPIO_Out0(AUDIOR_GPIO);

	int i, j;
	while (True)
	{
		for (i = 3; i >= 0; i--)
		{
			j = ((code & (1 << i)) == 0) ? 250 : 1000;
			for (; j >= 0; j--)
			{
				GPIO_Flip(AUDIOL_GPIO);
				GPIO_Flip(AUDIOR_GPIO);
				WaitUs(500);
			}
			WaitMs(350);
		}

		WaitMs(1500);
	}
}
*/

// main function
int main(void)
{
	int i, j;

#if BEATLEBEAT		// 1 = use BeatleBeat device
	// start delay to enable reprogramming CPU
	WaitMs(5000);

	// Remap SWD debug interface (default 0)
	// 	0-3 ... SWD (SDI) enabled
	//	4 ... SWD (SDI) disable, pin served as GPIO
	GPIO_Remap_SWD(4);
#else
	// start delay to raise power
	WaitMs(200);
#endif

	// Remap PA1 & PA2 pins to OSC_IN & OSC_OUT (default 0)
	//	0 ... pins PA1 & PA2 are used as GPIO ports
	//	1 ... pins PA1 & PA2 are used as crystal pins OSC_IN & OSC_OUT
	GPIO_Remap_PA1PA2(0);
	WaitMs(10);

#if BABYBEAT		// 1 = use BabyBeat device
	// Initialize keyboard service
	KeyInit();
#endif

	// sound initialize
	SndInit();

	// initialize SD card interface
	SD_Init();

restart:
	// (re)mount disk
	while (!DiskMount()) { WaitMs(500); }

	// enumerate all directories
	DirFindEnum();

	// open first valid directory
	for (i = 0; i < DirFindNum; i++)
	{
		// open this directory
		if (DirFindOpen(i))
		{
			// open first file in current directory
			for (j = 0; j < FileFindNum; j++)
			{
				// open this file
				if (FileFindOpen(j)) break;
			}
			if (j < FileFindNum) break;
		}
	}
	if (i == DirFindNum) goto restart;

	// main loop
	while (True)
	{
		// ADPCM decompression
		u8 key = Decomp();

		// key
		switch (key)
		{
		// "Prev" file
		case KEY_PREV:
			for (i = FileFindNum + 1; i > 0; i--)
			{
				// open previous file
				if (FileFindOpen((FileFindInx == 0) ? (FileFindNum-1) : (FileFindInx-1))) break;
			}
			if (i == 0) goto restart;			
			break;

		// "Next" file
		case KEY_NEXT:
			for (i = FileFindNum + 1; i > 0; i--)
			{
				// open next file
				if (FileFindOpen((FileFindInx == FileFindNum-1) ? 0 : (FileFindInx+1))) break;
			}
			if (i == 0) goto restart;			
			break;

		// "Prev" directory
		case KEY_VOLDN_LONG:
			for (i = DirFindNum + 1; i > 0; i--)
			{
				// open previous directory
				if (DirFindOpen((DirFindInx == 0) ? (DirFindNum-1) : (DirFindInx-1)))
				{
					// open first file in current directory
					for (j = 0; j < FileFindNum; j++)
					{
						// open this file
						if (FileFindOpen(j)) break;
					}
					if (j < FileFindNum) break;
				}
			}
			if (i == 0) goto restart;			
			break;

		// "Next" directory
		case KEY_VOLUP_LONG:
			for (i = DirFindNum + 1; i > 0; i--)
			{
				// open next directory
				if (DirFindOpen((DirFindInx == DirFindNum-1) ? 0 : (DirFindInx+1)))
				{
					// open first file in current directory
					for (j = 0; j < FileFindNum; j++)
					{
						// open this file
						if (FileFindOpen(j)) break;
					}
					if (j < FileFindNum) break;
				}
			}
			if (i == 0) goto restart;			
			break;
		}
	}
}
