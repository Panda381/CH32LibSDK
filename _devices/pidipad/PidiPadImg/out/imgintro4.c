#include "../include.h"

// format: attribute graphics with cell 8x8 pixels
// image width: 160 pixels
// image height: 120 lines
// image pitch: 20 bytes
// attribute width: 20 colors
// attribute height: 15 rows
// attribute pitch: 10 bytes
const u8 ImgIntro4_Attr[150] = {
	0x9B, 0x99, 0x9B, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0xB2, 0x9B, 0x99, 0x99, 0x22, 0x22, 0x22, 
	0x22, 0x22, 0x22, 0xB2, 0x9B, 0x99, 0x99, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0xB2, 0x11, 0xA1, 
	0x1A, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xB1, 0xAA, 0x9A, 0x88, 0x88, 0x8B, 0x88, 0x88, 
	0xB8, 0x1B, 0xB1, 0xAA, 0x8A, 0x88, 0x88, 0x88, 0x88, 0x88, 0xB8, 0x1B, 0x11, 0x83, 0x38, 0x33, 
	0x33, 0x38, 0x33, 0x83, 0x38, 0x11, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 
	0x11, 0x88, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x81, 0x88, 0x88, 0x88, 0x88, 0x98, 
	0xAA, 0x88, 0x88, 0x18, 0x81, 0xB8, 0xBB, 0xBB, 0xBB, 0x98, 0xAA, 0xBA, 0x8B, 0x18, 0x81, 0xBB, 
	0xBB, 0xBB, 0xBB, 0xA8, 0xAA, 0xBA, 0xBB, 0x88, 0x81, 0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0xAA, 0xBA, 
	0xBB, 0x18, 0x81, 0x88, 0x88, 0x88, 0x88, 0x88, 0x8A, 0xAA, 0x88, 0x88, 0x11, 0x11, 0x11, 0x11, 
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 
};

const u8 ImgIntro4[2400] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xFF, 0xFF, 0x0F, 0x00, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xF0, 0x0F, 0x0F, 0x00, 0xF0, 
	0xF0, 0x1F, 0xFE, 0x00, 0x00, 0xFF, 0xFF, 0x0F, 0x00, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0xF0, 0xF0, 
	0x0F, 0x0F, 0x00, 0xF0, 0xF0, 0x7F, 0xFE, 0x00, 0x00, 0xFF, 0xFF, 0x0F, 0x00, 0xF0, 0xFF, 0xFF, 
	0x0F, 0xFF, 0xF0, 0xF8, 0x0F, 0x0F, 0x80, 0xF0, 0xF0, 0x7F, 0xFE, 0x00, 0x00, 0x03, 0xC0, 0x0F, 
	0x00, 0xF0, 0x03, 0xC0, 0x0F, 0x00, 0x00, 0xFC, 0x0F, 0x0F, 0xC0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 
	0x00, 0x03, 0xC0, 0x0F, 0x00, 0xF0, 0x03, 0xC0, 0x0F, 0x00, 0x00, 0xFE, 0x0F, 0x0F, 0xE0, 0xF0, 
	0xF0, 0xF0, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x0F, 0x00, 0xF0, 0x03, 0xC0, 0x0F, 0x00, 0x00, 0xFF, 
	0x0F, 0x0F, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x0F, 0x00, 0xF0, 0x03, 0xC0, 
	0x0F, 0xFF, 0x80, 0xFF, 0x8F, 0x0F, 0xF8, 0xF0, 0xF0, 0xFF, 0xF8, 0x00, 0x00, 0x03, 0xC0, 0x0F, 
	0x00, 0xF0, 0x03, 0xC0, 0x0F, 0xFF, 0x80, 0xFF, 0xCF, 0x0F, 0xFC, 0xF0, 0xF0, 0x7F, 0xFE, 0x00, 
	0x00, 0x03, 0xC0, 0x0F, 0x00, 0xF0, 0x03, 0xC0, 0x0F, 0xFF, 0x80, 0xF7, 0xEF, 0x0F, 0x7E, 0xF0, 
	0xF0, 0x7F, 0xFE, 0x00, 0x00, 0x03, 0xC0, 0x0F, 0x81, 0xF0, 0x03, 0xC0, 0x0F, 0xFF, 0x80, 0xF3, 
	0xFF, 0x0F, 0x3F, 0xF0, 0xF0, 0x1F, 0xFF, 0x00, 0x00, 0x03, 0xC0, 0x07, 0xC3, 0xE0, 0x03, 0xC0, 
	0x0F, 0x00, 0x00, 0xF1, 0xFF, 0x0F, 0x1F, 0xF0, 0xF0, 0x00, 0x0F, 0x00, 0x00, 0x03, 0xC0, 0x03, 
	0xE7, 0xC0, 0x03, 0xC0, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0x0F, 0x0F, 0xF0, 0xF0, 0x00, 0x0F, 0x00, 
	0x00, 0x03, 0xC0, 0x01, 0xFF, 0x80, 0x03, 0xC0, 0x0F, 0x00, 0x00, 0xF0, 0x7F, 0x0F, 0x07, 0xF0, 
	0xF0, 0x00, 0x0F, 0x00, 0x00, 0x03, 0xC0, 0x00, 0xFF, 0x00, 0x03, 0xC0, 0x0F, 0xFF, 0xF0, 0xF0, 
	0x3F, 0x0F, 0x03, 0xF0, 0xF0, 0x7F, 0xFE, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x7E, 0x00, 0x03, 0xC0, 
	0x0F, 0xFF, 0xF0, 0xF0, 0x1F, 0x0F, 0x01, 0xF0, 0xF0, 0x7F, 0xFE, 0x00, 0x00, 0x03, 0xC0, 0x00, 
	0x3C, 0x00, 0x03, 0xC0, 0x0F, 0xFF, 0xF0, 0xF0, 0x0F, 0x0F, 0x00, 0xF0, 0xF0, 0x7F, 0xF8, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0x1F, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x3F, 0xFF, 0xFF, 0x0F, 0x00, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x78, 0x00, 0x00, 0x0C, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 
	0x70, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0E, 0x60, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0xFF, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x60, 0x00, 0x07, 0x7F, 0xC0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x0E, 0x7E, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x0C, 0x7E, 0x70, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x0C, 0x7E, 
	0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x60, 0x00, 0x0C, 0xFE, 0x0C, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x80, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0xFE, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0xE7, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x06, 
	0x60, 0x00, 0x00, 0xE3, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x60, 
	0x60, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0xE1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x06, 0x60, 0x00, 0x01, 0xE0, 0xC0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x06, 0x60, 0x00, 0x03, 0xC0, 
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x06, 
	0x60, 0x00, 0x0F, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0x18, 0x00, 0x00, 0x06, 0x60, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x06, 0x60, 0x00, 0x0C, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x0C, 0x00, 0x00, 0x06, 0x60, 0x00, 0x0C, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x06, 
	0x60, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x06, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x06, 0x60, 0x03, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0xC0, 0x06, 0x60, 0x03, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x06, 
	0x60, 0x03, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
	0x00, 0xFF, 0xC0, 0x06, 0x60, 0x03, 0x0A, 0x00, 0x00, 0x50, 0xA1, 0x42, 0x85, 0x0A, 0x00, 0x28, 
	0x50, 0xA1, 0x42, 0x00, 0x00, 0x14, 0xC0, 0x06, 0x60, 0x03, 0x50, 0x00, 0x00, 0x85, 0x0A, 0x14, 
	0x28, 0x50, 0x00, 0x42, 0x85, 0x0A, 0x14, 0x00, 0x00, 0xA1, 0xC0, 0x06, 0x60, 0x03, 0x85, 0x00, 
	0x00, 0x28, 0x50, 0xA1, 0x42, 0x85, 0x00, 0x14, 0x28, 0x50, 0xA1, 0x00, 0x00, 0x0A, 0xC0, 0x06, 
	0x60, 0x03, 0x28, 0x50, 0xA1, 0x42, 0x85, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 0x85, 0x0A, 0x14, 
	0x28, 0x50, 0xC0, 0x06, 0x60, 0x03, 0x42, 0x85, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 0x85, 0x0A, 
	0x14, 0x28, 0x50, 0xA1, 0x42, 0x85, 0xC0, 0x06, 0x60, 0x03, 0x14, 0x28, 0x50, 0xA1, 0x42, 0x85, 
	0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 0x85, 0x0A, 0x14, 0x28, 0xC0, 0x06, 0x60, 0x03, 0xA1, 0x42, 
	0x85, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 0x85, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 0xC0, 0x06, 
	0x60, 0x03, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 0x85, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 0x85, 
	0x0A, 0x14, 0xC0, 0x06, 0x60, 0x03, 0x50, 0xA1, 0x42, 0x85, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 
	0x85, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0xC0, 0x06, 0x60, 0x03, 0x85, 0x0A, 0x14, 0x28, 0x50, 0xA1, 
	0x42, 0x85, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 0x85, 0x0A, 0xC0, 0x06, 0x60, 0x03, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x06, 
	0x60, 0x03, 0x60, 0x60, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xF0, 0xF0, 0xC0, 0x06, 0x60, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x80, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x60, 0x00, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x02, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x60, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x7F, 0xC0, 0x00, 0x00, 
	0x00, 0x60, 0x60, 0x06, 0x60, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x7F, 0xC0, 0x00, 0x00, 0x00, 0x20, 0x20, 0x06, 0x60, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x30, 0x30, 0x06, 0x60, 0x08, 0x08, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x10, 0x10, 0x06, 
	0x60, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x3F, 0x80, 0x00, 0x00, 
	0x00, 0x18, 0x18, 0x06, 0x60, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 
	0x1F, 0xFE, 0x00, 0x00, 0x00, 0x08, 0x08, 0x06, 0x60, 0x30, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xC0, 0x30, 0x03, 0xFF, 0x3F, 0xFF, 0xFF, 0xFC, 0x0C, 0x06, 0x60, 0x20, 0x3F, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x18, 0x03, 0xFF, 0x3F, 0xFF, 0xFF, 0xFC, 0x04, 0x06, 
	0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0C, 0x07, 0xFF, 0x80, 0x00, 
	0x00, 0x06, 0x06, 0x06, 0x60, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 
	0x07, 0xFF, 0xC0, 0x00, 0x00, 0x02, 0x02, 0x06, 0x60, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x04, 0x07, 0xFF, 0xE0, 0x00, 0x00, 0x03, 0x03, 0x06, 0x60, 0x80, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 0x0F, 0xFD, 0xF0, 0x00, 0x00, 0x01, 0x01, 0x06, 
	0x60, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 0x0F, 0xFE, 0xF8, 0x00, 
	0x00, 0x01, 0x81, 0x06, 0x60, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x98, 
	0x0F, 0xFE, 0x78, 0x00, 0x00, 0x00, 0x80, 0x06, 0x60, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0xFC, 0x1E, 0xFF, 0x38, 0x00, 0x00, 0x00, 0xC0, 0x06, 0x60, 0x02, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0C, 0x3E, 0xFF, 0x38, 0x00, 0x00, 0x00, 0x40, 0x06, 
	0x60, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x7C, 0xFF, 0x70, 0x00, 
	0x00, 0x00, 0x60, 0x60, 0x60, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0F, 
	0xF8, 0xFF, 0x70, 0x00, 0x00, 0x00, 0x20, 0x20, 0x60, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x0F, 0xE0, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60, 0x08, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0F, 0x81, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x10, 0x10, 
	0x60, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x83, 0xFF, 0xE0, 0x00, 
	0x00, 0x00, 0x18, 0x10, 0x60, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x0F, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x08, 0x00, 0x60, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x1F, 0xEF, 0xE0, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x60, 0x20, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x3F, 0xC7, 0xE0, 0x00, 0x00, 0x00, 0x04, 0x00, 
	0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x7F, 0x07, 0xE0, 0x00, 
	0x00, 0x00, 0x06, 0x06, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0xFF, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x02, 0x06, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0xFE, 0x03, 0xF0, 0x00, 0x00, 0x00, 0x03, 0x06, 0x60, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xF8, 0x03, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x06, 
	0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xF0, 0x01, 0xF8, 0x00, 
	0x00, 0x00, 0x01, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0xF0, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0xF0, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xF0, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xF0, 0x00, 0x0F, 0x80, 
	0x00, 0x00, 0x00, 0x60, 0x60, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 
	0xF0, 0xFF, 0x07, 0xC0, 0xFF, 0xFF, 0xFF, 0xE0, 0x60, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xFF, 0x03, 0xE0, 0xFF, 0xFF, 0xFF, 0xF0, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x01, 0xE0, 
	0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xF0, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x70, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 
	0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1E, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
