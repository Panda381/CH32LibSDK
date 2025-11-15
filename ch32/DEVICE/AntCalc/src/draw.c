
// ****************************************************************************
//
//                           AntCalc - Drawing
//
// ****************************************************************************

#include "../include.h"

Bool PrintInv = False;	// invert text

// clear screen
void DrawClear()
{
	memset(FrameBuf, 0, FRAMESIZE);
	PrintInv = False;
}

// ----------------------------------------------------------------------------
//                               Draw point
// ----------------------------------------------------------------------------

// draw pixel fast without limits
void DrawPointFast(int x, int y, u8 col)
{
	u8* d = &FrameBuf[(x>>3) + y*WIDTHBYTE];
	x = 7 - (x & 7);
	x = 1<<x;
	if (col == 0)
		*d &= ~x;
	else
		*d |= x;
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

	// get pixel
	u8* d = &FrameBuf[(x>>3) + y*WIDTHBYTE];
	int x2 = 7 - (x & 7);
	u8 col = (*d >> x2) & 1;
	return col;
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
	// clear pixel
	u8* d = &FrameBuf[(x>>3) + y*WIDTHBYTE];
	x = 7 - (x & 7);
	*d |= (1<<x);
}

// clear pixel
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

// Draw character normal sized (no background, graphics coordinates)
void DrawChar(char ch, int x, int y, u8 col)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		if (PrintInv != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) DrawPoint(x, y, col);
			m <<= 1;
			x++;
		}
		x -= 8;
		y++;
		src += 128;
	}
}

// Draw character normal sized, black background
void DrawCharBg(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		if (PrintInv != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0)
				DrawPointSet(x, y);
			else
				DrawPointClr(x, y);
			m <<= 1;
			x++;
		}
		x -= 8;
		y++;
		src += 128;
	}
}

// Draw character normal sized, white background
void DrawCharBgB(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		if (PrintInv != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) == 0)
				DrawPointSet(x, y);
			else
				DrawPointClr(x, y);
			m <<= 1;
			x++;
		}
		x -= 8;
		y++;
		src += 128;
	}
}

// Draw character condensed size 6x8 (no background, graphics coordinates)
void DrawCharCond(char ch, int x, int y, u8 col)
{
	const u8* src = &FONTCOND[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		if (PrintInv != 0) m = ~m;
		for (j = 6; j > 0; j--)
		{
			if ((m & B7) != 0) DrawPoint(x, y, col);
			m <<= 1;
			x++;
		}
		x -= 6;
		y++;
		src += 128;
	}
}

// Draw character condensed size 6x8, black background
void DrawCharCondBg(char ch, int x, int y)
{
	const u8* src = &FONTCOND[(u8)ch];
	int i, j;
	u8 m;
	for (i = 8; i > 0; i--)
	{
		m = *src;
		if (PrintInv != 0) m = ~m;
		for (j = 6; j > 0; j--)
		{
			if ((m & B7) != 0)
				DrawPointSet(x, y);
			else
				DrawPointClr(x, y);
			m <<= 1;
			x++;
		}
		x -= 6;
		y++;
		src += 128;
	}
}

// Draw character double-width (no background, graphics coordinates)
void DrawCharW(char ch, int x, int y, u8 col)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		if (PrintInv != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPoint(x, y, col);
				DrawPoint(x+1, y, col);
			}
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y++;
		src += 128;
	}
}

// Draw character double-height (no background, graphics coordinates)
void DrawCharH(char ch, int x, int y, u8 col)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		if (PrintInv != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPoint(x, y, col);
				DrawPoint(x, y+1, col);
			}
			m <<= 1;
			x++;
		}
		x -= 8;
		y += 2;
		src += 128;
	}
}

// Draw character double-sized (no background, graphics coordinates)
void DrawChar2(char ch, int x, int y, u8 col)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		if (PrintInv != 0) m = ~m;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPoint(x, y, col);
				DrawPoint(x+1, y, col);
				DrawPoint(x, y+1, col);
				DrawPoint(x+1, y+1, col);
			}
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y += 2;
		src += 128;
	}
}

// Clear character (background not changed, graphics coordinates)
void DrawCharClr(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) DrawPointClr(x, y);
			m <<= 1;
			x++;
		}
		x -= 8;
		y++;
		src += 128;
	}
}

// Clear character doble-width (background not changed, graphics coordinates)
void DrawCharWClr(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPointClr(x, y);
				DrawPointClr(x+1, y);
			}
			m <<= 1;
			x += 2;
		}
		x -= 2*8;
		y++;
		src += 128;
	}
}

// Clear character double-height (background not changed, graphics coordinates)
void DrawCharHClr(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
			{
				DrawPointClr(x, y);
				DrawPointClr(x, y+1);
			}
			m <<= 1;
			x++;
		}
		x -= 8;
		y += 2;
		src += 128;
	}
}

// Clear character doble-sized (background not changed, graphics coordinates)
void DrawChar2Clr(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
	{
		m = *src;
		for (j = 8; j > 0; j--)
		{
			if ((m & B7) != 0) 
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
		src += 128;
	}
}

// Invert character (background not changed, graphics coordinates)
void DrawCharInv(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
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
		src += 128;
	}
}

// Invert character doble-width (background not changed, graphics coordinates)
void DrawCharWInv(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
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
		src += 128;
	}
}

// Invert character doble-height (background not changed, graphics coordinates)
void DrawCharHInv(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
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
		src += 128;
	}
}

// Invert character doble-sized (background not changed, graphics coordinates)
void DrawChar2Inv(char ch, int x, int y)
{
	const u8* src = &FONT[(u8)ch];
	int i, j;
	u8 m;
	for (i = 12; i > 0; i--)
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
		src += 128;
	}
}

// Draw ASCIIZ text (no background, graphics coordinates)
void DrawText(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawChar(ch, x, y, col);
		x += 8;
	}
}

// Draw ASCIIZ text, black background
void DrawTextBg(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharBg(ch, x, y);
		x += 8;
	}
}

// Draw ASCIIZ text, white background
void DrawTextBgB(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharBgB(ch, x, y);
		x += 8;
	}
}

// Draw text condensed size 6x8 (no background, graphics coordinates)
void DrawTextCond(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharCond(ch, x, y, col);
		x += 6;
	}
}

// Draw text condensed size 6x8, black background
void DrawTextCondBg(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharCondBg(ch, x, y);
		x += 6;
	}
}

// Draw ASCIIZ text double-width (no background, graphics coordinates)
void DrawTextW(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharW(ch, x, y, col);
		x += 2*8;
	}
}

// Draw ASCIIZ text double-height (no background, graphics coordinates)
void DrawTextH(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharH(ch, x, y, col);
		x += 8;
	}
}

// Draw ASCIIZ text double-sized (no background, graphics coordinates)
void DrawText2(const char* text, int x, int y, u8 col)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawChar2(ch, x, y, col);
		x += 2*8;
	}
}

// Clear ASCIIZ text (background not changed, graphics coordinates)
void DrawTextClr(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharClr(ch, x, y);
		x += 8;
	}
}

// Clear ASCIIZ text double-width (background not changed, graphics coordinates)
void DrawTextWClr(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharWClr(ch, x, y);
		x += 2*8;
	}
}

// Clear ASCIIZ text double-height (background not changed, graphics coordinates)
void DrawTextHClr(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawCharHClr(ch, x, y);
		x += 8;
	}
}

// Clear ASCIIZ text double-sized (background not changed, graphics coordinates)
void DrawText2Clr(const char* text, int x, int y)
{
	char ch;
	while ((ch = *text++) != 0)
	{
		DrawChar2Clr(ch, x, y);
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
void DrawImgFast(const u8* img, int x, int y, int xs, int ys, int w, int h, int wsb)
{
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
}

void DrawImgInvFast(const u8* img, int x, int y, int xs, int ys, int w, int h, int wsb)
{
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
			*d++ = ~*s++;
		}
		s += wsb;
		d += wdb;
	}
}

// draw mono image, transparent background
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

// draw mono image with black background
void DrawImgBg(const u8* img, int x, int y, int w, int h, int wsb)
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
				DrawPointSet(xd, yd);
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
