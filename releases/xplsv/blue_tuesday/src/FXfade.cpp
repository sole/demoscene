#include "FXfade.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXfade::perFrame(float time) {

	
	miDemo->ponOrtopedico(2,2);

	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glColor4f(fadeColor.x,fadeColor.y,fadeColor.z,fadeColor.w);
	glEnable(GL_BLEND);
	glBlendFunc(fac1, fac2);
	float xt=2; // xtremo
	float z_depth=float(-0.0121);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		
		glVertex3f(-xt*2,-xt,z_depth);
		
		
		glVertex3f(xt*2,-xt, z_depth);

		
		glVertex3f(xt*2,xt,  z_depth);

		
		glVertex3f(-xt*2,xt,z_depth);


	glEnd();
	glDisable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	miDemo->quitaOrtopedico();

	glPopAttrib();
}

void FXfade::init(void) {
	// color por defecto -> blanco
	this->fadeColor.x=1;
	this->fadeColor.y=1;
	this->fadeColor.z=1;
	this->fadeColor.w=1;
	
}

void FXfade::setFadeColor(float r, float g, float b, float a) {
	this->fadeColor.x=r;
	this->fadeColor.y=g;
	this->fadeColor.z=b;
	this->fadeColor.w=a;
}

void FXfade::setBlendFunc(GLenum fac1,GLenum fac2) {
	this->fac1=fac1;
	this->fac2=fac2;
}


void FXfade::start(void) {
	
}

void FXfade::stop(void) {
	
}

void FXfade::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	
}

FXfade::FXfade() {
	fac1=GL_SRC_ALPHA;
	fac2=GL_ONE_MINUS_SRC_ALPHA;
}

FXfade::~FXfade() {
}
