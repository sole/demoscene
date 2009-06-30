#ifndef FXRUEDA_H
#define FXRUEDA_H

#include "Effect.h"

#include "Demo.h"
extern Demo *miDemo;
#include "FXfade.h"
extern FXfade *fxfade;
#include "textures.h"
#include "math3D.h"
#include "Camera.h"
#include "Particles.h"
#include "FXradialblur.h"
extern FXradialblur *fxradialblur;

#define NUMPOINTS 4*4
#define NUMVERTEX (NUMPOINTS*4)
#define RUEDAMAXPARTICLES 15
class FXrueda: public Effect {
protected:	// las cosas de los muros
	// La rueda de la fortuna!
	Point ruedaQuadVertex[NUMVERTEX];
	
	// mi cámara
	static Camera cam;
	// imágenes
	static TextureImage text_fondo;
	static TextureImage text_ford;
	static TextureImage text_particula;
	
	
	// Mega sistema de partículas
	ParticleSystem parts1;
	ParticleManager partm1;
	Particle misparticulas[RUEDAMAXPARTICLES];
	Point orisis;

	//
	static float radio1,radio2;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void marear(float par1, float par2);
	void stop(void);

	FXrueda();
	~FXrueda();
};

#endif //FXRUEDA_H
