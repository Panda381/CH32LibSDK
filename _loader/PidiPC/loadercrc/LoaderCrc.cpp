// PicoLibSDK - Alternative SDK library for Raspberry Pico, RP2040 and RP2350
// Copyright (c) 2023 Miroslav Nemecek, Panda38@seznam.cz, hardyplotter2@gmail.com
// 	https://github.com/Panda381/PicoLibSDK
//	https://www.breatharian.eu/hw/picolibsdk/index_en.html
//	https://github.com/pajenicko/picopad
//	https://picopad.eu/en/
// License:
//	This source code is freely available for any purpose, including commercial.
//	It is possible to take and modify the code or parts of it, without restriction.

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#pragma warning(disable : 4996) // function not safe

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;

#define BUFSIZE (256*1024)						// max. file size
u8 Buf[BUFSIZE+4];

#define LOADER_SIZE		0x5000					// loader size
#define APPINFO_OFF		(LOADER_SIZE + 0xA4)	// application info header offset
#define APPINFO_OFF_CRC	(APPINFO_OFF + 0x0c)	// start of computing CRC

// application info header
typedef struct {
	char	magic1[4];	// 0x00: magic 1: "INFO"
	u32		len;		// 0x04: application length of data after "AppInfoHeader_StartCRC" label, init: 0x01234567
	u16		crc;		// 0x08: application CRC of data after "AppInfoHeader_StartCRC" label, init: 0x89AB
						//		 - use CRC-16 CCITT (CRC16C, use Crc16CFast() with INIT=0x1D0F)
	char	mcu[2];		// 0x0A: MCU serie identifier ("0X" = CH32V00X)
//AppInfoHeader_StartCRC: ... start of computing CRC
	u32		stack;		// 0x0C: end of user stack, to setup SP register
	u32		start;		// 0x10: start address, to jump to application
	char	magic2[4];	// 0x14: magic 2: .ascii "info"
} sAppInfoHeader;

sAppInfoHeader AppInfo2;

// Calculate CRC-16 CCITT Normal (CRC16A), buffer - fast version
u16 Crc16CBufFast(u16 crc, const void* buf, int len)
{
	const u8* s = (const u8*)buf;

	for (; len > 0; len--)
	{
		crc = (crc >> 8) | (crc << 8);
		crc ^= *s++;
		crc ^= (crc & 0xff) >> 4;
		crc ^= crc << 12;
		crc ^= (crc & 0xff) << 5;
	}
	return crc;
}

// check patterns
#define CRCPAT1LEN 9	// length of CRC pattern 1
#define CRCPAT2LEN 3	// length of CRC pattern 2
const char CrcPat1[] = "123456789";
const u8 CrcPat2[CRCPAT2LEN+1] = { 0xFC, 0x05, 0x4A, 0x3E };

// CRC-16 CCITT Normal Alternative (CRC16C) init word (not reversed, not inverted)
#define CRC16C_INIT 0x1D0F

// Calculate CRC-16 CCITT Normal Alternative (CRC16C) - fast version
u16 Crc16CFast(const void* buf, int len)
{
	return Crc16CBufFast(CRC16C_INIT, buf, len);
}

int main(int argc, char* argv[])
{
	// Check CRC-16-CCITT (0x1D0F) pattern
#define CRC16C_RES1 0xE5CC
#define CRC16C_RES2 0x9144
	if ((Crc16CFast(CrcPat1, CRCPAT1LEN) != CRC16C_RES1) ||
		Crc16CFast(CrcPat2, CRCPAT2LEN) != CRC16C_RES2)
	{
		printf("CRC internal error!\n");
		return 1;
	}

	if (argc != 3)
	{
		printf("Syntax: LoaderCrc program.bin program.elf\n");
		return 1;
	}

	// open input file
	FILE* f = fopen(argv[1], "rb");
	if (f == NULL)
	{
		printf("File %s not found\n", argv[1]);
		return 1;
	}

	// get file size
	fseek(f, 0, SEEK_END);
	u32 size = (u32)ftell(f);
	fseek(f, 0, SEEK_SET);
	if ((size <= APPINFO_OFF + sizeof(sAppInfoHeader)) || (size > BUFSIZE))
	{
		printf("Incorrect %s file size\n", argv[1]);
		fclose(f);
		return 1;
	}

	// load file
	u32 n = (u32)fread(Buf, 1, size+4, f);
	if (n != size)
	{
		printf("Cannot load file %s\n", argv[1]);
		return 1;
	}
	fclose(f);

	// check header
	sAppInfoHeader* app = (sAppInfoHeader*)&Buf[APPINFO_OFF];
	if ((*(u32*)app->magic1 != 'OFNI') // magic "INFO"
		|| (app->len != 0x01234567) // application length
		|| (app->crc != 0x89AB) // application CRC
		|| (*(u16*)app->mcu != 'X0') // MCU identifier "0X"
		|| (*(u32*)app->magic2 != 'ofni')) // magic "info"
	{
		printf("Incorrect format of %s\n", argv[1]);
		return 1;
	}

	// calculate CRC
	app->len = size - APPINFO_OFF_CRC;
	app->crc = Crc16CFast(&Buf[APPINFO_OFF_CRC], size - APPINFO_OFF_CRC);

	// open for write
	f = fopen(argv[1], "r+b");
	if (f == NULL)
	{
		printf("Cannot open %s for write\n", argv[1]);
		return 1;
	}

	// write new header
	fseek(f, APPINFO_OFF, SEEK_SET);
	n = (u32)fwrite(&Buf[APPINFO_OFF], 1, sizeof(sAppInfoHeader), f);
	if (n != sizeof(sAppInfoHeader))
	{
		printf("Cannot write to %s\n", argv[1]);
		return 1;
	}
	fclose(f);

	// open ELF input file
	f = fopen(argv[2], "rb");
	if (f == NULL)
	{
		printf("File %s not found\n", argv[2]);
		return 1;
	}

	// read application info
	fseek(f, 0x1000 + APPINFO_OFF, SEEK_SET);
	n = (u32)fread(&AppInfo2, 1, sizeof(sAppInfoHeader), f);
	if (n != sizeof(sAppInfoHeader))
	{
		printf("Cannot load file %s\n", argv[2]);
		return 1;
	}
	fclose(f);

	// check header
	app = &AppInfo2;
	if ((*(u32*)app->magic1 != 'OFNI') // magic "INFO"
		|| (app->len != 0x01234567) // application length
		|| (app->crc != 0x89AB) // application CRC
		|| (*(u16*)app->mcu != 'X0') // MCU identifier "0X"
		|| (*(u32*)app->magic2 != 'ofni')) // magic "info"
	{
		printf("Incorrect format of %s\n", argv[2]);
		return 1;
	}

	// open for write
	f = fopen(argv[2], "r+b");
	if (f == NULL)
	{
		printf("Cannot open %s for write\n", argv[2]);
		return 1;
	}

	// write new header
	fseek(f, 0x1000 + APPINFO_OFF, SEEK_SET);
	n = (u32)fwrite(&Buf[APPINFO_OFF], 1, sizeof(sAppInfoHeader), f);
	if (n != sizeof(sAppInfoHeader))
	{
		printf("Cannot write to %s\n", argv[2]);
		return 1;
	}
	fclose(f);
	return 0;
}
