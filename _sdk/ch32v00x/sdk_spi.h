
// ****************************************************************************
//
//                                  SPI
//
// ****************************************************************************

#if USE_SPI		// 1=use SPI peripheral

#ifndef _SDK_SPI_H
#define _SDK_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

// SPI registers
typedef struct {
	io16	CTLR1;		// 0x00: control register 1
	io16	res1;		// 0x02: ... reserved
	io16	CTLR2;		// 0x04: control register 2
	io16	res2;		// 0x06: ... reserved
	io16	STATR;		// 0x08: status register
	io16	res3;		// 0x0A: ... reserved
	io16	DATAR;		// 0x0C: data register
	io16	res4;		// 0x0E: ... reserved
	io16	CRCR;		// 0x10: polynomial register
	io16	res5;		// 0x12: ... reserved
	io16	RCRCR;		// 0x14: receive CRC register
	io16	res6;		// 0x16: ... reserved
	io16	TCRCR;		// 0x18: transmit CRC register
	io16	res7;		// 0x1A: ... reserved
	io32	res8[2];	// 0x1C: ... reserved
	io16	HSCR;		// 0x24: high-speed control register
	io16	res9;		// 0x26: ... reserved
} SPI_t;
STATIC_ASSERT(sizeof(SPI_t) == 0x28, "Incorrect SPI_t!");
#define SPI1	((SPI_t*)SPI1_BASE)	// 0x40013000

// Baud rate setting divider
#define SPI_BAUD_DIV2		0	// Fhclk/2
#define SPI_BAUD_DIV4		1	// Fhclk/4
#define SPI_BAUD_DIV8		2	// Fhclk/8
#define SPI_BAUD_DIV16		3	// Fhclk/16
#define SPI_BAUD_DIV32		4	// Fhclk/32
#define SPI_BAUD_DIV64		5	// Fhclk/64
#define SPI_BAUD_DIV128		6	// Fhclk/128
#define SPI_BAUD_DIV256		7	// Fhclk/256

// === Setup

// Set clock phase to data sampling on First/Second edge (default first edge; register CTLR1.CPHA)
INLINE void SPIx_ClockPhaseFirst(SPI_t* spi) { spi->CTLR1 &= ~B0; }
INLINE void SPI1_ClockPhaseFirst(void) { SPIx_ClockPhaseFirst(SPI1); }

INLINE void SPIx_ClockPhaseSecond(SPI_t* spi) { spi->CTLR1 |= B0; }
INLINE void SPI1_ClockPhaseSecond(void) { SPIx_ClockPhaseSecond(SPI1); }

// Select clock polarity - held Low or High in idle state (default low; register CTLR1.CPOL)
// Mode 0 or 1: set SCK to low; mode 2 and 3: set SCK to high
INLINE void SPIx_ClockPolLow(SPI_t* spi) { spi->CTLR1 &= ~B1; }
INLINE void SPI1_ClockPolLow(void) { SPIx_ClockPolLow(SPI1); }

INLINE void SPIx_ClockPolHigh(SPI_t* spi) { spi->CTLR1 |= B1; }
INLINE void SPI1_ClockPolHigh(void) { SPIx_ClockPolHigh(SPI1); }

// Select master or slave mode (default slave; register CTLR1.MSTR)
INLINE void SPIx_Master(SPI_t* spi) { spi->CTLR1 |= B2; }
INLINE void SPI1_Master(void) { SPIx_Master(SPI1); }

INLINE void SPIx_Slave(SPI_t* spi) { spi->CTLR1 &= ~B2; }
INLINE void SPI1_Slave(void) { SPIx_Slave(SPI1); }

// Set Baut rate setting divider SPI_BAUD_DIV* (default 2; register CTLR1.BR[2:0])
// This bit only applies when the HSRXEN bit is 0 (SPIx_HSDisable()).
// When the HSRXEN bit is 1 (SPIx_HSEnable()), the SCK frequency is FHCLK/(baud+2).
INLINE void SPIx_Baud(SPI_t* spi, int baud) { spi->CTLR1 = (spi->CTLR1 & ~(7 << 3)) | (baud << 3); }
INLINE void SPI1_Baud(int baud) { SPIx_Baud(SPI1, baud); }

// Enable/Disable SPI (default disable; register CTLR1.SPE)
INLINE void SPIx_Enable(SPI_t* spi) { spi->CTLR1 |= B6; }
INLINE void SPI1_Enable(void) { SPIx_Enable(SPI1); }

INLINE void SPIx_Disable(SPI_t* spi) { spi->CTLR1 &= ~B6; }
INLINE void SPI1_Disable(void) { SPIx_Disable(SPI1); }

// Select first transmitted bit LSB or MSB (default MSB; register CTLR1.LSBFIRST)
// LSB is only supported by SPI as host.
// This bit cannot be modified during communication.
INLINE void SPIx_LSB(SPI_t* spi) { spi->CTLR1 |= B7; }
INLINE void SPI1_LSB(void) { SPIx_LSB(SPI1); }

INLINE void SPIx_MSB(SPI_t* spi) { spi->CTLR1 &= ~B7; }
INLINE void SPI1_MSB(void) { SPIx_MSB(SPI1); }

// Set level of NSS pin to Low or High (default low; register CTLR1.SSI)
// Bit determines the level of the NSS pin, in case of software control SPIx_NSSSw().
INLINE void SPIx_NSSLow(SPI_t* spi) { spi->CTLR1 &= ~B8; }
INLINE void SPI1_NSSLow(void) { SPIx_NSSLow(SPI1); }

INLINE void SPIx_NSSHigh(SPI_t* spi) { spi->CTLR1 |= B8; }
INLINE void SPI1_NSSHigh(void) { SPIx_NSSHigh(SPI1); }

// Select whether NSS pin is controlled by software or hardware (default hardware; register CTLR1.SSM)
INLINE void SPIx_NSSSw(SPI_t* spi) { spi->CTLR1 |= B9; }
INLINE void SPI1_NSSSw(void) { SPIx_NSSSw(SPI1); }

INLINE void SPIx_NSSHw(SPI_t* spi) { spi->CTLR1 &= ~B9; }
INLINE void SPI1_NSSHw(void) { SPIx_NSSHw(SPI1); }

// Set receive-only mode in 2-wire mode (simplex mode), or full-duplex mode (default full-duplex; register CTLR1.RXONLY)
INLINE void SPIx_RxOnly(SPI_t* spi) { spi->CTLR1 |= B10; }
INLINE void SPI1_RxOnly(void) { SPIx_RxOnly(SPI1); }

INLINE void SPIx_Duplex(SPI_t* spi) { spi->CTLR1 &= ~B10; }
INLINE void SPI1_Duplex(void) { SPIx_Duplex(SPI1); }

// Select data format to 16-bit or 8-bit (default 8-bit; register CTLR1.DFF)
INLINE void SPIx_Data16(SPI_t* spi) { spi->CTLR1 |= B11; }
INLINE void SPI1_Data16(void) { SPIx_Data16(SPI1); }

INLINE void SPIx_Data8(SPI_t* spi) { spi->CTLR1 &= ~B11; }
INLINE void SPI1_Data8(void) { SPIx_Data8(SPI1); }

// Enable/Disable sending CRC register after next data transfer (default disabled; register CTLR1.CRCNEXT)
// - Should be enabled immediately after the last data is written to the data register.
INLINE void SPIx_CRCNextEnable(SPI_t* spi) { spi->CTLR1 |= B12; }
INLINE void SPI1_CRCNextEnable(void) { SPIx_CRCNextEnable(SPI1); }

INLINE void SPIx_CRCNextDisable(SPI_t* spi) { spi->CTLR1 &= ~B12; }
INLINE void SPI1_CRCNextDisable(void) { SPIx_CRCNextDisable(SPI1); }

// Enable/Disable hardware CRC calculation (default disabled; register CTLR1.CRCEN)
// Can only be written when SPE is 0 (SPIx_Disable()) and can only be used in full-duplex mode (SPIx_Duplex()).
INLINE void SPIx_CRCEnable(SPI_t* spi) { spi->CTLR1 |= B13; }
INLINE void SPI1_CRCEnable(void) { SPIx_CRCEnable(SPI1); }

INLINE void SPIx_CRCDisable(SPI_t* spi) { spi->CTLR1 &= ~B13; }
INLINE void SPI1_CRCDisable(void) { SPIx_CRCDisable(SPI1); }

// Select transmit-only or receive-only in 1-line bidirectional mode (default receive; register CTLR1.BIDIOE)
INLINE void SPIx_TxBidi(SPI_t* spi) { spi->CTLR1 |= B14; }
INLINE void SPI1_TxBidi(void) { SPIx_TxBidi(SPI1); }

INLINE void SPIx_RxBidi(SPI_t* spi) { spi->CTLR1 &= ~B14; }
INLINE void SPI1_RxBidi(void) { SPIx_RxBidi(SPI1); }

// Select 1-line or 2-line bidirectional mode (defalt 2-line; register CTLR1.BIDIMODE)
INLINE void SPIx_Bidi1(SPI_t* spi) { spi->CTLR1 |= B15; }
INLINE void SPI1_Bidi1(void) { SPIx_Bidi1(SPI1); }

INLINE void SPIx_Bidi2(SPI_t* spi) { spi->CTLR1 &= ~B15; }
INLINE void SPI1_Bidi2(void) { SPIx_Bidi2(SPI1); }

// Enable/Disable Rx buffer DMA (default disabled; register CTLR2.RXDMAEN)
INLINE void SPIx_RxDMAEnable(SPI_t* spi) { spi->CTLR2 |= B0; }
INLINE void SPI1_RxDMAEnable(void) { SPIx_RxDMAEnable(SPI1); }

INLINE void SPIx_RxDMADisable(SPI_t* spi) { spi->CTLR2 &= ~B0; }
INLINE void SPI1_RxDMADisable(void) { SPIx_RxDMADisable(SPI1); }

// Enable/Disable Tx buffer DMA (default disabled; register CTLR2.TXDMAEN)
INLINE void SPIx_TxDMAEnable(SPI_t* spi) { spi->CTLR2 |= B1; }
INLINE void SPI1_TxDMAEnable(void) { SPIx_TxDMAEnable(SPI1); }

INLINE void SPIx_TxDMADisable(SPI_t* spi) { spi->CTLR2 &= ~B1; }
INLINE void SPI1_TxDMADisable(void) { SPIx_TxDMADisable(SPI1); }

// Enable/Disable SS output (default disabled; register CTLR2.SSOE)
INLINE void SPIx_SSEnable(SPI_t* spi) { spi->CTLR2 |= B2; }
INLINE void SPI1_SSEnable(void) { SPIx_SSEnable(SPI1); }

INLINE void SPIx_SSDisable(SPI_t* spi) { spi->CTLR2 &= ~B2; }
INLINE void SPI1_SSDisable(void) { SPIx_SSDisable(SPI1); }

// === Interrupt

// Enable/Disable error interrupt (default disabled; register CTLR2.ERRIE)
INLINE void SPIx_ErrIntEnable(SPI_t* spi) { spi->CTLR2 |= B5; }
INLINE void SPI1_ErrIntEnable(void) { SPIx_ErrIntEnable(SPI1); }

INLINE void SPIx_ErrIntDisable(SPI_t* spi) { spi->CTLR2 &= ~B5; }
INLINE void SPI1_ErrIntDisable(void) { SPIx_ErrIntDisable(SPI1); }

// Enable/Disable Rx buffer not empty interrupt (default disabled; register CTLR2.RXNEIE)
INLINE void SPIx_RxReadyIntEnable(SPI_t* spi) { spi->CTLR2 |= B6; }
INLINE void SPI1_RxReadyIntEnable(void) { SPIx_RxReadyIntEnable(SPI1); }

INLINE void SPIx_RxReadyIntDisable(SPI_t* spi) { spi->CTLR2 &= ~B6; }
INLINE void SPI1_RxReadyIntDisable(void) { SPIx_RxReadyIntDisable(SPI1); }

// Enable/Disable Tx buffer empty interrupt (default disabled; register CTLR2.TXEIE)
INLINE void SPIx_TxEmptyIntEnable(SPI_t* spi) { spi->CTLR2 |= B7; }
INLINE void SPI1_TxEmptyIntEnable(void) { SPIx_TxEmptyIntEnable(SPI1); }

INLINE void SPIx_TxEmptyIntDisable(SPI_t* spi) { spi->CTLR2 &= ~B7; }
INLINE void SPI1_TxEmptyIntDisable(void) { SPIx_TxEmptyIntDisable(SPI1); }

// === Status

// Check if receive buffer not empty - received data are ready (register STATR.RXNE)
INLINE Bool SPIx_RxReady(SPI_t* spi) { return (spi->STATR & B0) != 0; }
INLINE Bool SPI1_RxReady(void) { return SPIx_RxReady(SPI1); }

// Check if transmit buffer is empty (register STATR.TXE)
INLINE Bool SPIx_TxEmpty(SPI_t* spi) { return (spi->STATR & B1) != 0; }
INLINE Bool SPI1_TxEmpty(void) { return SPIx_TxEmpty(SPI1); }

// Check if channel right has to be transmitted or has been received; or channel left otherwise (register STATR.CHSID)
//INLINE Bool SPIx_ChRight(SPI_t* spi) { return (spi->STATR & B2) != 0; }
//INLINE Bool SPI1_ChRight(void) { return SPIx_ChRight(SPI1); }

// Check/Clear underrun (register STATR.UDR)
//INLINE Bool SPIx_Under(SPI_t* spi) { return (spi->STATR & B3) != 0; }
//INLINE Bool SPI1_Under(void) { return SPIx_Under(SPI1); }

//INLINE void SPIx_UnderClr(SPI_t* spi) { spi->STATR &= ~B3; }
//INLINE void SPI1_UnderClr(void) { SPIx_UnderClr(SPI1); }

// Check/Clear CRC error (register STATR.CRCERR)
INLINE Bool SPIx_CRCErr(SPI_t* spi) { return (spi->STATR & B4) != 0; }
INLINE Bool SPI1_CRCErr(void) { return SPIx_CRCErr(SPI1); }

INLINE void SPIx_CRCErrClr(SPI_t* spi) { spi->STATR &= ~B4; }
INLINE void SPI1_CRCErrClr(void) { SPIx_CRCErrClr(SPI1); }

// Check/Clear mode fault error (register STATR.MODF)
INLINE Bool SPIx_ModeErr(SPI_t* spi) { return (spi->STATR & B5) != 0; }
INLINE Bool SPI1_ModeErr(void) { return SPIx_ModeErr(SPI1); }

INLINE void SPIx_ModeErrClr(SPI_t* spi) { spi->STATR &= ~B5; }
INLINE void SPI1_ModeErrClr(void) { SPIx_ModeErrClr(SPI1); }

// Check/Clear overrun (register STATR.OVR)
INLINE Bool SPIx_Over(SPI_t* spi) { return (spi->STATR & B6) != 0; }
INLINE Bool SPI1_Over(void) { return SPIx_Over(SPI1); }

INLINE void SPIx_OverClr(SPI_t* spi) { spi->STATR &= ~B6; }
INLINE void SPI1_OverClr(void) { SPIx_OverClr(SPI1); }

// Check busy flag - SPI is communicating, or the send buffer is not empty (register STATR.BSY)
INLINE Bool SPIx_Busy(SPI_t* spi) { return (spi->STATR & B7) != 0; }
INLINE Bool SPI1_Busy(void) { return SPIx_Busy(SPI1); }

// === Data

// Send data
INLINE void SPIx_Write(SPI_t* spi, u16 data) { spi->DATAR = data; }
INLINE void SPI1_Write(u16 data) { SPIx_Write(SPI1, data); }

// Send data with wait
void SPIx_SendWait(SPI_t* spi, u16 data);
INLINE void SPI1_SendWait(u16 data) { SPIx_SendWait(SPI1, data); }

// Receive data
INLINE u16 SPIx_Read(SPI_t* spi) { return (u16)spi->DATAR; }
INLINE u16 SPI1_Read(void) { return SPIx_Read(SPI1); }

// Receive data with wait
u16 SPIx_RecvWait(SPI_t* spi);
INLINE u16 SPI1_RecvWait(void) { return SPIx_RecvWait(SPI1); }

// Set/Get CRC polynomial register (register CRCR)
INLINE void SPIx_Crc(SPI_t* spi, u16 crc) { spi->CRCR = crc; }
INLINE void SPI1_Crc(u16 crc) { SPIx_Crc(SPI1, crc); }

INLINE u16 SPIx_GetCrc(SPI_t* spi) { return (u16)spi->CRCR; }
INLINE u16 SPI1_GetCrc(void) { return SPIx_GetCrc(SPI1); }

// Get receive CRC register (register RCRCR)
INLINE u16 SPIx_RxCrc(SPI_t* spi) { return (u16)spi->RCRCR; }
INLINE u16 SPI1_RxCrc(void) { return SPIx_RxCrc(SPI1); }

// Get transmit CRC register (register TCRCR)
INLINE u16 SPIx_TxCrc(SPI_t* spi) { return (u16)spi->TCRCR; }
INLINE u16 SPI1_TxCrc(void) { return SPIx_TxCrc(SPI1); }

// Enable/Disable high-speed mode, when clock is divided by 2 (default disabled; register HSCR.HSRXEN)
// When the HSRXEN bit is 1 (SPIx_HSEnable()), the SCK frequency is FHCLK/(baud+2).
INLINE void SPIx_HSEnable(SPI_t* spi) { spi->HSCR = B0; }
INLINE void SPI1_HSEnable(void) { SPIx_HSEnable(SPI1); }

INLINE void SPIx_HSDisable(SPI_t* spi) { spi->HSCR = 0; }
INLINE void SPI1_HSDisable(void) { SPIx_HSDisable(SPI1); }

#ifdef __cplusplus
}
#endif

#endif // _SDK_SPI_H

#endif // USE_SPI
