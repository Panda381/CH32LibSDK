
#ifndef _GAME_H
#define _GAME_H

#define FRAC_SHIFT	15		// number of fractional shifts
#define FRAC_MUL	(1<<FRAC_SHIFT)	// fractional multiplier
//#define TOFRAC(n) ((n)<<FRAC_SHIFT)	// convert integer number to fractional number
//#define TOINT(n) ((n)>>FRAC_SHIFT)	// convert fractional number to integer number
INLINE int TOFRAC(int n) { return n << FRAC_SHIFT; }
INLINE int TOINT(int n) { return (n < 0) ? ((n + FRAC_MUL - 1) >> FRAC_SHIFT) : (n >> FRAC_SHIFT); }

typedef struct GROUPE {
	uint8_t ANIMREFLECT;
	uint8_t launch;
	uint8_t Px;
	uint8_t Py;
	uint8_t BlocsGrid[6][5];
	int Ballxpos;		// float Ballxpos;
	int SIMBallxpos;	// float SIMBallxpos;
	int Ballypos;		// float Ballypos;
	int SIMBallypos;	// float SIMBallypos;
	int BallSpeedx;		// float BallSpeedx;
	int SIMBallSpeedx;	// float SIMBallSpeedx;
	int BallSpeedy;		// float BallSpeedy;
	int SIMBallSpeedy;	// float SIMBallSpeedy;
	int8_t TrackAngleOut;
	int Ballxposflip;	// float Ballxposflip;
	int Ballyposflip;	// float Ballyposflip;
	uint8_t BALLyDecal;
	uint8_t Ypos;
	uint8_t TrackBary;
	uint8_t TrackBaryDecal;
	uint8_t LEVEL;
	uint8_t LEVELSPEED;
	uint8_t live;
	uint8_t Frame;
} GROUPE;

void setup();
void RsVarNewGame(GROUPE *VAR);
void loop();
void PLAYMUSIC(void);
uint8_t BallMissing(GROUPE *VAR);
uint8_t CheckLevelEnded(GROUPE *VAR);
void UpdateBall(GROUPE *VAR);
void RecupeBALLPosForSIM(GROUPE *VAR);
void TestMoveBALL(GROUPE *VAR);
void SimulMove(uint8_t Sim,GROUPE *VAR);
uint8_t CheckCollisionBall(GROUPE *VAR);
uint8_t CheckCollisionWithBLOCK(GROUPE *VAR);
void RecupePositionOnGrid(GROUPE *VAR);
uint8_t RecupeXPositionOnGrid(GROUPE *VAR);
uint8_t RecupeYPositionOnGrid(GROUPE *VAR);
uint8_t CheckCollisionWithTRACKBAR(GROUPE *VAR);
void WriteBallMove(GROUPE *VAR);
void Tiny_Flip(uint8_t render0_picture1,GROUPE *VAR);
uint8_t PannelLevel(uint8_t X,uint8_t Y,GROUPE *VAR);
uint8_t Block(uint8_t X,uint8_t Y,GROUPE *VAR);
uint8_t RecupeDecalageY(int Valeur);
uint8_t Ball(uint8_t X,uint8_t Y,GROUPE *VAR);
uint8_t SplitSpriteDecalageY(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN);
uint8_t TrackBar(uint8_t X,uint8_t Y,GROUPE *VAR);
uint8_t PannelLive(uint8_t X,uint8_t Y,GROUPE *VAR);
uint8_t background(uint8_t X,uint8_t Y);
void Sound(uint8_t freq,uint8_t dur);
void LoadLevel(uint8_t Level,GROUPE *VAR);
void ResetVar(GROUPE *VAR);
void ResetBall(GROUPE *VAR);

#endif // _GAME_H
