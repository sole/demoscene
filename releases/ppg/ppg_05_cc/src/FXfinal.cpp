#include "FXfinal.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXfinal::perFrame(float time) {
	time *= 0.001f;
	float cc=time*0.05; // constante de color, lo usare pa saturar
	int pattern=miMusic.getPattern();
	int row=miMusic.getRow();
	float fftbass=miMusic.getFFTBass();

	if(pattern>12) {
		float menos=float(row)/32.0;
		glClearColor(0.0,0.2-menos,0.4-menos,1);
	} else {
		glClearColor(0.0,0.2,0.4,1);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	float t=time*0.5;
	if(row<=8) {
		cam.SetPos(0,8+3*cos(t),6+2*sin(t));
	} else if ((row>8)&&(row<=16)) {
		cam.SetPos(5+3*cos(t),0,3+2*sin(t));
	} else if ((row>16)&&(row<=24)) {
		cam.SetPos(5+3*cos(t),3+2*sin(t),0);
	} else if ((row>24)) {
		cam.SetPos(5+3*cos(t),3+2*sin(t),3+2*sin(t));
	}

	if(miMusic.getPattern()>12) {
		if(row<=8) {
			glPointSize(3);
		} else if ((row>8)&&(row<=16)) {
			glPointSize(2);
		} else if ((row>16)&&(row<=24)) {
			glPointSize(1);
		} else if ((row>24)) {
			glPointSize(0.5);
		}
	} else {
		glPointSize(4);
	}
	cam.toOGL();
	cam.SetLook(8,7,5);
	cam.setFov(60+40*sin(t));

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	
	float xt=2; // xtremo
	float z_depth=float(-0.0121);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(time,1,0,0);
	glPushMatrix();
	

	glColor3f(1,1,1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	


	unCubo.setPolys(0);
	unCubo.setNorm(0);
	unCubo.setWire(0);
	int numCub=15;
	float radio=2;
	float s;
	
	int angint=360.0/numCub;
	for(int j=0;j<numCub;j++) {
		for(int k=0;k<numCub;k++) {
			for(int m=0;m<numCub;m++) {
				s=1+cos(time+j+k+m);
				glLoadIdentity();
				glColor3f(0.5+0.5*sin(angint*j+time)+cc,0.5+0.5*cos(angint*k+time)+cc,0.5+0.25*(cos(m+time)+cos(5+m*4+time*5))+cc);

				glTranslatef(j,k,m);
				glScalef(s,s,s);
				unCubo.perFrame(time);
			}
		}
	}
	
	glDisable(GL_BLEND);
		
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	// textos 
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
	

	for(int i=1;i<3;i++) {
		fxmotionblur->perFrame(time);		
	}
	fxmotionblur->postprepareFrame();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	xt=1;//10-0.05*_row; // xtremos
	miDemo->ponOrtopedico(5,4);
	float al=pulso*0.6+fftbass*16,dp=0,dpy=0;//1.5*sin((_row+_pattern)*0.01); // desplazamiento
	float correccion=pulso;

	if(miMusic.getPattern()==13) {
		
	}
	if(miMusic.getPattern()<13) {
		glColor4f(1,1,1,al);
		
		glBindTexture(GL_TEXTURE_2D, this->layerFinal01.texID);
	} else  {
		glColor4f(1,1,1,al);
		
		glBindTexture(GL_TEXTURE_2D, this->layerFinal02.texID);
	}
	xt=2;
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0); 
	glVertex3f(-xt+dp,-xt+dpy,z_depth);
	
	glTexCoord2f(1,0);
	glVertex3f(xt+dp,-xt+dpy, z_depth);

	glTexCoord2f(1,1);
	glVertex3f(xt+dp,xt+dpy,  z_depth);

	glTexCoord2f(0,1);
	glVertex3f(-xt+dp,xt+dpy,z_depth);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	miDemo->quitaOrtopedico();
}

void FXfinal::init(void) {
	
	unCubo.setLength(0.3);
	unCubo.update();
	unaEsfera.setLength(3);
	unaEsfera.setIterations(1);
	unaEsfera.update();
	LoadTGA(&layerFinal01,"./data/cosa04d1.tga");
	LoadTGA(&layerFinal02,"./data/cosa05b1.tga");
}


void FXfinal::start(void) {
	cam.SetPos(5,5,5);
	glLineWidth(1.0);
}

void FXfinal::stop(void) {
	
}

void FXfinal::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	this->unCubo.deInit();
	this->unaEsfera.deInit();	
}

FXfinal::FXfinal() {
}

FXfinal::~FXfinal() {
}
