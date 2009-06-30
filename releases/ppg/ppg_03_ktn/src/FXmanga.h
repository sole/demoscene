#ifndef MANGA_H
#define MANGA_H

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

#define X_SLICES 10
#define Y_SLICES 40

class FXmanga: public Effect {
protected:	// las cosas de los muros

	// malla para poner los graffitis sobre los muros. 
	// aqui me guardo x e y
	static float bannerMesh[X_SLICES][Y_SLICES][2]; 
	// una auxiliar
	static float bannerMeshAux[X_SLICES][Y_SLICES][2];
	// y aqui me guardo x e y de la textura
	static float bannerText[X_SLICES][Y_SLICES][2]; 

	// mi cámara
	static Camera cam;
	// imágenes
	static TextureImage text_oso;
	static TextureImage text_k;

	// quadricas (a ver qué pasa!!)
	static GLUquadricObj *quad;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);

	FXmanga();
	~FXmanga();
};

#endif //MANGA_H
