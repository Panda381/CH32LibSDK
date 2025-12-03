
// ****************************************************************************
//
//                                 Keys
//
// ****************************************************************************

#include "def.h"

#if USE_KEY_ASM			// 1=use ASM in Key module

#define	PERIPH_BASE		0x40000000	// Peripheral base address in the alias region
#define APB2PERIPH_BASE		(PERIPH_BASE + 0x10000)		// 0x40010000
#define GPIOA_BASE		(APB2PERIPH_BASE + 0x0800)	// PA port 0x40010800
#define GPIOB_BASE		(APB2PERIPH_BASE + 0x0C00)	// PB port 0x40010C00
#define GPIOC_BASE		(APB2PERIPH_BASE + 0x1000)	// PC port 0x40011000
#define GPIOD_BASE		(APB2PERIPH_BASE + 0x1400)	// PD port 0x40011400

#define EXTI_BASE		(APB2PERIPH_BASE + 0x0400)	// EXTI external interrupt registers 0x40010400

#define GPIO_CFGLR_OFF	0x00	// configuration register low
#define GPIO_INDR_OFF	0x08	// input data register
#define GPIO_BSHR_OFF	0x10	// bit set/reset output data register (low 16 bits: set bit, high 16 bits: clear bit)
#define GPIO_BCR_OFF	0x14	// bit clear output data register (low 16 bits: clear bit)

#define EXTI_INTENR_OFF	0x00	// Interrupt enable register
#define EXTI_FTENR_OFF	0x0C	// Falling edge trigger enable register
#define EXTI_INTFR_OFF	0x14	// Interrupt flag register

#define IRQ_EXTI7	20		// External line 7..0 interrupts (default weak handler EXTI7_0_IRQHandler)
#define PFIC_BASE	0xE000E000	// Programmable Fast Interrupt Controller (PFIC)
#define PFIC_IENR_OFF	0x100		// Interrupt enable setting register

#define GPIO_MODE_IN_PU		0x48	// input with pull up (set output register to 1)

// input keys (Note: The pin numbers must be different in order to map EXTI)
#define PORTA_INX	0
#define PORTD_INX	3
#define PA0	(PORTA_INX*8)
#define PA1	(PA0+1)
#define PA2	(PA0+2)
#define PD0	(PORTD_INX*8)
#define PD4	(PD0+4)

#define KEY_A_GPIO	PA1	// gpio of key A
#define KEY_B_GPIO	PA2	// gpio of key B
#define KEY_C_GPIO	PD4	// gpio of key C (it is connected to SWIO PD1 pin)

#define GPIO_PORTINX(gpio) ((gpio)>>3)
#define GPIO_PIN(gpio) ((gpio)&0x07)

#define KEY_A_PORT	GPIO_PORTINX(KEY_A_GPIO)	// port of key A
#define KEY_A_PIN	GPIO_PIN(KEY_A_GPIO)		// pin of key A
#define KEY_B_PORT	GPIO_PORTINX(KEY_B_GPIO)	// port of key B
#define KEY_B_PIN	GPIO_PIN(KEY_B_GPIO)		// pin of key B
#define KEY_C_PORT	GPIO_PORTINX(KEY_C_GPIO)	// port of key C
#define KEY_C_PIN	GPIO_PIN(KEY_C_GPIO)		// pin of key C

	.section	.text

// ----------------------------------------------------------------------------
// get button from keyboard buffer KEY_* (returns NOKEY if no key)
// ----------------------------------------------------------------------------
// u8 KeyGet()

.global KeyGet
KeyGet:
	lbu	a0,RAM_KEYBUF_OFF(gp)	// A0 <- get key from keyboard buffer
	beqz	a0,KeyFlush2		// skip if no key

	add	sp,sp,-8
	sw	ra,0(sp)
	sw	a0,4(sp)

	li	a0,477
	li	a1,16
	call	PlayTone		// PlayTone(NOTE_C7, NOTE_LEN64); // sound of pressing key

	lw	a0,4(sp)
	lw	ra,0(sp)
	add	sp,sp,8

// ---- continue to KeyFlush

// ----------------------------------------------------------------------------
// key flush
// ----------------------------------------------------------------------------
// void KeyFlush()

.global KeyFlush
KeyFlush:
	sb	zero,RAM_KEYBUF_OFF(gp)	// clear keyboard buffer
KeyFlush2:
	ret

// ----------------------------------------------------------------------------
// keyboard interrupt - called every 20ms from SysTick interrupt
// ----------------------------------------------------------------------------
// void KeyScan()

.global KeyScan
KeyScan:
	// prepare registers
	la	a3,KeyGpio		// A3 <- prepare pointer to KeyGpio
	addi	a4,gp,RAM_KEYPRESS_OFF	// A4 <- pointer to KeyPress
	li	a5,1			// A5 <- key index 1..3

	// read key state -> A2
2:	lbu	a2,0(a3)		// A2 <- GPIO number
	srai	a1,a2,3			// A1 <- port index
	slli	a1,a1,10		// A1 <- port index * 1024 (1024 = GPIOB_BASE-GPIOA_BASE)
	lui	a0,%hi(GPIOA_BASE)	// A0 <- hi GPIOA base
	add	a1,a1,a0		// A1 <- address of the port HIGH
	lw	a1,%lo(GPIOA_BASE)+GPIO_INDR_OFF(a1) // A1 <- read port
	andi	a2,a2,7			// A2 <- mask pin index
	srl	a2,a1,a2		// A2 <- shift input bit to position 0
	andi	a2,a2,1			// A2 <- mask input bit

	// read old key press counter -> A1
	lbu	a1,0(a4)		// A1 <- old key press counter

	// skip if key is not pressed
	bnez	a2,5f			// skip if button is 1 (= key not pressed)

	// check first press
	bnez	a1,3f			// skip if press counter was not 0
	sb	a5,RAM_KEYBUF_OFF(gp)	// save key to key buffer
3:	li	a1,5			// A1 <- new release counter, about 100 ms

	// decrement release counter
5:	beqz	a1,6f			// skip if release counter is 0
	addi	a1,a1,-1		// A1 <- decrement release counter
	sb	a1,0(a4)		// save new release counter

	// increase pointers
6:	addi	a3,a3,1			// shift KeyGpio pointer
	addi	a4,a4,1			// shift KeyPress pointer
	addi	a5,a5,1			// shift key index
	li	a1,4			// A1 <- max. key index + 1
	bne	a5,a1,2b		// next key
	ret

// ----------------------------------------------------------------------------
// interrupt on key falling edge
// ----------------------------------------------------------------------------
// HANDLER void EXTI7_0_IRQHandler()

.global EXTI7_0_IRQHandler
EXTI7_0_IRQHandler:
	lui	a5,%hi(EXTI_BASE)	// A5 <- HIGH EXTI
	li	a4,0x3ff		// A4 <- clear word
	sw	a4,%lo(EXTI_BASE)+EXTI_INTFR_OFF(a5) // clear add interrupts
	mret

// ----------------------------------------------------------------------------
// keyboard initialize
// ----------------------------------------------------------------------------
// void KeyInit()

.global KeyInit
KeyInit:
	// save registers
	addi	sp,sp,-4
	sw	ra,0(sp)

	// setup key pins - input mode with pull-up
	li	a0,KEY_A_GPIO
	li	a1,GPIO_MODE_IN_PU
	call	GPIO_Mode		// KEY A: mode with pull-up
	li	a0,KEY_B_GPIO
	li	a1,GPIO_MODE_IN_PU
	call	GPIO_Mode		// KEY B: mode with pull-up
	li	a0,KEY_C_GPIO
	li	a1,GPIO_MODE_IN_PU
	call	GPIO_Mode		// KEY C: mode with pull-up

	// remap EXTI to keys A and B (do not use key C - it is connected with SWIO)
	li	a0,KEY_A_PORT
	li	a1,KEY_A_PIN
	call	GPIO_EXTILine		// setup external interrupt input pin KEY A
	li	a0,KEY_B_PORT
	li	a1,KEY_B_PIN
	call	GPIO_EXTILine		// setup external interrupt input pin KEY B

	// setup EXTI interrupt
	lui	a5,%hi(EXTI_BASE)	// A5 <- HIGH EXTI base
	li	a0,(1<<KEY_A_PIN) | (1<<KEY_B_PIN) // A0 <- pins
	sw	a0,%lo(EXTI_BASE)+EXTI_FTENR_OFF(a5) // setup EXTI on falling edge of KEY A and KEY B
	sw	a0,%lo(EXTI_BASE)+EXTI_INTENR_OFF(a5) // enable EXTI line interrupt of KEY A and KEY B

	// enable NVIC interrupt
	lui	a5,%hi(PFIC_BASE + (IRQ_EXTI7>>5))	// A5 <- PFIC (NVIC) base
	li	a0,1 << (IRQ_EXTI7 & 0x1f) // A0 <- IRQ bit
	sw	a0,%lo(PFIC_BASE + (IRQ_EXTI7>>5)) + PFIC_IENR_OFF(a5) // enable EXTI interrupt service 

	// restore registers
	lw	ra,0(sp)
	addi	sp,sp,4
	ret

#endif // USE_KEY_ASM
