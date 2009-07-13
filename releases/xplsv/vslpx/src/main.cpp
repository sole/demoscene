/**

  "vslpx" / xplsv

  Start date ~ february 2005
  Released 20050416
  Source released 20090713

  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  Copyright 2005-2009 Soledad Penades http://soledadpenades.com
 
  This file is part of xplsv_vslpx
 
  xplsv_vslpx is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 3 only, as published
  by the Free Software Foundation.
 
  xplsv_vslpx is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with xplsv_vslpx. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <getopt.h>
#include <math.h>

#include "my_opengl.h"
#include "Music.h"
#include "ScriptLoader.h"
#include "my_opengl.h"

Music miMusic;
Demo *miDemo;
int multiSampling;
int multiSamplingBuffers;
int startOrder;
int startRow;
float startTime;
SDL_Surface *screen;
Uint32 flags;

bool active=true;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void loader(float porcentaje)
{
	glViewport(0,0,(GLsizei) DEMOWIDTH ,(GLsizei) DEMOHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glFrustum(-1.0,1.0,-1.0,1.0,1.0,20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1,0.2,0.6);
	miDemo->ponOrtopedico(100,100);

	float ypo=3;
	glTranslatef(-50,-50,0);
	glBegin(GL_QUADS);
		glVertex2f(0,ypo);
		glVertex2f(porcentaje,ypo);
		glVertex2f(porcentaje,ypo+1);
		glVertex2f(0,ypo+1);
	glEnd();

	miDemo->quitaOrtopedico();

	glFlush();
	SDL_GL_SwapBuffers();
}



int init(void)
{
	ScriptLoader sl;

	sl.setFilename("./data/script.xml");	
	sl.load();
	
	/* Load Music */	
	int musicrdo=miMusic.initSound();
	if(musicrdo==0) {
		miMusic.loadMP3("./data/dalezy.mp3");
		loader(100);
		return(1);
	} else {
		return(-1);
	}
	return(1);
}

void finish(void)
{
	miMusic.freeSound();
	
	SDL_Quit();
	
	exit(0);
}

int display(void)
{
	if(!miMusic.isPlaying())
	{
		miMusic.playSound();
		miMusic.playMP3();
		miMusic.setMP3Pos(startTime);
	}
	
	float currentTime = miMusic.getMP3Seconds() + 0.2f;
	
	if(!miDemo->hasError() && (miDemo->play(currentTime) >= 0) && (!miMusic.hasFinished()))
	{
		glFlush();
		return(1);
	}
	else
	{
		return(0);
	}
	
}

void list_modes()
{
	SDL_Rect** modes;
	int i;

	modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);

	if (modes == (SDL_Rect**)0)
	{
		fprintf(stdout, "No modes available!\n");
		exit(-1);
	}

	if (modes == (SDL_Rect**)-1)
	{
		fprintf(stdout, "All resolutions available.\n");
		exit(0);
	}
	else
	{
		printf("Available Fullscreen Modes\n");
		for (i=0; modes[i]; ++i)
		{
			fprintf(stdout, "%dx%d\n", modes[i]->w, modes[i]->h);
		}
		
		exit(1);
	}

}

void parse_arguments(int argc, char*argv[], int *width, int *height, int *fullscreen, int *multiSampling, int *multiSamplingBuffers, float *seconds)
{
	int option_index = 0, c;
	
	// Set some defaults to begin with
	*fullscreen = 0;
	*width = 640;
	*height = 480;
	*multiSampling = 0;
	*multiSamplingBuffers = 4;
	*seconds = 0;
	
	static struct option long_options[] =
	{
		{"fullscreen",	no_argument, fullscreen, 1},
		{"width",		required_argument, NULL, 'w'},
		{"height",		required_argument, NULL, 'h'},
		{"antialias",	no_argument, multiSampling, 1},
		{"antialias-samples",	required_argument, NULL, 'a'},
		{"start-time",	required_argument, NULL, 't'},
		{"list-modes",	no_argument, NULL, 'l'},
		{"help",		no_argument, NULL, '?'},
		{0, 0, 0, 0}
	};
	
	while(1)
	{
		c = getopt_long (argc, argv, "w:h:o:r:l", long_options, &option_index);
		
		if(c == -1) { break; }
		
		switch (c)
		{
			case 'w':
				*width = atoi((char*)optarg);
				break;
			  
			case 'h':
				*height = atoi((char*)optarg);
				break;
				
			case 'a':
				*multiSamplingBuffers = atoi((char*)optarg);
				break;
				
			case 't':
				*seconds = atof((char*)optarg);
				break;
			
			case 'l':
				list_modes();
				break;
				
			case '?':
				printf("Usage:\n"
				"%s [options]\n\n"
				"where options is one or more of the following:\n\n"
				"-w, --width WIDTH: screen width in pixels (default=640)\n"
				"-h, --height HEIGHT: screen height in pixels (default=480)\n"
				"--fullscreen: use fullscreen (default=no)\n"
				"--antialias: use antialias (default=no)\n"
				"--antialias-samples: how many antialias samples to use (default=4)\n"
				"-t, --start-time SECONDS: begin playing at SECONDS time (default=0)\n"
				"-l, --list-modes: show available accelerated fullscreen size combinations\n"
				"-?, --help: show this message\n"
				, argv[0]);
				exit(0);
		}
    }
}

void save_screenshot(int width, int height)
{
	float ms = miMusic.getMilliseconds();
	char filename[255];
	sprintf(filename, "screenshot-%05d.bmp", (int)ms);

	int save_result = SOIL_save_screenshot
	(
		filename,
		SOIL_SAVE_TYPE_BMP,
		0, 0, width, height
	);
	
	if(save_result)
	{
		printf("Screenshot saved to %s\n", filename);
	}

}

// Entry point
int main(int argc, char *argv[])
{
	int width, height, fullscreen;

	// Initialize SDL's subsystems
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
	// Parse command line parameters
	parse_arguments(argc, argv, &width, &height, &fullscreen, &multiSampling, &multiSamplingBuffers, &startTime);
	
	// printf("Using width = %d, height = %d, fullscreen = %d\nstart order = %d, row = %d\n", width, height, fullscreen, startOrder, startRow);
	
	atexit(finish);
	
    
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	
	flags = SDL_OPENGL;
	
	if(fullscreen)
	{
		flags |= SDL_FULLSCREEN;
	}
	
	if(multiSampling)
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, true);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multiSamplingBuffers);
	}
	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);//vsync, SDL manual says it's on by default but I highly doubt it
	
	// Attempt to create the opengl window with 32bit pixels.
	screen = SDL_SetVideoMode(width, height, 32, flags);
	
	// If we fail, return error.
	if ( screen == NULL ) 
	{
		fprintf(stderr, "Unable to set %dx%d opengl video (fullscreen = %d, antialias samples = %d): %s\n", width, height, fullscreen, multiSamplingBuffers, SDL_GetError());
		list_modes();
		exit(1);
	}
	
	SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_SetCaption("xplsv - vslpx", "xplsv - vslpx");

	miDemo = new Demo(width, height);
	if(init() != 1)
	{
		printf("There was an error while initializing\n");
		exit(-1);
	}
	
	// Main loop: loop forever.
	while (display())
	{
		SDL_GL_SwapBuffers();
		
		// Poll for events, and handle the ones we care about.
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
				case SDL_KEYDOWN:
					break;
				case SDL_KEYUP:
					// If escape is pressed, return (and thus, quit)
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						return 0;
					}
					
					if(event.key.keysym.sym == SDLK_RIGHT)
					{
						float secs = miMusic.getMP3Seconds();
						miMusic.setMP3Pos(secs + 10);
						break;
					}
					
					if(event.key.keysym.sym == SDLK_LEFT)
					{
						float secs = miMusic.getMP3Seconds() - 10;
						if(secs < 0) secs = 0;
						miMusic.setMP3Pos(secs);
						break;
					}
					
					if(event.key.keysym.sym == SDLK_s)
					{
						save_screenshot(width, height);
						break;
					}
					
					break;
					case SDL_QUIT:
					return(0);
			}
		}
	}
	return 0;
}

