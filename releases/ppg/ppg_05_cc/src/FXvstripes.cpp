#include "FXvstripes.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXvstripes::perFrame(float time) {

	glColor4f(textColor.x,textColor.y,textColor.z,textColor.w);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,myTexture.texID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float xt=1; // xtremo
	float yt=1;
	float z_depth=float(-0.01);

	static float quadWidth=xt*2/NUMALPHALEVELS;

	float xofs=-xt;
	float texX=0;
	float texQWidth=1.0/NUMALPHALEVELS;

	static float lastExec=-1;
	if(lastExec==-1) {
		lastExec=time;
	}
	int aleatorio,pasadas;
	float incr;

	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	for(int i=0;i<NUMALPHALEVELS;i++) {
		
		/* incrementar algo el alpha de este level ... */
		if(time-lastExec>lightingTime) {
			for(int j=0;j<70;j++) {
				aleatorio=int(getRand()*NUMALPHALEVELS);
				incr=getRand()*0.1;
				if(mode==APPEAR) {
					pasadas=0;
					while(alphaLevels[aleatorio]>=0.95f && pasadas<20) {
						alphaLevels[aleatorio]=1.0;
						aleatorio=int(getRand()*NUMALPHALEVELS);
						pasadas++;
					}
					alphaLevels[aleatorio]+=incr;
					if(alphaLevels[aleatorio]>1.0) {
						alphaLevels[aleatorio]=1.0;
					}
					
				} else {

					pasadas=0;
					while(alphaLevels[aleatorio]<=0.05f && alphaLevels[aleatorio]>=0.0f && pasadas<20) {
						alphaLevels[aleatorio]=0.0;
						aleatorio=int(getRand()*NUMALPHALEVELS);
						pasadas++;
					}
					alphaLevels[aleatorio]-=incr;

					if(alphaLevels[aleatorio]<0.0) {
						alphaLevels[aleatorio]=0.0;
					}
				}
			}
			lastExec=time;
		}
		float ys,xs; // ysize, lo q le doy de mas segun el alpha :D
		
		glBegin(GL_QUADS);
			glColor4f(textColor.x,textColor.y,textColor.z,alphaLevels[i]);
			ys=20*(1-alphaLevels[i]);
			xs=0;//ys*0.2;
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(texX, 0.0f);
			glVertex3f(xofs-xs,-yt-ys,z_depth);

			glTexCoord2f(texX+texQWidth, 0.0f);
			glVertex3f(xofs+quadWidth+xs,-yt-ys, z_depth);

			glTexCoord2f(texX+texQWidth, 1.0f);
			glVertex3f(xofs+quadWidth+xs,yt+ys,  z_depth);

			glTexCoord2f(texX, 1.0f);
			glVertex3f(xofs-xs,yt+ys,z_depth);
		glEnd();

		xofs+=quadWidth;
		texX+=texQWidth;
	}

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
}

void FXvstripes::init(void) {
	// color por defecto -> blanco
	this->textColor.x=1;
	this->textColor.y=1;
	this->textColor.z=1;
	this->textColor.w=1;

	LoadTGA(&myTexture,textPath);

	lightingTime=0.005; // en segundos

	for(int i=0;i<NUMALPHALEVELS;i++) {
		alphaLevels[i]=0.0;
	}

	mode=APPEAR;
}

void FXvstripes::setColor(float r, float g, float b, float a) {
	this->textColor.x=r;
	this->textColor.y=g;
	this->textColor.z=b;
	this->textColor.w=a;
}

void FXvstripes::setTexture(char *texturePath) {
	strcpy(textPath,texturePath);
}

void FXvstripes::setLightingTime(float newTime) {
	lightingTime=newTime;
}
 

void FXvstripes::setMode(int newMode) {
	mode=newMode;
}

void FXvstripes::start(void) {
	
}

void FXvstripes::stop(void) {
	
}

void FXvstripes::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	
}

FXvstripes::FXvstripes() {
}

FXvstripes::~FXvstripes() {
}
