
// ****************************************************************************
//
//                                 Pimitachi
//
// ****************************************************************************

#include "../include.h"

// wait [ms] with IWDT (must be less than 8 seconds)
void WaitMsIWDT(int ms)
{
	// feed watch dog
	IWDG_Reload();

	// wait
	cb();
	WaitMs(ms);
	cb();

	// feed watch dog
	IWDG_Reload();
}

// loop idle (returns True if was sleeping)
Bool LoopIdle(void)
{
	// next tick
	if ((u32)(Time() - LastTick) >= TICK*1000*HCLK_PER_US)
	{
		// shift pet state by 1 tick - not sleeping
		PetTick(False);

		// time of last tick
		LastTick = Time();
	}

	// time-out, go to sleep
	if ((u32)(Time() - Last) >= TIMEOUT*1000000*HCLK_PER_US)
	{
		// go sleep
		GoSleep();
		return True;
	}
	return False;
}

// main code
int main(void)
{
	u8 key;

	// start and initialize
	Init();

	// main loop
	while (True)
	{
		// delay 10ms
		WaitMsIWDT(10);

		// game animation
		GameAnim();

		// get key
		key = KeyGet();
		if (key != NOKEY)
		{
			// game control
			GameCtrl(key);
		}

		// loop idle
		LoopIdle();
	}
}
