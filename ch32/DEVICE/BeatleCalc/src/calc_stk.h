
// ****************************************************************************
//
//                          Calculator - Stack
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// calculator stack
extern sNum CalcStk[STK_NUM];		// calculator stack
extern u8 OperStk[STK_NUM];		// operations stack
extern int CalcStkNum;			// number of entries in calculator and operations stack

// get last number on calculator stack
sNum* CalcTop(void);

// get pre-last number on calculator stack
sNum* CalcPreTop(void);

// get pre2-last number on calculator stack
sNum* CalcPre2Top(void);

// create new entry on end of calculator stack
sNum* CalcNew(void);

// push number to calculator stack
void CalcPush(const sNum* num);

// stop edit, push register X to calculator stack
void CalcPushX();

// push integer number to calculator stack
void CalcPushInt(s32 n);

// pop number from calculator stack, delete number from the stack
void CalcPop(sNum* num);

// pop number from calculator stack, decode result and delete number from the stack
void CalcPopX();

// delete entry in calculator stack
void CalcDel(void);

// duplicate number on top of calculator stack
void CalcDup(void);

// duplicate number on pre-top of calculator stack
void CalcDup2(void);

// exchange two number on top of calculator stack
void CalcExc(void);

// exchange top and pre2-top numbers on calculator stack
void CalcExc2(void);

// negate number on top of calculator stack
void CalcNeg();

// absolute value of the number on top of calculator stack
void CalcAbs();

// subtract two numbers on calculator stack (pre-top = pre-top - top, deletes top number)
void CalcSub();

// add two numbers on calculator stack (pre-top = pre-top + top, deletes top number)
void CalcAdd();

// multiply two numbers on calculator stack (pre-top = pre-top * top, deletes top number)
void CalcMul();

// divide two numbers on calculator stack (pre-top = pre-top / top, deletes top number)
void CalcDiv();

// mod two numbers on calculator stack (pre-top = pre-top mod top, deletes top number)
void CalcMod();

// power two numbers on calculator stack (pre-top = pre-top ^ top, deletes top number)
void CalcPow();

// root two numbers on calculator stack (pre-top = pre-top root top, deletes top number)
void CalcRoot();

// decode number from calculator stack and destroy the number from calculator stack
void CalcDisp();

// set operation of operand on top of calculator stack
void SetOper(u8 op);

// get operation of operand on top of calculator stack (returns 0 if no operand)
u8 GetOper(void);

// get operation of operand on pre-top of calculator stack (returns 0 if less than 2 operands)
u8 GetPreOper(void);

#ifdef __cplusplus
}
#endif
