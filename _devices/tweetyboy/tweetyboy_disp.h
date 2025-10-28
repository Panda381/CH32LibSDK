
// ****************************************************************************
//
//                        TweetyBoy - Display driver
//
// ****************************************************************************
// LCD IPS 0.96" ST7735S SPI display, resolution 160x80 pixels, controller ST7735S, power 3.3V.
// https://pajenicko.cz/komponenty/displeje/barevny-displej-ips-0.96-80x160-st7735s-spi

// SPI display
// 0 ... PA4:CS, PA5:SCK, PA6:MISO, PA7:MOSI
// void GPIO_Remap_SPI1(int map);

//#define DISP_SCK_GPIO		PA5		// SCK output to SPI display
//#define DISP_MOSI_GPIO	PA7		// MOSI output to SPI display
//#define DISP_RES_GPIO		PA12		// RES output to SPI display
//#define DISP_DC_GPIO		PA13		// DC output to SPI display
//#define DISP_CS_GPIO		PA4		// CS output to SPI display
//#define DISP_BLK_GPIO		PB4		// BLK output to SPI display
//#define DISP_SPI_MAP		0		// hardware display driver: display SPI mapping
//#define DISP_SPI_DIV		7		// hardware display driver: display SPI baud divider 0..7 (means div=2..256)
//#define DISP_SPEED		(HCLK_PER_US*2)	// software display driver: wait delay "HCLK_PER_US*2" = 250 kbps
//#define USE_DISP		2		// 1=use software display driver, 2=use hardware display driver (0=no driver)

#if USE_DISP		// 1=use software display driver, 2=use hardware display driver (0=no driver)

#ifndef _TWEETYBOY_DISP_H
#define _TWEETYBOY_DISP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PALETTE
#define PALETTE DefPalette	// default palettes RGB332 in RGB565 format
#endif

#define WIDTH		160		// width in pixels
#define HEIGHT		80		// height in graphics lines
#define WIDTHBYTE	WIDTH		// width in bytes (= 160)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in pixels, 1 pixel = 1 byte (= 160*80 = 12800 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 20)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 10; 1 character = 8x8 pixels)

#define BACKLIGHT_DIV	8		// backlight timer divider (clock = 48MHz/8 = 6MHz, PWM clock = 6MHz/256 = 23kHz)
#define BACKLIGHT_LOOP	8		// loop period bits (= 256)
#define BACKLIGHT_MAX	9		// maximal backlight level (= 256)
#define BACKLIGHT_DEF	6		// default backlight level (= 32)
#define BACKLIGHT_MIN	1		// minimal backlight level (= 1)
#define BACKLIGHT_FLASHOFF 0x30		// flash add offset

extern u8 FrameBuf[FRAMESIZE];		// display graphics buffer (1 pixel = 1 byte)
extern const u16 DefPalette[256];	// default palettes RGB332 in RGB565 format
extern const u16* Palette;		// pointer to palettes in RGB565 format

extern int DispUpdateX;		// display update X coordinate
extern int DispUpdateY;		// display update Y coordinate
extern int DispUpdateW;		// display update width
extern int DispUpdateH;		// display update height

extern u8 Disp_OutCol;		// current output color
extern u8 Disp_OutPage;		// current output page (0..7)
extern u8 Disp_OutX;		// current output X (0..127)

// --- internal functions

// rotation mode for ST7735_MADCTL
extern const u8 RotationTab[4];

// display connect (activate chip selection)
void DispConnect(void);

// display disconnect (deactivate chip selection)
void DispDisconnect(void);

// write a byte to the display
void DispWriteByte(u8 data);

// write command to display (display must be connected)
void DispWriteCmd(u8 cmd);

// write data to display (display must be connected)
void DispWriteData(u8 data);

// set draw window, start sending data (display must be connected)
void DispWindow(u16 x1, u16 x2, u16 y1, u16 y2);

// --- global functions

// start simulated I2C communication
INLINE void DispI2C_Start(void) {}

// stop simulated I2C communication
INLINE void DispI2C_Stop(void) {}

// Display select simulated I2C page
void DispI2C_SelectPage(int page);

// write a byte over simulated I2C (write to frame buffer), using Disp_OutCol color
// - After write all data, send image to display with DispUpdate().
void DispI2C_Write(u8 data);

// add byte over simulated I2C (write to frame buffer), write only '1' bits
// - After write all data, send image to display with DispUpdate().
void DispI2C_Add(int x, int y, u8 data, u8 col);

// set byte over simulated I2C (write to frame buffer)
// - After write all data, send image to display with DispUpdate().
void DispI2C_Set(int x, int y, u8 data, u8 col);

// clear byte over simulated I2C (write to frame buffer)
// - After write all data, send image to display with DispUpdate().
void DispI2C_Clr(int x, int y);

// set backlight 1..9
// Total current, by backlight:
// 9: 256 ... 23mA (6+17mA)
// 8: 128 ... 16mA (6+10mA)
// 7: 64 .... 12mA (6+6mA)
// 6: 32 .... 9mA (6+3mA) *default*
// 5: 16 .... 8mA (6+2mA)
// 4: 8 ..... 7mA (6+1mA)
// 3: 4 ..... 7mA (6+1mA)
// 2: 2 ..... 7mA (6+1mA)
// 1: 1 ..... 6mA (6+0mA)
void DispBacklight(u8 backlight);

// read backlight setup level 1..9 from Flash
u8 DispBacklightGet(void);

// write backlight setup level 1..9 to Flash
void DispBacklightSet(u8 backlight);

// clear backlight setup level to default value to Flash
void DispBacklightSetDef();

// update backlight from Flash setup
void DispBacklightUpdate(void);

// Display initialize
void DispInit(void);

// Display terminate
void DispTerm(void);

// set display update window (default full screen is DispUpdateSetup(0, 0, WIDTH, HEIGHT))
void DispUpdateSetup(int x, int y, int w, int h);

// Display update - send frame buffer to the display
void DispUpdate();

#ifdef __cplusplus
}
#endif

#endif // _TWEETYBOY_DISP_H

#endif // USE_DISP
