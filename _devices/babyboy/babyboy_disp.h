
// ****************************************************************************
//
//                        BabyBoy - Display driver
//
// ****************************************************************************
// OLED I2C 0.96" SSD1306 display, resolution 128x64 pixels, controller SSD1306, power 3 to 5V.
// https://pajenicko.cz/graficky-oled-displej-096-128x64-i2c-bily

//#define DISP_I2C_ADDR	0x3C	// display I2C address
//#define DISP_SDA_GPIO	PC1	// display gpio with SDA
//#define DISP_SCL_GPIO	PC2	// display gpio with SCL
//#define DISP_WAIT_CLK	4	// number of I2C wait clock (0 or more)

#if USE_DISP		// 1=use software display driver, 2=use hardware display driver (0=no driver)

#ifndef _BABYBOY_DISP_H
#define _BABYBOY_DISP_H

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

extern u8 FrameBuf[FRAMESIZE];		// display graphics buffer

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

#endif // _BABYBOY_DISP_H

#endif // USE_DISP
