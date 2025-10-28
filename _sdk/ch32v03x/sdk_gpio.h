
// ****************************************************************************
//
//                                GPIO pins
//
// ****************************************************************************

#ifndef _SDK_GPIO_H
#define _SDK_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

// GPIO pin mode
#define GPIO_MODE_AIN		0x00	// analog input mode (ADC; read input data register will always be 0)
#define GPIO_MODE_IN		0x04	// floating input mode (no pulls)
#define GPIO_MODE_IN_PD		0x28	// input with pull down (set output register to 0)
#define GPIO_MODE_IN_PU		0x48	// input with pull up (set output register to 1)
#define GPIO_MODE_OUT		(0+1)	// push-pull output
#define GPIO_MODE_AF		(8+1)	// alternate function output (I2C automatic open drain)

#define GPIO_MODE_OUT_SLOW	GPIO_MODE_OUT
#define GPIO_MODE_OUT_FAST	GPIO_MODE_OUT
#define GPIO_MODE_AF_SLOW	GPIO_MODE_AF
#define GPIO_MODE_AF_FAST	GPIO_MODE_AF
#define GPIO_MODE_AFOD		GPIO_MODE_AF

// GPIO port
typedef struct {
	io32	CFGLR;		// 0x00: configuration register low
	io32	CFGHR;		// 0x04: configuration register high
	io32	INDR;		// 0x08: input data register (8 or 16 pins)
	io32	OUTDR;		// 0x0C: output data register (8 or 16 pins; for pull inputs: 0=pull down, 1=pull up)
	io32	BSHR;		// 0x10: bit set/reset output data register (low 16 bits: set bit, high 16 bits: clear bit)
	io32	BCR;		// 0x14: bit clear output data register (low 16 bits: clear bit)
	io32	LCKR;		// 0x18: configuration lock register (high 16 bits to lock: write 1, write 0, write 1, read 0, read 1)
	io32	CFGXR;		// 0x1C: configuration register expansion
	io32	BSXR;		// 0x20: set/reset register high 16 bits
} GPIO_t;
STATIC_ASSERT(sizeof(GPIO_t) == 0x24, "Incorrect GPIO_t!");

// Alternate function registers
typedef struct {
	io32	res1;		// 0x00: ... reserved
	io32	PCFR1;		// 0x04: Remap register 1
	io32	EXTICR[2];	// 0x08: External interrupt configuration register
	io32	res2;		// 0x10 ... reserved
	io32	res3;		// 0x14 ... reserved
	io32	CTLR;		// 0x18: Control register
} AFIO_t;
STATIC_ASSERT(sizeof(AFIO_t) == 0x1C, "Incorrect AFIO_t!");

#define GPIOA			((GPIO_t*)GPIOA_BASE)	// PA port 0x40010800
#define GPIOB			((GPIO_t*)GPIOB_BASE)	// PB port 0x40010C00
#define GPIOC			((GPIO_t*)GPIOC_BASE)	// PC port 0x40011000
#define AFIO			((AFIO_t*)AFIO_BASE)	// alternative function select 0x40010000

// PC16/UDM and PC17/UDP pull-up mode
#define GPIO_UDMPULL_OFF	0	// UDM pull-up disabled
#define GPIO_UDMPULL_35		1	// UDM pull-up 35us (used with GPIO)
#define GPIO_UDMPULL_10K	2	// UDM pull-up 10Kohm (with VDD=5V)
#define GPIO_UDMPULL_1K5	3	// UDM pull-up 1.5Kohm (with VDD=3.3V)

// get port index from GPIO index
INLINE int GPIO_PortInx(int gpio) { return GPIO_PORTINX(gpio); }

// get port base from GPIO index
#define GPIO_PORT(gpio) ((GPIO_t*)(GPIO_PORTINX(gpio)*(GPIOB_BASE-GPIOA_BASE)+GPIOA_BASE))
INLINE GPIO_t* GPIO_Port(int gpio) { return GPIO_PORT(gpio); }

// get port pin from GPIO index
INLINE int GPIO_Pin(int gpio) { return GPIO_PIN(gpio); }

// compose GPIO index
//  port ... port index PORT*_INX
//  pin ... port pin 0..
INLINE int GPIO_Gpio(int port, int pin) { return GPIO_GPIO(port, pin); }

// get input bit from GPIO input port (returns 0 or 1; port = GPIOA..., pin = 0.., gpio = PA0...)
INLINE u8 GPIOx_In(GPIO_t* port, int pin) { return (port->INDR >> pin) & 1; }
INLINE u8 GPIOA_In(int pin) { return GPIOx_In(GPIOA, pin); }
INLINE u8 GPIOB_In(int pin) { return GPIOx_In(GPIOB, pin); }
INLINE u8 GPIOC_In(int pin) { return GPIOx_In(GPIOC, pin); }
INLINE u8 GPIO_In(int gpio) { return GPIOx_In(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// get all input bits from GPIO input port (returns input bits; port = GPIOA..., gpio = PA0...)
INLINE u32 GPIOx_InAll(GPIO_t* port) { return port->INDR; }
INLINE u32 GPIOA_InAll(void) { return GPIOx_InAll(GPIOA); }
INLINE u32 GPIOB_InAll(void) { return GPIOx_InAll(GPIOB); }
INLINE u32 GPIOC_InAll(void) { return GPIOx_InAll(GPIOC); }
INLINE u32 GPIO_InAll(int gpio) { return GPIOx_InAll(GPIO_PORT(gpio)); }

// get output from GPIO output port  (returns 0 or 1; port = GPIOA..., pin = 0.., gpio = PA0...)
INLINE u8 GPIOx_GetOut(GPIO_t* port, int pin) { return (port->OUTDR >> pin) & 1; }
INLINE u8 GPIOA_GetOut(int pin) { return GPIOx_GetOut(GPIOA, pin); }
INLINE u8 GPIOB_GetOut(int pin) { return GPIOx_GetOut(GPIOB, pin); }
INLINE u8 GPIOC_GetOut(int pin) { return GPIOx_GetOut(GPIOC, pin); }
INLINE u8 GPIO_GetOut(int gpio) { return GPIOx_GetOut(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// get all output bits from GPIO output port (returns output bits; port = GPIOA..., gpio = PA0...)
INLINE u32 GPIOx_GetOutAll(GPIO_t* port) { return port->OUTDR; }
INLINE u32 GPIOA_GetOutAll(void) { return GPIOx_GetOutAll(GPIOA); }
INLINE u32 GPIOB_GetOutAll(void) { return GPIOx_GetOutAll(GPIOB); }
INLINE u32 GPIOC_GetOutAll(void) { return GPIOx_GetOutAll(GPIOC); }
INLINE u32 GPIO_GetOutAll(int gpio) { return GPIOx_GetOutAll(GPIO_PORT(gpio)); }

// output 0 to GPIO output pin (port = GPIOA..., pin = 0.., gpio = PA0...)
//  In GPIO_MODE_IN_* modes this selects pull-down mode.
INLINE void GPIOx_Out0(GPIO_t* port, int pin) { port->BCR = BIT(pin); }
INLINE void GPIOA_Out0(int pin) { GPIOx_Out0(GPIOA, pin); }
INLINE void GPIOB_Out0(int pin) { GPIOx_Out0(GPIOB, pin); }
INLINE void GPIOC_Out0(int pin) { GPIOx_Out0(GPIOC, pin); }
INLINE void GPIO_Out0(int gpio) { GPIOx_Out0(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// output 1 to GPIO output pin (port = GPIOA..., pin = 0.., gpio = PA0...)
//  In GPIO_MODE_IN_* modes this selects pull-up mode.
INLINE void GPIOx_Out1(GPIO_t* port, int pin) { io32* reg = &port->BSHR;
	if (pin >= 16) { pin -= 16; reg = &port->BSXR; } *reg = BIT(pin); }
INLINE void GPIOA_Out1(int pin) { GPIOx_Out1(GPIOA, pin); }
INLINE void GPIOB_Out1(int pin) { GPIOx_Out1(GPIOB, pin); }
INLINE void GPIOC_Out1(int pin) { GPIOx_Out1(GPIOC, pin); }
INLINE void GPIO_Out1(int gpio) { GPIOx_Out1(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// output value to GPIO output pin (val = 0 or <>0; port = GPIOA..., pin = 0.., gpio = PA0...)
//  In GPIO_MODE_IN_* modes 0 selects pull-down mode, <>0 selects pull-up mode.
void GPIOx_Out(GPIO_t* port, int pin, int val);
INLINE void GPIOA_Out(int pin, int val) { GPIOx_Out(GPIOA, pin, val); }
INLINE void GPIOB_Out(int pin, int val) { GPIOx_Out(GPIOB, pin, val); }
INLINE void GPIOC_Out(int pin, int val) { GPIOx_Out(GPIOC, pin, val); }
INLINE void GPIO_Out(int gpio, int val) { GPIOx_Out(GPIO_PORT(gpio), GPIO_PIN(gpio), val); }
INLINE void GPIOx_OutFast(GPIO_t* port, int pin, int val)
{
	if (pin >= 16)
	{
		if (val != 0) pin -= 16;
		port->BSXR = BIT(pin);
	}
	else
	{
		if (val == 0) pin += 16;
		port->BSHR = BIT(pin);
	}
}

// flip GPIO output pin (port = GPIOA..., pin = 0.., gpio = PA0...)
void GPIOx_Flip(GPIO_t* port, int pin);
INLINE void GPIOA_Flip(int pin) { GPIOx_Flip(GPIOA, pin); }
INLINE void GPIOB_Flip(int pin) { GPIOx_Flip(GPIOB, pin); }
INLINE void GPIOC_Flip(int pin) { GPIOx_Flip(GPIOC, pin); }
INLINE void GPIO_Flip(int gpio) { GPIOx_Flip(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// output all output pins to GPIO output port (port = GPIOA..., gpio = PA0...)
INLINE void GPIOx_OutAll(GPIO_t* port, int value) { port->OUTDR = value; }
INLINE void GPIOA_OutAll(int value) { GPIOx_OutAll(GPIOA, value); }
INLINE void GPIOB_OutAll(int value) { GPIOx_OutAll(GPIOB, value); }
INLINE void GPIOC_OutAll(int value) { GPIOx_OutAll(GPIOC, value); }
INLINE void GPIO_OutAll(int gpio, int value) { GPIOx_OutAll(GPIO_PORT(gpio), value); }

// lock GPIO pin (pin configuration cannot be changed until next reset MCU or reset port; gpio = PA0...)
void GPIO_Lock(int gpio);

// set GPIO pin mode (gpio = PA0..., mode = GPIO_MODE_*)
//  For GPIO_MODE_IN_* modes, the output register will be set accordingly.
void GPIO_Mode(int gpio, int mode);

// get current GPIO pin mode (returns GPIO_MODE_*; gpio = PA0...)
int GPIO_GetMode(int gpio);

// setup external interrupt input pin
//  port ... source port (PORTA_INX,...)
//  pin ... source pin/interrupt pin (0..23)
// - Determines which port pin the external interrupt pin is mapped to.
void GPIO_EXTILine(int port, int pin);

// Remap alternate function with 1 bit, register 1 (pos = bit position, map = remapping index)
INLINE void GPIO_Remap1_1b(int pos, int map) { AFIO->PCFR1 = (AFIO->PCFR1 & ~(1 << pos)) | (map << pos); }

// Remap alternate function with 2 bits, register 1 (pos = bit position, map = remapping index)
INLINE void GPIO_Remap1_2b(int pos, int map) { AFIO->PCFR1 = (AFIO->PCFR1 & ~(3 << pos)) | (map << pos); }

// Remap alternate function with 3 bits, register 1 (pos = bit position, map = remapping index)
INLINE void GPIO_Remap1_3b(int pos, int map) { AFIO->PCFR1 = (AFIO->PCFR1 & ~(7 << pos)) | (map << pos); }

// Remap SPI1 (default 0)
//	0 ... PA4:CS, PA5:SCK, PA6:MISO, PA7:MOSI
//	1 ... PB21:CS, PB15:SCK, PA8:MISO, PA9:MOSI
//	2 ... PA12:CS, PA11:SCK, PA9:MISO, PA10:MOSI
//	3 ... PC4:CS, PC5:SCK, PC6:MISO, PC7:MOSI
INLINE void GPIO_Remap_SPI1(int map) { GPIO_Remap1_2b(0, map); }

// Remap I2C1 (default 0)
//	0 ... PA10:SCL, PA11:SDA
//	1 ... PA13:SCL, PA14:SDA
//	2 ... PC16:SCL, PC17:SDA
//	3 ... PC19:SCL, PC18:SDA
//	4,6 ... PC17:SCL, PC16:SDA
//	5,7 ... PC18:SCL, PC19:SDA
INLINE void GPIO_Remap_I2C1(int map) { GPIO_Remap1_3b(2, map); }

// Remap USART1 (default 0)
//	0 ... PB10:TX, PB11:RX, PB9:CLK, PC16:CTS, PC17:RTS
//	1 ... PA10:TX, PA11:RX, PB9:CLK, PC16:CTS, PC17:RTS
//	2 ... PB10:TX, PB11:RX, PB5:CLK, PA9:CTS, PA8:RTS
//	3 ... PA7:TX, PB2:RX, PB12:CLK, PA13:CTS, PA14:RTS
INLINE void GPIO_Remap_USART1(int map) { GPIO_Remap1_2b(5, map); }

// Remap USART2 (default 0)
//	0 ... PA2:TX, PA3:RX, PA4:CLK, PA0:CTS, PA1:RTS
//	1 ... PA20:TX, PA19:RX, PA23:CLK, PA1:CTS, PA2:RTS
//	2 ... PA15:TX, PA16:RX, PA22:CLK, PA17:CTS, PA21:RTS
//	3 ... PC0:TX, PC1:RX, PB20:CLK, PC2:CTS, PC3:RTS
//	4-7 ... PA15:TX, PA16:RX, PA22:CLK, PA17:CTS, PC3:RTS
INLINE void GPIO_Remap_USART2(int map) { GPIO_Remap1_3b(7, map); }

// Remap USART3 (default 0)
//	0 ... PB3:TX, PB4:RX, PB5:CLK, PB6:CTS, PB7:RTS
//	1 ... PC18:TX, PC19:RX, PB5:CLK, PB6:CTS, PB7:RTS
//	2 ... PA18:TX, PB14:RX, PB8:CLK, PA3:CTS, PA4:RTS
//	3 ... PB16:TX, PB17:RX, (none CLK), PB18:CTS, PB19:RTS
INLINE void GPIO_Remap_USART3(int map) { GPIO_Remap1_2b(10, map); }

// Remap USART4 (default 0)
//	0 ... PB0:TX, PB1:RX, PB2:CLK, PB15:CTS, PA8:RTS
//	1 ... PA5:TX, PA9:RX, PA6:CLK, PA7:CTS, PB21:RTS
//	2 ... PC16:TX, PC17:RX, PB2:CLK, PB15:CTS, PA8:RTS
//	3 ... PB9:TX, PA10:RX, PB8:CLK, PA14:CTS, PA13:RTS
//	4,6 ... PB13:TX, PC19:RX, PA8:CLK, PA5:CTS, PA6:RTS
//	5,7 ... PC17:TX, PC16:RX, PB2:CLK, PB15:CTS, PA8:RTS
INLINE void GPIO_Remap_USART4(int map) { GPIO_Remap1_3b(12, map); }

// Remap Timer 1 (default 0)
//	0 ... PC17:ETR, PB9:CH1, PB10:CH2, PB11:CH3, PC16:CH4, PB5:BKIN, PB6:CH1N, PB7:CH2N, PB8:CH3N
//	1 ... PC17:ETR, PB9:CH1, PB10:CH2, PB11:CH3, PC16:CH4, PA6:BKIN, PA7:CH1N, PB0:CH2N, PB1:CH3N
//	2 ... PC18:ETR, PB9:CH1, PB10:CH2, PB11:CH3, PB12:CH4, PB5:BKIN, PB6:CH1N, PB7:CH2N, PB8:CH3N
//	3 ... PC18:ETR, PC0:CH1, PC1:CH2, PC2:CH3, PC3:CH4, PC4:BKIN, PC5:CH1N, PC6:CH2N, PC7:CH3N
//	4-7 ... PC15:ETR, PC14:CH3
INLINE void GPIO_Remap_TIM1(int map) { GPIO_Remap1_3b(15, map); }

// Remap Timer 2 (default 0)
//	0 ... PA19:ETR, PA0:CH1, PA1:CH2, PA2:CH3, PA3:CH4, PA20:BKIN, PA21:CH1N, PA22:CH2N, PA23:CH3N
//	1 ... PA18:ETR, PB21:CH1, PB15:CH2, PA2:CH3, PA3:CH4, PA9:BKIN, PA12:CH1N, PA13:CH2N, PA14:CH3N
//	2 ... PA19:ETR, PA0:CH1, PA1:CH2, PB3:CH3, PB4:CH4, PA20:BKIN, PC3:CH1N, PA22:CH2N, PA23:CH3N
//	3 ... PA18:ETR, PB21:CH1, PB15:CH2, PB3:CH3, PB4:CH4, PA9:BKIN, PA12:CH1N, PA13:CH2N, PA14:CH3N
//	4 ... PC4:ETR, PB16:CH1, PB17:CH2, PB18:CH3, PB19:CH4, PC0:BKIN, PC1:CH1N, PC2:CH2N, PC3:CH3N
//	5 ... PA2:ETR, PC19:CH1, PA12:CH2, PA13:CH3, PC0:CH4, PB4:BKIN, PC18:CH1N, PB12:CH2N, PB3:CH3N
//	6,7 ... PA2:ETR, PC19:CH1, PC14:CH2, PC15:CH3, PC0:CH4, PB4:BKIN, PB11:CH1N, PB12:CH2N, PB3:CH3N
INLINE void GPIO_Remap_TIM2(int map) { GPIO_Remap1_3b(18, map); }

// Remap Timer 3 (default 0)
//	0 ... PA6:CH1, PA7:CH2
//	1 ... PB4:CH1, PB5:CH2
//	2 ... PC19:CH1, PC18:CH2
//	3 ... PA3:CH1, PA4:CH2
INLINE void GPIO_Remap_TIM3(int map) { GPIO_Remap1_2b(21, map); }

// Remap PIOC interface 0/1 (default 0)
//	0 ... PC18:[0], PC19:[1]
//	1 ... PC7:[0], PC19:[1]
INLINE void GPIO_Remap_PIOC(int map) { GPIO_Remap1_1b(23, map); }

// Remap SWD debug interface (default 0)
// 	0-3 ... SWD (SDI) enabled
//	4 ... SWD (SDI) disable, pin served as GPIO
// Note: Before switching the SWD pin to GPIO, insert a short delay
// from system startup to allow the chip to be reprogrammed later.
INLINE void GPIO_Remap_SWD(int map) { GPIO_Remap1_3b(24, map); }

// --- USB Control

// Setup pull-up mode for PC16/UDM pins GPIO_UDMPULL_* (default GPIO_UDMPULL_35)
INLINE void GPIO_UDMPull(int pull) { AFIO->CTLR = (AFIO->CTLR & ~3) | pull; }

// Setup pull-up mode for PC17/UDP pins GPIO_UDMPULL_* (default GPIO_UDMPULL_35)
INLINE void GPIO_UDPPull(int pull) { AFIO->CTLR = (AFIO->CTLR & ~(3 << 2)) | (pull << 2); }

// Set USB transceiver PHY output limit to VDD (used with VDD voltage 3.3V; default)
INLINE void GPIO_USBPHYVDD(void) { AFIO->CTLR |= B6; }

// Set USB transceiver PHY output limit to 3.3V (used with VDD voltage 5V)
INLINE void GPIO_USBPHY3V3(void) { AFIO->CTLR &= ~B6; }

// Enable/Disable USB IO multiplexing (see RM manual how to setup PC16 and PC17)
INLINE void GPIO_USBIOEnable(void) { AFIO->CTLR |= B7; }
INLINE void GPIO_USBIODisable(void) { AFIO->CTLR &= ~B7; }

// Set USB PD transceiver PHY output limit to VDD (used with VDD voltage 3.3V; default)
INLINE void GPIO_USBPDPHYVDD(void) { AFIO->CTLR |= B8; }

// Set USB PD transceiver PHY output limit to 3.3V (used with VDD voltage 5V)
INLINE void GPIO_USBPDPHY3V3(void) { AFIO->CTLR &= ~B8; }

// Set USB PD pin PC14/PC15 threshold input mode HIGH/LOW
INLINE void GPIO_USBPDInH(void) { AFIO->CTLR |= B9; }
INLINE void GPIO_USBPDInL(void) { AFIO->CTLR &= ~B9; }

// Reset pin to default state (pin must not be locked; does not reset mappings)
void GPIO_PinReset(int gpio);

// Reset GPIO port to default state (use port index PORT*_INX, does not disable clock)
void GPIO_PortReset(int portinx);

// Reset all GPIO ports and all mappings to default state (does not disable clock)
void GPIO_AllReset(void);

#ifdef __cplusplus
}
#endif

#endif // _SDK_GPIO_H
