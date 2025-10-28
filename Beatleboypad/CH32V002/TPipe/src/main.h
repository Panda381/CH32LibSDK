
#ifndef _MAIN_H
#define _MAIN_H

//#ifdef __cplusplus
//extern "C" {
//#endif

// format: 1-bit pixel graphics
// image width: 51 pixels
// image height: 8 lines
// image pitch: 7 bytes
//extern const u8 ImgIntro[56];

#define PROGMEM
//INLINE u8 pgm_read_byte(const u8* addr) { return *addr; }
INLINE u8 pgm_read_byte(const void* addr) { return *(u8*)addr; }

#define BLACK 0
#define WHITE 1

#define LOW 0
#define HIGH 1
typedef u8 uint8_t;
typedef s8 int8;
typedef s8 int8_t;
typedef u16 uint16_t;
typedef s16 int16_t;

//INLINE u32 random(void ) { return RandU32(); }

// Game setup
void setup();

// Main program loop
void loop();

// delay [ms]
INLINE void delay(int ms) { WaitMs(ms); }
INLINE void _delay_ms(int ms) { WaitMs(ms); }

// play sound tone
void Sound(uint8_t freq, uint8_t dur);

//#ifdef __cplusplus
//}
//#endif

#endif // _MAIN_H
