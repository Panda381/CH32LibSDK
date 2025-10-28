
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

//#pragma once

// Dungeon walls inspired by the original Dungeon Master
// The walls are made of large, regular stone blocks - the first iteration, but somehow boring

//#if defined( DUNGEON_MASTER_STYLE_WALLS )
// 'frontwall96x64_inv2', 96x64px (768 bytes)
extern const unsigned char frontWalls_D1 [] PROGMEM;

// 'frontwall48x32_inv2_cropped', 96x32px (384 bytes)
extern const unsigned char frontWalls_D2 [] PROGMEM;

// 'frontwall24x16_inv2_cropped', 96x16px (192 bytes)
extern const unsigned char frontWalls_D3 [] PROGMEM;

// 'leftrightwalls_inv2', 96x64px (768 bytes)
extern const unsigned char leftRightWalls [] PROGMEM;
//#endif
