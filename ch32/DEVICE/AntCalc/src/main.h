
// ****************************************************************************
//
//                           AntCalc - main code
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// key level
#define KEYLEVEL_1ST	0	// 1st key level
#define KEYLEVEL_2ND	1	// 2nd key level
#define KEYLEVEL_3RD	2	// 3rd key level
#define KEYLEVEL_4TH	3	// 4th key level
#define KEYLEVEL_5TH	4	// 5th key level
#define KEYLEVEL_6TH	5	// 6th key level
#define KEYLEVEL_7TH	6	// 7th key level
#define KEYLEVEL_NUM	7	// number of key levels
extern u8 KeyLevel;

// Error flag
extern Bool Error;

// programming in progress: 1..PROGNUM, 0=not programming
extern u8 Programming;

// running in progress
extern u8 Running; // counter of remaining bytes
extern u8* RunningPtr; // pointer to program

// set error
void SetError(void);

// clear error
void ClearErr(void);

// display key level status (need to call DispUpdate)
void DispKeyLevel();

// display angle unit (need to call DispUpdate)
void DispAngleUnit();

// display battery (need to call DispUpdate)
void DispBat();

// measure battery, update display if needed
void BatUpdate();

// display register 0..3 from calculator stack or from edit buffer (need to call DispUpdate)
void DispReg(int inx);

// display all registers (need to call DispUpdate)
void DispAllReg();

// write memory to flash
void WriteMem();

#ifdef __cplusplus
}
#endif
