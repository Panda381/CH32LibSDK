#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable : 4996) // unsafe fopen

//#define TEST		// uncomment to test unpack to buffer ImgTest

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long int s32;		// on 64-bit system use "signed int"
typedef unsigned long int u32;		// on 64-bit system use "unsigned int"

typedef unsigned int BOOL;
#define TRUE  1
#define FALSE 0

#pragma pack(push,1)
typedef struct _bmpBITMAPFILEHEADER { // 14 bytes
		u16		bfType;
		u32		bfSize;
		u16		bfReserved1;
		u16		bfReserved2;
		u32		bfOffBits;
} bmpBITMAPFILEHEADER;

typedef struct _bmpBITMAPINFOHEADER{ // 40 bytes at offset 0x0E
		u32		biSize;
		s32		biWidth;
		s32		biHeight;
		u16		biPlanes;
		u16		biBitCount;
		u32		biCompression;
		u32		biSizeImage;
		s32		biXPelsPerMeter;
		s32		biYPelsPerMeter;
		u32		biClrUsed;
		u32		biClrImportant;
		// palettes at offset 54 = 0x36
} bmpBITMAPINFOHEADER;
#pragma pack(pop)

#define bmpBI_RGB	0

#define LENMAX	7	// max. length of stream chunk

u8* Img; // input file buffer
#ifdef TEST
u8* ImgTest; // test buffer
#endif
u8* ImgOut[LENMAX+1]; // output file buffer, 1..7-bit stream
int OutNum[LENMAX+1]; // number of bytes
int W,H,WBS; // input file width and height
int B; // bit count

// input stream
u8* S; // source image
u8 InByteCache;
int InByteBits = 0;
int InByteWidth;

// output stream
u8* D; // destination image
u8 OutByteCache = 0;
int OutByteBits = 0;

// input bit stream (returns value 0 or 1)
int InBit()
{
	// skip bits on end of line
	if (InByteWidth == 0)
	{
		InByteWidth = WBS*8 - W;
		while (InByteWidth > 0) InBit();
		InByteWidth = W;
	}

	// no bits left in the cache
	if (InByteBits == 0)
	{
			InByteCache = *S++; // get next input byte
			InByteBits = 8;	// refresh number of input bits
	}

	// skip bits
	InByteWidth--;

	// get bit from cache
	int bit = (InByteCache >> 7) & 1;
	InByteCache <<= 1;
	InByteBits--;

	return bit;
}

// flush output bit stream
void OutFlush()
{
	if (OutByteBits > 0)
	{
		if (OutByteBits < 8) OutByteCache <<= 8 - OutByteBits;
		*D++ = OutByteCache;
		OutByteCache = 0;
		OutByteBits = 0;
	}
}

// output bit stream (output bit 0 or 1)
void OutBit(int bit)
{
	bit &= 1;
	OutByteCache <<= 1;
	OutByteCache |= bit;
	OutByteBits++;
	if (OutByteBits == 8) OutFlush();
}

// output bit stream group (len = number of bits)
void OutBitNum(int val, int len)
{
	for (; len > 0; len--)
	{
		OutBit(val >> (len - 1));
	}
}

// RLE compression (len = number of bits per chunk)
void Comp(int len)
{
	InByteWidth = W;
	InByteBits = 0;
	OutByteBits = 0;
	OutByteCache = 0;

	int n, bit, bitnum, prevbit;
	int max = (1 << len) - 1;

	// output image size - 1
	OutBitNum(W-1, 8);
	OutBitNum(H-1, 8);

	// output stream size as 3 bits
	OutBitNum(len, 3);

	// len <= 1, simple copy
	if (len <= 1)
	{
		for (n = W*H; n > 0; n--) OutBit(InBit());
		OutFlush();
		return;
	}

	// get first bit
	prevbit = InBit();
	bitnum = 1;

	// if not default bit 0, switch color
	if (prevbit != 0)
	{
		OutBitNum(0, len);
	}

	for (n = W*H-1; n > 0; n--)
	{
		// get next bit
		bit = InBit();

		// read first bit of next chunk
		if (bitnum == 0)
		{
			prevbit = bit;
			bitnum = 1;
			continue;
		}

		// check next bit
		if (bit != prevbit)
		{
			// flush stream
			OutBitNum(bitnum, len);
			bitnum = 1;
			prevbit = bit;
			continue;
		}

		// count this bit
		bitnum++;

		// overflow number of bits
		if (bitnum > max)
		{
			OutBitNum(max, len);
			bitnum -= max;

			// switch color
			OutBitNum(0, len);
		}
	}

	// flush stream
	OutBitNum(bitnum, len);
	OutFlush();
}

void Help()
{
		printf("Syntax: PimitachiImg in_file.bmp out_file.c img_name bit\n");
		printf("            bit ... number of bits per chunk 1..%d, 0=auto\n", LENMAX);
}

#ifdef TEST
// ========== test
// get bits from RLE compression
const u8* RleData;
u8 RleByteCache;
u8 RleByteBits;

int RleBit()
{
	if (RleByteBits == 0)
	{
		RleByteCache = *RleData++;
		RleByteBits = 8;
	}
	int bit = (RleByteCache >> 7) & 1;
	RleByteCache <<= 1;
	RleByteBits--;
	return bit;
}

int RleBitNum(int len)
{
	int d = 0;
	for (; len > 0; len--)
	{
		d <<= 1;
		d |= RleBit();
	}
	return d;
}

// test decompression
void Test(u8* dst, const u8* src)
{
	OutByteBits = 0;
	OutByteCache = 0;
	InByteWidth = W;
	D = dst;

	// prepare variables
	RleData = src;
	RleByteBits = 0;

	// get image size and stream size
	int w = RleBitNum(8) + 1;
	int h = RleBitNum(8) + 1;
	int len = RleBitNum(3);
	int i = w*h;

	// simple copy
	if (len < 2)
	{
		for (; i > 0; i--)
		{
			OutBit(RleBit());
			InByteWidth--;
			if (InByteWidth == 0)
			{
				if (WBS*8 > W) OutBitNum(0, WBS*8-W);
				InByteWidth = W;
			}
		}
	}

	else
	{
		// prepare first chunk (it will be 0)
		int col = 0;
		int n = RleBitNum(len);

		for (; i > 0; i--)
		{
			// next chunk
			while (n == 0)
			{
				n = RleBitNum(len);
				col ^= 1;
			}

			OutBit(col);
			InByteWidth--;
			if (InByteWidth == 0)
			{
				if (WBS*8 > W) OutBitNum(0, WBS*8-W);
				InByteWidth = W;
			}
			n--;
		}
	}
	OutFlush();

	FILE* f = fopen("test.bmp", "wb");
	fwrite(ImgTest, 1, (int)(D - ImgTest), f);
	fclose(f);
}
#endif // TEST

// main function
int main(int argc, char* argv[])
{
	int i, n;

	if ((sizeof(_bmpBITMAPFILEHEADER) != 14) ||
		(sizeof(_bmpBITMAPINFOHEADER) != 40))
	{
		printf("Incorrect size of data types. Check typedef of s32/u32 or do 32-bit compilation.\n");
		return 1;
	}

	// check syntax
	if (argc != 5)
	{
		Help();
		return 1;
	}

	// get chunk length
	int len = atoi(argv[4]);
	if ((len < 0) || (len > LENMAX))
	{
		Help();
		return 1;
	}

	// open main input file
	FILE* f = fopen(argv[1], "rb");
	if (f == NULL)
	{
		printf("Error opening input file %s\n", argv[1]);
		return 1;
	}

	// size of input file
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (size < 40)
	{
		printf("Incorrect size of input file %s\n", argv[1]);
		return 1;
	}

	// create buffers
	Img = (u8*)malloc(size + 16);
#ifdef TEST
	ImgTest = (u8*)malloc(size + 16);
	if ((Img == NULL) || (ImgTest == NULL))
#else
	if (Img == NULL)
#endif
	{
		printf("Memory error\n");
		return 1;
	}

	for (i = 1; i <= LENMAX; i++)
	{
		ImgOut[i] = (u8*)malloc(size*(i+1) + 16);
		if (ImgOut[i] == NULL)
		{
			printf("Memory error\n");
			return 1;
		}
	}

	// read file
	int size2 = (int)fread(Img, 1, size, f);
	fclose(f);
	if (size2 != size)
	{
		printf("Error reading input file %s\n", argv[1]);
		return 1;
	}

	// check BMP header
	bmpBITMAPFILEHEADER* bmf = (bmpBITMAPFILEHEADER*)Img;
	bmpBITMAPINFOHEADER* bmi = (bmpBITMAPINFOHEADER*)&bmf[1];
	W = bmi->biWidth;
	H = bmi->biHeight;
	B = bmi->biBitCount;
	if (H < 0) H = -H;
	if ((bmf->bfType != 0x4d42) ||
		(bmf->bfOffBits < 0x30) || (bmf->bfOffBits > 0x440) ||
		(bmi->biCompression != bmpBI_RGB) ||
		(W < 4) || (W > 10000) || (H < 4) || (H > 10000) ||
		(B != 1))
	{
		printf("Incorrect format of input file %s,\n", argv[1]);
		printf("  must be Windows-BMP 1-bit uncompressed.\n");
		return 1;
	}

	// source width in bytes
	WBS = (((W+7)/8) + 3)& ~3;

	// open output file
	f = fopen(argv[2], "wb");
	if (f == NULL)
	{
		printf("Error creating %s\n", argv[2]);
		return 1;
	}

	// use chunk level
	u8* bestimg;
	int bestlen;

	if (len > 0)
	{
		S = &Img[bmf->bfOffBits];
		D = ImgOut[len];
		bestimg = D;
		Comp(len);
		bestlen = (int)(D - ImgOut[len]);
	}

	// auto selection chunk level
	else
	{
		bestlen = 0x7fffffff;
		bestimg = NULL;
		for (i = 1; i <= LENMAX; i++)
		{
			S = &Img[bmf->bfOffBits];
			D = ImgOut[i];
			Comp(i);
			int n = (int)(D - ImgOut[i]);
			if (n < bestlen)
			{
				len = i;
				bestlen = n;
				bestimg = ImgOut[i];
			}
		}
	}

	// test decompression
#ifdef TEST
	memcpy(ImgTest, Img, bmf->bfOffBits);
	Test(&ImgTest[bmf->bfOffBits], bestimg);
#endif

	// info header
	fprintf(f, "#include \"../include.h\"\n\n");
	fprintf(f, "// format: 1-bit pixel graphics RLE compressed\n");
	fprintf(f, "// chunk length: %d bits\n", len);
	fprintf(f, "// compression: %d%%\n", bestlen*100/((W*H+3+16+7)/8));
	fprintf(f, "// image width: %d pixels\n", W);
	fprintf(f, "// image height: %d lines\n", H);

	// image header
	fprintf(f, "const u8 %s[%d] = {", argv[3], bestlen);
	n = 0;
	for (i = 0; i < bestlen; i++)
	{
		if ((n & 0x0f) == 0) fprintf(f, "\n\t");
		fprintf(f, "0x%02X, ", bestimg[i]);
		n++;
	}
	fprintf(f, "\n};\n");

	// close file
	fclose(f);
	free(Img);
#ifdef TEST
	free(ImgTest);
#endif
	for (i = 1; i <= LENMAX; i++) free(ImgOut[i]);

	return 0;
}
