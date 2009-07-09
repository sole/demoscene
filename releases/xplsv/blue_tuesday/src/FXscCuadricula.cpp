#include "FXscCuadricula.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXscCuadricula::perFrame(float time) {
	static float doFlash=0;
	GLboolean currentMask;

	glClearColor(0,0,0.27,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	float a=fabs(0.9-fmod(miMusic.getFFTBass(),1));

	float d=500;
	
	static float camx,camy,camz, ang=0, angPulse=0;
	float maxAngPulse=2;

	camx=200*sin(ang);
	camy=0;
	camz=200*cos(ang);
	cam.SetPos(200,-200,200);
	cam.SetLook(0.1,0.1,-0.1);
	cam.toOGL();
	glMatrixMode(GL_PROJECTION);
	glRotatef(time*15,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	

	float c=a*0.9;
	glColor4f(c,c,c,a);

	glPushMatrix();
	float s=2;
	glScalef(s,s,s);
	
	glMatrixMode(GL_MODELVIEW);

	
	glColor4f(0,0,0.0,1);
	
	glPopMatrix();
	float lado=10;

	
	glPushAttrib(GL_DEPTH_WRITEMASK);
	glDisable(GL_DEPTH_WRITEMASK);
	glEnable(GL_DEPTH_TEST);
	
	static float t0=0, t1=0, prevBass=0;
	float bass;
	if(time-t0>0.03) {
		bass=miMusic.getFFTBass()*10;
		bass*=bass;
		spiral.pushPoint(prevBass*0.5 + 0.5*bass );
		prevBass=bass;
		t0=time;
		if(doFlash>0)
			doFlash-=0.05;
		if(angPulse>0)
			angPulse-=0.7*angPulse*angPulse;
		ang+=0.01;
		
	}


	glLoadIdentity();
	char str[255];
	int maxParts=800;
	unsigned int defParts;
	static unsigned int kk=0;
	unsigned int i;
	if(time-t1>0.02297) {
		kk++;
		t1=time;
		if(kk>maxParts) {
			defParts=0;
		} else {
			defParts=maxParts- kk;
		}
		tape.setNumDrawParts(defParts);
		tape3.setNumDrawParts(defParts);			

		for(i=0; i<FXSCCUADRICULA_NUM; i++)
		{
			tapeList[i].setNumDrawParts(defParts);	
		}	
	}
	
	for(i=0; i<FXSCCUADRICULA_NUM; i++){
		tapeList[i].perFrame(time);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

	tape.perFrame(time);
	tape3.perFrame(time);
	
	glDisable(GL_BLEND);

	glPopAttrib();
	
	if(checkEventFlag(EVENT_TYPE_SNARE))
	{
		doFlash = 0.2f;
		angPulse = 2.0f;
		resetEventFlag(EVENT_TYPE_SNARE);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	

	if(doFlash>0) {
		fxfade->setFadeColor(1,1,1,doFlash);
		fxfade->perFrame(time);
	}
	
	// Al principio se hace fade de blanco, y al final de la escena se hace fade a blanco...
	static float t_start = 132;
	static float t_end = 153.3;
	static float fade_time = 2;
	
	if(time >= t_start && time < (t_start + fade_time))
	{
		fxfade->setFadeColor(1,1,1, map(time, t_start, t_start+fade_time, 1.0f, 0.0f));
		fxfade->perFrame(time);
	}
	else if(time >= t_end - fade_time)
	{
		fxfade->setFadeColor(1,1,1, map(time, t_end - fade_time, t_end, 0.0f, 1.0f));
		fxfade->perFrame(time);
	}
	
	planeText1.perFrame(time);
	
}

void FXscCuadricula::init(void) {
	unsigned int i;
	fxfade->setFadeColor(1,1,1,1);
	fxfade->setBlendFunc(GL_DST_ALPHA, GL_SRC_ALPHA);
	
	cam.setFar(1,100000);
	cam.setFov(100);
	cam.SetPos(200,0,200);

	planeText1.setTextureName("data/sccuadricula/lyrics01.png");
	planeText1.setBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	planeText1.setStartTime(132);
	planeText1.setSustain(9);
	planeText1.setRelease(8);
	planeText1.setAttack(2);
	planeText1.init();
	planeText1.setPlaneColor(1,1,1,1);

	spiral.init();
	spiral.setWidth(6);
	spiral.setBorderColor(0,0,0,1);
	spiral.setPlaneColor(0.8,0,1,0.7);

	unsigned int numV=60;
	float rz=1000;
	tape.setNumVertex(numV);
	tape.setCurvePrec(100);
	tape.setNumDrawParts(0);
	tape.setHeight(0);
	tape.setWidth(10);
	tape.setPlaneColor(1,1,1,1);

	tape.setTextureName("data/sccuadricula/dotted.png");
	tape.init();
	for( i=0; i<numV; i++){
		tape.setPointAt(i, -rz/2 + getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz);
	}

	// La negra!! (hum, q ahora es rosa XD)
	tape3.setNumVertex(numV);
	tape3.setCurvePrec(100);
	tape3.setNumDrawParts(0);
	tape3.setHeight(0);
	tape3.setWidth(10);
	tape3.setPlaneColor(1,1,1,1);

	tape3.setTextureName("data/sccuadricula/dottedblack.png");
	tape3.init();
	for( i=0; i<numV; i++){
		tape3.setPointAt(i, -rz/2 + getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz);
	}


	// Estas son las cintas adicionales y mas finas
	rz=400;
	unsigned int finasNumV=numV;
	for(i=0; i<FXSCCUADRICULA_NUM; i++){
		tapeList[i].setNumVertex(finasNumV);
		tapeList[i].setCurvePrec(50);
		tapeList[i].setNumDrawParts(0);
		tapeList[i].setHeight(0);
		tapeList[i].setWidth(5);
		tapeList[i].setPlaneColor(0,0,0,1);
		tapeList[i].init();
		for(unsigned int j=0; j<finasNumV; j++){
			tapeList[i].setPointAt(j, -rz/2 + getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz);
		}
				
	}


	float ancho=600, alto=600, largo=600, xinc, yinc, zinc;
	float origenx=-ancho;
	float origeny=-alto;
	float origenz=-largo;
	xinc=2*ancho/float(FXSCCUADRICULA_NUMPLUS);
	yinc=2*alto/float(FXSCCUADRICULA_NUMPLUS);
	zinc=2*largo/float(FXSCCUADRICULA_NUMPLUS);
	float lado=5;

	
	int j,k,index=0;
	for(i=0;i<FXSCCUADRICULA_NUMPLUS;i++) {
		for(j=0;j<FXSCCUADRICULA_NUMPLUS;j++) {
			for(k=0;k<FXSCCUADRICULA_NUMPLUS;k++) {
				this->pointList[index].x=origenx+xinc*i;
				this->pointList[index].y=origeny+yinc*j;
				this->pointList[index].z=origenz+zinc*k;
				index++;
			}
		}
	}

}


void FXscCuadricula::start(void) {
	
	glLineWidth(1.0);
	glEnable(GL_SMOOTH);
	
	fxtvdistort->setClearColor(1,1,1,0.5);
	fxtvdistort->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	fxfade->setFadeColor(1,1,1,0.5);
	fxfade->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glHint(GL_LINE_SMOOTH_HINT , GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT , GL_NICEST);

}

void FXscCuadricula::stop(void) {
	
}

void FXscCuadricula::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	tape.deInit();
	tape3.deInit();
	
}

FXscCuadricula::FXscCuadricula() {
	this->numCintas=FXSCCUADRICULA_NUM;
}

FXscCuadricula::~FXscCuadricula() {
}
