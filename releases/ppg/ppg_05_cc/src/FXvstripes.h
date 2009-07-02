#ifndef FXVSTRIPES_H
#define FXVSTRIPES_H

#include "Effect.h"
#include "math3D.h"
#include "Demo.h"
#include "textures.h"
extern Demo *miDemo;

#define NUMALPHALEVELS 400
#define APPEAR 1
#define DISSAPPEAR 2

class FXvstripes: public Effect {
protected:

	TextureImage myTexture;
	Point textColor;
	char textPath[255];
	float alphaLevels[NUMALPHALEVELS];
	float lightingTime;
	int mode;

public:
	void setTexture(char *texturePath);
	void setLightingTime(float newTime);
	void setMode(int newMode);
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	void setColor(float r,float g, float b, float a);
	FXvstripes();
	~FXvstripes();
};

#endif //FXVSTRIPES_H
