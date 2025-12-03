
// ****************************************************************************
//
//                                 Keys
//
// ****************************************************************************

#ifndef _KEY_H
#define _KEY_H

#ifdef __cplusplus
extern "C" {
#endif

// input keys (Note: The pin numbers must be different in order to map EXTI)
#define KEY_A_GPIO	PA1	// gpio of key A
#define KEY_B_GPIO	PA2	// gpio of key B
#define KEY_C_GPIO	PD4	// gpio of key C (it is connected to SWIO PD1 pin)

#define KEY_A_PORT	GPIO_PORTINX(KEY_A_GPIO)	// port of key A
#define KEY_A_PIN	GPIO_PIN(KEY_A_GPIO)		// pin of key A
#define KEY_B_PORT	GPIO_PORTINX(KEY_B_GPIO)	// port of key B
#define KEY_B_PIN	GPIO_PIN(KEY_B_GPIO)		// pin of key B
#define KEY_C_PORT	GPIO_PORTINX(KEY_C_GPIO)	// port of key C
#define KEY_C_PIN	GPIO_PIN(KEY_C_GPIO)		// pin of key C

// pressed key
#define KEY_A	1
#define KEY_B	2
#define KEY_C	3

#define NOKEY	0		// no key

// keyboard buffer - pressed key (NOKEY = none)
extern volatile u8 KeyBuf;

// key GPIOs
extern const u8 KeyGpio[3];

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet(void);

// key flush
void KeyFlush(void);

// keyboard interrupt - called every 20ms from SysTick interrupt
void KeyScan(void);

// keyboard initialize
void KeyInit(void);

#ifdef __cplusplus
}
#endif

#endif // _KEY_H
