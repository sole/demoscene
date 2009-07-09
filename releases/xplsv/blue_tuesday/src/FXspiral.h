#ifndef FXSPIRAL_H
#define FXSPIRAL_H

#include <math.h>
#include "Effect.h"
#include "math3D.h"
#include "Demo.h"
#include "textures.h"
#include "my_opengl.h"

extern Demo *miDemo;

#define SPIRAL_VTX 1200

class FXspiral: public Effect {
protected:

	// aqui me guardo el color base de cada quad
	Point planeColor;
	Point borderColor;
	GLenum fac1,fac2;

	// puntos que forman la espiral
	Point vertexList[SPIRAL_VTX];

	// la textura a aplicar en cada quad
	char textureName[255];
	TextureImage planeData;

	float radioinc;
	unsigned int pos;

	float tUpdate; // cuanto tiempo tarda en actualizar su "gravedad"
	Point gravity;
	float tamSeg;

	float width;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	void setPlaneColor(float r,float g, float b, float a);
	void setBorderColor(float r, float g, float b, float a);
	void setGravity(float x, float y, float z, float w);
	void setBlendFunc(GLenum fac1,GLenum fac2);
	void setTextureName(char *filename);
	void setWidth(float _w);

	void pushPoint(float _yvalue);

	FXspiral();
	~FXspiral();
};

#endif //FXSPIRAL_H
