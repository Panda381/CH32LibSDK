
// ****************************************************************************
//
//                        BeatleBoyPad - Display driver
//
// ****************************************************************************

// BeatleBoy
// =========
// OLED I2C 0.96" SSD1306 display, resolution 128x64 pixels, controller SSD1306, power 3 to 5V.
// https://pajenicko.cz/graficky-oled-displej-096-128x64-i2c-bily

//#define DISP_I2C_ADDR	0x3C	// display I2C address
//#define DISP_SDA_GPIO	PC1	// display gpio with SDA
//#define DISP_SCL_GPIO	PC2	// display gpio with SCL
//#define DISP_WAIT_CLK	4	// number of I2C wait clock (0 or more)

// BeatlePad
// =========
// CH32V002:
// SPI1 - "Video" output via PD6, MOSI mapping 4 (PD3:CS, PD4:SCK, PD5:MISO, PD6:MOSI)
// VSYNC, output via PC2
// Timer 2, channel 1 - HSYNC, output via PC1, TIM2 mapping 3 (PC1:CH1/ETR, PC7:CH2, PD6:CH3/CH1N, PD5:CH4/CH2N)
// Timer 2, channel 2 - interrupt to draw image line

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

#if USE_DISP		// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver

#ifndef _BEATLEBOYPAD_DISP_H
#define _BEATLEBOYPAD_DISP_H

#ifdef __cplusplus
extern "C" {
#endif

#define DISP_SDA_PORT	GPIO_PORT(DISP_SDA_GPIO)	// display port with SDA
#define DISP_SCL_PORT	GPIO_PORT(DISP_SCL_GPIO)	// display port with SCL
#define DISP_SDA_PIN	GPIO_PIN(DISP_SDA_GPIO)		// display pin with SDA
#define DISP_SCL_PIN	GPIO_PIN(DISP_SCL_GPIO)		// display pin with SCL

#define WIDTH		128		// width in pixels
#define HEIGHT		64		// height in graphics lines
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 16)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 16*64 = 1024 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 16)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 8; 1 character = 8x8 pixels)
#define SPI_HDIV	SPI_BAUD_DIV4	// SPI horizontal divider

#if DISP_DBLBUF		// 1=use VGA display double buffer (FrameBuf+DispBuf)
extern u8 DispBuf[FRAMESIZE];		// display graphics buffer
#endif
extern u8 FrameBuf[FRAMESIZE];		// display graphics buffer
extern volatile u32 DispLine;		// current display line
extern volatile u32 DispFrame;		// current frame
extern volatile u8* FrameBufAddr;	// current pointer to graphics buffer
extern volatile u32 DispTimTest;	// test - get TIM-CNT value at start of image

// check VSYNC
INLINE Bool DispIsVSync() { return DispLine >= 256; }

// wait for VSync scanline
void WaitVSync();

// start I2C communication
void DispI2C_Start(void);

// stop I2C communication
void DispI2C_Stop(void);

// write a byte over I2C
void DispI2C_Write(u8 data);

// Display select SSD1306 page, start transfer data
void DispI2C_SelectPage(int page);

// Display initialize
void DispInit(void);

// Display terminate
void DispTerm(void);

// Display update - send frame buffer to the display
void DispUpdate();

#ifdef __cplusplus
}
#endif

#endif // _BEATLEBOYPAD_DISP_H

#endif // USE_DISP
