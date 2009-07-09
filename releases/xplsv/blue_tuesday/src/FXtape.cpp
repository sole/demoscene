#include "FXtape.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXtape::perFrame(float time) {

	static float t0=0;
	unsigned int update=0;

	unsigned int i,j,index;
	
	// Update the curves data
	Punto punto, normal;
	Punto c0,c1,c2,c3,c4;
	
	// primera curva, caso base
	punto.x=this->vertexList[0].x;
	punto.y=this->vertexList[0].y;
	punto.z=this->vertexList[0].z;
	punto.w=this->vertexList[0].w;
	this->curveList[0].modificaPunto(0,punto);

	// tangente 1 (punto de control 2)
	c0=this->curveList[0].control(0);
	punto.x=this->vertexList[1].x;
	punto.y=this->vertexList[1].y;
	punto.z=this->vertexList[1].z;
	punto.w=this->vertexList[1].w;
	c1=(punto-c0)*3;
	this->curveList[0].modificaPunto(1,c1);

	// punto final
	c3.x=this->vertexList[3].x;
	c3.y=this->vertexList[3].y;
	c3.z=this->vertexList[3].z;
	c3.w=this->vertexList[3].w;
	this->curveList[0].modificaPunto(3,c3);

	// tangente 2 (punto de control 3)
	c0=this->curveList[0].control(0);
	punto.x=this->vertexList[1].x;
	punto.y=this->vertexList[1].y;
	punto.z=this->vertexList[1].z;
	punto.w=this->vertexList[1].w;
	c1=(punto-c0)*3;
	this->curveList[0].modificaPunto(1,c1);
	

	for(i=1;i<this->numCurves;i++) {
		
		index=3 + (i-1)*2;

		// primer pto es igual que el anterior
		
		punto=this->curveList[i-1].control(3);
		this->curveList[i].modificaPunto(0,punto);

		// siguiente punto: tangente, me baso en la curva previa, ya que quiero tener la misma tangente
		punto=(this->curveList[i-1].control(3) - this->curveList[i-1].control(2)) + this->curveList[i].control(0);
	

		this->curveList[i].modificaPunto(1,punto);

		// punto final de esta curva
		punto.x=this->vertexList[index+2].x;
		punto.y=this->vertexList[index+2].y;
		punto.z=this->vertexList[index+2].z;
		punto.w=this->vertexList[index+2].w;
		this->curveList[i].modificaPunto(3,punto);
		
		// y la ultima tangente
		punto.x=this->vertexList[index+1].x;
		punto.y=this->vertexList[index+1].y;
		punto.z=this->vertexList[index+1].z;
		punto.w=this->vertexList[index+1].w;
		c3=this->curveList[i].control(3);

		c2=(c3-punto)*3;

		this->curveList[i].modificaPunto(2,punto);


	}

	// empezamos a dibujar ya!!!!!

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	if(this->planeColor.w!=1)
		glEnable(GL_BLEND);
	if(this->withTexture)
		glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, planeData.texID);
		
	glColor4f(planeColor.x,planeColor.y,planeColor.z,planeColor.w);
	glBlendFunc(fac1, fac2);

	float g=this->width;

	Point p, p2;

	glBegin(GL_QUADS);

	unsigned int drawnParts=0;
	i=0;
	while( (i<this->numCurves) && (drawnParts<this->numDrawParts) ) {		
		this->curveList[i].tramosCurva(this->curvePrecision, this->tramosTemp);
		
		
		// dibujo del primer vertice de la curva al primer tramo
		punto=this->curveList[i].control(0);
		p.x=punto.x;
		p.y=punto.y;
		p.z=punto.z;

		p2.x=this->tramosTemp[0].x;
		p2.y=this->tramosTemp[0].y;
		p2.z=this->tramosTemp[0].z;

		
		if(drawnParts>= this->startDrawingCurve) {
			glTexCoord2f(0,0);
			glVertex3f(p.x,p.y,p.z);
			glTexCoord2f(0,1);
			glVertex3f(p2.x,p2.y,p2.z);
			glTexCoord2f(1,1);
			glVertex3f(p2.x+g,p2.y,p2.z+g);
			glTexCoord2f(1,0);
			glVertex3f(p.x+g,p.y,p.z+g);
		}

		// La normal
		normal=(punto^this->tramosTemp[0]);
		glNormal3f(normal.x, normal.y, normal.z);

		

		this->lastPoint.x=p2.x;
		this->lastPoint.y=p2.y;
		this->lastPoint.z=p2.z;

		drawnParts++;
	

		// dibujo de las subdivisiones intermedias de la curva
		for(j=0;((j<this->curvePrecision)&&(drawnParts<this->numDrawParts));j++) {
			p.x=this->tramosTemp[j].x;
			p.y=this->tramosTemp[j].y;
			p.z=this->tramosTemp[j].z;

			p2.x=this->tramosTemp[j+1].x;
			p2.y=this->tramosTemp[j+1].y;
			p2.z=this->tramosTemp[j+1].z;

			if(drawnParts>= this->startDrawingCurve) {
				glTexCoord2f(0,0);
				glVertex3f(p.x,p.y,p.z);
				glTexCoord2f(0,1);
				glVertex3f(p2.x,p2.y,p2.z);
				glTexCoord2f(1,1);
				glVertex3f(p2.x+g,p2.y,p2.z+g);
				glTexCoord2f(1,0);
				glVertex3f(p.x+g,p.y,p.z+g);

				// La normal
				normal=(this->tramosTemp[j]^this->tramosTemp[j+1]);
				glNormal3f(normal.x, normal.y, normal.z);

				// lo mismo pero abajo
				if(abs(this->height)!=0) {
					// justo lo de abajo
					glVertex3f(p.x,p.y-this->height,p.z);
					glVertex3f(p2.x,p2.y-this->height,p2.z);
					glVertex3f(p2.x+g,p2.y-this->height,p2.z+g);
					glVertex3f(p.x+g,p.y-this->height,p.z+g);

					// lateral derecho
					glVertex3f(p.x,p.y-this->height,p.z);
					glVertex3f(p2.x,p2.y-this->height,p2.z);
					glVertex3f(p2.x,p2.y,p2.z+g);
					glVertex3f(p.x,p.y,p.z+g);

					// lateral izquierdo
					glVertex3f(p.x,p.y-this->height,p.z);
					glVertex3f(p2.x,p2.y-this->height,p2.z);
					glVertex3f(p2.x,p2.y,p2.z);
					glVertex3f(p.x,p.y,p.z);
				}

				this->lastLook.x=(p2.x-this->lastPoint.x);
				this->lastLook.y=(p2.y-this->lastPoint.y);
				this->lastLook.z=(p2.z-this->lastPoint.z);

				this->lastPoint.x=p2.x;
				this->lastPoint.y=p2.y;
				this->lastPoint.z=p2.z;

			}
			drawnParts++;
			
		}

		// dibujo del ultimo tramo al ultimo vertice de la curva
		//glColor4f(1,0,1,1);
		punto=this->curveList[i].control(3);
		p2.x=punto.x;
		p2.y=punto.y;
		p2.z=punto.z;

		p.x=this->tramosTemp[this->curvePrecision].x;
		p.y=this->tramosTemp[this->curvePrecision].y;
		p.z=this->tramosTemp[this->curvePrecision].z;

		if(drawnParts>= this->startDrawingCurve) {
			glVertex3f(p.x,p.y,p.z);
			glVertex3f(p2.x,p2.y,p2.z);
			glVertex3f(p2.x+g,p2.y,p2.z+g);
			glVertex3f(p.x+g,p.y,p.z+g);
		}
		// La normal
		normal=(punto^this->tramosTemp[this->curvePrecision]);
		glNormal3f(normal.x, normal.y, normal.z);

		i++;	
	}

	glEnd();

	if(this->planeColor.w!=1)
		glDisable(GL_BLEND);
	if(this->withTexture)
		glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();	

}

void FXtape::setNumVertex(unsigned int num) {
	this->numVertex=num;
}

void FXtape::setNumDrawParts(unsigned int num) {
	this->numDrawParts=num;
}

unsigned int FXtape::getNumDrawParts(void) {
	return this->numDrawParts;
}


unsigned int FXtape::getNumVertex(void) {
	return this->numVertex;
}

void FXtape::setPointAt(unsigned int index, float x, float y, float z, float w) {
	if((index>=0) && (index < this->numVertex)) {
		this->vertexList[index].x=x;
		this->vertexList[index].y=y;
		this->vertexList[index].z=z;
		this->vertexList[index].w=w;
	}
}

Point FXtape::getPointAt(unsigned int index) {
	return this->vertexList[index];
}

void FXtape::setCurvePrec(unsigned int prec) {
	this->curvePrecision=prec;
}

unsigned int FXtape::getCurvePrec(void) {
	return this->curvePrecision;
}

void FXtape::setHeight(float _h) {
	this->height=_h;
}


void FXtape::setWidth(float _w) {
	this->width=_w;
}

Point FXtape::getLastPoint() {
	return this->lastPoint;
}

Point FXtape::getLastLook() {
	return this->lastLook;
}

void FXtape::init(void) {
	

	if(strcmp(this->textureName,"")!=0) {
		// si hay textura la cargo
		LoadTGA(&planeData,textureName);
		this->withTexture=1;
	}
	
	// Si no se ha especificado un path, hago un init a lo típico, con los otros parámetros
	if(strcmp(this->filePath,"")==0) {
		// Preparo espacio para los vértices
		this->vertexList=new Point[this->numVertex];

		// numero de curvas:
		this->numCurves=(int)(this->numVertex-1)/3;
		this->curveList=new CurvaBezier[this->numCurves];

		
	} else {
		unsigned int i, numV;
		miPath.loadPath(this->filePath);
		numV=miPath.getNumICP();
		this->numVertex=numV;
		this->vertexList=new Point[numV];
		this->numCurves=(int)(this->numVertex-1)/3;
		this->curveList=new CurvaBezier[this->numCurves];
		Point p;
		for(i=0;i<numV;i++) {
			miPath.getPointAt(i,&p);
			this->setPointAt(i,p.x,p.y,p.z,p.w);
		}
	}
	
	// espacio temporal para almacenar los tramos intermedios
	this->tramosTemp=new Punto[this->curvePrecision+2];

	if(this->numCurves>0) {
		this->lastLook.x=this->curveList[0].control(0).x;
		this->lastLook.y=this->curveList[0].control(0).y;
		this->lastLook.z=this->curveList[0].control(0).z;
		this->lastLook.w=this->curveList[0].control(0).w;

	}
	
}

void FXtape::setPlaneColor(float r, float g, float b, float a) {
	this->planeColor.x=r;
	this->planeColor.y=g;
	this->planeColor.z=b;
	this->planeColor.w=a;
}

Point FXtape::getPlaneColor(void) {
	return this->planeColor;
}


void FXtape::setBorderColor(float r, float g, float b, float a) {
	this->borderColor.x=r;
	this->borderColor.y=g;
	this->borderColor.z=b;
	this->borderColor.w=a;
}

void FXtape::setBlendFunc(GLenum fac1,GLenum fac2) {
	this->fac1=fac1;
	this->fac2=fac2;
}

void FXtape::setTextureName(const char *filename) {
	strcpy(textureName,filename);
}

void FXtape::setPathName(const char *filename) {
	strcpy(filePath,filename);
}

void FXtape::start(void) {
	
}

void FXtape::stop(void) {
	
}

void FXtape::deInit(void) {
	
}

FXtape::FXtape() {
	
	fac1=GL_SRC_ALPHA;
	fac2=GL_ONE_MINUS_SRC_ALPHA;
	strcpy(textureName,"");
	strcpy(filePath,"");
	// color por defecto -> blanco, alpha=100%
	this->planeColor.x=1;
	this->planeColor.y=1;
	this->planeColor.z=1;
	this->planeColor.w=1;

	this->numVertex=0;
	this->numCurves=0;

	// al máximo
	this->numDrawParts=10000;

	// 
	this->height=2;
	this->width=2;

	this->withTexture=0;
	
	this->startDrawingCurve=0;
}

FXtape::~FXtape() {
}

void FXtape::setStartDrawingCurve(unsigned int _start) {
	this->startDrawingCurve=_start;
}
