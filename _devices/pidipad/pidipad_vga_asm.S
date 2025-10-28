
// ****************************************************************************
//
//                        PidiPad - VGA display driver
//
// ****************************************************************************

// project configuration
#include "config.h"		// project configuration
#include "_config.h"		// default configuration

#if USE_DISP		// 1=use display support

#define	PERIPH_BASE		0x40000000	// Peripheral base address in the alias region
#define APB1PERIPH_BASE		PERIPH_BASE			// 0x40000000
#define APB2PERIPH_BASE		(PERIPH_BASE + 0x10000)		// 0x40010000

#define GPIOA_BASE		(APB2PERIPH_BASE + 0x0800)	// PA port 0x40010800
#define GPIOB_BASE		(APB2PERIPH_BASE + 0x0C00)	// PB port 0x40010C00
#define GPIOC_BASE		(APB2PERIPH_BASE + 0x1000)	// PC port base (0x40011000)
#define GPIOD_BASE		(APB2PERIPH_BASE + 0x1400)	// PD port 0x40011400
#define SPI1_BASE		(APB2PERIPH_BASE + 0x3000)	// SPI1 base (0x40013000)
#define TIM1_BASE		(APB2PERIPH_BASE + 0x2C00)	// TIM1 0x40012C00
#define TIM2_BASE		(APB1PERIPH_BASE + 0x0000)	// TIM2 0x40000000

#define SPI_DATAR_OFF		0x0C		// data register offset
#define GPIO_INDR_OFF		0x08		// GPIO input register offset
#define GPIO_OUTDR_OFF		0x0C		// GPIO output register offset
#define GPIO_BSHR_OFF		0x10		// GPIO bit set output data register
#define GPIO_BCR_OFF		0x14		// GPIO bit clear output data register
#define TIM_INTFR_OFF		0x10		// timer interrupt register offset
#define TIM_CCER_OFF		0x20		// timer compare register
#define TIM_CNT_OFF		0x24		// timer counter register offset
#define TIM_ATRLR_OFF		0x2C		// ATRLR timer auto-reload value register
#define TIM_CH1CVR_OFF		0x34		// CH1CVR timer compare/capture register 1

.global FrameBuf			// (u8[]) display graphics buffer
#if VMODE != 5
.global AttrBuf				// (u8[]) display attribute buffer (color of 2 pixels: 1st pixels in bits 1..3, 2nd pixel in bits 5..7)
.global AttrBufAddr			// (u8*) current pointer to attribute buffer
#endif
#if (VMODE == 7) || (VMODE == 8)
.global FontBuf				// (u8[]) bont buffer 8x8
#endif
.global DispLine			// (int) current display line
.global DispFrame			// (u32) current frame
.global FrameBufAddr			// (u8*) current pointer to graphics buffer
.global DispTimTest			// test - get TIM-CNT value at start of image
.global DrawFont			// (u8*) current pointer to font
#define KEY_NUM			8	// number of buttons

#define KEYBUF_SIZE		8	// size of keyboard buffer
// If you change the settings, also check this in pidipad_key.h.
.global KeyReleaseCnt			// (u8[]) key release counter + key repeat counter; >0 if key is pressed (without NOKEY)
.global KeyBuf				// (u8[]) keyboard buffer
.global KeyWriteOff			// (u8) write offset to keyboard buffer
.global KeyReadOff			// (u8) read offset from keyboard buffer

.global SoundMelodyPtr			// (sMelodyNote*) pointer to current melody
.global SoundMelodyNext			// (sMelodyNote*) pointer to next melody
.global SoundMelodyLen			// (s16) remaining length of current tone (0 = no melody, -1 = start next melody)

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
//    1: Graphics mode 160x120 pixels mono with color attributes 8x8 pixels
// ============================================================================

#if VMODE == 1

// ---- draw code
// Registers:
//  A0 = temporary with sample
//  A1 = temporary with attribute
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  A4 = SPI
//  A5 = PORTB
//  T0 = current line
//  T1 = return address
//  T2 = TIM

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-65=223)
//	lw	a0,TIM_CNT_OFF(t2)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,
	// [2] send gap to SPI, to start SPI data synchronization
	sw	x0,SPI_DATAR_OFF(a4)	// -65: [2] send gap to SPI

	// [52] delay
	li	a1,13			// -63: [1]
	.align 2,,			// -62: [1]
	// [12*4+2=50] loop		// -61: [50]
1:	addi	a1,a1,-1		// ... [1]
	bnez	a1,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [1] prepare number of samples/2 -> A1
	li	a1,10			// -11: [1]

	.align 2,,			// -10: [1]

// [128 loop] send 2 samples ... This address must be aligned

	// [6] send 1st sample to SPI
2:	nop				// -9: [1]
	lbu	a0,0(a2)		// -8: [2] A0 <- load sample
	addi	a2,a2,1			// -6: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(a4)	// -5: [2] send sample to SPI

	// [5] send 1st color
	lbu	a0,0(a3)		// -3: [2] A1 <- load attribute
	li	t2,13			// -1: [1] loop counter
	sw	a0,GPIO_OUTDR_OFF(a5)	//  0: [2] send color

	// [54] delay
	.align 2,,			// +2: [1]
	// [12*4+2=50] loop		// +3: [50]
1:	addi	t2,t2,-1		// ... [1]
	bnez	t2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	3			// +53: [3]

	// [5] send 2nd sample to SPI
	lbu	a0,0(a2)		// +56: [2] A0 <- load sample
	addi	a2,a2,1			// +58: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(a4)	// +59: [2] send sample to SPI

	// [5] send 2nd color
	lbu	a0,0(a3)		// +61: [2] A1 <- load attribute
	srli	a0,a0,4			// +63: [1] A1 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	//  0: [2] send color

	// [48] delay
	li	t2,12			// +2: [1]
	.align 2,,			// +3: [1]
	// [11*4+2=46] loop		// +4: [46]
1:	addi	t2,t2,-1		// ... [1]
	bnez	t2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [1] increase attribute address
	addi	a3,a3,1			// +50: [1] increase attribute address

	// [4,2] loop counter
	addi	a1,a1,-1		// +51: [1]
	bnez	a1,2b			// +52: [1,3]
					// +53 (pass), +55 (loop):

	// send black color
	sw	x0,SPI_DATAR_OFF(a4)	// +53: [2] send black sample to SPI
	j	1f			// +55: [3]
1:	j	1f			// +58: [3]
1:	j	1f			// +61: [3]
1:	sw	x0,GPIO_OUTDR_OFF(a5)	// +64: [2] send black color

// Registers:
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  T0 = current line
//  T1 = return address

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a1,3			// to compare
	and	a0,t0,a1		// get lowest 2 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer

	// save new attribute pointer only every 32th scanline (divide line by 8*4=32)
1:	li	a1,0x1f			// to compare
	and	a0,t0,a1		// get lowest 5 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,AttrBufAddr
	sw	a3,0(a4)		// save new pointer

1:	j	TIM2_IRQHandler4	// increase scanline

.endm

#endif // VMODE == 1

// ============================================================================
//    2: Graphics mode 160x120 pixels mono with color attributes 4x4 pixels
// ============================================================================

#if VMODE == 2

// ---- draw code
// Registers:
//  A0 = temporary with sample
//  A1 = temporary with attribute
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  A4 = SPI
//  A5 = PORTB
//  T0 = current line
//  T1 = return address
//  T2 = TIM

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-65=223)
//	lw	a0,TIM_CNT_OFF(t2)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,
	// [2] send gap to SPI, to start SPI data synchronization
	sw	x0,SPI_DATAR_OFF(a4)	// -65: [2] send gap to SPI

	// [52] delay
	li	a1,13			// -63: [1]
	.align 2,,			// -62: [1]
	// [12*4+2=50] loop		// -61: [50]
1:	addi	a1,a1,-1		// ... [1]
	bnez	a1,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [1] prepare number of samples -> A1
	li	a1,20			// -11: [1]

	.align 2,,			// -10: [1]

// [64 loop] ... This address must be aligned

	// [6] send sample to SPI
2:	nop				// -9: [1]
	lbu	a0,0(a2)		// -8: [2] A0 <- load sample
	addi	a2,a2,1			// -6: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(a4)	// -5: [2] send sample to SPI

	// [5] send 1st color
	lbu	a0,0(a3)		// -3: [2] A0 <- load attribute
	addi	a3,a3,1			// -1: [1] increase attribute address
	sw	a0,GPIO_OUTDR_OFF(a5)	//  0: [2] send color

	// [29] delay
	li	t2,7			// +2: [1]
	.align 2,,			// +3: [0]
	// [6*4+2=26] loop		// +3: [26]
1:	addi	t2,t2,-1		// ... [1]
	bnez	t2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +29: [2]

	// [3] send 2nd color
	srli	a0,a0,4			// +31: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +32: [2] send color

	// [17] delay
	li	a0,4			// +34: [1]
	.align 2,,			// +35: [0]
	// [3*4+2=14] loop		// +35: [14]
1:	addi	a0,a0,-1		// ... [1]
	bnez	a0,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +49: [2]

	// [4,2] loop counter
	addi	a1,a1,-1		// +51: [1]
	bnez	a1,2b			// +52: [1,3]
					// +53 (pass), +55 (loop):
	// send black color
	sw	x0,SPI_DATAR_OFF(a4)	// +53: [2] send black sample to SPI
	j	1f			// +55: [3]
1:	j	1f			// +58: [3]
1:	j	1f			// +61: [3]
1:	sw	x0,GPIO_OUTDR_OFF(a5)	// +64: [2] send black color

// Registers:
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  T0 = current line
//  T1 = return address

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a1,3			// to compare
	and	a0,t0,a1		// get lowest 2 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer

	// save new attribute pointer only every 16th scanline (divide line by 4*4=16)
1:	li	a1,0x0f			// to compare
	and	a0,t0,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,AttrBufAddr
	sw	a3,0(a4)		// save new pointer

1:	j	TIM2_IRQHandler4	// increase scanline

.endm

#endif // VMODE == 2

// ============================================================================
//    3: Graphics mode 160x120 pixels mono with color attributes 2x2 pixels
// ============================================================================

#if VMODE == 3

// ---- draw code
// Registers:
//  A0 = temporary with sample
//  A1 = temporary with attribute
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  A4 = SPI
//  A5 = PORTB
//  T0 = current line
//  T1 = return address
//  T2 = TIM

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-65=223)
//	lw	a0,TIM_CNT_OFF(t2)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,
	// [2] send gap to SPI, to start SPI data synchronization
	sw	x0,SPI_DATAR_OFF(a4)	// -65: [2] send gap to SPI

	// [52] delay
	li	a1,13			// -63: [1]
	.align 2,,			// -62: [1]
	// [12*4+2=50] loop		// -61: [50]
1:	addi	a1,a1,-1		// ... [1]
	bnez	a1,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [1] prepare number of samples -> A1
	li	a1,20			// -11: [1]

	.align 2,,			// -10: [1]

// [64 loop] ... This address must be aligned

	// [6] send sample to SPI
2:	nop				// -9: [1]
	lbu	a0,0(a2)		// -8: [2] A0 <- load sample
	addi	a2,a2,1			// -6: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(a4)	// -5: [2] send sample to SPI

	// [5] send 1st color
	lbu	a0,0(a3)		// -3: [2] A0 <- load attribute
	addi	a3,a3,1			// -1: [1] increase attribute address
	sw	a0,GPIO_OUTDR_OFF(a5)	//  0: [2] send color

	// [13] delay
	li	t2,3			// +2: [1]
	.align 2,,			// +3: [0]
	// [2*4+2=10] loop		// +3: [10]
1:	addi	t2,t2,-1		// ... [1]
	bnez	t2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +13: [2]

	// [3] send 2nd color
	srli	a0,a0,4			// +15: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +16: [2] send color

	// [11] delay
	li	a0,3			// +18: [1]
	.align 2,,			// +19: [0]
	// [2*4+2=10] loop		// +19: [10]
1:	addi	a0,a0,-1		// ... [1]
	bnez	a0,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [5] send 3rd color
	lbu	a0,0(a3)		// +29: [2] A1 <- load attribute
	addi	a3,a3,1			// +31: [1] increase attribute address
	sw	a0,GPIO_OUTDR_OFF(a5)	// +32: [2] send color

	// [13] delay
	li	t2,3			// +34: [1]
	.align 2,,			// +35: [0]
	// [2*4+2=10] loop		// +35: [10]
1:	addi	t2,t2,-1		// ... [1]
	bnez	t2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +45: [2]

	// [4] send 4th color
	srli	a0,a0,4			// +47: [1] A1 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +48: [2] send color
	nop				// +50: [1]

	// [4,2] loop counter
	addi	a1,a1,-1		// +51: [1]
	bnez	a1,2b			// +52: [1,3]
					// +53 (pass), +55 (loop):
	// send black color
	sw	x0,SPI_DATAR_OFF(a4)	// +53: [2] send black sample to SPI
	j	1f			// +55: [3]
1:	j	1f			// +58: [3]
1:	j	1f			// +61: [3]
1:	sw	x0,GPIO_OUTDR_OFF(a5)	// +64: [2] send black color

// Registers:
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  T0 = current line
//  T1 = return address

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a1,3			// to compare
	and	a0,t0,a1		// get lowest 2 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer

	// save new attribute pointer only every 8th scanline (divide line by 2*4=8)
1:	li	a1,0x07			// to compare
	and	a0,t0,a1		// get lowest 3 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,AttrBufAddr
	sw	a3,0(a4)		// save new pointer

1:	j	TIM2_IRQHandler4	// increase scanline

.endm

#endif // VMODE == 3

// ============================================================================
//     4: Graphics mode 256x192 pixels mono with color attributes 8x8 pixels
// ============================================================================

#if VMODE == 4

// ---- draw code
// Registers:
//  A0 = temporary with sample
//  A1 = temporary with attribute
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  A4 = SPI
//  A5 = PORTB
//  T0 = current line
//  T1 = return address
//  T2 = TIM

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 416-34=382)
//	lw	a0,TIM_CNT_OFF(t2)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,
	// [3] send gap to SPI, to start SPI data synchronization
	nop				// -34: [1]
	sw	x0,SPI_DATAR_OFF(a4)	// -33: [2] send gap to SPI

	// [21] delay
	li	a1,5			// -31: [1]
	.align 2,,			// -30: [0]
	// [4*4+2=18] loop		// -30: [18]
1:	addi	a1,a1,-1		// ... [1]
	bnez	a1,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// -12: [2]

	// [1] prepare number of samples/2 -> A1
	li	a1,16			// -10: [1]

	.align 2,,			// -9: [1]

// [64 loop] send 2 samples ... This address must be aligned

	// [5] send 1st sample to SPI
2:	lbu	a0,0(a2)		// -8: [2] A0 <- load sample
	addi	a2,a2,1			// -6: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(a4)	// -5: [2] send sample to SPI

	// [5] send 1st color
	lbu	a0,0(a3)		// -3: [2] A0 <- load attribute
	li	t2,6			// -1: [1] loop counter
	sw	a0,GPIO_OUTDR_OFF(a5)	//  0: [2] send color

	// [22] delay
	.align 2,,			// +2: [0]
	// [5*4+2=22] loop		// +2: [22]
1:	addi	t2,t2,-1		// ... [1]
	bnez	t2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [5] send 2nd sample to SPI
	lbu	a0,0(a2)		// +24: [2] A0 <- load sample
	addi	a2,a2,1			// +26: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(a4)	// +27: [2] send sample to SPI

	// [5] send 2nd color
	lbu	a0,0(a3)		// +29: [2] A0 <- load attribute
	srli	a0,a0,4			// +31: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	//  0: [2] send color

	// [17] delay
	li	t2,4			// +2: [1]
	.align 2,,			// +3: [0]
	// [3*4+2=14] loop		// +3: [14]
1:	addi	t2,t2,-1		// ... [1]
	bnez	t2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +17: [2]

	// [1] increase attribute address
	addi	a3,a3,1			// +19: [1] increase attribute address

	// [4,2] loop counter
	addi	a1,a1,-1		// +20: [1]
	bnez	a1,2b			// +21: [1,3]
					// +22 (pass), +24 (loop):

	// send black color
	sw	x0,SPI_DATAR_OFF(a4)	// +22: [2] send black sample to SPI
	j	1f			// +24: [3]
1:	j	1f			// +27: [3]
1:	nop_rep	2			// +30: [2]
	sw	x0,GPIO_OUTDR_OFF(a5)	// +32: [2] send black color

// Registers:
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  T0 = current line
//  T1 = return address

	// save new sample pointer only every 2nd scanline (divide line by 2)
	li	a1,1			// to compare
	and	a0,t0,a1		// get lowest 1 bit
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer

	// save new attribute pointer only every 16th scanline (divide line by 8*2=16)
1:	li	a1,0x0f			// to compare
	and	a0,t0,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,AttrBufAddr
	sw	a3,0(a4)		// save new pointer

1:	j	TIM2_IRQHandler4	// increase scanline

.endm

#endif // VMODE == 4

// ============================================================================
//             5: Graphics mode 144x96 pixels with 8 colors
// ============================================================================

#if VMODE == 5

// ---- draw code
// Registers:
//  A0 = temporary with sample
//  A2 = pointer to graphics buffer
//  A3 = white sample 0xff
//  A4 = SPI
//  A5 = PORTB
//  T0 = current line
//  T1 = return address
//  T2 = TIM

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 352-65=287)
//	lw	a0,TIM_CNT_OFF(t2)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,
	// [2] send gap to SPI, to start SPI data synchronization
	nop				// -65: [1]
	sw	x0,SPI_DATAR_OFF(a4)	// -64: [2] send gap to SPI

	// [52] delay
	li	a1,13			// -62: [1]
	.align 2,,			// -61: [0]
	// [12*4+2=50] loop		// -61: [50]
1:	addi	a1,a1,-1		// ... [1]
	bnez	a1,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	j	1f			// -11: [2]
1:	nop				// -9: [1]

	// [1] white sample to send to SPI
	li	a3,0xff			// -8: [1] A3 <- white sample

	// [1] prepare number of samples -> A1
	li	a1,18			// -7: [1]

	// [1] load first sample
	lbu	t2,0(a2)		// -6: [2] A0 <- load 2 colors

	.align 2,,			// -4: [1]

// [64 loop] ... This address must be aligned

	// [3] send white sample to SPI
2:	sw	a3,SPI_DATAR_OFF(a4)	// -3: [2] send sample to SPI
	nop				// -1: [1]

	// [2] send 1st pixel
	sw	t2,GPIO_OUTDR_OFF(a5)	//  0: [2] send color

	// [4] delay
	j	1f			// +2: [3]
1:	nop				// +5: [1]

	// [4] send 2nd pixel
	srli	t2,t2,4			// +6: [1] A1 <- load 2nd attribute
	addi	a2,a2,1			// +7: [1] increase sample address
	sw	t2,GPIO_OUTDR_OFF(a5)	// +8: [2] send color

	// [3] delay
	j	1f			// +10: [3]

	// [6] send 3rd pixel
1:	lbu	a0,0(a2)		// +13: [2] A0 <- load 2 colors
	addi	a2,a2,1			// +15: [1] increase sample address
	sw	a0,GPIO_OUTDR_OFF(a5)	// +16: [2] send color

	// [5] delay
	j	1f			// +18: [3]
1:	nop_rep	2			// +21: [2]

	// send 4th pixel
	srli	a0,a0,4			// +23: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +24: [2] send color

	// [3] delay
	j	1f			// +26: [3]

	// [6] send 5th pixel
1:	lbu	a0,0(a2)		// +29: [2] A0 <- load 2 colors
	addi	a2,a2,1			// +31: [1] increase sample address
	sw	a0,GPIO_OUTDR_OFF(a5)	// +32: [2] send color

	// [5] delay
	j	1f			// +34: [3]
1:	nop_rep	2			// +37: [2]

	// send 6th pixel
	srli	a0,a0,4			// +39: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +40: [2] send color

	// [3] delay
	j	1f			// +42: [3]

	// [6] send 7th pixel
1:	lbu	a0,0(a2)		// +45: [2] A0 <- load 2 colors
	addi	a2,a2,1			// +47: [1] increase sample address
	sw	a0,GPIO_OUTDR_OFF(a5)	// +48: [2] send color

	// [5] delay
	nop_rep	2
	lbu	t2,0(a2)		// +52: [2] A0 <- load 2 colors
	addi	a1,a1,-1		// +54: [1] loop counter

	// send 8th pixel
	srli	a0,a0,4			// +55: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +56: [2] send color

	// [4,2] loop counter
	bnez	a1,2b			// +58: [1,3]
					// +59 (pass), +61 (loop):
	// send black color
	sw	x0,SPI_DATAR_OFF(a4)	// +59: [2] send black sample to SPI
	nop_rep	2			// +61: [2]
	sw	x0,GPIO_OUTDR_OFF(a5)	// +63: [2] send black color

// Registers:
//  A2 = pointer to graphics buffer
//  T0 = current line
//  T1 = return address

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a1,3			// to compare
	and	a0,t0,a1		// get lowest 2 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer
1:	j	TIM2_IRQHandler4	// increase scanline

.endm

#endif // VMODE == 5

// ============================================================================
//       6: Text mode 40x30 characters of 8x8 pixels, font in Flash
//     7: Text mode 40x30 characters of 8x8 pixels, font in RAM FontBuf
// ============================================================================

#if (VMODE == 6) || (VMODE == 7)

// ---- draw code
// Registers:
//  A0 = temporary
//  A1 = loop counter
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  A4 = SPI
//  A5 = PORTB
//  T0 = current line
//  T1 = return address
//  T2 = (TIM) pointer to font

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-43=245)
//	lw	a0,TIM_CNT_OFF(t2)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare pointer to font -> T2
#if VMODE == 7
	la	t2,FontBuf		// -43: [2]
	nop_rep	2			// -41: [2]
#else
	la	t2,DrawFont		// -43: [2] address of pointer
	lw	t2,0(t2)		// -41: [2] get pointer to font
#endif

	// shift font to current font line -> T2
	andi	a0,t0,0x0e		// -39: [2] A0 <- lowest 3 bits of the line * 2 (ignore bit 0, we use 2 scanlines per 1 graphics line)
	slli	a0,a0,7			// -37: [1] A0 <- offset of the line (1 line = 256 bytes)
	add	t2,t2,a0		// -36: [1] T2 <- shift pointer to current line of the font

	.align 2,,			// -35: [1]
	// [2] send gap to SPI, to start SPI data synchronization
	nop				// -34: [1]
	sw	x0,SPI_DATAR_OFF(a4)	// -33: [2] send gap to SPI

	// [16] delay
	li	a1,4			// -31: [1]
	.align 2,,			// -30: [0]
	// [3*4+2=14] loop		// -30: [14]
1:	addi	a1,a1,-1		// ... [1]
	bnez	a1,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop				// -16: [1]

	// [1] prepare number of samples/2 -> A1
	li	a1,20			// -15: [1]

	.align 2,,			// -14: [0]

// [64 loop] send 2 samples ... This address must be aligned

	// [11] load next character, load font sample and send sample to SPI
2:	lbu	a0,0(a2)		// -14: [2] A0 <- load text character
	addi	a2,a2,1			// -12: [1] increase sample address
	add	a0,a0,t2		// -11: [1] A0 <- address of the sample in the font
#if VMODE == 7
	lbu	a0,0(a0)		// -10: [2] A0 <- load font sample
	j	1f			// -8: [3] ... wait to load
#else
	lbu	a0,0(a0)		// -10: [4] A0 <- load font sample
	nop				// -6: [1] ... wait to load
#endif
1:	sw	a0,SPI_DATAR_OFF(a4)	// -5: [2] send sample to SPI

	// [5] send color
	lbu	a0,0(a3)		// -3: [2] A0 <- load attribute
	nop				// -1: [1] ... wait to load
	sw	a0,GPIO_OUTDR_OFF(a5)	//  0: [2] send color

	// [15] delay
	j	1f			// 2: [3]
1:	j	1f			// 5: [3]
1:	j	1f			// 8: [3]
1:	j	1f			// 11: [3]
1:	j	1f			// 14: [3]

	// [11] load next character, load font sample and send sample to SPI
1:	lbu	a0,0(a2)		// +17: [2] A0 <- load text character
	addi	a2,a2,1			// +19: [1] increase sample address
	add	a0,a0,t2		// +20: [1] A0 <- address of the sample in the font
#if VMODE == 7
	lbu	a0,0(a0)		// +21: [2] A0 <- load font sample
	j	1f  			// -23: [3] ... wait to load
#else
	lbu	a0,0(a0)		// +21: [4] A0 <- load font sample
	nop				// +25: [1] ... wait to load
#endif
1:	sw	a0,SPI_DATAR_OFF(a4)	// +26: [2] send sample to SPI

	// [6] send color
	lbu	a0,0(a3)		// +28: [2] A0 <- load attribute
	nop				// +30: [1] ... wait to load
	srli	a0,a0,4			// +31: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +32: [2] send color

	// [11] delay
	j	1f			// +34: [3]
1:	j	1f			// +37: [3]
1:	j	1f			// +40: [3]
1:	nop_rep	2			// +43: [2]

	// [1] increase attribute address
	addi	a3,a3,1			// +45: [1] increase attribute address

	// [4,2] loop counter
	addi	a1,a1,-1		// +46: [1]
	bnez	a1,2b			// +47: [1,3]
					// +48 (pass), +50 (loop):
	// send black color
	sw	x0,SPI_DATAR_OFF(a4)	// +48: [2] send black sample to SPI

	j	1f			// +50: [3]
1:	j	1f			// +53: [3]
1:	j	1f			// +56: [3]
1:	j	1f			// +59: [3]
1:	nop_rep	2			// +62: [2]

	sw	x0,GPIO_OUTDR_OFF(a5)	// +64: [2] send black color

// Registers:
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  T0 = current line
//  T1 = return address

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a1,0x0f			// to compare
	and	a0,t0,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer

	la	a4,AttrBufAddr
	sw	a3,0(a4)		// save new pointer

1:	j	TIM2_IRQHandler4	// increase scanline

.endm

#endif // VMODE == 6, 7

// ============================================================================
//       8: Text mode 80x30 characters of 8x8 pixels, font in RAM
// ============================================================================

#if VMODE == 8

// ---- draw code
// Registers:
//  A0 = temporary
//  A1 = loop counter
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  A4 = SPI
//  A5 = PORTB
//  T0 = current line
//  T1 = return address
//  T2 = (TIM) pointer to font

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-24=264)
//	lw	a0,TIM_CNT_OFF(t2)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	// prepare pointer to font -> T2
	la	t2,FontBuf		// -24: [2]

	// shift font to current font line -> T2
	andi	a0,t0,0x0e		// -22: [2] A0 <- lowest 3 bits of the line * 2 (ignore bit 0, we use 2 scanlines per 1 graphics line)
	slli	a0,a0,7			// -20: [1] A0 <- offset of the line (1 line = 256 bytes)
	add	t2,t2,a0		// -19: [1] T2 <- shift pointer to current line of the font

	.align 2,,			// -18: [1]
	// [2] send gap to SPI, to start SPI data synchronization
	sw	x0,SPI_DATAR_OFF(a4)	// -17: [2] send gap to SPI

	// [4] delay
	nop				// -15: [1]
	j	1f			// -14: [3]

	// [1] prepare number of samples/2 -> A1
1:	li	a1,40			// -11: [1]

	.align 2,,			// -10: [0]

// [32 loop] send 2 samples ... This address must be aligned

	// [8] load next character, load font sample and send sample to SPI
2:	lbu	a0,0(a2)		// -10: [2] A0 <- load text character
	addi	a2,a2,1			// -8: [1] increase sample address
	add	a0,a0,t2		// -7: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// -6: [2] A0 <- load font sample
	sw	a0,SPI_DATAR_OFF(a4)	// -4: [2] send sample to SPI

	// [4] send color
	lbu	a0,0(a3)		// -2: [2] A0 <- load attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	//  0: [2] send color

	// [2] delay
	nop_rep	2			// +2: [2]

	// [8] load next character, load font sample and send sample to SPI
	lbu	a0,0(a2)		// +4: [2] A0 <- load text character
	addi	a2,a2,1			// +6: [1] increase sample address
	add	a0,a0,t2		// +7: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// +8: [2] A0 <- load font sample
	sw	a0,SPI_DATAR_OFF(a4)	// +10: [2] send sample to SPI

	// [6] send color
	lbu	a0,0(a3)		// +12: [2] A0 <- load attribute
	addi	a3,a3,1			// +14: [1] increase attribute address
	srli	a0,a0,4			// +15: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +16: [2] send color

	// [4,2] loop counter
	addi	a1,a1,-1		// +18: [1] loop counter
	bnez	a1,2b			// +19: [1,3]
					// +20 (pass), +22 (loop):

	// send black color
	sw	x0,SPI_DATAR_OFF(a4)	// +20: [2] send black sample to SPI

	j	1f			// +22: [3]
1:	j	1f			// +25: [3]
1:	j	1f			// +28: [3]
1:	nop				// +31: [1]

	sw	x0,GPIO_OUTDR_OFF(a5)	// +32: [2] send black color

// Registers:
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  T0 = current line
//  T1 = return address

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a1,0x0f			// to compare
	and	a0,t0,a1		// get lowest 4 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer

	la	a4,AttrBufAddr
	sw	a3,0(a4)		// save new pointer

1:	j	TIM2_IRQHandler4	// increase scanline

.endm

#endif // VMODE == 8

// ============================================================================
//     9: Graphics mode 128x80 pixels mono with color attributes 1x1 pixels
// ============================================================================

#if VMODE == 9

// ---- draw code
// Registers:
//  A0 = temporary with sample
//  A1 = loop counter
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  A4 = SPI
//  A5 = PORTB
//  T0 = current line, temporary
//  T1 = return address
//  T2 = TIM, temporary

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 416-67=349)
//	lw	a0,TIM_CNT_OFF(t2)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,			// -67: [1]
	// [2] send gap to SPI, to start SPI data synchronization
	sw	x0,SPI_DATAR_OFF(a4)	// -66: [2] send gap to SPI

	// [52] delay
	li	a1,13			// -64: [1]

	.align 2,,			// -63: [1]

	// [12*4+2=50] loop		// -62: [50]
1:	addi	a1,a1,-1		// ... [1]
	bnez	a1,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// save T0
	addi	sp,sp,-4		// -12: [1]
	sw	t0,0(sp)		// -11: [2]

	// [6] load sample
1:	lbu	t0,0(a2)		// -9: [2] T0 <- load sample

	// [1] load colors
	lbu	t2,0(a3)		// -7: [2] T2 <- load 2 colors

	// [1] prepare number of samples -> A1
	li	a1,16			// -5: [1] 

	.align 2,,			// -4: [1]

// [64 loop] ... This address must be aligned

// T0 = sample
// T2 = color

	// [3] send sample
2:	addi	a2,a2,1			// -3: [1] increase sample address
	sw	t0,SPI_DATAR_OFF(a4)	// -2: [2] send sample to SPI

	// [2] send 1st pixel
	sw	t2,GPIO_OUTDR_OFF(a5)	// 0: [2] send color

	// [4] delay
	j	1f			// +2: [3]
1:	nop				// +5: [1]
	
	// [4] send 2nd pixel
	srli	t2,t2,4			// +6: [1] T2 <- load 2nd attribute
	addi	a3,a3,1			// +7: [1] increase attribute address
	sw	t2,GPIO_OUTDR_OFF(a5)	// +8: [2] send color

	// [3] delay
	j	1f			// +10: [3]

	// [6] send 3rd pixel
1:	lbu	a0,0(a3)		// +13: [2] A0 <- load 2 colors
	addi	a3,a3,1			// +15: [1] increase attribute address
	sw	a0,GPIO_OUTDR_OFF(a5)	// +16: [2] send color

	// [5] delay
	j	1f			// +18: [3]
1:	nop_rep	2			// +21: [2]

	// send 4th pixel
	srli	a0,a0,4			// +23: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +24: [2] send color

	// [3] delay
	j	1f			// +26: [3]

	// [6] send 5th pixel
1:	lbu	a0,0(a3)		// +29: [2] A0 <- load 2 colors
	addi	a3,a3,1			// +31: [1] increase attribute address
	sw	a0,GPIO_OUTDR_OFF(a5)	// +32: [2] send color

	// [5] delay
	j	1f			// +34: [3]
1:	lbu	t0,0(a2)		// +37: [2] T0 <- load sample

	// send 6th pixel
	srli	a0,a0,4			// +39: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +40: [2] send color

	// [3] delay
	j	1f			// +42: [3]

	// [6] send 7th pixel
1:	lbu	a0,0(a3)		// +45: [2] A0 <- load 2 colors
	addi	a3,a3,1			// +47: [1] increase attribute address
	sw	a0,GPIO_OUTDR_OFF(a5)	// +48: [2] send color

	// [5] delay
	nop_rep	2			// +50: [2]
	lbu	t2,0(a3)		// +52: [2] T2 <- load 2 colors
	addi	a1,a1,-1		// +54: [1] loop counter

	// send 8th pixel
	srli	a0,a0,4			// +55: [1] A0 <- load 2nd attribute
	sw	a0,GPIO_OUTDR_OFF(a5)	// +56: [2] send color

	// [4,2] loop counter
	bnez	a1,2b			// +58: [1,3]
					// +59 (pass), +61 (loop):
	// send black color
	sw	x0,SPI_DATAR_OFF(a4)	// +59: [2] send black sample to SPI
	nop_rep	2			// +61: [2]
	sw	x0,GPIO_OUTDR_OFF(a5)	// +63: [2] send black color

// Registers:
//  A2 = pointer to graphics buffer
//  T0 = current line
//  T1 = return address

	// restore T0
	lw	t0,0(sp)		// [2]
	addi	sp,sp,4			// [1]

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a1,3			// to compare
	and	a0,t0,a1		// get lowest 2 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer
	la	a4,AttrBufAddr
	sw	a3,0(a4)		// save new pointer
1:	j	TIM2_IRQHandler4	// increase scanline

.endm

#endif // VMODE == 9

// ============================================================================
//                   Timer handler - draw VGA graphics line
// ============================================================================

// Hardware prologie/epilogue HPE (2 levels):
//  Interrupt saves working registers: x1 (ra), x5-x7 (t0-t2), x10-x15 (a0-a5)

	.align  4,,
.global TIM2_IRQHandler
TIM2_IRQHandler:

	// save return address -> T1
	mv	t1,ra

	// clear update interrupt flag
	li	t2,TIM2_BASE
	lw	a1,TIM_INTFR_OFF(t2)	// get INTFR register
	andi	a1,a1,~(1<<1)
	sw	a1,TIM_INTFR_OFF(t2)

// Registers:
//  T1 = return address
//  T2 = TIM

	// time synchronization
	//  The exact interruption time may vary within a range of 1-7 processor clock
	//  cycles due to the varying length of instructions in the main program.
	lw	a0,TIM_CNT_OFF(t2)	// [2] load timer counter
					// [1] wait

// ==========
//  If you change Timer 2 channel 1 compare value, setup this
//  correction (select 0 to 7 to minimise display noise)

#if VMODE == 1
	addi	a0,a0,5			// [1] time correction: select 0 to 7
#elif VMODE == 2
	addi	a0,a0,5			// [1] time correction: select 0 to 7
#elif VMODE == 3
	addi	a0,a0,5			// [1] time correction: select 0 to 7
#elif VMODE == 4
	addi	a0,a0,7			// [1] time correction: select 0 to 7
#elif VMODE == 5
	addi	a0,a0,7			// [1] time correction: select 0 to 7
#elif VMODE == 6
	addi	a0,a0,5			// [1] time correction: select 0 to 7
#elif VMODE == 7
	addi	a0,a0,5			// [1] time correction: select 0 to 7
#elif VMODE == 8
	addi	a0,a0,5			// [1] time correction: select 0 to 7
#elif VMODE == 9
	addi	a0,a0,5			// [1] time correction: select 0 to 7
#endif

// ==========

	andi	a1,a0,7			// [2]
	slli	a1,a1,1			// [1]
	la	a2,TIM2_IRQHandler_sync // [2]
	add	a1,a1,a2		// [1]
	
	.align  2,,
	jr	a1			// [2]
	.align	2,,

TIM2_IRQHandler_sync:
	nop_rep	7			// 0..6: +7..+1 clk

	// load current line -> T0
	la	t0,DispLine
	lw	t0,0(t0)

// Registers:
//  T0 = current line
//  T1 = return address
//  T2 = TIM

	// check active image
#if VMODE == 9
	li	a1,320
#elif (VMODE == 4) || (VMODE == 5)
	li	a1,384
#else
	li	a1,480
#endif
	bge	t0,a1,TIM2_IRQHandler2 // not active image

// ==== active image

	// load pointer to graphics buffer -> A2
	la	a2,FrameBufAddr
	lw	a2,0(a2)

#if VMODE != 5
	// load pointer to attribute buffer
	la	a3,AttrBufAddr
	lw	a3,0(a3)
#endif

	// pointer to SPI1 base -> A4
	li	a4,SPI1_BASE

	// pointer to GPIOB base -> A5
	li	a5,GPIOB_BASE

// Registers:
//  A0 = temporary with sample
//  A1 = temporary with attribute
//  A2 = pointer to graphics buffer
//  A3 = pointer to attribute buffer
//  A4 = SPI
//  A5 = PORTB
//  T0 = current line
//  T1 = return address
//  T2 = TIM

	// draw VGA line (continue to TIM2_IRQHandler4)
	vga_draw

// ==== VSYNC

	.align  2,,

TIM2_IRQHandler2:

	// check front porch
#if VMODE == 9
	li	a1,320+64+10
#elif (VMODE == 4) || (VMODE == 5)
	li	a1,384+48+10
#else
	li	a1,480+10
#endif
	blt	t0,a1,TIM2_IRQHandler4	// front porch - black line

	// VSYNC
	li	a5,GPIOC_BASE		// A5 <- port C
	li	a0,1<<1			// pin 1 of port C
#if VMODE == 9
	li	a1,320+64+10+2 - 1
#elif (VMODE == 4) || (VMODE == 5)
	li	a1,384+48+10+2 - 1
#else
	li	a1,480+10+2 - 1
#endif
	bgt	t0,a1,TIM2_IRQHandler3	// not VSYNC

	// start VSYNC pulse (0 to PC1)
	sw	a0,GPIO_BCR_OFF(a5)	// send 0 to PC1
	bne	t0,a1,TIM2_IRQHandler5	// skip if not last line of VSYNC

// ==== Buttons

#if USE_KEY		// 1=use keyboard support

// Registers:
//  T0 = current line
//  T1 = return address

	// prepare to scan buttons (decreasing from 6 to 1)
	la	a1,ButKeyTab		// A1 <- pointer to button table
	li	a2,8			// A2 <- button index
	la	a3,KeyReleaseCnt+7	// A3 <- pointer to key release counter table + key repeat counter

	// prepare port base and pin mask
2:	lw	a4,0(a1)		// A4 <- port base
	lw	a5,4(a1)		// A5 <- pin mask

// Registers:
//  A0 =
//  A1 = pointer to button table
//  A2 = button index
//  A3 = pointer to key release counter + key repeat counter
//  A4 = ...port base
//  A5 = ...pin mask
//  T0 = current line
//  T1 = return address
//  T2 =
//  RA =

	// get input, check if button is pressed
	lw	a0,GPIO_INDR_OFF(a4)	// A0 <- get input port
	and	a0,a0,a5		// A0 <- check input pin, 0=pressed
	bnez	a0,4f			// button is not pressed

	// Button is pressed: release counter -> A0; is pressed for the first time?
	lbu	a0,0(a3)		// A0 <- get release counter
	li	a4,KEYCNT_PRESS		// A4 <- first repeat is 0.3 sec
	beqz	a0,6f			// release counter is 0, pressed for the first time

	// already pressed - count repeat counter
	lbu	a0,KEY_NUM(a3)		// A0 <- get repeat counter
	addi	a0,a0,-1		// decrement repeat counter
	sb	a0,KEY_NUM(a3)		// save new repeat counter
	bnez	a0,3f			// no repeat
	li	a4,KEYCNT_REPEAT	// A4 <- repeat is 0.1 sec

// Registers:
//  A0 = ...new write offset
//  A1 = pointer to button table
//  A2 = button index
//  A3 = pointer to key release counter + key repeat counter
//  A4 = ...repeat counter
//  A5 =
//  T0 = current line
//  T1 = return address
//  T2 = ...current write offset
//  RA = ...current read offset

	// set repeat counter to "first repeat"
6:	sb	a4,KEY_NUM(a3)		// setup repeat counter

	// Button is pressed for the first time: send button to keyboard buffer
7:	la	t2,KeyWriteOff		// T2 <- keyboard buffer write offset
	lbu	t2,0(t2)		// T2 <- get the write offset to keyboard buffer
	addi	a0,t2,1			// A0 <- shift write address
	li	ra,KEYBUF_SIZE		// RA <- max. buffer size
	bne	a0,ra,1f		// not end of the buffer
	li	a0,0			// A0 <- reset offset to the start of the buffer

1:	la	ra,KeyReadOff		// RA <- keyboard buffer read offset
	lbu	ra,0(ra)		// RA <- get read offset from keyboard buffer
	beq	a0,ra,3f		// skip if buffer is full

	la	ra,KeyBuf		// RA <- keyboard buffer
	add	t2,t2,ra		// T2 <- write pointer to keyboard buffer
	sb	a2,0(t2)		// save button to keyboard buffer

	la	t2,KeyWriteOff		// T2 <- keyboard buffer write offset
	sb	a0,0(t2)		// save new write offset

	// initialize press counter (update interval = 1/60 = 17ms, release time = 50 ms = 3 steps)
3:	li	a0,KEYCNT_REL		// release interval = (4-1)*17 = 50ms
	sb	a0,0(a3)		// save new release counter

	// Button is not pressed: decrease release counter
4:	lbu	a0,0(a3)		// A0 <- get release counter
	beqz	a0,5f			// counter is already 0
	addi	a0,a0,-1		// decrease counter
	sb	a0,0(a3)		// save new release counter

// Registers:
//  A0 =
//  A1 = pointer to button table
//  A2 = button index
//  A3 = pointer to key release counter + key repeat counter
//  A4 =
//  A5 =
//  T0 = current line
//  T1 = return address
//  T2 =
//  RA =

	// shift to next button
5:	addi	a1,a1,8			// shift table pointer
	addi	a2,a2,-1		// shift button index
	addi	a3,a3,-1		// shift key release counter table
	bnez	a2,2b			// next button

#endif // USE_KEY

	j	TIM2_IRQHandler4

// ==== Music

TIM2_IRQHandler5:

#if USE_SOUND		// 1=use sound support

// Registers:
//  A1 = SoundMelodyLen
//  A2 = SoundMelodyPtr
//  A3 = melody pointer
//  A4 = TIM1_BASE
//  T0 = current line
//  T1 = return address

	// get tone counter
	la	a1,SoundMelodyLen
	lh	a0,0(a1)		// A0 <- remaining length
	beqz	a0,TIM2_IRQHandler4	// no melody
	la	a2,SoundMelodyPtr
	li	a4,TIM1_BASE		// A4 <- Timer 1 base
	bgtz	a0,4f			// valid counter

// The audio output is via PA3 (pin 21), Timer 1 channel 1, mapping 5.

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
	sw	a3,TIM_CH1CVR_OFF(a4)	// save compare register

	// enable melody
	lw	a0,TIM_CCER_OFF(a4)	// load compare register
	ori	a0,a0,1<<0		// enable channel 1
	sw	a0,TIM_CCER_OFF(a4)	// save compare register
	j	TIM2_IRQHandler4

	// stop melody
8:	lw	a0,TIM_CCER_OFF(a4)	// load compare register
	andi	a0,a0,~(1<<0)		// disable channel 1
	sw	a0,TIM_CCER_OFF(a4)	// save compare register

#endif // USE_SOUND

	j	TIM2_IRQHandler4

// ==== Back porch

TIM2_IRQHandler3:

	// back porch - stop VSYNC pulse (1 to PC1)
	sw	a0,GPIO_BSHR_OFF(a5)	// send 1 to PC1

// ==== Increase scanline

TIM2_IRQHandler4:

// Registers:
//  T0 = current line
//  T1 = return address

	// inrease current scanline
	addi	t0,t0,1			// increase scanline
	li	a1,525			// total number of scanlines
	blt	t0,a1,8f		// not total line yet

	// reset to start of image
	li	t0,0			// scanline = 0

	// increase current frame
	la	a0,DispFrame
	lw	a1,0(a0)		// A1 <- current frame
	addi	a1,a1,1			// increase current frame
	sw	a1,0(a0)		// save new current frame

	// reset pointers
	la	a2,FrameBuf
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer

#if VMODE != 5
	la	a2,AttrBuf
	la	a4,AttrBufAddr
	sw	a2,0(a4)		// save new pointer
#endif

	// save new scanline
8:	la	a0,DispLine
	sw	t0,0(a0)

	// restore return address and quit
	mv	ra,t1
	mret

	.section .text
	.align  2,,

// Buttons port and pin mask
ButKeyTab:
	.word	GPIOC_BASE, 1 << 5	// 8: PC5 ... Y
	.word	GPIOC_BASE, 1 << 4	// 7: PC4 ... X
	.word	GPIOD_BASE, 1 << 2	// 6: PD2 ... B
	.word	GPIOD_BASE, 1 << 7	// 5: PD7 ... A
	.word	GPIOA_BASE, 1 << 4	// 4: PA4 ... DOWN
	.word	GPIOD_BASE, 1 << 0	// 3: PD0 ... LEFT
	.word	GPIOA_BASE, 1 << 0	// 2: PA0 ... UP
	.word	GPIOA_BASE, 1 << 5	// 1: PA5 ... RIGHT

#endif // USE_DISP
