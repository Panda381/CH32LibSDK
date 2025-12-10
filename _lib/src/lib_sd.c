
// ****************************************************************************
//
//                                 SD card
//
// ****************************************************************************

#include "../../includes.h"	// globals

#if USE_SD		// use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read

// SD card type
u8 SD_Type = SD_NONE;

// SD card type name
const char SD_Name0[] = "-no-";
const char SD_Name1[] = "MMC";
const char SD_Name2[] = "SDv1";
const char SD_Name3[] = "SDv2";
const char SD_Name4[] = "SDHC";
const char* const SD_Name[5] = { SD_Name0, SD_Name1, SD_Name2, SD_Name3, SD_Name4 };

// SD buffer
u8 SD_Buf[16];

// MMC/SD commands (ACMD<n> = command sequence CMD55 - CMD<n>)
#define ACMD 		0x80		// ACMD command flag

#define CMD0_IDLE	0		// GO_IDLE_STATE (start SPI mode, software reset), response R1
#define CMD1_MMCOP	1		// SEND_OP_COND (MMC), initiate initialization process, response R1
#define CMD8_IF		8		// SEND_IF_COND, only SDC V2, check voltage range, response R7
#define CMD9_CSD	9		// SEND_CSD, read CSD register, response R1
#define CMD10_CID	10		// SEND_CID, read CID register, response R1
#define CMD12_STOP	12		// STOP_TRANSMISSION, stop to read data, response R1
#define ACMD13_STATE	(ACMD+13)	// SD_STATUS (SDC)
#define CMD13_STATUS	13		// SEND_STATUS, response R2
#define CMD16_SETLEN	16		// SET_BLOCKLEN (arg=block length), change R/W block size, response R1
#define CMD17_READ1	17		// READ_SINGLE_BLOCK (arg=data address), response R1
#define CMD18_READMUL	18		// READ_MULTIPLE_BLOCK (arg=data address), response R1
//#define CMD23_SETCNT	23		// SET_BLOCK_COUNT (MMC)
//#define ACMD23_ERASE	(ACMD+23)	// SET_WR_BLK_ERASE_COUNT (SDC), for only SDC, 
#define CMD24_WRITE1	24		// WRITE_SINGLE_BLOCK (arg=data address), write a block, response R1
#define CMD25_WRITEMUL	25		// WRITE_MULTIPLE_BLOCK (arg=data address), write multiple blocks, response R1
#define CMD27_PROGCSD	27		// PROGRAM_CSD, response R1
#define CMD28_SETWP	28		// SET_WRITE_PROT (arg=data address), set write protection, response R1b
#define CMD29_CLRWP	29		// CLR_WRITE_PROT (arg=data address), clear write protection, response R1b
#define CMD30_SNDRWP	30		// SEND_WRITE_PROT (arg=data address), send write protection, response R1
#define CMD32_ERASE_BEG	32		// ERASE_ER_BLK_START, TAG_SECTOR_START (arg=data address), response R1
#define CMD33_ERASE_END	33		// ERASE_ER_BLK_END, TAG_SECTOR_END (arg=data address), response R1
#define CMD34_UNTAG	34		// UNTAG_SECTOR (arg=data address), response R1
#define CMD35_GRP_BEG	35		// TAG_ERASE_GROUP_START (arg=data address), response R1
#define CMD36_GRP_END	36		// TAG_ERASE_GROUP_END (arg=data address), response R1
#define CMD37_GRP_UNTAG	37		// UNTAG_ERASE_GROUP (arg=data address), response R1
#define CMD38_ERASE	38		// ERASE (arg=stuff bits)
#define ACMD41_SDCOP	(ACMD+41)	// APP_SEND_OP_COND (only SDC, arg=OCR contents), initiate initialization process, response R1
#define CMD42_UNLOCK	42		// LOCK_UNLOCK (arg=stuff bits), response R1b
#define CMD55_APP	55		// APP_CMD (arg=stuff bits), leading command of ACMD<n> commads, response R1
#define CMD58_OCR	58		// READ_OCR (arg=stuff bits), read OCR, response R3
#define CMD59_CRC	59		// CRC_ON_OFF (arg=crc option), enable CRC, response R1

// R1 response (1 byte; R1b equals R1, with additional busy bytes):
#define R1_IDLE_STATE	B0	// in idle state
#define R1_ERASE_RESET	B1	// erase reset
#define R1_ILL_COMMAND	B2	// illegal command error
#define R1_COM_CRC_ERR	B3	// CRC error
#define R1_ERASE_ERR	B4	// erase sequence error
#define R1_ADDR_ERR	B5	// address error
#define R1_PARAM_ERR	B6	// parameter error

// R2 response (2 bytes); 1st byte is R1, 2nd byte:
#define R2_CARD_LOCKED	B0
#define R2_WPERASE_SKIP	B1
#define R2_ERR		B2
#define R2_CARD_ERR	B3
#define R2_ECC_FAIL	B4
#define R2_WP_VIOLATION	B5
#define R2_INVAL_ERASE	B6
#define R2_OUT_OF_RANGE	B7

// R3 response (5 bytes); 1st byte is R1, 2nd..5th byte:
#define R3_OCR_MASK	0xffffffffUL

// Data Response (1 byte):
#define DR_STATUS_MASK		0x0e
#define DR_STATUS_ACCEPTED	0x05
#define DR_STATUS_CRC_ERR	0x0a
#define DR_STATUS_WRITE_ERR	0x0c

// communication with SD card using SPI protocol:
// - to start SPI mode, unselect card (set CS to 1) and togle clock at least 74 cycles,
//   than select card (set CS to 0) and send CMD0 to reset card (0x40, 0, 0, 0, 0, 0x95)
//   (01 000000 00000000 00000000 00000000 00000000 1001010 1),
//   card should response (after max. 16 cycles) with 8 bits of status (0x01 on success) - R1 response
// - clock should be in range 100..400 kHz
// - command 48 bits (from highest bits to lowest):
//	b47: 0 start bit
//	b48: 1 start bit
//	b40..b45: command number (6 bits, 0..63)
//	b8..b39: argument (32 bits)
//	b1..b7: CRC (7 bits), ignored by default except CMD8
//	b0: 1 stop bit
//    or:
//      byte 5 (b40..b47): command and start bits
//	byte 4 (b32..b39): argument byte 3
//	byte 3 (b24..b31): argument byte 2
//	byte 2 (b16..b23): argument byte 1
//	byte 1 (b8..b15): argument byte 0
//	byte 0 (b0..b7): CRC and stop bit
//
// After sending command it requires 8 clock cycles before response.

// current SD speed - number of HCLK cycles of one half-pulse
#if (USE_SD == 1) || (USE_SD == 3) // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
int SD_SpeedDelay = SD_SPEED_INIT;
#endif

// get SD card type name
const char* SD_GetName()
{
	return SD_Name[SD_Type];
}

#if USE_SD == 3		// use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
// SD transfer one byte - fast software read
//   Motorola format 0:
//	- MSB first
//	- master mode
//	- SCK low when idle (leading edge rising, trailing edge falling)
//	- clock phase: leading edge sample, trailing edge setup, 8 data bits
u8 SD_ByteFastRead()
{
	u8 res = 0;
	int i;
	for (i = 8; i > 0; i--)
	{
		// set output data bit (MSB first)
		GPIO_Out(SD_MOSI_GPIO, 1);

		// shift clock - leading edge rising (= MOSI data is valid, slave can get it)
		nop();
		GPIO_Out1(SD_CLK_GPIO);

		// read input data bit
		res <<= 1;
		cb();
		res |= GPIO_In(SD_MISO_GPIO);

		// shift clock - trailing edge falling (= master taken MISO data, slave can change it)
		GPIO_Out0(SD_CLK_GPIO);
	}

	return res;
}
#endif // USE_SD == 3

// SD transfer one byte
//   Motorola format 0:
//	- MSB first
//	- master mode
//	- SCK low when idle (leading edge rising, trailing edge falling)
//	- clock phase: leading edge sample, trailing edge setup, 8 data bits
u8 SD_Byte(u8 val)
{
#if (USE_SD == 1) || (USE_SD == 3) // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
// Software driver:

	u8 res = 0;
	int i;
	for (i = 8; i > 0; i--)
	{
		// set output data bit (MSB first)
		GPIO_Out(SD_MOSI_GPIO, (val & B7));
		val <<= 1;

		// shift clock - leading edge rising (= MOSI data is valid, slave can get it)
		nop();
		GPIO_Out1(SD_CLK_GPIO);

		// delay
		if (SD_SpeedDelay > 0) WaitClk(SD_SpeedDelay);

		// read input data bit
		res <<= 1;
		cb();
		res |= GPIO_In(SD_MISO_GPIO);

		// shift clock - trailing edge falling (= master taken MISO data, slave can change it)
		GPIO_Out0(SD_CLK_GPIO);

		// delay
		if (SD_SpeedDelay > 0) WaitClk(SD_SpeedDelay);
	}

	return res;

#else
// Hardware driver:

	// flush receive buffer
	(void)SPI1_Read();

	// send data
	SPI1_SendWait(val);

	// receive data
	return (u8)SPI1_RecvWait();

#endif
}

// unselect SD card
void SD_Unsel(void)
{
	// set CS signal to HIGH (= unselect)
	GPIO_Out1(SD_CS_GPIO);

	// send dummy clock to free SPI bus
	SD_Byte(0xff);
	SD_Byte(0xff);
	SD_Byte(0xff);
}

// select SD card
void SD_Sel(void)
{
	// set CS signal to LOW (= select)
	GPIO_Out0(SD_CS_GPIO);

	// send dummy clock to free SPI bus
	SD_Byte(0xff);
}

// send command with argument to SD card and return response (0 or 1 is OK, 0xff=timeout, other=error)
u8 SD_SendCmd(u8 cmd, u32 arg)
{
	u8 res, n;

	// send leading command CMD55 of ACMD* command
	if ((cmd & ACMD) != 0)
	{
		cmd &= ~ACMD;
		res = SD_SendCmd(CMD55_APP, 0);
		if (res > 1)
		{
			return res;
		}
	}

	// send dummy clock to free SPI bus
	SD_Byte(0xff);
	SD_Byte(0xff);
	SD_Byte(0xff);

	// send command packet
	SD_Byte(0x40 | cmd); // send command and start bits
	SD_Byte((u8)(arg >> 24)); // send byte 3 of the argument
	SD_Byte((u8)(arg >> 16)); // send byte 2 of the argument
	SD_Byte((u8)(arg >> 8)); // send byte 1 of the argument
	SD_Byte((u8)arg); // send byte 0 of the argument

	// send CRC
	n = 0xff; // dummy CRC and stop bit
	if (cmd == CMD0_IDLE) n = 0x95; // CRC for idle command
	if (cmd == CMD8_IF) n = 0x87; // CRC for IF command
	SD_Byte(n); // send CRC and stop bit

	// receive response (max. 10 attempts)
	for (n = 10; n > 0; n--)
	{
		// send dummy clock and get response
		res = SD_Byte(0xff);
		if ((res & 0x80) == 0) break;
	}

	// response (or 0xff on timeout error)
	return res;
}

// connect to SD card after inserting (returns False on error)
Bool SD_Connect()
{
	u8 n, res;

	// unknown card type
	SD_Type = SD_NONE;

	// set SPI to low speed
#if USE_SD == 2 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
	SPI1_Baud(SD_SPI_DIV_INIT);
#else
	SD_SpeedDelay = SD_SPEED_INIT;
#endif

	// unselect card (and send 3x FF)
	SD_Unsel();

	// initialize connection - send 10 empty bytes (=80 clocks)
	for (n = 20; n > 0; n--) SD_Byte(0xff);

	// select SD card
	SD_Sel();

	// reset card and set SPI mode, go to idle mode
	for (n = 100; n > 0; n--)
	{
		res = SD_SendCmd(CMD0_IDLE, 0);
		if (res == R1_IDLE_STATE) break;
	}

	// initialization timeout
	if (n == 0)
	{
		// unselect card
		SD_Unsel();

		return False;
	}

	// we have at least MMC card
	SD_Type = SD_MMC;

	// check SD v2 card, switch to 3.3V
	res = SD_SendCmd(CMD8_IF, 0x000001aa); // support 2.7-3.6V ?
	if ((res & R1_ILL_COMMAND) == 0)
	{
		SD_Byte(0xff);
		SD_Byte(0xff);
		res = SD_Byte(0xff);
		n = SD_Byte(0xff);
		if ((res == 1) && (n == 0xaa)) // check returned argument 0x000001aa
			SD_Type = SD_SD2;
	}

	// check SD v1 card
	if (SD_Type == SD_MMC)
	{
		res = SD_SendCmd(ACMD41_SDCOP, 0);
		if ((res & R1_ILL_COMMAND) == 0) SD_Type = SD_SD1;
	}

	// wait for card to get ready (max. 0.3 second)
	for (n = 30; n > 0; n--)
	{
		// wait for initialization
		if (SD_Type == SD_SD2)
			res = SD_SendCmd(ACMD41_SDCOP, B30);
		else if (SD_Type == SD_SD1)
			res = SD_SendCmd(ACMD41_SDCOP, 0);
		else
			res = SD_SendCmd(CMD1_MMCOP, 0);

		// initializadion completed
		if ((res & R1_IDLE_STATE) == 0) break;

		// wait 10 ms
		WaitMs(10);
	}

	// initialization timeout
	if (n == 0)
	{
		SD_Type = SD_NONE;

		// unselect card
		SD_Unsel();

		return False;
	}

	// check SDHC card
	if (SD_Type == SD_SD2)
	{
		res = SD_SendCmd(CMD58_OCR, 0);
		if (res <= 1)
		{
			if ((SD_Byte(0xff) & 0x40) != 0)
				SD_Type = SD_SDHC;
			SD_Byte(0xff);
			SD_Byte(0xff);
			SD_Byte(0xff);
		}
	}

	// set sector length to standard 512 bytes
	SD_SendCmd(CMD16_SETLEN, SECT_SIZE);

	// unselect card
	SD_Unsel();

	// set SPI to high speed
#if USE_SD == 2 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
	SPI1_Baud(SD_SPI_DIV_WRITE);
#else
	SD_SpeedDelay = SD_SPEED_WRITE;
#endif

	return True;
}

// disconnect SD card
void SD_Disconnect()
{
	// set SPI to low speed
#if USE_SD == 2 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
	SPI1_Baud(SD_SPI_DIV_INIT);
#else
	SD_SpeedDelay = SD_SPEED_INIT;
#endif

	// unselect card
	SD_Unsel();

	// invalidate disk type
	SD_Type = SD_NONE;
}

// read data block (returns False on error)
Bool SD_ReadBlock(u8* buffer, int num)
{
	// wait for data block (wait for start byte 0xfe)
	int n;
	u8 res;
	for(n = 60000; n > 0; n--)
	{
#if USE_SD == 3 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
		res = SD_ByteFastRead();
#else
		res = SD_Byte(0xff);
#endif
		if (res != 0xff) break;
	}

	if (res != 0xfe) return False;

	// read data
#if USE_SD == 3 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
	for (n = 0; n < num; n++) buffer[n] = SD_ByteFastRead();
#else
	for (n = 0; n < num; n++) buffer[n] = SD_Byte(0xff);
#endif

	// get CRC16
	SD_Byte(0xff);
	SD_Byte(0xff);

	return True;
}

// open SD card
void SD_Open()
{
	// set SPI to high speed
#if USE_SD == 2 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
	SPI1_Baud(SD_SPI_DIV_INIT);
#else
	SD_SpeedDelay = SD_SPEED_INIT;
#endif

	// select SD card
	SD_Sel();

	// send dummy clock to free SPI bus
	SD_Byte(0xff);
	SD_Byte(0xff);
	SD_Byte(0xff);
}

// close SD card
void SD_Close()
{
	// unselect card
	SD_Unsel();

	// free SPI bus (to make MMC/SDC release the MISO line, the master
	// device needs to send a byte after the CS signal is deasserted)
	SD_Byte(0xff);
	SD_Byte(0xff);
	SD_Byte(0xff);
	SD_Byte(0xff);
}

// read one sector from SD card (returns False on error)
Bool SD_ReadSect(u32 sector, u8* buffer)
{
	// check if card is connected
	if (SD_Type == SD_NONE) return False;

	// open SD card
	SD_Open();

	// set SPI to high speed
#if USE_SD == 2 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
	SPI1_Baud(SD_SPI_DIV_READ);
#else
	SD_SpeedDelay = SD_SPEED_READ;
#endif

	// convert sector number to offset
	if (SD_Type != SD_SDHC) sector *= SECT_SIZE;

	// send command to get single block
	u8 res = SD_SendCmd(CMD17_READ1, sector);
	if (res != 0)
	{
		// unselect card
		SD_Unsel();

		return False;
	}

	// receive data block
	res = SD_ReadBlock(buffer, SECT_SIZE);

	// close SD card
	SD_Close();

	return res;
}

// write one sector to SD card (returns False on error)
Bool SD_WriteSect(u32 sector, const u8* buffer)
{
	// check if card is connected
	if (SD_Type == SD_NONE) return False;

	// open SD card
	SD_Open();

	// set SPI to high speed
#if USE_SD == 2 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
	SPI1_Baud(SD_SPI_DIV_WRITE);
#else
	SD_SpeedDelay = SD_SPEED_WRITE;
#endif

	// convert sector number to offset
	if (SD_Type != SD_SDHC) sector *= SECT_SIZE;

	// send command to write single block
	u8 res = SD_SendCmd(CMD24_WRITE1, sector);
	if (res != 0)
	{
		// unselect card
		SD_Unsel();

		return False;
	}

	// wait for card is ready
	int n;
	for(n = 60000; n > 0; n--)
	{
		res = SD_Byte(0xff);
		if (res == 0xff) break;
	}

	if (n == 0)
	{
		// unselect card
		SD_Unsel();

		return False;
	}

	// send start byte
	SD_Byte(0xfe);

	// write data
	for (n = 0; n < SECT_SIZE; n++) SD_Byte(buffer[n]);

	// set CRC16
	SD_Byte(0xff);
	SD_Byte(0xff);

	// wait while card is busy
	for(n = 60000; n > 0; n--)
	{
		res = SD_Byte(0xff);
		if (res == 0xff) break;
	}
	SD_Byte(0xff);

	// close SD card
	SD_Close();

	return True;
}

// get media size (in number of sectors; returns 0 on error)
u32 SD_MediaSize()
{
	// check if card is connected
	if (SD_Type == SD_NONE) return 0;

	// open SD card
	SD_Open();

	// set SPI to high speed
#if USE_SD == 2 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
	SPI1_Baud(SD_SPI_DIV_READ);
#else
	SD_SpeedDelay = SD_SPEED_READ;
#endif

	// send command to read CSD
	u32 size = 0;
	if ((SD_SendCmd(CMD9_CSD, 0) == 0) && SD_ReadBlock(SD_Buf, 16))
	{
		// SDC ver 2.00
		if ((SD_Buf[0] >> 6) == 1)
		{
			u32 csize = SD_Buf[9] + ((u32)SD_Buf[8] << 8) + ((u32)(SD_Buf[7] & 0x3f) << 16) + 1;
			size = csize << 10;
		}
		// SDC ver 1.xx or MMC ver 3
		else
		{
			u8 n = (SD_Buf[5] & 0xf) + ((SD_Buf[10] & 0x80) >> 7) + ((SD_Buf[9] & 0x03) << 1) + 2;
			u32 csize = (SD_Buf[8] >> 6) + ((u32)SD_Buf[7] << 2) + ((u32)(SD_Buf[6] & 0x03) << 10) + 1;
			size = csize << (n - 9);
		}
	}

	// close SD card
	SD_Close();

	return size;
}

// initialize SD card interface
//   Motorola format 0:
//	- MSB first
//	- master mode
//	- SCK low when idle (leading edge rising, trailing edge falling)
//	- clock phase: leading edge sample, trailing edge setup, 8 data bits
void SD_Init(void)
{
	// enable ports
	RCC_PxClkEnable(GPIO_PORTINX(SD_CS_GPIO));	// enable CS port
#if GPIO_PORTINX(SD_CLK_GPIO) != GPIO_PORTINX(SD_CS_GPIO)
	RCC_PxClkEnable(GPIO_PORTINX(SD_CLK_GPIO));	// enable CLK port
#endif
#if (GPIO_PORTINX(SD_MISO_GPIO) != GPIO_PORTINX(SD_CS_GPIO)) && (GPIO_PORTINX(SD_MISO_GPIO) != GPIO_PORTINX(SD_CLK_GPIO))
	RCC_PxClkEnable(GPIO_PORTINX(SD_MISO_GPIO));	// enable MISO port
#endif
#if (GPIO_PORTINX(SD_MOSI_GPIO) != GPIO_PORTINX(SD_CS_GPIO)) && (GPIO_PORTINX(SD_MOSI_GPIO) != GPIO_PORTINX(SD_CLK_GPIO)) && (GPIO_PORTINX(SD_MOSI_GPIO) != GPIO_PORTINX(SD_MISO_GPIO))
	RCC_PxClkEnable(GPIO_PORTINX(SD_MOSI_GPIO));	// enable MOSI port
#endif

	// init MISO pin
	GPIO_Mode(SD_MISO_GPIO, GPIO_MODE_IN_PU);

	// init CS pin: inactive HIGH
	GPIO_Out1(SD_CS_GPIO);
	GPIO_Mode(SD_CS_GPIO, GPIO_MODE_OUT);

#if (USE_SD == 1) || (USE_SD == 3) // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
// Software driver:

	// init CLK pin: clock LOW when idle, leading edge rising, trailing edge falling
	// clock phase: leading rising edge sample, trailing falling edge setup
	GPIO_Out0(SD_CLK_GPIO);
	GPIO_Mode(SD_CLK_GPIO, GPIO_MODE_OUT);

	// init MOSI pin
	GPIO_Out0(SD_MOSI_GPIO);
	GPIO_Mode(SD_MOSI_GPIO, GPIO_MODE_OUT);

#else
// Hardware driver:

	// SPI1 clock enable
	RCC_SPI1ClkEnable();

	// SPI1 reset
	RCC_SPI1Reset();

	// set SPI mapping
	GPIO_Remap_SPI1(SD_SPI_MAP);

	// sampling on first edge, clock polarity low
	SPI1_ClockPhaseFirst();
	SPI1_ClockPolLow();

	// set master mode
	SPI1_Master();

	// set SPI to low speed
	SPI1_HSDisable();
	SPI1_Baud(SD_SPI_DIV_INIT);

	// MSB bit first
	SPI1_MSB();

	// set NSS pin High
	SPI1_NSSHigh();

	// NSS controlled by software
	SPI1_NSSSw();

	// full duplex
	SPI1_Duplex();

	// 8-bit (default setup)
	SPI1_Data8();

	// 2 lines (default setup)
	SPI1_Bidi2();

	// CRC disable
	SPI1_CRCNextDisable();
	SPI1_CRCDisable();

	// disable SS output
	SPI1_SSDisable();

	// SPI enable
	SPI1_Enable();

	// setup pins
	GPIO_Mode(SD_CLK_GPIO, GPIO_MODE_AF);
	GPIO_Mode(SD_MOSI_GPIO, GPIO_MODE_AF);
#endif
}

// Terminate SD card interface
void SD_Term(void)
{
#if USE_SD == 2 // use SD card driver: 0=no, 1=software, 2=hardware (with software CS), 3=software with fast read
	// SPI1 reset
	RCC_SPI1Reset();
#endif
	// disable ports
	GPIO_PinReset(SD_CS_GPIO);
	GPIO_PinReset(SD_CLK_GPIO);
	GPIO_PinReset(SD_MISO_GPIO);
	GPIO_PinReset(SD_MOSI_GPIO);
}

#endif // USE_SD
