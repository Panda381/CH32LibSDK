
// ****************************************************************************
//
//                             PidiPC - Drawing
//
// ****************************************************************************

#include "../../includes.h"

#if USE_DRAW || USE_PRINT || USE_DISP

const u8* DrawFont = FONT;		// current draw font (characters 8x8)
const u8* DrawFontCond = FONTCOND;	// current draw condensed font (characters 6x8)

#if USE_DRAW || USE_PRINT
int PrintPos = 0;			// current print position
int PrintRow = 0;			// current print row
u8 PrintCol = COL_WHITE;		// current print color
u8 PrintInv = 0;			// print inversion - offset added to characters (128 = inversion)

// clear screen
void DrawClear()
{
	memset(FrameBuf, 0, FRAMESIZE);
	memset(AttrBuf, COL_WHITE|(COL_WHITE<<4), ATTRSIZE);
	PrintPos = 0;
	PrintRow = 0;
	PrintCol = COL_WHITE;
	PrintInv = 0;
}
#endif // USE_DRAW || USE_PRINT

#if USE_DRAW	// 1=use graphics drawing functions

#if VMODE <= 4 // only graphics modes

// ----------------------------------------------------------------------------
//                               Draw point
// ----------------------------------------------------------------------------

// draw pixel fast without limits
void DrawPointFast(int x, int y, u8 col)
{
	// set color
// Videomode 4: graphics mode 256x192 pixels mono with color attributes 8x8 pixels, required memory 6144+384 = 6528 B (driver size 516 B in RAM)
#if VMODE == 4
	int x2 = x >> 3;
	u8* a = &AttrBuf[(y/8)*(ATTRWIDTHBYTE) + x2/2];
	if ((x2 & 1) == 0)
		*a = (*a & 0xf0) | col;
	else
		*a = (*a & 0x0f) | (col << 4);

// Videomode 2: graphics mode 160x120 pixels mono with color attributes 4x4 pixels, required memory 2400+600 = 3000 B (driver size 540 B in RAM)
#elif VMODE == 2
	int x2 = x >> 2;
	u8* a = &AttrBuf[(y/4)*(ATTRWIDTHBYTE) + x2/2];
	if ((x2 & 1) == 0)
		*a = (*a & 0xf0) | col;
	else
		*a = (*a & 0x0f) | (col << 4);

// Videomode 3: graphics mode 160x120 pixels mono with color attributes 2x2 pixels, required memory 2400+2400 = 4800 B (driver size 532 B in RAM)
#elif VMODE == 3
	int x2 = x >> 1;
	u8* a = &AttrBuf[(y/2)*(ATTRWIDTHBYTE) + x2/2];
	if ((x2 & 1) == 0)
		*a = (*a & 0xf0) | col;
	else
		*a = (*a & 0x0f) | (col << 4);

// Videomode 1: graphics mode 128x64 pixels mono with color attributes 1x1 pixel, required memory 1024+4096 = 5120 B
#elif VMODE == 1
	u8* a = &AttrBuf[y*(ATTRWIDTHBYTE) + x/2];
	if ((x & 1) == 0)
		*a = (*a & 0xf0) | col;
	else
		*a = (*a & 0x0f) | (col << 4);
#endif

	// draw pixel
	u8* d = &FrameBuf[(x>>3) + y*WIDTHBYTE];
	x = 7 - (x & 7);
	*d |= 1<<x;
}

// draw pixel
void DrawPoint(int x, int y, u8 col)
{
	if ((x >= 0) && (x < WIDTH) && (y >= 0) && (y < HEIGHT)) DrawPointFast(x, y, col);
}

// get pixel color
u8 DrawGetPoint(int x, int y)
{
	if ((x < 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT)) return COL_BLACK;

	// check pixel
	u8* d = &FrameBuf[(x>>3) + y*WIDTHBYTE];
	int x2 = 7 - (x & 7);
	if ((*d & (1<<x2)) == 0) return COL_BLACK;

	// get color
// Videomode 4: graphics mode 256x192 pixels mono with color attributes 8x8 pixels, required memory 6144+384 = 6528 B (driver size 516 B in RAM)
#if VMODE == 4
	x2 = x >> 3;
	u8* a = &AttrBuf[(y/8)*(ATTRWIDTHBYTE) + x2/2];
	if ((x2 & 1) == 0)
		return *a & 0x0f;
	else
		return *a >> 4;

// Videomode 2: graphics mode 160x120 pixels mono with color attributes 4x4 pixels, required memory 2400+600 = 3000 B (driver size 540 B in RAM)
#elif VMODE == 2
	x2 = x >> 2;
	u8* a = &AttrBuf[(y/4)*(ATTRWIDTHBYTE) + x2/2];
	if ((x2 & 1) == 0)
		return *a & 0x0f;
	else
		return *a >> 4;

// Videomode 3: graphics mode 160x120 pixels mono with color attributes 2x2 pixels, required memory 2400+2400 = 4800 B (driver size 532 B in RAM)
#elif VMODE == 3
	x2 = x >> 1;
	u8* a = &AttrBuf[(y/2)*(ATTRWIDTHBYTE) + x2/2];
	if ((x2 & 1) == 0)
		return *a & 0x0f;
	else
		return *a >> 4;

// Videomode 1: graphics mode 128x64 pixels mono with color attributes 1x1 pixel, required memory 1024+4096 = 5120 B
#elif VMODE == 1
	u8* a = &AttrBuf[y*(ATTRWIDTHBYTE) + x/2];
	if ((x & 1) == 0)
		return *a & 0x0f;
	else
		return *a >> 4;
#endif
}

// clear pixel fast without limits
void DrawPointClrFast(int x, int y)
{
	// clear pixel
	u8* d = &FrameBuf[(x>>3) + y*WIDTHBYTE];
	x = 7 - (x & 7);
	*d &= ~(1<<x);
}

// clear pixel
void DrawPointClr(int x, int y)
{
	if ((x >= 0) && (x < WIDTH) && (y >= 0) && (y < HEIGHT)) DrawPointClrFast(x, y);
}

// set pixel fast without limits
void DrawPointSetFast(int x, int y)
{
	// set pixel
	u8* d = &FrameBuf[(x>>3) + y*WIDTHBYTE];
	x = 7 - (x & 7);
	*d |= (1<<x);
}

// set pixel
void DrawPointSet(int x, int y)
{
	if ((x >= 0) && (x < WIDTH) && (y >= 0) && (y < HEIGHT)) DrawPointSetFast(x, y);
}

// invert pixel fast without limits
void DrawPointInvFast(int x, int y)
{
	// invert pixel
	u8* d = &FrameBuf[(x>>3) + y*WIDTHBYTE];
	x = 7 - (x & 7);
	*d ^= 1<<x;
}

// invert pixel
void DrawPointInv(int x, int y)
{
	if ((x >= 0) && (x < WIDTH) && (y >= 0) && (y < HEIGHT)) DrawPointInvFast(x, y);
}

// ----------------------------------------------------------------------------
//                            Draw rectangle
// ----------------------------------------------------------------------------

// draw rectangle
void DrawRect(int x, int y, int w, int h, u8 col)
{
	// limit x
	if (x < 0) { w += x; x = 0; }

	// limit w
	if (x + w > WIDTH) w = WIDTH - x;
	if (w <= 0) return;

	// limit y
	if (y < 0) { h += y; y = 0; }

	// limit h
	if (y + h > HEIGHT) h = HEIGHT - y;
	if (h <= 0) return;

	// draw rectangle
	int x0 = x;
	int w2;
	for (; h > 0; h--)
	{
		x = x0;
		for (w2 = w; w2 > 0; w2--)
		{
			DrawPointFast(x, y, col);
			x++;
		}
		y++;
	}
}

// clear rectangle
void DrawRectClr(int x, int y, int w, int h)
{
	// limit x
	if (x < 0) { w += x; x = 0; }

	// limit w
	if (x + w > WIDTH) w = WIDTH - x;
	if (w <= 0) return;

	// limit y
	if (y < 0) { h += y; y = 0; }

	// limit h
	if (y + h > HEIGHT) h = HEIGHT - y;
	if (h <= 0) return;

	// draw rectangle
	int x0 = x;
	int w2;
	for (; h > 0; h--)
	{
		x = x0;
		for (w2 = w; w2 > 0; w2--)
		{
			DrawPointClrFast(x, y);
			x++;
		}
		y++;
	}
}

// invert rectangle
void DrawRectInv(int x, int y, int w, int h)
{
	// limit x
	if (x < 0) { w += x; x = 0; }

	// limit w
	if (x + w > WIDTH) w = WIDTH - x;
	if (w <= 0) return;

	// limit y
	if (y < 0) { h += y; y = 0; }

	// limit h
	if (y + h > HEIGHT) h = HEIGHT - y;
	if (h <= 0) return;

	// draw rectangle
	int x0 = x;
	int w2;
	for (; h > 0; h--)
	{
		x = x0;
		for (w2 = w; w2 > 0; w2--)
		{
			DrawPointInvFast(x, y);
			x++;
		}
		y++;
	}
}

// ----------------------------------------------------------------------------
//                 Draw horizontal line, vertical line, frame
// ----------------------------------------------------------------------------

// draw horizontal line
void DrawHLine(int x, int y, int w, u8 col) { DrawRect(x, y, w, 1, col); }

// clear horizontal line
void DrawHLineClr(int x, int y, int w) { DrawRectClr(x, y, w, 1); }

// invert horizontal line
void DrawHLineInv(int x, int y, int w) { DrawRectInv(x, y, w, 1); }

// draw vertical line
void DrawVLine(int x, int y, int h, u8 col) { DrawRect(x, y, 1, h, col); }

// clear vertical line
void DrawVLineClr(int x, int y, int h) { DrawRectClr(x, y, 1, h); }

// invert vertical line
void DrawVLineInv(int x, int y, int h) { DrawRectInv(x, y, 1, h); }

// draw frame
void DrawFrame(int x, int y, int w, int h, u8 col)
{
	if (w <= 1)
	{
		DrawVLine(x, y, h, col);
	}
	else if (h <= 1)
	{
		DrawHLine(x, y, w, col);
	}
	else
	{
		DrawHLine(x, y, w, col);
		DrawHLine(x, y+h-1, w, col);
		DrawVLine(x, y+1, h-2, col);
		DrawVLine(x+w-1, y+1, h-2, col);
	}
}

// clear frame
void DrawFrameClr(int x, int y, int w, int h)
{
	if (w <= 1)
	{
		DrawVLineClr(x, y, h);
	}
	else if (h <= 1)
	{
		DrawHLineClr(x, y, w);
	}
	else
	{
		DrawHLineClr(x, y, w);
		DrawHLineClr(x, y+h-1, w);
		DrawVLineClr(x, y+1, h-2);
		DrawVLineClr(x+w-1, y+1, h-2);
	}
}

// invert frame
void DrawFrameInv(int x, int y, int w, int h)
{
	if (w <= 1)
	{
		DrawVLineInv(x, y, h);
	}
	else if (h <= 1)
	{
		DrawHLineInv(x, y, w);
	}
	else
	{
		DrawHLineInv(x, y, w);
		DrawHLineInv(x, y+h-1, w);
		DrawVLineInv(x, y+1, h-2);
		DrawVLineInv(x+w-1, y+1, h-2);
	}
}

// ----------------------------------------------------------------------------
//                                  Draw line
// ----------------------------------------------------------------------------

// draw line
void DrawLine(int x1, int y1, int x2, int y2, u8 col)
{
	// difference of coordinates
	int dx = x2 - x1;
	int dy = y2 - y1;

	// increment X
	int sx = 1;
	if (dx < 0)
	{
		sx = -1;
		dx = -dx;
	}

	// increment Y
	int sy = 1;
	if (dy < 0)
	{
		sy = -1;
		dy = -dy;
	}

	// steeply in X direction, X is prefered as base
	if (dx > dy)
	{
		int m = 2*dy;
		int p = m - dx;
		dx = 2*dx;
		x2 += sx;
		for (; x1 != x2; x1 += sx)
		{
			DrawPoint(x1, y1, col);

			if (p > 0)
			{
				y1 += sy;
				p -= dx;
			}
			p += m;
		}
	}

	// steeply in Y direction, Y is prefered as base
	else
	{
		int m = 2*dx;
		int p = m - dy;
		dy = 2*dy;
		y2 += sy;
		for (; y1 != y2; y1 += sy)
		{
			DrawPoint(x1, y1, col);

			if (p > 0)
			{
				x1 += sx;
				p -= dy;
			}
			p += m;
		}
	}
}

// clear line
void DrawLineClr(int x1, int y1, int x2, int y2)
{
	// difference of coordinates
	int dx = x2 - x1;
	int dy = y2 - y1;

	// increment X
	int sx = 1;
	if (dx < 0)
	{
		sx = -1;
		dx = -dx;
	}

	// increment Y
	int sy = 1;
	if (dy < 0)
	{
		sy = -1;
		dy = -dy;
	}

	// steeply in X direction, X is prefered as base
	if (dx > dy)
	{
		int m = 2*dy;
		int p = m - dx;
		dx = 2*dx;
		x2 += sx;
		for (; x1 != x2; x1 += sx)
		{
			DrawPointClr(x1, y1);

			if (p > 0)
			{
				y1 += sy;
				p -= dx;
			}
			p += m;
		}
	}

	// steeply in Y direction, Y is prefered as base
	else
	{
		int m = 2*dx;
		int p = m - dy;
		dy = 2*dy;
		y2 += sy;
		for (; y1 != y2; y1 += sy)
		{
			DrawPointClr(x1, y1);

			if (p > 0)
			{
				x1 += sx;
				p -= dy;
			}
			p += m;
		}
	}
}

// invert line
void DrawLineInv(int x1, int y1, int x2, int y2)
{
	// difference of coordinates
	int dx = x2 - x1;
	int dy = y2 - y1;

	// increment X
	int sx = 1;
	if (dx < 0)
	{
		sx = -1;
		dx = -dx;
	}

	// increment Y
	int sy = 1;
	if (dy < 0)
	{
		sy = -1;
		dy = -dy;
	}

	// steeply in X direction, X is prefered as base
	if (dx > dy)
	{
		int m = 2*dy;
		int p = m - dx;
		dx = 2*dx;
		x2 += sx;
		for (; x1 != x2; x1 += sx)
		{
			DrawPointInv(x1, y1);

			if (p > 0)
			{
				y1 += sy;
				p -= dx;
			}
			p += m;
		}
	}

	// steeply in Y direction, Y is prefered as base
	else
	{
		int m = 2*dx;
		int p = m - dy;
		dy = 2*dy;
		y2 += sy;
		for (; y1 != y2; y1 += sy)
		{
			DrawPointInv(x1, y1);

			if (p > 0)
			{
				x1 += sx;
				p -= dy;
			}
			p += m;
		}
	}
}

// ----------------------------------------------------------------------------
//                          Draw round (Filled circle)
// ----------------------------------------------------------------------------

// draw round (filled circle)
void DrawRound(int x0, int y0, int r, u8 col)
{
	int x, y;
	if (r <= 0) return;
	int r2 = r*(r-1);
	r--;

	// full circle
	for (y = -r; y <= r; y++)
	{
		for (x = -r; x <= r; x++)
		{
			if ((x*x + y*y) <= r2) DrawPoint(x+x0, y+y0, col);
		}
	}
}

// clear round (filled circle)
void DrawRoundClr(int x0, int y0, int r)
{
	int x, y;
	if (r <= 0) return;
	int r2 = r*(r-1);
	r--;

	// full circle
	for (y = -r; y <= r; y++)
	{
		for (x = -r; x <= r; x++)
		{
			if ((x*x + y*y) <= r2) DrawPointClr(x+x0, y+y0);
		}
	}
}

// invert round (filled circle)
void DrawRoundInv(int x0, int y0, int r)
{
	int x, y;
	if (r <= 0) return;
	int r2 = r*(r-1);
	r--;

	// full circle
	for (y = -r; y <= r; y++)
	{
		for (x = -r; x <= r; x++)
		{
			if ((x*x + y*y) <= r2) DrawPointInv(x+x0, y+y0);
		}
	}
}

// ----------------------------------------------------------------------------
//                               Draw circle
// ----------------------------------------------------------------------------

// draw circle
void DrawCircle(int x0, int y0, int r, u8 col)
{
	int x, y;
	if (r <= 0) return;
	r--;

	x = 0;
	y = r;
	int p = 1 - r;

	while (x <= y)
	{
		DrawPoint(x0+y, y0-x, col);
		DrawPoint(x0+x, y0-y, col);
		DrawPoint(x0-x, y0-y, col);
		DrawPoint(x0-y, y0-x, col);
		DrawPoint(x0-y, y0+x, col);
		DrawPoint(x0-x, y0+y, col);
		DrawPoint(x0+x, y0+y, col);
		DrawPoint(x0+y, y0+x, col);

		x++;
		if (p > 0)
		{
			y--;
			p -= 2*y;
		}
		p += 2*x + 1;
	}
}

// clear circle
void DrawCircleClr(int x0, int y0, int r)
{
	int x, y;
	if (r <= 0) return;
	r--;

	x = 0;
	y = r;
	int p = 1 - r;

	while (x <= y)
	{
		DrawPointClr(x0+y, y0-x);
		DrawPointClr(x0+x, y0-y);
		DrawPointClr(x0-x, y0-y);
		DrawPointClr(x0-y, y0-x);
		DrawPointClr(x0-y, y0+x);
		DrawPointClr(x0-x, y0+y);
		DrawPointClr(x0+x, y0+y);
		DrawPointClr(x0+y, y0+x);

		x++;
		if (p > 0)
		{
			y--;
			p -= 2*y;
		}
		p += 2*x + 1;
	}
}

// invert circle
void DrawCircleInv(int x0, int y0, int r)
{
	int x, y;
	if (r <= 0) return;
	r--;

	x = 0;
	y = r;
	int p = 1 - r;

	while (x <= y)
	{
		DrawPointInv(x0+y, y0-x);
		DrawPointInv(x0+x, y0-y);
		DrawPointInv(x0-x, y0-y);
		DrawPointInv(x0-y, y0-x);
		DrawPointInv(x0-y, y0+x);
		DrawPointInv(x0-x, y0+y);
		DrawPointInv(x0+x, y0+y);
		DrawPointInv(x0+y, y0+x);

		x++;
		if (p > 0)
		{
			y--;
			p -= 2*y;
		}
		p += 2*x + 1;
	}
}

// ----------------------------------------------------------------------------
//                               Draw ring
// ----------------------------------------------------------------------------

// draw ring
void DrawRing(int x0, int y0, int rin, int rout, u8 col)
{
	int x, y, d;

	// draw circle
	if (rin == rout)
	{
		DrawCircle(x0, y0, rout, col);
		return;
	}

	// check radius order
	if (rin > rout)
	{
		x = rin;
		rin = rout;
		rout = x;
	}

	// inner radius is 0, draw round
	if (rin <= 0)
	{
		DrawRound(x0, y0, rout, col);
		return;
	}

	// prepare radius
	int rin2 = rin*(rin-1);
	int rout2 = rout*(rout-1);
	rout--;

	// full circle
	for (y = -rout; y <= rout; y++)
	{
		for (x = -rout; x <= rout; x++)
		{
			d = x*x + y*y;
			if ((d >= rin2) && (d <= rout2)) DrawPoint(x+x0, y+y0, col);
		}
	}
}

// clear ring
void DrawRingClr(int x0, int y0, int rin, int rout)
{
	int x, y, d;

	// draw circle
	if (rin == rout)
	{
		DrawCircleClr(x0, y0, rout);
		return;
	}

	// check radius order
	if (rin > rout)
	{
		x = rin;
		rin = rout;
		rout = x;
	}

	// inner radius is 0, draw round
	if (rin <= 0)
	{
		DrawRoundClr(x0, y0, rout);
		return;
	}

	// prepare radius
	int rin2 = rin*(rin-1);
	int rout2 = rout*(rout-1);
	rout--;

	// full circle
	for (y = -rout; y <= rout; y++)
	{
		for (x = -rout; x <= rout; x++)
		{
			d = x*x + y*y;
			if ((d >= rin2) && (d <= rout2)) DrawPointClr(x+x0, y+y0);
		}
	}
}

// invert ring
void DrawRingInv(int x0, int y0, int rin, int rout)
{
	int x, y, d;

	// draw circle
	if (rin == rout)
	{
		DrawCircleInv(x0, y0, rout);
		return;
	}

	// check radius order
	if (rin > rout)
	{
		x = rin;
		rin = rout;
		rout = x;
	}

	// inner radius is 0, draw round
	if (rin <= 0)
	{
		DrawRoundInv(x0, y0, rout);
		return;
	}

	// prepare radius
	int rin2 = rin*(rin-1);
	int rout2 = rout*(rout-1);
	rout--;

	// full circle
	for (y = -rout; y <= rout; y++)
	{
		for (x = -rout; x <= rout; x++)
		{
			d = x*x + y*y;
			if ((d >= rin2) && (d <= rout2)) DrawPointInv(x+x0, y+y0);
		}
	}
}

// ----------------------------------------------------------------------------
//                              Draw triangle
// ----------------------------------------------------------------------------

// draw triangle
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, u8 col)
{
	int x, y, k, xmin, xmax;

	// sort coordinates by Y (order from top to bottom: 1 / 2 / 3)
	if (y2 < y1)
	{
		k = x2; x2 = x1; x1 = k;
		k = y2; y2 = y1; y1 = k;
	}

	if (y3 < y1)
	{
		k = x3; x3 = x1; x1 = k;
		k = y3; y3 = y1; y1 = k;
	}
			
	if (y3 < y2)
	{
		k = x3; x3 = x2; x2 = k;
		k = y3; y3 = y2; y2 = k;
	}

	// top sub-triangle y1 <= y < y2 (without bottom y2)
	for (y = y1; y < y2; y++)
	{
		xmin = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		xmax = x1 + (x3 - x1) * (y - y1) / (y3 - y1);

		if (xmax < xmin)
		{
			k = xmin - xmax + 1;
			if (k > 0) DrawHLine(xmax, y, k, col);
		}
		else
		{
			k = xmax - xmin + 1;
			if (k > 0) DrawHLine(xmin, y, k, col);
		}
	}

	// bottom y2 == y3
	if (y2 == y3)
	{
		xmin = x2;
		xmax = x3;

		if (xmax < xmin)
		{
			k = xmin - xmax + 1;
			if (k > 0) DrawHLine(xmax, y, k, col);
		}
		else
		{
			k = xmax - xmin + 1;
			if (k > 0) DrawHLine(xmin, y, k, col);
		}
	}

	// bottom sub-triangle y2 <= y <= y3
	else
	{
		for (; y <= y3; y++)
		{
			xmin = x2 + (x3 - x2) * (y - y2) / (y3 - y2);
			xmax = x1 + (x3 - x1) * (y - y1) / (y3 - y1);

			if (xmax < xmin)
			{
				k = xmin - xmax + 1;
				if (k > 0) DrawHLine(xmax, y, k, col);
			}
			else
			{
				k = xmax - xmin + 1;
				if (k > 0) DrawHLine(xmin, y, k, col);
			}
		}
	}
}

// clear triangle
void DrawTriangleClr(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int x, y, k, xmin, xmax;

	// sort coordinates by Y (order from top to bottom: 1 / 2 / 3)
	if (y2 < y1)
	{
		k = x2; x2 = x1; x1 = k;
		k = y2; y2 = y1; y1 = k;
	}

	if (y3 < y1)
	{
		k = x3; x3 = x1; x1 = k;
		k = y3; y3 = y1; y1 = k;
	}
			
	if (y3 < y2)
	{
		k = x3; x3 = x2; x2 = k;
		k = y3; y3 = y2; y2 = k;
	}

	// top sub-triangle y1 <= y < y2 (without bottom y2)
	for (y = y1; y < y2; y++)
	{
		xmin = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		xmax = x1 + (x3 - x1) * (y - y1) / (y3 - y1);

		if (xmax < xmin)
		{
			k = xmin - xmax + 1;
			if (k > 0) DrawHLineClr(xmax, y, k);
		}
		else
		{
			k = xmax - xmin + 1;
			if (k > 0) DrawHLineClr(xmin, y, k);
		}
	}

	// bottom y2 == y3
	if (y2 == y3)
	{
		xmin = x2;
		xmax = x3;

		if (xmax < xmin)
		{
			k = xmin - xmax + 1;
			if (k > 0) DrawHLineClr(xmax, y, k);
		}
		else
		{
			k = xmax - xmin + 1;
			if (k > 0) DrawHLineClr(xmin, y, k);
		}
	}

	// bottom sub-triangle y2 <= y <= y3
	else
	{
		for (; y <= y3; y++)
		{
			xmin = x2 + (x3 - x2) * (y - y2) / (y3 - y2);
			xmax = x1 + (x3 - x1) * (y - y1) / (y3 - y1);

			if (xmax < xmin)
			{
				k = xmin - xmax + 1;
				if (k > 0) DrawHLineClr(xmax, y, k);
			}
			else
			{
				k = xmax - xmin + 1;
				if (k > 0) DrawHLineClr(xmin, y, k);
			}
		}
	}
}

// invert triangle
void DrawTriangleInv(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int x, y, k, xmin, xmax;

	// sort coordinates by Y (order from top to bottom: 1 / 2 / 3)
	if (y2 < y1)
	{
		k = x2; x2 = x1; x1 = k;
		k = y2; y2 = y1; y1 = k;
	}

	if (y3 < y1)
	{
		k = x3; x3 = x1; x1 = k;
		k = y3; y3 = y1; y1 = k;
	}
			
	if (y3 < y2)
	{
		k = x3; x3 = x2; x2 = k;
		k = y3; y3 = y2; y2 = k;
	}

	// top sub-triangle y1 <= y < y2 (without bottom y2)
	for (y = y1; y < y2; y++)
	{
		xmin = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		xmax = x1 + (x3 - x1) * (y - y1) / (y3 - y1);

		if (xmax < xmin)
		{
			k = xmin - xmax + 1;
			if (k > 0) DrawHLineInv(xmax, y, k);
		}
		else
		{
			k = xmax - xmin + 1;
			if (k > 0) DrawHLineInv(xmin, y, k);
		}
	}

	// bottom y2 == y3
	if (y2 == y3)
	{
		xmin = x2;
		xmax = x3;

		if (xmax < xmin)
		{
			k = xmin - xmax + 1;
			if (k > 0) DrawHLineInv(xmax, y, k);
		}
		else
		{
			k = xmax - xmin + 1;
			if (k > 0) DrawHLineInv(xmin, y, k);
		}
	}

	// bottom sub-triangle y2 <= y <= y3
	else
	{
		for (; y <= y3; y++)
		{
			xmin = x2 + (x3 - x2) * (y - y2) / (y3 - y2);
			xmax = x1 + (x3 - x1) * (y - y1) / (y3 - y1);

			if (xmax < xmin)
			{
				k = xmin - xmax + 1;
				if (k > 0) DrawHLineInv(xmax, y, k);
			}
			else
			{
				k = xmax - xmin + 1;
				if (k > 0) DrawHLineInv(xmin, y, k);
			}
		}
	}
}

// ----------------------------------------------------------------------------
//                               Text
// ----------------------------------------------------------------------------

// Draw character normal sized (black background, graphics coordinates)
void DrawChar(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		if ((col & COL_INV) != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
				DrawPoint(x, y, col);
			else
				DrawPointClr(x, y);
			m <<= 1;
			x++;
		}
		x -= 8;
		y++;
		src += 256;
	}
}

// Draw character condensed size 6x8 (black background, graphics coordinates)
void DrawCharCond(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFontCond[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		if ((col & COL_INV) != 0) m = ~m;
		for (j = 6; j > 0; j--)
		{
			if ((m & B7) != 0) 
				DrawPoint(x, y, col);
			else
				DrawPointClr(x, y);
			m <<= 1;
			x++;
		}
		x -= 6;
		y++;
		src += 256;
	}
}

// Draw character condensed size 6x6 (black background, graphics coordinates)
void DrawCharCond6(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFontCond[(u8)ch];
	int i, j;
	u8 m;
	for (i = 6; i > 0; i--)
	{
		m = *src;
		if ((col & COL_INV) != 0) m = ~m;
		for (j = 6; j > 0; j--)
		{
			if ((m & B7) != 0) 
				DrawPoint(x, y, col);
			else
				DrawPointClr(x, y);
			m <<= 1;
			x++;
		}
		x -= 6;
		y++;
		src += 256;
	}
}

// Draw character double-width (black background, graphics coordinates)
void DrawCharW(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		if ((col & COL_INV) != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPoint(x, y, col);
				DrawPoint(x+1, y, col);
			}
			else
			{
				DrawPointClr(x, y);
				DrawPointClr(x+1, y);
			}
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y++;
		src += 256;
	}
}

// Draw character double-height (black background, graphics coordinates)
void DrawCharH(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		if ((col & COL_INV) != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPoint(x, y, col);
				DrawPoint(x, y+1, col);
			}
			else
			{
				DrawPointClr(x, y);
				DrawPointClr(x, y+1);
			}
			m <<= 1;
			x++;
		}
		x -= 8;
		y += 2;
		src += 256;
	}
}

// Draw character double-sized (black background, graphics coordinates)
void DrawChar2(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		if ((col & COL_INV) != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPoint(x, y, col);
				DrawPoint(x+1, y, col);
				DrawPoint(x, y+1, col);
				DrawPoint(x+1, y+1, col);
			}
			else
			{
				DrawPointClr(x, y);
				DrawPointClr(x+1, y);
				DrawPointClr(x, y+1);
				DrawPointClr(x+1, y+1);
			}
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y += 2;
		src += 256;
	}
}

// Clear character (color background, graphics coordinates)
void DrawCharClr(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) == 0) 
				DrawPoint(x, y, col);
			else
				DrawPointClr(x, y);
			m <<= 1;
			x++;
		}
		x -= 8;
		y++;
		src += 256;
	}
}

// Clear character doble-width (color background, graphics coordinates)
void DrawCharWClr(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) == 0) 
			{
				DrawPoint(x, y, col);
				DrawPoint(x+1, y, col);
			}
			else
			{
				DrawPointClr(x, y);
				DrawPointClr(x+1, y);
			}
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y++;
		src += 256;
	}
}

// Clear character double-height (color background, graphics coordinates)
void DrawCharHClr(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) == 0) 
			{
				DrawPoint(x, y, col);
				DrawPoint(x, y+1, col);
			}
			else
			{
				DrawPointClr(x, y);
				DrawPointClr(x, y+1);
			}
			m <<= 1;
			x++;
		}
		x -= 8;
		y += 2;
		src += 256;
	}
}

// Clear character doble-sized (color background, graphics coordinates)
void DrawChar2Clr(char ch, int x, int y, u8 col)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) == 0) 
			{
				DrawPoint(x, y, col);
				DrawPoint(x+1, y, col);
				DrawPoint(x, y+1, col);
				DrawPoint(x+1, y+1, col);
			}
			else
			{
				DrawPointClr(x, y);
				DrawPointClr(x+1, y);
				DrawPointClr(x, y+1);
				DrawPointClr(x+1, y+1);
			}
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y += 2;
		src += 256;
	}
}

// Invert character (background not changed, graphics coordinates)
void DrawCharInv(char ch, int x, int y)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) DrawPointInv(x, y);
			m <<= 1;
			x++;
		}
		x -= 8;
		y++;
		src += 256;
	}
}

// Invert character doble-width (background not changed, graphics coordinates)
void DrawCharWInv(char ch, int x, int y)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPointInv(x, y);
				DrawPointInv(x+1, y);
			}
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y++;
		src += 256;
	}
}

// Invert character doble-height (background not changed, graphics coordinates)
void DrawCharHInv(char ch, int x, int y)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPointInv(x, y);
				DrawPointInv(x, y+1);
			}
			m <<= 1;
			x++;
		}
		x -= 8;
		y += 2;
		src += 256;
	}
}

// Invert character doble-sized (background not changed, graphics coordinates)
void DrawChar2Inv(char ch, int x, int y)
{
	const u8* src = &DrawFont[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPointInv(x, y);
				DrawPointInv(x+1, y);
				DrawPointInv(x, y+1);
				DrawPointInv(x+1, y+1);
			}
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y += 2;
		src += 256;
	}
}

// Draw ASCIIZ text (black background, graphics coordinates)
void DrawText(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawChar(ch, x, y, col);
		x += 8;
	}
}

// Draw text condensed size 6x8 (black background, graphics coordinates)
void DrawTextCond(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharCond(ch, x, y, col);
		x += 6;
	}
}

// Draw text condensed size 6x6 (black background, graphics coordinates)
void DrawTextCond6(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharCond6(ch, x, y, col);
		x += 6;
	}
}

// Draw ASCIIZ text double-width (black background, graphics coordinates)
void DrawTextW(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharW(ch, x, y, col);
		x += 2*8;
	}
}

// Draw ASCIIZ text double-height (black background, graphics coordinates)
void DrawTextH(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharH(ch, x, y, col);
		x += 8;
	}
}

// Draw ASCIIZ text double-sized (black background, graphics coordinates)
void DrawText2(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawChar2(ch, x, y, col);
		x += 2*8;
	}
}

// Clear ASCIIZ text (color background, graphics coordinates)
void DrawTextClr(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharClr(ch, x, y, col);
		x += 8;
	}
}

// Clear ASCIIZ text double-width (color background, graphics coordinates)
void DrawTextWClr(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharWClr(ch, x, y, col);
		x += 2*8;
	}
}

// Clear ASCIIZ text double-height (color background, graphics coordinates)
void DrawTextHClr(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharHClr(ch, x, y, col);
		x += 8;
	}
}

// Clear ASCIIZ text double-sized (color background, graphics coordinates)
void DrawText2Clr(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawChar2Clr(ch, x, y, col);
		x += 2*8;
	}
}

// Invert ASCIIZ text (background not changed, graphics coordinates)
void DrawTextInv(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharInv(ch, x, y);
		x += 8;
	}
}

// Invert ASCIIZ text double-width (background not changed, graphics coordinates)
void DrawTextWInv(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharWInv(ch, x, y);
		x += 2*8;
	}
}

// Invert ASCIIZ text double-height (background not changed, graphics coordinates)
void DrawTextHInv(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharHInv(ch, x, y);
		x += 8;
	}
}

// Invert ASCIIZ text double-sized (background not changed, graphics coordinates)
void DrawText2Inv(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawChar2Inv(ch, x, y);
		x += 2*8;
	}
}

// ----------------------------------------------------------------------------
//                               Draw image
// ----------------------------------------------------------------------------

// draw image fast - all coordinates and dimensions must be multiply of bytes and must be valid
void DrawImgFast(const u8* img, const u8* attr, int x, int y, int xs, int ys, int w, int h, int wsb, int wsab)
{
// Videomode 4: graphics mode 256x192 pixels mono with color attributes 8x8 pixels, required memory 6144+384 = 6528 B (driver size 516 B in RAM)
#if VMODE == 4

	int i, j;
	const u8* s = &img[(xs >> 3) + ys*wsb];		// source pixels
	u8* d = &FrameBuf[(x >> 3) + y*WIDTHBYTE];	// destination pixels
	w >>= 3;
	wsb -= w;
	int wdb = WIDTHBYTE - w;
	for (i = h; i > 0; i--)
	{
		for (j = w; j > 0; j--)
		{
			*d++ = *s++;
		}
		s += wsb;
		d += wdb;
	}

	s = &attr[(xs >> 4) + (ys >> 3)*wsab];		// source attributes
	d = &AttrBuf[(x >> 4) + (y >> 3)*ATTRWIDTHBYTE]; // destination attributes
	w >>= 1;
	h >>= 3;
	wsab -= w;
	wdb = ATTRWIDTHBYTE - w;
	for (; h > 0; h--)
	{
		for (j = w; j > 0; j--)
		{
			*d++ = *s++;
		}
		s += wsb;
		d += wdb;
	}

// Videomode 2: graphics mode 160x120 pixels mono with color attributes 4x4 pixels, required memory 2400+600 = 3000 B (driver size 540 B in RAM)
#elif VMODE == 2

	int i, j;
	xs >>= 3;
	x >>= 3;
	const u8* s = &img[xs + ys*wsb];	// source pixels
	u8* d = &FrameBuf[x + y*WIDTHBYTE];	// destination pixels
	w >>= 3;
	wsb -= w;
	int wdb = WIDTHBYTE - w;
	for (i = h; i > 0; i--)
	{
		for (j = w; j > 0; j--)
		{
			*d++ = *s++;
		}
		s += wsb;
		d += wdb;
	}

	s = &attr[xs + (ys >> 2)*wsab];		// source attributes
	d = &AttrBuf[x + (y >> 2)*ATTRWIDTHBYTE]; // destination attributes
	h >>= 2;
	wsab -= w;
	wdb = ATTRWIDTHBYTE - w;
	for (; h > 0; h--)
	{
		for (j = w; j > 0; j--)
		{
			*d++ = *s++;
		}
		s += wsb;
		d += wdb;
	}

// Videomode 3: graphics mode 160x120 pixels mono with color attributes 2x2 pixels, required memory 2400+2400 = 4800 B (driver size 532 B in RAM)
#elif VMODE == 3

	int i, j;
	xs >>= 3;
	x >>= 3;
	const u8* s = &img[xs + ys*wsb];	// source pixels
	u8* d = &FrameBuf[x + y*WIDTHBYTE];	// destination pixels
	w >>= 3;
	wsb -= w;
	int wdb = WIDTHBYTE - w;
	for (i = h; i > 0; i--)
	{
		for (j = w; j > 0; j--)
		{
			*d++ = *s++;
		}
		s += wsb;
		d += wdb;
	}

	s = &attr[(xs << 1) + (ys >> 1)*wsab];		// source attributes
	d = &AttrBuf[(x << 1) + (y >> 1)*ATTRWIDTHBYTE]; // destination attributes
	h >>= 1;
	wsab -= (w << 1);
	wdb = ATTRWIDTHBYTE - (w << 1);
	for (; h > 0; h--)
	{
		for (j = w; j > 0; j--)
		{
			*d++ = *s++;
			*d++ = *s++;
		}
		s += wsab;
		d += wdb;
	}

#endif
}

// draw mono image
void DrawImg(const u8* img, int x, int y, int w, int h, int wsb, u8 col)
{
	int xd;
	int yd = y;
	int ys;
	int xs;
	int m;
	const u8* s;
	u8 b;
	for (ys = 0; ys < h; ys++)
	{
		s = &img[ys*wsb];
		xd = x;
		m = B7;
		b = *s++;
		for (xs = 0; xs < w; xs++)
		{
			if ((b & m) == 0) DrawPoint(xd, yd, col);
			m >>= 1;
			if (m == 0)
			{
				m = B7;
				b = *s++;
			}
			xd++;
		}
		yd++;
	}
}

// draw mono image with background
void DrawImgBg(const u8* img, int x, int y, int w, int h, int wsb, u8 col)
{
	int xd;
	int yd = y;
	int ys;
	int xs;
	int m;
	const u8* s;
	u8 b;
	for (ys = 0; ys < h; ys++)
	{
		s = &img[ys*wsb];
		xd = x;
		m = B7;
		b = *s++;
		for (xs = 0; xs < w; xs++)
		{
			if ((b & m) == 0)
				DrawPoint(xd, yd, col);
			else
				DrawPointClr(xd, yd);
			m >>= 1;
			if (m == 0)
			{
				m = B7;
				b = *s++;
			}
			xd++;
		}
		yd++;
	}
}

// clear mono image
void DrawImgClr(const u8* img, int x, int y, int w, int h, int wsb)
{
	int xd;
	int yd = y;
	int ys;
	int xs;
	int m;
	const u8* s;
	u8 b;
	for (ys = 0; ys < h; ys++)
	{
		s = &img[ys*wsb];
		xd = x;
		m = B7;
		b = *s++;
		for (xs = 0; xs < w; xs++)
		{
			if ((b & m) == 0) DrawPointClr(xd, yd);
			m >>= 1;
			if (m == 0)
			{
				m = B7;
				b = *s++;
			}
			xd++;
		}
		yd++;
	}
}

// set mono image
void DrawImgSet(const u8* img, int x, int y, int w, int h, int wsb)
{
	int xd;
	int yd = y;
	int ys;
	int xs;
	int m;
	const u8* s;
	u8 b;
	for (ys = 0; ys < h; ys++)
	{
		s = &img[ys*wsb];
		xd = x;
		m = B7;
		b = *s++;
		for (xs = 0; xs < w; xs++)
		{
			if ((b & m) == 0) DrawPointSet(xd, yd);
			m >>= 1;
			if (m == 0)
			{
				m = B7;
				b = *s++;
			}
			xd++;
		}
		yd++;
	}
}

// invert mono image
void DrawImgInv(const u8* img, int x, int y, int w, int h, int wsb)
{
	int xd;
	int yd = y;
	int ys;
	int xs;
	int m;
	const u8* s;
	u8 b;
	for (ys = 0; ys < h; ys++)
	{
		s = &img[ys*wsb];
		xd = x;
		m = B7;
		b = *s++;
		for (xs = 0; xs < w; xs++)
		{
			if ((b & m) == 0) DrawPointInv(xd, yd);
			m >>= 1;
			if (m == 0)
			{
				m = B7;
				b = *s++;
			}
			xd++;
		}
		yd++;
	}
}

#endif // VMODE <= 4 // only graphics modes

#endif // USE_DRAW

#if USE_PRINT		// 1=use text printing functions

// ----------------------------------------------------------------------------
//                               Printing
// ----------------------------------------------------------------------------

// set print font
void SetFont(const char* font)
{
	DrawFont = font;

#if VMODE == 7
	// copy font to font buffer
	memcpy(FontBuf, font, 2048);
#endif
}

// scroll screen
void PrintScroll()
{
	PrintRow--;

#if VMODE >= 5	// text modes

	memmove(&FrameBuf[0], &FrameBuf[WIDTHBYTE], FRAMESIZE-WIDTHBYTE);
	memset(&FrameBuf[FRAMESIZE-WIDTHBYTE], ' ', WIDTHBYTE);

	memmove(&AttrBuf[0], &AttrBuf[ATTRWIDTHBYTE], ATTRSIZE-ATTRWIDTHBYTE);
	memset(&AttrBuf[ATTRSIZE-ATTRWIDTHBYTE], COL_WHITE|(COL_WHITE<<4), ATTRWIDTHBYTE);

#else // VMODE >= 5

	memmove(&FrameBuf[0], &FrameBuf[WIDTHBYTE*8], FRAMESIZE-WIDTHBYTE*8);
	memset(&FrameBuf[FRAMESIZE-WIDTHBYTE*8], 0, WIDTHBYTE*8);

// Videomode 4: graphics mode 256x192 pixels mono with color attributes 8x8 pixels, required memory 6144+384 = 6528 B (driver size 516 B in RAM)
#if VMODE == 4
	memmove(&AttrBuf[0], &AttrBuf[ATTRWIDTHBYTE], ATTRSIZE-ATTRWIDTHBYTE);
	memset(&AttrBuf[ATTRSIZE-ATTRWIDTHBYTE], COL_WHITE|(COL_WHITE<<4), ATTRWIDTHBYTE);
// Videomode 2: graphics mode 160x120 pixels mono with color attributes 4x4 pixels, required memory 2400+600 = 3000 B (driver size 540 B in RAM)
#elif VMODE == 2
	memmove(&AttrBuf[0], &AttrBuf[2*ATTRWIDTHBYTE], ATTRSIZE-2*ATTRWIDTHBYTE);
	memset(&AttrBuf[ATTRSIZE-2*ATTRWIDTHBYTE], COL_WHITE|(COL_WHITE<<4), 2*ATTRWIDTHBYTE);
// Videomode 3: graphics mode 160x120 pixels mono with color attributes 2x2 pixels, required memory 2400+2400 = 4800 B (driver size 532 B in RAM)
#elif VMODE == 3
	memmove(&AttrBuf[0], &AttrBuf[4*ATTRWIDTHBYTE], ATTRSIZE-4*ATTRWIDTHBYTE);
	memset(&AttrBuf[ATTRSIZE-4*ATTRWIDTHBYTE], COL_WHITE|(COL_WHITE<<4), 4*ATTRWIDTHBYTE);
// Videomode 1: graphics mode 128x64 pixels mono with color attributes 1x1 pixel, required memory 1024+4096 = 5120 B
#elif VMODE == 1
	memmove(&AttrBuf[0], &AttrBuf[8*ATTRWIDTHBYTE], ATTRSIZE-8*ATTRWIDTHBYTE);
	memset(&AttrBuf[ATTRSIZE-8*ATTRWIDTHBYTE], COL_WHITE|(COL_WHITE<<4), 8*ATTRWIDTHBYTE);
#endif

#endif // VMODE >= 5
}

// print character at text position
void PrintCharAt(char ch, int x, int y, u8 col)
{
#if VMODE >= 5	// text modes

	// check position
	if ((x < 0) || (x >= TEXTWIDTH) || (y < 0) || (y >= TEXTHEIGHT)) return;

	// save character
	u8* dst = &FrameBuf[WIDTHBYTE*y + x];
	*dst = ch;

	// save attribute
	u8* a = &AttrBuf[ATTRWIDTHBYTE*y + x/2];
	if ((x & 1) == 0)
		*a = (*a & 0xf0) | col;
	else
		*a = (*a & 0x0f) | (col << 4);

#else // VMODE >= 5

	// check position
	if ((x < 0) || (x >= TEXTWIDTH) || (y < 0) || (y >= TEXTHEIGHT)) return;

	// destination address
	u8* dst = &FrameBuf[WIDTHBYTE*8*y + x];

	// source address
	const u8* src = &DrawFont[(u8)ch];

	// write pixels
	dst[0*WIDTHBYTE] = src[0*256];
	dst[1*WIDTHBYTE] = src[1*256];
	dst[2*WIDTHBYTE] = src[2*256];
	dst[3*WIDTHBYTE] = src[3*256];
	dst[4*WIDTHBYTE] = src[4*256];
	dst[5*WIDTHBYTE] = src[5*256];
	dst[6*WIDTHBYTE] = src[6*256];
	dst[7*WIDTHBYTE] = src[7*256];

	// write color
// Videomode 4: graphics mode 256x192 pixels mono with color attributes 8x8 pixels, required memory 6144+384 = 6528 B (driver size 516 B in RAM)
#if VMODE == 4
	u8* a = &AttrBuf[ATTRWIDTHBYTE*y + x/2];
	if ((x & 1) == 0)
		*a = (*a & 0xf0) | col;
	else
		*a = (*a & 0x0f) | (col << 4);

// Videomode 2: graphics mode 160x120 pixels mono with color attributes 4x4 pixels, required memory 2400+600 = 3000 B (driver size 540 B in RAM)
#elif VMODE == 2
	u8* a = &AttrBuf[ATTRWIDTHBYTE*2*y + x];
	col = col | (col << 4);
	*a = col;
	a[ATTRWIDTHBYTE] = col;

// Videomode 3: graphics mode 160x120 pixels mono with color attributes 2x2 pixels, required memory 2400+2400 = 4800 B (driver size 532 B in RAM)
#elif VMODE == 3
	u8* a = &AttrBuf[ATTRWIDTHBYTE*4*y + x*2];
	col = col | (col << 4);
	*a = col;
	a[1] = col;
	a[ATTRWIDTHBYTE] = col;
	a[ATTRWIDTHBYTE+1] = col;
	a[2*ATTRWIDTHBYTE] = col;
	a[2*ATTRWIDTHBYTE+1] = col;
	a[3*ATTRWIDTHBYTE] = col;
	a[3*ATTRWIDTHBYTE+1] = col;
#endif

#endif // VMODE >= 5
}

// print ASCIIZ text at text position
void PrintTextAt(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		PrintCharAt(ch, x, y, col);
		x++;
	}
}

// print text with length at text position
void PrintTextLenAt(const char* text, int len, int x, int y, u8 col)
{
	char ch;
	for (; len > 0; len--)
	{
		ch = *text++;
		PrintCharAt(ch, x, y, col);
		x++;
	}
}

// reset print position
void PrintHome(void)
{
	PrintPos = 0;
	PrintRow = 0;
}

// print new line
void PrintNewLine(void)
{
	PrintPos = 0; // reset position
	PrintRow++; // increase row

	// scroll screen
	if (PrintRow >= TEXTHEIGHT)
	{
		PrintScroll(); // scroll screen
		PrintRow = TEXTHEIGHT-1;
	}
}

// print character RAW at print position, without control characters
void PrintCharRaw(char ch)
{
	// print character
	PrintCharAt(ch, PrintPos, PrintRow, PrintCol);

	// move right
	PrintPos++; // increase position

	// new line
	if (PrintPos >= TEXTWIDTH) PrintNewLine();
}

// print character RAW repeat, without control characters
void PrintCharRawRep(char ch, int num)
{
	while (num-- > 0) PrintCharRaw(ch);
}

// print space character
void PrintSpc(void)
{
	PrintCharRaw(' ' + PrintInv);
}

// print space character repeat
void PrintSpcRep(int num)
{
	while (num-- > 0) PrintSpc();
}

// print space to position
void PrintSpcTo(int pos)
{
	while (PrintPos < pos) PrintSpc();
}

// print character at print position
//   Control characters:
//     0x01 '\1' ^A ... set not-inverted text
//     0x02 '\2' ^B ... set inverted text (shift character code by 0x80)
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
void PrintChar(char ch)
{
	switch ((u8)ch)
	{
	// printable character
	default:
		PrintCharAt(ch + PrintInv, PrintPos, PrintRow, PrintCol);

  // ! continue case 0x07 (move right)

	// '\a' ... (bell) move cursor 1 position right (no print)
	case 0x07:
		PrintPos++; // increase position
		if (PrintPos < TEXTWIDTH) break;

  // ! continue case 0x0A (new line)

	// '\n' ... (new line) move cursor to start of next row
	case 0x0A:
		PrintNewLine();
		break;

	// 'x01' ... set not-inverted text
	case 0x01:
		PrintInv = 0;
		break;

	// 'x02' ... set inverted text
	case 0x02:
		PrintInv = 0x80;
		break;

	// '\b' ... (back space) move cursor 1 position left (no print)
	case 0x08:
		if (PrintPos > 0) PrintPos--;
		break;

	// '\t' ... (tabulator) move cursor to next 8-character position, print spaces
	case 0x09:
		do PrintChar(' '); while ((PrintPos & 7) != 0); // print spaces
		break;		

	// '\v' ... (vertical tabulator) move cursor to start of previous row
	case 0x0B:
		if (PrintRow > 0) PrintRow--; // decrease row
		PrintPos = 0;
		break;

	// '\f' ... (form feed) clear screen, reset cursor position and set default color
	case 0x0C:
		DrawClear();
		break;

	// '\r' ... (carriage return) move cursor to start of current row
	case 0x0D:
		PrintPos = 0;
		break;

	// 'x10' ... set gray text color (COL_GRAY)
	case 0x10:
		PrintCol = COL_GRAY;
		break;

	// 'x11' ... set blue text color (COL_BLUE)
	case 0x11:
		PrintCol = COL_BLUE;
		break;

	// 'x12' ... set green text color (COL_GREEN)
	case 0x12:
		PrintCol = COL_GREEN;
		break;

	// 'x13' ... set cyan text color (COL_CYAN)
	case 0x13:
		PrintCol = COL_CYAN;
		break;

	// 'x14' ... set red text color (COL_RED)
	case 0x14:
		PrintCol = COL_RED;
		break;

	// 'x15' ... set magenta text color (COL_MAGENTA)
	case 0x15:
		PrintCol = COL_MAGENTA;
		break;

	// 'x16' ... set yellow text color (COL_YELLOW)
	case 0x16:
		PrintCol = COL_YELLOW;
		break;

	// 'x17' ... set white text color (COL_WHITE)
	case 0x17:
		PrintCol = COL_WHITE;
		break;
	}
}

// print character repeat
void PrintCharRep(char ch, int num)
{
	while (num-- > 0) PrintChar(ch);
}

// print ASCIIZ text
void PrintText(const char* text)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		PrintChar(ch);
	}
}

// print ASCIIZ text RAW, without control characters
void PrintTextRaw(const char* text)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		PrintCharRaw(ch);
	}
}

// print text with length
void PrintTextLen(const char* text, int len)
{
	char ch;
	for (; len > 0; len--)
	{
		ch = *text++;
		PrintChar(ch);
	}
}

// print text with length RAW, without control characters
void PrintTextLenRaw(const char* text, int len)
{
	char ch;
	for (; len > 0; len--)
	{
		ch = *text++;
		PrintCharRaw(ch);
	}
}

#endif // USE_PRINT

#endif // USE_DRAW || USE_PRINT || USE_DISP
