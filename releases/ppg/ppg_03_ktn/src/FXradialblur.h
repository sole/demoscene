#ifndef FXRADIALBLUR_H
#define FXRADIALBLUR_H

#include "Effect.h"

#include "Demo.h"
extern Demo *miDemo;

#include "textures.h"
#include "math3D.h"

#define TEXTBLURSIZE 256

class FXradialblur: public Effect {
protected:	
	/* vars */
	static int viewWidth, viewHeight; // aqui me guardo el tamaño del viewport para restaurarlo
	static GLuint BlurTexture;
	static int times;
	static float inc;
	/* funciones */
	static GLuint EmptyTexture();
	static float ccr,ccg,ccb,cca;
	static GLenum fac1,fac2;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);

	void setClearColor(float r,float g,float b,float a);
	void setBlendFunc(GLenum fac1,GLenum fac2);
	void setView(int _width,int _height); // que si no se trona--> tamaño del viewport
	void setTimes(int _times); // num veces q se repite el blur
	void setInc(float _inc); // diferencia entre blurs ('densidad')
	void prepareFrame(void);
	void postprepareFrame(void);
	FXradialblur();
	~FXradialblur();
};

#endif //FXRADIALBLUR_H
