#include "../include.h"

// format: attribute graphics with cell 2x2 pixels
// image width: 160 pixels
// image height: 120 lines
// image pitch: 20 bytes
// attribute width: 80 colors
// attribute height: 60 rows
// attribute pitch: 40 bytes
const u8 ImgIntro_Attr[2400] = {
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0x99, 0x99, 0xB9, 0xBB, 0x99, 
	0xB9, 0x9B, 0x99, 0x99, 0x99, 0x99, 0xBB, 0x99, 0x99, 0x99, 0x99, 0x99, 0xBB, 0x99, 0x99, 0x99, 
	0x99, 0xBB, 0x9B, 0x99, 0x99, 0x99, 0xB9, 0xBB, 0x99, 0xB9, 0xBB, 0xBB, 0x99, 0xB9, 0xBB, 0xBB, 
	0xBB, 0x9B, 0x99, 0x99, 0x99, 0xB9, 0xBB, 0x99, 0xB9, 0x9B, 0x99, 0x99, 0x99, 0x99, 0xBB, 0x99, 
	0x99, 0x99, 0x99, 0x99, 0xBB, 0x99, 0x99, 0x99, 0x99, 0xBB, 0x9B, 0x99, 0x99, 0x99, 0xB9, 0xBB, 
	0x99, 0x99, 0xBB, 0xBB, 0x99, 0xB9, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0x99, 
	0xB9, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0x99, 0xB9, 0xBB, 
	0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0x99, 0x99, 0xB9, 0xBB, 0x99, 0xB9, 0xBB, 0xBB, 
	0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0x99, 0xB9, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0x99, 0xB9, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 
	0x99, 0x99, 0x99, 0xBB, 0x99, 0xB9, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0x99, 
	0xB9, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0x99, 0x99, 0x99, 
	0xB9, 0xBB, 0x9B, 0x99, 0x99, 0x99, 0xBB, 0xBB, 0x99, 0x99, 0x99, 0xB9, 0x99, 0xB9, 0xBB, 0xBB, 
	0xBB, 0x9B, 0x99, 0x99, 0x99, 0xBB, 0xBB, 0x99, 0xB9, 0x9B, 0x99, 0x99, 0x99, 0xB9, 0xBB, 0xBB, 
	0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0x99, 0x99, 0x99, 0xB9, 0xBB, 0x9B, 0x99, 0x99, 0x99, 0xBB, 0xBB, 
	0x99, 0x99, 0x99, 0x99, 0x99, 0xB9, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0x99, 0x99, 0xBB, 0xBB, 0x99, 
	0xB9, 0x9B, 0x99, 0x99, 0x99, 0xB9, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0x99, 0x99, 0x99, 
	0xB9, 0xBB, 0x9B, 0x99, 0x99, 0x99, 0xBB, 0xBB, 0x99, 0xB9, 0x99, 0x99, 0x99, 0xB9, 0xBB, 0xBB, 
	0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0x99, 0xB9, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0x99, 0xB9, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 
	0x99, 0xB9, 0x9B, 0x99, 0x99, 0xB9, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0x99, 
	0xB9, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0x99, 0xB9, 0xBB, 
	0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0x99, 0xB9, 0xBB, 0x99, 0x99, 0xB9, 0xBB, 0xBB, 
	0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0x99, 0xB9, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0x99, 0x99, 0x99, 0x99, 0xBB, 0x9B, 0x99, 0x99, 0x99, 0xB9, 0xBB, 
	0x99, 0xB9, 0xBB, 0x9B, 0x99, 0xB9, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0x99, 
	0xB9, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x9B, 0x99, 0xBB, 0xBB, 0xBB, 0x99, 0x99, 0x99, 
	0x99, 0xBB, 0x9B, 0x99, 0x99, 0x99, 0xB9, 0xBB, 0x99, 0xB9, 0xBB, 0xBB, 0x99, 0xB9, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x22, 0x22, 0x22, 0x22, 0xB2, 0x11, 0x11, 0x11, 0x11, 0x11, 
	0x11, 0x2B, 0x22, 0x22, 0x22, 0x22, 0x22, 0xB2, 0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x22, 0xAA, 
	0x22, 0x22, 0xB2, 0x11, 0x11, 0xAA, 0xAA, 0x11, 0x11, 0x2B, 0x22, 0xA2, 0xAA, 0x2A, 0x22, 0xB2, 
	0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0xA2, 0xAA, 0x22, 0x22, 0xB2, 0x11, 0xA1, 0xAA, 0xAA, 0x11, 
	0x11, 0x2B, 0x22, 0xA2, 0xAA, 0xAA, 0x22, 0xB2, 0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0xA2, 0xAA, 
	0x22, 0x22, 0xB2, 0x11, 0xA1, 0xAA, 0xAA, 0x11, 0x11, 0x2B, 0x22, 0x22, 0xAA, 0xAA, 0x22, 0xB2, 
	0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x22, 0xAA, 0x22, 0x22, 0xB2, 0x11, 0xA1, 0xAA, 0xAA, 0x1A, 
	0x11, 0x2B, 0x22, 0x22, 0xAA, 0xAA, 0x22, 0xB2, 0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xAB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x22, 0xAA, 
	0x22, 0x22, 0xB2, 0x11, 0xA1, 0x1A, 0xAA, 0x1A, 0x11, 0x2B, 0x22, 0x22, 0x22, 0xAA, 0x22, 0xB2, 
	0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAB, 0xAA, 0xBA, 0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0xA2, 0xAA, 0x2A, 0x22, 0xB2, 0x11, 0xA1, 0xAA, 0xAA, 0x1A, 
	0x11, 0x2B, 0x22, 0xA2, 0xAA, 0xAA, 0x22, 0xB2, 0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xAA, 0xAA, 0xAB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x22, 0x22, 
	0x22, 0x22, 0xB2, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x2B, 0x22, 0x22, 0x22, 0x22, 0x22, 0xB2, 
	0xAB, 0xBA, 0xBB, 0xAB, 0xAA, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xAA, 0xBA, 0xAA, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x22, 0x22, 0x22, 0x22, 0xB2, 0x11, 0x11, 0x11, 0x11, 0x11, 
	0x11, 0x2B, 0x22, 0x22, 0x22, 0x22, 0x22, 0xB2, 0xAB, 0xBA, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xBA, 
	0xAA, 0xAA, 0xAB, 0xBA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xAB, 0xBB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBA, 0xAA, 0xAA, 0xBB, 0xBA, 0xAA, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x11, 0xB1, 0x22, 0x22, 0x22, 0x22, 0x22, 
	0x22, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x11, 0xB1, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xBB, 0xAA, 0xBA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0xAA, 0xAA, 
	0x1A, 0x11, 0xB1, 0x22, 0xA2, 0xAA, 0xAA, 0x2A, 0x22, 0x1B, 0x11, 0xA1, 0x1A, 0x11, 0x11, 0xB1, 
	0xAB, 0xAA, 0xBA, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAB, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0xAA, 0x11, 0x11, 0x11, 0xB1, 0x22, 0xA2, 0x2A, 0xA2, 0x2A, 
	0x22, 0x1B, 0x11, 0xA1, 0x1A, 0x11, 0x11, 0xB1, 0xAB, 0xBA, 0xBB, 0xBB, 0xAB, 0xAA, 0xBA, 0xBB, 
	0xAB, 0xBA, 0xAA, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0xAA, 0xAA, 
	0x11, 0x11, 0xB1, 0x22, 0x22, 0xAA, 0xAA, 0x22, 0x22, 0x1B, 0x11, 0xAA, 0xA1, 0x11, 0x11, 0xB1, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAB, 0xAB, 0xAA, 0xBA, 0xBA, 0xAA, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0xAA, 0xAA, 0x1A, 0x11, 0xB1, 0x22, 0xA2, 0xAA, 0xAA, 0x2A, 
	0x22, 0x1B, 0x11, 0xAA, 0xAA, 0xAA, 0x11, 0xAB, 0xAA, 0xAA, 0xBB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xBA, 0xAA, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0x11, 0xAA, 
	0x1A, 0x11, 0xB1, 0x22, 0xA2, 0x2A, 0xA2, 0x2A, 0x22, 0x1B, 0x11, 0xAA, 0xAA, 0xAA, 0x11, 0xAB, 
	0xAA, 0xBA, 0xBB, 0xBB, 0xAA, 0xAA, 0xBB, 0xBB, 0xAA, 0xBA, 0xAB, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0xAA, 0xAA, 0x1A, 0x11, 0xB1, 0x22, 0xA2, 0xAA, 0xAA, 0x2A, 
	0x22, 0x1B, 0x11, 0x11, 0xAA, 0x11, 0x11, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xAB, 0xBA, 0xBB, 0xBB, 
	0xAB, 0xAA, 0xAB, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0x11, 0x11, 
	0x11, 0x11, 0xB1, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x11, 0xAA, 
	0xAA, 0xBB, 0xBB, 0xBB, 0xAB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xBA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xAA, 0xBA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 
	0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xAA, 0xBA, 0xAA, 0xAA, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x22, 0x22, 0x22, 0x22, 0xB2, 0x11, 0x11, 0x11, 0x11, 0x11, 
	0x11, 0x2B, 0x22, 0x22, 0x22, 0x22, 0x22, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xAA, 0xAA, 0xAA, 0xAB, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0xA2, 0x2A, 0x22, 
	0xAA, 0x22, 0xB2, 0x11, 0xAA, 0x1A, 0xA1, 0xAA, 0x11, 0x2B, 0xA2, 0x2A, 0xA2, 0xAA, 0x2A, 0xAA, 
	0xAA, 0xBB, 0xBB, 0xBB, 0xAB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xAA, 0xAA, 0xBA, 0xAA, 0xBA, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0xA2, 0x2A, 0xA2, 0xAA, 0x22, 0xB2, 0xA1, 0xAA, 0x1A, 0xAA, 0xAA, 
	0x11, 0x2B, 0xAA, 0x2A, 0x22, 0xAB, 0x2A, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xAA, 0xBA, 0xBB, 0xBB, 
	0xAB, 0xAA, 0xAA, 0xAA, 0xBA, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x2A, 0x22, 
	0xAA, 0x22, 0xB2, 0x11, 0xA1, 0x1A, 0x11, 0xAA, 0x11, 0x2B, 0xA2, 0x2A, 0x22, 0xAA, 0x22, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xAA, 0xAA, 0xAA, 0xAA, 0xBA, 0xAB, 0xAA, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x2A, 0x22, 0xAA, 0x22, 0xB2, 0x11, 0xA1, 0x1A, 0x11, 0xAA, 
	0x11, 0x2B, 0xA2, 0x2A, 0x22, 0xA2, 0x2A, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xBA, 0xAB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0xA2, 0xAA, 0xA2, 
	0xAA, 0x2A, 0xB2, 0xA1, 0xAA, 0xAA, 0xAA, 0xAA, 0x1A, 0x2B, 0xAA, 0xAA, 0xA2, 0xAA, 0x2A, 0xAB, 
	0xAA, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBA, 0xAB, 0xAA, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0xA2, 0xAA, 0xA2, 0xAA, 0x2A, 0xB2, 0xA1, 0xAA, 0xAA, 0xAA, 0xAA, 
	0x1A, 0x2B, 0xAA, 0xAA, 0xA2, 0xAA, 0x22, 0xAB, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x2B, 0x22, 0x22, 0x22, 
	0x22, 0x22, 0xB2, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x2B, 0x22, 0x22, 0x22, 0x22, 0x22, 0xB2, 
	0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAB, 0xAA, 0xAA, 0xAA, 0xBB, 0xAB, 0xAA, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAB, 0xAA, 0xBB, 0xBB, 0xBB, 0x22, 0xB2, 0xBB, 
	0xBB, 0xAA, 0xAA, 0xBA, 0xBB, 0xAB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0x11, 0x11, 
	0x11, 0x11, 0xBB, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x11, 0xB1, 
	0xBB, 0xAA, 0xBA, 0xBB, 0xBB, 0x22, 0x22, 0xB2, 0xBB, 0xAA, 0xAA, 0xBB, 0xBA, 0xAA, 0xAA, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0x1A, 0x11, 0xAA, 0x11, 0xBB, 0x22, 0xA2, 0x22, 0xAA, 0xAA, 
	0x22, 0x1B, 0x11, 0x11, 0xAA, 0x1A, 0x11, 0xB1, 0xAB, 0xAB, 0xAA, 0xBB, 0xAA, 0xBA, 0x2B, 0x22, 
	0xBB, 0xAA, 0xBA, 0xAB, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0xA1, 0x1A, 0xA1, 
	0xAA, 0x1A, 0xBB, 0xA2, 0xAA, 0x22, 0xAA, 0xAA, 0x22, 0x1B, 0x11, 0xA1, 0xAA, 0xAA, 0x11, 0xB1, 
	0xAB, 0xBA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xAB, 0xAA, 0xBB, 0xAA, 0xAA, 0xAA, 0xBA, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0xA1, 0x1A, 0xA1, 0xA1, 0x1A, 0xBB, 0xA2, 0xAA, 0x22, 0x2A, 0x22, 
	0x22, 0x1B, 0x11, 0xA1, 0x11, 0xAA, 0x11, 0xB1, 0xAB, 0xBA, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0x1A, 0x11, 
	0xAA, 0x1A, 0xBB, 0x22, 0xAA, 0x22, 0xAA, 0xAA, 0x22, 0x1B, 0x11, 0xA1, 0xAA, 0xAA, 0x11, 0xB1, 
	0xAB, 0xBA, 0xBB, 0xBB, 0xAB, 0xAA, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0x1A, 0xA1, 0xAA, 0x11, 0xBB, 0x22, 0xAA, 0x22, 0x22, 0xAA, 
	0x2A, 0x1B, 0x11, 0x11, 0xAA, 0xAA, 0x11, 0xB1, 0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0xAA, 0xAA, 0xA1, 
	0xAA, 0x1A, 0xBB, 0xA2, 0xAA, 0xBA, 0xAA, 0xAA, 0x2A, 0x1B, 0x11, 0xA1, 0xAA, 0xAA, 0x11, 0xB1, 
	0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0xAA, 0xAA, 0xA1, 0xAA, 0x1A, 0xBB, 0xA2, 0xAA, 0xBA, 0xAA, 0xAA, 
	0x22, 0x1B, 0x11, 0xA1, 0xAA, 0x1A, 0x11, 0xB1, 0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0x1B, 0x11, 0x11, 0x11, 
	0x11, 0x11, 0xBB, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x11, 0xB1, 
	0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
};

const u8 ImgIntro[2400] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFC, 0x0F, 0x81, 0xFF, 0xFE, 0x0F, 
	0xFF, 0xFE, 0x0F, 0xFF, 0xF0, 0x3F, 0xFF, 0xC0, 0xF0, 0x00, 0xF8, 0x00, 0x03, 0xFF, 0xFC, 0x0F, 
	0x81, 0xFF, 0xFE, 0x0F, 0xFF, 0xFE, 0x0F, 0xFF, 0xF0, 0x3F, 0xFF, 0xC0, 0xF8, 0x00, 0xF8, 0x00, 
	0x03, 0xFF, 0xFC, 0x0F, 0x81, 0xFF, 0xFE, 0x0F, 0xFF, 0xFE, 0x0F, 0xFF, 0xF0, 0x3F, 0xFF, 0xC0, 
	0xFC, 0x00, 0xF8, 0x00, 0x03, 0xFF, 0xFC, 0x0F, 0x81, 0xFF, 0xFE, 0x0F, 0xFF, 0xFE, 0x0F, 0xFF, 
	0xF0, 0x3F, 0xFF, 0xC0, 0xFE, 0x00, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 
	0x1F, 0x00, 0x0F, 0x80, 0x00, 0x3E, 0x00, 0x00, 0xFF, 0x00, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 
	0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0x80, 0x00, 0x3E, 0x00, 0x00, 0xFF, 0x80, 0xF8, 0x00, 
	0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0x80, 0x00, 0x3E, 0x00, 0x00, 
	0xFF, 0xC0, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0x80, 
	0x00, 0x3E, 0x00, 0x00, 0xFF, 0xE0, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 
	0x1F, 0x00, 0x0F, 0x80, 0x00, 0x3E, 0x00, 0x00, 0xFF, 0xF0, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 
	0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0xFF, 0xC0, 0x3F, 0xFF, 0x00, 0xFF, 0xF8, 0xF8, 0x00, 
	0x03, 0xFF, 0xF0, 0x0F, 0x81, 0xFF, 0xF8, 0x00, 0x1F, 0x00, 0x0F, 0xFF, 0xC0, 0x3F, 0xFF, 0x00, 
	0xFB, 0xFC, 0xF8, 0x00, 0x03, 0xFF, 0xF0, 0x0F, 0x81, 0xFF, 0xF8, 0x00, 0x1F, 0x00, 0x0F, 0xFF, 
	0xC0, 0x3F, 0xFF, 0x00, 0xF9, 0xFE, 0xF8, 0x00, 0x03, 0xFF, 0xF0, 0x0F, 0x81, 0xFF, 0xF8, 0x00, 
	0x1F, 0x00, 0x0F, 0xFF, 0xC0, 0x3F, 0xFF, 0x00, 0xF8, 0xFF, 0xF8, 0x00, 0x03, 0xFF, 0xF0, 0x0F, 
	0x81, 0xFF, 0xF8, 0x00, 0x1F, 0x00, 0x0F, 0x80, 0x00, 0x3E, 0x00, 0x00, 0xF8, 0x7F, 0xF8, 0x00, 
	0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0x80, 0x00, 0x3E, 0x00, 0x00, 
	0xF8, 0x3F, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0x80, 
	0x00, 0x3E, 0x00, 0x00, 0xF8, 0x1F, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 
	0x1F, 0x00, 0x0F, 0x80, 0x00, 0x3E, 0x00, 0x00, 0xF8, 0x0F, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 
	0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0x80, 0x00, 0x3E, 0x00, 0x00, 0xF8, 0x07, 0xF8, 0x00, 
	0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0xFF, 0xF0, 0x3F, 0xFF, 0xC0, 
	0xF8, 0x03, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0xFF, 
	0xF0, 0x3F, 0xFF, 0xC0, 0xF8, 0x01, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 0x81, 0xF0, 0x00, 0x00, 
	0x1F, 0x00, 0x0F, 0xFF, 0xF0, 0x3F, 0xFF, 0xC0, 0xF8, 0x00, 0xF8, 0x00, 0x03, 0xE0, 0x00, 0x0F, 
	0x81, 0xF0, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0xFF, 0xF0, 0x3F, 0xFF, 0xC0, 0xF8, 0x00, 0x78, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0E, 0x3F, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFC, 0x38, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFC, 
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0xF0, 0xFF, 0x8F, 0xF0, 0x0F, 
	0xE1, 0xFC, 0x03, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0xEE, 
	0xFF, 0x8F, 0xF7, 0xF7, 0xE1, 0xFD, 0xFD, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0E, 0x3F, 0xDE, 0xFF, 0x8F, 0xCF, 0xF7, 0xE1, 0xFD, 0xFE, 0xFC, 0x38, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0xBE, 0xFF, 0x8F, 0xDC, 0x0F, 0xE1, 0xFC, 0x1E, 0xFC, 
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0xBE, 0xFF, 0x8F, 0xBC, 0x0F, 
	0xE1, 0xFF, 0x1E, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0x8E, 
	0xFF, 0x8F, 0xBF, 0xEF, 0xE1, 0xFF, 0x7C, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0E, 0x3F, 0xEE, 0xFF, 0x8F, 0xBF, 0xF3, 0xE1, 0xFF, 0x7C, 0xFC, 0x38, 0x00, 0x00, 0x00, 
	0x0C, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0xEE, 0xFF, 0x8F, 0xBC, 0x7B, 0xE1, 0xFF, 0x0E, 0xFC, 
	0x38, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0xEE, 0xFF, 0x8F, 0xBB, 0x3B, 
	0xE1, 0xFF, 0xEE, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x3F, 0x83, 0x80, 0x00, 0x00, 0x0E, 0x3F, 0x8E, 
	0x3F, 0x8F, 0xBC, 0x7B, 0xE1, 0xFC, 0x0E, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x1F, 0xC3, 0xC0, 0x00, 
	0x00, 0x0E, 0x3F, 0xBF, 0xBF, 0x8F, 0xDF, 0xFB, 0xE1, 0xFD, 0xFE, 0xFC, 0x38, 0x00, 0x00, 0x00, 
	0x0F, 0xF3, 0xC0, 0x00, 0x00, 0x0E, 0x3F, 0xBF, 0xBF, 0x8F, 0xCF, 0xF3, 0xE1, 0xFD, 0xFC, 0xFC, 
	0x38, 0x00, 0x00, 0x00, 0x03, 0xF1, 0xE0, 0x00, 0x00, 0x0E, 0x3F, 0x80, 0x3F, 0x8F, 0xF0, 0x0F, 
	0xE1, 0xFC, 0x03, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF0, 0x00, 0x00, 0x0E, 0x3F, 0xFF, 
	0xFF, 0x8F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFC, 0x38, 0x01, 0xFF, 0xFC, 0x00, 0x38, 0xF0, 0x00, 
	0x00, 0x0E, 0x3F, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFC, 0x38, 0x1F, 0xFF, 0xFC, 
	0xF0, 0x18, 0xF0, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x38, 0x3F, 0xFF, 0xFC, 0xFE, 0x0C, 0x70, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0xFF, 0xFF, 0xFC, 0xFF, 0x0C, 0x70, 0x00, 0x00, 0x0E, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xFF, 0xFF, 0xFC, 0x3F, 0x04, 0x70, 0x00, 
	0x00, 0x0E, 0x3F, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFC, 0x23, 0xFF, 0xFF, 0xFC, 
	0x0F, 0x84, 0x70, 0x00, 0x00, 0x0E, 0x3F, 0x80, 0x7F, 0x8F, 0xF0, 0x0F, 0xE1, 0xFF, 0x3F, 0xFC, 
	0x07, 0xFF, 0xFF, 0xFF, 0x03, 0xC6, 0xF0, 0x00, 0x00, 0x0E, 0x3F, 0x7F, 0xBF, 0x8F, 0xCF, 0xF3, 
	0xE1, 0xFC, 0xDF, 0xFC, 0x0F, 0x81, 0xFF, 0xFF, 0xC1, 0xE7, 0xF0, 0x00, 0x00, 0x0E, 0x3F, 0x7F, 
	0xBF, 0x8F, 0xDF, 0xFB, 0xE1, 0xFD, 0xDF, 0xFC, 0x1F, 0x00, 0xFF, 0xFF, 0xF0, 0xFF, 0xF0, 0x00, 
	0x00, 0x0E, 0x3F, 0x70, 0x7F, 0x8F, 0xDC, 0x3B, 0xE1, 0xFD, 0xBF, 0xFC, 0x3C, 0x00, 0x3F, 0x80, 
	0x18, 0xFF, 0xF0, 0x00, 0x00, 0x0E, 0x3F, 0x77, 0xFF, 0x8F, 0xDD, 0xBB, 0xE1, 0xFB, 0xAF, 0xFC, 
	0x3C, 0x00, 0x32, 0x00, 0x18, 0xFF, 0xF8, 0x00, 0x00, 0x0E, 0x3F, 0x70, 0xFF, 0x8F, 0xEC, 0x37, 
	0xE1, 0xF3, 0x57, 0xFC, 0x7C, 0xFC, 0x32, 0x00, 0x0C, 0x7F, 0xF8, 0x00, 0x00, 0x0E, 0x3F, 0x7F, 
	0x7F, 0x8F, 0xF7, 0xEF, 0xE1, 0xF7, 0x37, 0xF0, 0xFF, 0xFF, 0xF2, 0x3F, 0x84, 0x7F, 0xF8, 0x00, 
	0x00, 0x0E, 0x3F, 0x7F, 0xBF, 0x8F, 0xCF, 0xF3, 0xE1, 0xF7, 0x30, 0xF0, 0xFF, 0x07, 0xF7, 0xFF, 
	0xC4, 0x7F, 0xF8, 0x00, 0x00, 0x0E, 0x3F, 0x07, 0xBF, 0x8F, 0xDC, 0x3B, 0xE1, 0xF7, 0xFE, 0xF1, 
	0xFE, 0x01, 0xFF, 0x80, 0xFC, 0x3F, 0xF8, 0x00, 0x00, 0x0E, 0x3F, 0xF3, 0xBF, 0x8F, 0xBD, 0xBD, 
	0xE1, 0xF7, 0xFE, 0xF1, 0xF8, 0x00, 0xFE, 0x00, 0x7C, 0x3F, 0xF8, 0x00, 0x00, 0x0E, 0x3F, 0x87, 
	0xBF, 0x8F, 0xBC, 0x3D, 0xE1, 0xF0, 0x70, 0xE3, 0xF0, 0xFC, 0x7C, 0x00, 0x3C, 0x3F, 0xF8, 0x00, 
	0x00, 0x0E, 0x3F, 0x7F, 0xBF, 0x8F, 0xDF, 0xFB, 0xE1, 0xFF, 0x77, 0xE3, 0xF1, 0xFE, 0x38, 0xFE, 
	0x1F, 0x3F, 0xFC, 0x00, 0x00, 0x0E, 0x3F, 0x7F, 0x3F, 0x8F, 0xCF, 0xF3, 0xE1, 0xFF, 0x77, 0xE7, 
	0xE3, 0xFF, 0x11, 0xFF, 0x0F, 0x1F, 0xFC, 0x00, 0x00, 0x0E, 0x3F, 0x80, 0xFF, 0x8F, 0xF0, 0x0F, 
	0xE1, 0xFF, 0x8F, 0xE7, 0xE3, 0xFF, 0x93, 0xFF, 0x87, 0x0F, 0xFC, 0x00, 0x00, 0x0E, 0x3F, 0xFF, 
	0xFF, 0x8F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xE7, 0xC7, 0x8F, 0x83, 0xFF, 0xC7, 0x8F, 0xFE, 0x00, 
	0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xC7, 0x07, 0x87, 0x1F, 
	0xC7, 0x87, 0xFE, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0xC6, 0x03, 0x86, 0x07, 0xE7, 0xC1, 0xFF, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0xC6, 0x03, 0x86, 0x07, 0xE7, 0xE0, 0xFF, 0x00, 0x00, 0x0E, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xC6, 0x03, 0x86, 0x07, 0xE7, 0xF8, 0x3F, 0x00, 
	0x00, 0x0E, 0x3F, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xE7, 0xC6, 0x07, 0x86, 0x07, 
	0xE7, 0xF8, 0x1F, 0x00, 0x00, 0x0E, 0x3F, 0x3F, 0x9F, 0x8F, 0xC7, 0xF1, 0xE1, 0xE3, 0xC0, 0xE7, 
	0xE3, 0x8F, 0x87, 0x0F, 0xC7, 0xFE, 0x0F, 0x80, 0x00, 0x0E, 0x3C, 0xDE, 0x6F, 0x8F, 0x3B, 0xCE, 
	0xE1, 0xDD, 0xBF, 0x27, 0xF3, 0xFF, 0x03, 0xFF, 0xC7, 0xFF, 0x07, 0x80, 0x00, 0x0E, 0x3D, 0xDE, 
	0xEF, 0x8F, 0x7B, 0xDE, 0xE1, 0xBD, 0xBF, 0xA7, 0xF1, 0xFE, 0x31, 0xFF, 0x8F, 0xFF, 0x87, 0x80, 
	0x00, 0x0E, 0x3B, 0xDD, 0xEF, 0x8C, 0xFB, 0x3E, 0xE1, 0x7D, 0xC3, 0xA7, 0xF0, 0x00, 0x78, 0xFF, 
	0x1F, 0xFF, 0x87, 0x80, 0x00, 0x0E, 0x3B, 0xDD, 0xEF, 0x8D, 0xFB, 0x7E, 0xE1, 0x7D, 0xF3, 0xA7, 
	0xF8, 0x00, 0xFC, 0x7C, 0x3F, 0xFF, 0x87, 0xC0, 0x00, 0x0E, 0x3C, 0xDE, 0x6F, 0x8E, 0x3B, 0x8E, 
	0xE1, 0x9D, 0xEF, 0x67, 0xFF, 0xFF, 0xFC, 0x00, 0x7F, 0xFF, 0x83, 0xC0, 0x00, 0x0E, 0x3E, 0xDF, 
	0x6F, 0x8F, 0xBB, 0xEE, 0xE1, 0xDD, 0xEF, 0x63, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x83, 0xE0, 
	0x00, 0x0E, 0x3E, 0xDF, 0x6F, 0x8F, 0xBB, 0xEE, 0xE1, 0xDD, 0xF3, 0xA3, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x83, 0xE0, 0x00, 0x0E, 0x3E, 0xDF, 0x6F, 0x8F, 0xBB, 0xEE, 0xE1, 0xDD, 0xFB, 0xA3, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x83, 0xE0, 0x00, 0x0E, 0x38, 0xC4, 0x63, 0x8C, 0x38, 0x0E, 
	0x21, 0x1C, 0x43, 0xB1, 0xFF, 0xF8, 0x00, 0x07, 0xFF, 0xFF, 0x83, 0xE0, 0x00, 0x0E, 0x3B, 0xF5, 
	0xFB, 0x8D, 0xFE, 0x7F, 0xA1, 0x7F, 0x3F, 0xB1, 0xFF, 0xF0, 0x00, 0x01, 0xFF, 0xFF, 0x01, 0xF0, 
	0x00, 0x0E, 0x3B, 0xF5, 0xFB, 0x8D, 0xFE, 0x7F, 0xA1, 0x7F, 0x3F, 0x71, 0xFF, 0xC0, 0x00, 0x00, 
	0xFF, 0xFE, 0x00, 0xF0, 0x00, 0x0E, 0x38, 0x04, 0x03, 0x8C, 0x00, 0x00, 0x21, 0x00, 0x40, 0xF0, 
	0xFF, 0x80, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0xF0, 0x00, 0x0E, 0x3F, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 
	0xE1, 0xFF, 0xFF, 0xFC, 0x7F, 0x00, 0x00, 0x00, 0x3F, 0xFE, 0x00, 0xF0, 0x00, 0x0E, 0x3F, 0xFF, 
	0xFF, 0x8F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x1F, 0xFC, 0x01, 0xF0, 
	0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x07, 0x00, 
	0x0F, 0xF8, 0x01, 0xF0, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x1F, 0x00, 0x0F, 0xC0, 0x0F, 0xF8, 0x01, 0xF0, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0xF0, 0x0F, 0xF0, 0x03, 0xF0, 0x00, 0x0E, 0x3F, 0xFF, 
	0xFF, 0x0F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFC, 0x07, 0x80, 0x00, 0xFC, 0x0F, 0xE0, 0xCF, 0xF0, 
	0x00, 0x0E, 0x3F, 0x3F, 0x0F, 0x0F, 0x8F, 0x00, 0xE1, 0xFF, 0x03, 0xFC, 0x23, 0xC0, 0x00, 0x3E, 
	0x0F, 0xC1, 0xFF, 0xF0, 0x00, 0x0E, 0x3E, 0xDE, 0xF7, 0x0F, 0x36, 0xFF, 0x61, 0xFE, 0xFB, 0xFC, 
	0x21, 0xF0, 0x7C, 0x00, 0x0F, 0x83, 0xFF, 0xC0, 0x00, 0x0E, 0x3D, 0xDD, 0xFB, 0x0C, 0xF6, 0xFF, 
	0x61, 0xFD, 0xFC, 0xFC, 0x30, 0xFF, 0xFF, 0x00, 0x1E, 0x07, 0xFF, 0xC0, 0x00, 0x0E, 0x3B, 0xDB, 
	0x9D, 0x0D, 0xF6, 0xC0, 0xE1, 0xFB, 0x8E, 0xFC, 0x38, 0x7F, 0xFF, 0xE0, 0x3E, 0x00, 0xFF, 0x00, 
	0x00, 0x0E, 0x3B, 0xDB, 0x4D, 0x0D, 0xF6, 0xDF, 0xE1, 0xFB, 0x6E, 0xFC, 0x38, 0x1F, 0xFF, 0xF8, 
	0xF8, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3C, 0xDC, 0xDD, 0x0C, 0x76, 0xC1, 0xE1, 0xFB, 0x6E, 0xFC, 
	0x38, 0x03, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3E, 0xDF, 0x3B, 0x0F, 0x76, 0xFE, 
	0xE1, 0xFB, 0x8E, 0xFC, 0x38, 0x00, 0x3F, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3E, 0xDF, 
	0x73, 0x0F, 0x76, 0xFF, 0x21, 0xFD, 0xFE, 0xFC, 0x38, 0x00, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0E, 0x3E, 0xDC, 0xEF, 0x0F, 0x77, 0x07, 0xA1, 0xFE, 0xFE, 0xFC, 0x38, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3E, 0xDD, 0xCF, 0x0F, 0x77, 0xF3, 0xA1, 0xFF, 0x0E, 0xFC, 
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x30, 0xCB, 0x83, 0x0C, 0x70, 0x07, 
	0xA1, 0xFC, 0x0E, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x37, 0xF3, 
	0xFD, 0x0D, 0xFC, 0xFF, 0x21, 0xFD, 0xFC, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0E, 0x37, 0xF3, 0xFD, 0x0D, 0xFC, 0xFE, 0xE1, 0xFD, 0xFB, 0xFC, 0x38, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x30, 0x0C, 0x03, 0x0C, 0x00, 0x00, 0xE1, 0xFC, 0x03, 0xFC, 
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 
	0xE1, 0xFF, 0xFF, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x3F, 0xFF, 
	0xFF, 0x0F, 0xFF, 0xFF, 0xE1, 0xFF, 0xFF, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
