//        >>>>>  T-I-N-Y  M-O-R-P-I-O-N for ATTINY85  GPL v3 <<<<<
//                    Programmer: Daniel C 2020-2021
//             Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                    https://WWW.TINYJOYPAD.COM
//          https://sites.google.com/view/arduino-collection

//  tiny-Morpion is free software: you can redistribute it and/or modify
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

/*
#define TINYJOYPAD_LEFT  (analogRead(A0)>=750)&&(analogRead(A0)<950)
#define TINYJOYPAD_RIGHT (analogRead(A0)>500)&&(analogRead(A0)<750)
#define TINYJOYPAD_DOWN (analogRead(A3)>=750)&&(analogRead(A3)<950)
#define TINYJOYPAD_UP  (analogRead(A3)>500)&&(analogRead(A3)<750)
#define BUTTON_DOWN (digitalRead(1)==0)
#define BUTTON_UP (digitalRead(1)==1)
*/

extern const uint8_t CPU_RNDALT_TMORPION[] PROGMEM;
extern const uint8_t LINE_CHECK_TMORPION[] PROGMEM;
extern const uint8_t CPU_CHECK_MIDDLE_TMORPION[] PROGMEM;
extern const uint8_t police_TMORPION[] PROGMEM;
extern const uint8_t PLATEAU_UP_TMORPION[] PROGMEM;
extern const uint8_t PLATEAU_TMORPION[] PROGMEM;
extern const uint8_t UP_POS_TMORPION[] PROGMEM;
extern const uint8_t MIDDLE_POS_TMORPION[] PROGMEM;
extern const uint8_t DOWN_POS_TMORPION[] PROGMEM;
extern const uint8_t UP_TMORPION[] PROGMEM;
extern const uint8_t MIDDLE_TMORPION[] PROGMEM;
extern const uint8_t DOWN_TMORPION[] PROGMEM;
extern const uint8_t menu_TMORPION[] PROGMEM;
extern const uint8_t CURSEUR_TMORPION[] PROGMEM;
extern const uint8_t intro_TMORPION[] PROGMEM;

#endif // _SPRITEBANK_H
