//        >>>>>  T-I-N-Y  P-L-A-Q-U-E for ATTINY85  GPL v3 <<<<<
//                    Programmer: Daniel C 2020-2021
//               Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                    https://WWW.TINYJOYPAD.COM
//          https://sites.google.com/view/arduino-collection

//  Tiny-Plaque is free software: you can redistribute it and/or modify
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

void setup();

#define MAX_FOOD_TPLAQUE 4
#define MAX_FOOD_D_TPLAQUE 8

int16_t Mymap(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max);

//PUBLIC VAR
extern uint8_t Scan_Teeth_TPLAQUE;
extern uint8_t SCAN_COLLISION_TPLAQUE;
extern uint8_t BLINK_START_TPLAQUE;
extern uint8_t TC_TPLAQUE;
extern uint8_t TPC_TPLAQUE;
extern uint8_t TSIA_TPLAQUE;
extern bool ATTAQUE1_TPLAQUE;
extern bool ATTAQUE2_TPLAQUE;
extern uint8_t M10000_TPLAQUE;
extern uint8_t M1000_TPLAQUE;
extern uint8_t M100_TPLAQUE;
extern uint8_t M10_TPLAQUE;
extern uint8_t M1_TPLAQUE;

//PUBLIC OBJ
extern Main_Sprite_TPLAQUE MainSprite_TPLAQUE;
extern Food_Sprite_TPLAQUE M_Spr[MAX_FOOD_D_TPLAQUE];
extern Sprite_TPLAQUE TEETH_UP[8];
extern Sprite_TPLAQUE TEETH_DOWN[8];
extern Weapon_Sprite_TPLAQUE weapon;

void INIT_NEW_GAME_TPLAQUE(void);
void loop();
void ADJUST_TUBE_TIMER_TPLAQUE(void);
void ADJUST_TUBE_TPLAQUE(void);
void SCORE_ADD_TPLAQUE(uint8_t SC_);
void UPDATE_PANNEL_TPLAQUE(void);
void COMPIL_SCO_TPLAQUE(void);
uint8_t GAME_PLAY_TPLAQUE(void);
uint8_t END_OF_LEVEL_TPLAQUE(void);
void DSOUND_TPLAQUE(uint8_t T_AD);
void DSOUND2_TPLAQUE(void);
void DECOUNT_TPLAQUE(void);
void RESTORE_TEETH_TPLAQUE(void);
void Sound_ADDTEETH_TPLAQUE(void);
void ADD_TEETH_TPLAQUE(void);
uint8_t PUT_TEETH_TPLAQUE(Sprite_TPLAQUE &TEETH_);
void NEXT_LEVEL_TPLAQUE(void);
void LOAD_LEVEL_TPLAQUE(void);
void DELETE_TEETH_TPLAQUE(void);
void HIT_BOX_TPLAQUE(void);
void CHECK_NUMBER_OF_TEETH_TPLAQUE(void);
void Check_Collision_WBALISTIC_TPLAQUE(uint8_t T_V);
uint8_t Check_Collision_WTEETH_TPLAQUE(int8_t FX,int8_t FW,int8_t FY,int8_t FH,Sprite_TPLAQUE &SP_);
uint8_t Collision_WTEETH_AGAIN_TPLAQUE(uint8_t &Count,Sprite_TPLAQUE &TEETH_);
void INVERT_FOOD_DIRECTION_TPLAQUE(void);
void TEETH_RESET_TPLAQUE(void);
void FOOD_RESET_TPLAQUE(void);
void FOOD_MOVE_UPDATE_TPLAQUE(void);
void ADD_FOOD_TPLAQUE(void);
void COLAPS_FOOD_TPLAQUE(uint8_t T_V);
void UPDATE_FOOD_TRIGER_TPLAQUE(void);
void UPDATE_CHANGEX_TPLAQUE(void);
uint8_t blitzSprite_TPLAQUE(int8_t xPos,int8_t yPos,uint8_t xPASS,uint8_t yPASS,uint8_t FRAME,const uint8_t *SPRITES);
uint8_t BACK_TPLAQUE(uint8_t xPASS,uint8_t yPASS);
uint8_t TEETH_TPLAQUE(uint8_t xPASS);
uint8_t TEETH_DOWN_TPLAQUE(uint8_t xPASS,uint8_t MULT);
uint8_t TUBE_TPLAQUE(uint8_t xPASS,uint8_t yPASS);
uint8_t Food_Recupe_TPLAQUE(uint8_t xPASS,uint8_t yPASS);
uint8_t Recupe_TPLAQUE(uint8_t xPASS,uint8_t yPASS);
uint8_t SplitSpriteDecalageY_TPLAQUE(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN);
int8_t RecupeLineY_TPLAQUE(int8_t Valeur);
uint8_t RecupeDecalageY_TPLAQUE(uint8_t Valeur);
uint8_t Recupe_DCOUNT_TPLAQUE(uint8_t xPASS,uint8_t yPASS);
void Tiny_Flip_TPLAQUE(uint8_t T_FLIP);
uint8_t INTRO_TPLAQUE(uint8_t xPASS,uint8_t yPASS);
uint8_t TRACE_TPLAQUE(uint8_t xPASS);
uint8_t recupe_SCORES_TPLAQUE(uint8_t xPASS,uint8_t yPASS);
uint8_t Recupe_ExtraTeeth_TPLAQUE(uint8_t xPASS,uint8_t yPASS);
uint8_t SPEED_BLITZ_TPLAQUE(int8_t xPos,int8_t yPos,uint8_t xPASS,uint8_t yPASS,uint8_t FRAME,const uint8_t *SPRITES);

#endif // _GAME_H
