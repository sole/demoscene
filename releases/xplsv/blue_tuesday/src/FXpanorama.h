#ifndef FXPANORAMA_H
#define FXPANORAMA_H

#include "Effect.h"
#include "math3D.h"
#include "Demo.h"
extern Demo *miDemo;

class FXpanorama: public Effect {
protected:

	// aqui me guardo el color de las barras de panorama
	Point panColor;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	void setPanColor(float r,float g, float b, float a);
	FXpanorama();
	~FXpanorama();
};

#endif //FXPANORAMA_H
