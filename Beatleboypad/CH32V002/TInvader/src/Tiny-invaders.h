//   >>>>>  T-I-N-Y  I-N-V-A-D-E-R-S v3.1 for ATTINY85  GPLv3 <<<<
//                     Tinyjoypad rev2 compatible
//                   Programmer: Daniel C 2018-2021
//              Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                    https://www.tinyjoypad.com
//         https://sites.google.com/view/arduino-collection

//  Tiny Invaders v3.1 is free software: you can redistribute it and/or modify
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

#ifndef _TINY_INVADERS_H
#define _TINY_INVADERS_H

#define MAXLEVELSHIELDED 3

typedef struct SPACE
{
	int8_t UFOxPos;
	uint8_t oneFrame;
	uint8_t MonsterShoot[2];
	int8_t MonsterGrid[5][6];
	uint8_t Shield[6];                         
	uint8_t ScrBackV;
	int8_t MyShootBall;
	uint8_t MyShootBallxpos;
	uint8_t MyShootBallFrame;
	uint8_t anim;
	uint8_t frame;
	uint8_t PositionDansGrilleMonsterX;
	uint8_t PositionDansGrilleMonsterY;
	uint8_t MonsterFloorMax;
	uint8_t MonsterOffsetGauche;
	uint8_t MonsterOffsetDroite;
	uint8_t MonsterGroupeXpos;
	uint8_t MonsterGroupeYpos;
	uint8_t DecalageY8;
	uint8_t frameMax;
	uint8_t Direction;
} SPACE;

// var public
extern uint8_t Live;
extern uint8_t ShieldRemoved;
extern uint8_t MONSTERrest;
extern uint8_t LEVELS;
extern uint8_t SpeedShootMonster;
extern uint8_t ShipDead;
extern uint8_t ShipPos;

// fin var public

void setup();
void LoadMonstersLevels(int8_t Levels,SPACE *space);
void loop();
void SnD(int8_t Sp_,uint8_t SN);
void SpeedControle(SPACE *space);
void GRIDMonsterFloorY(SPACE *space);
uint8_t LivePrint(uint8_t x,uint8_t y);
void Tiny_Flip(uint8_t render0_picture1,SPACE *space);
uint8_t UFOWrite(uint8_t x,uint8_t y,SPACE *space);
void UFOUpdate(SPACE *space);
void ShipDestroyByMonster(SPACE *space);
void MonsterShootupdate(SPACE *space);
void MonsterShootGenerate(SPACE *space);
uint8_t MonsterShoot(uint8_t x,uint8_t y,SPACE *space);
uint8_t ShieldDestroy(uint8_t Origine,uint8_t VarX,uint8_t VarY,SPACE *space);
void ShieldDestroyWrite(uint8_t BOOLWRITE,uint8_t line,SPACE *space,uint8_t Origine);
uint8_t MyShield(uint8_t x,uint8_t y,SPACE *space);
uint8_t ShieldBlitz(uint8_t Part,uint8_t LineSH );
uint8_t BOOLREAD(uint8_t SHnum,uint8_t LineSH,SPACE *space );
void RemoveExplodOnMonsterGrid(SPACE *space);
uint8_t background(uint8_t x,uint8_t y,SPACE *space);
uint8_t Vesso(uint8_t x,uint8_t y,SPACE *space);
void UFO_Attack_Check(uint8_t x,SPACE *space);
uint8_t MyShoot(uint8_t x,uint8_t y,SPACE *space);
void Monster_Attack_Check(SPACE *space);
int8_t OuDansLaGrilleMonster(uint8_t x,uint8_t y,SPACE *space);
uint8_t SplitSpriteDecalageY(uint8_t Input,uint8_t UPorDOWN,SPACE *space);
uint8_t Murge_Split_UP_DOWN(uint8_t x,SPACE *space);
uint8_t WriteMonster14(uint8_t x);
uint8_t Monster(uint8_t x,uint8_t y,SPACE *space);
uint8_t MonsterRefreshMove(SPACE *space);
void Sound(uint8_t freq,uint8_t dur);
void VarResetNewLevel(SPACE *space);

#endif // _TINY_INVADERS_H
