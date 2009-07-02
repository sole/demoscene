#ifndef SHAPE_H
#define SHAPE_H

#include "Node.h"

class Shape: public Node {
protected:
	// cuantos vertices tengo?
	int numVertex;

	// la lista de vertices
	Point *vertexList;
	
	// tambien esta bien tener una lista de caras ;)
	// son trianguladas asi q guardare una cara con 3 vertices...
	int numFaces;
	int *faceList1;
	int *faceList2;
	int *faceList3;

	// Faltan las normales a las caras, NENA!
	
	int dibujarWire;
	int dibujarPolys;
	int dibujarVert;
	int dibujarNorm;

	// Colores for the people
	float polyAlpha;
	Point polyColor;

public:
	// dibujar (y q tb sean virtuales - por si alguno no se dibuja solo poniendo glvertex)
	// el dibujar es el perFrame ;)
	// calcular (y q tb sean virtuales)
	virtual int update()=0;
	virtual void perFrame(float time);
	virtual void deInit(void);
	Shape();
	virtual ~Shape();
	void setWire(int _wire);
	void setPolys(int _polys);
	void setVert(int _vert);
	void setNorm(int _norm);

	int getNumVertex(void);
	Point getVertex(int numV);
	void setVertex(int numV, Point p);

	// colorines
	void setPolyAlpha(float _a);
	void setPolyColor(Point _p);
	void setPolyColorR(float _r);
	void setPolyColorG(float _g);
	void setPolyColorB(float _b);
};

#endif
