//: src:Resource.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 30 july 2005  
// Declaration of CResource class

#ifndef RESOURCE_H
#define RESOURCE_H

class CRender;
class CDemo;

#include "Algebra.h"
#include <string>
using namespace std;

class CResource {
protected:
	string m_id; // unique id for each resource
	string m_type; // type of the resource
	CRender* m_Render;
	CDemo*   m_Demo;
	
	float m_alpha; // can be used by resources if they want to apply the calculated alpha factor
	float m_startTime;
	float m_endTime;
	
	// the blending
	bool m_hasCustomBlending;
	unsigned int m_renderBlendingPos;
public:
	CResource();
	~CResource();
	virtual void play(float time)=0;
	virtual void init(void)=0;
	virtual void start(void)=0;
	virtual void deInit(void)=0;
	
	virtual	string getType(void);
	
	virtual void setParam(string name, string value)=0;
	
	void doCustomBlending();
	void setCustomBlending(int blendingPos);
	void setAlpha(float alpha);
	void setStartTime(float startTime);
	void setEndTime(float endTime);
	void setId(string id);
	string getId(void);
	void setRenderer(CRender *render);
	void setDemo(CDemo *demo);
};

#endif
