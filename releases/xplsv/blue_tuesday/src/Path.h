#ifndef __PATH__
#define __PATH__

#include "math3D.h"


class Path {
public:
	Path();
	int loadPath(const char *filename);
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
