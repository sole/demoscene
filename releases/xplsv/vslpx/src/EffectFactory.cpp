#include "EffectFactory.h"
#include <strings.h>

EffectFactory::EffectFactory() {	
}

EffectFactory::~EffectFactory () {
}

Effect* EffectFactory::createInstance(char *effectType) {

	/*
	switch(...)
	case ... return new ...loqsea
	*/
	Effect* theEffect;
	if(strcasecmp(effectType,"effecttest")==0) {
		theEffect = new EffectTest();
		return theEffect;
	}
	if(strcasecmp(effectType,"effectflash")==0) {
		theEffect = new EffectFlash();
		return theEffect;
	}
	if(strcasecmp(effectType,"effectclearbuffer")==0) {
		theEffect = new EffectClearBuffer();
		return theEffect;
	}
	if(strcasecmp(effectType,"effectrender2texture")==0) {
		theEffect = new EffectRender2Texture();
		return theEffect;
	}
	if(strcasecmp(effectType,"effectmotionblur")==0) {
		theEffect = new EffectMotionBlur();
		return theEffect;
	}
	if(strcasecmp(effectType,"effectweirdblur")==0) {
		theEffect = new EffectWeirdBlur();
		return theEffect;
	}

	return new EffectTest;
}

