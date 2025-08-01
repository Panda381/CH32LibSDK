#include "../include.h"

// format: 1-bit pixel graphics
// image width: 6 pixels
// image height: 48 lines
// image pitch: 1 bytes
const u8 ImgTiles[48] = {
	0xFC, 0xFE, 0xFC, 0xFC, 0xFC, 0xFC, 0x04, 0x06, 0xFC, 0x20, 0x20, 0xFC, 0xFC, 0xFC, 0xDC, 0xFC, 
	0xFC, 0xFC, 0xFC, 0xCC, 0x84, 0x84, 0xCC, 0xFC, 0x00, 0x70, 0x68, 0x5B, 0x38, 0x00, 0x00, 0x40, 
	0x00, 0x00, 0x08, 0x00, 0xCC, 0xCC, 0x84, 0x49, 0xCC, 0xB4, 0x30, 0x30, 0x78, 0xB4, 0x33, 0x48, 
};
