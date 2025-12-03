
// ****************************************************************************
//
//                       Definitions (common to C and ASM)
//
// ****************************************************************************

#ifndef _DEF_H
#define _DEF_H

// DEBUG mode
#define DEBUG		0		// 1=DEBUG mode, use fast pet mode (16x faster)

#define USE_DISP_ASM	1		// 1=use ASM in Disp module
#define USE_DRAW_ASM	1		// 1=use ASM in Draw module
#define USE_KEY_ASM	1		// 1=use ASM in Key module
#define USE_MEM_ASM	1		// 1=use ASM in Mem module

// frame buffer
#define WIDTH		128		// width in pixels
#define HEIGHT		64		// height in graphics lines
#define WIDTHBYTE	(WIDTH/8)	// width in bytes (= 16) ... hardcoded in Draw functions in ASM
#define FRAMESIZE	(WIDTHBYTE*HEIGHT) // size of frame buffer in bytes (= 16*64 = 1024 bytes)
#define TEXTWIDTH	(WIDTH/8)	// text width in characters (= 16)
#define TEXTHEIGHT	(HEIGHT/8)	// text height in rows (= 8; 1 character = 8x8 pixels)

// display
#define DISP_I2C_ADDR	0x3C		// display I2C address
#define DISP_SDA_GPIO	PC1		// display gpio with SDA
#define DISP_SCL_GPIO	PC2		// display gpio with SCL

#define DISP_INITDATA_NUM	25	// number of bytes of DispI2C_InitData[]

// Colors
#define COL_BLACK	0		// black color
#define COL_WHITE	1		// white color

// font (128 characters of size 8x8 pixels)
#define FONT	FontZx

// game setup
#define SLOTSIZE	256		// size of one flash slot (must be equal to flash page size)
#define NAMEMAX		12		// max. length of the name, including terminating 0 (real name length is 11 characters)
#define BASENUM		6		// number of base pet types
#define TYPENUM		7		// number of total pet types (including baby)
#define AGEDEF		21		// default maximal age in days
#define AGEADULT	4		// adult age in days
#define PETNUM		12		// max. number of pets in the gallery
#define STATEMAX	10		// state max level
#define TICK		8200		// one tick in number of [ms]
					// - More precisely, it should be 8192, but there is some
					//   delay during the CPU reset before the IWDT restarts.
#define TIMEOUT		30		// time-out to go to sleep, in seconds

#if DEBUG	// 1=DEBUG mode, use fast pet mode
#define TICKSDAY	37		// number of ticks per day ... fast mode, 1 day of pet = 5 minutes real time, total 21 days = 1 3/4 hours
#else
#define TICKSDAY	10537		// number of ticks per day ... normal mode, 1 day of pet = 1 day of real time
#endif

// animal indices
#define BABY_INX	0		// baby
#define CAT_INX		1		// cat
#define DOG_INX		2		// dog
#define BUNNY_INX	3		// bunny
#define HAMSTER_INX	4		// hamster
#define BIRD_INX	5		// bird
#define DRAGON_INX	6		// dragon

// game state
#define STATE_SEL	1	// select new pet
#define STATE_NAME	2	// set pet's name
#define STATE_GAME	3	// in base game
#define STATE_MENU	4	// display menu

// state indices
#define STATE_FEED	0		// fullness state (0=hungry .. STATEMAX=well-fed)
#define STATE_HEALTH	1		// health status (0=sick .. STATEMAX=healthy)
#define STATE_REST	2		// rest state (0=tired .. STATEMAX=rested)
#define STATE_HAPPY	3		// happiness (0=unhappy .. STATEMAX=happy)
#define STATE_CLEAN	4		// clean (0=mess .. STATEMAX=clean)
#define STATE_DISC	5		// discipline (0=undisciplined .. STATEMAX=disciplined)
#define STATE_NUM	6		// number of states

// mask of ticks to shift the state
#if DEBUG	// 1=DEBUG mode, use fast pet mode
// fast DEBUG mode - 16x faster
#define MASK_FEED	0x1f		// 32 ticks (4 minutes) ... full starvation 3/4 hour
#define MASK_HEALTH	0x0f		// 16 ticks (2 minutes) ... full sick 21 minutes
#define MASK_REST	0x03		// 4 ticks (1/2 minute) ... full rest 5 minutes
#define MASK_HAPPY	0x1f		// 32 ticks (4 minutes) ... full unhappy 3/4 hour
#define MASK_CLEAN	0x1f		// 32 ticks (4 minutes) ... full mess 3/4 hour
#define MASK_DISC	0x1f		// 32 ticks (4 minutes) ... full undisciplined 3/4 hour
#else
// normal mode
#define MASK_FEED	0x1ff		// 512 ticks (1 hour) ... full starvation 11 hours
#define MASK_HEALTH	0x0ff		// 256 ticks (1/2 hour) ... full sick 6 hours
#define MASK_REST	0x03f		// 64 ticks (8 minutes) ... full rest 1 1/2 hour
#define MASK_HAPPY	0x1ff		// 512 ticks (1 hour) ... full unhappy 11 hours
#define MASK_CLEAN	0x1ff		// 512 ticks (1 hour) ... full mess 11 hours
#define MASK_DISC	0x1ff		// 512 ticks (1 hour) ... full undisciplined 11 hours
#endif

// RAM data offsets (Synchronize it with the file data_asm.S)
#define RAM_PRINTINV_OFF	0x00	// (Bool PrintInv) Draw inversion
#define RAM_STATE_OFF		0x01	// (u8 State) Current state STATE_*
#define RAM_DIRRIGHT_OFF	0x02	// (Bool DirRight) Current direction is to right
#define RAM_WINK_OFF		0x03	// (Bool Wink) Current wink state
#define RAM_ANIM_OFF		0x04	// (Bool Anim) Current anim state
#define RAM_NEWPETINX_OFF	0x05	// (u8 NewPetInx) Index of new pet
#define RAM_MENUINX_OFF		0x06	// (u8 MenuInx) Index of menu
#define RAM_NEWPETNAMEINX_OFF	0x07	// (u8 NewPetNameInx) Index of character of name of new pet
#define RAM_NEWPETNAME_OFF	0x08	// (char NewPetName[NAMEMAX], 12 bytes) Name of new pet, including terminating 0 (real name length is 11 characters)
#define RAM_DIRNEXTTIME_OFF	0x14	// (u32 DirNextTime) Time to next change direction
#define RAM_WINKNEXTTIME_OFF	0x18	// (u32 WinkNextTime) Time to next wink change
#define RAM_ANIMNEXTTIME_OFF	0x1C	// (u32 AnimNextTime) Time to next anim change
#define RAM_KEYPRESS_OFF	0x20	// (volatile u8 KeyPress[3], 3 bytes) Key pressed counter (key is pressed if counter is > 0)
#define RAM_KEYBUF_OFF		0x23	// (volatile u8 KeyBuf) keyboard buffer - pressed key (NOKEY = none)
#define RAM_FLASHDATAACTIVE_OFF	0x24	// (u8 FlashDataActive) Index of last used Flash data (programming will take place in the other slot)
// 3
#define RAM_RLEDATAIMG_OFF	0x28	// (sRleData RleDataImg, 8 bytes) RLE image data
#define RAM_RLEDATAMSK_OFF	0x30	// (sRleData RleDataMsk, 8 bytes) RLE mask data
#define RAM_LAST_OFF		0x38	// (u32 Last) time of last key
#define RAM_LASTTICK_OFF	0x3C	// (u32 LastTick) time of last tick

#define RAM_FLASHDATA_OFF	0x40	// (sFlashData FlashData, 256 bytes) Current flash data (size must be 256 bytes = FLASH_PAGEPG_SIZE)
#define RAM_FRAMEBUF_OFF	0x140	// (u8 FrameBuf[FRAMESIZE], 1024 bytes) Display graphics buffer

// RLE decompressor structure sRleData
#define RLE_IMG_OFF		0x00	// (const u8*) data of the image
#define RLE_CACHE_OFF		0x04	// (u8) byte cache of the image
#define RLE_BITS_OFF		0x05	// (u8) number of bits in byte cache of the image

// flash data sFlashData (SLOTSIZE = 256 bytes)
#define FLASHDATA_CRC_OFF	0x00	// (u32 crc32) checksum of next 252 bytes calculated with Crc32BSlow()
#define FLASHDATA_INDEX_OFF	0x04	// (u32 index) index of this structure - every new entry increases this counter
#define FLASHDATA_PETNUM_OFF	0x0C	// (u16 petnum) number of pets in history (only last 12 pets are in the list)
#define FLASHDATA_PET_OFF	0x10	// (sPetData pet[PETNUM]) list of pets (entry 0 is the last pet)

// flash pet entry sPetData (20 bytes)
#define PETDATA_NAME_OFF	0x00	// (u8 name[NAMEMAX], 12 bytes) name (with spaces on the end, with 0 on last byte), 
#define PETDATA_STATE_OFF	0x0C	// (sPetState state, 8 bytes) pet state

// RAM data sRamData (size 16 bytes)
#define RAMDATA_CRC_OFF		0x00	// (u32 crc32) checksum of next 12 bytes calculated with Crc32BSlow()
#define RAMDATA_TICKS_OFF	0x04	// (u16 ticks) tick counter per one day (1 tick = 8.2 seconds, total about 10450 ticks per day)
#define RAMDATA_STATE_OFF	0x08	// (sPetState state, 8 bytes) pet state

// pet state sPetState (8 bytes)
#define PETSTATE_TYPE_OFF	0x02	// (u8 type) bit 0..5: pet type 1..TYPENUM (0=invalid)
					//           bit 6 (TYPE_ADULT): 1=pet is adult, 0=pet is baby
					//           bit 7 (TYPE_GONE): 1=pet is complete and gone, 0=pet is processed
#define PETSTATE_AGE_OFF	0x03	// (u8 age) pet's age in days
#define PETSTATE_STATE_OFF	0x04	// (u8 state[3]) (6 states in nibbless, low nibble is 1st state)
#define PETSTATE_AGEMAX_OFF	0x07	// (u8 agemax) age limit
#define PETSTATE_DATA_OFF	0x00	// (u32 data[2]) raw data

#endif // _DEF_H
