
// ****************************************************************************
//
//                         Music Player - Sound output
//
// ****************************************************************************

#include "../include.h"

// output buffer
sOutBuf OutBuf;

#if BABYBEAT		// 1 = use BabyBeat device
// volume
int Volume = 6;				// current volume
int VolMul = 769;			// current volume multiplier

// volume table
const int VolMulTab[VOLMAX+1] = {
	96,		// 0
	136,		// 1
	192,		// 2
	272,		// 3
	384,		// 4
	544,		// 5
	769,		// 6
	1088,		// 7
	1539,		// 8
	2177,		// 9
};
#else // BABYBEAT
#define VolMul	1088
#endif // BABYBEAT

// save sample to output buffer
void OutSamp(s16 samp)
{
	// prepare pointer to output buffer descriptor
	sOutBuf* o = &OutBuf;

	// convert 16-bit signed sample to unsigned ~11-bit sample (range 0..2176)
	u16 val = (((int)samp + 32768) * VolMul) >> 16;

	// waiting for ring buffer to be freed
	while (True)
	{
		int w = o->w;	// write index into ring buffer
		cb();
		int r = o->r;	// read index from ring buffer
		cb();
		int w2 = w + 1;	// next write index
		if (w2 >= OUTBUF_SIZE) w2 = 0; // wrap index to start of the buffer
		if (w2 != r)	// check if there si a free space in the ring buffer
		{
			o->buf[w] = val; // write data to ring buffer
			cb();
			o->w = w2;	// save new write index
			break;
		}
	}
}

// timer handler
HANDLER void TIM1_UP_IRQHandler(void)
{
	// clear interrupt request
	TIM1_UpIntClr();

	// prepare pointer to output buffer descriptor
	sOutBuf* o = &OutBuf;

	// prepare indices
	int w = o->w;	// write index into ring buffer
	int r = o->r;	// read index from ring buffer
	int r2 = r + 1;	// next read index
	if (r2 >= OUTBUF_SIZE) r2 = 0; // wrap index to start of the buffer

	// check if we have 2 samples to read from the ring buffer
	int s = o->old[0]; // left channel if we have data drop-out
	int s2 = o->old[1]; // right channel if we have data drop-out
	if ((r != w) && (r2 != w)) // we need 2 samples
	{
		// prepare sample of left channel
		s = o->buf[r];	// get sample from the ring buffer
		o->old[0] = s;

		// prepare sample of right channel
		s2 = o->buf[r2]; // get sample from the ring buffer
		o->old[1] = s2;

		// save new read index
		r2++;		// next read index
		if (r2 >= OUTBUF_SIZE) r2 = 0; // wrap index to start of the buffer
		o->r = r2;	// save new read index
	}

	// output samples
#if BABYBEAT		// 1 = use BabyBeat device
	//   Timer1, mapping 2: PC6:CH1 (right), PC7:CH2 (left)
	TIM1_Comp2(s);		// update new PWM value for left channel
	TIM1_Comp1(s2);		// update new PWM value for right channel
#else
	//   Timer1, mapping 9: PA1:CH2 (right), PA2:CH3 (left)
	TIM1_Comp3(s);		// update new PWM value for left channel
	TIM1_Comp2(s2);		// update new PWM value for right channel
#endif
}

// sound initialize
void SndInit(void)
{
	// initialize output buffer
	memset(&OutBuf, 0, sizeof(OutBuf));

	// setup output pins
	RCC_AFIClkEnable();
#if BABYBEAT		// 1 = use BabyBeat device
	RCC_PCClkEnable();
#else
	RCC_PAClkEnable();
#endif
	GPIO_Mode(AUDIOL_GPIO, GPIO_MODE_AF);
	GPIO_Mode(AUDIOR_GPIO, GPIO_MODE_AF);

	// Remap Timer 1 (default 0)
#if BABYBEAT		// 1 = use BabyBeat device
	//  2 ... PC5:ETR, PC6:CH1 (right), PC7:CH2 (left), PC0:CH3, PD3:CH4, PC1:BKIN, PC3:CH1N, PC4:CH2N, PD1:CH3N
	GPIO_Remap_TIM1(2);

	// initialize PWM output: Timer 1, channel 1, divider 1, reload 2176, compare 0, high
// System frequency: 48 MHz
// Sample rate: divider 1, period 2177, result sample rate: 48000000/2177 = 22049 Hz
	TIM1_InitPWM(1, 1, 2176, 0, True);

#else
	// 9 ... PB4:ETR, PA0:CH1, PA1:CH2 (right), PA2:CH3 (left), PA3:CH4, PB2:BKIN, PC0:CH1N, PC1:CH2N, PC2:CH3N
	GPIO_Remap_TIM1(9);

	// initialize PWM output: Timer 1, channel 3, divider 1, reload 2176, compare 0, high
// System frequency: 48 MHz
// Sample rate: divider 1, period 2177, result sample rate: 48000000/2177 = 22049 Hz
	TIM1_InitPWM(3, 1, 2176, 0, True);
#endif

	// initialize channel 2
	TIM1_Comp2(0);			// set compare value
	TIM1_OC2Mode(TIM_COMP_PWM1);	// set compare mode
	TIM1_OC2PreEnable();		// enable preload compare register
	TIM1_CC2Enable();		// enable compare output

	// set interrupt
	TIM1_UpIntEnable();		// enable update interrupt
	NVIC_IRQEnable(IRQ_TIM1_UP);	// enable interrupt service
}
