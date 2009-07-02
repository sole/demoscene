#include "FXmotionblur.h"
#include <math.h>
#include "math3D.h"

// inicializar lo estático aquí...
GLuint FXmotionblur::BlurTexture;
int FXmotionblur::viewWidth;
int FXmotionblur::viewHeight;
float FXmotionblur::inc;
int FXmotionblur::times;
float FXmotionblur::ccr;
float FXmotionblur::ccg;
float FXmotionblur::ccb;
float FXmotionblur::cca;
GLenum FXmotionblur::fac1;
GLenum FXmotionblur::fac2
;
// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

GLuint FXmotionblur::EmptyTexture() {
	GLuint txtnumber;
	unsigned int* data;	


	data = (unsigned int*)new GLuint[((this->textWidth * this->textHeight)* 4 * sizeof(unsigned int))];
	
	glGenTextures(1, &txtnumber);								
	glBindTexture(GL_TEXTURE_2D, txtnumber);					
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->textWidth, this->textHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);						
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	delete [] data;												

	return txtnumber;											

}

void FXmotionblur::setView(int _width, int _height) {
	this->viewWidth=_width;
	this->viewHeight=_height;
}

void FXmotionblur::setTimes(int _times) {
	// num veces q se repite el blur
	this->times=_times;
}
void FXmotionblur::setInc(float _inc) {
	// diferencia entre blurs ('densidad')
	this->inc=_inc;
}

void FXmotionblur::setClearColor(float r,float g,float b,float a) {
	ccr=r;
	ccg=g;
	ccb=b;
	cca=a;
}

void FXmotionblur::setBlendFunc(GLenum fac1,GLenum fac2) {
	this->fac1=fac1;
	this->fac2=fac2;
}
void FXmotionblur::prepareFrame(void) {
	// el viewport se pone del tamaño de la textura de blur (TEXTBLURSIZE)
	glViewport(0,0, this->textWidth, this->textHeight); 
	// en demo: 	glViewport(0,0,this->width,this->height);

}

void FXmotionblur::postprepareFrame(void) {
	glBindTexture(GL_TEXTURE_2D,BlurTexture);					

	glCopyTexSubImage2D(GL_TEXTURE_2D,// target
		0, //level mipmaps
		0, //xoffset
		0, // yoffset
		0, // x
		0, //y
		miDemo->getWidth(), // width
    	miDemo->getHeight()  //height 		
    	);
}


// Funciones a definir desde Effect.h
void FXmotionblur::perFrame(float time) {

	
	miDemo->ponOrtopedico(7.98,3.98/*7.97,3.97*/);

	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(this->fac1,this->fac2);
	glBindTexture(GL_TEXTURE_2D,BlurTexture);

	static float xt=2; // xtremo
	static float xt2=xt*2;
	float z_depth=float(0.02);
	float dp=0;
	float x_offset = miDemo->getWidth() * 1.0f / this->textWidth;
	float y_offset = miDemo->getHeight() * 1.0f / this->textHeight;
	
	glColor4f(ccr,ccg,ccb,cca);
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0); 
	glVertex3f(-xt2+dp,-xt,z_depth);
	
	glTexCoord2f(x_offset ,0);
	glVertex3f(xt2+dp,-xt, z_depth);

	glTexCoord2f(x_offset, y_offset);
	glVertex3f(xt2+dp,xt,  z_depth);

	glTexCoord2f(0, y_offset);
	glVertex3f(-xt2+dp,xt,z_depth);
	glEnd();
	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	miDemo->quitaOrtopedico();	
}

void FXmotionblur::setTextureSize(int width, int height) {
	this->textWidth=width;
	this->textHeight=height;
}
void FXmotionblur::init(void) {
	// asignar recursos y tal, cargar ficheros, blabla
	
	this->setTextureSize(clp2(miDemo->getWidth()), clp2(miDemo->getHeight()));
	BlurTexture = EmptyTexture();								
	ccr=0.7;
	ccg=0;
	ccb=0.7;
	cca=0.3;
	fac1=GL_SRC_ALPHA;
	fac2=GL_ONE_MINUS_SRC_ALPHA;
}

void FXmotionblur::start(void) {
}

void FXmotionblur::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	glDeleteTextures(1,&BlurTexture);							
}

FXmotionblur::FXmotionblur() {
}

FXmotionblur::~FXmotionblur() {
}
