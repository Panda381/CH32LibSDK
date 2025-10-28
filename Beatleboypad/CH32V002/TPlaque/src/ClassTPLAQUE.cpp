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

#include "../include.h"

//PUBLIC:VAR
int8_t RD_TPLAQUE=0;
uint8_t RNDPOS_TPLAQUE=19;

uint8_t RND_POS_TPLAQUE(void)
{
	RNDPOS_TPLAQUE=(RNDPOS_TPLAQUE!=85)?RNDPOS_TPLAQUE+11:19;
	return RNDPOS_TPLAQUE;
}

int8_t RND_TPLAQUE(void)
{
	RD_TPLAQUE=(RD_TPLAQUE<11)?RD_TPLAQUE+1:0;
	return pgm_read_byte(&RnD_TPLAQUE[RD_TPLAQUE]);
}

/*
void Sound_TPLAQUE(uint8_t freq_,uint8_t dur)
{
	uint8_t t, t2;
	for (t=0;t<dur;t++)
	{
		digitalWrite(4,HIGH); 
		for (t2=0; t2<(255-freq_); t2++) _delay_us(1);
		digitalWrite(4,LOW);
		for (t2=0; t2<(255-freq_); t2++) _delay_us(1);
	}
}
*/

GAME_DATA_TPLAQUE GD;

int8_t Sprite_TPLAQUE::X(void) { return x; }
int8_t Sprite_TPLAQUE::Y(void) { return y; }
int8_t Sprite_TPLAQUE::ACTIVE(void) { return active; }
void Sprite_TPLAQUE::PUT_X(int8_t XX) { x=XX; }
void Sprite_TPLAQUE::PUT_Y(int8_t YY) { y=YY; }
void Sprite_TPLAQUE::PUT_ACTIVE(int8_t ACT) { active=ACT; }
int8_t Sprite_TPLAQUE::DIRECTION_X(void) { return direction_x; }
int8_t Sprite_TPLAQUE::DIRECTION_Y(void) { return direction_y; }
void Sprite_TPLAQUE::PUT_DIRECTION_X(int8_t D_X) { direction_x=D_X; }
void Sprite_TPLAQUE::PUT_DIRECTION_Y(int8_t D_Y) { direction_y=D_Y; }
//end sprite

//start Moving sprite
int8_t Moving_Sprite_TPLAQUE::SOMX(void) { return Som_x; }
int8_t Moving_Sprite_TPLAQUE::SOMY(void) { return Som_y; }
int8_t Moving_Sprite_TPLAQUE::SX(void) { return sx; }
int8_t Moving_Sprite_TPLAQUE::SY(void) { return sy; }
void Moving_Sprite_TPLAQUE::PUT_SX(int8_t SX_) { sx=SX_; }
void Moving_Sprite_TPLAQUE::PUT_SY(int8_t SY_) { sy=SY_; }
void Moving_Sprite_TPLAQUE::PUT_SOMX(int8_t PUT_SOMX_) { Som_x=PUT_SOMX_; }
void Moving_Sprite_TPLAQUE::PUT_SOMY(int8_t PUT_SOMY_) { Som_y=PUT_SOMY_; }
void Moving_Sprite_TPLAQUE::HAUT(void)
{
	int8_t T_SOMY=SOMY();
	if ((T_SOMY+(-GD.sp))<=-FOOD_ACCEL_SPEED_TPLAQUE)
	{
		PUT_SOMY((T_SOMY+(-GD.sp))+FOOD_ACCEL_SPEED_TPLAQUE);
		PUT_Y(Y()-1);
	}
	else
	{
		PUT_SOMY(T_SOMY+(-GD.sp));
	}
}
void Moving_Sprite_TPLAQUE::DROITE(void)
{
	int8_t T_SOMX=SOMX();
	if ((T_SOMX+GD.sp)>=FOOD_ACCEL_SPEED_TPLAQUE)
	{
		PUT_SOMX((T_SOMX+GD.sp)-FOOD_ACCEL_SPEED_TPLAQUE);
		PUT_X(X()+1);
	}
	else
	{
		PUT_SOMX(T_SOMX+GD.sp);
	}
}  

void Moving_Sprite_TPLAQUE::BAS(void)
{
	int8_t T_SOMY=SOMY();
	if ((T_SOMY+GD.sp)>=FOOD_ACCEL_SPEED_TPLAQUE)
	{
		PUT_SOMY((T_SOMY+GD.sp)-FOOD_ACCEL_SPEED_TPLAQUE);
		PUT_Y(Y()+1);
	}
	else
	{
		PUT_SOMY(T_SOMY+GD.sp);
	}
}

void Moving_Sprite_TPLAQUE::GAUCHE(void)
{
	int8_t T_SOMX=SOMX();
	if ((T_SOMX+(-GD.sp))<=-FOOD_ACCEL_SPEED_TPLAQUE)
	{
		PUT_SOMX((T_SOMX+(-GD.sp))+FOOD_ACCEL_SPEED_TPLAQUE);
		PUT_X(X()-1);
	}
	else
	{
		PUT_SOMX(T_SOMX+(-GD.sp));
	}
}
//end moving sprite

//start Food_sprite
void Food_Sprite_TPLAQUE::PUT_COLAPSED(uint8_t COL_) { colapsed=COL_; }
uint8_t Food_Sprite_TPLAQUE::COLAPSED(void) { return colapsed; }
void Food_Sprite_TPLAQUE::COPY_OBJ(Food_Sprite_TPLAQUE &T_OBJ)
{
	PUT_COLAPSED(1);
	PUT_START_POS(T_OBJ.START_POS()+11);
	PUT_X(T_OBJ.X()+11);
	PUT_Y(T_OBJ.Y());
	PUT_DIRECTION_X(T_OBJ.DIRECTION_X());
	PUT_DIRECTION_Y(T_OBJ.DIRECTION_Y());
	PUT_SOMX(T_OBJ.SOMX());
	PUT_SOMY(T_OBJ.SOMY());
}

void Food_Sprite_TPLAQUE::ADJUST_X(void)
{
	if (X()>(START_POS()))
		GAUCHE();
	else if (X()<(START_POS()))
		DROITE();
	else
	{
		if (START_POS()!=0)
		{
			PUT_START_POS(0);
			PUT_SOMX(0);
			PUT_SOMY(0);
			PUT_DIRECTION_X(0);
			switch(GD.up_down)
			{
			case(0):
				PUT_DIRECTION_Y(-1);
				PUT_SY(0);
				break;

			case(1):
				PUT_DIRECTION_Y(1);
				PUT_SY(0);
				break;

			default:
				break;
			}
		}
	}
}

uint8_t Food_Sprite_TPLAQUE::START_POS(void)
{
	return Start_Pos;
}

void Food_Sprite_TPLAQUE::PUT_START_POS(uint8_t x_t)
{
	Start_Pos=x_t;
}

void Food_Sprite_TPLAQUE::CREAT_FOOD(void)
{
	RESET_OBJ();
	if (START_POS()>55)
	{
		PUT_X(116);
	}
	else
	{
		PUT_X(-4);
	}
	switch(GD.up_down)
	{
	case(0):
		PUT_Y(46);
		break;

	case(1):
		PUT_Y(17);
		break;

	default:
		break;
	}
}

void Food_Sprite_TPLAQUE::RESET_OBJ(void)
{
	PUT_START_POS(RND_POS_TPLAQUE());
	PUT_COLAPSED(0);
	PUT_ACTIVE(1);
	PUT_DIRECTION_X(0);
	PUT_DIRECTION_Y(0);
	PUT_SOMX(0);
	PUT_SOMY(0);
}

void Food_Sprite_TPLAQUE::DISABLE_RESET(void)
{
	PUT_ACTIVE(0);
}

void Food_Sprite_TPLAQUE::MOVE_UPDATE()
{
	if (ACTIVE()==1)
	{
		if (START_POS()!=0)
		{
			ADJUST_X();
			ADJUST_X();
			ADJUST_X();
		}
		else
		{
			switch(DIRECTION_X())
			{
			case 0:
				break;

			case 1:
				DROITE();
				if (X()>116) PUT_X(6);
				break;

			case -1:
				GAUCHE();
				if (X()<6) PUT_X(116);
				break;

			default:
				break;
			}

			switch(DIRECTION_Y())
			{
			case 0:
				break;

			case 1:
				BAS();
				if (Y()>60) PUT_ACTIVE(0);
				break;

			case -1:
				HAUT();
				if (Y()<1) PUT_ACTIVE(0);
				break;

			default:
				break;
			}
		}
	}
}

//start Main sprite
void Main_Sprite_TPLAQUE::INIT(void)
{
	PUT_X(60);
	PUT_Y(38);
	PUT_ACTIVE(1);
	PUT_DIRECTION_Y(-1);
	PUT_DIRECTION_X(0);
	PUT_SOMX(0);
	PUT_SOMY(0);
	PUT_SX(0);
	PUT_SY(0);
}

void Main_Sprite_TPLAQUE::MHAUT(void)
{
	int8_t T_SOMY=SOMY();
	int8_t T_SY=SY();
	if (T_SY>-MAIN_ACCEL_SPEED_TPLAQUE) PUT_SY(T_SY-1);
	if ((T_SOMY+T_SY)<=0)
	{
		if ((T_SOMY+T_SY)<=-MAIN_ACCEL_SPEED_TPLAQUE)
		{
			PUT_SOMY((T_SOMY+T_SY)+MAIN_ACCEL_SPEED_TPLAQUE);
			PUT_Y(Y()-1);
		}
		else
		{	
			PUT_SOMY(T_SOMY+T_SY);
		}
	}
	else
		DECEL_Y();
	PUT_DIRECTION_Y(-1);
	LIMIT_CHECK();
}

void Main_Sprite_TPLAQUE::MDROITE(void)
{
	int8_t T_SOMX=SOMX();
	int8_t T_SX=SX();
	if (T_SX<MAIN_ACCEL_SPEED_TPLAQUE) PUT_SX(T_SX+1);
	if ((T_SOMX+T_SX)>=0)
	{
		if ((T_SOMX+T_SX)>=MAIN_ACCEL_SPEED_TPLAQUE)
		{
			PUT_SOMX((T_SOMX+T_SX)-MAIN_ACCEL_SPEED_TPLAQUE);
			PUT_X(X()+1);
		}
		else
		{
			PUT_SOMX(T_SOMX+T_SX);
		}
	}
	else
	{
		DECEL_X();
	}
	LIMIT_CHECK();
}
    
void Main_Sprite_TPLAQUE::MBAS(void)
{
	int8_t T_SOMY=SOMY();
	int8_t T_SY=SY();
	if (T_SY<MAIN_ACCEL_SPEED_TPLAQUE) PUT_SY(T_SY+1);
	if ((T_SOMY+T_SY)>=0)
	{
		if ((T_SOMY+T_SY)>=MAIN_ACCEL_SPEED_TPLAQUE)
		{
			PUT_SOMY((T_SOMY+T_SY)-MAIN_ACCEL_SPEED_TPLAQUE);
			PUT_Y(Y()+1);
		}
		else
		{
			PUT_SOMY(T_SOMY+T_SY);
		}
	}
	else
		DECEL_Y();
	PUT_DIRECTION_Y(1);
	LIMIT_CHECK();
}
    
void Main_Sprite_TPLAQUE::MGAUCHE(void)
{
	int8_t T_SOMX=SOMX();
	int8_t T_SX=SX();
	if (T_SX>-MAIN_ACCEL_SPEED_TPLAQUE) PUT_SX(T_SX-1);
	if ((T_SOMX+T_SX)<=0)
	{
		if ((T_SOMX+T_SX)<=-MAIN_ACCEL_SPEED_TPLAQUE)
		{
			PUT_SOMX((T_SOMX+T_SX)+MAIN_ACCEL_SPEED_TPLAQUE);
			PUT_X(X()-1);
		}
		else
		{
			PUT_SOMX(T_SOMX+T_SX);
		}
	}
	else
		DECEL_X();
	LIMIT_CHECK();
}
    
void Main_Sprite_TPLAQUE::DECEL_Y(void)
{
	int8_t T_SOMY=SOMY();
	int8_t T_SY=SY();
	if ((T_SOMY+T_SY)>=0)
	{
		if (T_SY>0) PUT_SY(T_SY-1);
		if ((T_SOMY+T_SY)>=MAIN_ACCEL_SPEED_TPLAQUE)
		{
			PUT_SOMY((T_SOMY+T_SY)-MAIN_ACCEL_SPEED_TPLAQUE);
			PUT_Y(Y()+1);
		}
		else
		{
			PUT_SOMY(T_SOMY+T_SY);
		}
	}
	else
	{
		if (T_SY<0) PUT_SY(T_SY+1);
		if ((T_SOMY+T_SY)<=-MAIN_ACCEL_SPEED_TPLAQUE)
		{
			PUT_SOMY((T_SOMY+T_SY)+MAIN_ACCEL_SPEED_TPLAQUE);
			PUT_Y(Y()-1);
		}
		else
		{
			PUT_SOMY(T_SOMY+T_SY);
		}
	}
	LIMIT_CHECK();
}

void Main_Sprite_TPLAQUE::DECEL_X(void)
{
	int8_t T_SOMX=SOMX();
	int8_t T_SX=SX();
	if ((T_SOMX+T_SX)>=0)
	{
		if (T_SX>0) PUT_SX(T_SX-1);
		if ((T_SOMX+T_SX)>=MAIN_ACCEL_SPEED_TPLAQUE)
		{
			PUT_SOMX((T_SOMX+T_SX)-MAIN_ACCEL_SPEED_TPLAQUE);
			PUT_X(X()+1);
		}
		else
		{
			PUT_SOMX(T_SOMX+T_SX);
		}
	}
	else
	{
		if (T_SX<0) PUT_SX(T_SX+1);
		if ((T_SOMX+T_SX)<=-MAIN_ACCEL_SPEED_TPLAQUE)
		{
			PUT_SOMX((T_SOMX+T_SX)+MAIN_ACCEL_SPEED_TPLAQUE);
			PUT_X(X()-1);
		}
		else
		{
			PUT_SOMX(T_SOMX+T_SX);
		}
	}
	LIMIT_CHECK();
}

void Main_Sprite_TPLAQUE::LIMIT_CHECK(void)
{
	if(X()<11)
	{
		PUT_X(11);
		PUT_SX(0);
		PUT_SOMX(0);
	}

	if(X()>108)
	{
		PUT_X(108);
		PUT_SX(0);
		PUT_SOMX(0);
	}

	if(Y()<17)
	{
		PUT_Y(17);
		PUT_SY(0);
		PUT_SOMY(0);
	}

	if(Y()>41)
	{
		PUT_Y(41);
		PUT_SY(0);
		PUT_SOMY(0);
	}

	if (Y()<18)
	{
		PUT_DIRECTION_Y(1);
	}

	if (Y()>40)
	{
		PUT_DIRECTION_Y(-1);
	}
} 
//end main sprite

//START WAPON_SPRITE
void Weapon_Sprite_TPLAQUE::Start(Main_Sprite_TPLAQUE Main_S_)
{
	if (ACTIVE()==0)
	{
		Sound_TPLAQUE(200,4);
		PUT_ACTIVE(1);
		PUT_Y(Main_S_.Y()+2);
	PUT_DIRECTION_Y(Main_S_.DIRECTION_Y());
	}
}

void Weapon_Sprite_TPLAQUE::Update(void)
{
	if (ACTIVE()>0)
	{
		switch(DIRECTION_Y())
		{
		case -1:
			PUT_Y(Y()-2);
			break;

		case 1:
			PUT_Y(Y()+2);
			break;
		}
	}
	if (COLLISION_DETECT()) PUT_ACTIVE(0);
}

uint8_t Weapon_Sprite_TPLAQUE::COLLISION_DETECT(void)
{
	if ((Y()<9)||(Y()>56)) return 1;
	return 0;
}
//END WAPON SPRITE
