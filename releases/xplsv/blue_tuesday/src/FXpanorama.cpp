#include "FXpanorama.h"
#include "my_opengl.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXpanorama::perFrame(float time) {

	miDemo->ponOrtopedico(2,1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glColor4f(panColor.x,panColor.y,panColor.z,panColor.w);
	glDisable(GL_BLEND);
	float xt=1.3f; // xtremo
	float yt=0.51f;
	float z_depth=-0.0121f;
	
	glBegin(GL_QUADS);
		// el de abajo
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glVertex3f(-xt,-yt,z_depth);
		glVertex3f(xt,-yt, z_depth);
		glVertex3f(xt,0.178-yt,  z_depth);
		glVertex3f(-xt,0.178-yt,z_depth);

		glVertex3f(-xt,0.335f,z_depth);
		glVertex3f(xt,0.335f, z_depth);
		glVertex3f(xt,yt+0.1,  z_depth);
		glVertex3f(-xt,yt+0.1,z_depth);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	miDemo->quitaOrtopedico();
}

void FXpanorama::init(void) {
	// color por defecto -> negro
	this->panColor.x=0;
	this->panColor.y=0;
	this->panColor.z=0;
	this->panColor.w=1;
}

void FXpanorama::setPanColor(float r, float g, float b, float a) {
	this->panColor.x=r;
	this->panColor.y=g;
	this->panColor.z=b;
	this->panColor.w=a;
}

void FXpanorama::start(void) {
	
}

void FXpanorama::stop(void) {
	
}

void FXpanorama::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	
}

FXpanorama::FXpanorama() {
}

FXpanorama::~FXpanorama() {
}
