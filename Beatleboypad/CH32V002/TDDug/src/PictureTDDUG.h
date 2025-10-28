//        >>>>>  T-I-N-Y  D-D-U-G for ATTINY85  GPL v3 <<<<<
//                  Programmer: Daniel C 2020-2021
//               Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                    https://WWW.TINYJOYPAD.COM
//          https://sites.google.com/view/arduino-collection

//  tiny-DDug is free software: you can redistribute it and/or modify
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

//#include <avr/pgmspace.h>

#ifndef _PICTURE_TDDUG_H
#define _PICTURE_TDDUG_H

enum {
	HAUT=0,
	DROITE=1,
	BAS=2,
	GAUCHE=3
};

/*
#define TINYJOYPAD_LEFT KeyPressed(KEY_LEFT) //(analogRead(A0) >= 750) && (analogRead(A0) < 950)
#define TINYJOYPAD_RIGHT KeyPressed(KEY_RIGHT) //(analogRead(A0) > 500) && (analogRead(A0) < 750)
#define TINYJOYPAD_DOWN KeyPressed(KEY_DOWN) //(analogRead(A3) >= 750) && (analogRead(A3) < 950)
#define TINYJOYPAD_UP KeyPressed(KEY_UP) //(analogRead(A3) > 500) && (analogRead(A3) < 750)
#define BUTTON_DOWN KeyPressed(KEY_A) //(digitalRead(1) == 0)
#define BUTTON_UP (!KeyPressed(KEY_A)) //(digitalRead(1) == 1)
*/

extern const int8_t ENEMY_ENABLE_TDDUG[] PROGMEM;
extern const int8_t ENEMY_TDDUG[] PROGMEM;
extern const uint8_t LEVEL_TDDUG[] PROGMEM;
extern const int8_t RnD_TDDUG[] PROGMEM;
extern const uint8_t TDDUG[] PROGMEM;
extern const uint8_t Dig_TDDUG[] PROGMEM;
extern const uint8_t police_TDDUG[] PROGMEM;
extern const uint8_t Sprite_ENEMY_TDDUG[] PROGMEM;
extern const uint8_t LAZER_TDDUG[] PROGMEM;
extern const uint8_t LIVE_TDDUG[] PROGMEM;
extern const uint8_t DDUG_INTRO_TDDUG[] PROGMEM;
extern const uint8_t START_TDDUG[] PROGMEM;

#endif // _PICTURE_TDDUG_H
