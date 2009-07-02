#include "FXdummy.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXdummy::perFrame(float time)
{
	float fftbass=miMusic.getFFTBass()*20;

	glClearColor(0.05,0.55,0.55,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	cam.toOGL();
	cam.SetPos(0,0,-3);
	cam.SetLook(0,0,-0.1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glRotatef(time*0.01,1,1,1);

	float xt=2; // xtremo
	float z_depth=float(-0.0121);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glPointSize(10);
	glColor3f(1,1,1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	unaEsfera.perFrame(time);
	unCubo.perFrame(time);
	glDisable(GL_BLEND);
		
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	for(int i=1;i<7;i++)
	{
		fxmotionblur->perFrame(time);
	}
	fxmotionblur->postprepareFrame();

	// textos de bienvenida XD
	int row=miMusic.getRow();
	float valy;
	static float pulso;
	if((row==0) || (row==1) || (row==8) || (row==9) || (row==16) || (row==17) || (row==24) || (row==25)) {
		valy=1;
		
	} else {
		valy=0;
	}
	if(valy>0) {
		pulso=valy;
	} else {
		if(pulso>0) {
			pulso=pulso-pulso*pulso*0.05;
		}
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	xt=1;//10-0.05*_row; // xtremos
	miDemo->ponOrtopedico(4,4);
	float al=pulso,dp=0,dpy=-1;//1.5*sin((_row+_pattern)*0.01); // desplazamiento
	glColor4f(1,1,1,al);
	glBindTexture(GL_TEXTURE_2D, this->layerWelcome.texID);
	if(miMusic.getPattern()==1) {
		glBindTexture(GL_TEXTURE_2D, this->layerWelcome.texID);
	} else if(miMusic.getPattern()==3) {
		glBindTexture(GL_TEXTURE_2D, this->layerTitle.texID);
	}

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

	glColor4f(1,1,1,fftbass * 0.5);
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, this->layerMierda.texID);
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
	glDisable(GL_BLEND);
	miDemo->quitaOrtopedico();
}

void FXdummy::init(void) {
		
	unCubo.setLength(4);
	unCubo.setWire(1);
	unCubo.setPolys(1);
	unCubo.update();
	unaEsfera.setLength(3);
	unaEsfera.setIterations(5);
	unaEsfera.update();

	LoadTGA(&layerWelcome,"./data/cosa00d.tga");
	LoadTGA(&layerTitle,"./data/cosa00d2.tga");
	LoadTGA(&layerMierda,"./data/cosa00e01.tga");
}


void FXdummy::start(void) {
	cam.SetPos(5,5,5);
	glLineWidth(1.0);
}

void FXdummy::stop(void) {
	
}

void FXdummy::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	this->unCubo.deInit();
	this->unaEsfera.deInit();	
}

FXdummy::FXdummy() {
}

FXdummy::~FXdummy() {
}
