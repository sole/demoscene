#include <stdlib.h>
#if defined(_MSC_VER)
#include "SDL.h"
#include "SDL_opengl.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#endif

#include <math.h>

SDL_Surface *screen;
Uint32 flags;

void render()
{   
	GLubyte data[32*4];
	
	for(int i=0;i<32*4;++i)
	{  data[i]=rand();  }
	
	// Lock surface if needed
	if (SDL_MUSTLOCK(screen))
		if (SDL_LockSurface(screen) < 0) 
			return;
	
	// Ask SDL for the time in milliseconds
	int tick = SDL_GetTicks();
	
	glClearColor(1,0,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// and the mighty triangle....
	glPushMatrix();
	glRotatef(tick*0.01, 0,0,1);
	
	glEnable(GL_POLYGON_STIPPLE);
	
	glPolygonStipple(data);
	
	glBegin(GL_TRIANGLES);						// Drawing Using Triangles
	glVertex3f( 0.0f, 1.0f, 0.0f);				// Top
	glVertex3f(-1.0f,-1.0f, 0.0f);				// Bottom Left
	glVertex3f( 1.0f,-1.0f, 0.0f);				// Bottom Right
	glEnd();	
	
	glPopMatrix();

	glDisable(GL_POLYGON_STIPPLE);

	
	// Unlock if needed
	if (SDL_MUSTLOCK(screen)) 
		SDL_UnlockSurface(screen);
	
	// Tell SDL to update the whole screen
	SDL_UpdateRect(screen, 0, 0, 640, 480);    
}

// Entry point
int main(int argc, char *argv[])
{
	// Initialize SDL's subsystems
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
	// Register SDL_Quit to be called at exit; makes sure things are
	// cleaned up when we quit.
	atexit(SDL_Quit);
    
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	
	flags = SDL_OPENGL;
	//flags |= SDL_FULLSCREEN;
	
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, true);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	
	// Attempt to create a 640x480 window with 32bit pixels.
	screen = SDL_SetVideoMode(640, 480, 32, flags);
	
	// If we fail, return error.
	if ( screen == NULL ) 
	{
		fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
		exit(1);
	}

	
	// Main loop: loop forever.
	while (1)
	{
		// Render stuff
		render();
		
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
						return 0;
					break;
					case SDL_QUIT:
					return(0);
			}
		}
	}
	return 0;
}
