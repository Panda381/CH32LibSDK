
// ****************************************************************************
//
//                                 Game levels
//
// ****************************************************************************

#ifndef _LEVELS_H
#define _LEVELS_H

#define LEVNUM	45 //50	// number of levels (without demo scene)

// Item indices (symbols are used in level definitions)
#define CRY	0	// crystal
#define CRO	1	// crown
#define	TRE	2	// tree
#define	APL	3	// apple
#define	COW	4	// cow
#define	CHE	5	// cherry
#define	POL	6	// pool
#define	GIR	7	// giraffe
#define	ICE	8	// ice cream
#define	CAK	9	// cake
#define	COM	10	// computer
#define	CAR	11	// car
#define	BAL	0 //12	// balloon
#define	CLO	0 //13	// alarm clock
#define	ELE	0 //14	// elephant
#define	GLA	0 //15	// drinking glass
#define	MON	0 //16	// money
#define	AIR	0 //17	// airplane
#define	LEM	0 //18	// Lemmings

#define	EMP	15 //EMPTY		// empty tile
#define	WAL	14 //WALL		// wall tile
#define LOC	13 //LOCO_R		// locomotive
#define GAT	12 //GATE		// gate

// level scenes
extern const u8 Levels[(LEVNUM+1)*(MAPW/2)*MAPH];

// level paswords
extern const char LevelPsw[(LEVNUM+1)*PSWLEN+1];

// Level solution
//extern const char* const Solution[LEVNUM+1];

#endif // _LEVELS_H
