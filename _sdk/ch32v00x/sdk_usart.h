
// ****************************************************************************
//
//                                   USART
//
// ****************************************************************************

#if USE_USART		// 1=use USART peripheral

#ifndef _SDK_USART_H
#define _SDK_USART_H

#ifdef __cplusplus
extern "C" {
#endif

// USART registers
typedef struct {
	io32	STATR;		// 0x00: status register
	io32	DATAR;		// 0x04: data register
	io32	BRR;		// 0x08: baud rate register
	io32	CTLR1;		// 0x0C: control register 1
	io32	CTLR2;		// 0x10: control register 2
	io32	CTLR3;		// 0x14: control register 3
	io32	GPR;		// 0x18: protection and prescaler register
} USART_t;
STATIC_ASSERT(sizeof(USART_t) == 0x1C, "Incorrect USART_t!");
#define USART1	((USART_t*)USART1_BASE)	// 0x40013800
#define USART2	((USART_t*)USART2_BASE)	// 0x40004400 (only CH32V005-CH32V007)

// Get USART periphery from USART index 1.. (returns NULL if not valid)
INLINE USART_t* USART_GetHw(int inx) { return (inx == 1) ? USART1 : ((inx == 2) ? USART2 : NULL); }

// Get USART index 1.. from USART periphery (returns -1 if not valid)
INLINE int USART_GetInx(USART_t* usart) { return (usart == USART1) ? 1 : ((usart == USART2) ? 2 : -1); }

// Parity
#define USART_PARITY_NONE	0	// none parity
//#define USART_PARITY_NONE	1	// none parity
#define USART_PARITY_EVEN	2	// even parity
#define USART_PARITY_ODD	3	// odd parity

// Stop bits
#define USART_STOP_1		0	// 1 stop bit
#define USART_STOP_05		1	// 0.5 stop bit
#define USART_STOP_2		2	// 2 stop bits
#define USART_STOP_15		3	// 1.5 stop bit

// Word length
#define USART_WORDLEN_8		0x00	// 8 data bits
#define USART_WORDLEN_9		0x01	// 9 data bits

// === Get status

// Get parity error flag on receive
// - Read this bit and then read data register to reset this bit.
INLINE Bool USARTx_ParityError(USART_t* usart) { return (usart->STATR & B0) != 0; }
INLINE Bool USART1_ParityError(void) { return USARTx_ParityError(USART1); }
INLINE Bool USART2_ParityError(void) { return USARTx_ParityError(USART2); }

// Get frame error flag on receive (synchronization error)
// - Read this bit and then read data register to reset this bit.
INLINE Bool USARTx_FrameError(USART_t* usart) { return (usart->STATR & B1) != 0; }
INLINE Bool USART1_FrameError(void) { return USARTx_FrameError(USART1); }
INLINE Bool USART2_FrameError(void) { return USARTx_FrameError(USART2); }

// Get noise error flag on receive
// - Read this bit and then read data register to reset this bit.
INLINE Bool USARTx_NoiseError(USART_t* usart) { return (usart->STATR & B2) != 0; }
INLINE Bool USART1_NoiseError(void) { return USARTx_NoiseError(USART1); }
INLINE Bool USART2_NoiseError(void) { return USARTx_NoiseError(USART2); }

// Get overload error flag on receive (receive data buffer is full)
INLINE Bool USARTx_OverloadError(USART_t* usart) { return (usart->STATR & B3) != 0; }
INLINE Bool USART1_OverloadError(void) { return USARTx_OverloadError(USART1); }
INLINE Bool USART2_OverloadError(void) { return USARTx_OverloadError(USART2); }

// Get bus idle error flag on receive
// - Read this bit and then read data register to reset this bit.
INLINE Bool USARTx_IdleError(USART_t* usart) { return (usart->STATR & B4) != 0; }
INLINE Bool USART1_IdleError(void) { return USARTx_IdleError(USART1); }
INLINE Bool USART2_IdleError(void) { return USARTx_IdleError(USART2); }

// Check if received data is ready
// - Read data register to reset this bit, or use USART1_RxReadyClr() function.
INLINE Bool USARTx_RxReady(USART_t* usart) { return (usart->STATR & B5) != 0; }
INLINE Bool USART1_RxReady(void) { return USARTx_RxReady(USART1); }
INLINE Bool USART2_RxReady(void) { return USARTx_RxReady(USART2); }

// Clear flag "received data is ready"
INLINE void USARTx_RxReadyClr(USART_t* usart) { usart->STATR &= ~B5; }
INLINE void USART1_RxReadyClr(void) { USARTx_RxReadyClr(USART1); }
INLINE void USART2_RxReadyClr(void) { USARTx_RxReadyClr(USART2); }

// Check if sending is completed (frame from shift register was sent)
// - Read this bit and then write data register, of use USART_TxSentClr() function.
INLINE Bool USARTx_TxSent(USART_t* usart) { return (usart->STATR & B6) != 0; }
INLINE Bool USART1_TxSent(void) { return USARTx_TxSent(USART1); }
INLINE Bool USART2_TxSent(void) { return USARTx_TxSent(USART2); }

// Clear flag "sending is completed"
INLINE void USARTx_TxSentClr(USART_t* usart) { usart->STATR &= ~B6; }
INLINE void USART1_TxSentClr(void) { USARTx_TxSentClr(USART1); }
INLINE void USART2_TxSentClr(void) { USARTx_TxSentClr(USART2); }

// Check if sending buffer is empty (TDR register was transfered to shift register)
INLINE Bool USARTx_TxEmpty(USART_t* usart) { return (usart->STATR & B7) != 0; }
INLINE Bool USART1_TxEmpty(void) { return USARTx_TxEmpty(USART1); }
INLINE Bool USART2_TxEmpty(void) { return USARTx_TxEmpty(USART2); }

// Check if LIN Break was detected
INLINE Bool USARTx_BreakError(USART_t* usart) { return (usart->STATR & B8) != 0; }
INLINE Bool USART1_BreakError(void) { return USARTx_BreakError(USART1); }
INLINE Bool USART2_BreakError(void) { return USARTx_BreakError(USART2); }

// Clear LIN Break detection flag
INLINE void USARTx_BreakErrorClr(USART_t* usart) { usart->STATR &= ~B8; }
INLINE void USART1_BreakErrorClr(void) { USARTx_BreakErrorClr(USART1); }
INLINE void USART2_BreakErrorClr(void) { USARTx_BreakErrorClr(USART2); }

// Check CTS state change flag
INLINE void USARTx_CTSChange(USART_t* usart) { usart->STATR &= ~B9; }
INLINE void USART1_CTSChange(void) { USARTx_CTSChange(USART1); }
INLINE void USART2_CTSChange(void) { USARTx_CTSChange(USART2); }

// Clear CTS state change flag
INLINE void USARTx_CTSChangeClr(USART_t* usart) { usart->STATR &= ~B9; }
INLINE void USART1_CTSChangeClr(void) { USARTx_CTSChangeClr(USART1); }
INLINE void USART2_CTSChangeClr(void) { USARTx_CTSChangeClr(USART2); }

// === Setup

// USART RCC clock Enable/Disable
INLINE void USART1_RCCClkEnable(void) { RCC_USART1ClkEnable(); }
INLINE void USART2_RCCClkEnable(void) { RCC_USART2ClkEnable(); }
INLINE void USARTx_RCCClkEnable(USART_t* usart)
{
	if (usart == USART1) USART1_RCCClkEnable();
	if (usart == USART2) USART2_RCCClkEnable();
}

INLINE void USART1_RCCClkDisable(void) { RCC_USART1ClkDisable(); }
INLINE void USART2_RCCClkDisable(void) { RCC_USART2ClkDisable(); }
INLINE void USARTx_RCCClkDisable(USART_t* usart)
{
	if (usart == USART1) USART1_RCCClkDisable();
	if (usart == USART2) USART2_RCCClkDisable();
}

// USART reset to default values
INLINE void USART1_Reset(void) { RCC_USART1Reset(); }
INLINE void USART2_Reset(void) { RCC_USART2Reset(); }
INLINE void USARTx_Reset(USART_t* usart)
{
	if (usart == USART1) USART1_Reset();
	if (usart == USART2) USART2_Reset();
}

// Set integer baudrate register in 1/16 fractions (in range 16..65535)
//  baudrate = HCLK/ibaud, ibaud = HCLK/baudrate
//  Example: HCLK=48000000, baudrate=115200, ibaud=48000000/115200=417, real baudrate=115109, error 0.08%
INLINE void USARTx_IBaud(USART_t* usart, int ibaud) { usart->BRR = ibaud; }
INLINE void USART1_IBaud(int ibaud) { USARTx_IBaud(USART1, ibaud); }
INLINE void USART2_IBaud(int ibaud) { USARTx_IBaud(USART2, ibaud); }

// Get integer baudrate register in 1/16 fractions 16..65535
//  baudrate = HCLK/ibaud, ibaud = HCLK/baudrate
INLINE int USARTx_GetIBaud(USART_t* usart) { return usart->BRR & 0xffff; }
INLINE int USART1_GetIBaud(void) { return USARTx_GetIBaud(USART1); }
INLINE int USART2_GetIBaud(void) { return USARTx_GetIBaud(USART2); }

// Set baudrate (in Bauds)
void USARTx_Baud(USART_t* usart, int baud);
INLINE void USART1_Baud(int baud) { USARTx_Baud(USART1, baud); }
INLINE void USART2_Baud(int baud) { USARTx_Baud(USART2, baud); }

// Get baudrate (in Bauds)
int USARTx_GetBaud(USART_t* usart);
INLINE int USART1_GetBaud(void) { return USARTx_GetBaud(USART1); }
INLINE int USART2_GetBaud(void) { return USARTx_GetBaud(USART2); }

// Send break character
INLINE void USARTx_SendBreak(USART_t* usart) { usart->CTLR1 |= B0; }
INLINE void USART1_SendBreak(void) { USARTx_SendBreak(USART1); }
INLINE void USART2_SendBreak(void) { USARTx_SendBreak(USART2); }

// Enable/Disable receiver silent mode (receiver wakeup; default disabled)
// - Before enabling silent mode, the USART needs to receive a data byte first,
//   otherwise it cannot be woken up by bus idle in silent mode.
// - When configured as address mark wakeup, this flag cannot be modified
//   by software when RXNE (read data register non-empty) is set.
INLINE void USARTx_SilentEnable(USART_t* usart) { usart->CTLR1 |= B1; }
INLINE void USART1_SilentEnable(void) { USARTx_SilentEnable(USART1); }
INLINE void USART2_SilentEnable(void) { USARTx_SilentEnable(USART2); }

INLINE void USARTx_SilentDisable(USART_t* usart) { usart->CTLR1 &= ~B1; }
INLINE void USART1_SilentDisable(void) { USARTx_SilentDisable(USART1); }
INLINE void USART2_SilentDisable(void) { USARTx_SilentDisable(USART2); }

// Enable/Disable receiver (default disabled)
INLINE void USARTx_RxEnable(USART_t* usart) { usart->CTLR1 |= B2; }
INLINE void USART1_RxEnable(void) { USARTx_RxEnable(USART1); }
INLINE void USART2_RxEnable(void) { USARTx_RxEnable(USART2); }

INLINE void USARTx_RxDisable(USART_t* usart) { usart->CTLR1 &= ~B2; }
INLINE void USART1_RxDisable(void) { USARTx_RxDisable(USART1); }
INLINE void USART2_RxDisable(void) { USARTx_RxDisable(USART2); }

// Enable/Disable transmitter (default disabled)
INLINE void USARTx_TxEnable(USART_t* usart) { usart->CTLR1 |= B3; }
INLINE void USART1_TxEnable(void) { USARTx_TxEnable(USART1); }
INLINE void USART2_TxEnable(void) { USARTx_TxEnable(USART2); }

INLINE void USARTx_TxDisable(USART_t* usart) { usart->CTLR1 &= ~B3; }
INLINE void USART1_TxDisable(void) { USARTx_TxDisable(USART1); }
INLINE void USART2_TxDisable(void) { USARTx_TxDisable(USART2); }

// Set parity USART_PARITY_* (default none)
INLINE void USARTx_Parity(USART_t* usart, int parity) { usart->CTLR1 = (usart->CTLR1 & (3<<9)) | (parity<<9); }
INLINE void USART1_Parity(int parity) { USARTx_Parity(USART1, parity); }
INLINE void USART2_Parity(int parity) { USARTx_Parity(USART2, parity); }

// Set wake-up method to Address marker or Bus Idle (default marker)
INLINE void USARTx_WakeUpMarker(USART_t* usart) { usart->CTLR1 |= B11; }
INLINE void USART1_WakeUpMarker(void) { USARTx_WakeUpMarker(USART1); }
INLINE void USART2_WakeUpMarker(void) { USARTx_WakeUpMarker(USART2); }

INLINE void USARTx_WakeUpIdle(USART_t* usart) { usart->CTLR1 &= ~B11; }
INLINE void USART1_WakeUpIdle(void) { USARTx_WakeUpIdle(USART1); }
INLINE void USART2_WakeUpIdle(void) { USARTx_WakeUpIdle(USART2); }

// Set word length USART_WORDLEN_* (default 8 bits)
INLINE void USARTx_WordLen(USART_t* usart, int len)
	{ usart->CTLR1 = (usart->CTLR1 & ~(B12|B14|B15)) | (len << 12); }
INLINE void USART1_WordLen(int len) { USARTx_WordLen(USART1, len); }
INLINE void USART2_WordLen(int len) { USARTx_WordLen(USART2, len); }

// Enable/Disable USART (default disabled)
INLINE void USARTx_Enable(USART_t* usart) { usart->CTLR1 |= B13; }
INLINE void USART1_Enable(void) { USARTx_Enable(USART1); }
INLINE void USART2_Enable(void) { USARTx_Enable(USART2); }

INLINE void USARTx_Disable(USART_t* usart) { usart->CTLR1 &= ~B13; }
INLINE void USART1_Disable(void) { USARTx_Disable(USART1); }
INLINE void USART2_Disable(void) { USARTx_Disable(USART2); }

// Set address of USART node in multiprocessor communication 0..15 (default 0)
INLINE void USARTx_Addr(USART_t* usart, int addr) { usart->CTLR2 = (usart->CTLR1 & ~0x0f) | addr; }
INLINE void USART1_Addr(int addr) { USARTx_Addr(USART1, addr); }
INLINE void USART2_Addr(int addr) { USARTx_Addr(USART2, addr); }

// Set LIN Break detection length to 10 or 11 bits (default 10 bits)
INLINE void USARTx_LinBreak10(USART_t* usart) { usart->CTLR2 &= ~B5; }
INLINE void USART1_LinBreak10(void) { USARTx_LinBreak10(USART1); }
INLINE void USART2_LinBreak10(void) { USARTx_LinBreak10(USART2); }

INLINE void USARTx_LinBreak11(USART_t* usart) { usart->CTLR2 |= B5; }
INLINE void USART1_LinBreak11(void) { USARTx_LinBreak11(USART1); }
INLINE void USART2_LinBreak11(void) { USARTx_LinBreak11(USART2); }

/* ... not supported
// Enable/Disable output last bit clock pulse (default disabled)
INLINE void USARTx_LastBitClkEnable(USART_t* usart) { usart->CTLR2 |= B8; }
INLINE void USART1_LastBitClkEnable(void) { USARTx_LastBitClkEnable(USART1); }
INLINE void USART2_LastBitClkEnable(void) { USARTx_LastBitClkEnable(USART2); }

INLINE void USARTx_LastBitClkDisable(USART_t* usart) { usart->CTLR2 &= ~B8; }
INLINE void USART1_LastBitClkDisable(void) { USARTx_LastBitClkDisable(USART1); }
INLINE void USART2_LastBitClkDisable(void) { USARTx_LastBitClkDisable(USART2); }

// Select clock phase of data capture to First/Second edge (default first edge)
// - This bit cannot be modified after enabling transmit.
INLINE void USARTx_ClockPhaseFirst(USART_t* usart) { usart->CTLR2 &= ~B9; }
INLINE void USART1_ClockPhaseFirst(void) { USARTx_ClockPhaseFirst(USART1); }
INLINE void USART2_ClockPhaseFirst(void) { USARTx_ClockPhaseFirst(USART2); }

INLINE void USARTx_ClockPhaseSecond(USART_t* usart) { usart->CTLR2 |= B9; }
INLINE void USART1_ClockPhaseSecond(void) { USARTx_ClockPhaseSecond(USART1); }
INLINE void USART2_ClockPhaseSecond(void) { USARTx_ClockPhaseSecond(USART2); }

// Select clock polarity - steady Low or High level (default low)
// - This bit cannot be modified after enabling transmit.
INLINE void USARTx_ClockPolLow(USART_t* usart) { usart->CTLR2 &= ~B10; }
INLINE void USART1_ClockPolLow(void) { USARTx_ClockPolLow(USART1); }
INLINE void USART2_ClockPolLow(void) { USARTx_ClockPolLow(USART2); }

INLINE void USARTx_ClockPolHigh(USART_t* usart) { usart->CTLR2 |= B10; }
INLINE void USART1_ClockPolHigh(void) { USARTx_ClockPolHigh(USART1); }
INLINE void USART2_ClockPolHigh(void) { USARTx_ClockPolHigh(USART2); }

// Enable/Disable clock (default disabled)
INLINE void USARTx_ClockEnable(USART_t* usart) { usart->CTLR2 |= B11; }
INLINE void USART1_ClockEnable(void) { USARTx_ClockEnable(USART1); }
INLINE void USART2_ClockEnable(void) { USARTx_ClockEnable(USART2); }

INLINE void USARTx_ClockDisable(USART_t* usart) { usart->CTLR2 &= ~B11; }
INLINE void USART1_ClockDisable(void) { USARTx_ClockDisable(USART1); }
INLINE void USART2_ClockDisable(void) { USARTx_ClockDisable(USART2); }
*/

// Set number of stop bits USART_STOP_* (default 1 stop bit)
INLINE void USARTx_Stop(USART_t* usart, int stop) { usart->CTLR2 = (usart->CTLR2 & ~(3 << 12)) | (stop << 12); }
INLINE void USART1_Stop(int stop) { USARTx_Stop(USART1, stop); }
INLINE void USART2_Stop(int stop) { USARTx_Stop(USART2, stop); }

// Enable/Disable LIN mode (capability to send LIN Synch Breaks; default disabled)
INLINE void USARTx_LINEnable(USART_t* usart) { usart->CTLR2 |= B14; }
INLINE void USART1_LINEnable(void) { USARTx_LINEnable(USART1); }
INLINE void USART2_LINEnable(void) { USARTx_LINEnable(USART2); }

INLINE void USARTx_LINDisable(USART_t* usart) { usart->CTLR2 &= ~B14; }
INLINE void USART1_LINDisable(void) { USARTx_LINDisable(USART1); }
INLINE void USART2_LINDisable(void) { USARTx_LINDisable(USART2); }

// Enable/Disable IsDA infrared mode (default disabled)
INLINE void USARTx_IrDAEnable(USART_t* usart) { usart->CTLR3 |= B1; }
INLINE void USART1_IrDAEnable(void) { USARTx_IrDAEnable(USART1); }
INLINE void USART2_IrDAEnable(void) { USARTx_IrDAEnable(USART2); }

INLINE void USARTx_IrDADisable(USART_t* usart) { usart->CTLR3 &= ~B1; }
INLINE void USART1_IrDADisable(void) { USARTx_IrDADisable(USART1); }
INLINE void USART2_IrDADisable(void) { USARTx_IrDADisable(USART2); }

// Enable/Disable IsDA low-power (default disabled)
INLINE void USARTx_IRLPEnable(USART_t* usart) { usart->CTLR3 |= B2; }
INLINE void USART1_IRLPEnable(void) { USARTx_IRLPEnable(USART1); }
INLINE void USART2_IRLPEnable(void) { USARTx_IRLPEnable(USART2); }

INLINE void USARTx_IRLPDisable(USART_t* usart) { usart->CTLR3 &= ~B2; }
INLINE void USART1_IRLPDisable(void) { USARTx_IRLPDisable(USART1); }
INLINE void USART2_IRLPDisable(void) { USARTx_IRLPDisable(USART2); }

// Enable/Disable half-duplex (default disabled)
INLINE void USARTx_HalfDuplexEnable(USART_t* usart) { usart->CTLR3 |= B3; }
INLINE void USART1_HalfDuplexEnable(void) { USARTx_HalfDuplexEnable(USART1); }
INLINE void USART2_HalfDuplexEnable(void) { USARTx_HalfDuplexEnable(USART2); }

INLINE void USARTx_HalfDuplexDisable(USART_t* usart) { usart->CTLR3 &= ~B3; }
INLINE void USART1_HalfDuplexDisable(void) { USARTx_HalfDuplexDisable(USART1); }
INLINE void USART2_HalfDuplexDisable(void) { USARTx_HalfDuplexDisable(USART2); }

/* ... not supported
// Enable/Disable smartcard NACK (default disabled)
INLINE void USARTx_NACKEnable(USART_t* usart) { usart->CTLR3 |= B4; }
INLINE void USART1_NACKEnable(void) { USARTx_NACKEnable(USART1); }
INLINE void USART2_NACKEnable(void) { USARTx_NACKEnable(USART2); }

INLINE void USARTx_NACKDisable(USART_t* usart) { usart->CTLR3 &= ~B4; }
INLINE void USART1_NACKDisable(void) { USARTx_NACKDisable(USART1); }
INLINE void USART2_NACKDisable(void) { USARTx_NACKDisable(USART2); }

// Enable/Disable smartcard mode (default disabled)
INLINE void USARTx_SmartCardEnable(USART_t* usart) { usart->CTLR3 |= B5; }
INLINE void USART1_SmartCardEnable(void) { USARTx_SmartCardEnable(USART1); }
INLINE void USART2_SmartCardEnable(void) { USARTx_SmartCardEnable(USART2); }

INLINE void USARTx_SmartCardDisable(USART_t* usart) { usart->CTLR3 &= ~B5; }
INLINE void USART1_SmartCardDisable(void) { USARTx_SmartCardDisable(USART1); }
INLINE void USART2_SmartCardDisable(void) { USARTx_SmartCardDisable(USART2); }
*/

// Enable/Disable receive DMA (default disabled)
INLINE void USARTx_RxDMAEnable(USART_t* usart) { usart->CTLR3 |= B6; }
INLINE void USART1_RxDMAEnable(void) { USARTx_RxDMAEnable(USART1); }
INLINE void USART2_RxDMAEnable(void) { USARTx_RxDMAEnable(USART2); }

INLINE void USARTx_RxDMADisable(USART_t* usart) { usart->CTLR3 &= ~B6; }
INLINE void USART1_RxDMADisable(void) { USARTx_RxDMADisable(USART1); }
INLINE void USART2_RxDMADisable(void) { USARTx_RxDMADisable(USART2); }

// Enable/Disable tramsmit DMA (default disabled)
INLINE void USARTx_TxDMAEnable(USART_t* usart) { usart->CTLR3 |= B7; }
INLINE void USART1_TxDMAEnable(void) { USARTx_TxDMAEnable(USART1); }
INLINE void USART2_TxDMAEnable(void) { USARTx_TxDMAEnable(USART2); }

INLINE void USARTx_TxDMADisable(USART_t* usart) { usart->CTLR3 &= ~B7; }
INLINE void USART1_TxDMADisable(void) { USARTx_TxDMADisable(USART1); }
INLINE void USART2_TxDMADisable(void) { USARTx_TxDMADisable(USART2); }

// Enable/Disable RTS flow control (default disabled)
INLINE void USARTx_RTSEnable(USART_t* usart) { usart->CTLR3 |= B8; }
INLINE void USART1_RTSEnable(void) { USARTx_RTSEnable(USART1); }
INLINE void USART2_RTSEnable(void) { USARTx_RTSEnable(USART2); }

INLINE void USARTx_RTSDisable(USART_t* usart) { usart->CTLR3 &= ~B8; }
INLINE void USART1_RTSDisable(void) { USARTx_RTSDisable(USART1); }
INLINE void USART2_RTSDisable(void) { USARTx_RTSDisable(USART2); }

// Enable/Disable CTS flow control (default disabled)
INLINE void USARTx_CTSEnable(USART_t* usart) { usart->CTLR3 |= B9; }
INLINE void USART1_CTSEnable(void) { USARTx_CTSEnable(USART1); }
INLINE void USART2_CTSEnable(void) { USARTx_CTSEnable(USART2); }

INLINE void USARTx_CTSDisable(USART_t* usart) { usart->CTLR3 &= ~B9; }
INLINE void USART1_CTSDisable(void) { USARTx_CTSDisable(USART1); }
INLINE void USART2_CTSDisable(void) { USARTx_CTSDisable(USART2); }

// Set prescaler value (default 0)
// - In IrDA Low-power mode, source clock is divided by this value with a value of 0 indicating retention.
// - In normal IrDA mode, this can only be set to 1.
// - In smartcard mode, source clock is divided by twice this value to clock
//     the smart card, with a value of 0 indicating retention
INLINE void USARTx_Presc(USART_t* usart, int presc) { usart->GPR = (usart->GPR & ~0xff) | presc; }
INLINE void USART1_Presc(int presc) { USARTx_Presc(USART1, presc); }
INLINE void USART2_Presc(int presc) { USARTx_Presc(USART2, presc); }

// Get prescaler value
INLINE int USARTx_GetPresc(USART_t* usart) { return usart->GPR & 0xff; }
INLINE int USART1_GetPresc(void) { return USARTx_GetPresc(USART1); }
INLINE int USART2_GetPresc(void) { return USARTx_GetPresc(USART2); }

/* ... not supported
// Set guard time value in terms of number of baud clocks, used in smartcard mode (default 0)
INLINE void USARTx_GuardTime(USART_t* usart, int guardtime) { usart->GPR = (usart->GPR & ~(0xff << 8)) | (guardtime << 8); }
INLINE void USART1_GuardTime(int guardtime) { USARTx_GuardTime(USART1, guardtime); }
INLINE void USART2_GuardTime(int guardtime) { USARTx_GuardTime(USART2, guardtime); }

// Get guard time value in terms of number of baud clocks
INLINE int USARTx_GetGuardTime(USART_t* usart) { return (usart->GPR >> 8) & 0xff; }
INLINE int USART1_GetGuardTime(void) { return USARTx_GetGuardTime(USART1); }
INLINE int USART2_GetGuardTime(void) { return USARTx_GetGuardTime(USART2); }
*/

// === Interrupt

// Enable/Disable IDLE interrupt (default disabled)
INLINE void USARTx_IdleIntEnable(USART_t* usart) { usart->CTLR1 |= B4; }
INLINE void USART1_IdleIntEnable(void) { USARTx_IdleIntEnable(USART1); }
INLINE void USART2_IdleIntEnable(void) { USARTx_IdleIntEnable(USART2); }

INLINE void USARTx_IdleIntDisable(USART_t* usart) { usart->CTLR1 &= ~B4; }
INLINE void USART1_IdleIntDisable(void) { USARTx_IdleIntDisable(USART1); }
INLINE void USART2_IdleIntDisable(void) { USARTx_IdleIntDisable(USART2); }

// Enable/Disable interrupt on "received data is ready" (default disabled)
INLINE void USARTx_RxReadyIntEnable(USART_t* usart) { usart->CTLR1 |= B5; }
INLINE void USART1_RxReadyIntEnable(void) { USARTx_RxReadyIntEnable(USART1); }
INLINE void USART2_RxReadyIntEnable(void) { USARTx_RxReadyIntEnable(USART2); }

INLINE void USARTx_RxReadyIntDisable(USART_t* usart) { usart->CTLR1 &= ~B5; }
INLINE void USART1_RxReadyIntDisable(void) { USARTx_RxReadyIntDisable(USART1); }
INLINE void USART2_RxReadyIntDisable(void) { USARTx_RxReadyIntDisable(USART2); }

// Enable/Disable interrupt on "sending is completed" (default disabled)
INLINE void USARTx_TxSentIntEnable(USART_t* usart) { usart->CTLR1 |= B6; }
INLINE void USART1_TxSentIntEnable(void) { USARTx_TxSentIntEnable(USART1); }
INLINE void USART2_TxSentIntEnable(void) { USARTx_TxSentIntEnable(USART2); }

INLINE void USARTx_TxSentIntDisable(USART_t* usart) { usart->CTLR1 &= ~B6; }
INLINE void USART1_TxSentIntDisable(void) { USARTx_TxSentIntDisable(USART1); }
INLINE void USART2_TxSentIntDisable(void) { USARTx_TxSentIntDisable(USART2); }

// Enable/Disable interrupt on "sending buffer is empty" (default disabled)
INLINE void USARTx_TxEmptyIntEnable(USART_t* usart) { usart->CTLR1 |= B7; }
INLINE void USART1_TxEmptyIntEnable(void) { USARTx_TxEmptyIntEnable(USART1); }
INLINE void USART2_TxEmptyIntEnable(void) { USARTx_TxEmptyIntEnable(USART2); }

INLINE void USARTx_TxEmptyIntDisable(USART_t* usart) { usart->CTLR1 &= ~B7; }
INLINE void USART1_TxEmptyIntDisable(void) { USARTx_TxEmptyIntDisable(USART1); }
INLINE void USART2_TxEmptyIntDisable(void) { USARTx_TxEmptyIntDisable(USART2); }

// Enable/Disable interrupt on parity error receive (default disabled)
INLINE void USARTx_ParityErrorIntEnable(USART_t* usart) { usart->CTLR1 |= B8; }
INLINE void USART1_ParityErrorIntEnable(void) { USARTx_ParityErrorIntEnable(USART1); }
INLINE void USART2_ParityErrorIntEnable(void) { USARTx_ParityErrorIntEnable(USART2); }

INLINE void USARTx_ParityErrorIntDisable(USART_t* usart) { usart->CTLR1 &= ~B8; }
INLINE void USART1_ParityErrorIntDisable(void) { USARTx_ParityErrorIntDisable(USART1); }
INLINE void USART2_ParityErrorIntDisable(void) { USARTx_ParityErrorIntDisable(USART2); }

// Enable/Disable LIN Break detection interrupt (default disabled)
INLINE void USARTx_LinBreakIntEnable(USART_t* usart) { usart->CTLR2 |= B6; }
INLINE void USART1_LinBreakIntEnable(void) { USARTx_LinBreakIntEnable(USART1); }
INLINE void USART2_LinBreakIntEnable(void) { USARTx_LinBreakIntEnable(USART2); }

INLINE void USARTx_LinBreakIntDisable(USART_t* usart) { usart->CTLR2 &= ~B6; }
INLINE void USART1_LinBreakIntDisable(void) { USARTx_LinBreakIntDisable(USART1); }
INLINE void USART2_LinBreakIntDisable(void) { USARTx_LinBreakIntDisable(USART2); }

// Enable/Disable error interrupt (default disabled)
INLINE void USARTx_ErrIntEnable(USART_t* usart) { usart->CTLR3 |= B0; }
INLINE void USART1_ErrIntEnable(void) { USARTx_ErrIntEnable(USART1); }
INLINE void USART2_ErrIntEnable(void) { USARTx_ErrIntEnable(USART2); }

INLINE void USARTx_ErrIntDisable(USART_t* usart) { usart->CTLR3 &= ~B0; }
INLINE void USART1_ErrIntDisable(void) { USARTx_ErrIntDisable(USART1); }
INLINE void USART2_ErrIntDisable(void) { USARTx_ErrIntDisable(USART2); }

// Enable/Disable CTS interrupt (default disabled)
INLINE void USARTx_CTSIntEnable(USART_t* usart) { usart->CTLR3 |= B10; }
INLINE void USART1_CTSIntEnable(void) { USARTx_CTSIntEnable(USART1); }
INLINE void USART2_CTSIntEnable(void) { USARTx_CTSIntEnable(USART2); }

INLINE void USARTx_CTSIntDisable(USART_t* usart) { usart->CTLR3 &= ~B10; }
INLINE void USART1_CTSIntDisable(void) { USARTx_CTSIntDisable(USART1); }
INLINE void USART2_CTSIntDisable(void) { USARTx_CTSIntDisable(USART2); }

// === Simple transfer in poll direct mode

// send data character (8 or 9 bits; send buffer must be empty)
INLINE void USARTx_TxWrite(USART_t* usart, int ch) { usart->DATAR = ch; }
INLINE void USART1_TxWrite(int ch) { USARTx_TxWrite(USART1, ch); }
INLINE void USART2_TxWrite(int ch) { USARTx_TxWrite(USART2, ch); }

// receve data character (8 or 9 bits; received character must be ready)
INLINE int USARTx_RxRead(USART_t* usart) { return usart->DATAR & 0x1ff; }
INLINE int USART1_RxRead(void) { return USARTx_RxRead(USART1); }
INLINE int USART2_RxRead(void) { return USARTx_RxRead(USART2); }

// send data character in poll mode with wait (8 or 9 bits)
void USARTx_SendChar(USART_t* usart, int ch);
INLINE void USART1_SendChar(int ch) { USARTx_SendChar(USART1, ch); }
INLINE void USART2_SendChar(int ch) { USARTx_SendChar(USART2, ch); }

// receive data character in poll mode with wait (8 or 9 bits)
int USARTx_RecvChar(USART_t* usart);
INLINE int USART1_RecvChar(void) { return USARTx_RecvChar(USART1); }
INLINE int USART2_RecvChar(void) { return USARTx_RecvChar(USART2); }

// send 8-bit data buffer in poll mode
void USARTx_SendBuf(USART_t* usart, const u8* buf, int len);
INLINE void USART1_SendBuf(const u8* buf, int len) { USARTx_SendBuf(USART1, buf, len); }
INLINE void USART2_SendBuf(const u8* buf, int len) { USARTx_SendBuf(USART2, buf, len); }

// receive 8-bit data buffer in poll mode, with time-out in [us] 0..89sec (returns number of bytes)
#define USART_LONGTIMEOUT 20000000	// long time-out
int USARTx_RecvBuf(USART_t* usart, u8* buf, int len, u32 timeout);
INLINE int USART1_RecvBuf(u8* buf, int len, u32 timeout) { return USARTx_RecvBuf(USART1, buf, len, timeout); }
INLINE int USART2_RecvBuf(u8* buf, int len, u32 timeout) { return USARTx_RecvBuf(USART2, buf, len, timeout); }

// send ASCIIZ text in poll mode
void USARTx_SendText(USART_t* usart, const char* buf);
INLINE void USART1_SendText(const char* buf) { USARTx_SendText(USART1, buf); }
INLINE void USART2_SendText(const char* buf) { USARTx_SendText(USART2, buf); }

// initialize simple transfer in polled direct mode (data length 8 bits)
//  baud ... baudrate in Bauds
//  wordlen ... word length USART_WORDLEN_*
//  parity ... parity USART_PARITY_*
//  stop ... stop bits USART_STOP_*
// Also set GPIOs as follows:
//  Remap USART1 (default 0) with GPIO_Remap_USART1(map):
//	0 ... PD5:TX, PD6:RX, PD3:CTS, PC2:RTS
//	1 ... PD6:TX, PD5:RX, PC6:CTS, PC7:RTS
//	2 ... PD0:TX, PD1:RX, PC3:CTS, PC2:RTS
//	3 ... PC0:TX, PC1:RX, PC6:CTS, PC7:RTS
//	4 ... PD1:TX, PB3:RX, PD7:CTS, PA5:RTS
//	5 ... PB3:TX, PD1:RX, PD7:CTS, PA5:RTS
//	6 ... PC5:TX, PC6:RX, PC7:CTS, PB4:RTS
//	7 ... PB5:TX, PB6:RX, PC7:CTS, PB4:RTS
//	8 ... PA0:TX, PA1:RX, PD2:CTS, PD3:RTS
//	9 ... PA0:TX, PC4:RX, PD5:CTS, PD4:RTS
//  Remap USART2 (default 0) with GPIO_Remap_USART2(map):
//	0 ... PA7:TX, PB3:RX, PA4:CTS, PA5:RTS
//	1 ... PA4:TX, PA5:RX, PA7:CTS, PB3:RTS
//	2 ... PA2:TX, PA3:RX, PA0:CTS, PA1:RTS
//	3 ... PD2:TX, PD3:RX, PA0:CTS, PA1:RTS
//	4 ... PB0:TX, PB1:RX, PB6:CTS, PA1:RTS
//	5 ... PC4:TX, PD1:RX, PA4:CTS, PA11:RTS
//	6 ... PA6:TX, PA5:RX, PA7:CTS, PB3:RTS
//  Set mode GPIO_Mode(gpio, mode) of TX to GPIO_MODE_AF
//  Set mode GPIO_Mode(gpio, mode) of RX to GPIO_MODE_IN
void USARTx_Init(USART_t* usart, int baud, int wordlen, int parity, int stop);
INLINE void USART1_Init(int baud, int wordlen, int parity, int stop) { USARTx_Init(USART1, baud, wordlen, parity, stop); }
INLINE void USART2_Init(int baud, int wordlen, int parity, int stop) { USARTx_Init(USART2, baud, wordlen, parity, stop); }

#ifdef __cplusplus
}
#endif

#endif // _SDK_USART_H

#endif // USE_USART
