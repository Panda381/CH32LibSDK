
// ****************************************************************************
//
//                                 Memorize
//
// ****************************************************************************

#include "../include.h"

// Flash data slots (2 slots)
__attribute__((section(".flashminislot"))) __attribute__((aligned(256))) volatile const sFlashData FlashDataSlot[2];

#if !USE_MEM_ASM		// 1=use ASM in Mem module

// load current flash data (returns False if no flash data has been found and using default)
NOMEMSET Bool LoadFlash()
{
	int i, inx;
	Bool ok, ok2;

	// initialize default flash data
	u8* d = (u8*)&FlashData;
	for (i = sizeof(FlashData); i > 0; i--) *d++ = 0;
	FlashData.pet[0].state.state[0] = 0x55; // set all state to mid. value (=5)
	FlashData.pet[0].state.state[1] = 0x55;
	FlashData.pet[0].state.state[2] = 0x55;
	FlashDataActive = 0;

	// check Flash slots
	ok = False;
	const volatile sFlashData* f = FlashDataSlot; // pointer to flash data slot
	for (inx = 0; inx < 2; inx++)
	{
		//const sFlashData* f = &FlashDataSlot[inx]; // pointer to flash data slot
// --- Why is the slot "volatile" - because otherwise, if the pointer was created inside the loop like this,
//     the variables stayed cached from the previous slot... a GCC bug?

		// check slot
		ok2 = FlashDataCRC(f) == f->crc32; // check slot CRC
		if ((f->petnum == 0) || (f->petnum == 0xffff)) ok2 = False;	// check number of pets
		if (f->index == 0xffffffff) ok2 = False;			// uninitialized flash

		// use this slot
		if (ok2 && (f->index >= FlashData.index))
		{
			memcpy(&FlashData, (const void*)f, sizeof(FlashData));
			FlashDataActive = inx;
			ok = True;
		}

		// shift slot pointer
		f++;
	}
	return ok;
}

// save flash data (returns False on error)
Bool SaveFlash()
{
	// increase slot index
	FlashData.index++;

	// set slot CRC
	FlashData.crc32 = FlashDataCRC(&FlashData);

	// prepare slot address
	const volatile sFlashData* f = &FlashDataSlot[FlashDataActive ^ 1];
	u32 slot = (u32)f + FLASH_BASE;
	
	// clear flash slot (address and size must be multiply of 256 B)
	Flash_Erase(slot, SLOTSIZE, 1000);

	// write data
	Flash_Program(slot, (u32*)&FlashData, SLOTSIZE, 1000);

	// verify slot data
	int i;
	const u8* s = (const u8*)f;
	const u8* d = (const u8*)&FlashData;
	for (i = sizeof(FlashData); i > 0; i--)
	{
		if (*s != *d) break;
		s++;
		d++;
	}

	if (i == 0) // data are equal
	{
		FlashDataActive ^= 1;	// shift index to next active flash slot
		return True;
	}

	// slot is invalid, restore old record index
	FlashData.index--;
	return False;
}

// set state variable
NOINLINE void PetSetState(int inx, u8 val)
{
	// feed watch dog
	IWDG_Reload();
	cb();

	// set state
	u8* s = &RamData->state.state[inx >> 1];
	if ((inx & 1) == 0)
		*s = (*s & 0xf0) | val;
	else
		*s = (*s & 0x0f) | (val << 4);

	// upgrade CRC
	cb();
	RamCrc();
}

// increase state
void PetAddState(int inx, u8 add)
{
	int val = PetGetState(inx) + add;
	if (val > STATEMAX) val = STATEMAX;
	PetSetState(inx, val);
}

// update checksum of RAM data
//   First call IWDG_Reload() to prevent RAM data inconsistency, then set
//   the variable in RamData, and finally update the CRC using RamCrc().
void RamCrc(void)
{
	RamData->crc32 = RamDataCRC(RamData);
}

// save RAM to flash, if need update (returns False on error)
Bool SaveRamFlash(void)
{
	// check if update is needed
	if (	(FlashData.pet[0].state.data[0] != RamData->state.data[0]) ||
		(FlashData.pet[0].state.data[1] != RamData->state.data[1]))
	{
		// save data
		FlashData.pet[0].state.data[0] = RamData->state.data[0];
		FlashData.pet[0].state.data[1] = RamData->state.data[1];
		return SaveFlash();
	}
	return True;
}

#endif // !USE_MEM_ASM
