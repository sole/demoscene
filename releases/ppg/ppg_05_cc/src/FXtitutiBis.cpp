#include "FXtitutiBis.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXtitutiBis::perFrame(float time) {
	float t = time * 0.001f;
	glClearColor(0.0,0.2,0.4,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//cam.SetPos(5+3*sin(t),5+3*cos(t),5);
	int row=miMusic.getRow();

	if(row<=8) {
		cam.SetPos(0,8+3*cos(t),6+2*sin(t));
	} else if ((row>8)&&(row<=16)) {
		cam.SetPos(5+3*cos(t),0,3+2*sin(t));
	} else if ((row>16)&&(row<=24)) {
		cam.SetPos(5+3*cos(t),3+2*sin(t),0);
	} else if ((row>24)) {
		cam.SetPos(5+3*cos(t),3+2*sin(t),3+2*sin(t));
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
	glRotatef(t,1,0,0);
	glPushMatrix();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	glPointSize(4);
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
				s=1+cos(t+j+k+m);
				glLoadIdentity();
				glColor3f(0.5+0.5*sin(angint*j+t),0.5+0.5*cos(angint*k+t),0.5+0.25*(cos(m+t)+cos(5+m*4+t*5)));
				glTranslatef(j,k,m);
				glScalef(s,s,s);
				unCubo.perFrame(t);
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

	for(int i=1;i<3;i++) {
		fxmotionblur->perFrame(t);		
	}
	fxmotionblur->postprepareFrame();


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	xt=2 ;//10-0.05*_row; // xtremos
	miDemo->ponOrtopedico(2,4);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0,-1,0);

	fxGreets.perFrame(t);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	miDemo->quitaOrtopedico();

	if(row==24) {
		fxGreets.setMode(DISSAPPEAR);
	}
}

void FXtitutiBis::init(void) {
	
	unCubo.setLength(0.3);
	unCubo.update();
	unaEsfera.setLength(3);
	unaEsfera.setIterations(1);
	unaEsfera.update();
	LoadTGA(&layerGreets,"./data/cosa03.tga");

	fxGreets.setTexture("./data/cosa03c.tga");
	fxGreets.init();
	fxGreets.setLightingTime(0.00001);
}

void FXtitutiBis::squarePlane(TextureImage *_texture) {
	float xt=1,dp=0,dpy=0,extraancho=0,z_depth=0.01f;
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, _texture->texID);
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0); 
	glVertex3f(-xt*2+dp,-xt+dpy,z_depth);
	
	glTexCoord2f(1,0);//x
	glVertex3f(xt*2+dp+extraancho,-xt+dpy, z_depth);

	glTexCoord2f(1,1);//x
	glVertex3f(xt*2+dp+extraancho,xt+dpy,  z_depth);

	glTexCoord2f(0,1);
	glVertex3f(-xt*2+dp,xt+dpy,z_depth);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void FXtitutiBis::start(void) {
	cam.SetPos(5,5,5);
	glLineWidth(1.0);
}

void FXtitutiBis::stop(void) {
	
}

void FXtitutiBis::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	this->unCubo.deInit();
	this->unaEsfera.deInit();	
}

FXtitutiBis::FXtitutiBis() {
}

FXtitutiBis::~FXtitutiBis() {
}
