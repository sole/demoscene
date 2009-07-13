#ifndef __EFFECTMOTIONBLUR__
#define __EFFECTMOTIONBLUR__

#include "Effect.h"
#include "textures.h"
#include "math3D.h"
#include "my_opengl.h"

/*
	This effect simply paints a QUAD with the desired texture, color and blending properties
*/
class EffectMotionBlur : public Effect {
private:
	TextureImage* myTexture;
	Point textColor;
	GLenum fac1,fac2; // for the blending
	unsigned int width, height;
	unsigned int textureId;

public:
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	const char *getEffectType(void);
	int setParam(char *paramName, char *attribName, float value);

};

#endif
