#ifndef _CALGEBRA
#define _CALGEBRA

//Clases basicas de geometria y algebra

class Punto;
class Matriz;
class Transformacion;
class Matriz3d;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class Punto
//Actua indistintamente como punto o vector almacenado 4 coordenadas o componentes
{
public:
	float x,y,z,w;							//Coordenadas homogeneas

	Punto(float xx=0.0, float yy=0.0,		//Constructor
		  float zz=0.0, float ww=1.0); 
	Punto operator +(Punto p);				//Suma de puntos
	Punto operator -(Punto p);				//Resta de puntos
	Punto operator *(float k);				//Producto por un escalar
	float operator [](int i);				//Considerado como vector
	Punto operator *(Matriz m);				//Producto por una matriz
	Punto transformar(Transformacion &t);	//Transformacion de un punto
	Punto negado();							//Punto con el signo cambiado
	Punto normalizar();						//Normaliza el punto y se devuelve asi mismo
	Punto unitario();						//Vector unitario en esa direccion
	float modulo();							//Calcula el modulo del vector
	float longitud();						//Calcula la longitud esferica del vector
	float latitud();						//Calcula la latitud esferica del vector
	void escribir();						//Escribe el punto
	// MAS!
	float operator *(Punto p); // producto escalar
	Punto operator ^(Punto p); // PRoducto vectorial
	Punto homogeneo(); // da punto HOmogeneo


private:
	int esUnitario;							//esta normalizado
};
 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class Matriz
//Matriz de 4x4 coordenadas o Matriz vector de 4 puntos
{
public:
	float e[4][4];

	Matriz();							//Construye la identidad por defecto
	Matriz(Punto e1,Punto e2,			//Constructor por columnas
		   Punto e3,Punto e4=Punto());
	Punto fila(int i);					//Devuelve un punto con la fila i(0..3)
	Punto columna(int i);				//Devuelve un punto con la columna i(0..3)
	Matriz operator =(const Matriz &);	//Asignacion de matrices
	Matriz operator *(Matriz m);		//Producto de matrices
	Punto operator *(Punto p);			//Producto por un vector
	Matriz3d operator *(const Matriz3d &);//Producto por capas con una matriz 3d
	Matriz operator *(float k);			//Producto por un escalar
	Matriz operator !();				//Traspone filas y columnas
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class Transformacion: public Matriz
// Matriz de transformación derivada de matriz que acumula transformaciones 3D
{
public:

	//La acumulacion es LIFO sobre el punto pensando en coordenadas fijas
	//y se debe aplicar por la izquierda del punto en columna (idem GL)
	//Ej: P' = M1*M2*M3*P  (M3 fue la ultima en acumularse y la primera en aplicarse)

	void traslacion(Punto d);
	//Acumula la traslacion propuesta

	void escalado(float sx=1.0,float sy=1.0,float sz=1.0, Punto centro=Punto());
	//Acumula el escalado

	void giro(float ang, Punto vectorEje, Punto enRecta=Punto() );
	//Acumula el giro (ang en grados)

	void giroX(float ang);
	void giroY(float ang);
	void giroZ(float ang);
	//Acumulacion de giros específicos (ang en grados)


	void giro(Punto u,Punto v,Punto w);
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class Matriz3d: public Matriz
//Matriz cubica de 4x4x4 (filas X columnas X capas)
{
public:
	float e[4][4][4];

	Matriz3d();
	Matriz3d(Matriz , Matriz , Matriz , Matriz );
	//Constructor por columnas

	Punto fiCo(int i,int j);				//Devuelve el punto en fila i, columna j
	Matriz3d ponerEn(int i, int j, Punto p);//Mete el punto en la posicion i,j
	Matriz3d operator =(const Matriz3d &);  //Asignación de matrices 3d
	Matriz3d operator *(const Matriz &);	//Producto por capas con una matriz
};

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
											// MAS!
	float operator *(CPoint p); // producto escalar
	CPoint operator ^(CPoint p); // PRoducto vectorial
	CPoint homogeneus(); // da punto HOmogeneo
	
	
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
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class CTransformation: public CMatrix
// CMatrix de transformación derivada de matriz que acumula transformaciones 3D
{
public:
	
	//La acumulacion es LIFO sobre el punto pensando en coordenadas fijas
	//y se debe aplicar por la izquierda del punto en column (idem GL)
	//Ej: P' = M1*M2*M3*P  (M3 fue la ultima en acumularse y la primera en aplicarse)
	
	void traslate(CPoint d);
	//Acumula la traslate propuesta
	
	void scale(float sx=1.0,float sy=1.0,float sz=1.0, CPoint centro=CPoint());
	//Acumula el scale
	
	void rotate(float ang, CPoint vectorEje, CPoint enRecta=CPoint() );
	//Acumula el giro (ang en grados)
	
	void rotateX(float ang);
	void rotateY(float ang);
	void rotateZ(float ang);
	//Acumulacion de giros específicos (ang en grados)
	
	
	void rotate(CPoint u,CPoint v,CPoint w);
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
		CMatrix3d operator =(const CMatrix3d &);  //Asignación de matrices 3d
		CMatrix3d operator *(const CMatrix &);	//Producto por capas con una matriz
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif 
