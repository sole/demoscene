//: src:ResourceSceneTubeBeginning.h.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 19 february 2006  
// Declaration of CResourceSceneTubeBeginning.h class

#ifndef RESOURCESCENETUBEBEGINNING_H
#define RESOURCESCENETUBEBEGINNING_H

#include "Resource.h"
#include "Texture.h"
#include "ResourceParticleSystemSnow.h"

class CResourceSceneTubeBeginning : public CResource {
private:
	
	// resources used in this scene
	CResource* m_resOT;
	CCamera m_resCamera;
	float m_bassLevel;
	CPoint m_speed;
	
public:
		CResourceSceneTubeBeginning();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif