
// ****************************************************************************
//                                 
//                        Project library configuration
//
// ****************************************************************************

#ifndef _CONFIG_H
#define _CONFIG_H

// Pre-set defines (use #if to check):
//	target MCU	MCU serie	MCU class	MCU subclass
//	CH32V002x4	CH32V002	CH32V0		CH32V00X
//	CH32V003x4	CH32V003	CH32V0
//	CH32V004x6	CH32V004	CH32V0		CH32V00X
//	CH32V005x6	CH32V005	CH32V0		CH32V00X
//	CH32V006x4	CH32V006	CH32V0		CH32V00X
//	CH32V006x8	CH32V006	CH32V0		CH32V00X
//	CH32V007x8	CH32V007	CH32V0		CH32V00X
//	CH32X033x8	CH32V033	CH32V0		CH32V03X
//	CH32X035x7	CH32V035	CH32V0		CH32V03X
//	CH32X035x8	CH32V035	CH32V0		CH32V03X
//	CH32V103x6	CH32V103	CH32V1
//	CH32V103x8	CH32V103	CH32V1
//	CH32L103x8	CH32L103	CH32V1

// FLASHSIZE ... Flash size in bytes
// RAMSIZE ... RAM size in bytes
// STACKSIZE ... Stack size in bytes

// default font
#define FONT		FontBold8x8	// default system font
#define FONTCOND	FontCond6x8	// default condensed font

// Videomodes (9 colors: 1 black background + 8 foreground colors):
// 	1 ... graphics mode 128x64 pixels mono with color attributes 1x1 pixel, required memory 1024+4096 = 5120 B
// 	2 ... graphics mode 160x120 pixels mono with color attributes 4x4 pixels, required memory 2400+600 = 3000 B (driver size 540 B in RAM)
// 	3 ... graphics mode 160x120 pixels mono with color attributes 2x2 pixels, required memory 2400+2400 = 4800 B (driver size 532 B in RAM)
// 	4 ... graphics mode 256x192 pixels mono with color attributes 8x8 pixels, required memory 6144+384 = 6528 B (driver size 516 B in RAM)
// 	5 ... text mode 32x24 characters of 8x8 pixels with ZX-80/ZX-81 font of 64 characters in Flash, with color attributes, required memory 768+384 = 1152 B
// 	6 ... text mode 40x30 characters of 8x8 pixels (resolution 320x240 pixels, pseudographics 80x60 pixels) with color attributes, font 2048 B in Flash, required memory 1200+600=1800 B
// 	7 ... text mode 80x30 characters of 8x8 pixels (resolution 640x240 pixels, pseudographics 160x60 pixels) with color attributes, font 2048 B in RAM FontBuf, required memory 2400+1200+2048=5648 B (driver size 504 B in RAM)
#define VMODE	6

// ----------------------------------------------------------------------------
//                            Clock Setup
// ----------------------------------------------------------------------------

// frequency of HSI internal oscillator 24MHz
//#define HSI_VALUE	25000000

// Frequency of HSE external oscillator
//#define HSE_VALUE	25000000	// CH32V0, CH32L103: 4..25 MHz

// System clock source: 1=HSI, 2=HSE, 3=HSE_Bypass, 4=PLL_HSI, 5=PLL_HSE, 6=PLL_HSE_Bypass, 7=PLL_HSI/2, 8=PLL_HSE/2, 9=PLL_HSE_Bypass/2
//#define SYSCLK_SRC	6

// PLL multiplier
//#define PLLCLK_MUL	2		// only *2 supported; 24 MHz * 2 = 48 MHz

// System clock divider: 1, 2, 3, 4, 5, 6, 7, 8, 16, 32, 64, 128, 256 (default 1)
//#define SYSCLK_DIV	1

// ADC clock divider: (1,) 2, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128 (default 1 or 2)
//#define ADCCLK_DIV	1		// CH32V0: max. 24 MHz (48 / 2 = 24 MHz)

// number of HCLK clock cycles per 1 us (used with Wait functions)
// - If you want to change frequency of system clock run-time, use a variable instead of constant.
//#define HCLK_PER_US	50

// increment of system time in [ms] on SysTick interrupt (0=do not use SysTick interrupt)
//#define SYSTICK_MS	0

// ----------------------------------------------------------------------------
//                          Peripheral clock enable
// ----------------------------------------------------------------------------

// System
#define ENABLE_SRAM	1		// SRAM enable
#define ENABLE_FLASH	1		// FLASH enable
#define ENABLE_WWDG	0		// Window watchdog enable
#define ENABLE_PWR	1		// Power module enable
#define ENABLE_CRC	0		// CRC module enable
#define ENABLE_BKP	0		// Backup module enable
#define ENABLE_FSMC	0		// FSMC module enable
#define ENABLE_RNG	0		// RNG module enable
#define ENABLE_SDIO	0		// SDIO module enable
#define ENABLE_DVP	0		// DVP module enable
#define ENABLE_BLEC	0		// BLEC module enable
#define ENABLE_BLES	0		// BLES module enable
// Ports
#define ENABLE_AFI	1		// I/O auxiliary function enable
#define ENABLE_PA	1		// PA port enable
#define ENABLE_PB	1		// PB port enable
#define ENABLE_PC	1		// PC port enable
#define ENABLE_PD	1		// PD port enable
#define ENABLE_PE	0		// PE port enable
// ADC
#define ENABLE_ADC1	0		// ADC1 module enable
#define ENABLE_ADC2	0		// ADC2 module enable
// DAC
#define ENABLE_DAC	0		// DAC module enable
// Timers
#define ENABLE_TIM1	1		// TIM1 module enable
#define ENABLE_TIM2	1		// TIM2 module enable
#define ENABLE_TIM3	0		// TIM3 module enable
#define ENABLE_TIM4	0		// TIM4 module enable
#define ENABLE_TIM5	0		// TIM5 module enable
#define ENABLE_TIM6	0		// TIM6 module enable
#define ENABLE_TIM7	0		// TIM7 module enable
#define ENABLE_TIM8	0		// TIM8 module enable
#define ENABLE_TIM9	0		// TIM9 module enable
#define ENABLE_TIM10	0		// TIM10 module enable
#define ENABLE_LPTIM	0		// LPTIM module enable
// SPI
#define ENABLE_SPI1	1		// SPI1 module enable
#define ENABLE_SPI2	0		// SPI2 module enable
// USART
#define ENABLE_USART1	1		// USART1 module enable
#define ENABLE_USART2	1		// USART2 module enable
#define ENABLE_USART3	0		// USART3 module enable
#define ENABLE_USART4	0		// USART4 module enable
#define ENABLE_USART5	0		// USART5 module enable
#define ENABLE_USART6	0		// USART6 module enable
#define ENABLE_USART7	0		// USART7 module enable
#define ENABLE_USART8	0		// USART8 module enable
// I2C
#define ENABLE_I2C1	0		// I2C1 module enable
#define ENABLE_I2C2	0		// I2C2 module enable
// CAN
#define ENABLE_CAN1	0		// CAN1 module enable
#define ENABLE_CAN2	0		// CAN2 module enable
// DMA
#define ENABLE_DMA1	0		// DMA1 module enable
#define ENABLE_DMA2	0		// DMA2 module enable
// USB
#define ENABLE_USBFS	0		// USBFS module enable
#define ENABLE_USBPD	0		// USBPD module enable
#define ENABLE_USBD	0		// USBD module enable
#define ENABLE_USBHS	0		// USBHS module enable
#define ENABLE_USBOTG	0		// USBOTG module enable
// Ethernet
#define ENABLE_ETHMAC	0		// ETHMAC module enable
#define ENABLE_ETHMACTX	0		// ETHMACTX module enable
#define ENABLE_ETHMACRX	0		// ETHMACRX module enable

// ----------------------------------------------------------------------------
//                             SDK modules
// ----------------------------------------------------------------------------

#define USE_ADC		0	// 1=use ADC peripheral
#define USE_DMA		0	// 1=use DMA peripheral
#define USE_FLASH	1	// 1=use Flash programming
#define USE_I2C		1	// 1=use I2C peripheral
#define USE_IRQ		1	// 1=use IRQ interrupt support
#define USE_PWR		1	// 1=use power control
#define USE_SPI		1	// 1=use SPI peripheral
#define USE_TIM		1	// 1=use timers
#define USE_USART	1	// 1=use USART peripheral

// ----------------------------------------------------------------------------
//                            Library modules
// ----------------------------------------------------------------------------

#define USE_CRC		1	// 1=use CRC library
#define USE_DECNUM	1	// 1=use decode number
#define USE_FAT		1	// 1=use FAT filesystem
#define USE_RAND	1	// 1=use random number generator
#define USE_SD		1	// 1=use SD card driver

// ----------------------------------------------------------------------------
//                             Device setup
// ----------------------------------------------------------------------------

#define USE_DRAW	0	// 1=use graphics drawing functions
#define USE_PRINT	1	// 1=use text printing functions
#define USE_KEY		1	// 1=use keyboard support
#define USE_SOUND	0	// 1=use sound support
#define USE_DISP	1	// 1=use display support
#define KEYCNT_REL	4	// keyboard counter - release interval in 1/60 sec
#define KEYCNT_PRESS	20	// keyboard counter - first repeat in 1/60 sec
#define KEYCNT_REPEAT	6	// keyboard counter - next repeat in 1/60 sec

#endif // _CONFIG_H
