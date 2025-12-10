
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

#define BABYBEAT	1	// 1 = use BabyBeat device
//#define BEATLEBEAT	1	// 1 = use BeatleBeat device

#if BABYBEAT		// 1 = use BabyBeat device
#define SYSTICK_KEYSCAN	1	// 1=call KeyScan() function from SysTick system timer
#else
#define SYSTICK_KEYSCAN	0	// 1=call KeyScan() function from SysTick system timer
#endif

// ----------------------------------------------------------------------------
//                            Clock Setup
// ----------------------------------------------------------------------------

// frequency of HSI internal oscillator 48MHz
#define HSI_VALUE	24000000

// System clock source: 1=HSI, 2=HSE, 3=HSE_Bypass, 4=PLL_HSI, 5=PLL_HSE, 6=PLL_HSE_Bypass, 7=PLL_HSI/2, 8=PLL_HSE/2, 9=PLL_HSE_Bypass/2
#define SYSCLK_SRC	4

// PLL multiplier
#define PLLCLK_MUL	2		// only *2 supported; 24 MHz * 2 = 48 MHz

// System clock divider: 1, 2, 3, 4, 5, 6, 7, 8, 16, 32, 64, 128, 256 (default 1)
#define SYSCLK_DIV	1

// ADC clock divider: (1,) 2, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128 (default 1 or 2)
#define ADCCLK_DIV	8		// CH32V0: max. 24 MHz (48 / 8 = 6 MHz)

// number of HCLK clock cycles per 1 us (used with Wait functions)
// - If you want to change frequency of system clock run-time, use a variable instead of constant.
#define HCLK_PER_US	48

// increment of system time in [ms] on SysTick interrupt (0=do not use SysTick interrupt)
#if BABYBEAT		// 1 = use BabyBeat device
#define SYSTICK_MS	20
#else
#define SYSTICK_MS	0
#endif

// ----------------------------------------------------------------------------
//                          Peripheral clock enable
// ----------------------------------------------------------------------------

#define ENABLE_SRAM	1		// SRAM enable
#define ENABLE_FLASH	0		// FLASH enable
#define ENABLE_WWDG	0		// Window watchdog enable
#define ENABLE_PWR	1		// Power module enable
#define ENABLE_AFI	1		// I/O auxiliary function enable
#define ENABLE_PA	1		// PA port enable
#define ENABLE_PB	0		// PB port enable
#define ENABLE_PC	1		// PC port enable
#define ENABLE_PD	1		// PD port enable
#define ENABLE_ADC1	0		// ADC1 module enable
#define ENABLE_TIM1	1		// TIM1 module enable
#define ENABLE_TIM2	0		// TIM2 module enable
#define ENABLE_TIM3	0		// TIM3 module enable
#define ENABLE_SPI1	0		// SPI1 module enable
#define ENABLE_USART1	0		// USART1 module enable
#define ENABLE_I2C1	0		// I2C1 module enable
#define ENABLE_DMA1	0		// DMA1 module enable

// ----------------------------------------------------------------------------
//                            Library modules
// ----------------------------------------------------------------------------

#define USE_CRC		0	// 1=use CRC library
#define USE_DECNUM	0	// 1=use decode number
#define USE_FAT		1	// 1=use FAT filesystem
#define USE_RAND	0	// 1=use random number generator

// SD card
#if BABYBEAT		// 1 = use BabyBeat device
// Note: cannot use hardware SPI at this CPU, mappings 3 and 4 are not working.
#define SD_CS_GPIO	PA1	// CS output to SD card
#define SD_CLK_GPIO	PD4	// CLK output to SD card
#define SD_MISO_GPIO	PD5	// MISO input from SD card
#define SD_MOSI_GPIO	PD6	// MOSI output to SD card
#else // BABYBEAT
// SD card
#define SD_CS_GPIO	PC4	// CS output to SD card
#define SD_CLK_GPIO	PC2	// CLK output to SD card
#define SD_MISO_GPIO	PC1	// MISO input from SD card
#define SD_MOSI_GPIO	PD1	// MOSI output to SD card
#endif // BABYBEAT
#define USE_SD		3	// use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
#define SD_SPEED_INIT	(HCLK_PER_US*2)	// SD speed on init: wait delay "HCLK_PER_US*2" = 250 kbps
#define SD_SPEED_READ	3	// (working value 0..3) SD speed on read: wait delay "HCLK_PER_US/8" = 4 Mbps
#define SD_SPEED_WRITE	(HCLK_PER_US/2)	// SD speed on write: wait delay "HCLK_PER_US/2" = 1 Mbps

// ----------------------------------------------------------------------------
//                             SDK modules
// ----------------------------------------------------------------------------

#define USE_ADC		0	// 1=use ADC peripheral
#define USE_DMA		0	// 1=use DMA peripheral
#define USE_FLASH	0	// 1=use Flash programming
#define USE_I2C		0	// 1=use I2C peripheral
#define USE_IRQ		1	// 1=use IRQ interrupt support
#define USE_PWR		1	// 1=use power control
#define USE_SPI		0	// 1=use SPI peripheral
#define USE_TIM		1	// 1=use timers
#define USE_USART	0	// 1=use USART peripheral

#endif // _CONFIG_H
