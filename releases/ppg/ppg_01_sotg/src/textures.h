#ifndef __TEXTURES__
#define __TEXTURES__

#include <string.h>
#include <stdlib.h>
#include "my_opengl.h"
#include "SOIL/SOIL.h"

// NOTE: this was probably taken from a nehe tutorial

typedef struct
{
	GLubyte	*imageData;
	GLuint	bpp;
	GLuint	width;
	GLuint	height;
	GLuint	texID;
} TextureImage;


bool LoadTGA(TextureImage *texture, char *filename);


#endif
