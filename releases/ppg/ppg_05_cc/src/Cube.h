#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube: public Shape {
private:
	// los parámetros de esta shape son sencillos!
	float length;

public:
	Cube();
	~Cube();

	int update();

	int setLength(float _length);
};

#endif