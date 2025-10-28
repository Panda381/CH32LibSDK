
// ****************************************************************************
//
//                        BabyPad - VGA display driver
//
// ****************************************************************************
// Using system clock 50MHz with HSI internal oscillator or external crystal 25MHz.
//
// Video signals, chip CH32V002A4M6
// --------------------------------
// SPI1 - "Video" output via PC6 (pin 5), MOSI base mapping (PC1:CS, PC5:SCK, PC7:MISO, PC6:MOSI)
// VSYNC, output via PC7 (pin 6)
// Timer 2, channel 1 - HSYNC, output via PD4 (pin 8), TIM2 base mapping (PD4:CH1/ETR, PD3:CH2, PC0:CH3/CH1N, PD7:CH4/CH2N)
// Timer 2, channel 2 - interrupt to draw image line
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

#ifndef _BABYPAD_VGA_H
#define _BABYPAD_VGA_H

#ifdef __cplusplus
extern "C" {
#endif

// Videomodes

// Videomode 1: graphics mode 160x120 pixels, required memory 2400 B
#if VMODE == 1
#define WIDTH		160		// width in pixels
#define HEIGHT		120		// height in graphics lines (must be even number - due render "next scanline")
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 20)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 20*120 = 2400 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 20)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 15; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV8	// SPI horizontal divider

// Videomode 2: graphics mode 160x120 pixels with gray 1-bit attributes 2x2 pixels, required memory 2400+600 = 3000 B
#elif VMODE == 2
#define WIDTH		160		// width in pixels
#define HEIGHT		120		// height in graphics lines (must be even number - due render "next scanline")
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 20)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 20*120 = 2400 bytes)
#define ATTRWIDTHBYTE	(WIDTH/16)	// width of attribute buffer in bytes (= 10) ... 1 attribute byte = 8 double-pixels = 16 pixels
#define ATTRHEIGHT	(HEIGHT/2)	// height of attribute buffer (= 60)
#define ATTRSIZE	(ATTRWIDTHBYTE*ATTRHEIGHT) // size of attribute buffer in bytes (= 10x60 = 600 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 20)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 15; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV8	// SPI horizontal divider

// Videomode 3: text mode 40x30 characters of 8x8 pixels (resolution 320x240 pixels, pseudographics 80x60 pixels), required memory 1200 bytes, font 8x8 pixels 2048 bytes in Flash
#elif VMODE == 3
#define WIDTH		40		// width in characters
#define HEIGHT		30		// height in text rows
#define WIDTHBYTE	WIDTH		// width in bytes (= 40)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 40*30 = 1200 bytes)
#define TEXTWIDTH	WIDTH		// text width in characters (= 40)
#define TEXTHEIGHT	HEIGHT		// text height in rows (= 30; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV4	// SPI horizontal divider

// Videomode 4: text mode 80x30 characters of 8x8 pixels (resolution 640x240 pixels, pseudographics 160x60 pixels), required memory 2400 bytes, font 8x8 pixels 2048 bytes in Flash
#elif VMODE == 4
#define WIDTH		80		// width in characters
#define HEIGHT		30		// height in text rows
#define WIDTHBYTE	WIDTH		// width in bytes (= 80)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 80*30 = 2400 bytes)
#define TEXTWIDTH	WIDTH		// text width in characters (= 80)
#define TEXTHEIGHT	HEIGHT		// text height in rows (= 30; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV2	// SPI horizontal divider

#endif // VMODE=...

extern u8 FrameBuf[FRAMESIZE];		// display graphics buffer
#if VMODE == 2
extern u8 AttrBuf[ATTRSIZE];		// display attribute buffer (1 bit = high level of white color; 1st pixel is MSB)
#endif
extern volatile u32 DispLine;		// current display line
extern volatile u32 DispFrame;		// current frame
extern volatile u8* FrameBufAddr;	// current pointer to graphics buffer
extern volatile u32 DispTimTest;	// test - get TIM-CNT value at start of image

// check VSYNC
INLINE Bool DispIsVSync() { return DispLine >= 480; }

// wait for VSync scanline
void WaitVSync();

// Initialize videomode
void DispInit();

// Terminate videomode
void DispTerm();

#ifdef __cplusplus
}
#endif

#endif // _BABYPAD_VGA_H

#endif // USE_DISP
