
// ****************************************************************************
//
//                          Calculator - Stack
//
// ****************************************************************************

#include "../include.h"

// calculator stack
sNum CalcStk[STK_NUM];			// calculator stack
u8 OperStk[STK_NUM];			// operations stack
int CalcStkNum = 0;			// number of entries in calculator and operations stack

// get last number on calculator stack
sNum* CalcTop(void)
{
	return &CalcStk[CalcStkNum-1];
}

// get pre-last number on calculator stack
sNum* CalcPreTop(void)
{
	return &CalcStk[CalcStkNum-2];
}

// get pre2-last number on calculator stack
sNum* CalcPre2Top(void)
{
	return &CalcStk[CalcStkNum-3];
}

// create new entry on end of calculator stack
sNum* CalcNew(void)
{
	// overflow
	int n = CalcStkNum;
	if (n >= STK_NUM)
	{
		SetError();
		return &CalcStk[STK_NUM-1];
	}

	// add entry
	CalcStkNum = n + 1;
	return &CalcStk[n];
}

// push number to calculator stack
void CalcPush(const sNum* num)
{
	sNum* dst = CalcNew();
	NumCopy(dst, num);
}

// push integer number to calculator stack
void CalcPushInt(s32 n)
{
	sNum* num = CalcNew();
	NumSetInt(num, n);
}

// stop edit, push register X to calculator stack
void CalcPushX()
{
	EditStop();
	CalcPush(&RegX);
}

// pop number from calculator stack, delete number from the stack
void CalcPop(sNum* num)
{
	NumCopy(num, CalcTop());
	CalcDel();
}

// pop number from calculator stack, decode result and delete number from the stack
void CalcPopX()
{
	NumCopy(&RegX, CalcTop());
	NumDecode(CalcTop());
	CalcDel();
}

// delete entry in calculator stack
void CalcDel(void)
{
	CalcStkNum--;
}

// duplicate number on top of calculator stack
void CalcDup(void)
{
	// create new entry
	sNum* num = CalcNew();

	// copy number
	NumCopy(CalcTop(), CalcPreTop());
}

// duplicate number on pre-top of calculator stack
void CalcDup2(void)
{
	// create new entry
	sNum* num = CalcNew();

	// copy number
	NumCopy(CalcTop(), CalcPre2Top());
}

// exchange top and pre-top numbers on calculator stack
void CalcExc(void)
{
	NumExc(CalcTop(), CalcPreTop());
}

// exchange top and pre2-top numbers on calculator stack
void CalcExc2(void)
{
	NumExc(CalcTop(), CalcPre2Top());
}

// negate number on top of calculator stack
void CalcNeg()
{
	NumNeg(CalcTop());
}

// absolute value of the number on top of calculator stack
void CalcAbs()
{
	sNum* num = CalcTop();
	if (NumIsNeg(num)) NumNeg(num);
}

// subtract two numbers on calculator stack (pre-top = pre-top - top, deletes top number)
void CalcSub()
{
	NumSub(CalcPreTop(), CalcPreTop(), CalcTop());
	CalcDel();
}

// add two numbers on calculator stack (pre-top = pre-top + top, deletes top number)
void CalcAdd()
{
	NumAdd(CalcPreTop(), CalcPreTop(), CalcTop());
	CalcDel();
}

// multiply two numbers on calculator stack (pre-top = pre-top * top, deletes top number)
void CalcMul()
{
	NumMul(CalcPreTop(), CalcPreTop(), CalcTop());
	CalcDel();
}

// divide two numbers on calculator stack (pre-top = pre-top / top, deletes top number)
void CalcDiv()
{
	NumDiv(CalcPreTop(), CalcPreTop(), CalcTop());
	CalcDel();
}

// mod two numbers on calculator stack (pre-top = pre-top mod top, deletes top number)
void CalcMod()
{
	NumMod(CalcPreTop(), CalcPreTop(), CalcTop());
	CalcDel();
}

// power two numbers on calculator stack (pre-top = pre-top ^ top, deletes top number)
void CalcPow()
{
	NumPow(CalcPreTop(), CalcPreTop(), CalcTop());
	CalcDel();
}

// root two numbers on calculator stack (pre-top = pre-top root top, deletes top number)
void CalcRoot()
{
	NumRoot(CalcPreTop(), CalcPreTop(), CalcTop());
	CalcDel();
}

// decode number from calculator stack and destroy the number from calculator stack
void CalcDisp()
{
	NumDecode(CalcTop());
	CalcDel();
}

// set operation of operand on top of calculator stack
void SetOper(u8 op)
{
	int i = CalcStkNum;
	if (i != 0) OperStk[i-1] = op;
}

// get operation of operand on top of calculator stack (returns 0 if no operand)
u8 GetOper(void)
{
	int i = CalcStkNum;
	if (i == 0) return 0;
	return OperStk[i-1];
}

// get operation of operand on pre-top of calculator stack (returns 0 if less than 2 operands)
u8 GetPreOper(void)
{
	int i = CalcStkNum;
	if (i < 2) return 0;
	return OperStk[i-2];
}
