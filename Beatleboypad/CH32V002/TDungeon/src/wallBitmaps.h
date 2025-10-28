
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#ifndef _WALLBITMAPS_H
#define _WALLBITMAPS_H

//#pragma once

//#include <Arduino.h>

//#define RUSTICAL_STYLE_WALLS
//#define DUNGEON_MASTER_STYLE_WALLS

#if defined( RUSTICAL_STYLE_WALLS )
  #include "EyeOfTheBeholderWallBitmaps.h"
#endif
#if defined( DUNGEON_MASTER_STYLE_WALLS )
  #include "DungeonMasterWallBitmaps.h"
#endif

#endif // _WALLBITMAPS_H
