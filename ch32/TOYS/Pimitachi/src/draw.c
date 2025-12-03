
// ****************************************************************************
//
//                                 Drawing
//
// ****************************************************************************

#include "../include.h"

#if !USE_DRAW_ASM		// 1=use ASM in Draw module

// clear screen
void DrawClear()
{
	PrintInv = 0;
	memset(FrameBuf, 0, FRAMESIZE);
}

// draw pixel with inverted color
void DrawPointInv(int x, int y, int col)
{
	DrawPoint(x, y, col == 0);
}

// draw pixel
void DrawPoint(int x, int y, int col)
{
	if (((uint)x < WIDTH) && ((uint)y < HEIGHT))
	{
		u8* d = &FrameBuf[(x>>3) + y*WIDTHBYTE];
		x = 7 - (x & 7);
		x = 1<<x;
		*d |= x;
		if (col == 0) *d ^= x;
	}
}

// draw rectangle
void DrawRect(int x, int y, int w, int h, int col)
{
	if ((w <= 0) || (h <= 0)) return;

	int x0 = x;
	int w2;
	for (; h > 0; h--)
	{
		x = x0;
		for (w2 = w; w2 > 0; w2--)
		{
			DrawPoint(x, y, col);
			x++;
		}
		y++;
	}
}

// draw horizontal line
void DrawHLine(int x, int y, int w, int col) { DrawRect(x, y, w, 1, col); }

// draw vertical line
void DrawVLine(int x, int y, int h, int col) { DrawRect(x, y, 1, h, col); }

// draw frame
void DrawFrame(int x, int y, int w, int h, int col)
{
	DrawHLine(x, y+h-1, w, col);
	DrawHLine(x, y, w, col);
	DrawVLine(x, y, h, col);
	DrawVLine(x+w-1, y, h, col);
}

// Draw character normal sized, with background
void DrawCharBg(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		if (PrintInv) m = ~m;
		for (j = 8; j > 0; j--)
		{
			DrawPointInv(x, y, m & B7);
			m <<= 1;
			x++;
		}
		x -= 8;
		y++;
		src += 128;
	}
}

// Draw character double-sized, with background
void DrawChar2Bg(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	int col;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		if (PrintInv) m = ~m;
		for (j = 8; j > 0; j--)
		{
			col = m & B7;
			DrawPointInv(x, y, col);
			DrawPointInv(x+1, y, col);
			DrawPointInv(x, y+1, col);
			DrawPointInv(x+1, y+1, col);
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y += 2;
		src += 128;
	}
}

// Draw ASCIIZ text, with background
void DrawTextBg(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharBg(ch, x, y);
		x += 8;
	}
}

// Draw ASCIIZ text double-sized, with background
void DrawText2Bg(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawChar2Bg(ch, x, y);
		x += 2*8;
	}
}

// get bits from RLE compression
// Note: len<=0 not supported in ASM
NOINLINE int RleBitNum(int len, sRleData* rle)
{
	int d = 0;
	for (; len > 0; len--)
	{
		d <<= 1;

		if (rle->bits == 0)
		{
			rle->cache = *rle->img++;
			rle->bits = 8;
		}
		int bit = (rle->cache >> 7) & 1;
		rle->cache <<= 1;
		rle->bits--;

		d |= bit;
	}
	return d;
}

NOINLINE int RleBitNumImg(int len) { return RleBitNum(len, &RleDataImg); }
NOINLINE int RleBitNumMsk(int len) { return RleBitNum(len, &RleDataMsk); }

// draw mono image with RLE compression, with background
void DrawImgRleBgDir(const u8* img, int x, int y, int dir)
{
	int xd, w2;

	// prepare RLE structure
	img += 2; // skip 2 bytes of the dimension
	RleDataImg.img = img;
	RleDataImg.bits = 0;

	// get image size and stream size
	int w = img[-2];
	int dx = 1;
	if (dir != 0)
	{
		x += w; // last pixel
		dx = -1;
	}
	w++;
	int h = img[-1] + 1;
	int len = RleBitNumImg(3);

	// simple copy
	if (len < 2)
	{
		for (; h > 0; h--)
		{
			xd = x;
			for (w2 = w; w2 > 0; w2--)
			{
				DrawPointInv(xd, y, RleBitNumImg(1));
				xd += dx;
			}
			y++;
		}
		return;
	}

	// prepare first chunk (it will be 0)
	int col = PrintInv;
	int n = RleBitNumImg(len);

	for (; h > 0; h--)
	{
		xd = x;
		for (w2 = w; w2 > 0; w2--)
		{
			// next chunk
			while (n == 0)
			{
				n = RleBitNumImg(len);
				col ^= 1;
			}

			DrawPointInv(xd, y, col);
			n--;
			xd += dx;
		}
		y++;
	}
}

// draw mono image with RLE compression, with background
void DrawImgRleBg(const u8* img, int x, int y) { DrawImgRleBgDir(img, x, y, False); }

// draw mono image with RLE compression reversed, with background
void DrawImgRleBgRev(const u8* img, int x, int y) { DrawImgRleBgDir(img, x, y, True); }

// draw mono image with RLE compression and with mask
// Note: Both the image and the mask must be identical, either in compressed
//       or uncompressed format (chunk length > 1, or chunk length == 1).
void DrawImgRleMask(const u8* img, const u8* msk, int x, int y)
{
	int xd, w2, col, m;

	// prepare RLE structures
	img += 2; // skip 2 bytes of the dimension
	msk += 2; // skip 2 bytes of the dimension
	RleDataImg.img = img;
	RleDataImg.bits = 0;
	RleDataMsk.img = msk;
	RleDataMsk.bits = 0;

	// get image size and stream size
	int w = (u8)img[-2] + 1;
	int h = (u8)img[-1] + 1;
	int lenmsk = RleBitNumMsk(3);
	int len = RleBitNumImg(3);

	// simple copy
	if (len < 2)
	{
		for (; h > 0; h--)
		{
			xd = x;
			for (w2 = w; w2 > 0; w2--)
			{
				col = RleBitNumImg(1);
				m = RleBitNumMsk(1);
				if (m == 0)
				{
					DrawPointInv(xd, y, col);
				}
				xd++;
			}
			y++;
		}
		return;
	}

	// prepare first chunk (it will be 0)
	col = PrintInv;
	m = 0;
	int n = RleBitNumImg(len);
	int nmsk = RleBitNumMsk(lenmsk);

	for (; h > 0; h--)
	{
		xd = x;
		for (w2 = w; w2 > 0; w2--)
		{
			// next chunk
			while (n == 0)
			{
				n = RleBitNumImg(len);
				col ^= 1;
			}

			while (nmsk == 0)
			{
				nmsk = RleBitNumMsk(lenmsk);
				m ^= 1;
			}

			if (m == 0)
			{
				DrawPointInv(xd, y, col);
			}
			n--;
			nmsk--;
			xd++;
		}
		y++;
	}
}

#endif // !USE_DRAW_ASM
