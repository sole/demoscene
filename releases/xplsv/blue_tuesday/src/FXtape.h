#ifndef FXTAPE_H
#define FXTAPE_H

#include <math.h>
#include "Effect.h"
#include "math3D.h"
#include "Demo.h"
#include "textures.h"
#include "CurvaBezier.h"
#include "Path.h"
#include "my_opengl.h"

extern Demo *miDemo;

class FXtape: public Effect {
protected:

	// aqui me guardo el color base de cada quad
	Point planeColor;
	Point borderColor;
	GLenum fac1,fac2;

	// puntos que forman la cinta
	unsigned int numVertex;
	Point *vertexList;

	// curvas que forman la cinta
	unsigned int numCurves;
	CurvaBezier *curveList;

	// precisión de cada curva (numero de tramos)
	unsigned int curvePrecision;
	Punto *tramosTemp;

	// la textura a aplicar en cada quad
	char textureName[255];
	TextureImage planeData;

	// en que curva empieza a dibujar
	unsigned int startDrawingCurve;
	
	// tramos a dibujar de la curva
	unsigned int numDrawParts;

	// Algunos parámetros para el dibujado de cada segmento y tal...
	float width, height;

	// El truco del almendruco!!!!!!
	Path miPath;
	char filePath[255];

	// ult punto & direccion
	Point lastPoint;
	Point lastLook;

	unsigned char withTexture;
public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	void setPlaneColor(float r,float g, float b, float a);
	Point getPlaneColor(void);
	void setBorderColor(float r, float g, float b, float a);
	void setBlendFunc(GLenum fac1,GLenum fac2);
	void setTextureName(const char *filename);
	void setPathName(const char *filename);

	void setPointAt(unsigned int index, float x, float y, float z, float w);
	Point getPointAt(unsigned int index);
	void setCurvePrec(unsigned int prec);
	unsigned int getCurvePrec(void);
	void setStartDrawingCurve(unsigned int _start);
	
	void setNumVertex(unsigned int num);
	unsigned int getNumVertex(void);
	void setNumDrawParts(unsigned int num);
	unsigned int getNumDrawParts(void);
	void setHeight(float _h);
	void setWidth(float _w);


	Point getLastPoint(void); // devuelve el vector posicion del ultimo punto dibujado
	Point getLastLook(void); // vector direccional blabla

	FXtape();
	~FXtape();
};

#endif //FXTAPE_H
