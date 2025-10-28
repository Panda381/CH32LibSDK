
#ifndef _GAME_H
#define _GAME_H

//Public VAR
extern unsigned long currentMillis;
extern unsigned long MemMillis;
extern uint8_t RDLP;
extern uint8_t START_RDLP;

extern uint8_t REVERSE_TMISSILE;
extern uint8_t M10000_TMISSILE;
extern uint8_t M1000_TMISSILE;
extern uint8_t M100_TMISSILE;
extern uint8_t M10_TMISSILE;
extern uint8_t M1_TMISSILE;
extern uint16_t Scores_TMISSILE;
extern uint8_t SHOT_ADJ_TMISSILE;
extern uint8_t LEVEL_TMISSILE;

//CLASS DECLARATION
extern CLK RENEW;
extern CLK SPEED_MISSILE;
extern STATIC_SPRITE_ANIM_TMISSILE INTERCEPT[3];
extern STATIC_SPRITE_ANIM_TMISSILE DOME[NUM_of_DOME_TMISSILE];
extern LINE_TMISSILE Missile[NUM_of_MISSILE_TMISSILE];
extern CROSS Cross;
extern DEFENCE Dfence[3];
extern ARMY_TMISSILE ARM_TMISSILE;

void setup();
void loop();
uint8_t ALL_ANIM_END_TMISSILE(void);
void RESTORE_DOME_TMISSILE(void);
uint8_t Score_Dome_Munition_TMISSILE(void);
void ADJ_LEVEL_TMISSILE(uint8_t Level_);
void NEW_GAME_TMISSILE(void);
void NEXTLEVEL_TMISSILE(void);
void INC_SCORES_TMISSILE(void);
uint8_t UPDATE_ENGINE_TMISSILE(void);
void UPDATE_DOME_TMISSILE(void);
void UPDATE_Intercept_TMISSILE(void);
void Destroy_TMISSILE(uint8_t t_);
void Create_New_Intercept_TMISSILE(int8_t X_,int8_t Y_);
void NEW_POS_TMISSILE(int8_t *ST_,int8_t *END_);
void Start_RDLP_MIX(void);
void RDLP_MIX(void);
void UPDATE_DFENCE_TMISSILE(void);
void Renew_Shield_TMISSILE(int8_t x_END,int8_t y_END);
void REFRESH_TOPBAR_TMISSILE(void);
void RESET_ALL_MISSILE_TMISSILE(void);
void RENEW_MISSILE(void);
uint8_t RECUP_LINE_TMISSILE(uint8_t xPASS,uint8_t yPASS);
uint8_t RECUP_DOME_TMISSILE(uint8_t xPASS,uint8_t yPASS);
uint8_t RECUP_CROSS_TMISSILE(uint8_t xPASS,uint8_t yPASS);
uint8_t RECUP_SHIELD_TMISSILE(uint8_t xPASS,uint8_t yPASS);
uint8_t RECUPE_TOPBAR_TMISSILE(uint8_t xPASS,uint8_t yPASS);
uint8_t RECUP_INTERCEPT_TMISSILE(uint8_t xPASS,uint8_t yPASS);
uint8_t Recupe_TMISSILE(uint8_t xPASS,uint8_t yPASS);
uint8_t BACKGROUND_TMISSILE(uint8_t xPASS,uint8_t yPASS);
void Tiny_Flip_TMISSILE(uint8_t ST_,uint8_t ED_,uint8_t XS_);
void INTRO_TMISSILE(uint8_t FL_);
uint8_t RECUPE_INTRO_TMISSILE(uint8_t xPASS,uint8_t yPASS,uint8_t Fl_);
uint8_t RECUP_PANEL_TMISSILE(uint8_t xPASS,uint8_t yPASS);
uint8_t INVENTORY_TMISSILE(uint8_t xPASS);
uint8_t MUNITION_TMISSILE(uint8_t xPASS);
uint8_t NUMERIC_TMISSILE(uint8_t xPASS);
uint8_t recupe_SCORES_TMISSILE(uint8_t xPASS);
void COMPIL_SCO_TMISSILE(void);
void SNDBOX_TMISSILE(uint8_t Snd_);

#endif // _GAME_H
