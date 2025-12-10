
// ****************************************************************************
//
//                         Music Player - Keys
//
// ****************************************************************************

#ifndef _KEY_H
#define _KEY_H

#ifdef __cplusplus
extern "C" {
#endif

// Key codes
#define KEY_PLAY	1		// key "Play", short
#define KEY_PREV	2		// key "Prev", short
#define KEY_NEXT	3		// key "Next", short
#define KEY_VOLUP	4		// key "VolUp", short
#define KEY_VOLDN	5		// key "VolDn", short

#define KEY_NUM		5		// number of keys

#define KEY_PLAY_LONG	6		// key "Play", long
#define KEY_PREV_LONG	7		// key "Prev", long
#define KEY_NEXT_LONG	8		// key "Next", long
#define KEY_VOLUP_LONG	9		// key "VolUp", long
#define KEY_VOLDN_LONG	10		// key "VolDn", long

#define NOKEY		0		// no key

#if BABYBEAT		// 1 = use BabyBeat device

// Key GPIOs (GPIOs are hardcoded in key service)
#define KEY_PLAY_GPIO	PC0		// key "Play" GPIO
#define KEY_PREV_GPIO	PC1		// key "Prev" GPIO
#define KEY_NEXT_GPIO	PC2		// key "Next" GPIO
#define KEY_VOLUP_GPIO	PC3		// key "VolUp" GPIO
#define KEY_VOLDN_GPIO	PC4		// key "VolDn" GPIO

// get press button (NOKEY = no key)
u8 KeyGet();

// flush key buffer
void KeyFlush();

// Initialize keyboard service
void KeyInit();

#endif // BABYBEAT

#ifdef __cplusplus
}
#endif

#endif // _KEY_H
