
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#include "../include.h"

//#pragma once

//#include <Arduino.h>
//#include "dungeonTypes.h"

/*
// monsters
extern const uint8_t joey[] PROGMEM;
extern const uint8_t beholder[] PROGMEM;
extern const uint8_t rat[] PROGMEM;

// objects
extern const uint8_t newBars[] PROGMEM;
extern const uint8_t door[] PROGMEM;
extern const uint8_t leverLeft[] PROGMEM;
extern const uint8_t leverRight[] PROGMEM;
extern const uint8_t chestClosed[] PROGMEM;
extern const uint8_t chestOpen[] PROGMEM;
extern const uint8_t fountain[] PROGMEM;
extern const uint8_t statusPanel[] PROGMEM;
extern const uint8_t compass[] PROGMEM;

// walls
extern const unsigned char smallFrontWall_D1[] PROGMEM;
extern const unsigned char smallFrontWall_D2 [] PROGMEM;
extern const unsigned char smallFrontWall_D3 [] PROGMEM;
extern const unsigned char leftRightWalls_D0[] PROGMEM;
extern const unsigned char leftRightWalls_D1[] PROGMEM;
extern const unsigned char leftRightWalls_D2[] PROGMEM;
extern const unsigned char leftRightWalls_D3[] PROGMEM;
extern const unsigned char outerLeftRightWalls_D2 [] PROGMEM;
extern const unsigned char outerLeftRightWalls_D3 [] PROGMEM;
*/

// list of possible non wall objects (i.e. monsters, doors, ...) (10 bytes per object)
const NON_WALL_OBJECT objectList [11] PROGMEM = {
//  itemType    , width, verticalOffsetBits, heightBits, lineOffset, scalingThreshold, bitmapData
  { SKELETON    ,  28,         2 * 8,          5 * 8,         56,      { 1, 2,  5 },   joey        },  //  0
  { BEHOLDER    ,  32,         0 * 8,          7 * 8,         64,      { 1, 2,  5 },   beholder    },  //  1
  { BARS        ,  28,         1 * 8,          6 * 8,         56,      { 1, 2,  5 },   newBars     },  //  2
  { DOOR        ,  32,         1 * 8,          7 * 8,         64,      { 1, 3, 12 },   door        },  //  3
  { LVR_LEFT    ,  16,         3 * 8,          1 * 8,         32,      { 1, 2,  8 },   leverLeft   },  //  4
  { LVR_RIGHT   ,  16,         3 * 8,          1 * 8,         32,      { 1, 2,  8 },   leverRight  },  //  5
  { CLOSED_CHEST,  24,         4 * 8,          3 * 8,         48,      { 1, 3, 99 },   chestClosed },  //  6
  { MIMIC       ,  24,         4 * 8,          3 * 8,         48,      { 1, 3, 99 },   chestClosed },  //  7
  { OPEN_CHEST  ,  24,         4 * 8,          3 * 8,         48,      { 1, 3, 99 },   chestOpen   },  //  8
  { FOUNTAIN    ,  12,         4 * 8,          3 * 8,         24,      { 1, 2, 99 },   fountain    },  //  9
  { RAT         ,  20,         5 * 8,          2 * 8,         40,      { 1, 2, 99 },   rat         },  // 10
};

// array of conditions for wall display (9 bytes per row)
// 'WALL & ~FLAG_SOLID' means all walls, fake or not...
// CAUTION: The entries must be ordered from min. distance(0) to max. distance (3)
// Otherwise display errors will occur
const SIMPLE_WALL_INFO arrayOfWallInfo[] PROGMEM = {
  // *wallBitmap           , startX, endX, posStartEndY, distance, l/r offset,relPos, width
  // distance 0            
  { leftRightWalls_D0      ,   0   ,   3 ,   0x07      ,     0   ,     -1    ,   0  ,   8 }, //  0
  { leftRightWalls_D0      ,  92   ,  95 ,   0x07      ,     0   ,     +1    ,   4  ,   8 }, //  1
																						  
  // distance 1	                                                                          
  { smallFrontWall_D1      ,   0   ,   3 ,   0x07      ,     1   ,     -1    ,  84  ,  88 }, //  2
  { smallFrontWall_D1      ,   4   ,  91 ,   0x07      ,     1   ,      0    ,   0  ,  88 }, //  3
  { smallFrontWall_D1      ,  92   ,  95 ,   0x07      ,     1   ,     +1    ,   0  ,  88 }, //  4
  { leftRightWalls_D1      ,   4   ,  25 ,   0x07      ,     1   ,     -1    ,   0  ,  44 }, //  5
  { leftRightWalls_D1      ,  70   ,  91 ,   0x07      ,     1   ,     +1    ,  22  ,  44 }, //  6
																						  
  // distance 2	                                                                          
  { smallFrontWall_D2      ,   0   ,  25 ,   0x25      ,     2   ,     -1    ,  18  ,  44 }, //  7
  { smallFrontWall_D2      ,  26   ,  69 ,   0x25      ,     2   ,      0    ,   0  ,  44 }, //  8
  { smallFrontWall_D2      ,  70   ,  95 ,   0x25      ,     2   ,     +1    ,   0  ,  44 }, //  9
  { leftRightWalls_D2      ,  26   ,  36 ,   0x25      ,     2   ,     -1    ,   0  ,  22 }, // 10
  { leftRightWalls_D2      ,  59   ,  69 ,   0x25      ,     2   ,     +1    ,  11  ,  22 }, // 11
  { outerLeftRightWalls_D2 ,   0   ,  14 ,   0x25      ,     2   ,     -2    ,   0  ,  30 }, // 12
  { outerLeftRightWalls_D2 ,  81   ,  95 ,   0x25      ,     2   ,     +2    ,  15  ,  30 }, // 13

  // distance 3
  { smallFrontWall_D3      ,   0   ,  14 ,   0x34      ,     3   ,     -2    ,   7  ,  22 }, // 14
  { smallFrontWall_D3      ,  15   ,  36 ,   0x34      ,     3   ,     -1    ,   0  ,  22 }, // 15
  { smallFrontWall_D3      ,  37   ,  58 ,   0x34      ,     3   ,      0    ,   0  ,  22 }, // 16
  { smallFrontWall_D3      ,  59   ,  80 ,   0x34      ,     3   ,     +1    ,   0  ,  22 }, // 17
  { smallFrontWall_D3      ,  81   ,  95 ,   0x34      ,     3   ,     +2    ,   0  ,  22 }, // 18
  { leftRightWalls_D3      ,  37   ,  41 ,   0x34      ,     3   ,     -1    ,   0  ,  10 }, // 19
  { leftRightWalls_D3      ,  54   ,  58 ,   0x34      ,     3   ,     +1    ,   5  ,  10 }, // 20
  { outerLeftRightWalls_D3 ,  15   ,  29 ,   0x34      ,     3   ,     -2    ,   0  ,  30 }, // 21
  { outerLeftRightWalls_D3 ,  66   ,  80 ,   0x34      ,     3   ,     +2    ,  15  ,  30 }, // 22

  { NULL                   ,   0   ,   0 ,   0x00      ,     0   ,      0    ,   0  ,   0 }, // 7 unused bytes.. how can I save those?
};
