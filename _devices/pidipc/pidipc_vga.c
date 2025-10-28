
// ****************************************************************************
//
//                        PidiPC - VGA display driver
//
// ****************************************************************************

#include "../../includes.h"

#if USE_DISP		// 1=use display support

u8 FrameBuf[FRAMESIZE];		// display graphics buffer
u8 AttrBuf[ATTRSIZE];		// display attribute buffer (color of 2 pixels: 1st pixels in bits 1..3, 2nd pixel in bits 5..7)
volatile u8* AttrBufAddr = AttrBuf; // current pointer to attribute buffer
#if VMODE == 7
u8 FontBuf[2048];		// bont buffer 8x8
#endif
volatile int DispLine;		// current display line
volatile u32 DispFrame;		// current frame
volatile u8* FrameBufAddr = FrameBuf;	// current pointer to graphics buffer
volatile u32 DispTimTest;	// test - get TIM-CNT value at start of image
#if VMODE == 5
u32 DispMaxLine = 384;		// index of last scanline
#endif

// wait for VSync scanline
void WaitVSync()
{
	while (DispIsVSync()) {}
	while (!DispIsVSync()) {}
}

// Initialize videomode
void DispInit()
{
	// switch PC5 to GPIO mode, if not already set
	if (((OB->USER >> 3) & 3) != 3)
	{
		OB_t ob;
		Flash_OBRead(&ob);	// read option bytes
		ob.USER |= B3|B4;	// disable RESET function
		Flash_OBWrite(&ob);	// write new option bytes
	}

#if VMODE == 7
	// copy font to font buffer
	memcpy(FontBuf, FONT, 2048);
#endif

	DispLine = 0;			// current display line
	AttrBufAddr = AttrBuf;		// current pointer to attribute buffer
	FrameBufAddr = FrameBuf;	// current pointer to graphics buffer

	// trim HSI oscillator to 25MHz
	RCC_HSITrim(31);

	// initialize GPIO pins (note: clocks are setup at config.h)
	// - PC0 video out, GPIO push-pull output, fast speed
	RCC_AFIClkEnable();
	RCC_PBClkEnable();
	RCC_PCClkEnable();

	GPIO_Mode(PB0, GPIO_MODE_OD_FAST);	// blue
	GPIO_Mode(PB1, GPIO_MODE_OD_FAST);	// red
	GPIO_Mode(PB3, GPIO_MODE_OD_FAST);	// green
	// - PC4 VSYNC, GPIO push-pull output, fast speed
	GPIO_Mode(PC4, GPIO_MODE_OUT_FAST);
	// - PC5 HSYNC, TIM2 channel 1 output
	GPIO_Mode(PC5, GPIO_MODE_AF_FAST);

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
	// 3 ... PB0:CS, PB1:SCK, PB2:MISO, PC0:MOSI
	GPIO_Remap_SPI1(3);		// remap MOSI to PC0
	GPIO_Mode(PC0, GPIO_MODE_AF_FAST);

	// Remap Timer 2 - mapping 2 (output CH1 to PC5)
	// 2 ... PC5:CH1/ETR, PC2:CH2, PD2:CH3/CH1N, PC1:CH4/CH2N
	GPIO_Remap_TIM2(2);

	// Setup Timer 2 for HSYNC signal:
	//  System frequency 50 MHz
	//  Total period 31.77756 us = 1600 clock cycles
	//  Sync 3.81331 us = 192 clock cycles
	//  Image start at 5.71996 us (= HSYNC + back porch) = 288 clock cycles (visible area is 1280 clock cycles)
// void TIM2_InitPWM(int chan, int div, int reload, int comp, Bool high);
//   chan ... channel 1..4
//   div ... divider 1..65536
//   reload ... reload value 0..65535 (timer period = reload+1)
//   comp ... compare value 0..reload
//   high ... direction HIGH->LOW (or LOW->HIGH otherwise)
	TIM2_InitPWM(1, 1, 1600-1, 192, False);

	// Setup interrupt on Timer 2 channel 3 to display image
	//  160x120: 8 clock cycles per pixel, 64 clock cycles per character
	//  256x192: 4 clock cycles per pixel, 32 clock cycles per character.
	//		Image starts 32 pixels later = add 128 clock cycles.
	//		In vertical direction, 384 scanlines is active area, add 48 scanlines to front and back porch.
	//  320x240: 4 clock cycles per pixel, 32 clock cycles per character
	//  128x64: 8 clock cycles per pixel 64 clock cycles per character
	//		Image starts 16 pixels later = add 128 clock cycles.
	//		In vertical direction, 256 scanlines is active area, add 112 scanlines to front and back porch.

// Do not change this compare value! If you change it, you must correct "time synchronization" in vga_asm.S.
#if VMODE == 1
	TIM2_Comp3(288+128 - 135);	// set compare value
#elif VMODE == 2
	TIM2_Comp3(288 - 130);		// set compare value
#elif VMODE == 3
	TIM2_Comp3(288 - 130);		// set compare value
#elif VMODE == 4
	TIM2_Comp3(288+128 - 96); 	// set compare value
#elif VMODE == 5
	TIM2_Comp3(288+128 - 102); 	// set compare value
#elif VMODE == 6
	TIM2_Comp3(288 - 105);		// set compare value
#elif VMODE == 7
	TIM2_Comp3(288 - 84);		// set compare value
#endif
	TIM2_OC3Mode(TIM_COMP_FREEZE);	// set compare mode
	TIM2_OC3PreEnable();		// enable preload compare register
//	TIM2_CC3Enable();		// enable compare output ... do not use, PD2 us used by PORT
	TIM2_CC3IntClr();		// clear interrupt request
	TIM2_CC3IntEnable();		// enable capture compare of channel 3
	NVIC_IRQEnable(IRQ_TIM2);	// enable interrupt service
}

// Terminate videomode
void DispTerm()
{
	// disable capture compare interrupt
	NVIC_IRQDisable(IRQ_TIM2);	// disable interrupt service
	TIM2_CC3IntDisable();		// disable capture compare of channel 3
	TIM2_CC3Disable();		// disable compare output
	TIM2_CC3IntClr();		// enable capture compare of channel 3

	// disable timer
	TIM2_Disable();

	// Reset timer to default setup
	TIM2_Reset();

	// reset SPI
	RCC_SPI1Reset();		// reset SPI1 to default state

	// reset GPIO pint
	GPIO_PinReset(PB0);		// blue
	GPIO_PinReset(PB1);		// red
	GPIO_PinReset(PB3);		// green
	GPIO_PinReset(PC4);
	GPIO_PinReset(PC5);

	// reset HSI trim to default value 24 MHz
	RCC_HSITrim(16);
}

#endif // USE_DISP
