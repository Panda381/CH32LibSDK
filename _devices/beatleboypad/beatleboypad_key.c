
// ****************************************************************************
//
//                             BeatleBoyPad - Keyboard
//
// ****************************************************************************

#include "../../includes.h"

#if USE_KEY		// 1=use keyboard support

// keyboard buffer
u8 KeyBuf[KEYBUF_SIZE];		// keyboard buffer
u8 KeyWriteOff = 0;		// write offset to keyboard buffer
u8 KeyReadOff = 0;		// read offset from keyboard buffer
u8 KeyPressMapOld = 0;		// old pressed keys

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

// scan keys
void KeyScan()
{
	int i, m;
	int map = KeyPressMap;
	int old = KeyPressMapOld;
	KeyPressMapOld = map;
	m = B1;
	for (i = 1; i <= KEY_NUM; i++)
	{
		if (((map & m) != 0) && ((old & m) == 0)) KeyWriteKey(i);
		m <<= 1;
	}
}

// check if button KEY_* is currently pressed
Bool KeyPressed(u8 key)
{
	KeyScan();
	return (KeyPressMap & (1 << key)) != 0;
}

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet()
{
	KeyScan();

	// check if keyboard buffer is empty
	u8 r = KeyReadOff;
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
	KeyScan();
	return KeyPressMap == 0;
}

// wait for no key pressed
void KeyWaitNoPressed()
{
	while (!KeyNoPressed()) {}
}

#endif // USE_KEY
