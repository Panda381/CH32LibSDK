
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
extern Bool FlagExpValid;	// exponent digits are valid

// clear edit buffer
void EditBufClear();

// check exponent mode in edit buffer
Bool CheckExpValid();

// shift mantissa in edit buffer left
void EditBufShiftL(u8 dig);

// shift mantissa in edit buffer right
void EditBufShiftR();

// start editing
void EditStart();

// stop edit mode
void EditStop();

// restart edit number on display
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
