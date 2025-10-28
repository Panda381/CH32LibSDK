//      >>>>>  T-I-N-Y  A-R-K-A-N-O-I-D for ATTINY85  GPL v3 <<<<
//                Programmer: Daniel Champagne 2018-2021
//                 Contact EMAIL: phoenixbozo@gmail.com
//           https://sites.google.com/view/arduino-collection

//  Tiny ARKANOID is free software: you can redistribute it and/or modify
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

//#include "FastTinyDriver.h"
#include "spritebank.h"

// var public
// fin var public

// Game setup
void setup()
{
/*
	TinyOLED_init();
	pinMode(1,INPUT);
	pinMode(4,OUTPUT);
	pinMode(A0,INPUT); 
	pinMode(A3,INPUT);
*/
}

// Reset variables for a new game
void RsVarNewGame(GROUPE *VAR)
{
	VAR->LEVELSPEED=16;
	VAR->LEVEL=1;
	VAR->live=3;
	VAR->ANIMREFLECT=0;
	LoadLevel(0,VAR);
}

// Main program loop
void loop()
{
	GROUPE VARIABLE;
NEWGAME:
	DrawClear();
	Tiny_Flip(1,&VARIABLE);
	while(1)
	{
		if (BUTTON_DOWN) break;
	}
	while(1) { if (BUTTON_UP) break; }
	RsVarNewGame(&VARIABLE);
	Tiny_Flip(2,&VARIABLE);
	PLAYMUSIC();
	LoadLevel(VARIABLE.LEVEL-1,&VARIABLE);
	goto ONE;

NEXTLEVEL:
	Sound(60,100);
	Sound(80,100);
	Sound(100,100);
	Sound(120,100);
	Sound(140,100);
	if (VARIABLE.LEVELSPEED>8) VARIABLE.LEVELSPEED -= 2;
	Tiny_Flip(2,&VARIABLE);
	delay(400);
	ResetVar(&VARIABLE);
	VARIABLE.LEVEL++;
	goto ONE;

RESTARTLEVEL:
	Sound(200,100);
	Sound(150,100);
	Sound(100,100);
	Sound(50,100);
	if (VARIABLE.live>0) VARIABLE.live--; else goto NEWGAME;

ONE:
	ResetBall(&VARIABLE);

	while(1)
	{
		if (VARIABLE.Frame%8==0)
		{
			// down
			if (KeyPressed(KEY_DOWN)) //(analogRead(A3)>=750)&&(analogRead(A3)<950))
			{
				if (VARIABLE.TrackBaryDecal<7)
				{
					if (VARIABLE.TrackBaryDecal+(VARIABLE.TrackBary*8)<44)
					{
						VARIABLE.TrackBaryDecal++;
					}
				}
				else
				{
					VARIABLE.TrackBaryDecal=0;
					VARIABLE.TrackBary++;
				}
			}

			// up
			if (KeyPressed(KEY_UP)) //(analogRead(A3)>500)&&(analogRead(A3)<750))
			{
				if (VARIABLE.TrackBaryDecal>0)
				{
					if (VARIABLE.TrackBaryDecal+(VARIABLE.TrackBary*8)>4)
					{
						VARIABLE.TrackBaryDecal--;
					}
				}
				else
				{
					VARIABLE.TrackBaryDecal=7;
					VARIABLE.TrackBary--;
				}
			}

			if ((VARIABLE.launch==0)&&(KeyPressed(KEY_A)/*digitalRead(1)==LOW*/)) VARIABLE.launch=1;

			if (VARIABLE.launch==0)
			{
				VARIABLE.Ballypos=TOFRAC(((VARIABLE.TrackBary*8)+VARIABLE.TrackBaryDecal)+10);
				VARIABLE.SIMBallypos=VARIABLE.Ballypos;
			}
		}

		if ((VARIABLE.Frame%VARIABLE.LEVELSPEED==0)) UpdateBall(&VARIABLE);

		if (VARIABLE.Frame%32==0) Tiny_Flip(0,&VARIABLE);

		if (VARIABLE.Frame==48)
		{
			if (VARIABLE.ANIMREFLECT<3) VARIABLE.ANIMREFLECT++;

			if (BallMissing(&VARIABLE)) goto RESTARTLEVEL;

			if (CheckLevelEnded(&VARIABLE)) goto NEXTLEVEL;
		}

		if (VARIABLE.Frame<64) VARIABLE.Frame++; else VARIABLE.Frame=1;

		WaitUs(500);
	}
}

////////////////////////////////// main end /////////////////////////////////

void PLAYMUSIC(void)
{
	uint8_t t;
	for (t=0;t<92;t=t+2)
	{
		Sound(pgm_read_byte(&Music1[t]),(pgm_read_byte(&Music1[t+1])-100));
	}
}

uint8_t BallMissing(GROUPE *VAR)
{
	if (VAR->Ballxpos<0) return 1;
	return 0; 
}

uint8_t CheckLevelEnded(GROUPE *VAR)
{
	uint8_t h,v,res=1;
	for(v=0;v<5;v++)
	{
		for(h=0;h<6;h++)
		{
			if ((VAR->BlocsGrid[h][v]!=255)&&(VAR->BlocsGrid[h][v]!=5)) res=0;
		}
	}
	return res;
}

void UpdateBall(GROUPE *VAR)
{
	VAR->TrackAngleOut=0;
	for (uint8_t T1=0;T1<=6;T1++)
	{
		RecupeBALLPosForSIM(VAR);
		if (VAR->launch==0) break;
		SimulMove(T1,VAR);
		TestMoveBALL(VAR);
		if (CheckCollisionBall(VAR)==0) break;
	}
	WriteBallMove(VAR);
}

void RecupeBALLPosForSIM(GROUPE *VAR)
{
	VAR->SIMBallxpos=VAR->Ballxpos;
	VAR->SIMBallypos=VAR->Ballypos;
	VAR->SIMBallSpeedx=VAR->BallSpeedx;
	VAR->SIMBallSpeedy=VAR->BallSpeedy;
}

void TestMoveBALL(GROUPE *VAR)
{
	VAR->SIMBallxpos=VAR->SIMBallxpos+VAR->SIMBallSpeedx;
	VAR->SIMBallypos=VAR->SIMBallypos+VAR->SIMBallSpeedy;
}

void SimulMove(uint8_t Sim,GROUPE *VAR)
{
	switch(Sim)
	{
	case (0):
		VAR->SIMBallSpeedx=VAR->BallSpeedx;
		VAR->SIMBallSpeedy=VAR->BallSpeedy;
		break;

	case (1):
		VAR->SIMBallSpeedx=-VAR->BallSpeedx;
		VAR->SIMBallSpeedy=VAR->BallSpeedy;
		break;

	case (2):
		VAR->SIMBallSpeedx=VAR->BallSpeedx;
		VAR->SIMBallSpeedy=-VAR->BallSpeedy;
		break;

	case (3):
		VAR->SIMBallSpeedx=-VAR->BallSpeedx;
		VAR->SIMBallSpeedy=-VAR->BallSpeedy;
		break;

	case (4):
		VAR->SIMBallSpeedx=-VAR->BallSpeedy;
		VAR->SIMBallSpeedy=-VAR->BallSpeedx;
		break;

	case (5):
		VAR->SIMBallxpos=VAR->Ballxpos+TOFRAC(1);
		VAR->SIMBallypos=VAR->Ballypos;
		VAR->SIMBallSpeedx=TOFRAC(-1);
		VAR->SIMBallSpeedy=TOFRAC(1);
		break;

	case (6):
		VAR->SIMBallxpos=VAR->Ballxpos+TOFRAC(1);
		VAR->SIMBallypos=VAR->Ballypos;
		VAR->SIMBallSpeedx=TOFRAC(-1);
		VAR->SIMBallSpeedy=TOFRAC(-1);
		break;

	default:
		break;
	}
}

uint8_t CheckCollisionBall(GROUPE *VAR)
{
	if (VAR->SIMBallxpos>TOFRAC(106)) return 1;
	if (VAR->SIMBallypos>TOFRAC(59)) return 1;
	if (VAR->SIMBallypos<TOFRAC(4)) return 1;
	if (CheckCollisionWithTRACKBAR(VAR))
	{
		Sound(60,10);
		return 1;
	}
	if (CheckCollisionWithBLOCK(VAR)) return 1;
	return 0;
}

uint8_t CheckCollisionWithBLOCK(GROUPE *VAR)
{
	RecupePositionOnGrid(VAR);
	if ((VAR->Px==255)||(VAR->Py==255)) return 0;
	if (VAR->BlocsGrid[VAR->Py][VAR->Px]==5)
	{
		Sound(210,50);
		VAR->ANIMREFLECT=0;
		return 1;
	}
	if (VAR->BlocsGrid[VAR->Py][VAR->Px]==255) return 0;
	Sound(150,10);
	VAR->BlocsGrid[VAR->Py][VAR->Px]=255;
	return 1;
}

void RecupePositionOnGrid(GROUPE *VAR)
{
	VAR->Px=RecupeXPositionOnGrid(VAR);
	VAR->Py=RecupeYPositionOnGrid(VAR);
}

uint8_t RecupeXPositionOnGrid(GROUPE *VAR)
{
	if ((VAR->SIMBallxpos>=TOFRAC(66))&&(VAR->SIMBallxpos<TOFRAC(72))) return 0;
	else if ((VAR->SIMBallxpos>=TOFRAC(72))&&(VAR->SIMBallxpos<TOFRAC(78))) return 1;
	else if ((VAR->SIMBallxpos>=TOFRAC(78))&&(VAR->SIMBallxpos<TOFRAC(84))) return 2;
	else if ((VAR->SIMBallxpos>=TOFRAC(84))&&(VAR->SIMBallxpos<TOFRAC(90))) return 3;
	else if ((VAR->SIMBallxpos>=TOFRAC(90))&&(VAR->SIMBallxpos<TOFRAC(96))) return 4;  
	return 255;
}

uint8_t RecupeYPositionOnGrid(GROUPE *VAR)
{
	if ((VAR->SIMBallypos>=TOFRAC(8))&&(VAR->SIMBallypos<TOFRAC(16))) return 0;
	else if ((VAR->SIMBallypos>=TOFRAC(16))&&(VAR->SIMBallypos<TOFRAC(23))) return 1;
	else if ((VAR->SIMBallypos>=TOFRAC(23))&&(VAR->SIMBallypos<TOFRAC(31))) return 2;
	else if ((VAR->SIMBallypos>=TOFRAC(31))&&(VAR->SIMBallypos<TOFRAC(40))) return 3;
	else if ((VAR->SIMBallypos>=TOFRAC(40))&&(VAR->SIMBallypos<TOFRAC(48))) return 4; 
	else if ((VAR->SIMBallypos>=TOFRAC(48))&&(VAR->SIMBallypos<TOFRAC(55))) return 5;   
	return 255;
}

uint8_t CheckCollisionWithTRACKBAR(GROUPE *VAR)
{
	int TRACK=TOFRAC((VAR->TrackBary*8)+VAR->TrackBaryDecal);
	if ((VAR->SIMBallxpos>TOFRAC(6))||(VAR->SIMBallxpos<TOFRAC(5))) return 0;
	if (TRACK>VAR->SIMBallypos) return 0;
	if ((TRACK+TOFRAC(16))<VAR->SIMBallypos) return 0;
	VAR->TrackAngleOut=TOINT(((VAR->SIMBallypos-TRACK)*200)/16)-100;
	return 1;
}

void WriteBallMove(GROUPE *VAR)
{
	int CORECTIONY=(VAR->SIMBallSpeedy)+(TOFRAC(VAR->TrackAngleOut)/100);
	if (CORECTIONY<TOFRAC(-1)) CORECTIONY=TOFRAC(-1);
	if (CORECTIONY>TOFRAC(1)) CORECTIONY=TOFRAC(1);
	VAR->Ballxpos=VAR->SIMBallxpos;
	VAR->Ballypos=VAR->SIMBallypos;
	VAR->BallSpeedx=VAR->SIMBallSpeedx;
	VAR->BallSpeedy=CORECTIONY;
	VAR->BALLyDecal=RecupeDecalageY(VAR->Ballypos-TOFRAC(1));
	VAR->Ypos=TOINT((VAR->Ballypos/*-TOFRAC(1)*/)/8);
}

void Tiny_Flip(uint8_t render0_picture1,GROUPE *VAR)
{
	uint8_t y,x; 
	for (y = 0; y < 8; y++)
	{ 
		ssd1306_selectPage(y);
		for (x = 0; x < 128; x++)
		{
			if (render0_picture1==0)
			{
				i2c_write(Block(x,y,VAR)|Ball(x,y,VAR)|TrackBar(x,y,VAR)|background(x,y)|PannelLive(x,y,VAR)|PannelLevel(x,y,VAR));
			}
			else if (render0_picture1==1)
			{
				i2c_write(pgm_read_byte(&MAIN[x+(y*128)]));
			}
			else if (render0_picture1==2)
			{
				i2c_write(background(x,y));
			}
		}
		i2c_stop();
	}
}

uint8_t PannelLevel(uint8_t X,uint8_t Y,GROUPE *VAR)
{
	if ((Y<5)||(Y>6)||(X<117)||(X>123)) return 0x00;
#define VAl10 (VAR->LEVEL/10)
#define VAl01 (VAR->LEVEL-(VAl10*10))
	if (Y==5)
		return (pgm_read_byte(&DIGITAL[(X-117)+(VAl10*7)]));
	else if (Y==6) return (pgm_read_byte(&DIGITAL[(X-117)+(VAl01*7)]));
	return 0x00;
}

uint8_t Block(uint8_t X,uint8_t Y,GROUPE *VAR)
{
	uint8_t XValue=255;
	if ((X>=67)&&(X<97)&&(Y>=1)&&(Y<=6))
	{
		if ((X>=67)&&(X<73)) XValue=0;
		else if ((X>=73)&&(X<79)) XValue=1;
		else if ((X>=79)&&(X<85)) XValue=2;
		else if ((X>=85)&&(X<91)) XValue=3;
		else if ((X>=91)&&(X<97)) XValue=4;
		if (XValue==255) return 0x00;
		//uint8_t XValue=((X-67)/6);
		if (VAR->BlocsGrid[(Y-1)][XValue]==255) return 0x00;
		if (VAR->BlocsGrid[(Y-1)][XValue]==5)
		{
			return pgm_read_byte(&BLOCKREFLECT[((X-67)-(XValue*6))+(VAR->ANIMREFLECT*6)])
				| pgm_read_byte(&BLOCK[((X-67)-(XValue*6))+((VAR->BlocsGrid[(Y-1)][XValue])*6)]);
		}
		return pgm_read_byte(&BLOCK[((X-67)-(XValue*6))+((VAR->BlocsGrid[(Y-1)][XValue])*6)]);
	}
	return 0x00;
}

uint8_t RecupeDecalageY(int Valeur)
{
	while(Valeur>TOFRAC(7)) Valeur=Valeur-TOFRAC(8);
	return (u8)TOINT(Valeur);
}

uint8_t Ball(uint8_t X,uint8_t Y,GROUPE *VAR)
{
#define BALLXPOS (VAR->Ballxpos-TOFRAC(1))
#define BALLYPOS (VAR->Ballypos-TOFRAC(1))
	if (Y<VAR->Ypos) return 0x00;
	if (Y>(VAR->Ypos+1)) return 0x00;
	if ((X-(uint8_t)TOINT(BALLXPOS))<0) return 0x00;
	if (TOFRAC(X)<BALLXPOS) return 0x00;
	if (TOFRAC(X)>BALLXPOS+TOFRAC(2)) return 0x00;
	if (VAR->BALLyDecal==0)
	{
		if (Y==VAR->Ypos) return (pgm_read_byte(&BALL[(X-(uint8_t)TOINT(BALLXPOS))]));
	}
	else
	{
		uint8_t DECAL=RecupeDecalageY(BALLYPOS);
		if (Y==VAR->Ypos) return SplitSpriteDecalageY(DECAL,pgm_read_byte(&BALL[(X-(uint8_t)TOINT(BALLXPOS))]),1);
		if (Y==(VAR->Ypos)+1) return SplitSpriteDecalageY(DECAL,pgm_read_byte(&BALL[(X-(uint8_t)TOINT(BALLXPOS))]),0);
	}
	return 0x00;
}

uint8_t SplitSpriteDecalageY(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN)
{
	if (UPorDOWN)
		return Input<<decalage;
	else
		return Input>>(8-decalage);
}

uint8_t TrackBar(uint8_t X,uint8_t Y,GROUPE *VAR)
{
	if (X>6) return 0;
	if (X<3) return 0;
	if (Y>=(3+VAR->TrackBary)) return 0;
	if (Y<(VAR->TrackBary)) return 0;
	if (VAR->TrackBaryDecal==0)
	{
		if (Y!=VAR->TrackBary+2) return (pgm_read_byte(&TRACKBAR[(X-3)+((Y-VAR->TrackBary)*4)]));
	}
	else
	{
		if (Y==VAR->TrackBary)
			return SplitSpriteDecalageY(VAR->TrackBaryDecal,pgm_read_byte(&TRACKBAR[(X-3)]),1);
		else if (Y==VAR->TrackBary+1)
			return SplitSpriteDecalageY(VAR->TrackBaryDecal,pgm_read_byte(&TRACKBAR[(X-3)]),0)|SplitSpriteDecalageY(VAR->TrackBaryDecal,pgm_read_byte(&TRACKBAR[(X-3)+4]),1);
		else if ((Y==VAR->TrackBary+2)&&(VAR->TrackBaryDecal!=0))
			return SplitSpriteDecalageY(VAR->TrackBaryDecal,pgm_read_byte(&TRACKBAR[(X-3)+4]),0);
	}
	return 0x00;
}

uint8_t PannelLive(uint8_t X,uint8_t Y,GROUPE *VAR)
{
	if ((Y<1)||(Y>VAR->live)||(X>121)||(X<119)) return 0x00;
	return (pgm_read_byte(&LIVE[X-119]));
}

uint8_t SWIFT_TEXTURE=0;
uint8_t background(uint8_t X,uint8_t Y)
{ 
	if (X==0) SWIFT_TEXTURE=0;
	if (X<=105)
	{
		if (SWIFT_TEXTURE<14) SWIFT_TEXTURE++; else SWIFT_TEXTURE=0;
		switch(Y)
		{
		case 0:
			return pgm_read_byte(&back_UP[X]);
			break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			return pgm_read_byte(&texture[SWIFT_TEXTURE]);
			break;

		case 7:
			return pgm_read_byte(&back_DOWN[X]);
			break;

		default:
			break;  
		}

	}
	else
	{
		return pgm_read_byte(&back_RIGHT[(X-106)+(Y*22)]);
	}
	return 0x00;
}

void LoadLevel(uint8_t Level,GROUPE *VAR)
{
	uint8_t a,b;
	for(b=0;b<5;b++)
	{
		for(a=0;a<6;a++)
		{
			VAR->BlocsGrid[a][b]=pgm_read_byte(&LEVEL[(Level*30)+b+(a*5)]);
		}
	}
}

void ResetVar(GROUPE *VAR)
{
	uint8_t f=VAR->LEVEL;
	while(1)
	{
		if (f>4) f=f-5; else break;
	}
	LoadLevel(f,VAR);
	VAR->launch=0;
}

void ResetBall(GROUPE *VAR)
{
	VAR->ANIMREFLECT=0;
	VAR->TrackBary=2;
	VAR->TrackBaryDecal=4;
	VAR->Ballxpos=TOFRAC(8);
	VAR->SIMBallxpos=TOFRAC(8);
	VAR->Ballypos=TOFRAC(32);
	VAR->SIMBallypos=TOFRAC(32);
	VAR->BallSpeedx=TOFRAC(1);
	VAR->SIMBallSpeedx=TOFRAC(1);
	if (VAR->Frame>32)
	{
		VAR->BallSpeedy=TOFRAC(41)/100;
		VAR->SIMBallSpeedy=TOFRAC(41)/100;
	}
	else
	{
		VAR->BallSpeedy=TOFRAC(47)/100;
		VAR->SIMBallSpeedy=TOFRAC(47)/100;  
	}
	VAR->launch=0;
}
