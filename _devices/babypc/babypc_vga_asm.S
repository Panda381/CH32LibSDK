
// ****************************************************************************
//
//                        BabyPC - VGA display driver
//
// ****************************************************************************

// project configuration
#include "config.h"		// project configuration
#include "_config.h"		// default configuration

#if USE_DISP		// 1=use display support

#define	PERIPH_BASE		0x40000000	// Peripheral base address in the alias region
#define APB1PERIPH_BASE		PERIPH_BASE			// 0x40000000
#define APB2PERIPH_BASE		(PERIPH_BASE + 0x10000)		// 0x40010000

#define GPIOC_BASE		(APB2PERIPH_BASE + 0x1000)	// PC port base (0x40011000)
#define GPIOD_BASE		(APB2PERIPH_BASE + 0x1400)	// PD port 0x40011400
#define SPI1_BASE		(APB2PERIPH_BASE + 0x3000)	// SPI1 base (0x40013000)
#define TIM1_BASE		(APB2PERIPH_BASE + 0x2C00)	// TIM1 0x40012C00
#define TIM2_BASE		(APB1PERIPH_BASE + 0x0000)	// TIM2 0x40000000
#define USART1_BASE		(APB2PERIPH_BASE + 0x3800)	// USART1 0x40013800

#define SPI_DATAR_OFF		0x0C		// data register offset
#define GPIO_INDR_OFF		0x08		// GPIO input register offset
#define GPIO_BSHR_OFF		0x10		// GPIO bit set output data register
#define GPIO_BCR_OFF		0x14		// GPIO bit clear output data register
#define TIM_INTFR_OFF		0x10		// timer interrupt register offset
#define TIM_CCER_OFF		0x20		// timer compare register
#define TIM_CNT_OFF		0x24		// timer counter register offset
#define TIM_ATRLR_OFF		0x2C		// ATRLR timer auto-reload value register
#define TIM_CH4CVR_OFF		0x40		// CH4CVR timer compare/capture register 4
#define USART_DATAR_OFF		0x04		// USART data register offset

// commands from CPU1 to CPU2
//#define CPU_CMD_SYNC	0x16		// sync - echo CPU_STATE_SYNC back, and set ROW4 to 1
#define CPU_CMD_ROW41	0x17		// return columns in 2 bytes (in bits 0..4) and set ROW4 to 1
#define CPU_CMD_ROW40	0x18		// return columns in 2 bytes (in bits 0..4) and set ROW4 to 0

// state from CPU2 to CPU1
//#define CPU_STATE_SYNC	0x15		// sync - echo back after CPU_CMD_SYNC

.global FrameBuf			// (u8[]) display graphics buffer
.global DispLine			// (u32) current display line
.global DispFrame			// (u32) current frame
.global FrameBufAddr			// (u8*) current pointer to graphics buffer
.global DispTimTest			// test - get TIM-CNT value at start of image
.global DrawFont			// (u8*) current pointer to font

#define KEY_NUM			40	// number of buttons
#define KEYBUF_SIZE		16	// size of keyboard buffer
// If you change the settings, also check this in babypc_key.h.
.global KeyReleaseCnt			// (u8[]) key release counter + key repeat counter; >0 if key is pressed (without NOKEY)
.global KeyBuf				// (u8[]) keyboard buffer
.global KeyWriteOff			// (u8) write offset to keyboard buffer
.global KeyReadOff			// (u8) read offset from keyboard buffer
.global CPUIntLocked			// (u8) CPU communication from interrupt is locked (prohibited)
.global CPUIntLockedReq			// (u8) request to lock CPU communication from interrupt

.global SoundMelodyPtr			// (sMelodyNote*) pointer to current melody
.global SoundMelodyNext			// (sMelodyNote*) pointer to next melody
.global SoundMelodyLen			// (s16) remaining length of current tone (0 = no melody, -1 = start next melody)

// Keyboard scanning:
#if VMODE == 0
#define KEY_SCANLINE_1	(256+112+10+2+1) // scanline 1: set ROW1 to 0, send CPU_CMD_ROW41
#define KEY_SCANLINE_2	(256+112+10+2+2) // scanline 2: set ROW1 to 1, receive byte 1, process byte 1 of ROW1
#define KEY_SCANLINE_3	(256+112+10+2+3) // scanline 3: set ROW2 to 0, send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW1
#define KEY_SCANLINE_4	(256+112+10+2+4) // scanline 4: set ROW2 to 1, receive byte 1, process byte 1 of ROW2
#define KEY_SCANLINE_5	(256+112+10+2+5) // scanline 5: set ROW3 to 0, send CPU_CMD_ROW40, receive byte 2, process byte 2 or ROW2
#define KEY_SCANLINE_6	(256+112+10+2+6) // scanline 6: set ROW3 to 1, receive byte 1, process byte 1 of ROW3
#define KEY_SCANLINE_7	(256+112+10+2+7) // scanline 7: send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW3
#define KEY_SCANLINE_8	(256+112+10+2+8) // scanline 8: receive byte 1, process byte 1 of ROW4
#define KEY_SCANLINE_9	(256+112+10+2+9) // scanline 9: receive byte 2, process byte 2 or ROW4
#elif (VMODE == 2) || (VMODE == 5) || (VMODE == 7)
#define KEY_SCANLINE_1	(384+48+10+2+1)	// scanline 1: set ROW1 to 0, send CPU_CMD_ROW41
#define KEY_SCANLINE_2	(384+48+10+2+2)	// scanline 2: set ROW1 to 1, receive byte 1, process byte 1 of ROW1
#define KEY_SCANLINE_3	(384+48+10+2+3)	// scanline 3: set ROW2 to 0, send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW1
#define KEY_SCANLINE_4	(384+48+10+2+4)	// scanline 4: set ROW2 to 1, receive byte 1, process byte 1 of ROW2
#define KEY_SCANLINE_5	(384+48+10+2+5)	// scanline 5: set ROW3 to 0, send CPU_CMD_ROW40, receive byte 2, process byte 2 or ROW2
#define KEY_SCANLINE_6	(384+48+10+2+6)	// scanline 6: set ROW3 to 1, receive byte 1, process byte 1 of ROW3
#define KEY_SCANLINE_7	(384+48+10+2+7)	// scanline 7: send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW3
#define KEY_SCANLINE_8	(384+48+10+2+8)	// scanline 8: receive byte 1, process byte 1 of ROW4
#define KEY_SCANLINE_9	(384+48+10+2+9)	// scanline 9: receive byte 2, process byte 2 or ROW4
#else
#define KEY_SCANLINE_1	(480+10+2+1)	// scanline 1: set ROW1 to 0, send CPU_CMD_ROW41
#define KEY_SCANLINE_2	(480+10+2+2)	// scanline 2: set ROW1 to 1, receive byte 1, process byte 1 of ROW1
#define KEY_SCANLINE_3	(480+10+2+3)	// scanline 3: set ROW2 to 0, send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW1
#define KEY_SCANLINE_4	(480+10+2+4)	// scanline 4: set ROW2 to 1, receive byte 1, process byte 1 of ROW2
#define KEY_SCANLINE_5	(480+10+2+5)	// scanline 5: set ROW3 to 0, send CPU_CMD_ROW40, receive byte 2, process byte 2 or ROW2
#define KEY_SCANLINE_6	(480+10+2+6)	// scanline 6: set ROW3 to 1, receive byte 1, process byte 1 of ROW3
#define KEY_SCANLINE_7	(480+10+2+7)	// scanline 7: send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW3
#define KEY_SCANLINE_8	(480+10+2+8)	// scanline 8: receive byte 1, process byte 1 of ROW4
#define KEY_SCANLINE_9	(480+10+2+9)	// scanline 9: receive byte 2, process byte 2 or ROW4
#endif

#define NEWLINE		0x76	// NEWLINE

// 32-bit NOP
.macro nopw
	.word	0x13
.endm

// multiply 16-bit NOP
.macro nop_rep num
.rept \num
	nop
.endr
.endm

// multiply 32-bit NOP
.macro nopw_rep num
.rept \num
	nopw
.endr
.endm

	.section .time_critical, "ax"

// ============================================================================
//         0: graphics mode 128x64 pixels, required memory 1024 B
// ============================================================================

#if VMODE == 0

// Registers:
//  A0-A3, T0-T1 =
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address
// - continue to TIM2_IRQHandler4

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-5=283)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare number of samples -> A3
	li	a3,16			// -5: [1]

	.align	2,,			// -4: [1]

// [64 loop] send sample ... This address must be aligned

// Registers:
//  A0 = temporary with sample
//  A1, T0-T1 =
//  A2 = delay counter
//  A3 = loop counter
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address

	// [5] send sample to SPI
2:	lbu	a0,0(a4)		// -3: [2] A0 <- load sample
	addi	a4,a4,1			// -1: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(a5)	// 0: [2] send sample to SPI

	// [55] delay
	li	a2,14			// +2: [1]
	.align	2,,			// +3: [0]
	// [13*4+2=54] loop
1:	addi	a2,a2,-1		// [1]
	bnez	a2,1b			// [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [2,4] loop counter
	addi	a3,a3,-1		// +57: [1]
	bnez	a3,2b			// +58: [1,3] 
					// +59 (pass), +61 (loop)

	// send black color
	sw	x0,SPI_DATAR_OFF(a5)	// send black sample to SPI

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a1,3			// to compare
	and	a0,t2,a1		// get lowest 2 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

1:	j	TIM2_IRQHandler4

.endm

#endif // VMODE == 0

// ============================================================================
//         1: graphics mode 160x120 pixels, required memory 2400 B
// ============================================================================

#if VMODE == 1

// Registers:
//  A0-A3, T0-T1 =
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address
// - continue to TIM2_IRQHandler4

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-5=283)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare number of samples -> A3
	li	a3,20			// -5: [1]

	.align	2,,			// -4: [1]

// [64 loop] send sample ... This address must be aligned

// Registers:
//  A0 = temporary with sample
//  A1, T0-T1 =
//  A2 = delay counter
//  A3 = loop counter
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address

	// [5] send sample to SPI
2:	lbu	a0,0(a4)		// -3: [2] A0 <- load sample
	addi	a4,a4,1			// -1: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(a5)	// 0: [2] send sample to SPI

	// [55] delay
	li	a2,14			// +2: [1]
	.align	2,,			// +3: [0]
	// [13*4+2=54] loop
1:	addi	a2,a2,-1		// [1]
	bnez	a2,1b			// [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [2,4] loop counter
	addi	a3,a3,-1		// +57: [1]
	bnez	a3,2b			// +58: [1,3] 
					// +59 (pass), +61 (loop)

	// send black color
	sw	x0,SPI_DATAR_OFF(a5)	// send black sample to SPI

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a1,3			// to compare
	and	a0,t2,a1		// get lowest 2 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

1:	j	TIM2_IRQHandler4

.endm

#endif // VMODE == 1

// ============================================================================
// 2: text mode 32x24 characters of 8x8 pixels (resolution 256x192 pixels, pseudographics
//    64x48 pixels), required memory 768 bytes, font 8x8 pixels 2048 bytes in Flash
// ============================================================================

#if VMODE == 2

// Registers:
//  A0-A3, T0-T1 =
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address
// - continue to TIM2_IRQHandler4

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-19+4*32=397)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare pointer to font -> A1
	la	a1,DrawFont		// -19: [2] address of pointer
	lw	a1,0(a1)		// -17: [2] A1 <- get pointer to font

	// shift font to current font line -> A1
	andi	a0,t2,0x0e		// -15: [2] A0 <- lowest 3 bits of the line * 2 (ignore bit 0, we use 2 scanlines per 1 graphics line)
	slli	a0,a0,7			// -13: [1] A0 <- offset of the line (1 line = 256 bytes)
	add	a1,a1,a0		// -12: [1] A1 <- shift pointer to current line of the font

	// prepare number of samples -> A3
	li	a3,32			// -11: [1]

	.align	2,,			// -10: [1]

// [32 loop] send sample ... This address must be aligned

// Registers:
//  A0 = temporary with sample
//  A1 = pointer to font
//  A2 = delay counter
//  A3 = loop counter
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T0-T1 =
//  T2 = current scanline
//  RA = return address

	// [11] load next character, load font sample and send sample to SPI
2:	lbu	a0,0(a4)		// -9: [2] A0 <- load text character
	addi	a4,a4,1			// -7: [1] increase sample address
	add	a0,a0,a1		// -6: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// -5: [4] A0 <- load font sample
	addi	a3,a3,-1		// -1: [1] decrease loop counter
	sw	a0,SPI_DATAR_OFF(a5)	// 0: [2] send sample to SPI

	// [18] delay
	li	a2,4			// +2: [1]
	.align	2,,			// +3: [1]
	// [3*4+2=14] loop
1:	addi	a2,a2,-1		// +4: [1]
	bnez	a2,1b			// [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +18: [2]

	// [1,3] loop counter
	bnez	a3,2b			// +20: [1,3] 
					// +21 (pass), +23 (loop)

	// send black color
	sw	x0,SPI_DATAR_OFF(a5)	// send black sample to SPI

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a1,0x0f			// to compare
	and	a0,t2,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

1:	j	TIM2_IRQHandler4

.endm

#endif // VMODE == 2

// ============================================================================
// 3: text mode 40x30 characters of 8x8 pixels (resolution 320x240 pixels, pseudographics
//    80x60 pixels), required memory 1200 bytes, font 8x8 pixels 2048 bytes in Flash
// ============================================================================

#if VMODE == 3

// Registers:
//  A0-A3, T0-T1 =
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address
// - continue to TIM2_IRQHandler4

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-19=269)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare pointer to font -> A1
	la	a1,DrawFont		// -19: [2] address of pointer
	lw	a1,0(a1)		// -17: [2] A1 <- get pointer to font

	// shift font to current font line -> A1
	andi	a0,t2,0x0e		// -15: [2] A0 <- lowest 3 bits of the line * 2 (ignore bit 0, we use 2 scanlines per 1 graphics line)
	slli	a0,a0,7			// -13: [1] A0 <- offset of the line (1 line = 256 bytes)
	add	a1,a1,a0		// -12: [1] A1 <- shift pointer to current line of the font

	// prepare number of samples -> A3
	li	a3,40			// -11: [1]

	.align	2,,			// -10: [1]

// [32 loop] send sample ... This address must be aligned

// Registers:
//  A0 = temporary with sample
//  A1 = pointer to font
//  A2 = delay counter
//  A3 = loop counter
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T0-T1 =
//  T2 = current scanline
//  RA = return address

	// [11] load next character, load font sample and send sample to SPI
2:	lbu	a0,0(a4)		// -9: [2] A0 <- load text character
	addi	a4,a4,1			// -7: [1] increase sample address
	add	a0,a0,a1		// -6: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// -5: [4] A0 <- load font sample
	addi	a3,a3,-1		// -1: [1] decrease loop counter
	sw	a0,SPI_DATAR_OFF(a5)	// 0: [2] send sample to SPI

	// [18] delay
	li	a2,4			// +2: [1]
	.align	2,,			// +3: [1]
	// [3*4+2=14] loop
1:	addi	a2,a2,-1		// +4: [1]
	bnez	a2,1b			// [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +18: [2]

	// [1,3] loop counter
	bnez	a3,2b			// +20: [1,3] 
					// +21 (pass), +23 (loop)

	// send black color
	sw	x0,SPI_DATAR_OFF(a5)	// send black sample to SPI

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a1,0x0f			// to compare
	and	a0,t2,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

1:	j	TIM2_IRQHandler4

.endm

#endif // VMODE == 3

// ============================================================================
// 4: text mode 80x30 characters of 8x8 pixels (resolution 640x240 pixels, pseudographics
//    160x60 pixels), required memory 2400 bytes, font 8x8 pixels 2048 bytes in Flash
// ============================================================================

#if VMODE == 4

// Registers:
//  A0-A3, T0-T1 =
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address
// - continue to TIM2_IRQHandler4

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-19=269)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare pointer to font -> A1
	la	a1,DrawFont		// -19: [2] address of pointer
	lw	a1,0(a1)		// -17: [2] A1 <- get pointer to font

	// shift font to current font line -> A1
	andi	a0,t2,0x0e		// -15: [2] A0 <- lowest 3 bits of the line * 2 (ignore bit 0, we use 2 scanlines per 1 graphics line)
	slli	a0,a0,7			// -13: [1] A0 <- offset of the line (1 line = 256 bytes)
	add	a1,a1,a0		// -12: [1] A1 <- shift pointer to current line of the font

	// prepare number of samples -> A3
	li	a3,80			// -11: [1]

	.align	2,,			// -10: [1]

// [32 loop] send sample ... This address must be aligned

// Registers:
//  A0 = temporary with sample
//  A1 = pointer to font
//  A2 = delay counter
//  A3 = loop counter
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T0-T1 =
//  T2 = current scanline
//  RA = return address

	// [11] load next character, load font sample and send sample to SPI
2:	lbu	a0,0(a4)		// -9: [2] A0 <- load text character
	addi	a4,a4,1			// -7: [1] increase sample address
	add	a0,a0,a1		// -6: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// -5: [4] A0 <- load font sample
	addi	a3,a3,-1		// -1: [1] decrease loop counter
	sw	a0,SPI_DATAR_OFF(a5)	// 0: [2] send sample to SPI

	// [2] delay
	nop_rep	2			// +2: [2]

	// [1,3] loop counter
	bnez	a3,2b			// +4: [1,3] 
					// +5 (pass), +7 (loop)

	// send black color
	sw	x0,SPI_DATAR_OFF(a5)	// send black sample to SPI

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a1,0x0f			// to compare
	and	a0,t2,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

1:	j	TIM2_IRQHandler4

.endm

#endif // VMODE == 4

// ============================================================================
// 5: text mode 32x24 characters in ZX-80 format (NEWLINE=0x76 is new line)
// ============================================================================

#if VMODE == 5

// Registers:
//  A0-A3, T0-T1 =
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address
// - continue to TIM2_IRQHandler4

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-26+4*32=390)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare pointer to font -> A1
	la	a1,DrawFont		// -26: [2] address of pointer
	lw	a1,0(a1)		// -24: [2] A1 <- get pointer to font

	// shift font to current font line -> A1
	srli	a0,t2,1			// -22: [2] A0 <- graphics line (2 scanlines per 1 graphics line)
	andi	a0,a0,7			// -20: [1] A0 <- lowest 3 bits of the line
	add	a1,a1,a0		// -19: [1] A1 <- shift pointer to current line of the font

	// prepare number of samples -> A3
	li	a3,32			// -18: [1]

	.align	2,,			// -17: [1]

// [32 loop] send sample ... This address must be aligned

// Registers:
//  A0 = temporary with sample
//  A1 = pointer to font
//  A2 = delay counter
//  A3 = loop counter
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T0-T1 =
//  T2 = current scanline
//  RA = return address

	// [3] load next character
2:	lbu	a2,0(a4)		// -16: [2] A0 <- load text character
	addi	a4,a4,1			// -14: [1] increase sample address

	// [2,4] New line (clear rest of the line)
	li	a0,NEWLINE		// -13: [1] new line character
	beq	a2,a0,TIM2_IRQHandler_NL1 // -12: [1,3] skip if new line (skip to time -9)

	// [7] load font sample
	andi	a0,a2,0x3f		// -11: [2] A2 <- character index
	slli	a0,a0,3			// -9: [1] A2 <- character * 8 (= offset of the font)
	add	a0,a0,a1		// -8: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// -7: [3] A0 <- load font sample

	// [4] invert sample
	slli	a2,a2,32-8		// -4: [1] check bit 7
	bltz	a2,5f			// -3: [1,3] skip if bit 7 is set
	not	a0,a0			// -2: [1] invert sample
	nop				// -1: [1]

	// [2] send sample
5:	sw	a0,SPI_DATAR_OFF(a5)	// 0: [2] send sample to SPI

	// [10] delay
	j	1f			// +2: [3]
1:	j	1f			// +5: [3]
1:	j	1f			// +8: [3]
1:	nop				// +11: [1]

	// [2,4] loop counter
	addi	a3,a3,-1		// +12: [1] decrease loop counter
	bnez	a3,2b			// +13: [1,3] 
					// +14 (pass), +16 (loop)

	// send black color
8:	sw	x0,SPI_DATAR_OFF(a5)	// +14: send black sample to SPI

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a1,0x0f			// to compare
	and	a0,t2,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

1:	j	TIM2_IRQHandler4B

	.align	2,,			// -10: [1]

// -9: clear rest of the line
TIM2_IRQHandler_NL1:

	// [8] delay
	j	1f			// -9: [3]
1:	j	1f			// -6: [3]
1:	nop				// -3: [1]
	nop				// -2: [1]

	// [3] send white color
	li	a0,0xff			// -1: [1] white color
	sw	a0,SPI_DATAR_OFF(a5)	// 0: [2] send sample to SPI

	// [17] delay
	li	a2,4			// +2: [1]
	.align	2,,			// +3: [0]
	// [3*4+2=14] loop
1:	addi	a2,a2,-1		// +3: [1]
	bnez	a2,1b			// [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +17: [2]

	// [2,4] loop counter
	addi	a3,a3,-1		// +19: [1] decrease loop counter
	bnez	a3,TIM2_IRQHandler_NL1	// +20: [1,3] 
					// +21 (pass), +23 (loop)

	j	8b			// +21: [3]

TIM2_IRQHandler4B:
	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

#endif // VMODE == 5

// ============================================================================
// 6: text mode 40x30 characters of 8x8 pixels with ZX Spectrum font of 128 characters
// ============================================================================

#if VMODE == 6

// Registers:
//  A0-A3, T0-T1 =
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address
// - continue to TIM2_IRQHandler4

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-23=265)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare pointer to font -> A1
	la	a1,DrawFont		// -23: [2] address of pointer
	lw	a1,0(a1)		// -21: [2] A1 <- get pointer to font

	// shift font to current font line -> A1
	andi	a0,t2,0x0e		// -19: [2] A0 <- lowest 3 bits of the line (bit 0 is ignored, 2 scanlines per 1 graphics line)
	slli	a0,a0,6			// -17: [1] A0 <- offset in the font (128 bytes per line)
	add	a1,a1,a0		// -16: [1] A1 <- shift pointer to current line of the font

	// prepare number of samples -> A3
	li	a3,40			// -15: [1]

	.align	2,,			// -14: [1]

// [32 loop] send sample ... This address must be aligned

// Registers:
//  A0 = temporary with sample
//  A1 = pointer to font
//  A2 = delay counter
//  A3 = loop counter
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T0-T1 =
//  T2 = current scanline
//  RA = return address

	// [3] load next character
2:	lbu	a2,0(a4)		// -13: [2] A0 <- load text character
	addi	a4,a4,1			// -11: [1] increase sample address

	// [6] load font sample
	andi	a0,a2,0x7f		// -10: [2] A2 <- character index
	add	a0,a0,a1		// -8: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// -7: [3] A0 <- load font sample

	// [4] invert sample
	slli	a2,a2,32-8		// -4: [1] check bit 7
	bgez	a2,5f			// -3: [1,3] skip if bit 7 is not set
	not	a0,a0			// -2: [1] invert sample
	nop				// -1: [1]

	// [2] send sample
5:	sw	a0,SPI_DATAR_OFF(a5)	// 0: [2] send sample to SPI

	// [12] delay
	j	1f			// +2: [3]
1:	j	1f			// +5: [3]
1:	j	1f			// +8: [3]
1:	j	1f			// +11: [3]
1:	nop				// +14: [1]

	// [2,4] loop counter
	addi	a3,a3,-1		// +15: [1] decrease loop counter
	bnez	a3,2b			// +16: [1,3] 
					// +17 (pass), +19 (loop)

	// send black color
8:	sw	x0,SPI_DATAR_OFF(a5)	// +17: send black sample to SPI

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a1,0x0f			// to compare
	and	a0,t2,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

1:	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

#endif // VMODE == 6

// ============================================================================
// 7: text mode 32x24 characters of 8x8 pixels with ZX-80/ZX-81 font of 64 characters
// ============================================================================

#if VMODE == 7

// Registers:
//  A0-A3, T0-T1 =
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current scanline
//  RA = return address
// - continue to TIM2_IRQHandler4

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-23=265)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare pointer to font -> A1
	la	a1,DrawFont		// -23: [2] address of pointer
	lw	a1,0(a1)		// -21: [2] A1 <- get pointer to font

	// shift font to current font line -> A1
	andi	a0,t2,0x0e		// -19: [2] A0 <- lowest 3 bits of the line (bit 0 is ignored, 2 scanlines per 1 graphics line)
	slli	a0,a0,5			// -17: [1] A0 <- offset in the font (64 bytes per line)
	add	a1,a1,a0		// -16: [1] A1 <- shift pointer to current line of the font

	// prepare number of samples -> A3
	li	a3,32			// -15: [1]

	.align	2,,			// -14: [1]

// [32 loop] send sample ... This address must be aligned

// Registers:
//  A0 = temporary with sample
//  A1 = pointer to font
//  A2 = delay counter
//  A3 = loop counter
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T0-T1 =
//  T2 = current scanline
//  RA = return address

	// [3] load next character
2:	lbu	a2,0(a4)		// -13: [2] A0 <- load text character
	addi	a4,a4,1			// -11: [1] increase sample address

	// [6] load font sample
	andi	a0,a2,0x3f		// -10: [2] A2 <- character index
	add	a0,a0,a1		// -8: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// -7: [3] A0 <- load font sample

	// [4] invert sample
	slli	a2,a2,32-8		// -4: [1] check bit 7
	bgez	a2,5f			// -3: [1,3] skip if bit 7 is not set
	not	a0,a0			// -2: [1] invert sample
	nop				// -1: [1]

	// [2] send sample
5:	sw	a0,SPI_DATAR_OFF(a5)	// 0: [2] send sample to SPI

	// [12] delay
	j	1f			// +2: [3]
1:	j	1f			// +5: [3]
1:	j	1f			// +8: [3]
1:	j	1f			// +11: [3]
1:	nop				// +14: [1]

	// [2,4] loop counter
	addi	a3,a3,-1		// +15: [1] decrease loop counter
	bnez	a3,2b			// +16: [1,3] 
					// +17 (pass), +19 (loop)

	// send black color
8:	sw	x0,SPI_DATAR_OFF(a5)	// +17: send black sample to SPI

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a1,0x0f			// to compare
	and	a0,t2,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

1:	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

#endif // VMODE == 7

// ============================================================================
//                   Timer handler - draw VGA graphics line
// ============================================================================
// Hardware prologie/epilogue HPE (2 levels):
//  Interrupt saves working registers: x1 (ra), x5-x7 (t0-t2), x10-x15 (a0-a5)

	.align  4,,
.global TIM2_IRQHandler
TIM2_IRQHandler:

// ==== Clear interrupt flag
// Registers:
//  A0-A5, T0-T2 =
//  RA = return address

	// clear compare interrupt flag (Timer 2, channel 1)
	li	a2,TIM2_BASE		// A2 <- Timer 2 base
	lw	a1,TIM_INTFR_OFF(a2)	// A1 <- get INTFR register
	lw	a0,TIM_CNT_OFF(a2)	// A0 <- load timer counter
	andi	a1,a1,~(1<<1)		// clear interrupt flag
	sw	a1,TIM_INTFR_OFF(a2)	// set INTFR register

// ==== Time synchronization
// Registers:
//  A0 = Timer 2 counter value
//  A1-A5,T0-T2 =
//  RA = return address

	//  The exact interruption time may vary within a range of 1-7 processor clock
	//  cycles due to the varying length of instructions in the main program.

	// >>>>>>>> SETUP
	//  If you change Timer 2 channel 1 compare value, setup this
	//  correction - select 0 to 7 to minimise display noise.
#ifdef VMODE_SHIFT	// custom shift VMODE time correction
	addi	a0,a0,VMODE_SHIFT	// time correction: select 0 to 7
#else

#if VMODE == 0
	addi	a0,a0,7			// time correction: select 0 to 7
#elif VMODE == 1
	addi	a0,a0,7			// time correction: select 0 to 7
#elif VMODE == 2
	addi	a0,a0,6			// time correction: select 0 to 7
#elif VMODE == 3
	addi	a0,a0,7			// time correction: select 0 to 7
#elif VMODE == 4
	addi	a0,a0,6			// time correction: select 0 to 7
#elif VMODE == 5
	addi	a0,a0,6			// time correction: select 0 to 7
#elif VMODE == 6
	addi	a0,a0,1			// time correction: select 0 to 7
#elif VMODE == 7
	addi	a0,a0,0			// time correction: select 0 to 7
#endif

#endif
	// <<<<<<<<

	andi	a0,a0,7			// mask lower 3 bits of the timer counter
	slli	a0,a0,1			// timer * 2 (because jump to NOPs is multiply of 2 bytes)
	la	a2,TIM2_IRQHandler_sync	// table of 7x NOP instruction
	add	a0,a0,a2		// A0 <- jump address
	
	.align  2,,
	jr	a0			// jump to NOP and delay additional 'x' clock cycles
	.align	2,,

TIM2_IRQHandler_sync:
	nop_rep	7			// 0..7: +7..+0 clk

// ==== Get current scanline

	// load current scanline -> T2
	la	a0,DispLine
	lw	t2,0(a0)

// Registers:
//  A0-A5, T0-T1 =
//  T2 = current scanline
//  RA = return address

	// check active image
#if VMODE == 0
	li	a0,256
#elif (VMODE == 2) || (VMODE == 5) || (VMODE == 7)
	li	a0,384
#else
	li	a0,480
#endif
	bge	t2,a0,TIM2_IRQHandler2 // not active image

// ==== active image

	// load pointer to graphics buffer -> A4
	la	a4,FrameBufAddr
	lw	a4,0(a4)

	// pointer to SPI1 base -> A5
	li	a5,SPI1_BASE

// Registers:
//  A0-A2, T0-T1 =
//  A3 = pointer to attribute buffer
//  A4 = pointer to source graphics buffer
//  A5 = SPI
//  T2 = current line
//  RA = return address

	// draw VGA line (continue to TIM2_IRQHandler4)
	vga_draw


// ==== VSYNC
// Registers:
//  A0-A5, T0-T1 =
//  T2 = current scanline
//  RA = return address

	.align  2,,

TIM2_IRQHandler2:

#if (VMODE == 5) || (VMODE == 6) || (VMODE == 7)
	la	a0,TIM2_IRQHandler2B
	jr	a0
	.section .text
TIM2_IRQHandler2B:
#endif

	// check front porch
#if VMODE == 0
	li	a1,256+112+10
#elif (VMODE == 2) || (VMODE == 5) || (VMODE == 7)
	li	a1,384+48+10
#else
	li	a1,480+10
#endif
	blt	t2,a1,TIM2_IRQHandler4	// front porch - black line

	// VSYNC
	li	a3,GPIOC_BASE		// A3 <- port C
	li	a0,1<<4			// A0 <- pin 4 of port C

// Registers:
//  A1-A2,A4,A5, T0-T1 =
//  A0 = mask of pin 7
//  A3 = GPIOC base
//  T2 = current scanline
//  RA = return address

#if VMODE == 0
	li	a1,256+112+10+2 - 1	// A1 <- index of last VSYNC scanline
#elif (VMODE == 2) || (VMODE == 5) || (VMODE == 7)
	li	a1,384+48+10+2 - 1	// A1 <- index of last VSYNC scanline
#else
	li	a1,480+10+2 - 1		// A1 <- index of last VSYNC scanline
#endif
	bgt	t2,a1,TIM2_IRQHandler3	// not VSYNC, serve back porch

	// start VSYNC pulse (send 0 to PC4)
	sw	a0,GPIO_BCR_OFF(a3)	// send 0 to PC4
	bne	t2,a1,TIM2_IRQHandler4	// skip if not last line of VSYNC

// ==== Music
// Registers:
//  A0-A5, T0-T1 =
//  T2 = current scanline
//  RA = return address

#if USE_SOUND		// 1=use sound support

// Registers:
//  A0 = remaining length
//  A1 = SoundMelodyLen variable
//  A2 = SoundMelodyPtr variable
//  A3 = melody pointer
//  A4 = TIM1 base
//  A5,T0-T1 =
//  T2 = current scanline
//  RA = return address

	// get tone counter
	la	a1,SoundMelodyLen
	lh	a0,0(a1)		// A0 <- remaining length
	beqz	a0,TIM2_IRQHandler4	// no melody, quit
	la	a2,SoundMelodyPtr
	li	a4,TIM1_BASE		// A4 <- Timer 1 base
	bgtz	a0,4f			// valid counter

// The audio output is via PD4 (pin 8), Timer 1 channel 4, mapping 3.

	// request to start new melody
	la	a3,SoundMelodyNext
	lw	a3,0(a3)		// A3 <- pointer to next melody
	sw	a3,0(a2)		// save new pointer
	j	5f			// start new note

	// decrease counter
4:	addi	a0,a0,-1		// shift length counter
	sh	a0,0(a1)		// save new counter
	bnez	a0,TIM2_IRQHandler4	// counter not 0, continue with this tone

	// shift current melody pointer
	lw	a3,0(a2)		// A3 <- current melody pointer
	addi	a3,a3,4			// shift melody pointer
	sw	a3,0(a2)		// save new pointer

	// start new note
5:	lhu	a0,0(a3)		// A0 <- note length
	sh	a0,0(a1)		// save counter
	beqz	a0,8f			// stop melody

	// get note divider
	lhu	a3,2(a3)		// A3 <- note divider
	beqz	a3,8f			// pause

	// set timer load
	sw	a3,TIM_ATRLR_OFF(a4)	// save auto-reload register
	srli	a3,a3,1			// divider / 2
	sw	a3,TIM_CH4CVR_OFF(a4)	// save compare register

	// enable melody
	lw	a0,TIM_CCER_OFF(a4)	// load compare register
	li	a1,1<<12
	or	a0,a0,a1		// enable channel 4
	sw	a0,TIM_CCER_OFF(a4)	// save compare register
	j	TIM2_IRQHandler4

	// stop melody
8:	lw	a0,TIM_CCER_OFF(a4)	// load compare register
	li	a1,~(1<<12)
	and	a0,a0,a1		// disable channel 4
	sw	a0,TIM_CCER_OFF(a4)	// save compare register

#endif // USE_SOUND

	j	TIM2_IRQHandler4

// ==== Back porch
// Registers:
//  A1-A2,A4,A5,T0-T1 =
//  A0 = mask of pin 7
//  A3 = GPIOC base
//  T2 = current scanline
//  RA = return address

TIM2_IRQHandler3:

	// back porch - stop VSYNC pulse (1 to PC4)
	sw	a0,GPIO_BSHR_OFF(a3)	// send 1 to PC4

#if USE_KEY		// 1=use keyboard support

// ==== Buttons
// Registers:
//  A0-A3, T0-T1 =
//  A4 = value of CPUIntLocked ... -> key index
//  A5 = pointer to CPUIntLocked ... -> received byte, 5 bits, 1=key is pressed
//  T2 = current scanline
//  RA = return address

	la	a5,CPUIntLocked
	lbu	a4,0(a5)		// A4 <- locked

// #define KEY_SCANLINE_1	(480+10+2+1)	// scanline 1: set ROW1 to 0, send CPU_CMD_ROW41
	li	a1,KEY_SCANLINE_1
	bne	t2,a1,TIM2_IRQHandler3_2

	// unlock
	la	a3,CPUIntLockedReq
	lbu	a4,0(a3)		// A4 <- lock request
	sb	a4,0(a5)		// save new state of the lock
	bnez	a4,TIM2_IRQHandler4	// locked

	// set ROW1 (PC3) to 0
	li	a3,GPIOC_BASE		// A3 <- port C
	li	a1,1<<3			// A1 <- PC3 pin
	sw	a1,GPIO_BCR_OFF(a3)	// set ROW1 to 0

	// send CPU_CMD_ROW41 to CPU2
	li	a3,USART1_BASE		// A3 <- USART1 base
	lw	a1,USART_DATAR_OFF(a3)	// A1 <- destroy possible received false data
	li	a1,CPU_CMD_ROW41	// A1 <- command CPU_CMD_ROW41
	sw	a1,USART_DATAR_OFF(a3)	// send command
	j	TIM2_IRQHandler4

// #define KEY_SCANLINE_2	(480+10+2+2)	// scanline 2: set ROW1 to 1, receive byte 1, process byte 1 of ROW1
TIM2_IRQHandler3_2:
	bnez	a4,TIM2_IRQHandler4	// locked

	li	a1,KEY_SCANLINE_2
	bne	t2,a1,TIM2_IRQHandler3_3

	// set ROW1 (PC3) to 1
	li	a3,GPIOC_BASE		// A3 <- port C
	li	a1,1<<3			// A1 <- PC3 pin
	sw	a1,GPIO_BSHR_OFF(a3)	// set ROW1 to 1

	// receive byte 1
	li	a3,USART1_BASE		// A3 <- USART1 base
	lw	a5,USART_DATAR_OFF(a3)	// A5 <- receive byte 1
	li	a4,1+0*5		// A4 <- start key index, byte 1 of ROW1
	j	TIM2_IRQHandler3_10	// process byte

// #define KEY_SCANLINE_3	(480+10+2+3)	// scanline 3: set ROW2 to 0, send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW1
TIM2_IRQHandler3_3:
	li	a1,KEY_SCANLINE_3
	bne	t2,a1,TIM2_IRQHandler3_4

	// set ROW2 (PC0) to 0
	li	a3,GPIOC_BASE		// A3 <- port C
	li	a1,1<<0			// A1 <- PC0 pin
	sw	a1,GPIO_BCR_OFF(a3)	// set ROW2 to 0

	// receive byte 2
	li	a3,USART1_BASE		// A3 <- USART1 base
	lw	a5,USART_DATAR_OFF(a3)	// A5 <- receive byte 2
	li	a4,1+1*5		// A4 <- start key index, byte 2 of ROW1

	// send CPU_CMD_ROW41 to CPU2
	li	a2,CPU_CMD_ROW41	// A1 <- command CPU_CMD_ROW41
	sw	a2,USART_DATAR_OFF(a3)	// send command
	j	TIM2_IRQHandler3_10	// process byte

// #define KEY_SCANLINE_4	(480+10+2+4)	// scanline 4: set ROW2 to 1, receive byte 1, process byte 1 of ROW2
TIM2_IRQHandler3_4:
	li	a1,KEY_SCANLINE_4
	bne	t2,a1,TIM2_IRQHandler3_5

	// set ROW2 (PC0) to 1
	li	a3,GPIOC_BASE		// A3 <- port C
	li	a1,1<<0			// A1 <- PC0 pin
	sw	a1,GPIO_BSHR_OFF(a3)	// set ROW2 to 1

	// receive byte 1
	li	a3,USART1_BASE		// A3 <- USART1 base
	lw	a5,USART_DATAR_OFF(a3)	// A5 <- receive byte 1
	li	a4,1+2*5		// A4 <- start key index, byte 1 of ROW2
	j	TIM2_IRQHandler3_10	// process byte

// #define KEY_SCANLINE_5	(480+10+2+5)	// scanline 5: set ROW3 to 0, send CPU_CMD_ROW40, receive byte 2, process byte 2 or ROW2
TIM2_IRQHandler3_5:
	li	a1,KEY_SCANLINE_5
	bne	t2,a1,TIM2_IRQHandler3_6

	// set ROW3 (PD7) to 0
	li	a3,GPIOD_BASE		// A3 <- port D
	li	a1,1<<7			// A1 <- PD7 pin
	sw	a1,GPIO_BCR_OFF(a3)	// set ROW3 to 0

	// receive byte 2
	li	a3,USART1_BASE		// A3 <- USART1 base
	lw	a5,USART_DATAR_OFF(a3)	// A5 <- receive byte 2
	li	a4,1+3*5		// A4 <- start key index, byte 2 of ROW2

	// send CPU_CMD_ROW40 to CPU2
	li	a2,CPU_CMD_ROW40	// A1 <- command CPU_CMD_ROW40
	sw	a2,USART_DATAR_OFF(a3)	// send command
	j	TIM2_IRQHandler3_10	// process byte

// #define KEY_SCANLINE_6	(480+10+2+6)	// scanline 6: set ROW3 to 1, receive byte 1, process byte 1 of ROW3
TIM2_IRQHandler3_6:
	li	a1,KEY_SCANLINE_6
	bne	t2,a1,TIM2_IRQHandler3_7

	// set ROW3 (PD7) to 1
	li	a3,GPIOD_BASE		// A3 <- port D
	li	a1,1<<7			// A1 <- PD7 pin
	sw	a1,GPIO_BSHR_OFF(a3)	// set ROW3 to 1

	// receive byte 1
	li	a3,USART1_BASE		// A3 <- USART1 base
	lw	a5,USART_DATAR_OFF(a3)	// A5 <- receive byte 1
	li	a4,1+4*5		// A4 <- start key index, byte 1 of ROW3
	j	TIM2_IRQHandler3_10	// process byte

// #define KEY_SCANLINE_7	(480+10+2+7)	// scanline 7: send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW3
TIM2_IRQHandler3_7:
	li	a1,KEY_SCANLINE_7
	bne	t2,a1,TIM2_IRQHandler3_8

	// receive byte 2
	li	a3,USART1_BASE		// A3 <- USART1 base
	lw	a5,USART_DATAR_OFF(a3)	// A5 <- receive byte 2
	li	a4,1+5*5		// A4 <- start key index, byte 2 of ROW3

	// send CPU_CMD_ROW41 to CPU2
	li	a2,CPU_CMD_ROW41	// A1 <- command CPU_CMD_ROW41
	sw	a2,USART_DATAR_OFF(a3)	// send command
	j	TIM2_IRQHandler3_10	// process byte

// #define KEY_SCANLINE_8	(480+10+2+8)	// scanline 8: receive byte 1, process byte 1 of ROW4
TIM2_IRQHandler3_8:
	li	a1,KEY_SCANLINE_8
	bne	t2,a1,TIM2_IRQHandler3_9

	// receive byte 1
	li	a3,USART1_BASE		// A3 <- USART1 base
	lw	a5,USART_DATAR_OFF(a3)	// A5 <- receive byte 1
	li	a4,1+6*5		// A4 <- start key index, byte 1 of ROW4
	j	TIM2_IRQHandler3_10	// process byte

// #define KEY_SCANLINE_9	(480+10+2+9)	// scanline 9: receive byte 2, process byte 2 or ROW4
TIM2_IRQHandler3_9:
	li	a1,KEY_SCANLINE_9
	bne	t2,a1,TIM2_IRQHandler4

	// receive byte 2
	li	a3,USART1_BASE		// A3 <- USART1 base
	lw	a5,USART_DATAR_OFF(a3)	// A5 <- receive byte 2
	li	a4,1+7*5		// A4 <- start key index, byte 2 of ROW4

	// process byte
TIM2_IRQHandler3_10:

// Registers:
//  A0-A3, T0-T1 =
//  A4 = key index
//  A5 = received byte, 5 bits, 1=key is pressed
//  T2 = current scanline
//  RA = return address

	// pointer to KeyReleaseCnt table
	la	a3,KeyReleaseCnt-1
	add	a3,a3,a4		// A3 <- pointer to KeyReleaseCnt table
	li	t1,5			// T1 <- number of keys

// Registers:
//  A0-A2, T0 =
//  A3 = pointer to KeyReleaseCnt table + key repeat counter
//  A4 = key index
//  A5 = received byte, 5 bits, 1=key is pressed
//  T1 = key counter
//  T2 = current scanline
//  RA = return address

	// check if button is pressed
2:	andi	a0,a5,1			// A0 <- get button bit
	srli	a5,a5,1			// shift by 1 bit
	beqz	a0,4f			// button is not pressed

	// Button is pressed: release counter -> A0; is pressed for the first time?
	lbu	a0,0(a3)		// A0 <- get release counter
	li	a2,KEYCNT_PRESS		// A2 <- first repeat is 0.3 sec
	beqz	a0,6f			// release counter is 0, pressed for the first time

	// already pressed - count repeat counter
	lbu	a0,KEY_NUM(a3)		// A0 <- get repeat counter
	addi	a0,a0,-1		// decrement repeat counter
	sb	a0,KEY_NUM(a3)		// save new repeat counter
	bnez	a0,3f			// no repeat
	li	a2,KEYCNT_REPEAT	// A2 <- repeat is 0.1 sec

// Registers:
//  A0-A1, T0 =
//  A2 = ...repeat counter
//  A3 = pointer to key release counter + key repeat counter
//  A4 = key index
//  A5 = received byte, 5 bits, 1=key is pressed
//  T1 = key counter
//  T2 = current scanline
//  RA = return address

	// set repeat counter
6:	sb	a2,KEY_NUM(a3)		// setup repeat counter

	// Button is pressed for the first time: send button to keyboard buffer
	la	a2,KeyWriteOff		// T1 <- keyboard buffer write offset variable
	lbu	a1,0(a2)		// A1 <- get write offset to keyboard buffer
	addi	a0,a1,1			// A0 <- shift write offset
	li	t0,KEYBUF_SIZE		// T0 <- max. buffer size
	bne	a0,t0,1f		// not end of the buffer
	li	a0,0			// A0 <- reset offset to the start of the buffer

// Registers:
//  A0 = ... new write offset to keyboard buffer
//  A1 = ... old write offset to keyboard buffer 
//  A2 = ... keyboard buffer write offset variable 
//  A3 = pointer to key release counter + key repeat counter
//  A4 = key index
//  A5 = received byte, 5 bits, 1=key is pressed
//  T0 = ... max. buffer size, read offset from keyboard buffer, keyboard buffer
//  T1 = key counter
//  T2 = current scanline
//  RA = return address

1:	la	t0,KeyReadOff		// T0 <- keyboard buffer read offset
	lbu	t0,0(t0)		// T0 <- get read offset from keyboard buffer
	beq	a0,t0,3f		// skip if buffer is full

	la	t0,KeyBuf		// T0 <- keyboard buffer
	add	t0,a1,t0		// T0 <- write pointer to keyboard buffer
	sb	a4,0(t0)		// save button to keyboard buffer

	sb	a0,0(a2)		// save new write offset

	// initialize press counter (update interval = 1/60 = 17ms, release time = 50 ms = 3 steps)
3:	li	a0,KEYCNT_REL		// release interval = (4-1)*17 = 50ms
	sb	a0,0(a3)		// save new release counter

	// Button is not pressed: decrease release counter
4:	lbu	a0,0(a3)		// A0 <- get release counter
	beqz	a0,5f			// counter is already 0
	addi	a0,a0,-1		// decrease counter
	sb	a0,0(a3)		// save new release counter

// Registers:
//  A0-A2, T0 =
//  A3 = pointer to key release counter + key repeat counter
//  A4 = key index
//  A5 = received byte, 5 bits, 1=key is pressed
//  T1 = key counter
//  T2 = current scanline
//  RA = return address

	// shift to next button
5:	addi	a3,a3,1			// shift key release counter table
	addi	a4,a4,1			// shift button index
	addi	t1,t1,-1		// decrease loop counter
	bnez	t1,2b			// next button

#endif // USE_KEY

//	j	TIM2_IRQHandler4

// ==== Increase scanline
// Registers:
//  A0-A5, T0-T1 =
//  T2 = current scanline
//  RA = return address

TIM2_IRQHandler4:

	// inrease current scanline
	addi	t2,t2,1			// T2 <- next scanline
	li	a2,525			// A2 <- total number of scanlines
	blt	t2,a2,8f		// not total line yet

	// reset to start of image
	li	t2,0			// T2 <- new scanline = 0

	// increase current frame
	la	a0,DispFrame		// A0 <- current frame
	lw	a1,0(a0)		// A1 <- get current frame 
	addi	a1,a1,1			// increase current frame
	sw	a1,0(a0)		// save new current frame

	// reset pointers
	la	a0,FrameBuf		// A0 <- frame buffer
#if VMODE == 5
	lw	a0,0(a0)		// A0 <- frame buffer address
#endif
	la	a1,FrameBufAddr		// A1 <- frame buffer address
	sw	a0,0(a1)		// save new pointer

	// save new scanline
8:	la	a0,DispLine
	sw	t2,0(a0)		// save new scanline
	mret

#endif // USE_DISP
