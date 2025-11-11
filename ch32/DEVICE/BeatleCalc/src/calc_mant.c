
// ****************************************************************************
//
//                      Calculator - Mantissa operations
//
// ****************************************************************************

#include "../include.h"

// check if denormalized mantissa is zero (returns True if mantissa is zero)
Bool MantIsZero(const sNum* num)
{
	int i;
	const u8* m = num->mant;
	for (i = 0; i < MANTBYTES; i++)
	{
		if (m[i] != 0) return False;
	}
	return True;
}

// invert denormalized mantissa (nines' complement: 9 - x)
void MantNot(sNum* num)
{
	int i;
	u8* m = num->mant;
	for (i = 0; i < MANTBYTES; i++)
	{
		// load byte
		u8 b = m[i];

		// invert 1st digit (high nibble)
		u8 digH = b & 0xf0;
		digH = 0x90 - digH;

		// invert 2nd digit (low nibble)
		u8 digL = b & 0x0f;
		digL = 9 - digL;

		// save byte
		m[i] = digH | digL;
	}
}

// add digit 0..10 to denormalized mantissa (returns carry 0 or 1)
u8 MantAddDig(sNum* num, u8 carry)
{
	int i;
	u8* m = num->mant;
	for (i = MANTBYTES-1; i >= 0; i--)
	{
		// no carry
		if (carry == 0) break;

		// load byte
		u8 b = m[i];

		// add carry to 2nd digit (low nibble)
		u8 digL = b & 0x0f;	// get digit
		digL += carry; 		// add carry
		carry = 0;		// clear carry
		if (digL >= 10)		// overflow
		{
			digL -= 10;
			carry = 1;
		}

		// add carry to 1st digit (high nibble)
		u8 digH = (b >> 4);	// get digit
		digH += carry; 		// add carry
		carry = 0;		// clear carry
		if (digH >= 10)		// overflow
		{
			digH -= 10;
			carry = 1;
		}

		// save byte
		m[i] = (digH << 4) | digL;
	}
	return carry;
}

// subtract digit 0..10 from denormalized mantissa (returns borrow 0 or 1)
u8 MantSubDig(sNum* num, u8 borrow)
{
	int i;
	u8* m = num->mant;
	for (i = MANTBYTES-1; i >= 0; i--)
	{
		// no borrow
		if (borrow == 0) break;

		// load byte
		u8 b = m[i];

		// add carry to 2nd digit (low nibble)
		s8 digL = b & 0x0f;	// get digit
		digL -= borrow; 	// subtract borrow
		borrow = 0;		// clear borrow
		if (digL < 0)		// underflow
		{
			digL += 10;
			borrow = 1;
		}

		// add carry to 1st digit (high nibble)
		s8 digH = (b >> 4);	// get digit
		digH -= borrow; 	// subtract borrow
		borrow = 0;		// clear borrow
		if (digH < 0)		// underflow
		{
			digH += 10;
			borrow = 1;
		}

		// save byte
		m[i] = (digH << 4) | digL;
	}
	return borrow;
}

// increment denormalized mantissa (add 1 to lowest digit; returns carry 0 or 1)
u8 MantInc(sNum* num)
{
	return MantAddDig(num, 1);
}

// decrement denormalized mantissa (subtract 1 from lowest digit; returns borrow 0 or 1)
u8 MantDec(sNum* num)
{
	return MantSubDig(num, 1);
}

// negate denormalized mantissa (tens' complement: 9 - x + 1 = 10 - x)
void MantNeg(sNum* num)
{
	// invert mantissa (nines' complement: 9 - x)
	MantNot(num);

	// increment mantissa
	MantInc(num);
}

// sum two denormalized mantissas and carry (dst <- src1 + src2 + carry; src and dst can be the same; returns carry 0 or 1)
u8 MantAdd(sNum* dst, const sNum* src1, const sNum* src2, u8 carry)
{
	u8* d = dst->mant;
	const u8* s1 = src1->mant;
	const u8* s2 = src2->mant;
	int i;
	for (i = MANTBYTES-1; i >= 0; i--)
	{
		// load bytes
		u8 b1 = s1[i];
		u8 b2 = s2[i];

		// sum 2nd digits (low nibbles)
		u8 dig1 = b1 & 0x0f;	// get digit 1
		u8 dig2 = b2 & 0x0f;	// get digit 2
		u8 digL = dig1 + dig2 + carry; // sum digits and carry (result 0..19)
		carry = 0; // clear carry
		if (digL >= 10) // overflow
		{
			// overflow digit
			digL -= 10;
			carry = 1; // new carry
		}

		// sum 1st digits (high nibbles)
		dig1 = b1 >> 4;		// get digit 1
		dig2 = b2 >> 4;		// get digit 2
		u8 digH = dig1 + dig2 + carry; // sum digits and carry (result 0..19)
		carry = 0; // clear carry
		if (digH >= 10) // overflow
		{
			// overflow digit
			digH -= 10;
			carry = 1; // new carry
		}

		// save byte
		d[i] = (digH << 4) | digL;
	}
	return carry;
}

// subtract two denormalized mantissas and borrow (dst <- src1 - src2 - borrow; src and dst can be the same; returns borrow 0 or 1)
u8 MantSub(sNum* dst, const sNum* src1, const sNum* src2, u8 borrow)
{
	u8* d = dst->mant;
	const u8* s1 = src1->mant;
	const u8* s2 = src2->mant;
	int i;
	for (i = MANTBYTES-1; i >= 0; i--)
	{
		// load bytes
		u8 b1 = s1[i];
		u8 b2 = s2[i];

		// subtract 2nd digits (low nibbles)
		u8 dig1 = b1 & 0x0f;	// get digit 1
		u8 dig2 = b2 & 0x0f;	// get digit 2
		s8 digL = dig1 - dig2 - borrow; // subtract digits and borrow
		borrow = 0; // clear borrow
		if (digL < 0) // underflow
		{
			// underflow digit
			digL += 10;
			borrow = 1; // new borrow
		}

		// subtract 1st digits (high nibbles)
		dig1 = b1 >> 4;		// get digit 1
		dig2 = b2 >> 4;		// get digit 2
		s8 digH = dig1 - dig2 - borrow; // subtract digits and borrow
		borrow = 0; // clear borrow
		if (digH < 0) // underflow
		{
			// underflow digit
			digH += 10;
			borrow = 1; // new borrow
		}

		// save byte
		d[i] = (digH << 4) | digL;
	}
	return borrow;
}

// shift denormalized mantissa right by 1 position (insert new highest digit, returns old lowest digit)
u8 MantRight(sNum* num, u8 dig)
{
	int i;
	u8* m = num->mant;
	for (i = 0; i < MANTBYTES; i++)
	{
		u8 b = m[i];		// load byte
		u8 carry = b & 0x0f;	// save new carry from 2nd digit in low nibble
		b = (b >> 4) | (dig << 4); // shift digits and set new digit
		m[i] = b;		// save byte
		dig = carry;		// new carry
	}
	return dig;
}

// shift denormalized mantissa right by 1 position, signed - repeat sign digit (returns old lowest digit)
u8 MantRightS(sNum* num)
{
	u8 dig = num->mant[0]; // get first digit (in high nibble)
	dig = (dig >= (SIGN_THRES << 4)) ? 9 : 0; // prepare sign byte
	return MantRight(num, dig);
}

// shift denormalized mantissa left by 1 position (insert new lowest digit, returns old highest digit)
u8 MantLeft(sNum* num, u8 dig)
{
	int i;
	u8* m = num->mant;
	for (i = MANTBYTES-1; i >= 0; i--)
	{
		u8 b = m[i];		// load byte
		u8 carry = b >> 4;	// save new carry from 1st digit in high nibble
		b = (b << 4) | dig;	// shift digits and set new digit
		m[i] = b;		// save byte
		dig = carry;		// new carry
	}
	return dig;
}

// shift denormalized mantissa left by 1 position (insert 0 to lowest digit, returns old highest digit)
u8 MantLeft0(sNum* num)
{
	return MantLeft(num, 0);
}

// compare positive denormalized mantissas (returns: -1 if num1<num2, 0 if num1=num2, +1 if num1>num2)
int MantComp(const sNum* num1, const sNum* num2)
{
	int i, d;
	const u8* m1 = num1->mant;
	const u8* m2 = num2->mant;
	for (i = 0; i < MANTBYTES; i++)
	{
		d = m1[i] - m2[i];
		if (d != 0)
		{
			if (d < 0) return -1;
			return +1;
		}
	}
	return 0;
}
