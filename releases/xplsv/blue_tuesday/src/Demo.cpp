#include "Demo.h"
#include "my_opengl.h"
#include <stdlib.h>

int init(void);

Demo::Demo(int _width, int _height) {
	if((_height>0) && (_width>0)) {
		this->height=_height;
		this->width=_width;
	} else {
		this->height=480;
		this->width=640;
	}
}

int Demo::getHeight(void) {
	return this->height;
}

int Demo::getWidth(void) {
	return this->width;
}

void Demo::setSize(int _width, int _height) {
	if((_height>0) && (_width>0)) {
		this->height=_height;
		this->width=_width;
	} 
}
bool Demo::isFullScreen(void) {
	return this->fullscreen;
}

void Demo::setFullScreen(bool _fullscr) {
	this->fullscreen=_fullscr;
}
void Demo::setTitle(char *_title) {
	strcpy(this->title,_title);
}
char *Demo::getTitle(void) {
	return this->title;
}

void Demo::ponOrtopedico(float xres, float yres ) {	
	// Ahora pongo el modo ortho-pedico 
	
	if(xres == -1)
	{
		xres = this->width;
	}
	
	if(yres == -1)
	{
		yres == this->height;
	}
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glViewport(0,0,this->width,this->height);
	float xrespartido2=xres*0.5f;
	float yrespartido2=yres*0.5f;
	glOrtho(-xrespartido2, xrespartido2, -yrespartido2, yrespartido2, 0.10f, 200.0f);
	
	glMatrixMode(GL_MODELVIEW);
}


void Demo::quitaOrtopedico(void) {
	// restauro el modo que hubiera antes
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Demo::ejes(void) {
	glLineWidth(3.0f);
	glColor3f(1.0f,0.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1000.0f,0.0f,0.0f); // X
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(-1000.0f,0.0f,0.0f); // X neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.0f,1.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1000.0f,0.0f); // y
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,-1000.0f,0.0f); // y neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.0f,0.0,1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1000.0f); // z
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,-1000.0f); // z neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0f);
	
}
