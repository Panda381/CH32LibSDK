
// ****************************************************************************
//
//                               Power Control
//
// ****************************************************************************

#if USE_PWR		// 1=use power control

#ifndef _SDK_PWR_H
#define _SDK_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

// Power control 0x40007000
typedef struct {
	io32	CTLR;		// 0x00: Power control register
	io32	CSR;		// 0x04: Power control/status register
	io32	AWUCSR;		// 0x08: Auto-wakeup control/status register
	io32	AWUWR;		// 0x0C: Auto-wakeup window comparison value register
	io32	AWUPSC;		// 0x10: Auto-wakeup crossover factor register
} PWR_t;
STATIC_ASSERT(sizeof(PWR_t) == 0x14, "Incorrect PWR_t!");
#define PWR	((PWR_t*)PWR_BASE)

// level of power voltage detector
#define PWR_PVDLEVEL_2V9	0	// 2.85V rising, 2.70V falling
#define PWR_PVDLEVEL_3V1	1	// 3.05V rising, 2.90V falling
#define PWR_PVDLEVEL_3V3	2	// 3.30V rising, 3.15V falling
#define PWR_PVDLEVEL_3V5	3	// 3.50V rising, 3.30V falling
#define PWR_PVDLEVEL_3V7	4	// 3.70V rising, 3.50V falling
#define PWR_PVDLEVEL_3V9	5	// 3.90V rising, 3.70V falling
#define PWR_PVDLEVEL_4V1	6	// 4.10V rising, 3.90V falling
#define PWR_PVDLEVEL_4V4	7	// 4.40V rising, 4.20V falling
#define PWR_PVDLEVEL_MASK	7

#define PWR_AWUCMP_MAX		0x3f	// max. value of auto-wakeup windows compare

// Auto-wakeup prescaler
#define PWR_AWUPSC_OFF		0	// prescaler off
#define PWR_AWUPSC_1		1	// not divided
#define PWR_AWUPSC_2		2	// divided by 2
#define PWR_AWUPSC_4		3	// divided by 4
#define PWR_AWUPSC_8		4	// divided by 8
#define PWR_AWUPSC_16		5	// divided by 16
#define PWR_AWUPSC_32		6	// divided by 32
#define PWR_AWUPSC_64		7	// divided by 64
#define PWR_AWUPSC_128		8	// divided by 128
#define PWR_AWUPSC_256		9	// divided by 256
#define PWR_AWUPSC_512		10	// divided by 512
#define PWR_AWUPSC_1024		11	// divided by 1024
#define PWR_AWUPSC_2048		12	// divided by 2048
#define PWR_AWUPSC_4096		13	// divided by 4096
#define PWR_AWUPSC_10240	14	// divided by 10240
#define PWR_AWUPSC_61440	15	// divided by 61440
#define PWR_AWUPSC_MASK		0x0f

// Select Sleep mode on power-down deep sleep scenario (default)
INLINE void PWR_PDDSSleep(void) { PWR->CTLR &= ~B1; }

// Select Standby mode on power-down deep sleep scenario
INLINE void PWR_PDDSStandby(void) { PWR->CTLR |= B1; }

// Enable/Disable power voltage detector
INLINE void PWR_PVDEnable(void) { PWR->CTLR |= B4; }
INLINE void PWR_PVDDisable(void) { PWR->CTLR &= ~B4; }

// Set level of power voltage detector PWR_PVDLEVEL_*
INLINE void PWR_PVDLevel(int level) { PWR->CTLR = (PWR->CTLR & ~(PWR_PVDLEVEL_MASK<<5)) | (level<<5); }

// Check if VDD is below PVD threshold
INLINE Bool PWR_PVDLow(void) { return (PWR->CSR & B2) != 0; }

// Enable/Disable auto-wakeup
INLINE void PWR_AWUEnable(void) { PWR->AWUCSR |= B1; }
INLINE void PWR_AWUDisable(void) { PWR->AWUCSR &= ~B1; }

// Setup auto-wakeup window compare value, 0 to PWR_AWUCMP_MAX (0..63)
// - When the up-counter is equal to window compare value + 1, wake-up signal is generated.
INLINE void PWR_AWUCmp(int comp) { PWR->AWUWR = (PWR->AWUWR & ~PWR_AWUCMP_MAX) | comp; }

// Setup auto-wakeup prescaler PWR_AWUPSC_* (to divide LSI time base)
INLINE void PWR_AWUPsc(int psc) { PWR->AWUPSC = (PWR->AWUPSC & ~PWR_AWUPSC_MASK) | psc; }

// Enter sleep mode, use WFI wakeup
void PWR_EnterSleep();

// Enter sleep mode, use WFE wakeup
void PWR_EnterSleepWfe();

// Enter standby mode, use WFI wakeup
void PWR_EnterStandby();

// Enter standby mode, use WFE wakeup
void PWR_EnterStandbyWfe();

#ifdef __cplusplus
}
#endif

#endif // _SDK_PWR_H

#endif // USE_PWR
