
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#ifndef _EXTERNBITMAPS_H
#define _EXTERNBITMAPS_H

// list of possible non wall objects (i.e. monsters, doors, ...) (10 bytes per object)
extern const NON_WALL_OBJECT objectList [11] PROGMEM;

// array of conditions for wall display (9 bytes per row)
// 'WALL & ~FLAG_SOLID' means all walls, fake or not...
// CAUTION: The entries must be ordered from min. distance(0) to max. distance (3)
// Otherwise display errors will occur
extern const SIMPLE_WALL_INFO arrayOfWallInfo[] PROGMEM;

#endif // _EXTERNBITMAPS_H
