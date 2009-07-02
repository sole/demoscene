#include "FXtituti.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXtituti::perFrame(float time) {
	float t = time * 0.001f;
	float fftbass=miMusic.getFFTBass();

	glClearColor(0.2,0.6,0.9,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	int row=miMusic.getRow();

	if(row<8) {
		cam.SetPos(0,0,-5);
	} else if ((row>8)&&(row<16)) {
		cam.SetPos(0,-5,0);
	} else if ((row>16)&&(row<24)) {
		cam.SetPos(-5,0,0);
	} else if ((row>24)) {
		cam.SetPos(-5,-5,-5);
	}
	cam.toOGL();
	cam.SetLook(0,-1,-0.1);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	cam.SetPos(5,5+3*cos(t),5);
	
	float xt=2; // xtremo
	float z_depth=float(-0.0121);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glPointSize(10);
	glColor3f(1,1,1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	int numCub=10;
	float radio=2;
	float s;
	int angint=360.0/numCub;
	for(int j=0;j<numCub;j++) {
		if(j%2==0) {			
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		} else {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		}
		glLoadIdentity();
		glColor3f(1,1,1);
		glTranslatef(radio*sin(angint*j+t),radio*cos(angint*j+t),radio*sin(t+j));
		unCubo.setWire(1);
		unCubo.perFrame(t);
		glColor3f(1,1,1);
		s=3+cos(t);
		glScalef(s,s,s);
		glRotatef(t+j,1,1,1);
		unCubo.setWire(0);
		unCubo.perFrame(t);
	}
	

	glDisable(GL_BLEND);
		
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	for(int i=1;i<7;i++) {
		fxmotionblur->perFrame(t);		
	}
	fxmotionblur->postprepareFrame();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	xt=1+fftbass*0.5;//10-0.05*_row; // xtremos
	miDemo->ponOrtopedico(4,4);
	float al=0.5+0.5*sin(t*4),dp=0,dpy=-0.2; // desplazamiento
	glColor4f(1,1,1,al);
	glBindTexture(GL_TEXTURE_2D, this->layerTitle.texID);
	
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0); 
	glVertex3f(-xt*2+dp,-xt+dpy,z_depth);
	
	glTexCoord2f(1,0);
	glVertex3f(xt*2+dp,-xt+dpy, z_depth);

	glTexCoord2f(1,1);
	glVertex3f(xt*2+dp,xt+dpy,  z_depth);

	glTexCoord2f(0,1);
	glVertex3f(-xt*2+dp,xt+dpy,z_depth);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	miDemo->quitaOrtopedico();

}

void FXtituti::init(void) {
	
	unCubo.setLength(0.65);
	unCubo.update();
	unCubo.setPolyColorR(0);
	unCubo.setPolyColorG(0.7);
	unaEsfera.setLength(3);
	unaEsfera.setIterations(1);
	unaEsfera.update();
	LoadTGA(&layerTitle,"./data/cosa02b.tga");

}


void FXtituti::start(void) {
	cam.SetPos(5,5,5);
	glLineWidth(1.0);
}

void FXtituti::stop(void) {
	
}

void FXtituti::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	this->unCubo.deInit();
	this->unaEsfera.deInit();	
}

FXtituti::FXtituti() {
}

FXtituti::~FXtituti() {
}
