#ifndef __SCENETEST__
#define __SCENETEST__

#include "GeomObject.h"
#include "Scene3D.h"

#include "Scene.h"

class SceneTest : public Scene {
private:
	GeomObject go_test;
	Scene3D s3_test;
public:
	void play(float _time);
	void init(void);
	void start(void);
	void deInit(void);
	const char *getSceneType(void);
};

#endif
