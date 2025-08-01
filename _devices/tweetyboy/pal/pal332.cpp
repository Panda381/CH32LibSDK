// Palettes 332 (RGB332)

#include <stdio.h>

#pragma warning(disable : 4996)

#define FILENAME "pal332.act"
#define FILENAME2 "pal332.csv"
#define FILENAME3 "pal332.h"

//                        0x00, 0x55, 0xAA, 0xFF
unsigned char Levels4[4] = { 0,   85,  170,  255 };

//                        0x00, 0x24, 0x49, 0x6D, 0x92, 0xB6, 0xDB, 0xFF
unsigned char Levels8[8] = { 0,   36,   73,  109,  146,  182,  219,  255 };

#define B0	(1<<0)
#define B1	(1<<1)
#define B2	(1<<2)
#define B3	(1<<3)
#define B4	(1<<4)
#define B5	(1<<5)
#define B6	(1<<6)
#define B7	(1<<7)

int main(int argc, char* argv[])
{
	FILE* f = fopen(FILENAME, "wb");
	if (f == NULL)
	{
		printf("Error opening " FILENAME "\n");
		return 1;
	}

	FILE* f2 = fopen(FILENAME2, "wb");
	if (f2 == NULL)
	{
		printf("Error opening " FILENAME2 "\n");
		return 1;
	}
	fprintf(f2, "index,hex,RGB565,RGB888,red,green,blue\n");

	FILE* f3 = fopen(FILENAME3, "wb");
	if (f3 == NULL)
	{
		printf("Error opening " FILENAME3 "\n");
		return 1;
	}
	fprintf(f3, "const u16 DefPalette[256] = {");

	int i, k;
	unsigned char b[3];
	for (i = 0; i < 256; i++)
	{
		b[2] = Levels4[i & 3]; // blue
		b[1] = Levels8[(i >> 2) & 7]; // green
		b[0] = Levels8[(i >> 5) & 7]; // red
		fwrite(b, 1, 3, f);

		k = ((b[0]>>3)<<11) | ((b[1]>>2)<<5) | (b[2]>>3);

		fprintf(f2, "%i,0x%02X,0x%04X,0x%06X,%d,%d,%d\n",
			i, i, k, (b[0]<<16)|(b[1]<<8)|b[2], b[0], b[1], b[2]);

		if ((i & 7) == 0)
			fprintf(f3, "\n\t");
		else
			fprintf(f3, " ");
		fprintf(f3, "0x%04X,", k);
	}
	fprintf(f3,"\n};\n");

	fclose(f);
	fclose(f2);
	fclose(f3);

	return 0;
}

