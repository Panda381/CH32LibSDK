#include "../include.h"

// format: 1-bit pixel graphics RLE compressed
// chunk length: 3 bits
// compression: 90%
// image width: 9 pixels
// image height: 7 lines
const u8 ImgBirdAnim[10] = {
	0x08, 0x06, 0x61, 0xE3, 0x96, 0x72, 0xAE, 0x38, 0xE2, 0x00, 
};
