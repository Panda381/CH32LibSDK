
// ****************************************************************************
//
//                             PidiBoy - Keyboard
//
// ****************************************************************************

#include "../../includes.h"

#if USE_KEY		// 1=use keyboard support

// keyboard buffer
Bool KeyInitOk = False;		// keyboard initialized
u32 KeyLastPress[KEY_NUM];
u32 KeyLastRelease[KEY_NUM];
volatile Bool KeyPressMap[KEY_NUM]; // keys are currently pressed (index = button code - 1)
u8 KeyBuf[KEYBUF_SIZE];		// keyboard buffer
volatile u8 KeyWriteOff = 0;	// write offset to keyboard buffer
volatile u8 KeyReadOff = 0;	// read offset from keyboard buffer

//  1: PD3 .... RIGHT
//  2: PD6 .... UP
//  3: PD2 .... LEFT
//  4: PD5 .... DOWN
//  5: PD0 .... A
//  6: PD4 .... B
//  7: PD7 .... Y

// buttons GPIOs
const u8 KeyGpioTab[KEY_NUM] = {
	PD3,	//  1: PD3 .... KEY_RIGHT
	PD6,	//  2: PD6 .... KEY_UP
	PD2,	//  3: PD2 .... KEY_LEFT
	PD5,	//  4: PD5 .... KEY_DOWN
	PD0,	//  5: PD0 .... KEY_A
	PD4,	//  6: PD4 .... KEY_B
	PD7,	//  7: PD7 .... KEY_Y
};

// write key to keyboard buffer
void KeyWriteKey(u8 key)
{
	u8 w = KeyWriteOff;
	u8 w2 = w + 1;
	if (w2 >= KEYBUF_SIZE) w2 = 0;
	if (w2 != KeyReadOff)
	{
		KeyBuf[w] = key;
		cb();
		KeyWriteOff = w2;
	}
}

//#define KEYCNT_REL	50	// keyboard counter - release interval in [ms]
//#define KEYCNT_PRESS	400	// keyboard counter - first repeat in [ms]
//#define KEYCNT_REPEAT	100	// keyboard counter - next repeat in [ms]

// scan keys
void KeyScan()
{
	if (!KeyInitOk) return; // keyboard not initialized

	int i;
	u32 t = Time(); // time in ticks
	for (i = 0; i < KEY_NUM; i++)
	{
		// check if button is pressed
		if (GPIO_In(KeyGpioTab[i]) == 0)
		{
			// button is pressed for the first time
			if (!KeyPressMap[i])
			{
				KeyLastPress[i] = t + (KEYCNT_PRESS - KEYCNT_REPEAT)*1000*HCLK_PER_US;
				KeyPressMap[i] = True;
				KeyWriteKey(i+1);
			}

			// button is already pressed - check repeat interval
			else
			{
				if ((s32)(t - KeyLastPress[i]) >= (s32)(KEYCNT_REPEAT*1000*HCLK_PER_US))
				{
					KeyLastPress[i] = t;
					KeyWriteKey(i+1);
				}
			}
			KeyLastRelease[i] = t;
		}

		// button is release - check stop of press
		else
		{
			if (KeyPressMap[i])
			{
				if ((s32)(t - KeyLastRelease[i]) >= (s32)(KEYCNT_REL*1000*HCLK_PER_US))
				{
					KeyPressMap[i] = False;
				}
			}
		}
	}
}

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet()
{
	// check if keyboard buffer is empty
	u8 r = KeyReadOff;
	cb();
	if (r == KeyWriteOff) return NOKEY;

	// get key from keyboard buffer
	u8 ch = KeyBuf[r];

	// write new read offset
	r++;
	if (r >= KEYBUF_SIZE) r = 0;
	KeyReadOff = r;

	return ch;
}

// key flush
void KeyFlush()
{
	while (KeyGet() != NOKEY) {}
}

// check no pressed key
Bool KeyNoPressed()
{
	int i;
	for (i = 0; i < KEY_NUM; i++) if (KeyPressMap[i]) return False;
	return True;
}

// wait for no key pressed
void KeyWaitNoPressed()
{
	while (!KeyNoPressed()) {}
}

// Initialize keyboard service (should be called before display init)
void KeyInit()
{
#if USE_FLASH		// 1=use Flash programming
	// switch PD7 to GPIO mode, if not already set
	if (((OB->USER >> 3) & 3) != 3)
	{
		OB_t ob;
		Flash_OBRead(&ob);	// read option bytes
		ob.USER |= B3|B4;	// disable RESET function
		Flash_OBWrite(&ob);	// write new option bytes
	}
#endif

	KeyWriteOff = 0;
	KeyReadOff = 0;

	// initialize key ports
	RCC_PBClkEnable();
	RCC_PCClkEnable();
	int i;
	for (i = 0; i < KEY_NUM; i++)
	{
		GPIO_Mode(KeyGpioTab[i], GPIO_MODE_IN_PU);
		KeyPressMap[i] = False;
	}

	KeyInitOk = True; // keyboard initialized
}

// terminate keyboard
void KeyTerm()
{
	KeyInitOk = False; // keyboard not initialized
	cb();
	int i;
	for (i = 0; i < KEY_NUM; i++) GPIO_PinReset(KeyGpioTab[i]);
}

#endif // USE_KEY
