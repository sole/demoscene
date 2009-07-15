//: src:ResourceOSStarField.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 13 june 2006  
// Declaration of CResourceOSStarField class

#ifndef RESOURCEOSSTARFIELD_H
#define RESOURCEOSSTARFIELD_H

#include "Resource.h"
#include "Algebra.h"
#include <vector>
#include "Camera.h"


class CResourceOSStarField : public CResource {
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
		CResourceOSStarField();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	//int setAttribute(string name, float value);
	//int setAttribute(string name, string value);
	//int setParam(string name, float value);
	void setParam(string name, string value);
	//int parseAttributes(TiXmlElement* node);
};

#endif