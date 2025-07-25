
// ****************************************************************************
//
//                              Reset and Clock Control
//
// ****************************************************************************

#ifndef _SDK_RCC_H
#define _SDK_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

// default frequencies
#ifndef HSI_VALUE
#define HSI_VALUE	8000000		// frequency of HSI internal oscillator 8MHz
#endif

#ifndef HSE_VALUE
#define HSE_VALUE	24000000	// frequency of HSE external oscillator 24MHz (should be 3..25 MHz)
#endif

#ifndef LSI_VALUE
#define LSI_VALUE	40000		// frequency of LSI low-speed internal oscillator 40kHz
#endif

#ifndef LSE_VALUE
#define LSE_VALUE	32768		// frequency of LSE low-speed external oscillator 32768Hz
#endif

#ifndef SYSCLK_SRC
#define SYSCLK_SRC	4		// System clock source: 1=HSI, 2=HSE, 3=HSE_Bypass, 4=PLL_HSI, 5=PLL_HSE, 6=PLL_HSE_Bypass, 7=PLL_HSI/2, 8=PLL_HSE/2, 9=PLL_HSE_Bypass/2
#endif

#ifndef PLLCLK_MUL
#define PLLCLK_MUL	9		// PLL multiplier 2 - 18 (max. output 72MHz)
#endif

#ifndef SYSCLK_DIV
#define SYSCLK_DIV	1		// System clock divider: 1, 2, 4, 8, 16, 64, 128, 256, 512 (max. output 72MHz)
#endif

#ifndef APB1CLK_DIV
#define APB1CLK_DIV	1		// APB1 PCLK1 divider: 1, 2, 4, 8, 16 (max. output 72MHz)
#endif

#ifndef APB2CLK_DIV
#define APB2CLK_DIV	1		// APB2 PCLK1 divider: 1, 2, 4, 8, 16 (max. output 72MHz)
#endif

#ifndef ADCCLK_DIV
#define ADCCLK_DIV	6		// ADC clock divider: 1, 2, 4, 6, 8 (max. 14 MHz)
#endif

// Reset and clock control 0x40021000
typedef struct {
	io32	CTLR;		// 0x00: Clock control register
	io32	CFGR0;		// 0x04: Clock configuration register 0
	io32	INTR;		// 0x08: Clock interrupt register
	io32	APB2PRSTR;	// 0x0C: PB2 peripheral reset register
	io32	APB1PRSTR;	// 0x10: PB1 peripheral reset register
	io32	AHBPCENR;	// 0x14: HB peripheral clock enable register
	io32	APB2PCENR;	// 0x18: PB2 peripheral clock enable register
	io32	APB1PCENR;	// 0x1C: PB1 peripheral clock enable register
	io32	BDCTLR;		// 0x20: Backup domain control register
	io32	RSTSCKR;	// 0x24: Control/status register
	io32	AHBRSTR;	// 0x28: HB peripheral reset register
} RCC_t;
STATIC_ASSERT(sizeof(RCC_t) == 0x2C, "Incorrect RCC_t!");
#define RCC	((RCC_t*)RCC_BASE)

// system clock source
#define RCC_SYSCLKSRC_HSI	0	// HSI as system clock (default)
#define RCC_SYSCLKSRC_HSE	1	// HSE as system clock
#define RCC_SYSCLKSRC_PLL	2	// PLL as system clock

// AHB clock divider (from SYSCLK)
#define RCC_SYSCLK_DIV1		0	// (0-7) prescaler off
#define RCC_SYSCLK_DIV2		8	// SYSCLK divided by 2
#define RCC_SYSCLK_DIV4		9	// SYSCLK divided by 4
#define RCC_SYSCLK_DIV8		10	// SYSCLK divided by 8
#define RCC_SYSCLK_DIV16	11	// SYSCLK divided by 16
#define RCC_SYSCLK_DIV64	12	// SYSCLK divided by 64
#define RCC_SYSCLK_DIV128	13	// SYSCLK divided by 128
#define RCC_SYSCLK_DIV256	14	// SYSCLK divided by 256
#define RCC_SYSCLK_DIV512	15	// SYSCLK divided by 512

// APB1 and APB2 clock divider (from HCLK; cannot exceed 72MHz))
#define RCC_HCLK_DIV1		0	// HCLK not divided
//#define RCC_HCLK_DIV1		1	// HCLK not divided
//#define RCC_HCLK_DIV1		2	// HCLK not divided
//#define RCC_HCLK_DIV1		3	// HCLK not divided
#define RCC_HCLK_DIV2		4	// HCLK divided by 2
#define RCC_HCLK_DIV4		5	// HCLK divided by 4
#define RCC_HCLK_DIV8		6	// HCLK divided by 8
#define RCC_HCLK_DIV16		7	// HCLK divided by 16

// ADC clock divider (from PCLK2; ADC clock should not exceed 14MHz)
#define RCC_ADCCLK_DIV2		0	// PCLK2 divided by 2 as ADC clock
#define RCC_ADCCLK_DIV4		1	// PCLK2 divided by 4 as ADC clock
#define RCC_ADCCLK_DIV6		2	// PCLK2 divided by 6 as ADC clock
#define RCC_ADCCLK_DIV8		3	// PCLK2 divided by 8 as ADC clock

// PLL clock source
#define RCC_PLLSRC_HSI		0	// HSI is fed into PLL
#define RCC_PLLSRC_HSE		1	// HSE is fed into PLL

// PLL multiplication (PLL output cannot exceed 72MHz)
#define RCC_PLL_MUL2		0	// PLL input clock * 2
#define RCC_PLL_MUL3		1	// PLL input clock * 3
#define RCC_PLL_MUL4		2	// PLL input clock * 4
#define RCC_PLL_MUL5		3	// PLL input clock * 5
#define RCC_PLL_MUL6		4	// PLL input clock * 6
#define RCC_PLL_MUL7		5	// PLL input clock * 7
#define RCC_PLL_MUL8		6	// PLL input clock * 8
#define RCC_PLL_MUL9		7	// PLL input clock * 9
#define RCC_PLL_MUL10		8	// PLL input clock * 10
#define RCC_PLL_MUL11		9	// PLL input clock * 11
#define RCC_PLL_MUL12		10	// PLL input clock * 12
#define RCC_PLL_MUL13		11	// PLL input clock * 13
#define RCC_PLL_MUL14		12	// PLL input clock * 14
#define RCC_PLL_MUL15		13	// PLL input clock * 15
#define RCC_PLL_MUL16		14	// PLL input clock * 16
#define RCC_PLL_MUL18		15	// PLL input clock * 18

// USB PLL prescaler (result frequency should be 48 MHz)
#define RCC_USBPRE_DIV1		0	// USB PLL 1-division for PLLCLK=48MHz
#define RCC_USBPRE_DIV2		1	// USB PLL 2-division for PLLCLK=96MHz
#define RCC_USBPRE_DIV15	2	// USB PLL 1.5-division for PLLCLK=72MHz

// MCO pin clock output
#define RCC_MCO_NONE		0	// (0-3) no clock output
#define RCC_MCO_SYSCLK		4	// system clock
#define RCC_MCO_HSI		5	// HSI internal oscillator 8MHz
#define RCC_MCO_HSE		6	// HSE external oscillator
#define RCC_MCO_PLL		7	// PLL clock output

// AHB peripheral clock mask
#define RCC_AHBCLK_DMA1		B0	// DMA1 module clock mask
#define RCC_AHBCLK_SRAM		B2	// SRAM clock mask
#define RCC_AHBCLK_CRC		B6	// CRC clock mask
#define RCC_AHBCLK_USBFS	B12	// USBFS clock mask
#define RCC_AHBCLK_USBPD	B17	// USBPD clock mask

// APB2 peripheral clock mask
#define RCC_APB2CLK_AFI		B0	// I/O auxiliary function module clock mask
#define RCC_APB2CLK_PA		B2	// PA port module clock mask
#define RCC_APB2CLK_PB		B3	// PB port module clock mask
#define RCC_APB2CLK_PC		B4	// PC port module clock mask
#define RCC_APB2CLK_PD		B5	// PD port module clock mask
#define RCC_APB2CLK_ADC1	B9	// ADC1 module clock mask
#define RCC_APB2CLK_TIM1	B11	// TIM1 module clock mask
#define RCC_APB2CLK_SPI1	B12	// SPI1 module clock mask
#define RCC_APB2CLK_USART1	B14	// USART1 module clock mask

// APB1 peripheral clock mask
#define RCC_APB1CLK_TIM2	B0	// TIM2 module clock mask
#define RCC_APB1CLK_TIM3	B1	// TIM3 module clock mask
#define RCC_APB1CLK_TIM4	B2	// TIM4 module clock mask
#define RCC_APB1CLK_WWDG	B11	// Window watchdog clock mask
#define RCC_APB1CLK_SPI2	B14	// SPI2 module clock mask
#define RCC_APB1CLK_USART2	B17	// USART2 module clock mask
#define RCC_APB1CLK_USART3	B18	// USART3 module clock mask
#define RCC_APB1CLK_USART4	B19	// USART4 module clock mask
#define RCC_APB1CLK_I2C1	B21	// I2C1 module clock mask
#define RCC_APB1CLK_I2C2	B22	// I2C2 module clock mask
#define RCC_APB1CLK_CAN1	B25	// CAN1 module clock mask
#define RCC_APB1CLK_BKP		B27	// Backup module clock mask
#define RCC_APB1CLK_PWR		B28	// Power module clock mask
#define RCC_APB1CLK_LPTIM	B31	// LPTIM module clock mask

// RTC clock source
#define RCC_RTCSRC_NO		0	// no clock
#define RCC_RTCSRC_LSE		1	// LSE oscillator
#define RCC_RTCSRC_LSI		2	// LSI oscillator
#define RCC_RTCSRC_HSE		3	// HSE oscillator divided by 128

// Reset reason - copy of the RCC->RSTSCKR register on system start (check using RCC_RESETON_* flags)
#define RCC_RESETON_LPWR	B31	// Low-power reset
#define RCC_RESETON_WWD		B30	// Windows watchdog reset
#define RCC_RESETON_IWD		B29	// Independent watchdog reset
#define RCC_RESETON_SW		B28	// software reset
#define RCC_RESETON_PWR		B27	// power-on reset
#define RCC_RESETON_RST		B26	// manual reset on NRST pin
extern u32 ResetReason;

// AHB clock divider table (from SYSCLK)
extern const u16 RCC_AHBClkDivTab[16];

// APB1 and APB2 clock divider table (from HCLK)
extern const u8 RCC_APBClkDivTab[8];

// PLL multiplication table
extern const u8 RCC_PLLMulTab[16];

// Current frequencies
#define CLK_HSI		0	// HSI oscillator frequency index (8 MHz)
#define CLK_HSE		1	// HSE oscillator frequency index (4-16 MHz)
#define CLK_LSI		2	// LSI oscillator frequency index (40 kHz)
#define CLK_LSE		3	// LSE oscillator frequency index (32768 Hz)
#define CLK_SYSCLK	4	// SYSCLK frequency index (system frequency from clock sources)
#define CLK_HCLK	5	// HCLK frequency index, AHB clock (main clock to periphery and flash, SYSCLK divided)
#define CLK_PCLK1	6	// PCLK1 frequency index, APB1 clock
#define CLK_PCLK2	7	// PCLK2 frequency index, APB2 clock
#define CLK_ADCCLK	8	// ADCCLK frequency index (ADC clock, PCLK2 divided)
#define CLK_USBCLK	9	// USBCLK frequency index (should be 48MHz)

#define CLK_NUM		10	// number of frequency indices

extern u32 RCC_FreqTab[CLK_NUM];	// current frequencies in [Hz]

#define SystemCoreClock RCC_FreqTab[CLK_HCLK] // system core clock

// --- HSI high-speed internal oscillator 8MHz

// Enable/Disable HSI high-speed internal oscillator 8MHz (default enabled)
// - Enabled by hardware when returning from standby mode or when HSE fails.
INLINE void RCC_HSIEnable(void) { RCC->CTLR |= B0; }
INLINE void RCC_HSIDisable(void) { RCC->CTLR &= ~B0; }

// Check if HSI high-speed internal oscillator 8MHz is stable
INLINE Bool RCC_HSIIsStable(void) { return (RCC->CTLR & B1) != 0; }

// Get current adjustment value of the HSI internal high-speed clock 8MHz (0..31; default 16)
//  Clock adjustment value is in range 0..31, with default value 16.
//  Oscillator frequency 8MHz can be adjusted by 20kHz or 2.5kHz per step.
INLINE u8 RCC_HSIGetTrim(void) { return (u8)((RCC->CTLR >> 3) & 0x1f); }

// Set adjustment value of the HSI internal high-speed clock 8MHz (0..31)
//  Clock adjustment value is in range 0..31, with default value 16.
//  Oscillator frequency 8MHz can be adjusted by 20kHz or 2.5kHz per step.
INLINE void RCC_HSITrim(int trim) { RCC->CTLR = (RCC->CTLR & ~(0x1f << 3)) | (trim << 3); }

// Get calibration value of the HSI internal high-speed clock 8MHz (0..31)
INLINE u8 RCC_HSIGetCal(void) { return (u8)((RCC->CTLR >> 8) & 0xff); }

// Enable/Disable HSI low-power mode
INLINE void RCC_HSILPEnable(void) { RCC->CTLR |= B2; }
INLINE void RCC_HSILPDisable(void) { RCC->CTLR &= ~B2; }

// --- HSE high-speed external crystal oscillator

// Enable/Disable HSE high-speed external crystal oscillator (default disabled)
// - Disabled by hardware after entering standby low-power mode.
INLINE void RCC_HSEEnable(void) { RCC->CTLR |= B16; }
INLINE void RCC_HSEDisable(void) { RCC->CTLR &= ~B16; }

// Check if HSE high-speed external crystal oscillator is stable
INLINE Bool RCC_HSEIsStable(void) { return (RCC->CTLR & B17) != 0; }

// Enable/Disable bypass HSE high-speed external crystal oscillator (HSE must be disabled)
INLINE void RCC_HSEBypassEnable(void) { RCC->CTLR |= B18; }
INLINE void RCC_HSEBypassDisable(void) { RCC->CTLR &= ~B18; }

// Enable/Disable HSE low-power mode
INLINE void RCC_HSELPEnable(void) { RCC->CTLR |= B20; }
INLINE void RCC_HSELPDisable(void) { RCC->CTLR &= ~B20; }

// Start HSE oscillator and wait to be stable (bypass = bypass HSE crystal; returns False on error)
Bool RCC_HSEStart(Bool bypass);

// --- LSI low-speed internall oscillator

// Enable/Disable LSI low speed clock 128KHz
INLINE void RCC_LSIEnable(void) { RCC->RSTSCKR |= B0; }
INLINE void RCC_LSIDisable(void) { RCC->RSTSCKR &= ~B0; }

// Check if LSI low speed clock 128KHz is stable
INLINE Bool RCC_LSIIsStable(void) { return (RCC->RSTSCKR & B1) != 0; }

// --- LSE low-speed external crystal oscillator 32768Hz

// Enable/Disable LSE low-speed crytal oscillator 32768Hz
INLINE void RCC_LSEEnable(void) { RCC->BDCTLR |= B0; }
INLINE void RCC_LSEDisable(void) { RCC->BDCTLR &= ~B0; }

// Check if LSE low speed clock 32768Hz is stable
INLINE Bool RCC_LSEIsStable(void) { return (RCC->BDCTLR & B1) != 0; }

// Enable/Disable bypass LSE low-speed external crystal oscillator (LSE must be disabled)
INLINE void RCC_LSEBypassEnable(void) { RCC->BDCTLR |= B2; }
INLINE void RCC_LSEBypassDisable(void) { RCC->BDCTLR &= ~B2; }

// --- PLL clock

// Enable/Disable PLL clock (default disabled)
// - Disabled by hardware after entering standby low-power mode.
INLINE void RCC_PLLEnable(void) { RCC->CTLR |= B24; }
INLINE void RCC_PLLDisable(void) { RCC->CTLR &= ~B24; }

// Check if PLL clock is ready
INLINE Bool RCC_PLLIsReady(void) { return (RCC->CTLR & B25) != 0; }

// Select PLL clock source RCC_PLLSRC_* (PLL should be off)
INLINE void RCC_PLLSrc(int src) { RCC->CFGR0 = (RCC->CFGR0 & ~B16) | (src << 16); }

// Get PLL clock source RCC_PLLSRC_*
INLINE u8 RCC_GetPLLSrc(void) { return (u8)((RCC->CFGR0 >> 16) & 1); }

// Select HSE divider for PLL entry: HSE not divided
INLINE void RCC_PLLHSEDiv1(void) { RCC->CFGR0 &= B17; }

// Select HSE divider for PLL entry: HSE divided by 2
INLINE void RCC_PLLHSEDiv2(void) { RCC->CFGR0 |= B17; }

// Check if HSE is divided by 2 for PLL entry
INLINE Bool RCC_PLLHSEIsDiv(void) { return (RCC->CFGR0 & B17) != 0; }

// Select HSI divider for PLL entry: HSI not divided
INLINE void RCC_PLLHSIDiv1(void) { *(u32*)EXTEN_BASE |= B4; }

// Select HSI divider for PLL entry: HSI divided by 2
INLINE void RCC_PLLHSIDiv2(void) { *(u32*)EXTEN_BASE &= ~B4; }

// Check if HSI is divided by 2 for PLL entry
INLINE Bool RCC_PLLHSIIsDiv(void) { return (*(u32*)EXTEN_BASE & B4) == 0; }

// Set PLL multiplication factor RCC_PLL_MUL* (PLL should be off; PLL output cannot exceed 72MHz)
INLINE void RCC_PLLMul(int mul) { RCC->CFGR0 = (RCC->CFGR0 & ~(0x0f << 18)) | (mul << 18); }

// Get PLL multiplication factor RCC_PLL_MUL*
INLINE int RCC_GetPLLMul(void) { return (RCC->CFGR0 >> 18) & 0x0f; }

// Get PLL multiplication factor value 2..18
INLINE int RCC_GetPLLMulVal(void) { return RCC_PLLMulTab[RCC_GetPLLMul()]; }

// Set USB PLL prescaler RCC_USBPRE_DIV* (result frequency should be 48 MHz)
INLINE void RCC_USBPLLDiv(int div) { RCC->CFGR0 = (RCC->CFGR0 & ~(3 << 22)) | (div << 22); }

// --- Clock source

// Select system clock source RCC_SYSCLKSRC_* (default 0 = HSI)
INLINE void RCC_SysClkSrc(int src) { RCC->CFGR0 = (RCC->CFGR0 & ~3) | src; }

// Get current system clock source RCC_SYSCLKSRC_* (hardware set)
INLINE u8 RCC_SysClk(void) { return (u8)((RCC->CFGR0 >> 2) & 3); }

// Set AHB clock divider RCC_SYSCLK_DIV* (default 2 = divide by 3)
INLINE void RCC_AHBDiv(int div) { RCC->CFGR0 = (RCC->CFGR0 & ~(0x0f << 4)) | (div << 4); }

// Get AHB clock divider RCC_SYSCLK_DIV*
INLINE u8 RCC_GetAHBDiv(void) { return (u8)((RCC->CFGR0 >> 4) & 0x0f); }

// Get AHB clock divider value 1..512
INLINE u16 RCC_GetAHBDivVal(void) { return RCC_AHBClkDivTab[RCC_GetAHBDiv()]; }

// Set APB1 (PCLK1) clock divider RCC_HCLK_DIV* (default 0 = not divided)
INLINE void RCC_APB1Div(int div) { RCC->CFGR0 = (RCC->CFGR0 & ~(7 << 8)) | (div << 8); }

// Get APB1 (PCLK1) clock divider RCC_HCLK_DIV* 
INLINE u8 RCC_GetAPB1Div(void) { return (u8)((RCC->CFGR0 >> 8) & 7); }

// Get APB1 (PCLK1) clock divider value 1..16
INLINE u16 RCC_GetAPB1DivVal(void) { return RCC_APBClkDivTab[RCC_GetAPB1Div()]; }

// Set APB2 (PCLK2) clock divider RCC_HCLK_DIV* (default 0 = not divided)
INLINE void RCC_APB2Div(int div) { RCC->CFGR0 = (RCC->CFGR0 & ~(7 << 11)) | (div << 11); }

// Get APB2 (PCLK2) clock divider RCC_HCLK_DIV* 
INLINE u8 RCC_GetAPB2Div(void) { return (u8)((RCC->CFGR0 >> 11) & 7); }

// Get APB2 (PCLK2) clock divider value 1..16
INLINE u16 RCC_GetAPB2DivVal(void) { return RCC_APBClkDivTab[RCC_GetAPB2Div()]; }

// Set ADC clock duty cycle 0..7 HCLK clock cycles (default 0 means 0.5 HCLK clock cycles)
INLINE void RCC_ADCDuty(int duty) { RCC->CFGR0 = (RCC->CFGR0 & ~(7 << 28)) | (duty << 28); }

// Set ADC clock divider RCC_ADCCLK_DIV* (should not exceed 14MHz) (default 0 = divided by 2)
INLINE void RCC_ADCDiv(int div) { RCC->CFGR0 = (RCC->CFGR0 & ~(3 << 14)) | (div << 14); }

// Get ADC clock divider RCC_ADCCLK_DIV*
INLINE u8 RCC_GetADCDiv(void) { return (u8)((RCC->CFGR0 >> 14) & 3); }

// Get ADC clock divider value 2..8
INLINE u8 RCC_GetADCDivVal(void) { return (u8)((RCC_GetADCDiv()+1)<<1); }

// Enable/Disable ADC AHB clock divider (AHB clock does not divide frequency, if disabled)
INLINE void RCC_ADCDivEnable(void) { RCC->CFGR0 &= ~B31; }
INLINE void RCC_ADCDivDisable(void) { RCC->CFGR0 |= B31; }
INLINE Bool RCC_GetADCDivEnabled(void) { return (RCC->CFGR0 & B31) != 0; }

// Set MCO pin clock output source RCC_MCO_* (default 0 = disabled)
INLINE void RCC_MCOClkSrc(int src) { RCC->CFGR0 = (RCC->CFGR0 & ~(7 << 24)) | (src << 24); }

// Get clock frequency in [Hz] from frequency table CLK_*
INLINE u32 RCC_GetFreq(int inx) { return RCC_FreqTab[inx]; }

// Update frequencies in clock frequency table (should be called after change settings)
void RCC_UpdateFreq(void);

// Initialize system clock to default configuration
void RCC_ClockInit(void);

// Reset system clock to default configuration (select HSI oscillator/3)
void RCC_ClockReset(void);

// --- Interrupt (default all disabled)

// LSI clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_LSIIntEnable(void) { RCC->INTR |= B8; }
INLINE void RCC_LSIIntDisable(void) { RCC->INTR &= ~B8; }
INLINE Bool RCC_LSIInt(void) { return (RCC->INTR & B0) != 0; }
INLINE void RCC_LSIIntClear(void) { RCC->INTR |= B16; }

// LSE clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_LSEIntEnable(void) { RCC->INTR |= B9; }
INLINE void RCC_LSEIntDisable(void) { RCC->INTR &= ~B9; }
INLINE Bool RCC_LSEInt(void) { return (RCC->INTR & B1) != 0; }
INLINE void RCC_LSEIntClear(void) { RCC->INTR |= B17; }

// HSI clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_HSIIntEnable(void) { RCC->INTR |= B10; }
INLINE void RCC_HSIIntDisable(void) { RCC->INTR &= ~B10; }
INLINE Bool RCC_HSIInt(void) { return (RCC->INTR & B2) != 0; }
INLINE void RCC_HSIIntClear(void) { RCC->INTR |= B18; }

// HSE clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_HSEIntEnable(void) { RCC->INTR |= B11; }
INLINE void RCC_HSEIntDisable(void) { RCC->INTR &= ~B11; }
INLINE Bool RCC_HSEInt(void) { return (RCC->INTR & B3) != 0; }
INLINE void RCC_HSEIntClear(void) { RCC->INTR |= B19; }

// PLL clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_PLLIntEnable(void) { RCC->INTR |= B12; }
INLINE void RCC_PLLIntDisable(void) { RCC->INTR &= ~B12; }
INLINE Bool RCC_PLLInt(void) { return (RCC->INTR & B4) != 0; }
INLINE void RCC_PLLIntClear(void) { RCC->INTR |= B20; }

// CSS HSE clock failure Enable/Disable/Flag/Clear
//  - Triggers CSSF and NMI interrupt when HSE fails
INLINE void RCC_CSSEnable(void) { RCC->CTLR |= B19; }
INLINE void RCC_CSSDisable(void) { RCC->CTLR &= ~B19; }
INLINE Bool RCC_CSSInt(void) { return (RCC->INTR & B7) != 0; }
INLINE void RCC_CSSIntClear(void) { RCC->INTR |= B23; }

// Clear all interrupt flags
INLINE void RCC_IntClear(void) { RCC->INTR |= B16|B17|B18|B19|B20|B23; }

// Disable all interrupt flags
INLINE void RCC_IntDisable(void) { RCC->INTR &= ~(B8|B9|B10|B11|B12); }

// --- Peripheral reset

// I/O auxiliary function module reset ON/OFF/Reset
INLINE void RCC_AFIResetOn(void) { RCC->APB2PRSTR |= B0; cb(); }
INLINE void RCC_AFIResetOff(void) { RCC->APB2PRSTR &= ~B0; cb(); }
INLINE void RCC_AFIReset(void) { RCC_AFIResetOn(); nop(); RCC_AFIResetOff(); }

// PA port module reset ON/OFF/Reset
INLINE void RCC_PAResetOn(void) { RCC->APB2PRSTR |= B2; cb(); }
INLINE void RCC_PAResetOff(void) { RCC->APB2PRSTR &= ~B2; cb(); }
INLINE void RCC_PAReset(void) { RCC_PAResetOn(); nop(); RCC_PAResetOff(); }

// PB port module reset ON/OFF/Reset
INLINE void RCC_PBResetOn(void) { RCC->APB2PRSTR |= B3; cb(); }
INLINE void RCC_PBResetOff(void) { RCC->APB2PRSTR &= ~B3; cb(); }
INLINE void RCC_PBReset(void) { RCC_PBResetOn(); nop(); RCC_PBResetOff(); }

// PC port module reset ON/OFF/Reset
INLINE void RCC_PCResetOn(void) { RCC->APB2PRSTR |= B4; cb(); }
INLINE void RCC_PCResetOff(void) { RCC->APB2PRSTR &= ~B4; cb(); }
INLINE void RCC_PCReset(void) { RCC_PCResetOn(); nop(); RCC_PCResetOff(); }

// PD port module reset ON/OFF/Reset
INLINE void RCC_PDResetOn(void) { RCC->APB2PRSTR |= B5; cb(); }
INLINE void RCC_PDResetOff(void) { RCC->APB2PRSTR &= ~B5; cb(); }
INLINE void RCC_PDReset(void) { RCC_PDResetOn(); nop(); RCC_PDResetOff(); }

// Port module reset (use port index PORT*_INX)
INLINE void RCC_PxResetOn(int portinx) { RCC->APB2PRSTR |= BIT(portinx+2); cb(); }
INLINE void RCC_PxResetOff(int portinx) { RCC->APB2PRSTR &= ~BIT(portinx+2); cb(); }
INLINE void RCC_PxReset(int portinx) { RCC_PxResetOn(portinx); nop(); RCC_PxResetOff(portinx); }

// ADC1 module reset ON/OFF/Reset
INLINE void RCC_ADC1ResetOn(void) { RCC->APB2PRSTR |= B9; cb(); }
INLINE void RCC_ADC1ResetOff(void) { RCC->APB2PRSTR &= ~B9; cb(); }
INLINE void RCC_ADC1Reset(void) { RCC_ADC1ResetOn(); nop(); RCC_ADC1ResetOff(); }

// TIM1 module reset ON/OFF/Reset
INLINE void RCC_TIM1ResetOn(void) { RCC->APB2PRSTR |= B11; cb(); }
INLINE void RCC_TIM1ResetOff(void) { RCC->APB2PRSTR &= ~B11; cb(); }
INLINE void RCC_TIM1Reset(void) { RCC_TIM1ResetOn(); nop(); RCC_TIM1ResetOff(); }

// SPI1 module reset ON/OFF/Reset
INLINE void RCC_SPI1ResetOn(void) { RCC->APB2PRSTR |= B12; cb(); }
INLINE void RCC_SPI1ResetOff(void) { RCC->APB2PRSTR &= ~B12; cb(); }
INLINE void RCC_SPI1Reset(void) { RCC_SPI1ResetOn(); nop(); RCC_SPI1ResetOff(); }

// USART1 module reset ON/OFF/Reset
INLINE void RCC_USART1ResetOn(void) { RCC->APB2PRSTR |= B14; cb(); }
INLINE void RCC_USART1ResetOff(void) { RCC->APB2PRSTR &= ~B14; cb(); }
INLINE void RCC_USART1Reset(void) { RCC_USART1ResetOn(); nop(); RCC_USART1ResetOff(); }

// TIM2 module reset ON/OFF/Reset
INLINE void RCC_TIM2ResetOn(void) { RCC->APB1PRSTR |= B0; cb(); }
INLINE void RCC_TIM2ResetOff(void) { RCC->APB1PRSTR &= ~B0; cb(); }
INLINE void RCC_TIM2Reset(void) { RCC_TIM2ResetOn(); nop(); RCC_TIM2ResetOff(); }

// TIM3 module reset ON/OFF/Reset
INLINE void RCC_TIM3ResetOn(void) { RCC->APB1PRSTR |= B1; cb(); }
INLINE void RCC_TIM3ResetOff(void) { RCC->APB1PRSTR &= ~B1; cb(); }
INLINE void RCC_TIM3Reset(void) { RCC_TIM3ResetOn(); nop(); RCC_TIM3ResetOff(); }

// TIM4 module reset ON/OFF/Reset
INLINE void RCC_TIM4ResetOn(void) { RCC->APB1PRSTR |= B2; cb(); }
INLINE void RCC_TIM4ResetOff(void) { RCC->APB1PRSTR &= ~B2; cb(); }
INLINE void RCC_TIM4Reset(void) { RCC_TIM4ResetOn(); nop(); RCC_TIM4ResetOff(); }

// Window watchdog reset ON/OFF/Reset
INLINE void RCC_WWDGResetOn(void) { RCC->APB1PRSTR |= B11; cb(); }
INLINE void RCC_WWDGResetOff(void) { RCC->APB1PRSTR &= ~B11; cb(); }
INLINE void RCC_WWDGReset(void) { RCC_WWDGResetOn(); nop(); RCC_WWDGResetOff(); }

// SPI2 module reset ON/OFF/Reset
INLINE void RCC_SPI2ResetOn(void) { RCC->APB1PRSTR |= B14; cb(); }
INLINE void RCC_SPI2ResetOff(void) { RCC->APB1PRSTR &= ~B14; cb(); }
INLINE void RCC_SPI2Reset(void) { RCC_SPI2ResetOn(); nop(); RCC_SPI2ResetOff(); }

// USART2 module reset ON/OFF/Reset
INLINE void RCC_USART2ResetOn(void) { RCC->APB1PRSTR |= B17; cb(); }
INLINE void RCC_USART2ResetOff(void) { RCC->APB1PRSTR &= ~B17; cb(); }
INLINE void RCC_USART2Reset(void) { RCC_USART2ResetOn(); nop(); RCC_USART2ResetOff(); }

// USART3 module reset ON/OFF/Reset
INLINE void RCC_USART3ResetOn(void) { RCC->APB1PRSTR |= B18; cb(); }
INLINE void RCC_USART3ResetOff(void) { RCC->APB1PRSTR &= ~B18; cb(); }
INLINE void RCC_USART3Reset(void) { RCC_USART3ResetOn(); nop(); RCC_USART3ResetOff(); }

// USART4 module reset ON/OFF/Reset
INLINE void RCC_USART4ResetOn(void) { RCC->APB1PRSTR |= B19; cb(); }
INLINE void RCC_USART4ResetOff(void) { RCC->APB1PRSTR &= ~B19; cb(); }
INLINE void RCC_USART4Reset(void) { RCC_USART4ResetOn(); nop(); RCC_USART4ResetOff(); }

// I2C1 module reset ON/OFF/Reset
INLINE void RCC_I2C1ResetOn(void) { RCC->APB1PRSTR |= B21; cb(); }
INLINE void RCC_I2C1ResetOff(void) { RCC->APB1PRSTR &= ~B21; cb(); }
INLINE void RCC_I2C1Reset(void) { RCC_I2C1ResetOn(); nop(); RCC_I2C1ResetOff(); }

// I2C2 module reset ON/OFF/Reset
INLINE void RCC_I2C2ResetOn(void) { RCC->APB1PRSTR |= B22; cb(); }
INLINE void RCC_I2C2ResetOff(void) { RCC->APB1PRSTR &= ~B22; cb(); }
INLINE void RCC_I2C2Reset(void) { RCC_I2C2ResetOn(); nop(); RCC_I2C2ResetOff(); }

// CAN1 module reset ON/OFF/Reset
INLINE void RCC_CAN1ResetOn(void) { RCC->APB1PRSTR |= B25; cb(); }
INLINE void RCC_CAN1ResetOff(void) { RCC->APB1PRSTR &= ~B25; cb(); }
INLINE void RCC_CAN1Reset(void) { RCC_CAN1ResetOn(); nop(); RCC_CAN1ResetOff(); }

// Backup module reset ON/OFF/Reset
INLINE void RCC_BKPResetOn(void) { RCC->APB1PRSTR |= B27; cb(); }
INLINE void RCC_BKPResetOff(void) { RCC->APB1PRSTR &= ~B27; cb(); }
INLINE void RCC_BKPReset(void) { RCC_BKPResetOn(); nop(); RCC_BKPResetOff(); }

// Power module reset ON/OFF/Reset
INLINE void RCC_PWRResetOn(void) { RCC->APB1PRSTR |= B28; cb(); }
INLINE void RCC_PWRResetOff(void) { RCC->APB1PRSTR &= ~B28; cb(); }
INLINE void RCC_PWRReset(void) { RCC_PWRResetOn(); nop(); RCC_PWRResetOff(); }

// LPTIM module reset ON/OFF/Reset
INLINE void RCC_LPTIMResetOn(void) { RCC->APB1PRSTR |= B31; cb(); }
INLINE void RCC_LPTIMResetOff(void) { RCC->APB1PRSTR &= ~B31; cb(); }
INLINE void RCC_LPTIMReset(void) { RCC_LPTIMResetOn(); nop(); RCC_LPTIMResetOff(); }

// USBFS module reset ON/OFF/Reset
INLINE void RCC_USBFSResetOn(void) { RCC->AHBRSTR |= B12; cb(); }
INLINE void RCC_USBFSResetOff(void) { RCC->AHBRSTR &= ~B12; cb(); }
INLINE void RCC_USBFSReset(void) { RCC_USBFSResetOn(); nop(); RCC_USBFSResetOff(); }

// USBPD reset ON/OFF/Reset
INLINE void RCC_USBPDResetOn(void) { RCC->AHBRSTR |= B17; cb(); }
INLINE void RCC_USBPDResetOff(void) { RCC->AHBRSTR &= ~B17; cb(); }
INLINE void RCC_USBPDReset(void) { RCC_USBPDResetOn(); nop(); RCC_USBPDResetOff(); }

// Backup domain reset ON/OFF/Reset
INLINE void RCC_BDResetOn(void) { RCC->BDCTLR |= B16; cb(); }
INLINE void RCC_BDResetOff(void) { RCC->BDCTLR &= ~B16; cb(); }
INLINE void RCC_BDReset(void) { RCC_BDResetOn(); nop(); RCC_BDResetOff(); }

// --- Peripheral clock

// DMA1 module clock Enable/Disable
INLINE void RCC_DMA1ClkEnable(void) { RCC->AHBPCENR |= B0; cb(); }
INLINE void RCC_DMA1ClkDisable(void) { RCC->AHBPCENR &= ~B0; cb(); }

// SRAM module clock Enable/Disable (enabled by default)
INLINE void RCC_SRAMClkEnable(void) { RCC->AHBPCENR |= B2; cb(); }
INLINE void RCC_SRAMClkDisable(void) { RCC->AHBPCENR &= ~B2; cb(); }

// CRC module clock Enable/Disable
INLINE void RCC_CRCClkEnable(void) { RCC->AHBPCENR |= B6; cb(); }
INLINE void RCC_CRCClkDisable(void) { RCC->AHBPCENR &= ~B6; cb(); }

// USBFS module clock Enable/Disable (enabled by default)
INLINE void RCC_USBFSClkEnable(void) { RCC->AHBPCENR |= B12; cb(); }
INLINE void RCC_USBFSClkDisable(void) { RCC->AHBPCENR &= ~B12; cb(); }

// USBPD clock Enable/Disable (enabled by default)
INLINE void RCC_USBPDClkEnable(void) { RCC->AHBPCENR |= B17; cb(); }
INLINE void RCC_USBPDClkDisable(void) { RCC->AHBPCENR &= ~B17; cb(); }

// I/O auxiliary function module clock Enable/Disable
INLINE void RCC_AFIClkEnable(void) { RCC->APB2PCENR |= B0; cb(); }
INLINE void RCC_AFIClkDisable(void) { RCC->APB2PCENR &= ~B0; cb(); }

// Px port (0=PA, 1=PB, ...) module clock Enable/Disable
INLINE void RCC_PxClkEnable(int portinx) { RCC->APB2PCENR |= (1<<(portinx+2)); cb(); }
INLINE void RCC_PxClkDisable(int portinx) { RCC->APB2PCENR &= ~(1<<(portinx+2)); cb(); }

// PA port module clock Enable/Disable
INLINE void RCC_PAClkEnable(void) { RCC->APB2PCENR |= B2; cb(); }
INLINE void RCC_PAClkDisable(void) { RCC->APB2PCENR &= ~B2; cb(); }

// PB port module clock Enable/Disable
INLINE void RCC_PBClkEnable(void) { RCC->APB2PCENR |= B3; cb(); }
INLINE void RCC_PBClkDisable(void) { RCC->APB2PCENR &= ~B3; cb(); }

// PC port module clock Enable/Disable
INLINE void RCC_PCClkEnable(void) { RCC->APB2PCENR |= B4; cb(); }
INLINE void RCC_PCClkDisable(void) { RCC->APB2PCENR &= ~B4; cb(); }

// PD port module clock Enable/Disable
INLINE void RCC_PDClkEnable(void) { RCC->APB2PCENR |= B5; cb(); }
INLINE void RCC_PDClkDisable(void) { RCC->APB2PCENR &= ~B5; cb(); }

// ADC1 module clock Enable/Disable
INLINE void RCC_ADC1ClkEnable(void) { RCC->APB2PCENR |= B9; cb(); }
INLINE void RCC_ADC1ClkDisable(void) { RCC->APB2PCENR &= ~B9; cb(); }

// TIM1 module clock Enable/Disable
INLINE void RCC_TIM1ClkEnable(void) { RCC->APB2PCENR |= B11; cb(); }
INLINE void RCC_TIM1ClkDisable(void) { RCC->APB2PCENR &= ~B11; cb(); }

// SPI1 module clock Enable/Disable
INLINE void RCC_SPI1ClkEnable(void) { RCC->APB2PCENR |= B12; cb(); }
INLINE void RCC_SPI1ClkDisable(void) { RCC->APB2PCENR &= ~B12; cb(); }

// USART1 module clock Enable/Disable
INLINE void RCC_USART1ClkEnable(void) { RCC->APB2PCENR |= B14; cb(); }
INLINE void RCC_USART1ClkDisable(void) { RCC->APB2PCENR &= ~B14; cb(); }

// TIM2 module clock Enable/Disable
INLINE void RCC_TIM2ClkEnable(void) { RCC->APB1PCENR |= B0; cb(); }
INLINE void RCC_TIM2ClkDisable(void) { RCC->APB1PCENR &= ~B0; cb(); }

// TIM3 module clock Enable/Disable
INLINE void RCC_TIM3ClkEnable(void) { RCC->APB1PCENR |= B1; cb(); }
INLINE void RCC_TIM3ClkDisable(void) { RCC->APB1PCENR &= ~B1; cb(); }

// TIM4 module clock Enable/Disable
INLINE void RCC_TIM4ClkEnable(void) { RCC->APB1PCENR |= B2; cb(); }
INLINE void RCC_TIM4ClkDisable(void) { RCC->APB1PCENR &= ~B2; cb(); }

// Window watchdog clock Enable/Disable
INLINE void RCC_WWDGClkEnable(void) { RCC->APB1PCENR |= B11; cb(); }
INLINE void RCC_WWDGClkDisable(void) { RCC->APB1PCENR &= ~B11; cb(); }

// SPI2 module clock Enable/Disable
INLINE void RCC_SPI2ClkEnable(void) { RCC->APB1PCENR |= B14; cb(); }
INLINE void RCC_SPI2ClkDisable(void) { RCC->APB1PCENR &= ~B14; cb(); }

// USART2 module clock Enable/Disable
INLINE void RCC_USART2ClkEnable(void) { RCC->APB1PCENR |= B17; cb(); }
INLINE void RCC_USART2ClkDisable(void) { RCC->APB1PCENR &= ~B17; cb(); }

// USART3 module clock Enable/Disable
INLINE void RCC_USART3ClkEnable(void) { RCC->APB1PCENR |= B18; cb(); }
INLINE void RCC_USART3ClkDisable(void) { RCC->APB1PCENR &= ~B18; cb(); }

// USART4 module clock Enable/Disable
INLINE void RCC_USART4ClkEnable(void) { RCC->APB1PCENR |= B19; cb(); }
INLINE void RCC_USART4ClkDisable(void) { RCC->APB1PCENR &= ~B19; cb(); }

// I2C1 module clock Enable/Disable
INLINE void RCC_I2C1ClkEnable(void) { RCC->APB1PCENR |= B21; cb(); }
INLINE void RCC_I2C1ClkDisable(void) { RCC->APB1PCENR &= ~B21; cb(); }

// I2C2 module clock Enable/Disable
INLINE void RCC_I2C2ClkEnable(void) { RCC->APB1PCENR |= B22; cb(); }
INLINE void RCC_I2C2ClkDisable(void) { RCC->APB1PCENR &= ~B22; cb(); }

// CAN1 module clock Enable/Disable
INLINE void RCC_CAN1ClkEnable(void) { RCC->APB1PCENR |= B25; cb(); }
INLINE void RCC_CAN1ClkDisable(void) { RCC->APB1PCENR &= ~B25; cb(); }

// Backup module clock Enable/Disable
INLINE void RCC_BKPClkEnable(void) { RCC->APB1PCENR |= B27; cb(); }
INLINE void RCC_BKPClkDisable(void) { RCC->APB1PCENR &= ~B27; cb(); }

// Power module clock Enable/Disable
INLINE void RCC_PWRClkEnable(void) { RCC->APB1PCENR |= B28; cb(); }
INLINE void RCC_PWRClkDisable(void) { RCC->APB1PCENR &= ~B28; cb(); }

// LPTIM module clock Enable/Disable
INLINE void RCC_LPTIMClkEnable(void) { RCC->APB1PCENR |= B31; cb(); }
INLINE void RCC_LPTIMClkDisable(void) { RCC->APB1PCENR &= ~B31; cb(); }

// Multiply AHB peripheral clock Enable/Disable (use combination of RCC_AHBCLK_* flags)
INLINE void RCC_AHBClkEnable(u32 mask) { RCC->AHBPCENR |= mask; cb(); }
INLINE void RCC_AHBClkDisable(u32 mask) { RCC->AHBPCENR &= ~mask; cb(); }

// Multiply APB2 peripheral clock Enable/Disable (use combination of RCC_APB2CLK_* flags)
INLINE void RCC_APB2ClkEnable(u32 mask) { RCC->APB2PCENR |= mask; cb(); }
INLINE void RCC_APB2ClkDisable(u32 mask) { RCC->APB2PCENR &= ~mask; cb(); }

// Multiply APB1 peripheral clock Enable/Disable (use combination of RCC_APB1CLK_* flags)
INLINE void RCC_APB1ClkEnable(u32 mask) { RCC->APB1PCENR |= mask; cb(); }
INLINE void RCC_APB1ClkDisable(u32 mask) { RCC->APB1PCENR &= ~mask; cb(); }

// --- RTC clock

// Select RTC clock source RCC_RTCSRC_*
// - Once the RTC clock source is selected and enabled, it cannot be changed until next reset backup domain.
INLINE void RCC_RTCSrc(int src) { RCC->BDCTLR = (RCC->BDCTLR & ~(3 << 8)) | (src << 8); }

// Enable/Disable RTC clock
INLINE void RCC_RTCEnable(void) { RCC->BDCTLR |= B15; }
INLINE void RCC_RTCDisable(void) { RCC->BDCTLR &= ~B15; }

// --- Reset

// Check occurence of NRST pin reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetPinRes(void) { return (RCC->RSTSCKR & B26) != 0; }

// Check occurence of power reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetPwrRes(void) { return (RCC->RSTSCKR & B27) != 0; }

// Check occurence of software reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetSwRes(void) { return (RCC->RSTSCKR & B28) != 0; }

// Check occurence of independent watchdog reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetIwdgRes(void) { return (RCC->RSTSCKR & B29) != 0; }

// Check occurence of window watchdog reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetWwdgRes(void) { return (RCC->RSTSCKR & B30) != 0; }

// Check occurence of low-power reset flag (set by hardware, cleared by software)
INLINE Bool RCC_GetLowPwrRes(void) { return (RCC->RSTSCKR & B31) != 0; }

// Clear all reset flags
INLINE void RCC_ClrRes(void) { RCC->RSTSCKR |= B24; }

// System initialize
void SystemInit(void);

// System terminate
void SystemTerm(void);

// exit application and reset to boot loader (execute software reset)
void ResetToBootLoader(void);

#ifdef __cplusplus
}
#endif

#endif // _SDK_RCC_H
