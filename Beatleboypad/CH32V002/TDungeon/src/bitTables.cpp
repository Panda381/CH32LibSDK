
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#include "../include.h"

//#pragma once

// some simple tables to save time and code

//#include <Arduino.h>

// Table of '1' bits in a nibble.
const uint8_t nibbleBitCount[16] PROGMEM =
{
  0, // 0b0000
  1, // 0b0001
  1, // 0b0010
  2, // 0b0011
  1, // 0b0100
  2, // 0b0101
  2, // 0b0110
  3, // 0b0111
  1, // 0b1000
  2, // 0b1001
  2, // 0b1010
  3, // 0b1011
  2, // 0b1100
  3, // 0b1101
  3, // 0b1110
  4, // 0b1111
};

// a 4 bit zoom table (e.g. for character enlargement)
const uint8_t  nibbleZoom[] PROGMEM = {
  0b00000000, // 0b0000
  0b00000011, // 0b0001
  0b00001100, // 0b0010
  0b00001111, // 0b0011
  0b00110000, // 0b0100
  0b00110011, // 0b0101
  0b00111100, // 0b0110
  0b00111111, // 0b0111
  0b11000000, // 0b1000
  0b11000011, // 0b1001
  0b11001100, // 0b1010
  0b11001111, // 0b1011
  0b11110000, // 0b1100
  0b11110011, // 0b1101
  0b11111100, // 0b1110
  0b11111111, // 0b1111
};

// Conversion table from view distance to scaling factor.
// A distance of '0' is undefined but simplyfies addressing.
const uint8_t scalingFactorFromDistance[] PROGMEM = { 0, 1, 2, 4 };

// Vertical start and end offsets depending on distance
//
// distance: 1 2 3
//           0 - - 
//           1 - -
//           2 0 -
//           3 1 0
//           4 2 1
//           5 3 -
//           6 - -
//           7 - -
const uint8_t verticalStartOffset[] PROGMEM = { 0, 0, 2, 3 };
const uint8_t verticalEndOffset[]   PROGMEM = { 0, 7, 5, 4 };

// Conversion table from scaling factor to bit mask.
// A factor of '0' is undefined but simplyfies addressing.
const uint8_t bitMaskFromScalingFactor[] PROGMEM =
{
//    -     1     2     -       4 
    0x00, 0x01, 0x03, 0x00  , 0x0F,
};
