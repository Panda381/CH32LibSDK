
// ****************************************************************************
//
//                           AntCalc - Keyboard
//
// ****************************************************************************
// Keyboard pins:
// PD6: ROW1
// PC6: ROW2
// PA1: ROW3
// PA2: COL1
// PD5: COL2
// PC7: COL3
// PD4: COL4

#ifdef __cplusplus
extern "C" {
#endif

// Button codes
// --- 1st digits
#define KEY_0		0	// 0
#define KEY_1		1	// 1
#define KEY_2		2	// 2
#define KEY_3		3	// 3
#define KEY_4		4	// 4
#define KEY_5		5	// 5
#define KEY_6		6	// 6
#define KEY_7		7	// 7
#define KEY_8		8	// 8
#define KEY_9		9	// 9
#define KEY_DOT		10	// .
#define KEY_2ND		11	// 2nd
// --- 2nd operators
#define KEY_ADD		12	// + (2nd 0)
#define KEY_SUB		13	// - (2nd 1)
#define KEY_MUL		14	// * (2nd 2)
#define KEY_DIV		15	// / (2nd 3)
#define KEY_PWR		16	// Yx (2nd 4)
#define KEY_XY		17	// Y/X (2nd 5)
#define KEY_SQRT	16	// sqrt (2nd 6)
#define KEY_ENTER	19	// Enter (2nd 7)
#define KEY_CE		20	// CE (2nd 8)
#define KEY_EE		21	// EE (2nd 9)
#define KEY_NEG		22	// +/- (2nd .)
#define KEY_3RD		23	// 3rd (2nd 2nd)
// --- 3rd functions
#define KEY_SIN		24	// sin (3rd 0)
#define KEY_ASIN	25	// asin (3rd 1)
#define KEY_LOG		26	// log (3rd 2)
#define KEY_LN		27	// ln (3rd 3)
#define KEY_COS		28	// cos (3rd 4)
#define KEY_ACOS	29	// acos (3rd 5)
#define KEY_EXP10	30	// exp10 (3rd 6)
#define KEY_EXP		31	// exp (3rd 7)
#define KEY_TAN		32	// tan (3rd 8)
#define KEY_ATAN	33	// atan (3rd 9)
#define KEY_REC		34	// 1/x (3rd .)
#define KEY_4TH		35	// 4th (3rd 2nd)
// --- 4th RCL
#define KEY_RCL0	36	// RCL0 (4th 0)
#define KEY_RCL1	37	// RCL1 (4th 1)
#define KEY_RCL2	38	// RCL2 (4th 2)
#define KEY_RCL3	39	// RCL3 (4th 3)
#define KEY_RCL4	40	// RCL4 (4th 4)
#define KEY_RCL5	41	// RCL5 (4th 5)
#define KEY_RCL6	42	// RCL6 (4th 6)
#define KEY_RCL7	43	// RCL7 (4th 7)
#define KEY_RCL8	44	// RCL8 (4th 8)
#define KEY_RCL9	45	// RCL9 (4th 9)
#define KEY_PI		46	// pi (4th .)
#define KEY_5TH		47	// 5th (4th 2nd)
// --- 5th STO
#define KEY_STO0	48	// STO0 (5th 0)
#define KEY_STO1	49	// STO1 (5th 1)
#define KEY_STO2	50	// STO2 (5th 2)
#define KEY_STO3	51	// STO3 (5th 3)
#define KEY_STO4	52	// STO4 (5th 4)
#define KEY_STO5	53	// STO5 (5th 5)
#define KEY_STO6	54	// STO6 (5th 6)
#define KEY_STO7	55	// STO7 (5th 7)
#define KEY_STO8	56	// STO8 (5th 8)
#define KEY_STO9	57	// STO9 (5th 9)
#define KEY_DEG		58	// deg (5th .)
#define KEY_6TH		59	// 6th (5th 2nd)
// --- 6th RUN
#define KEY_RUN0	60	// RUN0 (6th 0)
#define KEY_RUN1	61	// RUN1 (6th 1)
#define KEY_RUN2	62	// RUN2 (6th 2)
#define KEY_RUN3	63	// RUN3 (6th 3)
#define KEY_RUN4	64	// RUN4 (6th 4)
#define KEY_RUN5	65	// RUN5 (6th 5)
#define KEY_RUN6	66	// RUN6 (6th 6)
#define KEY_RUN7	67	// RUN7 (6th 7)
#define KEY_RUN8	68	// RUN8 (6th 8)
#define KEY_RUN9	69	// RUN9 (6th 9)
#define KEY_INT		70	// INT (6th .)
#define KEY_7TH		71	// 7th (6th 2nd)
// --- 7th PRG
#define KEY_PRG0	72	// PRG0 (7th 0)
#define KEY_PRG1	73	// PRG1 (7th 1)
#define KEY_PRG2	74	// PRG2 (7th 2)
#define KEY_PRG3	75	// PRG3 (7th 3)
#define KEY_PRG4	76	// PRG4 (7th 4)
#define KEY_PRG5	77	// PRG5 (7th 5)
#define KEY_PRG6	78	// PRG6 (7th 6)
#define KEY_PRG7	79	// PRG7 (7th 7)
#define KEY_PRG8	80	// PRG8 (7th 8)
#define KEY_PRG9	81	// PRG9 (7th 9)
#define KEY_C		82	// C (7th .)
#define KEY_1ST		83	// 1st (7th 2nd)

#define KEY_NUM		12	// number of buttons
#define KEYFNC_NUM	84	// number of key functions

#define NOKEY		0xff	// no key

// keyboard buffer
#define KEYBUF_SIZE	4	// size of keyboard buffer
extern u8 KeyBuf[KEYBUF_SIZE];	// keyboard buffer
extern volatile u8 KeyWriteOff;	// write offset to keyboard buffer
extern volatile u8 KeyReadOff;	// read offset from keyboard buffer
extern volatile u8 KeyMap[KEY_NUM]; // press counters and map of pressed keys

// check if button KEY_* is currently pressed
INLINE Bool KeyPressed(int key) { return KeyMap[key] != 0; }

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet();

// key flush
void KeyFlush();

// check no pressed key
Bool KeyNoPressed();

// wait for no key pressed
void KeyWaitNoPressed();

// Initialize keyboard service
void KeyInit();

// terminate keyboard
void KeyTerm();

#ifdef __cplusplus
}
#endif
