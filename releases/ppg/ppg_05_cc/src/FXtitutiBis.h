#ifndef FXTITUTIBIS_H
#define FXTITUTIBIS_H
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
#include "FXvstripes.h"

class FXtitutiBis: public Effect {
protected:
	Camera cam;
	float ang;

	Cube unCubo;
	Sphere unaEsfera;
	TextureImage layerGreets;
	TextureImage textHalo;
	FXvstripes fxGreets;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	void squarePlane(TextureImage *_texture);// dibuja un cuadrado de 1x1 centrado en 0,0,0, con coord's de textura

	FXtitutiBis();
	~FXtitutiBis();
};

#endif //FXTITUTIBIS_H
