#ifndef FXSCCUADRICULA_H
#define FXSCCUADRICULA_H
#include <math.h>
#include "Effect.h"
#include "math3D.h"
#include "Camera.h"
#include "Demo.h"
extern Demo *miDemo;

#include "FXfade.h"
extern FXfade *fxfade;

#include "Music.h"
extern Music miMusic;

#include "FXTVDistort.h"
extern FXTVDistort *fxtvdistort;

#include "FXplane.h"

#include "FXspiral.h"
#include "FXtape.h"

#define FXSCCUADRICULA_NUM 5
#define FXSCCUADRICULA_NUMPLUS 20

class FXscCuadricula: public Effect {
protected:
	Camera cam;
	float ang;

	FXplane planeText1;
	FXplane planeText2;

	FXspiral spiral;
	FXtape tape;
	FXtape tape2;
	FXtape tape3;

	unsigned int numCintas;
	FXtape tapeList[FXSCCUADRICULA_NUM];

	Point pointList[FXSCCUADRICULA_NUMPLUS*FXSCCUADRICULA_NUMPLUS*FXSCCUADRICULA_NUMPLUS];

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXscCuadricula();
	~FXscCuadricula();
};

#endif //FXSCCUADRICULA_H
