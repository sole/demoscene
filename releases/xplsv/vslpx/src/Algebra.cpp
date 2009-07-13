//Clases basicas de geometria y algebra

#include <stdlib.h>
#include <math.h>
#include "Algebra.h"

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
	};
	exit(1);
	return 0.0f;
};

CPoint CPoint::operator *(CMatrix m)
//Producto por una matriz POR LA DERECHA (P*M)
{
	CPoint mult,ptoAux;
//	int fil,col;
//	float acum;

	/* Recordatorio de la multiplicacion vector*matriz
	   -----------------------------------------------

	   Se multiplica el vector por cada column de la matriz:

	
					| a b c d |
		(x y z w)   | e f g h |
				    | i j k l |
					| m n o p |

	   resulta ser:

		(x*a + y*e + z*i + w*m , x*b + y*f + z*j + w*n , ....)
	*/
	
	/*for(col=0;col<=3;col++) {
		acum=0;
		for(fil=0;fil<=3;fil++) {
			acum+=(this[fil]*m.e[col][fil]);
		}
		mult[col]=acum;
	}
    */

	mult.x=x*m.e[0][0]+y*m.e[1][0]+z*m.e[2][0]+w*m.e[3][0];
	mult.y=x*m.e[0][1]+y*m.e[1][1]+z*m.e[2][1]+w*m.e[3][1];
	mult.z=x*m.e[0][2]+y*m.e[1][2]+z*m.e[2][2]+w*m.e[3][2];
	mult.w=x*m.e[0][3]+y*m.e[1][3]+z*m.e[2][3]+w*m.e[3][3];

	return mult;
};

CPoint CPoint::transform(CTransformation &t)
//Transforma considerando el punto como vector column
//es decir, aplica la transformacion por la izquierda
{
	return (t*(*this));
};

CPoint CPoint::negate()
//Devuelve un nuevo vector con el signo cambiado
{
	return CPoint(-x,-y,-z,w);
};

float CPoint::module()
//Devuelve el module del vector
{
	float modulin;

	modulin=sqrtf(x*x+y*y+z*z);
	return modulin;
};

CPoint CPoint::normalize()
//Normaliza el vector receptor y se devuelve a si mismo
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
//Devuelve el vector unitary en esa direccion
{
	/*
	/// esto no hay que hacerlo, que ocupa mucha memoria!!!
	CPoint vUnitario;

	vUnitario=*this;

	return vUnitario.normalize();*/

	return ((*this).normalize());
};

float CPoint::longitude()
{//Calcula la longitude (0..360º) esferica del vector en grados
	/* distancia en grados al eje Z ,desde el eje X, y en el sentido antihorario */
	float longi;
	longi= (float) acos(z/sqrt(x*x+z*z));		
	if(x<0) longi= 2*PI-longi;
	return longi*180/PI;

	
};

float CPoint::latitude()
//Calcula la latitude (-90º..90º) esférica del vector en grados
{
	float lat;
	lat= (float)acos(sqrt(x*x-z*z)/module());		
	if(y<0) lat= -lat;
	return lat*180/PI;
};

/*nuevas operaciones para la practica2*/
CPoint CPoint::operator ^(CPoint p)
{
	// Producto vectorial.
	return CPoint( y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x );
}
float CPoint::operator *(CPoint p)
{
	// Producto escalar.
	return (x*p.x+y*p.y+z*p.z);
}

CPoint CPoint::homogeneus()					
{
	//divide el punto por w y lo devuelve
	if( w == 1.0 ) return *this;
	else return CPoint(x/w,y/w,z/w,1.0f);
}




//Clase CMatrix -------------------------------------------
//--------------------------------------------------------


CMatrix::CMatrix()
//Construye la identidad por defecto
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(j==i) e[i][j]=1.0f;
			else e[i][j]=0.0f;
		};
};

CMatrix::CMatrix(CPoint e1,CPoint e2,CPoint e3,CPoint e4)
//Construye la matriz por columns
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
//Devuelve un punto formado por la row i (0..3)
{
	if(i<4 && i>=0) return CPoint(e[i][0],e[i][1],e[i][2],e[i][3]);
	else {		
		exit(1);
	};
	return CPoint();
};

CPoint CMatrix::column(int i)
//Devuelve un punto con la column i (0..3)
{
	if(i<4 && i>=0) return CPoint(e[0][i],e[1][i],e[2][i],e[3][i]);
	else {		
		exit(1);
	};
	return CPoint();
};


CMatrix CMatrix::operator =(const CMatrix &m)
//Asignacion de matrices
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++) e[i][j]=m.e[i][j];
	return *this;
};

CMatrix CMatrix::operator *(CMatrix m)
//Producto de matrices. Devuelve una nueva matriz
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
//Producto por un vector POR LA DERECHA (M*P)
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
//Multiplica por capas (k cte.) y devuelve una matriz3d
{
	int i,j,k,n;
	CMatrix3d mr;	//Por defecto toda a ceros

	for(k=0;k<4;k++) //fija la capa
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				for(n=0;n<4;n++)
					mr.e[i][j][k]= mr.e[i][j][k] + e[i][n]*m3d.e[n][j][k];
	return mr;

};


CMatrix CMatrix::operator *(float k)
//Producto por un escalar (M*k). Devuelve una nueva matriz
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
//Devuelve la traspuesta en una nueva matriz. 
//Usar parentesis para asegurar precedencia (!M)
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


//Clase CTransformation (subclase de CMatrix) -------------------------
//-------------------------------------------------------------------

void CTransformation::traslate(CPoint d)
//Acumula la traslate propuesta
{
	CMatrix t;
	int i;

	for (i=0;i<3;i++) t.e[i][3]=d[i];
	CMatrix::operator=((*this)*t); // uso el operador = de la clase papi

};

void CTransformation::scale(float sx,float sy,float sz, CPoint centro)
//Acumula el scale sobre un punto generico
{  
	CMatrix ms;
	// Antes de escalar, hay que trasladar!
	traslate(centro);

	ms.e[0][0]=sx;
	ms.e[1][1]=sy;
	ms.e[2][2]=sz;

	// Ahora acumulo la transformacion
	CMatrix::operator =((*this)*ms); //un poco marciano no???

	// Se deshace la traslate!
	traslate(centro.negate());

};


void CTransformation::rotate(float ang, CPoint vectorEje, CPoint enRecta )
//Acumula el giro alrededor de un eje generico
{
	// enRecta es un punto que está en el eje de rotacion
	float lat= vectorEje.latitude();		//latitude
	float lon= vectorEje.longitude();		//longitude

	// Me llevo el sistema de coordenadas al punto que quiero girar
	traslate(enRecta);
	// Lo giro para que esté como el eje vectorEje
	rotateY(lon);
	rotateX(-lat);
	rotateZ(ang);
	// ahora a volver al sitio original
	rotateX(lat);
	rotateY(-lon);
	traslate(enRecta.negate());
};

void CTransformation::rotate(CPoint u,CPoint v,CPoint w)
//Cambio de base
{
	CMatrix t = !CMatrix(u,v,w);
	t.e[0][3]=t.e[1][3]=t.e[2][3]=0.0f;
	CMatrix::operator=((*this)*(t));
}

//Acumulacion de giros específicos
void CTransformation::rotateX(float ang)
//en X
{
	CMatrix g;
	g.e[1][1]=(float)cos((double)ang/180*PI);
    g.e[1][2]=(float)sin((double)(-ang/180*PI));
	g.e[2][1]= -g.e[1][2];        
	g.e[2][2]=g.e[1][1];

	CMatrix::operator=((*this)*g);
};
void CTransformation::rotateY(float ang)
//en Y
{
	CMatrix g;
	g.e[0][0]=(float)cos((double)ang/180*PI);
    g.e[0][2]=(float)-sin((double)(-ang/180*PI));
	g.e[2][0]= -g.e[0][2];        
	g.e[2][2]= g.e[0][0];

	CMatrix::operator=((*this)*g);
};
void CTransformation::rotateZ(float ang)
//en Z
{
	CMatrix g;
	g.e[0][0]=(float)cos((double)ang/180*PI);
    g.e[0][1]=(float)sin((double)(-ang/180*PI));
	g.e[1][0]= -g.e[0][1];        g.e[1][1]=g.e[0][0];

	CMatrix::operator=((*this)*g);
};

// Clase CMatrix3d -------------------------------------------
//-----------------------------------------------------------

CMatrix3d::CMatrix3d()
//Constructor por defecto. CMatrix toda a 0.0
{
	int i,j,k;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		for(k=0;k<4;k++) e[i][j][k]=0.0f;
};

CMatrix3d::CMatrix3d(CMatrix c1, CMatrix c2, CMatrix c3, CMatrix c4)
//Contruye la matriz3d con las matrices como columns
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
//Asignacion de matrices 3d
{
	int fil,col,iter;

	for(fil=0;fil<=3;fil++)
		for(col=0;col<=3;col++)
			for(iter=0;iter<=3;iter++)
				e[fil][col][iter]=m.e[fil][col][iter];

	return (*this);
};

CMatrix3d CMatrix3d::operator *(const CMatrix &m)
//Multiplica por capas y devuelve la nueva matriz 3d
{
	int i,j,k,n;
	CMatrix3d mr;	//Por defecto toda a ceros

	for(k=0;k<4;k++) //fija la capa
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				for(n=0;n<4;n++)
					mr.e[i][j][k]= mr.e[i][j][k] + e[i][n][k]*m.e[n][j];
	return mr;

};

CPoint CMatrix3d::rowCol(int i, int j)
//Devuelve el punto para esa row,column 
{
	CPoint ptoFilaColumna;

	ptoFilaColumna.x=e[i][j][0];
	ptoFilaColumna.y=e[i][j][1];
	ptoFilaColumna.z=e[i][j][2];
	ptoFilaColumna.w=1;

	return ptoFilaColumna;
};


CMatrix3d CMatrix3d::putIn(int i, int j, CPoint p)
//Mete un punto en la posicion i,j
{
	int k;
	for(k=0;k<4;k++)
		e[i][j][k]=p[k];
	return *this;
};

