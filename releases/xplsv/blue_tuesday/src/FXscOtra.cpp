#include "FXscOtra.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXscOtra::perFrame(float time) {
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

	
	CPoint tapePos, tapeLook, tapeUp;
	Point pTapePos, pTapeLook;
	pTapePos = tape.getLastPoint();
	pTapeLook = tape.getLastLook();
	tapePos.x = pTapePos.x;
	tapePos.y = pTapePos.y;
	tapePos.z = pTapePos.z;
	tapeLook.x = pTapeLook.x;
	tapeLook.y = pTapeLook.y;
	tapeLook.z = pTapeLook.z;
	tapeUp = tapePos ^ tapeLook;
	
	CPoint camPos;
	CPoint pDif;
	pDif.x = 100;
	pDif.y = 100;
	pDif.z = 100;
	
	camPos = tapeUp.normalize()*(60+40*sin(time));
	cam.SetPos(camPos.x,camPos.y,camPos.z);
	cam.SetLook(tapePos.x,tapePos.y,tapePos.z);
	cam.toOGL();
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();

	float c=a*0.9;
	glColor4f(c,c,c,a);

	glPushMatrix();
	
	glMatrixMode(GL_MODELVIEW);

	
	glColor4f(0,0,0.0,1);
	
	glPopMatrix();
	float lado=10;

	glPushAttrib(GL_DEPTH_WRITEMASK);
	glDisable(GL_DEPTH_WRITEMASK);
	glEnable(GL_DEPTH_TEST);

	glGetBooleanv(GL_DEPTH_WRITEMASK, &currentMask);
	glDepthMask(GL_FALSE);
	
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
	int maxParts=1000;//940;
	unsigned int defParts;
	static unsigned int drawnPartsT1=0; // cuantas partes dibujadas de la cinta 1(white)
	static unsigned int drawnPartsTapes=0; // cuantas partes dibujadas de las cintas finas
	static unsigned int kk=0;
	unsigned int i;
	if(time-t1>0.02) {//0.039 0.02
		kk++;
		drawnPartsT1 ++;
		drawnPartsTapes +=1;
		t1=time;
		if(kk>maxParts) {
			defParts=0;
		} else {
			defParts=maxParts- kk;
		}
		tape.setNumDrawParts(drawnPartsT1);

		for(i=0; i<FXSCOTRA_NUM; i++){
				tapeList[i].setNumDrawParts(drawnPartsTapes);				
		}	
		
		for(i=0; i<FXSCOTRA_NUM2; i++){
			tapeList2[i].setNumDrawParts(drawnPartsTapes);				
		}	
	}
	
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
	// Cinta blanca
	tape.perFrame(time);
	
	// Cintas mas finas alrededor de la blanca
	for(i=0; i<FXSCOTRA_NUM; i++){
		tapeList[i].perFrame(time);
	}
	for(i=0; i<FXSCOTRA_NUM2; i++){
		tapeList2[i].perFrame(time);
	}

	
	glDisable(GL_BLEND);
	// restauro depth mask
	glDepthMask(currentMask);
	glPopAttrib();

	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	if(checkEventFlag(EVENT_TYPE_SNARE))
	{
		doFlash = 0.2f;
		angPulse = 2.0f;
		resetEventFlag(EVENT_TYPE_SNARE);
	}
	

	if(doFlash>0) {
		fxfade->setFadeColor(1,1,1,doFlash);
		fxfade->perFrame(time);
	}
	
	// Al principio se hace fade de blanco, y al final de la escena se hace fade a blanco...
	static float t_start = 97;
	static float t_end = 132;
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
	
}

void FXscOtra::init(void) {
	unsigned int i;
	unsigned int curvePrec = 200;
	fxfade->setFadeColor(1,1,1,1);
	fxfade->setBlendFunc(GL_DST_ALPHA, GL_SRC_ALPHA);
	
	cam.setFar(1,100000);
	cam.setFov(50);
	cam.SetPos(200,0,200);

	unsigned int numV=400;
	float rz=800;
	// tape=cinta blanca
	tape.setNumVertex(numV);
	tape.setCurvePrec(curvePrec);
	tape.setNumDrawParts(0);
	tape.setHeight(0);
	tape.setWidth(4);
	tape.setPlaneColor(1,1,1,1);

	tape.init();
	for( i=0; i<numV; i++){
		tape.setPointAt(i, -rz/2 + getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz);
	}

	// Estas son las cintas adicionales y mas finas
	// Su posicion esta basada en la de la cinta blanca, pero en random
	rz=25;
	unsigned int tapesNumV = numV ;
	for(i=0; i<FXSCOTRA_NUM; i++){
		rz = 1;
		tapeList[i].setNumVertex(tapesNumV);
		tapeList[i].setCurvePrec(curvePrec);
		tapeList[i].setNumDrawParts(0);
		tapeList[i].setHeight(0);
		tapeList[i].setWidth(3);
		if((i%2)==0) {
			tapeList[i].setPlaneColor(1,1,1,1);
		} else {
			tapeList[i].setPlaneColor(0,0,0,1);
		}
		
		tapeList[i].setTextureName("data/sccuadricula/dottedblack.png");
		tapeList[i].init();
		Point p;
		float val;
		unsigned int index=0;
		unsigned int freq = 25;
		for(unsigned int j=0; j<numV; j++){
			p = tape.getPointAt(j);
			//val = j*freq + index;
			rz+=20;
			val = j*freq+index+i*10;
			tapeList[i].setPointAt(index, p.x + getRand()*rz - getRand()*rz, p.y + getRand()*rz - getRand()*rz, p.z + getRand()*rz - getRand()*rz, p.w + getRand()*rz - getRand()*rz);index++;
		}
				
	}
	
	// Y estas son las cintas adicionales y mas finas pero negras
	// Su posicion esta basada en la de la cinta blanca, pero en random
	rz=250;
	tapesNumV = numV ;
	for(i=0; i<FXSCOTRA_NUM2; i++){
		tapeList2[i].setNumVertex(tapesNumV);
		tapeList2[i].setCurvePrec(40);
		tapeList2[i].setNumDrawParts(0);
		tapeList2[i].setHeight(0);
		tapeList2[i].setWidth(1);
		tapeList2[i].setPlaneColor(0,0,0,1);
		
		tapeList2[i].init();
		Point p;
		float val;
		unsigned int index=0;
		unsigned int freq = 25;
		for(unsigned int j=0; j<numV; j++){
			tapeList2[i].setPointAt(index,-rz/2 + getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz, -rz/2 +getRand()*rz);
			index++;
		}
		
	}


	float ancho=600, alto=600, largo=600, xinc, yinc, zinc;
	float origenx=-ancho;
	float origeny=-alto;
	float origenz=-largo;
	xinc=2*ancho/float(FXSCOTRA_NUMPLUS);
	yinc=2*alto/float(FXSCOTRA_NUMPLUS);
	zinc=2*largo/float(FXSCOTRA_NUMPLUS);
	float lado=5;

	int j,k,index=0;

	for(i=0;i<FXSCOTRA_NUMPLUS;i++) {
		for(j=0;j<FXSCOTRA_NUMPLUS;j++) {
			for(k=0;k<FXSCOTRA_NUMPLUS;k++) {
				this->pointList[index].x=origenx+xinc*i;
				this->pointList[index].y=origeny+yinc*j;
				this->pointList[index].z=origenz+zinc*k;
				index++;
			}
		}
	}

}


void FXscOtra::start(void)
{
	glLineWidth(1.0);
	glEnable(GL_SMOOTH);

	fxfade->setFadeColor(1,1,1,0.5);
	fxfade->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void FXscOtra::stop(void) {
	
}

void FXscOtra::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	int i;
	tape.deInit();
	for(i=0; i<FXSCOTRA_NUM; i++){
		tapeList[i].deInit();
	}
	for(i=0; i<FXSCOTRA_NUM2; i++){
		tapeList2[i].deInit();
	}
}

FXscOtra::FXscOtra() {
	this->numCintas=FXSCOTRA_NUM;
}

FXscOtra::~FXscOtra() {
}
