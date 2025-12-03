
// ****************************************************************************
//
//                           Graphics and tables
//
// ****************************************************************************

#ifndef _GRAPH_H
#define _GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

// pet default names
extern const char* const PetDefName[BASENUM];

// pet eggs
extern const u8* const ImgEggList[BASENUM];

// pet eggs coordinates X and Y
extern const u8 ImgEggXY[2*BASENUM];

// pet bed
extern const u8* const ImgBedList[TYPENUM];

// pet bed coordinates X and Y
extern const u8 ImgBedXY[2*TYPENUM];

// pet wakeup
extern const u8* const ImgWakeupList[TYPENUM];

// pet wakeup coordinates X and Y
extern const u8 ImgWakeupXY[2*TYPENUM];

// pet base image
extern const u8* const ImgPetList[TYPENUM];

// state icons (14x14 pixels)
extern const u8* const ImgStateList[STATE_NUM+2];

// menu text (24x7 pixels)
extern const u8* const ImgMenuList[STATE_NUM+2];

// pet wink
extern const u8* const ImgWinkList[TYPENUM];

// pet wink coordinates X and Y
extern const u8 ImgWinkXY[2*TYPENUM];

// pet anim
extern const u8* const ImgAnimList[TYPENUM];

// pet anim coordinates X and Y
extern const u8 ImgAnimXY[2*TYPENUM];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 48 pixels
// image height: 6 lines
extern const u8 ImgTitle[39];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 93%
// image width: 26 pixels
// image height: 8 lines
// X=7, Y=15
extern const u8 ImgBabyEye[27];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 96%
// image width: 14 pixels
// image height: 14 lines
extern const u8 ImgPill[26];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 73%
// image width: 18 pixels
// image height: 14 lines
extern const u8 ImgHand[25];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 8 pixels
// image height: 6 lines
extern const u8 ImgDirt[9];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 5 bits
// compression: 48%
// image width: 38 pixels
// image height: 39 lines
extern const u8 ImgBaby[92];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 5 bits
// compression: 74%
// image width: 44 pixels
// image height: 51 lines
extern const u8 ImgCat[210];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 5 bits
// compression: 68%
// image width: 47 pixels
// image height: 52 lines
extern const u8 ImgDog[210];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 5 bits
// compression: 77%
// image width: 33 pixels
// image height: 51 lines
extern const u8 ImgBunny[165];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 5 bits
// compression: 67%
// image width: 40 pixels
// image height: 45 lines
extern const u8 ImgHamster[155];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 5 bits
// compression: 60%
// image width: 46 pixels
// image height: 47 lines
extern const u8 ImgBird[164];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 75%
// image width: 37 pixels
// image height: 50 lines
extern const u8 ImgDragon[177];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 18 pixels
// image height: 5 lines
// X=12, Y=15
extern const u8 ImgBabyWink[14];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 4 pixels
// image height: 5 lines
// X=33, Y=5
extern const u8 ImgBirdWink[5];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 4 pixels
// image height: 4 lines
// X=22, Y=19
extern const u8 ImgBunnyWink[5];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 12 pixels
// image height: 5 lines
// X=25, Y=14
extern const u8 ImgCatWink[10];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 4 pixels
// image height: 5 lines
// X=33, Y=8
extern const u8 ImgDogWink[5];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 4 pixels
// image height: 5 lines
// X=24, Y=14
extern const u8 ImgDragonWink[5];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 13 pixels
// image height: 5 lines
// X=22, Y=10
extern const u8 ImgHamsterWink[11];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 6 bits
// compression: 61%
// image width: 38 pixels
// image height: 7 lines
// X=0, Y=20
extern const u8 ImgBabyAnim[22];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 3 bits
// compression: 90%
// image width: 9 pixels
// image height: 7 lines
// X=0, Y=38
extern const u8 ImgBirdAnim[10];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 16 pixels
// image height: 13 lines
// X=6, Y=0
extern const u8 ImgBunnyAnim[29];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 3 bits
// compression: 94%
// image width: 7 pixels
// image height: 16 lines
// X=0, Y=24
extern const u8 ImgCatAnim[16];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 3 bits
// compression: 81%
// image width: 9 pixels
// image height: 17 lines
// X=0, Y=23
extern const u8 ImgDogAnim[18];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 11 pixels
// image height: 11 lines
// X=0, Y=21
extern const u8 ImgDragonAnim[18];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 5 pixels
// image height: 5 lines
// X=0, Y=37
extern const u8 ImgHamsterAnim[6];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 5 bits
// compression: 36%
// image width: 29 pixels
// image height: 38 lines
extern const u8 ImgEgg[52];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 79%
// image width: 19 pixels
// image height: 9 lines
// X=4, Y=2
extern const u8 ImgEggCrack[19];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 87%
// image width: 17 pixels
// image height: 14 lines
// X=6, Y=-4
extern const u8 ImgEggBorn[29];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 79%
// image width: 20 pixels
// image height: 22 lines
// X=4, Y=7
extern const u8 ImgEggBird[46];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 73%
// image width: 22 pixels
// image height: 21 lines
// X=3, Y=9
extern const u8 ImgEggBunny[45];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 82%
// image width: 21 pixels
// image height: 17 lines
// X=4, Y=12
extern const u8 ImgEggCat[39];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 89%
// image width: 21 pixels
// image height: 20 lines
// X=4, Y=9
extern const u8 ImgEggDog[49];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 72%
// image width: 23 pixels
// image height: 23 lines
// X=3, Y=9
extern const u8 ImgEggDragon[50];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 93%
// image width: 17 pixels
// image height: 19 lines
// X=6, Y=11
extern const u8 ImgEggHamster[40];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 5 bits
// compression: 73%
// image width: 54 pixels
// image height: 48 lines
extern const u8 ImgBed[239];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 75%
// image width: 28 pixels
// image height: 12 lines
// X=37, Y=1
extern const u8 ImgZzz[34];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 21 pixels
// image height: 23 lines
// X=6, Y=5
extern const u8 ImgBedBaby[63];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 23 pixels
// image height: 24 lines
// X=6, Y=3
extern const u8 ImgBedBird[72];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 21 pixels
// image height: 24 lines
// X=6, Y=3
extern const u8 ImgBedBunny[66];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 26 pixels
// image height: 26 lines
// X=7, Y=1
extern const u8 ImgBedCat[87];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 22 pixels
// image height: 23 lines
// X=7, Y=3
extern const u8 ImgBedDog[66];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 20 pixels
// image height: 22 lines
// X=8, Y=4
extern const u8 ImgBedDragon[58];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 29 pixels
// image height: 30 lines
// X=2, Y=1
extern const u8 ImgBedHamster[112];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 11 pixels
// image height: 7 lines
// X=11, Y=15
extern const u8 ImgWakeupBaby[12];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 12 pixels
// image height: 6 lines
// X=10, Y=14
extern const u8 ImgWakeupBird[12];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 9 pixels
// image height: 7 lines
// X=14, Y=14
extern const u8 ImgWakeupBunny[11];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 8 pixels
// image height: 8 lines
// X=16, Y=12
extern const u8 ImgWakeupCat[11];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 7 pixels
// image height: 9 lines
// X=12, Y=11
extern const u8 ImgWakeupDog[11];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 9 pixels
// image height: 6 lines
// X=10, Y=14
extern const u8 ImgWakeupDragon[10];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 11 pixels
// image height: 8 lines
// X=10, Y=16
extern const u8 ImgWakeupHamster[14];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 32 pixels
// image height: 20 lines
extern const u8 ImgState[83];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 77%
// image width: 14 pixels
// image height: 14 lines
extern const u8 ImgStateClean[21];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 88%
// image width: 14 pixels
// image height: 14 lines
extern const u8 ImgStateCure[24];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 81%
// image width: 14 pixels
// image height: 14 lines
extern const u8 ImgStateFood[22];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 14 pixels
// image height: 14 lines
extern const u8 ImgStateGame[27];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 70%
// image width: 14 pixels
// image height: 14 lines
extern const u8 ImgStateLearn[19];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 3 bits
// compression: 85%
// image width: 14 pixels
// image height: 14 lines
extern const u8 ImgStateRest[23];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 4 bits
// compression: 74%
// image width: 14 pixels
// image height: 14 lines
extern const u8 ImgStateInfo[20];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 14 pixels
// image height: 14 lines
extern const u8 ImgStateGiveup[27];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 24 pixels
// image height: 7 lines
extern const u8 ImgMenuClean[24];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 24 pixels
// image height: 7 lines
extern const u8 ImgMenuCure[24];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 24 pixels
// image height: 7 lines
extern const u8 ImgMenuFood[24];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 24 pixels
// image height: 7 lines
extern const u8 ImgMenuGame[24];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 24 pixels
// image height: 7 lines
extern const u8 ImgMenuLearn[24];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 24 pixels
// image height: 7 lines
extern const u8 ImgMenuRest[24];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 24 pixels
// image height: 7 lines
extern const u8 ImgMenuInfo[24];

// format: 1-bit pixel graphics RLE compressed
// chunk length: 1 bits
// compression: 100%
// image width: 24 pixels
// image height: 7 lines
extern const u8 ImgMenuGiveup[24];

#ifdef __cplusplus
}
#endif

#endif // _GRAPH_H
