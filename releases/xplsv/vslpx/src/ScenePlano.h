#ifndef __SCENEPLANO__
#define __SCENEPLANO__

#include "Scene.h"


#include "Particles.h"
#include "Path.h"

#include "Camera.h"
#include "GeomObject.h"
#include "Scene3D.h"


#define SCENEPLANO_PARALELNUM 200
#define SCENEPLANO_QUADRICNUM 8
#define SCENEPLANO_MAXPARTICLES 800

class ScenePlano : public Scene {
private:
	Scene3D scene3d;
	unsigned int m_uiNumParalel;
	float m_fXRange, m_fYRange, m_fZRange;
	Point m_vParalelPos[SCENEPLANO_PARALELNUM];
	unsigned int m_uiNumQuadrics;
	unsigned int m_uiNumSubQuadrics;
	GLUquadricObj* m_Quadric;
	ParticleSystem parts1;
	ParticleManager partm1;
	Particle misparticulas[SCENEPLANO_MAXPARTICLES];
	Point orisis;
	TextureImage m_TextureParticle;
	TextureImage m_TexturePlane;
	Path pathCam01,pathCam02;
	Path pathCamLook01;
	TextureImage 
		m_TextureXplsv01, 
		m_TextureVslpx, 
		m_TextureCircle, 
		m_TextureDalezy, 
		m_TextureLayer01,
		m_TextureLayer02,
		m_TextureLayer03,
		m_TextureSole,
		m_TextureTrace,
		m_TextureVslpx2,
		m_TextureXplsv,
		m_Texture2005;

public:
	void play(float _time);
	void init(void);
	void start(void);
	void deInit(void);
	const char *getSceneType(void);
};



#endif
