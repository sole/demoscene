#ifndef __MATH3D__
	#define __MATH3D__


#include <stdlib.h>
#define INVRANDMAX 1/RAND_MAX

//#pragma once

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
// vector unitario
Point pointUnitary(Point a);
// vector normal a otros dos (regla de la mano derecha x)
Point normal2Vectors(Point a, Point b);

// Trigonometriasss
#define TRIGPREC 512

void prepareTables(void);
double getSinTable(int index);
double getCosTable(int index);

float getRand(void);

unsigned int clp2(unsigned int x);

// Adapted from http://www.bit-101.com/blog/?p=1242
float normalize(float value, float minimum, float maximum);
float interpolate(float normValue, float minimum, float maximum);
float map(float value, float in_min, float in_max, float out_min, float out_max);
#endif
