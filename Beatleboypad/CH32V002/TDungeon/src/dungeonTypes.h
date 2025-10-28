
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#ifndef _DUNGEONTYPES_H
#define _DUNGEONTYPES_H

const uint8_t LEVEL_WIDTH       = 16;
const uint8_t LEVEL_HEIGHT      = 16;
const uint16_t MAX_LEVEL_BYTES  = LEVEL_WIDTH * LEVEL_HEIGHT;
const uint8_t MAX_VIEW_DISTANCE = 3;

const uint8_t MAX_MONSTERS      = 10;

const uint8_t WINDOW_SIZE_X     = 96;
const uint8_t WINDOW_CENTER_X   = WINDOW_SIZE_X / 2; /* = 48 */
const uint8_t WINDOW_SIZE_Y     = 64;
const uint8_t WINDOW_CENTER_Y   = WINDOW_SIZE_Y / 2; /* = 32 */

const int8_t  POTION_HITPOINT_BONUS = 8;

/*
extern const uint8_t LEVEL_WIDTH;
extern const uint8_t LEVEL_HEIGHT;
extern const uint16_t MAX_LEVEL_BYTES;
extern const uint8_t MAX_VIEW_DISTANCE;

extern const uint8_t MAX_MONSTERS;

extern const uint8_t WINDOW_SIZE_X;
extern const uint8_t WINDOW_CENTER_X;
extern const uint8_t WINDOW_SIZE_Y;
extern const uint8_t WINDOW_CENTER_Y;

extern const int8_t POTION_HITPOINT_BONUS;
*/

// possible item types
enum
{
  // bit 2 marks an object as a "monster" 
  FLAG_MONSTER        = 0x04,
  // bit 3 is reserved for marking objects as "SOLID", making them impassable
  FLAG_SOLID          = 0x08,
  
  WALL_MASK           = 0x10,
  OBJECT_MASK         = 0xF0 | FLAG_SOLID | FLAG_MONSTER,

  EMPTY               = 0x00,

  // Caution! The following objects are always rendered *on* a wall,
  // so the wall bit (0) is always set!
  FAKE_WALL           = 0x10,
  WALL                = FAKE_WALL | FLAG_SOLID,
  DOOR                = 0x30	| FLAG_SOLID,
  LVR_LEFT            = 0x50	| FLAG_SOLID,
  LVR_RIGHT           = 0x70	| FLAG_SOLID,

  // Caution! The following objects are *never* rendered on a wall,
  // so the wall bit (0) must be '0'
  RAT                 = 0x20 | FLAG_MONSTER | FLAG_SOLID,
  SKELETON            = 0x40 | FLAG_MONSTER | FLAG_SOLID,
  BEHOLDER            = 0x60 | FLAG_MONSTER | FLAG_SOLID,
  CLOSED_CHEST        = 0x80, // | FLAG_SOLID,
  // a mimic is like a chest, but you may not pass through it
  MIMIC               = CLOSED_CHEST | FLAG_MONSTER | FLAG_SOLID,
  OPEN_CHEST          = 0xA0, // | FLAG_SOLID,
  FOUNTAIN            = 0xC0 | FLAG_SOLID,
  BARS                = 0xE0 | FLAG_SOLID,
};

// special FX types
enum 
{
  TELEPORTER          = 0x01,
  SPINNER             = 0x02,
};

// list of items in chests or monster treasure
enum
{
  ITEM_NONE    = 0x00,
  ITEM_COMPASS = 0x01,
  ITEM_AMULET  = 0x02,
  ITEM_RING    = 0x04,
  ITEM_KEY     = 0x08,
  ITEM_POTION  = 0x10,
  ITEM_SWORD   = 0x20,
  ITEM_SHIELD  = 0x40,
  ITEM_VICTORY = 0x80,
};


// monster stats
class MONSTER_STATS
{
public:

  // monster position (byte offset from level start)
  uint8_t position;
  // monster type
  uint8_t monsterType;
  // hit points
  int8_t  hitpoints;
  // damage (additional to 1D8)
  int8_t  damageBonus;
  // monster attacks first?
  uint8_t attacksFirst;
  // treasure (bit mask)
  uint8_t treasureItemMask;
/*
#if !defined(__AVR_ATtiny85__)
  void serialPrint() 
  {
    Serial.print( F("  position         = (") ); Serial.print( position % LEVEL_WIDTH ); Serial.print(F(", ")); Serial.print( position / LEVEL_WIDTH ); Serial.println(F(")"));
    Serial.print( F("  monsterType      = ") ); printHexToSerial( monsterType, false );
    Serial.print( F("  hitpoints        = ") ); Serial.println( hitpoints );
    Serial.print( F("  damageBonus      = ") ); Serial.println( damageBonus );
    Serial.print( F("  attacksFirst     = ") ); Serial.println( ( attacksFirst != 0 ) ? "yes" : "no" );
    Serial.print( F("  treasureItemMask = ") ); Serial.println( treasureItemMask );
    Serial.println();
  }
#endif
*/
};


// DUNGEON
class DUNGEON
{
public:

  int8_t  playerX;
  int8_t  playerY;
  uint8_t dir;
  int8_t  playerHP;
  int8_t  playerDamage;
  int8_t  playerArmour;
  uint8_t playerItems;
/*
#if !defined( __AVR_ATtiny85__ )
  int8_t  dice;
#endif  
*/
  uint8_t displayXorEffect;
  uint8_t invertMonsterEffect;
  uint8_t invertStatusEffect;
  uint8_t currentLevel[MAX_LEVEL_BYTES];
#ifdef _USE_FIELD_OF_VIEW_
  uint8_t fieldOfView[5 * MAX_VIEW_DISTANCE];
#endif
  MONSTER_STATS monsterStats[MAX_MONSTERS];

/*
#if !defined(__AVR_ATtiny85__)
  void serialPrint()
  {
    Serial.println( F("DUNGEON") );
    Serial.print( F("  playerX = ") );Serial.print( playerX );
    Serial.print( F(", playerY = ") );Serial.print( playerY );
    Serial.print( F(", dir = ") );Serial.print( dir );
    Serial.print( F(", HP = ") );Serial.print( playerHP );
    Serial.print( F(", DAM = ") );Serial.print( playerDamage );
    Serial.print( F(", Armour = ") );Serial.print( playerArmour );
    Serial.print( F(", Items = ") );printHexToSerial( playerItems, false );Serial.print( F(", "));
    Serial.print( F(", Keys = ") );Serial.print( ( playerItems & ITEM_KEY ) != 0 );
    Serial.print( F(", Compass = ") );Serial.print( ( playerItems & ITEM_COMPASS ) != 0 );
    Serial.print( F(", displayXorEffect = ") );Serial.print( displayXorEffect );
    Serial.println();

    for ( uint8_t y = 0; y < LEVEL_HEIGHT; y++ )
    {
      for( uint8_t x = 0; x < LEVEL_WIDTH; x++ )
      {
        uint8_t cellValue = currentLevel[y * LEVEL_WIDTH + x];
        char text[3] = "..";
        if ( ( cellValue & OBJECT_MASK ) == LVR_LEFT ) { memcpy_P( text, F("W>"), 2 ); }
        else if ( ( cellValue & OBJECT_MASK ) == LVR_RIGHT ) { memcpy_P( text, F("W<"), 2 ); }
        else if ( ( cellValue & WALL_MASK ) == FAKE_WALL ) { memcpy_P( text, F("W "), 2 ); }
        else if ( cellValue == SKELETON ) { memcpy_P( text, F("sk"), 2 ); }
        else if ( cellValue == BEHOLDER ) { memcpy_P( text, F("bh"), 2 ); }
        else if ( cellValue == RAT ) { memcpy_P( text, F("rt"), 2 ); }
        else if ( cellValue == MIMIC ) { memcpy_P( text, F("mi"), 2 ); }
        else if ( ( cellValue & OBJECT_MASK ) == DOOR ) { memcpy_P( text, F("D "), 2 ); }
        else if ( ( cellValue & OBJECT_MASK ) == BARS ) { memcpy_P( text, F("# "), 2 ); }
        else if ( ( cellValue & OBJECT_MASK ) == FOUNTAIN ) { memcpy_P( text, F("F "), 2 ); }
        Serial.print( text );
        Serial.print( F(" ") );
      }
    Serial.println();
    }
    Serial.println();
  }
#endif
*/
};

// NON_WALL_OBJECT
class NON_WALL_OBJECT
{
public:

  uint8_t itemType;
  uint8_t bitmapWidth;
  uint8_t bitmapVerticalOffsetInBits;
  uint8_t bitmapHeightInBits;
  uint8_t nextLineOffset;
  uint8_t scalingThreshold[3];
  const uint8_t *bitmapData;

/*
#if !defined(__AVR_ATtiny85__)
  void serialPrint() 
  {
    Serial.println( F("NON_WALL_OBJECT") );
    Serial.print( F("  itemType                     = ") );Serial.println( itemType );
    Serial.print( F("  bitmapWidth                  = ") );Serial.print( bitmapWidth );Serial.println();
    Serial.print( F("  bitmapVerticalOffsetInBytes  = ") );Serial.print( bitmapVerticalOffsetInBits );Serial.println();
    Serial.print( F("  bitmapHeightInBytes          = ") );Serial.print( bitmapHeightInBits );Serial.println();
    Serial.print( F("  nextLineOffset               = ") );Serial.println( nextLineOffset );
    Serial.print( F("  scalingThreshold[0]          = ") );Serial.print( scalingThreshold[1] );Serial.println();
    Serial.print( F("  scalingThreshold[1]          = ") );Serial.print( scalingThreshold[2] );Serial.println();
    Serial.print( F("  scalingThreshold[2]          = ") );Serial.print( scalingThreshold[3] );Serial.println();
    Serial.println();
  }
#endif
*/
};


// information for single wall display
// SIMPLE_WALL_INFO
class SIMPLE_WALL_INFO
{
public:

  // wall bitmap to use
  const uint8_t *wallBitmap;
  // screen start position for this bitmap
  int8_t   startPosX;
  // screen end position for this bitmap
  int8_t   endPosX;
  // start and end position for Y
  int8_t posStartEndY;
  // view distance of this object
  int8_t   viewDistance;
  // offset to left or right
  int8_t   leftRightOffset;
  // relative offset from left screen edge
  int8_t   relPos;
  // width off the bitmap/offset to the next line
  int8_t   width;
};

// interaction information
class INTERACTION_INFO
{
public:

  // position in which the dungeon is interacted with
  uint8_t currentPosition;
  // required status of this position
  uint8_t currentStatus;
  // new status if true
  uint8_t nextStatus;
  // bit coded item number for gained items, i.e. keys
  uint8_t newItem;
  // position in which the dungeon will be modified
  uint8_t modifiedPosition;
  // new status on modified position
  uint8_t modifiedPositionCellValue;

/*
#if !defined(__AVR_ATtiny85__)
  void serialPrint() 
  {
    Serial.println( F("INTERACTION_INFO") );
    Serial.print( F("  currentPosition    = ") );Serial.println( currentPosition );
    Serial.print( F("  currentStatus      = ") );printHexToSerial( currentStatus );Serial.println();
    Serial.print( F("  nextStatus         = ") );printHexToSerial( nextStatus );Serial.println();
    Serial.print( F("  newItem            = ") );printHexToSerial( newItem );Serial.println();
    Serial.print( F("  modifiedPosition   = ") );Serial.println( modifiedPosition );
    Serial.print( F("  modifiedPosValue   = ") );printHexToSerial( modifiedPositionCellValue );Serial.println();
    Serial.println();
  }
#endif
*/
};

// interaction information
class SPECIAL_CELL_INFO
{
public:

  // cell type
  uint8_t specialFX;
  // combined xy-position of the effect (as byte offset from level start)
  uint8_t position;
  // additional parameter 1 (target position x, ...)
  uint8_t value_1;
  // additional parameter 2 (target position y, ...)
  uint8_t value_2;

/*
#if !defined(__AVR_ATtiny85__)
  void serialPrint() 
  {
    Serial.print( F("  specialFX    = ") );if ( specialFX == TELEPORTER ) { Serial.println( F("TELEPORTER") ); } else { Serial.println( F("SPINNER") ); }
    Serial.print( F("  value        = (") );Serial.print( value_1 ); Serial.print( F(", ") );Serial.print( value_2 );Serial.println( F(")"));
    Serial.println();
  }
#endif
*/
};

// orientations
enum 
{
  NORTH = 0,
  UP    = NORTH,
  EAST  = 1,
  RIGHT = EAST,
  SOUTH = 2,
  DOWN  = SOUTH,
  WEST  = 3,
  LEFT  = WEST,
  MAX_ORIENTATION = 4,
};

#endif // _DUNGEONTYPES_H
