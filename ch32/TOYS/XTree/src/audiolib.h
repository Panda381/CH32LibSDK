
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

#ifdef __cplusplus
extern "C" {
#endif

// Derived definitions
#define	AUDIO_VOICES		(1<<AUDIO_VOICES_POW2)		// number of voices per channel
#define	AUDIO_FIFO_SIZE		(1<<AUDIO_FIFO_SIZE_POW2)	// audio FIFO size in bytes
#define AUDIO_FIFO_MASK		(AUDIO_FIFO_SIZE-1)		// mask of FIFO index
#define AUDIO_SHAPE_DIVIDER	(AUDIO_UPDATE_FREQUENCY/100)	// audio shape update divider (100 Hz or update every 10ms)
#define AUDIO_TIMER_PRESCALER	(HCLK_PER_US*1000000/(256*AUDIO_UPDATE_FREQUENCY)) // Audio Timer Prescaler (round down, to get min. 256 timer cycles per sample)
								// = 24*1000000/(256*32768) = 2
								// Timer clock: 24000000/2 = 12000000 Hz
								// update frequency would be: 24000000/(2*256) = 46875 Hz
#define AUDIO_TIMER_RELOAD (HCLK_PER_US*1000000/(AUDIO_TIMER_PRESCALER*AUDIO_UPDATE_FREQUENCY)-1) // Audio Timer reload value
								// = 24*1000000/(2*32768)-1 = 365
								// - can be higher than 256, to get more precise sampling rate
								// real update frequency: 24000000/(2*(365+1)) = 32786 Hz

// ADSR envelope descriptor (ADSR = "Attack–Decay–Sustain–Release")
typedef struct {
	u16	attack_delta;		// Ramp from 0 to max
	u16	attack_peak;		// Attack peak value
	u16	decay_delta;		// Ramp from max to sustain value
	u16	sustain_value;		// Sustain value
	u16	release_delta;		// Ramp from sustain to 0
} AL_ADSR;

// Instrument descriptor
typedef s8 (*sample_hander)(u16 index);		// waveform samples
typedef struct {
	sample_hander	sample;			// waveform sampler
	AL_ADSR*	pADSR;			// pointer to ADSR envelope descriptor
	u16		vibrato_amplitude;	// Vibrato amplitude (4 bits fraction)
	s16		vibrato_delta;		// Vibrato delta (4 bits fraction)
	u16		tremolo_amplitude;	// Tremolo amplitude (4 bits fraction)
	s16		tremolo_delta;		// Tremolo delta (4 bits fraction)
} AL_Instrument;

// A voice plays a single instrument
typedef struct {
	u16		position;		// Position in wave table fixed point 0 to 1
	u16		delta;			// Derived from frequency and length of wave table
	u16		pitchbend;		// Pitch bend (delta on delta)

	u16		volume;			// 8 bit volume 
	u16		compositevolume;	// voice_volume * channel_volume * master_volume
	u16		sample_volume;		// The volume applied to samples
	s16		output_value;		// Value

	u8		playing;		// True if voice is playing
 
	u8		ADSR_phase;		// Current phase
	s16		ADSR_volume;		// Current volume of the envelope
	AL_ADSR		ADSR_composite;		// ADSR settings scaled by composite volume at keyon

	s16		vibrato;		// Vibrato value
	s16		vibrato_delta;		// Vibrato delta

	s16		tremolo;		// Tremolo value
	s16		tremolo_delta;		// Tremolo delta
	s16		tremolo_amplitude;	// Tremolo amplitude scaled by composite volume at keyon

	const AL_Instrument* pInstrument;	// Pointer to instrument
	u8		flags;          
} AL_Voice;

// A channel is a polyphonic physical output (a single PWM pin)
typedef struct {
	AL_Voice	voice[AUDIO_VOICES];	// Voices in the channel
	u16		volume;			// Channel set volume
	u16		compositevolume;	// Channel volume * master volume
	s16		output_value;		// Value of all voices in the channel
	u8		flags;
} AL_Channel;

// Audio Library FIFO
typedef struct {
	u8		buf[AUDIO_FIFO_SIZE];	// FIFO Buffer
	volatile int	write;			// write index
	volatile int	read;			// read index
} AL_FIFO;

// Entire audio system
#define AL_SYSTEM_FLAG_UPDATE_VOLUME		B0
#define AL_SYSTEM_FLAG_UPDATE_COMPOSITE_VOLUME	B1
typedef struct {
	AL_Channel	channel[AUDIO_CHANNELS]; // Polyphonic sound channels
	u16		volume;			// Master volume
	u16		envelopedivider;	// For lower frequency shaping processing
	u8		flags;			// flags AL_SYSTEM_FLAG_*
	AL_FIFO		fifo;			// fifo    
} AL_System;

// MIDI player
typedef struct {
	u16		channel;		// Channel song is playing on
	u16		samplespertick;		// Samples per 10ms mini-midi tick
	u16		sample_timer;		// Sample timer
	u16		tick_timer;		// Ticks until next event
	u8*		pevent;			// Pointer to next event, NULL if not playing
	u8		first;			// Flag needed for first event
} MIDI_Player;

// Audio system instance
extern AL_System Audio_System;

// MIDI player instance
extern MIDI_Player Midi_Player;

// Quarter sintab, signed, 0 center
extern const s8 Audio_QuarterSinTab[256];

// MIDI note frequencies C1 through G9
extern const u16 Midi_NoteFrequencies[];

// seed of audio noise sampler
extern s8 Audio_Noise1Value;
extern s8 Audio_Noise2Value;

// Audio noise sampler - tinny white noise
s8 Audio_Noise1Sampler(u16 index);

// Audio noise 2 sampler - midtone white noise, index changes pitch
s8 Audio_Noise2Sampler(u16 index);

// Robot sampler - midtone robotfrequency changes pitch
s8 Audio_RobotSampler(u16 index);

// Sawtooth sampler
s8 Audio_SawtoothSampler(u16 index);

// Square wave sampler
s8 Audio_SquareSampler(u16 index);

// Triangle sampler
s8 Audio_TriangleSampler(u16 index);

// Sine sampler
s8 Audio_SineSampler(u16 index);

// 4-Octave sine sampler
s8 Audio_4OctaveSineSampler(u16 index);

// 4-Octave sawtooth sampler
s8 Audio_4OctaveMixSampler(u16 index);

// Multiply an 8 bit unsigned volume by an 8 bit signed sample, returning a signed modulated sample
s16 Audio_VolumeSampleMultiply(u16 u, s16 s);

// Multiply 8 bit unsigned volumes by one another, returning an 8 bit volume
u16 Audio_VolumeVolumeMultiply(u16 v1, u16 v2);

// Initialize audio library
void Audio_Initialize(void);

// Audio update
void Audio_Update(void);

// Get the value of an output pin
u8 Audio_GetChannelValue(u16 channel);

// Set audio system master volume
void Audio_SetMasterVolume(u16 volume);

// Set audio system channel volume
void Audio_SetChannelVolume(u16 channel, u16 volume);

// Set audio system voice volume
void Audio_SetVoiceVolume(u16 channel, u16 voice, u16 volume);

// Set audio system voice volume
void Audio_SetVoicePitchbend(u16 channel, u16 voice, u16 pitchbend);

// Set a voice's instrument parameters
void Audio_SetInstrument(u16 channel, u16 voice, const AL_Instrument *instrument);

// Key a note on a voice on
FASTCODE void Audio_KeyOn(u16 channel, u16 voice, u16 frequency, u16 velocity);

// Key a note on a voice off (trigger sound decay)
void Audio_KeyOff(u16 channel, u16 voice);

// Stop and silence a voice
void Audio_StopVoice(u16 channel, u16 voice);

// Shutdown audio library and release resources
void Audio_Release(void);

// Initialize FIFO
void Audio_FifoInitialize(AL_FIFO* fifo);

// Read an element from the FIFO - called from the interrupt service
u8 Audio_FifoRead(AL_FIFO* fifo);

// Write an element to the FIFO - called from the main code
void Audio_FifoWrite(AL_FIFO* fifo, u8 data);

// Check if FIFO is not full (returns True if writing is possible)
Bool Audio_FifoIsFree(AL_FIFO* fifo);

// Initialize music player
void Midi_PlayerInitialize(void);

// Start playing a mini midi song
void Midi_PlayerStartSong(u16 channel, u8* psong);

// Stop playing a mini midi song
void Midi_PlayerStopSong(void);

// Return true if mini midi player is playing a song
u16 Midi_PlayerPlayingSong(void);

// MIDI update to be called at 100 Hz (every 10ms)
void Midi_PlayerUpdate(void);

// Release music player
void Midi_PlayerRelease(void);

// ADSR parameters
extern const AL_ADSR Audio_ADSR_On;
extern const AL_ADSR Audio_ADSR_Piano;
extern const AL_ADSR Audio_ADSR_8bit;
extern const AL_ADSR Audio_ADSR_Violin;
extern const AL_ADSR Audio_ADSR_Flute;
extern const AL_ADSR Audio_ADSR_Sax;
extern const AL_ADSR Audio_ADSR_Tom;
extern const AL_ADSR Audio_ADSR_Snare;
extern const AL_ADSR Audio_ADSR_Cymbol;
extern const AL_ADSR Audio_ADSR_Hihat;
    
// Instruments
extern const AL_Instrument Audio_Instrument_Sine;
extern const AL_Instrument Audio_Instrument_Triangle;
extern const AL_Instrument Audio_Instrument_Square;
extern const AL_Instrument Audio_Instrument_Sawtooth;
extern const AL_Instrument Audio_Instrument_4OctaveSine;
extern const AL_Instrument Audio_Instrument_4OctaveSawtooth;
extern const AL_Instrument Audio_Instrument_Piano;
extern const AL_Instrument Audio_Instrument_Organ;
extern const AL_Instrument Audio_Instrument_FatOrgan;
extern const AL_Instrument Audio_Instrument_Synth;
extern const AL_Instrument Audio_Instrument_8bit;
extern const AL_Instrument Audio_Instrument_Vibraphone;
extern const AL_Instrument Audio_Instrument_Violin;
extern const AL_Instrument Audio_Instrument_Violin2;
extern const AL_Instrument Audio_Instrument_Drum;
extern const AL_Instrument Audio_Instrument_Hihat;
extern const AL_Instrument Audio_Instrument_Snare;
extern const AL_Instrument Audio_Instrument_Cymbol;
extern const AL_Instrument Audio_Instrument_Tom;
extern const AL_Instrument Audio_Instrument_Flute;
extern const AL_Instrument Audio_Instrument_Sax;
extern const AL_Instrument Audio_Instrument_Xylophone;

#ifdef __cplusplus
}
#endif
