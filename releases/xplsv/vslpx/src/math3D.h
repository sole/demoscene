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
#endif