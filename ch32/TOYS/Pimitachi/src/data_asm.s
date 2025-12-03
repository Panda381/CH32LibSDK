
// ****************************************************************************
//
//                           Global data area
//
// ****************************************************************************
// Global data is used for quick access to data using the GP (global pointer) register.

// In linker script *.ld:
//	.globaldata (NOLOAD) :
//	{
//		. = ALIGN(4);
//		__globaldata_start = .;
//		KEEP(*(.globaldata))
//		__globaldata_end = .;
//		. = ALIGN(4);
//	} > RAM
//	PROVIDE( __global_pointer$ = __globaldata_start );	/* pointer to global data section */

// In startup crt0.S:
//	// setup global pointer
//	.option	push			// push current linker setup
//	.option	norelax			// disable linker relaxation (disable optimizing programs at link-time)
//	la	gp,__global_pointer$	// global pointer to global data in RAM
//	.option	pop			// pop original linker setup

// RISC-V assembler:
// Function may destroy (storer=caller): x1 (ra), x5-x7 (t0-t2), x10-x15 (a0-a5)
// Function must save (storer=callee): x8 (s0/fp), x9 (s1)
// Special registers: x0 (zero), x2 (sp), x3 (gp), x4 (tp)

// TP (x4, Thread Pointer) register is not used in this system, can be used as special register in functions.

#include "def.h"

	.section	.globaldata, "aw"

RamData_Beg:			// start of global RAM data

// >>> Beware of alignment of addresses of variables! <<<

PrintInv:	.space	1	// 0x00 (Bool) Draw inversion
State:		.space	1	// 0x01 (u8) Current state STATE_*
DirRight:	.space	1	// 0x02 (Bool) Current direction is to right
Wink:		.space	1	// 0x03 (Bool) Current wink state
Anim:		.space	1	// 0x04 (Bool) Current anim state
NewPetInx:	.space	1	// 0x05 (u8) Index of new pet
MenuInx:	.space	1	// 0x06 (u8) Index of menu
NewPetNameInx:	.space	1	// 0x07 (u8) Index of character of name of new pet
NewPetName:	.space	NAMEMAX // 0x08 (char[12], 12 bytes) Name of new pet, including terminating 0 (real name length is 11 characters)
DirNextTime:	.space	4	// 0x14 (u32) Time to next change direction
WinkNextTime:	.space	4	// 0x18 (u32) Time to next wink change
AnimNextTime:	.space	4	// 0x1C (u32) Time to next anim change
KeyPress:	.space	3	// 0x20 (volatile u8[3], 3 bytes) Key pressed counter (key is pressed if counter is > 0)
KeyBuf:		.space	1	// 0x23 (volatile u8) keyboard buffer - pressed key (NOKEY = none)
FlashDataActive: .space	1	// 0x24 (u8) Index of last used Flash data (programming will take place in the other slot)
		.space	3
RleDataImg:	.space	8	// 0x28 (sRleData, 8 bytes) RLE image data
RleDataMsk:	.space	8	// 0x30 (sRleData, 8 bytes) RLE mask data
Last:		.space	4	// 0x38 (u32) time of last key
LastTick:	.space	4	// 0x3C (u32) time of last tick

FlashData:	.space	256	// 0x40 (sFlashData, 256 bytes) Current flash data (size must be 256 bytes = FLASH_PAGEPG_SIZE)
FrameBuf:	.space	FRAMESIZE // 0x140 (u8 FrameBuf[FRAMESIZE]) Display graphics buffer

RamData_End:			// end of global RAM data


.global RamData_Beg

.global	PrintInv
.global	State
.global	DirRight
.global	Wink
.global	Anim
.global	NewPetInx
.global	MenuInx
.global	NewPetNameInx
.global	NewPetName
.global	DirNextTime
.global	WinkNextTime
.global	AnimNextTime
.global	KeyPress
.global KeyBuf
.global FlashDataActive
.global RleDataImg
.global RleDataMsk
.global Last
.global LastTick

.global FlashData
.global FrameBuf

.global RamData_End
