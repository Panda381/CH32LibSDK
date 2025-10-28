
#ifndef _GAME_H
#define _GAME_H

typedef struct PERSONAGE_
{
	uint8_t anim;//=0;
	uint8_t dead;//=0;
	uint8_t type;//=0;
	uint8_t DirectionAnim;//=0;
	uint8_t DirectionH;//=0;
	uint8_t DirectionV;//=0;
	uint8_t x;//=0;
	uint8_t Decalagey;//=0;
	int8_t y;//=0;
	uint8_t switchanim;//=0;
} PERSONAGE;

void LoadLevel(uint8_t LeveL);
void ResetVar(PERSONAGE * Sprite);
void resetMonster(PERSONAGE *Sprite);
void resetBomb(void);
void setup();
void StartGame(void);
void loop();
uint8_t CheckLevelEnded(PERSONAGE *Sprite);
void DeadSong(void);
void DestroyBloc(void);
void DestroyEnemy(PERSONAGE *Sprite);
uint8_t COLLISION11(uint8_t x1,uint8_t y1,uint8_t w1,uint8_t h1,uint8_t x2,uint8_t y2,uint8_t w2,uint8_t h2);
uint8_t CollisionTiny2Caracter(PERSONAGE *Sprite);
void RefreshCaracter(PERSONAGE *Sprite);
uint8_t CheckCollisionWithBack(uint8_t SpriteCheck,uint8_t HorVcheck,PERSONAGE *Sprite);
uint8_t CheckCollisionWithBomb(uint8_t SpriteCheck,PERSONAGE *Sprite);
uint8_t CheckCollisionWithBlock(uint8_t SpriteCheck,PERSONAGE *Sprite);
uint8_t RecupeBacktoCompV(uint8_t SpriteCheck,PERSONAGE *Sprite);
uint8_t Trim(uint8_t Y1orY2,uint8_t TrimValue,uint8_t Decalage);
uint8_t ScanHRecupe(uint8_t UporDown,uint8_t Decalage);
uint8_t RecupeBacktoCompH(uint8_t SpriteCheck,PERSONAGE *Sprite);
void Tiny_Flip(uint8_t render0_picture1,PERSONAGE *Sprite);
uint8_t PrintLive(uint8_t x,uint8_t y);
uint8_t Explose(uint8_t x,uint8_t y);
uint8_t BombBlitz(uint8_t x,uint8_t y);
uint8_t BlockBomb(uint8_t x,uint8_t y,uint8_t Divx);
void BOOLWRITE0(uint8_t BoolNumber);
uint8_t BOOLREAD(uint8_t Numero);
uint8_t SplitSpriteDecalageY(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN);
uint8_t SpriteWrite(uint8_t x,uint8_t y,PERSONAGE *Sprite);
uint8_t return_if_sprite_present(uint8_t x,PERSONAGE  *Sprite,uint8_t SpriteNumber);
uint8_t background(uint8_t x,uint8_t y);
//void Sound(uint8_t freq,uint8_t dur);

#endif // _GAME_H
