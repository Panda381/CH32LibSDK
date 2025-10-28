#pragma once

#include <Arduino.h>

#if !defined(__AVR_ATtiny85__)
  static uint8_t hexdumpPositionCount = 0;
  static uint8_t hexdumpValuesPerLine = 16;

  void hexdumpResetPositionCount();
  void hexdumpToSerial( uint8_t *pData, uint16_t byteCount, bool finalComma = false, bool finalLinebreak = true );
  #if defined(__AVR__)
  void EEPROM_hexdumpToSerial( uint16_t startAddress, uint16_t byteCount, bool finalComma = false, bool finalLinebreak = true );
  #endif
  void pgm_hexdumpToSerial( uint8_t *pData, uint16_t byteCount, bool finalComma = false, bool finalLinebreak = true );
  void printHexToSerial( uint8_t value, bool addComma = false );
  void printScreenBufferToSerial( const uint8_t *buffer, const uint8_t widthInPixels, const uint8_t heightInBytes );
#endif
