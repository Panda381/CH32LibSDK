
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#ifndef _LEVELDEFINITIONS_H
#define _LEVELDEFINITIONS_H

// simple level - 1 byte per cell
extern const uint8_t Level_1[] PROGMEM;

// interaction data (6 bytes per event)
extern const INTERACTION_INFO interactionData[23] PROGMEM;

// special cell effects (4 bytes per FX)
extern const SPECIAL_CELL_INFO specialCellFX[5] PROGMEM;

// monster stats (6 bytes per monster - must fit into RAM - or EEPROM???)
extern const MONSTER_STATS monsterStats[MAX_MONSTERS] PROGMEM;

#endif // _LEVELDEFINITIONS_H
