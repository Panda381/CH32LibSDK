
// ****************************************************************************
//
//                              Data area
//
// ****************************************************************************

#ifndef _DATA_H
#define _DATA_H

#ifdef __cplusplus
extern "C" {
#endif

extern u8 RamData_Beg;		// start of global RAM data

extern Bool PrintInv;		// Draw inversion
extern u8 State;		// Current state STATE_*
extern Bool DirRight;		// Current direction is to right
extern Bool Wink;		// Current wink state
extern Bool Anim;		// Current anim state
extern u8 NewPetInx;		// Index of new pet
extern u8 MenuInx;		// Index of menu
extern u8 NewPetNameInx;	// Index of character of name of new pet
extern char NewPetName[NAMEMAX]; // Name of new pet, including terminating 0 (real name length is 11 characters)
extern u32 DirNextTime;		// Time to next change direction
extern u32 WinkNextTime;	// Time to next wink change
extern u32 AnimNextTime;	// Time to next anim change
extern volatile u8 KeyPress[3]; // Key pressed counter (key is pressed if counter is > 0)
extern volatile u8 KeyBuf;	// keyboard buffer - pressed key (NOKEY = none)
extern u8 FlashDataActive;	// Index of last used Flash data (programming will take place in the other slot)
extern u32 Last;		// time of last key
extern u32 LastTick;		// time of last tick

//extern sFlashData FlashData;	// Current Flash data (size must be 256 bytes = FLASH_PAGEPG_SIZE)
extern u8 FrameBuf[FRAMESIZE];	// Display graphics buffer

extern u8 RamData_End;		// end of global RAM data

#ifdef __cplusplus
}
#endif

#endif // _DATA_H
