#include "FXscCintas2.h"
#include "Events.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXscCintas2::perFrame(float time) {
	static float doFlash=0;
	static int pulse=0;

	glClearColor(0,0,0.27,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	float a=fabs(0.9-fmod(miMusic.getFFTBass(),1));
	
	if(time > 199.912)
		planeText2.perFrame(time);

	static float camx=0,camy=0,camz=0;

	cam.SetPos(camx,camy,camz);
	cam.SetLook(0.1,0.1,-1);
	cam.toOGL();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();

	float c=a*0.9;
	glColor4f(c,c,c,a);

	glPushMatrix();
	float s=0.75;
	glScalef(s,s,s);

	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	if(time < 198.987)
		tapeList[0].perFrame(time);
	if(time < 198.707)
		tapeList[1].perFrame(time);
	if(time < 198.521)
		tapeList[2].perFrame(time);

	glDepthFunc(GL_LESS);
	glPopAttrib();
	glPopMatrix();

	static float t0=0, t1=0;
	if(time-t0>0.03) {
		t0=time;
		camx+=0.2;
		camy+=0.2;
		cam.setFov(cam.getFov()+0.02);
		if(doFlash>0)
			doFlash-=0.05;
	}

	glLoadIdentity();

	static unsigned int kk=0;
	static unsigned int startDrawingCurve = 1;
	if(time-t1>0.03) {
		int rpulse;

		pulse-= 1;
		if(pulse>0)
			kk+=pulse;
		if(0>pulse)
			rpulse=0;
		else
			rpulse=pulse;
		
		t1=time;
		
		for(unsigned int i=0; i<FXSCCINTAS_NUM; i++){
			tapeList[i].setStartDrawingCurve(startDrawingCurve);
			tapeList[i].setNumDrawParts(tapeList[i].getNumDrawParts()+1+rpulse);
		}

	}
	
	static float tdraw=0;
	if(time-tdraw>0.01) {
		tdraw = time;
		startDrawingCurve+=2;
	}
	
	static int counter = 0;
	if(checkEventFlag(EVENT_TYPE_SNARE))
	{
		doFlash = 0.2f;
		pulse = 15;
		counter++;
		
		float max = 150;
		
		if(counter%2 == 0)
		{
			camx = max * cos(0.1f * time);
		}
		else
		{
			camy = max * sin(0.1f * time);
		}
		resetEventFlag(EVENT_TYPE_SNARE);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	

	fxfade->setBlendFunc(GL_SRC_ALPHA,GL_ONE);
	fxfade->setFadeColor(0.15,0.15,0.15,0.25);
	fxfade->perFrame(time);
	
	if(doFlash>0) {
		fxfade->setFadeColor(1,1,1,doFlash);
		fxfade->setBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		fxfade->perFrame(time);
	}

	// Al principio se hace fade de blanco, y al final de la escena se hace fade a negro...
	static float t_start = 153.3;
	static float t_end = 206;
	static float fade_time = 2;
	
	if(time >= t_start && time < (t_start + fade_time))
	{
		fxfade->setFadeColor(1,1,1, map(time, t_start, t_start+fade_time, 1.0f, 0.0f));
		fxfade->perFrame(time);
	}
	else if(time >= t_end - fade_time)
	{
		fxfade->setBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		fxfade->setFadeColor(0,0,0, map(time, t_end - fade_time, t_end, 0.0f, 1.0f));
		fxfade->perFrame(time);
	}

	planeText1.perFrame(time);
}

void FXscCintas2::init(void) {
	unsigned int i;
	unsigned int cPrec=200;//250
	unsigned int numV=1200;
	float rz=500;
	

	fxfade->setFadeColor(1,1,1,1);
	fxfade->setBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	cam.setFar(1,10000);
	cam.setFov(100);
	
	planeText1.setTextureName("data/sccintas2/greetings.png");
	planeText1.setBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	planeText1.setStartTime(168.172);
	planeText1.setSustain(10);
	planeText1.setRelease(5);
	planeText1.setAttack(2);
	planeText1.init();
	planeText1.setPlaneColor(1,1,1,1);
	planeText1.setFinalPlaneColor(1,1,1,0);
	
	planeText2.setTextureName("data/sccintas2/xplsv.png");
	planeText2.init();	

	for(i=0; i<FXSCCINTAS_NUM; i++){
		tapeList[i].setBlendFunc(GL_SRC_ALPHA, GL_ONE);
		tapeList[i].setNumVertex(numV);
		tapeList[i].setCurvePrec(cPrec);
		tapeList[i].setNumDrawParts(i*3+300);
		tapeList[i].setHeight(0);
		tapeList[i].setWidth(8);
		tapeList[i].init();
	}

	srand(1000);
	// inicializo la primera cinta
	i=0;
	tapeList[i].setPointAt(0,-1000,-1000,1000, 0);
	for(unsigned j=1; j<numV; j++){
		tapeList[i].setPointAt(j, -rz/2 + getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz);
	}
		
	// y las otras son copias de la primera pero un poco desplazadas...
	Point pt;
	for(i=1; i<FXSCCINTAS_NUM; i++){
		for(unsigned j=0; j<numV; j++){
			pt=tapeList[0].getPointAt(j);
			pt.x+=10*i;
			pt.z+=10*i;
			pt.y+=0.5*i;
			tapeList[i].setPointAt(j, pt.x,pt.y,pt.z,pt.w);
		}
	}

	tapeList[0].setPlaneColor(0,0,0,1);
	tapeList[2].setPlaneColor(0.82,0,0.30,1);

}


void FXscCintas2::start(void) {
	cam.SetPos(5,5,5);
	glLineWidth(1.0);
	glEnable(GL_SMOOTH);

	fxfade->setFadeColor(1,1,1,0.5);
	fxfade->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void FXscCintas2::stop(void) {
	
}

void FXscCintas2::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	tape.deInit();
	
}

FXscCintas2::FXscCintas2() {
	this->numCintas=FXSCCINTAS_NUM;
}

FXscCintas2::~FXscCintas2() {
}
