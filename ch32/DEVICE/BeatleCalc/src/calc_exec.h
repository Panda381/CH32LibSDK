
// ****************************************************************************
//
//                          Calculator - Execute
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// Registers
extern sNum RegX, RegLast;
extern u8 OperLast;	// last operation (0 = not valid)

// slot with memory
typedef union {
	sNum RegM[10]; // memory slots 0..9
	sSlot	slot;
} uMem;

extern uMem Mem;

// invalid key function
void ExecNone(u8 key);

// set 1st key level
void Exec1st(u8 key);

// set 2nd key level
void Exec2nd(u8 key);

// set 3rd key level
void Exec3rd(u8 key);

// Calculate one level of arithmetics operations
void ExecCalc();

// add +
void ExecAdd(u8 key);

// sub -
void ExecSub(u8 key);

// mul *
void ExecMul(u8 key);

// div /
void ExecDiv(u8 key);

// mod
void ExecMod(u8 key);

// power Y^x
void ExecPow(u8 key);

// root Y^(1/x)
void ExecRoot(u8 key);

// result =
void ExecEqu(u8 key);

// left parenthesis '('
void ExecLPar(u8 key);

// right parenthesis ')'
void ExecRPar(u8 key);

// truncate - round towards zero (= "integer" function)
void ExecTrunc(u8 key);

// fraction
void ExecFrac(u8 key);

// floor - round down
void ExecFloor(u8 key);

// ln
void ExecLn(u8 key);

// exp
void ExecExp(u8 key);

// log
void ExecLog(u8 key);

// exp10
void ExecExp10(u8 key);

// pi
void ExecPi(u8 key);

// 1/x reciprocal
void ExecRec(u8 key);

// square root
void ExecSqrt(u8 key);

// square
void ExecSqr(u8 key);

// sin
void ExecSin(u8 key);

// sind
void ExecSind(u8 key);

// cos
void ExecCos(u8 key);

// cosd
void ExecCosd(u8 key);

// tan
void ExecTan(u8 key);

// tand
void ExecTand(u8 key);

// asin
void ExecASin(u8 key);

// asind
void ExecASind(u8 key);

// acos
void ExecACos(u8 key);

// acosd
void ExecACosd(u8 key);

// atan
void ExecATan(u8 key);

// atand
void ExecATand(u8 key);

// STO1..STO4
void ExecSto(u8 key);

// RCL1..RCL4
void ExecRcl(u8 key);

#ifdef __cplusplus
}
#endif
