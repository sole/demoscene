#include "Scene01.h"
#include "Demo.h"
extern Demo *miDemo;

#include "Camera.h"
#include <math.h>

void Scene01::play(float _time) {
	int i=0;
	static int playing=0;
	
	int is;
	/*glClearColor(0,0,0,1);glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	Camera miCam;
	float d=100;
	
	miCam.SetPos(d,d,0);
	miCam.setFov(60);
	miCam.SetLook(0.1,0.1,0.1);
	miCam.setFar(1,10000);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	miCam.toOGL();
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glRotatef(_time*5,1,1,1);


	glBegin(GL_LINE_STRIP);
		
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
*/
	// Quite simple: play all effects if they need to...
	for(i=0;i<this->numEffects;i++) {
		is = this->effectsList[i]->isPlaying(_time);
		assert( (is==-1) || (is>=0));
		if(is!=-1) {
			this->effectsList[i]->play(_time);
		}
	}
}

void Scene01::init() {
	int i=0;

	//this->s3_test.loadFromFile(".\\data\\tests04.ASE");


	// TODO this->numEffects=0;
	for(i=0;i<this->numEffects;i++) {		
		this->effectsList[i]->init();	
	}
}

void Scene01::start() {
	int i=0;
}

void Scene01::deInit(void) {
	int i=0;
}

const char* Scene01::getSceneType(void) {
	return "Scene01";
}
