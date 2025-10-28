//        >>>>>  T-I-N-Y  M-I-S-S-I-L-E for ATTINY85  GPL v3 <<<<<
//                    Programmer: Daniel C 2020-2021
//             Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                    https://WWW.TINYJOYPAD.COM
//          https://sites.google.com/view/arduino-collection

//  tiny-Missile is free software: you can redistribute it and/or modify
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

#ifndef _PIC_TMISSILE_H
#define _PIC_TMISSILE_H

//#include <avr/pgmspace.h>

//DEFINE
#define NUM_of_DOME_TMISSILE 6
#define NUM_of_MISSILE_TMISSILE 4
//#define CONTROL_FRAMERATE(ZETA_) while((currentMillis-MemMillis)<ZETA_){currentMillis=millis();}MemMillis=currentMillis
//DEFINE END

extern const uint8_t DOME_ORDER_TMISSILE[] PROGMEM;
extern const uint8_t DOME_SPRITE_TMISSILE[] PROGMEM;
extern const uint8_t ROCKET_TMISSILE[] PROGMEM;
extern const uint8_t CROSS_TMISSILE[] PROGMEM;
extern const uint8_t police_TMISSILE[] PROGMEM;
extern const uint8_t INTERCEPT_TMISSILE[] PROGMEM;
extern const uint8_t TOP_PANEL_TMISSILE[] PROGMEM;
extern const uint8_t intro_TMISSILE[] PROGMEM;
extern const uint8_t Y1_TMISSILE[] PROGMEM;
extern const uint8_t CENTER_TMISSILE[] PROGMEM;
extern const uint8_t Y6_TMISSILE[] PROGMEM;
extern const uint8_t Y7_TMISSILE[] PROGMEM;

#endif // _PIC_TMISSILE_H
