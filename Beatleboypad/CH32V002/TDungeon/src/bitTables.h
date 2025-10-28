
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#ifndef _BITTABLES_H
#define _BITTABLES_H

// Table of '1' bits in a nibble.
extern const uint8_t nibbleBitCount[16] PROGMEM;

// a 4 bit zoom table (e.g. for character enlargement)
extern const uint8_t  nibbleZoom[] PROGMEM;

// Conversion table from view distance to scaling factor.
// A distance of '0' is undefined but simplyfies addressing.
extern const uint8_t scalingFactorFromDistance[] PROGMEM;

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
extern const uint8_t verticalStartOffset[] PROGMEM;
extern const uint8_t verticalEndOffset[]   PROGMEM;

// Conversion table from scaling factor to bit mask.
// A factor of '0' is undefined but simplyfies addressing.
extern const uint8_t bitMaskFromScalingFactor[] PROGMEM;

#endif // _BITTABLES_H
