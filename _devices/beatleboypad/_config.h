
// ----------------------------------------------------------------------------
//                            Clock Setup
// ----------------------------------------------------------------------------

// Frequency of HSE external oscillator
#ifndef HSE_VALUE
#define HSE_VALUE	24000000
#endif

// frequency of HSI internal oscillator
#ifndef HSI_VALUE
#define HSI_VALUE	24000000
#endif

// System clock source: 1=HSI, 2=HSE, 3=HSE_Bypass, 4=PLL_HSI, 5=PLL_HSE, 6=PLL_HSE_Bypass, 7=PLL_HSI/2, 8=PLL_HSE/2, 9=PLL_HSE_Bypass/2
#ifndef SYSCLK_SRC
#define SYSCLK_SRC	1
#endif

// PLL multiplier
#ifndef PLLCLK_MUL
#define PLLCLK_MUL	0		// only *2 supported; 24 MHz * 2 = 48 MHz
#endif

// System clock divider: 1, 2, 3, 4, 5, 6, 7, 8, 16, 32, 64, 128, 256 (default 1)
#ifndef SYSCLK_DIV
#define SYSCLK_DIV	1
#endif

// number of HCLK clock cycles per 1 us (used with Wait functions)
// - If you want to change frequency of system clock run-time, use a variable instead of constant.
#ifndef HCLK_PER_US
#define HCLK_PER_US	24
#endif

// ADC clock divider: (1,) 2, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128 (default 1 or 2)
#ifndef ADCCLK_DIV
#define ADCCLK_DIV	24		// CH32V0: max. 24 MHz (24 / 24 = 1 MHz)
#endif

// increment of system time in [ms] on SysTick interrupt (0=do not use SysTick interrupt)
#ifndef SYSTICK_MS
#define SYSTICK_MS	0
#endif

// ----------------------------------------------------------------------------
//                             Device setup
// ----------------------------------------------------------------------------

// run mode
#define RUNMODE_OLED	0	// hardcoded in beatleboypad_asm.S
#define RUNMODE_VGA	1

#ifndef DISP_DBLBUF
#define DISP_DBLBUF	0	// 1=use VGA display double buffer (FrameBuf+DispBuf)
#endif

// ADC measure
// - Buttons are valid if they are detected twice identically - so the reaction time is 2*32=64 ms.
#define PADADC_SHIFT	9	// bits of number of measures of PAD (= period 31.8us * 2 * 512 = 32ms)
#define PADADC_NUM	(1<<PADADC_SHIFT) // number of measures of PAD
#define SUPPLYADC_SHIFT	5	// bits of number of measures of supply voltage (= period 32ms * 32 = 1sec)
#define SUPPLYADC_NUM	(1<<SUPPLYADC_SHIFT) // number of measures of supply voltage

// Button codes (order corresponds to the order of the arrow characters in the font)
#define KEY_RIGHT	1	// right (character code 0x0C = arrow right, or ASCII code 0x1C)
#define KEY_UP		2	// up (character code 0x0D = arrow up, or ASCII code 0x1D)
#define KEY_LEFT	3	// left (character code 0x0E = arrow left, or ASCII code 0x1E)
#define KEY_DOWN	4	// down (character code 0x0F = arrow down, or ASCII code 0x1F)
#define KEY_A		5	// A
#define KEY_B		6	// B

#define NOKEY		0	// no key

#define KEY_NUM		6	// number of buttons

// display
#define DISP_I2C_ADDR	0x3C	// display I2C address
#define DISP_SDA_GPIO	PC1	// display gpio with SDA
#define DISP_SCL_GPIO	PC2	// display gpio with SCL
#define DISP_I2C_MAP	0	// hardware display driver: I2C mapping

#ifndef DISP_WAIT_CLK
#define DISP_WAIT_CLK	3	// software display driver: number of I2C wait clock (0 or more) ... DispUpdate() takes 2:10ms, 3-4:11ms, 10:26 ms
#endif

#ifndef DISP_SPEED_HZ
#define DISP_SPEED_HZ	750000	// hardware display driver: I2C speed in Hz ... DispUpdate() takes 3M:4ms, 2M:6ms, 1M:11ms, 500K:20ms
#endif

#ifndef USE_DISP
#define USE_DISP	1	// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver
#endif

#ifndef USE_SD
#define USE_SD		0	// 1=use software SD card driver, 2=use hardware SD card driver (0=no driver)
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

//#ifndef KEYCNT_REL
//#define KEYCNT_REL	4	// keyboard counter - release interval in 1/60 sec
//#endif

//#ifndef KEYCNT_PRESS
//#define KEYCNT_PRESS	20	// keyboard counter - first repeat in 1/60 sec
//#endif

//#ifndef KEYCNT_REPEAT
//#define KEYCNT_REPEAT	6	// keyboard counter - next repeat in 1/60 sec
//#endif

// do not use SysTick
//#define SYSTICK_KEYSCAN	0	// 1=call KeyScan() function from SysTick system timer
//#define SYSTICK_SOUNDSCAN 0	// 1=call SoundScan() function from SysTick system timer

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

#ifndef ENABLE_PD
#define ENABLE_PD	1		// PD port enable
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
#define ENABLE_TIM3	0		// TIM3 module enable
#endif

#ifndef ENABLE_SPI1
#define ENABLE_SPI1	0		// SPI1 module enable
#endif

#ifndef ENABLE_USART1
#define ENABLE_USART1	0		// USART1 module enable
#endif

#ifndef ENABLE_USART2
#define ENABLE_USART2	0		// USART2 module enable
#endif

#ifndef ENABLE_USART3
#define ENABLE_USART3	0		// USART3 module enable
#endif

#ifndef ENABLE_USART4
#define ENABLE_USART4	0		// USART4 module enable
#endif

#ifndef ENABLE_I2C1
#define ENABLE_I2C1	1		// I2C1 module enable
#endif

// ----------------------------------------------------------------------------
//                            Library modules
// ----------------------------------------------------------------------------

#ifndef USE_CRC
#define USE_CRC		0	// 1=use CRC library
#endif

#ifndef USE_DECNUM
#define USE_DECNUM	1	// 1=use decode number
#endif

#ifndef USE_FAT
#define USE_FAT		0	// 1=use FAT filesystem
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
#define USE_DMA		0	// 1=use DMA peripheral
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
#define USE_USART	0	// 1=use USART peripheral
#endif

