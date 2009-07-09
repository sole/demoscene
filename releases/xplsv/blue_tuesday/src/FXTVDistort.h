#ifndef FXTVDISTORT_H
#define FXTVDISTORT_H

#include "Effect.h"

#include "Demo.h"
extern Demo *miDemo;

#include "textures.h"
#include "math3D.h"
#include "my_opengl.h"

#define TEXTBLURSIZE 256
#define TVDISTORTINTERV 100
#define TVD_NUMPARAMS 2
#define TVD_PARAM_V 0 // vertical module or effect
#define TVD_PARAM_POWER 1 // "how much" effect is applied | de 0 a 1!

class FXTVDistort: public Effect {
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

	float xMax, yMax;

	float texPos[TVDISTORTINTERV+1][TVDISTORTINTERV+1][3];
	float quadPos[TVDISTORTINTERV+1][TVDISTORTINTERV+1][3];
	float randQuadPos[TVDISTORTINTERV+1][TVDISTORTINTERV+1][3];
	float quad[TVDISTORTINTERV+1][TVDISTORTINTERV+1][3];
	float normalInterv[TVDISTORTINTERV+1];
	float normalMagnit[TVDISTORTINTERV+1];

	float params[TVD_NUMPARAMS];

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

	void setParam(unsigned int pOffset, float pValue);
	FXTVDistort();
	~FXTVDistort();
};

#endif //FXTVDISTORT_H
