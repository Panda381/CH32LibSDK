;/********************************** (C) COPYRIGHT *******************************
;* File Name          : startup_ch32x035.s
;* Author             : WCH
;* Version            : V1.0.1
;* Date               : 2023/12/06
;* Description        : vector table for eclipse toolchain.
;*********************************************************************************
;* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
;* Attention: This software (modified or not) and binary are used for 
;* microcontroller manufactured by Nanjing Qinheng Microelectronics.
;*******************************************************************************/

#define BOOTLOADER_SIZE	0x5000	// size of boot loader (20 KB; must be multiply of sector size 512 B)
#define APPINFO_OFF	0xDC	// application info header offset

	.section	.init, "ax", @progbits

// ---- Initialize - vector table and reset handler

	.option	push		// push current linker setup
	.option	norvc		// disable compressed instructions in vector table (use 32-bit jumps)
	.option	norelax		// disable linker relaxation (disable optimizing programs at link-time)
	.align	2

.global _start
_start:
_vector_base:
	// CPU Internal Interrupts
	j	handle_reset		// 0: RESET handler
	.word	0			// 1:
	.word	NMI_Handler		// 2: NMI Handler, Non Naskable interrupt (IRQ_NMI)
	.word	HardFault_Handler	// 3: Hard Fault Handler, Exception interrupt (IRQ_HARDFAULT)
	.word	0			// 4:
	.word	Ecall_M_Mode_Handler	// 5: Ecall M Mode Interrupt (IRQ_ECALL_MMODE)
	.word	0			// 6:
	.word	0			// 7:
	.word	Ecall_U_Mode_Handler	// 8: Ecall U Mode Interrupt (IRQ_ECALL_UMODE)
	.word	Break_Point_Handler	// 9: Break Point Interrupt (IRQ_BREAKPOINT)
	.word	0			// 10:
	.word	0			// 11:
	.word	SysTick_Handler		// 12: SysTick Handler, System Timer interrupt (IRQ_SYSTICK)
	.word	0			// 13:
	.word	SW_Handler		// 14: SW Handler, software interrupt (IRQ_SW)
	.word	0			// 15:
	// External Interrupts
	.word	WWDG_IRQHandler		// 16: Window Watchdog, Window WatchDog interrupt (IRQ_WWDG)
	.word	PVD_IRQHandler		// 17: PVD through EXTI Line detection interrupt, Supply voltage detection interrupt (IRQ_PVD)
	.word	FLASH_IRQHandler	// 18: Flash global interrupt (IRQ_FLASH)
	.word	0			// 19:
	.word	EXTI7_0_IRQHandler	// 20: EXTI Line 7..0, External line 7..0 interrupts (IRQ_EXTI7)
	.word	AWU_IRQHandler		// 21: AWU, Automate WakeUp interrupt (IRQ_AWU)
	.word	DMA1_Channel1_IRQHandler // 22: DMA1 Channel 1 global interrupt (IRQ_DMA1_CH1)
	.word	DMA1_Channel2_IRQHandler // 23: DMA1 Channel 2 global interrupt (IRQ_DMA1_CH2)
	.word	DMA1_Channel3_IRQHandler // 24: DMA1 Channel 3 global interrupt (IRQ_DMA1_CH3)
	.word	DMA1_Channel4_IRQHandler // 25: DMA1 Channel 4 global interrupt (IRQ_DMA1_CH4)
	.word	DMA1_Channel5_IRQHandler // 26: DMA1 Channel 5 global interrupt (IRQ_DMA1_CH5)
	.word	DMA1_Channel6_IRQHandler // 27: DMA1 Channel 6 global interrupt (IRQ_DMA1_CH6)
	.word	DMA1_Channel7_IRQHandler // 28: DMA1 Channel 7 global interrupt (IRQ_DMA1_CH7)
	.word	ADC1_IRQHandler		// 29: ADC1 global interrupt (IRQ_ADC1)
	.word	I2C1_EV_IRQHandler	// 30: I2C1 Event interrupt (IRQ_I2C1_EV)
	.word	I2C1_ER_IRQHandler	// 31: I2C1 Error interrupt (IRQ_I2C1_ER)
	.word	USART1_IRQHandler	// 32: USART1 global interrupt (IRQ_USART1)
	.word	SPI1_IRQHandler		// 33: SPI1 global interrupt (IRQ_SPI1)
	.word	TIM1_BRK_IRQHandler	// 34: TIM1 Break interrupt (IRQ_TIM1_BRK)
	.word	TIM1_UP_IRQHandler	// 35: TIM1 Update interrupt (IRQ_TIM1_UP)
	.word	TIM1_TRG_COM_IRQHandler	// 36: TIM1 Trigger and Commutation interrupt (IRQ_TIM1_TRG)
	.word	TIM1_CC_IRQHandler	// 37: TIM1 Capture Compare interrupt (IRQ_TIM1_CC)
	.word	TIM2_UP_IRQHandler	// 38: TIM2 Update interrupt (IRQ_TIM2_UP)
	.word	USART2_IRQHandler	// 39: USART2 global Interrupt (IRQ_USART2)
	.word	EXTI15_8_IRQHandler	// 40: External Line[15:8] Interrupts (IRQ_EXTI15_8)
	.word	EXTI25_16_IRQHandler	// 41: External Line[25:16] Interrupts (IRQ_EXTI25_16)
	.word	USART3_IRQHandler	// 42: USART3 global Interrupt (IRQ_USART3)
	.word	USART4_IRQHandler	// 43: USART4 global Interrupt (IRQ_USART4)
	.word	DMA1_Channel8_IRQHandler // 44: DMA1 Channel 8 global Interrupt (IRQ_DMA1_CH8)
	.word	USBFS_IRQHandler	// 45: USBFS Host/Device global Interrupt (IRQ_USBFS)
	.word	USBFSWakeUp_IRQHandler	// 46: USBFS Host/Device WakeUp Interrupt (IRQ_USBFS_WU)
	.word	PIOC_IRQHandler		// 47: PIOC global Interrupt (IRQ_PIOC)
	.word	OPA_IRQHandler		// 48: OPA global Interrupt (IRQ_OPA)
	.word	USBPD_IRQHandler	// 49: USBPD global Interrupt (IRQ_USBPD)
	.word	USBPDWakeUp_IRQHandler	// 50: USBPD WakeUp Interrupt (IRQ_USBPD_WU)
	.word	TIM2_CC_IRQHandler	// 51: TIM2 Capture Compare Interrupt (IRQ_TIM2_CC)
	.word	TIM2_TRG_COM_IRQHandler	// 52: TIM2 Trigger and Commutation Interrupt (IRQ_TIM2_TRG)
	.word	TIM2_BRK_IRQHandler	// 53: TIM2 Break Interrupt (IRQ_TIM2_BRK)
	.word	TIM3_IRQHandler		// 54: TIM3 global Interrupt (IRQ_TIM3)

	.option	pop			// pop original linker setup

#if !REDUCE_CRT0_SIZE

// ---- Application info header (start at offset 55*4 = 220 = 0xDC, header size 0x18 bytes) - see sdk_runtime.*

	.align	2

.global AppInfoHeader
AppInfoHeader:
	.ascii	"INFO"		// 0x00: magic 1
	.word	0x01234567	// 0x04: application length of data after "AppInfoHeader_StartCRC" label
	.hword	0x89AB		// 0x08: application CRC of data after "AppInfoHeader_StartCRC" label ... CRC-16 CCITT (CRC16C, use Crc16CFast() with INIT=0x1D0F)
	.ascii	"3X"		// 0x0A: MCU serie identifier (CH32X03x)
				//		"03" = CH32V003
				//		"0X" = CH32V00x
				//		"3X" = CH32X03x
				//		"V1" = CH32V103
				//		"L1" = CH32L103
				//		"V2" = CH32V2xx
				//		"V3" = CH32V3xx
				//		"V4" = CH32V4xx

.global AppInfoHeader_StartCRC
AppInfoHeader_StartCRC:		// 0x0C: start calculatin CRC ... CRC-16 CCITT (CRC16C, use Crc16CFast() with INIT=0x1D0F)

	.word	_eusrstack	// 0x0C: end of user stack, to setup SP register
	.word	handle_reset	// 0x10: start address, to jump to application
	.ascii	"info"		// 0x14: magic 2

#endif // !REDUCE_CRT0_SIZE

// ---- Weak handlers

	.align	2

.macro weak_irq name
.weak \name
.type \name,%function
\name:
.endm
	weak_irq	NMI_Handler		// 2: NMI Handler, Non Naskable interrupt (IRQ_NMI)
	weak_irq	HardFault_Handler	// 3: Hard Fault Handler, Exception interrupt (IRQ_HARDFAULT)
	weak_irq	Ecall_M_Mode_Handler	// 5: Ecall M Mode Interrupt (IRQ_ECALL_MMODE)
	weak_irq	Ecall_U_Mode_Handler	// 8: Ecall U Mode Interrupt (IRQ_ECALL_UMODE)
	weak_irq	Break_Point_Handler	// 9: Break Point Interrupt (IRQ_BREAKPOINT)
	weak_irq	SysTick_Handler		// 12: SysTick Handler, System Timer interrupt (IRQ_SYSTICK)
	weak_irq	SW_Handler		// 14: SW Handler, software interrupt (IRQ_SW)
	weak_irq	WWDG_IRQHandler		// 16: Window Watchdog, Window WatchDog interrupt (IRQ_WWDG)
	weak_irq	PVD_IRQHandler		// 17: PVD through EXTI Line detection interrupt, Supply voltage detection interrupt (IRQ_PVD)
	weak_irq	FLASH_IRQHandler	// 18: Flash global interrupt (IRQ_FLASH)
	weak_irq	EXTI7_0_IRQHandler	// 20: EXTI Line 7..0, External line 7..0 interrupts (IRQ_EXTI7)
	weak_irq	AWU_IRQHandler		// 21: AWU, Automate WakeUp interrupt (IRQ_AWU)
	weak_irq	DMA1_Channel1_IRQHandler // 22: DMA1 Channel 1 global interrupt (IRQ_DMA1_CH1)
	weak_irq	DMA1_Channel2_IRQHandler // 23: DMA1 Channel 2 global interrupt (IRQ_DMA1_CH2)
	weak_irq	DMA1_Channel3_IRQHandler // 24: DMA1 Channel 3 global interrupt (IRQ_DMA1_CH3)
	weak_irq	DMA1_Channel4_IRQHandler // 25: DMA1 Channel 4 global interrupt (IRQ_DMA1_CH4)
	weak_irq	DMA1_Channel5_IRQHandler // 26: DMA1 Channel 5 global interrupt (IRQ_DMA1_CH5)
	weak_irq	DMA1_Channel6_IRQHandler // 27: DMA1 Channel 6 global interrupt (IRQ_DMA1_CH6)
	weak_irq	DMA1_Channel7_IRQHandler // 28: DMA1 Channel 7 global interrupt (IRQ_DMA1_CH7)
	weak_irq	ADC1_IRQHandler		// 29: ADC1 global interrupt (IRQ_ADC1)
	weak_irq	I2C1_EV_IRQHandler	// 30: I2C1 Event interrupt (IRQ_I2C1_EV)
	weak_irq	I2C1_ER_IRQHandler	// 31: I2C1 Error interrupt (IRQ_I2C1_ER)
	weak_irq	USART1_IRQHandler	// 32: USART1 global interrupt (IRQ_USART1)
	weak_irq	SPI1_IRQHandler		// 33: SPI1 global interrupt (IRQ_SPI1)
	weak_irq	TIM1_BRK_IRQHandler	// 34: TIM1 Break interrupt (IRQ_TIM1_BRK)
	weak_irq	TIM1_UP_IRQHandler	// 35: TIM1 Update interrupt (IRQ_TIM1_UP)
	weak_irq	TIM1_TRG_COM_IRQHandler	// 36: TIM1 Trigger and Commutation interrupt (IRQ_TIM1_TRG)
	weak_irq	TIM1_CC_IRQHandler	// 37: TIM1 Capture Compare interrupt (IRQ_TIM1_CC)
	weak_irq	TIM2_UP_IRQHandler	// 38: TIM2 Update interrupt (IRQ_TIM2_UP)
	weak_irq	USART2_IRQHandler	// 39: USART2 global Interrupt (IRQ_USART2)
	weak_irq	EXTI15_8_IRQHandler	// 40: External Line[15:8] Interrupts (IRQ_EXTI15_8)
	weak_irq	EXTI25_16_IRQHandler	// 41: External Line[25:16] Interrupts (IRQ_EXTI25_16)
	weak_irq	USART3_IRQHandler	// 42: USART3 global Interrupt (IRQ_USART3)
	weak_irq	USART4_IRQHandler	// 43: USART4 global Interrupt (IRQ_USART4)
	weak_irq	DMA1_Channel8_IRQHandler // 44: DMA1 Channel 8 global Interrupt (IRQ_DMA1_CH8)
	weak_irq	USBFS_IRQHandler	// 45: USBFS Host/Device global Interrupt (IRQ_USBFS)
	weak_irq	USBFSWakeUp_IRQHandler	// 46: USBFS Host/Device WakeUp Interrupt (IRQ_USBFS_WU)
	weak_irq	PIOC_IRQHandler		// 47: PIOC global Interrupt (IRQ_PIOC)
	weak_irq	OPA_IRQHandler		// 48: OPA global Interrupt (IRQ_OPA)
	weak_irq	USBPD_IRQHandler	// 49: USBPD global Interrupt (IRQ_USBPD)
	weak_irq	USBPDWakeUp_IRQHandler	// 50: USBPD WakeUp Interrupt (IRQ_USBPD_WU)
	weak_irq	TIM2_CC_IRQHandler	// 51: TIM2 Capture Compare Interrupt (IRQ_TIM2_CC)
	weak_irq	TIM2_TRG_COM_IRQHandler	// 52: TIM2 Trigger and Commutation Interrupt (IRQ_TIM2_TRG)
	weak_irq	TIM2_BRK_IRQHandler	// 53: TIM2 Break Interrupt (IRQ_TIM2_BRK)
	weak_irq	TIM3_IRQHandler		// 54: TIM3 global Interrupt (IRQ_TIM3)

	weak_irq	DefaultHandler		// default handler
1:	j	1b

// ---- Reset handler

	.align	2

.type handle_reset,%function
handle_reset:

	// setup global pointer
	.option	push			// push current linker setup
	.option	norelax			// disable linker relaxation (disable optimizing programs at link-time)
	la	gp,__global_pointer$	// global pointer to global data in RAM
	.option	pop			// pop original linker setup

	// setup stack pointer
	la	sp,_eusrstack		// SP <- end of user stack

	// Load data section from flash to RAM
	la	a0,_data_lma		// A0 <- load memory address of initialized data in Flash (source address)
	la	a1,_data_vma		// A1 <- virtual memory address of initialized data in RAM (destination address)
	la	a2,_edata		// A2 <- end of initialized data in RAM
	bgeu	a1,a2,2f		// skip if no data to copy

1:	lw	t0,(a0)			// T0 <- load data as 32-bit word from Flash
	sw	t0,(a1)			// save data to RAM
	addi	a0,a0,4			// A0 <- shift source address
	addi	a1,a1,4			// A1 <- shift destination address
	bltu	a1,a2,1b		// copy next word

	// Clear bss section
2:	la	a0,_sbss		// A0 <- start of bss section
	la	a1,_ebss		// A1 <- end of bss section
	bgeu	a0,a1,2f		// skip if no bss section

1:	sw	zero,(a0)		// store 0 to (a0)
	addi	a0,a0,4			// A0 <- shift destination addres
	bltu	a0,a1,1b		// continue with next data

	// Configure pipelining and instruction prediction
2:	li	t0,0x1f
	csrw	0xbc0,t0

	// Enable interrupt nesting and hardware stack
	li	t0,0x3
	csrw	0x804,t0

	// Enable global interrupt and configure privileged mode
   	li	t0,0x88           
   	csrw	mstatus,t0

	// Configure the interrupt vector table recognition mode and entry address mode
	la	t0,_vector_base		// T0 <- start of vector table
	ori	t0,t0,3			// set vector mode
	csrw	mtvec,t0		// set vector table

	// System initialize  
	jal	SystemInit

	// jump to main function
	la	t0,main			// T0 <- pointer to main function
	csrw	mepc,t0			// setup machine exception address
	mret				// jump to main function

// ==== Run application
// Called from boot3 loader

	.align	2

#if !REDUCE_CRT0_SIZE

// run application from Flash
.type GoToApp,%function
.global GoToApp
GoToApp:
	lui	a0,%hi(0x08000000 + BOOTLOADER_SIZE) // vector table of application -> A0
	addi	a0,a0,3				// set vector mode
	csrw	mtvec,a0			// setup vector address register MTVEC, using vector mode

	lw	a1,APPINFO_OFF+0x0C-3(a0)	// A1 <- load start stack
	lw	a0,APPINFO_OFF+0x10-3(a0)	// A0 <- load start address
	mv	sp,a1				// set stack pointer
	jr	a0				// run application code

#endif // !REDUCE_CRT0_SIZE
