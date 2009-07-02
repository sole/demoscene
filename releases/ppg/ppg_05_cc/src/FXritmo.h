#ifndef FXRITMO_H
#define FXRITMO_H
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

class FXritmo: public Effect {
protected:
	Camera cam;
	float ang;

	Cube unCubo;
	Sphere unaEsfera;
	TextureImage layerTitle;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXritmo();
	~FXritmo();
};

#endif //FXRITMO_H
