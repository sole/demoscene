#ifndef __LIGHT__
	#include "Light.h"
#endif

#ifndef __MESH__
	#define __MESH__
#endif

class Mesh {
public:
	// constructor
	Mesh(void);
	// destructor
	~Mesh();
	// dibuja los poligonos (triangulos) en pantalla
	void draw(void);
	// carga una malla
	int loadMesh(char *filename);
	// dibuja las aristas en pantalla
	void drawWire(float linewidth,int numcar);
	// dibuja los poligonos -triangulos- pero con las luces q le hayamos aplicado, si no hay luces no se vera nada
	//void drawLit(void);

	// Sobre las luces que le aplico
	//int addLight(Light *l);
	//int removeLight(int num); // jis jis jis por ahora nooorll!!

private:
	int numVertex; // número de vértices de la malla
	int numFaces; // número de caras
	float *x,*y,*z; // puntero a vector de vértices
	int *faceList[3]; // puntero a vector de caras (o sea una lista de caras)
	float *normalList[3]; // puntero a vector de normales
	//Light *lightList;
	void normalize(void);

};