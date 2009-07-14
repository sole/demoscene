//: src:ResourceSceneTGForest.h.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 19 february 2006  
// Declaration of CResourceSceneTGForest.h class

#ifndef RESOURCESCENETGFOREST_H
#define RESOURCESCENETGFOREST_H

#include "Resource.h"
#include "Texture.h"
#include "ResourceParticleSystemSnow.h"

class CResourceSceneTGForest : public CResource {
private:
	
	// resources used in this scene
	CResource* m_resPSSnow;
	CCamera m_resCamera;
	
public:
		CResourceSceneTGForest();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif
