
#ifndef _MAIN_H
#define _MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#define TILESIZE 6	// tile size in number of pixels
#define MAPW	21	// board width
#define MAPH	11	// board height
#define MAPSIZE	(MAPW*MAPH) // board size

#define MAZEW	(((MAPW+1)/2*2)-1) // maze width (=21, must be odd number)
#define MAZEH	(((MAPH+1)/2*2)-1) // maze height (=11, must be odd number)

#define BOARDW	(MAZEW*TILESIZE)	// board width in pixels (= 126)
#define BOARDH	(MAZEH*TILESIZE)	// board height in pixels (= 66)

#define BOARDX	1	// board X coordinate
#define BOARDY	-1	// board Y coordinate

#define SPEED	1 //50	// step speed (delay in [ms])

// tile indices
enum {
	S_BLACK = 0,		// 0: black tile
	S_EMPTY_HIDE,		// 1: hidden empty field (grass)
	S_WALL_HIDE,		// 2: hidden wall
	S_DOOR_HIDE,		// 3: hidden door
	S_EMPTY,		// 4: empty field (grass)
	S_WALL,			// 5: wall
	S_DOOR,			// 6: door
	S_FACE,			// 7: face on empty field

	TILE_NUM		// number of tiles
};

// format: 1-bit pixel graphics
// image width: 128 pixels
// image height: 64 lines
// image pitch: 16 bytes
extern const u8 ImgIntro[1024];

#ifdef __cplusplus
}
#endif

#endif // _MAIN_H
