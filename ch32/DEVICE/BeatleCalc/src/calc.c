
// ****************************************************************************
//
//                              Calculator
//
// ****************************************************************************

#include "../include.h"

// key level
int KeyLevel = KEYLEVEL_1ST;

// Error flag
Bool Error = False;

// set error
void SetError(void)
{
	Error = True;
}

// clear error
void ClearErr(void)
{
	if (Error)
	{
		Error = False;
		NumSet0(&RegX);
		EditBufClear();
		DispUpdate();
	}
}

// key execute table
const pKeyExec KeyExecList[KEY_NUM*3] = {
	// 1st key level
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
	ExecAdd,	// #define KEY_ADD	10	// +
	ExecSub,	// #define KEY_SUB	11	// -
	ExecMul,	// #define KEY_MUL	12	// *
	ExecDiv,	// #define KEY_DIV	13	// /
	ExecEqu,	// #define KEY_EQU	14	// =
	ExecDot,	// #define KEY_DOT	15	// .
	ExecEE,		// #define KEY_EE	16	// EE
	ExecCE,		// #define KEY_CE	17	// CE
	Exec2nd,	// #define KEY_2ND	18	// 2nd
	Exec3rd,	// #define KEY_3RD	19	// 3rd
	// 2nd key level
	ExecSqrt,	// #define KEY_0	0	// 0 sqrt
	ExecTrunc,	// #define KEY_1	1	// 1 int
	ExecPow,	// #define KEY_2	2	// 2 power
	ExecCosd,	// #define KEY_3	3	// 3 cosd
	ExecSto,	// #define KEY_4	4	// 4 STO3
	ExecSto,	// #define KEY_5	5	// 5 STO4
	ExecLn,		// #define KEY_6	6	// 6 ln
	ExecSto,	// #define KEY_7	7	// 7 STO1
	ExecSto,	// #define KEY_8	8	// 8 STO2
	ExecTand,	// #define KEY_9	9	// 9 tand
	ExecSin,	// #define KEY_ADD	10	// + sin
	ExecCos,	// #define KEY_SUB	11	// - cos
	ExecLog,	// #define KEY_MUL	12	// * log
	ExecTan,	// #define KEY_DIV	13	// / tan
	ExecLPar,	// #define KEY_EQU	14	// = (
	ExecNeg,	// #define KEY_DOT	15	// . +/-
	ExecSind,	// #define KEY_EE	16	// EE sind
	ExecMod,	// #define KEY_CE	17	// CE mod
	Exec1st,	// #define KEY_2ND	18	// 2nd
	Exec3rd,	// #define KEY_3RD	19	// 3rd
	// 3rd key level
	ExecSqr,	// #define KEY_0	0	// 0 x^2
	ExecFrac,	// #define KEY_1	1	// 1 frac
	ExecRoot,	// #define KEY_2	2	// 2 root
	ExecACosd,	// #define KEY_3	3	// 3 acosd
	ExecRcl,	// #define KEY_4	4	// 4 RCL3
	ExecRcl,	// #define KEY_5	5	// 5 RCL4
	ExecExp,	// #define KEY_6	6	// 6 exp
	ExecRcl,	// #define KEY_7	7	// 7 RCL1
	ExecRcl,	// #define KEY_8	8	// 8 RCL2
	ExecATand,	// #define KEY_9	9	// 9 atand
	ExecASin,	// #define KEY_ADD	10	// + asin
	ExecACos,	// #define KEY_SUB	11	// - acos
	ExecExp10,	// #define KEY_MUL	12	// * exp10
	ExecATan,	// #define KEY_DIV	13	// / atan
	ExecRPar,	// #define KEY_EQU	14	// = )
	ExecRec,	// #define KEY_DOT	15	// . 1/x
	ExecASind,	// #define KEY_EE	16	// EE asind
	ExecPi,		// #define KEY_CE	17	// CE pi
	Exec2nd,	// #define KEY_2ND	18	// 2nd
	Exec1st,	// #define KEY_3RD	19	// 3rd
};

// Debug - disp HEX number
   // DispHex(num1); WaitMs(100000000);
void DispHex(const sNum* num)
{
	const u8* s = (const u8*)num;
	int i;
	u8* d = DispBuf;
	for (i = 4; i > 0; i--)
	{
		*d++ = (*s >> 4) + CH_0;
		*d++ = (*s & 0x0f) + CH_0;
		s++;
		if (i == 4) *d++ = CH_SPC;
	}
	DispUpdate();
}

// Run calculator
void RunCalc(void)
{
	u8 key;

	// initialize calculator
	CalcStkNum = 0;			// number of entries in calculator and operator stack
	Error = False;			// clear error

	// clear registers
	NumSet0(&RegX);
	NumSet0(&RegLast);

	// clear edit buffer
	EditBufClear();
	DispUpdate();

	// calculator loop
	while (True)
	{
		// get key
		key = KeyGet();

		// key execute
		if (key != NOKEY)
		{
			// key execute
			KeyExecList[KEY_NUM*KeyLevel+key](key);

			// skip on 2nd and 3rd
			if ((key != KEY_2ND) && (key != KEY_3RD))
			{
				// reset key level
				Exec1st(0);

				// display update edit buffer
				DispUpdate();
			}
		}
	}
}
