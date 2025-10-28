
// ****************************************************************************
//
//                             PidiPC - Keyboard
//
// ****************************************************************************
// PD3: ROW1
// PD4: ROW2
// PD7: ROW3
// PD6: USART1_TX mapping 1, TX1-RX2 (send from CPU1 to CPU2, this is CPU1)
// PD5: USART1_RX mapping 1, RX1-TX2 (send from CPU2 to CPU1, this is CPU1)
//
// Input from the buttons is handled during the VGA rendering service,
// during back porch vertical scanlines (33 scanlines).
// Whole line = 31.8 us. 10us to transfer 1 byte. 4us wait after setting ROWs.

#if USE_KEY		// 1=use keyboard support

#ifndef _PIDIPC_KEY_H
#define _PIDIPC_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

// Button codes
#define KEY_1		1	// 1 NOT
#define KEY_2		2	// 2 AND
#define KEY_3		3	// 3 THEN
#define KEY_4		4	// 4 TO
#define KEY_5		5	// 5 LEFT
#define KEY_6		6	// 6 DOWN
#define KEY_7		7	// 7 UP
#define KEY_8		8	// 8 RIGHT
#define KEY_9		9	// 9 HOME
#define KEY_0		10	// 0 RUBOUT

#define KEY_Q		11	// Q
#define KEY_W		12	// W
#define KEY_E		13	// E
#define KEY_R		14	// R
#define KEY_T		15	// T
#define KEY_Y		16	// Y "
#define KEY_U		17	// U $
#define KEY_I		18	// I (
#define KEY_O		19	// O )
#define KEY_P		20	// P *

#define KEY_A		21	// A
#define KEY_S		22	// S
#define KEY_D		23	// D
#define KEY_F		24	// F
#define KEY_G		25	// G
#define KEY_H		26	// H **
#define KEY_J		27	// J -
#define KEY_K		28	// K +
#define KEY_L		29	// L =
#define KEY_NL		30	// NEW LINE, EDIT

#define KEY_SHIFT	31	// SHIFT
#define KEY_Z		32	// Z :
#define KEY_X		33	// X ;
#define KEY_C		34	// C ?
#define KEY_V		35	// V /
#define KEY_B		36	// B OR
#define KEY_N		37	// N <
#define KEY_M		38	// M >
#define KEY_DOT		39	// . ,
#define KEY_SPACE	40	// SPACE BREAK

#define KEY_RIGHT	KEY_8	// RIGHT
#define KEY_UP		KEY_7	// UP
#define KEY_LEFT	KEY_5	// LEFT
#define KEY_DOWN	KEY_6	// DOWN

#define NOKEY		0	// no key

#define KEY_NUM		40	// number of buttons

// commands from CPU1 to CPU2
#define CPU_CMD_SYNC	0x16		// sync - echo CPU_STATE_SYNC back, and set ROW4 to 1
#define CPU_CMD_ROW41	0x17		// return columns in 2 bytes (in bits 0..4) and set ROW4 to 1
#define CPU_CMD_ROW40	0x18		// return columns in 2 bytes (in bits 0..4) and set ROW4 to 0

// state from CPU2 to CPU1
#define CPU_STATE_SYNC	0x15		// sync - echo back after CPU_CMD_SYNC

// keyboard buffer
// If you change the settings, also check the code for reading the buttons in pidipc_vga_asm.S.
#define KEYBUF_SIZE	16	// size of keyboard buffer
extern volatile u8 KeyReleaseCnt[KEY_NUM*2]; // key release counter + key repeat counter; >0 if key is pressed (without NOKEY)
extern u8 KeyBuf[KEYBUF_SIZE];	// keyboard buffer
extern volatile u8 KeyWriteOff;	// write offset to keyboard buffer
extern volatile u8 KeyReadOff;	// read offset from keyboard buffer
extern volatile u8 CPUIntLocked; // CPU communication from interrupt is locked (prohibited)
extern u8 CPUIntLockedReq;	// request to lock CPU communication from interrupt

// check if button KEY_* is currently pressed
Bool KeyPressed(int key);
//INLINE Bool KeyPressed(int key) { return KeyReleaseCnt[key-1] > 0; }

// get button from keyboard buffer KEY_* (returns NOKEY if no key)
u8 KeyGet();

// check if joystick is pressed (KEY_RIGHT, KEY_UP, KEY_LEFT, KEY_DOWN, KEY_A, KEY_B, KEY_X, KEY_Y)
Bool JoyPressed(int key);

// get joystick (returns NOKEY or KEY_RIGHT, KEY_UP, KEY_LEFT, KEY_DOWN, KEY_A, KEY_B, KEY_X, KEY_Y)
u8 JoyGet();

// Get character (Remap keys to ASCII characters; returns NOKEY of no character)
char KeyGetChar();

// key flush
void KeyFlush();

// check no pressed key
Bool KeyNoPressed();

// wait for no key pressed
void KeyWaitNoPressed();

// Initialize keyboard service (should be called before display init)
void KeyInit();

// terminate keyboard
void KeyTerm();

// CPU synchronization at startup
void CPU_SyncInit();

// check free send byte to other CPU
Bool CPU_SendReady();

// send byte to other CPU
void CPU_Send(u8 data);

// check received byte from other CPU
Bool CPU_RecvReady();

// receive byte from other CPU
u8 CPU_Recv();

// lock CPU communication from interrupt
void CPU_IntLock();

// unlock CPU communication from interrupt
void CPU_IntUnlock();

#ifdef __cplusplus
}
#endif

#endif // _PIDIPC_KEY_H

#endif // USE_KEY
