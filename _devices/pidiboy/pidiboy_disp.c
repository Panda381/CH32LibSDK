
// ****************************************************************************
//
//                        PidiBoy - Display driver
//
// ****************************************************************************

#include "../../includes.h"

#if USE_DISP		// 1=use software display driver, 2=use hardware display driver (0=no driver)

u8 FrameBuf[FRAMESIZE];		// display graphics buffer

#if USE_SCREENSHOT		// 1=use screen shot
u8 SS_DispOutPage = 0;	// current output page (0..7)
u8 SS_DispOutX = 0;	// current output X (0..127)
#endif

// fast set mode of SDA pin
#if DISP_SDA_PIN < 8
#define DISP_I2C_SDA_MODE(mode) DISP_SDA_PORT->CFGLR = (DISP_SDA_PORT->CFGLR & ~(0x0f << (DISP_SDA_PIN*4))) | (mode << (DISP_SDA_PIN*4))
#elif DISP_SDA_PIN < 16
#define DISP_I2C_SDA_MODE(mode) DISP_SDA_PORT->CFGHR = (DISP_SDA_PORT->CFGHR & ~(0x0f << ((DISP_SDA_PIN-8)*4))) | (mode << ((DISP_SDA_PIN-8)*4))
#else
#define DISP_I2C_SDA_MODE(mode) DISP_SDA_PORT->CFGXR = (DISP_SDA_PORT->CFGXR & ~(0x0f << ((DISP_SDA_PIN-16)*4))) | (mode << ((DISP_SDA_PIN-16)*4))
#endif

// GPIO manipulation
#define DISP_SCL_HIGH()		GPIOx_Out1(DISP_SCL_PORT, DISP_SCL_PIN)	// set SCL to HIGH
#define DISP_SCL_LOW()		GPIOx_Out0(DISP_SCL_PORT, DISP_SCL_PIN)	// set SCL to LOW
#define DISP_SDA_HIGH()		GPIOx_Out1(DISP_SDA_PORT, DISP_SDA_PIN)	// set SDA to HIGH
#define DISP_SDA_LOW()		GPIOx_Out0(DISP_SDA_PORT, DISP_SDA_PIN)	// set SDA to LOW
#define DISP_SDA_INPUT()	DISP_I2C_SDA_MODE(8);			// set SDA to input mode with pulls (to simulate open-drain)
#define DISP_SDA_OUTPUT()	DISP_I2C_SDA_MODE(1);			// set SDA to ouput mode
#define DISP_SDA_OUTDATA(val)	GPIOx_OutFast(DISP_SDA_PORT, DISP_SDA_PIN, (val)) // output SDA data

// clock delay (it has also compiler barrier effect)
#if DISP_WAIT_CLK <= 0
#define DISP_CLK_WAIT()		cb()
#elif DISP_WAIT_CLK == 1
#define DISP_CLK_WAIT()		nop()
#elif DISP_WAIT_CLK == 2
#define DISP_CLK_WAIT()		{ nop(); nop(); }
#elif DISP_WAIT_CLK == 3
#define DISP_CLK_WAIT()		{ nop(); nop(); nop(); }
#elif DISP_WAIT_CLK == 4
#define DISP_CLK_WAIT()		{ nop(); nop(); nop(); nop(); }
#elif DISP_WAIT_CLK == 5
#define DISP_CLK_WAIT()		{ nop(); nop(); nop(); nop(); nop(); }
#elif DISP_WAIT_CLK == 6
#define DISP_CLK_WAIT()		{ nop(); nop(); nop(); nop(); nop(); nop(); }
#else
#define DISP_CLK_WAIT()		WaitClk(DISP_WAIT_CLK)
#endif

// SSD1306 init data
const u8 DispI2C_InitData[] = {
	DISP_I2C_ADDR << 1,	// SSD1306 slave address with write bit (0)
	0x00,			// control byte to indicate commands
	0xAE,			// display off
	0xD5, 0x80,		// set clock divide ratio
	0xA8, 0x3F,		// set multiplexing to 64 lines (for 128x64)
	0xD3, 0x00,		// set display offset to 0
	0x40,			// set starting line to 0
	0x8D, 0x14,		// activate internal charge pump
	0xA1,			// invert segment mapping (orientation)
	0xC8,			// reverse the scanning direction of COM lines
	0xDA, 0x12,		// configure COM pins for a 128x64 screen
	0x81, 0xCF,		// set screen contrast
	0xD9, 0xF1,		// define the preload period
	0xDB, 0x40,		// set VCOMH voltage
	0x20, 0x00,		// set the memory mode to horizontal
	0xAF,			// display on
};

// start I2C communication (on start, SDA and SCL must be high)
void DispI2C_Start(void)
{
#if USE_DISP == 1	// 1=use software display driver, 2=use hardware display driver (0=no driver)
// Software driver:

	// start condition: SDA goes low while SCL is high
	cb();
	DISP_SDA_LOW();
	DISP_CLK_WAIT();
	DISP_SCL_LOW();
	DISP_CLK_WAIT();

#else
// Hardware driver:

	// sent start bit, start master mode
	I2C1_StartEnable();

	// wait start bit sent
	while (!I2C1_StartSent()) {}

#endif
}

// stop I2C communication
void DispI2C_Stop(void)
{
#if USE_DISP == 1	// 1=use software display driver, 2=use hardware display driver (0=no driver)
// Software driver:

	// stop condition: SDA goes high while SCL is high
	cb();
	DISP_SCL_HIGH();
	DISP_CLK_WAIT();
	DISP_SDA_HIGH();
	DISP_CLK_WAIT();

#else
// Hardware driver:

	// sent stop bit
	I2C1_StopEnable();

#endif
}

// write a byte over I2C, internal
static void _DispI2C_Write(u8 data)
{
#if USE_DISP == 1	// 1=use software display driver, 2=use hardware display driver (0=no driver)
// Software driver:

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

#else
// Hardware driver:

	// write data byte
	I2C1_WriteWait(data);

#endif
}

// write a byte over I2C, with screenshot
void DispI2C_Write(u8 data)
{
	// screen shot
#if USE_SCREENSHOT		// 1=use screen shot
	{
		int y = SS_DispOutPage;
		int x = SS_DispOutX;
		if ((x < 128) && (y < 8))
		{
			u8* d = &FrameBuf[(x >> 3) + y*(WIDTHBYTE*8)];
			u8 mask = 1 << (7 - (x & 7));
			if ((data & B0) == 0) d[0*WIDTHBYTE] &= ~mask; else d[0*WIDTHBYTE] |= mask;
			if ((data & B1) == 0) d[1*WIDTHBYTE] &= ~mask; else d[1*WIDTHBYTE] |= mask;
			if ((data & B2) == 0) d[2*WIDTHBYTE] &= ~mask; else d[2*WIDTHBYTE] |= mask;
			if ((data & B3) == 0) d[3*WIDTHBYTE] &= ~mask; else d[3*WIDTHBYTE] |= mask;
			if ((data & B4) == 0) d[4*WIDTHBYTE] &= ~mask; else d[4*WIDTHBYTE] |= mask;
			if ((data & B5) == 0) d[5*WIDTHBYTE] &= ~mask; else d[5*WIDTHBYTE] |= mask;
			if ((data & B6) == 0) d[6*WIDTHBYTE] &= ~mask; else d[6*WIDTHBYTE] |= mask;
			if ((data & B7) == 0) d[7*WIDTHBYTE] &= ~mask; else d[7*WIDTHBYTE] |= mask;
			x++;
			if (x >= 128)
			{
				x = 0;
				SS_DispOutPage++;
			}
			SS_DispOutX = x;
		}
	}
#endif
	// send data
	_DispI2C_Write(data);
}

// Display select SSD1306 page 0..7, start transfer data, internal
static void _DispI2C_SelectPage(int page)
{
#if USE_DISP == 1	// 1=use software display driver, 2=use hardware display driver (0=no driver)
// Software driver:

	// select page
	DispI2C_Start();			// start I2C communication
	_DispI2C_Write(DISP_I2C_ADDR << 1);	// send I2C address
	_DispI2C_Write(0);			// control byte for command
	_DispI2C_Write(0xb0 | (page & 7));	// select page
	_DispI2C_Write(0x00);			// set low column to 0
	_DispI2C_Write(0x10);			// set high column to 0
	DispI2C_Stop();				// stop transfer

	// start transfer data
	DispI2C_Start();			// start I2C communication
	_DispI2C_Write(DISP_I2C_ADDR << 1);	// send I2C address
	_DispI2C_Write(0x40);			// control byte to start transfer data

#else
// Hardware driver:

	// select page
	I2C1_SendAddr(DISP_I2C_ADDR, I2C_DIR_WRITE); // send address, write mode
	I2C1_WriteWait(0);			// control byte for command
	I2C1_WriteWait(0xb0 | (page & 7));	// select page
	I2C1_WriteWait(0x00);			// set low column to 0
	I2C1_WriteWait(0x10);			// set high column to 0
	I2C1_StopEnable();			// stop transfer

	// start transfer data
	I2C1_SendAddr(DISP_I2C_ADDR, I2C_DIR_WRITE); // send address, write mode
	I2C1_WriteWait(0x40);			// control byte to start transfer data

#endif
}

// Display select SSD1306 page 0..7, start transfer data, with screen shot
void DispI2C_SelectPage(int page)
{
#if USE_SCREENSHOT		// 1=use screen shot
	SS_DispOutPage = page;
	SS_DispOutX = 0;
#endif

	_DispI2C_SelectPage(page);
}

// Display initialize (port clock must be enabled)
void DispInit(void)
{
#if USE_DISP == 1	// 1=use software display driver, 2=use hardware display driver (0=no driver)
// Software driver:

	// initialize pins to HIGH output
	GPIO_Out1(DISP_SDA_GPIO);
	GPIO_Out1(DISP_SCL_GPIO);
	GPIO_Mode(DISP_SDA_GPIO, GPIO_MODE_OUT);
	GPIO_Mode(DISP_SCL_GPIO, GPIO_MODE_OUT);

	// wait to stabilize power supply of OLED, minimum 5ms
	WaitMs(10);

	// OLED configuration
	DispI2C_Start();			// start I2C communication
	int i;
	for (i = 0; i < count_of(DispI2C_InitData); i++) _DispI2C_Write(DispI2C_InitData[i]);
	DispI2C_Stop();				// stop transfer

#else
// Hardware driver:

	// I2C clock enable
	RCC_I2C1ClkEnable();

	// reset I2C
	I2C1_Reset();

	// setup I2C mapping
	GPIO_Remap_I2C1(DISP_I2C_MAP);

	// initialize pins
	GPIO_Mode(DISP_SDA_GPIO, GPIO_MODE_AFOD);
	GPIO_Mode(DISP_SCL_GPIO, GPIO_MODE_AFOD);

	// Initialize I2C interface
	I2C1_Init(DISP_I2C_ADDR, DISP_SPEED_HZ);

	// wait to stabilize power supply of OLED, minimum 5ms
	WaitMs(10);

	// OLED configuration
	I2C1_SendAddr(DISP_I2C_ADDR, I2C_DIR_WRITE); // send address, write mode
	I2C1_SendData(DispI2C_InitData + 1, count_of(DispI2C_InitData) - 1); // send data, without address
	I2C1_StopEnable();			// stop transfer

#endif

	// short delay to guarantee initialization
	WaitMs(2);
}

// Display terminate
void DispTerm(void)
{
	GPIO_PinReset(DISP_SDA_GPIO);
	GPIO_PinReset(DISP_SCL_GPIO);

#if USE_DISP == 2	// 1=use software display driver, 2=use hardware display driver (0=no driver)

	// reset I2C
	I2C1_Reset();

#endif
}

// Display update - send frame buffer to the display (takes 15 ms)
void DispUpdate()
{
	int x, y, m;
	for (y = 0; y < 8; y++)
	{
		_DispI2C_SelectPage(y);			// select page
		const u8* s = &FrameBuf[y*8*WIDTHBYTE];
		for (x = 0; x < 16; x++)
		{
			for (m = 0x80; m != 0; m >>= 1)
			{
				u8 b = 0;
				if ((s[0*WIDTHBYTE] & m) != 0) b |= B0;
				if ((s[1*WIDTHBYTE] & m) != 0) b |= B1;
				if ((s[2*WIDTHBYTE] & m) != 0) b |= B2;
				if ((s[3*WIDTHBYTE] & m) != 0) b |= B3;
				if ((s[4*WIDTHBYTE] & m) != 0) b |= B4;
				if ((s[5*WIDTHBYTE] & m) != 0) b |= B5;
				if ((s[6*WIDTHBYTE] & m) != 0) b |= B6;
				if ((s[7*WIDTHBYTE] & m) != 0) b |= B7;
				_DispI2C_Write(b);
			}
			s++;
		}
		DispI2C_Stop();				// stop transfer
	}
}

#endif // USE_DISP
