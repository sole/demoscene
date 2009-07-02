#include "math3D.h"
#include <math.h>

double sinTable[TRIGPREC];
double cosTable[TRIGPREC];

Point pointAdd(Point a,Point b) {
	Point result;
	result.x=a.x + b.x;
	result.y=a.y + b.y;
	result.z=a.z + b.z;

	return result;
}

Point pointCrossProduct(Point a, Point b) {
	Point *result=new Point();
	// | i  j  k  | 
	// | xa ya za | = i*ya*zb + j*za*xb + yb*xa*k - k*ya*xb - za*yb*i - xa*j*zb
    // | xb yb zb |

	// por componentes: 
	// i*ya*zb - i*za*yb
	// j*za*xb - j*xa*zb
	// k*yb*xa - k*ya*xb
	
	result->x=a.y*b.z - a.z*b.y;
	result->y=a.z*b.x - a.x*b.z;
	result->z=b.y*a.x - a.y*b.x;

	return *result;
}

Point pointUnitary(Point a) {
	float length,ilength;
	Point *result=new Point();

	length=(float)(sqrt(a.x*a.x + a.y*a.y + a.z*a.z));
	if(length==0) {
		ilength=1;
	}
	result->x=a.x*ilength;
	result->y=a.y*ilength;
	result->z=a.z*ilength;
	//result->w=a->w;
	
	return *result;
}

Point normal2Vectors(Point a, Point b) {
	// encuentra el vector normal y unitario a otros dos vectores
	Point *result=new Point();
	*result=pointCrossProduct(a,b);
	*result=pointUnitary(*result);
	return *result;
}

void prepareTables(void) {
	/* LA ciudad está desierta ...
	ya sólo me quedo a mí misma ... 
	Y los pañuelos!
	¡Es nefasta, esta frase!
	*/
	int i;
	double pi = 3.1415926535;
	double pi2=2*pi;

	for(i=0;i<=TRIGPREC;i++) {
		sinTable[i]=sin((pi2/TRIGPREC)*i);
		cosTable[i]=cos((pi2/TRIGPREC)*i);
	}
}
// No se si creerme que funcionará pero bueno la esperanza nunca se pierde
#pragma auto_inline (on)

double getSinTable(int index) {
	return sinTable[index];
}

double getCosTable(int index) {
	return cosTable[index];
}

float getRand(void) {
	return float(rand())/RAND_MAX;
}

// From Hacker's delight, p.48
unsigned int clp2(unsigned int x)
{
	x = x - 1;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	return x + 1;
}
