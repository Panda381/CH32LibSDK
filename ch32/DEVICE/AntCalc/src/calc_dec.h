
// ****************************************************************************
//
//                         Calculator - Decode
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// mantissa rounding in exponent mode (rounding on 6th digit)
extern const sNum RoundExp;

// print buffer
extern u8 PrintBuf[EDITMAX];	// print buffer
extern Bool PrintFlagDP;	// print flag - decimal point was entered
extern Bool PrintExpValid;	// print flag - exponent digits are valid
extern sNum PrintNumTmp;	// temporary buffer

// decode number to print buffer PrintBuf (returns text length)
int NumDecode(const sNum* num);

// encode number from edit buffer to X register
void NumEncode();

#ifdef __cplusplus
}
#endif
