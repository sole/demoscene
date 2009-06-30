#ifndef FXESPACIOK_H
#define FXESPACIOK_H

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

#define NUM_PT_ESP_X 8
#define NUM_PT_ESP_Y 8
#define NUM_PT_ESP_Z 8

#define NUM_PT_ESP_TUNEL 8

#define NUM_PT_ESP (NUM_PT_ESP_X*NUM_PT_ESP_Y*NUM_PT_ESP_Z)

class FXespaciok: public Effect {
protected:	// las cosas de los muros

	// puntos / neuronas / lo q sea, joer!
	static Point pointList[NUM_PT_ESP];
	static Point pointListTunel[NUM_PT_ESP_TUNEL];
	
	static float xinc,yinc,zinc;
	static float ancho,alto,largo;
	static float lado;

	static float tunellargo;
	// mi cámara
	static Camera cam;
	// imágenes
	static TextureImage text_k;
	static TextureImage text_tunel;

	static TextureImage text_chemical;
	static TextureImage text_creditos_aux;
	static TextureImage text_staff;
	static TextureImage text_sole;
	static TextureImage text_sara;
	static TextureImage text_theyhave;
	static TextureImage text_greets01;
	static TextureImage text_greets02;
	static TextureImage text_greets03;
	static TextureImage text_greets04;
	static TextureImage text_allez;
	static TextureImage text_epileptics;

	static TextureImage text_mascara;

	//static TextureImage text_fondo; // tiene que ser algo muy dezign

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	FXespaciok();
	~FXespaciok();
};

#endif //FXESPACIOK_H
