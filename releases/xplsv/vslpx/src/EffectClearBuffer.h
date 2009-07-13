#ifndef __EFFECTCLEARBUFFER__
#define __EFFECTCLEARBUFFER__

#include "math3D.h"
#include <string.h>

#include "Effect.h"
/*
	This effect simply clears the color buffer with the desired color (canvasColor)
*/
class EffectClearBuffer : public Effect {
private:
	Point canvasColor;

public:
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	const char *getEffectType(void);
	int setParam(char *paramName, char *attribName, float value);

};

#endif
