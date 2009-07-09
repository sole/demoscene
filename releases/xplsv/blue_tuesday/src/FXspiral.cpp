#include "FXspiral.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXspiral::perFrame(float time) {

	static float t0=0;
	unsigned int update=0;
	if(time-t0>this->tUpdate) {
		update=1;
		t0=time;
	}
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(fac1, fac2);

	

	unsigned int i;
	glLineWidth(2);
	float g=this->width;

	glColor4f(planeColor.x, planeColor.y, planeColor.z, planeColor.w);
	

	glBegin(GL_QUADS);
	for(i=0;i<SPIRAL_VTX-1; i++) {
		if(update) {
			this->vertexList[i].y=this->vertexList[i].y+(0.15*i)*this->gravity.y ;
			if(this->vertexList[i].y<0)
				this->vertexList[i].y=0.1;
		}
		glVertex3f(this->vertexList[i].x,this->vertexList[i].y,this->vertexList[i].z);
		glVertex3f(this->vertexList[i+1].x,this->vertexList[i+1].y,this->vertexList[i+1].z);
		glVertex3f(this->vertexList[i+1].x+g,this->vertexList[i+1].y,this->vertexList[i+1].z+g);
		glVertex3f(this->vertexList[i].x+g,this->vertexList[i].y,this->vertexList[i].z+g);
	}
	glEnd();

	if(update) {
		this->vertexList[SPIRAL_VTX-1].y=this->vertexList[SPIRAL_VTX-1].y+this->gravity.y;
		if(this->vertexList[SPIRAL_VTX-1].y<0)
				this->vertexList[SPIRAL_VTX-1].y=0;
	}

	glColor4f(borderColor.x, borderColor.y, borderColor.z, borderColor.w);
	for(i=0;i<SPIRAL_VTX-1; i++) {
		glBegin(GL_LINE_STRIP);
		glVertex3f(this->vertexList[i].x,this->vertexList[i].y,this->vertexList[i].z);
		glVertex3f(this->vertexList[i+1].x,this->vertexList[i+1].y,this->vertexList[i+1].z);
		glVertex3f(this->vertexList[i+1].x+g,this->vertexList[i+1].y,this->vertexList[i+1].z+g);
		glVertex3f(this->vertexList[i].x+g,this->vertexList[i].y,this->vertexList[i].z+g);
		glEnd();
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void FXspiral::pushPoint(float _yvalue) {

	float max=5, exceso, dif;
	unsigned int i;
	for(i=SPIRAL_VTX-1;i>0;i--) {
		this->vertexList[i].y=this->vertexList[i-1].y;
	}
	exceso=max-_yvalue;
	if(exceso<0) {
		this->vertexList[0].y=_yvalue;//max;
		// y lo que sobra lo reparto
		exceso=-exceso;
		i=1;
		while(exceso > 0 && i<SPIRAL_VTX) {
			dif = (SPIRAL_VTX-i)*0.0015;
			this->vertexList[i].y+=dif;
			exceso-=dif;
			i++;
		}
	} else 
		this->vertexList[0].y=_yvalue;
	
}

void FXspiral::init(void) {
	

	if(strcmp(this->textureName,"")!=0) {
		// si hay textura la cargo
		LoadTGA(&planeData,textureName);
	}
}

void FXspiral::setPlaneColor(float r, float g, float b, float a) {
	this->planeColor.x=r;
	this->planeColor.y=g;
	this->planeColor.z=b;
	this->planeColor.w=a;
}

void FXspiral::setBorderColor(float r, float g, float b, float a) {
	this->borderColor.x=r;
	this->borderColor.y=g;
	this->borderColor.z=b;
	this->borderColor.w=a;
}

void FXspiral::setGravity(float x, float y, float z, float w) {
	this->gravity.x=x;
	this->gravity.y=y;
	this->gravity.z=z;
	this->gravity.w=w;
}
void FXspiral::setWidth(float _w) {
	this->width=_w;
}

void FXspiral::setBlendFunc(GLenum fac1,GLenum fac2) {
	this->fac1=fac1;
	this->fac2=fac2;
}

void FXspiral::setTextureName(char *filename) {

	strcpy(textureName,filename);
}

void FXspiral::start(void) {
	
}

void FXspiral::stop(void) {
	
}

void FXspiral::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	//if(planeData->texID!=NULL)
	//	glDeleteTextures(1, *planeData->texID);
}

FXspiral::FXspiral() {
	
	fac1=GL_SRC_ALPHA;
	fac2=GL_ONE_MINUS_SRC_ALPHA;
	strcpy(textureName,"");
	// color por defecto -> blanco, alpha=100%
	this->planeColor.x=1;
	this->planeColor.y=1;
	this->planeColor.z=1;
	this->planeColor.w=1;
	this->radioinc=0.9;
	this->tamSeg=8;

	unsigned int i;
	float ang, radio;
	radio=this->tamSeg*1.5;
	ang=0;
	for(i=0;i<SPIRAL_VTX; i++) {
		//ang=16*i*(2*3.1415)/SPIRAL_VTX;
		ang+=tamSeg / radio;
		this->vertexList[i].x= radio * sin(ang);
		this->vertexList[i].z= radio * cos(ang);
		this->vertexList[i].y= radio * 1.5 ;

		radio+=this->radioinc;
	}

	pos=0;

	gravity.x=0;
	gravity.y=-0.008;
	gravity.z=0;

	this->tUpdate=0.06;
	width=this->tamSeg/8;
}

FXspiral::~FXspiral() {
}
