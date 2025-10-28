//   >>>>>  T-I-N-Y  D-U-N-G-E-O-N v1.0.1 for ATTINY85  MIT License <<<<
//						Tinyjoypad rev2 compatible
//                   Developer: Sven B 2021-2023
//              Contact EMAIL: Lorandil@gmx.de

//  Tiny Dungeon is free software: you can redistribute it and/or modify
//  it under the terms of the MIT License.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  MIT License for more details.

// Resources:
// ----------
// A SSD1306 library for I2C is required:
// - for ATtiny85 the <ssd1306xled> library by Tinusaur/Neven Boyanov is required.
// - for all other micro controllers the Adafruit_SSD1306 library is used.
//
// Because the Arduino IDE doesn't come with ATtiny85 support, a suitable core is required:
//   To stuff all code and data into the 8192 bytes of the ATtiny85
//   the ATTinyCore (v1.5.2) by Spence Konde is recommended.
//   The core is available at github: [https://github.com/SpenceKonde/ATTinyCore], just add the
//   following board manager to the Arduino IDE: [http://drazzy.com/package_drazzy.com_index.json]
//   Please enable LTO (link time optimization) and disable 'millis()' and
//   'micros()' and set the PLL to 16MHZ Internal PLL.

// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#ifndef _GAME_H
#define _GAME_H

void setup();
void loop();

#endif // _GAME_H
