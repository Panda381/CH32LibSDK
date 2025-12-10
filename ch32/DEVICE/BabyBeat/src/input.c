
// ****************************************************************************
//
//                         Music Player - Input file
//
// ****************************************************************************

#include "../include.h"

// input buffer
sInBuf InBuf;

// WAV format
#pragma pack(push,1)
// WAV format descriptor (32 bytes)
typedef struct WAVFORMAT_ {
	char			tFormatIdent[8];	// 0x08: (8) format identifier (= "WAVEfmt ")
	u32			nFormatSize;		// 0x10: (4) size of following format data (= 20 = 0x14)

	u16			wFormatTag;		// 0x14: (2) data format (1 = PCM, 17 = 0x11 = Intel DVI ADPCM)
	u16			nChannels;		// 0x16: (2) number of channels (1 = mono, 2 = stereo)
	u32			nSamplesPerSec;		// 0x18: (4) sample frequency (number of samples per second; = 22050 = 0x5622)
	u32			nAvgBytesPerSec;	// 0x1C: (4) transfer rate (number of bytes per second)
	u16			nBlockAlign;		// 0x20: (2) data align (PCM: bits*channels/8; ADPCM: 1024 = 0x400)

	u16			wBitsPerSample;		// 0x22: (2) number of bits per one sample (= 4)

	u16			wExtraByte;		// 0x24: (2) ADPCM: number of following extra bytes (= 2)
	u16			wSampBlock;		// 0x26: (2) ADPCM: number of samples per block including 1st sample in preamble header (= 1017 = 0x3F9, 1 blok = 8 + 1016 = 1024 B)
							// 0x28

// ADPCM: Each block starts with 4 bytes of preamble (stereo starts with 2 preambles):
//  s16	... audio sample (= 1st sample, initial predictor)
//  u8 ... table index
//  u8 ... dummy byte (= 0)
// 1st data sample is in LOW 4 bits, nest sample is in HIGH 4 bits
} WAVFORMAT;

// WAV data descriptor (8 Bytes)
typedef struct WAVDATA_ {
	char			tDataIdent[4];		// 0x00: (4) data identifier "data"
	u32			nDataSize;		// 0x04: (4) size of following sound data
} WAVDATA;

// WAV file header (44 B)
typedef struct WAVHEAD_ {
	char		tWavIdent[4];		// 0x00: (4) file identifier (= "RIFF")
	u32		nFileSize;		// 0x04: (4) size of following file data

	WAVFORMAT	WavFormat;		// 0x08: (32) format descriptor
						// ... some other chunks
	WAVDATA		WavData;		// data block
} WAVHEAD;
#pragma pack( pop )

// load input buffer
void Load()
{
	// pointer to input buffer descriptor
	sInBuf* in = &InBuf;

	// shift remaining data
	int d = in->inx;
	int n = in->num - d;
	if (n > 0) memmove(in->buf, &in->buf[d], n);
	in->num = n;
	in->inx = 0;

	// read next data
	in->num += FileRead(&in->file, &in->buf[n], INBUF_SIZE - n);

	// there is some error - we only quiet data and break playing
	if (in->num <= 0)
	{
		in->num = INBUF_SIZE;
		in->err = True;
	}
}

// load next byte from input file
u8 GetByte()
{
	// pointer to input buffer descriptor
	sInBuf* in = &InBuf;

	// load buffer
	int inx = in->inx;
	int n = in->num;
	if (inx >= n)
	{
		Load();
		inx = in->inx;
		n = in->num;
	}

	u8 b = 0;
	if (inx < n)
	{
		b = in->buf[inx];
		in->inx = inx + 1;
	}
	return b;
}

// seek input file (inx = new index of the sample)
void InSeek(int inx)
{
	// pointer to descriptors
	sAdpcm* a = &Adpcm;
	sInBuf* in = &InBuf;

	// limit sample index
	if (inx < 0) inx = 0;
	if (inx >= a->sampnum) inx = a->sampnum-1;

	// align index to whole preamble block
	inx /= a->sampblock; // index of preamble block
	int off = in->dataoffset + in->blocksize*inx; // offset in the file
	inx *= a->sampblock; // index of the sample

	// set new current index
	a->sampinx = inx;

	// reset decompressor
	a->sampcnt = 0; // end of preamble block

	// reset input buffer
	in->num = 0; // no data in input buffer
	in->inx = 0; // reset input index

	// set file pointer
	FileSeek(&in->file, off);
}

// start new file (returns False if file is invalid)
Bool StartFile(const char* name)
{
	Bool res;

	// pointer to descriptors
	sAdpcm* a = &Adpcm;
	sInBuf* in = &InBuf;

	// open file
	if (!FileOpen(&InBuf.file, name)) return False;

	// reset error flag
	in->err = False;

	// read header to input buffer
	u8* s = in->buf;
	int n = FileRead(&in->file, s, INBUF_SIZE);

	// invalid file
	if (n < INBUF_SIZE) return False;

	// pointer to header
	//  We do not check the file format. In case of an error, the user will hear a bad noise 
	//  to let him know that the file has the wrong format and needs to be corrected.
	WAVHEAD* wav = (WAVHEAD*)s;
	WAVFORMAT* fmt = &wav->WavFormat;
	WAVDATA* data = (WAVDATA*)((u8*)fmt + 12 + (u16)fmt->nFormatSize);

	// number of samples per block
	a->sampblock = fmt->wSampBlock;

	// search start of data
	int i;
	for (i = 10; i > 0; i--)
	{
		if (	(data->tDataIdent[0] == 'd') &&
			(data->tDataIdent[1] == 'a') &&
			(data->tDataIdent[2] == 't') &&
			(data->tDataIdent[3] == 'a'))
			break;

		data = (WAVDATA*)((u8*)data + 8 + data->nDataSize);
		if (((u8*)data - s) > INBUF_SIZE) return False; // header is out of buffer
	}

	// prepare total number of stereo-samples
	int num = data->nDataSize; // data size
	int blocksize = fmt->nBlockAlign; // size of one preamble block
	in->blocksize = blocksize;	// sabe block size
	int blocknum = num/fmt->nBlockAlign; // get number of whole data blocks
	int sampnum = blocknum*fmt->wSampBlock; // number of samples in whole data blocks
	num -= blocknum*fmt->nBlockAlign; // remaining data size
	if (num >= 8) // at least preamble header?
	{
		sampnum++; // add preamnle header
		num -= 8;
		sampnum += num; // add remaining samples (1 byte = 1 stereo-sample)
	}
	a->sampnum = sampnum; // total number of samples
	a->pause = False;	// playing is paused

	// offset of start of data
	int off = (u8*)&data[1] - s;
	in->dataoffset = off;	// offset of start of data in the file

	// seek to start of data
	InSeek(0);

	// all OK
	return True;
}
