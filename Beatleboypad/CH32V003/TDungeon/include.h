
// ****************************************************************************
//                                 
//                              Includes
//
// ****************************************************************************

#include INCLUDES_H		// all includes

#define RUSTICAL_STYLE_WALLS
#define DUNGEON_MASTER_STYLE_WALLS
//#define _USE_FIELD_OF_VIEW_
//#define _ENABLE_SHADING_

#include "../../CH32V002/TDungeon/src/main.h"		// main code

#include "../../CH32V002/TDungeon/src/dungeonTypes.h"

#include "../../CH32V002/TDungeon/src/bitTables.h"
#include "../../CH32V002/TDungeon/src/dungeon.h"
#include "../../CH32V002/TDungeon/src/externBitmaps.h"
#include "../../CH32V002/TDungeon/src/LevelDefinitions.h"
#include "../../CH32V002/TDungeon/src/monsterBitmaps.h"
#include "../../CH32V002/TDungeon/src/objectBitmaps.h"
#include "../../CH32V002/TDungeon/src/soundFX.h"
#include "../../CH32V002/TDungeon/src/TinyDungeon.h"
#include "../../CH32V002/TDungeon/src/TinyJoypadUtils.h"
#include "../../CH32V002/TDungeon/src/wallBitmaps.h"
