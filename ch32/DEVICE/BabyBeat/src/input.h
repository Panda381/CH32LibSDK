
// ****************************************************************************
//
//                         Music Player - Input file
//
// ****************************************************************************

#ifndef _INPUT_H
#define _INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

// input buffer size
// - The input buffer must be large enough to hold the entire WAV file header up to the start of the data.
#define INBUF_SIZE	512		// number of bytes in input buffer

// input buffer
typedef struct {
	u8		buf[INBUF_SIZE];	// input buffer
	int		num;			// number of bytes in input buffer
	int		inx;			// index in input buffer
	sFile		file;			// input file
	s16		dataoffset;		// offset of start of data in the file
	s16		blocksize;		// size of preamble block in bytes
	Bool		err;			// error flag - break this file
} sInBuf;
extern sInBuf InBuf;

// load input buffer
void Load();

// load next byte from input file
u8 GetByte();

// seek input file (inx = new index of the sample)
void InSeek(int inx);

// start new file (returns False if file is invalid)
Bool StartFile(const char* name);

#ifdef __cplusplus
}
#endif

#endif // _INPUT_H
