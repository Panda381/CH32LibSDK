//      >>>>>  T-I-N-Y  B-E-R-T for ATTINY85  GPL v3 <<<<
//                   Programmer: Daniel C 2019-2021
//              Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                     https://www.tinyjoypad.com   
//           https://sites.google.com/view/arduino-collection

//  Tiny Bert is free software: you can redistribute it and/or modify
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

#define DEFAULT_SPEED  30
extern uint8_t MAX_RENEW;
extern uint8_t MAX_SPEED;

typedef struct Sprite
{
	uint8_t moveTimer1;
	uint8_t DEAD;
	uint8_t Timer_new_Live;
	uint8_t JumpFrame;  
	int8_t GridXpos;
	int8_t GridYpos;
	int8_t xPOS;
	int8_t yPOS;
	uint8_t Joypad_Key;
	uint8_t sw;
} Sprite;

extern uint8_t PlateGrid[4][4];
extern const int8_t RAND2[] PROGMEM;
extern const int8_t RAND4[] PROGMEM;
extern const int8_t Jump[] PROGMEM;
extern const uint8_t PlatePos[] PROGMEM;
extern const uint8_t INTRO[] PROGMEM;
extern const uint8_t BACK[] PROGMEM;
extern const uint8_t Plate[] PROGMEM;
extern const uint8_t TINYBERT[] PROGMEM;
extern const uint8_t TINYBERT_BLACK[] PROGMEM;
extern const uint8_t BALL[] PROGMEM;
extern const uint8_t BALL_BLACK[] PROGMEM;
extern const uint8_t SNACK[] PROGMEM;
extern const uint8_t SNACK_BLACK[] PROGMEM;
extern const uint8_t Live[] PROGMEM;
extern const uint8_t police[] PROGMEM;
extern const uint8_t LIFT_PLATE[] PROGMEM;

#endif // _SPRITEBANK_H
