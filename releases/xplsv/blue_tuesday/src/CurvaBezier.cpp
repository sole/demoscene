//Implementación de la clase Curva de Bezier

#include "CurvaBezier.h"


//Matriz CurvaBezier::MBezier;
Matriz CurvaBezier::MBezier=Matriz(Punto(-1.0f , 3.0f , -3.0f , 1.0f),
 								   Punto(3.0f , -6.0f , 3.0f , 0.0f),
 								   Punto(-3.0f , 3.0f , 0.0f , 0.0f),
 								   Punto(1.0f , 0.0f , 0.0f , 0.0f));



CurvaBezier::CurvaBezier()
//Constructor por defecto
{
	pControl[0]= Punto();
	pControl[1]= Punto();
	pControl[2]= Punto();
	pControl[3]= Punto();
}
	
CurvaBezier::CurvaBezier(Punto p[4])
//Constructor
{
	int i;
	for(i=0;i<4;i++) pControl[i]=p[i];
	calculaC();
}

CurvaBezier::CurvaBezier(Punto p0, Punto p1, Punto p2, Punto p3)
//Constructor
{
	pControl[0]= p0;
	pControl[1]= p1;
	pControl[2]= p2;
	pControl[3]= p3;
	calculaC();

}

void CurvaBezier::calculaC()
//Calculo de coeficientes 
{
	Matriz P(pControl[0],pControl[1],pControl[2],pControl[3]);
	P=!P;
	c = MBezier * P;
}


void CurvaBezier::modificaPunto(int cual, Punto nuevo)
//Cambia el punto cual [0..3] por el nuevo
{
	pControl[cual]= nuevo;
	calculaC();
}

Punto CurvaBezier::control(int i)
//Devuelve el punto de control
{
	return pControl[i];
}


void CurvaBezier::tramosCurva(int cuantos, Punto *puntos)
//Devuelve cuantos+1 puntos sobre la curva en puntos[]
//mediante el método de las diferencias avanzadas
{
		float delta = (1.0f/(float)cuantos);
	float delta2 = delta*delta;
	float delta3 = delta*delta*delta;
	
	Matriz E =	Matriz(	Punto(0.0f , delta3 , 6.0f*delta3, 6.0f*delta3),
								Punto(0.0f , delta2 , 2.0f*delta2, 0.0f),
								Punto(0.0f , delta  , 0.0f     , 0.0f),
								Punto(1.0f , 0.0f , 0.0f     , 0.0f));
	
	Matriz incD = E*c;

	Punto P = incD.fila(0);
	Punto incP = incD.fila(1);
	Punto inc2P = incD.fila(2);
	Punto inc3P = incD.fila(3);

	puntos[0] = pControl[0];
	for(int i=1; i<cuantos; i++) {
		P=P+incP;
		incP=incP+inc2P;
		inc2P=inc2P+inc3P;
		puntos[i]=P;
	}
	puntos[cuantos]=pControl[3];
};


