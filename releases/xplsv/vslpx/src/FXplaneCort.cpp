#include "FXplaneCort.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXplaneCort::perFrame(float time) {

	static float baseY=480.0/640.0;//768.0/1024.0;
	GLboolean currentMask;

	int baseViewport=(int)(DEMOHEIGHT - planeData.height) / 2;
	
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glGetBooleanv(GL_DEPTH_WRITEMASK, &currentMask);
	glDepthMask(false);
	//miDemo->ponOrtopedico(1,baseY);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glViewport(0,baseViewport,planeData.width,planeData.height);
	//glOrtho(-0.5,0.5,-0.5*baseY,0.5*baseY,0.10f,200.0f);
	//glOrtho(0, planeData.width, 0,planeData.height, 0,200.0f);
	//gluOrtho2D(0, planeData.width, 0,planeData.height);
	glOrtho(0, planeData.width, 0,planeData.height, -200.0f,200.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	//glTranslatef(0,baseY*0.5,0);
	glColor4f(planeColor.x,planeColor.y,planeColor.z,planeColor.w);
	glBlendFunc(fac1, fac2);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	
	static const float xt=0.5; // xtremo
	static const float yt=0.5*baseY;
	static float z_depth=float(-0.0121);
	glBindTexture(GL_TEXTURE_2D, planeData.texID);
	glNormal3f( 0.0f, 0.0f, 1.0f);

	// asumo q la textura es cuadrada y los datos estan en la parte superior
	

	float texBase=0;//1-baseY;

	glBegin(GL_QUADS);
		/*glTexCoord2f(0.0f, texBase); glVertex3f(-xt, -yt,  z_depth);
		glTexCoord2f(1.0f, texBase); glVertex3f( xt, -yt,  z_depth);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( xt,  yt,  z_depth);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-xt,  yt,  z_depth);*/

		glTexCoord2f(0.0f, texBase); glVertex3f(0.0f, 0.0f,  z_depth);
		glTexCoord2f(this->porc, texBase); glVertex3f( planeData.width*this->porc, 0.0f,  z_depth);
		glTexCoord2f(this->porc, 1.0f); glVertex3f( planeData.width*this->porc, planeData.height,  z_depth);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,  planeData.height,  z_depth);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	//miDemo->quitaOrtopedico();
	
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
	assert(filename!=NULL);

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
	// desasignar recursos y tal, descargar ficheros, blabla
	//if(planeData->texID!=NULL)
	//	glDeleteTextures(1, *planeData->texID);
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
