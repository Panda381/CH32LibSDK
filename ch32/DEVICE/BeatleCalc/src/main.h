
// ****************************************************************************
//
//                           BeatleCalc - main code
//
// ****************************************************************************
// CPU1 pins
// =========
// PC0: SA
// PC1: SB
// PC2: SC
// PC3: SD
// PC4: SE
// PC6: SF
// PC7: SG
// PD4: SP
// PD5: USART1_TX mapping 0, TX1-RX2 (send from CPU1 to CPU2, this is CPU1)
// PD6: USART1_RX mapping 0, RX1-TX2 (send from CPU2 to CPU1, this is CPU1)
// PA1: KN input
// PA2: KO input

// To switch calculator mode:
// 1) Press and hold selection key 1..5:
//		1 TI-2500 Datamath, slow mode with real timmings (info text " DAtAMAtH")
//		2 Sinclair Scientific, slow mode with real timmings (info text " SINCLAIr")
//		3 BeatleCalc calculator (info text "  CALCUL ")
//		4 TI-2500 Datamath, fast mode on max speed (info text "FDAtAMAtH")
//		5 Sinclair Scientific, fast mode on max speed (info text "FSINCLAIr")
// 2) Press and release C key (reset key), or shortly disconnect power (info text appears)
// 3) Release selection key (info text disappears)

#ifdef __cplusplus
extern "C" {
#endif

// slots
#define SLOTNUM		0x0100		// size of the slot in bytes (= equal to flash page size)
#define SLOTMAX		48		// max. number of slots - use max. 48, to be 3*16 (=12.2 KB)
#define SLOTALIGN	0x0100		// align slot in memory

// program slot
typedef struct {
	u8	data[SLOTNUM];		// one slot
} sSlot;

// calculator mode
#define MODE_CALCUL	1	// Calculator
#define MODE_SINCLAIR	2	// Sinclair Scientific
#define MODE_DATAMATH	3	// Texas Instruments TI-2500 Datamath
#define MODE_DEF	MODE_CALCUL // default calculator mode
extern u8 CalcMode;		// calculator mode

#define IS_CALCUL	(CalcMode == MODE_CALCUL)	// check if Calculator mode
#define IS_SINCLAIR	(CalcMode == MODE_SINCLAIR)	// check if Sinclair mode
#define IS_DATAMATH	(CalcMode == MODE_DATAMATH)	// check if Datamath mode

// display segments (the segment must be set to 0 to light up)
//  +--SA--+
//  |      |
// SF     SB
//  |      |
//  +--SG--+
//  |      |
// SE     SC
//  |      |
//  +--SD--+  SP

#define SA	B0	// PC0
#define SB	B1	// PC1
#define SC	B2	// PC2
#define SD	B3	// PC3
#define SE	B4	// PC4
#define SF	B6	// PC6
#define SG	B7	// PC7
#define SP	B5	// PD4

// digits and characters
// - digits
#define CH_0	0	// "0"
#define CH_1	1	// "1"
#define CH_2	2	// "2"
#define CH_3	3	// "3"
#define CH_4	4	// "4"
#define CH_5	5	// "5"
#define CH_6	6	// "6"
#define CH_7	7	// "7"
#define CH_8	8	// "8"
#define CH_9	9	// "9"
// - characters
#define CH_A	10	// "A"
#define CH_B	11	// "b"
#define CH_C	12	// "C" (overflow)
#define CH_D	13	// "d"
#define CH_E	14	// "E"
#define CH_F	15	// "F"
#define CH_G	16	// "G"
#define CH_H	17	// "H"
#define	CH_I	18	// "i"
#define	CH_J	19	// "J"
#define	CH_K	20	// "K"
#define	CH_L	21	// "L" (low battery)
#define	CH_M	22	// "M"
#define	CH_N	23	// "n"
#define	CH_O	24	// "o"
#define	CH_P	25	// "P"
#define	CH_Q	26	// "Q"
#define	CH_R	27	// "r"
#define	CH_S	28	// "S"
#define	CH_T	29	// "t"
#define	CH_U	30	// "u"
#define	CH_V	31	// "V"
#define	CH_W	32	// "W"
#define	CH_X	33	// "X"
#define	CH_Y	34	// "Y"
#define	CH_Z	35	// "Z"
// - special
#define CH_C2	36	// "c"
#define CH_QUER	37	// ?
#define CH_NEG	38	// "-" minus
#define CH_SPC	39	// space
// - graphics
#define CH_SEGA	40	// only segment A
#define CH_SEGB	41	// only segment B
#define CH_SEGC	42	// only segment C
#define CH_SEGD	43	// only segment D
#define CH_SEGE	44	// only segment E
#define CH_SEGF	45	// only segment F
#define CH_SEGG	46	// only segment G
#define CH_SEGP	47	// only segment P

#define CH_NUM	48	// number od characters

#define CH_MASK	0x3f	// mask single character, without dot
#define CH_DOT	B6	// DOT flag - do OR this flag with another symbol to display dot

// keyboard
// ---------------------------------
// Datamath, 18 keys:
//  CE  /   *
//  7   8   9   C
//  4   5   6   -
//  1   2   3   +
//  0   .   =
//
// Key matrix:
//  digit:     D1    D2    D3    D4    D5    D6    D7    D8    D9
//  row KN:     1     2     3     4     5     6     7     8     9
//  row KO:     C     =     +     -     *     /    CE     .     0
// ---------------------------------
// Sinclair, 18 keys:
//  up  C
//  7   8   9   * (log,exp10)
//  4   5   6   / (tan,atan)
//  1   2   3   + (sin,asin)
//  dn  0   E   - (cos,acos)
//
// Key matrix:
//  digit:     D1    D2    D3    D4    D5    D6    D7    D8    D9
//  row KN:     1     2     3     4     5     6     7     8     9
//  row KO:     C    dn     +     -     /     *    up     E     0
// ---------------------------------
// BeatleCalc, 21 keys:
//  C(reset)
//  7   8   9   /,tan,atan  CE(C)
//  4   5   6   *,log,exp   INV (dn)
//  1   2   3   +,sin,asin  2nd (up)
//  0  .,+- EE  -,cos,acos  =,sqrt,y^x
//
// Key matrix:
// digit:     D1    D2    D3    D4    D5    D6    D7    D8    D9   D10
// row KN:     1     2     3     4     5     6     7     8     9    .
// row KO:    CE    3rd    +     -     /     *    2nd    EE    0    =

// Keys
#define KEY_0	0	// 0
#define KEY_1	1	// 1
#define KEY_2	2	// 2
#define KEY_3	3	// 3
#define KEY_4	4	// 4
#define KEY_5	5	// 5
#define KEY_6	6	// 6
#define KEY_7	7	// 7
#define KEY_8	8	// 8
#define KEY_9	9	// 9
#define KEY_ADD	10	// +
#define KEY_SUB	11	// -
#define KEY_MUL	12	// *
#define KEY_DIV	13	// /
#define KEY_EQU	14	// =
#define KEY_DOT	15	// .
#define KEY_EE	16	// EE
#define KEY_CE	17	// CE
#define KEY_2ND	18	// 2nd, up
#define KEY_3RD	19	// 3rd, dn

#define KEY_NUM	20	// number of key codes
#define NOKEY	KEY_NUM	// invalid key

#define KEY_DK	(KEY_NUM+1)	// virtual key "Address Advances"

#define KEY_RELEASE_CNT	6	// key release counter (= time in multiply of 10ms)

// digits (contains inverted segments of the digits and characters)
extern const u8 SegDig[CH_NUM];

// frame buffer (contains inverted segments SA..SP: set segment to 0 to light up)
//  Note: Last digit with index 9 is not visible, it is used only to scan keys.
#define DISP_NUM	10	// number of display digits
extern u8 FrameBuf[DISP_NUM];

// display buffer (contains digits CH_0,...)
//  Note: Last digit with index 9 is not visible, it is used only to scan keys.
extern u8 DispBuf[DISP_NUM];

// map of pressed key (>0 if pressed)
extern volatile u8 KeyMap[KEY_NUM];

// keyboard buffer
#define KEYBUF_SIZE	4	// size of keyboard buffer
extern volatile u8 KeyBuf[KEYBUF_SIZE];	// keyboard buffer
extern volatile u8 KeyWriteOff;		// write offset to keyboard buffer
extern volatile u8 KeyReadOff;		// read offset from keyboard buffer

// remap key index to key code
extern const u8 KeyRemap[KEY_NUM];

// index of KeyScan digit (incremented every 1 ms)
extern volatile u8 KeyScanInx;

// check if key KEY_* is pressed
INLINE Bool KeyIsPressed(u8 key) { if (key >= KEY_NUM) return False; return KeyMap[key] > 0; }

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet(void);

// key flush
void KeyFlush(void);

// check no pressed key
Bool KeyNoPressed(void);

// wait for no key pressed
void KeyWaitNoPressed(void);

// write key to keyboard buffer (called from KeyScan())
void KeyWriteKey(u8 key);

// interrupt to serve display and keys - called from SysTick every 1 ms
void KeyScan(void);

// display update 1 digit (index inx = 0..DISP_NUM-1)
void DigUpdate(int inx);

// write digit to display buffer (index inx = 0..DISP_NUM-1, character ch = CH_*)
void DigWrite(int inx, u8 ch);

// display update - convert digits from DispBuf to segments in FrameBuf
void DispUpdate(void);

// read memory slot
void ReadSlot(sSlot* s, int inx);

// write memory slot
void WriteSlot(const sSlot* s, int inx);

#ifdef __cplusplus
}
#endif
