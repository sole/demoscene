#include "FXplane.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXplane::perFrame(float time) {
char s[255];

	this->_time=time;
	GLboolean currentMask;

	// Si es demasiado pronto que no empiece
	if(time<=this->starttime && !this->fixed) {
		return;
	}
	
	if(this->started==0) {
		// es la primera vez que se pone en marcha el efecto
		this->started=1;

		// es como si le dijera: Empieza aqui tu ciclo!!! TRIGGER!
		this->starttime=time;
	}


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
	
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glGetBooleanv(GL_DEPTH_WRITEMASK, &currentMask);
	glDepthMask(false);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	float scaled_width, scaled_height;
	int baseViewport;
	
	scaled_width = miDemo->getWidth();
	scaled_height = planeData.height * scaled_width / planeData.width;
	baseViewport = (int)(miDemo->getHeight() - scaled_height) / 2;
	glViewport(0, baseViewport, (GLsizei) scaled_width, (GLsizei) scaled_height);
	glOrtho(0, scaled_width, 0, scaled_height, -0.1, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	
	glColor4f(pc.x,pc.y,pc.z,pc.w);

	glBlendFunc(fac1, fac2);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	

	static float z_depth=float(0.15);
	glBindTexture(GL_TEXTURE_2D, planeData.texID);
	glNormal3f( 0.0f, 0.0f, 1.0f);

	// asumo q la textura es cuadrada y los datos estan en la parte superior
	float texBase=0;//1-baseY;

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, texBase); glVertex3f(0, 0,  z_depth);
		glTexCoord2f(1.0f, texBase); glVertex3f( scaled_width, 0,  z_depth);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( scaled_width, scaled_height,  z_depth);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  scaled_height,  z_depth);
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

void FXplane::setTextureName(const char *filename) {
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
