#include "Effect.h"

#ifndef __EFFECTTEST__
#define __EFFECTTEST__

class EffectTest : public Effect {

public:
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	const char *getEffectType(void);
	int setParam(char *paramName, char *attribName, float value);

};

#endif
