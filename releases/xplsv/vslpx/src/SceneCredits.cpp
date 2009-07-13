#include "SceneCredits.h"
#include <math.h>

#include "Demo.h"
#include "Music.h"
extern Demo *miDemo;
extern Music miMusic;

#include "Camera.h"
#include "GeomObject.h"

void SceneCredits::play(float _time) {
	unsigned int i=0,j;
	static int playing=0;
	Camera miCam;
	
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

	glBindTexture(GL_TEXTURE_2D, textureScroller.texID);
	glNormal3f( 0.0f, 0.0f, 1.0f);

	// asumo q la textura es cuadrada y los datos estan en la parte superior
	static float texBase=0;//1-baseY;
	static float xt = 320;
	static float yt = 120, ydesp=-30;
	static float z_depth=float(0.15);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	miDemo->ejes();
	glColor4f(1,1,1,0.75);
	/*glBegin(GL_QUADS);
		glTexCoord2f(0.0f, texBase); glVertex3f(-xt, -yt+ydesp,  z_depth);
		glTexCoord2f(1.0f, texBase); glVertex3f( xt, -yt+ydesp,  z_depth);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( xt,  yt+ydesp,  z_depth);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-xt,  yt+ydesp,  z_depth);

	glEnd();*/ // Lo quito porque molesta TODO
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	miDemo->quitaOrtopedico();

	// ...........................
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//glLoadIdentity();

	miCam.SetPos(-100,0,400);
	miCam.SetLook(-150,0.1,0.1);
	miCam.setFar(1,10000);
	miCam.setFov(45);

	miCam.toOGL();
	//camara-opengl
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glLineWidth(2.0);glColor3f(1,0,0);
	miDemo->ejes();

	//scene3d.draw();

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

void SceneCredits::init() {
	unsigned int i=0;
	
	// Cargar textura de SCroll TODO
	// LoadTGA(&textureScroller,".\\data\\scroller.tga");

	// Cargar escena con la cacharra
	//scene3d.loadFromFile(".\\data\\12dolls_cacharra.ASE");
	//scene3d.loadFromFile(".\\data\\tests04.ASE");

	// TODO this->numEffects=0;
	for(i=0;i<(unsigned)this->numEffects;i++) {		
		this->effectsList[i]->init();	
	}
}

void SceneCredits::start() {
	int i=0;
}

void SceneCredits::deInit(void) {
	int i=0;
}

const char* SceneCredits::getSceneType(void) {
	return "SceneCredits";
}
