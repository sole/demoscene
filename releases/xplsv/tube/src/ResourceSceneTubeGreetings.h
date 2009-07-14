//: src:ResourceSceneTubeGreetings.h.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 19 february 2006  
// Declaration of CResourceSceneTubeGreetings.h class

#ifndef RESOURCESCENETUBEGREETINGS_H
#define RESOURCESCENETUBEGREETINGS_H

#include "Resource.h"
#include "Texture.h"
#include "ResourceParticleSystemSnow.h"

class CResourceSceneTubeGreetings : public CResource {
private:
	
	// resources used in this scene
	CResource* m_resOTGreetings;
	CCamera m_resCamera;
	float m_bassLevel;
	
public:
		CResourceSceneTubeGreetings();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif