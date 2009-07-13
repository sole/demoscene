#ifndef __SCENEFACTORY__
#define __SCENEFACTORY__

#include "Scene.h"

// Include here all the defined-registered scenes
#include "SceneTest.h"
#include "Scene01.h"
#include "ScenePlano.h"
#include "SceneScroller.h"
#include "SceneCredits.h"
#include "SceneGreets.h"

// end of registered scenes


class SceneFactory {
   public:
      SceneFactory() ;
      ~SceneFactory() ;
      Scene *createInstance(char *sceneType);   
};

#endif

