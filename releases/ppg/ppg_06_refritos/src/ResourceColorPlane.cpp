#include "ResourceColorPlane.h"
#include "Render.h"
#include <iostream>
using namespace std;

void CResourceColorPlane::play(float _time) {	
	float currentColor[4];
	
	// Set ortogonal view to 2,2 so we can put our points in -1,-1, etc...
	m_Render->orthoSet(2,2);
	// get current rendering color (for restoring it after)
	m_Render->getCurrentColor(currentColor);
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	// set the current vertex color
	m_Render->setColor(currColor);
	// enable blending
	m_Render->enableBlend();
	doCustomBlending();
	
	// Draw a plane using the whole view -> 4 vertex... etc
	m_Render->beginShapeQuads();
		m_Render->addVertex(-1,-1);
		m_Render->addVertex(1,-1);
		m_Render->addVertex(1,1);
		m_Render->addVertex(-1,1);
	m_Render->endShape();
	
	// disable transparency
	m_Render->disableBlend();
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// restore view
	m_Render->orthoUnset();
}

void CResourceColorPlane::init() {
}

void CResourceColorPlane::start() {
	
}

void CResourceColorPlane::deInit(void) {
	
}

string CResourceColorPlane::getType(void) {
	return "CResourceColorPlane";
}

/*
int CResourceColorPlane::setAttribute(string name, string value) {
	
	return 0;
}*/

/*int CResourceColorPlane::setAttribute(string name, float value) {
return 0;
}*/

/*
int CResourceColorPlane::setParam(string name, float value) {
	return 0;
}*/
void CResourceColorPlane::setParam(string name, string value) {
	if(name=="r") {
		m_Color.x = (float) atof(value.c_str());
	}
	if(name=="g") {
		m_Color.y = (float) atof(value.c_str());
	}
	if(name=="b") {
		m_Color.z = (float) atof(value.c_str());
	}
	if(name=="a") {
		m_Color.w = (float) atof(value.c_str());
	}
	if(name=="blending") {
		this->m_hasCustomBlending = true;
		this->m_renderBlendingPos = this->m_Render->getBlending(value);
	}
}
/*
int CResourceColorPlane::parseAttributes(TiXmlElement* node) {
	return 0;
}*/