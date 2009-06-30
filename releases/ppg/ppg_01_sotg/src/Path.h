#ifndef __PATH__
	#define __PATH__

#include "math3D.h"


class Path {
public:
	Path();
//	~Path();
	int loadPath(char *filename);
	//void interpolatePoints(void); // No lo usar�... por ahora pq max lo interpola :-?? tal vez luego haga falta si va demasiado a golpes :S
	void getPointAt(int pointNum, Point *p);
	int getNumICP(void); // devuelve el numero de ptos de control interpolados q tiene
	void scale(float sx, float sy, float sz);
private:
	int numControlPoints;
	int numInterpolatedPoints;
	Point *controlPointsList;
	Point *interCPList;
};

#endif