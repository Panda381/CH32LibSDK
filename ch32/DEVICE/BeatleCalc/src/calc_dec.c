
// ****************************************************************************
//
//                         Calculator - Decode
//
// ****************************************************************************

#include "../include.h"

// mantissa rounding in exponent mode (rounding on 6th digit)
const sNum RoundExp = { EXP_1, { 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00 } };
const sNum RoundMant = { EXP_1, { 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00 } };

// decode number to display buffer DispBuf (destroys content of source number!)
void NumDecode(sNum* num)
{
	int n;

	// destination pointer
	u8* d = DispBuf;

	// zero
	if (NumIsZero(num))
	{
		memset(d, CH_SPC, DISP_NUM);
		d[DISP_NUM-2] = CH_0;
		return;
	}

	// store sign
	*d++ = NumIsNeg(num) ? CH_NEG : CH_SPC;

	// overflow or system error
	if (NumIsOver(num) || Error)
	{
DecNumOver:
		SetError();
		memset(d, CH_9 | CH_DOT, DISP_NUM-1);
		return;
	}

	// absolute value of the number
	NumAbs(num);

	// check exponent mode +1.2345+12 (max. value 99999999. = 1e8-1, min. value 0.0010000 = 1e-3)
	int e = num->exp;
	if ((e < -3) || (e >= 8))
	{
		// add rounding correction
		MantAdd(num, num, &RoundExp, 0);

		// overflow mantissa
		if (num->mant[0] > 9)
		{
			// shift denormalized mantissa right by 1 position (insert new highest digit, returns old lowest digit)
			MantRight(num, 0);

			// increment exponent
			ExpInc(num);
			if (NumIsOver(num)) goto DecNumOver; // overflow
			e = num->exp;
		}		

DecNumExp:

		// decode 5 digits of the mantissa
		u8* m = num->mant;
		*d++ = m[0] + (CH_0 | CH_DOT);
		*d++ = (m[1] >> 4) + CH_0;
		*d++ = (m[1] & 0x0f) + CH_0;
		*d++ = (m[2] >> 4) + CH_0;
		*d++ = (m[2] & 0x0f) + CH_0;

		// decode sign of the exponent
		*d++ = (e < 0) ? CH_NEG : CH_SPC;
		if (e < 0) e = -e;

		// decode digits of the exponent
		int e1 = e/10;
		*d++ = e1 + CH_0;
		*d = e - e1*10 + CH_0;
		return;
	}

	// number is < 1, add leading zeros
	while (e < 0)
	{
		MantRight(num, 0);
		e++;
	}

	// add rounding correction
	MantAdd(num, num, &RoundMant, 0);

	// overflow mantissa
	if (num->mant[0] > 9)
	{
		// shift denormalized mantissa right by 1 position (insert new highest digit, returns old lowest digit)
		MantRight(num, 0);

		// increment exponent
		e++;

		// overflow exponent to exponent mode, result will be 1.0000e8
		if (e >= 8) goto DecNumExp;
	}

	// decode mantissa
	n = 8; // number of digits to decode
	for (; n > 0; n--)
	{
		*d = num->mant[0] + CH_0;
		num->mant[0] = 0;
		if (e == 0) *d |= CH_DOT;
		d++;
		e--;
		MantLeft0(num);
	}

	// truncate zeros
	while (d[-1] == CH_0) d--;

	// clear decimal point
	if ((d[-1] & CH_DOT) != 0) d[-1] &= ~CH_DOT;

	// align number right
	n = d - DispBuf;
	memmove(&DispBuf[DISP_NUM-1-n], DispBuf, n);
	memset(DispBuf, CH_SPC, DISP_NUM-1-n);
}

// encode number from edit buffer to X register
void NumEncode()
{
	// prepare exponent
	int e = 0;

	// check exponent mode
	int n = 9; // max. digits
	if (CheckExpValid())
	{
		// load exponent
		e = (DispBuf[DISP_NUM-3] - CH_0)*10 + (DispBuf[DISP_NUM-2] - CH_0);
		if (DispBuf[DISP_NUM-4] == CH_NEG) e = -e;
		n = 6; // max. digits
	}

	// clear mantissa of the X register
	u8* m = RegX.mant;
	memset(m, 0, MANTBYTES);

	// load mantissa digits
	u8* s = DispBuf;
	Bool dp = False;
	Bool lead0 = True;
	u8 sign = SIGN_POS << 4;
	u8 ch;
	int dignum = 0; // counter of valid digits
	for (; n > 0; n--)
	{
		// load one character
		ch = *s++;

		// skip space
		if (ch == CH_SPC) continue;

		// sign
		if (ch == CH_NEG)
		{
			sign = SIGN_NEG << 4;
			continue;
		}

		// dot (or last digit - default dot)
		if (((ch & CH_DOT) != 0) || (n == 1))
		{
			dp = True;
			ch &= CH_MASK;
		}

		// leading zeros
		if ((ch == CH_0) && lead0)
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
	
		// valid digit - stop leading zeros
		lead0 = False;	// not leading zero

		// if this digit is before decimal point, increase exponent
		if (!dp) e++;

		// shift mantissa and store digit
		MantLeft(&RegX, ch);
		dignum++;
	}

	// align mantissa
	dignum = MANTDIG - 1 - dignum;
	for (; dignum > 0; dignum--) MantLeft(&RegX, 0);

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
