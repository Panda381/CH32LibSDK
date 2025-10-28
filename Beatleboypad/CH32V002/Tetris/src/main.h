
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
// image width: 4 pixels
// image height: 4 lines
// image pitch: 1 bytes
extern const u8 ImgTile[4];

// format: 1-bit pixel graphics
// image width: 4 pixels
// image height: 4 lines
// image pitch: 1 bytes
extern const u8 ImgBrick[4];

#ifdef __cplusplus
}
#endif

#endif // _MAIN_H
