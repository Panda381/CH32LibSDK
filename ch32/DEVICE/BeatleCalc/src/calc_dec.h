
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

// decode number to display buffer DispBuf (destroys content of source number!)
void NumDecode(sNum* num);

// encode number from edit buffer to X register
void NumEncode();

#ifdef __cplusplus
}
#endif
