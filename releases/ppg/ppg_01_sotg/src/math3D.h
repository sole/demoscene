#ifndef __MATH3D__
	#define __MATH3D__


#include <stdlib.h>

struct Point {
	float x;
	float y;
	float z;
	float w;
};
// Suma de puntos
Point pointAdd(Point a,Point b); 
// Producto vectorial
Point pointCrossProduct(Point a,Point b);

// Trigonometriasss
#define TRIGPREC 512

void prepareTables(void);
double getSinTable(int index);
double getCosTable(int index);

float getRand(void);

// Adapted from http://www.bit-101.com/blog/?p=1242
float normalize(float value, float minimum, float maximum);
float interpolate(float normValue, float minimum, float maximum);
float map(float value, float in_min, float in_max, float out_min, float out_max);


#endif
