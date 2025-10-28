
// ****************************************************************************
//                                 
//                         Global common C definitions
//
// ****************************************************************************

#ifndef _GLOBAL_H
#define _GLOBAL_H

#define SDK_VER		031	// SDK library version in hundredths (031 = 0.31)

// ----------------------------------------------------------------------------
//                               Attributes
// ----------------------------------------------------------------------------

// count of array entries
#define count_of(a) (sizeof(a)/sizeof((a)[0]))

// I/O port prefix
//#define __IO	volatile

// request to use inline
#define INLINE __attribute__((always_inline)) inline

// avoid to use inline
#define NOINLINE __attribute__((noinline))

// Interrupt handler
#define HANDLER __attribute__((interrupt("WCH-Interrupt-fast")))

// weak function
#define WEAK __attribute__((weak))

// align array to 4-bytes
#define ALIGNED __attribute__((aligned(4)))

// packed structure, to allow access to unaligned entries
#define PACKED __attribute__ ((packed))

// place time critical function into RAM
#define NOFLASH(fnc) NOINLINE __attribute__((section(".time_critical." #fnc))) fnc

// forbidden to replace the "for" loop with the "memset" function
#define NOMEMSET __attribute__((optimize("no-tree-loop-distribute-patterns")))

// no return from function
#define NORETURN __attribute__((noreturn))

// fast function optimization
#define FASTCODE __attribute__ ((optimize("-Ofast")))

// small function optimization
#define SMALLCODE __attribute__ ((optimize("-Os")))

// wrapper function (to replace standard library function)
#define WRAPPER_FUNC(x) __wrap_ ## x

// absolute value
#define ABS(val) ( ((val)<0) ? -(val) : (val) )

// maximal value
#define MAX(val1,val2) ( ((val1)<(val2)) ? (val2) : (val1) )

// minimal value
#define MIN(val1,val2) ( ((val1)<(val2)) ? (val1) : (val2) )

// compile-time check
#ifdef __cplusplus
#define STATIC_ASSERT(c, msg) static_assert((c), msg)
#else
#define STATIC_ASSERT(c, msg) _Static_assert((c), msg)
#endif

// change endian of u16 (little endian LSB MSB = Intel, big endian MSB LSB = Motorola)
#define ENDIAN16(k) ( (((k)>>8)&0xff) | (((k)&0xff)<<8) )

// ----------------------------------------------------------------------------
//                              Base data types
// ----------------------------------------------------------------------------

/* Basic data types and their sizes (in bytes) depending on the system:

		8-bit	16-bit	32-bit	64-bit
char		1	1	1	1
short		1	1	2	2
int		2	2	4	4
long		4	4	4	4,8
long long	8	8	8	8
*/

// Note: 'char' can be signed or unsigned

// base types
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;		// on 8-bit system use "signed int"
typedef unsigned short u16;		// on 8-bit system use "unsigned int"
typedef signed long int s32;		// on 64-bit system use "signed int"
typedef unsigned long int u32;		// on 64-bit system use "unsigned int"
typedef signed long long int s64;
typedef unsigned long long int u64;

typedef unsigned int uint;

// hw registers
typedef volatile u32 io32;
typedef volatile u16 io16;
typedef volatile u8 io8;

// optimised Bool
//  Note: Why is a Bool type of boolean variable used? Two types of boolean variables
//  are commonly used. In Windows notation, a boolean variable is called BOOL with
//  the values TRUE and FALSE. It is based on the C language, where the boolean value
//  FALSE is considered to be the zero value of an integer number, and TRUE is
//  considered to be a non-zero value. This type of logical variable requires a variable
//  of size int, that is, typically 32 bits. In C++, the bool logical variable was
//  introduced with the values true and false. It is a bit variable with a typical size
//  of 1 byte and values of 0 and 1. The bool variable is more memory efficient than the
//  BOOL type, but it is more demanding for the processor - it requires permanent
//  conversion of the result of operations to the value 0 or 1. The Bool type variable
//  is an optimal compromise between the two methods. It uses a variable of size 1 byte,
//  treats a value of False as a zero value and a non-zero value as True. This method is
//  memory-efficient while being fast and efficient for the processor.
typedef unsigned char Bool;
#define True 1
#define False 0

// NULL
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif

// compile-time check 
STATIC_ASSERT(sizeof(s8) == 1, "Incorrect typedef s8!");
STATIC_ASSERT(sizeof(u8) == 1, "Incorrect typedef u8!");
STATIC_ASSERT(sizeof(s16) == 2, "Incorrect typedef s16!");
STATIC_ASSERT(sizeof(u16) == 2, "Incorrect typedef u16!");
STATIC_ASSERT(sizeof(s32) == 4, "Incorrect typedef s32!");
STATIC_ASSERT(sizeof(u32) == 4, "Incorrect typedef u32!");
STATIC_ASSERT(sizeof(s64) == 8, "Incorrect typedef s64!");
STATIC_ASSERT(sizeof(u64) == 8, "Incorrect typedef u64!");

// ----------------------------------------------------------------------------
//                               Constants
// ----------------------------------------------------------------------------

#define	B0 (1<<0)
#define	B1 (1<<1)
#define	B2 (1<<2)
#define	B3 (1<<3)
#define	B4 (1<<4)
#define	B5 (1<<5)
#define	B6 (1<<6)
#define	B7 (1<<7)
#define	B8 (1U<<8)
#define	B9 (1U<<9)
#define	B10 (1U<<10)
#define	B11 (1U<<11)
#define	B12 (1U<<12)
#define	B13 (1U<<13)
#define	B14 (1U<<14)
#define	B15 (1U<<15)
#define B16 (1UL<<16)
#define B17 (1UL<<17)
#define B18 (1UL<<18)
#define	B19 (1UL<<19)
#define B20 (1UL<<20)
#define B21 (1UL<<21)
#define B22 (1UL<<22)
#define B23 (1UL<<23)
#define B24 (1UL<<24)
#define B25 (1UL<<25)
#define B26 (1UL<<26)
#define B27 (1UL<<27)
#define B28 (1UL<<28)
#define B29 (1UL<<29)
#define B30 (1UL<<30)
#define B31 (1UL<<31)

#define BIT(pos) (1UL<<(pos))
#define BIT64(pos) (1ULL<<(pos))

#define	BIGINT	0x40000000 // big int value

#define PI 3.14159265358979324
#define PI2 (3.14159265358979324*2)

#define KHZ 1000	// kHz multiply
#define MHZ 1000000	// MHz multiply

// ----------------------------------------------------------------------------
//                           Base Includes
// ----------------------------------------------------------------------------

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)

// project configuration
#include "config.h"		// project configuration

// default configuration
#if USE_CH32BASE
#include "_devices/ch32base/_config.h"
#endif

#if USE_BABYBOY
#include "_devices/babyboy/_config.h"
#endif

#if USE_BABYPAD
#include "_devices/babypad/_config.h"
#endif

#if USE_BEATLEBOYPAD
#include "_devices/beatleboypad/_config.h"
#endif

#if USE_PIDIBOY
#include "_devices/pidiboy/_config.h"
#endif

#if USE_PIDIPAD
#include "_devices/pidipad/_config.h"
#endif

#if USE_TWEETYBOY
#include "_devices/tweetyboy/_config.h"
#endif

#if USE_BABYPC
#include "_devices/babypc/_config.h"
#endif

#if USE_PIDIPC
#include "_devices/pidipc/_config.h"
#endif

#include <string.h>		// memcpy
#include <stdarg.h>		// va_list
#include <math.h>		// HUGE_VAL

// ----------------------------------------------------------------------------
//                               Library modules
// ----------------------------------------------------------------------------

#ifndef USE_CRC
#define USE_CRC		1	// 1=use CRC library
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

#ifndef USE_SD
#define USE_SD		0	// 1=use SD card driver
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

#endif // _GLOBAL_H
