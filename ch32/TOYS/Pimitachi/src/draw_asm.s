
// ****************************************************************************
//
//                                 Drawing
//
// ****************************************************************************

#include "def.h"

#if USE_DRAW_ASM		// 1=use ASM in Draw module

	.section	.text

// ----------------------------------------------------------------------------
// Clear screen
// ----------------------------------------------------------------------------
// void DrawClear();

.global DrawClear
DrawClear:
	sb	zero,RAM_PRINTINV_OFF(gp) // clear PrintInv flag
	addi	a0,gp,RAM_FRAMEBUF_OFF	// A0 <- pointer to frame buffer
	li	a1,0			// A1 <- byte to clear
	li	a2,FRAMESIZE		// A2 <- size of data
	j	memset			// clear frame buffer

// ----------------------------------------------------------------------------
// Draw pixel with inverted color
// ----------------------------------------------------------------------------
// void DrawPointInv(int x, int y, int col);

.global DrawPointInv
DrawPointInv:

	// invert color: set to 1 if color is 0
	seqz	a2,a2

// continue to DrawPoint

// ----------------------------------------------------------------------------
// Draw pixel
// ----------------------------------------------------------------------------
// void DrawPoint(int x, int y, int col)

.global DrawPoint
DrawPoint:

	// check X coordinate
	li	a5,WIDTH	// max. X coordinate
	bgeu	a0,a5,9f	// exit if X is not valid

	// check Y coordinate
	li	a5,HEIGHT	// max. Y coordinate
	bgeu	a1,a5,9f	// exit if Y is not valid

	// get pointer to frame buffer -> A4
	srai	a5,a0,3		// A5 <- X >> 3, byte offset
	slli	a1,a1,4		// A1 <- Y*WIDTHBYTE = Y*16, convert Y to offset in frame buffer
	add	a5,a5,a1	// A5 <- offset in frame buffer = (X>>3) + (Y*WIDTHBYTE)
	addi	a4,gp,RAM_FRAMEBUF_OFF // A4 <- pointer to frame buffer
	add	a4,a4,a5	// A4 <- address of the byte in frame buffer

	// prepare mask of the bit -> A5
	not	a0,a0		// A0 <- ~X
	andi	a0,a0,7		// A0 <- (~X) & 7 = 7 - (X & 7)
	li	a5,1		// A5 <- 1
	sll	a5,a5,a0	// A5 <- bit mask ( = 1 << (7 - (X & 7)) )

	// set pixel
	lbu	a3,0(a4)	// A3 <- get color byte from frame buffer
	or	a3,a3,a5	// set color bit (= set white color)
	bnez	a2,1f		// skip if 'col' is not 0 (= if color is white)
	xor	a3,a3,a5	// XOR color bit (= set black color)
1:	sb	a3,0(a4)	// save color byte
9:	ret

// ----------------------------------------------------------------------------
// Draw frame
// ----------------------------------------------------------------------------
// void DrawFrame(int x, int y, int w, int h, int col)

.global DrawFrame
DrawFrame:

	// save registers
	addi	sp,sp,-24
	sw	ra,0(sp)
	sw	a0,4(sp)	// save X
	sw	a1,8(sp)	// save Y
	sw	a2,12(sp)	// save W
	sw	a3,16(sp)	// save H
	sw	a4,20(sp)	// save COL

// Registers:
//  0: RA
//  4: X
//  8: Y
//  12: W
//  16: H
//  20: col

	// draw bottom H line ... DrawHLine(x, y+h-1, w, col);
	add	a1,a1,a3	// A1 <- Y+H
	addi	a1,a1,-1	// A1 <- Y+H-1
	mv	a3,a4		// A3 <- color
	call	DrawHLine

	// draw top H line ... DrawHLine(x, y, w, col);
	lw	a0,4(sp)	// A0 <- X
	lw	a1,8(sp)	// A1 <- Y
	lw	a2,12(sp)	// A2 <- W
	lw	a3,20(sp)	// A3 <- col
	call	DrawHLine

	// draw left V line ... DrawVLine(x, y, h, col);
	lw	a0,4(sp)	// A0 <- X
	lw	a1,8(sp)	// A1 <- Y
	lw	a2,16(sp)	// A2 <- H
	lw	a3,20(sp)	// A3 <- col
	call	DrawVLine
	
	// draw right V line ... DrawVLine(x+w-1, y, h, col);
	lw	a0,4(sp)	// A0 <- X
	lw	a1,8(sp)	// A1 <- Y
	lw	a2,12(sp)	// A2 <- W
	add	a0,a0,a2	// A0 <- X+W
	addi	a0,a0,-1	// A0 <- X+W-1
	lw	a2,16(sp)	// A2 <- H
	lw	a3,20(sp)	// A3 <- col

	// restore register
	lw	ra,0(sp)
	addi	sp,sp,24

// ---- continue to DrawVLine

// ----------------------------------------------------------------------------
// Draw vertical line
// ----------------------------------------------------------------------------
// void DrawVLine(int x, int y, int h, int col)

.global DrawVLine
DrawVLine:
	mv	a4,a3		// A4 <- color
	mv	a3,a2		// A3 <- height
	li	a2,1		// width = 1
	j	DrawRect

// ----------------------------------------------------------------------------
// Draw horizontal line
// ----------------------------------------------------------------------------
// void DrawHLine(int x, int y, int w, int col)

.global DrawHLine
DrawHLine:
	mv	a4,a3		// A4 <- color
	li	a3,1		// height = 1

// ---- continue to DrawRext

// ----------------------------------------------------------------------------
// Draw rectangle
// ----------------------------------------------------------------------------
// void DrawRect(int x, int y, int w, int h, int col)

.global DrawRect
DrawRect:

	// check if dimension is valid
	blez	a2,9f		// exit if W <= 0
	blez	a3,9f		// exit if H <= 0

// Registers in the stack:
//  0: RA
//  4: X0
//  8: X+W (A2)
//  12: Y+H (A3)
//  16: COL (A4)
//  20: X (A0)
//  24: Y (A1)

	// save registers
	addi	sp,sp,-28
	sw	ra,0(sp)	// save RA
	sw	a0,4(sp)	// save X0
	add	a2,a2,a0	// A2 <- X+W
	sw	a2,8(sp)	// save X+W
	add	a3,a3,a1	// A3 <- Y+H
	sw	a3,12(sp)	// save Y+H
	sw	a4,16(sp)	// save COL

	// prepare to draw horizontal line
2:	sw	a1,24(sp)	// save Y

	// draw pixel
3:	sw	a0,20(sp)	// save X
	lw	a2,16(sp)	// A2 <- COL
	call	DrawPoint	// draw pixel (A0=X, A1=Y, A2=COL)

	// next pixel
	lw	a0,20(sp)	// A0 <- X
	lw	a1,24(sp)	// A1 <- Y
	addi	a0,a0,1		// increase X
	lw	a3,8(sp)	// A3 <- X+W
	bne	a0,a3,3b	// next pixel

	// next line
	lw	a0,4(sp)	// A0 (X) <- X0
	addi	a1,a1,1		// increase Y
	lw	a3,12(sp)	// A3 <- Y+H
	bne	a1,a3,2b	// next line

	// restore registers
	lw	ra,0(sp)	// restore RA
	add	sp,sp,28
9:	ret

// ----------------------------------------------------------------------------
// Draw character normal sized, with background
// ----------------------------------------------------------------------------
// void DrawCharBg(char ch, int x, int y)

.global DrawCharBg
DrawCharBg:

	// save registers
	addi	sp,sp,-28
	sw	ra,0(sp)	// save RA
	addi	a3,a1,8		// A3 <- X+8
	sw	a3,24(sp)	// save X+8

// Registers:
//  0: RA
//  4: font source 'src'
//  8: font end 'src' + 8*128
// 12: font mask 'm'
// 16: X
// 20: Y
// 24: X+8

	// prepare font address -> A3
	la	a3,FONT		// A3 <- font address
	add	a3,a3,a0	// A3 <- address of font of character = 'src'
	addi	a4,a3,8*128	// A4 <- end of font
	sw	a4,8(sp)	// save end of font
	mv	a0,a1		// A0 <- X
	mv	a1,a2		// A1 <- Y

	// prepare for next line
2:	lbu	a4,0(a3)	// A4 <- font sample 'm'
	sw	a3,4(sp)	// save 'src' font address
	lbu	a5,RAM_PRINTINV_OFF(gp) // A5 <- PrintInv flag
	beqz	a5,3f		// skip if PrintInv = 0 (no inversion)
	not	a4,a4		// A4 <- invert sample 'm'

	// draw pixel
3:	andi	a2,a4,0x80	// A2 <- mask bit 7 (= color)
	sw	a4,12(sp)	// save 'm' font mask
	sw	a0,16(sp)	// save X
	sw	a1,20(sp)	// save Y
	call	DrawPointInv

	// next pixel
	lw	a1,20(sp)	// A1 <- Y
	lw	a0,16(sp)	// A0 <- X
	addi	a0,a0,1		// A0 <- increase X+1
	lw	a4,12(sp)	// A4 <- 'm' font mask
	slli	a4,a4,1		// A4 <- shift mask m<<1
	lw	a5,24(sp)	// A5 <- X+8
	bne	a0,a5,3b	// next pixel

	// next line
	addi	a0,a0,-8	// restore X
	addi	a1,a1,1		// increase Y
	lw	a3,4(sp)	// A3 <- font address 'src'
	addi	a3,a3,128	// shift font address 'src'
	lw	a5,8(sp)	// A5 <- font end
	bne	a3,a5,2b	// next line

	// restore registers
	lw	ra,0(sp)	// restore RA
	add	sp,sp,28
	ret

// ----------------------------------------------------------------------------
// Draw character double-sized, with background
// ----------------------------------------------------------------------------
// void DrawChar2Bg(char ch, int x, int y)

.global DrawChar2Bg
DrawChar2Bg:

	// save registers
	addi	sp,sp,-32
	sw	ra,0(sp)	// save RA
	addi	a3,a1,16	// A3 <- X+16
	sw	a3,24(sp)	// save X+16

// Registers:
//  0: RA
//  4: font source 'src'
//  8: font end 'src' + 8*128
// 12: font mask 'm'
// 16: X
// 20: Y
// 24: X+16
// 28: col

	// prepare font address -> A3
	la	a3,FONT		// A3 <- font address
	add	a3,a3,a0	// A3 <- address of font of character = 'src'
	addi	a4,a3,8*128	// A4 <- end of font
	sw	a4,8(sp)	// save end of font
	mv	a0,a1		// A0 <- X
	mv	a1,a2		// A1 <- Y

	// prepare for next line
2:	lbu	a4,0(a3)	// A4 <- font sample 'm'
	sw	a3,4(sp)	// save 'src' font address
	lbu	a5,RAM_PRINTINV_OFF(gp) // A5 <- PrintInv flag
	beqz	a5,3f		// skip if PrintInv = 0 (no inversion)
	not	a4,a4		// A4 <- invert sample 'm'

	// draw pixel
3:	andi	a2,a4,0x80	// A2 <- mask bit 7 (= color)
	sw	a4,12(sp)	// save 'm' font mask
	sw	a0,16(sp)	// save X
	sw	a1,20(sp)	// save Y
	sw	a2,28(sp)	// save col
	call	DrawPointInv
	lw	a1,20(sp)	// A1 <- Y
	lw	a0,16(sp)	// A0 <- X
	addi	a0,a0,1		// A0 <- X+1
	lw	a2,28(sp)	// A2 <- col
	call	DrawPointInv
	lw	a1,20(sp)	// A1 <- Y
	lw	a0,16(sp)	// A0 <- X
	addi	a1,a1,1		// A1 <- Y+1
	lw	a2,28(sp)	// A2 <- col
	call	DrawPointInv
	lw	a1,20(sp)	// A1 <- Y
	lw	a0,16(sp)	// A0 <- X
	addi	a0,a0,1		// A0 <- X+1
	addi	a1,a1,1		// A1 <- Y+1
	lw	a2,28(sp)	// A2 <- col
	call	DrawPointInv

	// next pixel
	lw	a1,20(sp)	// A1 <- Y
	lw	a0,16(sp)	// A0 <- X
	addi	a0,a0,2		// A0 <- increase X+2
	lw	a4,12(sp)	// A4 <- 'm' font mask
	slli	a4,a4,1		// A4 <- shift mask m<<1
	lw	a5,24(sp)	// A5 <- X+16
	bne	a0,a5,3b	// next pixel

	// next line
	addi	a0,a0,-16	// restore X
	addi	a1,a1,2		// increase Y
	lw	a3,4(sp)	// A3 <- font address 'src'
	addi	a3,a3,128	// shift font address 'src'
	lw	a5,8(sp)	// A5 <- font end
	bne	a3,a5,2b	// next line

	// restore registers
	lw	ra,0(sp)	// restore RA
	add	sp,sp,32
	ret

// ----------------------------------------------------------------------------
// Draw ASCIIZ text, with background
// ----------------------------------------------------------------------------
// void DrawTextBg(const char* text, int x, int y)

.global DrawTextBg
DrawTextBg:

	// save registers
	addi	sp,sp,-16
	sw	ra,0(sp)

	// prepare next character
2:	sw	a0,4(sp)	// save text pointer
	lbu	a0,0(a0)	// load next character
	beqz	a0,8f		// end of text

	// print character
	sw	a1,8(sp)	// save X
	sw	a2,12(sp)	// save Y
	call	DrawCharBg

	// next character
	lw	a2,12(sp)	// A2 <- Y
	lw	a1,8(sp)	// A1 <- X
	addi	a1,a1,8		// A1 <- X+8
	lw	a0,4(sp)	// A0 <- text pointer
	addi	a0,a0,1		// increase text pointer
	j	2b		// next character

	// restore registers
8:	lw	ra,0(sp)
	addi	sp,sp,16
	ret

// ----------------------------------------------------------------------------
// Draw ASCIIZ text double-sized, with background
// ----------------------------------------------------------------------------
// void DrawText2Bg(const char* text, int x, int y)

.global DrawText2Bg
DrawText2Bg:

	// save registers
	addi	sp,sp,-16
	sw	ra,0(sp)

	// prepare next character
2:	sw	a0,4(sp)	// save text pointer
	lbu	a0,0(a0)	// load next character
	beqz	a0,8f		// end of text

	// print character
	sw	a1,8(sp)	// save X
	sw	a2,12(sp)	// save Y
	call	DrawChar2Bg

	// next character
	lw	a2,12(sp)	// A2 <- Y
	lw	a1,8(sp)	// A1 <- X
	addi	a1,a1,16	// A1 <- X+16
	lw	a0,4(sp)	// A0 <- text pointer
	addi	a0,a0,1		// increase text pointer
	j	2b		// next character

	// restore registers
8:	lw	ra,0(sp)
	addi	sp,sp,16
	ret

// ----------------------------------------------------------------------------
// get bits from RLE compression
// ----------------------------------------------------------------------------
// NOINLINE int RleBitNum(int len, sRleData* rle)
// NOINLINE int RleBitNumImg(int len) { return RleBitNum(len, &RleDataImg); }
// NOINLINE int RleBitNumMsk(int len) { return RleBitNum(len, &RleDataMsk); }
// Note: len<=0 not supported in ASM

.global RleBitNumMsk
RleBitNumMsk:
	addi	a1,gp,RAM_RLEDATAMSK_OFF // A1 <- pointer to RleDataMsk
	j	RleBitNum

.global RleBitNumImg
RleBitNumImg:
	addi	a1,gp,RAM_RLEDATAIMG_OFF // A1 <- pointer to RleDataImg

// ---- continue to RleBitNum

.global RleBitNum
RleBitNum:

// Registers:
//  A0: result accumulator 'd'
//  A1: pointer to sRleData
//  A2: byte cache 'cache'
//  A3: number of remaining bits 'bits'
//  A4: pointer to image 'img', temporary bit

	// prepare accumulator
	mv	a5,a0		// A5 <- required number of bits
	li	a0,0		// A0 <- accumulator 'd'

	// shift accumulator left
2:	slli	a0,a0,1		// A0 <- shift accumulator left d<<1

	// get cache -> A2
	lbu	a2,RLE_CACHE_OFF(a1) // A2 <- data cache

	// check if number of remaining bits is 0 -> A3
	lbu	a3,RLE_BITS_OFF(a1) // A3 <- get number of remaining bits
	bnez	a3,4f		// skip if number of bits is not 0

	// load next byte to the cache
	lw	a4,RLE_IMG_OFF(a1) // A4 <- pointer to image data
	lbu	a2,0(a4)	// A2 <- load next byte
	addi	a4,a4,1		// increase pointer to image data
	sw	a4,RLE_IMG_OFF(a1) // save new pointer to image data
	li	a3,8		// A3 <- new number of bits = 8

	// get next bit from data cache (data is 8 bits, no mask '& 1' needed)
4:	srli	a4,a2,7		// A4 <- get bit 7
	or	a0,a0,a4	// A0 <- add bit to the accumulator

	// decrease bits in the cache
	addi	a3,a3,-1	// A3 <- decrease number of bits
	sb	a3,RLE_BITS_OFF(a1) // save new number of bits
	slli	a2,a2,1		// A2 <- shift data cache
	sb	a2,RLE_CACHE_OFF(a1) // save new data cache

	// next bit
	addi	a5,a5,-1	// decrease loop counter
	bnez	a5,2b		// next bit
	ret

// ----------------------------------------------------------------------------
// draw mono image with RLE compression, with background
// ----------------------------------------------------------------------------
// void DrawImgRleBgDir(const u8* img, int x, int y, int dir)
// void DrawImgRleBg(const u8* img, int x, int y) { DrawImgRleBgDir(img, x, y, False); }
// void DrawImgRleBgRev(const u8* img, int x, int y) { DrawImgRleBgDir(img, x, y, True); }

.global DrawImgRleBgRev
DrawImgRleBgRev:
	li	a3,1		// A3 <- direction left
	j	DrawImgRleBgDir

.global DrawImgRleBg
DrawImgRleBg:
	li	a3,0		// A3 <- direction right

// ---- continue to DrawImgRleBgDir

.global DrawImgRleBgDir
DrawImgRleBgDir:

// Input:
//  A0: pointer to image data 'img'
//  A1: X
//  A2: Y
//  A3: dir (0=right, 1=left)

	// save registers
	addi	sp,sp,-44
	sw	ra,0(sp)	// save RA
	sw	s0,4(sp)	// save S0
	sw	s1,8(sp)	// save S1
	sw	tp,12(sp)	// save TP
	mv	s0,a2		// save Y

// Registers:
//  0: RA
//  4: S0
//  8: S1
//  12: TP
//  16: X original start
//  20: Y+H end Y
//  24: DX increment X (+1 or -1)
//  28: W
//  32: len chunk length
//  36: col color
//  40: n chunk counter
//
//  S0: Y current
//  S1: Xd current
//  TP: W2 width counter

	// prepare RLE structure
	addi	a4,a0,2			// skip 2 bytes of the dimension
	addi	a5,gp,RAM_RLEDATAIMG_OFF // A5 <- RLE image data
	sw	a4,RLE_IMG_OFF(a5)	// save pointer to image data
	sb	zero,RLE_BITS_OFF(a5)	// clear number of bits

	// get image width - 1 -> A4
	lbu	a4,0(a0)		// A4 <- get image width - 1

	// prepare start X
	li	a5,1			// A5 <- increment dx = 1
	beqz	a3,1f			// skip if direction is 0
	add	a1,a1,a4		// A1 <- start X = X+W-1
	li	a5,-1			// A5 <- decrement dx = -1
1:	sw	a5,24(sp)		// save dx (+1 or -1)
	sw	a1,16(sp)		// save original X

	// prepare width
	addi	a4,a4,1			// W++
	sw	a4,28(sp)		// save width 'w'

	// prepare end Y = Y + H
	lbu	a4,1(a0)		// A4 <- get image height - 1
	addi	a4,a4,1			// H++
	add	a4,s0,a4		// A4 <- Y+H
	sw	a4,20(sp)		// save end Y

	// prepare chunk length
	li	a0,3
	call	RleBitNumImg		// get chunk length
	sw	a0,32(sp)		// save chunk length 'len'

	// check simple copy mode
	li	a1,2			// minimal length
	bge	a0,a1,5f		// using RLE compression

// ---- simple copy

	// start next line
2:	lw	s1,16(sp)		// S1 <- prepare Xd
	lw	tp,28(sp)		// TP <- width counter

	// get color -> A2
3:	li	a0,1			// number of bits = 1
	call	RleBitNumImg		// get RLE bits
	mv	a2,a0			// A2 <- color 0 or 1

	// draw pixel
	mv	a0,s1			// A0 <- current Xd
	mv	a1,s0			// A1 <- current Y
	call	DrawPointInv		// draw pixel

	// next pixel
	lw	a1,24(sp)		// A1 <- increment DX
	add	s1,s1,a1		// S1 <- shift Xd
	addi	tp,tp,-1		// decrease width counter
	bnez	tp,3b			// next pixel

	// next line
	addi	s0,s0,1			// S0 <- increment Y
	lw	a2,20(sp)		// A2 <- end Y
	bne	s0,a2,2b		// next line
	j	9f			// exit

// ---- RLE compression

	// prepare first chunk (it will be 0) ... here is A0=chunk length 'len'
5:	lbu	a1,RAM_PRINTINV_OFF(gp)	// A1 <- get PrintInv flag
	sw	a1,36(sp)		// save flag as first color
	call	RleBitNumImg		// get length of first chunk
	sw	a0,40(sp)		// save first chunk counter 'n'

	// start next line
6:	lw	s1,16(sp)		// S1 <- prepare Xd
	lw	tp,28(sp)		// TP <- width counter

	// load next chunk
7:	lw	a0,40(sp)		// A0 <- chunk counter 'n'
8:	bnez	a0,1f			// skip if chunk is not 0
	lw	a0,32(sp)		// A0 <- chunk length
	call	RleBitNumImg		// load next chunk counter -> A0
	lw	a1,36(sp)		// A1 <- color 'col'
	xori	a1,a1,1			// flip color
	sw	a1,36(sp)		// save new color
	j	8b			// next chunk

1:	addi	a0,a0,-1		// A0 <- decrease chunk counter
	sw	a0,40(sp)		// save new chunk counter

	// draw pixel
	mv	a0,s1			// A0 <- current Xd
	mv	a1,s0			// A1 <- current Y
	lw	a2,36(sp)		// A2 <- color 'col'
	call	DrawPointInv		// draw pixel

	// next pixel
	lw	a1,24(sp)		// A1 <- increment DX
	add	s1,s1,a1		// S1 <- shift Xd
	addi	tp,tp,-1		// decrease width counter
	bnez	tp,7b			// next pixel

	// next line
	addi	s0,s0,1			// S0 <- increment Y
	lw	a2,20(sp)		// A2 <- end Y
	bne	s0,a2,6b		// next line

	// restore registers
9:	lw	tp,12(sp)
	lw	s1,8(sp)
	lw	s0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,44
	ret

// ----------------------------------------------------------------------------
// draw mono image with RLE compression and with mask
// ----------------------------------------------------------------------------
// void DrawImgRleMask(const u8* img, const u8* msk, int x, int y)
// Note: Both the image and the mask must be identical, either in compressed
//       or uncompressed format (chunk length > 1, or chunk length == 1).

.global DrawImgRleMask
DrawImgRleMask:

// Input:
//  A0: pointer to image data 'img'
//  A1: pointer to mask 'msk'
//  A2: X
//  A3: Y

	// save registers
	addi	sp,sp,-48
	sw	ra,0(sp)	// save RA
	sw	s0,4(sp)	// save S0
	sw	s1,8(sp)	// save S1

	sw	a2,12(sp)	// save X original start
	mv	s0,a3		// save Y

// Registers:
//  0: RA
//  4: S0
//  8: S1
//  12: X original start
//  16: Y+H end Y
//  20: X+W end X
//  24: image chunk length 'len'
//  28: col color
//  32: n image chunk counter
//  36: mask chunk length 'lenmsk'
//  40: m mask
//  44: nmsk mask chunk counter

//  S0: Y current
//  S1: Xd current

	// prepare RLE structures
	addi	a4,a0,2			// skip 2 bytes of the dimension
	addi	a5,gp,RAM_RLEDATAIMG_OFF // A5 <- RLE image data
	sw	a4,RLE_IMG_OFF(a5)	// save pointer to image data
	sb	zero,RLE_BITS_OFF(a5)	// clear number of bits

	addi	a1,a1,2			// skip 2 bytes of the dimension
	addi	a5,gp,RAM_RLEDATAMSK_OFF // A5 <- RLE mask data
	sw	a1,RLE_IMG_OFF(a5)	// save pointer to mask data
	sb	zero,RLE_BITS_OFF(a5)	// clear number of bits

	// prepare end X = X + W
	lbu	a4,0(a0)		// A4 <- get image width - 1
	addi	a4,a4,1			// W++
	add	a4,a4,a2		// A4 <- X+W
	sw	a4,20(sp)		// save end X

	// prepare end Y = Y + H
	lbu	a4,1(a0)		// A4 <- get image height - 1
	addi	a4,a4,1			// H++
	add	a4,s0,a4		// A4 <- Y+H
	sw	a4,16(sp)		// save end Y

	// prepare mask chunk length
	li	a0,3
	call	RleBitNumMsk		// get chunk length
	sw	a0,36(sp)		// save chunk length 'lenmsk'

	// prepare image chunk length
	li	a0,3
	call	RleBitNumImg		// get chunk length
	sw	a0,24(sp)		// save chunk length 'len'

	// check simple copy mode
	li	a1,2			// minimal length
	bge	a0,a1,5f		// using RLE compression

// ---- simple copy

	// start next line
2:	lw	s1,12(sp)		// S1 <- prepare Xd

	// get color
3:	li	a0,1			// number of bits = 1
	call	RleBitNumImg		// get RLE bits
	sw	a0,28(sp)		// save color

	// get mask -> A0
	li	a0,1			// number of bits = 1
	call	RleBitNumMsk		// get RLE bits
	bnez	a0,4f			// skip if mask is not 0

	// draw pixel
	mv	a0,s1			// A0 <- current Xd
	mv	a1,s0			// A1 <- current Y
	lw	a2,28(sp)		// A2 <- color
	call	DrawPointInv		// draw pixel

	// next pixel
4:	addi	s1,s1,1			// S1 <- shift Xd
	lw	a5,20(sp)		// A5 <- end X
	bne	s1,a5,3b		// next pixel

	// next line
	addi	s0,s0,1			// S0 <- increment Y
	lw	a2,16(sp)		// A2 <- end Y
	bne	s0,a2,2b		// next line
	j	9f			// exit

// ---- RLE compression

	// prepare first chunk (it will be 0) ... here is A0=chunk length 'len'
5:	lbu	a1,RAM_PRINTINV_OFF(gp)	// A1 <- get PrintInv flag
	sw	a1,28(sp)		// save flag as first color
	sw	zero,40(sp)		// save 0 as first mask
	call	RleBitNumImg		// get length of first image chunk
	sw	a0,32(sp)		// save first image chunk counter 'n'
	lw	a0,36(sp)		// A0 <- mask length 'lenmsk'
	call	RleBitNumMsk		// get length of first mask chunk
	sw	a0,44(sp)		// save first mask chunk counter 'nmsk'

	// start next line
6:	lw	s1,12(sp)		// S1 <- prepare Xd

	// load next image chunk
7:	lw	a0,32(sp)		// A0 <- chunk counter 'n'
8:	bnez	a0,1f			// skip if chunk is not 0
	lw	a0,24(sp)		// A0 <- chunk length
	call	RleBitNumImg		// load next chunk counter -> A0
	lw	a1,28(sp)		// A1 <- color 'col'
	xori	a1,a1,1			// flip color
	sw	a1,28(sp)		// save new color
	j	8b			// next chunk
1:	addi	a0,a0,-1		// A0 <- decrease chunk counter
	sw	a0,32(sp)		// save new chunk counter

	// load next mask chunk
	lw	a0,44(sp)		// A0 <- chunk counter 'nmsk'
2:	bnez	a0,3f			// skip if chunk is not 0
	lw	a0,36(sp)		// A0 <- chunk length
	call	RleBitNumMsk		// load next chunk counter -> A0
	lw	a1,40(sp)		// A1 <- mask 'm'
	xori	a1,a1,1			// flip mask
	sw	a1,40(sp)		// save new mask
	j	2b			// next chunk
3:	addi	a0,a0,-1		// A0 <- decrease chunk counter
	sw	a0,44(sp)		// save new chunk counter

	// draw pixel
	lw	a1,40(sp)		// A1 <- mask 'm'
	bnez	a1,4f			// skip if mask is not 0
	mv	a0,s1			// A0 <- current Xd
	mv	a1,s0			// A1 <- current Y
	lw	a2,28(sp)		// A2 <- color 'col'
	call	DrawPointInv		// draw pixel

	// next pixel
4:	addi	s1,s1,1			// S1 <- shift Xd
	lw	a5,20(sp)		// A5 <- end X
	bne	s1,a5,7b		// next pixel

	// next line
	addi	s0,s0,1			// S0 <- increment Y
	lw	a2,16(sp)		// A2 <- end Y
	bne	s0,a2,6b		// next line

	// restore registers
9:	lw	s1,8(sp)
	lw	s0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,48
	ret

#endif // USE_DRAW_ASM
