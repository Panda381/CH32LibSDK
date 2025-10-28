
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

#define GPIO_MODE_OUT		(0+1)	// push-pull output, medium speed (10 MHz)
#define GPIO_MODE_OUT_SLOW	(0+2)	// push-pull output, slow speed (2 MHz)
#define GPIO_MODE_OUT_FAST	(0+3)	// push-pull output, fast speed (50 MHz)

#define GPIO_MODE_OD		(4+1)	// open-drain output, medium speed (10 MHz)
#define GPIO_MODE_OD_SLOW	(4+2)	// open-drain output, slow speed (2 MHz)
#define GPIO_MODE_OD_FAST	(4+3)	// open-drain output, fast speed (50 MHz)

#define GPIO_MODE_AF		(8+1)	// alternate function output, medium speed (10 MHz)
#define GPIO_MODE_AF_SLOW	(8+2)	// alternate function output, slow speed (2 MHz)
#define GPIO_MODE_AF_FAST	(8+3)	// alternate function output, fast speed (50 MHz)

#define GPIO_MODE_AFOD		(12+1)	// alternate function open-drain output, medium speed (10 MHz)
#define GPIO_MODE_AFOD_SLOW	(12+2)	// alternate function open-drain output, slow speed (2 MHz)
#define GPIO_MODE_AFOD_FAST	(12+3)	// alternate function open-drain output, fast speed (50 MHz)

// GPIO port
typedef struct {
	io32	CFGLR;		// 0x00: configuration register low
	io32	CFGHR;		// 0x04: configuration register high
	io32	INDR;		// 0x08: input data register (8 or 16 pins)
	io32	OUTDR;		// 0x0C: output data register (8 or 16 pins; for pull inputs: 0=pull down, 1=pull up)
	io32	BSHR;		// 0x10: bit set/reset output data register (low 16 bits: set bit, high 16 bits: clear bit)
	io32	BCR;		// 0x14: bit clear output data register (low 16 bits: clear bit)
	io32	LCKR;		// 0x18: configuration lock register (high 16 bits to lock: write 1, write 0, write 1, read 0, read 1)
} GPIO_t;
STATIC_ASSERT(sizeof(GPIO_t) == 0x1C, "Incorrect GPIO_t!");

// Alternate function registers
typedef struct {
	io32	ECR;		// 0x00: Event control register
	io32	PCFR1;		// 0x04: Remap register 1
	io32	EXTICR[4];	// 0x08: External interrupt configuration register
	io32	res;		// 0x18: ...reserved
	io32	PCFR2;		// 0x1C: Remap register 2
} AFIO_t;
STATIC_ASSERT(sizeof(AFIO_t) == 0x20, "Incorrect AFIO_t!");

#define GPIOA			((GPIO_t*)GPIOA_BASE)	// PA port 0x40010800
#define GPIOB			((GPIO_t*)GPIOB_BASE)	// PC port 0x40010C00
#define GPIOC			((GPIO_t*)GPIOC_BASE)	// PC port 0x40011000
#define GPIOD			((GPIO_t*)GPIOD_BASE)	// PD port 0x40011400
#define GPIOE			((GPIO_t*)GPIOE_BASE)	// PE port 0x40011800
#define AFIO			((AFIO_t*)AFIO_BASE)	// alternative function select 0x40010000

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
INLINE u8 GPIOD_In(int pin) { return GPIOx_In(GPIOD, pin); }
INLINE u8 GPIOE_In(int pin) { return GPIOx_In(GPIOE, pin); }
INLINE u8 GPIO_In(int gpio) { return GPIOx_In(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// get all input bits from GPIO input port (returns input bits; port = GPIOA..., gpio = PA0...)
INLINE u16 GPIOx_InAll(GPIO_t* port) { return (u16)port->INDR; }
INLINE u16 GPIOA_InAll(void) { return GPIOx_InAll(GPIOA); }
INLINE u16 GPIOB_InAll(void) { return GPIOx_InAll(GPIOB); }
INLINE u16 GPIOC_InAll(void) { return GPIOx_InAll(GPIOC); }
INLINE u16 GPIOD_InAll(void) { return GPIOx_InAll(GPIOD); }
INLINE u16 GPIOE_InAll(void) { return GPIOx_InAll(GPIOE); }
INLINE u16 GPIO_InAll(int gpio) { return GPIOx_InAll(GPIO_PORT(gpio)); }

// get output from GPIO output port  (returns 0 or 1; port = GPIOA..., pin = 0.., gpio = PA0...)
INLINE u8 GPIOx_GetOut(GPIO_t* port, int pin) { return (port->OUTDR >> pin) & 1; }
INLINE u8 GPIOA_GetOut(int pin) { return GPIOx_GetOut(GPIOA, pin); }
INLINE u8 GPIOB_GetOut(int pin) { return GPIOx_GetOut(GPIOB, pin); }
INLINE u8 GPIOC_GetOut(int pin) { return GPIOx_GetOut(GPIOC, pin); }
INLINE u8 GPIOD_GetOut(int pin) { return GPIOx_GetOut(GPIOD, pin); }
INLINE u8 GPIOE_GetOut(int pin) { return GPIOx_GetOut(GPIOE, pin); }
INLINE u8 GPIO_GetOut(int gpio) { return GPIOx_GetOut(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// get all output bits from GPIO output port (returns output bits; port = GPIOA..., gpio = PA0...)
INLINE u16 GPIOx_GetOutAll(GPIO_t* port) { return (u16)port->OUTDR; }
INLINE u16 GPIOA_GetOutAll(void) { return GPIOx_GetOutAll(GPIOA); }
INLINE u16 GPIOB_GetOutAll(void) { return GPIOx_GetOutAll(GPIOB); }
INLINE u16 GPIOC_GetOutAll(void) { return GPIOx_GetOutAll(GPIOC); }
INLINE u16 GPIOD_GetOutAll(void) { return GPIOx_GetOutAll(GPIOD); }
INLINE u16 GPIOE_GetOutAll(void) { return GPIOx_GetOutAll(GPIOE); }
INLINE u16 GPIO_GetOutAll(int gpio) { return GPIOx_GetOutAll(GPIO_PORT(gpio)); }

// output 0 to GPIO output pin (port = GPIOA..., pin = 0.., gpio = PA0...)
//  In GPIO_MODE_IN_* modes this selects pull-down mode.
INLINE void GPIOx_Out0(GPIO_t* port, int pin) { port->BCR = BIT(pin); }
INLINE void GPIOA_Out0(int pin) { GPIOx_Out0(GPIOA, pin); }
INLINE void GPIOB_Out0(int pin) { GPIOx_Out0(GPIOB, pin); }
INLINE void GPIOC_Out0(int pin) { GPIOx_Out0(GPIOC, pin); }
INLINE void GPIOD_Out0(int pin) { GPIOx_Out0(GPIOD, pin); }
INLINE void GPIOE_Out0(int pin) { GPIOx_Out0(GPIOE, pin); }
INLINE void GPIO_Out0(int gpio) { GPIOx_Out0(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// output 1 to GPIO output pin (port = GPIOA..., pin = 0.., gpio = PA0...)
//  In GPIO_MODE_IN_* modes this selects pull-up mode.
INLINE void GPIOx_Out1(GPIO_t* port, int pin) { port->BSHR = BIT(pin); }
INLINE void GPIOA_Out1(int pin) { GPIOx_Out1(GPIOA, pin); }
INLINE void GPIOB_Out1(int pin) { GPIOx_Out1(GPIOB, pin); }
INLINE void GPIOC_Out1(int pin) { GPIOx_Out1(GPIOC, pin); }
INLINE void GPIOD_Out1(int pin) { GPIOx_Out1(GPIOD, pin); }
INLINE void GPIOE_Out1(int pin) { GPIOx_Out1(GPIOE, pin); }
INLINE void GPIO_Out1(int gpio) { GPIOx_Out1(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// output value to GPIO output pin (val = 0 or <>0; port = GPIOA..., pin = 0.., gpio = PA0...)
//  In GPIO_MODE_IN_* modes 0 selects pull-down mode, <>0 selects pull-up mode.
INLINE void GPIOx_Out(GPIO_t* port, int pin, int val) { pin = BIT(pin);
	if (val == 0) pin <<= 16; port->BSHR = pin; }
INLINE void GPIOA_Out(int pin, int val) { GPIOx_Out(GPIOA, pin, val); }
INLINE void GPIOB_Out(int pin, int val) { GPIOx_Out(GPIOB, pin, val); }
INLINE void GPIOC_Out(int pin, int val) { GPIOx_Out(GPIOC, pin, val); }
INLINE void GPIOD_Out(int pin, int val) { GPIOx_Out(GPIOD, pin, val); }
INLINE void GPIOE_Out(int pin, int val) { GPIOx_Out(GPIOE, pin, val); }
INLINE void GPIO_Out(int gpio, int val) { GPIOx_Out(GPIO_PORT(gpio), GPIO_PIN(gpio), val); }

// flip GPIO output pin (port = GPIOA..., pin = 0.., gpio = PA0...)
INLINE void GPIOx_Flip(GPIO_t* port, int pin) { pin = BIT(pin);
	if ((port->OUTDR & pin) != 0) pin <<= 16; port->BSHR = pin; }
INLINE void GPIOA_Flip(int pin) { GPIOx_Flip(GPIOA, pin); }
INLINE void GPIOB_Flip(int pin) { GPIOx_Flip(GPIOB, pin); }
INLINE void GPIOC_Flip(int pin) { GPIOx_Flip(GPIOC, pin); }
INLINE void GPIOD_Flip(int pin) { GPIOx_Flip(GPIOD, pin); }
INLINE void GPIOE_Flip(int pin) { GPIOx_Flip(GPIOE, pin); }
INLINE void GPIO_Flip(int gpio) { GPIOx_Flip(GPIO_PORT(gpio), GPIO_PIN(gpio)); }

// output all output pins to GPIO output port (port = GPIOA..., gpio = PA0...)
INLINE void GPIOx_OutAll(GPIO_t* port, int value) { port->OUTDR = value; }
INLINE void GPIOA_OutAll(int value) { GPIOx_OutAll(GPIOA, value); }
INLINE void GPIOB_OutAll(int value) { GPIOx_OutAll(GPIOB, value); }
INLINE void GPIOC_OutAll(int value) { GPIOx_OutAll(GPIOC, value); }
INLINE void GPIOD_OutAll(int value) { GPIOx_OutAll(GPIOD, value); }
INLINE void GPIOE_OutAll(int value) { GPIOx_OutAll(GPIOE, value); }
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
//  pin ... source pin/interrupt pin (0..15)
// - Determines which port pin the external interrupt pin is mapped to.
void GPIO_EXTILine(int port, int pin);

// setup EVENTOUT pin (gpio = PA0...)
INLINE void GPIO_EventOut(int gpio) { AFIO->ECR = gpio | (AFIO->ECR & 0xFFFFFF80); }

// enable EVENTOUT 
INLINE void GPIO_EventOn(void) { AFIO->ECR |= B7; }

// disable EVENTOUT 
INLINE void GPIO_EventOff(void) { AFIO->ECR &= ~B7; }

// Remap alternate function with 1 bit, register 1 (pos = bit position, map = remapping index)
INLINE void GPIO_Remap1_1b(int pos, int map) { AFIO->PCFR1 = (AFIO->PCFR1 & ~(1 << pos)) | (map << pos); }

// Remap alternate function with 2 bits, register 1 (pos = bit position, map = remapping index)
INLINE void GPIO_Remap1_2b(int pos, int map) { AFIO->PCFR1 = (AFIO->PCFR1 & ~(3 << pos)) | (map << pos); }

// Remap alternate function with 3 bits, register 1 (pos = bit position, map = remapping index)
INLINE void GPIO_Remap1_3b(int pos, int map) { AFIO->PCFR1 = (AFIO->PCFR1 & ~(7 << pos)) | (map << pos); }

// Remap alternate function with 4 bits, register 1 (pos = bit position, map = remapping index)
INLINE void GPIO_Remap1_4b(int pos, int map) { AFIO->PCFR1 = (AFIO->PCFR1 & ~(0x0f << pos)) | (map << pos); }

// Remap alternate function with 1 bit, register 2 (pos = bit position, map = remapping index)
INLINE void GPIO_Remap2_1b(int pos, int map) { AFIO->PCFR2 = (AFIO->PCFR2 & ~(1 << pos)) | (map << pos); }

// Remap alternate function with 2 bits, register 2 (pos = bit position, map = remapping index)
INLINE void GPIO_Remap2_2b(int pos, int map) { AFIO->PCFR2 = (AFIO->PCFR2 & ~(3 << pos)) | (map << pos); }

// Remap SPI1 (default 0)
//	0 ... PA4:CS, PA5:SCK, PA6:MISO, PA7:MOSI
//	1 ... PA15:CS, PB3:SCK, PB4:MISO, PB5:MOSI
INLINE void GPIO_Remap_SPI1(int map) { GPIO_Remap1_1b(0, map); }

// Remap SPI3 (default 0)
//	0 ... PA15:CS, PB3:SCK, PB4:MISO, PB5:MOSI
//	1 ... PA4:CS, PC10:SCK, PC11:MISO, PC12:MOSI
INLINE void GPIO_Remap_SPI3(int map) { GPIO_Remap1_1b(28, map); }

// Remap I2C1 (default 0)
//	0 ... PB6:SCL, PB7:SDA
//	1 ... PB8:SCL, PB9:SDA
INLINE void GPIO_Remap_I2C1(int map) { GPIO_Remap1_1b(1, map); }

// Remap USART1 (default 0)
//	0 ... PA9:TX, PA10:RX, PA8:CLK, PA11:CTS, PA12:RTS
//	1 ... PB6:TX, PB7:RX, PA8:CLK, PA11:CTS, PA12:RTS
//	2 ... PB15:TX, PA8:RX, PA10:CLK, PA5:CTS, PA9:RTS
//	3 ... PA6:TX, PA7:RX, PA5:CLK, PC4:CTS, PC5:RTS
INLINE void GPIO_Remap_USART1(int map) { GPIO_Remap1_1b(2, map & B0); GPIO_Remap2_1b(26, map >> 1); }

// Remap USART2 (default 0)
//	0 ... PA2:TX, PA3:RX, PA4:CLK, PA0:CTS, PA1:RTS
//	1 ... PD5:TX, PD6:RX, PD7:CLK, PD3:CTS, PD4:RTS
INLINE void GPIO_Remap_USART2(int map) { GPIO_Remap1_1b(3, map); }

// Remap USART3 (default 0)
//	0 ... PB10:TX, PB11:RX, PB12:CLK, PB13:CTS, PB14:RTS
//	1 ... PC10:TX, PC11:RX, PC12:CLK, PB13:CTS, PB14:RTS
//	2 ... PA13:TX, PA14:RX, PD10:CLK, PD11:CTS, PD12:RTS
//		The "2" remapping is not supported for lot numbers where
//		the fifth digit of the lot number is less than 2 and the
//		penultimate sixth digit of the lot number is 0.
//	3 ... PD8:TX, PD9:RX, PD10:CLK, PD11:CTS, PD12:RTS
INLINE void GPIO_Remap_USART3(int map) { GPIO_Remap1_2b(4, map); }

// Remap USART4 (default 0)
//	0 ... PC10:TX, PC11:RX
//	1 ... PB0:TX, PB1:RX
//	2,3 ... PE0:TX, PE1:RX
//  CH32V203 with 64 pins:
//	0, 2 ... PB0:TX, PB1:RX, PB2:CLK, PB3:CTS, PB4:RTS
//	1, 3 ... PA5:TX, PB5:RX, PA6:CLK, PA7:CTS, PA15:RTS
INLINE void GPIO_Remap_USART4(int map) { GPIO_Remap2_2b(16, map); }

// Remap USART5 (default 0)
//	0 ... PC12:TX, PD2:RX
//	1 ... PB4:TX, PB5:RX
//	2,3 ... PE8:TX, PE9:RX
INLINE void GPIO_Remap_USART5(int map) { GPIO_Remap2_2b(18, map); }

// Remap USART6 (default 0)
//	0 ... PC0:TX, PC1:RX
//	1 ... PB8:TX, PB9:RX
//	2,3 ... PE10:TX, PE11:RX
INLINE void GPIO_Remap_USART6(int map) { GPIO_Remap2_2b(20, map); }

// Remap USART7 (default 0)
//	0 ... PC2:TX, PC3:RX
//	1 ... PA6:TX, PA7:RX
//	2,3 ... PE12:TX, PE13:RX
INLINE void GPIO_Remap_USART7(int map) { GPIO_Remap2_2b(22, map); }

// Remap USART8 (default 0)
//	0 ... PC4:TX, PC5:RX
//	1 ... PA14:TX, PA15:RX
//	2,3 ... PE14:TX, PE15:RX
INLINE void GPIO_Remap_USART8(int map) { GPIO_Remap2_2b(24, map); }

// Remap Timer 1 (default 0)
//	0 ... PA12:ETR, PA8:CH1, PA9:CH2, PA10:CH3, PA11:CH4, PB12:BKIN, PB13:CH1N, PB14:CH2N, PB15:CH3N
//	1 ... PA12:ETR, PA8:CH1, PA9:CH2, PA10:CH3, PA11:CH4, PA6:BKIN, PA7:CH1N, PB0:CH2N, PB1:CH3N
//	3 ... PE7:ETR, PE9:CH1, PE11:CH2, PE13:CH3, PE14:CH4, PE15:BKIN, PE8:CH1N, PE10:CH2N, PE12:CH3N
INLINE void GPIO_Remap_TIM1(int map) { GPIO_Remap1_2b(6, map); }

// Remap Timer 2 (default 0)
//	0 ... PA0:CH1/ETR, PA1:CH2, PA2:CH3, PA3:CH4
//	1 ... PA15:CH1/ETR, PB3:CH2, PA2:CH3, PA3:CH4
//	2 ... PA0:CH1/ETR, PA1:CH2, PB10:CH3, PB11:CH4
//	3 ... PA15:CH1/ETR, PB3:CH2, PB10:CH3, PB11:CH4
INLINE void GPIO_Remap_TIM2(int map) { GPIO_Remap1_2b(8, map); }

// Remap Timer 2 internal trigger 1 (default 0)
//	0 ... connect Timer 2 internal trigger 1 to Ethernet PTP output
//	1 ... connect Timer 2 internal trigger 1 to SOF output of full-speed USB OTG
INLINE void GPIO_Remap_TIM2ITR1(int map) { GPIO_Remap1_1b(29, map); }

// Remap Timer 3 (default 0)
//	0 ... PA6:CH1, PA7:CH2, PB0:CH3, PB1:CH4
//	2 ... PB4:CH1, PB5:CH2, PB0:CH3, PB1:CH4
//	3 ... PC6:CH1, PC7:CH2, PC8:CH3, PC9:CH4
INLINE void GPIO_Remap_TIM3(int map) { GPIO_Remap1_2b(10, map); }

// Remap Timer 4 (default 0)
//	0 ... PB6:CH1, PB7:CH2, PB8:CH3, PB9:CH4
//	1 ... PD12:CH1, PD13:CH2, PD14:CH3, PD15:CH4
INLINE void GPIO_Remap_TIM4(int map) { GPIO_Remap1_1b(12, map); }

// Remap Timer 5 Channel 4 (default 0)
//	0 ... default remapping of timer 5 channel 4
//	1 ... timer 5 channel 4 mapped to the LSI internal clock
INLINE void GPIO_Remap_TIM5CH4(int map) { GPIO_Remap1_1b(16, map); }

// Remap Timer 8 (default 0)
//	0 ... PA0:ETR, PC6:CH1, PC7:CH2, PC8:CH3, PC9:CH4, PA6:BKIN, PA7:CH1N, PB0:CH2N, PB1:CH3N
//	1 ... PA0:ETR, PB6:CH1, PB7:CH2, PB8:CH3, PC13:CH4, PB9:BKIN, PA13:CH1N, PA14:CH2N, PA15:CH3N
INLINE void GPIO_Remap_TIM8(int map) { GPIO_Remap2_1b(2, map); }

// Remap Timer 9 (default 0)
//	0 ... PA2:ETR, PA2:CH1, PA3:CH2, PA4:CH3, PC4:CH4, PC5:BKIN, PC0:CH1N, PC1:CH2N, PC2:CH3N
//	1 ... PA2:ETR, PA2:CH1, PA3:CH2, PA4:CH3, PC14:CH4, PA1:BKIN, PB0:CH1N, PB1:CH2N, PB2:CH3N
//	2,3 ... PD9:ETR/CH1, PD11:CH2, PD13:CH3, PD15:CH4, PD14:BKIN, PD8:CH1N, PD10:CH2N, PD12:CH3N
INLINE void GPIO_Remap_TIM9(int map) { GPIO_Remap2_2b(3, map); }

// Remap Timer 10 (default 0)
//	0 ... PC10:ETR, PB8:CH1, PB9:CH2, PC3:CH3, PC11:CH4, PC12:BKIN, PA12:CH1N, PA13:CH2N, PA14:CH3N
//	1 ... PB11:ETR, PB3:CH1, PB4:CH2, PB5:CH3, PC15:CH4, PB10:BKIN, PA5:CH1N, PA6:CH2N, PA7:CH3N
//	2,3 ... PD0:ETR, PD1:CH1, PD3:CH2, PD5:CH3, PD7:CH4, PE2:BKIN, PE3:CH1N, PE4:CH2N, PE5:CH3N
INLINE void GPIO_Remap_TIM10(int map) { GPIO_Remap2_2b(5, map); }

// Remap CAN1 (default 0)
//	0 ... PA11:CAN_RX, PA12:CAN_TX
//	2 ... PB8:CAN_RX, PB9:CAN_TX
//	3 ... PD0:CAN_RX, PD1:CAN_TX
INLINE void GPIO_Remap_CAN1(int map) { GPIO_Remap1_2b(13, map); }

// Remap CAN2 (default 0)
//	0 ... PB12:CAN_RX, PB13:CAN_TX
//	1 ... PB5:CAN_RX, PB6:CAN_TX
INLINE void GPIO_Remap_CAN2(int map) { GPIO_Remap1_1b(22, map); }

// Remap ADC1 external trigger injection conversion (default 0)
//	0 ... ADC1 external trigger injection conversion connected to EXTI15
//	1 ... ADC1 external trigger injection conversion connected to TIM8_CH4
INLINE void GPIO_Remap_ADC1INJ(int map) { GPIO_Remap1_1b(17, map); }

// Remap ADC1 external trigger regular conversion (default 0)
//	0 ... ADC1 external trigger regular conversion connected to EXTI11
//	1 ... ADC1 external trigger regular conversion connected to TIM8_TRGO
INLINE void GPIO_Remap_ADC1REG(int map) { GPIO_Remap1_1b(18, map); }

// Remap ADC2 external trigger injection conversion (default 0)
//	0 ... ADC2 external trigger injection conversion connected to EXTI15
//	1 ... ADC2 external trigger injection conversion connected to TIM8_CH4
INLINE void GPIO_Remap_ADC2INJ(int map) { GPIO_Remap1_1b(19, map); }

// Remap ADC2 external trigger regular conversion (default 0)
//	0 ... ADC2 external trigger regular conversion connected to EXTI11
//	1 ... ADC2 external trigger regular conversion connected to TIM8_TRGO
INLINE void GPIO_Remap_ADC2REG(int map) { GPIO_Remap1_1b(20, map); }

// Remap Ethernet (default 0)
//	0 ... PA7:RX_DV-CRS_DV, PC4:RXD0, PC5:RXD1, PB0:RXD2, PB1:RXD3
//	1 ... PD8:RX_DV-CRS_DV, PD9:RXD0, PD10:RXD1, PD11:RXD2, PD12:RXD3
INLINE void GPIO_Remap_ETH(int map) { GPIO_Remap1_1b(21, map); }

// Remap Ethernet MAC (default 0)
//	0 ... Ethernet MAC uses MII interface
//	1 ... Ethernet MAC uses RMII interface
INLINE void GPIO_Remap_MAC(int map) { GPIO_Remap1_1b(23, map); }

// Remap PTP PPS (default 0)
//	0 ... PTP PPS not output to PB5
//	1 ... PTP PPS output to PB5
INLINE void GPIO_Remap_PTPPPS(int map) { GPIO_Remap1_1b(30, map); }

// Remap FSMC_NADV (default 0)
//	0 ... FSMC_NADV is mapped to PB7
//	1 ... FSMC_NADV output disabled
INLINE void GPIO_Remap_FSMCNADV(int map) { GPIO_Remap2_1b(10, map); }

// Remap PD0 & PD1 pins to OSC_IN & OSC_OUT (default 0)
//	0 ... pins PD0 & PD1 are used as crystal pins OSC_IN & OSC_OUT
//	1 ... pins PD0 & PD1 are used as GPIO ports
INLINE void GPIO_Remap_PD0PD1(int map) { GPIO_Remap1_1b(15, map); }

// Remap SWD debug interface (default 0)
// 	0-3 ... SWD (SDI) enabled
//	4 ... SWD (SDI) disable, pin served as GPIO
// Note: Before switching the SWD pin to GPIO, insert a short delay
// from system startup to allow the chip to be reprogrammed later.
INLINE void GPIO_Remap_SWD(int map) { GPIO_Remap1_3b(24, map); }

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
