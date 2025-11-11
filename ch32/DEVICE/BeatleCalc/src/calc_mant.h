
// ****************************************************************************
//
//                      Calculator - Mantissa operations
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// check if mantissa is negative (returns True if mantissa is negative)
INLINE Bool MantIsNeg(const sNum* num) { return num->mant[0] >= (SIGN_THRES << 4); }

// check if denormalized mantissa is zero (returns True if mantissa is zero)
Bool MantIsZero(const sNum* num);

// invert denormalized mantissa (nines' complement: 9 - x)
void MantNot(sNum* num);

// add digit 0..10 to denormalized mantissa (returns carry 0 or 1)
u8 MantAddDig(sNum* num, u8 carry);

// subtract digit 0..10 from denormalized mantissa (returns borrow 0 or 1)
u8 MantSubDig(sNum* num, u8 borrow);

// increment denormalized mantissa (add 1 to lowest digit; returns carry 0 or 1)
u8 MantInc(sNum* num);

// decrement denormalized mantissa (subtract 1 from lowest digit; returns borrow 0 or 1)
u8 MantDec(sNum* num);

// negate denormalized mantissa (tens' complement: 9 - x + 1 = 10 - x)
void MantNeg(sNum* num);

// sum two denormalized mantissas and carry (dst <- src1 + src2 + carry; src and dst can be the same; returns carry 0 or 1)
u8 MantAdd(sNum* dst, const sNum* src1, const sNum* src2, u8 carry);

// subtract two denormalized mantissas and borrow (dst <- src1 - src2 - borrow; src and dst can be the same; returns borrow 0 or 1)
u8 MantSub(sNum* dst, const sNum* src1, const sNum* src2, u8 borrow);

// shift denormalized mantissa right by 1 position (insert new highest digit, returns old lowest digit)
u8 MantRight(sNum* num, u8 dig);

// shift denormalized mantissa right by 1 position, signed - repeat sign digit (returns old lowest digit)
u8 MantRightS(sNum* num);

// shift denormalized mantissa left by 1 position (insert new lowest digit, returns old highest digit)
u8 MantLeft(sNum* num, u8 dig);

// shift denormalized mantissa left by 1 position (insert 0 to lowest digit, returns old highest digit)
u8 MantLeft0(sNum* num);

// compare positive denormalized mantissas (returns: -1 if num1<num2, 0 if num1=num2, +1 if num1>num2)
int MantComp(const sNum* num1, const sNum* num2);

#ifdef __cplusplus
}
#endif
