
// ****************************************************************************
//
//                          Calculator - Editor
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// Edit flags
extern Bool FlagEdit;		// edit mode active
extern Bool FlagDP;		// decimal point was entered
extern Bool FlagExpEdit;	// entering exponent (or mantissa otherwise)
extern u8 EditBuf[EDITMAX];	// edit buffer
extern u8 EditMantNum;		// number of characters of mantissa
extern u8 EditExpNum;		// number of characters of exponent (0 = no exponent, or 3 = exponent is valid)

// clear edit buffer
void EditBufClear();

// add character to end of mantissa
void EditMantAdd(u8 dig);

// delete character from end of mantissa
void EditMantDel();

// start editing (clear edit buffer; does not display new edit buffer)
void EditStart();

// stop edit mode (encode number to X register)
void EditStop();

// restart edit number on display - if not editing, loads register X into edit buffer
void EditRestart();

// execute digit 0..9
void ExecDig(u8 key);

// start exponent mode EE
void ExecEE(u8 key);

// stop exponent mode
void StopExp();

// execute dot
void ExecDot(u8 key);

// negate
void ExecNeg(u8 key);

// clear error CE
void ExecCE(u8 key);

#ifdef __cplusplus
}
#endif
