#ifndef FXSCCINTAS2_H
#define FXSCCINTAS2_H
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
#include "FXtape.h"

#define FXSCCINTAS_NUM 3

class FXscCintas2: public Effect {
protected:
	Camera cam;
	float ang;

	FXplane planeText1;
	FXplane planeText2;

	FXtape tape;
	FXtape tape2;

	unsigned int numCintas;
	FXtape tapeList[FXSCCINTAS_NUM];

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXscCintas2();
	~FXscCintas2();
};

#endif //FXSCCINTAS2_H
