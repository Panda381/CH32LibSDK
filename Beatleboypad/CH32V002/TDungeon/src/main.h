
#ifndef _MAIN_H
#define _MAIN_H

#define PROGMEM
INLINE u8 pgm_read_byte(const u8* addr) { return *addr; }

typedef u8 uint8_t;
typedef s8 int8;
typedef s8 int8_t;
typedef u16 uint16_t;
typedef s16 int16_t;

// delay [ms]
INLINE void delay(int ms) { WaitMs(ms); }
INLINE void _delay_ms(int ms) { WaitMs(ms); }
INLINE void _delay_us(int us) { WaitUs(us); }

#define memcpy_P memcpy

// play sound tone
void Sound(uint8_t freq, uint8_t dur);

#endif // _MAIN_H
