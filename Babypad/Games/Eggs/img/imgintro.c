#include "../include.h"

// format: 1-bit pixel graphics
// image width: 160 pixels
// image height: 120 lines
// image pitch: 20 bytes
const u8 ImgIntro[2400] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAF, 0xFE, 0xAA, 0xAA, 0xAF, 0xFF, 0xF5, 0x55, 0x55, 0x7F, 0xFF, 
	0xAA, 0xAA, 0xFF, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 0x55, 0x57, 0xFD, 0x55, 0x55, 0x57, 0xFF, 0xEA, 
	0xAA, 0xAA, 0xBF, 0xFD, 0x55, 0x55, 0x5F, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAD, 0xFA, 0xAA, 
	0xAA, 0xAB, 0xFF, 0xD5, 0x55, 0x55, 0x5F, 0xFA, 0xAA, 0xAA, 0xAF, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 
	0x55, 0x55, 0xF5, 0x55, 0x55, 0x55, 0xFF, 0xAA, 0xAA, 0xAA, 0xAF, 0xF5, 0x55, 0x55, 0x57, 0xFF, 
	0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAD, 0xEA, 0xAA, 0xAA, 0xAA, 0xFF, 0x55, 0x55, 0x55, 0x57, 0xFA, 
	0xAA, 0xAA, 0xAF, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 0x55, 0x55, 0xD5, 0x55, 0x55, 0x55, 0x7E, 0xAA, 
	0xAA, 0xAA, 0xAB, 0xF5, 0x55, 0x55, 0x57, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAD, 0xEA, 0xAA, 
	0xAA, 0xAA, 0xFF, 0x55, 0x55, 0x55, 0x57, 0xEA, 0xAA, 0xAA, 0xAB, 0xFF, 0xFF, 0xFF, 0xD5, 0x5F, 
	0xFF, 0xFD, 0xD5, 0x57, 0xFD, 0x55, 0x5E, 0xAA, 0xBF, 0xEA, 0xAA, 0xF5, 0x57, 0xF5, 0x56, 0xFF, 
	0xFF, 0xFF, 0xAA, 0xB0, 0x00, 0x01, 0xEA, 0xAC, 0x02, 0xAA, 0xDF, 0x55, 0x60, 0x15, 0x56, 0xEA, 
	0xAE, 0x1A, 0xAA, 0xFF, 0xFF, 0xFF, 0xD5, 0x57, 0xFF, 0xFF, 0xD5, 0x59, 0xFF, 0x55, 0x5E, 0xAA, 
	0xCF, 0xFA, 0xAA, 0xF5, 0x54, 0xF5, 0x56, 0xFF, 0xFF, 0xFF, 0xAA, 0xB7, 0xFF, 0xFF, 0xEA, 0xAB, 
	0xFE, 0xAA, 0xDF, 0x55, 0x5F, 0xF5, 0x56, 0xEA, 0xAD, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xD5, 0x57, 
	0xFF, 0xFF, 0xD5, 0x5B, 0xFF, 0xFF, 0xDE, 0xAA, 0xDF, 0xFF, 0xFE, 0xF5, 0x55, 0xFC, 0x00, 0xFF, 
	0xFF, 0xFF, 0xAA, 0xB7, 0xFF, 0xFF, 0xEA, 0xAB, 0xFF, 0x80, 0x1F, 0x55, 0x5F, 0xFC, 0x00, 0xEA, 
	0xAD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD5, 0x57, 0xFF, 0xFF, 0xD5, 0x5B, 0xFF, 0xFF, 0xFE, 0xAA, 
	0xDF, 0xFF, 0xFF, 0xF5, 0x57, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xAB, 0xFF, 0xEA, 0xAB, 
	0xFF, 0xFF, 0xFF, 0x55, 0x5F, 0xFF, 0xFF, 0xEA, 0xAA, 0xAA, 0xFF, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 
	0x55, 0xFF, 0xD5, 0x5B, 0xFF, 0xFF, 0xFE, 0xAA, 0xDF, 0xFF, 0xFF, 0xF5, 0x55, 0x55, 0x5F, 0xFF, 
	0xFF, 0xFF, 0xAA, 0xAA, 0xAB, 0x7F, 0xEA, 0xAB, 0xEA, 0xAA, 0xFF, 0x55, 0x5F, 0x55, 0x57, 0xFA, 
	0xAA, 0xAA, 0xAF, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 0x55, 0x7F, 0xD5, 0x5B, 0xD5, 0x55, 0x7E, 0xAA, 
	0xDE, 0xAA, 0xAB, 0xFD, 0x55, 0x55, 0x57, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xAB, 0x7F, 0xEA, 0xAB, 
	0xEA, 0xAA, 0xDF, 0x55, 0x5F, 0x55, 0x56, 0xFE, 0xAA, 0xAA, 0xAF, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 
	0x55, 0x7F, 0xD5, 0x5B, 0xD5, 0x55, 0x5E, 0xAA, 0xDE, 0xAA, 0xAA, 0xFF, 0x55, 0x55, 0x57, 0xFF, 
	0xFF, 0xFF, 0xAA, 0xBF, 0xFF, 0x7F, 0xEA, 0xAB, 0xEA, 0xAA, 0xDF, 0x55, 0x5F, 0x55, 0x56, 0xFF, 
	0xFF, 0xEA, 0xAB, 0xFF, 0xFF, 0xFF, 0xD5, 0x50, 0x00, 0x7F, 0xD5, 0x5B, 0xD5, 0x55, 0x5E, 0xAA, 
	0xDE, 0xAA, 0xAA, 0xFF, 0xFF, 0xF5, 0x56, 0xFF, 0xFF, 0xFF, 0xAA, 0xB7, 0xFF, 0xFF, 0xEA, 0xAB, 
	0xEA, 0xAA, 0xDF, 0x55, 0x5F, 0x55, 0x56, 0xFF, 0xFF, 0xFA, 0xAA, 0xFF, 0xFF, 0xFF, 0xD5, 0x57, 
	0xFF, 0xFF, 0xD5, 0x5B, 0xFF, 0x55, 0x5E, 0xAA, 0xDF, 0xFA, 0xAA, 0xFF, 0xFF, 0xF5, 0x56, 0xFF, 
	0xFF, 0xFF, 0xAA, 0xB7, 0xFF, 0xFF, 0xEA, 0xAB, 0xFE, 0xAA, 0xDF, 0x55, 0x5F, 0xF5, 0x56, 0xEA, 
	0xAF, 0xFA, 0xAA, 0xFF, 0xFF, 0xFF, 0xD5, 0x57, 0xFF, 0xFF, 0xD5, 0x5B, 0xFF, 0x55, 0x5E, 0xAA, 
	0xDF, 0xFA, 0xAA, 0xF5, 0x57, 0xF5, 0x56, 0xFF, 0xFF, 0xFF, 0xAA, 0xBF, 0xFF, 0xFF, 0xEA, 0xAF, 
	0xFE, 0xAA, 0xDF, 0x55, 0x7F, 0xF5, 0x56, 0xEA, 0xAB, 0xEA, 0xAA, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 
	0x55, 0x57, 0xD5, 0x55, 0x55, 0x55, 0x5E, 0xAA, 0xAA, 0xAA, 0xAA, 0xF5, 0x55, 0x55, 0x56, 0xFF, 
	0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAF, 0xEA, 0xAA, 0xAA, 0xAA, 0xDF, 0x55, 0x55, 0x55, 0x56, 0xEA, 
	0xAA, 0xAA, 0xAA, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 0x55, 0x55, 0xF5, 0x55, 0x55, 0x55, 0xDF, 0xAA, 
	0xAA, 0xAA, 0xAE, 0xF5, 0x55, 0x55, 0x56, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAD, 0xEA, 0xAA, 
	0xAA, 0xAA, 0xDF, 0x55, 0x55, 0x55, 0x56, 0xFA, 0xAA, 0xAA, 0xAE, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 
	0x55, 0x55, 0xF5, 0x55, 0x55, 0x55, 0xBF, 0xAA, 0xAA, 0xAA, 0xAD, 0xFD, 0x55, 0x55, 0x5D, 0xFF, 
	0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAD, 0xFA, 0xAA, 0xAA, 0xAB, 0xBF, 0xD5, 0x55, 0x55, 0x5D, 0xFE, 
	0xAA, 0xAA, 0xBD, 0xFF, 0xFF, 0xFF, 0xD5, 0x55, 0x55, 0x55, 0xFF, 0x55, 0x55, 0x5F, 0x7F, 0xFA, 
	0xAA, 0xAA, 0xFB, 0xFF, 0x55, 0x55, 0x7B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFE, 0xFF, 
	0xFF, 0xFC, 0xFF, 0xF7, 0xFF, 0xFF, 0xE7, 0xFF, 0x3F, 0xFF, 0xE7, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 
	0x00, 0x01, 0xFF, 0x80, 0x00, 0x03, 0xFF, 0xFC, 0x00, 0x00, 0x1F, 0xFF, 0xC0, 0x00, 0x1F, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEA, 0xBF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFD, 0x55, 0x5F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xAA, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x55, 0x5F, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEA, 0xAA, 0xAF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xF5, 0x55, 0x5F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEA, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0x60, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEA, 0xE0, 0x0F, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xF5, 0x80, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x71, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFC, 0x00, 0x71, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x70, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x57, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFE, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 
	0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 
	0xFF, 0xFC, 0x00, 0x00, 0x5F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFC, 0x1F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xF8, 0x00, 0x06, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8, 0x0F, 0xFF, 
	0xFF, 0xF8, 0x00, 0x0D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 
	0xFF, 0xF0, 0x07, 0xFF, 0xFF, 0xF0, 0x00, 0x0A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 
	0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xE0, 0x01, 0xFF, 0xFF, 0xE0, 0x00, 0x05, 0x7F, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0xFF, 0xFF, 0xC0, 0x00, 0x0A, 
	0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x3F, 
	0xFF, 0x00, 0x00, 0x05, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x07, 0xFF, 0xFF, 
	0xFF, 0xC0, 0x00, 0x0F, 0xFE, 0x00, 0x00, 0x0E, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x18, 
	0x60, 0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x0F, 0x7F, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xE0, 0x3C, 0xF0, 0x03, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x7C, 0xF8, 0x03, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x38, 0x70, 0x03, 0xFF, 0xFF, 
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x11, 
	0x20, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xE0, 0x02, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x30, 0x00, 0x00, 0x01, 0x00, 0x0F, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x05, 0x40, 0x03, 0xFF, 0xFF, 0xFF, 0x80, 0x18, 0x00, 
	0x00, 0x03, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x0A, 0x80, 0x07, 0xFF, 0xFF, 
	0xFF, 0x80, 0x1C, 0x00, 0x00, 0x07, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x1F, 0xFF, 0xFF, 0xF0, 0x05, 
	0x40, 0x0F, 0xFF, 0xFF, 0xFF, 0x80, 0x1E, 0x00, 0x00, 0x07, 0x00, 0x0F, 0xFF, 0xFF, 0x00, 0x00, 
	0x7F, 0xFF, 0xF8, 0x0A, 0x80, 0x1F, 0xFF, 0xFF, 0xFF, 0xC0, 0x0E, 0x00, 0x00, 0x0F, 0x00, 0x0F, 
	0xFF, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0xF8, 0x01, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xC0, 0x07, 0x00, 
	0x00, 0x0E, 0x00, 0x0F, 0xFF, 0xF8, 0x00, 0x00, 0x0F, 0xFF, 0xFC, 0x02, 0x00, 0x03, 0xFF, 0xFF, 
	0xFF, 0xC0, 0x07, 0x80, 0x00, 0x1E, 0x00, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 0x07, 0xFF, 0xFC, 0x00, 
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xE0, 0x03, 0xC0, 0x00, 0x3C, 0x00, 0x7F, 0xFF, 0xE0, 0x00, 0x00, 
	0x07, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xE0, 0x01, 0xE0, 0x00, 0x38, 0x00, 0x7F, 
	0xFF, 0xC0, 0x0A, 0xA8, 0x01, 0xFF, 0xFE, 0x00, 0x02, 0x00, 0x1F, 0xFF, 0xFF, 0xF0, 0x01, 0xF0, 
	0x00, 0xF8, 0x00, 0x7F, 0xFF, 0x80, 0x05, 0x54, 0x00, 0xFF, 0xFC, 0x00, 0x07, 0x00, 0x07, 0xFF, 
	0xFF, 0xF8, 0x00, 0x7C, 0x03, 0xE0, 0x00, 0x7F, 0xFF, 0x00, 0x20, 0xAA, 0x00, 0xFF, 0xFC, 0x00, 
	0x07, 0x01, 0x87, 0xFF, 0xFF, 0xF8, 0x00, 0x3F, 0x07, 0xC0, 0x00, 0x7F, 0xFC, 0x00, 0x10, 0x55, 
	0x00, 0x1F, 0xFC, 0x00, 0x06, 0x01, 0x8F, 0xFF, 0xFF, 0xF8, 0x00, 0x0F, 0xFF, 0x00, 0x01, 0xFF, 
	0xF8, 0x00, 0xA0, 0xAA, 0x80, 0x1F, 0xFC, 0x00, 0x03, 0x03, 0x9F, 0xFF, 0xFF, 0xFC, 0x00, 0x03, 
	0xFE, 0x00, 0x03, 0xFF, 0xE0, 0x00, 0x50, 0x55, 0x40, 0x0F, 0xFC, 0x00, 0x01, 0x83, 0x1F, 0xFF, 
	0xFF, 0xFC, 0x00, 0x00, 0xF8, 0x00, 0x03, 0xFF, 0xC0, 0x03, 0xAA, 0xAA, 0xB0, 0x07, 0xFE, 0x00, 
	0x01, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0x00, 0x07, 0x55, 0x55, 
	0x78, 0x07, 0xFE, 0x00, 0x00, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x1F, 0xFE, 
	0x00, 0x07, 0xAA, 0xAA, 0xF8, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 
	0x00, 0x00, 0x7F, 0xFC, 0x00, 0x07, 0xD5, 0x55, 0x78, 0x03, 0xFF, 0x80, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x03, 0xAA, 0xAA, 0xF0, 0x03, 0xFF, 0xC0, 
	0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x03, 0xD5, 0x55, 
	0xE0, 0x03, 0xFF, 0xC0, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x03, 0xFF, 0xF0, 
	0x00, 0x01, 0xEA, 0xAB, 0xE0, 0x03, 0xFF, 0xF0, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 
	0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0xF5, 0x55, 0xC0, 0x07, 0xFF, 0xF8, 0x00, 0x0F, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFE, 0x00, 0x03, 0xE7, 0xFF, 0xF0, 0x00, 0x00, 0x7A, 0xAF, 0xC0, 0x0F, 0xFF, 0xFF, 
	0xBD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x06, 0xBF, 0xFF, 0xF8, 0x00, 0x00, 0x7F, 0xFF, 
	0x00, 0x0F, 0xFF, 0xFF, 0xBD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF1, 0xF7, 0x7F, 0xFF, 0xFC, 
	0x00, 0x00, 0x3F, 0xFE, 0x00, 0x1F, 0xFF, 0xFE, 0x3D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 
	0x5F, 0xBF, 0xFF, 0xFC, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x3F, 0xFF, 0xF8, 0x79, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFE, 0xBF, 0x7F, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x38, 0x00, 0x7F, 0xFF, 0xFE, 
	0x20, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xBF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 
	0x00, 0xFF, 0xFF, 0xFE, 0xB9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xBD, 0x5F, 0xFF, 0xFF, 
	0xE0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xF5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x7A, 0xAB, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFE, 0xBD, 0x55, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x5F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 
	0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0xAB, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xC0, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 
	0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};
