
// ****************************************************************************
//
//                          Calculator - Editor
//
// ****************************************************************************

#include "../include.h"

// Edit flags
Bool FlagEdit = False;	// edit mode active
Bool FlagDP = False;	// decimal point was entered
Bool FlagExpEdit = False; // entering exponent (or mantissa otherwise)
Bool FlagExpValid = False; // exponent digits are valid

// clear edit buffer
void EditBufClear()
{
	// clear flags
	FlagDP = False;	// decimal point was not entered
	FlagExpEdit = False; // not entering exponent
	FlagExpValid = False; // exponent digits are not valid

	// clear edit buffer
	memset(DispBuf, CH_SPC, DISP_NUM-2);

	// set digit '0'
	DispBuf[DISP_NUM-2] = CH_0;
}

// check exponent mode in edit buffer
Bool CheckExpValid()
{
	// DispBuf: "     9 99 "
	return ((((DispBuf[DISP_NUM-4] == CH_SPC) || (DispBuf[DISP_NUM-4] == CH_NEG)) // exponent sign
			&& (DispBuf[DISP_NUM-5] != CH_SPC))); // last digit of the mantissa
}

// shift mantissa in edit buffer left
void EditBufShiftL(u8 dig)
{
	// check if buffer is full
	if ((DispBuf[1] != CH_SPC) && (DispBuf[1] != CH_NEG)) return;

	// shift mantissa
	//  exponent mode: 6 digits, normal mode: 9 digits
	int i = FlagExpValid ? 5 : 8;
	memmove(DispBuf, DispBuf+1, i);

	// add new digit
	DispBuf[i] = dig;
}

// shift mantissa in edit buffer right
void EditBufShiftR()
{
	// check if deleting dot
	int i = FlagExpValid ? 5 : 8; // exponent mode: 6 digits, normal mode: 9 digits
	if ((DispBuf[i] & CH_DOT) != 0) FlagDP = False; // decimal point not entered

	//  exponent mode
	memmove(DispBuf+1, DispBuf, i);

	// clear first digit
	DispBuf[0] = CH_SPC;
}

// start editing
void EditStart()
{
	// set edit mode active flag
	FlagEdit = True;

	// clear edit buffer
	EditBufClear();
}

// stop edit mode
void EditStop()
{
	// check if edit mode
	if (FlagEdit)
	{
		// clear edit flag
		FlagEdit = False;

		// encode number from edit buffer do X register
		NumEncode();
	}
}

// restart edit number on display
void EditRestart()
{
	FlagEdit = True;	// edit mode active
	FlagExpValid = CheckExpValid(); // exponent is valid
	int i;
	FlagDP = False; // not decimal point
	for (i = 0; i < DISP_NUM-1; i++)
	{
		if ((DispBuf[i] & CH_DOT) != 0) FlagDP = True; // valid decimal point
	}
	FlagExpEdit = False;	// not entering exponent
}

// execute digit 0..9
void ExecDig(u8 key)
{
	// convert key to digit
	u8 dig = key - KEY_0 + CH_0;

	// start edit mode
	if (!FlagEdit) EditStart();

	// entering exponent?
	if (FlagExpEdit)
	{
		// enter exponent digits
		DispBuf[DISP_NUM-3] = DispBuf[DISP_NUM-2]; // shift previous exponent digit
		DispBuf[DISP_NUM-2] = dig; // save new digit
	}

	// entering mantissa
	else
	{
		// end of mantissa (exponent mode: 6 digits, normal mode: 9 digits)
		int i = FlagExpValid ? 5 : 8;

		// if only one '0', delete it
		if ((DispBuf[i] == CH_0) && ((DispBuf[i-1] == CH_SPC) || (DispBuf[i-1] == CH_NEG)))
		{
			EditBufShiftR();
		}

		// insert new digit
		EditBufShiftL(dig);
	}
}

// start exponent mode EE
void ExecEE(u8 key)
{
	// restart edit number on display
	EditRestart();

	// start exponent mode
	if (!FlagExpValid)
	{
		// check free space
		if ((DispBuf[3] != CH_SPC) && (DispBuf[3] != CH_NEG)) return;

		// shift mantissa left
		EditBufShiftL(CH_SPC);
		EditBufShiftL(CH_0);
		EditBufShiftL(CH_0);

		// validate exponent mode
		FlagExpValid = True;
	}

	// start edit exponent
	FlagExpEdit = True;		// entering exponent
}

// stop exponent mode
void StopExp()
{
	// if exponent is valid
	if (FlagExpValid)
	{
		// invalidate exponent
		FlagExpEdit = False; // not entering exponent
		FlagExpValid = False; // exponent digits are not valid

		// delete exponent digits
		EditBufShiftR();
		EditBufShiftR();
		EditBufShiftR();
	}
}

// execute dot
void ExecDot(u8 key)
{
	// start edit mode
	if (!FlagEdit) EditStart();

	// stop exponent mode
	FlagExpEdit = False;

	// add decimal point (if was not entered)
	if (!FlagDP)
	{
		// set flag of decimal point
		FlagDP = True;

		// end of mantissa (exponent mode: 6 digits, normal mode: 9 digits)
		int i = FlagExpValid ? 5 : 8;

		// mark decimal point
		DispBuf[i] |= CH_DOT;
	}
}

// negate
void ExecNeg(u8 key)
{
	// not edit - change sign of the X
	if (!FlagEdit)
	{
		NumNeg(&RegX);
		FlagExpEdit = False;
	}

	// exponent mode
	if (FlagExpEdit)
	{
		DispBuf[DISP_NUM-4] ^= CH_SPC ^ CH_NEG;
	}

	// mantissa mode
	else
	{
		// find sign
		int i = 0;
		while ((DispBuf[i+1] == CH_SPC) || (DispBuf[i+1] == CH_NEG)) i++;
		DispBuf[i] ^= CH_SPC ^ CH_NEG;
	}
}

// clear error CE
void ExecCE(u8 key)
{
	// clear error
	if (Error)
	{
		// clear error
		ClearErr();
		return;
	}

	// start edit mode
	if (!FlagEdit)
	{
		// restart edit number on display
		EditRestart();
	}

	// entering exponent
	if (FlagExpEdit)
	{
		// delete exponent mode if exponent was 0
		if ((DispBuf[DISP_NUM-2] == CH_0) && (DispBuf[DISP_NUM-3] == CH_0))
		{
			// stop exponent mode
			StopExp();
		}
		else
		{
			// shift exponent digits
			DispBuf[DISP_NUM-2] = DispBuf[DISP_NUM-3]; // shift second exponent digit
			DispBuf[DISP_NUM-3] = CH_0; // set first '0'
		}
	}

	// entering mantissa
	else
	{
		// delete last character
		EditBufShiftR();

		// end of mantissa (exponent mode: 6 digits, normal mode: 9 digits)
		int i = FlagExpValid ? 5 : 8;

		// mantissa is empty - set number to '0' (clear exponent mode)
		if ((DispBuf[i] == CH_SPC) || (DispBuf[i] == CH_NEG))
		{
			EditBufClear();
		}
	}
}
