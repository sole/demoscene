#ifndef FXSCCINTAS_H
#define FXSCCINTAS_H
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

#include "FXplane.h"
#include "FXspiral.h"
#include "FXtape.h"

#define FXSCCINTAS_NUM 3

class FXscCintas: public Effect {
protected:
	Camera cam;
	float ang;

	FXplane planeText1;
	FXplane planeText2;

	FXspiral spiral;
	
	unsigned int numCintas;
	FXtape tapeList[FXSCCINTAS_NUM];

	float startTime;
public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXscCintas();
	~FXscCintas();
};

#endif
