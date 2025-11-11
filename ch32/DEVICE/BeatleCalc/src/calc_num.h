
// ****************************************************************************
//
//                      Calculator - Numeric operations
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// check if number is negative (returns True if number is negative; number need not be normalized)
INLINE Bool NumIsNeg(const sNum* num) { return num->mant[0] >= (SIGN_THRES << 4); }

// check if number is zero (returns True if number is zero)
INLINE Bool NumIsZero(const sNum* num) { return num->exp == EXP_0; }

// check if number is overflow (returns True if number is overflow)
INLINE Bool NumIsOver(const sNum* num) { return num->exp == EXP_OVER; }

// check if exponent is valid (returns True if number is in valid range)
INLINE Bool ExpIsValid(const sNum* num) { return (num->exp >= EXP_MIN) && (num->exp <= EXP_MAX); }

// set number to value 0 (content of the mantissa will remain random)
INLINE void NumSet0(sNum* num) { num->exp = EXP_0; }

// absolute value of the number
INLINE void NumAbs(sNum* num) { num->mant[0] &= 0x0f; }

// negate number - flip sign 0/9 if number is not zero (number must be in normalized form)
void NumNeg(sNum* num);

// exchange two numbers
void NumExc(sNum* num1, sNum* num2);

// copy number
void NumCopy(sNum* dst, const sNum* src);

// set number to value 1
void NumSet1(sNum* num);

// set number to value -1
void NumSetM1(sNum* num);

// set overflow (sets error; content of the mantissa will remain random)
void NumSetOver(sNum* num);

// set integer
void NumSetInt(sNum* num, s32 n);

// get integer (rounded towards zero)
s32 NumGetInt(const sNum* num);

// increment exponent (= multiply * 10)
void ExpInc(sNum* num);

// decrement exponent (= divide / 10)
void ExpDec(sNum* num);

// increment number
void NumInc(sNum* dst, sNum* src);

// decrement number
void NumDec(sNum* dst, sNum* src);

// subtract two numbers (num <- num1 - num2)
void NumSub(sNum* num, const sNum* num1, const sNum* num2);

// add two numbers (num <- num1 + num2)
void NumAdd(sNum* num, const sNum* num1, const sNum* num2);

// multiply two numbers (num <- num1 * num2)
void NumMul(sNum* num, const sNum* num1, const sNum* num2);

// divide two numbers (num <- num1 / num2)
void NumDiv(sNum* num, const sNum* num1, const sNum* num2);

// power (num <- num1 ^ num2)
void NumPow(sNum* num, const sNum* num1, const sNum* num2);

// root (num <- num1 root num2)
void NumRoot(sNum* num, const sNum* num1, const sNum* num2);

// check if numbers are equal (returns True if numbers are equal)
Bool NumEqu(const sNum* num1, const sNum* num2);

// truncate - round towards zero (= "integer" function)
void NumTrunc(sNum* num);

// fraction
void NumFrac(sNum* num);

// floor - round down
void NumFloor(sNum* num);

// mod two numbers (num <- num1 mod num2)
void NumMod(sNum* num, const sNum* num1, const sNum* num2);

// calculate ln(x)
void NumLn(sNum* num);

// calculate exp(x)
void NumExp(sNum* num);

// calculate log(x)
void NumLog(sNum* num);

// calculate exp10(x)
void NumExp10(sNum* num);

// calculate 1/x reciprocal
void NumRec(sNum* num);

// square root
void NumSqrt(sNum* num);

// square
void NumSqr(sNum* num);

// normalize angle to range -pi..+pi
void NumNormPi(sNum* num);

// sin
void NumSin(sNum* num);

// sind
void NumSind(sNum* num);

// cos
void NumCos(sNum* num);

// cosd
void NumCosd(sNum* num);

// tan
void NumTan(sNum* num);

// tand
void NumTand(sNum* num);

// asin
void NumASin(sNum* num);

// asind
void NumASind(sNum* num);

// acos
void NumACos(sNum* num);

// acosd
void NumACosd(sNum* num);

// atan
void NumATan(sNum* num);

// atand
void NumATand(sNum* num);

#ifdef __cplusplus
}
#endif
