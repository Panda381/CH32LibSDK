
// ****************************************************************************
//
//                        BeatleBoyPad - VGA display driver
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
#define GPIOC_BASE		(APB2PERIPH_BASE + 0x1000)	// PC port 0x40011000
#define GPIOD_BASE		(APB2PERIPH_BASE + 0x1400)	// PD port 0x40011400
#define SPI1_BASE		(APB2PERIPH_BASE + 0x3000)	// SPI1 base (0x40013000)
#define TIM1_BASE		(APB2PERIPH_BASE + 0x2C00)	// TIM1 0x40012C00
#define TIM2_BASE		(APB1PERIPH_BASE + 0x0000)	// TIM2 0x40000000
#define ADC1_BASE		(APB2PERIPH_BASE + 0x2400)	// ADC1 0x40012400

#define SPI_DATAR_OFF		0x0C		// data register offset
#define GPIO_INDR_OFF		0x08		// GPIO input register offset
#define GPIO_OUTDR_OFF		0x0C		// GPIO output register offset
#define GPIO_BSHR_OFF		0x10		// GPIO bit set output data register
#define GPIO_BCR_OFF		0x14		// GPIO bit clear output data register
#define TIM_INTFR_OFF		0x10		// timer interrupt register offset
#define TIM_CCER_OFF		0x20		// timer compare register
#define TIM_CNT_OFF		0x24		// timer counter register offset
#define TIM_ATRLR_OFF		0x2C		// ATRLR timer auto-reload value register
#define TIM_CH1CVR_OFF		0x34		// CH4CVR timer compare/capture register 1
#define TIM_CH2CVR_OFF		0x38		// CH4CVR timer compare/capture register 2
#define TIM_CH3CVR_OFF		0x3C		// CH4CVR timer compare/capture register 3
#define TIM_CH4CVR_OFF		0x40		// CH4CVR timer compare/capture register 4
#define ADC_RDATAR_OFF		0x4C		// ADC data register (read ADC data)
#define ADC_RSQR3_OFF		0x34		// sequence register 3 (select ADC channel)
#define ADC_CTLR2_OFF		0x08		// control resiter 2 (write bit 22 to start conversion)

#if DISP_DBLBUF		// 1=use VGA display double buffer (FrameBuf+DispBuf)
.global DispBuf				// (u8[]) display graphics buffer
#endif
.global FrameBuf			// (u8[]) display graphics buffer
.global DispLine			// (u32) current display line
.global DispFrame			// (u32) current frame
.global FrameBufAddr			// (u8*) current pointer to graphics buffer
.global DispTimTest			// test - get TIM-CNT value at start of image
.global RunMode				// (u8) device run mode RUNMODE_* (0=OLED, 1=VGA)

.global Pad1AdcChan			// (u8) PAD1 ADC channel (OLED: 6 from PD6, VGA: 5 from PD5)
.global SupplyVoltageCnt		// (u8) counter of samples of supply voltage
.global KeyPressOld			// (u8) previous state of presseed keys
.global KeyPressMap			// (u8) currently pressed keys
.global PadCnt				// (u16) PAD measure sample counter
.global SupplyVoltageAcc		// (u32) supply voltage accumulator
.global SupplyVoltageVal		// (u32) supply voltage value (voltage in [mV] = (1200 << (12 + SUPPLYADC_SHIFT)) / SupplyVoltage)
.global Pad1Acc				// (u32) PAD1 voltage accumulator
.global Pad1Val				// (u32) PAD1 value (value size PADADC_SHIFT+12 bits)
.global Pad2Acc				// (u32) PAD2 voltage accumulator
.global Pad2Val				// (u32) PAD2 value (value size PADADC_SHIFT+12 bits)
.global PadThreshold			// (u32[7]) ADC PAD thresholds

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
//         graphics mode 128x64 pixels, required memory 1024 B
// ============================================================================

// Registers:
//  A0-A3, T0-T1 =
//  A4 = pointer to source graphics buffer
//  A5 = SPI or port A
//  T2 = current scanline
//  RA = return address
// - continue to TIM2_IRQHandler4

.macro vga_draw

	// test - get TIM-CNT value at start of image (should be 186-5=181; or CH32V003: 178-5=173)
//	li	a0,TIM2_BASE		// A0 <- Timer 2 base
//	lw	a0,TIM_CNT_OFF(a0)	// load timer counter
//	la	a1,DispTimTest
//	sw	a0,0(a1)		// save value

#if CH32V003

	// [1] prepare number of samples -> A3
	li	a3,16			// -5: [1]

	// [2] load first sample -> A0
	lbu	a0,0(a4)		// -4: [2] A0 <- load first sample

	// [1] prepare bit 7 -> T0
	srli	t0,a0,6			// -2: [1] T0 <- bit 7

	.align	2,,			// -1: [1]

// [33 loop] send sample, 4 (or 5) clock cycles per pixel ... This address must be aligned
// Whole active image takes: 15*33+32 = 527 clock cycles. Difference against 512 is 15 clock cycles.
// To center, 8 clock cycles should be shifted to the left.

// Registers:
//  A0 = sample
//  A1 = output bit
//  A2 = next sample
//  T0 = another output bit
//  T1 =
//  A3 = loop counter
//  A4 = pointer to source graphics buffer
//  A5 = pointer to PA output port (output to bit 1)
//  T2 = current scanline
//  RA = return address

	// [2] pixel 0: send bit 7
2:	sw	t0,GPIO_OUTDR_OFF(a5)	// 0*4=0: [2] send bit 7 to port A (bit 1)

	// [4] pixel 1: send bit 6
	addi	a4,a4,1			// 2: [1] A4 <- increase sample address
	srli	a1,a0,5			// 3: [1] A1 <- bit 6
	sw	a1,GPIO_OUTDR_OFF(a5)	// 1*4=4: [2] send bit 6 to port A (bit 1)

	// [4] pixel 2: send bit 5
	srli	a1,a0,4			// 6: [1] A1 <- bit 5
	srli	t0,a0,3			// 7: [1] T0 <- bit 4
	sw	a1,GPIO_OUTDR_OFF(a5)	// 2*4=8: [2] send bit 5 to port A (bit 1)

	// [4] pixel 3: send bit 4
	lbu	a2,0(a4)		// 10: [2] A2 <- load next sample
	sw	t0,GPIO_OUTDR_OFF(a5)	// 3*4=12 : [2] send bit 4 to port A (bit 1)

	// [4] pixel 4: send bit 3
	nop				// 14: [1]
	srli	a1,a0,2			// 15: [1] A1 <- bit 3
	sw	a1,GPIO_OUTDR_OFF(a5)	// 4*4=16: [2] send bit 3 to port A (bit 1)

	// [4] pixel 5: send bit 2
	addi	a3,a3,-1		// 18: [1] decrease loop counter
	srli	a1,a0,1			// 19: [1] A1 <- bit 2
	sw	a1,GPIO_OUTDR_OFF(a5)	// 5*4=20: [2] send bit 2 to port A (bit 1)

	// [4] pixel 6: send bit 1
	slli	a1,a0,1			// 22: [1] A1 <- bit 0
	srli	t0,a2,6			// 23: [1] T0 <- next bit 7
	sw	a0,GPIO_OUTDR_OFF(a5)	// 6*4=24: [2] send bit 1 to port A (bit 1)

	// [4] pixel 7: send bit 0
	nop				// 26: [1]
	mv	a0,a2			// 27: [1] A0 <- next sample
	sw	a1,GPIO_OUTDR_OFF(a5)	// 7*4=28: [2] send bit 0 to port A (bit 1)

	// [1,3] loop counter
	bnez	a3,2b			// 30: [1,3] 
					// 31 (pass), 33 (loop)

	// send black color
	nop				// 31: [1]
	sw	x0,GPIO_OUTDR_OFF(a5)	// 8*4=32: [2] send black sample port A

#else // CH32V003

	// prepare number of samples -> A3
	li	a3,16			// -5: [1]

	.align	2,,			// -4: [1]

// [32 loop] send sample ... This address must be aligned

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
2:	lbu	a0,0(a4)		// +29,-3: [2] A0 <- load sample
	addi	a4,a4,1			// +31,-1: [1] increase sample address
	sw	a0,SPI_DATAR_OFF(a5)	// +32,0: [2] send sample to SPI

	// [23] delay
	li	a2,6			// +2: [1]
	.align	2,,			// +3: [0]
	// [5*4+2=22] loop
1:	addi	a2,a2,-1		// [1]
	bnez	a2,1b			// [1 pass, 3 loop] loop ... 4 clock cycles per loop

	// [2,4] loop counter
	addi	a3,a3,-1		// +25: [1]
	bnez	a3,2b			// +26: [1,3] 
					// +27 (pass), +29 (loop)

	// send black color
	sw	x0,SPI_DATAR_OFF(a5)	// send black sample to SPI

#endif // CH32V003

	// save new sample pointer only every 4th scanline (divide line by 4)
	li	a1,3			// to compare
	and	a0,t2,a1		// get lowest 2 bits
	bne	a0,a1,1f		// skip if not correct scanline
	la	a2,FrameBufAddr
	sw	a4,0(a2)		// save new pointer

1:	la	a0,TIM2_IRQHandler4
	jr	a0

.endm

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

	// clear compare interrupt flag (Timer 2, channel 2)
	li	a2,TIM2_BASE		// A2 <- Timer 2 base
	lw	a1,TIM_INTFR_OFF(a2)	// A1 <- get INTFR register
	lw	a0,TIM_CNT_OFF(a2)	// A0 <- load timer counter
	andi	a1,a1,~0x1f		// clear CC and UP interrupt flags
	sw	a1,TIM_INTFR_OFF(a2)	// set INTFR register

	// skip VGA service
	la	a3,RunMode
	lbu	a3,0(a3)		// A3 <- run mode 0=OLED, 1=VGA
	beqz	a3,TIM2_IRQHandler1	// skip VGA service

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
#if CH32V003
	addi	a0,a0,1 // (0-3 are usable)	// time correction: select 0 to 7
#else
	addi	a0,a0,0 // (0-3 are usable)	// time correction: select 0 to 7
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
	li	a0,256
	bge	t2,a0,TIM2_IRQHandler2 // not active image

// ==== active image

	// load pointer to graphics buffer -> A4
	la	a4,FrameBufAddr
	lw	a4,0(a4)

#if CH32V003
	// pointer to PA port -> A5
	li	a5,GPIOA_BASE
#else
	// pointer to SPI1 base -> A5
	li	a5,SPI1_BASE
#endif

// Registers:
//  A0-A2, T0-T1 =
//  A3 = pointer to attribute buffer
//  A4 = pointer to source graphics buffer
//  A5 = SPI or port PA
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

TIM2_IRQHandler1:	// jump from OLED mode

	// load current scanline -> T2
	la	a1,DispLine
	lw	t2,0(a1)

// >>>>>>>> select pin which is not used <<<<<<<
	li	a0,1<<6			// A0 <- pin 6 of port C (as VSYNC, which is not used)

	la	a1,TIM2_IRQHandler2C
	jr	a1

TIM2_IRQHandler2:	// jump from VGA mode

	la	a0,TIM2_IRQHandler2B
	jr	a0
	.section .text
TIM2_IRQHandler2B:

	// VSYNC
	li	a0,1<<2			// A0 <- pin 2 of port C

TIM2_IRQHandler2C:
	li	a3,GPIOC_BASE		// A3 <- port C

	// check front porch
	li	a1,256+112+10
	blt	t2,a1,TIM2_IRQHandler4	// front porch - black line

// Registers:
//  A1-A2,A4,A5, T0-T1 =
//  A0 = mask of pin 7
//  A3 = GPIOC base
//  T2 = current scanline
//  RA = return address

	li	a1,256+112+10+2 - 1	// A1 <- index of last VSYNC scanline
	bgt	t2,a1,TIM2_IRQHandler3	// not VSYNC, serve back porch

	// start VSYNC pulse (send 0 to PC2)
	sw	a0,GPIO_BCR_OFF(a3)	// send 0 to PC2
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

// The audio output is via PC4, Timer 1, channel 4, mapping 0.

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
	li	a1,1<<(3*4)		// channel 4
	or	a0,a0,a1		// enable channel 4
	sw	a0,TIM_CCER_OFF(a4)	// save compare register
	j	TIM2_IRQHandler4

	// stop melody
8:	lw	a0,TIM_CCER_OFF(a4)	// load compare register
	li	a1,~(1<<(3*4))		// channel 4
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

	// back porch - stop VSYNC pulse (1 to PC2)
	sw	a0,GPIO_BSHR_OFF(a3)	// send 1 to PC2
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
#if DISP_DBLBUF		// 1=use VGA display double buffer (FrameBuf+DispBuf)
	la	a0,DispBuf		// A0 <- frame buffer
#else
	la	a0,FrameBuf		// A0 <- frame buffer
#endif
	la	a1,FrameBufAddr		// A1 <- frame buffer address
	sw	a0,0(a1)		// save new pointer

	// save new scanline
8:	la	a0,DispLine
	sw	t2,0(a0)		// save new scanline

#if USE_KEY		// 1=use keyboard support

// Registers:
//  A0 = ADC result
//  A1 = temporary
//  A2 =
//  A3 =
//  A4 = pointer to supply voltage counter SupplyVoltageAcc(u8)
//  A5 = current PAD sample counter PadCnt
//  T0 = pointer to accumulator or result
//  T1 = ADC1 base
//  T2 = pointer to PAD sample counter PadCnt (u16)
//  RA = return address

// ---- get counter and next sample

	// get current sample sequence counter -> A5
	la	t2,PadCnt		// T2 <- PAD sample counter
	lhu	a5,0(t2)		// A5 <- get PAD sample counter

	// read ADC result -> A0
	li	t1,ADC1_BASE		// T1 <- ADC1 base
	lw	a0,ADC_RDATAR_OFF(t1)	// A0 <- read ADC result

	// check end of sequence
	li	a1,2*PADADC_NUM		// A1 <- number of measures
	bne	a1,a5,3f		// skip if not end of sequence

// ---- serve supply measure

	// add measure to supply voltage accumulator -> A0
	la	t0,SupplyVoltageAcc	// T0 <- address of the accumulator
	lw	a1,0(t0)		// A1 <- current accumulator
	add	a0,a0,a1		// add value to the accumulator
	sw	a0,0(t0)		// save new accumulator

	// increase number of samples
	la	a4,SupplyVoltageCnt	// A4 <- address of supply voltage counter
	lbu	a1,0(a4)		// A1 <- read counter
	addi	a1,a1,1			// increase counter
	sb	a1,0(a4)		// save new counter

	// end of samples
	li	a2,SUPPLYADC_NUM	// A2 <- number of samples
	blt	a1,a2,1f		// skip if not end
	sb	zero,0(a4)		// reset sample counter
	sw	zero,0(t0)		// reset accumulator
	la	t0,SupplyVoltageVal	// T0 <- address of the value
	sw	a0,0(t0)		// save new result

// ---- start new sequence

	// restart sequence, start measure PAD1
1:	sh	zero,0(t2)		// reset PAD sample counter
2:	la	a1,Pad1AdcChan		// T2 <- pointer to PAD1 ADC channel
	lbu	a1,0(a1)		// A1 <- PAD1 ADC channel
	j	8f			// start new conversion

// ---- select PAD1 or PAD2

	// increase sample counter, check bit 0 of the counter
3:	slli	a1,a5,31		// A0 <- shift bít 0 to position 31
	addi	a5,a5,1			// A5 <- increase sample counter
	sh	a5,0(t2)		// save new sample counter
	bgez	a1,7f			// skip if counter is even = PAD1

// ---- PAD2 (odd sample counter)

	// add measure to PAD2 -> A0
	la	t0,Pad2Acc		// T0 <- address of the accumulator
	lw	a1,0(t0)		// A1 <- current accumulator
	add	a0,a0,a1		// add value to the accumulator
	sw	a0,0(t0)		// save new accumulator

	// if not end of sequence, start measure PAD1
	li	a1,2*PADADC_NUM		// A1 <- number of measures
	bne	a1,a5,2b		// start measure PAD1 if not end of sequence

// ---- end of sequence, process keys

	// reset PAD2 measure and get PAD2 results
	sw	zero,0(t0)		// reset PAD2 accumulator
	la	t0,Pad2Val		// T0 <- address of PAD2 value
	sw	a0,0(t0)		// save result PAD2 value

	// detect PAD2 keys
	li	a1,0			// A1 <- no keys
	la	t0,PadThreshold		// T0 <- threshold table, index 0
	lw	a2,3*4(t0)		// A2 <- value of start KEY1
	blt	a0,a2,1f		// not KEY1
	ori	a1,a1,1<<KEY_LEFT	// mark KEY1 = LEFT
	addi	t0,t0,4*4		// shift table to index 4

1:	lw	a2,1*4(t0)		// A2 <- value of start KEY2
	blt	a0,a2,1f		// not KEY2
	ori	a1,a1,1<<KEY_UP		// mark KEY2 = UP
	addi	t0,t0,2*4		// shift table to index 2 or 6

1:	lw	a2,0*4(t0)		// A2 <- value of start KEY3
	blt	a0,a2,1f		// not KEY3
	ori	a1,a1,1<<KEY_RIGHT	// mark KEY3 = RIGHT

	// reset PAD1 measure and get PAD1 results
1:	la	t0,Pad1Acc		// T0 <- address of PAD1 accumulator
	lw	a0,0(t0)		// A0 <- get PAD1 accumulator
	sw	zero,0(t0)		// reset PAD1 accumulator
	la	t0,Pad1Val		// T0 <- address of PAD1 value
	sw	a0,0(t0)		// save result PAD1 value

	// detect PAD1 keys
	la	t0,PadThreshold		// T0 <- threshold table, index 0
	lw	a2,3*4(t0)		// A2 <- value of start KEY1
	blt	a0,a2,1f		// not KEY1
	ori	a1,a1,1<<KEY_A		// mark KEY1 = A
	addi	t0,t0,4*4		// shift table to index 4

1:	lw	a2,1*4(t0)		// A2 <- value of start KEY2
	blt	a0,a2,1f		// not KEY2
	ori	a1,a1,1<<KEY_B		// mark KEY2 = B
	addi	t0,t0,2*4		// shift table to index 2 or 6

1:	lw	a2,0*4(t0)		// A2 <- value of start KEY3
	blt	a0,a2,1f		// not KEY3
	ori	a1,a1,1<<KEY_DOWN	// mark KEY3 = DOWN

	// validate keys
1:	la	t0,KeyPressOld
	lbu	a0,0(t0)		// A0 <- get old state
	sb	a1,0(t0)		// save new state
	bne	a0,a1,1f		// skip if state is not equal
	la	t0,KeyPressMap
	sb	a0,0(t0)		// save new state

	// start measure supply voltage
1:	li	a1,8			// A1 <- ADC reference channel
	j	8f			// start measure

// ---- PAD1 (even sample counter)

	// add measure to PAD1 -> A0
7:	la	t0,Pad1Acc		// T0 <- address of the accumulator
	lw	a1,0(t0)		// A1 <- current accumulator
	add	a0,a0,a1		// add value to the accumulator
	sw	a0,0(t0)		// save new accumulator

	// start measure PAD2
	li	a1,0			// ADC0 to get PAD2

	// start new conversion (A1 = ADC channel)
8:	sw	a1,ADC_RSQR3_OFF(t1)	// select PAD1 ADC channel
	li	a1,1<<22
	lw	a0,ADC_CTLR2_OFF(t1)	// A0 <- control register 2
	or	a0,a0,a1		// start conversion
	sw	a0,ADC_CTLR2_OFF(t1)	// set new control register 2

#endif // USE_KEY

9:
	// check time reserve (every loop is 4 clock cycles) ... reserve is about 30 clock cycles
//	li	a0,8
//1:	addi	a0,a0,-1	// [1]
//	bnez	a0,1b		// [1,3]

	mret

#endif // USE_DISP
