/**

  "PPG01: Scene of the girls"
  A joke prod!

  Start date 20030803
  Released 20031102
  Source released 20090629

  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  Copyright 2003-2009 Soledad Penades http://soledadpenades.com
 
  This file is part of ppg01_sotg
 
  ppg01_sotg is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 3 only, as published
  by the Free Software Foundation.
 
  ppg01_sotg is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with ppg01_sotg. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#if defined(_MSC_VER)
#include "SDL.h"
#include "SDL_opengl.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#endif

#include <getopt.h>
#include <math.h>

#include "scenes.h"
#include "math3D.h"
#include "Music.h"
#include "textures.h"
#include "Demo.h"
#include "SOIL/SOIL.h"

#define VANCHO 50
#define VALTO 50
#define TAM (4*(VANCHO+1)*(VALTO+1))

Music miMusic;
Demo *miDemo;
int multiSampling;
int multiSamplingBuffers;
int startOrder;
int startRow;

float t0;
float angulo=0;
bool active=true;

SDL_Surface *screen;
Uint32 flags;

void loader(float porcentaje) {
	// Es muy OB_VIOOO, dibuja una barra proporcional al porcentaje
	// Tan simple que da risa
	// Eso si, porcentaje debe ser 0..100

	glViewport(0,0,(GLsizei) 640 ,(GLsizei) 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1,0.0,0.0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glFrustum(-1.0,1.0,-1.0,1.0,1.0,20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1,1,1);
	
	ponOrtopedico(110,10);
	
	glColor3f(0.6,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-50.5,-0.1,0);
		glVertex3f(50.5,-0.1,0);
		glVertex3f(50.5,0.3,0);
		glVertex3f(-50.5,0.3,0);
		
	glEnd();
	

	float ancho=porcentaje;
	float alto=0.2;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1,1,1,porcentaje/100);
	glBegin(GL_QUADS);
		glVertex3f(-50,0,0);
		glVertex3f(-50+ancho,0,0);
		glVertex3f(-50+ancho,alto,0);
		glVertex3f(-50,alto,0);
		
	glEnd();
	glDisable(GL_BLEND);
	quitaOrtopedico();
	glFlush();
	SDL_GL_SwapBuffers();
}

int init(void) {
	printf("        ___         \n"
		   "       /  /  ______  __   __\n"
		   "      /  /  / __  / /  \\_/  \\   ____\n"
		   "  ___/  /  / /_/ / / /\\   /\\ \\_/ __ \\\n"
		   " / __  /  / ____/ / /  \\_/  \\   /_/ /\n"
		   "/ /_/ /__/ /_____/ /         \\_____/\n"
		   "\\_________________/\n"
		   );
	printf("D.E.M.O. (Discrete Effort to Merely Outstand) v0.1 by Sole\n");
	printf("Now loading SOTG\n");
	glClearColor(0.10,0.10,0.0,1.0);
	glShadeModel(GL_FLAT);
	printf("Precalc::trigtables\n");
	loader(0);
	prepareTables();
	setCurrentHeight(HEIGHT);
	setCurrentWidth(WIDTH);
	printf("Initializing sound...\n");
	int musicrdo=miMusic.initSound();
	if(musicrdo>=0) {
		printf("Loading music...\n");
		loader(10);
		miMusic.loadMod("./data/mysotg.it");
		printf("Initializing scenes...\n");
		loader(40);
		initScenes();
		loader(60);
		printf("Wait...\n");
		
		for(int kaka=61;kaka<100;kaka++) {
			loader((float)kaka);
		}

	} else {
		return(-1);
	}
	return(1);
}

void finish(void)
{
	
	printf("Freeing sound\n");
	miMusic.freeSound();

	printf("Freeing more data...\n");
	finishScenes();
	
	SDL_Quit();
	
	exit(0);
}

int display(void) {

	int pattern,row;
	float musicSeconds;
	float fft[512];
	
	glClear(GL_COLOR_BUFFER_BIT);
	if(!miMusic.isPlaying())
	{
		miMusic.playSound();
		miMusic.playMod();
		miMusic.setPos(startOrder, startRow);
	}
	
	miMusic.syncro();
	pattern=miMusic.getPattern();
	row=miMusic.getRow();
	musicSeconds = miMusic.getSeconds();

	if(miMusic.hasFinished())
	{
		return 0;
	}
	
	// Lanzo las escenas segun corresponda
	switch(pattern) {
			// Patron 0, escena del simbolo femenino ;)
	case 0: sceneSimbolo(row);
			break;
			// Patron 1, los latidos donde sale 'scene of the girls'
	case 1: sceneLatidos(row);
			break;
			// Círculos y créditos
	case 2: sceneCircles(row);
			break;
	case 3: sceneRotante(row, musicSeconds);
			break;
	case 4: sceneRotante2(row, musicSeconds);
			break;
	case 5: scene4segundos(row);
			break;
	case 6:	 
	case 7: miMusic.getFFT(fft,512);
			sceneSurfaceBlur(miMusic.getPattern(), row, musicSeconds, fft);
			break; 
	case 8: 
	case 9: sceneDiscos2(row, musicSeconds);
			break;
	case 10:
	case 11:
	case 12:
	case 13:sceneDiscos3(row, musicSeconds);
			break;
	default:
		return(0);
		break;
	}
	
	return(1);
	
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

void parse_arguments(int argc, char*argv[], int *width, int *height, int *fullscreen, int *multiSampling, int *multiSamplingBuffers, int *order, int *row)
{
	int option_index = 0, c;
	
	// Set some defaults to begin with
	*fullscreen = 0;
	*width = 640;
	*height = 480;
	*multiSampling = 0;
	*multiSamplingBuffers = 4;
	*order = 0;
	*row = 0;
	
	static struct option long_options[] =
	{
		{"fullscreen",	no_argument, fullscreen, 1},
		{"width",		required_argument, NULL, 'w'},
		{"height",		required_argument, NULL, 'h'},
		{"antialias",	no_argument, multiSampling, 1},
		{"antialias-samples",	required_argument, NULL, 'a'},
		{"start-order",	required_argument, NULL, 'o'},
		{"start-row",	required_argument, NULL, 'r'},
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
				
			case 'o':
				*order = atoi((char*)optarg);
				break;
				
			case 'r':
				*row = atoi((char*)optarg);
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
				"-o, --start-order ORDER: begin playing at order number ORDER (default=0)\n"
				"-r, --start-row ROW: begin playing at row number ROW (default=0)\n"
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
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
	// Parse command line parameters
	parse_arguments(argc, argv, &width, &height, &fullscreen, &multiSampling, &multiSamplingBuffers, &startOrder, &startRow);
	
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

	miDemo = new Demo(width, height);
	init();
	
	// Main loop: loop forever.
	while (display())
	{
		// Render stuff
		;
		
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
						miMusic.setPos(miMusic.getPattern() + 1, 0);
						break;
					}
					
					if(event.key.keysym.sym == SDLK_LEFT)
					{
						int prev = miMusic.getPattern() - 1;
						if(prev < 0) prev = 0;
						miMusic.setPos(prev, 0);
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
