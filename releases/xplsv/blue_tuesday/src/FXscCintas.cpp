#include "FXscCintas.h"
#include "Events.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXscCintas::perFrame(float time)
{
	static float doFlash=0;
	static int effectStarted=-1;
	static unsigned int pulse=0;
	
	if(effectStarted==-1) {
		effectStarted=1;
		this->startTime=time;
	}

	glClearColor(0,0,0.27,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	float a=fabs(0.9-fmod(miMusic.getFFTBass(),1));
	float d=500;
	
	static float camx,camy,camz;

	cam.SetPos(camx,camy,camz);
	cam.SetLook(0.1,0.1,-1);
	cam.toOGL();
	glMatrixMode(GL_PROJECTION);
	glRotatef(time*2,0,0,1);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();

	float c=a*0.9;
	glColor4f(c,c,c,a);

	glPushMatrix();
	float s=2;
	glScalef(s,s,s);

	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	float fadetime = 25;
	float elapsedTime = time - this->startTime;
	float tapeWidth = 8;
	
	// Tape 0
	if( (elapsedTime>0) && (elapsedTime<fadetime) )
		tapeList[0].setWidth(elapsedTime/fadetime*tapeWidth);
	else 
		tapeList[0].setWidth(tapeWidth);
	// Tape 1
	if( (elapsedTime>7.5) && (elapsedTime<7.5+fadetime) )
		tapeList[1].setWidth((elapsedTime-7.5)/fadetime*tapeWidth);
	else 
		tapeList[1].setWidth(tapeWidth);
	// Tape 2
	if( (elapsedTime>15) && (elapsedTime<15+fadetime) )
		tapeList[2].setWidth((elapsedTime-15)/fadetime*tapeWidth);
	else 
		tapeList[2].setWidth(tapeWidth);
	
	
	tapeList[0].perFrame(time);
	if((time-this->startTime)>7.5)
		tapeList[1].perFrame(time);
	if((time-this->startTime)>15)
		tapeList[2].perFrame(time);


	glDisable(GL_DEPTH_TEST);
	glPopAttrib();

	glPopMatrix();

	static float t0=0, t1=0, prevBass=0;

	if(time-t0>0.03) {
		
		t0=time;
		camx+=0.2;
		camy+=0.2;
		if(doFlash>0)
			doFlash-=0.05;
	}

	glLoadIdentity();

	static unsigned int kk=0;
	if((time-t1>0.02))
	{
		kk++;

		t1=time;

		tapeList[0].setNumDrawParts(tapeList[0].getNumDrawParts()+1);
		if((time-this->startTime)>7.5)
			tapeList[1].setNumDrawParts(tapeList[1].getNumDrawParts()+1);
		if((time-this->startTime)>15)
			tapeList[2].setNumDrawParts(tapeList[2].getNumDrawParts()+1);

	}

	if(checkEventFlag(EVENT_TYPE_SNARE))
	{
		doFlash = 0.2f;
		pulse = 0.0f;
		resetEventFlag(EVENT_TYPE_SNARE);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	
	if(doFlash>0)
	{
		fxfade->setFadeColor(1,1,1,doFlash);
		fxfade->setBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		fxfade->perFrame(time);
	}

	float eTime=time-this->startTime;
	char t[255];
	
		
	// Al final de la escena se hace fade a blanco...
	static float t_end = 97;
	static float fade_time = 2;
	
	if(time >= t_end - fade_time)
	{
		fxfade->setFadeColor(1,1,1, map(time, t_end - fade_time, t_end, 0.0f, 1.0f));
		fxfade->perFrame(time);
	}
}

void FXscCintas::init(void) {
	unsigned int i;

	float cPrec=70;

	fxfade->setFadeColor(1,1,1,1);
	fxfade->setBlendFunc(GL_DST_ALPHA, GL_SRC_ALPHA);
	cam.setFar(1,10000);
	cam.setFov(100);
	
	spiral.init();
	spiral.setBorderColor(0,0,0,1);
	spiral.setPlaneColor(0.8,0,1,0.7);

	unsigned int numV=120;
	float rz=300;

	rz=400;
	float ox, oy, oz; // origin for each tape.. something like its gravity center..
	for(i=0; i<FXSCCINTAS_NUM; i++)
	{
		tapeList[i].setBlendFunc(GL_SRC_ALPHA, GL_ONE/*_MINUS_SRC_ALPHA*/);
		tapeList[i].setNumVertex(150);
		tapeList[i].setCurvePrec(cPrec);
		tapeList[i].setNumDrawParts(i+350);
		tapeList[i].setHeight(0);
		tapeList[i].setWidth(8);
		tapeList[i].init();
		if(i==0)
		{
			ox = 0;
			oy = 0;
			oz = 0;
		} else if(i==1) {
			ox = -200;
			oy = 200;
			oz = -200;
		} else {
			ox = 200;
			oy = -200;
			oz = 200;
		}
		for(unsigned j=0; j<100; j++){
			tapeList[i].setPointAt(j, -rz/2 + getRand()*rz + ox, -rz/2 +getRand()*rz + oy, -rz/2 +getRand()*rz + oz, -rz/2 +getRand()*rz);
		}
	}
	tapeList[0].setPlaneColor(0,0,0,1);
	tapeList[2].setPlaneColor(0.82,0,0.30,1);

}


void FXscCintas::start(void)
{
	cam.SetPos(5,5,5);
	glLineWidth(1.0);
	glEnable(GL_SMOOTH);
	
	fxfade->setFadeColor(1,1,1,0.5);
	fxfade->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->startTime=-1;
}

void FXscCintas::stop(void) {}

void FXscCintas::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	for(int i=0; i<FXSCCINTAS_NUM; i++)
	{
		tapeList[i].deInit();
	}
	
}

FXscCintas::FXscCintas() {
	this->numCintas=FXSCCINTAS_NUM;
	this->startTime=-1;
}

FXscCintas::~FXscCintas() {
}
