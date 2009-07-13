#include <math.h>
#include "SceneScroller.h"

#include "Demo.h"
#include "Music.h"
extern Demo *miDemo;
extern Music miMusic;

#include "Camera.h"
#include "GeomObject.h"


void SceneScroller::play(float _time) {
	unsigned int i=0,j;
	static int playing=0;
	
	// Getting the bombo!!
	/*unsigned int bombo;
	float theBASS = miMusic.getFFTBass()*100;
	if(theBASS>30)
		bombo=1;
	else
		bombo=0;*/

	/*glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	//camara-opengl
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();*/

	// Textura de fondo

	miDemo->ponOrtopedico();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	
	// Layers y alphas cogidos de la mano
	unsigned int snare;
	if(this->effectsList[0]->isPlaying(_time)!=-1)
		snare=1;
	else
		snare=0;
	static float layerAlpha=0;
	static float layerAlphaVar=0;
	static float timerSnare = -1000;
	if(snare)
		layerAlpha=1;
	
	if( ( _time - timerSnare  ) > 0.03) {
		timerSnare = _time;
		
		if(layerAlpha > 0) {
			layerAlpha -= 0.05f;
		}
	}	
	
	
	static const float baseY=miDemo->getHeight()/miDemo->getWidth();
	static const float xt=0.5; // xtremo
	static const float yt=0.5*baseY;
	static float z_depth=float(0.15);
	glBindTexture(GL_TEXTURE_2D, textureScroller.texID);
	glNormal3f( 0.0f, 0.0f, 1.0f);

	static float texBase=0;//1-baseY;
	float height = textureScroller.height;
	float xdesp = 70 * (_time-49.765); //  px por segundo!!
	glTranslatef(320 - xdesp, -height * 0.5f,0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_TEXTURE_2D);
	
	glColor4f(1,1,1,layerAlpha);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, texBase); glVertex3f(0, 0,  z_depth);
		glTexCoord2f(1.0f, texBase); glVertex3f( textureScroller.width, 0,  z_depth);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( textureScroller.width, height,  z_depth);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  height,  z_depth);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	miDemo->quitaOrtopedico();


}

void SceneScroller::init() {
	unsigned int i=0;
	
	// Cargar textura de SCroll
	LoadTGA(&textureScroller,"./data/greetings.png");

	// TODO this->numEffects=0;
	for(i=0;i<(unsigned)this->numEffects;i++) {		
		this->effectsList[i]->init();	
	}
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

}

void SceneScroller::start() {
	int i=0;
}

void SceneScroller::deInit(void) {
	int i=0;
}

const char* SceneScroller::getSceneType(void) {
	return "SceneScroller";
}
