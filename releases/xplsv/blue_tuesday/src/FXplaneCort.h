#ifndef FXPLANECORT_H
#define FXPLANECORT_H

#include "Effect.h"
#include "math3D.h"
#include "Demo.h"
#include "textures.h"

extern Demo *miDemo;

class FXplaneCort: public Effect {
protected:

	float porc;

	// aqui me guardo el color base del plano
	Point planeColor;
	GLenum fac1,fac2;

	// la textura a aplicar en el plano
	char textureName[255];
	TextureImage planeData;
public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	void setPlaneColor(float r,float g, float b, float a);
	void setBlendFunc(GLenum fac1,GLenum fac2);
	void setTextureName(char *filename);
	void setPorc(float _porc);

	FXplaneCort();
	~FXplaneCort();
};

#endif //FXPLANECORT_H
