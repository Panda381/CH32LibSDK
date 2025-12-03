
// ****************************************************************************
//
//                                 Keys
//
// ****************************************************************************

#include "../include.h"

// key GPIOs
const u8 KeyGpio[3] = { KEY_A_GPIO, KEY_B_GPIO, KEY_C_GPIO };

#if !USE_KEY_ASM		// 1=use ASM in Key module

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet()
{
	u8 key = KeyBuf;
	KeyBuf = NOKEY;
	if (key != NOKEY) PlayTone(NOTE_C7, NOTE_LEN64); // sound of pressing key
	return key;
}

// key flush
void KeyFlush()
{
	KeyBuf = NOKEY;
}

// keyboard interrupt - called every 20ms from SysTick interrupt
void KeyScan()
{
	u8* s = (u8*)KeyPress;
	int i;
	for (i = 0; i < 3; i++)
	{
		// read key state
		int k = GPIO_In(KeyGpio[i]);
		int p = *s;
		if (k == 0) // pressed
		{
			// first press
			if (p == 0) KeyBuf = i + KEY_A;
			p = 5; // release counter 100ms
		}

		// decrement release counter
		if (p > 0)
		{
			p--;
			*s = p;
		}
		s++;
	}
}

// interrupt on key falling edge
HANDLER void EXTI7_0_IRQHandler()
{
	// clear all interrupt requests
	EXTI->INTFR = 0x3ff;
}

// keyboard initialize
void KeyInit()
{
	// setup key pins
	GPIO_Mode(KEY_A_GPIO, GPIO_MODE_IN_PU);	// KEY A: mode with pull-up
	GPIO_Mode(KEY_B_GPIO, GPIO_MODE_IN_PU);	// KEY B: mode with pull-up
	GPIO_Mode(KEY_C_GPIO, GPIO_MODE_IN_PU);	// KEY C: mode with pull-up

	// remap EXTI to keys A and B (do not use key C - it is connected with SWIO)
	GPIO_EXTILine(KEY_A_PORT, KEY_A_PIN);	// setup external interrupt input pin KEY A
	GPIO_EXTILine(KEY_B_PORT, KEY_B_PIN);	// setup external interrupt input pin KEY B
	EXTI_FallEnable(KEY_A_PIN);		// enable EXTI on falling edge of KEY A
	EXTI_FallEnable(KEY_B_PIN);		// enable EXTI on falling edge of KEY B
	EXTI_Enable(KEY_A_PIN);			// enable EXTI line interrupt of KEY A
	EXTI_Enable(KEY_B_PIN);			// enable EXTI line interrupt of KEY B
	NVIC_IRQEnable(IRQ_EXTI7);		// enable EXTI interrupt service
}

#endif // !USE_KEY_ASM
