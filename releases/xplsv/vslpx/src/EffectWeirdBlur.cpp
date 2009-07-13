#include "EffectWeirdBlur.h"
#include "math3D.h"
#include <strings.h>
#include "Demo.h"
extern Demo* miDemo;

#define TEXTRADIALBLURSIZE 512

void EffectWeirdBlur::play(float _time) {
						
	int nCurrentRadius=1;
	int nRadius=TEXTRADIALBLURSIZE;

	glDisable(GL_TEXTURE_2D);
	//glEnable(GL_TEXTURE_2D);									
	//glDisable(GL_DEPTH_TEST);
	// Set Blending Mode
	//glEnable(GL_BLEND);											
	glBlendFunc(this->fac1,this->fac2);
	glBindTexture(GL_TEXTURE_2D,this->myTexture->texID);					
	
	/* vieworto*/
	glMatrixMode(GL_PROJECTION);							
	glPushMatrix();												
	glLoadIdentity();											
	glOrtho(0 ,TEXTRADIALBLURSIZE , 0,TEXTRADIALBLURSIZE , -1, 1000);		
	
	glMatrixMode(GL_MODELVIEW);									
	glPushMatrix();												
	glLoadIdentity();													
	/* end_vieworto*/

	static float w=TEXTRADIALBLURSIZE;//float(viewWidth);
	static float h=TEXTRADIALBLURSIZE;//float(viewHeight);
	//glBindTexture(GL_TEXTURE_2D,BlurTexture);
	float pasadas=nRadius/nCurrentRadius;
	float ainc=1.0/pasadas;
	int i=1;


	while(nCurrentRadius <= nRadius) {
		//glEnable(GL_TEXTURE_2D);
		//CopyToTexture(pTexture);
		glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0,TEXTRADIALBLURSIZE,TEXTRADIALBLURSIZE);
		//DrawPixelScaledQuad(pTexture, nCurrentRadius);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0 /*1-ainc*i*/);
		glBegin(GL_LINE_STRIP);
		glTexCoord2f(0,0);						
		glVertex2f(0,0);									

		glTexCoord2f(1,0);						
		glVertex2f(w+nCurrentRadius,0);								

		glTexCoord2f(1,1);						
		glVertex2f(w+nCurrentRadius,h+nCurrentRadius);							

		glTexCoord2f(0,1);						
		glVertex2f(0,h+nCurrentRadius);	
		glEnd();

		nCurrentRadius = nCurrentRadius * 2;
		i++;
		
		
	}
	glMatrixMode(GL_MODELVIEW);glPopMatrix();
	glMatrixMode(GL_PROJECTION);glPopMatrix();
//_-------------------------------------------------
	//miDemo->ponOrtopedico(2,1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);glPushMatrix();glLoadIdentity();
	glViewport(0,0,DEMOWIDTH,DEMOHEIGHT);
	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	

	//glBindTexture(GL_TEXTURE_2D, BlurTexture);
	//glColor4f(ccr,ccg,ccb,1);
	glColor4f(1,1,1,1);
		glBegin(GL_LINE_STRIP);
		glTexCoord2f(0,0);						
		glVertex2f(0,0);									

		glTexCoord2f(1,0);						
		glVertex2f(w,0);								

		glTexCoord2f(1,1);						
		glVertex2f(w,h);							

		glTexCoord2f(0,1);						
		glVertex2f(0,h);	
		
	glEnd();


	miDemo->ejes();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
		//miDemo->quitaOrtopedico();


	glMatrixMode( GL_PROJECTION );							
	glPopMatrix();		
	
	
	
	
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,0);	


}

void EffectWeirdBlur::init() {
	this->myTexture = miDemo->getTextureById(this->textureId);
}

void EffectWeirdBlur::start() {
	
}

void EffectWeirdBlur::deInit(void) {
	
}

const char* EffectWeirdBlur::getEffectType(void) {
	return "EffectWeirdBlur";
}

int EffectWeirdBlur::setParam(char *paramName, char *attribName, float value) {	
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
