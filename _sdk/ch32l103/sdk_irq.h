
// ****************************************************************************
//
//                                Interrupt
//
// ****************************************************************************

#if USE_IRQ		// 1=use IRQ interrupt support

#ifndef _SDK_IRQ_H
#define _SDK_IRQ_H

#ifdef __cplusplus
extern "C" {
#endif

// CPU Internal Interrupts
#define IRQ_RESET	0		// Reset
#define IRQ_NMI		2		// NMI, Non Naskable interrupt (default weak handler NMI_Handler)
#define IRQ_HARDFAULT	3		// Hard Fault, Exception interrupt (default weak handler HardFault_Handler)
#define IRQ_ECALL_MMODE	5		// Ecall M Mode Interrupt (default weak handler Ecall_M_Mode_Handler)
#define IRQ_ECALL_UMODE	8		// Ecall U Mode Interrupt (default weak handler Ecall_U_Mode_Handler)
#define IRQ_BREAKPOINT	9		// Break Point Interrupt (default weak handler Break_Point_Handler)
#define IRQ_SYSTICK	12		// SysTick, System Timer interrupt (default weak handler SysTick_Handler)
#define IRQ_SW		14		// Software interrupt (default weak handler SW_Handler)
// External Interrupts
#define IRQ_WWDG	16		// Window WatchDog interrupt (default weak handler WWDG_IRQHandler)
#define IRQ_PVD		17		// PVD through EXTI line detection interrupt (default weak handler PVD_IRQHandler)
#define IRQ_TAMPER	18		// Tamper interrupt (default weak handler TAMPER_IRQHandler)
#define IRQ_RTC		19		// RTC global interrupt (default weak handler RTC_IRQHandler)
#define IRQ_FLASH	20		// Flash global interrupt (default weak handler FLASH_IRQHandler)
#define IRQ_RCC		21		// RCC global Interrupt (default weak handler RCC_IRQHandler)
#define IRQ_EXTI0	22		// EXTI Line0 Interrupt (default weak handler EXTI0_IRQHandler)
#define IRQ_EXTI1	23		// EXTI Line1 Interrupt (default weak handler EXTI1_IRQHandler)
#define IRQ_EXTI2	24		// EXTI Line2 Interrupt (default weak handler EXTI2_IRQHandler)
#define IRQ_EXTI3	25		// EXTI Line3 Interrupt (default weak handler EXTI3_IRQHandler)
#define IRQ_EXTI4	26		// EXTI Line4 Interrupt (default weak handler EXTI4_IRQHandler)
#define IRQ_DMA1_CH1	27		// DMA1 Channel 1 global Interrupt (default weak handler DMA1_Channel1_IRQHandler)
#define IRQ_DMA1_CH2	28		// DMA1 Channel 2 global Interrupt (default weak handler DMA1_Channel2_IRQHandler)
#define IRQ_DMA1_CH3	29		// DMA1 Channel 3 global Interrupt (default weak handler DMA1_Channel3_IRQHandler)
#define IRQ_DMA1_CH4	30		// DMA1 Channel 4 global Interrupt (default weak handler DMA1_Channel4_IRQHandler)
#define IRQ_DMA1_CH5	31		// DMA1 Channel 5 global Interrupt (default weak handler DMA1_Channel5_IRQHandler)
#define IRQ_DMA1_CH6	32		// DMA1 Channel 6 global Interrupt (default weak handler DMA1_Channel6_IRQHandler)
#define IRQ_DMA1_CH7	33		// DMA1 Channel 7 global Interrupt (default weak handler DMA1_Channel7_IRQHandler)
#define IRQ_ADC1	34		// ADC1 global Interrupt (default weak handler ADC1_IRQHandler)
#define IRQ_USB_HP_CAN1_TX	35	// USB Device High Priority or CAN1 TX Interrupts (default weak handler USB_HP_CAN1_TX_IRQHandler)
#define IRQ_USB_LP_CAN1_RX0	36	// USB Device Low Priority or CAN1 RX0 Interrupts (default weak handler USB_LP_CAN1_RX0_IRQHandler)
#define IRQ_CAN1_SCE		38	// CAN1 SCE Interrupt (default weak handler CAN1_SCE_IRQHandler)
#define IRQ_EXTI9_5	39		// External Line[9:5] Interrupts (default weak handler EXTI9_5_IRQHandler)
#define IRQ_TIM1_BRK	40		// TIM1 Break Interrupt (default weak handler 
#define IRQ_TIM1_UP	41		// TIM1 Update Interrupt (default weak handler 
#define IRQ_TIM1_TRG	42		// TIM1 Trigger and Commutation Interrupt (default weak handler 
#define IRQ_TIM1_CC	43		// TIM1 Capture Compare Interrupt (default weak handler TIM1_CC_IRQHandler)
#define IRQ_TIM2	44		// TIM2 global Interrupt (default weak handler TIM2_IRQHandler)
#define IRQ_TIM3	45		// TIM3 global Interrupt (default weak handler TIM3_IRQHandler)
#define IRQ_TIM4	46		// TIM4 global Interrupt (default weak handler TIM4_IRQHandler)
#define IRQ_I2C1_EV	47		// I2C1 Event Interrupt (default weak handler I2C1_EV_IRQHandler)
#define IRQ_I2C1_ER	48		// I2C1 Error Interrupt (default weak handler I2C1_ER_IRQHandler)
#define IRQ_I2C2_EV	49		// I2C2 Event Interrupt (default weak handler I2C2_EV_IRQHandler)
#define IRQ_I2C2_ER	50		// I2C2 Error Interrupt (default weak handler I2C2_ER_IRQHandler)
#define IRQ_SPI1	51		// SPI1 global Interrupt (default weak handler SPI1_IRQHandler)
#define IRQ_SPI2	52		// SPI2 global Interrupt (default weak handler SPI2_IRQHandler)
#define IRQ_USART1	53		// USART1 global Interrupt (default weak handler USART1_IRQHandler)
#define IRQ_USART2	54		// USART2 global Interrupt (default weak handler USART2_IRQHandler)
#define IRQ_USART3	55		// USART3 global Interrupt (default weak handler USART3_IRQHandler)
#define IRQ_EXTI15_10	56		// External Line[15:10] Interrupts (default weak handler EXTI15_10_IRQHandler)
#define IRQ_RTC_ALARM	57		// RTC Alarm through EXTI Line Interrupt (default weak handler RTCAlarm_IRQHandler)
#define IRQ_LPTIM_WU	58		// LPTIM WakeUp (default weak handler LPTIMWakeUp_IRQHandler)
#define IRQ_USBFS	59		// USBFS global Interrupt (default weak handler USBFS_IRQHandler)
#define IRQ_USBFS_WU	60		// USBFS WakeUp Interrupt (default weak handler USBFSWakeUp_IRQHandler)
#define IRQ_USART4	61		// USART4 global Interrupt (default weak handler USART4_IRQHandler)
#define IRQ_DMA1_CH8	62		// DMA1 Channel 8 global Interrupt (default weak handler DMA1_Channel8_IRQHandler)
#define IRQ_LPTIM	63		// LPTIM global Interrupt (default weak handler LPTIM_IRQHandler)
#define IRQ_OPA		64		// OPA global Interrupt (default weak handler OPA_IRQHandler)
#define IRQ_USBPD	65		// USBPD global Interrupt (default weak handler USBPD_IRQHandler)
#define IRQ_USBPD_WU	67		// USBPD WakeUp Interrupt (default weak handler USBPDWakeUp_IRQHandler)
#define IRQ_CMP_WU	68		// CMP WakeUp Interrupt (default weak handler CMPWakeUp_IRQHandler)

#define IRQ_NUM		69		// number of interrupts

// common interrupt handler definition (need to mark handler function with HANDLER attribute)
typedef void (*irq_handler_t)(void);

// Programmable Fast Interrupt Controller (PFIC) 0xE000E000
typedef struct {
	io32	ISR[8];			// 0x00: (Read Only) Interrupt enable status register
	io32	IPR[8];			// 0x20: (Read Only) Interrupt pending status register
	io32	ITHRESDR;		// 0x40: Interrupt priority threshold configuration register
	io32	res1;			// 0x44: ... reserved
	io32	CFGR;			// 0x48: Interrupt configuration register
	io32	GISR;			// 0x4C: (Read Only) Interrupt global status register
	io8	VTFIDR[4];		// 0x50: VTF ID configuration register
	io32	res2[3];		// 0x54: ... reserved
	io32	VTFADDR[4];		// 0x60: VTF offset address register
	io32	res3[36];		// 0x70: ... reserved
	io32	IENR[8];		// 0x100: (Write Only) Interrupt enable setting register
	io32	res4[24];		// 0x120: ... reserved
	io32	IRER[8];		// 0x180: (Write Only) Interrupt enable clear register
	io32	res5[24];		// 0x1A0: ... reserved
	io32	IPSR[8];		// 0x200: (Write Only) Interrupt pending setting register
	io32	res6[24];		// 0x220: ... reserved
	io32	IPRR[8];		// 0x280: (Write Only) Interrupt pending clear register
	io32	res7[24];		// 0x2A0: ... reserved
	io32	IACTR[8];		// 0x300: (Read Only) Interrupt activation status register
	io32	res8[56];		// 0x320: ... reserved
	io8	IPRIOR[256];		// 0x400: Interrupt priority configuration register
	io32	res9[516];		// 0x500: ... reserved
	io32	SCTLR;			// 0xD10: System control register
} PFIC_t;
STATIC_ASSERT(sizeof(PFIC_t) == 0xD14, "Incorrect PFIC_t!");
#define PFIC		((PFIC_t*)PFIC_BASE)
#define NVIC		PFIC

#define NVIC_KEY1	0xFA050000
#define	NVIC_KEY2	0xBCAF0000
#define	NVIC_KEY3	0xBEEF0000

// IRQ priority
#define IRQ_PRIO_VERYHIGH	0x00	// highest priority - real-time time-critical interrupts
#define IRQ_PRIO_HIGH		0x40	// high priority - SysTick (must have higher priority than normal interrupts)
#define IRQ_PRIO_NORMAL		0x80	// default normal priority - normal code, normal interrupts
#define IRQ_PRIO_LOW		0xc0	// lowest priority - PendSV handler (must have lowest priority)

// External Interrupt/Event Controller 0x40010400
typedef struct {
	io32	INTENR;			// 0x00: Interrupt enable register
	io32	EVENR;			// 0x04: Event enable register
	io32	RTENR;			// 0x08: Rising edge trigger enable register
	io32	FTENR;			// 0x0C: Falling edge trigger enable register
	io32	SWIEVR;			// 0x10: Soft interrupt event register
	io32	INTFR;			// 0x14: Interrupt flag register
} EXTI_t;
STATIC_ASSERT(sizeof(EXTI_t) == 0x18, "Incorrect EXTI_t!");
#define EXTI		((EXTI_t*)EXTI_BASE)

// EXTI line
#define EXTI_LINE0	0		// External interrupt line 0
#define EXTI_LINE1	1		// External interrupt line 1
#define EXTI_LINE2	2		// External interrupt line 2
#define EXTI_LINE3	3		// External interrupt line 3
#define EXTI_LINE4	4		// External interrupt line 4
#define EXTI_LINE5	5		// External interrupt line 5
#define EXTI_LINE6	6		// External interrupt line 6
#define EXTI_LINE7	7		// External interrupt line 7
#define EXTI_LINE8	8		// External interrupt line 8
#define EXTI_LINE9	9		// External interrupt line 9
#define EXTI_LINE10	10		// External interrupt line 10
#define EXTI_LINE11	11		// External interrupt line 11
#define EXTI_LINE12	12		// External interrupt line 12
#define EXTI_LINE13	13		// External interrupt line 13
#define EXTI_LINE14	14		// External interrupt line 14
#define EXTI_LINE15	15		// External interrupt line 15
#define EXTI_LINE16	16		// External interrupt line 16 Connected to the PVD Output
#define EXTI_LINE17	17		// External interrupt line 17 Connected to the RTC Alarm event
#define EXTI_LINE19	19		// External interrupt line 19 Connected to the USBPD Wakeup event
#define EXTI_LINE20	20		// External interrupt line 20 Connected to the USBFS Wakeup event
#define EXTI_LINE21	21		// External interrupt line 21 Connected to the LPTIM Wakeup event
#define EXTI_LINE22	22		// External interrupt line 22 Connected to the COMP Wakeup event

// === NVIC Interrupt Controller

// get address of interrupt vector table
INLINE irq_handler_t* GetVTOR(void) { return (irq_handler_t*)(get_MTVEC() & ~3); } 

// set address of interrupt vector table
INLINE void SetVTOR(irq_handler_t* addr) { cb(); set_MTVEC((u32)addr | 3); cb(); }

// set interrupt IRQ_* service handler
// - Vector table must be located in RAM, or use weak handler otherwise, or use VTF channel.
// - Need to mark handler function with HANDLER attribute.
INLINE void SetHandler(int irq, irq_handler_t handler) { cb(); GetVTOR()[irq] = handler; dmb(); }

// get current interrupt IRQ_* service handler 
INLINE irq_handler_t GetHandler(int irq) { return GetVTOR()[irq]; }

// Enable/Disable interrupt of IRQ_* interrupt
INLINE void NVIC_IRQEnable(int irq) { NVIC->IENR[irq >> 5] = BIT(irq & 0x1f); }
INLINE void NVIC_IRQDisable(int irq) { NVIC->IRER[irq >> 5] = BIT(irq & 0x1f); isb(); }

// Check if IRQ_* interrupt is enabled
INLINE Bool NVIC_IRQIsEnabled(int irq) { return (NVIC->ISR[irq >> 5] & BIT(irq & 0x1f)) != 0; }

// Disable all interrupts
void NVIC_IRQAllDisable(void);

// Force IRQ_* interrupt, set pending
INLINE void NVIC_IRQForce(int irq) { NVIC->IPSR[irq >> 5] = BIT(irq & 0x1f); }

// Clear IRQ_* interrupt pending state
INLINE void NVIC_IRQClear(int irq) { NVIC->IPRR[irq >> 5] = BIT(irq & 0x1f); isb(); }

// Check if IRQ_* interrupt is pending
INLINE Bool NVIC_IRQIsPending(int irq) { return (NVIC->IPR[irq >> 5] & BIT(irq & 0x1f)) != 0; }

// Clear all interrupt pending states
void NVIC_IRQAllClear(void);

// Check if any interrupt is pending
INLINE Bool NVIC_IsPending(void) { return (NVIC->GISR & B9) != 0; }

// Check if IRQ_* interrupt is active (set up by hardware on interrupt handler enter, cleared on leave)
INLINE Bool NVIC_IRQIsActive(int irq) { return (NVIC->IACTR[irq >> 5] & BIT(irq & 0x1f)) != 0; }

// Check if any interrupt is active (executed right now)
INLINE Bool NVIC_IsActive(void) { return (NVIC->GISR & B8) != 0; }

// Set IRQ_* interrupt priority IRQ_PRIO_* (or 0..255, lower numer means higher priority)
INLINE void NVIC_IRQPriority(int irq, int prio) { NVIC->IPRIOR[irq] = prio; }

// Get current nesting status (3:level 2 interrupt, 1:level 1 interrupt, 0:no interrupt)
INLINE u8 NVIC_GetNest(void) { return (u8)NVIC->GISR; }

// Execute WFI command as WFE instruction
INLINE void WFItoWFE(void) { NVIC->SCTLR |= B3; }

// Execute WFI command as WFI instruction
INLINE void WFItoWFI(void) { NVIC->SCTLR &= ~B3; }

// Set/check low power mode Sleep/DeepSleep
INLINE void NVIC_Sleep(void) { NVIC->SCTLR &= ~B2; }
INLINE void NVIC_DeepSleep(void) { NVIC->SCTLR |= B2; }
INLINE Bool NVIC_IsDeepSleep(void) { return (NVIC->SCTLR & B2) != 0; }

// Set low-power mode after leave interrupt
INLINE void NVIC_SleepOnExit(void) { NVIC->SCTLR |= B1; }

// Enter main program after leave interrupt
INLINE void NVIC_MainOnExit(void) { NVIC->SCTLR &= ~B1; }

// Set event - execute WFI command as WFE instruction
void sev(void);

// wait for event
INLINE void wfe(void) { WFItoWFE(); wfi_ins(); }

// wait for event doubled, with set event
INLINE void wfe2(void) { sev(); wfe(); wfe(); }

// wait for interrupt
INLINE void wfi(void) { WFItoWFI(); wfi_ins(); }

// Setup and enable VTF (Vector Table Free), channel 0..3 - set IRQ and handler address (must be two-byte alignment)
// - Need to mark handler function with HANDLER attribute.
void NVIC_VTFEnable(int ch, int irq, irq_handler_t handler);

// Disable VTF (Vector Table Free), channel 0..3
INLINE void NVIC_VTFDisable(int ch) { NVIC->VTFADDR[ch] = 0; }

// System reset
INLINE void SystemReset(void) { NVIC->CFGR = NVIC_KEY3 | B7; }

// === EXTI External Interrupt

// Enable/Disable EXTI line interrupt EXTI_LINE*
INLINE void EXTI_Enable(int line) { EXTI->INTENR |= BIT(line); }
INLINE void EXTI_Disable(int line) { EXTI->INTENR &= ~BIT(line); }

// Check if EXTI line interrupt is enabled EXTI_LINE*
INLINE Bool EXTI_IsEnabled(int line) { return (EXTI->INTENR & BIT(line)) != 0; }

// Enable/Disable EXTI line event EXTI_LINE*
INLINE void EXTI_EventEnable(int line) { EXTI->EVENR |= BIT(line); }
INLINE void EXTI_EventDisable(int line) { EXTI->EVENR &= ~BIT(line); }

// Check if EXTI line event is enabled EXTI_LINE*
INLINE Bool EXTI_EventIsEnabled(int line) { return (EXTI->EVENR & BIT(line)) != 0; }

// Enable/Disable EXTI line rising edge trigger EXTI_LINE*
INLINE void EXTI_RiseEnable(int line) { EXTI->RTENR |= BIT(line); }
INLINE void EXTI_RiseDisable(int line) { EXTI->RTENR &= ~BIT(line); }

// Check if EXTI line rising edge trigger is enabled EXTI_LINE*
INLINE Bool EXTI_RiseIsEnabled(int line) { return (EXTI->RTENR & BIT(line)) != 0; }

// Enable/Disable EXTI line falling edge trigger EXTI_LINE*
INLINE void EXTI_FallEnable(int line) { EXTI->FTENR |= BIT(line); }
INLINE void EXTI_FallDisable(int line) { EXTI->FTENR &= ~BIT(line); }

// Check if EXTI line falling edge trigger is enabled EXTI_LINE*
INLINE Bool EXTI_FallIsEnabled(int line) { return (EXTI->FTENR & BIT(line)) != 0; }

// Force/Unforce EXTI line interrupt EXTI_LINE* (software interrupt, set pending flag)
INLINE void EXTI_Force(int line) { EXTI->SWIEVR |= BIT(line); }
INLINE void EXTI_Unforce(int line) { EXTI->SWIEVR &= ~BIT(line); }

// Check if EXTI line interrupt is forced EXTI_LINE*
INLINE Bool EXTI_IsForced(int line) { return (EXTI->SWIEVR & BIT(line)) != 0; }

// Check if EXTI line interrupt is pending EXTI_LINE*
INLINE Bool EXTI_IsPending(int line) { return (EXTI->INTFR & BIT(line)) != 0; }

// Clear EXTI line pending flag EXTI_LINE*
INLINE void EXTI_Clear(int line) { EXTI->INTFR = BIT(line); }

#ifdef __cplusplus
}
#endif

#endif // _SDK_IRQ_H

#endif // USE_IRQ
