
// ****************************************************************************
//
//                           Graphics and tables
//
// ****************************************************************************

#include "../include.h"

// pet default names
const char* const PetDefName[BASENUM] = {
	"Pimikotchi",		// CAT_INX	1	// cat
	"Pimishinu",		// DOG_INX	2	// dog
	"Pimibaku",		// BUNNY_INX	3	// bunny
	"Pimihamu",		// HAMSTER_INX	4	// hamster
	"Pimitori",		// BIRD_INX	5	// bird
	"Pimiryu",		// DRAGON_INX	6	// dragon
};

// pet eggs
const u8* const ImgEggList[BASENUM] = {
	ImgEggCat,	// CAT_INX	1	// cat
	ImgEggDog,	// DOG_INX	2	// dog
	ImgEggBunny,	// BUNNY_INX	3	// bunny
	ImgEggHamster,	// HAMSTER_INX	4	// hamster
	ImgEggBird,	// BIRD_INX	5	// bird
	ImgEggDragon,	// DRAGON_INX	6	// dragon
};

// pet eggs coordinates X and Y
const u8 ImgEggXY[2*BASENUM] = {
	4, 12,	// CAT_INX	1	// cat
	4, 9,	// DOG_INX	2	// dog
	3, 9,	// BUNNY_INX	3	// bunny
	6, 11,	// HAMSTER_INX	4	// hamster
	4, 7,	// BIRD_INX	5	// bird
	3, 9,	// DRAGON_INX	6	// dragon
};

// pet bed
const u8* const ImgBedList[TYPENUM] = {
	ImgBedBaby,	// BABY_INX	0	// baby
	ImgBedCat,	// CAT_INX	1	// cat
	ImgBedDog,	// DOG_INX	2	// dog
	ImgBedBunny,	// BUNNY_INX	3	// bunny
	ImgBedHamster,	// HAMSTER_INX	4	// hamster
	ImgBedBird,	// BIRD_INX	5	// bird
	ImgBedDragon,	// DRAGON_INX	6	// dragon
};

// pet bed coordinates X and Y
const u8 ImgBedXY[2*TYPENUM] = {
	6, 5,	// BABY_INX	0	// baby
	7, 1,	// CAT_INX	1	// cat
	7, 3,	// DOG_INX	2	// dog
	6, 3,	// BUNNY_INX	3	// bunny
	2, 1,	// HAMSTER_INX	4	// hamster
	6, 3,	// BIRD_INX	5	// bird
	8, 4,	// DRAGON_INX	6	// dragon
};

// pet wakeup
const u8* const ImgWakeupList[TYPENUM] = {
	ImgWakeupBaby,		// BABY_INX	0	// baby
	ImgWakeupCat,		// CAT_INX	1	// cat
	ImgWakeupDog,		// DOG_INX	2	// dog
	ImgWakeupBunny,		// BUNNY_INX	3	// bunny
	ImgWakeupHamster,	// HAMSTER_INX	4	// hamster
	ImgWakeupBird,		// BIRD_INX	5	// bird
	ImgWakeupDragon,	// DRAGON_INX	6	// dragon
};

// pet wakeup coordinates X and Y
const u8 ImgWakeupXY[2*TYPENUM] = {
	11, 15,	// BABY_INX	0	// baby
	16, 12,	// CAT_INX	1	// cat
	12, 11,	// DOG_INX	2	// dog
	14, 14,	// BUNNY_INX	3	// bunny
	10, 16,	// HAMSTER_INX	4	// hamster
	10, 14,	// BIRD_INX	5	// bird
	10, 14,	// DRAGON_INX	6	// dragon
};

// pet base image
const u8* const ImgPetList[TYPENUM] = {
	ImgBaby,	// BABY_INX	0	// baby
	ImgCat,		// CAT_INX	1	// cat
	ImgDog,		// DOG_INX	2	// dog
	ImgBunny,	// BUNNY_INX	3	// bunny
	ImgHamster,	// HAMSTER_INX	4	// hamster
	ImgBird,	// BIRD_INX	5	// bird
	ImgDragon,	// DRAGON_INX	6	// dragon
};

// state icons (14x14 pixels)
const u8* const ImgStateList[STATE_NUM+2] = {
	ImgStateFood,	// STATE_FEED	0	// fullness state (0=hungry .. STATEMAX=well-fed)
	ImgStateCure,	// STATE_HEALTH	1	// health status (0=sick .. STATEMAX=healthy)
	ImgStateRest,	// STATE_REST	2	// rest state (0=tired .. STATEMAX=rested)
	ImgStateGame,	// STATE_HAPPY	3	// happiness (0=unhappy .. STATEMAX=happy)
	ImgStateClean,	// STATE_CLEAN	4	// clean (0=mess .. STATEMAX=clean)
	ImgStateLearn,	// STATE_DISC	5	// discipline (0=undisciplined .. STATEMAX=disciplined)
	ImgStateInfo,	// info
	ImgStateGiveup,	// give up
};

// menu text (24x7 pixels)
const u8* const ImgMenuList[STATE_NUM+2] = {
	ImgMenuFood,	// STATE_FEED	0	// fullness state (0=hungry .. STATEMAX=well-fed)
	ImgMenuCure,	// STATE_HEALTH	1	// health status (0=sick .. STATEMAX=healthy)
	ImgMenuRest,	// STATE_REST	2	// rest state (0=tired .. STATEMAX=rested)
	ImgMenuGame,	// STATE_HAPPY	3	// happiness (0=unhappy .. STATEMAX=happy)
	ImgMenuClean,	// STATE_CLEAN	4	// clean (0=mess .. STATEMAX=clean)
	ImgMenuLearn,	// STATE_DISC	5	// discipline (0=undisciplined .. STATEMAX=disciplined)
	ImgMenuInfo,	// info
	ImgMenuGiveup,	// give up
};

// pet wink
const u8* const ImgWinkList[TYPENUM] = {
	ImgBabyWink,		// BABY_INX	0	// baby
	ImgCatWink,		// CAT_INX	1	// cat
	ImgDogWink,		// DOG_INX	2	// dog
	ImgBunnyWink,		// BUNNY_INX	3	// bunny
	ImgHamsterWink,		// HAMSTER_INX	4	// hamster
	ImgBirdWink,		// BIRD_INX	5	// bird
	ImgDragonWink,		// DRAGON_INX	6	// dragon
};

// pet wink coordinates X and Y
const u8 ImgWinkXY[2*TYPENUM] = {
	12, 15,	// BABY_INX	0	// baby
	25, 14,	// CAT_INX	1	// cat
	33, 8,	// DOG_INX	2	// dog
	22, 19,	// BUNNY_INX	3	// bunny
	22, 10,	// HAMSTER_INX	4	// hamster
	33, 5,	// BIRD_INX	5	// bird
	24, 14,	// DRAGON_INX	6	// dragon
};

// pet anim
const u8* const ImgAnimList[TYPENUM] = {
	ImgBabyAnim,		// BABY_INX	0	// baby
	ImgCatAnim,		// CAT_INX	1	// cat
	ImgDogAnim,		// DOG_INX	2	// dog
	ImgBunnyAnim,		// BUNNY_INX	3	// bunny
	ImgHamsterAnim,		// HAMSTER_INX	4	// hamster
	ImgBirdAnim,		// BIRD_INX	5	// bird
	ImgDragonAnim,		// DRAGON_INX	6	// dragon
};

// pet anim coordinates X and Y
const u8 ImgAnimXY[2*TYPENUM] = {
	0, 20,	// BABY_INX	0	// baby
	0, 24,	// CAT_INX	1	// cat
	0, 23,	// DOG_INX	2	// dog
	6, 0,	// BUNNY_INX	3	// bunny
	0, 37,	// HAMSTER_INX	4	// hamster
	0, 38,	// BIRD_INX	5	// bird
	0, 21,	// DRAGON_INX	6	// dragon
};
