//: src:Algebra.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 31 july 2005  
// Declaration of CPoint, CMatrix, CTransformation, CMatrix3d classes

#ifndef ALGEBRA_H
#define ALGEBRA_H

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Clases basicas de geometria y algebra

class CPoint;
class CMatrix;
class CTransformation;
class CMatrix3d;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class CPoint
//Actua indistintamente como punto o vector almacenado 4 coordenadas o componentes
{
public:
	float x,y,z,w;							//Coordenadas homogeneas
	
	CPoint(float xx=0.0, float yy=0.0,		//Constructor
		   float zz=0.0, float ww=1.0); 
	CPoint operator +(CPoint p);				//Suma de puntos
	CPoint operator -(CPoint p);				//Resta de puntos
	CPoint operator *(float k);				//Producto por un escalar
	float operator [](int i);				//Considerado como vector
	CPoint operator *(CMatrix m);				//Producto por una matriz
	CPoint transform(CTransformation &t);	//CTransformation de un punto
	CPoint negate();							//CPoint con el signo cambiado
	CPoint normalize();						//Normaliza el punto y se devuelve asi mismo
	CPoint unitary();						//Vector unitary en esa direccion
	float module();							//Calcula el module del vector
	float longitude();						//Calcula la longitude esferica del vector
	float latitude();						//Calcula la latitude esferica del vector
	void write();						//Escribe el punto
											// MAS!
	float operator *(CPoint p); // producto escalar
	CPoint operator ^(CPoint p); // PRoducto vectorial
	CPoint homogeneus(); // da punto HOmogeneo
	void randomize(CPoint p); // randomiza los valores en base a ese maximo p
	
private:
		int isUnitary;							//esta normalizado
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class CMatrix
//CMatrix de 4x4 coordenadas o CMatrix vector de 4 puntos
{
public:
	float e[4][4];
	
	CMatrix();							//Construye la identidad por defecto
	CMatrix(CPoint e1,CPoint e2,			//Constructor por columns
			CPoint e3,CPoint e4=CPoint());
	CPoint row(int i);					//Devuelve un punto con la row i(0..3)
	CPoint column(int i);				//Devuelve un punto con la column i(0..3)
	CMatrix operator =(const CMatrix &);	//Asignacion de matrices
	CMatrix operator *(CMatrix m);		//Producto de matrices
	CPoint operator *(CPoint p);			//Producto por un vector
	CMatrix3d operator *(const CMatrix3d &);//Producto por capas con una matriz 3d
	CMatrix operator *(float k);			//Producto por un escalar
	CMatrix operator !();				//Traspone rows y columns
	void escribir();					//Escribe la matriz
	void identity(); // Resetea a "identidad"
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class CTransformation: public CMatrix
// CMatrix de transformaciÛn derivada de matriz que acumula transformaciones 3D
{
public:
	
	//La acumulacion es LIFO sobre el punto pensando en coordenadas fijas
	//y se debe aplicar por la izquierda del punto en column (idem GL)
	//Ej: P' = M1*M2*M3*P  (M3 fue la ultima en acumularse y la primera en aplicarse)
	
	//Acumula la translate propuesta
	void translate(CPoint d);
	void translate(float x, float y, float z, float w);
	
	
	void scale(float sx=1.0,float sy=1.0,float sz=1.0, CPoint centro=CPoint());
	//Acumula el scale
	
	void rotate(float ang, CPoint vectorEje, CPoint enRecta=CPoint() );
	//Acumula el giro (ang en grados)
	
	void rotateX(float ang);
	void rotateY(float ang);
	void rotateZ(float ang);
	//Acumulacion de giros especÌficos (ang en grados)
	
	
	void rotate(CPoint u,CPoint v,CPoint w);
	
	// Creates a rotation matrix based on the quaternion value :-U
	void rotateQuaternion(float x, float y, float z, float w);
	void rotateQuaternion(CPoint p);
	
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class CMatrix3d: public CMatrix
//CMatrix cubica de 4x4x4 (rows X columns X capas)
{
public:
	float e[4][4][4];
	
	CMatrix3d();
	CMatrix3d(CMatrix , CMatrix , CMatrix , CMatrix );
	//Constructor por columns
	
	CPoint rowCol(int i,int j);				//Devuelve el punto en row i, column j
	CMatrix3d putIn(int i, int j, CPoint p);//Mete el punto en la posicion i,j
		CMatrix3d operator =(const CMatrix3d &);  //AsignaciÛn de matrices 3d
		CMatrix3d operator *(const CMatrix &);	//Producto por capas con una matriz
		void escribir();
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif