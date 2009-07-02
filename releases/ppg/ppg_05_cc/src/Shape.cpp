#include "Shape.h"

#include "my_opengl.h"

Shape::Shape() {
	this->numVertex=0;
	this->vertexList=NULL;
	this->numFaces=0;
	this->faceList1=NULL;
	this->faceList2=NULL;
	this->faceList3=NULL;
	this->dibujarWire=1;
	this->dibujarPolys=1;
	this->dibujarVert=1;
	this->dibujarNorm=1;


	this->polyAlpha=0.5f;
	this->polyColor.x=1;
	this->polyColor.y=1;
	this->polyColor.z=1;
}

Shape::~Shape() {
	/* solo vaciaré los vértices si se han creado */
	if((this->numVertex>0) || (this->vertexList!=NULL)) {
		delete this->vertexList; // (qué miedo me da esta línea!! me huele a petada segura)
		delete this->faceList1;
		delete this->faceList2;
		delete this->faceList3;
		this->numFaces=0;
		this->numVertex=0;
	}
}

void Shape::perFrame(float time) {
	// a dibujarrrrrr!
	int i;
	int v1,v2,v3;

	// Si la figura no está actualizada, tengo que actualizarla antes de dibujar
	if(!this->isUpdated()) {
		this->update();
	}

	if(this->dibujarVert==1) {
		glBegin(GL_POINTS);
		for(i=0;i<this->numVertex;i++) {
			glVertex3f(this->vertexList[i].x,this->vertexList[i].y,this->vertexList[i].z);
		}
		glEnd();
	}

	/*glLineWidth(1); ///////// EJES
	glColor3f(1,0,0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(100,0,0);
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(0,100,0);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(0,0,100);
	glEnd();*/

	if(this->dibujarPolys==1) {
		float trans=this->polyAlpha;
		glBegin(GL_TRIANGLES);
		for(i=0;i<this->numFaces;i++) {
			v1=this->faceList1[i];
			v2=this->faceList2[i];
			v3=this->faceList3[i];
			glColor4f(polyColor.x,0,0,trans);
			glVertex3f(this->vertexList[v1].x,this->vertexList[v1].y,this->vertexList[v1].z);
			glColor4f(0,polyColor.y,0,trans);
			glVertex3f(this->vertexList[v2].x,this->vertexList[v2].y,this->vertexList[v2].z);
			glColor4f(0,0,polyColor.z,trans);
			glVertex3f(this->vertexList[v3].x,this->vertexList[v3].y,this->vertexList[v3].z);
		
		}
	glEnd();
	}

	// las normales 
	if(this->dibujarNorm==1) {
		glColor4f(1,1,0,1);
		glBegin(GL_LINES);
		for(i=0;i<this->numFaces;i++) {
			v1=this->faceList1[i];
			v2=this->faceList2[i];
			v3=this->faceList3[i];
			glVertex3f(0,0,0);
			glVertex3f(this->vertexList[v1].x,this->vertexList[v1].y,this->vertexList[v1].z);
			glVertex3f(0,0,0);
			glVertex3f(this->vertexList[v2].x,this->vertexList[v2].y,this->vertexList[v2].z);
			glVertex3f(0,0,0);
			glVertex3f(this->vertexList[v3].x,this->vertexList[v3].y,this->vertexList[v3].z);
		
		}
		glEnd();
	}
	// uniendo todos los vértices :-¿?¿?
	if(this->dibujarWire==1) {
		glColor3f(1,0,1);
		glBegin(GL_LINE_STRIP);
		for(i=0;i<this->numVertex;i++) {
			glVertex3f(this->vertexList[i].x,this->vertexList[i].y,this->vertexList[i].z);
		}
		glVertex3f(this->vertexList[0].x,this->vertexList[0].y,this->vertexList[0].z);
		glEnd();
	}
}

void Shape::deInit(void) {
}

void Shape::setWire(int _wire) {
	this->dibujarWire=_wire;
}

void Shape::setPolys(int _polys) {
	this->dibujarPolys=_polys;
}

void Shape::setVert(int _vert) {
	this->dibujarVert=_vert;
}

void Shape::setNorm(int _norm) {
	this->dibujarNorm=_norm;
}

int Shape::getNumVertex(void) {
	return this->numVertex;
}

Point Shape::getVertex(int numV){
	return this->vertexList[numV];
}

void Shape::setVertex(int numV, Point p) {
	this->vertexList[numV].x=p.x;
	this->vertexList[numV].y=p.y;
	this->vertexList[numV].z=p.z;
	this->vertexList[numV].w=p.w;
}

void Shape::setPolyAlpha(float _a) {
	this->polyAlpha=_a;
}

void Shape::setPolyColor(Point _p){
	this->polyColor=_p;
}
void Shape::setPolyColorR(float _r){
	this->polyColor.x=_r;
}
void Shape::setPolyColorG(float _g){
	this->polyColor.y=_g;
}
void Shape::setPolyColorB(float _b){
	this->polyColor.z=_b;
}
