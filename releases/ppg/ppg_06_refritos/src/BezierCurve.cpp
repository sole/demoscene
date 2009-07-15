//ImplementaciÛn de la clase Curva de Bezier

#include "BezierCurve.h"
#include<new>

//Matrix BezierCurve::MBezier;
CMatrix CBezierCurve::MBezier=CMatrix(CPoint(-1.0f , 3.0f , -3.0f , 1.0f),
 								   CPoint(3.0f , -6.0f , 3.0f , 0.0f),
 								   CPoint(-3.0f , 3.0f , 0.0f , 0.0f),
 								   CPoint(1.0f , 0.0f , 0.0f , 0.0f));



CBezierCurve::CBezierCurve()
//Constructor por defecto
{
	pControl[0]= CPoint();
	pControl[1]= CPoint();
	pControl[2]= CPoint();
	pControl[3]= CPoint();
};

CBezierCurve::CBezierCurve(CPoint p[4])
//Constructor
{
	int i;
	for(i=0;i<4;i++) pControl[i]=p[i];
	calculateC();
};

CBezierCurve::CBezierCurve(CPoint p0, CPoint p1, CPoint p2, CPoint p3)
//Constructor
{
	pControl[0]= p0;
	pControl[1]= p1;
	pControl[2]= p2;
	pControl[3]= p3;
	calculateC();
	
};

void CBezierCurve::calculateC()
//Calculo de coeficientes 
{
	CMatrix P(pControl[0],pControl[1],pControl[2],pControl[3]);
	P=!P;
	c = MBezier * P;
	
};


void CBezierCurve::setPoint(int which, CPoint newPoint)
//Cambia el punto cual [0..3] por el nuevo
{
	pControl[which]= newPoint;
	calculateC();
};

CPoint CBezierCurve::control(int i)
//Devuelve el punto de control
{
	if(i>=0 && i<=3)
	return pControl[i];
	else return CPoint();
};


void CBezierCurve::curveSteps(int number, CPoint *points)
//Devuelve cuantos+1 puntos sobre la curva en puntos[]
//mediante el mÈtodo de las diferencias avanzadas
{
	float delta = (1.0f/(float)number);
	float delta2 = delta*delta;
	float delta3 = delta*delta*delta;
	
	CMatrix E =	CMatrix(	CPoint(0.0f , delta3 , 6.0f*delta3, 6.0f*delta3),
						CPoint(0.0f , delta2 , 2.0f*delta2, 0.0f),
						CPoint(0.0f , delta  , 0.0f     , 0.0f),
						CPoint(1.0f , 0.0f , 0.0f     , 0.0f));
	//E = !E;
	
	CMatrix incD = E*c;
	
	CPoint P = incD.row(0);
	CPoint incP = incD.row(1);
	CPoint inc2P = incD.row(2);
	CPoint inc3P = incD.row(3);
	
	points[0] = pControl[0];
	for(int i=1; i<number; i++) {
		P=P+incP;
		incP=incP+inc2P;
		inc2P=inc2P+inc3P;
		points[i]=P;
	}
	points[number]=pControl[3];
};


