//
// This file works for TinyJoypad compatible devices.
//
// If not compiled for ATTiny85 (meaning __AVR_ATtiny85__ is not defined),
// generic functions are used instead of direct port access, which 
// makes it possible to use an Arduino or Mega2560 (or many others)
// for debugging with serial output or even hardware breakpoints.
//

// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#include "../include.h"

#if 0

//#include <Arduino.h>
//#include "TinyJoypadUtils.h"

#if defined(__AVR_ATtiny85__)
  #include <ssd1306xled.h>
#else
  // include Adafruit library and immediately create an object
  #include <Adafruit_SSD1306.h>
  Adafruit_SSD1306 display( 128, 64, &Wire, -1 );
  uint8_t *adafruitBuffer;

  // these functions are only required if a screenshot should be printed as a hexdump to the serial port
  #ifdef _ENABLE_SERIAL_SCREENSHOT_
    // include serial output functions
    #include "SerialHexTools.h"
  #endif
#endif

// buffered analog joystick inputs
uint16_t analogJoystickX;
uint16_t analogJoystickY;

/*-------------------------------------------------------*/
// function for initializing the TinyJoypad (ATtiny85) and other microcontrollers
void InitTinyJoypad()
{
#if defined(__AVR_ATtiny85__)
  // not using 'pinMode()' here saves ~100 bytes of flash!
  // configure A0, A3 and D1 as input
  SOUND_PORT_DDR &= ~( ( 1 << PB5) | ( 1 << PB3 ) | ( 1 << PB1 ) );
  // configure A2 (aka SOUND_PIN) as output
  SOUND_PORT_DDR |= ( 1 << SOUND_PIN );
#else
  // use 'pinMode()' for simplicity's sake... any other micro controller has enough flash :)
  pinMode( LEFT_RIGHT_BUTTON, INPUT );
  pinMode( UP_DOWN_BUTTON, INPUT );
  pinMode( FIRE_BUTTON, INPUT );
  // configure SOUND_PIN as output (Pin D12 on Arduino UNO R3 and Pin D10 on Arduino Mega 2560 )
  pinMode( SOUND_PIN, OUTPUT );

  // prepare serial port for debugging output
  Serial.begin( 115200 );
#endif
}

/*-------------------------------------------------------*/
bool isLeftPressed()
{
  uint16_t inputX = analogRead( LEFT_RIGHT_BUTTON );
  return( ( inputX >= ANALOG_UPPER_LIMIT_MIN ) && ( inputX < ANALOG_UPPER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool isRightPressed()
{
  uint16_t inputX = analogRead( LEFT_RIGHT_BUTTON );
  return( ( inputX > ANALOG_LOWER_LIMIT_MIN ) && ( inputX < ANALOG_LOWER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool isUpPressed()
{
  uint16_t inputY = analogRead( UP_DOWN_BUTTON );
  return( ( inputY > ANALOG_LOWER_LIMIT_MIN ) && ( inputY < ANALOG_LOWER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool isDownPressed()
{
  uint16_t inputY = analogRead( UP_DOWN_BUTTON );
  return( ( inputY >= ANALOG_UPPER_LIMIT_MIN ) && ( inputY < ANALOG_UPPER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool isFirePressed()
{
  return( digitalRead( FIRE_BUTTON ) == 0 );
}
#endif

/*-------------------------------------------------------*/
// wait until all buttons are released
void waitUntilButtonsReleased()
{
  while( isLeftPressed() || isRightPressed() || isUpPressed() || isDownPressed() || isFirePressed() );
}

/*-------------------------------------------------------*/
// wait until all buttons are released and wait a little delay
void waitUntilButtonsReleased( const uint8_t delayTime )
{
  waitUntilButtonsReleased();
  _delay_ms( delayTime );
}

#if 0

/*-------------------------------------------------------*/
// read analog joystick inputs into internal variables
void readAnalogJoystick()
{
  analogJoystickX = analogRead( LEFT_RIGHT_BUTTON );
  analogJoystickY = analogRead( UP_DOWN_BUTTON );
}

/*-------------------------------------------------------*/
bool wasLeftPressed()
{
  return( ( analogJoystickX >= ANALOG_UPPER_LIMIT_MIN ) && ( analogJoystickX < ANALOG_UPPER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool wasRightPressed()
{
  return( ( analogJoystickX > ANALOG_LOWER_LIMIT_MIN ) && ( analogJoystickX < ANALOG_LOWER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool wasUpPressed()
{
  return( ( analogJoystickY > ANALOG_LOWER_LIMIT_MIN ) && ( analogJoystickY < ANALOG_LOWER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
bool wasDownPressed()
{
  return( ( analogJoystickY >= ANALOG_UPPER_LIMIT_MIN ) && ( analogJoystickY < ANALOG_UPPER_LIMIT_MAX ) );
}

/*-------------------------------------------------------*/
uint16_t getAnalogValueX()
{
  return( analogJoystickX );
}

/*-------------------------------------------------------*/
uint16_t getAnalogValueY()
{
  return( analogJoystickY );
}

/*-------------------------------------------------------*/
void __attribute__ ((noinline)) _variableDelay_us( uint8_t delayValue )
{
  while ( delayValue-- != 0 )
  {
    _delay_us( 1 );
  }
}

/*-------------------------------------------------------*/
// This code was originaly borrowed from Daniel C's Tiny-invaders :)
// Code optimization by sbr
void Sound( const uint8_t freq, const uint8_t dur )
{
  for ( uint8_t t = 0; t < dur; t++ )
  {
#if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
    if ( freq != 0 ){ SOUND_PORT = SOUND_PORT | ( 1 << SOUND_PIN); }
    _variableDelay_us( 255 - freq );
    SOUND_PORT = SOUND_PORT & ~( 1 << SOUND_PIN );
    _variableDelay_us( 255 - freq );
#else
    if ( freq != 0 ){ digitalWrite( SOUND_PIN, 1 ); }
    _variableDelay_us( 255 - freq );
    digitalWrite( SOUND_PIN, 0 );
    _variableDelay_us( 255 - freq );
#endif
  }
}

/*-------------------------------------------------------*/
void InitDisplay()
{
#if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
  #if defined( _SSD1306XLED_TINY_INIT_SUPPORTED_ )
    // library supports shorter init method
    SSD1306.ssd1306_tiny_init();
  #else
    // use standard init method
    SSD1306.ssd1306_init();
  #endif
#else
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // Address 0x3D for 128x64
  if( !display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
    // extended the error message
    Serial.println(F("SSD1306 allocation failed - 1024 bytes for frame buffer required!")); for(;;);
  }
#endif
}

u8 DispOutPage = 0;	// current output page (0..7)
u8 DispOutX = 0;	// current output X (0..127)

/*-------------------------------------------------------*/
// This code will init the display for row <y>
void PrepareDisplayRow( uint8_t y )
{
	DispOutPage = y;
	DispOutX = 0;

#if defined(__AVR_ATtiny85__)  /* codepath for ATtiny85 */
    // initialize image transfer to segment 'y'
    SSD1306.ssd1306_send_command(0xb0 + y);
  #ifdef _USE_SH1106_
    // SH1106 internally uses 132 pixels/line,
    // output is (always?) centered, so we need to start at position 2
    SSD1306.ssd1306_send_command(0x02);
    SSD1306.ssd1306_send_command(0x10);  
  #else
    // classic SSD1306 supports only 128 pixels/line, so we start at 0
    SSD1306.ssd1306_send_command(0x00);
    SSD1306.ssd1306_send_command(0x10);  
  #endif    
    SSD1306.ssd1306_send_data_start();

#else  /* codepath for any Adafruit_SSD1306 supported MCU */

  // address the display buffer
  adafruitBuffer = display.getBuffer() + ( y * 128 );
#endif

}

/*-------------------------------------------------------*/
void SendPixels( uint8_t pixels )
{
	int y = DispOutPage;
	int x = DispOutX;

	u8* d = &FrameBuf[(x >> 3) + ((16 >> 3) + 28*WIDTHBYTE) + y*(WIDTHBYTE*8)];
	u8 mask = 1 << (7 - (x & 7));
	if ((pixels & B0) == 0) d[0*WIDTHBYTE] &= ~mask; else d[0*WIDTHBYTE] |= mask;
	if ((pixels & B1) == 0) d[1*WIDTHBYTE] &= ~mask; else d[1*WIDTHBYTE] |= mask;
	if ((pixels & B2) == 0) d[2*WIDTHBYTE] &= ~mask; else d[2*WIDTHBYTE] |= mask;
	if ((pixels & B3) == 0) d[3*WIDTHBYTE] &= ~mask; else d[3*WIDTHBYTE] |= mask;
	if ((pixels & B4) == 0) d[4*WIDTHBYTE] &= ~mask; else d[4*WIDTHBYTE] |= mask;
	if ((pixels & B5) == 0) d[5*WIDTHBYTE] &= ~mask; else d[5*WIDTHBYTE] |= mask;
	if ((pixels & B6) == 0) d[6*WIDTHBYTE] &= ~mask; else d[6*WIDTHBYTE] |= mask;
	if ((pixels & B7) == 0) d[7*WIDTHBYTE] &= ~mask; else d[7*WIDTHBYTE] |= mask;

	x++;
	if (x >= 128)
	{
		x = 0;
		DispOutPage++;
	}

	DispOutX = x;

#if defined(__AVR_ATtiny85__) /* codepath for ATtiny85 */
  // send a byte directly to the SSD1306
  SSD1306.ssd1306_send_byte( pixels );

#else  /* codepath for any Adafruit_SSD1306 supported MCU */
  // write pixels directly to the buffer
  *adafruitBuffer++ = pixels;
#endif

}

/*-------------------------------------------------------*/
// This code will finish a row (only on Tiny85)
void FinishDisplayRow()
{
#if defined(__AVR_ATtiny85__)
  // this line appears to be optional, as it was never called during the intro screen...
  // but hey, we still have some bytes left ;)
  SSD1306.ssd1306_send_data_stop();
#endif
}

/*-------------------------------------------------------*/
void DisplayBuffer()
{
#if !defined(__AVR_ATtiny85__) /* codepath for any Adafruit_SSD1306 supported MCU */
  // display buffer (not necessary)
  display.display();

  // slow down fast microcontrollers
  #if defined(_VARIANT_ARDUINO_ZERO_)
    // wait 100ms to compensate for extremely fast hardware i2c
    delay( 100 );
  #endif
  
  #ifndef _SERIAL_SCREENSHOT_NO_AUTO_SHOT_
    // check for screenshot request
    CheckForSerialScreenshot();
  #endif
#endif
}

/*-------------------------------------------------------*/
// Output is one hex byte per pixel. To get the actual image perform the following steps:
// (1) The output can be converted to binary with 'https://tomeko.net/online_tools/hex_to_file.php?lang=en' online.
// (2) Then import the file with IrfanView (https://www.irfanview.com/): Open as -> RAW file...
// (3) Set Image width to 64 and Image height to 128, 8 BPP -> OK
// (4) Rotate and mirror the result as needed :)
void SerialScreenshot()
{
#if !defined(__AVR_ATtiny85__) /* codepath for any Adafruit_SSD1306 supported MCU */
  #ifdef _ENABLE_SERIAL_SCREENSHOT_
    // print a short header
    Serial.println( F("\r\nThis is a TinyJoypad screenshot. Output is one hex byte per pixel. To get the actual image perform the following steps:") );
    Serial.println( F("(1) The output can be converted to binary with 'https://tomeko.net/online_tools/hex_to_file.php?lang=en' online.") );
    Serial.println( F("(2) Then import the file with IrfanView (https://www.irfanview.com/): Open as -> RAW file...") );
    Serial.println( F("(3) Set Image width to 64 and Image height to 128, 8 BPP -> OK") );
    Serial.println( F("(4) Rotate and mirror the result as needed :)\r\n") );
    Serial.println( F("Hint: If you only get partial screenshots, try using a terminal program to capture the serial output.") );
    // output the full buffer as a hexdump to the serial port
    printScreenBufferToSerial( display.getBuffer(), 128, 8 );
  #endif
#endif
}

/*-------------------------------------------------------*/
// Perform a screenshot if 
//  [x] enabled and 
//  [x] trigger condition met
void CheckForSerialScreenshot()
{
#if !defined(__AVR_ATtiny85__) /* codepath for any Adafruit_SSD1306 supported MCU */
  #ifdef _ENABLE_SERIAL_SCREENSHOT_
    if ( _SERIAL_SCREENSHOT_TRIGGER_CONDITION_ )
    {
      // perform the screenshot
      SerialScreenshot();
    }
  #endif
#endif
}

///////////////////////////////////////////////////////////////////////////////////
// serial output without clustering the code with #if !defined(__AVR_ATtiny85__)...

/*-------------------------------------------------------*/
void serialPrint( const char *text )
{
#ifdef USE_SERIAL_PRINT
  Serial.print( text );
#endif
}

/*-------------------------------------------------------*/
void serialPrintln( const char *text )
{
#ifdef USE_SERIAL_PRINT
  Serial.println( text );
#endif
}

/*-------------------------------------------------------*/
void serialPrint( const __FlashStringHelper *text )
{
#ifdef USE_SERIAL_PRINT
  Serial.print( text );
#endif
}

/*-------------------------------------------------------*/
void serialPrintln( const __FlashStringHelper *text )
{
#ifdef USE_SERIAL_PRINT
  Serial.println( text );
#endif
}

/*-------------------------------------------------------*/
void serialPrint( const unsigned int number )
{
#ifdef USE_SERIAL_PRINT
  Serial.print( number );
#endif
}

/*-------------------------------------------------------*/
void serialPrintln( const unsigned int number )
{
#ifdef USE_SERIAL_PRINT
  Serial.println( number );
#endif
}

/*-------------------------------------------------------*/
void serialPrint( const int number )
{
#ifdef USE_SERIAL_PRINT
  Serial.print( number );
#endif
}

/*-------------------------------------------------------*/
void serialPrintln( const int number )
{
#ifdef USE_SERIAL_PRINT
  Serial.println( number );
#endif
}

#endif
