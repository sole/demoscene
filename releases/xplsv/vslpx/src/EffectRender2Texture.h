#ifndef __EFFECTRENDER2TEXTURE__
#define __EFFECTRENDER2TEXTURE__

#include "Effect.h"

#include "math3D.h"
#include "textures.h"

/*
	This effect simply copies what it is on the framebuffer to a texture
*/
class EffectRender2Texture : public Effect {
private:
	TextureImage* myTexture;

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
