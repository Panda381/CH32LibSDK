
// ****************************************************************************
//
//                        Peripheral memory map
//
// ****************************************************************************
// Included from both C and assembly.

#ifndef _SDK_ADDRESSMAP_H
#define _SDK_ADDRESSMAP_H

#define	FLASH_BASE		0x08000000	// FLASH base address in the alias region
#define	SRAM_BASE		0x20000000	// SRAM base address in the alias region
#define	PERIPH_BASE		0x40000000	// Peripheral base address in the alias region

#define APB1PERIPH_BASE		PERIPH_BASE			// 0x40000000
#define APB2PERIPH_BASE		(PERIPH_BASE + 0x10000)		// 0x40010000
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x20000)		// 0x40020000

#define TIM2_BASE		(APB1PERIPH_BASE + 0x0000)	// TIM2 0x40000000
#define TIM3_BASE		(APB1PERIPH_BASE + 0x0400)	// TIM3 0x40000400
#define WWDG_BASE		(APB1PERIPH_BASE + 0x2C00)	// WWDG 0x40002C00
#define IWDG_BASE		(APB1PERIPH_BASE + 0x3000)	// IWDG 0x40003000
#define USART2_BASE		(APB1PERIPH_BASE + 0x4400)	// USART2 0x40004400
#define USART3_BASE		(APB1PERIPH_BASE + 0x4800)	// USART3 0x40004800
#define USART4_BASE		(APB1PERIPH_BASE + 0x4C00)	// USART4 0x40004C00
#define I2C1_BASE		(APB1PERIPH_BASE + 0x5400)	// I2C 0x40005400
#define PWR_BASE		(APB1PERIPH_BASE + 0x7000)	// Power control 0x40007000

#define AFIO_BASE		(APB2PERIPH_BASE + 0x0000)	// alternative function select 0x40010000
#define EXTI_BASE		(APB2PERIPH_BASE + 0x0400)	// EXTI external interrupt registers 0x40010400
#define GPIOA_BASE		(APB2PERIPH_BASE + 0x0800)	// PA port 0x40010800
#define GPIOB_BASE		(APB2PERIPH_BASE + 0x0C00)	// PB port 0x40010C00
#define GPIOC_BASE		(APB2PERIPH_BASE + 0x1000)	// PC port 0x40011000
#define ADC1_BASE		(APB2PERIPH_BASE + 0x2400)	// ADC1 0x40012400
#define TIM1_BASE		(APB2PERIPH_BASE + 0x2C00)	// TIM1 0x40012C00
#define SPI1_BASE		(APB2PERIPH_BASE + 0x3000)	// SPI1 0x40013000
#define USART1_BASE		(APB2PERIPH_BASE + 0x3800)	// USART1 0x40013800

#define DMA1_BASE		(AHBPERIPH_BASE + 0x0000)	// DMA1 0x40020000
#define DMA1_Channel1_BASE	(AHBPERIPH_BASE + 0x0008)	// DMA1 channel 1 0x40020008
#define DMA1_Channel2_BASE	(AHBPERIPH_BASE + 0x001C)	// DMA1 channel 2 0x4002001C
#define DMA1_Channel3_BASE	(AHBPERIPH_BASE + 0x0030)	// DMA1 channel 3 0x40020030
#define DMA1_Channel4_BASE	(AHBPERIPH_BASE + 0x0044)	// DMA1 channel 4 0x40020044
#define DMA1_Channel5_BASE	(AHBPERIPH_BASE + 0x0058)	// DMA1 channel 5 0x40020058
#define DMA1_Channel6_BASE	(AHBPERIPH_BASE + 0x006C)	// DMA1 channel 6 0x4002006C
#define DMA1_Channel7_BASE	(AHBPERIPH_BASE + 0x0080)	// DMA1 channel 7 0x40020080
#define DMA1_Channel8_BASE	(AHBPERIPH_BASE + 0x0094)	// DMA1 channel 8 0x40020094
#define RCC_BASE		(AHBPERIPH_BASE + 0x1000)	// Reset and clock control 0x40021000
#define FLASH_R_BASE		(AHBPERIPH_BASE + 0x2000)	// Flash registers base address 0x40022000
#define USBFS_BASE		(AHBPERIPH_BASE + 0x3400)
#define OPA_BASE		(AHBPERIPH_BASE + 0x6000)
#define AWU_BASE		(AHBPERIPH_BASE + 0x6400)	// Auto-wakeup 0x40026400
#define PIOC_BASE		(AHBPERIPH_BASE + 0x6C00)
#define USBPD_BASE		(AHBPERIPH_BASE + 0x7000)

#define OB_BASE			0x1FFFF800			// Flash Option Bytes base address
#define PFIC_BASE		0xE000E000			// Programmable Fast Interrupt Controller (PFIC)
#define SYSTICK_BASE		0xE000F000			// SysTick System counter

#endif // _SDK_ADDRESSMAP_H
