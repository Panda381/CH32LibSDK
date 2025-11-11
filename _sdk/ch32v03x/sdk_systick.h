
// ****************************************************************************
//
//                           SysTick System Timer
//
// ****************************************************************************

#ifndef _SDK_SYSTICK_H
#define _SDK_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

// number of HCLK clock cycles per 1 us (used with Wait functions)
// - If you want to change frequency of system clock run-time, use a variable instead of constant.
#ifndef HCLK_PER_US
#define HCLK_PER_US	48
#endif

// number of HCLK clock cycles per 1 ms
// - If you want to change frequency of system clock run-time, use a variable instead of constant.
#ifndef HCLK_PER_MS
#define HCLK_PER_MS	(HCLK_PER_US*1000)
#endif

// increment of system time in [ms] on SysTick interrupt (0=do not use SysTick interrupt)
#ifndef SYSTICK_MS
#define SYSTICK_MS	16
#endif

// number of HCLK clock cycles per SysTick interrupt
// - If you want to change frequency of system clock run-time, use a variable instead of constant.
#ifndef SYSTICK_HCLK
#define SYSTICK_HCLK	(SYSTICK_MS*HCLK_PER_MS)
#endif

// SysTick System counter
typedef struct {
	io32	CTLR;			// 0x00: system count control register
	io32	SR;			// 0x04: system count status register
	io32	CNT;			// 0x08: system counter register LOW
	io32	CNTH;			// 0x0C: system counter register HIGH
	io32	CMP;			// 0x10: counting comparison register LOW
	io32	CMPH;			// 0x14: counting comparison register HIGH
} SysTick_t;
STATIC_ASSERT(sizeof(SysTick_t) == 0x18, "Incorrect SysTick_t!");
#define SysTick		((SysTick_t*)SYSTICK_BASE) // 0xE000F000

// system time counter, counts time from system start in [ms]
// - overflow after 49 days (use difference, not absolute value!)
extern volatile u32 SysTime;

// current date and time
extern volatile u32 UnixTime;	// current date and time in Unix format
				// - number of seconds since 1/1/1970 (thursday) up to 12/31/2099
extern volatile u16 CurTimeMs;	// current time in [ms] 0..999

// Enable/Disable System counter
INLINE void SysTick_Enable(void) { SysTick->CTLR |= B0; }
INLINE void SysTick_Disable(void) { SysTick->CTLR &= ~B0; }

// Enable/Disable System counter interrut (enable IRQ with NVIC_IRQEnable(IRQ_SYSTICK))
INLINE void SysTick_IntEnable(void) { SysTick->CTLR |= B1; }
INLINE void SysTick_IntDisable(void) { SysTick->CTLR &= ~B1; }

// Select System counter time base to HCLK or HCLK/8
INLINE void SysTick_SrcHCLK(void) { SysTick->CTLR |= B2; }
INLINE void SysTick_SrcHCLK8(void) { SysTick->CTLR &= ~B2; }

// Enable/Disable reset to 0 after reaching comparison value (or count to max otherwise)
INLINE void SysTick_ResetEnable(void) { SysTick->CTLR |= B3; }
INLINE void SysTick_ResetDisable(void) { SysTick->CTLR &= ~B3; }

// Set counting direction up/dwn
INLINE void SysTick_CountUp(void) { SysTick->CTLR &= ~B4; }
INLINE void SysTick_CountDown(void) { SysTick->CTLR |= B4; }

// Check/Clear flag of counter initial value update
INLINE Bool SysTick_IsInit(void) { return (SysTick->CTLR & B5) != 0; }
INLINE void SysTick_ClrInit(void) { SysTick->CTLR |= B5; }

// Force/Unforce software interrupt trigger (must be unforced on interrupt)
INLINE void SysTick_Force(void) { SysTick->CTLR |= B31; }
INLINE void SysTick_Unforce(void) { SysTick->CTLR &= ~B31; }
INLINE Bool SysTick_IsForced(void) { return (SysTick->CTLR & B31) != 0; }

// Check/Clear comparison flag
INLINE Bool SysTick_IsCmp(void) { return (SysTick->SR & B0) != 0; }
INLINE void SysTick_ClrCmp(void) { SysTick->SR &= ~B0; }

// Set SysTick System counter (counter should be stopped)
INLINE void SysTick_Set(u64 cnt)
{
	SysTick->CNT = (u32)cnt;
	SysTick->CNTH = (u32)(cnt >> 32);
}

// Get SysTick System counter LOW
INLINE u32 SysTick_Get(void) { return SysTick->CNT; }

// Get SysTick System counter 64-bit (interrupt safe)
u64 SysTick_Get64(void);

// Set SysTick comparison value
INLINE void SysTick_SetCmp(u64 cmp)
{
	// high word should be set first - in most cases it is higher than old value
	SysTick->CMPH = (u32)(cmp >> 32);
	cb();
	SysTick->CMP = (u32)cmp;
}

// Get SysTick comparison value
INLINE u64 SysTick_GetCmp64(void) { return SysTick->CMP | ((u64)SysTick->CMPH << 32); }

// scan keyboard (called from SysTick)
void KeyScan();

// Initialize SysTick
void SysTick_Init(void);

// Reset SysTick
void SysTick_Reset(void);

// Get current time in number of CPU clock cycles (= 48 MHz, overflow after 89 seconds)
// - Use HCLK_PER_US to get number of ticks per 1 us.
INLINE u32 Time(void) { return SysTick_Get(); }
INLINE u64 Time64(void) { return SysTick_Get64(); }

// Wait for delay in CPU clock cycles (max. 89 seconds)
void WaitClk(u32 clk);

// Wait for delay in [us] (max. 89 seconds)
void WaitUs(u32 us);

// Wait for delay in [ms] (max. 89 seconds)
void WaitMs(u32 ms);

#ifdef __cplusplus
}
#endif

#endif // _SDK_SYSTICK_H
