//      >>>>>  T-I-N-Y  T-R-I-C-K for ATTINY85  GPL v3 <<<<
//                    Programmer: Daniel C 2019-2021
//              Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                      https://WWW.TINYJOYPAD.COM
//           https://sites.google.com/view/arduino-collection

//  Tiny trick is free software: you can redistribute it and/or modify
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

typedef struct Sprite
{
	uint8_t Xpos;
	uint8_t Ypos;
	uint8_t CumuleX;
	uint8_t SpeedXpositif;
	uint8_t SpeedXnegatif;
	uint8_t CumuleY;
	uint8_t SpeedYpositif;
	uint8_t SpeedYnegatif;
} Sprite;

extern const int8_t PLAYER_Puck[] PROGMEM;
extern const uint8_t PLAYER_DIM[] PROGMEM;
extern const uint8_t GOALER_WHITE[] PROGMEM;
extern const uint8_t GOALER_BLACK[] PROGMEM;
extern const uint8_t puck[] PROGMEM;
extern const uint8_t NUM[] PROGMEM;
extern const uint8_t PLAYER_WHITE_B[] PROGMEM;
extern const uint8_t PLAYER_BLACK_B[] PROGMEM;
extern const uint8_t patinoire1_2[] PROGMEM;
extern const uint8_t Intro[] PROGMEM;
extern const uint8_t cadre40_37[] PROGMEM;
extern const uint8_t screen[] PROGMEM;
extern const uint8_t lost[] PROGMEM;
extern const uint8_t win[] PROGMEM;

#endif // _SPRITEBANK_H
