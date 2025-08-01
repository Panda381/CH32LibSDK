
// -----------------------------------------
// TweetyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#include "../include.h"

//#pragma once

//#include <Arduino.h>

// 'beholder32x56_w_mask', 64x56px (448 bytes)
const unsigned char beholder [] PROGMEM = {
	0x38, 0x44, 0x82, 0x39, 0x29, 0x39, 0x82, 0x44, 0x38, 0x00, 0x00, 0x38, 0x44, 0x82, 0x39, 0x29, 
	0x39, 0x82, 0x44, 0x38, 0x70, 0x88, 0x04, 0x72, 0x52, 0x72, 0x04, 0x88, 0x70, 0x00, 0x00, 0x00, 
	0xc7, 0x83, 0x01, 0x00, 0x00, 0x00, 0x01, 0x83, 0xc7, 0xff, 0xff, 0xc7, 0x83, 0x01, 0x00, 0x00, 
	0x00, 0x01, 0x83, 0xc7, 0x8f, 0x07, 0x03, 0x01, 0x01, 0x01, 0x03, 0x07, 0x8f, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x03, 0x04, 0x18, 0x60, 0x83, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0xc0, 0x3f, 0x00, 0x80, 
	0x7e, 0x01, 0x80, 0x60, 0x18, 0x04, 0xc3, 0x30, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xfc, 0xf8, 0xe0, 0x80, 0x00, 0x03, 0x0f, 0x3f, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 
	0x80, 0xfe, 0x7f, 0x1f, 0x07, 0x03, 0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x46, 0x48, 0x30, 0x33, 0x1c, 0x13, 0x1c, 0x10, 0x11, 
	0x1e, 0x1e, 0x11, 0x30, 0x2c, 0x23, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x38, 0x30, 0x00, 0x00, 0x03, 0x0c, 0x00, 0x00, 0x00, 
	0x01, 0x01, 0x00, 0x00, 0x10, 0x1c, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xc0, 0x30, 0x08, 0x04, 0x82, 0xe1, 0xe0, 0xe8, 0xe4, 0xd4, 0x96, 0x36, 0x73, 0xf3, 0xf3, 0xfb, 
	0x9b, 0xcb, 0xf3, 0xf2, 0xf6, 0xe4, 0xec, 0x68, 0x60, 0xe1, 0x82, 0x04, 0x08, 0x30, 0xc0, 0x00, 
	0x3f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x3f, 0xff, 
	0x45, 0x00, 0x00, 0xfe, 0xff, 0xef, 0xe7, 0xf7, 0xf3, 0xfb, 0xfb, 0xff, 0xe1, 0x40, 0xc0, 0xc0, 
	0x40, 0xe1, 0xff, 0xed, 0xed, 0xcd, 0xdc, 0x9e, 0xbf, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x45, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0x07, 0x18, 0x20, 0x40, 0x83, 0x07, 0x07, 0x2f, 0x6f, 0x47, 0xd3, 0xd9, 0xdc, 0xde, 0xdf, 0xdf, 
	0xde, 0xd8, 0xd3, 0xdf, 0xdf, 0x4f, 0x6f, 0x2f, 0x07, 0x03, 0x83, 0x40, 0x20, 0x18, 0x07, 0x00, 
	0xf8, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf8, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x08, 0x08, 0x08, 0x11, 0x11, 0x11, 0x11, 
	0x11, 0x11, 0x11, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// 'joey28x40_w_mask', 56x40px (280 bytes)
const unsigned char joey [] PROGMEM = {
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x38, 0x38, 
	0xfc, 0xfc, 0x3c, 0x38, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x03, 0x03, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0xc1, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x0f, 0x29, 0xaf, 0x29, 0x0f, 0x0f, 0x07, 0x07, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
	0x70, 0x60, 0x40, 0x00, 0x00, 0x00, 0x40, 0x60, 0x70, 0x70, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x07, 0x78, 0x80, 0x03, 0x7c, 0x80, 0x80, 0x00, 0x80, 0xf0, 0x3c, 0x07, 0x7d, 0xf5, 0x55, 
	0x03, 0xf9, 0xd9, 0x35, 0x77, 0x13, 0x76, 0x30, 0xd8, 0xf8, 0x00, 0x00, 0xff, 0xf8, 0x80, 0x00, 
	0x00, 0x03, 0x7f, 0x7f, 0x7f, 0x07, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0xff, 0x00, 0x00, 0x04, 0x0b, 0x0a, 0x08, 0x10, 0x10, 
	0x06, 0x0f, 0x01, 0x00, 0x00, 0x08, 0x5d, 0x13, 0x00, 0x0f, 0x18, 0x30, 0x66, 0x69, 0x66, 0x30, 
	0x18, 0x0f, 0x00, 0x00, 0xff, 0xff, 0xfb, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xfc, 
	0xe3, 0x22, 0x00, 0x00, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x20, 0x2d, 0x00, 
	0x00, 0x00, 0x00, 0x2d, 0x20, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x1f, 0x0f, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xc0, 0x80, 
	0x80, 0x0f, 0x1f, 0xbf, 0xff, 0xff, 0xff, 0xff
/*  
  0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x38, 0x38, 
	0xfc, 0xfc, 0x3c, 0x38, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x03, 0x03, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0xc1, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x0f, 0x29, 0xaf, 0x29, 0x0f, 0x0f, 0x07, 0x07, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
	0x70, 0x60, 0x40, 0x00, 0x00, 0x00, 0x40, 0x60, 0x70, 0x70, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x07, 0x78, 0x80, 0x03, 0x7c, 0x80, 0x80, 0x00, 0x80, 0xf0, 0x3c, 0x07, 0x7d, 0xed, 0x45, 
	0x37, 0xf5, 0x25, 0xed, 0x27, 0xe9, 0x27, 0xe0, 0x20, 0xc0, 0x00, 0x00, 0xff, 0xf8, 0x80, 0x00, 
	0x00, 0x03, 0x7f, 0x7f, 0x7f, 0x07, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x1f, 0xff, 0x00, 0x00, 0x04, 0x0b, 0x0a, 0x08, 0x10, 0x10, 
	0x06, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x5d, 0x9f, 0x40, 0x3f, 0x60, 0x7f, 0x40, 0x7f, 0x40, 0x7f, 
	0x60, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xfb, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xfc, 
	0xff, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x20, 0x2d, 0x00, 
	0x00, 0x00, 0x00, 0x2d, 0x20, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x1f, 0x0f, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xc0, 0x80, 
	0x80, 0x0f, 0x1f, 0xbf, 0xff, 0xff, 0xff, 0xff
*/
/*
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x98, 0x9c, 
	0xfc, 0xfe, 0xfe, 0x9e, 0x9c, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x01, 0x07, 0xff, 0xff, 0xff, 0xff, 0x0e, 0xf1, 0x00, 0x0f, 0x70, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x14, 0xd7, 0x14, 0x07, 0x07, 0x03, 0x03, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xf1, 0x00, 0x00, 0x00, 0x0f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x78, 0x70, 0x60, 0x00, 0x00, 0x00, 0x60, 0x70, 0x78, 0x78, 0xfc, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x07, 0x78, 0x80, 0x03, 0x7c, 0x80, 0x80, 0x00, 0x80, 0xf0, 0x3c, 0x07, 0x7d, 0xed, 
	0x45, 0x37, 0xf5, 0x25, 0xed, 0x27, 0xe9, 0x27, 0xe0, 0x20, 0xc0, 0x00, 0xff, 0xff, 0xf8, 0x80, 
	0x00, 0x00, 0x03, 0x7f, 0x7f, 0x7f, 0x07, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x1f, 0x00, 0x00, 0x00, 0x04, 0x0b, 0x0a, 0x08, 0x10, 
	0x10, 0x06, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x5d, 0x9f, 0x40, 0x3f, 0x60, 0x7f, 0x40, 0x7f, 0x40, 
	0x7f, 0x60, 0x3f, 0x00, 0xff, 0xff, 0xff, 0xfb, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xfc, 0xff, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x20, 0x2d, 
	0x00, 0x00, 0x00, 0x00, 0x2d, 0x20, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x1f, 0x0f, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xc0, 
	0x80, 0x80, 0x0f, 0x1f, 0xbf, 0xff, 0xff, 0xff
*/
};


// 'rat_20x16_w_mask', 40x16px (80 bytes)
const unsigned char rat [] PROGMEM = {
	0x00, 0x00, 0x18, 0x7e, 0xb0, 0xf0, 0xf0, 0xb8, 0xfc, 0xee, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 
	0x28, 0x84, 0x00, 0x00, 0xff, 0xe7, 0x81, 0x00, 0x01, 0x07, 0x07, 0x03, 0x01, 0x00, 0x11, 0x1f, 
	0x1f, 0x3f, 0x7f, 0xc3, 0x01, 0x01, 0x7b, 0xff, 0x00, 0x0c, 0x06, 0x43, 0x43, 0x61, 0x31, 0x0e, 
	0x0f, 0x1f, 0x33, 0x4d, 0x5f, 0x7f, 0x5c, 0x08, 0x04, 0x0a, 0x00, 0x00, 0xe2, 0xe1, 0x30, 0x08, 
	0x18, 0x0c, 0x80, 0xc0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa3, 0xe0, 0xe0, 0xf0, 0xff
};
