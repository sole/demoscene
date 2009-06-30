#include "FXtext.h"
#include <math.h>
TextureImage FXtext::textura;	
// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXtext::perFrame(float time) {

	
	miDemo->ponOrtopedico(5,5);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
glColor4f(color.x,color.y,color.z,color.w);
	glBegin(GL_LINES);
	glVertex3f(0,0,1);
	glVertex3f(this->altoCar,0,1);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura.texID);	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glDisable(GL_DEPTH_TEST); // creo q me puedo arriesgar a dejarlo x ahora asi si veo q falla consultaria el estado q hubiera antes y tal blbalbal

	
	
	float z_depth=0.2;
	float xs=1;
	int i;
	for(i=0;i<this->numChar2See;i++) {
		glLoadIdentity();
		glTranslatef(i*(1.0+xs)/this->numChar2See,0,0);
		glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			
			glTexCoord2f(0,this->textPos[i]); 
			glColor3f(1,0,0);
			glVertex3f(0,0,z_depth);

			glTexCoord2f(1,this->textPos[i]); 
			glColor3f(0,1,0);
			glVertex3f(xs,0,z_depth);

			glTexCoord2f(1,this->textPos[i]+this->size_y); 
			glColor3f(0,0,1);
			glVertex3f(xs,1,z_depth);

			glTexCoord2f(0,this->textPos[i]+this->size_y);
			glColor3f(1,1,0);
			glVertex3f(0,1,z_depth);


		glEnd();
	}

	
	glMatrixMode(GL_MODELVIEW);	
	glPopMatrix();
	
	

	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();

	miDemo->quitaOrtopedico();
//	glMatrixMode(GL_PROJECTION);
//	glPopMatrix();
}

void FXtext::init(void) {
	// color por defecto -> blanco
	this->color.x=1;
	this->color.y=1;
	this->color.z=1;
	this->color.w=1;

	this->pos.x=0;
	this->pos.y=0;
	this->pos.z=-1;
	this->pos.w=0;

	this->spacingPixels=3;
	//this->altoCar=16;
	this->anchoCar=32;

	this->textSize=256;
	
	// cargo la megatextura
	LoadTGA(&textura,".\\data\\textohelp2.tga");

	// Amos a preparar las coordenadas Y de fuente
	this->charCount=4;//90;
	this->altoCar=1.0/this->charCount;

	size_y=1.0/this->charCount; // esto lo deja en 0..1, perfecto.
	float ypos;
	int i;

	for(i=0;i<this->charCount;i++) {
		this->textPos[i]=1-size_y*i;
	}

}

void FXtext::setColor(float r, float g, float b, float a) {
	this->color.x=r;
	this->color.y=g;
	this->color.z=b;
	this->color.w=a;
}

void FXtext::setString(char *string) {
	//txt q queremos ver
	strcpy(buffer,string);
	this->numChar2See=strlen(buffer);
}
void FXtext::setPos(float x,float y) {
	// posicion de pantalla en q queremso dibujar..
	// se recomeinda margen de -1 a 1 en x y en y
	this->pos.x=x;
	this->pos.y=y;
}


void FXtext::start(void) {
	
}

void FXtext::stop(void) {
	
}

void FXtext::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
}

FXtext::FXtext() {
}

FXtext::~FXtext() {
}