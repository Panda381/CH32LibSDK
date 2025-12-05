
// ****************************************************************************
//
//                                  Watchdog
//
// ****************************************************************************
// To use IWDG (Independent Watchdog; can run in low-power mode):
// - Enable LSI low speed clock 128kHz with: RCC_LSIEnable(void), wait until RCC_LSIIsStable(void)
// - See flash option byte "USER", bit 0: select 1=software IWDG (default) or 0=hardware IWDG
// - Enable write to IWDG registers with IWDG_EnableWrite().
// - Wait if IWDG_PrescBusy(), set IWDG prescaler with IWDG_SetPresc(). ... IWDG uses clock source LSI 128kHz.
// - Wait if IWDG_ReloadBusy(), set reload register with IWDG_SetReload(). ... Max. wait time is 8 seconds.
// - Start watchdog with IWDG_Enable().
// - Repeatedly feed the dog with IWDG_Reload().
// - After reset, check ResetReason variable with mask RCC_RESETON_IWDG, to check if IWDG was reset reason.

#if USE_WDG		// 1=use watchdog peripheral

#ifndef _SDK_WDG_H
#define _SDK_WDG_H

#ifdef __cplusplus
extern "C" {
#endif

// IWDG (Independent Watchdog) registers
typedef struct {
	io32	CTLR;		// 0x00: control register
	io32	PSCR;		// 0x04: prescaler register
	io32	RLDR;		// 0x08: reload value register
	io32	STATR;		// 0x0C: status register
} IWDG_t;
STATIC_ASSERT(sizeof(IWDG_t) == 0x10, "Incorrect IWDG_t!");
#define IWDG	((IWDG_t*)IWDG_BASE)	// 0x40003000

// WWDG (Window Watchdog) registers
typedef struct {
	io32	CTLR;		// 0x00: control register
	io32	CFGR;
	io32	STATR;
} WWDG_t;
STATIC_ASSERT(sizeof(WWDG_t) == 0x0C, "Incorrect WWDG_t!");
#define WWDG	((WWDG_t*)WWDG_BASE)	// 0x40002C00

// IWDG keys
#define IWDG_KEY_DISABLE	0x0000		// disable write access
#define IWDG_KEY_WRITE		0x5555		// enable write access to prescaler and reload register
#define IWDG_KEY_RELOAD		0xAAAA		// reload counter from reload register ("Feed the dog")
#define IWDG_KEY_ENABLE		0xCCCC		// enable IWDG counter (cannot be disabled until next reset)

// IWDG prescaler
#define IWDG_PRESC_4	0	// IWDG prescaler 1/4 ... clock 32kHz
#define IWDG_PRESC_8	1	// IWDG prescaler 1/8 ... clock 16kHz
#define IWDG_PRESC_16	2	// IWDG prescaler 1/16 ... clock 8kHz
#define IWDG_PRESC_32	3	// IWDG prescaler 1/32 ... clock 4kHz
#define IWDG_PRESC_64	4	// IWDG prescaler 1/64 ... clock 2kHz
#define IWDG_PRESC_128	5	// IWDG prescaler 1/128 ... clock 1kHz
#define IWDG_PRESC_256	6	// IWDG prescaler 1/256 ... clock 500Hz

// WWDG prescaler
#define WWDG_PRESC_1	0	// WWDG prescaler 1/1 ... clock = HCLK/4096
#define WWDG_PRESC_2	1	// WWDG prescaler 1/2 ... clock = HCLK/4096/2
#define WWDG_PRESC_4	2	// WWDG prescaler 1/4 ... clock = HCLK/4096/4
#define WWDG_PRESC_8	3	// WWDG prescaler 1/8 ... clock = HCLK/4096/8

// === IWDG (Independent Watchdog) control
// - See flash option byte "USER", bit 0: select 1=software IWDG (default) or 0=hardware IWDG
// - Enable LSI low speed clock 128kHz with: RCC_LSIEnable(void), wait until RCC_LSIIsStable(void)
// - After reset, check ResetReason variable with mask RCC_RESETON_IWDG, to check if IWDG was reset reason.

// enable/disable IWDG write access
INLINE void IWDG_EnableWrite(void) { IWDG->CTLR = IWDG_KEY_WRITE; }
INLINE void IWDG_DisableWrite(void) { IWDG->CTLR = IWDG_KEY_DISABLE; }

// set/get IWDG prescaler IWDG_PRESC_* (time base timer is LSI 128kHz = LSI_VALUE; result clock is 32kHz..500Hz)
// - Write must be enabled first, with IWDG_EnableWrite()
// - Before read/write, wait if IWDG_PrescBusy() is busy.
INLINE void IWDG_SetPresc(u8 presc) { IWDG->PSCR = presc; }
INLINE u8 IWDG_GetPresc(void) { return (u8)(IWDG->PSCR & 7); }

// set/get IWDG reload value 0x000..0xFFF (= 0..4095; max. interval is 4096/500 = 8 seconds)
// - Write must be enabled first, with IWDG_EnableWrite()
// - Before read/write, wait if IWDG_ReloadBusy() is busy.
INLINE void IWDG_SetReload(int val) { IWDG->RLDR = val; }
INLINE u16 IWDG_GetReload(void) { return (u16)(IWDG->RLDR & 0xfff); }

// reload IWDG counter with value defined in the reload register
INLINE void IWDG_Reload(void) { IWDG->CTLR = IWDG_KEY_RELOAD; }

// enable IWDG, start watchdog (write access to prescaler and reload register will be disabled)
// - Cannot be disabled until next reset.
INLINE void IWDG_Enable(void) { IWDG->CTLR = IWDG_KEY_ENABLE; }

// check if clock division update is in progress (do not read/write prescaler if update is in progress)
// - Cannot write or read prescaler if update is in progress
INLINE Bool IWDG_PrescBusy(void) { return (IWDG->STATR & B0) != 0; }

// check if reload value update is in progress (do not read/write reload value register if update is in progress)
// - Cannot write or read reload value register if update is in progress.
INLINE Bool IWDG_ReloadBusy(void) { return (IWDG->STATR & B1) != 0; }

// === WWDG (Window Watchdog) control

// Enable/disable WWDG, start watchdog (default disabled)
INLINE void WWDG_Enable(void) { WWDG->CTLR |= B7; }
INLINE void WWDG_Disable(void) { WWDG->CTLR &= ~B7; }

// Get/set WWDG counter 0..127 (reset if counter decrements from 64 to 63; default 127)
INLINE u8 WWDG_GetCnt(void) { return (u8)(WWDG->CTLR & 0x7f); }
INLINE void WWDG_SetCnt(int cnt) { WWDG->CTLR = (WWDG->CTLR & ~0x7f) | cnt; }

// Get/set WWDG window value 0..127 (default 127)
// - Dog feeding can only be done when the value of the counter is less than the window value and greater than 63.
INLINE u8 WWDG_GetWin(void) { return (u8)(WWDG->CFGR & 0x7f); }
INLINE void WWDG_SetWin(int win) { WWDG->CFGR = (WWDG->CFGR & ~0x7f) | win; }

// Get/set WWDG prescaler WWDG_PRESC_* (default WWDG_PRESC_1)
INLINE u8 WWDG_GetPresc(void) { return (u8)((WWDG->CFGR >> 7) & 3); }
INLINE void WWDG_SetPresc(int presc) { WWDG->CFGR = (WWDG->CFGR & ~ (B7|B8)) | (presc << 7); }

// Get/enable wake up interrupt enable bit (interrupt occurs when the value of the counter reaches 64)
INLINE Bool WWDG_GetEnableInt(void) { return (WWDG->CFGR & B9) != 0; }
INLINE void WWDG_EnableInt(void) { WWDG->CFGR |= B9; }

// Get/clear wake up interrupt flag (interrupt occurs when the value of the counter reaches 64)
INLINE Bool WWDG_GetInt(void) { return (WWDG->STATR & B0) != 0; }
INLINE void WWDG_ClrInt(void) { WWDG->STATR = 0; }

#ifdef __cplusplus
}
#endif

#endif // _SDK_WDG_H

#endif // USE_WDG
