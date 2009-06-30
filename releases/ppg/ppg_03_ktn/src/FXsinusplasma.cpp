#include "FXsinusplasma.h"
#include <math.h>
// inicializar lo estático aquí...
Point FXsinusplasma::vertexList[NUM_PT_PLASMA_X][NUM_PT_PLASMA_Y];
Point FXsinusplasma::colorList[NUM_PT_PLASMA_X][NUM_PT_PLASMA_Y];

float FXsinusplasma::xinc;
float FXsinusplasma::yinc;
float FXsinusplasma::zinc;
float FXsinusplasma::ancho;
float FXsinusplasma::alto;
float FXsinusplasma::largo;
float FXsinusplasma::lado;
	
// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXsinusplasma::perFrame(float time) {

	static float t_start = -1;
	float t_elapsed;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	time *= 0.001f;
	
	if(t_start == -1)
	{
		t_start = time;
	}
	
	t_elapsed = time - t_start;
	this->_time=time;

	static float pulso;
	if((this->_row%8)==0) {
		pulso=15;
	}
	if(pulso>0) {
		pulso=pulso - pulso*pulso*1.2;
	}

	//cam.toOGL();
//	miDemo->ponOrtopedico(9,9);
	miDemo->ponOrtopedico(12,12);
	//glRotatef(90,0,0,1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	
	glEnable(GL_SMOOTH);

	int x,y;
	float z_depth=3;
	
	float pi=3.14;
	float t;
	float aux;
	float a;
	t=t_elapsed*2+sin(pulso);
	//glRotatef(t*20,0,0,1);
	float sx=1.5+0.5*(sin(t_elapsed*0.1)+cos(t_elapsed*0.2));
	float sy=1.5+0.5*cos(t_elapsed*0.1);
	glScalef(sx,sy,1);
	glBegin(GL_QUADS);
	for(x=1;x<NUM_PT_PLASMA_X-1;x++) {
			for(y=1;y<NUM_PT_PLASMA_X-1;y++) {
				//0.1+float(0.05f*getSinTable((y*20+this->_row*9)%(TRIGPREC+1)));
				
					glNormal3f( 0.0f, 0.0f, 1.0f);
					//glTexCoord2f(bannerText[x][y][0], bannerText[x][y][1]); 
					/*
					  z1:=sin(x/freq_temp*1.7*pi);
             z2:=sin((x/3+y)/freq_temp*1.5*pi);
             z3:=sin(y/freq_temp*0.9*pi);
					*/
					a=1;
					
					//r=0.5+cos(x+t)+sin(vertexList[x][y].x+t);
					//g=0.5;
					//b=0.5+cos(y+t*2)+sin(t+vertexList[x][y].y);
					
					glColor4f(colorList[x][y].x,colorList[x][y].y,colorList[x][y].z,a);
					glVertex3f(vertexList[x][y].x, vertexList[x][y].y,z_depth);
					
					//r=0.5+sin(x+_time*1.7+1);
					//g=0.2;
					//b=0.5+cos(y+_time*1.5+1);
					
				//	glColor4f(r,g,b,a);
					//glTexCoord2f(bannerText[x+1][y][0], bannerText[x+1][y][1]);
					glColor4f(colorList[x+1][y].x,colorList[x+1][y].y,colorList[x+1][y].z,a);
					glVertex3f( vertexList[x+1][y].x, vertexList[x+1][y].y, z_depth);

					//r=0.5+sin(x+_time*1.7+2);
					//g=0.2;
					//b=0.5+cos(y+_time*1.5+2);
					
				//	glColor4f(r,g,b,a);
 					//glTexCoord2f(bannerText[x+1][y+1][0], bannerText[x+1][y+1][1]);
					glColor4f(colorList[x+1][y+1].x,colorList[x+1][y+1].y,colorList[x+1][y+1].z,a);
					glVertex3f( vertexList[x+1][y+1].x, vertexList[x+1][y+1].y,  z_depth);

					//r=0.5+sin(x+_time*1.7+3);
					//g=0.2;
					//b=0.5+cos(y+_time*1.5+3);
					
				//	glColor4f(r,g,b,a);
					//glTexCoord2f(bannerText[x][y+1][0], bannerText[x][y+1][1]);
					glColor4f(colorList[x][y+1].x,colorList[x][y+1].y,colorList[x][y+1].z,a);
					glVertex3f(vertexList[x][y+1].x, vertexList[x][y+1].y,z_depth);

					//glVertex3f(0,0,0);
				
				this->colorList[x][y].x=0.7+0.5*(sin(vertexList[x][y].x+t + vertexList[x][y].z)+sin(vertexList[x][y].x+t*5 + vertexList[x][y].z));//+0.5*sin(vertexList[x][y].x+t);
				this->colorList[x][y].y=2+sin(t);//1+0.5*(sin(vertexList[x][y].x+t*0.1 + vertexList[x][y].z)+sin(vertexList[x][y].y+t*2 + vertexList[x][y].z));
				this->colorList[x][y].z=0.7+0.5*(sin(vertexList[x][y].y+t*1.7 + vertexList[x][y].z)+sin(vertexList[x][y].y+t*0.5 + vertexList[x][y].z)) +this->colorList[x][y].x;

				this->colorList[x][y].x=fmod(this->colorList[x][y].x + this->colorList[x][y].y,1.1+cos(t));
				this->colorList[x][y].z=fmod(this->colorList[x][y].z + this->colorList[x][y].y,1.1+sin(t));

				aux=this->colorList[x][y].y;
				this->colorList[x][y].y=this->colorList[x][y].x;
				this->colorList[x][y].x=aux;

				this->vertexList[x][y].z=10*(sin(t*0.1)+cos(t*0.5));
			}
		}	glEnd();

	
	glDisable(GL_SMOOTH);
	
	/*glBegin(GL_QUADS);
		glColor3f(1,0,0);
		glVertex3f(0,0,z);

		glColor3f(1,1,0);
		glVertex3f(1,0,z);

		glColor3f(1,0,1);
		glVertex3f(1,1,z);

		glColor3f(0,1,1);
		glVertex3f(0,1,z);
	glEnd();
	*/
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	miDemo->quitaOrtopedico();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// fade
	float alfita;
	if(_row<=16) {
		alfita=float(16-_row)/16.0;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfita);
		fxfade->perFrame(t_elapsed);
		glEnable(GL_DEPTH_TEST);
	}
	else if(_row>=112) {
		alfita=float(_row%16)/16.0;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfita);
		fxfade->perFrame(t_elapsed);
		glEnable(GL_DEPTH_TEST);
	}
}

void FXsinusplasma::init(void) {
	// asignar recursos y tal, cargar ficheros, blabla

//	this->conPrec=5;

	
	this->ancho=5;
	this->alto=ancho;
	this->largo=ancho;
	float origenx=-ancho;
	float origeny=-alto;
	float origenz=-largo;
	xinc=2*ancho/float(NUM_PT_PLASMA_X);
	yinc=2*alto/float(NUM_PT_PLASMA_Y);
	zinc=2*largo/float(NUM_PT_PLASMA_X);
	this->lado=ancho/(NUM_PT_PLASMA_X);
	
	int i,j;
	float z;
	z=0.5;
	for(i=0;i<NUM_PT_PLASMA_X;i++) {
		for(j=0;j<NUM_PT_PLASMA_Y;j++) {
		
				this->vertexList[i][j].x=origenx+xinc*i;
				this->vertexList[i][j].y=origeny+yinc*j;
				this->vertexList[i][j].z=z;
				
				this->colorList[i][j].x=1+0.5*sin(vertexList[i][j].x);
				this->colorList[i][j].y=0.5;//
				this->colorList[i][j].z=1+0.5*sin(vertexList[i][j].y);
		
		}
	}
}

void FXsinusplasma::start(void) {
	glEnable(GL_SMOOTH);
	// poner los parametros del radialblur
	fxradialblur->setInc(0.01f);
	fxradialblur->setTimes(10);
	fxradialblur->setView(miDemo->getWidth(),miDemo->getHeight());
	fxradialblur->setClearColor(0.25,0.1,0.5,1);
	fxradialblur->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// a ver si el viewport está pocho
	glViewport(0,0,miDemo->getWidth(),miDemo->getHeight());
	glClearColor(0,0,0,0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glPointSize(4);
	glEnable(GL_LINE_SMOOTH);
}

void FXsinusplasma::stop(void) {
	glEnable(GL_DEPTH_TEST);
}

void FXsinusplasma::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	
}

FXsinusplasma::FXsinusplasma() {
}

FXsinusplasma::~FXsinusplasma() {
}
