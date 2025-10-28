
// ****************************************************************************
//
//                        BabyPC - VGA display driver
//
// ****************************************************************************
// Using system clock 50MHz with HSI internal oscillator or external crystal 25MHz.
//
// Video signals, chip CH32V002A4M6
// --------------------------------
// SPI1 - "Video" output via PC6 (pin 5), MOSI base mapping (PC1:CS, PC5:SCK, PC7:MISO, PC6:MOSI)
// VSYNC, output via PC4 (pin 4)
// Timer 2, channel 2 - HSYNC, output via PC7 (pin 6), TIM2 mapping 3 (PC1:CH1/ETR, PC7:CH2, PD6:CH3/CH1N, PD5:CH4/CH2N)
// Timer 2, channel 1 - interrupt to draw image line
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

#ifndef _BABYPC_VGA_H
#define _BABYPC_VGA_H

#ifdef __cplusplus
extern "C" {
#endif

// Videomodes

// Videomode 0: graphics mode 128x64 pixels, required memory 1024 B
#if VMODE == 0
#define WIDTH		128		// width in pixels
#define HEIGHT		64		// height in graphics lines (must be even number - due render "next scanline")
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 16)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 16*64 = 1024 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 16)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 8; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV8	// SPI horizontal divider

// Videomode 1: graphics mode 160x120 pixels, required memory 2400 B
#elif VMODE == 1
#define WIDTH		160		// width in pixels
#define HEIGHT		120		// height in graphics lines (must be even number - due render "next scanline")
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 20)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 20*120 = 2400 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 20)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 15; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV8	// SPI horizontal divider

// Videomode 2: text mode 32x24 characters of 8x8 pixels (resolution 256x192 pixels, pseudographics 64x48 pixels), required memory 768 bytes, font 8x8 pixels 2048 bytes in Flash
#elif VMODE == 2
#define WIDTH		32		// width in characters
#define HEIGHT		24		// height in text rows
#define WIDTHBYTE	WIDTH		// width in bytes (= 32)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 32*24 = 768 bytes)
#define TEXTWIDTH	WIDTH		// text width in characters (= 32)
#define TEXTHEIGHT	HEIGHT		// text height in rows (= 24; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV4	// SPI horizontal divider

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

// Videomode 5: text mode 32x24 characters in ZX-80 format (NEWLINE=0x76 is new line)
#elif VMODE == 5
#define WIDTH		32		// width in characters
#define HEIGHT		24		// height in text rows
#define SPI_HDIV	SPI_BAUD_DIV4	// SPI horizontal divider

// Videomode 6: text mode 40x30 characters of 8x8 pixels with ZX Spectrum font of 128 characters
#elif VMODE == 6
#define WIDTH		40		// width in characters
#define HEIGHT		30		// height in text rows
#define WIDTHBYTE	WIDTH		// width in bytes (= 40)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 40*30 = 1200 bytes)
#define TEXTWIDTH	WIDTH		// text width in characters (= 40)
#define TEXTHEIGHT	HEIGHT		// text height in rows (= 30; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV4	// SPI horizontal divider

// Videomode 7:text mode 32x24 characters of 8x8 pixels with ZX-80/ZX-81 font of 64 characters
#elif VMODE == 7
#define WIDTH		32		// width in characters
#define HEIGHT		24		// height in text rows
#define WIDTHBYTE	WIDTH		// width in bytes (= 32)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 32*24 = 768 bytes)
#define TEXTWIDTH	WIDTH		// text width in characters (= 32)
#define TEXTHEIGHT	HEIGHT		// text height in rows (= 24; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV4	// SPI horizontal divider

#endif // VMODE=...

#if VMODE == 5
extern u8* volatile FrameBuf;		// display graphics buffer
#else
extern u8 FrameBuf[FRAMESIZE];		// display graphics buffer
#endif
extern volatile u32 DispLine;		// current display line
extern volatile u32 DispFrame;		// current frame
extern volatile u8* FrameBufAddr;	// current pointer to graphics buffer
extern volatile u32 DispTimTest;	// test - get TIM-CNT value at start of image

// check VSYNC
#if VMODE == 0
INLINE Bool DispIsVSync() { return DispLine >= 256; }
#elif (VMODE == 2) || (VMODE == 5) || (VMODE == 7)
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

#endif // _BABYPC_VGA_H

#endif // USE_DISP
