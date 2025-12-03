#include "../include.h"

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 8 pixels
// image height: 8 lines
const u8 ImgWakeupCat[11] = {
	0x07, 0x07, 0x20, 0x40, 0xA0, 0xE0, 0x48, 0x15, 0xBD, 0xC8, 0x80, 
};
