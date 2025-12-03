
// ****************************************************************************
//
//                                GPIO pins
//
// ****************************************************************************

#include "../_include.h"

// lock GPIO pin (pin configuration cannot be changed until next reset MCU or reset port; gpio = PA0...)
void GPIO_Lock(int gpio)
{
	// prepare port and pin
	GPIO_t* port = GPIO_PORT(gpio);
	int pin = GPIO_PIN(gpio);

	// prepare value mask
	int pinmask = BIT(pin);
	u32 tmp = B16 | pinmask;

	// lock pin
	port->LCKR = tmp;
	port->LCKR = pinmask;
	port->LCKR = tmp;
	tmp = port->LCKR;	
	tmp = port->LCKR;	
}

// set GPIO pin mode (gpio = PA0..., mode = GPIO_MODE_*)
//  For GPIO_MODE_IN_* modes, the output register will be set accordingly.
void GPIO_Mode(int gpio, int mode)
{
	// prepare port and pin
	GPIO_t* port = GPIO_PORT(gpio);
	int pin = GPIO_PIN(gpio);

	// prepare configuration register
	io32* reg = &port->CFGLR;
	int shift = pin;
	if (shift >= 8)
	{
		reg = &port->CFGHR;
		shift -= 8;
	}

	// setup mode
	shift <<= 2;
	*reg = (*reg & ~(0x0f << shift)) | ((mode & 0x0f) << shift);

	// set pulls
	if (mode >= 0x28)	// pulls?
	{
		shift = BIT(pin);	// pin mask for pull-up mode
		if (mode == GPIO_MODE_IN_PD) shift <<= 16; // pin mask for pull-down mode
		port->BSHR = shift;	// set pull mode
	}
}

// get current GPIO pin mode (returns GPIO_MODE_*; gpio = PA0...)
int GPIO_GetMode(int gpio)
{
	// prepare port and pin
	GPIO_t* port = GPIO_PORT(gpio);
	int pin = GPIO_PIN(gpio);

	// prepare configuration register
	io32* reg = &port->CFGLR;
	int shift = pin;
	if (shift >= 8)
	{
		reg = &port->CFGHR;
		shift -= 8;
	}

	// get current mode
	shift <<= 2;
	int mode = (*reg >> shift) & 0x0f;

	// process pulls of GPIO_MODE_IN_*
	if (mode == 8)
	{
		mode = (GPIOx_GetOut(port, pin) == 0) ? GPIO_MODE_IN_PD : GPIO_MODE_IN_PU;
	}
	return mode;
}

// setup external interrupt input pin
//  port ... source port (PORTA_INX,...)
//  pin ... source pin/interrupt pin (0..15)
// - Determines which port pin the external interrupt pin is mapped to.
void GPIO_EXTILine(int port, int pin)
{
	io32* reg = &AFIO->EXTICR[pin >> 2];
	pin = (pin & 3) << 2;
	*reg = (*reg & ~(0x0f << pin)) | (port << pin);
}

// Reset pin to default state (pin must not be locked; does not reset mappings)
void GPIO_PinReset(int gpio)
{
	// set floating input mode
	GPIO_Mode(gpio, GPIO_MODE_IN);

	// set output to 0
	GPIO_Out0(gpio);
}

// Reset GPIO port to default state (use port index PORT*_INX, does not disable clock)
void GPIO_PortReset(int portinx)
{
	RCC_PxReset(portinx);
}

// Reset all GPIO ports and all mappings to default state (does not disable clock)
void GPIO_AllReset(void)
{
	RCC_AFIReset();
	GPIO_PortReset(PORTA_INX);
	GPIO_PortReset(PORTB_INX);
	GPIO_PortReset(PORTC_INX);
	GPIO_PortReset(PORTD_INX);
	GPIO_PortReset(PORTE_INX);
}
