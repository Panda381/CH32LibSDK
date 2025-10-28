
#ifndef _GAME_H
#define _GAME_H

#define MAX_ENEMY_TDDUG 4

//  PUBLIC OBJ
extern Main_Sprite_TDDUG DUG_TDDUG;
extern WEAPON_TDDUG W_TDDUG[2];
extern Enemy_Sprite_TDDUG ENEMY_DDUG[MAX_ENEMY_TDDUG];

void setup();
void loop();
void RESET_ALL_GD_TDDUG(void);
void RESET_WEAPON_TDDUG(void);
void LOAD_ENEMY_POS_TDDUG(void);
void LOAD_LEVEL_TDDUG(uint8_t Lev_);
void NEWGAME_TDDUG(void);
void NEXTLEVEL_TDDUG(void);
void Trigger_adj_TDDUG(void);
void SND_TDDUG(uint8_t Val_);
void SND_DDUG(void);
void SCORES_ADD_TDDUG(void);
void COMPILING_TDDUG(void);
void DLAY(void);
uint8_t GamePlay_TDDUG(void);
void HowManyEnemy_TDDUG(void);
uint8_t Universal_TDDUG(int8_t ax,int8_t ay,int8_t aw,int8_t ah,int8_t bx,int8_t by,int8_t bw,int8_t bh);
void Check_Collision_TDDUG(void);
void ADJUST_FRAME_MAIN_DDUG(void);
void TL_ENEMY_TDDUG(void);
uint8_t Check_Balistic_Colid_TDDUG(void);
int8_t TrackX_TDDUG(int8_t t_);
int8_t TrackY_TDDUG(int8_t t_);
void UPDATE_ENEMY_TDDOG(void);
void Colapse_Enemy_Anim_TDDUG(void);
uint8_t RECUPE_ENEMY_BIG_TDDUG(uint8_t SPR_);
uint8_t RECUPE_ENEMY_FRAME_TDDUG(uint8_t SPR_);
void Adjust_main_speed_TDDUG(uint8_t RT_);
void UPDATE_PANNEL_TDDUG(uint8_t t_);
void COMPIL_SCO_TDDUG(void);
uint8_t READ_GRID_TDDUG(int8_t X_,int8_t Y_);
uint8_t WRITE_GRID_TDDUG(int8_t X_,int8_t Y_);
int8_t RND_TDDUG(void);
void ANIM_UPDATE_MAIN_TDDUG(uint8_t Direct_);
uint8_t blitzSprite_TDDUG(int8_t xPos,int8_t yPos,uint8_t xPASS,uint8_t yPASS,uint8_t FRAME,const uint8_t *SPRITES);
uint8_t BACK_TDDUG(uint8_t xPASS,uint8_t yPASS);
void ADJUST_LIVE_COMP_TDDUG(void);
uint8_t RECUPE_LIVE_TDDUG(uint8_t xPASS,uint8_t yPASS);
uint8_t BACKGROUND_TDDUG(uint8_t xPASS,uint8_t yPASS);
uint8_t MAIN_TDDUG(uint8_t xPASS,uint8_t yPASS);
uint8_t RECUPE_ENEMY_TDDUG(uint8_t xPASS,uint8_t yPASS);
uint8_t RECUPE_WEAPON_TDDUG(uint8_t xPASS,uint8_t yPASS);
uint8_t Recupe_TDDUG(uint8_t xPASS,uint8_t yPASS);
uint8_t SplitSpriteDecalageY_TDDUG(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN);
int8_t RecupeLineY_TDDUG(int8_t Valeur);
uint8_t RecupeDecalageY_TDDUG(uint8_t Valeur);
void Tiny_Flip_TDDUG(uint8_t Select_,uint8_t Blink_,uint8_t Maxx_,uint8_t St_y,uint8_t Ed_y);
uint8_t RECUPE_START_TDDUG(uint8_t xPASS,uint8_t yPASS,uint8_t Blink_);
uint8_t recupe_SCORES_TDDUG(uint8_t xPASS,uint8_t yPASS,int8_t Pos_);
uint8_t SPEED_BLITZ_TDDUG(int8_t xPos,int8_t yPos,uint8_t xPASS,uint8_t yPASS,uint8_t FRAME,const uint8_t *SPRITES);
//void Sound_TDDUG(uint8_t freq_,uint8_t dur);

#endif // _GAME_H
