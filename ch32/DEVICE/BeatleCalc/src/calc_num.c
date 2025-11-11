
// ****************************************************************************
//
//                      Calculator - Numeric operations
//
// ****************************************************************************

#include "../include.h"

// temporaries
sNum NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5;
sNum NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2;

// negate number - flip sign 0/9 if number is not zero (number must be in normalized form)
void NumNeg(sNum* num)
{
	if (!NumIsZero(num)) num->mant[0] ^= ((SIGN_POS ^ SIGN_NEG) << 4);
}

// exchange two numbers
void NumExc(sNum* num1, sNum* num2)
{
	// exchange exponents
	tEXP k = num1->exp;
	num1->exp = num2->exp;
	num2->exp = k;

	// exchange mantissas
	u8* m1 = num1->mant;
	u8* m2 = num2->mant;
	int i;
	for (i = 0; i < MANTBYTES; i++)
	{
		u8 b = m1[i];
		m1[i] = m2[i];
		m2[i] = b;
	}
}

// copy number
void NumCopy(sNum* dst, const sNum* src)
{
	memcpy(dst, src, sizeof(sNum));
}

// set number to value 1
void NumSet1(sNum* num)
{
	NumCopy(num, &Const1);
}

// set number to value -1
void NumSetM1(sNum* num)
{
	NumCopy(num, &ConstM1);
}

// set overflow (sets error; content of the mantissa will remain random)
void NumSetOver(sNum* num)
{
	num->exp = EXP_OVER;
	SetError();
}

// set integer
// - use FASTCODE to divide number /10 using multipy
FASTCODE void NumSetInt(sNum* num, s32 n)
{
	// prepare sign
	// Note: do not decode with s32, it may remain negative with 0x80000000
	u8 sign = (SIGN_POS << 4);
	u32 nn = (u32)n;
	if (n < 0)
	{
		sign = (SIGN_NEG << 4);
		nn = (u32)-n;
	}

	// clear number
	memset(num, 0, sizeof(sNum));
	int e = -1;

	// decode number
	do {
		MantRightS(num);
		u32 nn2 = nn / 10;
		u8 dig = nn - nn2*10;
		num->mant[0] = dig;
		nn = nn2;
		e++;
	} while (nn != 0);

	// set exponent and sign
	num->exp = e;
	num->mant[0] |= sign;
}

// get integer (rounded towards zero) ... uses NumMulTemp1
s32 NumGetInt(const sNum* num)
{
	// get exponent
	int e = num->exp - EXP_1;

	// underflow (or zero)
	if (e < 0) return 0;

	// get sign
	Bool neg = NumIsNeg(num);

	// overflow (max. 9 digits)
	if (e > 8) return neg ? -0x7fffffff : 0x7fffffff;

	// copy
	NumCopy(&NumMulTemp1, num);

	// load number
	s32 n = 0;
	for (; e >= 0; e--)
	{
		if (n > 0x7fffffff/10)
		{
			n = 0x7fffffff;
			break;
		}
		n *= 10;
		n += NumMulTemp1.mant[0] & 0x0f;
		if ((s32)n < 0)
		{
			n = 0x7fffffff;
			break;
		}
		MantLeft0(&NumMulTemp1);
	}
		
	return neg ? (-n) : n;
}

// increment exponent (= multiply * 10)
void ExpInc(sNum* num)
{
	if (ExpIsValid(num))
	{
		num->exp++;
		if (num->exp > EXP_MAX) NumSetOver(num);
	}
}

// decrement exponent (= divide / 10)
void ExpDec(sNum* num)
{
	if (ExpIsValid(num))
	{
		num->exp--;
		if (num->exp < EXP_MIN) NumSet0(num);
	}
}

// increment number ... uses NumMulTemp2
void NumInc(sNum* dst, sNum* src)
{
	NumAdd(dst, src, &Const1);
}

// decrement number ... uses NumMulTemp2
void NumDec(sNum* dst, sNum* src)
{
	NumAdd(dst, src, &ConstM1);
}

// subtract two numbers (num <- num1 - num2) ... uses NumMulTemp2
void NumSub(sNum* num, const sNum* num1, const sNum* num2)
{
	// copy second number
	NumCopy(&NumMulTemp2, num2);

	// negate second number
	NumNeg(&NumMulTemp2);	

	// add numbers
	NumAdd(num, num1, &NumMulTemp2);
}

// add two numbers (num <- num1 + num2) ... uses NumMulTemp2
void NumAdd(sNum* num, const sNum* num1, const sNum* num2)
{
	// 2nd number is zero or 1st number is overflow - 1st number is result
	if (NumIsZero(num2) || NumIsOver(num1))
	{
		NumCopy(num, num1);
		return;
	}

	// 1st number is zero or 2nd number is overflow - 2nd number is result
	if (NumIsZero(num1) || NumIsOver(num2))
	{
		NumCopy(num, num2);
		return;
	}

	// copy numbers
	NumCopy(&NumMulTemp2, num2);
	NumCopy(num, num1);

	// sort numbers - exponent of 2nd number must not be larger than 1st one
	int exp1 = num->exp;
	int exp2 = NumMulTemp2.exp;
	if (exp1 < exp2)
	{
		// exchange numbers
		NumExc(num, &NumMulTemp2);
		exp1 = num->exp;
		exp2 = NumMulTemp2.exp;
	}

	// prepare number of shifts
	int n = exp1 - exp2; // number of shifts

	// 2nd number is too small - only 1st number will be the result
	if (n >= MANTDIG-1) return;

	// save signs and denormalize numbers
	u8 sign1 = num->mant[0] >> 4;
	num->mant[0] &= 0x0f;
	u8 sign2 = NumMulTemp2.mant[0] >> 4;
	NumMulTemp2.mant[0] &= 0x0f;

	// shift 2nd number to the right to same exponent as 1st number
	for (; n > 0; n--) MantRight(&NumMulTemp2, 0);

	// add mantissas
	u8 sign = sign1; // result sign is equal to num1 sign
	if (sign1 == sign2) // signs are the same
	{
		MantAdd(num, num, &NumMulTemp2, 0); // sum mantissas
		if (num->mant[0] > 9)		// overflow
		{
			MantRight(num, 0);	// shift mantissa right
			ExpInc(num);		// increment exponent
		}
	}
	else
	{
		MantSub(num, num, &NumMulTemp2, 0); // subtract mantissas
		if (num->mant[0] > 9)		// result is negative
		{
			MantNeg(num);		// negate mantissa
			sign = sign2;		// result sign is equal to num2 sign
		}
	}

	// check if mantissa is zero
	if (MantIsZero(num))
	{
		// result will be zero
		num->exp = EXP_0;
		return;
	}

	// maximize mantissa
	while (ExpIsValid(num) && (num->mant[0] == 0))
	{
		// shift mantissa left by 1 position
		MantLeft0(num);

		// decrement exponent
		ExpDec(num);
	}

	// result is too small
	if (NumIsZero(num)) return;

	// set result sign
	num->mant[0] |= sign << 4;
}

// multiply two numbers (num <- num1 * num2) ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3
void NumMul(sNum* num, const sNum* num1, const sNum* num2)
{
	// 1st number is zero or overflow - 1st number is result
	if (NumIsZero(num1) || NumIsOver(num1))
	{
		NumCopy(num, num1);
		return;
	}

	// 2nd number is zero or overflow - 2nd number is result
	if (NumIsZero(num2) || NumIsOver(num2))
	{
		NumCopy(num, num2);
		return;
	}

	// copy source operands to temporary buffers
	NumCopy(&NumMulTemp1, num1);
	NumCopy(&NumMulTemp2, num2);

	// prepare result sign and denormalize numbers
	u8 sign = (NumMulTemp1.mant[0] ^ NumMulTemp2.mant[0]) & 0xf0;
	NumMulTemp1.mant[0] &= 0x0f;
	NumMulTemp2.mant[0] &= 0x0f;

	// sum exponents
	int e = NumMulTemp1.exp + NumMulTemp2.exp;

	// clear result mantissa accumulator
	memset(num->mant, 0, MANTBYTES);

	// loop through valid digits (mantissa is 10 digits, with 9 valid digits)
	// check overflow:
	//	accumulator max: 0999999999
	//	carry max: 1
	//	dig max: 9
	//	operand max: 0999999999
	//	add to accumulator: 0999999999 + 0999999999*9 + 1 = 9999999991
	//	accumulator after shift: 0999999999, possible carry 1
	//	min. result value, 9 shifts: 0100000000 * 0100000000 = 0010000000(000000000)
	//	max. result value, 9 shifts: 0999999999 * 0999999999 = 0999999998(000000001)
	int n;
	u8 dig, last;
	for (n = MANTDIG-1; n > 0; n--)
	{
		// shift accumulator right, save last digit
		last = MantRight(num, 0);

		// get digit from 1st operand
		dig = NumMulTemp1.mant[MANTBYTES-1] & 0x0f;

		// add 2nd operand to accumulator
		switch (dig)
		{
		// case 0:
		default: break;

		case 1: MantAdd(num, num, &NumMulTemp2, 0);		// +1 = *1
			break;

		case 2:	MantAdd(num, num, &NumMulTemp2, 0);		// +1 = *1
			MantAdd(num, num, &NumMulTemp2, 0);		// +1 = *2
			break;

		case 3:	MantAdd(num, num, &NumMulTemp2, 0);		// +1 = *1
			MantAdd(num, num, &NumMulTemp2, 0);		// +1 = *2
			MantAdd(num, num, &NumMulTemp2, 0);		// +1 = *3
			break;

		case 4:	MantAdd(&NumMulTemp3, &NumMulTemp2, &NumMulTemp2, 0); // tmp=*2
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *2
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *4
			break;

		case 5:	MantAdd(num, num, &NumMulTemp2, 0);		// +1 = *1
			MantAdd(&NumMulTemp3, &NumMulTemp2, &NumMulTemp2, 0); // tmp=*2
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *3
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *5
			break;

		case 6:	MantAdd(&NumMulTemp3, &NumMulTemp2, &NumMulTemp2, 0); // tmp=*2
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *2
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *4
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *6
			break;

		case 7:	MantAdd(&NumMulTemp3, &NumMulTemp2, &NumMulTemp2, 0); // tmp=*2
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *2
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *4
			MantAdd(num, num, &NumMulTemp3, 0);		// +2 = *6
			MantAdd(num, num, &NumMulTemp2, 0);		// +1 = *7
			break;

		case 8:	MantAdd(&NumMulTemp3, &NumMulTemp2, &NumMulTemp2, 0); // tmp=*2
			MantAdd(&NumMulTemp3, &NumMulTemp3, &NumMulTemp3, 0); // tmp=*4
			MantAdd(num, num, &NumMulTemp3, 0);		// +4 = *4
			MantAdd(num, num, &NumMulTemp3, 0);		// +4 = *8
			break;

		case 9:	MantAdd(&NumMulTemp3, &NumMulTemp2, &NumMulTemp2, 0); // tmp=*2
			MantAdd(&NumMulTemp3, &NumMulTemp3, &NumMulTemp3, 0); // tmp=*4
			MantAdd(num, num, &NumMulTemp3, 0);		// +4 = *4
			MantAdd(num, num, &NumMulTemp3, 0);		// +4 = *8
			MantAdd(num, num, &NumMulTemp2, 0);		// +1 = *9
			break;
		}

		// shift 1st operand right
		MantRight(&NumMulTemp1, 0);
	}

	// normalize result
	if (num->mant[0] > 9)
	{
		// shift accumulator right, save last digit
		last = MantRight(num, 0);

		// exponent correction
		e++;
	}

	// round result
	if (last >= SIGN_THRES)
	{
		// increment mantissa
		MantInc(num);

		// overflow?
		if (num->mant[0] > 9)
		{
			// shift accumulator right, save last digit
			MantRight(num, 0);

			// exponent correction
			e++;
		}
	}

	// check exponent overflow
	if (e > EXP_MAX)
	{
		NumSetOver(num);
		return;
	}

	// check exponent underflow
	if (e < EXP_MIN)
	{
		NumSet0(num);
		return;
	}

	// set result exponent
	num->exp = e;	

	// set result sign
	num->mant[0] |= sign;
}

// divide two numbers (num <- num1 / num2) ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5
void NumDiv(sNum* num, const sNum* num1, const sNum* num2)
{
	// 1st number is zero or 2nd number is overflow - result is 0
	if (NumIsZero(num1) || NumIsOver(num2))
	{
		NumSet0(num);
		return;
	}

	// 2nd number is zero or 1st number is overflow - result is overflow
	if (NumIsZero(num2) || NumIsOver(num1))
	{
		NumSetOver(num);
		return;
	}

	// copy source operands to temporary buffers
	NumCopy(&NumMulTemp1, num1); // dividend
	NumCopy(&NumMulTemp2, num2); // divisor * 1

	// prepare result sign and denormalize numbers
	u8 sign = (NumMulTemp1.mant[0] ^ NumMulTemp2.mant[0]) & 0xf0;
	NumMulTemp1.mant[0] &= 0x0f;
	NumMulTemp2.mant[0] &= 0x0f;

	// sub exponents
	int e = NumMulTemp1.exp - NumMulTemp2.exp - 1;

	// clear result mantissa accumulator
	memset(num->mant, 0, MANTBYTES);

	// prepare other divisors
	MantAdd(&NumMulTemp3, &NumMulTemp2, &NumMulTemp2, 0); // divisor * 2
	MantAdd(&NumMulTemp4, &NumMulTemp3, &NumMulTemp3, 0); // divisor * 4
	MantAdd(&NumMulTemp5, &NumMulTemp4, &NumMulTemp4, 0); // divisor * 8

	// loop through valid digits
	// Check ranges:
	//  Dividend: 0100000000..0999999999
	//  Divisor:  0100000000..0999999999
	//  Result, shift 9 left: 0100000000..9999999990
	// num ... result
	// NumMulTemp1 ... dividend
	// NumMulTemp2 ... divisor * 1
	// NumMulTemp3 ... divisor * 2
	// NumMulTemp4 ... divisor * 4
	// NumMulTemp5 ... divisor * 8
	int n;
	u8 dig;
	for (n = MANTDIG+1; n > 0; n--)
	{
		// shift accumulator left
		if (n > 1) MantLeft0(num);

		// get one digit
		dig = 0;
		if (MantComp(&NumMulTemp1, &NumMulTemp5) >= 0) // divisor * 8
		{
			dig = B3;
			MantSub(&NumMulTemp1, &NumMulTemp1, &NumMulTemp5, 0);
		}

		if (MantComp(&NumMulTemp1, &NumMulTemp4) >= 0) // divisor * 4
		{
			dig |= B2;
			MantSub(&NumMulTemp1, &NumMulTemp1, &NumMulTemp4, 0);
		}

		if (MantComp(&NumMulTemp1, &NumMulTemp3) >= 0) // divisor * 2
		{
			dig |= B1;
			MantSub(&NumMulTemp1, &NumMulTemp1, &NumMulTemp3, 0);
		}

		if (MantComp(&NumMulTemp1, &NumMulTemp2) >= 0) // divisor * 1
		{
			dig |= B0;
			MantSub(&NumMulTemp1, &NumMulTemp1, &NumMulTemp2, 0);
		}

		if (n > 1)
		{
			// store digit to the accumulator
			num->mant[MANTBYTES-1] |= dig;

			// shift dividend
			MantLeft0(&NumMulTemp1);
		}
	}

	// normalize
	if (num->mant[0] > 9)
	{
		dig = num->mant[MANTBYTES-1] & 0x0f;
		MantRight(num, 0);
		e++;
	}

	// rounding
	if (dig >= SIGN_THRES)
	{
		MantInc(num);
		if (num->mant[0] > 9)
		{
			MantRight(num, 0);
			e++;
		}
	}

	// check exponent overflow
	if (e > EXP_MAX)
	{
		NumSetOver(num);
		return;
	}

	// check exponent underflow
	if (e < EXP_MIN)
	{
		NumSet0(num);
		return;
	}

	// set result exponent
	num->exp = e;	

	// set result sign
	num->mant[0] |= sign;
}

// power (num <- num1 ^ num2) ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
void NumPow(sNum* num, const sNum* num1, const sNum* num2)
{
	// base must not be negative
	if (NumIsNeg(num1))
	{
		NumSetOver(num);
		return;
	}

	// base is zero - result will be zero
	if (NumIsZero(num1))
	{
		NumSet0(num);
		return;
	}

	// exponent is 1 or base is 1 - result is num1
	if (NumEqu(num2, &Const1) || NumEqu(num1, &Const1))
	{
		NumCopy(num, num1);
		return;
	}

	// get logarithm of the base
	NumCopy(num, num1);
	NumLn(num);

	// multiply by exponent
	NumMul(num, num, num2);

	// back to exponent
	NumExp(num);
}

// root (num <- num1 root num2) ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2
void NumRoot(sNum* num, const sNum* num1, const sNum* num2)
{
	NumDiv(&NumLnTmp2, &Const1, num2);
	NumPow(num, num1, &NumLnTmp2);
}

// check if numbers are equal (returns True if numbers are equal)
Bool NumEqu(const sNum* num1, const sNum* num2)
{
	return ((num1->exp == num2->exp) && (MantComp(num1, num2) == 0));
}

// truncate - round towards zero (= "integer" function)
void NumTrunc(sNum* num)
{
	// get exponent
	int e = num->exp - EXP_1;

	// small number 0..0.999 can be made zero
	if (e < 0)
	{
		NumSet0(num);
		return;
	}

	// big number is already integer
	if (e >= MANTDIG-2) return;

// here is e = 0..MANTDIG-3

	// prepare number of bits to clear (as result i = 1 .. MANTDIG-2)
	e = MANTDIG-2 - e;

	// reset decimal digits
	int i;
	for (i = MANTBYTES-1; ; i--)
	{
		// clear 2nd digit
		num->mant[i] &= 0xf0;
		e--;
		if (e == 0) break;

		// clear 1st digit
		num->mant[i] = 0;
		e--;
		if (e == 0) break;
	}
}

// fraction ... uses NumMulTemp1
void NumFrac(sNum* num)
{
	// backup original number
	NumCopy(&NumMulTemp1, num);

	// truncate - round towards zero
	NumTrunc(&NumMulTemp1);
	
	// get fraction
	NumSub(num, num, &NumMulTemp1);
}

// floor - round down ... uses NumMulTemp1
void NumFloor(sNum* num)
{
	// backup original number
	NumCopy(&NumMulTemp1, num);

	// truncate - round towards zero
	NumTrunc(num);

	// decrement if number was negative and not integer
	if (NumIsNeg(&NumMulTemp1) && !NumEqu(num, &NumMulTemp1))
	{
		NumDec(num, num);
	}
}

// mod two numbers (num <- num1 mod num2) ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnTmp
void NumMod(sNum* num, const sNum* num1, const sNum* num2)
{
	// divide, q = x/m;
	NumDiv(&NumLnTmp, num1, num2);

	// round down, q_int = floor(x/m)
	NumFloor(&NumLnTmp);

	// scale integer back again, qq = floor(x/m) * m
	NumMul(&NumLnTmp, &NumLnTmp, num2);

	// remainder, r = x - floor(x/m)*m
	NumSub(num, num1, &NumLnTmp);
}

// calculate ln(x) ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
//  Taylor serie D = (x-1)/(x+1),  xi+1 = xi*D^2*(i*2-1)/(i*2+1) ... x0 = 2*D
//  ln(x) = 2*D*(1 + D^2/3 + D^4/5 + D^6/7 ...) .... for x>0
void NumLn(sNum* num)
{
	// Registers of function NumLn():
	//	num ... result accumulator
	//	sNum NumLnX2 ... D^2
	//	sNum NumLnMem ... serie member
	//	sNum NumLnTmp ... temporary serie member, divided by factorial coefficient

	// check invalid argument <= 0
	if (NumIsZero(num) || NumIsNeg(num))
	{
		SetError();
		return;
	}

	// number 1
	if (NumEqu(num, &Const1))
	{
		NumSet0(num);
		return;
	}

	// get old exponent
	int e = num->exp;

	// set exponent to "1" base - number will be in range 1.00000 .. 9.99999
	num->exp = EXP_1;

	// scale number by 1/3 - number will be in range 0.33333 .. 3.33333 -> NumLnTmp (x)
	NumMul(&NumLnTmp, num, &Const13);

	// prepare member D = (x-1)/(x+1) -> num, NumLnMem
	NumInc(&NumLnMem, &NumLnTmp);	// mem <- x+1
	NumDec(num, &NumLnTmp);		// num <- x-1
	NumDiv(num, num, &NumLnMem);	// num <- (x - 1) / (x + 1) = D
	NumCopy(&NumLnMem, num);	// mem <- D

	// prepare D^2 -> NumLnX2
	NumMul(&NumLnX2, num, num);	// x2 <- D^2

	// factorial coefficient -> 1
	int faci = 1;

	// iterations
	for (;;)
	{
		// multiply member by D^2 (mem = mem * D^2)
		NumMul(&NumLnMem, &NumLnMem, &NumLnX2);

		// increase factorial coefficient by 2
		faci += 2;

		// divide member by factorial coefficient (tmp = mem / faci)
		NumSetInt(&NumLnTmp, faci);
		NumDiv(&NumLnTmp, &NumLnMem, &NumLnTmp);

		// check range of the member
		if (NumIsZero(num) || NumIsZero(&NumLnTmp) || ((num->exp - NumLnTmp.exp) > MANTDIG)) break;

		// add member to the accumulator
		NumAdd(num, num, &NumLnTmp);
	}

	// multiply by 2
	NumAdd(num, num, num);

	// add exponent to the result
	NumSetInt(&NumLnTmp, e);	// tmp <- exp
	NumMul(&NumLnTmp, &NumLnTmp, &ConstLn10); // tmp = exp * ln(10)
	NumAdd(num, num, &NumLnTmp);	// add exp*ln(10)
	NumAdd(num, num, &ConstLn3);	// add ln(3)
}

// calculate exp(x) ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
//  Taylor serie xi+1 = xi * x / (i+1) ... x0 = 1
//  exp(x) = 1 + x/1! + x^2/2! + x^3/3! + x^4/4! + x^5/5! + ...
void NumExp(sNum* num)
{
	// Registers of function NumLn():
	//	num ... result accumulator
	//	sNum NumLnMem ... serie member
	//	sNum NumLnTmp ... x
	//	sNum NumLnX2 ... factorial coefficient

	// number is zero, return 1
	if (NumIsZero(num))
	{
		NumSet1(num);
		return;
	}

	// overflow
	if (!NumIsNeg(num) && ((num->exp > ConstExpMax.exp) ||
		((num->exp == ConstExpMax.exp) && (MantComp(num, &ConstExpMax) >= 0))))
	{
		NumSetOver(num);
		return;
	}

	// underflow
	if (NumIsNeg(num) && ((num->exp > ConstExpMin.exp) ||
		((num->exp == ConstExpMin.exp) && (MantComp(num, &ConstExpMin) >= 0))))
	{
		NumSet0(num);
		return;
	}

	// get integer part of exponent
	NumMul(&NumLnTmp, num, &ConstRLn10);	// convert to 10-base x = num / ln(10)
	NumTrunc(&NumLnTmp);			// truncate (round towards zero)
	s32 e = NumGetInt(&NumLnTmp);		// get exponent
	NumMul(&NumLnTmp, &NumLnTmp, &ConstLn10); // convert back to e-base
	NumSub(&NumLnTmp, num, &NumLnTmp);	// tmp <- subtract integer exponent x

	// prepare member
	NumSet1(&NumLnMem);			// mem <- 1

	// factorial coefficient -> 0
	int faci = 0;

	// prepare result accumulator -> 1
	NumSet1(num);

	// iterations
	for (;;)
	{
		// multiply member by x
		NumMul(&NumLnMem, &NumLnMem, &NumLnTmp);

		// increase factorial coefficient
		faci++;

		// divide member by factorial coefficient
		NumSetInt(&NumLnX2, faci);
		NumDiv(&NumLnMem, &NumLnMem, &NumLnX2);

		// check range of the member
		if (NumIsZero(num) || NumIsZero(&NumLnMem) || ((num->exp - NumLnMem.exp) > MANTDIG)) break;

		// add member to the accumulator
		NumAdd(num, num, &NumLnMem);

		// overflow
		if (Error) return;
	}

	// add exponent
	e += num->exp;
	if (e > EXP_MAX) e = EXP_OVER;
	if (e < EXP_MIN) e = EXP_0;
	num->exp = e;
}

// calculate log(x) ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
void NumLog(sNum* num)
{
	// calculate ln(x)
	NumLn(num);

	// multiply * 1/ln(10)
	NumMul(num, num, &ConstRLn10);
}

// calculate exp10(x) ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
void NumExp10(sNum* num)
{
	// multiply * ln(10)
	NumMul(num, num, &ConstLn10);

	// calculate exp(x)
	NumExp(num);
}

// calculate 1/x reciprocal ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5
void NumRec(sNum* num)
{
	NumDiv(num, &Const1, num);
}

// square root ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
void NumSqrt(sNum* num)
{
	if (NumIsNeg(num))
	{
		SetError();
		return;
	}

	if (!NumIsZero(num))
	{
		NumLn(num);
		NumMul(num, num, &Const05);
		NumExp(num);
	}
}

// square ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3
void NumSqr(sNum* num)
{
	NumMul(num, num, num);
}

// normalize angle to range -pi..+pi
void NumNormPi(sNum* num)
{
	// normalize angle to range 0..2*pi
	NumMod(num, num, &ConstPi2);

	// shift angle to range -pi..+pi (subtract 2*pi if angle is >= pi)
	if ((num->exp == EXP_1) && (MantComp(num, &ConstPi) >= 0))
	{
		NumSub(num, num, &ConstPi2);
	}
}

// sin ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
//  Taylor serie xi+1 = xi * -x^2/((2*i)*(2*i+1)) ... x0 = x
//  sin(x) = x/1! - x^3/3! + x^5/5! - x^7/7! + x^9/9! - ...
void NumSin(sNum* num)
{
	// Registers of function NumLn():
	//	num ... result accumulator
	//	sNum NumLnMem ... serie member
	//	sNum NumLnX2 ... -x^2
	//	sNum NumLnTmp ... factorial coefficient

	// normalize angle to range -pi..+pi
	NumNormPi(num);

	// zero or pi - result will be zero
	if (NumIsZero(num) || NumEqu(num, &ConstPi))
	{
		NumSet0(num);
		return;
	}	

	// square -x^2
	NumMul(&NumLnX2, num, num);
	NumNeg(&NumLnX2);

	// prepare serie member
	NumCopy(&NumLnMem, num);

	// factorial coefficient -> 1
	int faci = 1;

	// iterations
	for (;;)
	{
		// multiply member by -x^2
		NumMul(&NumLnMem, &NumLnMem, &NumLnX2);

		// increase factorial coefficient
		faci += 2;

		// divide member by factorial coefficient
		NumSetInt(&NumLnTmp, faci*(faci-1));
		NumDiv(&NumLnMem, &NumLnMem, &NumLnTmp);

		// check range of the member
		if (NumIsZero(num) || NumIsZero(&NumLnMem) || ((num->exp - NumLnMem.exp) > MANTDIG)) break;

		// add member to the accumulator
		NumAdd(num, num, &NumLnMem);
	}

	// Range assurance -1 to +1 - due to inaccuracies, the result may slightly exceed the range.
	if (num->exp == EXP_1)
	{
		if (NumIsNeg(num))
			NumSetM1(num);
		else
			NumSet1(num);
	}
}

// sind ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
void NumSind(sNum* num)
{
	NumMul(num, num, &ConstPi180);
	NumSin(num);
}

// cos ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
void NumCos(sNum* num)
{
	NumAdd(num, num, &ConstPi12);
	NumSin(num);
}

// cosd ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp
void NumCosd(sNum* num)
{
	NumMul(num, num, &ConstPi180);
	NumCos(num);
}

// tan ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2
void NumTan(sNum* num)
{
	NumCopy(&NumLnTmp2, num);
	NumSin(num);
	NumCos(&NumLnTmp2);
	NumDiv(num, num, &NumLnTmp2);
}

// tand ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2
void NumTand(sNum* num)
{
	NumMul(num, num, &ConstPi180);
	NumTan(num);
}

// asin ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2
// asin(x) = atan(x / sqrt(1 - x^2))
void NumASin(sNum* num)
{
	// x = 1, result = pi/2
	if (NumEqu(num, &Const1))
	{
		NumCopy(num, &ConstPi12);
		return;
	}

	// x = -1, result = -pi/2
	if (NumEqu(num, &ConstM1))
	{
		NumCopy(num, &ConstPi12);
		NumNeg(num);
		return;
	}

	NumMul(&NumLnTmp2, num, num);			// x^2
	NumNeg(&NumLnTmp2);				// -x^2
	NumInc(&NumLnTmp2, &NumLnTmp2);			// 1 - x^2
	NumSqrt(&NumLnTmp2);				// sqrt(1 - x^2)
	NumDiv(num, num, &NumLnTmp2);			// x / sqrt(1 - x^2)
	NumATan(num);					// ATan
}

// asind ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2
void NumASind(sNum* num)
{
	NumASin(num);
	NumMul(num, num, &Const180Pi);
}

// acos ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2
void NumACos(sNum* num)
{
	NumASin(num);
	NumSub(num, &ConstPi12, num);
}

// acosd ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2
void NumACosd(sNum* num)
{
	NumACos(num);
	NumMul(num, num, &Const180Pi);
}

// atan ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2
//  Taylor serie arctan(x) = x - x^3/3 + x^5/5 - x^7/7 + .... (for -1 < x < 1)
//  For abs(x) >= 0.5 and < 2.0, we use alternate method: arctan(x) = pi/4 + arctan((x-1)/(x+1))
//  For abs(x) > 1 we use alternate method: arctan(x)= pi/2 + arctan(-1/x)
//  Note: correction >= 0.9 does not work for negative numbers, so we separate the sign.
void NumATan(sNum* num)
{
	// Registers of function NumLn():
	//	num ... result accumulator
	//	sNum NumLnMem ... serie member
	//	sNum NumLnX2 ... -x^2
	//	sNum NumLnTmp ... factorial coefficient
	//	sNum NumLnTmp2 ... final addition

	// if number is 0, return 0
	if (NumIsZero(num)) return;

	// absolute value
	Bool sign = NumIsNeg(num);
	if (sign) NumNeg(num);

	// clear final addition
	NumSet0(&NumLnTmp2);

	// if number is >= 0.5 and < 2.0, use alternate method: arctan = pi/4 + arctan((x-1)/(x+1))
	if (((num->exp == EXP_1-1) && (num->mant[0] >= 5)) ||
		((num->exp == EXP_1) && (num->mant[0] == 1)))
	{
		NumInc(&NumLnTmp2, num);		// x+1
		NumDec(num, num);			// x-1
		NumDiv(num, num, &NumLnTmp2);		// (x-1)/(x+1)
		NumCopy(&NumLnTmp2, &ConstPi14);	// additional correction pi/4
	}

	// if number is >= 1, use alternative: pi/2 + arctan(-1/x)
	else if (num->exp >= EXP_1)
	{
		NumDiv(num, &ConstM1, num);		// use reciprocal value: -1/x
		NumCopy(&NumLnTmp2, &ConstPi12);	// additional correction pi/2
	}

	// prepare member
	NumCopy(&NumLnMem, num);

	// prepare -x^2
	NumMul(&NumLnX2, num, num);
	NumNeg(&NumLnX2);

	// factorial coefficient -> 1
	int faci = 1;

	// iterations
	for (;;)
	{
		// multiply member by -x^2
		NumMul(&NumLnMem, &NumLnMem, &NumLnX2);

		// increase factorial coefficient
		faci += 2;

		// divide member by factorial coefficient
		NumSetInt(&NumLnTmp, faci);
		NumDiv(&NumLnTmp, &NumLnMem, &NumLnTmp);

		// check range of the member
		if (NumIsZero(num) || NumIsZero(&NumLnTmp) || ((num->exp - NumLnTmp.exp) > MANTDIG)) break;

		// add member to the accumulator
		NumAdd(num, num, &NumLnTmp);
	}

	// add final addition
	NumAdd(num, num, &NumLnTmp2);

	// sign correction
	if (sign) NumNeg(num);
}

// atand ... uses NumMulTemp1, NumMulTemp2, NumMulTemp3, NumMulTemp4, NumMulTemp5, NumLnX2, NumLnMem, NumLnTmp, NumLnTmp2
void NumATand(sNum* num)
{
	NumATan(num);
	NumMul(num, num, &Const180Pi);
}
