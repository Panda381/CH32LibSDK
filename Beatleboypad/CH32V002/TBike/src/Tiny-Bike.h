
#ifndef _GAME_H
#define _GAME_H

#define FRAC_SHIFT	15		// number of fractional shifts
#define FRAC_MUL	(1<<FRAC_SHIFT)	// fractional multiplier
//#define TOFRAC(n) ((n)<<FRAC_SHIFT)	// convert integer number to fractional number
//#define TOINT(n) ((n)>>FRAC_SHIFT)	// convert fractional number to integer number
INLINE int TOFRAC(int n) { return n << FRAC_SHIFT; }
INLINE int TOINT(int n) { return (n < 0) ? ((n + FRAC_MUL - 1) >> FRAC_SHIFT) : (n >> FRAC_SHIFT); }

void ResetSprite(void);
void setup();
void intro_sound(void);
void End_Line_Win_sound(void);
void restore_start_line(void);
void Next_Level(void);
void RESET_FOR_NEW_GAME(void);
void loop();
void Pause1(void);
uint8_t GAME_PLAY(void);
void TIME_TRACK(void);
void PLANTAGE(void);
void Higher_adj(uint8_t test);
void dinamic_adj(void);
void GRAVITY_ADJ(void);
void JUMP_ADJ(void);
void CheckCollision(void);
uint8_t Trouver_Sprite_Collisionner(void);
void analise_minutieuse(void);
void ADD_LIVE(uint8_t SPR);
void CLIMB_ADJ3(void);
void CLIMB_ADJ0(void);
void Break_Gravity(void);
void CLIMB_ADJ1(void);
void CLIMB_ADJ2(void);
uint8_t RECUPE_X_SPRITE(uint8_t Type_Sprite);
uint8_t RECUPE_Y_SPRITE(uint8_t Type_Sprite);
uint8_t CHECK_SPEED_ADJ(int /*float*/ REC_INT);
void TRACK_RUN_ADJ(void);
uint8_t RECUPE_MAP_BYTE(const uint8_t *Level);
uint8_t SPLIT_MAP_BYTE(uint8_t BYTE,uint8_t L0_R1);
void RefreshPosSprite(void);
void INCREMENTE_SCROLL(void);
uint8_t CREATE_NEWSPRITE(void);
uint8_t BACKGROUND(uint8_t xPASS,uint8_t yPASS);
uint8_t TOPBACK(uint8_t xPASS,uint8_t yPASS);
uint8_t FOUL1(void);
uint8_t GRADIN23(uint8_t yPASS);
uint8_t TIRE4(void);
uint8_t ROAD567(uint8_t yPASS);
uint8_t TABLEAU8(uint8_t xPASS);
uint8_t Return_live(uint8_t xPASS);
uint8_t Return_time(uint8_t xPASS);
uint8_t Return_Progress(uint8_t xPASS);
void AdjustVarScroll(void);
//uint8_t Sprite2PAINTinBLACK;
uint8_t Recupe(uint8_t xPASS,uint8_t yPASS);
uint8_t BLITZ_SPRITE_MAP(uint8_t xPASS,uint8_t yPASS);
uint8_t BIGSTEP_SPRITE(uint8_t numSprite,uint8_t xPASS,uint8_t yPASS);
uint8_t MINISTEP_SPRITE(uint8_t numSprite,uint8_t xPASS,uint8_t yPASS);
uint8_t Plantage(uint8_t numSprite,uint8_t xPASS,uint8_t yPASS);
uint8_t HUILE_SPRITE(uint8_t numSprite,uint8_t xPASS,uint8_t yPASS);
uint8_t LINE_SPRITE(uint8_t numSprite,uint8_t xPASS,uint8_t yPASS);
uint8_t START_SPRITE(uint8_t numSprite,uint8_t xPASS,uint8_t yPASS);
uint8_t SPEED_SPRITE(uint8_t numSprite,uint8_t xPASS,uint8_t yPASS);
uint8_t NEW_LIVE(uint8_t numSprite,uint8_t xPASS,uint8_t yPASS);
uint8_t BIKE_SPRITE(uint8_t xPASS,uint8_t yPASS);
uint8_t blitzSprite(int8_t xPos,int8_t yPos,uint8_t xPASS,uint8_t yPASS,uint8_t FRAME,const uint8_t *SPRITES);
void RecupeDecalageY(uint8_t Valeur);
uint8_t SplitSpriteDecalageY(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN);
void Tiny_Flip(uint8_t MODE);
//void Sound(uint8_t freq,uint8_t dur);

#endif // _GAME_H
