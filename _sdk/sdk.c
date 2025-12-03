// PicoLibSDK - Alternative SDK library for Raspberry Pico and RP2040
// Copyright (c) 2023 Miroslav Nemecek, Panda38@seznam.cz, hardyplotter2@gmail.com
// 	https://github.com/Panda381/PicoLibSDK
//	https://www.breatharian.eu/hw/picolibsdk/index_en.html
//	https://github.com/pajenicko/picopad
//	https://picopad.eu/en/
// License:
//	This source code is freely available for any purpose, including commercial.
//	It is possible to take and modify the code or parts of it, without restriction.

#include "../global.h"

#define STRINGIFYC_HELPER(x) #x
#define STRINGIFYC(x) STRINGIFYC_HELPER(x)
#define INCLUDEC_SDK_FILE(file) STRINGIFYC(SDK_SUBDIR/file)

#include INCLUDEC_SDK_FILE(sdk_adc.c)		// ADC
#include INCLUDEC_SDK_FILE(sdk_cpu.c)		// CPU control
#include INCLUDEC_SDK_FILE(sdk_dma.c)		// DMA
#include INCLUDEC_SDK_FILE(sdk_flash.c)		// Flash memory
#include INCLUDEC_SDK_FILE(sdk_gpio.c)		// GPIO pins
#include INCLUDEC_SDK_FILE(sdk_irq.c)		// Interrupt
#include INCLUDEC_SDK_FILE(sdk_i2c.c)		// I2C
#include INCLUDEC_SDK_FILE(sdk_pwr.c)		// Power control
#include INCLUDEC_SDK_FILE(sdk_rcc.c)		// Reset and clock control
#include INCLUDEC_SDK_FILE(sdk_runtime.c)	// application support
#include INCLUDEC_SDK_FILE(sdk_spi.c)		// SPI
#include INCLUDEC_SDK_FILE(sdk_systick.c)	// SysTick system counter
#include INCLUDEC_SDK_FILE(sdk_tim.c)		// TIM
#include INCLUDEC_SDK_FILE(sdk_usart.c)		// USART
#include INCLUDEC_SDK_FILE(sdk_wdg.c)		// WDG
