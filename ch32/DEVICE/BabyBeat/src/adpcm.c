
// ****************************************************************************
//
//                    Music Player - IMA ADPCM decompression
//
// ****************************************************************************

#include "../include.h"

// IMA ADPCM tables
#define ADPCM_MINVAL	-32768		// IMA ADPCM minimal value
#define ADPCM_MAXVAL	+32767		// IMA ADPCM maximal value
#define ADPCM_STEPS	89		// IMA ADPCM number of steps

const s8 ADPCM_TabInx[16] =	// IMA ADPCM table of index change steps
{
	-1,	-1,	-1,	-1,	// +0 .. +3, decrease step size
	2,	4,	6,	8,	// +4 .. +7, increase step size
	-1,	-1,	-1,	-1,	// -0 .. -3, decrease step size
	2,	4,	6,	8,	// -4 .. -7, increase step size
};

const s16 ADPCM_StepSize[ADPCM_STEPS] =	// IMA ADPCM table of step sizes
{
	7,	8,	9,	10,	11,	12,	13,	14,
	16,	17,	19,	21,	23,	25,	28,	31,
	34,	37,	41,	45,	50,	55,	60,	66,
	73,	80,	88,	97,	107,	118,	130,	143,
	157,	173,	190,	209,	230,	253,	279,	307,
	337,	371,	408,	449,	494,	544,	598,	658,
	724,	796,	876,	963,	1060,	1166,	1282,	1411,
	1552,	1707,	1878,	2066,	2272,	2499,	2749,	3024,
	3327,	3660,	4026,	4428,	4871,	5358,	5894,	6484,
	7132,	7845,	8630,	9493,	10442,	11487,	12635,	13899,
	15289,	16818,	18500,	20350,	22385,	24623,	27086,	29794,
	32767
};

// ADPCM decompressor
sAdpcm Adpcm;

// ADPCM decompression (returns key code)
u8 Decomp()
{
	u8 b;
	int val, val2;

	// pointer to descriptors
	sOutBuf* o = &OutBuf;
	sAdpcm* a = &Adpcm;

	while (True)
	{

#if BABYBEAT		// 1 = use BabyBeat device
		// keyboard
		u8 key = KeyGet();
		if (key != NOKEY)
		{
			switch (key)
			{
			// key "Play"
			case KEY_PLAY:
			case KEY_PLAY_LONG:	
				a->pause = !a->pause;
				break;

			// key "VolUp", short
			case KEY_VOLUP:
				if (Volume < VOLMAX)
				{
					Volume++;
					VolMul = VolMulTab[Volume];
				}
				break;

			// key "VolDn", short
			case KEY_VOLDN:
				if (Volume > 0)
				{
					Volume--;
					VolMul = VolMulTab[Volume];
				}
				break;

			// seek forward "Next", long
			case KEY_NEXT_LONG:
				a->pause = False;
				InSeek(a->sampinx + SAMPSKIP);
				break;

			// seek backward "Prev", long
			case KEY_PREV_LONG:
				a->pause = False;
				InSeek(a->sampinx - SAMPSKIP);
				break;

			// other keys
			default:
				return key;
			}
		}
#endif // BABYBEAT

		// pause
		if (a->pause)
		{
			// add value to output
			OutSamp(a->prevval[0]);
			OutSamp(a->prevval[1]);
			continue;
		}

		// preamble block
		if (a->sampcnt <= 0)
		{
			// get current value from block header
			b = GetByte();
			val = (s16)(b + GetByte()*256);
	                a->prevval[0] = (s16)val;
			a->stepinx[0] = (s8)GetByte();
			GetByte(); // skip 3rd byte

			b = GetByte();
			val2 = (s16)(b + GetByte()*256);
	                a->prevval[1] = (s16)val2;
			a->stepinx[1] = (s8)GetByte();
			GetByte(); // skip 3rd byte
			
			// set counter of samples per block
			a->sampcnt = a->sampblock; // new sample counter
			a->odd = False; // odd sub-sample
			a->byte4 = 0; // reset counter of 4-byte
		}
		else
		{
			u8 delta, delta2;

			// get next sample delta
			if (a->odd) // odd sub-sample (higher 4 bits)
			{
				delta = (u8)(a->subsample[0] >> 4);
				delta2 = (u8)(a->subsample[1] >> 4);
			}
			else // even sub-sample (lower 4 bits)
			{
				if (a->byte4 == 0)
				{
					delta = GetByte();
					a->cache[2] = GetByte();
					a->cache[1] = GetByte();
					a->cache[0] = GetByte();
					a->byte4 = 3;
				}
				else
				{
					a->byte4--;
					delta = a->cache[a->byte4];
				}
				a->subsample[0] = delta;
				delta &= 0x0f;

				delta2 = GetByte();
				a->subsample[1] = delta2;
				delta2 &= 0x0f;
			}

			// flip odd/even flag
			a->odd = !a->odd;

			// get step size
			s8 stepinx = a->stepinx[0];
			s16 step = ADPCM_StepSize[stepinx];

			s8 stepinx2 = a->stepinx[1];
			s16 step2 = ADPCM_StepSize[stepinx2];

			// shift step index
			stepinx += ADPCM_TabInx[delta];
			stepinx2 += ADPCM_TabInx[delta2];

			// limit step index
			if ((uint)stepinx >= (uint)ADPCM_STEPS)
			{
				if (stepinx < 0)
					stepinx = 0;
				else
					stepinx = ADPCM_STEPS - 1;
			}
			a->stepinx[0] = stepinx;

			if ((uint)stepinx2 >= (uint)ADPCM_STEPS)
			{
				if (stepinx2 < 0)
					stepinx2 = 0;
				else
					stepinx2 = ADPCM_STEPS - 1;
			}
			a->stepinx[1] = stepinx2;

			// get next difference
			s16 dif = step >> 3;
			if ((delta & B0) != 0) dif += step >> 2;
			if ((delta & B1) != 0) dif += step >> 1;
			if ((delta & B2) != 0) dif += step ;
			if ((delta & B3) != 0) dif = -dif; // sign correction

			s16 dif2 = step2 >> 3;
			if ((delta2 & B0) != 0) dif2 += step2 >> 2;
			if ((delta2 & B1) != 0) dif2 += step2 >> 1;
			if ((delta2 & B2) != 0) dif2 += step2 ;
			if ((delta2 & B3) != 0) dif2 = -dif2; // sign correction

			// add difference to previous value
			val = a->prevval[0] + dif;
			if (val > ADPCM_MAXVAL) val = ADPCM_MAXVAL;
			if (val < ADPCM_MINVAL) val = ADPCM_MINVAL;
			a->prevval[0] = (s16)val;

			val2 = a->prevval[1] + dif2;
			if (val2 > ADPCM_MAXVAL) val2 = ADPCM_MAXVAL;
			if (val2 < ADPCM_MINVAL) val2 = ADPCM_MINVAL;
			a->prevval[1] = (s16)val2;
		}

		// sample counter
		a->sampcnt--;

		// add value to output
		OutSamp(a->prevval[0]);
		OutSamp(a->prevval[1]);

		// shift sample index
		a->sampinx++;

		// end of file (or read error) - skip to next file
		if ((a->sampinx >= a->sampnum) || InBuf.err) return KEY_NEXT;
	}
}
