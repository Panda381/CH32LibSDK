
#ifndef _MAIN_H
#define _MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

// format: 1-bit pixel graphics
// image width: 128 pixels
// image height: 64 lines
// image pitch: 16 bytes
extern const u8 ImgIntro[1024];

// format: 1-bit pixel graphics
// image width: 6 pixels
// image height: 78 lines
// image pitch: 1 bytes
extern const u8 ImgTiles[78];

// tile indices
enum {
	TILE_0A = 0,	// empty tile
	TILE_0B,	// empty tile, inverse
	TILE_1A,	// tile 1, player 1
	TILE_1B,	// tile 1, player 2
	TILE_2A,	// tile 2, player 1
	TILE_2B,	// tile 2, player 2
	TILE_3A,	// tile 3, player 1
	TILE_3B,	// tile 3, player 2
	TILE_4A,	// tile 4, player 1
	TILE_4B,	// tile 4, player 2
	TILE_5A,	// tile 5, player 1
	TILE_5B,	// tile 5, player 2
	TILE_COMP,	// computer
};

#ifdef __cplusplus
}
#endif

#endif // _MAIN_H
