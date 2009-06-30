#ifndef FXPARON1_H
#define FXPARON1_H

#include "Effect.h"

#include "Demo.h"
extern Demo *miDemo;
#include "FXfade.h"
extern FXfade *fxfade;

#include "textures.h"
#include "math3D.h"
#include "Camera.h"
#include "FXradialblur.h"
extern FXradialblur *fxradialblur;


class FXparon1: public Effect {
protected:	// las cosas de los muros

	// mi cámara
	static Camera cam;
	// una quadric!!
	static GLUquadricObj *quad;
	static GLUquadricObj *quad2;
	static GLUquadricObj *quad3;
	// textura logo
	static TextureImage textlogo;
	// textura 'laser'
	static TextureImage textlaser;
	
public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXparon1();
	~FXparon1();
};

#endif //FXPARON1_H
