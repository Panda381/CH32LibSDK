
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
u8 EditBuf[EDITMAX];	// edit buffer
u8 EditMantNum = 0;	// number of characters of mantissa
u8 EditExpNum = 0;	// number of characters of exponent (0 = no exponent, or 3 = exponent is valid)

// clear edit buffer
void EditBufClear()
{
	FlagDP = False;		// decimal point was not entered
	FlagExpEdit = False;	// not entering exponent
	EditMantNum = 2;	// number of characters of mantissa
	EditExpNum = 0;		// number of characters of exponent (0 = no exponent)
	EditBuf[0] = ' ';	// set sign '+'
	EditBuf[1] = '0';	// set digit '0'
}

// add character to end of mantissa
void EditMantAdd(u8 dig)
{
	// check if edit buffer is full
	if (EditMantNum+EditExpNum >= EDITMAX) return;

	// get end of mantissa
	int i = EditMantNum; // number of characters of mantissa
	EditMantNum = i+1; // increase length of the mantissa

	// shift exponent
	if (EditExpNum != 0) // is exponent valid?
	{
		memmove(EditBuf+i+1, EditBuf+i, EditExpNum); // shift exponent
	}

	// update decimal point flag
	if (dig == '.') FlagDP = True; // decimal point entered

	// add new digit
	EditBuf[i] = dig;
}

// delete character from end of mantissa
void EditMantDel()
{
	// get end of mantissa
	int i = EditMantNum - 1; // number of characters of mantissa
	EditMantNum = i; // set new length of the mantissa

	// update decimal point flag
	if (EditBuf[i] == '.') FlagDP = False; // decimal point not entered

	// shift exponent
	if (EditExpNum != 0) // is exponent valid?
	{
		memmove(EditBuf+i, EditBuf+i+1, EditExpNum);
	}
}

// start editing (clear edit buffer; does not display new edit buffer)
void EditStart()
{
	// set edit mode active flag
	FlagEdit = True;

	// clear edit buffer
	EditBufClear();
}

// stop edit mode (encode number to X register)
void EditStop()
{
	// check if edit mode
	if (FlagEdit)
	{
		// clear edit flag
		FlagEdit = False;

		// encode number from edit buffer to X register
		NumEncode();
	}
}

// restart edit number on display - if not editing, loads register X into edit buffer
void EditRestart()
{
	if (!FlagEdit)	// if not editing
	{
		int n = NumDecode(&RegX); // decode RegX to print buffer PrintBuf (returns text length)
		memcpy(EditBuf, PrintBuf, n); // copy number to edit buffer
		FlagEdit = True;	// edit mode is now active
		FlagDP = PrintFlagDP;	// decimal point was entered
		EditMantNum = n;	// total number of digits
		EditExpNum = 0;		// no exponent?
		if (PrintExpValid)	// is exponent valid?
		{
			EditMantNum = n-3; // mantissa without exponent
			EditExpNum = 3;	// exponent length
		}
	}
}

// execute digit 0..9
void ExecDig(u8 key)
{
	int i;

	// convert key to digit
	u8 dig = key - KEY_0 + '0';

	// start edit mode
	if (!FlagEdit) EditStart();

	// get end of mantissa
	i = EditMantNum;

	// entering exponent?
	if (FlagExpEdit)
	{
		// enter exponent digits
		EditBuf[i + 1] = EditBuf[i + 2]; // shift previous exponent digit
		EditBuf[i + 2] = dig; // save new digit
	}

	// entering mantissa
	else
	{
		// if only one '0', delete it
		if ((i == 2) && (EditBuf[i-1] == '0'))
		{
			EditMantDel();
		}

		// insert new digit
		EditMantAdd(dig);
	}
}

// start exponent mode EE
void ExecEE(u8 key)
{
	// restart edit number on display - if not editing, loads register X into edit buffer
	EditRestart();

	// start exponent mode
	if (EditExpNum == 0)
	{
		// check free space
		if (EditMantNum > EDITMAX-3) return;

		// add exponent digits
		EditMantAdd(' ');
		EditMantAdd('0');
		EditMantAdd('0');

		// validate exponent mode
		EditMantNum -= 3;
		EditExpNum = 3;
	}

	// start edit exponent
	FlagExpEdit = True;		// entering exponent
}

// stop exponent mode
void StopExp()
{
	// if exponent is valid
	if (EditExpNum != 0)
	{
		// invalidate exponent
		EditMantNum += 3;
		EditExpNum = 0;
		FlagExpEdit = False; // not entering exponent

		// delete exponent digits
		EditMantDel();
		EditMantDel();
		EditMantDel();
	}
}

// execute dot
void ExecDot(u8 key)
{
	// start edit mode
	if (!FlagEdit) EditStart();

	// if entering exponent, delete exponent 00
	if (FlagExpEdit)
	{
		// stop exponent mode
		FlagExpEdit = False;

		// delete exponent mode if exponent was 0
		int i = EditMantNum;
		if ((EditBuf[i+1] == '0') && (EditBuf[i+2] == '0'))
		{
			// stop exponent mode - deletes exponent digits
			StopExp();
		}
	}

	// add decimal point (if was not entered)
	if (!FlagDP)
	{
		EditMantAdd('.');
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
		EditBuf[EditMantNum] ^= ' ' ^ '-';
	}

	// mantissa mode
	else
	{
		EditBuf[0] ^= ' ' ^ '-';
	}
}

// clear error CE
void ExecCE(u8 key)
{
	// restart edit number on display - if not editing, loads register X into edit buffer
	EditRestart();

	// entering exponent
	if (FlagExpEdit)
	{
		int i = EditMantNum;

		// delete exponent mode if exponent was 0
		if ((EditBuf[i+1] == '0') && (EditBuf[i+2] == '0'))
		{
			// stop exponent mode - deletes exponent digits
			StopExp();
		}
		else
		{
			// shift exponent digits
			EditBuf[i+2] = EditBuf[i+1]; // shift second exponent digit
			EditBuf[i+1] = '0'; // set first '0'
		}
	}

	// entering mantissa
	else
	{
		// delete last character
		EditMantDel();

		// mantissa is empty - set number to '0' (clear exponent mode)
		if (EditMantNum <= 1)
		{
			EditBufClear();
		}
	}
}
