#ifndef MUROS_H
#define MUROS_H

#include "Effect.h"

#include "Demo.h"
extern Demo *miDemo;

#include "FXfade.h"
extern FXfade *fxfade;

#include "textures.h"
#include "math3D.h"
#include <math.h>

#define X_SLICES 10
#define Y_SLICES 40

class FXmuros: public Effect {
protected:	// las cosas de los muros

	// malla para poner los graffitis sobre los muros. 
	// aqui me guardo x e y
	static float bannerMesh[X_SLICES][Y_SLICES][2]; 
	// una auxiliar
	static float bannerMeshAux[X_SLICES][Y_SLICES][2];
	// y aqui me guardo x e y de la textura
	static float bannerText[X_SLICES][Y_SLICES][2]; 

	static TextureImage text_gfx_ppg;
	static TextureImage text_gfx_presents;
	static TextureImage text_gfx_ademo;
	static TextureImage text_gfx_called;
	static TextureImage text_gfx_logokillo;


	static TextureImage text_gfx_notpm;
	static TextureImage text_gfx_supernena;
public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);

	FXmuros();
	~FXmuros();
};

#endif //MUROS_H
