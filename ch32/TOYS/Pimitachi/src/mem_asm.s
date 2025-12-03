
// ****************************************************************************
//
//                                 Memorize
//
// ****************************************************************************

#include "def.h"

#if USE_MEM_ASM		// 1=use ASM in Mem module

#define	FLASH_BASE		0x08000000	// FLASH base address in the alias region

#define	PERIPH_BASE		0x40000000	// Peripheral base address in the alias region
#define APB1PERIPH_BASE		PERIPH_BASE			// 0x40000000
#define IWDG_BASE		(APB1PERIPH_BASE + 0x3000)	// IWDG 0x40003000
#define IWDG_CTLR_OFF		0x00		// control register
#define IWDG_KEY_RELOAD		0xAAAA		// reload counter from reload register ("Feed the dog")

	.section	.text

// ----------------------------------------------------------------------------
// load current flash data (returns False if no flash data has been found and using default)
// ----------------------------------------------------------------------------
// NOMEMSET Bool LoadFlash()

.global LoadFlash
LoadFlash:

	// save registers
	addi	sp,sp,-16
	sw	ra,0(sp)

// Registers:
//  0: RA
//  4: pointer to flash data slot sFlashData 'f'
//  8: result 'ok'
//  12: flash index 'inx'

	// clear flash data
	addi	a5,gp,RAM_FLASHDATA_OFF	// A5 <- start of flash data
	addi	a4,a5,SLOTSIZE		// A4 <- end of flash data
1:	sb	zero,0(a5)		// save byte 0
	addi	a5,a5,1			// A5 <- shift destination pointer
	bne	a5,a4,1b		// next byte

	// initialize default flash data - set all state to mid. value (=5)
	li	a0,0x55			// A0 <- default value 5
	sb	a0,-SLOTSIZE+FLASHDATA_PET_OFF+PETDATA_STATE_OFF+PETSTATE_STATE_OFF+0(a4) // save state byte 0
	sb	a0,-SLOTSIZE+FLASHDATA_PET_OFF+PETDATA_STATE_OFF+PETSTATE_STATE_OFF+1(a4) // save state byte 1
	sb	a0,-SLOTSIZE+FLASHDATA_PET_OFF+PETDATA_STATE_OFF+PETSTATE_STATE_OFF+2(a4) // save state byte 2

	// select active data = 0
	sb	zero,RAM_FLASHDATAACTIVE_OFF(gp) // reset FlashDataActive

	// prepare pointer to flash slots FlashDataSlot
	sw	zero,8(sp)		// clear result 'ok' = False
	sw	zero,12(sp)		// clear current flash index 'inx'
	la	a0,FlashDataSlot	// A0 <- pointer to flash data slot

	// calculate CRC of this flash slot -> A0
2:	sw	a0,4(sp)		// save pointer to flash data slot 'f'
	addi	a0,a0,4			// skip CRC entry
	li	a1,SLOTSIZE-4		// A1 <- size of data
	call	Crc32BSlow		// calculate CRC

	// check CRC
	lw	a1,4(sp)		// A1 <- pointer to flash slot sFlashData 'f'
	lw	a2,FLASHDATA_CRC_OFF(a1) // A2 <- current CRC of flash slot
	bne	a0,a2,6f		// skip if CRC does not match

	// check number of pets
	lh	a2,FLASHDATA_PETNUM_OFF(a1) // A2 <- number of pets
	blez	a2,6f			// skip if number of pets <= 0

	// check slot index
	lw	a2,FLASHDATA_INDEX_OFF(a1) // A2 <- slot index
	bltz	a2,6f			// skip if slot index < 0
	lw	a3,RAM_FLASHDATA_OFF+FLASHDATA_INDEX_OFF(gp) // get current flash index
	blt	a2,a3,6f		// skip if new index is less than current flash index

	// copy flash slot to current flash data (A1 = pointer to flash slot)
	addi	a0,gp,RAM_FLASHDATA_OFF	// A0 <- pointer to current flash data
	li	a2,SLOTSIZE		// A2 <- size of the slot
	call	memcpy			// copy flash slot
	li	a0,1
	sw	a0,8(sp)		// set result to True
	lw	a1,12(sp)		// A1 <- current slot index 'inx'
	sb	a1,RAM_FLASHDATAACTIVE_OFF(gp) // set FlashDataActive
	
	// shift slot pointer
6:	lw	a0,4(sp)		// A0 <- pointer to flash slot 'f'
	addi	a0,a0,SLOTSIZE		// shift slot pointer 'f'
	lw	a1,12(sp)		// A1 <- current slot index 'inx'
	addi	a1,a1,1			// A1 <- increase slot index
	sw	a1,12(sp)		// save new slot index 'inx'
	li	a2,2			// A2 <- max. slot index
	bne	a1,a2,2b		// next slot

	// result
	lw	a0,8(sp)		// A0 <- result 'ok'

	// restore registers
	lw	ra,0(sp)
	addi	sp,sp,16
	ret

// ----------------------------------------------------------------------------
// save RAM to flash, if need update (returns False on error)
// ----------------------------------------------------------------------------
// Bool SaveRamFlash(void)

.global SaveRamFlash
SaveRamFlash:

	// read data from RamData -> A0, A1
	la	a5,_sloaderdata		// A5 <- RamData address
	lw	a0,RAMDATA_STATE_OFF(a5) // A0 <- data 0
	lw	a1,RAMDATA_STATE_OFF+4(a5) // A1 <- data 1

	// read data from FlashData
	addi	a5,gp,RAM_FLASHDATA_OFF+FLASHDATA_PET_OFF // A5 <- FlashData address
	lw	a2,PETDATA_STATE_OFF(a5) // A2 <- data 0
	lw	a3,PETDATA_STATE_OFF+4(a5) // A3 <- data 1

	// check if update is needed
	bne	a0,a2,4f		// skip if different
	bne	a1,a3,4f		// skip if different

	// equal, no save
	li	a0,1			// A0 <- result True
	ret

	// save new state
4:	sw	a0,PETDATA_STATE_OFF(a5) // save data 0
	sw	a1,PETDATA_STATE_OFF+4(a5) // save data 1

// ---- continue to SaveFlash

// ----------------------------------------------------------------------------
// save flash data (returns False on error)
// ----------------------------------------------------------------------------
// Bool SaveFlash()

.global SaveFlash
SaveFlash:

	// save registers
	addi	sp,sp,-16
	sw	ra,0(sp)
	sw	s0,4(sp)

	// prepare flash data FlashData pointer -> S0
	addi	s0,gp,RAM_FLASHDATA_OFF	// A0 <- pointer to flash data FlashData

	// increase slot index
	lw	a5,FLASHDATA_INDEX_OFF(s0) // A5 <- get current index
	addi	a5,a5,1			// increase flash index
	sw	a5,FLASHDATA_INDEX_OFF(s0) // set new flash index

	// set slot CRC
	addi	a0,s0,4			// A0 <- flash data + 4
	li	a1,SLOTSIZE-4		// A1 <- size of flash data - 4
	call	Crc32BSlow		// calculate CRC
	sw	a0,FLASHDATA_CRC_OFF(s0) // store CRC

	// prepare slot address
	lbu	a0,RAM_FLASHDATAACTIVE_OFF(gp) // A0 <- active flash slot
	xori	a0,a0,1			// A0 <- next flash slot
	la	a1,FlashDataSlot	// A1 <- pointer to flash data slot
	slli	a0,a0,8			// A0 <- offset of flash slot (= index * SLOTSIZE)
	add	a0,a0,a1		// A0 <- address of flash data slot 'f'
	sw	a0,8(sp)		// save address of flash data slot 'f'

	// prepare FLASH mapped slot address
	li	a1,FLASH_BASE		// FLASH base address in the alias region
	add	a0,a0,a1		// A0 <- FLASH mapped slot address
	sw	a0,12(sp)		// save FLASH address

	// clear flash slot (address and size must be multiply of 256 B)
	li	a1,SLOTSIZE		// A1 <- slot size
	li	a2,1000			// A2 <- time out in [ms]
	call	Flash_Erase		// flash erase

	// write data
	lw	a0,12(sp)		// A0 <- FLASH address
	mv	a1,s0			// A1 <- pointer to flash data to write
	li	a2,SLOTSIZE		// A2 <- slot size
	li	a3,1000			// A3 <- time out in [ms]
	call	Flash_Program		// write data

	// verify slot data (S0 = flash data FlashData)
	lw	a5,8(sp)		// A5 <- address of the slot
	addi	a4,s0,SLOTSIZE		// A4 <- end of FlashData
2:	lbu	a0,0(s0)		// A0 <- get byte from FlashData
	lbu	a1,0(a5)		// A1 <- get byte from the slot
	bne	a0,a1,4f		// skip if not equal
	addi	s0,s0,1			// S0 <- shift pointer FlashData
	addi	a5,a5,1			// A5 <- shfit pointer to slot
	bne	s0,a4,2b		// next byte

	// data are equal - shift index to next active flash slot
	lbu	a0,RAM_FLASHDATAACTIVE_OFF(gp) // A0 <- active flash slot
	xori	a0,a0,1			// A0 <- next flash slot
	sb	a0,RAM_FLASHDATAACTIVE_OFF(gp) // set new active slot
	li	a0,1			// A0 <- True
	j	9f

	// slot is invalid, restore old record index
4:	lw	a5,RAM_FLASHDATA_OFF+FLASHDATA_INDEX_OFF(gp) // A5 <- get current index
	addi	a5,a5,-1		// decrease flash index
	sw	a5,RAM_FLASHDATA_OFF+FLASHDATA_INDEX_OFF(gp) // set new flash index
	li	a0,0			// A0 <- false

	// restore registers
9:	lw	s0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,16
	ret

// ----------------------------------------------------------------------------
// increase state
// ----------------------------------------------------------------------------
// void PetAddState(int inx, u8 add)

.global PetAddState
PetAddState:

	// prepare pointer to state byte -> A5
	srai	a5,a0,1			// A5 <- state index >> 1 (= byte offset)
	la	a4,_sloaderdata		// A4 <- address of RamData
	add	a5,a5,a4		// A5 <- pointer to the byte

	// get old byte -> A4
	lbu	a4,RAMDATA_STATE_OFF+PETSTATE_STATE_OFF(a5) // A4 <- get byte

	// mask value
	andi	a3,a0,1			// odd/even?
	beqz	a3,2f			// skip if even byte
	srli	a4,a4,4			// shift value right
2:	andi	a4,a4,0x0f		// mask value

	// increase value
	add	a1,a1,a4		// A1 <- increase value
	li	a3,STATEMAX		// A3 <- max. state
	blt	a1,a3,PetSetState	// skip if no overflow
	mv	a1,a3			// A1 <- limit value on overflow

// ---- continue to PetSetState

// ----------------------------------------------------------------------------
// set state variable
// ----------------------------------------------------------------------------
// NOINLINE void PetSetState(int inx, u8 val)

.global PetSetState
PetSetState:

	// feed watch dog
	li	a5,IWDG_BASE		// A5 <- IWDG base
	li	a4,IWDG_KEY_RELOAD	// A4 <- reload keyword
	sw	a4,0(a5)		// reload IWDG

	// prepare pointer to state byte -> A5
	srai	a5,a0,1			// A5 <- state index >> 1 (= byte offset)
	la	a4,_sloaderdata		// A4 <- address of RamData
	add	a5,a5,a4		// A5 <- pointer to the byte

	// get old byte -> A4
	lbu	a4,RAMDATA_STATE_OFF+PETSTATE_STATE_OFF(a5) // A4 <- get byte

	// check odd/even
	andi	a0,a0,1			// A0 <- even or odd byte flag
	bnez	a0,2f			// skip if ODD state

	// set EVEN value
	andi	a4,a4,~0x0f		// A4 <- clear old value
	j	4f

	// set ODD value
2:	slli	a1,a1,4			// A1 <- shift value left
	andi	a4,a4,0x0f		// clear old value

	// store new value
4:	or	a4,a4,a1		// add new value
	sb	a4,RAMDATA_STATE_OFF+PETSTATE_STATE_OFF(a5) // store new value

// ---- continue to RamCrc

// ----------------------------------------------------------------------------
// update checksum of RAM data
// ----------------------------------------------------------------------------
//   First call IWDG_Reload() to prevent RAM data inconsistency, then set
//   the variable in RamData, and finally update the CRC using RamCrc().
// void RamCrc(void)

.global RamCrc
RamCrc:

	// save registers
	addi	sp,sp,-4
	sw	ra,0(sp)

	// get CRC
	la	a0,_sloaderdata+4	// A0 <- address of RamData (skip CRC)
	li	a1,12			// A1 <- length (widthou CRC)
	call	Crc32BSlow		// get CRC

	// set CRC
	lui	a5,%hi(_sloaderdata)	// A5 <- RamData address HIGH
	sw	a0,%lo(_sloaderdata)+RAMDATA_CRC_OFF(a5) // store new CRC

	// restore registers
	lw	ra,0(sp)
	addi	sp,sp,4
	ret

#endif // USE_MEM_ASM
