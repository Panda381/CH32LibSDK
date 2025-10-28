//         >>>>>  T-I-N-Y  P-I-P-E for ATTINY85  GPL v3 <<<<<
//                    Programmer: Daniel C 2021
//             Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                    https://WWW.TINYJOYPAD.COM
//          https://sites.google.com/view/arduino-collection

//  tiny-Pipe is free software: you can redistribute it and/or modify
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

extern const uint8_t Music[] PROGMEM;
extern const uint8_t Music2[] PROGMEM;
extern const uint8_t police_TPIPE[] PROGMEM;
extern const uint8_t LEVEL_TPIPE[] PROGMEM;
extern const uint8_t MAIN_TPIPE[] PROGMEM;
extern const uint8_t TURTLE_TPIPE[] PROGMEM;
extern const uint8_t RND_TPIPE[] PROGMEM;
extern const uint8_t POWER_TPIPE[] PROGMEM;
extern const uint8_t BACKGROUND_TPIPE[] PROGMEM;
extern const uint8_t TITLE_TPIPE[] PROGMEM;
extern const uint8_t START_TPIPE[] PROGMEM;

#endif // _SPRITEBANK_H
