//: src:EffectEmpty.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 30 july 2005  
// Declaration of CEffectEmpty class

#ifndef EFFECTEMPTY_H
#define EFFECTEMPTY_H

#include "Resource.h"

#include <string>
using namespace std;

class CEffect {
protected:
	// TODO EventList *myEventList; // i think this should go inside an effect
	CResource* m_Resource;
	unsigned int m_layer;
	float m_fadeIn, m_fadeOut;
	float m_start, m_length;
public:
		CEffect();
	~CEffect();
	void play(float time);
	virtual void init(void)=0;
	virtual void start(void)=0;
	virtual void deInit(void)=0;
	
	virtual int setParam(string name, float value)=0;
	virtual int setParam(string name, string value)=0;
	virtual int setParamModifier(string name, string expression)=0;
	// void setEventList(EventList *newEventList); // TODO 
	bool isPlaying(float time);
	
	void setResource(CResource *Resource);
};

#endif