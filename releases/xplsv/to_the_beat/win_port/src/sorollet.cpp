#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sorollet.h"
#include "utils.h"
#include "sys/msys_libc.h"
#include "sys/msys_malloc.h"
#include "sys/msys_random.h"

// ~~~~~~~ sorollet globals ~~~~~~~~

static unsigned int sorollet_sampling_rate;
static double sorollet_inv_sampling_rate;
static float sorollet_inv_rand_max;
//unsigned int sorollet_format;
unsigned char sorollet_audio_channels; // 1 or 2 (mono or stereo)
unsigned int sorollet_buffer_size;
unsigned char sorollet_num_synths;
t_sorollet_synth *sorollet_synths;
float sorollet_last_played_time;
t_sorollet_song sorollet_song;

#define M_PI   3.1415927f
#define M_PI_2 (0.5f*3.1415927f)


static double sorollet_vsa = (1.0 / 4294967295.0);   // Very small amount (Denormal Fix) (For EQ)

int sorollet_init(unsigned int sampling_rate, /*unsigned int format,*/ unsigned char audio_channels, unsigned int buffer_size)
{
//    int i;
	
	sorollet_last_played_time = -1;

    sorollet_sampling_rate = sampling_rate;
    sorollet_inv_sampling_rate = 1.0f / sampling_rate;
	sorollet_inv_rand_max = 1.0f / (float)RAND_MAX;
    //sorollet_format = format;
    sorollet_audio_channels = audio_channels;
    sorollet_buffer_size = buffer_size;

    return 0;
}

int sorollet_load_song_from_array(char* song)
{
	int i = 0, j, row, col;
	int size;
	
	size = sizeof(song);
	
	while(i < (size - 1))
	{
		// bpm, speed, num channels
		sorollet_song.bpm	= song[i]; i++;
		sorollet_song.speed = song[i]; i++;
		sorollet_num_synths = song[i]; i++;
		
		sorollet_song.frames_per_second = sorollet_song.bpm * 0.4f;
		sorollet_song.seconds_per_row = sorollet_song.speed / sorollet_song.frames_per_second;
		
		//printf("Lo que lei %d,%d,%d, SPR= %f\n", sorollet_song.bpm, sorollet_song.speed, sorollet_num_synths, sorollet_song.seconds_per_row);
		
		// Init requested synths
		if(sorollet_synths)
	    {
	        msys_mallocFree(sorollet_synths);
	    }

	    sorollet_synths = (t_sorollet_synth*)msys_mallocAlloc(sizeof(t_sorollet_synth) * sorollet_num_synths);

	    for(j = 0; j < sorollet_num_synths; j++)
	    {
	        sorollet_synth_init(&sorollet_synths[j]);
	    }
	
	
		// Order list
		sorollet_song.order_list_length = song[i]; i++;
		
		if(sorollet_song.order_list)
		{
			msys_mallocFree(sorollet_song.order_list);
		}
		
		sorollet_song.order_list = (unsigned char*) msys_mallocAlloc(sizeof(unsigned char) * sorollet_song.order_list_length);
		
		for(j = 0; j < sorollet_song.order_list_length; j++)
		{
			sorollet_song.order_list[j] = song[i]; i++;
			//printf("Order list %d: pattern %d\n", j, sorollet_song.order_list[j]);
		}
	
		
		// Patterns
		sorollet_song.num_patterns = song[i]; i++;
		
		if(sorollet_song.patterns)
		{
			msys_mallocFree(sorollet_song.patterns);
		}
		
		sorollet_song.patterns = (t_sorollet_pattern*) msys_mallocAlloc(sizeof(t_sorollet_pattern) * sorollet_song.num_patterns);
		
		for(j = 0; j < sorollet_song.num_patterns; j++)
		{
			sorollet_song.patterns[j].num_rows = (unsigned char) song[i]; i++;
			sorollet_song.patterns[j].data = (t_sorollet_pattern_cell**) msys_mallocAlloc(sizeof(t_sorollet_pattern_cell*) * sorollet_song.patterns[j].num_rows);
			
			for(row = 0; row < (int)sorollet_song.patterns[j].num_rows; row++)
			{
				sorollet_song.patterns[j].data[row] = (t_sorollet_pattern_cell*) msys_mallocAlloc(sizeof(t_sorollet_pattern_cell) * sorollet_num_synths);
				
				for(col = 0; col < sorollet_num_synths; col++)
				{
					sorollet_song.patterns[j].data[row][col].note = song[i]; i++;
					sorollet_song.patterns[j].data[row][col].volume = sorollet_char_to_float(song[i], 0, 1); i++;
				}
			}
		}
		
		// Synths config
		for(j = 0; j < sorollet_num_synths; j++)
		{
			sorollet_synths[j].oscillator_mix = sorollet_char_to_float(song[i], 0, 1); i++;
			sorollet_synths[j].level = sorollet_char_to_float(song[i], 0, 1); i++;
			
			// Osc1	
			sorollet_synths[j].osc1_function = sorollet_enum_to_wave(song[i]); i++;
			sorollet_synths[j].osc1_phase = sorollet_char_to_float(song[i], -M_PI_2, M_PI_2); i++;
			sorollet_synths[j].osc1_octave = song[i]; i++;
			
			// Osc2
			sorollet_synths[j].osc2_function = sorollet_enum_to_wave(song[i]); i++;
			sorollet_synths[j].osc2_phase = sorollet_char_to_float(song[i], -M_PI_2, M_PI_2); i++;
			sorollet_synths[j].osc2_octave = song[i]; i++;
			
			// Noise level
			sorollet_synths[j].noise_level = sorollet_char_to_float(song[i], 0, 1); i++;
			
			// Filter
			// type
			sorollet_synths[j].filter_type = song[i]; i++;
			// frequency
			sorollet_synths[j].filter_frequency = sorollet_char_to_float(song[i], 22, 300); i++;
			// resonance
			sorollet_synths[j].filter_resonance = sorollet_char_to_float(song[i], 0, 0.2f); i++;
			
			// Saturate
			sorollet_synths[j].saturate_active = song[i]; i++;
			sorollet_synths[j].saturate_max = sorollet_char_to_float(song[i], 0, 1); i++;
			
			// EQ
			sorollet_synths[j].eq_active = song[i]; i++;
			sorollet_synths[j].eq_state.lg = sorollet_char_to_float(song[i], 0, 10); i++;
			sorollet_synths[j].eq_state.mg = sorollet_char_to_float(song[i], 0, 10); i++;
			sorollet_synths[j].eq_state.hg = sorollet_char_to_float(song[i], 0, 10); i++;
			
			// Bass boost
			sorollet_synths[j].bass_boost_active = song[i]; i++;
			sorollet_synths[j].bass_boost_multiplier = sorollet_char_to_float(song[i], 0, 8); i++;
			
			
			// Envelopes
			float attack_time;
			float decay_time;
			float sustain_level;
			float release_time;
			
			// Amp envelope
			sorollet_synths[j].amp_envelope_active = song[i]; i++;
			attack_time = sorollet_char_to_float(song[i], 0, 16); i++;
			decay_time = sorollet_char_to_float(song[i], 0, 16); i++;
			sustain_level = sorollet_char_to_float(song[i], 0, 1); i++;
			release_time = sorollet_char_to_float(song[i], 0, 16); i++;
			
			sorollet_adsr_set_values(&sorollet_synths[j].amp_envelope, attack_time, decay_time, sustain_level, release_time);
			
			// Pitch envelope
			sorollet_synths[j].pitch_envelope_active = song[i]; i++;
			attack_time = sorollet_char_to_float(song[i], 0, 16); i++;
			decay_time = sorollet_char_to_float(song[i], 0, 16); i++;
			sustain_level = sorollet_char_to_float(song[i], 0, 1); i++;
			release_time = sorollet_char_to_float(song[i], 0, 16); i++;
			
			sorollet_adsr_set_values(&sorollet_synths[j].pitch_envelope, attack_time, decay_time, sustain_level, release_time);
			
			// Filter frequency envelope
			sorollet_synths[j].filter_freq_envelope_active = song[i]; i++;
			attack_time = sorollet_char_to_float(song[i], 0, 16); i++;
			decay_time = sorollet_char_to_float(song[i], 0, 16); i++;
			sustain_level = sorollet_char_to_float(song[i], 0, 1); i++;
			release_time = sorollet_char_to_float(song[i], 0, 16); i++;
			
			sorollet_adsr_set_values(&sorollet_synths[j].filter_freq_envelope, attack_time, decay_time, sustain_level, release_time);
			
			// Precalc filter parameters if the envelope is not used
			if(!sorollet_synths[j].filter_freq_envelope_active)
			{
				sorollet_synth_prepare_filter(&sorollet_synths[j], sorollet_synths[j].filter_frequency);
			}
			
		}
		
		
		sorollet_song.current_row = 0;
		sorollet_song.current_order = 0; // AQUI
		sorollet_last_played_time = 0;
		
		return 0;
	}
	return -1;
}

int sorollet_play(float t)
{
	int i;
	unsigned char note;
	float volume;
	float elapsed;
	t_sorollet_synth* p_synth;
	t_sorollet_pattern* p_pattern;
	
	elapsed = t - sorollet_last_played_time;
	
	if(elapsed > sorollet_song.seconds_per_row)
	{
		// printf("%X\t", sorollet_song.current_row);
		
		p_pattern = &sorollet_song.patterns[sorollet_song.order_list[sorollet_song.current_order]];
		
		for(i = 0; i < sorollet_num_synths; i++)
		{
			p_synth = &sorollet_synths[i];
			
			note = p_pattern->data[sorollet_song.current_row][i].note;
			volume =  p_pattern->data[sorollet_song.current_row][i].volume;
			
			if(note != 0)
			{
				if(note == 255)
				{
					sorollet_synth_send_release(p_synth);
					// I'm not too convinced about this here
					// it really should be inside sorollet_synth_send_release
					// but I didn't want to propagate t into another function...
					if(p_synth->amp_envelope_active)
					{
						sorollet_adsr_release(&p_synth->amp_envelope, t);
					}
					
					if(p_synth->pitch_envelope_active)
					{
						sorollet_adsr_release(&p_synth->pitch_envelope, t);
					}
					
					if(p_synth->filter_freq_envelope_active)
					{
						sorollet_adsr_release(&p_synth->filter_freq_envelope, t);
					}
					//printf("=== ....");
				}
				else if(note == 254)
				{
					sorollet_synth_send_note_cut(p_synth);
					//printf("^^^ ....");
				}
				else
				{
					sorollet_synth_send_note(p_synth, note, p_pattern->data[sorollet_song.current_row][i].volume);
					// I'm not too convinced about this here
					// it really should be inside sorollet_synth_send_note
					// but I didn't want to propagate t into another function...
					if(p_synth->amp_envelope_active)
					{
						sorollet_adsr_attack(&p_synth->amp_envelope, t);
					}
					
					if(p_synth->pitch_envelope_active)
					{
						sorollet_adsr_attack(&p_synth->pitch_envelope, t);
					}
					
					if(p_synth->filter_freq_envelope_active)
					{
						sorollet_adsr_attack(&p_synth->filter_freq_envelope, t);
					}
					
					//printf("N%d %0.2f", note, volume);
				}
			}
			//else
			//{
			//	printf("... ....");
			//}
			//printf("\t");
		}
		//printf("\n");
		
		sorollet_song.current_row++;
		
		if(sorollet_song.current_row >= p_pattern->num_rows)
		{
			sorollet_song.current_order++;
			//printf("===================== %02d %f =======================\n", sorollet_song.current_order, t);
			
			// Always loop	
			/*if(sorollet_song.current_order >= sorollet_song.order_list_length)
			{
				sorollet_song.current_order = 0;
			}*/
			
			// or exit when finished
			if(sorollet_song.current_order >= sorollet_song.order_list_length)
			{
				return 1;
			}
			
			sorollet_song.current_row = 0;
		}
		
		sorollet_last_played_time = t;
		
		
	}
	return 0;
}

float tmp_buffer2[8192];

int sorollet_get_buffer(float *buffer, int position, int num_samples)
{
	if( num_samples > 8192 )
		int kk = 0;

    int i, j;
	float t = (float)(position * sorollet_inv_sampling_rate);
	int active;
	
	// All zeroes
	msys_memset(buffer, 0, sizeof(float) * num_samples);
	
	for (j = 0; j < sorollet_num_synths; j++)
	{	
		active = sorollet_synth_get_buffer(&sorollet_synths[j], tmp_buffer2, position, num_samples, t);
		
		if(active)
		{
			for (i = 0; i < num_samples ; i++)
			{
                buffer[i] += tmp_buffer2[i];
			}
		}
	}
	return 0;
}

int sorollet_get_current_order()
{
	return sorollet_song.current_order;
}

int sorollet_get_current_row()
{
	return sorollet_song.current_row;
}

int sorollet_get_current_pattern()
{
	return sorollet_song.order_list[sorollet_song.current_order];
}

unsigned char sorollet_get_channel_note(int i)
{
	return sorollet_song.patterns[sorollet_song.order_list[sorollet_song.current_order]].data[sorollet_song.current_row][i].note;
}

// ~~~~~~~ Synths ~~~~~~~

int sorollet_synth_init(t_sorollet_synth* synth)
{
	int i;
	
	
	synth->oscillator_mix = 0.5f;
	synth->level = 0.8f;
	synth->sampling_rate = (float)sorollet_sampling_rate;
	synth->use_stereo = (sorollet_audio_channels == 2);
	synth->param_note = 0;
	synth->osc1_function = sorollet_osc_square_wave;
	synth->osc2_function = sorollet_osc_triangle_wave;

	synth->osc1_octave = 3;
	synth->osc2_octave = 4;

	synth->osc1_phase = 0;
	synth->osc2_phase = 0;

	synth->noise_level = 100;

	
	synth->filter_type = FILTER_TYPE_LOW_PASS;
	synth->filter_frequency = 200.0f;
	synth->filter_resonance = 0.01f;
	
	for(i = 0; i < 3; i++)
	{
		synth->filter_xn[i] = 0;
		synth->filter_yn[i] = 0;
	}
	
	// Saturate max
	synth->saturate_active = 0;
	synth->saturate_max = 0.8f;
	
	// EQ
	sorollet_eq_init(&synth->eq_state, 880, 5000, sorollet_sampling_rate);
	synth->eq_state.lg = 2;
	synth->eq_state.mg = 0;
	synth->eq_state.hg = 0;
	synth->eq_active = 1;
	
	// bass boost
	synth->bass_boost_multiplier = 1;
	synth->bass_boost_active = 0;

    // envelopes
    synth->amp_envelope_active = 1;
	sorollet_adsr_init(&synth->amp_envelope);
	sorollet_adsr_set_values(&synth->amp_envelope, 0, 0.15f, 0, 0);
	
	synth->pitch_envelope_active = 0;
	sorollet_adsr_init(&synth->pitch_envelope);
	sorollet_adsr_set_values(&synth->pitch_envelope, 0.1f, 0.4f, 0.3f, 0.1f);

    return 0;
}


float tmp_buffer[8192];
float osc1_buffer[8192];
float osc2_buffer[8192];
float noise_buffer[8192];

int sorollet_synth_get_buffer(t_sorollet_synth* synth, float *buffer, int position, int num_samples, float t)
{
	if( num_samples > 8192 )
	{
		int kk = 0;
	}

    int i;
	float osc1_mix = 1 - synth->oscillator_mix;
//	float a1, a2, a3, b1, b2, c, csquare;
	float amp_envelope_value;
	int actual_note;
//	int octave_transposing;
    
    if(synth->param_note <= 0 || synth->level == 0)
    {
        return 0;
    }
    
    actual_note = synth->param_note;
    if(synth->pitch_envelope_active)
    {
		actual_note += msys_ifloorf(map(sorollet_adsr_update(&synth->pitch_envelope, t), 0, 1, -12, 12));
	}
    
    if(actual_note <= 0)
    return 0;
    
    if(synth->oscillator_mix > 0)
    {
		/// KKDEVACA
		synth->osc1_function(osc1_buffer, position + msys_ifloorf(synth->osc1_phase), sorollet_synth_note_to_frequency(actual_note, synth->osc1_octave), num_samples, synth->use_stereo);
    }
    
    if(synth->oscillator_mix < 1)
    {
		/// KKDEVACA
		synth->osc2_function(osc2_buffer, position + msys_ifloorf(synth->osc2_phase), sorollet_synth_note_to_frequency(actual_note, synth->osc2_octave), num_samples, synth->use_stereo);
    }
    
    
    if(synth->amp_envelope_active)
    {
		amp_envelope_value = sorollet_adsr_update(&synth->amp_envelope, t) /** synth->level*/;
	}
	else
	{
		amp_envelope_value = 1.0;
	}
		
	
	if(amp_envelope_value == 0)
	{
		return 0;
	}
	
	if(synth->param_note_volume < 1)
	{
		amp_envelope_value *= synth->param_note_volume;
	}
	
	if(synth->noise_level > 0)
	{
		sorollet_osc_whitenoise(noise_buffer, position, 0, num_samples, synth->use_stereo);
	}
	
	
	// Recalculate filter params only if filter envelope is active
	if(synth->filter_freq_envelope_active && synth->filter_type)
	{
		float freq;
		
		freq = synth->filter_frequency + map(sorollet_adsr_update(&synth->filter_freq_envelope, t), 0, 1,  0, 1000);
		
		if(freq < 0)
		{
			freq = 0;
		}
		
		sorollet_synth_prepare_filter(synth, freq);
		
	}
	
	/*// Prepare some params for the filter here
	if(synth->filter_type != FILTER_TYPE_NONE)
	{
		float freq;
		
		if(synth->filter_freq_envelope_active)
		{
			freq = synth->filter_frequency + map(sorollet_adsr_update(&synth->filter_freq_envelope, t), 0, 1,  0, 1000);
			
			if(freq < 0)
			{
				freq = 0;
			}
		}
		else
		{
			freq = synth->filter_frequency;
		}
		
		if(synth->filter_type == FILTER_TYPE_LOW_PASS)
		{
			c = 1.0 / tan(M_PI * freq * sorollet_inv_sampling_rate);
			csquare = c * c;
			a1 = 1.0 / ( 1.0 + synth->filter_resonance * c + csquare);
			a2 = 2 * a1;
			a3 = a1;
			b1 = 2.0 * ( 1.0 - csquare) * a1;
			b2 = ( 1.0 - synth->filter_resonance * c + csquare) * a1;
		}
		else //if(synth->filter_type == FILTER_TYPE_HIGH_PASS)
		{
			c = tan(M_PI * freq * sorollet_inv_sampling_rate);
			csquare = c * c;
			a1 = 1.0 / ( 1.0 + synth->filter_resonance * c + csquare);
			a2 = -2*a1;
			a3 = a1;
			b1 = 2.0 * ( csquare - 1.0) * a1;
			b2 = ( 1.0 - synth->filter_resonance * c + csquare) * a1;
		}
	}*/
	
	// and prepare a couple of values for the noise
	float level;
	level = 1 - synth->noise_level;
			
	for(i = 0; i < num_samples; i++)
	{
		// Oscillators
		/*tmp_buffer[i] = (
			osc1_buffer[i] * osc1_mix + 
			osc2_buffer[i] * synth->oscillator_mix
			);*/
			
		if(osc1_mix == 1)
		{
			tmp_buffer[i] = osc1_buffer[i];
		}
		else if(osc1_mix == 0)
		{
			tmp_buffer[i] = osc2_buffer[i];
		}
		else
		{
			tmp_buffer[i] = (
			osc1_buffer[i] * osc1_mix + 
			osc2_buffer[i] * synth->oscillator_mix
			);
		}
			
		if(synth->noise_level > 0)
		{
			//tmp_buffer[i] += synth->noise_level * noise_buffer[i];
			
			 tmp_buffer[i] = tmp_buffer[i] * (level) + noise_buffer[i] * synth->noise_level;
			
			//tmp_buffer[i] = tmp_buffer[i] * noise_buffer[i];
		}
		
		tmp_buffer[i] *= amp_envelope_value;
		
		
		// Filter
		if(synth->filter_type != FILTER_TYPE_NONE)
		{
			synth->filter_xn[0] = tmp_buffer[i];
			synth->filter_yn[0] = synth->filter_a1 * synth->filter_xn[0] + synth->filter_a2 * synth->filter_xn[1] + synth->filter_a3 * synth->filter_xn[2] - synth->filter_b1 * synth->filter_yn[1] - synth->filter_b2 * synth->filter_yn[2];
			buffer[i] = synth->filter_yn[0];
			
			synth->filter_xn[2] = synth->filter_xn[1];
			synth->filter_xn[1] = synth->filter_xn[0];
			synth->filter_yn[2] = synth->filter_yn[1];
			synth->filter_yn[1] = synth->filter_yn[0];
			
			if(synth->saturate_active)
			{
				buffer[i] = sorollet_saturate(buffer[i], synth->saturate_max);
			}
			
			if(synth->eq_active)
			{
				buffer[i] = sorollet_eq_update(&synth->eq_state, buffer[i]);
			}
			
			if(synth->bass_boost_active)
			{
				buffer[i] = sorollet_bass_boost(buffer[i], synth->bass_boost_multiplier);
			}
			
			// Apply level here
			buffer[i] *= synth->level;
			
			// Right data (it's the same than for left at this point)
			i++;
			buffer[i] = buffer[i-1];
			
		}
		else
		{
			if(synth->saturate_active)
			{
				buffer[i] = sorollet_saturate(tmp_buffer[i], synth->saturate_max);
			}
			else
			{
				buffer[i] = tmp_buffer[i];
			}
			
			if(synth->eq_active)
			{
				buffer[i] = sorollet_eq_update(&synth->eq_state, buffer[i]);
			}
			
			if(synth->bass_boost_active)
			{
				buffer[i] = sorollet_bass_boost(buffer[i], synth->bass_boost_multiplier);
			}
			buffer[i] *= synth->level;
		}
	}
	
	
    return 1;
}

void sorollet_synth_send_note(t_sorollet_synth* synth, int note, float volume)
{
	synth->param_note = note;
	synth->param_note_volume = volume;
}

void sorollet_synth_send_release(t_sorollet_synth* synth)
{
	
}

void sorollet_synth_send_note_cut(t_sorollet_synth* synth)
{
	synth->param_note = 0;
}

float sorollet_synth_note_to_frequency(int note, int octave)
{
    // return (440.0f * pow(2, ( ( note - 69 + (octave - 4) * 12 ) / 12.0) ) );
    return (440.0f * msys_powf(2.0f, ( (float)( note - 57 + (octave - 4) * 12 ) / 12.0f) ) );
}

void sorollet_synth_prepare_filter(t_sorollet_synth* synth, float freq)
{
	if(synth->filter_type == FILTER_TYPE_LOW_PASS)
	{
		synth->filter_c = 1.0f / tanf(M_PI * freq * (float)sorollet_inv_sampling_rate);
		synth->filter_csquare = synth->filter_c * synth->filter_c;
		synth->filter_a1 = 1.0f / ( 1.0f + synth->filter_resonance * synth->filter_c + synth->filter_csquare);
		synth->filter_a2 = 2 * synth->filter_a1;
		synth->filter_a3 = synth->filter_a1;
		synth->filter_b1 = 2.0f * ( 1.0f - synth->filter_csquare) * synth->filter_a1;
		synth->filter_b2 = ( 1.0f - synth->filter_resonance * synth->filter_c + synth->filter_csquare) * synth->filter_a1;
	}
	else if(synth->filter_type == FILTER_TYPE_HIGH_PASS)
	{
		synth->filter_c = tanf(M_PI * freq * (float)sorollet_inv_sampling_rate);
		synth->filter_csquare = synth->filter_c * synth->filter_c;
		synth->filter_a1 = 1.0f / ( 1.0f + synth->filter_resonance * synth->filter_c + synth->filter_csquare);
		synth->filter_a2 = -2*synth->filter_a1;
		synth->filter_a3 = synth->filter_a1;
		synth->filter_b1 = 2.0f * ( synth->filter_csquare - 1.0f) * synth->filter_a1;
		synth->filter_b2 = ( 1.0f - synth->filter_resonance * synth->filter_c + synth->filter_csquare) * synth->filter_a1;
	}
}

// ~~~~~~~~ Oscillators ~~~~~~~~
void sorollet_osc_whitenoise(float *buffer, int position, float frequency, int num_samples, int use_stereo)
{
    int i;
    for (i = 0; i<num_samples ; ++i)
        buffer[i] = 2.0f*(msys_rand() * sorollet_inv_rand_max)-1.0f;
}

void sorollet_osc_sine_wave(float *buffer, int position, float frequency, int num_samples, int use_stereo)
{
	int i;
	float cst = 2.0f*M_PI*frequency * (float)sorollet_inv_sampling_rate;
	for (i=0; i<num_samples; ++i)
	{
		// buffer[i] = sin(2.0*M_PI*frequency*(i+position)/(float)sorollet_sampling_rate);
		
		buffer[i] = utils_lut_sin(cst*(i+position));
		
		if(use_stereo)
		{
			i++;
			buffer[i] = buffer[i-1];
		}
	}	
}

void sorollet_osc_triangle_wave(float *buffer, int position, float frequency, int num_samples, int use_stereo)
{
	int i;
	float period = 1.0f / frequency; // periodo de la onda en segundos
	float semiperiod = period * 0.5f;
	
	for (i=0; i<num_samples ; ++i)
	{
		//float t = (i+position) / (float)sorollet_sampling_rate;
		float t = (i+position) * (float)sorollet_inv_sampling_rate;
		
		
		if (msys_fmodf(t,period) < semiperiod)
			buffer[i] = 2.0f*(msys_fmodf(t, semiperiod) / semiperiod)-1.0f;
		else
			buffer[i] = 1.0f - 2.0f*msys_fmodf(t, semiperiod) / semiperiod;
			
		if(use_stereo)
		{
			i++;
			buffer[i] = buffer[i-1];
		}
	}
}

void sorollet_osc_square_wave(float *buffer, int position, float frequency, int num_samples, int use_stereo)
{
	int i;
	float period = 1.0f / frequency; // periodo de la onda en segundos
	
	for (i=0; i<num_samples ; ++i)
	{
		//float t = (i+position) / (float)sorollet_sampling_rate;
		float t = (float)((i+position) * sorollet_inv_sampling_rate);
		
		if (msys_fmodf(t,period) < period / 2.0f)
			buffer[i] = 1.0f;
		else
			buffer[i] = -1.0f;
		
		if(use_stereo)
		{
			i++;
			buffer[i] = buffer[i-1];
		}
	}
}

void sorollet_osc_sawtooth_wave(float *buffer, int position, float frequency, int num_samples, int use_stereo)
{
	int i;
	float period = 1.0f / frequency; // periodo de la onda en segundos
	
	for (i=0; i<num_samples ; ++i)
	{
		//float t = (i+position) / (float)sorollet_sampling_rate;
		float t = (i+position) * (float)sorollet_inv_sampling_rate;
		
		buffer[i] = 2.0f * (msys_fmodf(t, period) * frequency) - 1.0f;
		
		if(use_stereo)
		{
			i++;
			buffer[i] = buffer[i-1];
		}
	}
}

// ~~~~~~ ADSR ~~~~~~

void sorollet_adsr_init(t_adsr* adsr)
{
	adsr->state = ADSR_ATTACK;
	
	adsr->attack_time = 0.3f;
	adsr->decay_time = 0.1f;
	adsr->sustain_level = 0.5f;
}

void sorollet_adsr_set_values(t_adsr* adsr, float aTime, float dTime, float sLevel, float rTime)
{
	adsr->attack_time = aTime;
	adsr->decay_time = dTime;
	adsr->sustain_level = sLevel;
	adsr->release_time = rTime;
}

void sorollet_adsr_attack(t_adsr* adsr, float startTime)
{
	adsr->state = ADSR_ATTACK;
	adsr->start_time = startTime;
	adsr->value = 0;
}

float sorollet_adsr_update(t_adsr* adsr, float time)
{
	float attack_end, decay_end, release_end;
	
	attack_end = adsr->start_time + adsr->attack_time;
	decay_end = attack_end + adsr->decay_time;
	release_end = adsr->release_start_time + adsr->release_time;
	
	
	// Update state ~~~
	// Note how we don't switch to release here because that only happens
	// when we get a key_off/release event
	if((adsr->state == ADSR_ATTACK) && (attack_end <= time))
	{
		adsr->state = ADSR_DECAY;
	}
	else if((adsr->state == ADSR_DECAY) && (decay_end <= time))
	{
		//printf("==> SUSTAIN\n");
		adsr->state = ADSR_SUSTAIN;
	}
	else if((adsr->state == ADSR_RELEASE) && (release_end <= time))
	{
		adsr->state = ADSR_DONE;
	}
	
	// and calculate the value
	switch(adsr->state)
	{
		case ADSR_ATTACK:
			adsr->value = map(time, adsr->start_time, attack_end, 0.0, 1.0);
			break;
		case ADSR_DECAY:
			adsr->value = map(time, attack_end, decay_end, 1.0, adsr->sustain_level);
			break;
		case ADSR_SUSTAIN:
			adsr->value = adsr->sustain_level;
			break;
		case ADSR_RELEASE:
			adsr->value = map(time, adsr->release_start_time, release_end, adsr->sustain_level, 0);
			break;
		case ADSR_DONE:
			adsr->value = 0;
	}
	
	return adsr->value;
}

void sorollet_adsr_release(t_adsr* adsr, float releaseStartTime)
{
	adsr->state = ADSR_RELEASE;
	adsr->release_start_time = releaseStartTime;
}

float sorollet_saturate(float value, float saturate_max)
{
	// http://www.musicdsp.org/showArchiveComment.php?ArchiveID=42
	if(value < saturate_max)
	{
		return value;
	}
	else if(value > saturate_max)
	{
		float tmp = value - saturate_max;
		return (0.1f + saturate_max + tmp / (1 + msys_powf((tmp) / (1 - saturate_max), 2)));
	}
	else if(value > 1)
	{
		return ((saturate_max + 1) * 0.5f);
	}
	return value;
}

// http://www.musicdsp.org/archive.php?classid=3#236
/*
// Recommended frequencies are ...
//
//  lowfreq  = 880  Hz
//  highfreq = 5000 Hz
//
// Set mixfreq to whatever rate your system is using (eg 48Khz)
*/
void sorollet_eq_init(t_eqstate* es, int lowfreq, int highfreq, int mixfreq)
{
	 // Clear state
	msys_memset(es,0,sizeof(t_eqstate));

	// Set Low/Mid/High gains to unity

	es->lg = 1.0f;
	es->mg = 1.0f;
	es->hg = 1.0f;

	// Calculate filter cutoff frequencies

	es->lf = 2.0f * (float)sin(M_PI * ((double)lowfreq / (double)mixfreq));
	es->hf = 2.0f * (float)sin(M_PI * ((double)highfreq / (double)mixfreq));
}

float sorollet_eq_update(t_eqstate* es, float sample)
{
	// Locals

	float  l,m,h;      // Low / Mid / High - Sample Values

	// Filter #1 (lowpass)

	es->f1p0  += (es->lf * (sample   - es->f1p0)) + (float)sorollet_vsa;
	es->f1p1  += (es->lf * (es->f1p0 - es->f1p1));
	es->f1p2  += (es->lf * (es->f1p1 - es->f1p2));
	es->f1p3  += (es->lf * (es->f1p2 - es->f1p3));

	l          = es->f1p3;

	// Filter #2 (highpass)

	es->f2p0  += (es->hf * (sample   - es->f2p0)) + (float)sorollet_vsa;
	es->f2p1  += (es->hf * (es->f2p0 - es->f2p1));
	es->f2p2  += (es->hf * (es->f2p1 - es->f2p2));
	es->f2p3  += (es->hf * (es->f2p2 - es->f2p3));

	h          = es->sdm3 - es->f2p3;

	// Calculate midrange (signal - (low + high))

	m          = es->sdm3 - (h + l);

	// Scale, Combine and store

	l         *= es->lg;
	m         *= es->mg;
	h         *= es->hg;

	// Shuffle history buffer

	es->sdm3   = es->sdm2;
	es->sdm2   = es->sdm1;
	es->sdm1   = sample;                

	// Return result

	return(l + m + h);
}

// http://www.musicdsp.org/archive.php?classid=3#235
float sorollet_bass_boost(float sample, float multiplier)
{
	static float selectivity = 70.0f, gain1, ratio, cap;
	gain1 = 1.0f/(selectivity + 1.0f);
	float gain2 = multiplier;
	cap= (sample + cap*selectivity )*gain1;
	sample = sorollet_saturate((sample + cap*ratio)*gain2, 2.0f);

	return sample;
}

float sorollet_char_to_float(unsigned char value, float out_min, float out_max)
{
	// Because value is a char it can be 0..128 but we want it to be 0..255
	float tmp_value = ((unsigned char)value ) / 255.0f; // 0..1
	float out = tmp_value * (out_max - out_min) + out_min;
	
	//printf("value %d out min %f out max %f out = %f\n", (unsigned char)value, out_min, out_max, out);
	return out;
}


osc1_function_ptr sorollet_enum_to_wave(unsigned int i)
{
	switch(i)
	{
		case WAVE_SINE:
		return sorollet_osc_sine_wave;
		
		case WAVE_TRIANGLE:
		return sorollet_osc_triangle_wave;
		
		case WAVE_SQUARE:
		return sorollet_osc_square_wave;
		
		case WAVE_SAWTOOTH:
		return sorollet_osc_sawtooth_wave;
	}
	return sorollet_osc_sine_wave;
}
