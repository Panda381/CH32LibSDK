
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
#define PWR_PVDLEVEL_1V9	0	// 1.87V rising, 1.85V falling
#define PWR_PVDLEVEL_2V3	1	// 2.23V rising, 2.21V falling
#define PWR_PVDLEVEL_2V5	2	// 2.43V rising, 2.41V falling
#define PWR_PVDLEVEL_2V7	3	// 2.66V rising, 2.60V falling
#define PWR_PVDLEVEL_MASK	3

// Voltage regulator operating mode
#define PWR_LDOMODE_LOW		1	// low-power mode, LDO output 1.0V
#define PWR_LDOMODE_NORMAL	2	// normal mode, LDO output 1.2V
#define PWR_LDOMODE_SAVE	3	// energy saving mode, LDO output 1.0V

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

// Set voltage regulator operating mode PWR_LDOMODE_* (default PWR_LDOMODE_NORMAL)
INLINE void PWR_LDOMode(int mode) { PWR->CTLR = (PWR->CTLR & ~(3 << 2)) | (mode << 2); }

// Enable/Disable power voltage detector
INLINE void PWR_PVDEnable(void) { PWR->CTLR |= B4; }
INLINE void PWR_PVDDisable(void) { PWR->CTLR &= ~B4; }

// Set level of power voltage detector PWR_PVDLEVEL_*
INLINE void PWR_PVDLevel(int level) { PWR->CTLR = (PWR->CTLR & ~(PWR_PVDLEVEL_MASK<<5)) | (level<<5); }

// Enable/Disable Flash to enter low-power mode
INLINE void PWR_FlashLPEnable(void) { PWR->CTLR |= B9; }
INLINE void PWR_FlashLPDisable(void) { PWR->CTLR &= ~B9; }

// Set Flash status to Idle or Sleep
INLINE void PWR_FlashIdle(void) { PWR->CTLR &= ~(B10|B11); }
INLINE void PWR_FlashSleep(void) { PWR->CTLR |= B10|B11; }

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

// Enter sleep mode (use_wfi: True=use WFI wakeup, False=use WFE wakeup)
void PWR_EnterSleep(Bool use_wfi);

// Enter standby mode (use_wfi: True=use WFI wakeup, False=use WFE wakeup)
void PWR_EnterStandby(Bool use_wfi);

#ifdef __cplusplus
}
#endif

#endif // _SDK_PWR_H

#endif // USE_PWR
