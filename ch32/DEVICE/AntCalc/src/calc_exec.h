
// ****************************************************************************
//
//                          Calculator - Execute
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// calculator stack
extern sNum CalcStk[STK_NUM];		// calculator stack
#define RegX	CalcStk[0]
#define RegY	CalcStk[1]
#define RegZ	CalcStk[2]
#define RegT	CalcStk[3]

// memory slot (total size 512 B)
#define SLOTSIZE	0x0200		// size of the slot in bytes (= multiply of flash page size)
#define SLOTMAGIC	0x31		// magic indicating valid flash content
#define SLOTADDR	0x3E00		// address of the memory slot in Flash
#define PROGSIZE	38		// size of one program
#define PROGNUM		10		// number of programs
typedef union {
	struct {
		sNum	mem[10];	// memory 0..9 (size 10*12 = 120 bytes)
		u8	prog[PROGNUM*PROGSIZE]; // programs (size 380 bytes)
		u8	progsize[PROGNUM]; // size of programs 0 to 40 bytes (size 10 bytes)
		u8	magic;		// magic SLOTMAGIC indicating valid flash content
		u8	deg;		// flag: 1=use DEGs instead of RADs
	};
	u8	page[SLOTSIZE];		// flash page
} uMem;
STATIC_ASSERT(sizeof(uMem) == SLOTSIZE, "Incorrect size of uMem!");

extern uMem Mem;

#define AngleUnitDeg	Mem.deg		// flag - angle unit is in degrees (or in radians otherwise)

// key execute table
typedef void (*pKeyExec)(u8 key);
extern const pKeyExec KeyExecList[KEYFNC_NUM];

// clear calculator stack
void CalcStkClear();

// set key level
void ExecLevel(u8 key);

#ifdef __cplusplus
}
#endif
