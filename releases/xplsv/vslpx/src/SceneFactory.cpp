#include "SceneFactory.h"

/*
class SceneFactory {
   public:
      SceneFactory() {}
      ~SceneFactory() {}
      Scene *createInstance(char *sceneType);
};

*/

SceneFactory::SceneFactory() {
//	int i;
	
}

SceneFactory::~SceneFactory() {
}

Scene* SceneFactory::createInstance(char *sceneType) {

	/*
	switch(...)
	case ... return new ...loqsea
	*/
	Scene* theScene;
	if(strcmp(sceneType,"SceneTest")==0) {
		theScene = new SceneTest();
		return theScene;
	}
	if(strcmp(sceneType,"Scene01")==0) {
		theScene = new Scene01();
		return theScene;
	}
	if(strcmp(sceneType,"ScenePlano")==0) {
		theScene = new ScenePlano();
		return theScene;
	}
	if(strcmp(sceneType,"SceneScroller")==0) {
		theScene = new SceneScroller();
		return theScene;
	}
	if(strcmp(sceneType,"SceneCredits")==0) {
		theScene = new SceneCredits();
		return theScene;
	}
	if(strcmp(sceneType,"SceneGreets")==0) {
		theScene = new SceneGreets();
		return theScene;
	}
	return new SceneTest;
}

