#include "ResourcePsychoCircles.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "Render.h"

CResourcePsychoCircles::CResourcePsychoCircles(){
	this->m_numVertex = 32;
	m_numX = 1;
	m_numY = 1;
}
void CResourcePsychoCircles::drawCircle(CPoint center, float radio, unsigned int numVertex) {
	unsigned int i;
	float ang, anginc;
	anginc = 6.2831853 / float(numVertex);
	ang = 0;
	m_Render->beginShapePolygon();
	for(i=0; i<=numVertex; i++) { 
		m_Render->addVertex(center.x + radio*sin(ang), center.y + radio*cos(ang) );
		ang += anginc;
	}
	
	m_Render->endShape();
}

void CResourcePsychoCircles::play(float _time) {	
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
	
	CPoint c;
	CPoint ppos;
	float xpostemp;
	float stx = -1 + m_radio, sty = -1 + m_radio; // always adjusted to the viewport
	float lenx = 2 + m_radio*2, leny = lenx; ////2;
	for(unsigned int i=0; i<m_numX; i++) {
		xpostemp = stx + i*lenx/float(m_numX);
		for(unsigned int j=0; j<m_numY; j++) {
			if(j%2==0) {
				ppos.x=m_radio*2 + xpostemp;
			} else {
				ppos.x=xpostemp;
			}
			ppos.y = sty + j*leny/float(m_numY);
			drawCircle(c + ppos, m_radio, m_numVertex);
		}
	}
	
	// disable transparency
	m_Render->disableBlend();
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// restore view
	m_Render->orthoUnset();
}

void CResourcePsychoCircles::init() {
}

void CResourcePsychoCircles::start() {
	
}

void CResourcePsychoCircles::deInit(void) {
	
}

string CResourcePsychoCircles::getType(void) {
	return "CResourcePsychoCircles";
}

/*
 int CResourcePsychoCircles::setAttribute(string name, string value) {
	 
	 return 0;
 }*/

/*int CResourcePsychoCircles::setAttribute(string name, float value) {
return 0;
}*/

/*
 int CResourcePsychoCircles::setParam(string name, float value) {
	 return 0;
 }*/
void CResourcePsychoCircles::setParam(string name, string value) {
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
	if(name=="radio") {
		m_radio = (float) atof(value.c_str());
	}
	if(name=="num_vertex") {
		m_numVertex = (unsigned int) atoi(value.c_str());
	}
	if(name=="num_x") {
		m_numX = (unsigned int) atoi(value.c_str());
	}
	if(name=="num_y") {
		m_numY = (unsigned int) atoi(value.c_str());
	}
}
/*
 int CResourcePsychoCircles::parseAttributes(TiXmlElement* node) {
	 return 0;
 }*/