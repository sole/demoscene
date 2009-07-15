#include "Algebra.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
using namespace std;

#define PI 3.14159f

// Clase CPoint -------------------------------------------
//--------------------------------------------------------

CPoint::CPoint(float xx, float yy, float zz, float ww)
//Constructor por defecto
{
	x=xx; y=yy; z=zz; w=ww; isUnitary=0;
};

CPoint CPoint::operator +(CPoint p)
//Suma de dos vectores 
{
	CPoint suma;
	
	suma.x=x+p.x; suma.y=y+p.y; suma.z=z+p.z;
	return suma;
};

CPoint CPoint::operator -(CPoint p)
//Diferencia de dos vectores
{
	CPoint resta;
	
	resta.x=x-p.x;
	resta.y=y-p.y;
	resta.z=z-p.z;
	
	return resta;
	
};

CPoint CPoint::operator *(float k)
//Producto por un escalar POR LA DERECHA
{
	CPoint multiplicacion;
	
	multiplicacion.x=x*k;
	multiplicacion.y=y*k;
	multiplicacion.z=z*k;
	
	return multiplicacion;
};

float CPoint::operator [](int i)
//Tratamiento como vector por sobrecarga del operador []
{
	switch(i)
	{
		case 0:
			return(x);
			break;
		case 1:
			return(y);
			break;
		case 2:
			return(z);
			break;
		case 3:
			return(w);
			break;
		default:
			cerr << "GB:Indice de coordenada fuera de rango\n";
	};
	exit(1);
	return 0.0f;
};

CPoint CPoint::operator *(CMatrix m)
//Producto por una matriz POR LA DERECHA (P*M)
{
	CPoint mult,ptoAux;
	
	mult.x=x*m.e[0][0]+y*m.e[1][0]+z*m.e[2][0]+w*m.e[3][0];
	mult.y=x*m.e[0][1]+y*m.e[1][1]+z*m.e[2][1]+w*m.e[3][1];
	mult.z=x*m.e[0][2]+y*m.e[1][2]+z*m.e[2][2]+w*m.e[3][2];
	mult.w=x*m.e[0][3]+y*m.e[1][3]+z*m.e[2][3]+w*m.e[3][3];
	
	return mult;
};

CPoint CPoint::transform(CTransformation &t)
{
	return (t*(*this));
};

CPoint CPoint::negate()
{
	return CPoint(-x,-y,-z,w);
};

float CPoint::module()
{
	float modulin;
	
	modulin=sqrtf(x*x+y*y+z*z);
	return modulin;
};

CPoint CPoint::normalize()
{
	float md;
	
	if(!isUnitary) {
		md=this->module();
		md=1/md;
		x=x*md;
		y=y*md;
		z=z*md;
		this->isUnitary=1;
	}
	
	return (*this);
};

CPoint CPoint::unitary()
{	
	return ((*this).normalize());
};

float CPoint::longitude()
{
	float longi;
	longi= (float) acos(z/sqrt(x*x+z*z));		
	if(x<0) longi= 2*PI-longi;
	return longi*180/PI;
	
	
};

float CPoint::latitude()
{
	float lat;
	lat= (float)acos(sqrt(x*x-z*z)/module());		
	if(y<0) lat= -lat;
	return lat*180/PI;
};

CPoint CPoint::operator ^(CPoint p)
{
	return CPoint( y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x );
}
float CPoint::operator *(CPoint p)
{
	return (x*p.x+y*p.y+z*p.z);
}

CPoint CPoint::homogeneus()					
{
	if( w == 1.0 ) return *this;
	else return CPoint(x/w,y/w,z/w,1.0f);
}

void CPoint::randomize(CPoint p) {
	CPoint res;
	float invrandmax = 1.0/RAND_MAX;
	this->x = rand()*invrandmax-rand()*invrandmax;
	this->y = rand()*invrandmax-rand()*invrandmax;
	this->z = rand()*invrandmax-rand()*invrandmax;
	
	this->x = this->x*p.x;
	this->y = this->y*p.y;
	this->z = this->z*p.z;
}


void CPoint::write()
{
	printf("%6.2f %6.2f %6.2f %6.2f\n",x,y,z,w);
};


//Clase CMatrix -------------------------------------------
//--------------------------------------------------------


CMatrix::CMatrix()
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(j==i) e[i][j]=1.0f;
			else e[i][j]=0.0f;
		};
};

CMatrix::CMatrix(CPoint e1,CPoint e2,CPoint e3,CPoint e4)
{
	int i;
	for(i=0;i<4;i++){
		e[i][0]=e1[i];
		e[i][1]=e2[i];
		e[i][2]=e3[i];
		e[i][3]=e4[i];
	};
};

CPoint CMatrix::row(int i)
{
	if(i<4 && i>=0) return CPoint(e[i][0],e[i][1],e[i][2],e[i][3]);
	else {		
		cerr << "GB:Indice de row fuera de rango!\n";
		exit(1);
	};
	return CPoint();
};

CPoint CMatrix::column(int i)
{
	if(i<4 && i>=0) return CPoint(e[0][i],e[1][i],e[2][i],e[3][i]);
	else {		
		cerr << "GB:Indice de column fuera de rango\n";
		exit(1);
	};
	return CPoint();
};


CMatrix CMatrix::operator =(const CMatrix &m)
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++) e[i][j]=m.e[i][j];
	return *this;
};

CMatrix CMatrix::operator *(CMatrix m)
{
	int fil, col,itera;
	CMatrix result;
	
	result.e[0][0]=0.0f;
	result.e[1][1]=0.0f;
	result.e[2][2]=0.0f;
	result.e[3][3]=0.0f;
	
	for(fil=0;fil<=3;fil++) {
		for(col=0;col<=3;col++) {
			for(itera=0;itera<=3;itera++) {
				result.e[fil][col]=result.e[fil][col]+e[fil][itera]*m.e[itera][col];
			}
		}
		
	}
	
	return result;
};

CPoint CMatrix::operator *(CPoint p)
{
	int j;
	CPoint pr(0.0,0.0,0.0,0.0);
	
	for(j=0;j<4;j++){
		pr.x= pr.x+e[0][j]*p[j];
		pr.y= pr.y+e[1][j]*p[j];
		pr.z= pr.z+e[2][j]*p[j];
		pr.w= pr.w+e[3][j]*p[j];
	};
	return pr;
};

CMatrix3d CMatrix::operator *(const CMatrix3d &m3d)
{
	int i,j,k,n;
	CMatrix3d mr;
	
	for(k=0;k<4;k++)
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				for(n=0;n<4;n++)
					mr.e[i][j][k]= mr.e[i][j][k] + e[i][n]*m3d.e[n][j][k];
	return mr;
	
};


CMatrix CMatrix::operator *(float k)
{
	int i,j;
	CMatrix producto;
	
	for(i=0;i<=3;i++) {
		for(j=0;j<=3;j++) {
			producto.e[i][j]=e[i][j]*k;
		}
	}
	return producto;
};

CMatrix CMatrix::operator !()
{
	CMatrix mt;
	int i,j;
	
	for(i=0;i<=3;i++) {
		for(j=0;j<=3;j++) {
			mt.e[i][j]=e[j][i];
		}
	}
	
	return mt;
};

void CMatrix::escribir()
{
	int i,j;
	
	for(i=0;i<4;i++){
		printf("\n");
		for(j=0;j<4;j++)
			printf("%6.2f ",e[i][j]);
	};
	printf("\n");
};

void CMatrix::identity()
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(j==i) e[i][j]=1.0f;
			else e[i][j]=0.0f;
		};
};

//Clase CTransformation (subclase de CMatrix) -------------------------
//-------------------------------------------------------------------

void CTransformation::translate(CPoint d)
{
	CMatrix t;
	int i;
	
	for (i=0;i<3;i++) t.e[i][3]=d[i];
	CMatrix::operator=((*this)*t);
	
};

void CTransformation::translate(float x, float y, float z, float w) {
	CPoint p(x,y,z,w);
	translate(p);
}

void CTransformation::scale(float sx,float sy,float sz, CPoint centro)
{  
	CMatrix ms;
	// Antes de escalar, hay que trasladar!
	translate(centro);
	
	ms.e[0][0]=sx;
	ms.e[1][1]=sy;
	ms.e[2][2]=sz;
	
	// Ahora acumulo la transformacion
	CMatrix::operator =((*this)*ms);
	
	// Se deshace la translate!
	translate(centro.negate());
	
};


void CTransformation::rotate(float ang, CPoint vectorEje, CPoint enRecta )
//Acumula el giro alrededor de un eje generico
{
	// enRecta es un punto que esta en el eje de rotacion
	float lat= vectorEje.latitude();		//latitude
	float lon= vectorEje.longitude();		//longitude
	
	// Me llevo el sistema de coordenadas al punto que quiero girar
	translate(enRecta);
	// Lo giro para que este como el eje vectorEje
	rotateY(lon);
	rotateX(-lat);
	rotateZ(ang);
	// ahora a volver al sitio original
	rotateX(lat);
	rotateY(-lon);
	translate(enRecta.negate());
};

void CTransformation::rotate(CPoint u,CPoint v,CPoint w)
{
	CMatrix t = !CMatrix(u,v,w);
	t.e[0][3]=t.e[1][3]=t.e[2][3]=0.0f;
	CMatrix::operator=((*this)*(t));
}

// giros especificos
void CTransformation::rotateX(float ang)
{
	CMatrix g;
	g.e[1][1]=(float)cos((double)ang/180*PI);
    g.e[1][2]=(float)sin((double)(-ang/180*PI));
	g.e[2][1]= -g.e[1][2];        
	g.e[2][2]=g.e[1][1];
	
	CMatrix::operator=((*this)*g);
}

void CTransformation::rotateY(float ang)
{
	CMatrix g;
	g.e[0][0]=(float)cos((double)ang/180*PI);
    g.e[0][2]=(float)-sin((double)(-ang/180*PI));
	g.e[2][0]= -g.e[0][2];        
	g.e[2][2]= g.e[0][0];
	
	CMatrix::operator=((*this)*g);
}

void CTransformation::rotateZ(float ang)
{
	CMatrix g;
	g.e[0][0]=(float)cos((double)ang/180*PI);
    g.e[0][1]=(float)sin((double)(-ang/180*PI));
	g.e[1][0]= -g.e[0][1];        g.e[1][1]=g.e[0][0];
	
	CMatrix::operator=((*this)*g);
};

// Creates a rotation matrix based on the quaternion value :-U
// Obviously this destroy previous matrix values
void CTransformation::rotateQuaternion(float x, float y, float z, float w) {
	/*
	 w2 + x2 - y2 - z2       2xy - 2wz           2xz + 2wy
	 2xy + 2wz       w2 - x2 + y2 - z2       2yz - 2wx
	 2xz - 2wy           2yz + 2wx       w2 - x2 - y2 + z2 
	 
	 something neater: (TODO)
	 
	 1 - 2y2 - 2z2    2xy - 2wz      2xz + 2wy
	 2xy + 2wz    1 - 2x2 - 2z2    2yz - 2wx
	 2xz - 2wy      2yz + 2wx    1 - 2x2 - 2y2
	 
	 
	*/
	float x2 = x*x;
	float y2 = y*y;
	float z2 = z*z;
	float w2 = w*w;
	
	e[0][0] = w2 + x2 - y2 - z2;
	e[0][1] = 2*(x*y - w*z); //2*x*y - 2*w*z;
	e[0][2] = 2*(x*z + w*y);
	
	e[1][0] = 2*(x*y + w*z);
	e[1][1] = w2 - x2 + y2 - z2;
	e[1][2] = 2*(y*z - w*x);
	
	e[2][0] = 2*(x*z - w*y);
	e[2][1] = 2*(y*z + w*x);
	e[2][2] = w2 - x2 - y2 + z2;
}

void CTransformation::rotateQuaternion(CPoint p) {
	rotateQuaternion(p.x, p.y, p.z, p.w);
};

// Clase CMatrix3d -------------------------------------------
//-----------------------------------------------------------

CMatrix3d::CMatrix3d()
{
	int i,j,k;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			for(k=0;k<4;k++) e[i][j][k]=0.0f;
};

CMatrix3d::CMatrix3d(CMatrix c1, CMatrix c2, CMatrix c3, CMatrix c4)
{
	int i,k;
	
	for(i=0;i<4;i++)
		for(k=0;k<4;k++){
			e[i][0][k]=c1.e[k][i];
			e[i][1][k]=c2.e[k][i];
			e[i][2][k]=c3.e[k][i];
			e[i][3][k]=c4.e[k][i];
		};
};

CMatrix3d CMatrix3d::operator =(const CMatrix3d &m)
{
	int fil,col,iter;
	
	for(fil=0;fil<=3;fil++)
		for(col=0;col<=3;col++)
			for(iter=0;iter<=3;iter++)
				e[fil][col][iter]=m.e[fil][col][iter];
	
	return (*this);
};

CMatrix3d CMatrix3d::operator *(const CMatrix &m)
{
	int i,j,k,n;
	CMatrix3d mr;
	
	for(k=0;k<4;k++)
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				for(n=0;n<4;n++)
					mr.e[i][j][k]= mr.e[i][j][k] + e[i][n][k]*m.e[n][j];
	return mr;
	
};

CPoint CMatrix3d::rowCol(int i, int j)
{
	CPoint ptoFilaColumna;
	
	ptoFilaColumna.x=e[i][j][0];
	ptoFilaColumna.y=e[i][j][1];
	ptoFilaColumna.z=e[i][j][2];
	ptoFilaColumna.w=1;
	
	return ptoFilaColumna;
};

void CMatrix3d::escribir()
{
	int i,j,k;
	
	for(j=0;j<4;j++){
		printf("\n");
		for(i=0;i<4;i++){
			printf("\n");
			for(k=0;k<4;k++) 
				printf("%6.2f ",e[i][j][k]);
		};
	};
};

CMatrix3d CMatrix3d::putIn(int i, int j, CPoint p)
{
	int k;
	for(k=0;k<4;k++)
		e[i][j][k]=p[k];
	return *this;
};

