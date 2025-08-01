#include "../include.h"

// format: 1-bit pixel graphics
// image width: 14 pixels
// image height: 210 lines
// image pitch: 2 bytes
const u8 ImgTiles[420] = {
	0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 
	0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0x55, 0x54, 0xFF, 0xFC, 
	0x7F, 0xFC, 0xFF, 0xFC, 0x7F, 0xFC, 0xFF, 0xFC, 0x7F, 0xFC, 0xFF, 0xFC, 0x7F, 0xFC, 0xFF, 0xFC, 
	0x7F, 0xFD, 0xFF, 0xFD, 0x7F, 0xFD, 0xFF, 0xFD, 0x55, 0x55, 0xFF, 0xFD, 0x7F, 0xFD, 0xFF, 0xFD, 
	0x7F, 0xFD, 0xFF, 0xFD, 0x7C, 0xFD, 0xFC, 0xFD, 0x7F, 0xFD, 0xFF, 0xFD, 0x7F, 0xFD, 0xFF, 0xFD, 
	0x7F, 0xFD, 0xFF, 0xFD, 0x55, 0x55, 0xFF, 0xFD, 0x78, 0x7D, 0xF0, 0x3D, 0x70, 0x3D, 0xE0, 0x1D, 
	0x60, 0x1E, 0xE0, 0x1E, 0x60, 0x1E, 0xE0, 0x1E, 0x70, 0x3E, 0xF8, 0x7E, 0x7F, 0xFE, 0xFF, 0xFE, 
	0x55, 0x56, 0xFF, 0xFE, 0x70, 0xFE, 0xE0, 0x7E, 0x6A, 0x7E, 0xE0, 0x7E, 0x74, 0xDE, 0xF0, 0x1E, 
	0x70, 0x3E, 0xF8, 0x7E, 0x7A, 0xFE, 0xF2, 0x7E, 0x7F, 0xFE, 0xFF, 0xFE, 0x55, 0x56, 0xFF, 0xFE, 
	0x71, 0xFF, 0xE1, 0xFF, 0x45, 0xFF, 0xE1, 0xFF, 0x60, 0xCF, 0xE0, 0x0F, 0x60, 0x1F, 0xF0, 0x3F, 
	0x7A, 0xFF, 0xF2, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0x55, 0x57, 0xFF, 0xFF, 0x78, 0x7F, 0xF0, 0x3F, 
	0x74, 0xBF, 0xE0, 0x1F, 0x63, 0x1F, 0xE8, 0x5F, 0x68, 0x5F, 0xE7, 0x9F, 0x70, 0x3F, 0xF8, 0x7F, 
	0x7F, 0xFC, 0xFF, 0xFC, 0x55, 0x54, 0xFF, 0xFC, 0x71, 0xFC, 0xC1, 0x9C, 0x65, 0x1C, 0xC1, 0x3C, 
	0x60, 0xCC, 0xE0, 0x0C, 0x60, 0x1C, 0xF0, 0x3C, 0x7A, 0xFC, 0xF2, 0x7C, 0x7F, 0xFC, 0xFF, 0xFC, 
	0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0, 0x3F, 0xF0, 0x3F, 0xF0, 0x3F, 0xF0, 0x3F, 0xF0, 0x3F, 0xF0, 
	0x3F, 0xF1, 0x3F, 0xF1, 0x3F, 0xF1, 0x3F, 0xF1, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 
	0x3F, 0xF1, 0x3F, 0xF1, 0x3F, 0xF1, 0x3F, 0xF1, 0x3C, 0xF1, 0x3C, 0xF1, 0x3F, 0xF1, 0x3F, 0xF1, 
	0x3F, 0xF1, 0x3F, 0xF1, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x38, 0x71, 0x30, 0x31, 
	0x30, 0x32, 0x20, 0x12, 0x20, 0x12, 0x20, 0x12, 0x20, 0x12, 0x20, 0x12, 0x30, 0x32, 0x38, 0x72, 
	0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x30, 0xF2, 0x20, 0x72, 0x2A, 0x72, 0x20, 0x72, 
	0x34, 0xD2, 0x30, 0x12, 0x30, 0x32, 0x38, 0x72, 0x3A, 0xF2, 0x32, 0x72, 0x00, 0x02, 0x00, 0x02, 
	0x00, 0x03, 0x00, 0x03, 0x31, 0xF3, 0x21, 0xF3, 0x05, 0xF3, 0x21, 0xF3, 0x20, 0xC3, 0x20, 0x03, 
	0x20, 0x13, 0x30, 0x33, 0x3A, 0xF3, 0x32, 0x73, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 
	0x38, 0x73, 0x30, 0x33, 0x34, 0xB3, 0x20, 0x13, 0x23, 0x13, 0x28, 0x53, 0x28, 0x53, 0x27, 0x93, 
	0x30, 0x30, 0x38, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0xF0, 0x01, 0x90, 
	0x25, 0x10, 0x01, 0x30, 0x20, 0xC0, 0x20, 0x00, 0x20, 0x10, 0x30, 0x30, 0x3A, 0xF0, 0x32, 0x70, 
	0x00, 0x00, 0x00, 0x00, 
};
