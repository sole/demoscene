#include "FXplane.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXplane::perFrame(float time) {
char s[255];

	this->_time=time;
	GLboolean currentMask;


	// Si es demasiado pronto que no empiece
	if(time<=this->starttime) {
		if(!this->fixed) {
		return;
		}
	}

	static float baseY=768.0/1024.0;

	int baseViewport=(int)(miDemo->getHeight() - planeData.height) / 2;
	
	if(this->started==0) {
		// es la primera vez que se pone en marcha el efecto
		this->started=1;

		// es como si le dijera: Empieza aqui tu ciclo!!! TRIGGER!
		this->starttime=time;
	}


	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glGetBooleanv(GL_DEPTH_WRITEMASK, &currentMask);
	glDepthMask(false);

	miDemo->ponOrtopedico(planeData.width*4, planeData.height*4);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	//glTranslatef(0,baseY*0.5,0);
	
	// Determinamos el color del plano segun el tiempo transcurrido
	Point pc; // plane color
	float coef,coefmenos1;
	float attackRange=this->attack+this->starttime;
	float sustainRange=attackRange+ this->sustain;
	float releaseRange=sustainRange + this->release;

	if(time<=attackRange) {
		// coef es la cantidad de color transitorio q se quiere
		if(this->attack>0) {
			coef=1-(attackRange - time) / this->attack;
		} else
			coef=1;
		
		coefmenos1=1-coef;
		pc.x=planeColor.x*coef + finalPlaneColor.x*(coefmenos1);
		pc.y=planeColor.y*coef + finalPlaneColor.y*(coefmenos1);
		pc.z=planeColor.z*coef + finalPlaneColor.z*(coefmenos1);
		pc.w=planeColor.w*coef + finalPlaneColor.w*(coefmenos1);

	}else if((time>attackRange) && (time<=sustainRange)) {
		// es el período estacionario
		pc.x=planeColor.x;
		pc.y=planeColor.y;
		pc.z=planeColor.z;
		pc.w=planeColor.w;


	} else if((time > sustainRange) && (time <= releaseRange)){
		// release: time > sustain luego hemos entrado en el período de liberacion
		

		coef=(releaseRange - time) / this->release;

		coefmenos1=1-coef;
		pc.x=planeColor.x*coef + finalPlaneColor.x*(coefmenos1);
		pc.y=planeColor.y*coef + finalPlaneColor.y*(coefmenos1);
		pc.z=planeColor.z*coef + finalPlaneColor.z*(coefmenos1);
		pc.w=planeColor.w*coef + finalPlaneColor.w*(coefmenos1);
	} else {

		pc.x=finalPlaneColor.x;
		pc.y=finalPlaneColor.y;
		pc.z=finalPlaneColor.z;
		pc.w=finalPlaneColor.w;

	}
	glColor4f(pc.x,pc.y,pc.z,pc.w);

	glBlendFunc(fac1, fac2);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	
	static const float xt=0.5; // xtremo
	static const float yt=0.5*baseY;
	static float z_depth=float(0.15);
	glBindTexture(GL_TEXTURE_2D, planeData.texID);
	glNormal3f( 0.0f, 0.0f, 1.0f);

	// asumo q la textura es cuadrada y los datos estan en la parte superior
	

	float texBase=0;//1-baseY;

	glBegin(GL_QUADS);
/*	glTexCoord2f(0.0f, texBase); glVertex3f(0, 0,  z_depth);
	glTexCoord2f(1.0f, texBase); glVertex3f( planeData.width, 0,  z_depth);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( planeData.width, planeData.height,  z_depth);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  planeData.height,  z_depth);*/
	
	float xt2 = planeData.width;
	float dpy = 0;
	float dp = 0;
	glTexCoord2f(0, 0); 
	glVertex3f(-xt2*2+dp,-xt2+dpy,z_depth);
	
	glTexCoord2f(1,0);
	glVertex3f(xt2*2+dp,-xt2+dpy, z_depth);

	glTexCoord2f(1,1);
	glVertex3f(xt2*2+dp,xt2+dpy,  z_depth);

	glTexCoord2f(0,1);
	glVertex3f(-xt2*2+dp,xt2+dpy,z_depth);
	glEnd();

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glPopAttrib();
	glDepthMask(currentMask);

}

void FXplane::trigger(void) {
	this->starttime=_time;
}

void FXplane::setStartTime(float _stime) {
	this->starttime=_stime;
}

void FXplane::init(void) {
	

	if(strcmp(this->textureName,"")!=0) {
		// si hay textura la cargo
		LoadTGA(&planeData,textureName);
	}
	this->endtime=starttime + attack + sustain + release;
	
}

void FXplane::setPlaneColor(float r, float g, float b, float a) {
	this->planeColor.x=r;
	this->planeColor.y=g;
	this->planeColor.z=b;
	this->planeColor.w=a;

}

void FXplane::setFinalPlaneColor(float r, float g, float b, float a) {
	this->finalPlaneColor.x=r;
	this->finalPlaneColor.y=g;
	this->finalPlaneColor.z=b;
	this->finalPlaneColor.w=a;
}

void FXplane::setFixed(unsigned char _status) {
	this->fixed=_status;
}

void FXplane::setBlendFunc(GLenum fac1,GLenum fac2) {
	this->fac1=fac1;
	this->fac2=fac2;
}

void FXplane::setTextureName(char *filename) {
	assert(filename!=NULL);

	strcpy(textureName,filename);
}

void FXplane::setRelease(float _release) {
	this->release=_release;
}

void FXplane::setSustain(float _sustain) {
	this->sustain=_sustain;
}

void FXplane::setAttack(float _attack) {
	this->attack=_attack;
}

float FXplane::getAttack(void) {
	return this->attack;
}

float FXplane::getSustain(void) {
	return this->sustain;
}

float FXplane::getRelease(void) {
	return this->release;
}

float FXplane::getStartTime(void) {
	return this->starttime;
}

float FXplane::getEndTime(void) {
	
	return(this->endtime);
}

void FXplane::start(void) {
	
}

void FXplane::stop(void) {
	
}

void FXplane::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	//if(planeData->texID!=NULL)
	//	glDeleteTextures(1, *planeData->texID);
}

FXplane::FXplane() {
	fac1=GL_SRC_ALPHA;
	fac2=GL_ONE_MINUS_SRC_ALPHA;
	strcpy(textureName,"");
	// color por defecto -> blanco, alpha=100%
	this->planeColor.x=1;
	this->planeColor.y=1;
	this->planeColor.z=1;
	this->planeColor.w=1;

	this->starttime=0;
	this->started=0;
	this->sustain=1000; // (Segundos, y ya es una burrada!!)
	this->release=0;
	this->attack=0;
	this->fixed=0;


	this->endtime=starttime + attack + sustain + release;
}

FXplane::~FXplane() {
}
