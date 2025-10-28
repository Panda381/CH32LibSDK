
#ifndef _MAIN_H
#define _MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

//#define DRV	VideoVGA // timings
#define TILESIZE 5	// tile size in number of pixels

#if CH32V003
#define MAPW0	25	// hidden width
#define MAPH0	12	// hidden height
#else
#define MAPW0	(25+5)	// hidden width (=30)
#define MAPH0	(12+5)	// hidden height (=17)
#endif

#define MAPW	(WIDTH/TILESIZE) // real board width (=25)
#define MAPH	(HEIGHT/TILESIZE) // real board height (=12)
#define MAPSIZE	(MAPW0*MAPH0) // board size (=510)
#define SLOTNUM	1	// number of slots
#define MAPX	((MAPW0-MAPW)/2) // start X
#define MAPY	((MAPH0-MAPH)/2) // start X

#define BOARDW	(TILESIZE*MAPW+1) // board width (= 126)
#define BOARDH	(TILESIZE*MAPH+1) // board height (= 61)
#define BOARDX	1		// board X
#define BOARDY	1		// board Y

#define SPEED	300	// speed, sleep in [ms]

#define TILE_EMPTY	0	// empty tile
#define	TILE_FULL	1	// full tile
#define TILE_SELEMPTY 	2	// selected empty tile
#define TILE_SELFULL	3	// selected full tile

#define TILE_NUM	4	// number of tiles types

// format: 1-bit pixel graphics
// image width: 128 pixels
// image height: 64 lines
// image pitch: 16 bytes
extern const u8 ImgIntro[1024];

// format: 1-bit pixel graphics
// image width: 5 pixels
// image height: 5 lines
// image pitch: 1 bytes
extern const u8 ImgTileEmpty[5];
extern const u8 ImgTileEmptySel[5];
extern const u8 ImgTileCell[5];
extern const u8 ImgTileCellSel[5];

#define TILE_WB	1

#ifdef __cplusplus
}
#endif

#endif // _MAIN_H
