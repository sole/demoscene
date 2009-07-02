#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif

#include <math.h>

Sphere::Sphere() {
	// crear los vertices
	this->vertexList=new(Point[4]);
	// y asignar el numvertex
	this->numVertex=4;

	// Y las caras tb molan mucho
	int c=4;
	this->numFaces=c;
	this->faceList1=new(int[c]);
	this->faceList2=new(int[c]);
	this->faceList3=new(int[c]);


	// La longitud inicial de cada cara será 1.0f, pq lo digo yo
	this->length=1.0f;

	this->iterations=1;
	// completar la info de cada vertice (¿llamar a update?)
	//this->update();
}


Sphere::~Sphere() {
}

int Sphere::update() {

	float semilength=this->length*0.5f;

	// "fulimino" los vértices y las caras
	delete this->vertexList;
	delete this->faceList1;
	delete this->faceList2;
	delete this->faceList3;
	
	// Cuantos necesitaré?
	int numFinalCaras;
	int numFinalVertices;
	int tmpV,tmpF;
	int i;

	tmpV=4;
	tmpF=4;
	for(i=1;i<=this->iterations;i++) {
		tmpV=tmpV+tmpF;
		tmpF=tmpF*3;
	}
	
	numFinalCaras=tmpF;
	numFinalVertices=tmpV;

	this->vertexList=new(Point[numFinalVertices]);
	this->faceList1=new(int[numFinalCaras]);
	this->faceList2=new(int[numFinalCaras]);
	this->faceList3=new(int[numFinalCaras]);

	this->numFaces=4;
	this->numVertex=4;

	// [re]generar los vértices
	vertexList[0].x=0;
	vertexList[0].y=semilength;
	vertexList[0].z=0;

	vertexList[1].x=-semilength;
	vertexList[1].y=-semilength;
	vertexList[1].z=semilength;

	vertexList[2].x=semilength;
	vertexList[2].y=-semilength;
	vertexList[2].z=0;//-semilength;

	vertexList[3].x=0;//-semilength;
	vertexList[3].y=-semilength;
	vertexList[3].z=-semilength;

	this->faceList1[0]=0;
	this->faceList2[0]=1;
	this->faceList3[0]=2;

	this->faceList1[1]=0;
	this->faceList2[1]=2;
	this->faceList3[1]=3;

	this->faceList1[2]=0;
	this->faceList2[2]=3;
	this->faceList3[2]=1;

	this->faceList1[3]=3;
	this->faceList2[3]=1;
	this->faceList3[3]=2;

	
	// Ahora lo masivo!! Al ataqueeeeeee!!
	int j;
	Point p1,p2,p3,p4;
	int v1,v2,v3,v4;
	tmpF=this->numFaces;
	tmpV=this->numVertex;
	char s[255];
	int maxIterations=this->iterations;
	for(i=1;i<maxIterations;i++) {
		// Cara por cara, la subdividiré (las veces que me obligue iterations)
		for(j=0;j<this->numFaces;j++) {
			//sprintf(s,"maxF %d f %d maxV %d v %d\n",numFinalCaras,tmpF,numFinalVertices,tmpV);
			//OutputDebugString(s);

			assert(tmpF<=numFinalCaras);
			// Los índices de vértices de la cara j
			v1=this->faceList1[j];
			v2=this->faceList2[j];
			v3=this->faceList3[j];
			
			// el nuevo vértice a especificar
			v4=tmpV;

			// Los puntos en sí
			p1=this->vertexList[v1];
			p2=this->vertexList[v2];
			p3=this->vertexList[v3];

			// Y el nuevo punto!
			p4.x=(p1.x+p2.x+p3.x)/3.0f;
			p4.y=(p1.y+p2.y+p3.y)/3.0f;
			p4.z=(p1.z+p2.z+p3.z)/3.0f;

			// Asignacion en la lista de puntos
			this->vertexList[v4]=p4;

			// Hay que "redirigir" las caras a su nueva ubicacion y tal
			// De cada cara resultan 3, o sea, la antigua y 2 nuevas
			// Se cambia la antigua y se inicializan las nuevas.

			//antigua cara 
			this->faceList1[j]=v1;
			this->faceList2[j]=v4;
			this->faceList3[j]=v3;

			//nueva cara 1
			this->faceList1[tmpF]=v1;
			this->faceList2[tmpF]=v2;
			this->faceList3[tmpF]=v4;

			//nueva cara 2
			this->faceList1[tmpF+1]=v2;
			this->faceList2[tmpF+1]=v3;
			this->faceList3[tmpF+1]=v4;

			// Actualizamos el numero de caras y vertices tmp
			// No se actualiza directamente el de la clase pq sino el bucle iria mal
			tmpF=tmpF+2;//+2;
			tmpV++;

			
		}this->numFaces=tmpF; // para q asi tb divida las ultimas creadas ¿?
	}

	this->numFaces=tmpF;
	this->numVertex=tmpV;

	// Ahora "curvo" la esfera
	float radioXY,radioYZ,radioXZ,alfa,beta,comp1,comp2;
	float equiv=180.0/3.141592;
	float pi=3.141592;
	float modulo,modulo2;
	for(i=0;i<this->numVertex;i++) {
		p1=this->vertexList[i];
break;
		/*
		float lon;
		lon= (float)acos(z/sqrt(x*x+z*z));		
		if(x<0) lon= 2*PI-lon; //radianes

		float lat;
		lat= (float)acos(sqrt(x*x-z*z)/modulo());		
		if(y<0) lat= -lat; //radianes
		*/


		// primero obtendre la proyeccion del radio sobre el plano XY
		//alfa=atan(p1.y/p1.x);
		//sprintf(s,"%d x %f y %f z%f\n",i,p1.x,p1.y,p1.z);
		//OutputDebugString(s);
		
		modulo=sqrt(p1.x*p1.x+p1.z*p1.z);
		if(modulo==0) {
			modulo=1;
		}
		alfa=(float)acos(p1.z/modulo);
		/*if(p1.x<0) {
			alfa=2*pi - alfa;
		}*/
		comp1=cos(alfa)*p1.x;
		comp2=sin(alfa)*p1.y;
		radioXY=sqrt(comp1*comp1 + comp2*comp2);
		//alfa=gamma;//asin(p1.y/radioXY);// en radianes

		// Ahora quiero saber qué se cuece en el plano YZ
		//beta=acos(p1.z/radioYZ); // en radianes
	/*	beta=atan(-p1.y/p1.z);
		comp1=cos(beta)*p1.z;
		comp2=sin(beta)*p1.y;
		radioYZ=sqrt(comp1*comp1 + comp2*comp2);*/
		//beta=atan(p1.z/p1.x);
		
		modulo=sqrt(p1.x*p1.x-p1.z*p1.z);
		if(modulo==0) {
			modulo=1;
		}
		modulo2=sqrt(p1.x*p1.x + p1.y*p1.y + p1.z*p1.z);
		if(modulo2==0) {
			modulo2=1;
		}
		beta=(float)acos(sqrt(modulo2)/(modulo));
		/*if(p1.y<0) {
			beta=-beta;
		}*/
		comp1=cos(beta)*p1.x;
		comp2=sin(beta)*p1.z;

		//sprintf(s,"radio de %d es %f\n",i,radio);
		//sprintf(s,"%d alfa %f beta %f\n",i,alfa,beta);
		//OutputDebugString(s);
		//sprintf(s,"cos de alfa %f sin de alfa %f cos de beta %f\n",cos(alfa),sin(alfa),cos(beta));
		//OutputDebugString(s);
		// Nuevos valores X Y Z
		this->vertexList[i].x=this->length*cos(alfa)*0.5;
		this->vertexList[i].y=this->length*sin(alfa)*0.5;
		this->vertexList[i].z=this->length*cos(beta);
		//sprintf(s,"x %f y %f z %f\n",this->vertexList[i].x,this->vertexList[i].y,this->vertexList[i].z);
		//OutputDebugString(s);
	}

	this->updated=true;
	return 0;
}

int Sphere::setLength(float _length) {
	this->length=_length;

	this->updated=false;

	return this->length;
}

int Sphere::setIterations(int _iterations) {
	this->iterations=_iterations;

	//this->updated=false;

	return this->iterations;
}

void Sphere::perFrame(float time) {
	/*float lo=1;
	for(int i=0;i<this->numVertex;i++) {
		this->vertexList[i].x=lo*sin(time+i*2);
		this->vertexList[i].y=lo*cos(time+i+this->vertexList[i].x);
		this->vertexList[i].z=lo*sin(time+i+this->vertexList[i].y);
	}*/
	Shape::perFrame(time);
}