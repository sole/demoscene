#include "SceneGreets.h"
#include <math.h>

#include "Demo.h"
#include "Music.h"
extern Demo *miDemo;
extern Music miMusic;

void SceneGreets::drawCircle(float x, float y, float radius) {
	unsigned int i;

	static float angleIncrement = 6.283185307179586476925286766559 / float(SCENEGREETSCIRCLEPREC);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2,0xcccc);
	float xpos, ypos, ang;
	glBegin(GL_LINE_STRIP);	
	for(i=0; i<SCENEGREETSCIRCLEPREC; i++) {
		ang = angleIncrement*i;
		xpos = x + radius * sin(ang);
		ypos = y + radius * cos(ang);
		glVertex3f(xpos,0.0, ypos);
	}
	glVertex3f(x + radius * sin(0),0.0,  y + radius * cos(0));
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void SceneGreets::drawFillCircle(float x, float y, float radius) {
	unsigned int i;

	static float angleIncrement = 6.283185307179586476925286766559 / float(SCENEGREETSCIRCLEPREC);

	float xpos, ypos, ang;
	glBegin(GL_POLYGON);	
	for(i=0; i<SCENEGREETSCIRCLEPREC; i++) {
		ang = angleIncrement*i;
		xpos = x + radius * sin(ang);
		ypos = y + radius * cos(ang);
		glVertex3f(xpos,0.0,ypos);
	}
	glVertex3f(x + radius * sin(0),0.0,  y + radius * cos(0));
	glEnd();
}

void SceneGreets::drawFlower(float x, float y, float percentage, float alpha) {
	static float fmax = 50; // maximum flower radius

	float fbigCircleRadius = percentage * fmax;
	float flessBigCircleRadius = 0.9 * fbigCircleRadius;

	glColor4f(0.2,0.2,0.2,alpha);
	this->drawFillCircle(x,y,fbigCircleRadius);

	glColor4f(0.6,0,0,alpha);
	this->drawFillCircle(x,y,flessBigCircleRadius);

	glColor4f(0.7,0.7,0.7,alpha);

	unsigned int i, numSubCircles = 8;
	for(i=0;i < numSubCircles; i++) {
		this->drawCircle(x + getRand() * 4, y + getRand()*4, flessBigCircleRadius*0.85*(float(i)/float(numSubCircles)));
	}

	this->drawCircle(x,y,fbigCircleRadius+fbigCircleRadius);

}


void SceneGreets::play(float _time) {
	unsigned int i=0,j;
	static int playing=0;

	
	
	// Getting the bombo!!
	unsigned int bombo;
	float theBASS = miMusic.getFFTBass()*100;
	if(theBASS>30)
		bombo=1;
	else
		bombo=0;


	// Textura de fondo
	miDemo->ponOrtopedico();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//glBindTexture(GL_TEXTURE_2D, textureScroller.texID);
	glNormal3f( 0.0f, 0.0f, 1.0f);

	// asumo q la textura es cuadrada y los datos estan en la parte superior
	static float texBase=0;//1-baseY;
	static float xt = 320;
	static float yt = 120, ydesp=-30;
	static float z_depth=float(0.15);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_TEXTURE_2D);
	miDemo->ejes();
	glColor4f(1,0,0,1);

	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,z_depth);
		glVertex3f(100,100,z_depth); 
	glEnd();
	glDisable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	miDemo->quitaOrtopedico();

	// ...........................
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//glLoadIdentity();

	Point camPos;
	Camera miCam;
	Path *currentPath;
	currentPath = &this->pathCam01;
	static float cameraTimer=0;
	unsigned int currentCamPoint=0;
	if(_time-cameraTimer>0.02) {
		cameraTimer=_time;
		unsigned int maxPoints = currentPath->getNumICP();
		currentCamPoint++;
		if(currentCamPoint>maxPoints)
			currentCamPoint = 0;
	}
	currentPath->getPointAt(currentCamPoint, &camPos);

	miCam.SetPos(400,10,10);
	//miCam.SetPos(400*sin(_time),0,400*cos(_time));
	//miCam.SetPos(camPos);
	//miCam.SetLook(-150,0.1,0.1);
	miCam.SetLook(-100,0.1,-100);
	miCam.setFar(1,10000);
	miCam.setFov(45);

	miCam.toOGL();
	//camara-opengl
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();

	
	//glLineWidth(2.0);glColor3f(1,0,0);
	//miDemo->ejes();

	//scene3d.draw();
	static float timerFlowers = 0;
	float flowerVel, flowerDecay;
	if(_time - timerFlowers > 0.2) {
		flowerVel = -0.2;
		flowerDecay = 0.005;
	} else {
		flowerVel = 0;
		flowerDecay = 0;
	}
	float xpos, ypos;
	for(i = 0; i</*SCENEGREETSNUMFLOWERS*/1; i++) {
		xpos = this->vFlowerPositions[i].x+flowerVel;//*this->vFlowerPositions[i].w;
		ypos = this->vFlowerPositions[i].y;
		if(xpos < -320) {
			xpos = 320;
			ypos = getRand()*200 - getRand()*200;
		}
		
		this->vFlowerPositions[i].w+=flowerDecay;
		if(this->vFlowerPositions[i].w>1) {
			xpos = getRand()*320 - getRand()*320;
			ypos = getRand()*200 - getRand()*200;
			this->vFlowerPositions[i].w=0;
		}
		this->vFlowerPositions[i].x=xpos;
		this->vFlowerPositions[i].y=ypos;
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(this->vFlowerPositions[i].x,0,this->vFlowerPositions[i].y);
		miDemo->ejes();
		this->drawFlower(0,0,this->vFlowerPositions[i].w,1-this->vFlowerPositions[i].w);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
//		this->drawFlower(this->vFlowerPositions[i].x,this->vFlowerPositions[i].y,this->vFlowerPositions[i].w,1-this->vFlowerPositions[i].w);
	}


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Quite simple: play all effects if they need to...
	/*for(i=0;i<this->numEffects;i++) {
		is = this->effectsList[i]->isPlaying(_time);
		assert( (is==-1) || (is>=0));
		if(is!=-1) {
			this->effectsList[i]->play(_time);
		}
	}*/
}

void SceneGreets::init() {
	unsigned int i=0;
	
	// Cargar textura de SCroll TODO
	//LoadTGA(&textureScroller,".\\data\\scroller.tga");

	// Cargar escena con la cacharra
	//scene3d.loadFromFile(".\\data\\12dolls_cacharra.ASE");
	//scene3d.loadFromFile(".\\data\\tests04.ASE");

	// TODO this->numEffects=0;
	this->pathCam01.loadPath("./data/12dolls_pathcirculo.ASE"); 

	for(i=0;i<SCENEGREETSNUMFLOWERS;i++) {		
		this->vFlowerPositions[i].x=getRand()*miDemo->getWidth()*0.6;
		this->vFlowerPositions[i].y=getRand()*miDemo->getHeight()*0.6;
		this->vFlowerPositions[i].z=getRand();
		this->vFlowerPositions[i].w=getRand(); // usare el w como porcentaje de tamaño
	}
	for(i=0;i<(unsigned)this->numEffects;i++) {		
		this->effectsList[i]->init();	
	}
}

void SceneGreets::start() {
	int i=0;
}

void SceneGreets::deInit(void) {
	int i=0;
}

const char* SceneGreets::getSceneType(void) {
	return "SceneGreets";
}
