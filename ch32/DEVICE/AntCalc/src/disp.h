
// ****************************************************************************
//
//                           AntCalc - Display
//
// ****************************************************************************
// OLED I2C 0.96" SSD1306 display blue+yellow, resolution 128x64 pixels, controller SSD1306, power 3 to 5V.
// https://www.hadex.cz/m508c-displej-oled-096-128x64-znaku-iici2c-4piny-modrozluty/

#ifdef __cplusplus
extern "C" {
#endif

#define DISP_I2C_ADDR	0x3C	// display I2C address
#define DISP_SDA_GPIO	PC1	// display gpio with SDA
#define DISP_SCL_GPIO	PC2	// display gpio with SCL
#define DISP_I2C_MAP	0	// hardware display driver: I2C mapping
#define DISP_WAIT_CLK	5	// software display driver: number of I2C wait clock (0 or more) ... DispUpdate() takes 2:10ms, 3-4:11ms, 10:26 ms
#define DISP_SPEED_HZ	750000	// hardware display driver: I2C speed in Hz ... DispUpdate() takes 3M:4ms, 2M:6ms, 1M:11ms, 500K:20ms
#define USE_DISP	1	// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver

#define DISP_SDA_PORT	GPIO_PORT(DISP_SDA_GPIO)	// display port with SDA
#define DISP_SCL_PORT	GPIO_PORT(DISP_SCL_GPIO)	// display port with SCL
#define DISP_SDA_PIN	GPIO_PIN(DISP_SDA_GPIO)		// display pin with SDA
#define DISP_SCL_PIN	GPIO_PIN(DISP_SCL_GPIO)		// display pin with SCL

#define WIDTH		128		// width in pixels
#define HEIGHT		64		// height in graphics lines
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 16)
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 16*64 = 1024 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 16)

#define THEIGHT		16		// height of top part of the display
#define BHEIGHT		(HEIGHT-THEIGHT) // height of bottom part of the display (= 48) ... to display 4 rows (X, Y, Z, T), we need 12-line font

extern u8 FrameBuf[FRAMESIZE];		// display graphics buffer

// Display initialize
void DispInit(void);

// Display terminate
void DispTerm(void);

// Display update - send frame buffer to the display
void DispUpdate();

#ifdef __cplusplus
}
#endif
