/**
This used to ran based on code from nehe, then I adapted it to use SOIL
(Simple OpenGL Image Library) which is pretty neat.

*/

#include "textures.h"

bool LoadTGA(TextureImage *texture, char *filename)
{    
	
	int texID = SOIL_load_OGL_texture(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
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


