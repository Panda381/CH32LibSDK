
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
#define PLLCLK_MUL	18		// PLL multiplier 2 - 18 (max. output 144MHz)
#endif

#ifndef SYSCLK_DIV
#define SYSCLK_DIV	1		// System clock divider: 1, 2, 4, 8, 16, 64, 128, 256, 512 (max. output 144MHz)
#endif

#ifndef APB1CLK_DIV
#define APB1CLK_DIV	1		// APB1 PCLK1 divider: 1, 2, 4, 8, 16 (max. output 144MHz)
#endif

#ifndef APB2CLK_DIV
#define APB2CLK_DIV	1		// APB2 PCLK1 divider: 1, 2, 4, 8, 16 (max. output 144MHz)
#endif

#ifndef ADCCLK_DIV
#define ADCCLK_DIV	1		// ADC clock divider: 1, 2, 4, 6, 8 (max. 14 MHz)
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
	io32	CFGR2;		// 0x2C: Clock configuration register 2
} RCC_t;
STATIC_ASSERT(sizeof(RCC_t) == 0x30, "Incorrect RCC_t!");
#define RCC	((RCC_t*)RCC_BASE)

// OSC registers 0x4002202C
typedef struct {
	io32	HSE_CAL_CTRL;		// 0x00 (xx2C): HSE crystal oscillator calibration control register
	io32	res;			// 0x04 (xx30): ... reserved
	io16	res2;			// 0x08 (xx34): ... reserved
	io16	LSI32K_TUNE;		// 0x0A (xx36): LSI crystal oscillator calibration tune register
	io32	res3[4];		// 0x0C (xx38): ... reserved
	io8	res4;			// 0x1C (xx48): ... reserved
	io8	LSI32K_CAL_CFG;		// 0x1D (xx49): LSI crystal oscillator calibration configuration register
	io16	res5;			// 0x1E (xx4A): ... reserved
	io16	LSI32K_CAL_STATR;	// 0x20 (xx4C): LSI crystal oscillator calibration status register
	io8	LSI32K_CAL_OV_CNT;	// 0x22 (xx4E): LSI crystal oscillator calibration counter
	io8	LSI32K_CAL_CTRL;	// 0x23 (xx4F): LSI crystal oscillator calibration control register
} OSC_t;
STATIC_ASSERT(sizeof(OSC_t) == 0x24, "Incorrect OSC_t!");
#define OSC	((OSC_t*)OSC_BASE)

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

// APB1 and APB2 clock divider (from HCLK; cannot exceed 144MHz))
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

// PLL multiplication (PLL output cannot exceed 144MHz)
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

// PLL2 and PLL3 multiplication factor
#define RCC_PLL2_MUL25		0	// PLL input clock * 2.5
#define RCC_PLL2_MUL125		1	// PLL input clock * 12.5
#define RCC_PLL2_MUL4		2	// PLL input clock * 4
#define RCC_PLL2_MUL5		3	// PLL input clock * 5
#define RCC_PLL2_MUL6		4	// PLL input clock * 6
#define RCC_PLL2_MUL7		5	// PLL input clock * 7
#define RCC_PLL2_MUL8		6	// PLL input clock * 8
#define RCC_PLL2_MUL9		7	// PLL input clock * 9
#define RCC_PLL2_MUL10		8	// PLL input clock * 10
#define RCC_PLL2_MUL11		9	// PLL input clock * 11
#define RCC_PLL2_MUL12		10	// PLL input clock * 12
#define RCC_PLL2_MUL13		11	// PLL input clock * 13
#define RCC_PLL2_MUL14		12	// PLL input clock * 14
#define RCC_PLL2_MUL15		13	// PLL input clock * 15
#define RCC_PLL2_MUL16		14	// PLL input clock * 16
#define RCC_PLL2_MUL20		15	// PLL input clock * 20

// Gigabit Ethernet 125M clock source
#define RCC_ETH1GSRC_PLL2	0	// PLL2 VCO
#define RCC_ETH1GSRC_PLL3	1	// PLL3 VCO
#define RCC_ETH1GSRC_PB1	2	// PB1 input
//#define RCC_ETH1GSRC_PB1	3	// PB1 input

// USBHS PLL reference clock selection (USBHSPLLSRC/USBHSDIV)
#define RCC_USBHS_REF3		0	// 3 MHz
#define RCC_USBHS_REF4		1	// 4 MHz
#define RCC_USBHS_REF8		2	// 8 MHz
#define RCC_USBHS_REF5		3	// 5 MHz

// USB PLL prescaler (result frequency should be 48 MHz)
#define RCC_USBPRE_DIV1		0	// USB PLL 1-division for PLLCLK=48MHz
#define RCC_USBPRE_DIV2		1	// USB PLL 2-division for PLLCLK=96MHz
#define RCC_USBPRE_DIV3		2	// USB PLL 3-division for PLLCLK=144MHz
#define RCC_USBPRE_DIV5		3	// USB PLL 5-division for PLLCLK=240MHz

// MCO pin clock output
#define RCC_MCO_NONE		0	// (0-3) no clock output
#define RCC_MCO_SYSCLK		4	// system clock
#define RCC_MCO_HSI		5	// HSI internal oscillator 8MHz
#define RCC_MCO_HSE		6	// HSE external oscillator
#define RCC_MCO_PLL		7	// PLL clock output divided by 2
#define RCC_MCO_PLL2		8	// PLL2 clock output
#define RCC_MCO_PLL3DIV		9	// PLL3 clock output divided by 2
#define RCC_MCO_XT1		10	// XT1 clock output
#define RCC_MCO_PLL3		11	// PLL3 clock output

// AHB peripheral clock mask
#define RCC_AHBCLK_DMA1		B0	// DMA1 module clock mask
#define RCC_AHBCLK_DMA2		B1	// DMA2 module clock mask
#define RCC_AHBCLK_SRAM		B2	// SRAM clock mask
#define RCC_AHBCLK_CRC		B6	// CRC clock mask
#define RCC_AHBCLK_FSMC		B8	// FSMC clock mask
#define RCC_AHBCLK_RNG		B9	// RNG clock mask
#define RCC_AHBCLK_SDIO		B10	// SDIO clock mask
#define RCC_AHBCLK_USBHS	B11	// USBHS clock mask
#define RCC_AHBCLK_USBOTG	B12	// USBOTG clock mask
#define RCC_AHBCLK_DVP		B13	// DVP clock mask
#define RCC_AHBCLK_ETHMAC	B14	// ETHMAC clock mask
#define RCC_AHBCLK_ETHMACTX	B15	// ETHMACTX clock mask
#define RCC_AHBCLK_ETHMACRX	B16	// ETHMACRX clock mask
#define RCC_AHBCLK_BLEC		B16	// BLEC clock mask
#define RCC_AHBCLK_BLES		B17	// BLES clock mask

// APB2 peripheral clock mask
#define RCC_APB2CLK_AFI		B0	// I/O auxiliary function module clock mask
#define RCC_APB2CLK_PA		B2	// PA port module clock mask
#define RCC_APB2CLK_PB		B3	// PB port module clock mask
#define RCC_APB2CLK_PC		B4	// PC port module clock mask
#define RCC_APB2CLK_PD		B5	// PD port module clock mask
#define RCC_APB2CLK_PE		B6	// PE port module clock mask
#define RCC_APB2CLK_ADC1	B9	// ADC1 module clock mask
#define RCC_APB2CLK_ADC2	B10	// ADC2 module clock mask
#define RCC_APB2CLK_TIM1	B11	// TIM1 module clock mask
#define RCC_APB2CLK_SPI1	B12	// SPI1 module clock mask
#define RCC_APB2CLK_TIM8	B13	// TIM8 module clock mask
#define RCC_APB2CLK_USART1	B14	// USART1 module clock mask
#define RCC_APB2CLK_TIM9	B19	// TIM9 module clock mask
#define RCC_APB2CLK_TIM10	B20	// TIM10 module clock mask

// APB1 peripheral clock mask
#define RCC_APB1CLK_TIM2	B0	// TIM2 module clock mask
#define RCC_APB1CLK_TIM3	B1	// TIM3 module clock mask
#define RCC_APB1CLK_TIM4	B2	// TIM4 module clock mask
#define RCC_APB1CLK_TIM5	B3	// TIM5 module clock mask
#define RCC_APB1CLK_TIM6	B4	// TIM6 module clock mask
#define RCC_APB1CLK_TIM7	B5	// TIM7 module clock mask
#define RCC_APB1CLK_USART6	B6	// USART6 module clock mask
#define RCC_APB1CLK_USART7	B7	// USART7 module clock mask
#define RCC_APB1CLK_USART8	B8	// USART8 module clock mask
#define RCC_APB1CLK_WWDG	B11	// Window watchdog clock mask
#define RCC_APB1CLK_SPI2	B14	// SPI2 module clock mask
#define RCC_APB1CLK_SPI3	B15	// SPI3 module clock mask
#define RCC_APB1CLK_USART2	B17	// USART2 module clock mask
#define RCC_APB1CLK_USART3	B18	// USART3 module clock mask
#define RCC_APB1CLK_USART4	B19	// USART4 module clock mask
#define RCC_APB1CLK_USART5	B20	// USART5 module clock mask
#define RCC_APB1CLK_I2C1	B21	// I2C1 module clock mask
#define RCC_APB1CLK_I2C2	B22	// I2C2 module clock mask
#define RCC_APB1CLK_USBD	B23	// USBD module clock mask
#define RCC_APB1CLK_CAN1	B25	// CAN1 module clock mask
#define RCC_APB1CLK_CAN2	B26	// CAN2 module clock mask
#define RCC_APB1CLK_BKP		B27	// Backup module clock mask
#define RCC_APB1CLK_PWR		B28	// Power module clock mask
#define RCC_APB1CLK_DAC		B29	// DAC module clock mask

// RTC clock source
#define RCC_RTCSRC_NO		0	// no clock
#define RCC_RTCSRC_LSE		1	// LSE oscillator
#define RCC_RTCSRC_LSI		2	// LSI oscillator
#define RCC_RTCSRC_HSE		3	// HSE oscillator divided

// HSE internal match capacitor adjustment
#define RCC_HSEC_8PF		0	// 8pF
#define RCC_HSEC_10PF		1	// 10pF
#define RCC_HSEC_12PF		2	// 12pF
#define RCC_HSEC_14PF		3	// 14pF
#define RCC_HSEC_16PF		4	// 16pF
#define RCC_HSEC_18PF		5	// 18pF
#define RCC_HSEC_20PF		6	// 20pF
#define RCC_HSEC_22PF		7	// 22pF

// LSI32K calibration duration
#define RCC_CNTVLU_2		0	// 2 CK32K cycles
#define RCC_CNTVLU_4		1	// 4 CK32K cycles
#define RCC_CNTVLU_32		2	// 32 CK32K cycles
#define RCC_CNTVLU_64		3	// 64 CK32K cycles
#define RCC_CNTVLU_128		4	// 128 CK32K cycles
#define RCC_CNTVLU_256		5	// 256 CK32K cycles
#define RCC_CNTVLU_512		6	// 512 CK32K cycles
#define RCC_CNTVLU_1024		7	// 1024 CK32K cycles
#define RCC_CNTVLU_1088		8	// 1088 CK32K cycles
#define RCC_CNTVLU_1152		9	// 1152 CK32K cycles
#define RCC_CNTVLU_1216		10	// 1216 CK32K cycles
#define RCC_CNTVLU_1280		11	// 1280 CK32K cycles
#define RCC_CNTVLU_2000		12	// 2000 CK32K cycles

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

// Start HSE oscillator and wait to be stable (bypass = bypass HSE crystal; returns False on error)
Bool RCC_HSEStart(Bool bypass);

// --- LSI low-speed internall oscillator

// Enable/Disable LSI low speed clock 40KHz
INLINE void RCC_LSIEnable(void) { RCC->RSTSCKR |= B0; }
INLINE void RCC_LSIDisable(void) { RCC->RSTSCKR &= ~B0; }

// Check if LSI low speed clock 40KHz is stable
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

// Enable/Disable PLL2 clock (default disabled)
// - Disabled by hardware after entering standby low-power mode.
INLINE void RCC_PLL2Enable(void) { RCC->CTLR |= B26; }
INLINE void RCC_PLL2Disable(void) { RCC->CTLR &= ~B26; }

// Check if PLL2 clock is ready
INLINE Bool RCC_PLL2IsReady(void) { return (RCC->CTLR & B27) != 0; }

// Enable/Disable PLL3 clock (default disabled)
// - Disabled by hardware after entering standby low-power mode.
INLINE void RCC_PLL3Enable(void) { RCC->CTLR |= B28; }
INLINE void RCC_PLL3Disable(void) { RCC->CTLR &= ~B28; }

// Check if PLL3 clock is ready
INLINE Bool RCC_PLL3IsReady(void) { return (RCC->CTLR & B29) != 0; }

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

// Set PLL multiplication factor RCC_PLL_MUL* (PLL should be off; PLL output cannot exceed 144MHz)
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

// Set ADC clock divider RCC_ADCCLK_DIV* (should not exceed 14MHz) (default 0 = divided by 2)
INLINE void RCC_ADCDiv(int div) { RCC->CFGR0 = (RCC->CFGR0 & ~(3 << 14)) | (div << 14); }

// Get ADC clock divider RCC_ADCCLK_DIV*
INLINE u8 RCC_GetADCDiv(void) { return (u8)((RCC->CFGR0 >> 14) & 3); }

// Get ADC clock divider value 2..8
INLINE u8 RCC_GetADCDivVal(void) { return (u8)((RCC_GetADCDiv()+1)<<1); }

// ADC clock duty cycle adjustment to 1/2 or 3/4 high-level
INLINE void RCC_ADCClkAdj12(void) { RCC->CFGR0 &= ~(B30|B31); }
INLINE void RCC_ADCClkAdj34(void) { RCC->CFGR0 |= B30|B31; }

// Set MCO pin clock output source RCC_MCO_* (default 0 = disabled)
INLINE void RCC_MCOClkSrc(int src) { RCC->CFGR0 = (RCC->CFGR0 & ~(0x0f << 24)) | (src << 24); }

// Set Ethernet clock source prescaler 1 or 2
INLINE void RCC_EthPre1(void) { RCC->CFGR0 &= ~B28; }
INLINE void RCC_EthPre2(void) { RCC->CFGR0 |= B28; }

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

// PLL2 clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_PLL2IntEnable(void) { RCC->INTR |= B13; }
INLINE void RCC_PLL2IntDisable(void) { RCC->INTR &= ~B13; }
INLINE Bool RCC_PLL2Int(void) { return (RCC->INTR >> 5) & 1; }
INLINE void RCC_PLL2IntClear(void) { RCC->INTR |= B21; }

// PLL3 clock-ready interrupt Enable/Disable/Flag/Clear
INLINE void RCC_PLL3IntEnable(void) { RCC->INTR |= B14; }
INLINE void RCC_PLL3IntDisable(void) { RCC->INTR &= ~B14; }
INLINE Bool RCC_PLL3Int(void) { return (RCC->INTR >> 6) & 1; }
INLINE void RCC_PLL3IntClear(void) { RCC->INTR |= B22; }

// CSS HSE clock failure Enable/Disable/Flag/Clear
//  - Triggers CSSF and NMI interrupt when HSE fails
INLINE void RCC_CSSEnable(void) { RCC->CTLR |= B19; }
INLINE void RCC_CSSDisable(void) { RCC->CTLR &= ~B19; }
INLINE Bool RCC_CSSInt(void) { return (RCC->INTR & B7) != 0; }
INLINE void RCC_CSSIntClear(void) { RCC->INTR |= B23; }

// Clear all interrupt flags
INLINE void RCC_IntClear(void) { RCC->INTR |= B16|B17|B18|B19|B20|B21|B22|B23; }

// Disable all interrupt flags
INLINE void RCC_IntDisable(void) { RCC->INTR &= ~(B8|B9|B10|B11|B12|B13|B14); }

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

// PE port module reset ON/OFF/Reset
INLINE void RCC_PEResetOn(void) { RCC->APB2PRSTR |= B6; cb(); }
INLINE void RCC_PEResetOff(void) { RCC->APB2PRSTR &= ~B6; cb(); }
INLINE void RCC_PEReset(void) { RCC_PEResetOn(); nop(); RCC_PEResetOff(); }

// Port module reset (use port index PORT*_INX)
INLINE void RCC_PxResetOn(int portinx) { RCC->APB2PRSTR |= BIT(portinx+2); cb(); }
INLINE void RCC_PxResetOff(int portinx) { RCC->APB2PRSTR &= ~BIT(portinx+2); cb(); }
INLINE void RCC_PxReset(int portinx) { RCC_PxResetOn(portinx); nop(); RCC_PxResetOff(portinx); }

// ADC1 module reset ON/OFF/Reset
INLINE void RCC_ADC1ResetOn(void) { RCC->APB2PRSTR |= B9; cb(); }
INLINE void RCC_ADC1ResetOff(void) { RCC->APB2PRSTR &= ~B9; cb(); }
INLINE void RCC_ADC1Reset(void) { RCC_ADC1ResetOn(); nop(); RCC_ADC1ResetOff(); }

// ADC2 module reset ON/OFF/Reset
INLINE void RCC_ADC2ResetOn(void) { RCC->APB2PRSTR |= B10; cb(); }
INLINE void RCC_ADC2ResetOff(void) { RCC->APB2PRSTR &= ~B10; cb(); }
INLINE void RCC_ADC2Reset(void) { RCC_ADC2ResetOn(); nop(); RCC_ADC2ResetOff(); }

// TIM1 module reset ON/OFF/Reset
INLINE void RCC_TIM1ResetOn(void) { RCC->APB2PRSTR |= B11; cb(); }
INLINE void RCC_TIM1ResetOff(void) { RCC->APB2PRSTR &= ~B11; cb(); }
INLINE void RCC_TIM1Reset(void) { RCC_TIM1ResetOn(); nop(); RCC_TIM1ResetOff(); }

// SPI1 module reset ON/OFF/Reset
INLINE void RCC_SPI1ResetOn(void) { RCC->APB2PRSTR |= B12; cb(); }
INLINE void RCC_SPI1ResetOff(void) { RCC->APB2PRSTR &= ~B12; cb(); }
INLINE void RCC_SPI1Reset(void) { RCC_SPI1ResetOn(); nop(); RCC_SPI1ResetOff(); }

// TIM8 module reset ON/OFF/Reset
INLINE void RCC_TIM8ResetOn(void) { RCC->APB2PRSTR |= B13; cb(); }
INLINE void RCC_TIM8ResetOff(void) { RCC->APB2PRSTR &= ~B13; cb(); }
INLINE void RCC_TIM8Reset(void) { RCC_TIM8ResetOn(); nop(); RCC_TIM8ResetOff(); }

// USART1 module reset ON/OFF/Reset
INLINE void RCC_USART1ResetOn(void) { RCC->APB2PRSTR |= B14; cb(); }
INLINE void RCC_USART1ResetOff(void) { RCC->APB2PRSTR &= ~B14; cb(); }
INLINE void RCC_USART1Reset(void) { RCC_USART1ResetOn(); nop(); RCC_USART1ResetOff(); }

// TIM9 module reset ON/OFF/Reset
INLINE void RCC_TIM9ResetOn(void) { RCC->APB2PRSTR |= B19; cb(); }
INLINE void RCC_TIM9ResetOff(void) { RCC->APB2PRSTR &= ~B19; cb(); }
INLINE void RCC_TIM9Reset(void) { RCC_TIM9ResetOn(); nop(); RCC_TIM9ResetOff(); }

// TIM10 module reset ON/OFF/Reset
INLINE void RCC_TIM10ResetOn(void) { RCC->APB2PRSTR |= B20; cb(); }
INLINE void RCC_TIM10ResetOff(void) { RCC->APB2PRSTR &= ~B20; cb(); }
INLINE void RCC_TIM10Reset(void) { RCC_TIM10ResetOn(); nop(); RCC_TIM10ResetOff(); }

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

// TIM5 module reset ON/OFF/Reset
INLINE void RCC_TIM5ResetOn(void) { RCC->APB1PRSTR |= B3; cb(); }
INLINE void RCC_TIM5ResetOff(void) { RCC->APB1PRSTR &= ~B3; cb(); }
INLINE void RCC_TIM5Reset(void) { RCC_TIM5ResetOn(); nop(); RCC_TIM5ResetOff(); }

// TIM6 module reset ON/OFF/Reset
INLINE void RCC_TIM6ResetOn(void) { RCC->APB1PRSTR |= B4; cb(); }
INLINE void RCC_TIM6ResetOff(void) { RCC->APB1PRSTR &= ~B4; cb(); }
INLINE void RCC_TIM6Reset(void) { RCC_TIM6ResetOn(); nop(); RCC_TIM6ResetOff(); }

// TIM7 module reset ON/OFF/Reset
INLINE void RCC_TIM7ResetOn(void) { RCC->APB1PRSTR |= B5; cb(); }
INLINE void RCC_TIM7ResetOff(void) { RCC->APB1PRSTR &= ~B5; cb(); }
INLINE void RCC_TIM7Reset(void) { RCC_TIM7ResetOn(); nop(); RCC_TIM7ResetOff(); }

// USART6 module reset ON/OFF/Reset
INLINE void RCC_USART6ResetOn(void) { RCC->APB1PRSTR |= B6; cb(); }
INLINE void RCC_USART6ResetOff(void) { RCC->APB1PRSTR &= ~B6; cb(); }
INLINE void RCC_USART6Reset(void) { RCC_USART6ResetOn(); nop(); RCC_USART6ResetOff(); }

// USART7 module reset ON/OFF/Reset
INLINE void RCC_USART7ResetOn(void) { RCC->APB1PRSTR |= B7; cb(); }
INLINE void RCC_USART7ResetOff(void) { RCC->APB1PRSTR &= ~B7; cb(); }
INLINE void RCC_USART7Reset(void) { RCC_USART7ResetOn(); nop(); RCC_USART7ResetOff(); }

// USART8 module reset ON/OFF/Reset
INLINE void RCC_USART8ResetOn(void) { RCC->APB1PRSTR |= B8; cb(); }
INLINE void RCC_USART8ResetOff(void) { RCC->APB1PRSTR &= ~B8; cb(); }
INLINE void RCC_USART8Reset(void) { RCC_USART8ResetOn(); nop(); RCC_USART8ResetOff(); }

// Window watchdog reset ON/OFF/Reset
INLINE void RCC_WWDGResetOn(void) { RCC->APB1PRSTR |= B11; cb(); }
INLINE void RCC_WWDGResetOff(void) { RCC->APB1PRSTR &= ~B11; cb(); }
INLINE void RCC_WWDGReset(void) { RCC_WWDGResetOn(); nop(); RCC_WWDGResetOff(); }

// SPI2 module reset ON/OFF/Reset
INLINE void RCC_SPI2ResetOn(void) { RCC->APB1PRSTR |= B14; cb(); }
INLINE void RCC_SPI2ResetOff(void) { RCC->APB1PRSTR &= ~B14; cb(); }
INLINE void RCC_SPI2Reset(void) { RCC_SPI2ResetOn(); nop(); RCC_SPI2ResetOff(); }

// SPI3 module reset ON/OFF/Reset
INLINE void RCC_SPI3ResetOn(void) { RCC->APB1PRSTR |= B15; cb(); }
INLINE void RCC_SPI3ResetOff(void) { RCC->APB1PRSTR &= ~B15; cb(); }
INLINE void RCC_SPI3Reset(void) { RCC_SPI3ResetOn(); nop(); RCC_SPI3ResetOff(); }

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

// USART5 module reset ON/OFF/Reset
INLINE void RCC_USART5ResetOn(void) { RCC->APB1PRSTR |= B20; cb(); }
INLINE void RCC_USART5ResetOff(void) { RCC->APB1PRSTR &= ~B20; cb(); }
INLINE void RCC_USART5Reset(void) { RCC_USART5ResetOn(); nop(); RCC_USART5ResetOff(); }

// I2C1 module reset ON/OFF/Reset
INLINE void RCC_I2C1ResetOn(void) { RCC->APB1PRSTR |= B21; cb(); }
INLINE void RCC_I2C1ResetOff(void) { RCC->APB1PRSTR &= ~B21; cb(); }
INLINE void RCC_I2C1Reset(void) { RCC_I2C1ResetOn(); nop(); RCC_I2C1ResetOff(); }

// I2C2 module reset ON/OFF/Reset
INLINE void RCC_I2C2ResetOn(void) { RCC->APB1PRSTR |= B22; cb(); }
INLINE void RCC_I2C2ResetOff(void) { RCC->APB1PRSTR &= ~B22; cb(); }
INLINE void RCC_I2C2Reset(void) { RCC_I2C2ResetOn(); nop(); RCC_I2C2ResetOff(); }

// USBD module reset ON/OFF/Reset
INLINE void RCC_USBDResetOn(void) { RCC->APB1PRSTR |= B23; cb(); }
INLINE void RCC_USBDResetOff(void) { RCC->APB1PRSTR &= ~B23; cb(); }
INLINE void RCC_USBDReset(void) { RCC_USBDResetOn(); nop(); RCC_USBDResetOff(); }

// CAN1 module reset ON/OFF/Reset
INLINE void RCC_CAN1ResetOn(void) { RCC->APB1PRSTR |= B25; cb(); }
INLINE void RCC_CAN1ResetOff(void) { RCC->APB1PRSTR &= ~B25; cb(); }
INLINE void RCC_CAN1Reset(void) { RCC_CAN1ResetOn(); nop(); RCC_CAN1ResetOff(); }

// CAN2 module reset ON/OFF/Reset
INLINE void RCC_CAN2ResetOn(void) { RCC->APB1PRSTR |= B26; cb(); }
INLINE void RCC_CAN2ResetOff(void) { RCC->APB1PRSTR &= ~B26; cb(); }
INLINE void RCC_CAN2Reset(void) { RCC_CAN2ResetOn(); nop(); RCC_CAN2ResetOff(); }

// Backup module reset ON/OFF/Reset
INLINE void RCC_BKPResetOn(void) { RCC->APB1PRSTR |= B27; cb(); }
INLINE void RCC_BKPResetOff(void) { RCC->APB1PRSTR &= ~B27; cb(); }
INLINE void RCC_BKPReset(void) { RCC_BKPResetOn(); nop(); RCC_BKPResetOff(); }

// Power module reset ON/OFF/Reset
INLINE void RCC_PWRResetOn(void) { RCC->APB1PRSTR |= B28; cb(); }
INLINE void RCC_PWRResetOff(void) { RCC->APB1PRSTR &= ~B28; cb(); }
INLINE void RCC_PWRReset(void) { RCC_PWRResetOn(); nop(); RCC_PWRResetOff(); }

// DAC module reset ON/OFF/Reset
INLINE void RCC_DACResetOn(void) { RCC->APB1PRSTR |= B29; cb(); }
INLINE void RCC_DACResetOff(void) { RCC->APB1PRSTR &= ~B29; cb(); }
INLINE void RCC_DACReset(void) { RCC_DACResetOn(); nop(); RCC_DACResetOff(); }

// Backup domain reset ON/OFF/Reset
INLINE void RCC_BDResetOn(void) { RCC->BDCTLR |= B16; cb(); }
INLINE void RCC_BDResetOff(void) { RCC->BDCTLR &= ~B16; cb(); }
INLINE void RCC_BDReset(void) { RCC_BDResetOn(); nop(); RCC_BDResetOff(); }

// USBOTG FS reset flag ON/OFF
INLINE void RCC_USBOTGResetOn(void) { RCC->AHBRSTR |= B12; cb(); }
INLINE void RCC_USBOTGResetOff(void) { RCC->AHBRSTR &= ~B12; cb(); }
INLINE void RCC_USBOTGReset(void) { RCC_USBOTGResetOn(); nop(); RCC_USBOTGResetOff(); }

// DVP reset flag ON/OFF
INLINE void RCC_DVPResetOn(void) { RCC->AHBRSTR |= B13; cb(); }
INLINE void RCC_DVPResetOff(void) { RCC->AHBRSTR &= ~B13; cb(); }
INLINE void RCC_DVPReset(void) { RCC_DVPResetOn(); nop(); RCC_DVPResetOff(); }

// Ethernet MAC reset flag ON/OFF
INLINE void RCC_ETHMACResetOn(void) { RCC->AHBRSTR |= B14; cb(); }
INLINE void RCC_ETHMACResetOff(void) { RCC->AHBRSTR &= ~B14; cb(); }
INLINE void RCC_ETHMACReset(void) { RCC_ETHMACResetOn(); nop(); RCC_ETHMACResetOff(); }

// --- Peripheral clock

// DMA1 module clock Enable/Disable
INLINE void RCC_DMA1ClkEnable(void) { RCC->AHBPCENR |= B0; cb(); }
INLINE void RCC_DMA1ClkDisable(void) { RCC->AHBPCENR &= ~B0; cb(); }

// DMA2 module clock Enable/Disable
INLINE void RCC_DMA2ClkEnable(void) { RCC->AHBPCENR |= B1; cb(); }
INLINE void RCC_DMA2ClkDisable(void) { RCC->AHBPCENR &= ~B1; cb(); }

// SRAM module clock Enable/Disable (enabled by default)
INLINE void RCC_SRAMClkEnable(void) { RCC->AHBPCENR |= B2; cb(); }
INLINE void RCC_SRAMClkDisable(void) { RCC->AHBPCENR &= ~B2; cb(); }

// CRC module clock Enable/Disable
INLINE void RCC_CRCClkEnable(void) { RCC->AHBPCENR |= B6; cb(); }
INLINE void RCC_CRCClkDisable(void) { RCC->AHBPCENR &= ~B6; cb(); }

// FSMC module clock Enable/Disable
INLINE void RCC_FSMCClkEnable(void) { RCC->AHBPCENR |= B8; cb(); }
INLINE void RCC_FSMCClkDisable(void) { RCC->AHBPCENR &= ~B8; cb(); }

// RNG module clock Enable/Disable
INLINE void RCC_RNGClkEnable(void) { RCC->AHBPCENR |= B9; cb(); }
INLINE void RCC_RNGClkDisable(void) { RCC->AHBPCENR &= ~B9; cb(); }

// SDIO module clock Enable/Disable
INLINE void RCC_SDIOClkEnable(void) { RCC->AHBPCENR |= B10; cb(); }
INLINE void RCC_SDIOClkDisable(void) { RCC->AHBPCENR &= ~B10; cb(); }

// USBHS module clock Enable/Disable
INLINE void RCC_USBHSClkEnable(void) { RCC->AHBPCENR |= B11; cb(); }
INLINE void RCC_USBHSClkDisable(void) { RCC->AHBPCENR &= ~B11; cb(); }

// USBOTG module clock Enable/Disable
INLINE void RCC_USBOTGClkEnable(void) { RCC->AHBPCENR |= B12; cb(); }
INLINE void RCC_USBOTGClkDisable(void) { RCC->AHBPCENR &= ~B12; cb(); }

// DVP module clock Enable/Disable
INLINE void RCC_DVPClkEnable(void) { RCC->AHBPCENR |= B13; cb(); }
INLINE void RCC_DVPClkDisable(void) { RCC->AHBPCENR &= ~B13; cb(); }

// ETHMAC module clock Enable/Disable
INLINE void RCC_ETHMACClkEnable(void) { RCC->AHBPCENR |= B14; cb(); }
INLINE void RCC_ETHMACClkDisable(void) { RCC->AHBPCENR &= ~B14; cb(); }

// ETHMACTX module clock Enable/Disable
INLINE void RCC_ETHMACTXClkEnable(void) { RCC->AHBPCENR |= B15; cb(); }
INLINE void RCC_ETHMACTXClkDisable(void) { RCC->AHBPCENR &= ~B15; cb(); }

// ETHMACRX module clock Enable/Disable
INLINE void RCC_ETHMACRXClkEnable(void) { RCC->AHBPCENR |= B16; cb(); }
INLINE void RCC_ETHMACRXClkDisable(void) { RCC->AHBPCENR &= ~B16; cb(); }

// BLEC module clock Enable/Disable
INLINE void RCC_BLECClkEnable(void) { RCC->AHBPCENR |= B16; cb(); }
INLINE void RCC_BLECClkDisable(void) { RCC->AHBPCENR &= ~B16; cb(); }

// BLES module clock Enable/Disable
INLINE void RCC_BLESClkEnable(void) { RCC->AHBPCENR |= B17; cb(); }
INLINE void RCC_BLESClkDisable(void) { RCC->AHBPCENR &= ~B17; cb(); }

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

// PE port module clock Enable/Disable
INLINE void RCC_PEClkEnable(void) { RCC->APB2PCENR |= B6; cb(); }
INLINE void RCC_PEClkDisable(void) { RCC->APB2PCENR &= ~B6; cb(); }

// ADC1 module clock Enable/Disable
INLINE void RCC_ADC1ClkEnable(void) { RCC->APB2PCENR |= B9; cb(); }
INLINE void RCC_ADC1ClkDisable(void) { RCC->APB2PCENR &= ~B9; cb(); }

// ADC2 module clock Enable/Disable
INLINE void RCC_ADC2ClkEnable(void) { RCC->APB2PCENR |= B10; cb(); }
INLINE void RCC_ADC2ClkDisable(void) { RCC->APB2PCENR &= ~B10; cb(); }

// TIM1 module clock Enable/Disable
INLINE void RCC_TIM1ClkEnable(void) { RCC->APB2PCENR |= B11; cb(); }
INLINE void RCC_TIM1ClkDisable(void) { RCC->APB2PCENR &= ~B11; cb(); }

// SPI1 module clock Enable/Disable
INLINE void RCC_SPI1ClkEnable(void) { RCC->APB2PCENR |= B12; cb(); }
INLINE void RCC_SPI1ClkDisable(void) { RCC->APB2PCENR &= ~B12; cb(); }

// TIM8 module clock Enable/Disable
INLINE void RCC_TIM8ClkEnable(void) { RCC->APB2PCENR |= B13; cb(); }
INLINE void RCC_TIM8ClkDisable(void) { RCC->APB2PCENR &= ~B13; cb(); }

// USART1 module clock Enable/Disable
INLINE void RCC_USART1ClkEnable(void) { RCC->APB2PCENR |= B14; cb(); }
INLINE void RCC_USART1ClkDisable(void) { RCC->APB2PCENR &= ~B14; cb(); }

// TIM9 module clock Enable/Disable
INLINE void RCC_TIM9ClkEnable(void) { RCC->APB2PCENR |= B19; cb(); }
INLINE void RCC_TIM9ClkDisable(void) { RCC->APB2PCENR &= ~B19; cb(); }

// TIM10 module clock Enable/Disable
INLINE void RCC_TIM10ClkEnable(void) { RCC->APB2PCENR |= B20; cb(); }
INLINE void RCC_TIM10ClkDisable(void) { RCC->APB2PCENR &= ~B20; cb(); }

// TIM2 module clock Enable/Disable
INLINE void RCC_TIM2ClkEnable(void) { RCC->APB1PCENR |= B0; cb(); }
INLINE void RCC_TIM2ClkDisable(void) { RCC->APB1PCENR &= ~B0; cb(); }

// TIM3 module clock Enable/Disable
INLINE void RCC_TIM3ClkEnable(void) { RCC->APB1PCENR |= B1; cb(); }
INLINE void RCC_TIM3ClkDisable(void) { RCC->APB1PCENR &= ~B1; cb(); }

// TIM4 module clock Enable/Disable
INLINE void RCC_TIM4ClkEnable(void) { RCC->APB1PCENR |= B2; cb(); }
INLINE void RCC_TIM4ClkDisable(void) { RCC->APB1PCENR &= ~B2; cb(); }

// TIM5 module clock Enable/Disable
INLINE void RCC_TIM5ClkEnable(void) { RCC->APB1PCENR |= B3; cb(); }
INLINE void RCC_TIM5ClkDisable(void) { RCC->APB1PCENR &= ~B3; cb(); }

// TIM6 module clock Enable/Disable
INLINE void RCC_TIM6ClkEnable(void) { RCC->APB1PCENR |= B4; cb(); }
INLINE void RCC_TIM6ClkDisable(void) { RCC->APB1PCENR &= ~B4; cb(); }

// TIM7 module clock Enable/Disable
INLINE void RCC_TIM7ClkEnable(void) { RCC->APB1PCENR |= B5; cb(); }
INLINE void RCC_TIM7ClkDisable(void) { RCC->APB1PCENR &= ~B5; cb(); }

// USART6 module clock Enable/Disable
INLINE void RCC_USART6ClkEnable(void) { RCC->APB1PCENR |= B6; cb(); }
INLINE void RCC_USART6ClkDisable(void) { RCC->APB1PCENR &= ~B6; cb(); }

// USART7 module clock Enable/Disable
INLINE void RCC_USART7ClkEnable(void) { RCC->APB1PCENR |= B7; cb(); }
INLINE void RCC_USART7ClkDisable(void) { RCC->APB1PCENR &= ~B7; cb(); }

// USART8 module clock Enable/Disable
INLINE void RCC_USART8ClkEnable(void) { RCC->APB1PCENR |= B8; cb(); }
INLINE void RCC_USART8ClkDisable(void) { RCC->APB1PCENR &= ~B8; cb(); }

// Window watchdog clock Enable/Disable
INLINE void RCC_WWDGClkEnable(void) { RCC->APB1PCENR |= B11; cb(); }
INLINE void RCC_WWDGClkDisable(void) { RCC->APB1PCENR &= ~B11; cb(); }

// SPI2 module clock Enable/Disable
INLINE void RCC_SPI2ClkEnable(void) { RCC->APB1PCENR |= B14; cb(); }
INLINE void RCC_SPI2ClkDisable(void) { RCC->APB1PCENR &= ~B14; cb(); }

// SPI3 module clock Enable/Disable
INLINE void RCC_SPI3ClkEnable(void) { RCC->APB1PCENR |= B15; cb(); }
INLINE void RCC_SPI3ClkDisable(void) { RCC->APB1PCENR &= ~B15; cb(); }

// USART2 module clock Enable/Disable
INLINE void RCC_USART2ClkEnable(void) { RCC->APB1PCENR |= B17; cb(); }
INLINE void RCC_USART2ClkDisable(void) { RCC->APB1PCENR &= ~B17; cb(); }

// USART3 module clock Enable/Disable
INLINE void RCC_USART3ClkEnable(void) { RCC->APB1PCENR |= B18; cb(); }
INLINE void RCC_USART3ClkDisable(void) { RCC->APB1PCENR &= ~B18; cb(); }

// USART4 module clock Enable/Disable
INLINE void RCC_USART4ClkEnable(void) { RCC->APB1PCENR |= B19; cb(); }
INLINE void RCC_USART4ClkDisable(void) { RCC->APB1PCENR &= ~B19; cb(); }

// USART5 module clock Enable/Disable
INLINE void RCC_USART5ClkEnable(void) { RCC->APB1PCENR |= B20; cb(); }
INLINE void RCC_USART5ClkDisable(void) { RCC->APB1PCENR &= ~B20; cb(); }

// I2C1 module clock Enable/Disable
INLINE void RCC_I2C1ClkEnable(void) { RCC->APB1PCENR |= B21; cb(); }
INLINE void RCC_I2C1ClkDisable(void) { RCC->APB1PCENR &= ~B21; cb(); }

// I2C2 module clock Enable/Disable
INLINE void RCC_I2C2ClkEnable(void) { RCC->APB1PCENR |= B22; cb(); }
INLINE void RCC_I2C2ClkDisable(void) { RCC->APB1PCENR &= ~B22; cb(); }

// USBD module clock Enable/Disable
INLINE void RCC_USBDClkEnable(void) { RCC->APB1PCENR |= B23; cb(); }
INLINE void RCC_USBDClkDisable(void) { RCC->APB1PCENR &= ~B23; cb(); }

// CAN1 module clock Enable/Disable
INLINE void RCC_CAN1ClkEnable(void) { RCC->APB1PCENR |= B25; cb(); }
INLINE void RCC_CAN1ClkDisable(void) { RCC->APB1PCENR &= ~B25; cb(); }

// CAN2 module clock Enable/Disable
INLINE void RCC_CAN2ClkEnable(void) { RCC->APB1PCENR |= B26; cb(); }
INLINE void RCC_CAN2ClkDisable(void) { RCC->APB1PCENR &= ~B26; cb(); }

// Backup module clock Enable/Disable
INLINE void RCC_BKPClkEnable(void) { RCC->APB1PCENR |= B27; cb(); }
INLINE void RCC_BKPClkDisable(void) { RCC->APB1PCENR &= ~B27; cb(); }

// Power module clock Enable/Disable
INLINE void RCC_PWRClkEnable(void) { RCC->APB1PCENR |= B28; cb(); }
INLINE void RCC_PWRClkDisable(void) { RCC->APB1PCENR &= ~B28; cb(); }

// DAC module clock Enable/Disable
INLINE void RCC_DACClkEnable(void) { RCC->APB1PCENR |= B29; cb(); }
INLINE void RCC_DACClkDisable(void) { RCC->APB1PCENR &= ~B29; cb(); }

// Gigabit Ethernet 125M clock Enable/Disable
INLINE void RCC_ETH1GClkEnable(void) { RCC->CFGR2 |= B22; cb(); }
INLINE void RCC_ETH1GClkDisable(void) { RCC->CFGR2 &= ~B22; cb(); }

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

// --- Clock extra configuration

// Set PREDIV1 prescaler factor 1..16 (PLL1 must be off)
INLINE void RCC_PreDiv1(int div) { RCC->CFGR2 = (RCC->CFGR2 & ~0x0f) | (div - 1); }

// Set PREDIV2 prescaler factor 1..16 (PLL2 and PLL3 must be off)
INLINE void RCC_PreDiv2(int div) { RCC->CFGR2 = (RCC->CFGR2 & ~(0x0f << 4)) | ((div - 1) << 4); }

// Set PLL2 multiplication factor RCC_PLL2_MUL* (PLL2 must be off)
INLINE void RCC_PLL2Mul(int mul) { RCC->CFGR2 = (RCC->CFGR2 & ~(0x0f << 8)) | (mul << 8); }

// Set PLL3 multiplication factor RCC_PLL2_MUL* (PLL3 must be off)
INLINE void RCC_PLL3Mul(int mul) { RCC->CFGR2 = (RCC->CFGR2 & ~(0x0f << 12)) | (mul << 12); }

// Select PREDIV1 clock source HSE or PLL2
INLINE void RCC_PreDiv1SrcHSE(void) { RCC->CFGR2 &= ~B16; }
INLINE void RCC_PreDiv1SrcPLL2(void) { RCC->CFGR2 |= B16; }

// Select I2S2 clock source SYSCLK or PLL3
INLINE void RCC_I2S2SrcSYSCLK(void) { RCC->CFGR2 &= ~B17; }
INLINE void RCC_I2S2SrcPLL3(void) { RCC->CFGR2 |= B17; }

// Select I2S3 clock source SYSCLK or PLL3
INLINE void RCC_I2S3SrcSYSCLK(void) { RCC->CFGR2 &= ~B18; }
INLINE void RCC_I2S3SrcPLL3(void) { RCC->CFGR2 |= B18; }

// Select RNG clock source SYSCLK or PLL3
INLINE void RCC_RNGSrcSYSCLK(void) { RCC->CFGR2 &= ~B19; }
INLINE void RCC_RNGSrcPLL3(void) { RCC->CFGR2 |= B19; }

// Select Gigabit Ethernet 125M clock source RCC_ETH1GSRC_*
INLINE void RCC_ETH1GSrc(int src) { RCC->CFGR2 = (RCC->CFGR2 & ~(3 << 20)) | (src << 20); }

// Select USBHS PLL reference source prescaler to divide 1..8
INLINE void RCC_USBHSDiv(int div) { RCC->CFGR2 = (RCC->CFGR2 & ~(7 << 24)) | (div << 24); }

// Select USBHS PLL clock source HSE or HSI
INLINE void RCC_USBHSSrcHSE(void) { RCC->CFGR2 &= ~B27; }
INLINE void RCC_USBHSSrcHSI(void) { RCC->CFGR2 |= B27; }

// Select USBHS PLL reference clock RCC_USBHS_REF* (USBHSPLLSRC/USBHSDIV)
INLINE void RCC_USBHSRef(int ref) { RCC->CFGR2 = (RCC->CFGR2 & ~(3 << 28)) | (ref << 28); }

// USBHS PLL internal PLL Enable/Disable
INLINE void RCC_USBHSPLLEnable(void) { RCC->CFGR2 |= B30; }
INLINE void RCC_USBHSPLLDisable(void) { RCC->CFGR2 &= ~B30; }

// Select USBHS 48MHz clock source PLL or USB PHY
INLINE void RCC_USBHSSrcPLL(void) { RCC->CFGR2 &= ~B31; }
INLINE void RCC_USBHSSrcPHY(void) { RCC->CFGR2 |= B31; }

// --- Oscillator calibration

// Set HSE starting current adjustmen bit 0..3
INLINE void OSC_SetHSEITRIM(int trim) { OSC->HSE_CAL_CTRL = (OSC->HSE_CAL_CTRL & ~3) | trim; }

// Enable/Disable analog input HSE fault detection signal
INLINE void OSC_HSEFAULTEnable(void) { OSC->HSE_CAL_CTRL &= ~B27; }
INLINE void OSC_HSEFAULTDisable(void) { OSC->HSE_CAL_CTRL |= B27; }

// Set HSE internal match capacitor adjustment RCC_HSEC_*
INLINE void OSC_HSEC(int hsec) { OSC->HSE_CAL_CTRL = (OSC->HSE_CAL_CTRL & ~(0x0f << 28)) | (hsec << 28); }

// Set LSI32K coarse tune 0..31
INLINE void OSC_LTUNE(int ltune) { OSC->LSI32K_TUNE = (OSC->LSI32K_TUNE & ~0x1f) | ltune; }

// Set LSI32K fine tune 0..255
INLINE void OSC_HTUNE(int htune) { OSC->LSI32K_TUNE = (OSC->LSI32K_TUNE & ~(0xff << 5)) | (htune << 5); }

// Set LSI32K calibration sampling duration RCC_CNTVLU_*
INLINE void OSC_CNTVLU(int cnt) { OSC->LSI32K_CAL_CFG = (OSC->LSI32K_CAL_CFG & ~0x0f) | cnt; }

// Set LSI32K calibration count hal duration to 1 or 3 CK32K cycles
INLINE void OSC_HALTMD1(void) { OSC->LSI32K_CAL_CFG &= ~B4; }
INLINE void OSC_HALTMD3(void) { OSC->LSI32K_CAL_CFG |= B4; }

// Enable/Disable LSI32K wake-up interrupt
INLINE void OSC_WKUPEnable(void) { OSC->LSI32K_CAL_CFG |= B5; }
INLINE void OSC_WKUPDisable(void) { OSC->LSI32K_CAL_CFG &= ~B5; }

// Enable/Disable calibation enable in low-power mode
INLINE void OSC_LPCALEnable(void) { OSC->LSI32K_CAL_CFG |= B6; }
INLINE void OSC_LPCALDisable(void) { OSC->LSI32K_CAL_CFG &= ~B6; }

// Get count for several CK32K cycles 0..16383
INLINE int OSC_CNT(void) { return OSC->LSI32K_CAL_STATR & 0x3fff; }

// Get/Clear LSI32K sampling counter overflow flag
INLINE Bool OSC_CNTOV(void) { return (OSC->LSI32K_CAL_STATR & B14) != 0; }
INLINE void OSC_CNTOVClr(void) { OSC->LSI32K_CAL_STATR |= B14; }

// Get/Clear LSI32K calibration count end interrupt flag
INLINE Bool OSC_IFEND(void) { return (OSC->LSI32K_CAL_STATR & B15) != 0; }
INLINE void OSC_IFENDClr(void) { OSC->LSI32K_CAL_STATR |= B15; }

// Get LSI32K sampling counter overflow count 0..255
INLINE u8 OSC_OVCNT(void) { return OSC->LSI32K_CAL_OV_CNT; }

// Enable/Disable LSI32K calibration interrupt
INLINE void OSC_CALINTEnable(void) { OSC->LSI32K_CAL_CTRL |= B0; }
INLINE void OSC_CALINTDisable(void) { OSC->LSI32K_CAL_CTRL &= ~B0; }

// Enable/Disable LSI32K calibration
INLINE void OSC_CALEnable(void) { OSC->LSI32K_CAL_CTRL |= B1; }
INLINE void OSC_CALDisable(void) { OSC->LSI32K_CAL_CTRL &= ~B1; }

// Get LSI32K calibration count halt
INLINE Bool OSC_HALT(void) { return (OSC->LSI32K_CAL_CTRL & B7) != 0; }

#ifdef __cplusplus
}
#endif

#endif // _SDK_RCC_H
