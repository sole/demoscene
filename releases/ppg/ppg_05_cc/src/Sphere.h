#ifndef SPHERE_H
#define SPHERE_H


#include "Shape.h"

class Sphere: public Shape {
private:
	// los parámetros de esta shape son sencillos!
	float length;
	int iterations;

public:
	Sphere();
	~Sphere();

	int update();

	int setLength(float _length);
	int setIterations(int _iterations);
	void perFrame(float time);
};

#endif