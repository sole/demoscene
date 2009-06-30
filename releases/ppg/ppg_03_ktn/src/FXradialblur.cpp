#include "FXradialblur.h"
#include <math.h>
// inicializar lo estático aquí...
GLuint FXradialblur::BlurTexture;
int FXradialblur::viewWidth;
int FXradialblur::viewHeight;
float FXradialblur::inc;
int FXradialblur::times;
float FXradialblur::ccr;
float FXradialblur::ccg;
float FXradialblur::ccb;
float FXradialblur::cca;
GLenum FXradialblur::fac1;
GLenum FXradialblur::fac2
;
// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover
// un prepareFrame , para dibujar y luego hacer perframe
// guardar los parametros para hacer varios tipos de radialblur (girando swirl, volumetrico...)

GLuint FXradialblur::EmptyTexture() {
	GLuint txtnumber;											// Texture ID
	unsigned int* data;											// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((TEXTBLURSIZE * TEXTBLURSIZE)* 4 * sizeof(unsigned int))];
	//ZeroMemory(data,((TEXTBLURSIZE * TEXTBLURSIZE)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, TEXTBLURSIZE, TEXTBLURSIZE, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);						// Build Texture Using Information In data
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data

	return txtnumber;											// Return The Texture ID

}

void FXradialblur::setView(int _width, int _height) {
	this->viewWidth=_width;
	this->viewHeight=_height;
}

void FXradialblur::setTimes(int _times) {
	// num veces q se repite el blur
	this->times=_times;
}
void FXradialblur::setInc(float _inc) {
	// diferencia entre blurs ('densidad')
	this->inc=_inc;
}

void FXradialblur::setClearColor(float r,float g,float b,float a) {
	ccr=r;
	ccg=g;
	ccb=b;
	cca=a;
}

void FXradialblur::setBlendFunc(GLenum fac1,GLenum fac2) {
	this->fac1=fac1;
	this->fac2=fac2;
}
void FXradialblur::prepareFrame(void) {
	// el viewport se pone del tamaño de la textura de blur (TEXTBLURSIZE)
	glViewport(0,0,TEXTBLURSIZE,TEXTBLURSIZE); 
	// en demo: 	glViewport(0,0,this->width,this->height);

}

void FXradialblur::postprepareFrame(void) {
	glBindTexture(GL_TEXTURE_2D,BlurTexture);					// Bind To The Blur Texture

	// Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, TEXTBLURSIZE, TEXTBLURSIZE, 0);

	glClearColor(ccr,ccg,ccb,cca);						// Set The Clear Color To Medium Blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And Depth Buffer

	glViewport(0,0,viewWidth,viewHeight);		
}


// Funciones a definir desde Effect.h
void FXradialblur::perFrame(float time) {
	float spost = 0.0f;											// Starting Texture Coordinate Offset
	float alphainc;// = 0.9f / times;								// Fade Speed For Alpha Blending
	float alpha = cca;//0.2f;											// Starting Alpha Value

	glEnable(GL_TEXTURE_2D);									// Enable 2D Texture Mapping
	glDisable(GL_DEPTH_TEST);									// Disable Depth Testing
	glBlendFunc(this->fac1,this->fac2);
						// Set Blending Mode
	glEnable(GL_BLEND);											// Enable Blending
	glBindTexture(GL_TEXTURE_2D,BlurTexture);					// Bind To The Blur Texture
	
	/* vieworto*/
	glMatrixMode(GL_PROJECTION);								// Select Projection
	glPushMatrix();												// Push The Matrix
	glLoadIdentity();											// Reset The Matrix
	// en DEMO:	glOrtho(-float(xres)/2,float(xres)/2,-float(yres)/2,float(yres)/2,0.10f,200.0f);

	glOrtho( 0,viewWidth ,viewHeight , 0, -1, 1000);		// Select Ortho Mode (640x480)
	glMatrixMode(GL_MODELVIEW);									// Select Modelview Matrix
	glPushMatrix();												// Push The Matrix
	glLoadIdentity();													// Switch To An Ortho View
	/* end_vieworto*/
	//glTranslatef(0,0,2);
	alphainc = alpha / times;									// alphainc=0.2f / Times To Render Blur
	
	glBegin(GL_QUADS);											// Begin Drawing Quads
		for (int num = 0;num < times;num++)						// Number Of Times To Render Blur
		{
		
			glColor4f(1.0f, 1.0f, 1.0f, alpha);					// Set The Alpha Value (Starts At 0.2)
			glTexCoord2f(0+spost,1-spost);						// Texture Coordinate	( 0, 1 )
			glVertex2f(0,0);									// First Vertex		(   0,   0 )

			glTexCoord2f(0+spost,0+spost);						// Texture Coordinate	( 0, 0 )
			glVertex2f(0,float(viewHeight));									// Second Vertex	(   0, 480 )

			glTexCoord2f(1-spost,0+spost);						// Texture Coordinate	( 1, 0 )
			glVertex2f(float(viewWidth),float(viewHeight));								// Third Vertex		( 640, 480 )

			glTexCoord2f(1-spost,1-spost);						// Texture Coordinate	( 1, 1 )
			glVertex2f(float(viewWidth),0);									// Fourth Vertex	( 640,   0 )

			spost += inc;										// Gradually Increase spost (Zooming Closer To Texture Center)
			alpha = alpha - alphainc;							// Gradually Decrease alpha (Gradually Fading Image Out)
		}
	glEnd();													// Done Drawing Quads
	
	/* viewpersp*/										// Switch To A Perspective View
	glMatrixMode( GL_PROJECTION );								// Select Projection
	glPopMatrix();												// Pop The Matrix
	glMatrixMode( GL_MODELVIEW );								// Select Modelview
	glPopMatrix();	/**/
	/* end_viewpersp */
	
	
	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glDisable(GL_TEXTURE_2D);									// Disable 2D Texture Mapping
	glDisable(GL_BLEND);										// Disable Blending
	glBindTexture(GL_TEXTURE_2D,0);								// Unbind The Blur Texture
}


void FXradialblur::init(void) {
	// asignar recursos y tal, cargar ficheros, blabla
	BlurTexture = EmptyTexture();								// Create Our Empty Texture
	ccr=0.7;
	ccg=0;
	ccb=0.7;
	cca=0.2;
	fac1=GL_SRC_ALPHA;
	fac2=GL_SRC_COLOR;
	
}

void FXradialblur::start(void) {
	
}

void FXradialblur::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	glDeleteTextures(1,&BlurTexture);							// Delete The Blur Texture
}

FXradialblur::FXradialblur() {
}

FXradialblur::~FXradialblur() {
}