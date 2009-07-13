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
	unsigned int id; // my internal id - nothing related to opengl's id
	char name[255];
} TextureImage;


bool LoadTGA(TextureImage *texture, const char *filename);

GLuint EmptyTexture(GLuint _width, GLuint _height, GLint _minFilter = GL_LINEAR, GLint _magFilter = GL_LINEAR);

#endif
