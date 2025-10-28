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

//#include "PictureTDDUG.h"

#ifndef _CLASS_TDDUG_H
#define _CLASS_TDDUG_H

#define MAIN_ACCEL_SPEED_TDDUG 50
#define SPRITE_ACCEL_SPEED_TDDUG 50
#define ENEMY_SPEED_STEP_TDDUG 25

//PROTOTYPE
void SND_DDUG(void);
void SCORES_ADD_TDDUG(void);
uint8_t READ_GRID_TDDUG(int8_t X_,int8_t Y_);
uint8_t WRITE_GRID_TDDUG(int8_t X_,int8_t Y_);
uint8_t RecupeDecalageY_TDDUG(uint8_t Valeur);
int8_t RND_TDDUG(void);
void ANIM_UPDATE_MAIN_TDDUG(uint8_t Direct_);
void Sound_TDDUG(uint8_t freq_,uint8_t dur);

//PUBLIC VAR
extern int8_t RD_TDDUG;
extern uint8_t EXT_COUNT_TDDUG;
extern uint8_t EXT_GRID_TDDUG;
extern uint8_t M10000_TDDUG;
extern uint8_t M1000_TDDUG;
extern uint8_t M100_TDDUG;
extern uint8_t M10_TDDUG;
extern uint8_t M1_TDDUG;
extern uint8_t Anim_Enemy_TDDUG;
extern uint8_t Anim_Enemy_Frame_TDDUG;
extern uint8_t MAIN_SPEED_STEP_TDDUG;

//PUBLIC: STRUCT VAR
struct GAME_DATA_TDDUG
{
	uint8_t TimeLaps;
	uint8_t FirsT_Time;
	uint8_t One_Time_TDDUG;
	uint8_t Counter; 
	uint8_t Trigger_Counter;
	uint8_t MAIN_FRAME;
	uint8_t MAIN_ANIM_FRAME;
	uint8_t MAIN_ANIM;
	uint8_t DIRECTION_ANIM;
	uint16_t Scores;
	uint8_t Skip_Frame;
	uint8_t LEVEL;
	uint8_t GO_OUT;
	uint8_t NOSPRITE_GO_OUT;
	uint8_t DEAD;
	uint8_t LIVE;
	uint8_t LIVE_COMP;
};

extern GAME_DATA_TDDUG GD_DDUG;

extern uint8_t GRID_TDDUG[12][3];

class Sprite_TDDUG
{
private:
	int8_t x;
	int8_t y;
	int8_t direction_x;
	int8_t direction_y;
	int8_t active;
public:
	int8_t X(void);
	int8_t Y(void);
	int8_t ACTIVE(void);
	void PUT_X(int8_t XX);
	void PUT_Y(int8_t YY);
	void PUT_ACTIVE(int8_t ACT);
	int8_t DIRECTION_X(void);
	int8_t DIRECTION_Y(void);
	void PUT_DIRECTION_X(int8_t D_X);
	void PUT_DIRECTION_Y(int8_t D_Y);
};

class Moving_Sprite_TDDUG : public Sprite_TDDUG
{
private:
	int8_t Som_x;
	int8_t Som_y;
	int8_t sx;
	int8_t sy;

public:
	int8_t SOMX(void);
	int8_t SOMY(void);
	int8_t SX(void);
	int8_t SY(void);
	void PUT_SX(int8_t SX_);
	void PUT_SY(int8_t SY_);
	void PUT_SOMX(int8_t PUT_SOMX_);
	void PUT_SOMY(int8_t PUT_SOMX_);
	void HAUT(void);
	void DROITE(void);
	void BAS(void);
	void GAUCHE(void);
	void Ou_suis_je(uint8_t &x_,uint8_t &y_);
};

class Enemy_Sprite_TDDUG : public Moving_Sprite_TDDUG
{
private:
	uint8_t First;
	uint8_t Type;
	int8_t Tracking;
	uint8_t Anim_Direct;
	uint8_t Anim;
	uint8_t Big_zip;

public:
	uint8_t ANIM_DIRECT(void);
	void PUT_ANIM_DIRECT(uint8_t H_Dir_);
	void PUT_TYPE(uint8_t TY_);
	uint8_t TYPE(void);
	void PUT_TRACKING(int8_t TR_);
	int8_t TRACKING(void);
	void INIT(int8_t X_,int8_t Y_,int8_t Type_);
	void HAUT(void);
	void DROITE(void);
	void BAS(void);
	void GAUCHE(void);
	void NEW_DIRECTION(int8_t dir_);
	void NEW_LIMITE_DIRECTION(int8_t dir_);
	void PUT_ANIM(uint8_t Ani_);
	uint8_t ANIM(void);
	uint8_t E_GRID_UPDATE_UP(void);
	uint8_t E_GRID_UPDATE_DOWN(void);
	uint8_t E_GRID_UPDATE_RIGHT(void);
	uint8_t E_GRID_UPDATE_LEFT(void);
	uint8_t FIRST(void);
	void PUT_FIRST(uint8_t Fir_);
	uint8_t BIG_ZIP(void);
	void PUT_BIG_ZIP(uint8_t Fir_);
};
  
class Main_Sprite_TDDUG : public Moving_Sprite_TDDUG
{
public:
	void MHAUT(void);
	void MDROITE(void);
	void MBAS(void);
	void MGAUCHE(void);
	void INIT(void);
	void WALK_RIGHT(void);
	void WALK_LEFT(void);
	void WALK_UP(void);
	void WALK_DOWN(void);
	void GRID_UPDATE_RIGHT(void);
	void GRID_UPDATE_LEFT(void);
	void GRID_UPDATE_UP(void);
	void GRID_UPDATE_DOWN(void);
private:
};

//CLASS WEAPON
class WEAPON_TDDUG : public Sprite_TDDUG
{
public:
	void INIT_WEAPON(void);
	void ADJUST_WEAPON(Main_Sprite_TDDUG &MS_);
	void ADJUST_WEAPON2(WEAPON_TDDUG &W_,Main_Sprite_TDDUG &MS_);
	void WEAPON_COLISION_TDDUG(WEAPON_TDDUG W_,uint8_t Nu_);
	uint8_t ANIM_OR(void);
	void PUT_ANIM_OR(uint8_t WA_);
	void Ou_suis_je(uint8_t &x_,uint8_t &y_);
private:
	uint8_t anim_or;
};

#endif // _CLASS_TDDUG_H
