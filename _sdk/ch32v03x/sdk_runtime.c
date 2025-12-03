
// ****************************************************************************
//
//                              Application support
//
// ****************************************************************************

#include "../../includes.h"	// globals

// check application in memory
Bool CheckApp()
{
	// get pointer to application info header
	const sAppInfoHeader* app = AppInfo;

	// check info header
	if ((*(u32*)app->magic1 != APPINFO_MAGIC1) || // "INFO"
		(*(u16*)app->mcu != APPINFO_MCU) || // this MCU, "3X"
		(*(u32*)app->magic2 != APPINFO_MAGIC2)) // "info"
		return False;

	// get application length
	int len = app->len;
	if ((len < 12) || (len > FLASHSIZE - APPINFO_OFF_CRC)) return False;

	// checksum
	u16 crc = Crc16CFast((const void*)(FLASH_BASE+APPINFO_OFF_CRC), len);
	return crc == app->crc;
}

// Setup CRC of loader data
void LoaderData_CRC(void)
{
	sLoaderData* ld = LoaderData; // pointer to boot loader data
	ld->crc = Crc16CFast(&ld->flags, 14); // checksum of loader data
}

// Check CRC of loader data
Bool LoaderData_Check(void)
{
	sLoaderData* ld = LoaderData; // pointer to boot loader data
	return ld->crc == Crc16CFast(&ld->flags, 14); // checksum of loader data
}

// Initialize device
void DevInit();

// System initialize
void SystemInit(void)
{
	// save reset reason
	ResetReason = RCC->RSTSCKR;

	// Delay about 2ms allowing access of the programming tool
//	int i;
//	for (i = 5000; i > 0; i--) nop();

	// Initialize system clock to default configuration
	RCC_ClockInit();

	// Enable AHB clock
	u32 mask =
#if !defined(ENABLE_DMA1) || ENABLE_DMA1	// DMA1 module enable
		RCC_AHBCLK_DMA1 |
#endif
#if !defined(ENABLE_SRAM) || ENABLE_SRAM	// SRAM enable
		RCC_AHBCLK_SRAM |
#endif
#if !defined(ENABLE_USBFS) || ENABLE_USBFS	// USBFS module enable
		RCC_AHBCLK_USBFS |
#endif
#if !defined(ENABLE_USBPD) || ENABLE_USBPD	// USBPD module enable
		RCC_AHBCLK_USBPD |
#endif
		0;
	RCC_AHBClkEnable(mask);

	// Enable APB2 clock
	mask =
#if !defined(ENABLE_AFI) || ENABLE_AFI		// I/O auxiliary function enable
		RCC_APB2CLK_AFI |
#endif
#if !defined(ENABLE_PA) || ENABLE_PA		// PA port enable
		RCC_APB2CLK_PA |
#endif
#if !defined(ENABLE_PB) || ENABLE_PB		// PB port enable
		RCC_APB2CLK_PB |
#endif
#if !defined(ENABLE_PC) || ENABLE_PC		// PC port enable
		RCC_APB2CLK_PC |
#endif
#if !defined(ENABLE_ADC1) || ENABLE_ADC1	// ADC1 module enable
		RCC_APB2CLK_ADC1 |
#endif
#if !defined(ENABLE_TIM1) || ENABLE_TIM1	// TIM1 module enable
		RCC_APB2CLK_TIM1 |
#endif
#if !defined(ENABLE_SPI1) || ENABLE_SPI1	// SPI1 module enable
		RCC_APB2CLK_SPI1 |
#endif
#if !defined(ENABLE_USART1) || ENABLE_USART1	// USART1 module enable
		RCC_APB2CLK_USART1 |
#endif
		0;
	RCC_APB2ClkEnable(mask);

	// Enable APB1 clock
	mask =
#if !defined(ENABLE_TIM2) || ENABLE_TIM2	// TIM2 module enable
		RCC_APB1CLK_TIM2 |
#endif
#if !defined(ENABLE_TIM3) || ENABLE_TIM3	// TIM3 module enable
		RCC_APB1CLK_TIM3 |
#endif
#if !defined(ENABLE_WWDG) || ENABLE_WWDG	// Window watchdog module enable
		RCC_APB1CLK_WWDG |
#endif
#if !defined(ENABLE_USART2) || ENABLE_USART2	// USART2 module enable
		RCC_APB1CLK_USART2 |
#endif
#if !defined(ENABLE_USART3) || ENABLE_USART3	// USART3 module enable
		RCC_APB1CLK_USART3 |
#endif
#if !defined(ENABLE_USART4) || ENABLE_USART4	// USART4 module enable
		RCC_APB1CLK_USART4 |
#endif
#if !defined(ENABLE_I2C1) || ENABLE_I2C1	// I2C1 module enable
		RCC_APB1CLK_I2C1 |
#endif
#if !defined(ENABLE_PWR) || ENABLE_PWR		// Power module enable
		RCC_APB1CLK_PWR |
#endif
		0;
	RCC_APB1ClkEnable(mask);

	// Initialize SysTick
	SysTick_Init();

	// pre-initialize constructors
	extern void (*__preinit_array_start)();
	extern void (*__preinit_array_end)();
	void(**p)();
	for (p = &__preinit_array_start; p < &__preinit_array_end; p++) (*p)();

	// Initialize device
	DevInit();
}

// Terminate device
void DevTerm();

// System terminate
void SystemTerm(void)
{
	// Terminate device
	DevTerm();

	// Disable all interrupts
	NVIC_IRQAllDisable();

	// Clear all interrupt pending states
	NVIC_IRQAllClear();

	// Reset SysTick
	SysTick_Reset();

	// Reset system clock to default configuration (set to HSI oscillator)
	RCC_ClockReset();

	// Reset peripherals, except PWR module
	RCC->APB2PRSTR = ~0;
	RCC->APB1PRSTR = ~B28;
	RCC->APB2PRSTR = 0;
	RCC->APB1PRSTR = 0;

	// disable clocks, except SRAM and PWR
	RCC->AHBPCENR = B2;
	RCC->APB2PCENR = 0;
	RCC->APB1PCENR = B28;
}

// exit application and reset to boot loader (execute software reset)
void ResetToBootLoader(void)
{
#if USE_KEY
	// wait for no key pressed
	KeyWaitNoPressed();
#endif

	// request to return to boot loader
	LoaderData->flags |= B6;
	LoaderData_CRC();

	// System terminate
	SystemTerm();

	// System reset
	SystemReset();
}
