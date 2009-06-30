#ifndef __MESH__
#define __MESH__

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

private:
	int numVertex; // número de vértices de la malla
	int numFaces; // número de caras
	float *x,*y,*z; // puntero a vector de vértices
	int *faceList[3]; // puntero a vector de caras (o sea una lista de caras)
	float *normalList[3]; // puntero a vector de normales
	//Light *lightList;
	void normalize(void);

};

#endif

