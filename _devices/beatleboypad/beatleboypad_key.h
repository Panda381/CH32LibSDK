
// ****************************************************************************
//
//                             BeatleBoyPad - Keyboard
//
// ****************************************************************************

#if USE_KEY		// 1=use keyboard support

#ifndef _BEATLEBOYPAD_KEY_H
#define _BEATLEBOYPAD_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

// keyboard buffer
#define KEYBUF_SIZE	8	// size of keyboard buffer
extern u8 KeyBuf[KEYBUF_SIZE];	// keyboard buffer
extern u8 KeyWriteOff;		// write offset to keyboard buffer
extern u8 KeyReadOff;		// read offset from keyboard buffer
extern u8 KeyPressMapOld;	// old pressed keys

// scan keyboard
void KeyScan();

// check if button KEY_* is currently pressed
Bool KeyPressed(u8 key);

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet();

// key flush
void KeyFlush();

// check no pressed key
Bool KeyNoPressed();

// wait for no key pressed
void KeyWaitNoPressed();

// Initialize keyboard service
INLINE void KeyInit() {}

// terminate keyboard
INLINE void KeyTerm() {}

#ifdef __cplusplus
}
#endif

#endif // _BEATLEBOYPAD_KEY_H

#endif // USE_KEY
