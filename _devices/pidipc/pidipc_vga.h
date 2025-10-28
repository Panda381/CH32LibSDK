
// ****************************************************************************
//
//                        PidiPC - VGA display driver
//
// ****************************************************************************
// Using system clock 50MHz with HSI internal oscillator or external crystal 25MHz.
//
// Video signals, chip CH32V006E8R6
// --------------------------------
// SPI1 - "Video" output via PC0 (pin 2), MOSI mapping 3 (PB0:CS, PB1:SCK, PB2:MISO, PC0:MOSI)
// blue color, open-drain output via PB0 (pin 22)
// red color, open-drain output via PB1 (pin 23)
// green color, open-drain output via PB3 (pin 24)
// VSYNC, output via PC4 (pin 8)
// Timer 2, channel 1 - HSYNC, output via PC5 (pin 7), TIM2 mapping 2 (PC5:CH1/ETR, PC2:CH2, PD2:CH3/CH1N, PC1:CH4/CH2N)
// Timer 2, channel 3 - interrupt to draw image line in pidipc_vga_asm.S
//
// Videomode 640x480/60Hz timing
// -----------------------------
//  VSYNC: 60Hz
//  HSYNC: 31.46875 kHz
//  Pixel clock: 25.175 MHz (0.0397195 us/pixel)
//
//  H active: 640 pixels, 25.42205 us
//  H front porch: 16 pixels, 0.63555 us
//  H sync: 96 pixels, 3.81331 us
//  H back porch: 48 pixels, 1.90665 us
//  H whole line: 800 pixels, 31.77756 us
//
//  V active: 480 scanlines
//  V front porch: 10 scanlines
//  V sync: 2 scanlines
//  V back porch: 33 scanlines
//  V whole frame: 525 scanlines

#if USE_DISP		// 1=use display support

#ifndef _PIDIPC_VGA_H
#define _PIDIPC_VGA_H

#ifdef __cplusplus
extern "C" {
#endif

// Videomodes (9 colors: 1 black background + 8 foreground colors):
// Videomode 1: graphics mode 128x64 pixels mono with color attributes 1x1 pixel, required memory 1024+4096 = 5120 B
#if VMODE == 1
#define WIDTH		128		// width in pixels
#define HEIGHT		64		// height in graphics lines
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 16)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 16*64 = 1024 bytes)
#define ATTRWIDTHBYTE	(WIDTH/2)	// width of attribute buffer in bytes (= 64)
#define ATTRHEIGHT	HEIGHT		// height of attribute buffer (= 64)
#define ATTRSIZE	(ATTRWIDTHBYTE*ATTRHEIGHT) // size of attribute buffer in bytes (= 64x64 = 4096 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 16)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 8; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV8	// SPI horizontal divider

// Videomode 2: graphics mode 160x120 pixels mono with color attributes 4x4 pixels, required memory 2400+600 = 3000 B (driver size 540 B in RAM)
#elif VMODE == 2
#define WIDTH		160		// width in pixels
#define HEIGHT		120		// height in graphics lines
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 20)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 20*120 = 2400 bytes)
#define ATTRWIDTHBYTE	(WIDTH/8)	// width of attribute buffer in bytes (= 20)
#define ATTRHEIGHT	(HEIGHT/4)	// height of attribute buffer (= 30)
#define ATTRSIZE	(ATTRWIDTHBYTE*ATTRHEIGHT) // size of attribute buffer in bytes (= 20x30 = 600 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 20)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 15; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV8	// SPI horizontal divider

// Videomode 3: graphics mode 160x120 pixels mono with color attributes 2x2 pixels, required memory 2400+2400 = 4800 B (driver size 532 B in RAM)
#elif VMODE == 3
#define WIDTH		160		// width in pixels
#define HEIGHT		120		// height in graphics lines
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 20)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 20*120 = 2400 bytes)
#define ATTRWIDTHBYTE	(WIDTH/4)	// width of attribute buffer in bytes (= 40)
#define ATTRHEIGHT	(HEIGHT/2)	// height of attribute buffer (= 60)
#define ATTRSIZE	(ATTRWIDTHBYTE*ATTRHEIGHT) // size of attribute buffer in bytes (= 40x60 = 2400 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 20)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 15; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV8	// SPI horizontal divider

// Videomode 4: graphics mode 256x192 pixels mono with color attributes 8x8 pixels, required memory 6144+384 = 6528 B (driver size 516 B in RAM)
#elif VMODE == 4
#define WIDTH		256		// width in pixels
#define HEIGHT		192		// height in graphics lines
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 32)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 32*192 = 6144 bytes)
#define ATTRWIDTHBYTE	(WIDTH/16)	// width of attribute buffer in bytes (= 16)
#define ATTRHEIGHT	(HEIGHT/8)	// height of attribute buffer (= 24)
#define ATTRSIZE	(ATTRWIDTHBYTE*ATTRHEIGHT) // size of attribute buffer in bytes (= 16x24 = 384 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 32)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 24; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV4	// SPI horizontal divider

// Videomode 5: text mode 32x24 characters of 8x8 pixels with ZX-80/ZX-81 font of 64 characters in Flash, with color attributes, required memory 768+384 = 1152 B
#elif VMODE == 5
#define WIDTH		32		// width in characters
#define HEIGHT		24		// height in text rows
#define WIDTHBYTE	WIDTH		// width in bytes (= 32)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 32*24 = 768 bytes)
#define ATTRWIDTHBYTE	(WIDTH/2)	// width of attribute buffer in bytes (= 16)
#define ATTRHEIGHT	HEIGHT		// height of attribute buffer (= 24)
#define ATTRSIZE	(ATTRWIDTHBYTE*ATTRHEIGHT) // size of attribute buffer in bytes (= 16x24 = 384 bytes)
#define TEXTWIDTH	WIDTH		// text width in characters (= 32)
#define TEXTHEIGHT	HEIGHT		// text height in rows (= 24; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV4	// SPI horizontal divider

// Videomode 6: text mode 40x30 characters of 8x8 pixels (resolution 320x240 pixels, pseudographics 80x60 pixels) with color attributes, font 2048 B in Flash, required memory 1200+600=1800 B
#elif VMODE == 6
#define WIDTH		40		// width in characters
#define HEIGHT		30		// height in text rows
#define WIDTHBYTE	WIDTH		// width in bytes (= 40)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 40*30 = 1200 bytes)
#define ATTRWIDTHBYTE	(WIDTH/2)	// width of attribute buffer in bytes (= 20)
#define ATTRHEIGHT	HEIGHT		// height of attribute buffer (= 30)
#define ATTRSIZE	(ATTRWIDTHBYTE*ATTRHEIGHT) // size of attribute buffer in bytes (= 20x30 = 600 bytes)
#define TEXTWIDTH	WIDTH		// text width in characters (= 40)
#define TEXTHEIGHT	HEIGHT		// text height in rows (= 30; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV4	// SPI horizontal divider

// Videomode 7: text mode 80x30 characters of 8x8 pixels (resolution 640x240 pixels, pseudographics 160x60 pixels) with color attributes, font 2048 B in RAM FontBuf, required memory 2400+1200+2048=5648 B (driver size 504 B in RAM)
#elif VMODE == 7
#define WIDTH		80		// width in characters
#define HEIGHT		30		// height in text rows
#define WIDTHBYTE	WIDTH		// width in bytes (= 80)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 80*30 = 2400 bytes)
#define ATTRWIDTHBYTE	(WIDTH/2)	// width of attribute buffer in bytes (= 40)
#define ATTRHEIGHT	HEIGHT		// height of attribute buffer (= 30)
#define ATTRSIZE	(ATTRWIDTHBYTE*ATTRHEIGHT) // size of attribute buffer in bytes (= 40x30 = 1200 bytes)
#define TEXTWIDTH	WIDTH		// text width in characters (= 80)
#define TEXTHEIGHT	HEIGHT		// text height in rows (= 30; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV2	// SPI horizontal divider

#endif // VMODE=...

extern u8 FrameBuf[FRAMESIZE];		// display graphics buffer
extern u8 AttrBuf[ATTRSIZE];		// display attribute buffer (color of 2 pixels: 1st pixels in bits 1..3, 2nd pixel in bits 5..7)
#if VMODE == 7
extern u8 FontBuf[2048];		// bont buffer 8x8
#endif
extern volatile int DispLine;		// current display line
extern volatile u32 DispFrame;		// current frame
extern volatile u32 DispTimTest;	// test - get TIM-CNT value at start of image (should be 144-19=125)
#if VMODE == 5
extern u32 DispMaxLine;			// index of last scanline
#endif

// check VSYNC
#if VMODE == 1
INLINE Bool DispIsVSync() { return DispLine >= 256; }
#elif (VMODE == 4) || (VMODE == 5)
INLINE Bool DispIsVSync() { return DispLine >= 384; }
#else
INLINE Bool DispIsVSync() { return DispLine >= 480; }
#endif

// wait for VSync scanline
void WaitVSync();

// Initialize videomode
void DispInit();

// Terminate videomode
void DispTerm();

#ifdef __cplusplus
}
#endif

#endif // _PIDIPC_VGA_H

#endif // USE_DISP
