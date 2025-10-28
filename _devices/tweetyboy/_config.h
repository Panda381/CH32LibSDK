
#define BOOTLOADER_SIZE	0x5000	// size of boot loader (20 KB; must be multiply of sector size 512 B)

// ----------------------------------------------------------------------------
//                             Device setup
// ----------------------------------------------------------------------------

// SPI display
// 0 ... PA4:CS, PA5:SCK, PA6:MISO, PA7:MOSI
// void GPIO_Remap_SPI1(int map);
#define DISP_SCK_GPIO	PA5	// SCK output to SPI display
#define DISP_MOSI_GPIO	PA7	// MOSI output to SPI display
#define DISP_RES_GPIO	PA12	// RES output to SPI display
#define DISP_DC_GPIO	PA13	// DC output to SPI display
#define DISP_CS_GPIO	PA4	// CS output to SPI display
#define DISP_BLK_GPIO	PB4	// BLK output to SPI display
#define DISP_SPI_MAP	0	// hardware display driver: display SPI mapping
#define DISP_SPI_DIV	1	// hardware display driver: display SPI baud divider 0..7 (means div=2..256)
#define DISP_SPEED	2	// software display driver: wait delay
#define DISP_GAMMA	2	// select display gamma curve 0..15

#ifndef USE_DISP
#define USE_DISP	2	// 1=use software display driver, 2=use hardware display driver (0=no driver)
#endif

// SD card GPIOs
#define SD_CS_GPIO	PB12	// CS output to SD card
#define SD_CLK_GPIO	PB9	// CLK output to SD card
#define SD_MISO_GPIO	PB8	// MISO input from SD card
#define SD_MOSI_GPIO	PB7	// MOSI output to SD card
#define SD_SPEED_INIT	(HCLK_PER_US*2)	// SD speed on init: wait delay "HCLK_PER_US*2" = 250 kbps
#define SD_SPEED_READ	(HCLK_PER_US/4)	// SD speed on read: wait delay "HCLK_PER_US/4" = 2 Mbps
#define SD_SPEED_WRITE	(HCLK_PER_US/1)	// SD speed on write: wait delay "HCLK_PER_US/1" = 500 kbps

#ifndef USE_SD
#define USE_SD		1	// 1=use SD card driver
#endif

#ifndef USE_DRAW
#define USE_DRAW	1	// 1=use graphics drawing functions
#endif

#ifndef USE_PRINT
#define USE_PRINT	1	// 1=use text printing functions
#endif

#ifndef USE_KEY
#define USE_KEY		1	// 1=use keyboard support
#endif

#ifndef USE_SOUND
#define USE_SOUND	2	// use sound support 1=tone, 2=melody
#endif

#ifndef USE_SCREENSHOT
#define USE_SCREENSHOT	0	// 1=use screen shot
#endif

#ifndef KEYCNT_REL
#define KEYCNT_REL	50	// keyboard counter - release interval in [ms]
#endif

#ifndef KEYCNT_PRESS
#define KEYCNT_PRESS	400	// keyboard counter - first repeat in [ms]
#endif

#ifndef KEYCNT_REPEAT
#define KEYCNT_REPEAT	100	// keyboard counter - next repeat in [ms]
#endif

#if USE_KEY			// 1=use keyboard support
#define SYSTICK_KEYSCAN	1	// 1=call KeyScan() function from SysTick system timer
#else
#define SYSTICK_KEYSCAN	0	// 1=call KeyScan() function from SysTick system timer
#endif

#if USE_SOUND == 2		// use sound support 1=tone, 2=melody
#define SYSTICK_SOUNDSCAN 1	// 1=call SoundScan() function from SysTick system timer
#else
#define SYSTICK_SOUNDSCAN 0	// 1=call SoundScan() function from SysTick system timer
#endif

// ----------------------------------------------------------------------------
//                            Library modules
// ----------------------------------------------------------------------------

#ifndef USE_CRC
#define USE_CRC		1	// 1=use CRC library
#endif

#ifndef USE_DECNUM
#define USE_DECNUM	1	// 1=use decode number
#endif

#ifndef USE_FAT
#define USE_FAT		1	// 1=use FAT filesystem
#endif

#ifndef USE_RAND
#define USE_RAND	1	// 1=use random number generator
#endif

// ----------------------------------------------------------------------------
//                             SDK modules
// ----------------------------------------------------------------------------

#ifndef USE_ADC
#define USE_ADC		1	// 1=use ADC peripheral
#endif

#ifndef USE_DMA
#define USE_DMA		1	// 1=use DMA peripheral
#endif

#ifndef USE_FLASH
#define USE_FLASH	1	// 1=use Flash programming
#endif

#ifndef USE_I2C
#define USE_I2C		1	// 1=use I2C peripheral
#endif

#ifndef USE_IRQ
#define USE_IRQ		1	// 1=use IRQ interrupt support
#endif

#ifndef USE_PWR
#define USE_PWR		1	// 1=use power control
#endif

#ifndef USE_SPI
#define USE_SPI		1	// 1=use SPI peripheral
#endif

#ifndef USE_TIM
#define USE_TIM		1	// 1=use timers
#endif

#ifndef USE_USART
#define USE_USART	1	// 1=use USART peripheral
#endif

// ----------------------------------------------------------------------------
//                            Clock Setup
// ----------------------------------------------------------------------------

// frequency of HSI internal oscillator 48MHz
#ifndef HSI_VALUE
#define HSI_VALUE	48000000
#endif

// System clock divider: 1, 2, 3, 4, 5, 6, 7, 8, 16, 32, 64, 128, 256 (default 1)
#ifndef SYSCLK_DIV
#define SYSCLK_DIV	1
#endif

// ADC clock divider: 1-16 (default 1)
#ifndef ADCCLK_DIV
#define ADCCLK_DIV	8		// CH32V0: max. 24 MHz (48/8 = 6 MHz)
#endif

// number of HCLK clock cycles per 1 us (used with Wait functions)
// - If you want to change frequency of system clock run-time, use a variable instead of constant.
#ifndef HCLK_PER_US
#define HCLK_PER_US	48
#endif

// increment of system time in [ms] on SysTick interrupt (0=do not use SysTick interrupt)
#ifndef SYSTICK_MS
#define SYSTICK_MS	16
#endif

// ----------------------------------------------------------------------------
//                          Peripheral clock enable
// ----------------------------------------------------------------------------

// Periferals
#ifndef ENABLE_SRAM
#define ENABLE_SRAM	1		// SRAM enable
#endif

#ifndef ENABLE_FLASH
#define ENABLE_FLASH	1		// FLASH enable (needed to rewrite RESET function)
#endif

#ifndef ENABLE_WWDG
#define ENABLE_WWDG	0		// Window watchdog enable
#endif

#ifndef ENABLE_PWR
#define ENABLE_PWR	1		// Power module enable
#endif

#ifndef ENABLE_AFI
#define ENABLE_AFI	1		// I/O auxiliary function enable
#endif

#ifndef ENABLE_PA
#define ENABLE_PA	1		// PA port enable
#endif

#ifndef ENABLE_PB
#define ENABLE_PB	1		// PB port enable
#endif

#ifndef ENABLE_PC
#define ENABLE_PC	1		// PC port enable
#endif

#ifndef ENABLE_ADC1
#define ENABLE_ADC1	1		// ADC1 module enable
#endif

#ifndef ENABLE_TIM1
#define ENABLE_TIM1	1		// TIM1 module enable
#endif

#ifndef ENABLE_TIM2
#define ENABLE_TIM2	1		// TIM2 module enable
#endif

#ifndef ENABLE_TIM3
#define ENABLE_TIM3	1		// TIM3 module enable
#endif

#ifndef ENABLE_SPI1
#define ENABLE_SPI1	1		// SPI1 module enable
#endif

#ifndef ENABLE_USART1
#define ENABLE_USART1	1		// USART1 module enable
#endif

#ifndef ENABLE_USART2
#define ENABLE_USART2	0		// USART2 module enable
#endif

#ifndef ENABLE_USART3
#define ENABLE_USART3	0		// USART3 module enable
#endif

#ifndef ENABLE_USART4
#define ENABLE_USART4	1		// USART4 module enable
#endif

#ifndef ENABLE_I2C1
#define ENABLE_I2C1	1		// I2C1 module enable
#endif

#ifndef ENABLE_USBFS
#define ENABLE_USBFS	0		// USBFS module enable
#endif

#ifndef ENABLE_USBPD
#define ENABLE_USBPD	0		// USBPD module enable
#endif
