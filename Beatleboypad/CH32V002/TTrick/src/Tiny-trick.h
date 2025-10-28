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

#ifndef _GAME_H
#define _GAME_H

// var public
extern uint8_t Player1_Rotate;
extern uint8_t Computer_Rotate;
extern uint8_t COM_MAX_SPEED_x;
extern uint8_t COM_MAX_SPEED_y;
extern uint8_t ORIx;
extern uint8_t ORIy;
extern uint8_t SKIP_FRAME;
extern uint8_t Drag_Puck;
extern uint8_t Puck_x;
extern uint8_t Puck_y;
extern uint8_t X_Drag;
extern uint8_t Y_drag;
extern uint8_t GOAL_;
extern uint8_t Points_CPU;
extern uint8_t Points_Pl1;
// fin var public

void setup();

/*
#define TINYJOYPAD_LEFT KeyPressed(KEY_LEFT) //(analogRead(A0) >= 750) && (analogRead(A0) < 950)
#define TINYJOYPAD_RIGHT KeyPressed(KEY_RIGHT) //(analogRead(A0) > 500) && (analogRead(A0) < 750)
#define TINYJOYPAD_DOWN KeyPressed(KEY_DOWN) //(analogRead(A3) >= 750) && (analogRead(A3) < 950)
#define TINYJOYPAD_UP KeyPressed(KEY_UP) //(analogRead(A3) > 500) && (analogRead(A3) < 750)
#define BUTTON_DOWN KeyPressed(KEY_A) //(digitalRead(1) == 0)
#define BUTTON_UP (!KeyPressed(KEY_A)) //(digitalRead(1) == 1)
*/
/*
#define TINYJOYPAD_LEFT  (analogRead(A0)>=750)&&(analogRead(A0)<950)
#define TINYJOYPAD_RIGHT (analogRead(A0)>500)&&(analogRead(A0)<750)
#define TINYJOYPAD_DOWN (analogRead(A3)>=750)&&(analogRead(A3)<950)
#define TINYJOYPAD_UP  (analogRead(A3)>500)&&(analogRead(A3)<750)
#define BUTTON_DOWN (digitalRead(1)==0)
#define BUTTON_UP (digitalRead(1)==1)
*/

extern Sprite sprite[5];

void Reset_new_game(void);
void ResetAllSprites(void);
void INIT_ALL_VAR(void);
#define PUCK_X sprite[2].Xpos
#define PUCK_Y sprite[2].Ypos
void Goal_Adj(uint8_t Y_POS,uint8_t SPR_Type);
void SND(uint8_t Snd);
void loop();
uint8_t check_Puck2Gard(uint8_t Gard);
uint8_t GOAL(uint8_t Goal_0,uint8_t Goal_1);
void Reverse_x_puck_2_pos(uint8_t SpriteTested);
void Reverse_x_puck_2_neg(uint8_t SpriteTested);
uint8_t collision_check_LimiteScreen(uint8_t SpriteTested);
void KICK_PUCK(uint8_t Player_Rotate);
void Drag_Puck_Update(void);
void Drag_Puck_test(void);
void Speed_Puck_Decel(uint8_t SPR_TYPE);
void BOUNCE_SPRITE(void);
void Reverse_y_pla(uint8_t SpriteTested);
void Reverse_x_pla(uint8_t SpriteTested);
uint8_t collision_check_Sprite2Sprite(uint8_t Sp_1,uint8_t Sp_2);
uint8_t Computer_rotation_filter_update(void);
uint8_t Direction_Recupe(uint8_t Con);
uint8_t Update_Computer_Direction(void);
void Speed_H_Decel(uint8_t SPR_TYPE);
void Speed_V_Decel(uint8_t SPR_TYPE);
uint8_t Adjust_Speed_Computer(uint8_t Puck,uint8_t Val_Computer_2);
void Adjust_Cumule_Speed(uint8_t SPRITE_NO);
void Speed_adj_H_P(uint8_t SPRITE_NO);
void Speed_adj_H_N(uint8_t SPRITE_NO);
void Speed_adj_V_P(uint8_t SPRITE_NO);
void Speed_adj_V_N(uint8_t SPRITE_NO);
uint8_t blitzSprite(int8_t xPos,int8_t yPos,uint8_t xPASS,uint8_t yPASS,uint8_t FRAME,const uint8_t *SPRITES);
uint8_t Recupe(uint8_t xPASS,uint8_t yPASS);
uint8_t Patinoire1_2(uint8_t xPASS,uint8_t yPASS);
uint8_t SplitSpriteDecalageY(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN);
uint8_t RecupeLineY(uint8_t Valeur);
uint8_t RecupeDecalageY(uint8_t Valeur);
void Tiny_Flip(void);
void intro(uint8_t GOAL_SCREEN,uint8_t SLIDE);
uint8_t Lost_win(uint8_t xPASS,uint8_t yPASS,const uint8_t *SPRITES );
void SCREEN_GOAL(void);
//void Sound(uint8_t freq_,uint8_t dur);

#endif // _GAME_H
