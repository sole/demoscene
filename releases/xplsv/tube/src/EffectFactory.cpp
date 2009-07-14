#include "EffectFactory.h"


CEffectFactory::CEffectFactory() {	
}

CEffectFactory::~CEffectFactory () {
}

CEffect* CEffectFactory::createInstance(string type) {
	
	CEffect* theEffect;
	if(type=="empty") {
		theEffect = new CEffectEmpty();
		return theEffect;
	}
	
	return new CEffectEmpty();
}

