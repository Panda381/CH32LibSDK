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

#ifndef _SDK_INCLUDE_H
#define _SDK_INCLUDE_H

#define INCLUDE_SDK_FILE(file) STRINGIFY(SDK_SUBDIR/file)

#include INCLUDE_SDK_FILE(sdk_addressmap.h)	// Register address offsets
#include INCLUDE_SDK_FILE(sdk_cpu.h)		// CPU control
#include INCLUDE_SDK_FILE(sdk_rcc.h)		// Reset and clock control

#include INCLUDE_SDK_FILE(sdk_adc.h)		// ADC analog-to-digital converter
#include INCLUDE_SDK_FILE(sdk_dma.h)		// DMA
#include INCLUDE_SDK_FILE(sdk_flash.h)		// Flash memory
#include INCLUDE_SDK_FILE(sdk_gpio_pins.h)	// GPIO pins indices
#include INCLUDE_SDK_FILE(sdk_gpio.h)		// GPIO pins
#include INCLUDE_SDK_FILE(sdk_i2c.h)		// I2C
#include INCLUDE_SDK_FILE(sdk_irq.h)		// Interrupt
#include INCLUDE_SDK_FILE(sdk_pwr.h)		// Power control
#include INCLUDE_SDK_FILE(sdk_runtime.h)	// application support
#include INCLUDE_SDK_FILE(sdk_spi.h)		// SPI
#include INCLUDE_SDK_FILE(sdk_systick.h)	// SysTick system counter
#include INCLUDE_SDK_FILE(sdk_tim.h)		// TIM
#include INCLUDE_SDK_FILE(sdk_usart.h)		// USART
#include INCLUDE_SDK_FILE(sdk_wdg.h)		// WDG

#endif // _SDK_INCLUDE_H
