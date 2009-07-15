#include "ResourceFilterMonoTone.h"
#include <iostream>
#include <cmath>
#include "Render.h"

#define ratio 0.25

using namespace std;
CResourceFilterMonoTone::CResourceFilterMonoTone(){
	this->m_numVertex = 32;
	m_numX = 1;
	m_numY = 1;
	m_hasCustomBlending=false;
	m_threshold = CPoint(0.5,0.5,0.5,0.5);
	m_clearBuffer = false;
	m_refreshInterval = 0.2;
}

void CResourceFilterMonoTone::play(float _time) {	
	float currentColor[4];
	static int renderWidth = m_Render->getWidth();
	static int renderHeight = m_Render->getHeight();
	static int numpixels = renderWidth * renderHeight * 4; // rgba
	static float origX = -renderWidth*0.5;
	static float origY = -renderHeight*0.5;
	float x, x2, y, y2;
	unsigned int i,j;
	unsigned char* pixel;
	
	
	// Set ortogonal view to 2,2 so we can put our points in -1,-1, etc...
	m_Render->orthoSet();
	// get current rendering color (for restoring it after)
	m_Render->getCurrentColor(currentColor);
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	// set the current vertex color
	m_Render->setColor(currColor);
	
	CPoint p;
	p.w*=this->m_alpha;
	
	static float t=0;
	static int count=0;
	if(_time-t>m_refreshInterval) {
		glReadPixels(0,0,renderWidth,renderHeight,GL_RGBA,GL_UNSIGNED_BYTE,this->m_framebuffer);
		t=_time;
		count++;
		count=count%3;
	}
	if(m_clearBuffer) {
		glClear(GL_COLOR_BUFFER_BIT);
	} else {
		// enable blending
		m_Render->enableBlend();
	}
	// play with the framebuffer data
	static float elapsedTime;
	elapsedTime = _time-this->m_startTime;
	
	CPoint currThres = m_threshold + (m_thresholdModif*elapsedTime);
	
	unsigned char accum;
	for(i=0; i!=numpixels; i+=4) {
		
		pixel  = this->m_framebuffer + i;
		accum = pixel[0] + pixel[1] + pixel[2];
		accum = accum>currThres.x ? 255 : 0;
		
		pixel[0] = accum;
		pixel[1] = accum;
		pixel[2] = accum;
		
	}
	
	
	
	// get it back to the framebuffer ;)
	glDrawPixels(renderWidth, renderHeight, GL_RGBA, GL_UNSIGNED_BYTE, this->m_framebuffer);
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	m_Render->disableBlend();
	
	// restore view
	m_Render->orthoUnset();
}

void CResourceFilterMonoTone::init() {
	
	// initialize the framebuffer area
	this->m_framebuffer = new unsigned char[(unsigned int)m_Render->getWidth() * (unsigned int)m_Render->getHeight() * 4]; // always assume RGBA
}

void CResourceFilterMonoTone::start() {
	
}

void CResourceFilterMonoTone::deInit(void) {
	delete []this->m_framebuffer;
}

string CResourceFilterMonoTone::getType(void) {
	return "CResourceFilterMonoTone";
}

void CResourceFilterMonoTone::setParam(string name, string value) {
	if(name=="clear") {
		m_clearBuffer = value=="yes" ? true : false;
	}
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
	if(name=="refresh") {
		m_refreshInterval = (float) atof(value.c_str());
	}
	if(name=="thres_r") {
		m_threshold.x = (float) atof(value.c_str());
	}
	if(name=="thres_g") {
		m_threshold.y = (float) atof(value.c_str());
	}
	if(name=="thres_b") {
		m_threshold.z = (float) atof(value.c_str());
	}
	if(name=="thres_a") {
		m_threshold.w = (float) atof(value.c_str());
	}
	if(name=="thres_modif_r") {
		m_thresholdModif.x = (float) atof(value.c_str());
	}
	if(name=="thres_modif_g") {
		m_thresholdModif.y = (float) atof(value.c_str());
	}
	if(name=="thres_modif_b") {
		m_thresholdModif.z = (float) atof(value.c_str());
	}
	if(name=="thres_modif_a") {
		m_thresholdModif.w = (float) atof(value.c_str());
	}
	
	if(name=="radio") {
		m_radio = (float) atof(value.c_str());
	}
	if(name=="num_vertex") {
		m_numVertex = (unsigned int) atoi(value.c_str());
	}
	if(name=="num_x") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numX = (tmp < RESOURCEFILTERMONOTONE_MAX_X-1 ? tmp : RESOURCEFILTERMONOTONE_MAX_X);
	}
	if(name=="num_y") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numY = (tmp < RESOURCEFILTERMONOTONE_MAX_Y-1 ? tmp : RESOURCEFILTERMONOTONE_MAX_Y);
	}
	if(name=="blending") {
		this->m_hasCustomBlending = true;
		this->m_renderBlendingPos = this->m_Render->getBlending(value);
	}
}
