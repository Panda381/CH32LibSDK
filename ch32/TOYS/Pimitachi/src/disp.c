
// ****************************************************************************
//
//                                 Display
//
// ****************************************************************************

#include "../include.h"

// ports
#define DISP_SDA_PORT	GPIO_PORT(DISP_SDA_GPIO)	// display port with SDA
#define DISP_SCL_PORT	GPIO_PORT(DISP_SCL_GPIO)	// display port with SCL
#define DISP_SDA_PIN	GPIO_PIN(DISP_SDA_GPIO)		// display pin with SDA
#define DISP_SCL_PIN	GPIO_PIN(DISP_SCL_GPIO)		// display pin with SCL

// fast set mode of SDA pin
#define DISP_I2C_SDA_MODE(mode) DISP_SDA_PORT->CFGLR = (DISP_SDA_PORT->CFGLR & ~(0x0f << (DISP_SDA_PIN*4))) | (mode << (DISP_SDA_PIN*4))

// GPIO manipulation
#define DISP_SCL_HIGH()		GPIOx_Out1(DISP_SCL_PORT, DISP_SCL_PIN)	// set SCL to HIGH
#define DISP_SCL_LOW()		GPIOx_Out0(DISP_SCL_PORT, DISP_SCL_PIN)	// set SCL to LOW
#define DISP_SDA_HIGH()		GPIOx_Out1(DISP_SDA_PORT, DISP_SDA_PIN)	// set SDA to HIGH
#define DISP_SDA_LOW()		GPIOx_Out0(DISP_SDA_PORT, DISP_SDA_PIN)	// set SDA to LOW
#define DISP_SDA_INPUT()	DISP_I2C_SDA_MODE(8);			// set SDA to input mode with pulls (to simulate open-drain)
#define DISP_SDA_OUTPUT()	DISP_I2C_SDA_MODE(1);			// set SDA to ouput mode
#define DISP_SDA_OUTDATA(val)	GPIOx_OutFast(DISP_SDA_PORT, DISP_SDA_PIN, (val)) // output SDA data

// clock delay (it has also compiler barrier effect)
#define DISP_CLK_WAIT()		{ nop(); nop(); nop(); }

// SSD1306 init data
const u8 DispI2C_InitData[DISP_INITDATA_NUM] = {
	DISP_I2C_ADDR << 1,	// SSD1306 slave address with write bit (0)
	0x00,			// control byte to indicate commands
// Commands:
	0xAE,			// display OFF (go to sleep mode)
	0xD5, 0x80,		// set clock:
				//	bit 0..3: divide ratio to D+1 (default 0)
				//	bit 4..7: set oscillator frequency F (default 8)
	0xA8, 63,		// set multiplexing to N+1 (N=63, 64 lines for 128x64, default value)
				//	N=15 to 63, means multiplexing 16 to 64 (values 0 to 14 are invalid)
	0xD3, 0,		// set vertical shift by COM from 0..63 (default 0)
	0x40,			// set display RAM start line (0x40..0x7F sets RAM start line to 0..63, default 0x40 = line 0)
	0x8D, 0x14,		// activate internal charge pump
	0xA0, //0xA1,		// set segment mapping (horizontal orientation)
				//	0xA0: column address 0 is mapped to SEG0 (default)
				// 	0xA1: column address 127 is mapped to SEG0
	0xC0, //0xC8,		// reverse the scanning direction of COM lines (vertical orientation)
				//	0xC0: scan from COM0 to COMN (default)
				//	0xC8: scan from COMN to COM0
	0xDA, 0x12,		// configure COM pins for a 128x64 screen
				//	bit 4: 1=alternative COM pin configuration (default 1)
				//	bit 5: 1=enable COM left/right remap (default 0)
	0x81, 8, 		// set screen contrast (set 1 to 256, default value is 127)
				//	Console consumption dependence on display contrast:
				//	display in sleep mode ..... 0.0mA
				//	0 ......................... 0.5mA (display is black)
				//	1 ......................... 2.4mA
				//	16 ........................ 2.5mA
				//	32 ........................ 2.6mA
				//	64 ........................ 3.0mA
				//	127 ....................... 4.0mA
				//	192 ....................... 4.5mA
				//	255 ....................... 5.0mA
	0xD9, 0xF1,		// define the preload period:
				//	bit 0..3: phase 1 period 1..15 (default 2)
				//	bit 4..7: phase 2 period 1..15 (default 2)
	0xDB, 0x40,		// set VCOMH voltage
				//	0x00 = 0.65*Vcc
				//	0x20 = 0.77*Vcc (default)
				//	0x30 = 0x83*Vcc
	0x20, 0,		// set memory addressing mode
				//	0 = horizontal addressing mode
				//	1 = vertical addressing mode
				//	2 = page addressing mode (default state)
	0xAF,			// display ON
				//	0xAF = display ON in normal mode
				//	0xA7 = display ON with inverse
};
STATIC_ASSERT(sizeof(DispI2C_InitData) == DISP_INITDATA_NUM, "Incorrect DISP_INITDATA_NUM!");

#if !USE_DISP_ASM		// 1=use ASM in Disp module

// start I2C communication (on start, SDA and SCL must be high)
void DispI2C_Start(void)
{
	// start condition: SDA goes low while SCL is high
	cb();
	DISP_SDA_LOW();
	DISP_CLK_WAIT();
	DISP_SCL_LOW();
	DISP_CLK_WAIT();
}

// stop I2C communication
void DispI2C_Stop(void)
{
	// stop condition: SDA goes high while SCL is high
	cb();
	DISP_SCL_HIGH();
	DISP_CLK_WAIT();
	DISP_SDA_HIGH();
	DISP_CLK_WAIT();
}

// write a byte over I2C
void DispI2C_Write(u8 data)
{
	// send 8 bits
	int i;
	for (i = 8; i > 0; i--)
	{
		cb();
		DISP_SCL_LOW(); cb();		// set SCL low, to prepare next data
		DISP_SDA_OUTDATA(data & B7);	// set SDA data bit
		DISP_CLK_WAIT();		// delay
		DISP_SCL_HIGH();		// set SCL high to confirm valid data bit
		DISP_CLK_WAIT();		// delay
		data <<= 1;			// prepare next data bit
	}

	// handle ACK
	cb();
	DISP_SCL_LOW(); cb();	// set SCL low, to prepare next data
	DISP_SDA_HIGH(); cb();	// set SDA high, to release open-drain SDA line
	DISP_SDA_INPUT();	// set SDA to input, to simulate open-drain HIGH to read ACK
	DISP_CLK_WAIT();	// delay
	DISP_SCL_HIGH();	// set SCL high to confirm valid ACK data bit
	DISP_CLK_WAIT();	// delay
	DISP_SCL_LOW();		// set SCL low, to end ACK bit
	DISP_CLK_WAIT();	// delay
	DISP_SDA_LOW(); cb();	// set SDA back to low state
	DISP_SDA_OUTPUT(); cb(); // reconfigure SDA back to output mode 
}

// Display select SSD1306 page 0..7, start transfer data
void DispI2C_SelectPage(int page)
{
	// select page
	DispI2C_Start();			// start I2C communication
	DispI2C_Write(DISP_I2C_ADDR << 1);	// send I2C address
	DispI2C_Write(0);			// control byte for command
	DispI2C_Write(0xb0 | (page & 7));	// select page
	DispI2C_Write(0x00);			// set lower nibble of column start address to 0
	DispI2C_Write(0x10);			// set higher nibble of column start address to 0
	DispI2C_Stop();				// stop transfer

	// start transfer data
	DispI2C_Start();			// start I2C communication
	DispI2C_Write(DISP_I2C_ADDR << 1);	// send I2C address
	DispI2C_Write(0x40);			// control byte to start transfer data
}

// send command to the display
void DispCmd(u8 cmd)
{
	DispI2C_Start();			// start I2C communication
	DispI2C_Write(DISP_I2C_ADDR << 1);	// SSD1306 slave address with write bit (0)
	DispI2C_Write(0x00);			// control byte to indicate commands
	DispI2C_Write(cmd);			// send command
	DispI2C_Stop();				// stop transfer
}

// display ON
void DispOn(void)
{
	DispCmd(0xAF);			// display ON in normal mode
}

// display OFF
void DispOff(void)
{
	DispCmd(0xAE);			// display OFF (go to sleep mode)
}

// Display update - send frame buffer to the display
void DispUpdate()
{
	int x, y, m, j;
	for (y = 0; y < 8; y++)
	{
		DispI2C_SelectPage(y);			// select page
		const u8* s = &FrameBuf[y*8*WIDTHBYTE];
		for (x = 0; x < 16; x++)
		{
			for (m = 0x80; m != 0; m >>= 1)
			{
				int b = 0;
				for (j = 8; j > 0; j--)
				{
					b >>= 1;
					if ((*s & m) != 0) b |= B7;
					s += WIDTHBYTE;
				}
				s -= 8*WIDTHBYTE;
				DispI2C_Write(b);
			}
			s++;
		}
		DispI2C_Stop();				// stop transfer
	}
}

// Display initialize (port clock must be enabled)
void DispInit(void)
{
	// initialize pins to HIGH output
	DispI2C_Stop();				// set SDA and SCL pins to HIGH
	GPIO_Mode(DISP_SDA_GPIO, GPIO_MODE_OUT); // set SDA output mode
	GPIO_Mode(DISP_SCL_GPIO, GPIO_MODE_OUT); // set SCL output mode

	// wait to stabilize power supply of OLED, minimum 5ms
	WaitMs(10);

	// OLED configuration
	DispI2C_Start();			// start I2C communication
	int i;
	for (i = 0; i < count_of(DispI2C_InitData); i++) DispI2C_Write(DispI2C_InitData[i]);
	DispI2C_Stop();				// stop transfer

	// short delay to guarantee initialization
	WaitMs(2);
}

#endif // !USE_DISP_ASM
