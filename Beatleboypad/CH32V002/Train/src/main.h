
#ifndef _MAIN_H
#define _MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

// format: 1-bit pixel graphics
// image width: 160 pixels
// image height: 15 lines
// image pitch: 20 bytes
// - Every tile is 6 pixels width, 8 pixels is X distance, 5 lines height.
extern const u8 ImgTiles[300];

#ifdef __cplusplus
}
#endif

#endif // _MAIN_H
