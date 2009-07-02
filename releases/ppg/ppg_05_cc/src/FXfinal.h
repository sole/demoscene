#ifndef FXFINAL_H
#define FXFINAL_H
#include <math.h>
#include "Effect.h"
#include "math3D.h"
#include "Camera.h"
#include "Demo.h"
extern Demo *miDemo;

#include "FXmotionblur.h"
extern FXmotionblur *fxmotionblur;

#include "Music.h"
extern Music miMusic;

#include "Cube.h"
#include "Sphere.h"

class FXfinal: public Effect {
protected:
	Camera cam;
	float ang;

	Cube unCubo;
	Sphere unaEsfera;
	TextureImage layerFinal01;
	TextureImage layerFinal02;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXfinal();
	~FXfinal();
};

#endif //FXFINAL_H
