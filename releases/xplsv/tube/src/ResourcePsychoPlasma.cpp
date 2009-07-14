#include "ResourcePsychoPlasma.h"
#include <iostream>
#include <cmath>
#include "Render.h"

using namespace std;
CResourcePsychoPlasma::CResourcePsychoPlasma(){
	this->m_numVertex = 32;
	m_numX = 1;
	m_numY = 1;
}

void CResourcePsychoPlasma::play(float _time) {	
	float currentColor[4];
	float renderWidth = m_Render->getWidth();
	float renderHeight = m_Render->getHeight();
	float width= renderWidth*0.5, height = renderHeight*0.5;
	float quadincx = renderWidth / float(m_numX), quadincy= renderHeight/float(m_numY);
	static unsigned char p1,p2,p3,p4,t1,t2,t3,t4;
	float x, x2, y, y2;
	int col;
		
	static float xv[RESOURCEPSYCHOPLASMA_MAX_X];
	static float yv[RESOURCEPSYCHOPLASMA_MAX_Y];
	unsigned int i,j;
	
	
	for(i=0; i < m_numX+1; i++) {
		xv[i] = -width + i*quadincx;
	}
	for(j=0; j < m_numY+1; j++) {
		yv[j] = -height + j*quadincy ;
	}
	
	// Set ortogonal view to 2,2 so we can put our points in -1,-1, etc...
	m_Render->orthoSet();
	// get current rendering color (for restoring it after)
	m_Render->getCurrentColor(currentColor);
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	// set the current vertex color
	m_Render->setColor(currColor);
	// enable blending
	m_Render->enableBlend();
	CPoint p;
	p.w*=this->m_alpha;
	m_Render->beginShapeQuads();
	
	static float t=0;
	bool recalc = false;
	if(_time - t > 0.08) {
		recalc=true;
		t = _time;
	}
	
	for(i=0; i<m_numX; i++) {
		if(recalc) {
			t3=p3;
			t4=p4;
		}
		
		x = xv[i];
		x2 = xv[i+1];
		
		for(j=0; j<m_numY; j++) {
			
			y = yv[j];
			y2 = yv[j+1];
			
			col=m_cosinus[t1]+ m_cosinus[t2]+ m_cosinus[t3]+ m_cosinus[t4];
			// I'll separate the colour in components (r,g,b)
			//col = abs(col);
			p.x = (col & 0xF) /16.0;
			//p.y = col & 0xF0;
			p.z = (col & 0xF0) /96.0;
			
			if(recalc) {
				t3+=1;
				t4+=3;
			}
			
			p.x *= m_Color.x;
			p.y *= m_Color.y;
			p.z *= m_Color.z;
			p.w *= m_Color.w;
			
			m_Render->setColor(p);
			
			m_Render->addVertex(x,y);
			m_Render->addVertex(x2,y);
			m_Render->addVertex(x2, y2);
			m_Render->addVertex(x,y2);
			
		}
		if(recalc) {
			t1+=2;
			t2+=1;
		}
	}
	if(recalc) {
		p1+=1;
		p2-=2;
		p3+=3;
		p4-=4;
	}
	m_Render->endShape();

	// disable transparency
	m_Render->disableBlend();
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// restore view
	m_Render->orthoUnset();
}

void CResourcePsychoPlasma::init() {
	// precalc plasma table!!
	int i;
	for (i=0;i<256;i++)
		m_cosinus[i]=30*(cos(i*3.141592654/64.0));
}

void CResourcePsychoPlasma::start() {
	
}

void CResourcePsychoPlasma::deInit(void) {
	
}

string CResourcePsychoPlasma::getType(void) {
	return "CResourcePsychoPlasma";
}

void CResourcePsychoPlasma::setParam(string name, string value) {
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
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numX = (tmp < RESOURCEPSYCHOPLASMA_MAX_X-1 ? tmp : RESOURCEPSYCHOPLASMA_MAX_X);
	}
	if(name=="num_y") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numY = (tmp < RESOURCEPSYCHOPLASMA_MAX_Y-1 ? tmp : RESOURCEPSYCHOPLASMA_MAX_Y);
	}
}

