#ifndef FXSCOTRA_H
#define FXSCOTRA_H
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

#define FXSCOTRA_NUM 6
#define FXSCOTRA_NUM2 6
#define FXSCOTRA_NUMPLUS 20

class FXscOtra: public Effect {
protected:
	Camera cam;
	float ang;

	FXspiral spiral;
	FXtape tape;

	unsigned int numCintas;
	FXtape tapeList[FXSCOTRA_NUM];
	FXtape tapeList2[FXSCOTRA_NUM2];

	Point pointList[FXSCOTRA_NUMPLUS*FXSCOTRA_NUMPLUS*FXSCOTRA_NUMPLUS];

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXscOtra();
	~FXscOtra();
};

#endif //FXSCOTRA_H
