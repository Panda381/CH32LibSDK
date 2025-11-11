
// ****************************************************************************
//
//                           Calculator - Definitions
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// configuration
#define MANTBYTES	7		// number of bytes of the mantissa (use minimal 5)
#define EXPBITS		8		// number of bits of exponent (8 or 16)
#define STK_NUM		20		// max. number of entries in calculator stack

// derived configuration
#define MANTDIG		(MANTBYTES*2)	// number of digits of the mantissa, including sign digit (must be even number)
#define EXPBYTES	(EXPBITS/8)	// number of bytes of exponent
#define EXP_1		0		// exponent of number 1.0000

#if EXPBITS == 8	// 8-bit exponent
#define tEXP		s8		// exponent type
#define EXP_MIN		(-99)		// minimal value of the exponent
#define EXP_MAX		(+99)		// maximal value of the exponent
#define EXP_0		((tEXP)0x80)	// exponent of number with value 0 (content of the mantissa does not matter)
#else			// 16-bit exponent
#define EPX_TYPE	s16		// exponent type
#define EXP_MIN		(-9999)		// minimal value of the exponent
#define EXP_MAX		(+9999)		// maximal value of the exponent
#define EXP_0		((tEXP)0x8000)	// exponent of number with value 0 (the content of the mantissa does not matter)
#endif
#define EXP_OVER	(EXP_MAX+1)	// exponent of number with overflow (content of the mantissa does not matter)

#define SIGN_POS	0	// positive sign
#define SIGN_NEG	9	// negative sign
#define SIGN_THRES	5	// check threshold of sign byte to detect negative number

// BCD number descriptor
#define SNUM_ALIGN ((0 - EXPBYTES - MANTBYTES) & 3)
typedef struct {
	tEXP	exp;			// signed decimal exponent (0 means number 1.0000 to 9.9999)
	u8	mant[MANTBYTES];	// sign + mantissa in BCD format (digits 0..9 in 2 nibbles)
					// - Normalized mantissa: The upper nibble of byte 0 contains
					//   the sign of the number: 0=positive, 9=negative. The lower
					//   nibble of byte 0, the upper nibble of byte 1, etc., up to
					//   the lower nibble of the last byte, contain digits of
					//   positive mantissa without sign, in order from the highest
					//   digit to the lowest.
					// - Denormalized mantissa: The sign high nibble in byte 0 is
					//   used as the next highest digit of the signed mantissa.
#if SNUM_ALIGN > 0
	u8	align[SNUM_ALIGN];	// align to 4 bytes (as compiler does)
#endif
} sNum;

// align check (to be consistent with the ASM code)
STATIC_ASSERT(sizeof(sNum) == (EXPBYTES+MANTBYTES+SNUM_ALIGN), "Incorrect sNum!");

// codes of arithmetics operations (4 bits)
#define OPER_NONE	0	// no operation
#define OPER_ADD	1	// +
#define OPER_SUB	2	// -
#define OPER_MUL	3	// *
#define OPER_DIV	4	// /
#define OPER_MOD	5	// modulo
#define OPER_PWR	6	// power
#define OPER_ROOT	7	// root
#define OPER_LPAR	8	// ( left parenthesis
#define OPER_RPAR	9	// ) right parenthesis
#define OPER_EQU	10	// = result

#define OPER_MASK	0x0f	// mask of code of arithmetics operation

// priority of arithmetics operations (4 bits)
#define PRIO_NONE	0	// no level
#define PRIO_ADDSUB	1	// + -
#define PRIO_MULDIV	2	// * / modulo
#define PRIO_PWR	3	// power root

#define PRIO_SHIFT	4	// shift priority

#ifdef __cplusplus
}
#endif
