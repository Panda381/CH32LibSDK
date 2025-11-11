
// ****************************************************************************
//
//                              Calculator
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// key level
#define KEYLEVEL_1ST	0	// 1st key level
#define KEYLEVEL_2ND	1	// 2nd key level
#define KEYLEVEL_3RD	2	// 3rd key level
extern int KeyLevel;

// Error flag
extern Bool Error;

// key execute table
typedef void (*pKeyExec)(u8 key);
extern const pKeyExec KeyExecList[];

// set error
void SetError(void);

// clear error
void ClearErr(void);

// Debug - disp HEX number
void DispHex(const sNum* num);

// Run calculator
void RunCalc(void);

#ifdef __cplusplus
}
#endif
