/**
This used to ran based on code from nehe, then I adapted it to use SOIL
(Simple OpenGL Image Library) which is pretty neat.

*/

#include "textures.h"

bool LoadTGA(TextureImage *texture, const char *filename)
{    
	
	int texID = SOIL_load_OGL_texture(
		filename,
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y 
	);
	
	if(0 == texID)
	{
		printf( "SOIL loading error: %s '%s'\n", filename, SOIL_last_result() );
		return false;
	}
	
	GLint width, height, border;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_BORDER, &border);
	width -= border; height -= border;
	texture->texID = texID;
	texture->width=width;
	texture->height=height;
	
	return true;
}

GLuint EmptyTexture(GLuint _width, GLuint _height, GLint _minFilter, GLint _magFilter) {
	GLuint txtnumber;
	unsigned int* data;	


	data = (unsigned int*)new GLuint[((_width * _height)* 4 * sizeof(unsigned int))]; // allocate mem
	// ZeroMemory(data,((_width * _height)* 4 * sizeof(unsigned int)));	// empty memory...

	glGenTextures(1, &txtnumber);								
	glBindTexture(GL_TEXTURE_2D, txtnumber);					
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // GL_LINEAR_MIPMAP_LINEAR

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	// TODO: throw an error or something if ret!=0 --> then the mipmap has not been built
	int ret=gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, data);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Might be changeable in a future
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // and this too

	delete [] data;												

	return txtnumber;											

}
