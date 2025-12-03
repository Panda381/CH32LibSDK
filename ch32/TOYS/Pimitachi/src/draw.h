
// ****************************************************************************
//
//                                 Drawing
//
// ****************************************************************************

#ifndef _DRAW_H
#define _DRAW_H

#ifdef __cplusplus
extern "C" {
#endif

// RLE decompressor (size 8 bytes)
typedef struct {
	const u8*	img;		// 0x00: data of the image
	u8		cache;		// 0x04: byte cache of the image
	u8		bits;		// 0x05: number of bits in byte cache of the image
	u8		res[2];		// 0x06: ... reserved (align)
} sRleData;
STATIC_ASSERT(sizeof(sRleData) == 8, "Incorrect sRleData!");

extern sRleData RleDataImg;		// RLE image data
extern sRleData RleDataMsk;		// RLE mask data

// clear screen
void DrawClear();

// draw pixel with inverted color
void DrawPointInv(int x, int y, int col);

// draw pixel
void DrawPoint(int x, int y, int col);

// draw rectangle
void DrawRect(int x, int y, int w, int h, int col);

// draw horizontal line
void DrawHLine(int x, int y, int w, int col);

// draw vertical line
void DrawVLine(int x, int y, int h, int col);

// draw frame
void DrawFrame(int x, int y, int w, int h, int col);

// Draw character normal sized, with background
void DrawCharBg(char ch, int x, int y);

// Draw character double-sized, with background
void DrawChar2Bg(char ch, int x, int y);

// Draw ASCIIZ text, with background
void DrawTextBg(const char* text, int x, int y);

// Draw ASCIIZ text double-sized, with background
void DrawText2Bg(const char* text, int x, int y);

// get bits from RLE compression
// Note: len<=0 not supported in ASM
int RleBitNum(int len, sRleData* rle);
int RleBitNumImg(int len);
int RleBitNumMsk(int len);

// draw mono image with RLE compression, with background
void DrawImgRleBgDir(const u8* img, int x, int y, int dir);

// draw mono image with RLE compression, with background
void DrawImgRleBg(const u8* img, int x, int y);

// draw mono image with RLE compression reversed, with background
void DrawImgRleBgRev(const u8* img, int x, int y);

// draw mono image with RLE compression and with mask
// Note: Both the image and the mask must be identical, either in compressed
//       or uncompressed format (chunk length > 1, or chunk length == 1).
void DrawImgRleMask(const u8* img, const u8* msk, int x, int y);

#ifdef __cplusplus
}
#endif

#endif // _DRAW_H
