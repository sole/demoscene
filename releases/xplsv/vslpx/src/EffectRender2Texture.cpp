#include "EffectRender2Texture.h"
#include <strings.h>
#include "Demo.h"
extern Demo* miDemo;
#include "my_opengl.h"

void EffectRender2Texture::play(float _time) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,this->myTexture->texID);					

	glCopyTexSubImage2D(GL_TEXTURE_2D,// target
		0, //level mipmaps
		0, //xoffset
		0, // yoffset
		0, // x
		0, //y
		this->width, // width
    this->height //height
	); 
	

	miDemo->checkGLerror("EffectRender2Texture-glCopyTexSubImage2D");
}

void EffectRender2Texture::init() {
	// Existe la textura con ese nombre?
	// Si - pillar el ID
	// No
	// Crearla + asignar el ID

	// Y si la creo directamente? XD
	// mi demo get texture(id, width, height)
	// As i get errors with textures which are not power of 2...
	int width, height;
	if(this->width<512) {
		width=512;
	} else if(this->width<1024) {
		width=1024;
	}
	if(this->height<256) {
		height=256;
	} else if(this->height<512) {
		height=512;
	} else {
		height=1024;
	}
	this->myTexture = miDemo->addTexture(width, height, this->textureId);

}

void EffectRender2Texture::start() {
	
}

void EffectRender2Texture::deInit(void) {
	
}

const char* EffectRender2Texture::getEffectType(void) {
	return "EffectRender2Texture";
}

int EffectRender2Texture::setParam(char *paramName, char *attribName, float value) {	
	// Setting the TEXTURE
	if(strcasecmp(paramName,"texture")==0) {
		if(strcasecmp(attribName,"id")==0) {
			this->textureId = (unsigned int) value;
		}
		if(strcasecmp(attribName,"width")==0) {
			this->width=(unsigned int) value;
		}
		if(strcasecmp(attribName,"height")==0) {
			this->height=(unsigned int) value;
		}
	}
	
	return 0;
}
