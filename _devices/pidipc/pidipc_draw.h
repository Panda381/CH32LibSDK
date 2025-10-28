
// ****************************************************************************
//
//                             PidiPC - Drawing
//
// ****************************************************************************

#if USE_DRAW || USE_PRINT || USE_DISP

#ifndef _PIDIPC_DRAW_H
#define _PIDIPC_DRAW_H

#ifdef __cplusplus
extern "C" {
#endif

// === colors
// The order of color components is unconventionally chosen as GRB,
// following the example of the ZX Spectrum, so that brightness corresponds
// to color perception even on black-and-white displays.
//  bit 0: blue
//  bit 1: red
//  bit 3: green
#define COL_GRAY	0		// 0
#define COL_BLACK	0		// 0
#define COL_BLUE	B0		// 1
#define COL_RED		B1		// 2
#define COL_MAGENTA	(B0|B1)		// 3
#define COL_GREEN	B3		// 8
#define COL_CYAN	(B0|B3)		// 9
#define COL_YELLOW	(B1|B3)		// 10
#define COL_WHITE	(B0|B1|B3)	// 11

#define COL_INV		B4	// software invert text (only some text functions)
#define COL_HWINV	B2	// hardware invert text (only videomode 5)

#ifndef FONT
#define FONT		FontBold8x8	// default system font
#endif

#ifndef FONTCOND
#define FONTCOND	FontCond6x8	// default condensed font
#endif

extern const u8* DrawFont;	// current draw font (characters 8x8)
extern const u8* DrawFontCond;	// current draw condensed font (characters 6x8)

#if USE_DRAW || USE_PRINT
extern int PrintPos;		// current print position
extern int PrintRow;		// current print row
extern u8 PrintCol;		// current print color
extern u8 PrintInv;		// print inversion - offset added to characters (128 = inversion)

// clear screen
void DrawClear();
#endif

#if USE_DRAW	// 1=use graphics drawing functions

#if VMODE <= 4 // only graphics modes

// draw/clear/set/invert pixel
void DrawPoint(int x, int y, u8 col);
void DrawPointClr(int x, int y);
void DrawPointSet(int x, int y);
void DrawPointInv(int x, int y);
void DrawPointFast(int x, int y, u8 col);
void DrawPointClrFast(int x, int y);

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

// Draw character normal/width/height/sized (black background, graphics coordinates)
void DrawChar(char ch, int x, int y, u8 col);
void DrawCharW(char ch, int x, int y, u8 col);
void DrawCharH(char ch, int x, int y, u8 col);
void DrawChar2(char ch, int x, int y, u8 col);

// Draw character condensed size 6x8 (black background, graphics coordinates)
void DrawCharCond(char ch, int x, int y, u8 col);

// Draw character condensed size 6x6 (black background, graphics coordinates)
void DrawCharCond6(char ch, int x, int y, u8 col);

// Clear character normal/width/height/sized (color background, graphics coordinates)
void DrawCharClr(char ch, int x, int y, u8 col);
void DrawCharWClr(char ch, int x, int y, u8 col);
void DrawCharHClr(char ch, int x, int y, u8 col);
void DrawChar2Clr(char ch, int x, int y, u8 col);

// Invert character normal/width/height/sized (background not changed, graphics coordinates)
void DrawCharInv(char ch, int x, int y);
void DrawCharWInv(char ch, int x, int y);
void DrawCharHInv(char ch, int x, int y);
void DrawChar2Inv(char ch, int x, int y);

// Draw ASCIIZ text normal/width/height/sized (black background, graphics coordinates)
void DrawText(const char* text, int x, int y, u8 col);
void DrawTextW(const char* text, int x, int y, u8 col);
void DrawTextH(const char* text, int x, int y, u8 col);
void DrawText2(const char* text, int x, int y, u8 col);

// Draw text condensed size 6x8 (black background, graphics coordinates)
void DrawTextCond(const char* text, int x, int y, u8 col);

// Draw text condensed size 6x6 (black background, graphics coordinates)
void DrawTextCond6(const char* text, int x, int y, u8 col);

// Clear ASCIIZ text normal/width/height/sized (color background, graphics coordinates)
void DrawTextClr(const char* text, int x, int y, u8 col);
void DrawTextWClr(const char* text, int x, int y, u8 col);
void DrawTextHClr(const char* text, int x, int y, u8 col);
void DrawText2Clr(const char* text, int x, int y, u8 col);

// Invert ASCIIZ text normal/width/height/sized (background not changed, graphics coordinates)
void DrawTextInv(const char* text, int x, int y);
void DrawTextWInv(const char* text, int x, int y);
void DrawTextHInv(const char* text, int x, int y);
void DrawText2Inv(const char* text, int x, int y);

// draw image fast - all coordinates and dimensions must be multiply of bytes and must be valid
void DrawImgFast(const u8* img, const u8* attr, int x, int y, int xs, int ys, int w, int h, int wsb, int wsab);

// draw mono image
void DrawImg(const u8* img, int x, int y, int w, int h, int wsb, u8 col);

// draw mono image with background
void DrawImgBg(const u8* img, int x, int y, int w, int h, int wsb, u8 col);

// clear mono image
void DrawImgClr(const u8* img, int x, int y, int w, int h, int wsb);

// set mono image
void DrawImgSet(const u8* img, int x, int y, int w, int h, int wsb);

// invert mono image
void DrawImgInv(const u8* img, int x, int y, int w, int h, int wsb);

#endif // VMODE <= 4	// only graphics modes

#endif // USE_DRAW

// set print font
void SetFont(const char* font);

#if USE_PRINT		// 1=use text printing functions

// clear screen
INLINE void PrintClear() { DrawClear(); }

// scroll screen
void PrintScroll();

// print character at text position
void PrintCharAt(char ch, int x, int y, u8 col);

// print ASCIIZ text at text position
void PrintTextAt(const char* text, int x, int y, u8 col);

// print text with length at text position
void PrintTextLenAt(const char* text, int len, int x, int y, u8 col);

// reset print position
void PrintHome(void);

// print new line
void PrintNewLine(void);

// print character RAW at print position, without control characters
void PrintCharRaw(char ch);

// print character RAW repeat, without control characters
void PrintCharRawRep(char ch, int num);

// print space character
void PrintSpc(void);

// print space character repeat
void PrintSpcRep(int num);

// print space to position
void PrintSpcTo(int pos);

// print character at print position
//   Control characters:
//     0x01 '\1' ^A ... set not-inverted text
//     0x02 '\2' ^B ... set inverted text
//     0x07 '\a' ^G ... (bell) move cursor 1 position right (no print)
//     0x08 '\b' ^H ... (back space) move cursor 1 position left (no print)
//     0x09 '\t' ^I ... (tabulator) move cursor to next 8-character position, print spaces
//     0x0A '\n' ^J ... (new line) move cursor to start of next row
//     0x0B '\v' ^K ... (vertical tabulator) move cursor to start of previous row
//     0x0C '\f' ^L ... (form feed) clear screen, reset cursor position and set default color
//     0x0D '\r' ^M ... (carriage return) move cursor to start of current row
//     0x10 '\20' ^P ... set gray text color (COL_GRAY)
//     0x11 '\21' ^Q ... set blue text color (COL_BLUE)
//     0x12 '\22' ^R ... set green text color (COL_GREEN)
//     0x13 '\23' ^S ... set cyan text color (COL_CYAN)
//     0x14 '\24' ^T ... set red text color (COL_RED)
//     0x15 '\25' ^U ... set magenta text color (COL_MAGENTA)
//     0x16 '\26' ^V ... set yellow text color (COL_YELLOW)
//     0x17 '\27' ^W ... set white text color (COL_WHITE)
void PrintChar(char ch);

// print character repeat
void PrintCharRep(char ch, int num);

// print ASCIIZ text
void PrintText(const char* text);

// print ASCIIZ text RAW, without control characters
void PrintTextRaw(const char* text);

// print text with length
void PrintTextLen(const char* text, int len);

// print text with length RAW, without control characters
void PrintTextLenRaw(const char* text, int len);

#endif // USE_PRINT

#ifdef __cplusplus
}
#endif

#endif // _PIDIPC_DRAW_H

#endif // USE_DRAW || USE_PRINT || USE_DISP
