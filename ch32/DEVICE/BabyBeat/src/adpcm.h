
// ****************************************************************************
//
//                    Music Player - IMA ADPCM decompression
//
// ****************************************************************************

#ifndef _ADPCM_H
#define _ADPCM_H

#ifdef __cplusplus
extern "C" {
#endif

// ADPCM decompressor
typedef struct {
	int	sampinx;	// current index of stereo-sample
	int	sampnum;	// total number of stereo-samples
	s16	sampblock;	// number of samples per block (0 = no preamble)
	s16	sampcnt;	// counter of samples per block (0 = end of block)
	s16	prevval[2];	// previous value
	s8	stepinx[2];	// step index
	Bool	odd;		// odd sub-sample
	u8	byte4;		// counter of 4-byte
	u8	cache[3];	// cache of 4-byte
	u8	subsample[2];	// save sub-sample
	Bool	pause;		// playing is paused
} sAdpcm;

extern sAdpcm Adpcm;

#define SAMPSKIP	(22050*10)	// number of samples to skip in fast seek

// ADPCM decompression (returns key code)
u8 Decomp();

#ifdef __cplusplus
}
#endif

#endif // _ADPCM_H
