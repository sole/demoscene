/*
	Copyright 2009 Soledad Penades http://soledadpenades.com

	This file is part of xplsv_to_the_beat

	xplsv_to_the_beat is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License version 3 only, as published
	by the Free Software Foundation.

	xplsv_to_the_beat is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with xplsv_to_the_beat.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOROLLET_H
#define SOROLLET_H

// Data types //

typedef struct
{
	float value;
	float start_time;
	float release_start_time;

	int state;

	float attack_time;
	float decay_time;
	float sustain_level;
	float release_time;

} t_adsr;

typedef struct
{
	// Filter #1 (Low band)

	float  lf;       // Frequency
	float  f1p0;     // Poles ...
	float  f1p1;
	float  f1p2;
	float  f1p3;

	// Filter #2 (High band)

	float  hf;       // Frequency
	float  f2p0;     // Poles ...
	float  f2p1;
	float  f2p2;
	float  f2p3;

	// Sample history buffer

	float  sdm1;     // Sample data minus 1
	float  sdm2;     //                   2
	float  sdm3;     //                   3

	// Gain Controls

	float  lg;       // low  gain
	float  mg;       // mid  gain
	float  hg;       // high gain

} t_eqstate;

typedef struct
{
    // osc mixing balance; 0.5 = equal volume for both, 0.1 = 0.1*OSC1 + (1-0.1)*OSC2
    float oscillator_mix;

    // Misc
    float level;
	int param_note;
	float param_note_volume;
	float sampling_rate;
	int use_stereo;

    void (*osc1_function)(float*, int, float, int, int);
    void (*osc2_function)(float*, int, float, int, int);

    float osc1_phase, osc2_phase;
    unsigned int osc1_octave, osc2_octave;

	// Noise?
	float noise_level;

	// Filter
	unsigned int filter_type;
	float	filter_frequency;
	float	filter_resonance;
	float	filter_xn[3];
	float	filter_yn[3];
	float	filter_a1, filter_a2, filter_a3, filter_b1, filter_b2, filter_c, filter_csquare;

	// Saturate
	float	saturate_max;
	char	saturate_active;

	// EQ
	char		eq_active;
	t_eqstate	eq_state;

	// Bass boost
	char 		bass_boost_active;
	float		bass_boost_multiplier;

	// Envelopes
	char	amp_envelope_active;
	t_adsr	amp_envelope;
	char	pitch_envelope_active;
	t_adsr	pitch_envelope;
	char	filter_freq_envelope_active;
	t_adsr	filter_freq_envelope;

} t_sorollet_synth;

typedef struct
{
	unsigned char note;
	float volume;
} t_sorollet_pattern_cell;

typedef struct
{
	unsigned int num_rows;
	t_sorollet_pattern_cell** data;
} t_sorollet_pattern;

typedef struct
{
	unsigned char	bpm;
	unsigned char	speed;
	unsigned char	num_channels;
	float			frames_per_second;
	float			seconds_per_row;

	unsigned char	order_list_length;
	unsigned char*	order_list;

	unsigned char	num_patterns;
	t_sorollet_pattern*	patterns;

	unsigned char	current_row;
	unsigned char	current_order;

} t_sorollet_song;

// ~~~~~~~ Enums ~~~~~~~~~~~~ //

enum filter_types
{
	FILTER_TYPE_NONE,
	FILTER_TYPE_LOW_PASS,
	FILTER_TYPE_HIGH_PASS
};

enum adsr_states
{
	ADSR_ATTACK,
	ADSR_DECAY,
	ADSR_SUSTAIN,
	ADSR_RELEASE,
	ADSR_DONE
};

enum waves
{
	WAVE_SINE, //0
	WAVE_TRIANGLE, // 1
	WAVE_SQUARE, // 2
	WAVE_SAWTOOTH // 3
};

// ~~~~~~~ Functions ~~~~~~~~ //

extern int sorollet_init(unsigned int sampling_rate, unsigned int format, unsigned char audio_channels, unsigned int buffer_size);

extern int sorollet_load_song_from_array(char* song);

extern int sorollet_play(float t);

extern void sorollet_get_buffer(float *buffer, int position, int num_samples);

extern int sorollet_get_current_order();
extern int sorollet_get_current_row();
extern int sorollet_get_current_pattern();
extern unsigned char sorollet_get_channel_note(int i);


void sorollet_synth_init(t_sorollet_synth* synth);

int sorollet_synth_get_buffer(t_sorollet_synth* synth, float *buffer, int position, int num_samples, float t);

void sorollet_synth_send_note(t_sorollet_synth* synth, int note, float volume);

void sorollet_synth_send_release(t_sorollet_synth* synth);

void sorollet_synth_send_note_cut(t_sorollet_synth* synth);

float sorollet_synth_note_to_frequency(int note, int octave);

void sorollet_synth_prepare_filter(t_sorollet_synth* synth, float freq);


void sorollet_osc_whitenoise(float *buffer, int position, float frequency, int num_samples, int use_stereo);

void sorollet_osc_sine_wave(float *buffer, int position, float frequency, int num_samples, int use_stereo);

void sorollet_osc_triangle_wave(float *buffer, int position, float frequency, int num_samples, int use_stereo);

void sorollet_osc_square_wave(float *buffer, int position, float frequency, int num_samples, int use_stereo);

void sorollet_osc_sawtooth_wave(float *buffer, int position, float frequency, int num_samples, int use_stereo);


void sorollet_adsr_init(t_adsr* adsr);
void sorollet_adsr_set_values(t_adsr* adsr, float aTime, float dTime, float sLevel, float rTime);
void sorollet_adsr_attack(t_adsr* adsr, float startTime);
void sorollet_adsr_release(t_adsr* adsr, float releaseStartTime);
float sorollet_adsr_update(t_adsr* adsr, float time);

float sorollet_saturate(float value, float saturate_max);

void sorollet_eq_init(t_eqstate* es, int lowfreq, int highfreq, int mixfreq);
float sorollet_eq_update(t_eqstate* es, float sample);

float sorollet_bass_boost(float sample, float multiplier);

float sorollet_char_to_float(unsigned char value, float out_min, float out_max);

typedef void (*sorollet_osc_function_ptr)(float*, int, float, int, int);
sorollet_osc_function_ptr sorollet_enum_to_wave(unsigned int i);

#endif


