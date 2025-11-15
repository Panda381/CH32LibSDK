
// ****************************************************************************
//
//                           AntCalc - Drawing
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// format: 1-bit pixel graphics
// image width: 1024 pixels
// image height: 12 lines
// image pitch: 128 bytes
extern const u8 FontBold8x12[1536] __attribute__ ((aligned(4)));
#define FONT	FontBold8x12	// font name
#define FONTH	12		// font height
#define FONTW	8		// font width

// format: 1-bit pixel graphics
// image width: 1024 pixels
// image height: 8 lines
// image pitch: 128 bytes
extern const u8 FontCond6x8B[1024] __attribute__ ((aligned(4)));
#define FONTCOND	FontCond6x8B	// default condensed font

#define COL_BLACK	0		// black color
#define COL_WHITE	1		// white color

extern Bool PrintInv;	// invert text

// clear screen
void DrawClear();

// draw/clear/set/invert pixel
void DrawPoint(int x, int y, u8 col);
void DrawPointClr(int x, int y);
void DrawPointSet(int x, int y);
void DrawPointInv(int x, int y);
void DrawPointFast(int x, int y, u8 col);
void DrawPointClrFast(int x, int y);
void DrawPointSetFast(int x, int y);

// get pixel color
u8 DrawGetPoint(int x, int y);

// draw/clear/invert rectangle
void DrawRect(int x, int y, int w, int h, u8 col);
void DrawRectClr(int x, int y, int w, int h);
void DrawRectInv(int x, int y, int w, int h);

// draw/clear/invert horizontal line
void DrawHLine(int x, int y, int w, u8 col);
void DrawHLineClr(int x, int y, int w);
void DrawHLineInv(int x, int y, int w);

// draw/clear/invert vertical line
void DrawVLine(int x, int y, int h, u8 col);
void DrawVLineClr(int x, int y, int h);
void DrawVLineInv(int x, int y, int h);

// draw/clear/invert frame
void DrawFrame(int x, int y, int w, int h, u8 col);
void DrawFrameClr(int x, int y, int w, int h);
void DrawFrameInv(int x, int y, int w, int h);

// draw/clear/invert line
void DrawLine(int x1, int y1, int x2, int y2, u8 col);
void DrawLineClr(int x1, int y1, int x2, int y2);
void DrawLineInv(int x1, int y1, int x2, int y2);

// draw/clear/invert round (filled circle)
void DrawRound(int x0, int y0, int r, u8 col);
void DrawRoundClr(int x0, int y0, int r);
void DrawRoundInv(int x0, int y0, int r);

// draw/clear/invert circle
void DrawCircle(int x0, int y0, int r, u8 col);
void DrawCircleClr(int x0, int y0, int r);
void DrawCircleInv(int x0, int y0, int r);

// draw/clear/invert ring
void DrawRing(int x0, int y0, int rin, int rout, u8 col);
void DrawRingClr(int x0, int y0, int rin, int rout);
void DrawRingInv(int x0, int y0, int rin, int rout);

// draw/clear/invert triangle
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, u8 col);
void DrawTriangleClr(int x1, int y1, int x2, int y2, int x3, int y3);
void DrawTriangleInv(int x1, int y1, int x2, int y2, int x3, int y3);

// Draw character normal/width/height/sized (no background, graphics coordinates)
void DrawChar(char ch, int x, int y, u8 col);
void DrawCharW(char ch, int x, int y, u8 col);
void DrawCharH(char ch, int x, int y, u8 col);
void DrawChar2(char ch, int x, int y, u8 col);

// Draw character normal sized, black background
void DrawCharBg(char ch, int x, int y);

// Draw character normal sized, white background
void DrawCharBgB(char ch, int x, int y);

// Draw character condensed size 6x8 (no background, graphics coordinates)
void DrawCharCond(char ch, int x, int y, u8 col);

// Draw character condensed size 6x8, black background
void DrawCharCondBg(char ch, int x, int y);

// Clear character normal/width/height/sized (background not changed, graphics coordinates)
void DrawCharClr(char ch, int x, int y);
void DrawCharWClr(char ch, int x, int y);
void DrawCharHClr(char ch, int x, int y);
void DrawChar2Clr(char ch, int x, int y);

// Invert character normal/width/height/sized (background not changed, graphics coordinates)
void DrawCharInv(char ch, int x, int y);
void DrawCharWInv(char ch, int x, int y);
void DrawCharHInv(char ch, int x, int y);
void DrawChar2Inv(char ch, int x, int y);

// Draw ASCIIZ text normal/width/height/sized (no background, graphics coordinates)
void DrawText(const char* text, int x, int y, u8 col);
void DrawTextW(const char* text, int x, int y, u8 col);
void DrawTextH(const char* text, int x, int y, u8 col);
void DrawText2(const char* text, int x, int y, u8 col);

// Draw ASCIIZ text, black background
void DrawTextBg(const char* text, int x, int y);

// Draw ASCIIZ text, white background
void DrawTextBgB(const char* text, int x, int y);

// Draw text condensed size 6x8 (no background, graphics coordinates)
void DrawTextCond(const char* text, int x, int y, u8 col);

// Draw text condensed size 6x8, black background
void DrawTextCondBg(const char* text, int x, int y);

// Clear ASCIIZ text normal/width/height/sized (background not changed, graphics coordinates)
void DrawTextClr(const char* text, int x, int y);
void DrawTextWClr(const char* text, int x, int y);
void DrawTextHClr(const char* text, int x, int y);
void DrawText2Clr(const char* text, int x, int y);

// Invert ASCIIZ text normal/width/height/sized (background not changed, graphics coordinates)
void DrawTextInv(const char* text, int x, int y);
void DrawTextWInv(const char* text, int x, int y);
void DrawTextHInv(const char* text, int x, int y);
void DrawText2Inv(const char* text, int x, int y);

// draw image fast - all coordinates and dimensions must be multiply of bytes and must be valid
void DrawImgFast(const u8* img, int x, int y, int xs, int ys, int w, int h, int wsb);
void DrawImgInvFast(const u8* img, int x, int y, int xs, int ys, int w, int h, int wsb);

// draw mono image, transparent background
void DrawImg(const u8* img, int x, int y, int w, int h, int wsb, u8 col);

// draw mono image with black background
void DrawImgBg(const u8* img, int x, int y, int w, int h, int wsb);

// clear mono image
void DrawImgClr(const u8* img, int x, int y, int w, int h, int wsb);

// invert mono image
void DrawImgInv(const u8* img, int x, int y, int w, int h, int wsb);

#ifdef __cplusplus
}
#endif
