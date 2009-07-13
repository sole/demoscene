#include "Effect.h"

// Include here all the defined-registered effects
#include "EffectTest.h"
#include "EffectFlash.h"
#include "EffectClearBuffer.h"
#include "EffectRender2Texture.h"
#include "EffectMotionBlur.h"
#include "EffectWeirdBlur.h"


// end of registered scenes

#ifndef __EFFECTFACTORY__
#define __EFFECTFACTORY__


class EffectFactory {
   public:
      EffectFactory() ;
      ~EffectFactory() ;
      Effect *createInstance(char *effectType);   
};

#endif

