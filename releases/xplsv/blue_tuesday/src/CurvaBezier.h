#ifndef __CURVABEZIER
#define __CURVABEZIER

#include "Algebra.h"

class CurvaBezier
{

private:

	static Matriz MBezier;	//Matriz caracteristica de Bezier
	Punto pControl[4];		//Puntos de control
	Matriz c;				//Matriz de Coeficientes

	void calculaC();		//Calcula la matriz de coeficientes

public:

	CurvaBezier();		
	CurvaBezier(Punto p[4]);	
	CurvaBezier(Punto p0, Punto p1, Punto p2, Punto p3);
	//Constructores

	void tramosCurva(int cuantos, Punto *puntos);
	//Devuelve cuantos tramos sobre la curva en puntos[cuantos+1]

	void modificaPunto(int cual, Punto nuevo);
	//Cambia el punto cual [0..3] por el nuevo

	Punto control(int i);
	//Devuelve el punto de control [0..3]


};


#endif
