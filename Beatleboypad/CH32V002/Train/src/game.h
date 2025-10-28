
// ****************************************************************************
//
//                                Game engine
//
// ****************************************************************************

#ifndef _GAME_H
#define _GAME_H

// >>>>> DEBUG SETUP <<<<<
//#define AUTOMODE		// automode - uncomment, to autorun all levels to check solutions
#define LEVFIRST 	1	// first level

// Game speed
#ifdef AUTOMODE	// check levels
#define GAMESPEED	20	// game speed - delay between game steps, in [ms] (6 steps per second)
#else
#define GAMESPEED	166	// game speed - delay between game steps, in [ms] (6 steps per second)
#endif

#define TILEWIDTH 6	// tile width in number of pixels
#define TILEHEIGHT 5	// tile height in number of lines

// Game board
#define MAPW 	20		// width of game board
#define MAPH 	12		// height of game board
#define MAPSIZE (MAPW*MAPH)	// size of game board (=240)
#define MAPX	4		// board X coordinate
#define MAPY	-1		// board Y coordinate
#define INFOY	(MAPY+MAPH*TILEHEIGHT) // info row Y

// Info box
#define BOXW	(16*6)	// width of info box
#define BOXH	(5*8)	// height of info box
#define BOXX	((WIDTH-BOXW)/2) // coordinate X of info box
#define BOXY	((HEIGHT-6-BOXH)/2) // coordinate Y of info box

// Tiles
#define ITEM_NUM 19	// number of items

#define ITEM	0		// items
#define ITEMMIN ITEM		// item min.
#define ITEMMAX (ITEM+ITEM_NUM-1) // item max.

// Item indices (symbols are used in level definitions)
//#define	CRY	(ITEM+0)	// crystal
//#define	CRO	(ITEM+1)	// crown
//#define	TRE	(ITEM+2)	// tree
//#define	APL	(ITEM+3)	// apple
//#define	COW	(ITEM+4)	// cow
//#define	CHE	(ITEM+5)	// cherry
//#define	POL	(ITEM+6)	// pool
//#define	GIR	(ITEM+7)	// giraffe
//#define	ICE	(ITEM+8)	// ice cream
//#define	CAK	(ITEM+9)	// cake
//#define	COM	(ITEM+10)	// computer
//#define	CAR	(ITEM+11)	// car
//#define	BAL	(ITEM+12)	// balloon
//#define	CLO	(ITEM+13)	// alarm clock
//#define	ELE	(ITEM+14)	// elephant
//#define	GLA	(ITEM+15)	// drinking glass
//#define	MON	(ITEM+16)	// money
//#define	AIR	(ITEM+17)	// airplane
//#define	LEM	(ITEM+18)	// Lemmings

#define	EMPTY	19		// empty tile
//#define	EMP	EMPTY	// empty tile

#define WAGON_L	20		// wagon left
#define WAGON_U	21		// wagon up
#define WAGON_R	22		// wagon right
#define WAGON_D	23		// wagon down
#define WAGONMIN WAGON_L	// wagon min.
#define WAGONMAX WAGON_D	// wagon max.

#define LOCO_L	24		// locomotive left
#define LOCO_U	25		// locomotive up
#define LOCO_R	26		// locomotive right
#define LOCO_D	27		// locomotive down
#define LOCOMIN	LOCO_L		// locomotive min.
#define LOCOMAX LOCO_D		// locomotive max.
//#define LOC	LOCO_R		// locomotive

#define GATE	28		// gate
#define GATEMIN	GATE		// gate min
#define GATEMAX	(GATE+5)	// gate max
//#define GAT	GATE		// gate

#define WALL	34		// wall tile
//#define	WAL	WALL	// wall tile

#define TITLE	35		// title
#define TITLEMIN TITLE		// title min.
#define TITLEMAX (TITLE+4)	// title max.

#define CRASH	40		// crash
#define CRASHMIN CRASH		// crash min.
#define CRASHMAX (CRASH+9)	// crash max.

#define TILESNUM 50		// total number of tiles

// direction
enum {
	DIR_R=0,	// right
	DIR_U,		// up
	DIR_L,		// left
	DIR_D,		// down
};

// buffers
extern u8 Board[MAPSIZE];	// game board
extern u8 Dir[MAPSIZE/2];	// direction map DIR_* (1st tile = high nibble, 2nd tile = low nibble)
#define PSWLEN 5		// password length
extern u8 PswBuf[PSWLEN];	// password buffer

// game state
enum {
	S_WAIT = 0,	// wait for start
	S_GO,		// game progress
	S_CRASH,	// crash
	S_FINISH,	// game finish
	S_HELP,		// help mode
};

// current game state
extern u8 Level;	// current level
extern u8 HeadX, HeadY;	// head (loco) coordinates
extern u8 GateX, GateY;	// gate coordinates
extern u16 Length;	// train length (including loco)
extern u16 ItemNum;	// number of items on game board
extern u8 State;	// game state S_*
extern u8 AnimCnt;	// animation counter
extern u8 Phase;	// current animation phase
extern u8 CurDir;	// current direction DIR_*
extern int Score;	// current score

// key buffset for 2 keys (NOKEY=no key)
extern char KeyBuf1, KeyBuf2;

// wait step
void WaitStep();

// open level
void OpenLevel();

// initialize current level
void InitLevel();

// help level (returns True on break from keyboard)
//Bool HelpLevel();

// game loop - called every single game step (returns True on break Esc)
Bool GameLoop();

#endif // _GAME_H
