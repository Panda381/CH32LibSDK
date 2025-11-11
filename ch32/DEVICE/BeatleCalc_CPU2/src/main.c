
// CPU2
// ====
// PC0: D1
// PC1: D2
// PC2: D3
// PC3: D4
// PC4: D5
// PC6: D6
// PC7: D7
// PD4: D8
// PD5: USART1_TX mapping 0, RX1-TX2 (send from CPU2 to CPU1, this is CPU2)
// PD6: USART1_RX mapping 0, TX1-RX2 (send from CPU1 to CPU2, this is CPU2)
// PA1: D9
// PA2: D10

#include "../include.h"

// slots
#define SLOTNUM		0x0100		// size of the slot in bytes (= equal to flash page size)
#define SLOTMAX		48		// max. number of slots - use max. 48, to be 3*16 (=12.2 KB)
#define SLOTALIGN	0x0100		// align slot in memory

// program slot
typedef struct {
	u8	data[SLOTNUM];		// one slot
} sSlot;

// all slosts (default slot content should be '0')
__attribute__((section(".flashslot"))) __attribute__((aligned(SLOTALIGN))) const sSlot Slots[SLOTMAX];

// receive RAM slot
sSlot Slot0;

// commands from CPU1 to CPU2
// - Control
#define CPU_CMD_CTRL_CLASS 0
#define CPU_CMD_SETDEV1	0x01		// set device type to 1, response CPU_RES_DEVOK after write (value is hardcoded)
#define CPU_CMD_SETDEV2	0x02		// set device type to 2, response CPU_RES_DEVOK after write (value is hardcoded)
#define CPU_CMD_SETDEV3	0x03		// set device type to 3, response CPU_RES_DEVOK after write (value is hardcoded)
#define CPU_CMD_GETDEV	0x04		// get device type, response CPU_RES_DEV*
#define CPU_CMD_SYNC	0x0B		// sync (bit pattern 00001011) - echo CPU_RES_SYNC back
#define CPU_CMD_NEXT	0x0C		// command during LOAD - continue to send next byte
// - output D1..D10
#define CPU_CMD_DOUT_CLASS 1
#define CPU_CMD_D1	0x11		// set D1 output, no response
#define CPU_CMD_D2	0x12		// set D2 output, no response
#define CPU_CMD_D3	0x13		// set D3 output, no response
#define CPU_CMD_D4	0x14		// set D4 output, no response
#define CPU_CMD_D5	0x15		// set D5 output, no response
#define CPU_CMD_D6	0x16		// set D6 output, no response
#define CPU_CMD_D7	0x17		// set D7 output, no response
#define CPU_CMD_D8	0x18		// set D8 output, no response
#define CPU_CMD_D9	0x19		// set D9 output, no response
#define CPU_CMD_D10	0x1A		// set D10 output, no response
// - Load slot from CPU2 to CPU1
#define CPU_CMD_LOAD_CLASS_1	2
#define CPU_CMD_LOAD_CLASS_2	3
#define CPU_CMD_LOAD_CLASS_3	4
#define CPU_LOAD_FIRST	0x20		// load first slot
#define CPU_LOAD_LAST	(CPU_LOAD_FIRST+SLOTMAX-1) // load last slot (= 0x4F)
// - Save slot from CPU1 to CPU2
#define CPU_CMD_SAVE_CLASS_1	5
#define CPU_CMD_SAVE_CLASS_2	6
#define CPU_CMD_SAVE_CLASS_3	7
#define CPU_SAVE_FIRST	0x50		// load first slot
#define CPU_SAVE_LAST	(CPU_SAVE_FIRST+SLOTMAX-1) // load last slot (= 0x7F)

// response from CPU2 to CPU1
#define CPU_RES_DEV1	0x01		// response to CPU_CMD_GETDEV - device type is 1 (value is hardcoded)
#define CPU_RES_DEV2	0x02		// response to CPU_CMD_GETDEV - device type is 2 (value is hardcoded)
#define CPU_RES_DEV3	0x03		// response to CPU_CMD_GETDEV - device type is 3 (value is hardcoded)
#define CPU_RES_DEVOK	0x04		// response to CPU_CMD_SETDEV* after write device type
#define CPU_RES_NEXT	0x0C		// response during SAVE - continue to send next byte
#define CPU_RES_SYNC	0x0D		// echo back after CPU_CMD_SYNC (bit pattern 00001101)
					// - Do not use the same value as CPU_CMD_SYNC, as the
					//   Rx and Tx short circuit would not be recognized.

// USART communication divider (baudrate = HCLK/div, HCLK=48000000, div=min. 16; 48 at 48MHz -> 1MBaud, 1 byte = 10us)
#define CPU_UART_DIV	HCLK_PER_US	// USART CPU baudrate divider (baudrate = HCLK/div, HCLK=48000000, div=min. 16)

// send byte to other CPU (wait for ready)
void CPU_Send(u8 data)
{
	USART1_SendChar(data);
}

// receive byte from other CPU (wait for ready)
u8 CPU_Recv(void)
{
	return USART1_RecvChar();
}

FASTCODE int main(void)
{
	u8 ch;

	// initialize port clock
	RCC_AFIClkEnable();
	RCC_PAClkEnable();
	RCC_PCClkEnable();
	RCC_PDClkEnable();

	// trim HSI oscillator to 24MHz
	RCC_HSITrim(16);

	// Remap PA1 & PA2 pins to OSC_IN & OSC_OUT (default 0)
	// 0 ... pins PA1 & PA2 are used as GPIO ports
	GPIO_Remap_PA1PA2(0);

	// set all output pins to LOW
	GPIOA_OutAll(0);
	GPIOC_OutAll(0);
	GPIOD_OutAll(0);

	// setup pins to output
	GPIO_Mode(PC0, GPIO_MODE_OUT);	// D1
	GPIO_Mode(PC1, GPIO_MODE_OUT);	// D2
	GPIO_Mode(PC2, GPIO_MODE_OUT);	// D3
	GPIO_Mode(PC3, GPIO_MODE_OUT);	// D4
	GPIO_Mode(PC4, GPIO_MODE_OUT);	// D5
	GPIO_Mode(PC6, GPIO_MODE_OUT);	// D6
	GPIO_Mode(PC7, GPIO_MODE_OUT);	// D7
	GPIO_Mode(PD4, GPIO_MODE_OUT);	// D8
	GPIO_Mode(PA1, GPIO_MODE_OUT);	// D9
	GPIO_Mode(PA2, GPIO_MODE_OUT);	// D10

	// setup USART1 mapping 0, to communicate with CPU1
	// 0 ... PD5:TX, PD6:RX, PD3:CTS, PC2:RTS
// PD5: USART1_TX mapping 0, TX1-RX2 (send from CPU1 to CPU2, this is CPU1)
// PD6: USART1_RX mapping 0, RX1-TX2 (send from CPU2 to CPU1, this is CPU1)
	GPIO_Remap_USART1(0);
	USART1_Init((RCC_GetFreq(CLK_HCLK) + CPU_UART_DIV/2)/CPU_UART_DIV,
		USART_WORDLEN_8, USART_PARITY_NONE, USART_STOP_1);
	GPIO_Mode(PD5, GPIO_MODE_AF);		// TX
	GPIO_Mode(PD6, GPIO_MODE_IN);		// RX

	while(True)
	{
		// 10us to receive a character
		if (USART1_RxReady())
		{
			ch = USART1_RxRead();

			// fast switch to class
			switch (ch >> 4)
			{
			// control
			case CPU_CMD_CTRL_CLASS:
				// controls
				switch (ch)
				{
				// set device type, response CPU_RES_DEVOK after write
				case CPU_CMD_SETDEV1:	// set device type to 1, response CPU_RES_DEVOK after write
				case CPU_CMD_SETDEV2:	// set device type to 2, response CPU_RES_DEVOK after write
				case CPU_CMD_SETDEV3:	// set device type to 3, response CPU_RES_DEVOK after write
					{
						OB_t ob;
						Flash_OBRead(&ob);	// read option bytes
						ob.Data0 = ch;		// set mode
						Flash_OBWrite(&ob);	// write new option bytes
						CPU_Send(CPU_RES_DEVOK); // response
					}						
					break;

				// get device type, response CPU_RES_DEV*
				case CPU_CMD_GETDEV:
					{
						int n = OB->Data0;
						if ((n < 1) || (n > 3)) n = 1;
						CPU_Send(n);
					}
					break;

				// sync (bit pattern 00001011) - echo CPU_RES_SYNC back
				case CPU_CMD_SYNC:
					// at this place, only SYNC can appear
					CPU_Send(CPU_RES_SYNC);
					break;
				}
				break;

			// output D1..D10
			case CPU_CMD_DOUT_CLASS:
				// set all output pins to LOW
				GPIOA_OutAll(0);
				GPIOC_OutAll(0);
				GPIOD_OutAll(0);

				// set pin to HIGH
				switch (ch)
				{
				case CPU_CMD_D1: GPIO_Out1(PC0); break; // D1
				case CPU_CMD_D2: GPIO_Out1(PC1); break; // D2
				case CPU_CMD_D3: GPIO_Out1(PC2); break; // D3
				case CPU_CMD_D4: GPIO_Out1(PC3); break; // D4
				case CPU_CMD_D5: GPIO_Out1(PC4); break; // D5
				case CPU_CMD_D6: GPIO_Out1(PC6); break; // D6
				case CPU_CMD_D7: GPIO_Out1(PC7); break; // D7
				case CPU_CMD_D8: GPIO_Out1(PD4); break; // D8
				case CPU_CMD_D9: GPIO_Out1(PA1); break; // D9
				case CPU_CMD_D10: GPIO_Out1(PA2); break; // D10
				}
				break;

			// Load slot from CPU2 to CPU1
			case CPU_CMD_LOAD_CLASS_1:
			case CPU_CMD_LOAD_CLASS_2:
			case CPU_CMD_LOAD_CLASS_3:
				{
					int i = ch - CPU_LOAD_FIRST;	// slot index
					const u8* s = Slots[i].data;	// pointer to the slot data
					for (i = SLOTNUM; i > 0; i--)
					{
						// send data byte
						CPU_Send(*s++);

						// wait for next byte (this should be command CPU_CMD_NEXT)
						CPU_Recv();
					}
				}
				break;

			// Save slot from CPU1 to CPU2
			case CPU_CMD_SAVE_CLASS_1:
			case CPU_CMD_SAVE_CLASS_2:
			case CPU_CMD_SAVE_CLASS_3:
				{
					// receive data to the RAM slot
					u8* d = Slot0.data;	// pointer to the slot data
					int i;
					for (i = SLOTNUM; i > 0; i--)
					{
						// request to send next byte
						CPU_Send(CPU_RES_NEXT);

						// receive byte
						*d++ = CPU_Recv();
					}

					// prepare slot address and size
					const u8* s = Slots[ch - CPU_SAVE_FIRST].data;

					// clear flash slot (address and size must be multiply of 256 B)
					Flash_Erase((u32)s + FLASH_BASE, SLOTNUM, 1000);

					// write program
					Flash_Program((u32)s + FLASH_BASE, (const u32*)&Slot0, SLOTNUM, 1000);

					// send OK
					CPU_Send(CPU_RES_SYNC);
				}
				break;
			}
		}
	}
}
