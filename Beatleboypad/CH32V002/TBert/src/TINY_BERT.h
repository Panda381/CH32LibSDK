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

#ifndef _GAME_H
#define _GAME_H

// var public
extern uint8_t INTERLACE;
extern uint8_t ANIM_LIFT;
extern uint8_t DESTROY_LIFT_R;
extern uint8_t DESTROY_LIFT_L;
extern uint8_t SEED;
extern uint8_t INGAME;
extern uint8_t MAIN_GHOST;
extern uint8_t BYPASS_DEAD;
extern uint8_t DIFICULT_PLATE;
extern uint8_t Dificulty;
extern uint8_t RENEW_SPRITE;
extern int8_t Extra_Live;
extern uint8_t CHANGE_LEVEL;
extern uint8_t D4,D3,D2,D1,D0;
extern uint8_t HD4,HD3,HD2,HD1,HD0;
// fin var public

void setup();
void DIFICULTY_CHANGE(void);
void ResetDataVar(Sprite* DATA);
void RESET_GAME(void);
void SEED_RND(void);
uint8_t RANDOM(uint8_t STEP);
void Recupe_HighScore(void);
void Rst_Score(void);
void recupe_Score(void);
uint16_t HighScore(uint8_t D_3,uint8_t D_2,uint8_t D_1,uint8_t D_0);
void loop();
void DEAD_SOUND(void);
void DEADIFY(uint8_t SPr,Sprite *DATA);
void RenewSprite(uint8_t SPr,Sprite *DATA);
uint8_t Renew_if_Posible(Sprite *DATA);
uint8_t Renew_Check_if_Posible(uint8_t SPr,Sprite *DATA);
uint8_t COLLISION_CHECK(Sprite *DATA);
void FLIP_PLATE(void);
void GamePlayUpdate(Sprite *DATA);
void renew_if_possible_add(uint8_t Sprite );
void ResetPlateGrid(void);
void ScoreChange(void);
void refreshJump(uint8_t SpUSE,Sprite *DATA);
void TELEPORT_MAIN(Sprite *DATA);
uint8_t UPDATE_LIFT_MAIN(uint8_t SpUSE,Sprite *DATA);
void UPDATE_MAIN_MOVE(uint8_t SpUSE,Sprite *DATA);
void UPDATE_MAIN_DEAD(uint8_t SpUSE,Sprite *DATA);
void LimitCheck(uint8_t SpUSE,uint8_t JOYKEY,Sprite *DATA);
uint8_t GridLimitTest(uint8_t SpUSE,int8_t x,int8_t y,Sprite *DATA);
uint8_t Level_Completed(void);
void Ball_move_update(uint8_t SpUSE,Sprite *sprite);
uint8_t blitzSprite(int8_t xPos,int8_t yPos,uint8_t xPASS,uint8_t yPASS,uint8_t FRAME,const uint8_t *SPRITES);
uint8_t GridPlate(uint8_t xPASS,uint8_t yPASS);
uint8_t Recupe(uint8_t xPASS,uint8_t yPASS,Sprite *DATA);
uint8_t SplitSpriteDecalageY(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN);
int8_t RecupeLineY(int8_t Valeur);
uint8_t RecupeDecalageY(uint8_t Valeur);
uint8_t Tiny_Bert_Live_Print(uint8_t xPASS,uint8_t yPASS);
uint8_t Police_Print(uint8_t xPASS,uint8_t yPASS);
void Tiny_Flip(uint8_t Scan,Sprite *DATA);
//void Sound(uint8_t freq,uint8_t dur);

#endif // _GAME_H
