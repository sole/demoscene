#include "EffectMotionBlur.h"
#include "math3D.h"
#include <strings.h>
#include "Demo.h"
#include "my_opengl.h"
extern Demo* miDemo;

void EffectMotionBlur::play(float _time) {
						
	miDemo->ponOrtopedico(this->width,this->height);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,this->myTexture->texID);
	// Enable blending
	glEnable(GL_BLEND);
	// TODO: Assign custom blending values
	glBlendFunc(this->fac1,this->fac2);
	// TODO: Improve the size of the viewport & co to avoid rescaling of the image :-S
	glMatrixMode(GL_MODELVIEW);glPushMatrix();glLoadIdentity();
	static float xMax = float(this->width)/this->myTexture->width*1.0f;
	static float yMax = float(this->height)/this->myTexture->height*1.0f;
	static float xt=this->width*0.5; // xtremo
	static float yt=this->height*0.5;
	float z_depth=float(-0.0121);
	float dp=0;
	glColor4f(this->textColor.x,this->textColor.y,this->textColor.z,this->textColor.w);
	//glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0); 
		glVertex3f(-xt,-yt,z_depth);
		
		glTexCoord2f(xMax,0);
		glVertex3f(xt,-yt, z_depth);

		glTexCoord2f(xMax,yMax);
		glVertex3f(xt,yt,  z_depth);

		glTexCoord2f(0,yMax);
		glVertex3f(-xt,yt,z_depth);

	glEnd();

	glDisable(GL_BLEND);
	glMatrixMode(GL_MODELVIEW);glPopMatrix();
	
	miDemo->quitaOrtopedico();

	/*//miDemo->ponOrtopedico(7.97,3.97);
	miDemo->ponOrtopedico(miDemo->getWidth(),miDemo->getHeight());
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	glBlendFunc(this->fac1,this->fac2);
	glBindTexture(GL_TEXTURE_2D,this->myTexture->texID);
	miDemo->checkGLerror("EffectMotionBlur-aft glBindTexture");
	glMatrixMode(GL_MODELVIEW);glPushMatrix();glLoadIdentity();
	static float xMax = this->width/this->myTexture->width;
	static float yMax = this->height/this->myTexture->height;
	static float xt=1; // xtremo
	static float xt2=xt*2;
	float z_depth=float(0.02);
	float dp=0;
	//glColor4f(this->textColor.x,this->textColor.y,this->textColor.z,this->textColor.w);
	glColor4f(1,1,1,1);
	glBegin(GL_LINE_STRIP);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0); 
		glVertex3f(-xt2+dp,-xt,z_depth);
		
		glTexCoord2f(xMax,0);
		glVertex3f(xt2+dp,-xt, z_depth);

		glTexCoord2f(xMax,yMax);
		glVertex3f(xt2+dp,xt,  z_depth);

		glTexCoord2f(0,yMax);
		glVertex3f(-xt2+dp,xt,z_depth);

	glEnd();
	miDemo->ejes();
		glMatrixMode(GL_MODELVIEW);glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	miDemo->quitaOrtopedico();	*/


}

void EffectMotionBlur::init() {
	this->myTexture = miDemo->getTextureById(this->textureId);
}

void EffectMotionBlur::start() {
	
}

void EffectMotionBlur::deInit(void) {
	
}

const char* EffectMotionBlur::getEffectType(void) {
	return "EffectMotionBlur";
}

int EffectMotionBlur::setParam(char *paramName, char *attribName, float value) {	
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
	// Setting the COLOR
	if(strcasecmp(paramName,"color")==0) {
		if(strcasecmp(attribName,"r")==0) {
			this->textColor.x=value;
		}
		if(strcasecmp(attribName,"g")==0) {
			this->textColor.y=value;
		}
		if(strcasecmp(attribName,"b")==0) {
			this->textColor.z=value;
		}
		if(strcasecmp(attribName,"a")==0) {
			this->textColor.w=value;
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
