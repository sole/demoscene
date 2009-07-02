#ifndef FXPLANE_H
#define FXPLANE_H

#include <assert.h>
#include "Effect.h"
#include "math3D.h"
#include "Demo.h"
#include "textures.h"

extern Demo *miDemo;

class FXplane: public Effect {
protected:

	// aqui me guardo el color base y final del plano
	Point planeColor; // es el sustain
	Point finalPlaneColor; // corresponde a despues de release
	GLenum fac1,fac2;

	// la textura a aplicar en el plano
	char textureName[255];
	TextureImage planeData;

	// 
	unsigned char started;
	float attack, sustain, release, starttime, endtime;
	unsigned char fixed;
public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	void setPlaneColor(float r,float g, float b, float a);
	void setFinalPlaneColor(float r,float g, float b, float a);
	void setSustain(float _sustain);
	void setRelease(float _release);
	void setAttack(float _attack);
	void setFixed(unsigned char _status);
	void setStartTime(float _stime);

	float getRelease(void);
	float getAttack(void);
	float getSustain(void);
	float getStartTime(void);
	float getEndTime(void);

	void trigger(void);


	void setBlendFunc(GLenum fac1,GLenum fac2);
	void setTextureName(char *filename);

	FXplane();
	~FXplane();
};

#endif //FXPLANE_H
