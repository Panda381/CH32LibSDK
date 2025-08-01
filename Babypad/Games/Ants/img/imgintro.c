#include "../include.h"

// format: pseudo graphics with cell 2x2 pixels
// text width: 18 characters
// text height: 12 rows
// text pitch: 18 bytes
// image width: 36 pixels
// image height: 24 lines
// attribute width: 18 colors
// attribute height: 12 rows
// attribute pitch: 9 bytes
const u8 ImgIntro_Attr[108] = {
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 
};

const u8 ImgIntro[216] = {
	0x80, 0x84, 0x8F, 0x88, 0x80, 0x85, 0x8A, 0x80, 0x8D, 0x82, 0x8C, 0x8C, 0x8D, 0x8B, 0x80, 0x8C, 
	0x8C, 0x8C, 0x80, 0x8B, 0x84, 0x8A, 0x80, 0x8F, 0x8F, 0x88, 0x8B, 0x81, 0x8B, 0x87, 0x8A, 0x80, 
	0x85, 0x8F, 0x88, 0x81, 0x8D, 0x8B, 0x83, 0x8E, 0x85, 0x8B, 0x81, 0x8F, 0x8A, 0x80, 0x80, 0x8F, 
	0x82, 0x84, 0x88, 0x80, 0x8F, 0x8A, 0x82, 0x80, 0x80, 0x81, 0x81, 0x82, 0x80, 0x81, 0x80, 0x80, 
	0x81, 0x82, 0x80, 0x81, 0x83, 0x83, 0x83, 0x80, 0x80, 0x84, 0x89, 0x83, 0x88, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x89, 0x80, 0x8C, 0x88, 0x80, 0x80, 0x80, 0x80, 0x8C, 0x8C, 0x85, 0x80, 
	0x84, 0x88, 0x80, 0x80, 0x8C, 0x80, 0x8A, 0x89, 0x80, 0x81, 0x80, 0x80, 0x80, 0x81, 0x80, 0x8D, 
	0x87, 0x86, 0x80, 0x81, 0x86, 0x83, 0x80, 0x84, 0x87, 0x87, 0x8E, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x85, 0x8F, 0x8D, 0x89, 0x84, 0x89, 0x82, 0x83, 0x88, 0x81, 0x8D, 0x8D, 0x8B, 0x80, 0x80, 0x80, 
	0x84, 0x8C, 0x84, 0x8F, 0x8F, 0x8C, 0x8A, 0x80, 0x80, 0x80, 0x85, 0x8C, 0x8D, 0x8F, 0x8F, 0x84, 
	0x8C, 0x80, 0x8F, 0x8F, 0x8E, 0x87, 0x83, 0x86, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x87, 
	0x86, 0x8F, 0x8F, 0x8A, 0x81, 0x87, 0x83, 0x80, 0x8A, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x8A, 0x85, 0x83, 0x83, 0x80, 0x80, 0x81, 0x88, 0x80, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x85, 0x80, 0x80, 0x83, 0x80, 0x80, 
};
