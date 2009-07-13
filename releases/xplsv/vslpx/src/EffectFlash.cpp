#include <strings.h>
#include "Demo.h"
extern Demo* miDemo;

#include "EffectFlash.h"

void EffectFlash::play(float _time) {
	int i=0;
	/*char s[255];
	sprintf(s,"effecttest instance %s play %f\n",this->name, _time);
	OutputDebugString(s);*/
	miDemo->ponOrtopedico(2,2);
	
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glColor4f(this->flashColor.x,this->flashColor.y,this->flashColor.z,this->flashColor.w);
	glEnable(GL_BLEND);
	glBlendFunc(this->fac1, this->fac2);
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

void EffectFlash::init() {
	
}

void EffectFlash::start() {
	
}

void EffectFlash::deInit(void) {
	
}

const char* EffectFlash::getEffectType(void) {
	return "EffectFlash";
}

int EffectFlash::setParam(char *paramName, char *attribName, float value) {
	/* 
	Point flashColor;
	GLenum fac1,fac2; // for the blending
	*/
	
	// Setting the COLOR
	if(strcasecmp(paramName,"color")==0) {
		if(strcasecmp(attribName,"r")==0) {
			this->flashColor.x=value;
		}
		if(strcasecmp(attribName,"g")==0) {
			this->flashColor.y=value;
		}
		if(strcasecmp(attribName,"b")==0) {
			this->flashColor.z=value;
		}
		if(strcasecmp(attribName,"a")==0) {
			this->flashColor.w=value;
		}
	}
	// Setting the BLEND values
	if(strcasecmp(paramName,"blend")==0) {
		if(strcasecmp(attribName,"src")==0) {
			this->fac1=(GLuint) value;
		}
		if(strcasecmp(attribName,"dst")==0) {
			this->fac2=(GLuint) value;
		}
	}
	return 0;
}
