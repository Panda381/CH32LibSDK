
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#include "../include.h"

//#pragma once

//#include <Arduino.h>
//#include "dungeonTypes.h"
//#include "externBitmaps.h"

// simple level - 1 byte per cell
const uint8_t Level_1[] PROGMEM = 
{
/*             0             1             2            3              4              5             6            7             8            9           10           11            12           13           14           15              */
/*  0 */     WALL      ,   WALL      ,   WALL     ,   WALL      ,WALL|LVR_LEFT,     WALL     ,    WALL     ,     0       ,   WALL     ,   WALL     ,     0      ,     0       ,     0      ,     0      ,     0,         WALL   , /*  0 */
/*  1 */       0       ,/*START*/ 0  ,   BARS     ,     0       ,CLOSED_CHEST ,     WALL     , CLOSED_CHEST,   WALL      ,     0      ,   WALL     ,     0      ,   WALL      ,   WALL     ,   WALL     ,     0      ,   WALL     , /*  1 */
/*  2 */       0       ,     0       ,   WALL     ,     0       ,    WALL     ,     WALL     ,    WALL     ,     0       ,     0      ,   WALL     ,     0      ,   WALL      ,  FOUNTAIN  ,   WALL     ,     0      ,   WALL     , /*  2 */
/*  3 */  /* RAT*/ 0   ,   WALL      ,     0      ,     0       ,    WALL     ,       0      ,      0      ,     0       ,   WALL     ,   WALL     ,     0      ,   WALL      ,/*BEHOLDR*/0,   WALL     ,     0      ,   WALL     , /*  3 */
/*  4 */  WALL|LVR_LEFT,   WALL      ,     0      ,   WALL      ,      0      ,       0      ,    WALL     ,     0       ,     0      ,   WALL     ,     0      ,   WALL      ,     0      ,   BARS     ,     0      ,   WALL     , /*  4 */
/*  5 */     WALL      ,     0       ,/*SPINNER*/0, /* RAT*/ 0  ,    WALL     ,       0      ,    WALL     ,     0       ,     0      ,   WALL     ,     0      ,   WALL      ,   WALL     ,   WALL     ,   WALL     ,   WALL     , /*  5 */
/*  6 */       0       ,     0       ,   WALL     ,     0       ,      0      ,       0      ,    WALL     ,   WALL      ,CLOSED_CHEST,   WALL     ,     0      ,     0       ,     0      ,/*SKELETN*/0,CLOSED_CHEST,   BARS     , /*  6 */ 
/*  7 */     WALL      ,   WALL	     ,     0      ,     0       ,    WALL     ,     WALL     ,    WALL     ,WALL|LVR_LEFT,   WALL     ,   WALL     ,   WALL     ,   WALL      ,   WALL     ,   BARS     ,   WALL     ,   WALL     , /*  7 */
/*  8 */     WALL      ,     0       ,     0      ,     0       ,    WALL     ,       0      ,    WALL     ,/*SPINNER*/0 ,   WALL     ,     0      ,   WALL     ,     0       ,     0      ,     0      ,     0      ,     0      , /*  8 */
/*  9 */     WALL      ,     0       ,   WALL     , FAKE_WALL   ,    WALL     ,       0      ,      0      ,     0       ,     0      ,     0      ,   WALL     ,   BARS      ,   WALL     ,     0      ,   WALL     ,     0      , /*  9 */
/* 10 */     WALL      ,     0       ,   WALL     ,CLOSED_CHEST ,    WALL     ,       0      ,    WALL     ,     0       ,   WALL     ,     0      ,   WALL     , /*MIMIC*/ 0 ,   WALL     ,     0      ,     0      ,     0      , /* 10 */
/* 11 */     WALL      ,     0       ,     0      ,   WALL      ,    WALL     ,       0      ,      0      ,/*TELEP.*/ 0 ,     0      ,     0      ,   WALL     ,   WALL      ,     0      ,     0      ,   WALL     ,     0      , /* 11 */
/* 12 */  WALL|LVR_LEFT,   WALL      , FAKE_WALL  ,   BARS      ,    BARS     ,       0      ,    WALL     ,CLOSED_CHEST ,WALL|LVR_LEFT,    0      ,     0      , WALL|DOOR   ,     0      ,   WALL     ,     0      ,     0      , /* 12 */
/* 13 */       0       ,     0       ,     0      ,   WALL      ,    WALL     ,       0      ,      0      ,/*TELEP.*/ 0 ,     0      ,     0      ,   WALL     ,     0       ,     0      ,   WALL     ,     0      ,   WALL     , /* 13 */
/* 14 */     WALL      ,   WALL      ,     0      ,     0       ,    WALL     ,       0      ,    WALL     ,     0       ,   WALL     ,     0      ,   WALL     ,/*SKELETN*/0 ,   WALL     ,     0      ,     0      ,     0      , /* 14 */
/* 15 */       0       ,WALL|LVR_LEFT,   WALL     ,WALL|LVR_LEFT,    WALL     ,       0      ,      0      ,     0       ,     0      ,     0      ,   WALL     ,    WALL     ,   WALL     ,WALL|LVR_LEFT,   WALL    ,     0      , /* 15 */
/*             0             1             2            3              4              5             6            7             8            9           10           11            12           13           14           15              */
};

// interaction data (6 bytes per event)
const INTERACTION_INFO interactionData[23] PROGMEM =
{
  // currentPos                    currentStatus     nextStatus         newItem              modifiedPos        modifiedPosCellValue
  {  4 +  0 * LEVEL_WIDTH        ,    LVR_LEFT     , LVR_RIGHT   ,         0           ,  5 +  1 * LEVEL_WIDTH  ,      0        },

  {  7 +  0 * LEVEL_WIDTH        ,    LVR_LEFT     , LVR_RIGHT   ,         0           ,  2 +  1 * LEVEL_WIDTH  ,  /*TBD*/ 0    },
  {  7 +  0 * LEVEL_WIDTH        ,    LVR_RIGHT    , LVR_LEFT    ,         0           ,  2 +  1 * LEVEL_WIDTH  ,  /*TBD*/ 0    },
																      
  {  4 +  1 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST  ,     ITEM_COMPASS    ,  4 +  1 * LEVEL_WIDTH  ,  OPEN_CHEST   },
  {  6 +  1 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST  ,    ITEM_SHIELD      ,  6 +  1 * LEVEL_WIDTH  ,  OPEN_CHEST   },
																      
  { 12 +  2 * LEVEL_WIDTH        ,    FOUNTAIN     , FOUNTAIN    ,     ITEM_VICTORY    , 12 +  2 * LEVEL_WIDTH  ,    FOUNTAIN   },
																      
  {  0 +  4 * LEVEL_WIDTH        ,    LVR_LEFT     , LVR_RIGHT   ,         0           ,  2 +  1 * LEVEL_WIDTH  ,      0        },
  {  0 +  4 * LEVEL_WIDTH        ,    LVR_RIGHT    , LVR_LEFT    ,         0           ,  2 +  1 * LEVEL_WIDTH  ,     BARS      },
																      
  {  8 +  6 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST  ,     ITEM_AMULET     ,  8 +  6 * LEVEL_WIDTH  ,  OPEN_CHEST   },
  { 14 +  6 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST  ,ITEM_RING|ITEM_POTION, 14 +  6 * LEVEL_WIDTH  ,  OPEN_CHEST   },
																      
  {  7 +  7 * LEVEL_WIDTH        ,    LVR_LEFT     , LVR_RIGHT   ,         0           ,  7 + 15 * LEVEL_WIDTH  ,   /*TBD*/ 0   },
  {  7 +  7 * LEVEL_WIDTH        ,    LVR_RIGHT    , LVR_LEFT    ,         0           ,  7 + 15 * LEVEL_WIDTH  ,   /*TBD*/ 0   },
																      
  {  0 + 12 * LEVEL_WIDTH        ,    LVR_LEFT     , LVR_RIGHT   ,         0           ,  3 + 12 * LEVEL_WIDTH  ,      0        },
  {  0 + 12 * LEVEL_WIDTH        ,    LVR_RIGHT    , LVR_LEFT    ,         0           ,  4 + 12 * LEVEL_WIDTH  ,    BARS       },
  
  {  7 + 12 * LEVEL_WIDTH        ,    CLOSED_CHEST , OPEN_CHEST  ,ITEM_KEY|ITEM_COMPASS,  7 + 12 * LEVEL_WIDTH  ,  OPEN_CHEST   },
  {  8 + 12 * LEVEL_WIDTH        ,    LVR_LEFT     ,    0        ,         0           , 10 + 12 * LEVEL_WIDTH  ,      0        },   
  { 11 + 12 * LEVEL_WIDTH        ,    DOOR         ,    0        ,         0           , 11 + 12 * LEVEL_WIDTH  ,      0        },
																	    
  {  1 + 15 * LEVEL_WIDTH        ,    LVR_LEFT     , LVR_RIGHT   ,         0           ,  1 +  9 * LEVEL_WIDTH  ,    BARS       },
  {  1 + 15 * LEVEL_WIDTH        ,    LVR_RIGHT    , LVR_LEFT    ,         0           ,  1 +  9 * LEVEL_WIDTH  ,      0        },
  {  3 + 15 * LEVEL_WIDTH        ,    LVR_LEFT     , LVR_RIGHT   ,         0           ,  3 + 12 * LEVEL_WIDTH  ,    BARS       },
  {  3 + 15 * LEVEL_WIDTH        ,    LVR_RIGHT    , LVR_LEFT    ,         0           ,  4 + 12 * LEVEL_WIDTH  ,      0        },
																    
  { 13 + 15 * LEVEL_WIDTH        ,    LVR_LEFT     , LVR_RIGHT   ,         0           , 13 +  7 * LEVEL_WIDTH  ,      0        },
  { 13 + 15 * LEVEL_WIDTH        ,    LVR_RIGHT    , LVR_LEFT    ,         0           , 13 +  4 * LEVEL_WIDTH  ,      0        },
};

// special cell effects (4 bytes per FX)
const SPECIAL_CELL_INFO specialCellFX[5] PROGMEM =
{
  // cell type ,     position       , value_1, value_2
  { TELEPORTER ,  7 + 11 * LEVEL_WIDTH,     5  ,   13    },
  { TELEPORTER ,  7 + 13 * LEVEL_WIDTH,     5  ,   11    },
  { SPINNER    , 10 +  2 * LEVEL_WIDTH,    +2  ,    0    },
  { SPINNER    ,  2 +  5 * LEVEL_WIDTH,    +1  ,    0    },
  { SPINNER    ,  7 +  8 * LEVEL_WIDTH,    +3  ,    0    },
};

// monster stats (6 bytes per monster - must fit into RAM - or EEPROM???)
const MONSTER_STATS monsterStats[MAX_MONSTERS] PROGMEM =
{
  // position                monsterType  hp  bonusDamage   attacksFirst  treasureItemMask
  {   0 +  3 * LEVEL_WIDTH,  RAT        ,  3 ,     -6      ,      1       ,           0                               }, // rat
  {   8 +  1 * LEVEL_WIDTH,  RAT        ,  3 ,     -4      ,      1       ,           0                               }, // rat
  {  12 +  3 * LEVEL_WIDTH,  BEHOLDER   , 40 ,     +7      ,      1       ,           0                               }, // beholder (end boss)
  {   3 +  5 * LEVEL_WIDTH,  RAT        ,  5 ,     -4      ,      1       ,           0                               }, // rat
  {  13 +  6 * LEVEL_WIDTH,  SKELETON   , 15 ,     +4      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
  {   7 +  8 * LEVEL_WIDTH,  SKELETON   , 12 ,     +3      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
  {   3 + 10 * LEVEL_WIDTH,  MIMIC      , 15 ,     -1      ,      1       ,     ITEM_POTION | ITEM_SWORD              }, // mimic
  {  11 + 10 * LEVEL_WIDTH,  MIMIC      , 15 ,     +1      ,      0       ,  ITEM_SWORD | ITEM_SHIELD | ITEM_POTION   }, // mimic
  {   3 + 14 * LEVEL_WIDTH,  SKELETON   , 12 ,     +3      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
  {  13 + 14 * LEVEL_WIDTH,  SKELETON   , 12 ,     +3      ,      0       ,  ITEM_SWORD | ITEM_SHIELD                 }, // skeleton
};
