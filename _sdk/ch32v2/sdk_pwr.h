
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
#define PWR_PVDLEVEL_2V2	0	// 1.8V: 2.19V rising, 2.13V falling; 2.4V: 2.37V rising, 2.29V falling
#define PWR_PVDLEVEL_2V3	1	// 1.8V: 2.33V rising, 2.25V falling; 2.4V: 2.55V rising, 2.46V falling
#define PWR_PVDLEVEL_2V4	2	// 1.8V: 2.39V rising, 2.32V falling; 2.4V: 2.63V rising, 2.55V falling
#define PWR_PVDLEVEL_2V5	3	// 1.8V: 2.48V rising, 2.42V falling; 2.4V: 2.76V rising, 2.67V falling
#define PWR_PVDLEVEL_2V6	4	// 1.8V: 2.57V rising, 2.51V falling; 2.4V: 2.87V rising, 2.78V falling
#define PWR_PVDLEVEL_2V7	5	// 1.8V: 2.69V rising, 2.61V falling; 2.4V: 3.03V rising, 2.93V falling
#define PWR_PVDLEVEL_2V8	6	// 1.8V: 2.78V rising, 2.69V falling; 2.4V: 3.18V rising, 3.06V falling
#define PWR_PVDLEVEL_2V9	7	// 1.8V: 2.88V rising, 2.79V falling; 2.4V: 3.29V rising, 3.19V falling
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

// Enable/Disable write RTC and backup registers (default disabled)
INLINE void PWR_WRTCEnable(void) { PWR->CTLR |= B8; }
INLINE void PWR_WRTCDisable(void) { PWR->CTLR &= ~B8; }

// Enable/Disable 2K RAM standby power (default disabled)
INLINE void PWR_R2KSTYEnable(void) { PWR->CTLR |= B16; }
INLINE void PWR_R2KSTYDisable(void) { PWR->CTLR &= ~B16; }

// Enable/Disable 18K RAM standby power (default disabled)
INLINE void PWR_R18KSTYEnable(void) { PWR->CTLR |= B17; }
INLINE void PWR_R18KSTYDisable(void) { PWR->CTLR &= ~B17; }

// Enable/Disable 2K RAM VBAT power (default disabled)
INLINE void PWR_R2KVBATEnable(void) { PWR->CTLR |= B18; }
INLINE void PWR_R2KVBATDisable(void) { PWR->CTLR &= ~B18; }

// Enable/Disable 18K RAM VBAT power (default disabled)
INLINE void PWR_R18KVBATEnable(void) { PWR->CTLR |= B19; }
INLINE void PWR_R18KVBATDisable(void) { PWR->CTLR &= ~B19; }

// Enable/Disable RAM operate on low voltage (default disabled)
INLINE void PWR_RAMLVEnable(void) { PWR->CTLR |= B20; }
INLINE void PWR_RAMLVDisable(void) { PWR->CTLR &= ~B20; }

// Check if VDD is below PVD threshold
INLINE Bool PWR_PVDLow(void) { return (PWR->CSR & B2) != 0; }

// Enable/Disable WKUP pin to wake up the MCU (disabled default)
INLINE void PWR_WKUPEnable(void) { PWR->CSR |= B8; }
INLINE void PWR_WKUPDisable(void) { PWR->CSR &= ~B8; }

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
