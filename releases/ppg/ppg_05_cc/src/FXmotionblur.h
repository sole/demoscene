#ifndef FXMOTIONBLUR_H
#define FXMOTIONBLUR_H

#include "Effect.h"

#include "Demo.h"
extern Demo *miDemo;

#include "textures.h"
#include "math3D.h"

#define TEXTBLURSIZE 256

class FXmotionblur: public Effect {
protected:	
	/* vars */
	static int viewWidth, viewHeight; // aqui me guardo el tamaño del viewport para restaurarlo
	static GLuint BlurTexture;
	static int times;
	static float inc;
	unsigned char buffer[TEXTBLURSIZE*TEXTBLURSIZE*4];

	int textWidth, textHeight;
	/* funciones */
	GLuint EmptyTexture();
	static float ccr,ccg,ccb,cca;
	static GLenum fac1,fac2;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);

	void setTextureSize(int width, int height);
	void setClearColor(float r,float g,float b,float a);
	void setBlendFunc(GLenum fac1,GLenum fac2);
	void setView(int _width,int _height); // que si no se trona--> tamaño del viewport
	void setTimes(int _times); // num veces q se repite el blur
	void setInc(float _inc); // diferencia entre blurs ('densidad')
	void prepareFrame(void);
	void postprepareFrame(void);
	FXmotionblur();
	~FXmotionblur();
};

#endif //FXMOTIONBLUR_H
