#include "ResourceSotgPoints.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "Render.h"

CResourceSotgPoints::CResourceSotgPoints(){
	this->m_numVertex = 32;
	m_numX = 10;
	m_numY = 10;
	m_radio = 20;
	m_Color = CPoint(1,0,0,1);
}
void CResourceSotgPoints::drawCircle(CPoint center, float radio, unsigned int numVertex) {
	unsigned int i;
	float ang, anginc;
	anginc = 6.2831853 / float(numVertex);
	ang = 0;
	m_Render->beginShapePolygon();
	for(i=0; i<=numVertex; i++) { 
		m_Render->addVertex(center.x + radio*sin(ang), center.y + radio*cos(ang), center.z );
		ang += anginc;
	}
	
	m_Render->endShape();
}

void CResourceSotgPoints::play(float _time) {	
	float currentColor[4];
	CCamera myCam;
	
	m_Render->setProjectionMatrix();
	m_Render->pushMatrix();
	
	m_Render->setModelMatrix();
	m_Render->pushMatrix();
	m_Render->loadIdentity();
	
	// glDisable(GL_LIGHTING);
	
	
	
	float f = 1000;
	float f2 = 250;
	float f3 = 1;
	float tmult = _time*0.25;
	//myCam.SetLook(1,1,1);
	myCam.SetFar(1,10000);
	//myCam.SetPos(f2+f*sin(_time*0.5),3,/*f2*cos(_time)*/f2);
	myCam.Place(CPoint(f2*sin(tmult),f2*cos(tmult), 30), CPoint(0,0,0), CPoint(0,0,1));
	//myCam.Place(CPoint(100,0.1,100), CPoint(0,0,0), CPoint(0,1,0) );
		

	myCam.toOGL();
	
	// m_Render->auxAxis();
	
	//float fogColor[4];
//	fogColor[0] =0;
//	fogColor[1] = fogColor[2] = fogColor[3] = fogColor[0];
//	glEnable(GL_FOG);
//	glFogi(GL_FOG_MODE,    GL_EXP);
//	glFogf(GL_FOG_DENSITY, 5);
//	glFogf(GL_FOG_START, 8000);
//	glFogf(GL_FOG_END,   10000);
//	glFogfv(GL_FOG_COLOR, fogColor);
	
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

	float stx = -f + m_radio, sty = -f + m_radio; // always adjusted to the viewport
	//cout << stx << " " << sty << endl;
	float lenx = f*2 + m_radio*2, leny = lenx; ////2;
	for(unsigned int i=0; i<m_numX; i++) {
		xpostemp = stx + i*lenx/float(m_numX);
		for(unsigned int j=0; j<m_numY; j++) {
			if(j%2==0) {
				ppos.x=m_radio*2 + xpostemp;
			} else {
				ppos.x=xpostemp;
			}
			ppos.z = 20 * cos(_time + i + j);
			// cout << ppos.x << " " << ppos.y << " r " << m_radio << endl;
			ppos.y = sty + j*leny/float(m_numY);
			drawCircle(ppos, /*(sin(_time)+0.5) * m_radio - (ppos.y + ppos.x)*0.01*/ m_radio , m_numVertex);
		}
	}
	
	// disable transparency
	m_Render->disableBlend();
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// glDisable(GL_FOG);
	
	m_Render->setModelMatrix();
	m_Render->popMatrix();
	
	// restore view
	m_Render->setProjectionMatrix();
	m_Render->popMatrix();
}

void CResourceSotgPoints::init() {
}

void CResourceSotgPoints::start() {
	
}

void CResourceSotgPoints::deInit(void) {
	
}

string CResourceSotgPoints::getType(void) {
	return "CResourceSotgPoints";
}

/*
 int CResourceSotgPoints::setAttribute(string name, string value) {
	 
	 return 0;
 }*/

/*int CResourceSotgPoints::setAttribute(string name, float value) {
return 0;
}*/

/*
 int CResourceSotgPoints::setParam(string name, float value) {
	 return 0;
 }*/
void CResourceSotgPoints::setParam(string name, string value) {
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
 int CResourceSotgPoints::parseAttributes(TiXmlElement* node) {
	 return 0;
 }*/