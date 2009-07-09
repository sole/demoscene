#include "FXscIntro.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXscIntro::perFrame(float time) {

	static const float spiralStart=0 /*17*/;
	float a;
	static float t0=0, prevBass=0;
	float bass=0;
	bass=miMusic.getFFTBass()*300;
	
	if(time-t0>0.019) 
	{
		if(time>spiralStart)
			spiral.pushPoint((0.45*bass + 0.65*prevBass));
		t0=time;
		prevBass=bass;
	}
	
	glClearColor(0,0,0.27*(time/69.0),0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	a=fabs(0.9-fmod(miMusic.getFFTBass(),10));
	
	fxtvdistort->prepareFrame();


	planeText1.perFrame(time);
	planeText2.perFrame(time);
	planeText3.perFrame(time);
	planeText4.perFrame(time);
	
	fxtvdistort->setParam(TVD_PARAM_V,bass);
	fxtvdistort->setParam(TVD_PARAM_POWER,a);
	fxtvdistort->postprepareFrame();
	glClearColor(0,0,0.27*(time/67.0),0);

	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	cam.SetLook(0,0,0.1);

	float d=200;
	cam.SetPos(d,90+time,d+50*sin(time/10.0));
	
	cam.toOGL();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();

	float c=a*0.9;
	glColor4f(c,c,c,a);

	glRotatef(time*16,0,1,0);
	

	float s=0.5+ time*0.004;
	glScalef(s,s,s);

	glEnable(GL_DEPTH_TEST);

	if(time>spiralStart)
	{
		spiral.perFrame(time);
	}



	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	fxtvdistort->perFrame(time);


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glPopAttrib();
	
}

void FXscIntro::init(void) {
	
	fxfade->setFadeColor(1,1,1,1);
	fxfade->setBlendFunc(GL_ONE, GL_ONE);
	
	cam.setFar(1,10000);
	
	planeText1.setTextureName("data/scintro/title01.png");
	planeText1.setFinalPlaneColor(1,1,1,0);
	planeText1.setStartTime(0);
	planeText1.setSustain(11);
	planeText1.setRelease(3);
	planeText1.setAttack(6);
	planeText1.init();

	planeText2.setTextureName("data/scintro/sole01.png");
	planeText2.setFinalPlaneColor(1,1,1,0);
	planeText2.setSustain(11);
	planeText2.setRelease(3);
	planeText2.setAttack(3);
	planeText2.setStartTime(21);
	planeText2.init();

	planeText3.setTextureName("data/scintro/trace01.png");
	planeText3.setFinalPlaneColor(1,1,1,0);
	planeText3.setSustain(11);
	planeText3.setAttack(3);
	planeText3.setRelease(3);
	planeText3.setStartTime(39);	
	planeText3.init();

	planeText4.setTextureName("data/scintro/bauri01.png");
	planeText4.setFinalPlaneColor(1,1,1,0);
	planeText4.setSustain(11);
	planeText4.setAttack(2);
	planeText4.setRelease(3);
	planeText4.setStartTime(57);
	planeText4.init();

	planeText1.setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	planeText2.setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	planeText3.setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	planeText4.setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	spiral.init();
	spiral.setBorderColor(0,0,0,1);
	spiral.setPlaneColor(0,0,0,1);
	spiral.setWidth(15);
	spiral.setGravity(0,-0.006,0,0);
}


void FXscIntro::start(void)
{
	cam.SetPos(5,5,5);
	glLineWidth(1.0);
	glEnable(GL_SMOOTH);
	
	fxtvdistort->setClearColor(1,1,1,1);
	fxtvdistort->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void FXscIntro::stop(void) {
	
}

void FXscIntro::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	
}

FXscIntro::FXscIntro() {
}

FXscIntro::~FXscIntro() {
}
