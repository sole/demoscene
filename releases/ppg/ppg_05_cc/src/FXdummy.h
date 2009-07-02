#ifndef FXDUMMY_H
#define FXDUMMY_H
#include <math.h>
#include "Effect.h"
#include "math3D.h"
#include "Camera.h"
#include "Demo.h"
#include "textures.h"
extern Demo *miDemo;

#include "FXmotionblur.h"
extern FXmotionblur *fxmotionblur;

#include "Music.h"
extern Music miMusic;

#include "Cube.h"
#include "Sphere.h"

class FXdummy: public Effect {
protected:
	Camera cam;
	float ang;

	Cube unCubo;
	Sphere unaEsfera;

	TextureImage layerWelcome;
	TextureImage layerTitle;
	TextureImage layerMierda;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXdummy();
	~FXdummy();
};

#endif //FXDUMMY_H
