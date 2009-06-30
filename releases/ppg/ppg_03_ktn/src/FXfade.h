#ifndef FXFADE_H
#define FXFADE_H

#include "Effect.h"
#include "math3D.h"
#include "Demo.h"
extern Demo *miDemo;

class FXfade: public Effect {
protected:

	// aqui me guardo el color de los flashes
	Point fadeColor;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	void setFadeColor(float r,float g, float b, float a);
	FXfade();
	~FXfade();
};

#endif //FXFADE_H
