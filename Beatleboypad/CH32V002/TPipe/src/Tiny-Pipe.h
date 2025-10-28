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

#ifndef _GAME_H
#define _GAME_H

//PUBLIC VAR
extern uint8_t SEQUENCIALCHECK_TPIPE;//check all collision sprite in sequencial methode
extern uint8_t BLINK_TPIPE; //BLINK 50% FPS
extern uint8_t D_CHANGE_TPIPE;
extern uint8_t D_CHANGE_B_TPIPE;

extern unsigned long currentMillis;
extern unsigned long MemMillis;

extern GamePlay_TPIPE GP;

//PUBLIC OBJ
extern SPRITE_TPIPE Main;
extern SPRITE_TPIPE Sprite[NO_SPR];

void setup();
void loop();
void SND_TPIPE(uint8_t SnD_);
void UPDATE_DIGITAL_TPIPE(void);
void LOAD_LEVEL_TPIPE(uint8_t L_);
uint8_t Intro_TPIPE(void);
void ADJ_GP_TPIPE(void);
void SHIELD_REMOVE_TPIPE(void);
void TIMER_FOR_NEW_TURTLE_TPIPE(void);
void CHECK_FOR_NEW_TURTLE_TPIPE(void);
void CHECK_LEVEL_COMPLETED_TPIPE(void);
void NEW_TURTLE_TPIPE(void);
void CHECK_CYCLE_COLLISION_TPIPE(void);
void KILL_SPRITE_TPIPE(void);
void INVERT_TURTLE_TPIPE(uint8_t No_SPR,uint8_t VAL_SPR);
uint8_t HIT_BUMP_CHECK_TPIPE(void);
void ALL_INVERT_TURTLE_TPIPE(void);
void INIT_TURTLE_TPIPE(void);
void CHANGE_DIRECTION_TPIPE(void);
void REFRESH_TURTLE_TPIPE(void);
void NO_MOVE_TIMER_TPIPE(uint8_t SPR_);
uint8_t ANIM_TPIPE(SPRITE_TPIPE *SP_);
uint8_t Main_Blitz_TPIPE(uint8_t XPASS,uint8_t YPASS);
uint8_t Sprites_Turtle_TPIPE(uint8_t XPASS,uint8_t YPASS);
uint8_t Power_TPIPE(uint8_t XPASS,uint8_t YPASS);
uint8_t RECUPE_TPIPE(uint8_t XPASS,uint8_t YPASS);
uint8_t Back_TPIPE(uint8_t XPASS,uint8_t YPASS);
void Tiny_Flip_TPIPE(uint8_t FLIP_MODE_);
void INTRO_TPIPE(uint8_t FLIP_MODE_);
void DRAW_LEVEL_TPIPE(void);
void GP_INIT_TPIPE(void);
void NEW_GAME_TPIPE(void);
void NEXT_LEVEL_TPIPE(void);

#endif // _GAME_H
