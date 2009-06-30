#include "FXmanga.h"
#include <math.h>
// inicializar lo estático aquí...
float FXmanga::bannerMesh[X_SLICES][Y_SLICES][2];
float FXmanga::bannerMeshAux[X_SLICES][Y_SLICES][2];
float FXmanga::bannerText[X_SLICES][Y_SLICES][2];
Camera FXmanga::cam;

TextureImage FXmanga::text_oso;
TextureImage FXmanga::text_k;

GLUquadricObj *FXmanga::quad;

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXmanga::perFrame(float time) {
	float z_depth=-0.0120f,y_desp;
	static float pulso=0;
	int i;

	fxradialblur->prepareFrame();	
	
	glClearColor(0.8,0,0.8,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	//------------ matriz de objetos/whatever
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glColor3f(1,1,1);
	float z=0;
	
	cam.toOGL();
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);
	glLineWidth(1.5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(3,3,3);
	glRotatef(time * 0.15,0,1,0);
	glTranslatef(-1,0,0);
	// una k , q se me ha ocurrido
	for(i=1; i < 9;i++)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(0.1*i,0,0);
		glBegin(GL_LINE_STRIP);
			glVertex3f(0,2,z);
			glVertex3f(0,-2,z);
			glVertex3f(0.2,-2,z);
			glVertex3f(1.7,2,z);
			glVertex3f(1.9,2,z);
			glVertex3f(1.1,0.1,z);
			glVertex3f(2,-2,z);
		glEnd();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	
	//------------ fin de matriz de objetos

	fxradialblur->postprepareFrame();
	fxradialblur->perFrame(time);
	
	miDemo->ponOrtopedico(1,1);//(miDemo->getWidth(),miDemo->getHeight()); // el q debe ser es 2,2
	glEnable(GL_BLEND);
	
	// ahora algunos adornos technoish

	//glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	//glBlendFunc(GL_DST_COLOR,  GL_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);

	float c=1 ; // componente de color , es para hacer un grisaceo
	int slices = 64;
	float part1, part2;
	float d1; // estas distancias las usare para cambiar el radio de los discos
	glColor4f(c,c,c,0.3);

	d1=0.25*sin(time*0.005);
	// Varios círculos (algunos fijos y otros no)
	gluDisk(quad,0.02f,0.025f,slices,slices);
	gluDisk(quad,0.08f,0.1f,slices,slices);
	gluDisk(quad,0.36f+d1,0.362f+d1,slices/2,slices/2);
	gluDisk(quad,0.36f+d1+d1,0.362f+d1+d1,slices/2,slices/2);
	gluDisk(quad,0.4f,0.41f,slices,slices);
	
	// Trocitos de pizza pero en disco
	part1=0;

	// Trozos del centro
	part2=20;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	for(i=1;i<4;i++) {
		glRotatef(time*.1,0,0,-1);
		gluPartialDisk(quad,0.06f,0.08f,slices,slices,part1,part2-part1);	
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	
	// Trozos intermedios
	part2=20;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	for(i=1;i<6;i++) {
		glRotatef(time*.05,0,0,1);
		gluPartialDisk(quad,0.2f,0.30f,slices,slices,part1,part2-part1);	
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	// Trozos mas gordos
	part2=30;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	for(i=1;i<4;i++) {
		glRotatef(time*.0200,0,0,-1);
		gluPartialDisk(quad,0.5f,1.5f,slices,slices,part1,part2-part1);	
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	// ---------fin adornos technoish
	
	//------------ Trozo de muñeco/oso cabron
	glColor4f(1,1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if((this->_row%8)==0) {
		pulso=1;
		fxradialblur->setTimes(16);
	} else {
		fxradialblur->setTimes(10);
	}
	if(pulso>0) {
		pulso=pulso - pulso*pulso*0.9;
	}
	y_desp=pulso;
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0,-0.7,0);
	glBindTexture(GL_TEXTURE_2D, this->text_oso.texID);
	float lado=0.7;
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0,0); 
		glVertex3f(0,0+y_desp,z_depth);
		
		glTexCoord2f(1, 0);
		glVertex3f(lado,0+y_desp, z_depth);

		glTexCoord2f(1,1);
		glVertex3f(lado,lado+y_desp,  z_depth);

		glTexCoord2f(0,1);
		glVertex3f(0,lado+y_desp,z_depth);
	glEnd();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	y_desp=-y_desp;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//z_depth-=0.1;
	glTranslatef(-0.5,.1,0);
	glBindTexture(GL_TEXTURE_2D, this->text_k.texID);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0,0); 
		glVertex3f(0,0+y_desp,z_depth);
		
		glTexCoord2f(1, 0);
		glVertex3f(0.35,0+y_desp, z_depth);

		glTexCoord2f(1,1);
		glVertex3f(0.35,0.5+y_desp,  z_depth);

		glTexCoord2f(0,1);
		glVertex3f(0,0.35+y_desp,z_depth);

		//glVertex3f(0,0,0);

	glEnd();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	// fin osocabron

	
	miDemo->quitaOrtopedico();
	glDisable(GL_SMOOTH);	
	glDisable(GL_BLEND);

	// fade
	float alfa;
	if((_row<=16)&&(_pattern==5)) {
		alfa=float(16-_row)/16.0;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfa);
		fxfade->perFrame(_time);
		glEnable(GL_DEPTH_TEST);
	}
	else if((_row>=112)&&(_pattern==6)) {
		alfa=float(_row%16)/16.0;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfa);
		fxfade->perFrame(_time);
		glEnable(GL_DEPTH_TEST);
	} else if((_row%8)==0){
		alfa=0.15;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfa);
		fxfade->perFrame(_time);
		glEnable(GL_DEPTH_TEST);
	}

	
}

void FXmanga::init(void) {
	// asignar recursos y tal, cargar ficheros, blabla

	// Cargo las texturas
	LoadTGA(&text_oso,"./data/killamala2.tga");
	LoadTGA(&text_k,"./data/k.tga");

	// setup de la camara
	cam.SetPos(10,5,10);
	
	cam.SetLook(0,0,0.8);
	cam.setFar(1,100);

	// quadricas de la muerte
	this->quad=gluNewQuadric();
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);
}

void FXmanga::start(void) {
	glClearColor(1.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_SMOOTH);
	// poner los parametros del radialblur
	fxradialblur->setInc(0.02f);
	fxradialblur->setTimes(10);
	fxradialblur->setView(miDemo->getWidth(),miDemo->getHeight());
	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

void FXmanga::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	gluDeleteQuadric(this->quad);
}

FXmanga::FXmanga() {
}

FXmanga::~FXmanga() {
}
