
// ****************************************************************************
//
//                          Calculator - Execute
//
// ****************************************************************************

#include "../include.h"

// calculator stack
sNum CalcStk[STK_NUM];			// calculator stack

// memory slot
uMem Mem;

// clear calculator stack
void CalcStkClear()
{
	memset(CalcStk, 0, sizeof(CalcStk));
}

// delete 2nd entry in calculator stack (after operation)
void CalcStkPop()
{
	// copy calculator stack up
	memmove(&CalcStk[1], &CalcStk[2], (STK_NUM-2)*sizeof(sNum));

	// clear top register
	memset(&CalcStk[STK_NUM-1], 0, sizeof(sNum));

	// display new registers
	DispReg(1);
	DispReg(2);
	DispReg(3);
}

// invalid key function
void ExecNone(u8 key) { }

// C
void ExecC(u8 key)
{
	EditStop();
	CalcStkClear();
	CalcStkPop();
}

// set key level
void ExecLevel(u8 key)
{
	key = (key+1)/KEY_NUM;
	if (key > KEYLEVEL_NUM-1) key = 0;
	KeyLevel = key;
	DispKeyLevel();
}

// set RAD/DEG
void ExecDeg(u8 key)
{
	AngleUnitDeg = !AngleUnitDeg;
	DispAngleUnit();
	WriteMem();
}

// Enter
void ExecEnter(u8 key)
{
	// stop edit mode
	EditStop();

	// copy calculator stack up
	memmove(&CalcStk[1], &CalcStk[0], (STK_NUM-1)*sizeof(sNum));

	// display new registers
	DispReg(1);
	DispReg(2);
	DispReg(3);
}

// exchange registers X and Y
void ExecXY(u8 key)
{
	// stop edit mode
	EditStop();

	// exchange registers
	NumExc(&RegX, &RegY);

	// display register Y
	DispReg(1);
}

// add numbers
void ExecAdd(u8 key)
{
	// stop edit mode
	EditStop();

	// add numbers
	NumAdd(&RegX, &RegY, &RegX);

	// delete register Y
	CalcStkPop();
}

// sub numbers
void ExecSub(u8 key)
{
	// stop edit mode
	EditStop();

	// sub numbers
	NumSub(&RegX, &RegY, &RegX);

	// delete register Y
	CalcStkPop();
}

// mul numbers
void ExecMul(u8 key)
{
	// stop edit mode
	EditStop();

	// mul numbers
	NumMul(&RegX, &RegY, &RegX);

	// delete register Y
	CalcStkPop();
}

// div numbers
void ExecDiv(u8 key)
{
	// stop edit mode
	EditStop();

	// div numbers
	NumDiv(&RegX, &RegY, &RegX);

	// delete register Y
	CalcStkPop();
}

// pwr numbers
void ExecPwr(u8 key)
{
	// stop edit mode
	EditStop();

	// pwr numbers
	NumPow(&RegX, &RegY, &RegX);

	// delete register Y
	CalcStkPop();
}

// ln
void ExecLn(u8 key)
{
	EditStop();
	NumLn(&RegX);
}

// log
void ExecLog(u8 key)
{
	EditStop();
	NumLog(&RegX);
}

// exp
void ExecExp(u8 key)
{
	EditStop();
	NumExp(&RegX);
}

// exp10
void ExecExp10(u8 key)
{
	EditStop();
	NumExp10(&RegX);
}

// 1/x
void ExecRec(u8 key)
{
	EditStop();
	NumRec(&RegX);
}

// store memory
void ExecSto(u8 key)
{
	// stop edit
	EditStop();

	// memory index
	int inx = key - KEY_STO0;

	// copy number to memory
	NumCopy(&Mem.mem[inx], &RegX);

	// write memory to flash
	WriteMem();
}

// recall memory
void ExecRcl(u8 key)
{
	// stop edit
	EditStop();

	// memory index
	int inx = key - KEY_RCL0;

	// copy number from memory
	NumCopy(&RegX, &Mem.mem[inx]);
}

// pi
void ExecPi(u8 key)
{
	EditStop();
	NumCopy(&RegX, &ConstPi);
}

// sqrt
void ExecSqrt(u8 key)
{
	EditStop();
	NumSqrt(&RegX);
}	

// sin
void ExecSin(u8 key)
{
	EditStop();
	if (AngleUnitDeg) NumMul(&RegX, &RegX, &ConstPi180);
	NumSin(&RegX);
}

// cos
void ExecCos(u8 key)
{
	EditStop();
	if (AngleUnitDeg) NumMul(&RegX, &RegX, &ConstPi180);
	NumCos(&RegX);
}

// tan
void ExecTan(u8 key)
{
	EditStop();
	if (AngleUnitDeg) NumMul(&RegX, &RegX, &ConstPi180);
	NumTan(&RegX);
}

// asin
void ExecASin(u8 key)
{
	EditStop();
	NumASin(&RegX);
	if (AngleUnitDeg) NumMul(&RegX, &RegX, &Const180Pi);
}

// acos
void ExecACos(u8 key)
{
	EditStop();
	NumACos(&RegX);
	if (AngleUnitDeg) NumMul(&RegX, &RegX, &Const180Pi);
}

// atan
void ExecATan(u8 key)
{
	EditStop();
	NumATan(&RegX);
	if (AngleUnitDeg) NumMul(&RegX, &RegX, &Const180Pi);
}

// int
void ExecInt(u8 key)
{
	EditStop();
	NumTrunc(&RegX);
}

// programming
void ExecPrg(u8 key)
{
	// program index
	int inx = key - KEY_PRG0;

	// start programming
	if (Programming == 0)
	{
		Programming = inx + 1;
		Mem.progsize[inx] = 0; // reset program
	}

	// stop programming
	else
	{
		WriteMem();
		Programming = 0;
		DispBat();
	}
}

// running
void ExecRun(u8 key)
{
	// program index
	int inx = key - KEY_RUN0;

	// start running
	Running = Mem.progsize[inx];
	RunningPtr = Mem.prog + inx*PROGSIZE;
}

// key execute table
const pKeyExec KeyExecList[KEYFNC_NUM] = {
	// --- 1st digits
	ExecDig,	// #define KEY_0	0	// 0
	ExecDig,	// #define KEY_1	1	// 1
	ExecDig,	// #define KEY_2	2	// 2
	ExecDig,	// #define KEY_3	3	// 3
	ExecDig,	// #define KEY_4	4	// 4
	ExecDig,	// #define KEY_5	5	// 5
	ExecDig,	// #define KEY_6	6	// 6
	ExecDig,	// #define KEY_7	7	// 7
	ExecDig,	// #define KEY_8	8	// 8
	ExecDig,	// #define KEY_9	9	// 9
	ExecDot,	// #define KEY_DOT	10	// .
	ExecLevel,	// #define KEY_2ND	11	// 2nd
	// --- 2nd operators
	ExecAdd,	// #define KEY_ADD	12	// + (2nd 0)
	ExecSub,	// #define KEY_SUB	13	// - (2nd 1)
	ExecMul,	// #define KEY_MUL	14	// * (2nd 2)
	ExecDiv,	// #define KEY_DIV	15	// / (2nd 3)
	ExecPwr,	// #define KEY_PWR	16	// Yx (2nd 4)
	ExecXY,		// #define KEY_XY	17	// Y/X (2nd 5)
	ExecSqrt,	// #define KEY_SQRT	16	// sqrt (2nd 6)
	ExecEnter,	// #define KEY_ENTER	19	// Enter (2nd 7)
	ExecCE,		// #define KEY_CE	20	// CE (2nd 8)
	ExecEE,		// #define KEY_EE	21	// EE (2nd 9)
	ExecNeg,	// #define KEY_NEG	22	// +/- (2nd .)
	ExecLevel,	// #define KEY_3RD	23	// 3rd (2nd 2nd)
	// --- 3rd functions
	ExecSin,	// #define KEY_SIN	24	// sin (3rd 0)
	ExecASin,	// #define KEY_ASIN	25	// asin (3rd 1)
	ExecLog,	// #define KEY_LOG	26	// log (3rd 2)
	ExecLn,		// #define KEY_LN	27	// ln (3rd 3)
	ExecCos,	// #define KEY_COS	28	// cos (3rd 4)
	ExecACos,	// #define KEY_ACOS	29	// acos (3rd 5)
	ExecExp10,	// #define KEY_EXP10	30	// exp10 (3rd 6)
	ExecExp,	// #define KEY_EXP	31	// exp (3rd 7)
	ExecTan,	// #define KEY_TAN	32	// tan (3rd 8)
	ExecATan,	// #define KEY_ATAN	33	// atan (3rd 9)
	ExecRec,	// #define KEY_REC	34	// 1/x (3rd .)
	ExecLevel,	// #define KEY_4TH	35	// 4th (3rd 2nd)
	// --- 4th RCL
	ExecRcl,	// #define KEY_RCL0	36	// RCL0 (4th 0)
	ExecRcl,	// #define KEY_RCL1	37	// RCL1 (4th 1)
	ExecRcl,	// #define KEY_RCL2	38	// RCL2 (4th 2)
	ExecRcl,	// #define KEY_RCL3	39	// RCL3 (4th 3)
	ExecRcl,	// #define KEY_RCL4	40	// RCL4 (4th 4)
	ExecRcl,	// #define KEY_RCL5	41	// RCL5 (4th 5)
	ExecRcl,	// #define KEY_RCL6	42	// RCL6 (4th 6)
	ExecRcl,	// #define KEY_RCL7	43	// RCL7 (4th 7)
	ExecRcl,	// #define KEY_RCL8	44	// RCL8 (4th 8)
	ExecRcl,	// #define KEY_RCL9	45	// RCL9 (4th 9)
	ExecPi,		// #define KEY_PI	46	// pi (4th .)
	ExecLevel,	// #define KEY_5TH	47	// 5th (4th 2nd)
	// --- 5th STO
	ExecSto,	// #define KEY_STO0	48	// STO0 (5th 0)
	ExecSto,	// #define KEY_STO1	49	// STO1 (5th 1)
	ExecSto,	// #define KEY_STO2	50	// STO2 (5th 2)
	ExecSto,	// #define KEY_STO3	51	// STO3 (5th 3)
	ExecSto,	// #define KEY_STO4	52	// STO4 (5th 4)
	ExecSto,	// #define KEY_STO5	53	// STO5 (5th 5)
	ExecSto,	// #define KEY_STO6	54	// STO6 (5th 6)
	ExecSto,	// #define KEY_STO7	55	// STO7 (5th 7)
	ExecSto,	// #define KEY_STO8	56	// STO8 (5th 8)
	ExecSto,	// #define KEY_STO9	57	// STO9 (5th 9)
	ExecDeg,	// #define KEY_REG	58	// deg (5th .)
	ExecLevel,	// #define KEY_1ST	59	// 1st (5th 2nd)
	// --- 6th RUN
	ExecRun,	// #define KEY_RUN0	60	// RUN0 (6th 0)
	ExecRun,	// #define KEY_RUN1	61	// RUN1 (6th 1)
	ExecRun,	// #define KEY_RUN2	62	// RUN2 (6th 2)
	ExecRun,	// #define KEY_RUN3	63	// RUN3 (6th 3)
	ExecRun,	// #define KEY_RUN4	64	// RUN4 (6th 4)
	ExecRun,	// #define KEY_RUN5	65	// RUN5 (6th 5)
	ExecRun,	// #define KEY_RUN6	66	// RUN6 (6th 6)
	ExecRun,	// #define KEY_RUN7	67	// RUN7 (6th 7)
	ExecRun,	// #define KEY_RUN8	68	// RUN8 (6th 8)
	ExecRun,	// #define KEY_RUN9	69	// RUN9 (6th 9)
	ExecInt,	// #define KEY_INT	70	// INT (6th .)
	ExecLevel,	// #define KEY_7TH	71	// 7th (6th 2nd)
	// --- 7th PROG
	ExecPrg,	// #define KEY_PRG0	72	// PRG0 (7th 0)
	ExecPrg,	// #define KEY_PRG1	73	// PRG1 (7th 1)
	ExecPrg,	// #define KEY_PRG2	74	// PRG2 (7th 2)
	ExecPrg,	// #define KEY_PRG3	75	// PRG3 (7th 3)
	ExecPrg,	// #define KEY_PRG4	76	// PRG4 (7th 4)
	ExecPrg,	// #define KEY_PRG5	77	// PRG5 (7th 5)
	ExecPrg,	// #define KEY_PRG6	78	// PRG6 (7th 6)
	ExecPrg,	// #define KEY_PRG7	79	// PRG7 (7th 7)
	ExecPrg,	// #define KEY_PRG8	80	// PRG8 (7th 8)
	ExecPrg,	// #define KEY_PRG9	81	// PRG9 (7th 9)
	ExecC,		// #define KEY_C	82	// C (7th .)     
	ExecLevel,	// #define KEY_1ST	83	// 1st (7th 2nd)
};
