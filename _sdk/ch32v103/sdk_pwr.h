
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
} PWR_t;
STATIC_ASSERT(sizeof(PWR_t) == 0x08, "Incorrect PWR_t!");
#define PWR	((PWR_t*)PWR_BASE)

// level of power voltage detector
#define PWR_PVDLEVEL_2V7	0	// 2.65V rising, 2.50V falling
#define PWR_PVDLEVEL_2V9	1	// 2.87V rising, 2.70V falling
#define PWR_PVDLEVEL_3V1	2	// 3.07V rising, 2.89V falling
#define PWR_PVDLEVEL_3V3	3	// 3.27V rising, 3.08V falling
#define PWR_PVDLEVEL_3V5	4	// 3.46V rising, 3.27V falling
#define PWR_PVDLEVEL_3V8	5	// 3.76V rising, 3.55V falling
#define PWR_PVDLEVEL_4V1	6	// 4.07V rising, 3.84V falling
#define PWR_PVDLEVEL_4V4	7	// 4.43V rising, 4.13V falling
#define PWR_PVDLEVEL_MASK	7

// Select normal mode of voltage regulator (default)
INLINE void PWR_LPDSNorm(void) { PWR->CTLR &= ~B0; }

// Select low-power mode of voltage regulator
INLINE void PWR_LPDSLow(void) { PWR->CTLR |= B0; }

// Select Stop mode on power-down deep sleep scenario (default)
INLINE void PWR_PDDSSleep(void) { PWR->CTLR &= ~B1; }

// Select Standby mode on power-down deep sleep scenario
INLINE void PWR_PDDSStandby(void) { PWR->CTLR |= B1; }

// Clear wakeup flag bit
INLINE void PWR_WUFClr(void) { PWR->CTLR |= B2; }

// Check wakeup flag bit
INLINE Bool PWR_WUFIsSet(void) { return (PWR->CSR & B0) != 0; }

// Clear standby flag bit
INLINE void PWR_SBFClr(void) { PWR->CTLR |= B3; }

// Check standby flag bit
INLINE Bool PWR_SBFIsSet(void) { return (PWR->CSR & B1) != 0; }

// Enable/Disable power voltage detector
INLINE void PWR_PVDEnable(void) { PWR->CTLR |= B4; }
INLINE void PWR_PVDDisable(void) { PWR->CTLR &= ~B4; }

// Set level of power voltage detector PWR_PVDLEVEL_*
INLINE void PWR_PVDLevel(int level) { PWR->CTLR = (PWR->CTLR & ~(PWR_PVDLEVEL_MASK<<5)) | (level<<5); }

// Enable/Disable write RTC and backup registers (disabled default)
INLINE void PWR_WRTCEnable(void) { PWR->CTLR |= B8; }
INLINE void PWR_WRTCDisable(void) { PWR->CTLR &= ~B8; }

// Check if VDD is below PVD threshold
INLINE Bool PWR_PVDLow(void) { return (PWR->CSR & B2) != 0; }

// Enable/Disable WKUP pin to wake up the MCU (disabled default)
INLINE void PWR_WKUPEnable(void) { PWR->CSR |= B8; }
INLINE void PWR_WKUPDisable(void) { PWR->CSR &= ~B8; }

// Enter sleep mode (use_wfi: True=use WFI wakeup, False=use WFE wakeup)
void PWR_EnterSleep(Bool use_wfi);

// Enter standby mode (use_wfi: True=use WFI wakeup, False=use WFE wakeup)
void PWR_EnterStandby(Bool use_wfi);

#ifdef __cplusplus
}
#endif

#endif // _SDK_PWR_H

#endif // USE_PWR
