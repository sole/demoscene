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

#include "SDL.h"
#include "SDL_opengl.h"
#include <stdlib.h>
#include "sorollet.h"
#include "data/song.h"
#include "intro.h"

#define BUFFER_SIZE 2048		// buffer length, in samples
#define SAMPLING_RATE 44100
#define DESIRED_CHANNELS 2		
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

float sound_buffer[BUFFER_SIZE * 2];

// uncomment this for generating a raw file with the output sound
//#define OUTFILE "output.raw"

#ifdef OUTFILE
#include <stdio.h>
FILE *fout;
#endif

int finished;

void play(void *userdata, Uint8 *stream, int len)
{
	
	int i;
	int num_samples = len >> 1; // as we use signed 16 bit samples, it means we use 2 bytes per sample
	static int position = 0;
	float position_seconds = (float)position / (float) SAMPLING_RATE;
	float buffer[len];
	float volume = 0.75;

	Sint16 *dst_buf = (Sint16*) stream;

	finished = sorollet_play(position_seconds);
	
	sorollet_get_buffer(sound_buffer, position, num_samples);
	
	for (i=0; i < num_samples; ++i)
	{
		float v = sound_buffer[i] * volume;
		if (v > 1.0f)
			v = 1.0f;
		else if (v < -1.0f)
			v = -1.0f;
		dst_buf[i] = (Sint16)(32767.0f*v);
		
	}
	position += num_samples;

	#ifdef OUTFILE
		fwrite(dst_buf, sizeof(Sint16), num_samples, fout);
	#endif
}

int main(int argc, char **argv)
{
	int video_flags = SDL_OPENGL ;//| SDL_FULLSCREEN; // you know what to do here
	SDL_AudioSpec audio_spec;
	SDL_Event event;

	finished = 0;

	audio_spec.freq     = SAMPLING_RATE;
	audio_spec.format   = AUDIO_S16SYS;
	audio_spec.channels = DESIRED_CHANNELS;
	audio_spec.samples  = BUFFER_SIZE;
	audio_spec.callback = play;
	audio_spec.userdata = NULL;

	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);

	SDL_OpenAudio(&audio_spec, NULL);


#ifdef OUTFILE
fout = fopen(OUTFILE, "w");
#endif

	intro_init(WINDOW_WIDTH, WINDOW_HEIGHT);

	sorollet_init(SAMPLING_RATE, AUDIO_S16SYS, DESIRED_CHANNELS, BUFFER_SIZE);
	sorollet_load_song_from_array(song);

	// This does something odd with my system and the window doesn't open
	// (but the sound oddly works!)
	// If you know why, let me know (this only happens in linux)
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, video_flags);
	SDL_ShowCursor(0);

	utils_initialize_sin_cos_lut();
	intro_init(WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_PauseAudio(0);
	SDL_WM_SetCaption("to_the_beat / xplsv", 0);

	while (!finished)
	{
		intro_play(SDL_GetTicks());

		SDL_GL_SwapBuffers();

		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			finished = 1;
	}
	
	SDL_PauseAudio(1);
	SDL_CloseAudio();
	SDL_Quit();

	return 0;

}


