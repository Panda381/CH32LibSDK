
#ifndef _GAME_H
#define _GAME_H

void FPS_Count_TD(uint8_t Ms_);
extern const size_t Size_TD;

typedef struct GAME_PLAY_VAR_
{
	uint8_t Speed_TD;
	uint8_t Tab_range;
	uint8_t Level_TD;
	uint8_t Total_Virus_In_level;
} GAME_PLAY_VAR;

typedef struct SPLITPILL_TD_
{
	uint8_t Stat;
} SPLITPILL_TD;

typedef struct PILL_TD_
{
	uint8_t Active;
	uint8_t InTab;
	int8_t GraphPosX;
	int8_t GraphPosY;
	uint8_t Gridx;
	uint8_t Gridy;
	uint8_t Vertical;
	SPLITPILL_TD PillPart1Preview;
	SPLITPILL_TD PillPart2Preview;
	SPLITPILL_TD PillPart1;
	SPLITPILL_TD PillPart2;
} PILL_TD;

typedef struct ELEMENT_TD_
{
	uint8_t CLR;
	uint8_t ScanHV;
	uint8_t ElementCount;
	uint8_t ElementStart;
	uint8_t ElementStop;
	uint8_t ElementType;
} ELEMENT_TD;

extern ELEMENT_TD Element_TD;
extern PILL_TD Pill_TD;
extern GAME_PLAY_VAR GameP_TD;

void setup();
void loop();
void Compile_LV_Display_TD(uint8_t *A10_, uint8_t *B1_, uint8_t NUMBER_);
void AdjustGamePlay(void);
void FirstCalculeDisplay_TD(void);
void COMPIL_SCORE_TD(void);
void Virus_Loupe_TD(void);
void SND_TDOC_TD(uint8_t Snd_);
void init_public_Var_For_New_game_TD(void);
void init_public_Var_For_New_Level_TD(void);
void TINYJOYPAD_UPDATE_TD(void);
void InitNewBackTab_TD(void);
void CopyItem2Delete_TD(uint8_t x_, uint8_t y_);
void NewStepLine_TD(void);
void ElementCounter_TD(uint8_t x_, uint8_t y_, uint8_t Element_);
void CheckCompletedLine_TD(void);
void ClearLine_TD(void);
uint8_t ReturnConectionType_TD(uint8_t Type_);
uint8_t ReturnType_TD(uint8_t Val_);
uint8_t CheckMatch_TD(int8_t x_, int8_t y_);
uint8_t ReturnCombinedPillDirection_TD(int8_t x_, int8_t y_, uint8_t Type_);
void SetSinglePill_TD(void);
void AnimPillShoot_TD(void);
void DropMode_TD(void);
void PillProcess_TD(void);
uint8_t DropPills_TD(void);
uint8_t GenerateSidePill_TD(uint8_t Side);
void GeneratenewPreviewPill_TD(void);
void InitNewPill_TD(uint8_t Act_);
uint8_t Select_TD(void);
uint8_t OrderSelect_TD(uint8_t Select_, uint8_t Chiffre_);
uint8_t GetElement_TD(size_t index_);
void init_RND_TD(void);
uint8_t CheckRotateIsPosible_TD(void);
void RotatePill_TD(void);
void SetPicDirection_TD(uint8_t Vertical_);
void FixPill_TD(void);
uint8_t CheckColision_TD(int8_t X_, int8_t Y_);
void ReturnScanLineY_TD(uint8_t *a, uint8_t *b, uint8_t y);
void ReturnScanLineX_TD(uint8_t *a, uint8_t x);
uint8_t ReturncorectPills_TD(uint8_t Val_);
uint8_t DrawNewPill_TD(uint8_t x, uint8_t y);
uint8_t SwitchRecupVirus_TD(uint8_t Type_);
uint8_t DrawTAB_TP(uint8_t x, uint8_t y);
uint8_t DrawPreviewPill_TD(uint8_t x, uint8_t y);
uint8_t DrawShadowPreviewPill_TD(uint8_t x, uint8_t y);
uint8_t DrawLoupe_TD(uint8_t x, uint8_t y);
uint8_t Draw_Score_TD(uint8_t x, uint8_t y);
void IntroFlip_TD(uint8_t Show_);
uint8_t DrawDisplayLV_TD(uint8_t x, uint8_t y);
void TinyFlip_TD(uint8_t PartialX_85_128, uint8_t PartialY_4_8);
void LevelClearedFlip_TD(void);

#endif // _GAME_H
