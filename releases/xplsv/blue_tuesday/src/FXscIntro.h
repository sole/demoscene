#ifndef FXSCINTRO_H
#define FXSCINTRO_H
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


class FXscIntro: public Effect {
protected:
	Camera cam;
	float ang;

	FXplane planeText1;
	FXplane planeText2;
	FXplane planeText3;
	FXplane planeText4;
	
	FXspiral spiral;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXscIntro();
	~FXscIntro();
};

#endif //FXSCINTRO_H
