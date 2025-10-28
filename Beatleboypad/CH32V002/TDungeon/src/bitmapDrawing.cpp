
// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#include "../include.h"

/*
#include "bitTables.h"
#include "dungeon.h"
#include "monsterBitmaps.h"
#include "objectBitmaps.h"
#include "wallBitmaps.h"
*/

/*--------------------------------------------------------*/
uint8_t Dungeon::getWallPixels( const int8_t x, const int8_t y )
{
  uint8_t pixels = 0;

  SIMPLE_WALL_INFO wallInfo;
  
  const SIMPLE_WALL_INFO *wallInfoPtr = arrayOfWallInfo;

  // all objects are visible
  int8_t maxObjectDistance = MAX_VIEW_DISTANCE;

  //int8_t objectNo = -1;

  // iterate through the whole list (at least as long as it's necessary)
  while( true )
  {
    // the structure resides in PROGMEM, so we need to copy it to RAM first...
    memcpy_P( &wallInfo, wallInfoPtr, sizeof( wallInfo ) );

    // end of list reached?
    if ( wallInfo.wallBitmap == nullptr ) { break; }
    
    //objectNo++;

    // check conditions
    if ( ( x >= wallInfo.startPosX ) && ( x <= wallInfo.endPosX ) )
    {
      bool mirror = ( ( _dungeon.playerX + _dungeon.playerY ) & 0x01 );

      // is there a wall object?
    #ifdef _USE_FIELD_OF_VIEW_
      if ( ( getCell( wallInfo.viewDistance, wallInfo.leftRightOffset ) & WALL_MASK ) == ( WALL & ~FLAG_SOLID ) )
    #else
      if ( ( *( getCellRaw( _dungeon.playerX, _dungeon.playerY, wallInfo.viewDistance, wallInfo.leftRightOffset, _dungeon.dir ) ) & WALL_MASK ) == ( WALL & ~FLAG_SOLID ) )
    #endif
      {
        //if ( y == 0 ) { Serial.print( F("column = ") ); Serial.print( x ); Serial.print( F(" -> objectNo = ") ); Serial.println( objectNo ); }

        // split combined positions into start and end
        int8_t startPosY = wallInfo.posStartEndY / 16;
        int8_t endPosY = wallInfo.posStartEndY & 0x0f;

        // is there wall information for this vertical position
        if ( ( y >= startPosY ) && ( y <= endPosY ) )
        {
          uint8_t offsetX;

          // is the bitmap smaller than the screen?
          bool smallBitmap = ( wallInfo.width < WINDOW_SIZE_X );

          if ( smallBitmap )
          {
            // positions are to be considered relative to the bitmap
            int8_t posX = x - wallInfo.startPosX;

            if ( mirror )
            {
              offsetX = wallInfo.width - 1 - posX - wallInfo.relPos;
            }
            else
            {
              offsetX = posX + wallInfo.relPos;
            }
          }
          else
          {
            // mirror walls on odd fields
            offsetX = mirror ? ( WINDOW_SIZE_X - 1 ) - x : x;
          }

          // get wall pixels (shave off the empty rows)
          pixels = pgm_read_byte( wallInfo.wallBitmap + ( y - startPosY ) * wallInfo.width + offsetX );

        #ifdef _ENABLE_SHADING_
          switch ( wallInfo.viewDistance )
          {
            case 0:
            case 1:
              break;
            case 2:
              if ( x & 1 ) { pixels &= 0x55; }
              else { pixels &= 0xaa; }
              break;
            default:
              if ( x & 1 ) { pixels &= 055; }
              else { pixels &= 0x00; }
          }
        #endif
        }
        else
        {
          // nope, just nothing
          pixels = 0;
        }
        // objects behind walls are not visible, but doors or switches might be placed *on* walls
        maxObjectDistance = wallInfo.viewDistance;
        // that's it!
        break;
      }
    }
    // move to next entry
    wallInfoPtr++;
  }

  NON_WALL_OBJECT object;

  // draw NWOs (Non Wall Objects) over the background pixels (with mask!)
  for ( uint8_t distance = maxObjectDistance; distance > 0; distance-- )
  {
    for ( uint8_t n = 0; n < sizeof( objectList ) / sizeof( objectList[0] ); n++ )
    {
      memcpy_P( &object, &objectList[n], sizeof( object ) );
      uint8_t objectWidth = object.bitmapWidth >> distance;

      // non wall objects will only be rendered if directly in front of the player (for now!)
      if ( ( x >= WINDOW_CENTER_X - objectWidth ) && ( x < WINDOW_CENTER_X + objectWidth ) )
      {
      #ifdef _USE_FIELD_OF_VIEW_
        if ( ( getCell( distance, 0 ) & OBJECT_MASK ) == object.itemType )
      #else
        if ( ( *( getCellRaw( _dungeon.playerX, _dungeon.playerY, distance, 0, _dungeon.dir ) ) & OBJECT_MASK ) == object.itemType )
      #endif
        {
          objectWidth = WINDOW_CENTER_X - objectWidth;
          uint8_t posX = x - objectWidth;
          // free background
          uint8_t mask = getDownScaledBitmapData( posX, y, distance, &object, true );
          pixels &= mask;
          // and overlay scaled bitmap
          uint8_t scaledBitmap = getDownScaledBitmapData( posX, y, distance, &object, false );

        #ifdef _ENABLE_SHADING_
          // shading effect to pronounce the distance of an object
          switch ( distance )
          {
            case 0:
            case 1:
              break;
            case 2:
              if ( x & 1 ) { scaledBitmap &= 0x55; }
              else { scaledBitmap &= 0xaa; }
              break;
            default:
              if ( x & 1 ) { scaledBitmap &= 055; }
              else { scaledBitmap &= 0x00; }
          }
        #endif

          if ( distance == 1 )
          {
            // invert monster?!
            scaledBitmap ^= ( _dungeon.invertMonsterEffect & ~mask );
          }
          pixels |= scaledBitmap;
        }
      }
    }
  }
  
  return( pixels );
}

/*--------------------------------------------------------*/
// Returns the downscaled bitmap data at position x,y.
// Supported distance values are 1, 2, 3.
// Note that x is scaled by the scale factor for
// the current distance, while y remains unscaled!
uint8_t Dungeon::getDownScaledBitmapData( int8_t x,                      // already downscaled by 1 << ( distance - 1 )
                                          int8_t y,                      // unscaled vertical position
                                          const uint8_t distance,        // supported values are 1..3
                                          const NON_WALL_OBJECT *object, // current non wall object
                                          bool useMask                   // if true returns the down scaled mask instead of the bitmap
                                        )
{
  uint8_t pixels = 0;

  // get start address (and add optional offset for mask)
  const uint8_t *bitmapData = object->bitmapData;
  if ( useMask ) { bitmapData += object->bitmapWidth; }

  // Get scaling factor from LUT (efficient and still flexible).
  uint8_t scaleFactor = pgm_read_byte( scalingFactorFromDistance + distance );
  // get threshold (distance is 1..3, so subtract 1 (at no cost!))
  const uint8_t threshold = object->scalingThreshold[distance - 1];

  // is there anything to be done?
  uint8_t startOffsetY = pgm_read_byte( verticalStartOffset + distance );
  uint8_t endOffsetY = pgm_read_byte( verticalEndOffset + distance );

  if ( ( y >= startOffsetY ) && ( y <= endOffsetY ) )
  {
    // modify positions in source bitmap by scaling factor
    x = x * scaleFactor;
    // correct y position by start offset
    y -= startOffsetY;
    
    // get associated bit mask
    uint8_t bitMask = pgm_read_byte( bitMaskFromScalingFactor + scaleFactor );

    // calculate the first and last bit to be processed
    uint8_t startBitNo = object->bitmapVerticalOffsetInBits;
    uint8_t endBitNo = startBitNo + object->bitmapHeightInBits;
    
    // but we are starting with bit 0 (and its friends)
    uint8_t bitNo = y * 8 * scaleFactor;
  
    // We need to calculate 8 vertical output bits...
    // NOTE: Because the Tiny85 only supports shifting by 1 bit, it is
    //       more efficient to do the shifting in the 'for' loop instead
    //       of using a ( 1 << n ) construct.
    for ( uint8_t bitValue = 1; bitValue != 0; bitValue <<= 1 )
    {
      uint8_t bitSum = 0;
  
      if ( ( bitNo >= startBitNo ) && ( bitNo <  endBitNo ) )
      {
        // calculate start address
        uint8_t row = ( bitNo - startBitNo ) / 8;
        const uint8_t *data = bitmapData + row * object->nextLineOffset + x;
        
        // go over the columns - all required bits always are in one row
        for ( uint8_t col = 0; col < scaleFactor; col++ )
        {
          // to get the output value, we will sum all the bits up (using a lookup table saves time and flash space)
          bitSum += pgm_read_byte( nibbleBitCount + ( ( pgm_read_byte( data++ ) >> ( bitNo & 0x07 ) ) & bitMask ) );
        }
      }
      else if ( useMask )
      {
        // make bitsum count - otherwise we will erase the backgound
        bitSum += scaleFactor * scaleFactor;
      }
  
      // next bit position
      bitNo += scaleFactor;

      // calculate output pixel
      if ( bitSum >= threshold )
      {
        pixels |= bitValue;
      }
    } // for
  }
  // no bits here, set mask to 0xff
  else if ( useMask )
  { 
    pixels--;
  }
                                     
  return( pixels );  
}
