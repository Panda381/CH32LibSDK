
// ****************************************************************************
//
//                         Calculator - Decode
//
// ****************************************************************************

#include "../include.h"

// mantissa rounding in exponent mode (for EDITMAX=16: display 11 valid digits - rounding must be on 12th digit)
const sNum RoundExp = { EXP_1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00 } };

// mantissa rounding in fixe point mode (for EDITMAX=16: display 14 valid digits - rounding must be on 15th digit)
const sNum RoundMant = { EXP_1, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00 } };

// print buffer
u8 PrintBuf[EDITMAX];		// print buffer
Bool PrintFlagDP;		// print flag - decimal point was entered
Bool PrintExpValid;		// print flag - exponent digits are valid
sNum PrintNumTmp;		// temporary buffer

// decode number to print buffer PrintBuf (returns text length)
int NumDecode(const sNum* num)
{
	int n;

	// destination pointer
	u8* d = PrintBuf;

	// clear flags
	PrintFlagDP = False;		// print flag - decimal point was entered
	PrintExpValid = False;		// print flag - exponent digits are valid

	// zero
	if (NumIsZero(num))
	{
		*d++ = ' ';
		*d = '0';
		return 2;
	}

	// store sign
	*d++ = NumIsNeg(num) ? '-' : ' ';

	// temporary copy
	sNum* numtmp = &PrintNumTmp;
	NumCopy(numtmp, num);

	// overflow or system error
	if (NumIsOver(numtmp) || Error)
	{
DecNumOver:
		SetError();
		memcpy(d, "overflow", 8);
		return 1+8;
	}

	// absolute value of the number
	NumAbs(numtmp);

// exponent mode

	//   exponent mode (EDITMAX = 16 chars): +1.2345678901+12, 11 valid digits = EDITMAX-5
	//   max. value in fixed point mode (EDITMAX = 16 chars): +99999999999999. = 1e14-1 = 1e(EDITMAX-2)-1
	//   min. value in fixed point mode: +0.0010000000000 (11 valid digits = EDITMAX-5) = 1e-3
	int e = numtmp->exp;
	if ((e < -3) || (e >= EDITMAX-2))
	{
		// add rounding correction for exponent mode: +1.2345678901+12; for EDITMAX=16 add 5 on 12th digit position
		MantAdd(numtmp, numtmp, &RoundExp, 0);

		// overflow mantissa
		if (numtmp->mant[0] > 9)
		{
			// shift denormalized mantissa right by 1 position (insert new highest digit, returns old lowest digit)
			MantRight(numtmp, 0);

			// increment exponent
			ExpInc(numtmp);
			if (NumIsOver(numtmp)) goto DecNumOver; // overflow
			e = numtmp->exp;
		}		

DecNumExp:

		// decode digits of the mantissa
		u8* m = numtmp->mant;
		*d++ = *m + '0';
		*d++ = '.';
		n = EDITMAX-6;
		for (; n > 1; n -= 2)
		{
			m++;
			*d++ = (*m >> 4) + '0';
			*d++ = (*m & 0x0f) + '0';
		}
		if (n > 0) *d++ = (m[1] >> 4) + '0';

		// reduce trailing zeroes
		while (d[-1] == '0') d--;
		if (d[-1] == '.')
		{
			PrintFlagDP = False;
			d--;
		}

		// decode sign of the exponent
		*d++ = (e < 0) ? '-' : '+';
		if (e < 0) e = -e;

		// decode digits of the exponent
		int e1 = e/10;
		*d++ = e1 + '0';
		*d++ = e - e1*10 + '0';

		// set print flags
		PrintFlagDP = True;		// print flag - decimal point was entered
		PrintExpValid = True;		// print flag - exponent digits are valid

		// get length of the text
		return d - PrintBuf;
	}

// fixed-point mode

	// number is < 1, add leading zeros
	while (e < 0)
	{
		MantRight(numtmp, 0);
		e++;
	}

	// add rounding correction - +99999999999999.; for EDITMAX=16 (14 valid digits) add 5 to 15th digit
	MantAdd(numtmp, numtmp, &RoundMant, 0);

	// overflow mantissa
	if (numtmp->mant[0] > 9)
	{
		// shift denormalized mantissa right by 1 position (insert new highest digit, returns old lowest digit)
		MantRight(numtmp, 0);

		// increment exponent
		e++;

		// overflow exponent to exponent mode, result will be 1.0000e14
		if (e >= EDITMAX-2) goto DecNumExp;
	}

	// decode mantissa
	n = EDITMAX-2; // number of digits to decode
	for (; n > 0; n--)
	{
		*d++ = numtmp->mant[0] + '0';
		numtmp->mant[0] = 0;
		if (e == 0)
		{
			PrintFlagDP = True;		// print flag - decimal point was entered
			*d++ = '.';
		}
		e--;
		MantLeft0(numtmp);
	}

	// truncate zeros
	while (d[-1] == '0') d--;

	// clear decimal point
	if (d[-1] == '.')
	{
		PrintFlagDP = False;
		d--;
	}

	// get length of the text
	return d - PrintBuf;
}

// encode number from edit buffer to X register
void NumEncode()
{
	// number of digits of the mantissa
	int n = EditMantNum;

	// prepare exponent
	int e = 0;
	if (EditExpNum != 0)
	{
		// load exponent
		e = (EditBuf[n+1] - '0')*10 + (EditBuf[n+2] - '0');
		if (EditBuf[n] == '-') e = -e;
	}

	// clear mantissa of the X register
	u8* m = RegX.mant;
	memset(m, 0, MANTBYTES);

	// load mantissa digits
	u8* s = EditBuf; // pointer to text of the mantissa
	Bool dp = False; // flag, we did not see decimal point
	Bool lead0 = True; // flag, zeroes are leading
	u8 sign = SIGN_POS << 4; // prepare positive sign
	u8 ch;
	int dignum = 0; // counter of valid digits
	e--; // preset exponent
	for (; n > 0; n--)
	{
		// load one character
		ch = *s++;

		// skip space
		if (ch == ' ') continue;

		// sign
		if (ch == '-')
		{
			sign = SIGN_NEG << 4; // negative sign
			continue;
		}

		// decimal point
		if (ch == '.')
		{
			dp = True;	// we did see decimal point
			continue;	// skip this character of decimal point
		}

		// leading zeros
		if ((ch == '0') && lead0)
		{
			if (!dp)
			{
				// skip leading zeros before decimal point
			}
			else
			{
				// leading zeros after decimal pointer decreases exponent
				e--;
			}
			continue;
		}
	
		// this is valid digit - stop leading zeros
		lead0 = False;	// not leading zero

		// if this digit is before decimal point, increase exponent
		if (!dp) e++;

		// shift mantissa left and store digit to end of the mantissa
		MantLeft(&RegX, ch - '0');
		dignum++;
	}

	// align mantissa
	dignum = MANTDIG - 1 - dignum; // number of remaining shift
	for (; dignum > 0; dignum--) MantLeft(&RegX, 0); // shift mantissa left

	// check zero mantissa or underflow
	if (MantIsZero(&RegX) || (e < EXP_MIN))
	{
		NumSet0(&RegX);
		return;
	}

	// overflow
	if (e > EXP_MAX)
	{
		NumSetOver(&RegX);
		return;
	}

	// set exponent and sign
	RegX.exp = e;
	RegX.mant[0] |= sign;
}
