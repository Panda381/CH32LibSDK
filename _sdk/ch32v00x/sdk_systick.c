
// ****************************************************************************
//
//                           SysTick System Timer
//
// ****************************************************************************

#include "../../includes.h"	// globals

// system time counter, counts time from system start in [ms]
// - overflow after 49 days (use difference, not absolute value!)
volatile u32 SysTime = 0;

// current date and time
volatile u32 UnixTime = 0;	// current date and time in Unix format
				// - number of seconds since 1/1/1970 (thursday) up to 12/31/2099
volatile u16 CurTimeMs = 0;	// current time in [ms] 0..999

u32 SysTick_OldCnt;		// old SysTick counter

#if SYSTICK_MS > 0 // 0=do not use SysTick interrupt
// SysTick handler
HANDLER void SysTick_Handler()
{
	// clear interrupt request
	SysTick_ClrCmp();

	// get new counter
	u32 cnt = SysTick_Get();

	// load current time
	u32 sys = SysTime;
	u16 ms = CurTimeMs;
	u32 old = SysTick_OldCnt;

	// increase time
	u32 dif = cnt - old;
	while (dif >= SYSTICK_HCLK)
	{
		dif -= SYSTICK_HCLK;
		old += SYSTICK_HCLK;
		sys += SYSTICK_MS;
		ms += SYSTICK_MS;
		if (ms >= 1000)
		{
			UnixTime++;
			ms -= 1000;
		}
	}

	// save new current time
	SysTime = sys;
	CurTimeMs = ms;
	SysTick_OldCnt = old;

	// set new interrupt time (skip one interrupt, if remains < 100us)
	cnt += SYSTICK_HCLK - dif;
	if (dif >= SYSTICK_HCLK - 100*HCLK_PER_US) cnt += SYSTICK_HCLK;
	SysTick_SetCmp(cnt);

#if SYSTICK_KEYSCAN	// call KeyScan() function from SysTick system timer
	KeyScan();
#endif

#if SYSTICK_SOUNDSCAN	// 1=call SoundScan() function from SysTick system timer
	SoundScan();
#endif
}
#endif // SYSTICK_MS > 0

// Initialize SysTick
void SysTick_Init(void)
{
	SysTick_Disable();	// disable counter
	SysTick_IntDisable();	// disable interrupt
	SysTick_SrcHCLK();	// time base is HCLK
	SysTick_Unforce();	// not forced
	SysTick_Set(0);		// clear counter
	SysTick_SetCmp(HCLK_PER_MS/2-1); // set next compare value
	SysTick_ClrCmp();	// clear compare interrupt request
	SysTick_ResetDisable();	// not reseting to 0
	SysTick_OldCnt = 0;	// update current counter
	SysTick_Enable();	// enable counter
#if SYSTICK_MS > 0 // 0=do not use SysTick interrupt
	NVIC_IRQEnable(IRQ_SYSTICK); // IRQ enable
	SysTick_IntEnable();	// interrupt enable
#endif
}

// Reset SysTick
void SysTick_Reset(void)
{
	SysTick_IntDisable();	// interrupt disable
	NVIC_IRQDisable(IRQ_SYSTICK); // IRQ disable
	SysTick_ClrCmp();	// clear interrupt request
	SysTick_Disable();	// disable counter

	SysTick->CMP = 0;	// reset comparison register
	SysTick->CNT = 0;	// reset counter
	SysTick->SR = 0;	// clear comparison flag
	SysTick->CTLR = 0;	// reset control register
}

// Wait for delay in CPU clock cycles (max. 89 seconds)
void WaitClk(u32 clk)
{
	// get start time
	u32 start = Time();

	// wait
	while ((u32)(Time() - start) < clk) {}
}

// Wait for delay in [us] (max. 89 seconds)
void WaitUs(u32 us)
{
	// recalculate us to ticks
	us *= HCLK_PER_US;

	// get start time
	u32 start = Time();

	// wait
	while ((u32)(Time() - start) < us) {}
}

// Wait for delay in [ms] (max. 89 seconds)
void WaitMs(u32 ms)
{
	// recalculate ms to ticks
	ms *= HCLK_PER_MS;

	// get start time
	u32 start = Time();

	// wait
	while ((u32)(Time() - start) < ms) {}
}
