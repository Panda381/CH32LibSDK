
// ****************************************************************************
//
//                           TI Emulator
//
// ****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// flag - emulate real speed (= run slowly)
#define SLOWMODE	1		// 1=run slow at real speed, 0=run fast at max speed (runs 5x faster)

// real time simulation - 4000 instructions per second, 1 instruction takes 250us
#define STEPTIME	(250*HCLK_PER_US)	// number of CPU clock cycles per instruction

// Run emulator
void RunEmu(void);

#ifdef __cplusplus
}
#endif
