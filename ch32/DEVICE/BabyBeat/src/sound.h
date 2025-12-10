
// ****************************************************************************
//
//                         Music Player - Sound output
//
// ****************************************************************************
// Sound format: IMA ADPCM, 4-bit compression, stereo, 22050 Hz

#ifndef _SOUND_H
#define _SOUND_H

#ifdef __cplusplus
extern "C" {
#endif

// size of output buffer
#define OUTBUF_SIZE	1100		// number of samples in output buffer (1 sample = 2 bytes; valid range is 400..1200)

// output ports
#if BABYBEAT		// 1 = use BabyBeat device
// 2 ... PC5:ETR, PC6:CH1 (right), PC7:CH2 (left), PC0:CH3, PD3:CH4, PC1:BKIN, PC3:CH1N, PC4:CH2N, PD1:CH3N
#define AUDIOL_GPIO	PC7		// left, Timer1 channel 2
#define AUDIOR_GPIO	PC6		// right, Timer1 channel 1
#else
// 9 ... PB4:ETR, PA0:CH1, PA1:CH2 (right), PA2:CH3 (left), PA3:CH4, PB2:BKIN, PC0:CH1N, PC1:CH2N, PC2:CH3N
#define AUDIOL_GPIO	PA2		// left, Timer1 channel 2
#define AUDIOR_GPIO	PA1		// right, Timer1 channel 1
#endif

#if BABYBEAT		// 1 = use BabyBeat device
// volume
#define VOLMAX		9		// max. volume index
extern int Volume;			// current volume
extern int VolMul;			// current volume multiplier

// volume table
extern const int VolMulTab[VOLMAX+1];
#endif // BABYBEAT

// output buffer
typedef struct {
	u16		buf[OUTBUF_SIZE];	// output buffer
	volatile int	w;			// index of buffer to write to
	volatile int	r;			// index of buffer to read from
	u16		old[2];			// old values
} sOutBuf;
extern sOutBuf OutBuf;

// save sample to output buffer
void OutSamp(s16 samp);

// sound initialize
void SndInit(void);

#ifdef __cplusplus
}
#endif

#endif // _SOUND_H
