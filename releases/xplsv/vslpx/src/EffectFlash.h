#ifndef __EFFECTFLASH__
#define __EFFECTFLASH__

#include "Effect.h"

#include "math3D.h"
#include "my_opengl.h"

/*
	This effect simply paints a QUAD with the desired flashColor and blending properties
*/
class EffectFlash : public Effect {
private:
	Point flashColor;
	GLenum fac1,fac2; // for the blending

public:
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	const char *getEffectType(void);
	int setParam(char *paramName, char *attribName, float value);

};

#endif
