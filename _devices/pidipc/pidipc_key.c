
// ****************************************************************************
//
//                             PidiPC - Keyboard
//
// ****************************************************************************

#include "../../includes.h"

#if USE_KEY		// 1=use keyboard support

// keyboard buffer
volatile u8 KeyReleaseCnt[KEY_NUM*2]; // key release counter + key repeat counter; >0 if key is pressed (without NOKEY)
u8 KeyBuf[KEYBUF_SIZE];		// keyboard buffer
volatile u8 KeyWriteOff = 0;	// write offset to keyboard buffer
volatile u8 KeyReadOff = 0;	// read offset from keyboard buffer
volatile u8 CPUIntLocked = False; // CPU communication from interrupt is locked (prohibited)
u8 CPUIntLockedReq = False; // request to lock CPU communication from interrupt

// Remap keys to ASCII characters
const char KeyCharRemap[KEY_NUM+1] = {
	0,		// #define NOKEY		0	// no key
	'1',		// #define KEY_1		1	// 1 NOT
	'2',		// #define KEY_2		2	// 2 AND
	'3',		// #define KEY_3		3	// 3 THEN
	'4',		// #define KEY_4		4	// 4 TO
	'5',		// #define KEY_5		5	// 5 LEFT
	'6',		// #define KEY_6		6	// 6 DOWN
	'7',		// #define KEY_7		7	// 7 UP
	'8',		// #define KEY_8		8	// 8 RIGHT
	'9',		// #define KEY_9		9	// 9 HOME
	'0',		// #define KEY_0		10	// 0 RUBOUT

	'Q',		// #define KEY_Q		11	// Q
	'W',		// #define KEY_W		12	// W
	'E',		// #define KEY_E		13	// E
	'R',		// #define KEY_R		14	// R
	'T',		// #define KEY_T		15	// T
	'Y',		// #define KEY_Y		16	// Y "
	'U',		// #define KEY_U		17	// U $
	'I',		// #define KEY_I		18	// I (
	'O',		// #define KEY_O		19	// O )
	'P',		// #define KEY_P		20	// P *

	'A',		// #define KEY_A		21	// A
	'S',		// #define KEY_S		22	// S
	'D',		// #define KEY_D		23	// D
	'F',		// #define KEY_F		24	// F
	'G',		// #define KEY_G		25	// G
	'H',		// #define KEY_H		26	// H **
	'J',		// #define KEY_J		27	// J -
	'K',		// #define KEY_K		28	// K +
	'L',		// #define KEY_L		29	// L =
	13,		// #define KEY_NL		30	// NEW LINE, EDIT

	27,		// #define KEY_SHIFT	31	// SHIFT
	'Z',		// #define KEY_Z		32	// Z :
	'X',		// #define KEY_X		33	// X ;
	'C',		// #define KEY_C		34	// C ?
	'V',		// #define KEY_V		35	// V /
	'B',		// #define KEY_B		36	// B OR
	'N',		// #define KEY_N		37	// N <
	'M',		// #define KEY_M		38	// M >
	'.',		// #define KEY_DOT		39	// , ,
	' ',		// #define KEY_SPACE	40	// SPACE BREAK
};

const char KeyCharRemapShift[KEY_NUM+1] = {
	0,		// #define NOKEY		0	// no key
	'1',		// #define KEY_1		1	// 1 NOT
	'2',		// #define KEY_2		2	// 2 AND
	'3',		// #define KEY_3		3	// 3 THEN
	'4',		// #define KEY_4		4	// 4 TO
	'5',		// #define KEY_5		5	// 5 LEFT
	'6',		// #define KEY_6		6	// 6 DOWN
	'7',		// #define KEY_7		7	// 7 UP
	'8',		// #define KEY_8		8	// 8 RIGHT
	'9',		// #define KEY_9		9	// 9 HOME
	'0',		// #define KEY_0		10	// 0 RUBOUT

	' ',		// #define KEY_Q		11	// Q
	' ',		// #define KEY_W		12	// W
	' ',		// #define KEY_E		13	// E
	' ',		// #define KEY_R		14	// R
	' ',		// #define KEY_T		15	// T
	'"',		// #define KEY_Y		16	// Y "
	'$',		// #define KEY_U		17	// U $
	'(',		// #define KEY_I		18	// I (
	')',		// #define KEY_O		19	// O )
	'*',		// #define KEY_P		20	// P *

	' ',		// #define KEY_A		21	// A
	' ',		// #define KEY_S		22	// S
	' ',		// #define KEY_D		23	// D
	' ',		// #define KEY_F		24	// F
	' ',		// #define KEY_G		25	// G
	'*',		// #define KEY_H		26	// H **
	'-',		// #define KEY_J		27	// J -
	'+',		// #define KEY_K		28	// K +
	'=',		// #define KEY_L		29	// L =
	13,		// #define KEY_NL		30	// NEW LINE, EDIT

	27,		// #define KEY_SHIFT	31	// SHIFT
	':',		// #define KEY_Z		32	// Z :
	';',		// #define KEY_X		33	// X ;
	'?',		// #define KEY_C		34	// C ?
	'/',		// #define KEY_V		35	// V /
	' ',		// #define KEY_B		36	// B OR
	'<',		// #define KEY_N		37	// N <
	'>',		// #define KEY_M		38	// M >
	',',		// #define KEY_DOT		39	// . ,
	' ',		// #define KEY_SPACE	40	// SPACE BREAK
};

// check if button KEY_* is currently pressed
Bool KeyPressed(int key)
{
	return KeyReleaseCnt[key-1] > 0;
}

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet()
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
	cb();
	KeyReadOff = r;

	return ch;
}

// check if joystick is pressed (KEY_RIGHT, KEY_UP, KEY_LEFT, KEY_DOWN, KEY_A, KEY_B, KEY_X, KEY_Y)
Bool JoyPressed(int key)
{
	switch (key)
	{
	case KEY_RIGHT:
		return KeyPressed(KEY_RIGHT) || KeyPressed(KEY_F);

	case KEY_UP:
		return KeyPressed(KEY_UP) || KeyPressed(KEY_E);

	case KEY_LEFT:
		return KeyPressed(KEY_LEFT) || KeyPressed(KEY_S);

	case KEY_DOWN:
		return KeyPressed(KEY_DOWN) || KeyPressed(KEY_D);

	case KEY_A:
		return KeyPressed(KEY_A) || KeyPressed(KEY_SPACE);

	case KEY_B:
		return KeyPressed(KEY_B) || KeyPressed(KEY_NL);

	case KEY_X:
		return KeyPressed(KEY_X) || KeyPressed(KEY_P);

	case KEY_Y:
		return KeyPressed(KEY_Y) || KeyPressed(KEY_0);

	default:
		return False;
	}
}

// get joystick (returns NOKEY or KEY_RIGHT, KEY_UP, KEY_LEFT, KEY_DOWN, KEY_A, KEY_B, KEY_X, KEY_Y)
u8 JoyGet()
{
	u8 key;
	while (True)
	{
		key = KeyGet();
		switch (key)
		{
		case KEY_RIGHT:
		case KEY_F:
			return KEY_RIGHT;

		case KEY_UP:
		case KEY_E:
			return KEY_UP;

		case KEY_LEFT:
		case KEY_S:
			return KEY_LEFT;

		case KEY_DOWN:
		case KEY_D:
			return KEY_DOWN;

		case KEY_A:
		case KEY_SPACE:
			return KEY_A;

		case KEY_B:
		case KEY_NL:
			return KEY_B;

		case KEY_X:
		case KEY_P:
			return KEY_X;

		case KEY_Y:
		case KEY_0:
			return KEY_Y;

		case NOKEY:
			return NOKEY;
		}
	}
}

// key flush
void KeyFlush()
{
	while (KeyGet() != NOKEY) {}
}

// check no pressed key
Bool KeyNoPressed()
{
	int i;
	for (i = 0; i < KEY_NUM; i++) if (KeyReleaseCnt[i] > 0) return False;
	return True;
}

// wait for no key pressed
void KeyWaitNoPressed()
{
	while (!KeyNoPressed()) {}
}

// Get character (Remap keys to ASCII characters; returns NOKEY of no character)
char KeyGetChar()
{
	u8 key;
	while (True)
	{
		key = KeyGet();
		if (key == NOKEY) break;
		if (key != KEY_SHIFT) break;
	}

	if (key != NOKEY)
	{
		if (KeyPressed(KEY_SHIFT))
			return KeyCharRemapShift[key];
		else
			return KeyCharRemap[key];
	}
	return key;
}	

// Initialize keyboard service (should be called before display init)
void KeyInit()
{
	// initialize key ports, rows pull-up
// PD3: ROW1
// PD4: ROW2
// PD7: ROW3
	RCC_AFIClkEnable();
	RCC_PDClkEnable();
	GPIO_Out1(PD3);		// ROW1
	GPIO_Out1(PD4);		// ROW2
	GPIO_Out1(PD7);		// ROW3
	GPIO_Mode(PD3, GPIO_MODE_OD);	// ROW1
	GPIO_Mode(PD4, GPIO_MODE_OD);	// ROW2
	GPIO_Mode(PD7, GPIO_MODE_OD);	// ROW3

	// setup USART1 mapping 1, to communicate with CPU2
	// 1 ... PD6:TX, PD5:RX, PC6:CTS, PC7:RTS
// PD6: USART1_TX mapping 1, TX1-RX2 (send from CPU1 to CPU2, this is CPU1)
// PD5: USART1_RX mapping 1, RX1-TX2 (send from CPU2 to CPU1, this is CPU1)
	GPIO_Remap_USART1(1);
	USART1_Init((RCC_GetFreq(CLK_HCLK) + CPU_UART_DIV/2)/CPU_UART_DIV,
		USART_WORDLEN_8, USART_PARITY_NONE, USART_STOP_1);
	GPIO_Mode(PD6, GPIO_MODE_AF);	// TX
	GPIO_Mode(PD5, GPIO_MODE_IN);	// RX
}

// terminate keyboard
void KeyTerm()
{
	GPIO_PinReset(PD3);	// ROW1
	GPIO_PinReset(PD4);	// ROW0
	GPIO_PinReset(PD7);	// ROW3
	GPIO_PinReset(PD6);	// TX
	GPIO_PinReset(PD5);	// RX
}

// CPU synchronization at startup
void CPU_SyncInit()
{
	u8 ch;
	int ok = 0;
	u32 start = Time();
#define TIMEOUT	(HCLK_PER_US*500000)
	while (True)
	{
		// check time-out
		if (((u32)(Time() - start)) >= (u32)TIMEOUT)
		{
			ei();
#if USE_PRINT
			PrintClear();
			PrintText("CPU2 SYNC ERROR!");
#endif
			while (True) {}
		}

		// send next request
		if (CPU_SendReady()) CPU_Send(CPU_CMD_SYNC);

		// check response
		if (CPU_RecvReady())
		{
			ch = CPU_Recv();

			// invalid character
			if (ch != CPU_STATE_SYNC)
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

	// flush remaining SYNC responses
	start = Time();
	while (((u32)(Time() - start)) < ((u32)(HCLK_PER_US*300)))
	{
		if (CPU_RecvReady()) ch = CPU_Recv();
	}
}

// check free send byte to other CPU
Bool CPU_SendReady()
{
	return USART1_TxEmpty();
}

// send byte to other CPU
void CPU_Send(u8 data)
{
	USART1_SendChar(data);
}

// check received byte from other CPU
Bool CPU_RecvReady()
{
	return USART1_RxReady();
}

// receive byte from other CPU
u8 CPU_Recv()
{
	return USART1_RecvChar();
}

// lock CPU communication from interrupt
void CPU_IntLock()
{
	CPUIntLockedReq = True;
	cb();
	while (!CPUIntLocked) { cb(); }
}

// unlock CPU communication from interrupt
void CPU_IntUnlock()
{
	CPUIntLockedReq = False;
	cb();
	while (CPUIntLocked) { cb(); }
}

#endif // USE_KEY
