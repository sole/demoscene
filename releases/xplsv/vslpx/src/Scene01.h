#ifndef __SCENE01__
#define __SCENE01__

#include "GeomObject.h"
#include "Scene3D.h"
#include "Scene.h"

class Scene01 : public Scene {
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
