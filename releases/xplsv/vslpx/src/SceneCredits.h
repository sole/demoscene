#ifndef __SCENECREDITS__
#define __SCENECREDITS__

#include "Path.h"
#include "Scene3D.h"
#include "Scene.h"
#include "textures.h"

class SceneCredits : public Scene {
private:
	Scene3D scene3d;
	unsigned int m_uiNumParalel;
	float m_fXRange, m_fYRange, m_fZRange;
	//Point m_vParalelPos[SCENEPLANO_PARALELNUM];
	unsigned int m_uiNumQuadrics;
	unsigned int m_uiNumSubQuadrics;
	GLUquadricObj* m_Quadric;
	Path pathCam01,pathCam02;
	Path pathCamLook01;
	TextureImage textureScroller;
public:
	void play(float _time);
	void init(void);
	void start(void);
	void deInit(void);
	const char *getSceneType(void);
};



#endif
