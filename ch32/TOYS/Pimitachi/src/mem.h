
// ****************************************************************************
//
//                                 Memorize
//
// ****************************************************************************

#ifndef _MEM_H
#define _MEM_H

#ifdef __cplusplus
extern "C" {
#endif

// type flag
#define TYPE_GONE	B7		// 1=pet is complete and gone, 0=pet is processed
#define TYPE_ADULT	B6		// 1=pet is adult, 0=pet is baby
#define TYPE_MASK	0x3f		// type index mask

// Pet state (size 8 bytes)
typedef union {
	struct {
		u16	res;		// 0x00: ... reserved (for score)
		u8	type;		// 0x02: bit 0..5: pet type 1..TYPENUM (0=invalid)
					//       bit 6 (TYPE_ADULT): 1=pet is adult, 0=pet is baby
					//	 bit 7 (TYPE_GONE): 1=pet is complete and gone, 0=pet is processed
		u8	age;		// 0x03: pet's age in days
		u8	state[3];	// 0x04: state (6 states in nibbless, low nibble is 1st state)
		u8	agemax;		// 0x07: age limit
	};
	u32	data[2];
} sPetState;
STATIC_ASSERT(sizeof(sPetState) == 8, "Incorrect sPetState!");

// RAM data (size must be 16 bytes) - we will use protected structure in RAM sLoaderData;
//   we cannot use the Loader anyway, due to the protection of the saved state
typedef struct {
	u32		crc32;		// 0x00: checksum of next 12 bytes calculated with Crc32BSlow()
	u16		ticks;		// 0x04: tick counter per one day (1 tick = 8.2 seconds, total about 10450 ticks per day)
	u16		res;		// 0x06: ... reserved (align)
	sPetState	state;		// 0x08 (8): pet state
} sRamData;
STATIC_ASSERT(sizeof(sRamData) == 16, "Incorrect sRamData!");
#define RamData	((sRamData*)&_sloaderdata) // pointer to RAM data

// Flash pet entry
typedef struct {
	u8		name[NAMEMAX];	// 0x00 (12): name (with spaces on the end, with 0 on last byte), 
	sPetState	state;		// 0x0C (8): pet state
} sPetData;
STATIC_ASSERT(sizeof(sPetData) == 20, "Incorrect sPetData!");

// Flash data (size must be 256 bytes = FLASH_PAGEPG_SIZE = SLOTSIZE)
typedef struct {
	u32		crc32;		// 0x00: checksum of next 252 bytes calculated with Crc32BSlow()
	u32		index;		// 0x04: index of this structure - every new entry increases this counter
	u32		res2;		// 0x08: ... reserved (for total score of finished pets)
	u16		petnum;		// 0x0C: number of pets in history (only last 12 pets are in the list)
	u8		soundoff;	// 0x0E: 1=sound off, 0=sound on
	u8		res;		// 0x0F: ... align
	sPetData	pet[PETNUM];	// 0x10 (12*20=240=0xF0): list of pets (entry 0 is the last pet)
} sFlashData;
STATIC_ASSERT(sizeof(sFlashData) == SLOTSIZE, "Incorrect sFlashData!");

// get CRC of Flash data
INLINE u32 FlashDataCRC(const volatile sFlashData* f) { return Crc32BSlow((const u8*)f + 4, sizeof(sFlashData) - 4); }

// get CRC of RAM data
INLINE u32 RamDataCRC(const sRamData* r) { return Crc32BSlow((const u8*)r + 4, sizeof(sRamData) - 4); }

// Flash data slots (2 slots)
extern volatile const sFlashData FlashDataSlot[2];

// current Flash data
extern sFlashData FlashData;

// Get/set pet property
//   First call IWDG_Reload() to prevent RAM data inconsistency, then set
//   the variable in RamData, and finally update the CRC using RamCrc().

// pointer to current pet's name in FlashData structure
#define PetName	FlashData.pet[0].name

// get sound OFF
INLINE u8 GetSoundOff(void) { return FlashData.soundoff; }

// set sound OFF (save flash after write)
INLINE void SetSoundOff(u8 off) { FlashData.soundoff = off; }

// check if current pet is valid
INLINE Bool PetIsValid(void) { return RamData->state.type != 0; }

// get/set tick counter per one day
INLINE u16 PetTicks(void) { return RamData->ticks; }
INLINE void PetSetTicks(int ticks) { RamData->ticks = ticks; }

// get/set pet type (0=invalid)
INLINE u8 PetType(void) { return RamData->state.type; }
INLINE void PetSetType(int type) { RamData->state.type = type; }

// get pet current real type (get pet index *_INX)
INLINE u8 PetRealType(void)
{
	int i = PetType();
	if ((i & TYPE_ADULT) == 0) i = 0; // pet is baby
	return i & TYPE_MASK; // mask pet type
}

// get/set pet age in days
INLINE u8 PetAge(void) { return RamData->state.age; }
INLINE void PetSetAge(int age) { RamData->state.age = age; }

// get/set pet age max in days
INLINE u8 PetAgeMax(void) { return RamData->state.agemax; }
INLINE void PetSetAgeMax(int agemax) { RamData->state.agemax = agemax; }

// get state variable
INLINE u8 PetGetState(int inx)
{
	u8 s = RamData->state.state[inx >> 1];
	if ((inx & 1) != 0) s >>= 4;
	return s & 0x0f;
}

// set state variable
void PetSetState(int inx, u8 val);

// increase state
void PetAddState(int inx, u8 add);

// get/set pet fullness state
INLINE u8 PetFeed(void) { return PetGetState(STATE_FEED); }
INLINE void PetSetFeed(int val) { PetSetState(STATE_FEED, val); }
INLINE void PetAddFeed(int val) { PetAddState(STATE_FEED, val); }

// get/set pet health state
INLINE u8 PetHealth(void) { return PetGetState(STATE_HEALTH); }
INLINE void PetSetHealth(int val) { PetSetState(STATE_HEALTH, val); }
INLINE void PetAddHealth(int val) { PetAddState(STATE_HEALTH, val); }

// get/set pet rest state
INLINE u8 PetRest(void) { return PetGetState(STATE_REST); }
INLINE void PetSetRest(int val) { PetSetState(STATE_REST, val); }
INLINE void PetAddRest(int val) { PetAddState(STATE_REST, val); }

// get/set pet hapiness state
INLINE u8 PetHappy(void) { return PetGetState(STATE_HAPPY); }
INLINE void PetSetHappy(int val) { PetSetState(STATE_HAPPY, val); }
INLINE void PetAddHappy(int val) { PetAddState(STATE_HAPPY, val); }

// get/set pet clean state
INLINE u8 PetClean(void) { return PetGetState(STATE_CLEAN); }
INLINE void PetSetClean(int val) { PetSetState(STATE_CLEAN, val); }
INLINE void PetAddClean(int val) { PetAddState(STATE_CLEAN, val); }

// get/set pet discipline state
INLINE u8 PetDisc(void) { return PetGetState(STATE_DISC); }
INLINE void PetSetDisc(int val) { PetSetState(STATE_DISC, val); }
INLINE void PetAddDisc(int val) { PetAddState(STATE_DISC, val); }

// load current flash data (returns False if no flash data has been found and using default)
Bool LoadFlash();

// save flash data (returns False on error)
Bool SaveFlash();

// update checksum of RAM data
//   First call IWDG_Reload() to prevent RAM data inconsistency, then set
//   the variable in RamData, and finally update the CRC using RamCrc().
void RamCrc(void);

// save RAM to flash, if need update (returns False on error)
Bool SaveRamFlash(void);

#ifdef __cplusplus
}
#endif

#endif // _MEM_H
