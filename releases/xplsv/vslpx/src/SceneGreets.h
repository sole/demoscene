#ifndef __SCENEGREETS__
#define __SCENEGREETS__

#include "Path.h"


#include "Camera.h"
#include "GeomObject.h"
#include "Scene3D.h"
#include "textures.h"

#define SCENEGREETSCIRCLEPREC 32
#define SCENEGREETSNUMFLOWERS 20

#include "Scene.h"

class SceneGreets : public Scene {
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

	Point vFlowerPositions[SCENEGREETSNUMFLOWERS];

	void drawCircle(float x, float y, float radius);
	void drawFillCircle(float x, float y, float radius);
	void drawFlower(float x, float y, float percentage, float alpha);
public:
	void play(float _time);
	void init(void);
	void start(void);
	void deInit(void);
	const char *getSceneType(void);
};



#endif
