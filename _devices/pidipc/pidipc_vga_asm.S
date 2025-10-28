
// ****************************************************************************
//
//                        PidiPC - VGA display driver
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
#define USART1_BASE		(APB2PERIPH_BASE + 0x3800)	// USART1 0x40013800

#define SPI_DATAR_OFF		0x0C		// data register offset
#define GPIO_INDR_OFF		0x08		// GPIO input register offset
#define GPIO_OUTDR_OFF		0x0C		// GPIO output register offset
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
.global AttrBuf				// (u8[]) display attribute buffer (color of 2 pixels: 1st pixels in bits 1..3, 2nd pixel in bits 5..7)
.global AttrBufAddr			// (u8*) current pointer to attribute buffer
#if VMODE == 7
.global FontBuf				// (u8[]) bont buffer 8x8
#endif
.global DispLine			// (int) current display line
.global DispFrame			// (u32) current frame
.global FrameBufAddr			// (u8*) current pointer to graphics buffer
.global DispTimTest			// test - get TIM-CNT value at start of image
.global DrawFont			// (u8*) current pointer to font
#if VMODE == 5
.global DispMaxLine			// (u32) index of last graphics scanline
#endif

#define KEY_NUM			40	// number of buttons
#define KEYBUF_SIZE		16	// size of keyboard buffer
// If you change the settings, also check this in pidipc_key.h.
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
#if VMODE == 1
#define KEY_SCANLINE_1	(256+112+10+2+1) // scanline 1: set ROW1 to 0, send CPU_CMD_ROW41
#define KEY_SCANLINE_2	(256+112+10+2+2) // scanline 2: set ROW1 to 1, receive byte 1, process byte 1 of ROW1
#define KEY_SCANLINE_3	(256+112+10+2+3) // scanline 3: set ROW2 to 0, send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW1
#define KEY_SCANLINE_4	(256+112+10+2+4) // scanline 4: set ROW2 to 1, receive byte 1, process byte 1 of ROW2
#define KEY_SCANLINE_5	(256+112+10+2+5) // scanline 5: set ROW3 to 0, send CPU_CMD_ROW40, receive byte 2, process byte 2 or ROW2
#define KEY_SCANLINE_6	(256+112+10+2+6) // scanline 6: set ROW3 to 1, receive byte 1, process byte 1 of ROW3
#define KEY_SCANLINE_7	(256+112+10+2+7) // scanline 7: send CPU_CMD_ROW41, receive byte 2, process byte 2 or ROW3
#define KEY_SCANLINE_8	(256+112+10+2+8) // scanline 8: receive byte 1, process byte 1 of ROW4
#define KEY_SCANLINE_9	(256+112+10+2+9) // scanline 9: receive byte 2, process byte 2 or ROW4
#elif (VMODE == 4) || (VMODE == 5)
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
//     1: Graphics mode 128x64 pixels mono with color attributes 1x1 pixels
// ============================================================================

#if VMODE == 1

// Registers:
//  A0..A3 =
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 416-66+1=351)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,			// -66: [1]
	// [4] send gap to SPI, to start SPI data synchronization
	sw	x0,SPI_DATAR_OFF(t1)	// -65: [2] send gap to SPI
	nop_rep	2			// -63: [2]

	// [52] delay
	li	a2,13			// -61: [1]
	.align 2,,			// -60: [1]
	// [12*4+2=50] loop		// -59: [50]
1:	addi	a2,a2,-1		// ... [1]
	bnez	a2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [2] load sample -> A0
	lbu	a0,0(a4)		// -9: [2] A0 <- load sample

	// [2] load colors -> A1
	lbu	a1,0(a5)		// -7: [2] A1 <- load 2 colors

	// [1] prepare number of samples -> A3
	li	a3,16			// -5: [1] 

	.align 2,,			// -4: [1]

// [64 loop] ... This address must be aligned

// Registers:
//  A0 = sample
//  A1 = colors
//  A2 = temporary, delay
//  A3 = loop counter
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

	// [3] send sample
2:   	sw	a0,SPI_DATAR_OFF(t1)	// (+61) -3: [2] send sample to SPI
	addi	a4,a4,1			// (+63) -1: [1] increase sample address

	// [2] send 1st pixel
	sw	a1,GPIO_OUTDR_OFF(t0)	// (+64) 0: [2] send color

	// [4] delay
	j	1f			// +2: [3]
1:	nop				// +5: [1]
	
	// [4] send 2nd pixel
	srli	a1,a1,4			// +6: [1] A1 <- load 2nd attribute
	addi	a5,a5,1			// +7: [1] increase attribute address
	sw	a1,GPIO_OUTDR_OFF(t0)	// +8: [2] send color

	// [3] delay
	j	1f			// +10: [3]

	// [5] send 3rd pixel
1:	lbu	a1,0(a5)		// +13: [2] A1 <- load 2 colors
	addi	a5,a5,1			// +15: [1] increase attribute address
	sw	a1,GPIO_OUTDR_OFF(t0)	// +16: [2] send color

	// [5] delay
	j	1f			// +18: [3]
1:	nop_rep	2			// +21: [2]

	// [3] send 4th pixel
	srli	a1,a1,4			// +23: [1] A1 <- load 2nd attribute
	sw	a1,GPIO_OUTDR_OFF(t0)	// +24: [2] send color

	// [3] delay
	j	1f			// +26: [3]

	// [5] send 5th pixel
1:	lbu	a1,0(a5)		// +29: [2] A1 <- load 2 colors
	addi	a5,a5,1			// +31: [1] increase attribute address
	sw	a1,GPIO_OUTDR_OFF(t0)	// +32: [2] send color

	// [5] delay, load sample -> A0
	j	1f			// +34: [3]
1:	lbu	a0,0(a4)		// +37: [2] A0 <- load sample

	// [3] send 6th pixel
	srli	a1,a1,4			// +39: [1] A1 <- load 2nd attribute
	sw	a1,GPIO_OUTDR_OFF(t0)	// +40: [2] send color

	// [3] delay
	j	1f			// +42: [3]

	// [5] send 7th pixel
1:	lbu	a2,0(a5)		// +45: [2] A2 <- load 2 colors
	addi	a5,a5,1			// +47: [1] increase attribute address
	sw	a2,GPIO_OUTDR_OFF(t0)	// +48: [2] send color

	// [5] delay, load next 2 colors -> A1
	nop_rep	2			// +50: [2]
	lbu	a1,0(a5)		// +52: [2] A1 <- load 2 colors
	addi	a3,a3,-1		// +54: [1] loop counter

	// [3] send 8th pixel
	srli	a2,a2,4			// +55: [1] A2 <- load 2nd attribute
	sw	a2,GPIO_OUTDR_OFF(t0)	// +56: [2] send color

	// [1,3] loop counter
	bnez	a3,2b			// +58: [1,3]
					// +59 (pass), +61 (loop):
	// send black color
	sw	x0,SPI_DATAR_OFF(t1)	// +59: [2] send black sample to SPI
	j	1f			// +61: [3]
1:	sw	x0,GPIO_OUTDR_OFF(t0)	// +64: [2] send black color

// Registers:
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T2 = current scanline
//  RA = return address

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a1,3			// to compare
	and	a0,t2,a1		// get lowest 2 bits
	bne	a0,a1,1f		// skip if not correct scanline

	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

	la	a2,AttrBufAddr
	sw	a5,0(a2)		// save new pointer

1:	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

#endif // VMODE == 1

// ============================================================================
//    2: Graphics mode 160x120 pixels mono with color attributes 4x4 pixels
// ============================================================================

#if VMODE == 2

// Registers:
//  A0..A3 =
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-66+1=223)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,			// -66: [1]
	// [2] send gap to SPI, to start SPI data synchronization
	sw	x0,SPI_DATAR_OFF(t1)	// -65: [2] send gap to SPI

	// [52] delay
	li	a2,13			// -63: [1]
	.align 2,,			// -62: [1]
	// [12*4+2=50] loop		// -61: [50]
1:	addi	a2,a2,-1		// ... [1]
	bnez	a2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [1] prepare number of samples -> A3
	li	a3,20			// -11: [1]

	.align 2,,			// -10: [1]

// [64 loop] ... This address must be aligned

// Registers:
//  A0 = sample
//  A1 = colors
//  A2 = temporary, delay
//  A3 = loop counter
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

	// [6] send sample to SPI
2:	nop				// (+55) -9: [1]
	lbu	a0,0(a4)		// (+56) -8: [2] A0 <- load sample
	addi	a4,a4,1			// (+58) -6: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(t1)	// (+59) -5: [2] send sample to SPI

	// [5] send 1st color
	lbu	a1,0(a5)		// (+61) -3: [2] A1 <- load attribute
	addi	a5,a5,1			// (+63) -1: [1] increase attribute address
	sw	a1,GPIO_OUTDR_OFF(t0)	// (+64) 0: [2] send color

	// [29] delay
	li	a2,7			// +2: [1]
	.align 2,,			// +3: [0]
	// [6*4+2=26] loop		// +3: [26]
1:	addi	a2,a2,-1		// ... [1]
	bnez	a2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +29: [2]

	// [3] send 2nd color
	srli	a1,a1,4			// +31: [1] A1 <- load 2nd attribute
	sw	a1,GPIO_OUTDR_OFF(t0)	// +32: [2] send color

	// [17] delay
	li	a2,4			// +34: [1]
	.align 2,,			// +35: [0]
	// [3*4+2=14] loop		// +35: [14]
1:	addi	a2,a2,-1		// ... [1]
	bnez	a2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +49: [2]

	// [4,2] loop counter
	addi	a3,a3,-1		// +51: [1]
	bnez	a3,2b			// +52: [1,3]
					// +53 (pass), +55 (loop):
	// send black color
	sw	x0,SPI_DATAR_OFF(t1)	// +53: [2] send black sample to SPI
	j	1f			// +55: [3]
1:	j	1f			// +58: [3]
1:	j	1f			// +61: [3]
1:	sw	x0,GPIO_OUTDR_OFF(t0)	// +64: [2] send black color

// Registers:
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T2 = current line
//  RA = return address

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a3,3			// to compare
	and	a0,t2,a3		// get lowest 2 bits
	bne	a0,a3,1f		// skip if not correct scanline

	la	t1,FrameBufAddr
	sw	a4,0(t1)		// save new pointer

	// save new attribute pointer only every 16th scanline (divide line by 4*4=16)
1:	li	a3,0x0f			// to compare
	and	a0,t2,a3		// get lowest 4 bits
	bne	a0,a3,1f		// skip if not correct scanline

	la	t1,AttrBufAddr
	sw	a5,0(t1)		// save new pointer

1:	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

#endif // VMODE == 2

// ============================================================================
//    3: Graphics mode 160x120 pixels mono with color attributes 2x2 pixels
// ============================================================================

#if VMODE == 3

// Registers:
//  A0..A3 =
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-66+1=223)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,			// -66: [1]
	// [2] send gap to SPI, to start SPI data synchronization
	sw	x0,SPI_DATAR_OFF(t1)	// -65: [2] send gap to SPI

	// [52] delay
	li	a3,13			// -63: [1]
	.align 2,,			// -62: [1]
	// [12*4+2=50] loop		// -61: [50]
1:	addi	a3,a3,-1		// ... [1]
	bnez	a3,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [1] prepare number of samples -> A3
	li	a3,20			// -11: [1]

	.align 2,,			// -10: [1]

// [64 loop] ... This address must be aligned

// Registers:
//  A0 = sample
//  A1 = colors
//  A2 = temporary, delay
//  A3 = loop counter
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

	// [6] send sample to SPI
2:	nop				// (+55) -9: [1]
	lbu	a0,0(a4)		// (+56) -8: [2] A0 <- load sample
	addi	a4,a4,1			// (+58) -6: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(t1)	// (+59) -5: [2] send sample to SPI

	// [5] send 1st color
	lbu	a1,0(a5)		// (+61) -3: [2] A1 <- load attribute
	addi	a5,a5,1			// (+63) -1: [1] increase attribute address
	sw	a1,GPIO_OUTDR_OFF(t0)	// (+64) 0: [2] send color

	// [13] delay
	li	a2,3			// +2: [1]
	.align 2,,			// +3: [0]
	// [2*4+2=10] loop		// +3: [10]
1:	addi	a2,a2,-1		// ... [1]
	bnez	a2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +13: [2]

	// [3] send 2nd color
	srli	a1,a1,4			// +15: [1] A1 <- load 2nd attribute
	sw	a1,GPIO_OUTDR_OFF(t0)	// +16: [2] send color

	// [11] delay
	li	a2,3			// +18: [1]
	.align 2,,			// +19: [0]
	// [2*4+2=10] loop		// +19: [10]
1:	addi	a2,a2,-1		// ... [1]
	bnez	a2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [5] send 3rd color
	lbu	a1,0(a5)		// +29: [2] A1 <- load attribute
	addi	a5,a5,1			// +31: [1] increase attribute address
	sw	a1,GPIO_OUTDR_OFF(t0)	// +32: [2] send color

	// [13] delay
	li	a2,3			// +34: [1]
	.align 2,,			// +35: [1]
	// [2*4+2=10] loop		// +36: [10]
1:	addi	a2,a2,-1		// ... [1]
	bnez	a2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop				// +46: [1]

	// [4] send 4th color
	srli	a1,a1,4			// +47: [1] A1 <- load 2nd attribute
	sw	a1,GPIO_OUTDR_OFF(t0)	// +48: [2] send color
	nop				// +50: [1]

	// [4,2] loop counter
	addi	a3,a3,-1		// +51: [1]
	bnez	a3,2b			// +52: [1,3]
					// +53 (pass), +55 (loop):
	// send black color
	sw	x0,SPI_DATAR_OFF(t1)	// +53: [2] send black sample to SPI
	j	1f			// +55: [3]
1:	j	1f			// +58: [3]
1:	j	1f			// +61: [3]
1:	sw	x0,GPIO_OUTDR_OFF(t0)	// +64: [2] send black color

// Registers:
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T2 = current line
//  RA = return address

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a3,3			// to compare
	and	a0,t2,a3		// get lowest 2 bits
	bne	a0,a3,1f		// skip if not correct scanline

	la	t1,FrameBufAddr
	sw	a4,0(t1)		// save new pointer

	// save new attribute pointer only every 8th scanline (divide line by 2*4=8)
1:	li	a3,0x07			// to compare
	and	a0,t2,a3		// get lowest 3 bits
	bne	a0,a3,1f		// skip if not correct scanline

	la	t1,AttrBufAddr
	sw	a5,0(t1)		// save new pointer

1:	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

#endif // VMODE == 3

// ============================================================================
//     4: Graphics mode 256x192 pixels mono with color attributes 8x8 pixels
// ============================================================================

#if VMODE == 4

// Registers:
//  A0..A3 =
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 416-35+1=382)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,			// -35: [1]
	// [3] send gap to SPI, to start SPI data synchronization
	nop				// -34: [1]
	sw	x0,SPI_DATAR_OFF(t1)	// -33: [2] send gap to SPI

	// [21] delay
	li	a3,5			// -31: [1]
	.align 2,,			// -30: [0]
	// [4*4+2=18] loop		// -30: [18]
1:	addi	a3,a3,-1		// ... [1]
	bnez	a3,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// -12: [2]

	// [1] prepare number of samples/2 -> A3
	li	a3,16			// -10: [1]

	.align 2,,			// -9: [1]

// [64 loop] send 2 samples ... This address must be aligned

// Registers:
//  A0 = sample
//  A1 = colors
//  A2 = temporary, delay
//  A3 = loop counter
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

	// [5] send 1st sample to SPI
2:	lbu	a0,0(a4)		// (+24) -8: [2] A0 <- load sample
	addi	a4,a4,1			// (+26) -6: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(t1)	// (+27) -5: [2] send sample to SPI

	// [5] send 1st color
	lbu	a1,0(a5)		// (+29) -3: [2] A1 <- load attribute
	li	a2,6			// (+31) -1: [1] loop counter
	sw	a1,GPIO_OUTDR_OFF(t0)	// (+32) 0: [2] send color

	// [22] delay
	.align 2,,			// +2: [0]
	// [5*4+2=22] loop		// +2: [22]
1:	addi	a2,a2,-1		// ... [1]
	bnez	a2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [5] send 2nd sample to SPI
	lbu	a0,0(a4)		// +24: [2] A0 <- load sample
	addi	a4,a4,1			// +26: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(t1)	// +27: [2] send sample to SPI

	// [5] send 2nd color
	nop_rep	2			// +29: [2]
	srli	a1,a1,4			// +31: [1] A1 <- load 2nd attribute
	sw	a1,GPIO_OUTDR_OFF(t0)	//  0: [2] send color

	// [17] delay
	li	a2,4			// +2: [1]
	.align 2,,			// +3: [0]
	// [3*4+2=14] loop		// +3: [14]
1:	addi	a2,a2,-1		// ... [1]
	bnez	a2,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	nop_rep	2			// +17: [2]

	// [1] increase attribute address
	addi	a5,a5,1			// +19: [1] increase attribute address

	// [4,2] loop counter
	addi	a3,a3,-1		// +20: [1]
	bnez	a3,2b			// +21: [1,3]
					// +22 (pass), +24 (loop):

	// send black color
	sw	x0,SPI_DATAR_OFF(t1)	// +22: [2] send black sample to SPI
	j	1f			// +24: [3]
1:	j	1f			// +27: [3]
1:	nop_rep	2			// +30: [2]
	sw	x0,GPIO_OUTDR_OFF(t0)	// +32: [2] send black color

// Registers:
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T2 = current line
//  RA = return address

	// save new sample pointer only every 2nd scanline (divide line by 2)
	li	a3,1			// to compare
	and	a0,t2,a3		// get lowest 1 bit
	bne	a0,a3,1f		// skip if not correct scanline

	la	t1,FrameBufAddr
	sw	a4,0(t1)		// save new pointer

	// save new attribute pointer only every 16th scanline (divide line by 8*2=16)
1:	li	a3,0x0f			// to compare
	and	a0,t2,a3		// get lowest 4 bits
	bne	a0,a3,1f		// skip if not correct scanline

	la	t1,AttrBufAddr
	sw	a5,0(t1)		// save new pointer

1:	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

#endif // VMODE == 4

// ============================================================================
// 5: text mode 32x24 characters of 8x8 pixels with ZX-80/ZX-81 font of 64 characters in Flash, with color attributes
// ============================================================================

#if VMODE == 5

// Registers:
//  A0..A3 =
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 416-41+1=376)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,			// -41: [1]
	// prepare pointer to font -> A1
	la	a2,DrawFont		// -40: [2] address of pointer
	lw	a2,0(a2)		// -38: [2] A1 <- get pointer to font

	// shift font to current font line -> A1
	andi	a0,t2,0x0e		// -36: [2] A0 <- lowest 3 bits of the line (bit 0 is ignored, 2 scanlines per 1 graphics line)
	slli	a0,a0,5			// -34: [1] A0 <- offset in the font (64 bytes per line)
	add	a2,a2,a0		// -33: [1] A1 <- shift pointer to current line of the font

	// [2] send gap to SPI, to start SPI data synchronization
	nop				// -32: [1]
	sw	x0,SPI_DATAR_OFF(t1)	// -31: [2] send gap to SPI

	// [3] save T2
	addi	sp,sp,-4		// -29: [1]
	sw	t2,0(sp)		// -28: [2]

	// prepare number of samples/2 -> A3
	li	a3,16			// -26: [1]

	.align	2,,			// -25: [1]

// [64 loop] send 2 samples ... This address must be aligned

// Registers:
//  A0 = sample
//  A1 = colors
//  A2 = pointer to font
//  A3 = loop counter
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = inversion word
//  RA = return address

	// [3] load color -> A1
2:	lbu	a1,0(a5)		// (+7) -25: [2] A1 <- load attribute
	addi	a5,a5,1			// (+9) -23: [1] increase attribute address

	// [3] load next character -> A0
	lbu	a0,0(a4)		// (+10) -22: [2] A0 <- load text character
	addi	a4,a4,1			// (+12) -20: [1] increase sample address

	// [3] prepare inversion word -> T2
	slli	t2,a1,7-2		// (+13) -19: [1] T2 <- shift attribute bit 2 to position 7
	xor	t2,t2,a0		// (+14) -18: [1] T2 (bit 7) <- bit 7 of character XOR bit 2 of color (inversion flag)
	slli	t2,t2,31-7		// (+15) -17: [1] T2 <- shift bit 7 to position 21

	// [8] load font sample -> A0
	andi	a0,a0,0x3f		// (+16) -16: [1] A0 <- character index
	add	a0,a0,a2		// (+17) -15: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// (+18) -14: [4] A0 <- load font sample
	srai	t2,t2,31		// (+22) -10: [1] T2 <- -1 if inversion, 0 if not
	xor	a0,a0,t2		// (+23) -9: [1] A0 <- invert sample by T2

	// [5] send sample
	j	1f			// (+24) -8: [3] delay
1:	sw	a0,SPI_DATAR_OFF(t1)	// (+27) -5: [2] send sample to SPI

	// [5] send color
	j	1f			// (+29) -3: [3] delay
1:	sw	a1,GPIO_OUTDR_OFF(t0)	// (+32) 0: [2] send color

	// [1] load color -> A1
	srli	a1,a1,4			// +2: [1]

	// [3] load next character -> A0
	lbu	a0,0(a4)		// +3: [2] A0 <- load text character
	addi	a4,a4,1			// +5: [1] increase sample address

	// [3] prepare inversion word -> T2
	slli	t2,a1,7-2		// +6: [1] T2 <- shift attribute bit 2 to position 7
	xor	t2,t2,a0		// +7: [1] T2 (bit 7) <- bit 7 of character XOR bit 2 of color (inversion flag)
	slli	t2,t2,31-7		// +8: [1] T2 <- shift bit 7 to position 21

	// [8] load font sample -> A0
	andi	a0,a0,0x3f		// +9: [1] A0 <- character index
	add	a0,a0,a2		// +10: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// +11: [4] A0 <- load font sample
	srai	t2,t2,31		// +15: [1] T2 <- -1 if inversion, 0 if not
	xor	a0,a0,t2		// +16: [1] A0 <- invert sample by T2

	// [5] delay
	j	1f			// +17: [3]
1:	nop_rep	2			// +20: [2]

	// [6] send sample
	j	1f			// +22: [4]
1:	sw	a0,SPI_DATAR_OFF(t1)	// +26: [2] send sample to SPI

	// [6] send color
	j	1f			// +28: [4]
1:	sw	a1,GPIO_OUTDR_OFF(t0)	// +32: [2] send color

	// [1] delay
	nop				// +2: [1]

	// [2,4] loop counter
	addi	a3,a3,-1		// +3: [1] decrease loop counter
	bnez	a3,2b			// +4: [1,3] 
					// +5 (pass), +7 (loop):

	// [22] delay
	li	a1,5			// +7: [1]
	.align 2,,			// +8: [0]
	// [4*4+2=18] loop		// +8: [18]
1:	addi	a1,a1,-1		// ... [1]
	bnez	a1,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop
	j	1f			// +26: [4]

	// send black color
1:	sw	x0,SPI_DATAR_OFF(t1)	// send black sample to SPI
	nop_rep	2
	sw	x0,GPIO_OUTDR_OFF(t0)	// send black color

	// restore T2
	lw	t2,0(sp)
	addi	sp,sp,4

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a3,0x0f			// to compare
	and	a0,t2,a3		// get lowest 4 bits
	bne	a0,a3,1f		// skip if not correct scanline

	la	t1,FrameBufAddr
	sw	a4,0(t1)		// save new pointer

	la	t1,AttrBufAddr
	sw	a5,0(t1)		// save new pointer

1:	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

#endif // VMODE == 5

// ============================================================================
//       6: Text mode 40x30 characters of 8x8 pixels, font in Flash
// ============================================================================

#if VMODE == 6

// Registers:
//  A0..A3 =
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-44+1=245)
//	li	a0,TIM2_BASE		// [1] A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,			// -44: [1]
	// prepare pointer to font -> A2
	la	a2,DrawFont		// -43: [2] address of pointer
	lw	a2,0(a2)		// -41: [2] get pointer to font

	// shift font to current font line -> A2
	andi	a0,t2,0x0e		// -39: [2] A0 <- lowest 3 bits of the line * 2 (ignore bit 0, we use 2 scanlines per 1 graphics line)
	slli	a0,a0,7			// -37: [1] A0 <- offset of the line (1 line = 256 bytes)
	add	a2,a2,a0		// -36: [1] A2 <- shift pointer to current line of the font

	// [4] send gap to SPI, to start SPI data synchronization
	li	a3,4			// -35: [1]
	nop				// -34: [1]
	sw	x0,SPI_DATAR_OFF(t1)	// -33: [2] send gap to SPI

	// [15] delay
	.align 2,,			// -31: [1]
	// [3*4+2=14] loop		// -30: [14]
1:	addi	a3,a3,-1		// ... [1]
	bnez	a3,1b			// ... [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [1] prepare number of samples/2 -> A3
	li	a3,20			// -16: [1]

	.align 2,,			// -15: [1]

// [64 loop] send 2 samples ... This address must be aligned

// Registers:
//  A0 = sample
//  A1 = colors
//  A2 = pointer to font
//  A3 = loop counter
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

	// [11] load next character, load font sample and send sample to SPI
2:	lbu	a0,0(a4)		// (+50) -14: [2] A0 <- load text character
	addi	a4,a4,1			// (+52) -12: [1] increase sample address
	add	a0,a0,a2		// (+53) -11: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// (+54) -10: [4] A0 <- load font sample
	nop				// (+58) -6: [1] ... wait to load
	sw	a0,SPI_DATAR_OFF(t1)	// (+59) -5: [2] send sample to SPI

	// [5] send color
	lbu	a1,0(a5)		// (+61) -3: [2] A1 <- load attribute
	nop				// (+63) -1: [1] ... wait to load
	sw	a1,GPIO_OUTDR_OFF(t0)	// (+64) 0: [2] send color

	// [15] delay
	j	1f			// 2: [3]
1:	j	1f			// 5: [3]
1:	j	1f			// 8: [3]
1:	j	1f			// 11: [3]
1:	j	1f			// 14: [3]

	// [11] load next character, load font sample and send sample to SPI
1:	lbu	a0,0(a4)		// +17: [2] A0 <- load text character
	addi	a4,a4,1			// +19: [1] increase sample address
	add	a0,a0,a2		// +20: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// +21: [4] A0 <- load font sample
	nop				// +25: [1] ... wait to load
	sw	a0,SPI_DATAR_OFF(t1)	// +26: [2] send sample to SPI

	// [6] send color
	j	1f			// +28: [3]
1:	srli	a1,a1,4			// +31: [1] A1 <- load 2nd attribute
	sw	a1,GPIO_OUTDR_OFF(t0)	// +32: [2] send color

	// [11] delay
	j	1f			// +34: [3]
1:	j	1f			// +37: [3]
1:	j	1f			// +40: [3]
1:	nop_rep	2			// +43: [2]

	// [1] increase attribute address
	addi	a5,a5,1			// +45: [1] increase attribute address

	// [4,2] loop counter
	addi	a3,a3,-1		// +46: [1]
	bnez	a3,2b			// +47: [1,3]
					// +48 (pass), +50 (loop):
	// send black color
	sw	x0,SPI_DATAR_OFF(t1)	// +48: [2] send black sample to SPI

	j	1f			// +50: [3]
1:	j	1f			// +53: [3]
1:	j	1f			// +56: [3]
1:	j	1f			// +59: [3]
1:	nop_rep	2			// +62: [2]

	sw	x0,GPIO_OUTDR_OFF(t0)	// +64: [2] send black color

// Registers:
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T2 = current line
//  RA = return address

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a3,0x0f			// to compare
	and	a0,t2,a3		// get lowest 4 bits
	bne	a0,a3,1f		// skip if not correct scanline

	la	t1,FrameBufAddr
	sw	a4,0(t1)		// save new pointer

	la	t1,AttrBufAddr
	sw	a5,0(t1)		// save new pointer

1:	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

#endif // VMODE == 6

// ============================================================================
//       7: Text mode 80x30 characters of 8x8 pixels, font in RAM
// ============================================================================

#if VMODE == 7

// Registers:
//  A0..A3 =
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 288-25+1=264)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

	.align 2,,			// -25: [1]
	// prepare pointer to font -> A2
	la	a2,FontBuf		// -24: [2]

	// shift font to current font line -> A2
	andi	a0,t2,0x0e		// -22: [2] A0 <- lowest 3 bits of the line * 2 (ignore bit 0, we use 2 scanlines per 1 graphics line)
	slli	a0,a0,7			// -20: [1] A0 <- offset of the line (1 line = 256 bytes)
	add	a2,a2,a0		// -19: [1] A2 <- shift pointer to current line of the font
	nop				// -18: [1]
	
	// [2] send gap to SPI, to start SPI data synchronization
	sw	x0,SPI_DATAR_OFF(t1)	// -17: [2] send gap to SPI

	// [2] delay
	nop_rep	2			// -15: [2]

	// [1] prepare number of samples/2 -> A3
	li	a3,40			// -13: [1]

	.align 2,,			// -12: [1]

// [32 loop] send 2 samples ... This address must be aligned

// Registers:
//  A0 = sample
//  A1 = colors
//  A2 = pointer to font
//  A3 = loop counter
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

	// [10] load next character, load font sample and send sample to SPI
2:	lbu	a0,0(a4)		// (+21) -11: [2] A0 <- load text character
	addi	a4,a4,1			// (+23) -9: [1] increase sample address
	add	a0,a0,a2		// (+24) -8: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// (+25) -7: [2] A0 <- load font sample
	lbu	a1,0(a5)		// (+27) -5: [2] A1 <- load attribute
	sw	a0,SPI_DATAR_OFF(t1)	// (+29) -3: [2] send sample to SPI

	// [3] send color
	addi	a5,a5,1			// (+31) -1: [1] increase attribute address
	sw	a1,GPIO_OUTDR_OFF(t0)	// (+32) 0: [2] send color

	// [3] delay
	j	1f			// +2: [3]

	// [10] load next character, load font sample and send sample to SPI
1:	lbu	a0,0(a4)		// +5: [2] A0 <- load text character
	addi	a4,a4,1			// +7: [1] increase sample address
	add	a0,a0,a2		// +8: [1] A0 <- address of the sample in the font
	lbu	a0,0(a0)		// +9: [2] A0 <- load font sample
	nop				// +11: [1] ... wait to load
	addi	a3,a3,-1		// +12: [1] loop counter
	sw	a0,SPI_DATAR_OFF(t1)	// +13: [2] send sample to SPI

	// [3] send color
	srli	a1,a1,4			// +15: [1] A1 <- load 2nd attribute
	sw	a1,GPIO_OUTDR_OFF(t0)	// +16: [2] send color

	// [3,1] loop counter
	bnez	a3,2b			// +18: [1,3]
					// +19 (pass), +21 (loop):

	// send black color
	sw	x0,SPI_DATAR_OFF(t1)	// +19: [2] send black sample to SPI

	j	1f			// +21: [3]
1:	j	1f			// +24: [3]
1:	j	1f			// +27: [3]
1:	nop_rep	2			// +30: [2]

	sw	x0,GPIO_OUTDR_OFF(t0)	// +32: [2] send black color

// Registers:
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T2 = current line
//  RA = return address

	// save new sample pointer only every 16th scanline (divide line by 2)
	li	a3,0x0f			// to compare
	and	a0,t2,a3		// get lowest 4 bits
	bne	a0,a3,1f		// skip if not correct scanline

	la	t1,FrameBufAddr
	sw	a4,0(t1)		// save new pointer

	la	t1,AttrBufAddr
	sw	a5,0(t1)		// save new pointer

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

	// clear compare interrupt flag (Timer 2, channel 3)
	li	t2,TIM2_BASE		// T2 <- Timer 2 base
	lw	a1,TIM_INTFR_OFF(t2)	// A1 <- get INTFR register
	lw	a0,TIM_CNT_OFF(t2)	// A0 <- load timer counter
	andi	a1,a1,~(1<<3)		// clear interrupt flag
	sw	a1,TIM_INTFR_OFF(t2)	// set INTFR register

// ==== Time synchronization
// Registers:
//  A0 = Timer 2 counter value
//  A1-A5,T0-T2 =
//  RA = return address

	//  The exact interruption time may vary within a range of 1-10 processor clock
	//  cycles due to the varying length of instructions in the main program.

	// >>>>>>>> SETUP
	//  If you change Timer 2 channel 3 compare value, setup this
	//  correction - select 0 to 15 to minimise display noise.
#ifdef VMODE_SHIFT	// custom shift VMODE time correction
	addi	a0,a0,VMODE_SHIFT	// time correction: select 0 to 15
#else

#if VMODE == 1
	addi	a0,a0,2			// time correction: select 0 to 15
#elif VMODE == 2
	addi	a0,a0,2			// time correction: select 0 to 15
#elif VMODE == 3
	addi	a0,a0,2			// time correction: select 0 to 15
#elif VMODE == 4
	addi	a0,a0,0			// time correction: select 0 to 15
#elif VMODE == 5
	addi	a0,a0,6			// time correction: select 0 to 15
#elif VMODE == 6
	addi	a0,a0,4 		// time correction: select 0 to 15
#elif VMODE == 7
	addi	a0,a0,1			// time correction: select 0 to 15
#endif

#endif
	// <<<<<<<<
	andi	a0,a0,0x0f 		// mask lower 4 bits of the timer counter
	slli	a0,a0,1			// timer * 2 (because jump to NOPs is multiply of 2 bytes)
	la	a2,TIM2_IRQHandler_sync // table of 15x NOP instruction
	add	a0,a0,a2		// A0 <- jump address
	
	.align  2,,
	jr	a0			// jump to NOP and delay additional 'x' clock cycles
	.align	2,,

TIM2_IRQHandler_sync:
	nop_rep	15			// 0..14: +15..+1 clk

// ==== Get current scanline

	// load current line -> T2
	la	a0,DispLine
	lw	t2,0(a0)

// Registers:
//  A0-A5, T0-T1 =
//  T2 = current scanline
//  RA = return address

	// check active image
#if VMODE == 1
	li	a0,256
#elif VMODE == 4
	li	a0,384
#elif VMODE == 5
	la	a0,DispMaxLine
	lw	a0,0(a0)		// default 384
#else
	li	a0,480
#endif
	bge	t2,a0,TIM2_IRQHandler2 // not active image

// ==== active image

	// load pointer to graphics buffer -> A4
	la	a4,FrameBufAddr
	lw	a4,0(a4)

	// load pointer to attribute buffer -> A5
	la	a5,AttrBufAddr
	lw	a5,0(a5)

	// pointer to SPI1 base -> T1
	li	t1,SPI1_BASE

	// pointer to GPIOB base -> T0
	li	t0,GPIOB_BASE

// Registers:
//  A0..A3 =
//  A4 = pointer to graphics buffer
//  A5 = pointer to attribute buffer
//  T0 = PORTB
//  T1 = SPI1 base
//  T2 = current scanline
//  RA = return address

	// draw VGA line (continue to TIM2_IRQHandler4)
	vga_draw

// ==== VSYNC

	.align  2,,

TIM2_IRQHandler2:

	// jump from fast RAM to slow Flash code
	la	a0,TIM2_IRQHandler2B
	jr	a0
	.section .text
TIM2_IRQHandler2B:

	// check front porch
#if VMODE == 1
	li	a1,256+112+10
#elif (VMODE == 4) || (VMODE == 5)
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

#if VMODE == 1
	li	a1,256+112+10+2 - 1	// A1 <- index of last VSYNC scanline
#elif (VMODE == 4) || (VMODE == 5)
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
	sw	a3,TIM_CH4CVR_OFF(a4)	// save compare register

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

	// set ROW1 (PD3) to 0
	li	a3,GPIOD_BASE		// A3 <- port D
	li	a1,1<<3			// A1 <- PD3 pin
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

	// set ROW1 (PD3) to 1
	li	a3,GPIOD_BASE		// A3 <- port D
	li	a1,1<<3			// A1 <- PD3 pin
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

	// set ROW2 (PD4) to 0
	li	a3,GPIOD_BASE		// A3 <- port D
	li	a1,1<<4			// A1 <- PD4 pin
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

	// set ROW2 (PD4) to 1
	li	a3,GPIOD_BASE		// A3 <- port D
	li	a1,1<<4			// A1 <- PD4 pin
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

// ==== Increase scanline
// Registers:
//  A0-A5, T0-T1 =
//  T2 = current scanline
//  RA = return address

TIM2_IRQHandler4:

	// inrease current scanline
	addi	t2,t2,1			// T2 <- increase scanline
	li	a2,525			// A2 <- total number of scanlines
	blt	t2,a2,8f		// not total line yet

	// reset to start of image
	li	t2,0			// T2 <- scanline = 0

	// increase current frame
	la	a0,DispFrame		// A0 <- current frame
	lw	a1,0(a0)		// A1 <- get current frame
	addi	a1,a1,1			// increase current frame
	sw	a1,0(a0)		// save new current frame

	// reset pointers
	la	a2,FrameBuf
	la	a4,FrameBufAddr
	sw	a2,0(a4)		// save new pointer
	la	a2,AttrBuf
	la	a4,AttrBufAddr
	sw	a2,0(a4)		// save new pointer

	// save new scanline
8:	la	a0,DispLine
	sw	t2,0(a0)		// save new scanline
	mret

#endif // USE_DISP
