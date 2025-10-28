//       >>>>>  T-I-N-Y  S-Q-U-E-S-T for ATTINY85  GPL v3 <<<<<
//                    Programmer: Daniel C 2023
//             Contact EMAIL: electro_l.i.b@tinyjoypad.com
//  https://github.com/phoenixbozo/TinyJoypad/tree/main/TinyJoypad
//                    https://WWW.TINYJOYPAD.COM
//          https://sites.google.com/view/arduino-collection

//  tiny-Squest is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

//for TINY JOYPAD rev2 (attiny85)
//the code work at 16MHZ internal
//Program the chip with an arduino uno in "Arduino as ISP" mode.

// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#ifndef _SPRITEBANK_H
#define _SPRITEBANK_H

#define FADEIN 0
#define FADEOUT 1

extern const int8_t POSITION_TSQUEST[] PROGMEM;
extern const uint8_t RND3_TSQUEST[] PROGMEM;
extern const uint8_t RND2_TSQUEST[] PROGMEM;
extern const uint8_t Line_TSQUEST[] PROGMEM;
extern const int8_t SIN_TSQUEST[] PROGMEM;
extern const uint8_t Music[] PROGMEM;
extern const uint8_t police_TSQUEST[] PROGMEM;
extern const uint8_t BACKGROUND_TSQUEST[] PROGMEM;
extern const uint8_t T_SUBMAIN_TSQUEST[] PROGMEM;
extern const uint8_t BLINK_MAINSUB_TSQUEST[] PROGMEM;
extern const uint8_t DESTROYED_MAINSUB_TSQUEST[] PROGMEM;
extern const uint8_t SUB2_TSQUEST[] PROGMEM;
extern const uint8_t BALLISTIC_TSQUEST[] PROGMEM;
extern const uint8_t BALLISTIC2_TSQUEST[] PROGMEM;
extern const uint8_t FISH_TSQUEST[] PROGMEM;
extern const uint8_t PLONGEUR_TSQUEST[] PROGMEM;
extern const uint8_t Display_DIVER_TSQUEST[] PROGMEM;
extern const uint8_t LIVE_TSQUEST[] PROGMEM;
extern const uint8_t INTRO_TSQUEST[] PROGMEM;
extern const uint8_t START_TSQUEST[] PROGMEM;

#endif // _SPRITEBANK_H
