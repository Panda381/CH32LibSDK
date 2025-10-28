// On Flash memory error decrease SLOT13NUM to 0x100

#ifdef __cplusplus
extern "C" {
#endif

// Slot address and size must be multiply of 256 B.
#define SLOTNUM		0x0400		// save slot size (hardcoded to 1KB)
#define SLOTMAX		12		// max. slot index (= 1..12, 12 slots)
#define SLOTALIGN	0x0400		// align slots in memory

#define SLOT13NUM	0x0200		// size of slot 13 (must be aligned to 256 B)

// Slot13 - uses remaining free Flash space 512 B
extern __attribute__((section(".flashminislot"))) __attribute__((aligned(256))) const u8 Slot13[SLOT13NUM];

// program slots
typedef struct {
	u8	data[SLOTNUM];		// one slot
} sSlot;

extern __attribute__((section(".flashslot"))) __attribute__((aligned(SLOTALIGN))) const sSlot Slots[SLOTMAX];

// ===== Characters
// ZX-80 Character set

// Normal characters 0x00..0x3F (0..63)
//   Mosaic pixels 4321:
//	2 1
//	4 3
#define _SPC		0x00	// space
#define _QUOT		0x01	// " (string separator)
#define _1010		0x02	// mosaic on left
#define _1100		0x03	// mosaic on bottom
#define _0010		0x04	// mosaic on left top
#define _0001		0x05	// mosaic on right top
#define _1000		0x06	// mosaic on left bottom
#define _0100		0x07	// mosaic on right bottom
#define _1001		0x08	// mosaic on left bottom, right top
#define _CHESS		0x09	// chess pattern whole
#define _CHESS1		0x0A	// chess pattern bottom
#define _CHESS2		0x0B	// chess pattern top
#define _PERC		0x0C	// percentage %
#define _DOLLAR		0x0D	// dollar $
#define _COLON		0x0E	// : colon
#define _QUERY		0x0F	// ? query
//#define _LPAR		0x10	// ( left parenthesis
//#define _RPAR		0x11	// ) right parenthesis
//#define _MINUS	0x12	// - minus
//#define _PLUS		0x13	// + plus
//#define _ASTER	0x14	// * asterisk
//#define _SLASH	0x15	// / slash
//#define _EQU		0x16	// = equal
//#define _GT		0x17	// > greater
//#define _LT		0x18	// < less
//#define _SEMI		0x19	// ; semicolon
//#define _COMMA	0x1A	// , comma
#define _DOT		0x1B	// . dot (27)
#define _0		0x1C	// 0 (number 0) (28)
#define _1		0x1D	// 1 (number 1) (29)
#define _2		0x1E	// 2 (number 2) (30)
#define _3		0x1F	// 3 (number 3) (31)
#define _4		0x20	// 4 (number 4) (32)
#define _5		0x21	// 5 (number 5) (33)
#define _6		0x22	// 6 (number 6) (34)
#define _7		0x23	// 7 (number 7) (35)
#define _8		0x24	// 8 (number 8) (36)
#define _9		0x25	// 9 (number 9) (37)
#define _A		0x26	// A (38)
#define _B		0x27	// B (39)
#define _C		0x28	// C (40)
#define _D		0x29	// D (41)
#define _E		0x2A	// E (42)
#define _F		0x2B	// F (43)
#define _G		0x2C	// G (44)
#define _H		0x2D	// H (45)
#define _I		0x2E	// I (46)
#define _J		0x2F	// J (47)
#define _K		0x30	// K (48)
#define _L		0x31	// L (49)
#define _M		0x32	// M (50)
#define _N		0x33	// N (51)
#define _O		0x34	// O (52)
#define _P		0x35	// P (53)
#define _Q		0x36	// Q (54)
#define _R		0x37	// R (55)
#define _S		0x38	// S (56)
#define _T		0x39	// T (57)
#define _U		0x3A	// U (58)
#define _V		0x3B	// V (59)
#define _W		0x3C	// W (60)
#define _X		0x3D	// X (61)
#define _Y		0x3E	// Y (62)
#define _Z		0x3F	// Z (63)

#define _INV		0x80	// inversion flag

// Keys
#define _UP		0x70	// up
#define _DOWN		0x71	// down
#define _LEFT		0x72	// left
#define _RIGHT		0x73	// right
#define _HOME		0x74	// home
#define _EDIT		0x75	// edit
#define _NL		0x76	// NEWLINE
#define _DELETE		0x77	// delete (rubout)

#define _NONE		0xc0	// invalid character

// 0x80..0xBF (128..191) = inverted characters

// Tokens 0xD4..0xFF (212..255)
//#define _QUOT		0xD4 	// 212 "
#define _THEN		0xD5	// 213 THEN
#define _TO		0xD6	// 214 TO
#define _SEMI		0xD7	// 215 ;
#define _COMMA		0xD8	// 216 ,
#define _RPAR		0xD9	// 217 )
#define _LPAR		0xDA	// 218 (
#define _NOT		0xDB	// 219 NOT
#define _SUB		0xDC	// 220 -
#define _ADD		0xDD	// 221 +
#define _MUL		0xDE	// 222 *
#define _DIV		0xDF	// 223 /
#define _AND		0xE0	// 224 AND
#define _OR		0xE1	// 225 OR
#define _PWR		0xE2	// 226 ** power
#define _EQU		0xE3	// 227 =
#define _GR		0xE4	// 228 >
#define _LT		0xE5	// 229 <
// --- tokens at start of program line (commands):
#define _LIST	0xE6	// 230 (A) LIST
#define _BEEP	0xE7	// 231 (B) BEEP
#define _CLS	0xE8	// 232 (C) CLS
#define _DIM	0xE9	// 233 (D) DIM
#define _SAVE	0xEA	// 234 (E) SAVE
#define _FOR	0xEB	// 235 (F) FOR
#define _GOTO	0xEC	// 236 (G) GOTO
#define _POKE	0xED	// 237 (H) POKE
#define _INPUT	0xEE	// 238 (I) INPUT
#define _RANDOM	0xEF	// 239 (J) RANDOMISE
#define _RETURN	0xF0	// 240 (K) RETURN
#define _LET	0xF1	// 241 (L) LET
#define _MEMORY	0xF2	// 242 (M) MEMORY
#define _NEXT	0xF3	// 243 (N) NEXT
#define _LOAD	0xF4	// 244 (O) LOAD
#define _PRINT	0xF5	// 245 (P) PRINT
#define _NEW	0xF6	// 246 (Q) NEW
#define _RUN	0xF7	// 247 (R) RUN
#define _STOP	0xF8	// 248 (S) STOP
#define _CONT	0xF9	// 249 (T) CONTINUE
#define _IF	0xFA	// 250 (U) IF
#define _GOSUB	0xFB	// 251 (V) GOSUB
#define _WAIT	0xFC	// 252 (W) WAIT
#define _CLEAR	0xFD	// 253 (X) CLEAR
#define _REM	0xFE	// 254 (Y) REM
#define _DATA	0xFF	// 255 (Z) DATA

// decode line number as 2 bytes
#define LINE(n) (u8)((n) & 0xff), (u8)((n) >> 8)

#ifdef __cplusplus
}
#endif
