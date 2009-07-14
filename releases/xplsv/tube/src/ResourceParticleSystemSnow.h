//: src:ResourceParticleSystemSnow.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 11 august 2005  
// Declaration of CResourceParticleSystemSnow class

#ifndef RESOURCEPARTICLESYSTEMSNOW_H
#define RESOURCEPARTICLESYSTEMSNOW_H

#include "Resource.h"
#include "Algebra.h"
#include <vector>
#include "Camera.h"


class CResourceParticleSystemSnow : public CResource {
private:
	// color
	CPoint m_Color;
	
	unsigned int m_numParticles;
	CPoint m_origin1, m_origin2;
	CPoint m_gravity;
	CPoint m_vup, m_vright; // this is used for drawing each particle in the proper plane
	float m_fadeout;
	std::vector <CPoint> m_particlesList;
	
	// max size of each particle
	float m_maxSize;
	// the blending
	bool m_hasCustomBlending;
	unsigned int m_renderBlendingPos;
	
	// the texture
	string m_TextureFile;
	unsigned int m_texPos;
	bool m_hasTexture;
	
	inline void drawParticle(float x2, float y2, float z2, float dens, CPoint vup, CPoint vright);
	inline void initParticle(CPoint *p);
public:
		CResourceParticleSystemSnow();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif
