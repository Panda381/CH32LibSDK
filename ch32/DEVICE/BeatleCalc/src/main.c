
// ****************************************************************************
//
//                           BeatleCalc - main code
//
// ****************************************************************************

#include "../include.h"

// flag - display service is initialized
Bool DispInitOK = False;

// calculator mode
u8 CalcMode;			// calculator mode MODE_*

// intro texts
const u8 IntroTextCalcul[DISP_NUM-1]   = { CH_SPC, CH_SPC, CH_C, CH_A, CH_L, CH_C, CH_V, CH_L, CH_SPC };
const u8 IntroTextSinclair[DISP_NUM-1] = { CH_SPC, CH_S, CH_1, CH_M, CH_C, CH_L, CH_A, CH_1, CH_R };
const u8 IntroTextDatamath[DISP_NUM-1] = { CH_SPC, CH_D, CH_A, CH_T, CH_A, CH_M, CH_A, CH_T, CH_H };

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

// digits (contains inverted segments of the digits and characters)
const u8 SegDig[CH_NUM] = {
	// - digits
	(u8)~(SA+SB+SC+SD+SE+SF),	// CH_0
	(u8)~(SB+SC),			// CH_1
	(u8)~(SA+SB+SD+SE+SG),		// CH_2
	(u8)~(SA+SB+SC+SD+SG),		// CH_3
	(u8)~(SB+SC+SF+SG),		// CH_4
	(u8)~(SA+SC+SD+SF+SG),		// CH_5
	(u8)~(SA+SC+SD+SE+SF+SG),	// CH_6
	(u8)~(SA+SB+SC),		// CH_7
	(u8)~(SA+SB+SC+SD+SE+SF+SG),	// CH_8
	(u8)~(SA+SB+SC+SD+SF+SG),	// CH_9
	// - characters
	(u8)~(SA+SB+SC+SE+SF+SG),	// CH_A
	(u8)~(SC+SD+SE+SF+SG),		// CH_B
	(u8)~(SA+SD+SE+SF),		// CH_C
	(u8)~(SB+SC+SD+SE+SG),		// CH_D
	(u8)~(SA+SD+SE+SF+SG),		// CH_E
	(u8)~(SA+SE+SF+SG),		// CH_F
	(u8)~(SA+SC+SD+SE+SF),		// CH_G
	(u8)~(SB+SC+SE+SF+SG),		// CH_H
	(u8)~(SC),			// CH_I
	(u8)~(SB+SC+SD+SE),		// CH_J
	(u8)~(SE+SF+SG),		// CH_K
	(u8)~(SD+SE+SF),		// CH_L
	(u8)~(SA+SB+SC+SE+SF),		// CH_M
	(u8)~(SC+SE+SG),		// CH_N
	(u8)~(SC+SD+SE+SG),		// CH_O
	(u8)~(SA+SB+SE+SF+SG),		// CH_P
	(u8)~(SA+SB+SD+SE+SF),		// CH_Q
	(u8)~(SE+SG),			// CH_R
	(u8)~(SA+SC+SD+SF+SG),		// CH_S
	(u8)~(SD+SE+SF+SG),		// CH_T
	(u8)~(SC+SD+SE),		// CH_U
	(u8)~(SB+SC+SD+SE+SF),		// CH_V
	(u8)~(SB+SC+SD+SE+SF+SG),	// CH_W
	(u8)~(SC+SF+SG),		// CH_X
	(u8)~(SB+SC+SD+SF+SG),		// CH_Y
	(u8)~(SA+SB+SD+SE+SG),		// CH_Z
	// - special
	(u8)~(SD+SE+SG),		// CH_C2
	(u8)~(SA+SB+SE+SG),		// CH_QUER
	(u8)~(SG),			// CH_NEG
	(u8)~(0),			// CH_SPC
	// - graphics
	(u8)~(SA),			// CH_SEGA
	(u8)~(SB),			// CH_SEGB
	(u8)~(SC),			// CH_SEGC
	(u8)~(SD),			// CH_SEGD
	(u8)~(SE),			// CH_SEGE
	(u8)~(SF),			// CH_SEGF
	(u8)~(SG),			// CH_SEGG
	(u8)~(SP),			// CH_SEGP
};	

// frame buffer (contains inverted segments SA..SP: set segment to 0 to light on)
//  Note: Last digit with index 9 is not visible, it is used only to scan keys.
u8 FrameBuf[DISP_NUM] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

// display buffer (contains digits CH_0,...)
// - OR character with CH_DOT flag, to indicate dot.
//  Note: Last digit with index 9 is not visible, it is used only to scan keys.
u8 DispBuf[DISP_NUM] = { CH_SPC, CH_SPC, CH_SPC, CH_SPC, CH_SPC, CH_SPC, CH_SPC, CH_SPC, CH_SPC, CH_SPC };

// map of pressed key (>0 if pressed)
volatile u8 KeyMap[KEY_NUM];

// keyboard buffer
volatile u8 KeyBuf[KEYBUF_SIZE];// keyboard buffer
volatile u8 KeyWriteOff = 0;	// write offset to keyboard buffer
volatile u8 KeyReadOff = 0;	// read offset from keyboard buffer

// remap key index to key code
const u8 KeyRemap[KEY_NUM] = {
	//  D1       D2       D3       D4       D5       D6       D7       D8       D9      D10
	 KEY_1,   KEY_2,   KEY_3,   KEY_4,   KEY_5,   KEY_6,   KEY_7,   KEY_8,   KEY_9, KEY_DOT,	// row KN
	KEY_CE, KEY_3RD, KEY_ADD, KEY_SUB, KEY_DIV, KEY_MUL, KEY_2ND,  KEY_EE,   KEY_0, KEY_EQU,	// row KO
};

// index of KeyScan digit (incremented every 1 ms)
volatile u8 KeyScanInx = 0;

// check free send byte to other CPU
Bool CPU_SendReady()
{
	return USART1_TxEmpty();
}

// send byte to other CPU, wait for ready
void CPU_Send(u8 data)
{
	USART1_SendChar(data);
}

// check received byte from other CPU
Bool CPU_RecvReady()
{
	return USART1_RxReady();
}

// receive byte from other CPU, wait for ready
u8 CPU_Recv()
{
	return USART1_RecvChar();
}

// lock CPU communication from interrupt
void CPU_IntLock()
{
	cb();
	DispInitOK = False;
	cb();
	WaitUs(20);

	// clear all segments
	GPIOC_OutAll(0xff);
	GPIO_Out1(PD4);
}

// unlock CPU communication from interrupt
void CPU_IntUnlock()
{
	cb();
	DispInitOK = True;
	cb();
}

// CPU synchronization at startup
void CPU_SyncInit()
{
	u8 ch;
	int ok = 0;
	u32 start = Time();
#define TIMEOUT	(HCLK_PER_US*500000) // timeout 500ms
	while (True)
	{
		// check time-out
		if (((u32)(Time() - start)) >= (u32)TIMEOUT)
		{
			// CPU2 error ... only darkening of segments, we cannot display anything
			CPU_IntLock();
			while (True) {}
		}

		// send next request
		if (CPU_SendReady()) CPU_Send(CPU_CMD_SYNC);

		// check response
		if (CPU_RecvReady())
		{
			ch = CPU_Recv();

			// invalid character
			if (ch != CPU_RES_SYNC)
			{
				ok = 0;
			}

			// character counter
			else
			{
				// finish with 10 character
				ok++;
				if (ok >= 10) break;
			}
		}
	}

	// flush remaining SYNC responses (for 300us)
	start = Time();
	while (((u32)(Time() - start)) < ((u32)(HCLK_PER_US*300)))
	{
		if (CPU_RecvReady()) ch = CPU_Recv();
	}
}

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet(void)
{
	// check if keyboard buffer is empty
	u8 r = KeyReadOff;
	cb();
	if (r == KeyWriteOff) return NOKEY;

	// get key from keyboard buffer
	u8 ch = KeyBuf[r];

	// write new read offset
	r++;
	if (r >= KEYBUF_SIZE) r = 0;
	KeyReadOff = r;

	return ch;
}

// key flush
void KeyFlush(void)
{
	while (KeyGet() != NOKEY) {}
}

// check no pressed key
Bool KeyNoPressed(void)
{
	int i;
	for (i = 0; i < KEY_NUM; i++) if (KeyMap[i] > 0) return False;
	return True;
}

// wait for no key pressed
void KeyWaitNoPressed(void)
{
	while (!KeyNoPressed()) {}
}

// write key to keyboard buffer (called from KeyScan())
void KeyWriteKey(u8 key)
{
	u8 w = KeyWriteOff;
	u8 w2 = w + 1;
	if (w2 >= KEYBUF_SIZE) w2 = 0;
	if (w2 != KeyReadOff)
	{
		KeyBuf[w] = key;
		cb();
		KeyWriteOff = w2;
	}
}

// interrupt to serve display and keys - called from SysTick every 1 ms, whole cycle takes 10ms (=100 Hz)
void KeyScan(void)
{
	// exit if not initialized
	if (!DispInitOK) return;

	// get index (0..9)
	int inx = KeyScanInx;

	// clear all segments
	GPIOC_OutAll(0xff);
	GPIO_Out1(PD4);

	// send command to switch to the digit
	USART1_TxWrite(CPU_CMD_D1 + inx);

	// short delay: 10 us required to send the digit, plus some time to process the command
	//  checked: at least 11us is required for keys to be scanned correctly
	WaitUs(15);

	// get key input
	cb();
	int key = GPIOA_InAll();
	cb();

	// output segments to the display
	u8 seg = FrameBuf[inx];
	GPIOC_OutAll(seg);
	GPIO_Out(PD4, ((seg & SP) == 0) ? 0 : 1);

	// update KN row (input PA1)
	Bool press = (key & B1) != 0; // get pressed flag of KN
	u8 keyinx = KeyRemap[inx]; // key index
	volatile u8* map = &KeyMap[keyinx]; // index of key map
	u8 m = *map; // get map counter
	if (press)
	{
		if (m == 0) KeyWriteKey(keyinx); // write key press
		m = KEY_RELEASE_CNT; // restart counter if key is pressed
	}
	if (m > 0) m--; // decrease press counter
	*map = m; // store new key counter

	// update KO row (input PA2)
	press = (key & B2) != 0; // get pressed flag of KO
	keyinx = KeyRemap[inx + DISP_NUM]; // key index
	map = &KeyMap[keyinx]; // index of key map
	m = *map; // get map counter
	if (press)
	{
		if (m == 0) KeyWriteKey(keyinx); // write key press
		m = KEY_RELEASE_CNT; // restart counter if key is pressed
	}
	if (m > 0) m--; // decrease press counter
	*map = m; // store new key counter

	// update index
	inx++;
	if (inx >= DISP_NUM) inx = 0;
	KeyScanInx = inx;
}

// display update 1 digit (index inx = 0..DISP_NUM-1)
void DigUpdate(int inx)
{
	u8 ch = DispBuf[inx]; // get character from display buffer
	u8 seg = SegDig[ch & CH_MASK]; // get segments of the character
	if ((ch & CH_DOT) != 0) seg &= ~SP; // setup dot segment
	FrameBuf[inx] = seg;
}

// write digit to display buffer (index inx = 0..DISP_NUM-1, character ch = CH_*)
void DigWrite(int inx, u8 ch)
{
	DispBuf[inx] = ch;
	DigUpdate(inx);
}

// display update - convert digits from DispBuf to segments in FrameBuf
void DispUpdate(void)
{
	int i;
	for (i = 0; i < DISP_NUM; i++) DigUpdate(i);
}

// read memory slot
void ReadSlot(sSlot* s, int inx)
{
	// lock
	CPU_IntLock();

	// send command to read slot
	CPU_Send(CPU_LOAD_FIRST + inx);

	// receive data
	u8* d = s->data;
	int i;
	for (i = SLOTNUM; i > 0; i--)
	{
		*d++ = CPU_Recv();
		CPU_Send(CPU_CMD_NEXT);
	}

	// unlock
	CPU_IntUnlock();
}

// write memory slot
void WriteSlot(const sSlot* s, int inx)
{
	// lock
	CPU_IntLock();

	// send command to write slot
	CPU_Send(CPU_SAVE_FIRST + inx);

	// receive data
	const u8* src = s->data;
	int i;
	for (i = SLOTNUM; i > 0; i--)
	{
		CPU_Recv();
		CPU_Send(*src++);
	}

	// wait for write
	CPU_Recv();

	// unlock
	CPU_IntUnlock();
}

// main program
int main(void)
{
	// Remap PA1 & PA2 pins to OSC_IN & OSC_OUT (default 0)
	// 0 ... pins PA1 & PA2 are used as GPIO ports
	GPIO_Remap_PA1PA2(0);

	// setup pins to output
	GPIO_Mode(PC0, GPIO_MODE_OUT);	// SA
	GPIO_Mode(PC1, GPIO_MODE_OUT);	// SB
	GPIO_Mode(PC2, GPIO_MODE_OUT);	// SC
	GPIO_Mode(PC3, GPIO_MODE_OUT);	// SD
	GPIO_Mode(PC4, GPIO_MODE_OUT);	// SE
	GPIO_Mode(PC6, GPIO_MODE_OUT);	// SF
	GPIO_Mode(PC7, GPIO_MODE_OUT);	// SG
	GPIO_Mode(PD4, GPIO_MODE_OUT);	// SP

	// setup keyboard input pins, with pull-down
	GPIO_Mode(PA1, GPIO_MODE_IN_PD);	// KN
	GPIO_Mode(PA2, GPIO_MODE_IN_PD);	// KO

	// setup USART1 mapping 0, to communicate with CPU2
	// 0 ... PD5:TX, PD6:RX, PD3:CTS, PC2:RTS
// PD5: USART1_TX mapping 0, TX1-RX2 (send from CPU1 to CPU2, this is CPU1)
// PD6: USART1_RX mapping 0, RX1-TX2 (send from CPU2 to CPU1, this is CPU1)
	GPIO_Remap_USART1(0);
	USART1_Init((RCC_GetFreq(CLK_HCLK) + CPU_UART_DIV/2)/CPU_UART_DIV,
		USART_WORDLEN_8, USART_PARITY_NONE, USART_STOP_1);
	GPIO_Mode(PD5, GPIO_MODE_AF);		// TX
	GPIO_Mode(PD6, GPIO_MODE_IN);		// RX

	// CPU synchronization at startup
	CPU_SyncInit();

	// get configuration
	int calcmode;
	do {
		CPU_Send(CPU_CMD_GETDEV);
		calcmode = CPU_Recv();
	} while ((calcmode < 1) || (calcmode > 3));
	CalcMode = calcmode;

	// set flag - display service is initialized (KeyScan can start working)
//	DispInitOK = True; ... enabled in ReadSlot

	// read memory slot (it enables KeyScan)
	ReadSlot(&Mem.slot, 0);

	// wait some time to read keyboard - at least 10ms is required
	WaitMs(30);

	// check keys - setup configuration
	Bool key1 = KeyIsPressed(KEY_1);
	Bool key2 = KeyIsPressed(KEY_2);
	Bool key3 = KeyIsPressed(KEY_3);
	if (key1 || key2 || key3)
	{
		// get required mode
		calcmode = MODE_CALCUL;
		if (key2) calcmode = MODE_SINCLAIR;
		if (key3) calcmode = MODE_DATAMATH;

		// write selected mode to the flash memory
		if (calcmode != CalcMode)
		{
			CalcMode = calcmode;
			CPU_IntLock();
			CPU_Send(calcmode);
			CPU_Recv();
			CPU_IntUnlock();
		}

		// display selected mode
		const u8* t = IntroTextCalcul;
		if (calcmode == MODE_SINCLAIR) t = IntroTextSinclair;
		if (calcmode == MODE_DATAMATH) t = IntroTextDatamath;
		memcpy(DispBuf, t, DISP_NUM-1);
		DispUpdate();

		// wait for release the keys
		KeyWaitNoPressed();

		// clear display
		memset(DispBuf, CH_SPC, DISP_NUM-1);
		DispUpdate();
	}

#if 0
	// DEBUG: display current mode
	else
	{
		const u8* t = IntroTextCalcul;
		if (IS_SINCLAIR) t = IntroTextSinclair;
		if (IS_DATAMATH) t = IntroTextDatamath;
		memcpy(DispBuf, t, DISP_NUM-1);
		DispUpdate();
		WaitMs(1000);
		memset(DispBuf, CH_SPC, DISP_NUM-1);
		DispUpdate();
	}
#endif

	// flush keyboard
	KeyFlush();

	// Run emulator or calculator
	if (IS_CALCUL)
		RunCalc();
	else
		RunEmu();
}
