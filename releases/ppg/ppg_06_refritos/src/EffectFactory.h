//: src:EffectFactory.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 30 july 2005  
// Declaration of CEffectFactory class

#ifndef EFFECTFACTORY_H
#define EFFECTFACTORY_H

#include "Effect.h"

#include <string>
using namespace std;

// Include here all the defined-registered effects
#include "EffectEmpty.h"

// end of registered scenes

class CEffectFactory {
public:
	CEffectFactory() ;
	~CEffectFactory() ;
	CEffect *createInstance(string type);   
};

#endif
