
// ****************************************************************************
//
//                        BeatleBoyPad - Display driver
//
// ****************************************************************************

#include "../../includes.h"

#if USE_DISP		// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver

#if DISP_DBLBUF		// 1=use VGA display double buffer (FrameBuf+DispBuf)
u8 DispBuf[FRAMESIZE];		// display graphics buffer
#endif
u8 FrameBuf[FRAMESIZE];		// display graphics buffer
volatile u32 DispLine;		// current display line
volatile u32 DispFrame = 0;	// current frame
volatile u8* FrameBufAddr;	// current pointer to graphics buffer
volatile u32 DispTimTest;	// test - get TIM-CNT value at start of image
u8 DispOutPage = 0;	// current output page (0..7)
u8 DispOutX = 0;	// current output X (0..127)

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

// Memory mapping:
//  vertical pages PAGE0..PAGE7, every page is 8 lines height (COM0..COM7)
//  PAGE0, PAGE1,... PAGE7 = COM0-COM7, COM8-COM15,... COM56-COM63 = row remapping COM63-COM56, COM55-COM48,... COM7-COM0
//  horizontal segments SEG0..SET127, column remappuing SEG127..SEG0
//  Every data byte contains 8 vertical pixels of one segment on one page

// SSD1306 init data
const u8 DispI2C_InitData[] = {
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
	0x81, 32, 		// set screen contrast (set 1 to 256, default value is 127)
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

// wait for VSync scanline
void WaitVSync()
{
	if (RunMode == RUNMODE_VGA) // device run mode RUNMODE_* (0=OLED, 1=VGA)
	{
		while (DispIsVSync()) {}
		while (!DispIsVSync()) {}
	}
}

// start I2C communication (on start, SDA and SCL must be high)
void DispI2C_Start(void)
{
	if (RunMode == RUNMODE_OLED) // device run mode RUNMODE_* (0=OLED, 1=VGA)
	{
#if USE_DISP == 1	// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver
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
}

// stop I2C communication
void DispI2C_Stop(void)
{
	if (RunMode == RUNMODE_OLED) // device run mode RUNMODE_* (0=OLED, 1=VGA)
	{
#if USE_DISP == 1	// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver
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
}

// write a byte over I2C, internal
static void _DispI2C_Write(u8 data)
{
#if USE_DISP == 1	// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver
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
	if (RunMode == RUNMODE_OLED) // device run mode RUNMODE_* (0=OLED, 1=VGA)
	{
		// send data
		_DispI2C_Write(data);
	}
	else
	{
		int y = DispOutPage;
		int x = DispOutX;

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
			DispOutPage++;
		}

		DispOutX = x;
	}
}

// Display select SSD1306 page 0..7, start transfer data, internal
static void _DispI2C_SelectPage(int page)
{
	if (RunMode == RUNMODE_OLED) // device run mode RUNMODE_* (0=OLED, 1=VGA)
	{
#if USE_DISP == 1	// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver
// Software driver:

		// select page
		DispI2C_Start();			// start I2C communication
		_DispI2C_Write(DISP_I2C_ADDR << 1);	// send I2C address
		_DispI2C_Write(0);			// control byte for command
		_DispI2C_Write(0xb0 | (page & 7));	// select page
		_DispI2C_Write(0x00);			// set lower nibble of column start address to 0
		_DispI2C_Write(0x10);			// set higher nibble of column start address to 0
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
		I2C1_WriteWait(0x00);			// set lower nibble of column start address to 0
		I2C1_WriteWait(0x10);			// set higher nibble of column start address to 0
		I2C1_StopEnable();			// stop transfer

		// start transfer data
		I2C1_SendAddr(DISP_I2C_ADDR, I2C_DIR_WRITE); // send address, write mode
		I2C1_WriteWait(0x40);			// control byte to start transfer data

#endif
	}
	else
	{
		DispOutPage = page;
		DispOutX = 0;
	}
}

// Display select SSD1306 page 0..7, start transfer data, with screen shot
void DispI2C_SelectPage(int page)
{
	_DispI2C_SelectPage(page);
}

// Display initialize (port clock must be enabled)
void DispInit(void)
{
	if (RunMode == RUNMODE_VGA) // device run mode RUNMODE_* (0=OLED, 1=VGA)
	{
		DispLine = 0;			// current display line
#if DISP_DBLBUF		// 1=use VGA display double buffer (FrameBuf+DispBuf)
		FrameBufAddr = DispBuf;	// current pointer to graphics buffer
#else
		FrameBufAddr = FrameBuf;	// current pointer to graphics buffer
#endif

		// initialize GPIO pins (note: clocks are setup at config.h)
		RCC_AFIClkEnable();
		RCC_PAClkEnable();
		RCC_PCClkEnable();
		RCC_PDClkEnable();

		// - PC2 VSYNC, GPIO push-pull output, fast speed
		GPIO_Mode(PC2, GPIO_MODE_OUT_FAST);
		// - PC1 HSYNC, TIM2 channel 1 output
		GPIO_Mode(PC1, GPIO_MODE_AF_FAST);

#if CH32V003
		GPIO_Mode(PA1, GPIO_MODE_OUT_FAST);
#else // CH32V003
		// SPI setup
		RCC_SPI1ClkEnable();		// enable SPI1 clock
		RCC_SPI1Reset();		// reset SPI1 to default state
		SPI1_Baud(SPI_HDIV);		// horizontal divider
		SPI1_Data8();			// select 8-bit mode
		SPI1_MSB();			// transmit MSB (bit 7 first)
		SPI1_NSSSw();			// control NSS by software
		SPI1_NSSHigh();			// need set NSS to HIGH to enable master output
		SPI1_SSDisable();		// disable SS output
		SPI1_Bidi1();			// set 1-line bidirectional mode
		SPI1_TxBidi();			// transmit only
		SPI1_Master();			// master mode
		SPI1_Enable();			// enable SPI

		// 4 ... PD3:CS, PD4:SCK, PD5:MISO, PD6:MOSI
		GPIO_Remap_SPI1(4);		// remap MOSI to PD6
		GPIO_Mode(PD6, GPIO_MODE_AF_FAST);
#endif

		// Remap Timer 2 - mapping (output channel 1 to PC1)
#if CH32V003
		// 2 ... PC1:CH1/ETR, PD3:CH2, PC0:CH3, PD7:CH4
		GPIO_Remap_TIM2(2);
#else
		// 3 ... PC1:CH1/ETR, PC7:CH2, PD6:CH3/CH1N, PD5:CH4/CH2N
		GPIO_Remap_TIM2(3);
#endif

		// Setup Timer 2 channel 1 for HSYNC signal
		//  System frequency 24 MHz
		//  H whole line: 31.77756 us = 763 clock cycles
		//  H active: 25.42205 us = 610 clock cycles
		//  H front porch: 0.63555 us = 15 clock cycles
		//  HSYNC: 3.81331 us = 92 clock cycles
		//  H back porch: 1.90665 us = 46 clock cycles
		//  Image start at 5.71996 us (= HSYNC + back porch) = 137 clock cycles
		//     short line 128 pixels (512 clock cycles) starts at: 137 + 49 = 186 clock cycles
// void TIM2_InitPWM(int chan, int div, int reload, int comp, Bool high);
//   chan ... channel 1..4
//   div ... divider 1..65536
//   reload ... reload value 0..65535 (timer period = reload+1)
//   comp ... compare value 0..reload
//   high ... direction HIGH->LOW (or LOW->HIGH otherwise)
		TIM2_InitPWM(1, 1, 763-1, 92, False);

		// Setup interrupt on Timer 2 channel 2 to display image
		//  128x64: 4 clock cycles per pixel, 32 clock cycles per character, active 16 characters
#if CH32V003
		TIM2_Comp2(137+49-8 - 63);	// set compare value (image should start at 178 clock cycles)
#else
		TIM2_Comp2(137+49 - 63);	// set compare value (image should start at 186 clock cycles)
#endif
		TIM2_OC2Mode(TIM_COMP_FREEZE);	// set compare mode
		TIM2_OC2PreEnable();		// enable preload compare register
		TIM2_CC2Enable();		// enable compare output
		TIM2_CC2IntClr();		// clear interrupt request
		TIM2_CC2IntEnable();		// enable capture compare of channel 2
	}
	else
	{
#if USE_DISP == 1	// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver
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

		// setup interrupt on Timer 2
		TIM2_InitInt(1, 800-1);
	}
	NVIC_IRQEnable(IRQ_TIM2);	// enable interrupt service
}

// Display terminate
void DispTerm(void)
{
	NVIC_IRQDisable(IRQ_TIM2);	// disable interrupt service

	if (RunMode == RUNMODE_VGA) // device run mode RUNMODE_* (0=OLED, 1=VGA)
	{
		// disable capture compare interrupt (channel 2)
		TIM2_CC2IntDisable();		// disable capture compare of channel 2
		TIM2_CC2Disable();		// disable compare output
		TIM2_CC2IntClr();		// enable capture compare of channel 2

		// disable timer
		TIM2_Disable();

		// Reset timer to default setup
		TIM2_Reset();

		// reset SPI
		RCC_SPI1Reset();		// reset SPI1 to default state

		// reset GPIO pins
		GPIO_PinReset(PC1);
		GPIO_PinReset(PC2);
		GPIO_PinReset(PD6);
	}
	else
	{
		GPIO_PinReset(DISP_SDA_GPIO);
		GPIO_PinReset(DISP_SCL_GPIO);

		// disable timer
		TIM2_Disable();

		// Reset timer to default setup
		TIM2_Reset();

#if USE_DISP == 2	// 1=use software I2C display driver, 2=use hardware I2C display driver, 0=no display driver
		// reset I2C
		I2C1_Reset();
#endif
	}
}

// Display update - send frame buffer to the display (takes 15 ms)
void DispUpdate()
{
	if (RunMode == RUNMODE_OLED) // device run mode RUNMODE_* (0=OLED, 1=VGA)
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
	else
	{
#if DISP_DBLBUF		// 1=use VGA display double buffer (FrameBuf+DispBuf)
		memcpy(DispBuf, FrameBuf, FRAMESIZE);
#endif
	}
}

#endif // USE_DISP
