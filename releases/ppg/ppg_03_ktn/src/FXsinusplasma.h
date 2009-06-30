#ifndef FXSINUSPLASMA_H
#define FXSINUSPLASMA_H

#include "Effect.h"

#include "Demo.h"
extern Demo *miDemo;
#include "FXfade.h"
extern FXfade *fxfade;


#include "math3D.h"
#include "Camera.h"
#include "FXradialblur.h"
extern FXradialblur *fxradialblur;

#define NUM_PT_PLASMA_X 64
#define NUM_PT_PLASMA_Y 64


class FXsinusplasma: public Effect {
protected:	// las cosas de los muros

	// puntos / neuronas / lo q sea, joer!
	static Point vertexList[NUM_PT_PLASMA_X][NUM_PT_PLASMA_Y];
	static Point colorList[NUM_PT_PLASMA_X][NUM_PT_PLASMA_Y];

	
	static float xinc,yinc,zinc;
	static float ancho,alto,largo;
	static float lado;
	// mi cámara
	static Camera cam;

	//static TextureImage text_fondo; // tiene que ser algo muy dezign

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXsinusplasma();
	~FXsinusplasma();
};

#endif //FXSINUSPLASMA_H
