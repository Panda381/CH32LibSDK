
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
// image width: 24 pixels
// image height: 256 lines
// image pitch: 3 bytes
extern const u8 ImgTiles[768];

#ifdef __cplusplus
}
#endif

#endif // _MAIN_H
