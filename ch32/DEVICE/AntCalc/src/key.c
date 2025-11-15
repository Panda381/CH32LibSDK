
// ****************************************************************************
//
//                           AntCalc - Keyboard
//
// ****************************************************************************

#include "../include.h"

// keyboard buffer
u8 KeyBuf[KEYBUF_SIZE];		// keyboard buffer
volatile u8 KeyWriteOff = 0;	// write offset to keyboard buffer
volatile u8 KeyReadOff = 0;	// read offset from keyboard buffer
volatile u8 KeyMap[KEY_NUM];	// press counters and map of pressed keys
Bool KeyInitOK = False;		// flag - keyboard is initialized

const u8 RowPins[3] = { PD6, PC6, PA1 }; // ROW pins
const u8 ColPins[4] = { PA2, PD5, PC7, PD4 }; // COL pins

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

// key flush
void KeyFlush()
{
	while (KeyGet() != NOKEY) {}
}

// check no pressed key
Bool KeyNoPressed()
{
	int i;
	for (i = 0; i < KEY_NUM; i++) if (KeyMap[i] != 0) return False;
	return True;
}

// wait for no key pressed
void KeyWaitNoPressed()
{
	while (!KeyNoPressed()) {}
}

// keyboard interrupt - called every 20ms from SysTick interrupt
void KeyScan()
{
	int row, col;
	if (!KeyInitOK) return;	// keyboard is not initialized

	// loop through ROW pins
	u8 key = 0;
	volatile u8* m = &KeyMap[0];
	u8 mm;
	row = 0;
	for (row = 0; row < 3; row++)
	{
		// set row to LOW output
		GPIO_Out0(RowPins[row]);
		
		// delay to stabilize signals
		WaitUs(10);

		// loop through COL pins
		for (col = 0; col < 4; col++)
		{
			mm = *m;

			// key is pressed
			if (GPIO_In(ColPins[col]) == 0)
			{
				// button is pressed for the first time
				if (mm == 0) KeyWriteKey(key);
				mm = 4; // release time 60ms
			}

			// release counter
			if (mm != 0) mm--;

			*m = mm;

			// incrase key index
			key++;
			m++;
		}

		// set row to HIGH output (open-drain)
		GPIO_Out1(RowPins[row]);
	}
}

// Initialize keyboard service
void KeyInit()
{
	// remap PA1 & PA2 to GPIO
	GPIO_Remap_PA1PA2(0);

	// initialize key ports
	RCC_AFIClkEnable();
	RCC_PAClkEnable();
	RCC_PCClkEnable();
	RCC_PDClkEnable();
// PD6: ROW1 -> open-drain output
// PC6: ROW2 -> open-drain output
// PA1: ROW3 -> open-drain output
	GPIO_Mode(PD6, GPIO_MODE_OD);		// ROW1
	GPIO_Mode(PC6, GPIO_MODE_OD);		// ROW2
	GPIO_Mode(PA1, GPIO_MODE_OD);		// ROW3
// PA2: COL1 -> input with pull-up
// PD5: COL2 -> input with pull-up
// PC7: COL3 -> input with pull-up
// PD4: COL4 -> input with pull-up
	GPIO_Mode(PA2, GPIO_MODE_IN_PU);	// COL1
	GPIO_Mode(PD5, GPIO_MODE_IN_PU);	// COL2
	GPIO_Mode(PC7, GPIO_MODE_IN_PU);	// COL3
	GPIO_Mode(PD4, GPIO_MODE_IN_PU);	// COL4

	// clear key map
	memset((void*)KeyMap, 0, sizeof(KeyMap));

	// start keyboard service
	cb();
	KeyInitOK = True;		// keyboard is initialized
}

// terminate keyboard
void KeyTerm()
{
	KeyInitOK = False;	// keyboard not initialized
	cb();
	GPIO_PinReset(PD6);	// ROW1
	GPIO_PinReset(PC6);	// ROW2
	GPIO_PinReset(PA1);	// ROW3
	GPIO_PinReset(PA2);	// COL1
	GPIO_PinReset(PD5);	// COL2
	GPIO_PinReset(PC7);	// COL3
	GPIO_PinReset(PD4);	// COL4
}
