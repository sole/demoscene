#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "Algebra.h"

class CBezierCurve
{
	
private:
	
	static CMatrix MBezier;	//Matriz caracteristica de Bezier
	CPoint pControl[4];		//Puntos de control
	CMatrix c;				//Matriz de Coeficientes
	
	void calculateC();		//Calcula la matriz de coeficientes
	
public:
		
	CBezierCurve();		
	CBezierCurve(CPoint p[4]);	
	CBezierCurve(CPoint p0, CPoint p1, CPoint p2, CPoint p3);
	//Constructores
	
	void curveSteps(int number, CPoint *points);
	//return number+1 steps in the curve in points[number+1]
	
	// update point which [0..3] with newPoint
	void setPoint(int which, CPoint newPoint);
		
	CPoint control(int i);
	//Devuelve el punto de control [0..3]
	
	
};


#endif
