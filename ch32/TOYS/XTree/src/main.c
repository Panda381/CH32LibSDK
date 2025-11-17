
// ****************************************************************************
//
//                                   XTree
//
// ****************************************************************************

#include "../include.h"

#define LED_NUM		12	// number of LEDs

#define LED1_PIN	PA1	// gpio of LED1 signal
#define LED2_PIN	PA2	// gpio of LED1 signal
#define LED3_PIN	PC1	// gpio of LED1 signal
#define LED4_PIN	PC2	// gpio of LED1 signal

// pins HIGH and LOW to activate LED
const u8 LedPin[2*LED_NUM] = {
	LED2_PIN, LED3_PIN, 	// LED1
	LED3_PIN, LED2_PIN, 	// LED2
	LED3_PIN, LED4_PIN, 	// LED3
	LED4_PIN, LED3_PIN, 	// LED4
	LED2_PIN, LED4_PIN, 	// LED5
	LED4_PIN, LED2_PIN, 	// LED6
	LED1_PIN, LED2_PIN, 	// LED7
	LED2_PIN, LED1_PIN, 	// LED8
	LED4_PIN, LED1_PIN, 	// LED9
	LED1_PIN, LED4_PIN, 	// LED10
	LED3_PIN, LED1_PIN, 	// LED11
	LED1_PIN, LED3_PIN, 	// LED12
};

#define LEVEL_NUM	32	// number of bright levels 0..15

// bright samples (every sample is 15 steps + 1 stop bit)
const u16 LedSamp[LEVEL_NUM] = {
	0b1000000000000000,	// 1 x4
	0b1000000000000000,	// 1
	0b1000000000000000,	// 1
	0b1000000000000000,	// 1
	0b1000000010000000,	// 2 x4
	0b1000000010000000,	// 2
	0b1000000010000000,	// 2
	0b1000000010000000,	// 2
	0b1000010000100000,	// 3 x3
	0b1000010000100000,	// 3
	0b1000010000100000,	// 3
	0b1000100010001000,	// 4 x3
	0b1000100010001000,	// 4
	0b1000100010001000,	// 4
	0b1001001001001000,	// 5 x3
	0b1001001001001000,	// 5
	0b1001001001001000,	// 5
	0b1001010010010100,	// 6 x2
	0b1001010010010100,	// 6
	0b1010100101010100,	// 7 x2
	0b1010100101010100,	// 7
	0b1010101010101010,	// 8 x2
	0b1010101010101010,	// 8
	0b1110101010101010,	// 9 x2
	0b1110101010101010,	// 9
	0b1110101011101010,	// 10
	0b1110101110101110,	// 11
	0b1110111011101110,	// 12
	0b1111111011101110,	// 13
	0b1111111011111110,	// 14
	0b1111111111111110,	// 15
	0b1111111111111111,	// 16
};

u8 LedInx = 0;	// current LED serviced

#define LED_SPEED	5	// slowing down LED animation (= number of shifts of LED phase to sample step)

// phase of animation (<0 dark)
int LedPhase[LED_NUM];

// current sample (bit 15 of every sample is set to 1)
u32 LedCurSamp[LED_NUM];

#if AUDIO_VOICES==1
#include "../mid/music1.c"
#elif AUDIO_VOICES==2
#include "../mid/music2.c"
#elif AUDIO_VOICES==4
#include "../mid/music4.c"
#elif AUDIO_VOICES==8
#include "../mid/music8.c"
#endif

//const AL_Instrument *pinstrument= &Audio_Instrument_Square;
const AL_Instrument *pinstrument= &Audio_Instrument_8bit;
//const AL_Instrument *pinstrument= &Audio_Instrument_Synth;

//const AL_Instrument *pinstrument= &Audio_Instrument_Sine;
//const AL_Instrument *pinstrument= &Audio_Instrument_Triangle;
//const AL_Instrument *pinstrument= &Audio_Instrument_Square;
//const AL_Instrument *pinstrument= &Audio_Instrument_Sawtooth;
//const AL_Instrument *pinstrument= &Audio_Instrument_4OctaveSine;
//const AL_Instrument *pinstrument= &Audio_Instrument_4OctaveSawtooth;
//const AL_Instrument *pinstrument= &Audio_Instrument_Piano;
//const AL_Instrument *pinstrument= &Audio_Instrument_Organ;
//const AL_Instrument *pinstrument= &Audio_Instrument_FatOrgan;
//const AL_Instrument *pinstrument= &Audio_Instrument_Synth;
//const AL_Instrument *pinstrument= &Audio_Instrument_8bit;
//const AL_Instrument *pinstrument= &Audio_Instrument_Vibraphone;
//const AL_Instrument *pinstrument= &Audio_Instrument_Violin;
//const AL_Instrument *pinstrument= &Audio_Instrument_Violin2;
//const AL_Instrument *pinstrument= &Audio_Instrument_Tom;
//const AL_Instrument *pinstrument= &Audio_Instrument_Flute;
//const AL_Instrument *pinstrument= &Audio_Instrument_Sax;
//const AL_Instrument *pinstrument= &Audio_Instrument_Xylophone;

// PWM interrupt handler (called on 32768 Hz)
HANDLER void TIM1_CC_IRQHandler(void)
{
// --- audio output

	// clear interrupt request
	TIM1_CC4IntClr();

	// set compare value, channel 4
	TIM1_Comp4(Audio_FifoRead(&Audio_System.fifo));

// --- LED control

	// set all LED pins OFF
	GPIO_Mode(LED1_PIN, GPIO_MODE_IN);
	GPIO_Mode(LED2_PIN, GPIO_MODE_IN);
	GPIO_Mode(LED3_PIN, GPIO_MODE_IN);
	GPIO_Mode(LED4_PIN, GPIO_MODE_IN);

	// current LED index
	int ledinx = LedInx + 1;
	if (ledinx >= LED_NUM) ledinx = 0;
	LedInx = ledinx;

	// get LED phase of animation
	int ledphase = LedPhase[ledinx] + 1;
	if (ledphase >= ((2*LEVEL_NUM) << LED_SPEED))
	{
		// generate new wait time to next animation (2731 = 1 sec)
		ledphase = -RandU16MinMax(300, 3000);
	}

	// check if LED is waiting for next animation
	LedPhase[ledinx] = ledphase;
	if (ledphase < 0) return;

	// get current sample
	int samp = LedCurSamp[ledinx];
	if (samp == 0) // sample is already not valid
	{
		int sampinx = ledphase >> LED_SPEED;
		if (sampinx >= LEVEL_NUM) sampinx = 2*LEVEL_NUM-1 - sampinx;
		samp = LedSamp[sampinx];
	}

	// shift sample
	int bit = samp & 1;
	samp >>= 1;
	LedCurSamp[ledinx] = samp;

	// light LED ON
	if (bit != 0)
	{
		ledinx <<= 1;
		GPIO_Out1(LedPin[ledinx]);
		GPIO_Out0(LedPin[ledinx+1]);
		GPIO_Mode(LedPin[ledinx], GPIO_MODE_OUT);
		GPIO_Mode(LedPin[ledinx+1], GPIO_MODE_OUT);
	}
}

// Timer PWM initialize
// The audio output is via PC4, Timer 1 channel 4, mapping 0
void TimerPWMInit(void)
{
	// enable pin output
	RCC_AFIClkEnable();
	RCC_PCClkEnable();
	GPIO_Mode(AUDIO_PORT, GPIO_MODE_AF);

	// remap timer 1, use channel 4 on PC4 pin
	// 0 ... PC5:ETR, PD2:CH1, PA1:CH2, PC3:CH3, PC4:CH4, PC2:BKIN, PD0:CH1N, PA2:CH2N, PD1:CH3N
	GPIO_Remap_TIM1(0);

	// initialize PWM output from channel 4
//   chan ... channel 1..4
//   div ... divider 1..65536
//   reload ... reload value 0..65535 (timer period = reload+1)
//   comp ... compare value 0..reload
//   high ... direction HIGH->LOW (or LOW->HIGH otherwise)
	TIM1_InitPWM(4, AUDIO_TIMER_PRESCALER, AUDIO_TIMER_RELOAD, 128, True);

	// set interrupt
	TIM1_CC4IntClr();		// clear interrupt request
	TIM1_CC4IntEnable();		// enable capture compare of channel 4

	NVIC_IRQEnable(IRQ_TIM1_CC);	// enable interrupt service
}

//volatile const u8* Src = song;
//const AL_Instrument *pinstrument= &Audio_Instrument_Synth;

int main(void)
{
	int i;

	// randomize LED start phase
	for (i = 0; i < LED_NUM; i++) LedPhase[i] = -RandU16MinMax(500, 5000);

	// Remap PA1 & PA2 to GPIO
	GPIO_Remap_PA1PA2(0);

	// Timer PWM initialize
	TimerPWMInit();

	// Initialize audio system
	Audio_Initialize();

	// Initialize midi player
	Midi_PlayerInitialize();

	// Set up track instruments
	for (i=0; i < AUDIO_VOICES; i++)
	{
		Audio_SetInstrument(0, i, pinstrument);
	}

	// main loop
	while (True)
	{
		// Start the song if none is playing 
		if (!Midi_PlayerPlayingSong())
		{
			Midi_PlayerStartSong(0, (u8*)song);
		}

		// Keep audio fifo full
		while (Audio_FifoIsFree(&Audio_System.fifo))
		{
			// Update midi player
			Midi_PlayerUpdate();

			// Update audio system
			Audio_Update();
			
			// Write current audio sample to the fifo
			Audio_FifoWrite(&Audio_System.fifo, Audio_GetChannelValue(0));
		}
	}

	// Shut down mini midi player
//	Midi_PlayerRelease();

	// Shut down audio system
//	Audio_Release();
}
