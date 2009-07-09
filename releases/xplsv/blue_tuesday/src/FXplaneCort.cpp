#include "FXplaneCort.h"
#include "my_opengl.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXplaneCort::perFrame(float time) {

	GLboolean currentMask;
	
	float scaled_width, scaled_height;
	int baseViewport;
	
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glGetBooleanv(GL_DEPTH_WRITEMASK, &currentMask);
	glDepthMask(false);
	
	
	scaled_width = miDemo->getWidth();
	scaled_height = planeData.height * scaled_width / planeData.width;
	baseViewport = (int)(miDemo->getHeight() - scaled_height) / 2;
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	glViewport(0, baseViewport, (GLsizei) scaled_width, (GLsizei) scaled_height);
	glOrtho(0, scaled_width, 0, scaled_height, -200.0f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glColor4f(planeColor.x,planeColor.y,planeColor.z,planeColor.w);
	glBlendFunc(fac1, fac2);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	
	static float z_depth=float(-0.0121);
	glBindTexture(GL_TEXTURE_2D, planeData.texID);
	glNormal3f( 0.0f, 0.0f, 1.0f);


	float texBase=0;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, texBase); glVertex3f(0.0f, 0.0f,  z_depth);
		glTexCoord2f(this->porc, texBase); glVertex3f( scaled_width*this->porc, 0.0f,  z_depth);
		glTexCoord2f(this->porc, 1.0f); glVertex3f( scaled_width*this->porc, scaled_height,  z_depth);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,  scaled_height,  z_depth);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glPopAttrib();
	glDepthMask(currentMask);

}

void FXplaneCort::init(void) {
	

	if(strcmp(this->textureName,"")!=0) {
		// si hay textura la cargo
		LoadTGA(&planeData,textureName);
	}
	
}

void FXplaneCort::setPlaneColor(float r, float g, float b, float a) {
	this->planeColor.x=r;
	this->planeColor.y=g;
	this->planeColor.z=b;
	this->planeColor.w=a;
}

void FXplaneCort::setBlendFunc(GLenum fac1,GLenum fac2) {
	this->fac1=fac1;
	this->fac2=fac2;
}

void FXplaneCort::setTextureName(char *filename) {

	strcpy(textureName,filename);
}

void FXplaneCort::setPorc(float _porc) {
	this->porc=_porc/100.0;
}

void FXplaneCort::start(void) {
	
}

void FXplaneCort::stop(void) {
	
}

void FXplaneCort::deInit(void) {
	
}

FXplaneCort::FXplaneCort() {
	fac1=GL_SRC_ALPHA;
	fac2=GL_ONE_MINUS_SRC_ALPHA;
	strcpy(textureName,"");
	// color por defecto -> blanco, alpha=100%
	this->planeColor.x=1;
	this->planeColor.y=1;
	this->planeColor.z=1;
	this->planeColor.w=1;

	this->porc=1;
}

FXplaneCort::~FXplaneCort() {
}
