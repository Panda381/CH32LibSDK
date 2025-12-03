
// ****************************************************************************
//
//                               Display
//
// ****************************************************************************

#include "def.h"

#if USE_DISP_ASM		// 1=use ASM in Disp module

#define	PERIPH_BASE		0x40000000	// Peripheral base address in the alias region
#define APB2PERIPH_BASE		(PERIPH_BASE + 0x10000)		// 0x40010000
#define GPIOC_BASE		(APB2PERIPH_BASE + 0x1000)	// PC port 0x40011000

#define GPIO_CFGLR_OFF	0x00	// configuration register low
#define GPIO_BSHR_OFF	0x10	// bit set/reset output data register (low 16 bits: set bit, high 16 bits: clear bit)
#define GPIO_BCR_OFF	0x14	// bit clear output data register (low 16 bits: clear bit)

#define PORTC_INX	2
#define PC0		(PORTC_INX*8)
#define PC1		(PC0+1)
#define PC2		(PC0+2)

#define DISP_SDA_PIN	1		// SDA pin index (PC1)
#define DISP_SCL_PIN	2		// SCL pin index (PC2)

#define GPIO_MODE_OUT	1		// push-pull output mode

// communication delay
.macro DISP_CLK_WAIT
	j	clk_wait_\@
clk_wait_\@:
.endm

	.section	.text

// ----------------------------------------------------------------------------
// start I2C communication (on start, SDA and SCL must be high)
// ----------------------------------------------------------------------------
// void DispI2C_Start(void)

// start condition: SDA goes low while SCL is high

.global DispI2C_Start
DispI2C_Start:

	// get GPIOC base
	li	a5,GPIOC_BASE

	// set SDA LOW
	li	a4,1<<DISP_SDA_PIN	// A4 <- SDA pin
	sw	a4,GPIO_BCR_OFF(a5)	// clear SDA bit
	DISP_CLK_WAIT			// short delay

	// set SCL LOW
	li	a4,1<<DISP_SCL_PIN	// A4 <- SCL pin
	sw	a4,GPIO_BCR_OFF(a5)	// clear SCL bit
	ret

// ----------------------------------------------------------------------------
// display ON
// ----------------------------------------------------------------------------
// void DispOn(void)

.global DispOn
DispOn:
	li	a0,0xAF			// display ON in normal mode
	j	DispCmd			// send command

// ----------------------------------------------------------------------------
// display OFF
// ----------------------------------------------------------------------------
// void DispOff(void)

.global DispOff
DispOff:
	li	a0,0xAE			// display OFF (go to sleep mode)

// ---- continue to DispCmd

// ----------------------------------------------------------------------------
// send command to the display
// ----------------------------------------------------------------------------
// void DispCmd(u8 cmd)

.global DispCmd
DispCmd:

	// save registers
	addi	sp,sp,-8
	sw	ra,0(sp)
	sw	a0,4(sp)		// save command

	// send command
	call	DispI2C_Start		// start I2C communication
	li	a0,DISP_I2C_ADDR << 1	// I2C address * 2, bit 0 is 0 (= write)
	call	DispI2C_Write		// send I2C address
	li	a0,0			// A0 <- command flag
	call	DispI2C_Write		// send control byte for command
	lw	a0,4(sp)		// A0 <- command
	call	DispI2C_Write		// send command

	// restore registers
	lw	ra,0(sp)
	add	sp,sp,8

// ---- continue to DispI2C_Stop

// ----------------------------------------------------------------------------
// stop I2C communication
// ----------------------------------------------------------------------------
// void DispI2C_Stop(void)

// stop condition: SDA goes high while SCL is high

.global DispI2C_Stop
DispI2C_Stop:

	// get GPIOC base
	li	a5,GPIOC_BASE

	// set SCL HIGH
	li	a4,1<<DISP_SCL_PIN	// A4 <- SCL pin
	sw	a4,GPIO_BSHR_OFF(a5)	// set SCL bit
	DISP_CLK_WAIT			// short delay

	// set SDA HIGH
	li	a4,1<<DISP_SDA_PIN	// A4 <- SDA pin
	sw	a4,GPIO_BSHR_OFF(a5)	// set SDA bit
	ret

// ----------------------------------------------------------------------------
// Display select SSD1306 page 0..7, start transfer data
// ----------------------------------------------------------------------------
// void DispI2C_SelectPage(int page)

.global DispI2C_SelectPage
DispI2C_SelectPage:

	// save registers
	addi	sp,sp,-8
	sw	ra,0(sp)
	sw	a0,4(sp)		// save page

	// select page
	call	DispI2C_Start		// start I2C communication
	li	a0,DISP_I2C_ADDR << 1	// I2C address * 2, bit 0 is 0 (= write)
	call	DispI2C_Write		// send I2C address
	li	a0,0			// A0 <- command flag
	call	DispI2C_Write		// send control byte for command
	lw	a0,4(sp)		// A0 <- page
	andi	a0,a0,7			// mask page index
	ori	a0,a0,0xb0
	call	DispI2C_Write		// send page command
	li	a0,0
	call	DispI2C_Write		// set lower nibble of column start address to 0
	li	a0,16
	call	DispI2C_Write		// set higher nibble of column start address to 0
	call	DispI2C_Stop		// stop transfer

	// start transfer data
	call	DispI2C_Start		// start I2C communication
	li	a0,DISP_I2C_ADDR << 1	// I2C address * 2, bit 0 is 0 (= write)
	call	DispI2C_Write		// send I2C address
	li	a0,0x40			// control byte to start transfer data

	// restore registers
	lw	ra,0(sp)
	add	sp,sp,8

// ---- continue to DispI2C_Write

// ----------------------------------------------------------------------------
// write a byte over I2C
// ----------------------------------------------------------------------------
// void DispI2C_Write(u8 data)

.global DispI2C_Write
DispI2C_Write:

// ---- send 8 data bits

	// get GPIOC base
	li	a5,GPIOC_BASE		// A5 <- GPIOC base

	// send 8 bits of data A0
	li	a4,8			// A4 <- number of bits to send
	li	a3,1<<DISP_SCL_PIN	// A3 <- SCL pin

	// set SCL low, to prepare next data
2:	slli	a2,a0,24		// shift data left to check bit 7
	sw	a3,GPIO_BCR_OFF(a5)	// clear SCL bit

	// send SDA data bit
	li	a1,1<<DISP_SDA_PIN	// A1 <- SDA pin to set
	bltz	a2,3f			// skip if bit 7 was set
	slli	a1,a1,16		// A1 <- SDA pint to clear
3:	sw	a1,GPIO_BSHR_OFF(a5)	// set or clear SDA bit

	// short delay
	nop				// delay
	addi	a4,a4,-1		// loop counter
	slli	a0,a0,1			// A0 <- prepare next data bit

	// set SCL high to confirm valid data bit
	sw	a3,GPIO_BSHR_OFF(a5)	// set SCL bit

	// loop bits
	bnez	a4,2b			// next bit

// ---- handle ACK

	// set SDA high, to release open-drain SDA line
	li	a1,1<<DISP_SDA_PIN	// A1 <- SDA pin

	// set SDA to input, to simulate open-drain HIGH to read ACK
	lw	a4,GPIO_CFGLR_OFF(a5)	// T0 <- get configuration register LOW
	andi	a0,a4,~(0x0f << (DISP_SDA_PIN*4)) // clear mode bits
	ori	a0,a0,8 << (DISP_SDA_PIN*4) // input mode

	// set SCL low, to prepare next data, set SDA HIGH
	sw	a3,GPIO_BCR_OFF(a5)	// clear SCL bit
	sw	a1,GPIO_BSHR_OFF(a5)	// set SDA bit
	sw	a0,GPIO_CFGLR_OFF(a5)	// set new configuration register
	DISP_CLK_WAIT			// short delay

	// set SCL high to confirm valid ACK data bit
	sw	a3,GPIO_BSHR_OFF(a5)	// set SCL bit
	DISP_CLK_WAIT			// short delay

	// set SCL low, to end ACK bit
	sw	a3,GPIO_BCR_OFF(a5)	// clear SCL bit
	DISP_CLK_WAIT			// short delay

	// set SDA back to low state
	sw	a1,GPIO_BCR_OFF(a5)	// clear SDA bit

	// reconfigure SDA back to output mode 
	sw	a4,GPIO_CFGLR_OFF(a5)	// set new configuration register
	ret

// ----------------------------------------------------------------------------
// Display update - send frame buffer to the display
// ----------------------------------------------------------------------------
// void DispUpdate()

.global DispUpdate
DispUpdate:

	// save registers
	addi	sp,sp,-20
	sw	ra,0(sp)
	sw	s0,4(sp)
	sw	zero,8(sp)		// prepare page index 'y'

// Registers:
//  0: RA
//  4: S0
//  8: page index 'y'
//  12: counter 'x'
//  16: mask 'm'
//  S0: pointer to frame buffer 's'

	// prepare pointer to frame buffer -> S0
	addi	s0,gp,RAM_FRAMEBUF_OFF	// S0 <- pointer to frame buffer

	// select page
	lw	a0,8(sp)		// A0 <- current page 'y'
2:	call	DispI2C_SelectPage	// select page

	// prepare X counter
	li	a1,16			// A1 <- number of bytes per line
3:	sw	a1,12(sp)		// save counter 'x'

	// prepare mask
4:	li	a1,0x80			// mask, bit 7
40:	sw	a1,16(sp)		// save mask 'm'

	// prepare accumulator
5:	li	a0,0			// A0 <- accumulator 'b'
	li	a1,8			// A1 <- number of bits 'j'
	lw	a2,16(sp)		// A2 <- mask 'm'
	mv	a3,s0			// A3 <- source pointer 'src'

	// loop lines of the page
6:	srai	a0,a0,1			// A0 <- shift accumulator 'b' right
	lbu	a4,0(a3)		// A4 <- get byte from frame buffer
	and	a4,a4,a2		// A4 <- mask byte
	beqz	a4,7f			// skip if bit is 0
	ori	a0,a0,0x80		// add bit 7 to the accumulator
7:	addi	a3,a3,WIDTHBYTE		// shift source address
	addi	a1,a1,-1		// decrement bit counter 'j'
	bnez	a1,6b			// get next line

	// send data byte A0
	call	DispI2C_Write

	// shift mask
	lw	a1,16(sp)		// A1 <- mask 'm'
	srai	a1,a1,1			// A1 <- shift mask right 'm' >> 1
	bnez	a1,40b			// next bit of the mask

	// increase source pointer
	addi	s0,s0,1			// S0 <- increase source pointer 's'
	
	// loop X counter
	lw	a1,12(sp)		// A1 <- counter 'x' 
	addi	a1,a1,-1		// decrement counter 'x'
	bnez	a1,3b			// next X byte

	// stop transfer
	call	DispI2C_Stop
	
	// shift pointer to frame buffer
	addi	s0,s0,8*WIDTHBYTE - 16

	// increase page 'y'
	lw	a0,8(sp)		// A0 <- current page 'y'
	addi	a0,a0,1			// A0 <- increase page index 'y'
	sw	a0,8(sp)		// save new page index
	li	a2,8			// A2 <- max Y
	bne	a0,a2,2b		// next page

	// restore registers
	lw	s0,4(sp)
	lw	ra,0(sp)
	add	sp,sp,20
	ret

// ----------------------------------------------------------------------------
// Display initialize (port clock must be enabled)
// ----------------------------------------------------------------------------
// void DispInit(void)

.global DispInit
DispInit:

	// save registers
	addi	sp,sp,-8
	sw	ra,0(sp)

	// initialize pins to HIGH output
	call	DispI2C_Stop		// set SDA and SCL pins to HIGH
	li	a0,DISP_SDA_GPIO	// display gpio with SDA
	li	a1,GPIO_MODE_OUT	// output mode
	call	GPIO_Mode		// set SDA output mode
	li	a0,DISP_SCL_GPIO	// display gpio with SCL
	li	a1,GPIO_MODE_OUT	// output mode
	call	GPIO_Mode		// set SCL output mode

	// wait to stabilize power supply of OLED, minimum 5ms
	li	a0,10
	call	WaitMs

	// setup OLED configuration
	call	DispI2C_Start		// start I2C communication
	sw	zero,4(sp)		// reset byte index

	// send 1 byte
2:	lw	a1,4(sp)		// A1 <- byte index
	la	a2,DispI2C_InitData	// A2 <- pointer to DispI2C_InitData
	add	a2,a2,a1		// A2 <- pointer to data
	lbu	a0,0(a2)		// A0 <- read byte
	call	DispI2C_Write		// write data byte

	// next byte
	lw	a1,4(sp)		// A1 <- byte index
	addi	a1,a1,1			// A1 <- increase byte index
	sw	a1,4(sp)		// save new index
	li	a2,DISP_INITDATA_NUM	// A2 <- number of bytes
	bne	a1,a2,2b		// next byte

	// stop transfer
	call	DispI2C_Stop

	// restore registers
	lw	ra,0(sp)
	add	sp,sp,8

	// short delay to guarantee initialization
	li	a0,2
	j	WaitMs

#endif // USE_DISP_ASM
