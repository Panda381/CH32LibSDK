
// ****************************************************************************
//
//                          Calculator - Execute
//
// ****************************************************************************

#include "../include.h"

// Registers
sNum RegX, RegLast;
u8 OperLast = 0;	// last operation (0 = not valid)

// slot with memory
uMem Mem;

// invalid key function
void ExecNone(u8 key) { }

// set 1st key level
void Exec1st(u8 key)
{
	KeyLevel = KEYLEVEL_1ST;
	FrameBuf[0] |= SA|SD; // clear 2nd and 3rd flag
}

// set 2nd key level
void Exec2nd(u8 key)
{
	KeyLevel = KEYLEVEL_2ND;
	FrameBuf[0] |= SD; // clear 3rd flag
	FrameBuf[0] &= ~SA; // set 2nd flag
}

// set 3rd key level
void Exec3rd(u8 key)
{
	KeyLevel = KEYLEVEL_3RD;
	FrameBuf[0] |= SA; // clear 2nd flag
	FrameBuf[0] &= ~SD; // set 3rd flag
}

// apply arithmetics operator (op = combination of OPER_* and PRIO_*)
void ExecOp(u8 op)
{
	u8 op2, prio, prio2;

	// stop edit, push register X to calculator stack
	CalcPushX();
	if (Error) return; // error

	// save last operation, if previous operator is valid
	op2 = GetPreOper();
	prio2 = op2 >> PRIO_SHIFT;
	if (prio2 != 0)
	{
		OperLast = op2;
		NumCopy(&RegLast, &RegX);
	}

	// process higher operators
	prio = op >> PRIO_SHIFT;
	for (;;)
	{
		// get previous operator, or 0 if no operand
		op2 = GetPreOper();
		prio2 = op2 >> PRIO_SHIFT;

		// new priority is lower or equal - proces previous operator
		if (prio <= prio2)
		{
			// end of expression
			if (prio2 == 0)
			{
				// save result to X, decode and delete number
				CalcPopX();

				// if stack is not empty, delete parenthessis entry
				if (CalcStkNum > 0) CalcDel();

				// parenthesis ( ), exit
				if ((op & OPER_MASK) == OPER_RPAR) return;

				// result '=', exit if stack is empty
				if (CalcStkNum == 0) return;

				// otherwise continue
				continue;
			}

			// perform previous operation
			switch (op2 & OPER_MASK)
			{
			// +
			case OPER_ADD: CalcAdd(); break;

			// -
			case OPER_SUB: CalcSub(); break;

			// *
			case OPER_MUL: CalcMul(); break;

			// /
			case OPER_DIV: CalcDiv(); break;

			// mod
			case OPER_MOD: CalcMod(); break;

			// Y^x power
			case OPER_PWR: CalcPow(); break;

			// root
			case OPER_ROOT: CalcRoot(); break;

			// no operation - only delete 2nd operand
			default:
				CalcDel();
				break;
			}

			// save result to X
			NumCopy(&RegX, CalcTop());
		}

		// current priority is higher (prior > prior2), go deeper
		else
			break;
	 }

	// set operation
	SetOper(op);

	// decode register X to display result
	CalcPush(&RegX);
	NumDecode(CalcTop());
	CalcDel();
}

// add +
void ExecAdd(u8 key)
{
	ExecOp(OPER_ADD | (PRIO_ADDSUB << PRIO_SHIFT));
}

// sub -
void ExecSub(u8 key)
{
	ExecOp(OPER_SUB | (PRIO_ADDSUB << PRIO_SHIFT));
}

// mul *
void ExecMul(u8 key)
{
	ExecOp(OPER_MUL | (PRIO_MULDIV << PRIO_SHIFT));
}

// div /
void ExecDiv(u8 key)
{
	ExecOp(OPER_DIV | (PRIO_MULDIV << PRIO_SHIFT));
}

// mod
void ExecMod(u8 key)
{
	ExecOp(OPER_MOD | (PRIO_MULDIV << PRIO_SHIFT));
}

// power Y^x
void ExecPow(u8 key)
{
	ExecOp(OPER_PWR | (PRIO_PWR << PRIO_SHIFT));
}

// root Y^(1/x)
void ExecRoot(u8 key)
{
	ExecOp(OPER_ROOT | (PRIO_PWR << PRIO_SHIFT));
}

// result =
void ExecEqu(u8 key)
{
	// no operation in stack - repeat last operation
	if (CalcStkNum == 0)
	{
		if (OperLast == 0) return; // no last operation
		ExecOp(OperLast);
		NumCopy(&RegX, &RegLast);
	}
	ExecOp(OPER_EQU | (PRIO_NONE << PRIO_SHIFT));
}

// left parenthesis '('
void ExecLPar(u8 key)
{
	// create new entry in the stack (its content is not used)
	CalcNew();
	if (Error) return; // error

	// set operation
	SetOper(OPER_LPAR | (PRIO_NONE << PRIO_SHIFT));
}

// right parenthesis ')'
void ExecRPar(u8 key)
{
	ExecOp(OPER_RPAR | (PRIO_NONE << PRIO_SHIFT));
}

// truncate - round towards zero (= "integer" function)
void ExecTrunc(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate trunc
	NumTrunc(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// fraction
void ExecFrac(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate frac
	NumFrac(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// floor - round down
void ExecFloor(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate floor
	NumFloor(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// ln
void ExecLn(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate ln
	NumLn(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// exp
void ExecExp(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate exp
	NumExp(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// log
void ExecLog(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate log
	NumLog(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// exp10
void ExecExp10(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate exp10
	NumExp10(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// pi
void ExecPi(u8 key)
{
	// stop edit
	EditStop();

	// push pi
	CalcPush(&ConstPi);

	// save result to X, decode and delete number
	CalcPopX();
}

// 1/x reciprocal
void ExecRec(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate 1/x
	NumRec(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// square root
void ExecSqrt(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate sqrt
	NumSqrt(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// square
void ExecSqr(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate sqr
	NumSqr(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// sin
void ExecSin(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate sin
	NumSin(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// sind
void ExecSind(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate sind
	NumSind(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// cos
void ExecCos(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate cos
	NumCos(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// cosd
void ExecCosd(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate cosd
	NumCosd(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// tan
void ExecTan(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate tan
	NumTan(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// tand
void ExecTand(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate tand
	NumTand(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// asin
void ExecASin(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate asin
	NumASin(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// asind
void ExecASind(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate asind
	NumASind(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// acos
void ExecACos(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate acos
	NumACos(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// acosd
void ExecACosd(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate acosd
	NumACosd(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// atan
void ExecATan(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate atan
	NumATan(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// atand
void ExecATand(u8 key)
{
	// stop edit, push register X to calculator stack
	CalcPushX();

	// calculate atand
	NumATand(CalcTop());

	// save result to X, decode and delete number
	CalcPopX();
}

// STO1..STO4
void ExecSto(u8 key)
{
	// stop edit
	EditStop();

	// copy register X to Mem
	NumCopy(&Mem.RegM[key], &RegX);

	// save memory
	WriteSlot(&Mem.slot, 0);
}

// RCL1..RCL4
void ExecRcl(u8 key)
{
	// stop edit
	EditStop();

	// push Mem
	CalcPush(&Mem.RegM[key]);

	// save result to X, decode and delete number
	CalcPopX();
}
