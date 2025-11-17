
// ****************************************************************************
//
//                          MidiBox - Audio Library
//
// ****************************************************************************
// Library original source code:
//  Good Vibes: https://github.com/spot1984/good-vibes
//  A cross platform audio library.
//  (c) 2023 D. Scott Williamson

/*
    audio.h
    Audio library
    (c) 2023 D. Scott Williamson
    spot1984@gmail.com
       
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. 

    ----------

    Adaptation to CH32LibSDK library: (c) 2025 Miroslav Nemecek
*/

#include "../include.h"

// audio system instance
AL_System Audio_System;

// MIDI player instance
MIDI_Player Midi_Player;

// Quarter sintab, signed, 0 center
const s8 Audio_QuarterSinTab[256] = {
	  0,  0,  1,  2,  3,  3,  4,  5,  6,  7,  7,  8,  9, 10, 10, 11,
	 12, 13, 14, 14, 15, 16, 17, 18, 18, 19, 20, 21, 21, 22, 23, 24,
	 24, 25, 26, 27, 28, 28, 29, 30, 31, 31, 32, 33, 34, 34, 35, 36,
	 37, 37, 38, 39, 40, 40, 41, 42, 43, 43, 44, 45, 46, 46, 47, 48,
	 48, 49, 50, 51, 51, 52, 53, 54, 54, 55, 56, 56, 57, 58, 58, 59,
	 60, 61, 61, 62, 63, 63, 64, 65, 65, 66, 67, 67, 68, 69, 69, 70,
	 71, 71, 72, 73, 73, 74, 74, 75, 76, 76, 77, 78, 78, 79, 79, 80,
	 81, 81, 82, 83, 83, 84, 84, 85, 85, 86, 87, 87, 88, 88, 89, 89,
	 90, 91, 91, 92, 92, 93, 93, 94, 94, 95, 95, 96, 96, 97, 97, 98,
	 98, 99, 99,100,100,101,101,102,102,103,103,104,104,105,105,105,
	106,106,107,107,108,108,108,109,109,110,110,110,111,111,112,112,
	112,113,113,113,114,114,115,115,115,116,116,116,117,117,117,117,
	118,118,118,119,119,119,119,120,120,120,121,121,121,121,122,122,
	122,122,122,123,123,123,123,123,124,124,124,124,124,125,125,125,
	125,125,125,125,126,126,126,126,126,126,126,126,127,127,127,127,
	127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,
};

// MIDI note frequencies C1 through G9
const u16 Midi_NoteFrequencies[] = {
	8, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 19, 
	21, 22, 23, 25, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 
	52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123, 
	131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 
	294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 
	659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 
	1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 
	2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5920, 
	6272, 6645, 7040, 7459, 7902, 8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544,
};

// seed of audio noise sampler
s8 Audio_Noise1Value;
s8 Audio_Noise2Value;

// Audio noise sampler - tinny white noise
s8 Audio_Noise1Sampler(u16 index)
{
	Audio_Noise1Value = (AUDIO_NOISE_SOURCE) ^ Audio_Noise1Value;
	return Audio_Noise1Value;
}

// Audio noise 2 sampler - midtone white noise, index changes pitch
s8 Audio_Noise2Sampler(u16 index)
{
	Audio_Noise2Value = (s8)((AUDIO_NOISE_SOURCE) ^ Audio_Noise2Value ^ index);
	return Audio_Noise2Value;
}

// Robot sampler - midtone robotfrequency changes pitch
s8 Audio_RobotSampler(u16 index)
{
	return (s8)((AUDIO_NOISE_SOURCE) ^ index);
}

// Sawtooth sampler
s8 Audio_SawtoothSampler(u16 index)
{
	return (s8)(index >> 8);
}

// Square wave sampler
s8 Audio_SquareSampler(u16 index)
{
	return (s8)(((s16)index < 0) ? -127 : 127);
}

// Triangle sampler
s8 Audio_TriangleSampler(u16 index)
{
	if ((s16)index < 0)
		return -((s8) (((index >> 7) & 0xff))) - 129;
	else
		return (s8) (((index >> 7) & 0xff)) + 128;
} 

// Sine sampler
s8 Audio_SineSampler(u16 index)
{
	u16 tableindex = (index >> 6) & 0xff;
	switch (index >> 14)
	{
	case 0: return Audio_QuarterSinTab[tableindex];
	case 1: return Audio_QuarterSinTab[255 - tableindex];
	case 2: return -(Audio_QuarterSinTab[tableindex]);
	// case 3:
	default: return -(Audio_QuarterSinTab[255 - tableindex]);
	}
}

// 4-Octave sine sampler
s8 Audio_4OctaveSineSampler(u16 index)
{
	s16 sample =	Audio_SineSampler(index)
			+ Audio_SineSampler(index << 1)
			+ Audio_SineSampler(index << 2)
			+ Audio_SineSampler(index << 3);
	return sample >> 2;
}     

// 4-Octave sawtooth sampler
s8 Audio_4OctaveMixSampler(u16 index)
{
	s16 sample =	Audio_SawtoothSampler(index << 1)
			+ (Audio_TriangleSampler(index << 0) << 1);
	return sample >> 1;
}       

// Multiply an 8 bit unsigned volume by an 8 bit signed sample, returning a signed modulated sample
s16 Audio_VolumeSampleMultiply(u16 u, s16 s)
{
	return (u*s) >> 8;
}

// Multiply 8 bit unsigned volumes by one another, returning an 8 bit volume
u16 Audio_VolumeVolumeMultiply(u16 v1, u16 v2)
{
	return (v1*v2) >> 8;
}

// Initialize audio library
void Audio_Initialize(void)
{
	AL_System* as = &Audio_System;
	as->volume=255;
	as->envelopedivider=AUDIO_SHAPE_DIVIDER; 
	Audio_FifoInitialize(&as->fifo);
	u16 channel;
	for (channel=0; channel < AUDIO_CHANNELS; channel++)
	{
		AL_Channel* pChannel = &as->channel[channel];
		pChannel->volume=255;
		pChannel->compositevolume=(255*255>>8);

		u16 voice;
		for (voice=0; voice < AUDIO_VOICES; voice++)
		{
			AL_Voice* pVoice = &pChannel->voice[voice];
			pVoice->position=0;            
			pVoice->delta=0;            
			pVoice->pitchbend=0;            
			pVoice->volume=255;
			pVoice->compositevolume=(255*255*255>>16);
			pVoice->output_value=0;
			pVoice->pInstrument=NULL;
		}
	}
}

// Audio update
void Audio_Update(void)
{
	u16 channel, voice;
	AL_Channel* pChannel;
	AL_Voice* pVoice;
	AL_ADSR* padsr;
	AL_System* as = &Audio_System;
	s16 sample;

	// Update composite volumes if system, channel, or voice volumes have changed
	if (as->flags & AL_SYSTEM_FLAG_UPDATE_COMPOSITE_VOLUME)
	{
		for (channel=0; channel < AUDIO_CHANNELS; channel++)
		{
			pChannel = &as->channel[channel];

			// Update composite channel volumes
			if ((as->flags & AL_SYSTEM_FLAG_UPDATE_VOLUME) |
				(pChannel->flags & AL_SYSTEM_FLAG_UPDATE_VOLUME))
			{
				pChannel->compositevolume = Audio_VolumeVolumeMultiply(as->volume, pChannel->volume);
				pChannel->flags |= AL_SYSTEM_FLAG_UPDATE_VOLUME;
			}

			// Update composite voice volumes
			for (voice=0; voice < AUDIO_VOICES; voice++)
			{
				pVoice = &pChannel->voice[voice];
				if ((pChannel->flags & AL_SYSTEM_FLAG_UPDATE_VOLUME) |
					(pVoice->flags & AL_SYSTEM_FLAG_UPDATE_VOLUME))
				{
					pVoice->compositevolume = Audio_VolumeVolumeMultiply(pChannel->compositevolume, pVoice->volume);
					pVoice->flags &= ~AL_SYSTEM_FLAG_UPDATE_VOLUME;
				}
			}
			pChannel->flags &= ~AL_SYSTEM_FLAG_UPDATE_VOLUME;
		}
		as->flags &= ~AL_SYSTEM_FLAG_UPDATE_VOLUME;
	}

	// Update timers of all voice playback parameters
	for (channel=0; channel < AUDIO_CHANNELS; channel++)
	{
		pChannel = &as->channel[channel];
		pChannel->output_value=0;
		for (voice=0; voice < AUDIO_VOICES; voice++)
		{
			pVoice = &pChannel->voice[voice];
			if (pVoice->playing)
			{
				if (pVoice->pInstrument != NULL)
				{
					// There is an instrument, process
					pVoice->position += pVoice->delta + (pVoice->vibrato >> 4) + pVoice->pitchbend;
					sample = (s16)pVoice->pInstrument->sample(pVoice->position);
					pVoice->output_value = Audio_VolumeSampleMultiply(pVoice->sample_volume, sample);
				}
			}
			else
			{
				// Voice not playing 
				// Drift value to center 
				if (pVoice->output_value!=0)
				{
					if (pVoice->output_value > 0)
						pVoice->output_value--;
					else
						pVoice->output_value++;
				}
			}
			pChannel->output_value += pVoice->output_value;
		}

#if AUDIO_VOICES_POW2
		// Voice clipping
		pChannel->output_value >>= AUDIO_VOICES_POW2;
#endif
	}

	// Update audio evelope (ADSR, vibrato, tremelo)
	if (--as->envelopedivider == 0)
	{
		as->envelopedivider=AUDIO_SHAPE_DIVIDER;    // 10ms

		// Envelope update
		for (channel=0; channel < AUDIO_CHANNELS; channel++)
		{
			pChannel = &as->channel[channel];
			for (voice=0; voice < AUDIO_VOICES; voice++)
			{
				pVoice = &pChannel->voice[voice];
				if (pVoice->playing)
				{
					padsr = &pVoice->ADSR_composite;
					switch (pVoice->ADSR_phase)
					{
					// Attack
					case 'a':
						pVoice->ADSR_volume += padsr->attack_delta;
						if (pVoice->ADSR_volume >= padsr->attack_peak)
						{
							pVoice->ADSR_phase = 'd';
							pVoice->ADSR_volume = padsr->attack_peak;
						}
						break;

					// Decay
					case 'd':
						pVoice->ADSR_volume -= padsr->decay_delta;
						if ((pVoice->ADSR_volume <= padsr->sustain_value) || (pVoice->ADSR_volume < 0))
						{
							pVoice->ADSR_phase = 's';
							pVoice->ADSR_volume = padsr->sustain_value;
						}
						break;

					// Sustain 
					case 's':
						// Sustain does nothing but waits for a key release
						break;

					// Release
					case 'r':
						pVoice->ADSR_volume -= padsr->release_delta;
						if (pVoice->ADSR_volume < 0)
						{
							pVoice->ADSR_phase = 'x';
							pVoice->ADSR_volume = 0;
							pVoice->playing = False;
						}
						break;

					// ADSR not active
					default:
						break;                     
					}

					// Update vibrato
					pVoice->vibrato += pVoice->vibrato_delta;
					if (pVoice->vibrato > 0)
					{
						if (pVoice->vibrato >= pVoice->pInstrument->vibrato_amplitude)
						{
							pVoice->vibrato_delta = -pVoice->vibrato_delta;
							pVoice->vibrato = (pVoice->pInstrument->vibrato_amplitude << 1) - pVoice->vibrato;
						}
					}
					else if (pVoice->vibrato < 0)
					{
						if ((-pVoice->vibrato) >= pVoice->pInstrument->vibrato_amplitude)
						{
							pVoice->vibrato_delta = -pVoice->vibrato_delta;
							pVoice->vibrato = -(pVoice->pInstrument->vibrato_amplitude << 1) - pVoice->vibrato;
						}
					}

					// Update tremolo
					pVoice->tremolo += pVoice->tremolo_delta;
					if (pVoice->tremolo > 0)
					{
						if (pVoice->tremolo >= pVoice->tremolo_amplitude)
						{
							pVoice->tremolo_delta = -pVoice->tremolo_delta;
							pVoice->tremolo = (pVoice->tremolo_amplitude << 1) - pVoice->tremolo;
						}
					}
					else if (pVoice->tremolo < 0)
					{
						if (-pVoice->tremolo > pVoice->tremolo_amplitude)
						{
							pVoice->tremolo_delta = -pVoice->tremolo_delta;
							pVoice->tremolo = -(pVoice->tremolo_amplitude << 1) - pVoice->tremolo;
						}
					}

					// Calculate volume to be applied to the sampler
					// Note: Composite volume is applied to ADSR and tremolo parameters in keyon
					// Note: It is possible for tremolo to push amplitude to clip at high volumes
					pVoice->sample_volume = pVoice->ADSR_volume + (pVoice->tremolo >> 4);
				}
			}
		}
	}
}

// Get the value of an output pin
u8 Audio_GetChannelValue(u16 channel)
{   
	// Make the signed output value a positive byte for the FIFO
	int value = (Audio_System.channel[channel].output_value << AUDIO_VOLUME_SHIFT) + 128;

	// Clamp to PWM range to prevent wrapping
	if (value<0) value=0;
	if (value>255) value=255;
	return (u8)value;
}

// Set audio system master volume
void Audio_SetMasterVolume(u16 volume)
{
	// Volume changes are expensive and only should be done when needed
	if (Audio_System.volume != volume)
	{
		// Set the master volume
		Audio_System.volume=volume;

		// Flag that composite volumes need to be updated next update and that the master volume has changed
		Audio_System.flags |= AL_SYSTEM_FLAG_UPDATE_VOLUME | AL_SYSTEM_FLAG_UPDATE_COMPOSITE_VOLUME;
	}
}

// Set audio system channel volume
void Audio_SetChannelVolume(u16 channel, u16 volume)
{
	// Volume changes are expensive and only should be done when needed
	if (Audio_System.channel[channel].volume != volume)
	{
		// Set the channel volume
		Audio_System.channel[channel].volume=volume;

		// Flag that the channel composite volume needs update
		Audio_System.channel[channel].flags |= AL_SYSTEM_FLAG_UPDATE_VOLUME;

		// Flag that a volume has changed and composite volumes need to be updated next update
		Audio_System.flags |= AL_SYSTEM_FLAG_UPDATE_COMPOSITE_VOLUME;
	}
}

// Set audio system voice volume
void Audio_SetVoiceVolume(u16 channel, u16 voice, u16 volume)
{
	// Volume changes are expensive and only should be done when needed (no hardware multiply)
	if (Audio_System.channel[channel].voice[voice].volume != volume)
	{
		// Set the voice volume
		Audio_System.channel[channel].voice[voice].volume = volume;

		// Flag that the voice composite volume needs update
		Audio_System.channel[channel].voice[voice].flags |= AL_SYSTEM_FLAG_UPDATE_VOLUME;

		// Flag that a volume has changed and composite volumes need to be updated next update
		Audio_System.flags |= AL_SYSTEM_FLAG_UPDATE_COMPOSITE_VOLUME;
	}
}

// Set audio system voice volume
void Audio_SetVoicePitchbend(u16 channel, u16 voice, u16 pitchbend)
{
	Audio_System.channel[channel].voice[voice].pitchbend = pitchbend;
}

// Set a voice's instrument parameters
void Audio_SetInstrument(u16 channel, u16 voice, const AL_Instrument *instrument)
{
	Audio_System.channel[channel].voice[voice].pInstrument = instrument;
}

// Key a note on a voice on
//  Note: Use FASTCODE attribute to ensure that division is calculated
//  using faster 64-bit multiplication with inverted value AUDIO_UPDATE_FREQUENCY.
FASTCODE void Audio_KeyOn(u16 channel, u16 voice, u16 frequency, u16 velocity)
{
	AL_Voice *pVoice = &Audio_System.channel[channel].voice[voice];

	// Frequency calculations
	// samplerstepspersecond=samplerstepspercycle*cyclespersecond
	u32 samplerstepspersecond = (u32)frequency << 16;
    
	// stepsperupdate=stepspersecond/updatespersecond
//	pVoice->delta = samplerstepspersecond/AUDIO_UPDATE_FREQUENCY;
	pVoice->delta = samplerstepspersecond >> AUDIO_UPDATE_FREQUENCY_SHIFT;
    
	// Zero pitch bend for new note
	pVoice->pitchbend=0;

	// Potential Optimization:  Use a more efficient volume multiply routine with early exit

	//pVoice->position=0;       // commented out to maintain phase if interrupted playing channel
	//pVoice->output_value=0;   // commented out to prevent audible click

	const AL_Instrument *pInstrument = pVoice->pInstrument;

	// Calculate overall voice volume (system*channel*voice*velocity)
	u16 compositevelocityvolume = (u16)((u32)pVoice->compositevolume * (u32)velocity) >> 8;

	// Potential Optimization:  Only update when velocity or adsr are different 
	//                          (cache compositevolume and instrument)

	// Scale ADSR by voice velocity composite volume 
	AL_ADSR *pADSR_instrument = pInstrument->pADSR;
	AL_ADSR *pADSR_voice = &pVoice->ADSR_composite;
	pADSR_voice->attack_delta  = (u16)((u32)pADSR_instrument->attack_delta  * (u32)compositevelocityvolume) >> 8;
	pADSR_voice->attack_peak   = (u16)((u32)pADSR_instrument->attack_peak   * (u32)compositevelocityvolume) >> 8;
	pADSR_voice->decay_delta   = (u16)((u32)pADSR_instrument->decay_delta   * (u32)compositevelocityvolume) >> 8;
	pADSR_voice->sustain_value = (u16)((u32)pADSR_instrument->sustain_value * (u32)compositevelocityvolume) >> 8;
	pADSR_voice->release_delta = (u16)((u32)pADSR_instrument->release_delta * (u32)compositevelocityvolume) >> 8;

	// Start ADSR
	pVoice->ADSR_phase='a';
	pVoice->ADSR_volume=pADSR_voice->attack_delta;

	// Start vibrato
	pVoice->vibrato = pVoice->vibrato_delta = pInstrument->vibrato_delta;

	// Scale tremolo by voice velocity composite volume and start tremolo
	pVoice->tremolo = pVoice->tremolo_delta = (u16)((u32)pInstrument->tremolo_delta * (u32)compositevelocityvolume) >> 8;
	pVoice->tremolo_amplitude = (u16)((u32)pInstrument->tremolo_amplitude * (u32)compositevelocityvolume) >> 8;

	// Set the initial sample volume
	pVoice->sample_volume = pVoice->ADSR_volume + pVoice->tremolo;

	// Start the voice playing
	pVoice->playing=True;
}

// Key a note on a voice off (trigger sound decay)
void Audio_KeyOff(u16 channel, u16 voice)
{
	AL_Voice *pVoice = &Audio_System.channel[channel].voice[voice];
	if (pVoice->playing) pVoice->ADSR_phase='r';
}

// Stop and silence a voice
void Audio_StopVoice(u16 channel, u16 voice)
{
	// Stopping a voice immediately stops playing a sound
	// an audible click is possible
	Audio_System.channel[channel].voice[voice].playing=False;
}

// Shutdown audio library and release resources
void Audio_Release(void)
{
    // Nothing to do since audio library is statically allocated 
    // and update should no longer be called
}

// Initialize FIFO
void Audio_FifoInitialize(AL_FIFO* fifo)
{
	fifo->write=0;
	fifo->read=0;
	fifo->buf[AUDIO_FIFO_SIZE-1] = 128; // last value
}

// Read an element from the FIFO - called from the interrupt service
u8 Audio_FifoRead(AL_FIFO* fifo)
{
	// Get read index
	int r = fifo->read;

	// FIFO is empty
	if (r == fifo->write)
	{
		// Get last value
		return fifo->buf[(r - 1) & AUDIO_FIFO_MASK];
	}
	else
	{
		// Return current data
		u8 data = fifo->buf[r];

		// Compiler barrier
		cb();
        
		// Write new read index
		fifo->read = (r + 1) & AUDIO_FIFO_MASK;
        
		// Return data
		return data;
	}
}

// Write an element to the FIFO - called from the main code
void Audio_FifoWrite(AL_FIFO* fifo, u8 data)
{
	// get current and next write index
	int w = fifo->write;
	int w2 = (w + 1) & AUDIO_FIFO_MASK;

	// Check if FIFO is not full
	if (w2 != fifo->read)
	{
		// Set new data
		fifo->buf[w] = data;

		// Compiler barrier
		cb();

		// Set new write index
		fifo->write = w2;
	}
}

// Check if FIFO is not full (returns True if writing is possible)
Bool Audio_FifoIsFree(AL_FIFO* fifo)
{
	return fifo->read != ((fifo->write + 1) & AUDIO_FIFO_MASK);
}

// Initialize music player
void Midi_PlayerInitialize(void)
{
	Midi_Player.samplespertick = 0xffff;
	Midi_Player.sample_timer=0xffff;
	Midi_Player.tick_timer=0xffff;
	Midi_Player.pevent=NULL;
}

// Start playing a mini midi song
void Midi_PlayerStartSong(u16 channel, u8* psong)
{
	// Save channel
	Midi_Player.channel=channel;

	// Set tempo
	Midi_Player.samplespertick = AUDIO_SHAPE_DIVIDER;
    
	// start song
	Midi_Player.pevent=psong;
	Midi_Player.first=True;
	Midi_Player.tick_timer=1;   // starts next update
}

// Stop playing a mini midi song
void Midi_PlayerStopSong(void)
{
	// Silence voices on the midi player channel
	int voice;
	for(voice=0; voice<AUDIO_VOICES; voice++)
	{
		Audio_KeyOff(Midi_Player.channel,voice);
	}

	Midi_Player.pevent=NULL;
	Midi_Player.first=False;
}

// Return true if mini midi player is playing a song
u16 Midi_PlayerPlayingSong(void)
{
	return Midi_Player.pevent != NULL;
}

// MIDI update to be called at 100 Hz (every 10ms)
void Midi_PlayerUpdate(void)
{
	int voice;

	MIDI_Player* mp = &Midi_Player;
	if (mp->pevent)
	{
		if (--mp->sample_timer == 0)
		{
			mp->sample_timer = mp->samplespertick;
			mp->tick_timer--;
			while(mp->tick_timer == 0)
			{
				if (mp->first)
				{
					// First iteration, skip pending event to first delay 
					// (Could be optimized if tick parsing was in a routine and called from song start)
					mp->first = False;
				}
				else            
				{
					// Parse event at index
					u8 d0 = *mp->pevent++;
					u8 d1 = *mp->pevent++;

					// v1
					//u16 note = d0 & 0x7f;
					//u16 velocity = (d1&0xfe);
					//u16 voice = ((d0>>6)&0x02)|(d1&0x01);
					//u16 volume = velocity;

					// v2
					u16 note = d0 & 0x7f;
					u16 velocity = (d1 & 0xfc);
					u16 voice = ((d0 >> 5) & 0x04) | (d1 & 0x03);
					u16 volume = velocity + 3;

					// Velocity determines note on from note off
					if (velocity>0)
					{
						// Note on
						u16 frequency = Midi_NoteFrequencies[note];
						Audio_KeyOn(mp->channel, voice, frequency, volume);
					}
					else
					{
						// Note off
						Audio_KeyOff(mp->channel, voice);
					}
				}
                
				u8 tick = *mp->pevent++;
				switch (tick)
				{
				// End of song
				case 0xff:
					// Key off all voices
					for(voice=0; voice<AUDIO_VOICES; voice++)
					{
						Audio_KeyOff(mp->channel, voice);
					}
					Midi_PlayerInitialize();
					return;

				// Extended tick
				case 0xfe:
					tick = *mp->pevent++;
					tick += ((u16)*mp->pevent++) << 8;
					break;

				default:
					mp->tick_timer = tick;
				}
			}
		}
	}
}

// Release music player
void Midi_PlayerRelease(void)
{
	Midi_PlayerStopSong();
}

// Minimum 10ms
#define ADSR_RAMP_MS(ms) (256/((ms)/10))

// ADSR parameters: attack delta, attack peak, decay delta, sustain value, release delta
const AL_ADSR Audio_ADSR_On =     {256, 255, 0, 255, -255};
const AL_ADSR Audio_ADSR_Piano =  {256, 255, ADSR_RAMP_MS(050),255*.60,ADSR_RAMP_MS(900)};  
const AL_ADSR Audio_ADSR_8bit =   {ADSR_RAMP_MS(50), 255, ADSR_RAMP_MS(300), 255*.66, ADSR_RAMP_MS(900)};  
const AL_ADSR Audio_ADSR_Violin = {ADSR_RAMP_MS(150),255, ADSR_RAMP_MS(300), 255*.76, ADSR_RAMP_MS(90)};  
const AL_ADSR Audio_ADSR_Flute =  {ADSR_RAMP_MS(350),255, ADSR_RAMP_MS(300), 255*.66, ADSR_RAMP_MS(90)};  
const AL_ADSR Audio_ADSR_Sax =    {ADSR_RAMP_MS(350),255, ADSR_RAMP_MS(300), 255*.66, ADSR_RAMP_MS(90)};  
const AL_ADSR Audio_ADSR_Tom =    {128, 255, ADSR_RAMP_MS(250) ,  0, 0};  
const AL_ADSR Audio_ADSR_Snare =  {128, 255, ADSR_RAMP_MS(3000),  0, 0};  
const AL_ADSR Audio_ADSR_Cymbol = {128, 255, ADSR_RAMP_MS(650) ,  0, 0};  
const AL_ADSR Audio_ADSR_Hihat =  {128, 255, ADSR_RAMP_MS(1000), 64, ADSR_RAMP_MS(150)};  
    
// Instruments: sampler, ADSR, vibrato amplitude, vibrato delta, tremolo amplitude, tremolo delta
const AL_Instrument Audio_Instrument_Sine =   { Audio_SineSampler,       (AL_ADSR *) &Audio_ADSR_On,         0,0,    0,0};
const AL_Instrument Audio_Instrument_Triangle={ Audio_TriangleSampler,   (AL_ADSR *) &Audio_ADSR_On,         0,0,    0,0};
const AL_Instrument Audio_Instrument_Square = { Audio_SquareSampler,     (AL_ADSR *) &Audio_ADSR_On,         0,0,    0,0};
const AL_Instrument Audio_Instrument_Sawtooth={ Audio_SawtoothSampler,   (AL_ADSR *) &Audio_ADSR_On,         0,0,    0,0};
const AL_Instrument Audio_Instrument_4OctaveSine= { Audio_4OctaveSineSampler,(AL_ADSR *) &Audio_ADSR_On,     0,0,    0,0};
const AL_Instrument Audio_Instrument_4OctaveSawtooth= { Audio_4OctaveMixSampler,(AL_ADSR *) &Audio_ADSR_On,  0,0,    0,0};
const AL_Instrument Audio_Instrument_Piano =  { Audio_SineSampler,       (AL_ADSR *) &Audio_ADSR_Piano,      0,0,    0,0};
const AL_Instrument Audio_Instrument_Organ =  { Audio_TriangleSampler,   (AL_ADSR *) &Audio_ADSR_Piano,      0,0,    0,0};
const AL_Instrument Audio_Instrument_FatOrgan={ Audio_4OctaveMixSampler, (AL_ADSR *) &Audio_ADSR_Piano,      0,0,    0,0};
const AL_Instrument Audio_Instrument_Synth =  { Audio_SawtoothSampler,   (AL_ADSR *) &Audio_ADSR_Piano,      0,0,    0,0};
const AL_Instrument Audio_Instrument_8bit =   { Audio_SquareSampler,     (AL_ADSR *) &Audio_ADSR_8bit,       0,0,    0,0};
const AL_Instrument Audio_Instrument_Vibraphone={ Audio_SineSampler,     (AL_ADSR *) &Audio_ADSR_Piano,      4<<4,1<<4,    2<<4,1<<4};
const AL_Instrument Audio_Instrument_Violin = { Audio_SawtoothSampler,   (AL_ADSR *) &Audio_ADSR_Violin,     48,4,    32,4};
const AL_Instrument Audio_Instrument_Violin2= { Audio_SawtoothSampler,   (AL_ADSR *) &Audio_ADSR_Violin,     4<<4,1<<4,    2<<4,1<<4};
const AL_Instrument Audio_Instrument_Drum =   { Audio_Noise2Sampler,     (AL_ADSR *) &Audio_ADSR_Piano,      0,0,    0,0};
const AL_Instrument Audio_Instrument_Hihat =  { Audio_Noise2Sampler,     (AL_ADSR *) &Audio_ADSR_Hihat,      5<<4,-1<<4,   0,0};
const AL_Instrument Audio_Instrument_Snare =  { Audio_Noise2Sampler,     (AL_ADSR *) &Audio_ADSR_Tom,        1000<<4,-1,   0,0};
const AL_Instrument Audio_Instrument_Cymbol = { Audio_Noise2Sampler,     (AL_ADSR *) &Audio_ADSR_Cymbol,     50<<4,-5<<4,  0,0};
const AL_Instrument Audio_Instrument_Tom =    { Audio_SineSampler,       (AL_ADSR *) &Audio_ADSR_Tom,        100<<4,-1<<4, 0,0};
const AL_Instrument Audio_Instrument_Flute =  { Audio_TriangleSampler,   (AL_ADSR *) &Audio_ADSR_Flute,      4<<4,1<<4,    2<<4,1<<4};
const AL_Instrument Audio_Instrument_Sax =    { Audio_SawtoothSampler,   (AL_ADSR *) &Audio_ADSR_Sax,        4<<4,1<<4,    2<<4,1<<4};
const AL_Instrument Audio_Instrument_Xylophone={ Audio_SineSampler,      (AL_ADSR *) &Audio_ADSR_Tom,        -1,10,  0,0};
