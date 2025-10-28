
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#ifndef _DUNGEON_H
#define _DUNGEON_H

//#pragma once

//#include <Arduino.h>
//#include "dungeonTypes.h"
//#include "externBitmaps.h"

// uncomment this line to make the player invincible
//#define _GODMODE_

// Dungeon
class Dungeon
{
public:
  DUNGEON _dungeon;

//  Dungeon(){} // default constructor

  static constexpr uint8_t getLevelWidth() { return( LEVEL_WIDTH ); }
  static constexpr uint8_t getLevelHeight() { return( LEVEL_HEIGHT ); }

  void clear();
  void init();

  bool isPlayerAlive() { return( _dungeon.playerHP > 0 ); }

  void gameLoop();
  void checkPlayerMovement();

#ifdef _USE_FIELD_OF_VIEW_
  void updateFieldOfView();
  uint8_t getCell( const int8_t distance, const int8_t offsetLR );
#endif
  uint8_t *getCellRaw( int8_t x, int8_t y, const int8_t distance, const int8_t offsetLR, const uint8_t orientation );
  void limitDungeonPosition( int8_t &x, int8_t &y );
  void updateStatusPane();
  void openChest( INTERACTION_INFO &info );
  void initDice();
  void updateDice();
  uint8_t getDice( uint8_t maxValue );
  MONSTER_STATS *findMonster( const uint8_t position );
  void playerAttack( MONSTER_STATS *monster );
  void monsterAttack( MONSTER_STATS *monster );
  void playerInteraction( uint8_t *cell, const uint8_t cellValue );
  void /*__attribute__ ((noinline))*/ renderImage();
  // bitmap drawing functions
  uint8_t /*__attribute__ ((always_inline))*/ getWallPixels( const int8_t x, const int8_t y );
  uint8_t getDownScaledBitmapData( int8_t x, int8_t y, 
                                   const uint8_t distance, const NON_WALL_OBJECT *object,
                                   bool useMask );
};

#endif // _DUNGEON_H
