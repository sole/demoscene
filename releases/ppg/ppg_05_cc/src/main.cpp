/**

  "PPG05: code colors"

  Start date somewhere around july 2004
  Released 20040725
  Source released 20090703

  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  Copyright 2004-2009 Soledad Penades http://soledadpenades.com
 
  This file is part of ppg05_cc
 
  ppg05_cc is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 3 only, as published
  by the Free Software Foundation.
 
  ppg05_cc is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with ppg05_cc. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <getopt.h>
#include <math.h>

#include "my_opengl.h"
#include "Music.h"
#include "textures.h"
#include "Demo.h"
#include "SOIL/SOIL.h"

#include "Effect.h"
#include "FXmotionblur.h"
#include "FXdummy.h"
#include "FXritmo.h"
#include "FXtituti.h"
#include "FXtitutiBis.h"
#include "FXfinal.h"
#include "FXplane.h"

Music miMusic;
Demo *miDemo;
int multiSampling;
int multiSamplingBuffers;
int startOrder;
int startRow;
SDL_Surface *screen;
Uint32 flags;
FXplane miPlano;


/* Efectos */
struct t_effect_ {
	Effect *effect;
	int order;
	int state;
};

bool inicializado=false;

// Para la pantalla de carga
TextureImage loadingImage;

FXmotionblur *fxmotionblur=new FXmotionblur();
FXdummy *fxdummy=new FXdummy();
FXritmo *fxritmo=new FXritmo();
FXtituti *fxtituti=new FXtituti();
FXtitutiBis *fxtitutiBis=new FXtitutiBis();
FXfinal *fxfinal=new FXfinal();

t_effect_ script[6]={
	{fxdummy,0,0},
	{fxritmo,5,1},
	{fxtituti,7,2},
	{fxtitutiBis,9,3},
	{fxfinal,11,4},
	{NULL,14,5}
};

int script_index=0;
int max_scenes=5;

Effect *activeEffect;

bool active=true;


void loader(float porcentaje)
{
	// Es muy OB_VIOOO, dibuja una barra proporcional al porcentaje
	// Tan simple que da risa
	// Eso si, porcentaje debe ser 0..100

	glViewport(0,0,(GLsizei) miDemo->getWidth(), (GLsizei) miDemo->getHeight());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(0.05,0.55,0.55,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glFrustum(-1.0,1.0,-1.0,1.0,1.0,20.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0,-3,0);
	//glColor3f(1,1,1);
	
	miDemo->ponOrtopedico(110,10);
	
	glColor3f(0.0,0.6,0.81);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-50.5,-0.1,0);
		glVertex3f(50.5,-0.1,0);
		glVertex3f(50.5,0.3,0);
		glVertex3f(-50.5,0.3,0);
		
	glEnd();
	

	float ancho=porcentaje;
	float alto=0.2;

	float alfa=porcentaje/100;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1,1,1,alfa);
	glBegin(GL_QUADS);
		glVertex3f(-50,0,0);
		glVertex3f(-50+ancho,0,0);
		glVertex3f(-50+ancho,alto,0);
		glVertex3f(-50,alto,0);
		
	glEnd();
	
	miDemo->quitaOrtopedico();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// super imagen!
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	float z_depth=0.01f;
	miDemo->ponOrtopedico(1,2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, loadingImage.texID);	

	glColor4f(1,1,1,alfa*0.8);
	glTranslatef(-0.5f,-0.5f,0);
	glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 1.0f);			
			glTexCoord2f(0,0); 			
			glVertex3f(0,0,z_depth);
			glTexCoord2f(1,0); 			
			glVertex3f(1,0,z_depth);
			glTexCoord2f(1,1); 			
			glVertex3f(1,1.2,z_depth);
			glTexCoord2f(0,1);			
			glVertex3f(0,1.2,z_depth);
		glEnd();

	glDisable(GL_TEXTURE_2D);
	miDemo->quitaOrtopedico();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_BLEND);
	glFlush();
	SDL_GL_SwapBuffers();
}

int init(void)
{
	loader(0);

	// cargo la tga primero q todo para q el loader pueda jugar a ponerla!
	LoadTGA(&loadingImage,"./data/codecolors.tga");
	
	loader(10);

	loader(15);
	
	loader(20);

	int musicrdo=miMusic.initSound();
	if(musicrdo==0) {
		miMusic.loadMod("./data/sole_jd.it");
		
		loader(30);
		
		fxmotionblur->init();
		fxmotionblur->setClearColor(1.0f,1.0f,1.0f,0.99f); // 0.99 for ati, 0.45nvidia
		loader(49);
		fxdummy->init();
		loader(52);
		fxritmo->init();
		loader(56);
		fxtituti->init();
		loader(58);
		fxtitutiBis->init();
		loader(60);
		fxfinal->init();
		loader(64);
		miPlano.setTextureName("./data/diagonales640.tga");
		miPlano.setFixed(1);
		miPlano.setPlaneColor(1,1,1,0.2);
		miPlano.init();

		activeEffect=script[script_index].effect;
		if(activeEffect!=NULL) {
			activeEffect->start();
		}
		
		loader(100);
		//Sleep(1000);
		
	} else {
		inicializado=true;
		return(-1);
	}
	inicializado=true;
	return(1);
}

void finish(void)
{
	
	miMusic.freeSound();
	//finishScenes();

	fxmotionblur->deInit();
	fxdummy->deInit();
	fxritmo->deInit();
	fxtituti->deInit();
	fxtitutiBis->deInit();
	fxfinal->deInit();
	miPlano.deInit();

	delete fxmotionblur;
	delete fxdummy;
	delete fxritmo;
	delete fxtituti;
	delete fxtitutiBis;
	delete fxfinal;
	
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
		
		// and 'fast forward' to appropriate active effect
		if(startOrder != script[script_index].order)
		{
			if(activeEffect)
			{
				activeEffect->stop();
			}
			
			for(int i = 0; i < max_scenes; i++)
			{
				if(
					(script[i].order == startOrder) ||
					((script[i].order < startOrder) &&
						(script[i+1].order > startOrder))
				)
				{
					script_index = i;
				}
			}
			
			activeEffect = script[script_index].effect;
			activeEffect->start();
		}
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
	//if(activeEffect != NULL)
	if(script[script_index].effect != NULL)
	{
		if(pattern==script[script_index+1].order)
		{
			script_index++;
			activeEffect->stop();
			if(script_index>=max_scenes) {
				return(-1);
			}
			if(!script[script_index].effect)
			{ /* malrollo break;*/ }
			script[script_index].effect->start();

		}
		activeEffect=script[script_index].effect;
		activeEffect->setMusicParams(pattern,row);
		activeEffect->perFrame(miMusic.getMilliseconds());
		miPlano.perFrame(0);
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
	SDL_WM_SetCaption("PPG05 - Codecolors", "PPG05 - Codecolors");

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
