#include "Cube.h"

Cube::Cube() {
	// crear los vertices
	this->vertexList=new(Point[8]);
	// y asignar el numvertex
	this->numVertex=8;

	// Y las caras tb molan mucho
	int c=12;
	this->numFaces=c;
	this->faceList1=new(int[c]);
	this->faceList2=new(int[c]);
	this->faceList3=new(int[c]);


	// La longitud inicial de cada cara será 1.0f, pq lo digo yo
	this->length=1.0f;
	// completar la info de cada vertice (¿llamar a update?)
	this->update();
}

Cube::~Cube() {
}

int Cube::update() {

	float semilength=this->length*0.5f;

	// [re]generar los vértices
	vertexList[0].x=-semilength;
	vertexList[0].y=-semilength;
	vertexList[0].z=semilength;

	vertexList[1].x=semilength;
	vertexList[1].y=-semilength;
	vertexList[1].z=semilength;

	vertexList[2].x=semilength;
	vertexList[2].y=-semilength;
	vertexList[2].z=-semilength;

	vertexList[3].x=-semilength;
	vertexList[3].y=-semilength;
	vertexList[3].z=-semilength;

	// si quisiera ahorrar espacio, para calcular estos seria con los de antes 
	// mas "length" en la componente Y
	vertexList[4].x=-semilength;
	vertexList[4].y=semilength;
	vertexList[4].z=semilength;

	vertexList[5].x=semilength;
	vertexList[5].y=semilength;
	vertexList[5].z=semilength;

	vertexList[6].x=semilength;
	vertexList[6].y=semilength;
	vertexList[6].z=-semilength;

	vertexList[7].x=-semilength;
	vertexList[7].y=semilength;
	vertexList[7].z=-semilength;

	/* ni las aristas ni las caras deberian cambiar pero por ahora 
	las dejo aqui */
	this->faceList1[0]=0;
	this->faceList2[0]=1;
	this->faceList3[0]=2;

	this->faceList1[1]=2;
	this->faceList2[1]=3;
	this->faceList3[1]=0;

	this->faceList1[2]=4;
	this->faceList2[2]=5;
	this->faceList3[2]=6;

	this->faceList1[3]=6;
	this->faceList2[3]=7;
	this->faceList3[3]=4;

	this->faceList1[4]=1;
	this->faceList2[4]=2;
	this->faceList3[4]=6;

	this->faceList1[5]=6;
	this->faceList2[5]=5;
	this->faceList3[5]=1;

	this->faceList1[6]=2;
	this->faceList2[6]=6;
	this->faceList3[6]=7;

	this->faceList1[7]=2;
	this->faceList2[7]=7;
	this->faceList3[7]=3;

	this->faceList1[8]=3;
	this->faceList2[8]=7;
	this->faceList3[8]=4;

	this->faceList1[9]=4;
	this->faceList2[9]=0;
	this->faceList3[9]=3;

	this->faceList1[10]=0;
	this->faceList2[10]=1;
	this->faceList3[10]=5;

	this->faceList1[11]=5;
	this->faceList2[11]=4;
	this->faceList3[11]=0;

	return 0;
}

int Cube::setLength(float _length) {
	this->length=_length;

	this->updated=false;

	return this->length;
}