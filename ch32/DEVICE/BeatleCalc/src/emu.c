
// ****************************************************************************
//
//                           TI Emulator
//
// ****************************************************************************
// Code is based on these emulators:
//
// 1) Original source (c) Ken Shirriff
//    https://static.righto.com/calculator/sinclair_scientific_simulator.html
//    https://static.righto.com/calculator/TI_calculator_simulator.html
//
// 2) ArduinoNanoSinclairScientificCalculator (c) Arduino Enigma
//    https://gitlab.com/arduinoenigma/ArduinoNanoSinclairScientificCalculator
//    https://github.com/arduinoenigma/ArduinoNanoSinclairScientificCalculator

#include "../include.h"
#include "prog_datamath.inc"	// const u16 ProgDatamath[320]
#include "prog_sinclair.inc"	// const u16 ProgSinclair[320]

// Masks (S10 digit on left, S0 digit on right)
#define MASK_LEN	12	// length of one mask
#define	NUMBER_OF_MASKS	16	// number of masks
const u8* MasksDatamath[NUMBER_OF_MASKS] = {
	"          7",	// M0
	"         4 ",	// M1
	"        1  ",	// M2
	"       0   ",	// M3
	"      0    ",	// M4
	"     0     ",	// M5
	"    0      ",	// M6
	" 0         ",	// M7
	"1          ",	// M8
	"        000",	// M9
	"01         ",	// M10
	"000000001  ",	// M11
	"000000000  ",	// M12
	"         01",	// M13
	"         00",	// M14
	"00000000000",	// M15
};

const u8* MasksSinclair[NUMBER_OF_MASKS] = {
	"00000000000",	// M0
	"5          ",	// M1
	"  00       ",	// M2
	"    1      ",	// M3
	"    0000000",	// M4
	"          1",	// M5
	"  01       ",	// M6
	" 5         ",	// M7
	"000000     ",	// M8
	"0001       ",	// M9
	"    0000001",	// M10
	"     1     ",	// M11
	"    00005  ",	// M12
	"    00001  ",	// M13
	"    4      ",	// M14
	"    0      ",	// M15
};

// Keys on KN signal
//  Datamath: 1     2     3     4     5     6     7     8     9
//  Sinclair: 1     2     3     4     5     6     7     8     9
const u8 KeysKN[10] = { KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, NOKEY };

// Keys on KO signal
//  Datamath:  C     =     +     -     *     /    CE     .     0
//  Sinclair:  C    dn     +     -     /     *    up     E     0
const u8 KeysKODatamath[10] = { NOKEY, KEY_EQU, KEY_ADD, KEY_SUB, KEY_MUL, KEY_DIV, KEY_CE, KEY_DOT, KEY_0 };
const u8 KeysKOSinclair[10] = { NOKEY, KEY_3RD, KEY_ADD, KEY_SUB, KEY_DIV, KEY_MUL, KEY_2ND, KEY_EE, KEY_0 };

// variables
const u16* Rom;		// pointer current ROM code (= ProgDatamath or ProgSinclair)
const u8* KeysKO;	// pointer to keys on KO signal
u8 DActive = 0;		// Currently active D value 0-9
Bool Carry = 0;		// result carry (overflow) or condition flag
//u8 KeyPressed = NOKEY;	// pressed key
Bool KeyStrobeKN = False; // key signal KN is active
Bool KeyStrobeKO = False; // key signal KO is active
//Bool KeyStrobeKP = False; // key signal KP is active
int Address = 0;	// current execution address (= program counter)
const u8** MasksAll;	// pointer to masks
u8 Masks[MASK_LEN];	// current mask (' '=not masked, '*'=masked, n=mask and constant)
#if SLOWMODE	// 1=run slow at real speed, 0=run fast at max speed
u32 StepTime;		// time of next instruction
#endif

// Data registers
#define REG_LEN	11	// length of the register = number of digits
// Important: Array order matches display order, not bit order.
// I.e. a[0] is high-order digit S10, a[10] is low-order digit S0.
s8 RegA[REG_LEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// register A
s8 RegB[REG_LEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// register B
s8 RegC[REG_LEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// register C
s8 RegTmp[REG_LEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// temporary register (during comparison)
s8 RegAF[REG_LEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// flags A
s8 RegBF[REG_LEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// flags B

// list of opcodes for which the constant should be displayed (bit of opcode 0..31 is set)
// var opsWithK = { 1:'AAKA',2:'AAKC',5:'ACKA',6:'ACKB',9:'SAKA',11:'SCKC',13:'CAK',15:'CCK',
//		16:'AKA',17:'AKB',18:'AKC',26:'AKCN',27:'AAKAH',28:'SAKAH',29:'ACKC',};
// value: 1007135334 = 0x3C07AA66 = 0011 1100 0000 0111 1010 1010 0110 0110b
const u32 opsWithK = B29+B28+B27+B26+B18+B17+B16+B15+B13+B11+B9+B6+B5+B2+B1;

// Load mask for current instruction into Masks[] array. Returns pointer to Masks[].
// Note that S10 is in Masks[0]. Returns value 0 in Masks[0], if mask is not valid.
// Entries are ' ' if not masked, '*' if masked, n if mask and constant.
u8* GetMask()
{
	// parse instruction
	int cmd = Rom[Address];		// load instruction
	int cls = cmd >> 9;		// instruction class bits
	int op = (cmd >> 4) & 0x1f;	// operation code

	// check if mask is valid
	if ((cls == 3) || ((cls == 2) && (op > 18) && (op != 21) && (op != 22)))
	{
		// prepare mask bits
		int msk = cmd & 0x0f;
		const u8* m = MasksAll[msk];

		int i;
		for (i = 0; i <= 10; i++)
		{
			// get mask digit
			u8 d = *m++;

			// prepare mask (' '=not masked, '*'=masked, n=mask and constant)
			if (d == ' ')
				Masks[i] = d;		// ' ' = not masked
			else if ((cls == 3) && ((opsWithK & (1UL << op)) != 0))
				Masks[i] = d - '0';	// n = mask and constant
			else
				Masks[i] = '*';		// '*' = masked
		}
	}

	// invalid mask
	else
		Masks[0] = 0;

	return Masks;
}

// add operation
void Add(const s8* src1, const s8* src2, s8* dst, Bool hex)
{
	// reset input carry
	Bool carry = False;

	// load mask
	GetMask();

	// loop digits
	int i;
	for (i = 10; i >= 0; i--)
	{
		// not masked
		if (Masks[i] == ' ')
		{
			// masked out
		}
		else
		{
			// add digits
			s8 res = src1[i] + src2[i] + carry;
			carry = False;

			// check overflow
			if (!hex && (res >= 10)) // overflow decimal digit
			{
				// decimal digit overflow
				res -= 10;
				carry = True;
			}
			else if (hex && (res >= 16)) // overflow hex digit
			{
				// hex digit overflow
				res -= 16;
				carry = True;
			}

			// store new digit
			dst[i] = res;
		}
	}

	// result carry (overflow)
	if (carry) Carry = carry;
}

// sub operation
void Sub(const s8* src1, const s8* src2, s8* dst, Bool hex)
{
	// reset input borrow
	Bool borrow = False;

	// load mask
	GetMask();

	// loop digits
	int i;
	for (i = 10; i >= 0; i--)
	{
		// not masked
		if (Masks[i] == ' ')
		{
			// masked out
		}
		else
		{
			// sub digits
			s8 res = src1[i] - src2[i] - borrow;
			borrow = False;

			// check underflow
			if (res < 0)
			{
				res += hex ? 16 : 10;
				borrow = True;
			}

			// store new digit
			dst[i] = res;
		}
	}

	// result borrow (underflow)
	if (borrow) Carry = borrow;
}

// compare numbers (sets Carry if src1 < src2)
void Comp(const s8* src1, const s8* src2)
{
	Sub(src1, src2, RegTmp, False);
}

// copy numbers (masked)
void Copy(const s8* src, s8* dst)
{
	// load mask
	GetMask();

	// loop digits
	int i;
	for (i = 10; i >= 0; i--)
	{
		// not masked
		if (Masks[i] == ' ')
		{
			// masked out
		}
		else
		{
			dst[i] = src[i];
		}
	}
}

// shift number left (masked)
void Sll(s8* src)
{
	// load mask
	GetMask();

	// loop digits
	s8 dig = 0;
	int i;
	for (i = 10; i >= 0; i--)
	{
		// not masked
		if (Masks[i] == ' ')
		{
			// masked out
		}
		else
		{
			s8 newdig = src[i];
			src[i] = dig;
			dig = newdig;
		}
	}
}

// shift number right (masked)
void Srl(s8* src)
{
	// load mask
	GetMask();

	// loop digits
	s8 dig = 0;
	int i;
	for (i = 0; i <= 10; i++)
	{
		// not masked
		if (Masks[i] == ' ')
		{
			// masked out
		}
		else
		{
			s8 newdig = src[i];
			src[i] = dig;
			dig = newdig;
		}
	}
}

// write flags (0 or 1 to test flag, -1 to flip flag)
void WriteFlag(s8* dst, s8 val)
{
	// load mask
	GetMask();

	// loop digits
	int i;
	for (i = 10; i >= 0; i--)
	{
		// not masked
		if (Masks[i] == ' ')
		{
			// masked out
		}
		else
		{
			// Flip dst if val == -1, otherwise set to val
			dst[i] = (val < 0) ? (1 - dst[i]) : val;
		}
	}
}

// compare flags (sets Carry if not equal)
void CompFlag(const s8* src1, const s8* src2)
{
	// reset difference flag
	Bool cc = False;

	// load mask
	GetMask();

	// loop digits
	int i;
	for (i = 10; i >= 0; i--)
	{
		// not masked
		if (Masks[i] == ' ')
		{
			// masked out
		}
		else
		{
			if (src1[i] != src2[i]) cc = True;
		}
	}

	// result carry (not equal)
	if (cc) Carry = cc;
}

// exchange numbers
void Exchange(s8* src1, s8* src2)
{
	// load mask
	GetMask();

	// loop digits
	int i;
	for (i = 10; i >= 0; i--)
	{
		// not masked
		if (Masks[i] == ' ')
		{
			// masked out
		}
		else
		{
			s8 d = src1[i];
			src1[i] = src2[i];
			src2[i] = d;
		}
	}
}

// test flags (sets Carry if flag is set)
void TestFlag(const s8* src)
{
	// reset flag
	Bool cc = False;

	// load mask
	GetMask();

	// loop digits
	int i;
	for (i = 10; i >= 0; i--)
	{
		// not masked
		if (Masks[i] == ' ')
		{
			// masked out
		}
		else
		{
			if (src[i] != 0) cc = True;
		}
	}

	// result carry (flag set)
	if (cc) Carry = cc;
}

// update D
void UpdateD(void)
{
	int a = DActive + 1;
	if (a > 9) a = 0;
	DActive = (u8)a;
}

// Do emulated program step
void StepEmu()
{
	// load instruction
	int cmd = Rom[Address];		// load instruction
	int next = Address + 1;		// prepare next address
	int cls = cmd >> 9;		// instruction class bits
	int op = (cmd >> 4) & 0x1f;	// operation code

	// instruction class = 3, register operations
	if (cls == 3)
	{
		// execute operation code
		switch (op)
		{
		// AABA: A+B -> A
		case 0: Add(RegA, RegB, RegA, False); break;

		// AAKA: A+K -> A
		case 1: Add(RegA, GetMask(), RegA, False); break;

		// AAKC: A+K -> C
		case 2: Add(RegA, GetMask(), RegC, False); break;

		case 3:
			if (IS_SINCLAIR)
			{
				// ACBB C+B -> B
				Add(RegC, RegB, RegB, False);
			}
			else
			{
				// ABOA: B -> A
				Copy(RegB, RegA);
			}
			break;

		// ABOC: B -> C
		case 4: Copy(RegB, RegC); break;

		// ACKA: C+K -> A
		case 5: Add(RegC, GetMask(), RegA, False); break;

		// AKCB: C+K -> B
		case 6: Add(RegC, GetMask(), RegB, False); break;

		// SABA: A-B -> A
		case 7: Sub(RegA, RegB, RegA, False); break;

		// SABC: A-B -> C
		case 8: Sub(RegA, RegB, RegC, False); break;

		// SAKA: A-K -> A
		case 9: Sub(RegA, GetMask(), RegA, False); break;

		// SCBC: C-B -> C
		case 10: Sub(RegC, RegB, RegC, False); break;

		// SCKC: C-K -> C
		case 11: Sub(RegC, GetMask(), RegC, False); break;

		// CAB: compare A-B
		case 12: Comp(RegA, RegB); break;

		// CAK: compare A-K
		case 13: Comp(RegA, GetMask()); break;

		// CCB: compare C-B
		case 14: Comp(RegC, RegB); break;

		// CCK: compare C-K
		case 15: Comp(RegC, GetMask()); break;

		// AKA: K -> A
		case 16: Copy(GetMask(), RegA); break;

		// AKB: K -> B
		case 17: Copy(GetMask(), RegB); break;

		// AKC: K -> C
		case 18: Copy(GetMask(), RegC); break;

		// EXAB: exchange A and B
		case 19: Exchange(RegA, RegB); break;

		// SLLA: shift A left
		case 20: Sll(RegA); break;

		// SLLB: shift B left
		case 21: Sll(RegB); break;

		// SLLC: shift C left
		case 22: Sll(RegC); break;

		// SRLA: shift A right
		case 23: Srl(RegA); break;

		// SRLB: shift B right
		case 24: Srl(RegB); break;

		// SRLC: shift C right
		case 25: Srl(RegC); break;

		// AKCN: A+K -> A until key down on N or D11 [sic]
		// Patent says sets condition if key down, but real behavior
		// is to set condition if addition overflows (i.e. no key down)
		case 26:
			Add(RegA, GetMask(), RegA, False);
			if (KeyStrobeKN) // key signal KN is active
			{
				// Advance to next instruction
			}
			else if (DActive != 9) // wait for state D10
			{
				// Hold at current instruction and continue scan
				next = Address;
			}
			else
			{
				// For state d10, fall through
			}
			break;

		case 27:
			if (IS_SINCLAIR)
			{
				// SCBA C-B -> A
				Sub(RegC, RegB, RegA, False);
			}
			else
			{
				// AAKAH A+K -> A hex
				Add(RegA, GetMask(), RegA, True);
				Carry = False;
			}
			break;

		case 28:
			if (IS_SINCLAIR)
			{
				// SCKB C-K -> B
				Sub(RegC, GetMask(), RegB, False);
			}
			else
			{
				// SAKAH A-K -> A hex
				Sub(RegA, GetMask(), RegA, True);
				Carry = False;
			}
			break;

		// ACKC: C+K -> C
		case 29: Add(RegC, GetMask(), RegC, False); break;

		// AABC A+B -> C
		case 30:
			if (IS_SINCLAIR)
			{
				Add(RegA, RegB, RegC, False);
			}
			break;

		// ACBC C+B -> C
		case 31:
			if (IS_SINCLAIR)
			{
				Add(RegC, RegB, RegC, False);
			}
			break;
		}
	} // if (cls == 3)

	// Flag instruction
	else if ((cmd >> 8) == 5)
	{
		// execute operation code
		switch (op)
		{
		// NOP
		case 16: break;

		// WAITDK: wait for display key
		case 17:
/*
			if (KeyPressed == KEY_DK)
			{
				// Jump
				next = cmd & 0x1ff;
			}
			else
			{
				// Hold address until DK pressed
				next = Address;
			}
*/
			break;

		// WAITNO: wait for key or address register overflow
		case 18:
			if (KeyStrobeKN || KeyStrobeKO)// || KeyStrobeKP)
			{
				// Jump
				next = cmd & 0x1ff;
			}
			else
			{
				// Hold address until key pressed or address overflow
				next = Address;
			}
			break;

		// SFB: set flag B
		case 19: WriteFlag(RegBF, 1); break;

		// SFA: set flag A
		case 20: WriteFlag(RegAF, 1); break;

		// SYNC (SYNCH): hold address until end of D10
		case 21:
			if (DActive != 9) next = Address;
			Carry = False;
			break;

		// SCAN (SCANNO): wait for key
		case 22:
			if (KeyStrobeKN || KeyStrobeKO)// || KeyStrobeKP)
			{
				// key pressed
				Carry = True;
			}
			else
			{
				// no key
				Carry = False;

				// Hold address until end of D10
				if (DActive != 9) next = Address;
			}
			break;

		// ZFB: zero flag B
		case 23: WriteFlag(RegBF, 0); break;

		// ZFA: zero flag A
		case 24: WriteFlag(RegAF, 0); break;

		// TFB: test flag B
		case 25: TestFlag(RegBF); break;

		// TFA: test flag A
		case 26: TestFlag(RegAF); break;

		// FFB: flip flag B
		case 27: WriteFlag(RegBF, -1); break;

		// FFA: flip flag A
		case 28: WriteFlag(RegAF, -1); break;

		// CF: compare flags
		case 29: CompFlag(RegAF, RegBF); break;

		// NOP
		case 30: break;

		// EXF: exchange flags
		case 31: Exchange(RegAF, RegBF); break;
		}
	} // else if ((cmd >> 8) == 5)
		
	// jump if reset: BIU, BIZ, BIGE, BINC, BIE, BET
	else if (cls == 0)
	{
		if (!Carry) next = cmd & 0x1ff; // jump
		Carry = False; // Clear after jump
	}

	// jump if set: BID, BIO, BILT, BIC, BINE
	else if (cls == 1)
	{
		if (Carry) next = cmd & 0x1ff; // jump
		Carry = False; // Clear after jump
	}

	// Jump if key down on KO (BKO) (jump address 0 to 127)
	else if ((cmd >> 7) == 8)
	{
		if (KeyStrobeKO)
		{
			next = cmd & 0x1ff; // jump
		}
		Carry = False; // Clear after jump
	}

	// Jump if key down on KP (BKP) (jump address 128 to 255)
	else if ((cmd >> 7) == 9)
	{
/*
		if (KeyStrobeKP)
		{
			next = cmd & 0x1ff; // jump
		}
*/
		Carry = False; // Clear after jump
	}

	// set next address
	Address = next;

	// Put the mask for the next instruction in the model for display
	GetMask();

	// Update D state
	UpdateD();
}

// read keys
void ReadKey()
{
	// current digit position (0..9)
	u8 inx = DActive;

	// set KN signal
	KeyStrobeKN = KeyIsPressed(KeysKN[inx]);

	// set KO signal
	KeyStrobeKO = KeyIsPressed(KeysKO[inx]);
}

// display update
void DisplayUpdate()
{
	// Sinclair
	if (IS_SINCLAIR)
	{
		// current digit position
		u8 inx = DActive;
		if (inx > 8) return;

		// get digit from register A
		u8 dig = RegA[inx];

		switch (inx)
		{
		// number sign
		case 0: DigWrite(0, (dig == 0) ? CH_SPC : CH_NEG); break;

		// exponent sign
		case 1: DigWrite(6, (dig == 0) ? CH_SPC : CH_NEG); break;

		// exponent 1
		case 2: DigWrite(7, dig); break;

		// exponent 2
		case 3: DigWrite(8, dig); break;

		// mantissa 1 + decimal point
		case 4: DigWrite(1, dig | CH_DOT); break;

		// mantissa 2
		case 5: DigWrite(2, dig); break;

		// mantissa 3
		case 6: DigWrite(3, dig); break;

		// mantissa 4
		case 7: DigWrite(4, dig); break;

		// mantissa 5
		case 8: DigWrite(5, dig); break;
		}
	}

	// Datamath ... update on end of digit active D10
	else if (DActive == 9)
	{
		// flag - suppress zeros
		Bool nozero = True;

		// loop through digits
		int i;
		for (i = 0; i < 9; i++)
		{
			// get digit
			u8 dig = RegA[i];

			// validate zeros
			if ((i == 8) || (dig != 0) || (RegB[i] == 2)) nozero = False;

			// suppress zero
			if ((dig == 0) && nozero)
				dig = CH_SPC;

			// minus
			else if (dig == 14)
				dig = CH_NEG;

			// add decimal point
			if (RegB[i] == 2) dig |= CH_DOT;

			// save digit
			DispBuf[i] = dig;
		}

		// display update
		DispUpdate();
	}
}

// Run emulator
void RunEmu(void)
{
	// initialize emulator
	if (IS_DATAMATH)
	{
		// initialize Datamath
		Rom = ProgDatamath;
		MasksAll = MasksDatamath;
		KeysKO = KeysKODatamath;
	}
	else
	{
		// initialize Sinclair
		Rom = ProgSinclair;
		MasksAll = MasksSinclair;
		KeysKO = KeysKOSinclair;
	}

	// reset program counter
	Address = 0;

#if SLOWMODE	// 1=run slow at real speed, 0=run fast at max speed
	// start instruction timmings
	StepTime = Time(); // get time in CPU clock cycles
#endif

	// emulator loop
	while (True)
	{
		// read keys
		ReadKey();

		// do emulated program step
		StepEmu();

		// display update
		DisplayUpdate();

		// time synchronization in slow mode
#if SLOWMODE		// 1=run slow at real speed, 0=run fast at max speed
		u32 s = StepTime + STEPTIME; // time of next instruction
		StepTime = s; // save new time
		u32 t = Time(); // get current time
		s32 d = s - t;	// remaining time
		if (d < 0) d = -d; // absolute value
		if (d > 100*STEPTIME) // check synchronization (error max. 100*240us = 24ms)
		{
			// resynchronization if synchronization failure 
			StepTime = t;

#if 0
	// DEBUG: indicate lost synchronization
	int i;
	for (i = 0; i <	DISP_NUM; i++) DispBuf[i] = CH_SPC;
	DispBuf[1] = CH_C;
	DispUpdate();
	WaitMs(1000);
	DispBuf[1] = CH_SPC;
	DispUpdate();
#endif

		}
		else
		{
			// synchronize
			do {
				d = s - Time();
			} while (d > 0);
		}
#endif
	}
}
