//         >>>>>  T-I-N-Y  T-R-I-S v3 for ATTINY85  GPL v3 <<<<<
//                     Programmer: Daniel C 2019-2021
//              Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                      https://WWW.TINYJOYPAD.COM
//           https://sites.google.com/view/arduino-collection

//  Tiny-tris is free software: you can redistribute it and/or modify
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

/*
#define TINYJOYPAD_LEFT KeyPressed(KEY_LEFT) //(analogRead(A0) >= 750) && (analogRead(A0) < 950)
#define TINYJOYPAD_RIGHT KeyPressed(KEY_RIGHT) //(analogRead(A0) > 500) && (analogRead(A0) < 750)
#define TINYJOYPAD_DOWN KeyPressed(KEY_DOWN) //(analogRead(A3) >= 750) && (analogRead(A3) < 950)
#define TINYJOYPAD_UP KeyPressed(KEY_UP) //(analogRead(A3) > 500) && (analogRead(A3) < 750)
#define BUTTON_DOWN KeyPressed(KEY_A) //(digitalRead(1) == 0)
#define BUTTON_UP (!KeyPressed(KEY_A)) //(digitalRead(1) == 1)
*/

//public var
extern uint8_t Grid_TTRIS[12][3];
extern const uint8_t MEM_TTTRIS[16];
extern uint8_t Level_TTRIS;
extern uint16_t Scores_TTRIS;
extern uint16_t Nb_of_line_F_TTRIS;
extern uint8_t Level_Speed_ADJ_TTRIS;
extern uint8_t Nb_of_line_TTRIS[3];
extern uint8_t RND_VAR_TTRIS;
extern uint8_t LONG_PRESS_X_TTRIS;
extern uint8_t DOWN_DESACTIVE_TTRIS;
extern uint8_t DROP_SPEED_TTRIS;
extern uint8_t SPEED_x_trig_TTRIS;
extern uint8_t DROP_TRIG_TTRIS;
extern int8_t xx_TTRIS,yy_TTRIS;
extern uint8_t Piece_Mat2_TTRIS[5][5];
extern uint8_t Ripple_filter_TTRIS;
extern uint8_t PIECEs_TTRIS;
extern uint8_t PIECEs_TTRIS_PREVIEW;
extern uint8_t PIECEs_rot_TTRIS;
extern uint8_t DROP_BREAK_TTRIS;
extern int8_t OU_SUIS_JE_X_TTRIS;
extern int8_t OU_SUIS_JE_Y_TTRIS;
extern uint8_t OU_SUIS_JE_X_ENGAGED_TTRIS;
extern uint8_t OU_SUIS_JE_Y_ENGAGED_TTRIS;
extern int8_t DEPLACEMENT_XX_TTRIS;
extern int8_t DEPLACEMENT_YY_TTRIS;

extern const uint8_t H_Grid_TTTRIS[] PROGMEM;
extern const uint8_t Pieces_TTRIS[] PROGMEM;
extern const uint8_t tiny_PREVIEW_block_TTTRIS[] PROGMEM;
extern const uint8_t tinyblock_TTTRIS[] PROGMEM;
extern const uint8_t tinyblock2_TTTRIS[] PROGMEM;
extern const uint8_t police_TTRIS[] PROGMEM;
extern const uint8_t start_button_1_TTRIS[] PROGMEM;
extern const uint8_t start_button_2_TTRIS[] PROGMEM;
extern const uint8_t chateau_TTRIS[] PROGMEM;
extern const uint8_t BACKGROUND_TTRIS[] PROGMEM;

#endif // _SPRITEBANK_H
