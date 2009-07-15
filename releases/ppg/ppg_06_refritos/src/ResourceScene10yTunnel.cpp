#include "ResourceScene10yTunnel.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "Render.h"

CResourceScene10yTunnel::CResourceScene10yTunnel(){
	m_t0 = 0;
	
	m_fadeout = 1;
	this->m_hasCustomBlending = false;
	m_numCubes = 50;
	this->m_maxSize = 1;
}



void CResourceScene10yTunnel::play(float _time) {	
	//glEnable(GL_DEPTH_TEST);
	//glClear(GL_DEPTH_BUFFER_BIT);
	//m_Render->enableDepthMask();
	// set transparency
	m_Render->enableBlend();
	
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
	
	// temp set view
	CCamera myCam;
	
	
	m_Render->setProjectionMatrix();
	m_Render->pushMatrix();
	m_Render->loadIdentity();
	//myCam.SetLook(120,1,0);
	float incFov=0;
	float bass = this->getFFTAt(0);
	//cout << "BASSSSSSSS" << bass << endl;
	if(bass>0.55) {
		incFov+=bass;
	}
	myCam.SetFar(1,200+incFov); // far con la FFT
	myCam.SetFov(100);
	float time_multiplied = _time * 3;
	float dist = 80+ 20*sin(time_multiplied);
	float height = 0;//dist*cos(_time);
	float period = _time;
	
	
	//myCam.Place(CPoint(dist*sin(period),height,dist*cos(period)), CPoint(0,0,0), CPoint(0,1,0));
	//myCam.Place(CPoint(5,1,5), CPoint(0,0,0), CPoint(0,1,0));
	if(_time-m_t0 > m_interval) {
		
		if(m_followPath) {
			m_tunnelPath.getValue();
			m_tunnelPath.getValue();
			m_tunnelPath.getValue();	
			m_tunnelPath.getValue();
			m_tunnelPath.getValue();
			m_tunnelPath.getValue();
			m_tunnelPath.getValue();
			m_tunnelPath.getValue();
			m_tunnelPath.getValue();
		}
		m_pointCurrPos = m_tunnelPath.getValue();
		m_t0 = _time;
		m_pointCurrPos.y += bass*20;
	}
	CPoint camLook, camUp;
	camUp = CPoint(0,1,0);
	//
	
	if(m_followPath) {
		myCam.Place(m_pointCurrPos, camLook, CPoint(0,1,0));
	} else {
		camLook = m_tunnelPath.getValueAt(m_tunnelPath.getPosition()+2);
		myCam.Place(CPoint(dist*sin(time_multiplied),0,dist*cos(time_multiplied)), CPoint(0,0,0), CPoint(0,1,0));
	}
	
	
	myCam.toOGL();
	
	//m_Render->setActiveCamera(&myCam);
	
	
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	//cout << currColor.w << endl;
	// set the current vertex color
	m_Render->setColor(currColor);
	
	// draw & update
	unsigned int i;
	
	CPoint vup, vright;
	
	
	//m_Render->setColor(0.6,0.6,1,0.035);
	//m_Render->setColor(1,1,1,1);
	float decay, s=0.3;
	unsigned int numval = m_tunnelPath.getNumValues();
	m_Render->setLineWidth(2);
	m_Render->setPointSize(2);
	//m_Render->beginShapeLineStrip();
	m_Render->setModelMatrix();
	CPoint pos;
	for(i=0; i<numval;i++) {
		//m_Render->addVertex(m_tunnelPath.getValueAt(i));
		//m_tunnelPath.getValueAt(i).write();
		m_Render->pushMatrix();
		pos = m_tunnelPath.getValueAt(i);
		
		m_Render->translate(pos.x, pos.y, pos.z);
		//m_Render->scale(s,s,s);
		//m_Render->pushMatrix();
		//m_Render->scale(s,s,s);
		m_Render->drawCube(false);
		//m_Render->popMatrix();
		m_Render->popMatrix();
	}
	//m_Render->endShape();
	
	//m_Render->beginShapePoints();
	//for(i=0;i<m_tunnelPath.getNumControlPoints();i++) {
	//	m_Render->addVertex(m_tunnelPath.getControlPoint(i));
	//}
	//m_Render->endShape();
	//m_Render->popMatrix();
	
	// temp set view
	m_Render->setProjectionMatrix();
	m_Render->popMatrix();
	
	
	m_Render->disableBlend();
	
	// glDisable(GL_DEPTH_TEST);
}

void CResourceScene10yTunnel::init() {	
/*	m_tunnelPath.addControlPoint(CPoint(0,0,0));
	m_tunnelPath.addControlPoint(CPoint(1,1,1));
	m_tunnelPath.addControlPoint(CPoint(1,1,-1));
	m_tunnelPath.addControlPoint(CPoint(-1,-1,-1));
	
	
	m_tunnelPath.addControlPoint(CPoint(-1,-1,1));
	m_tunnelPath.addControlPoint(CPoint(-1,1,1));
	m_tunnelPath.addControlPoint(CPoint(0,0,0));*/
	
	/*m_tunnelPath.addControlPoint(CPoint(4,4,4));
	m_tunnelPath.addControlPoint(CPoint(6,6,6));
	m_tunnelPath.addControlPoint(CPoint(7,7,7));
	*/
	/*
	m_tunnelPath.addControlPoint(CPoint(0,0,0)); // P
	m_tunnelPath.addControlPoint(CPoint(1,1,1)); // T
	m_tunnelPath.addControlPoint(CPoint(1,-1,1)); // T
	m_tunnelPath.addControlPoint(CPoint(-1,-1,-1)); // P
	
	m_tunnelPath.addControlPoint(CPoint(2,2,2)); // pto control
	m_tunnelPath.addControlPoint(CPoint(-1,1,1)); // tangente
	m_tunnelPath.addControlPoint(CPoint(0,0,0)); // pto control
	*/
	m_followPath = false;
	for(unsigned int i=0; i<m_numCubes; i++) {
		CPoint p;
		p.randomize(CPoint(50,50,50));
		m_tunnelPath.addControlPoint(p);
	}
	m_tunnelPath.setControlPoint(m_numCubes-1, m_tunnelPath.getControlPoint(0));
	m_tunnelPath.calculate();
	
	// m_tunnelPath.outputInfo();
}

void CResourceScene10yTunnel::start() {
	
}

void CResourceScene10yTunnel::deInit(void) {
	
}

string CResourceScene10yTunnel::getType(void) {
	return "CResourceScene10yTunnel";
}

void CResourceScene10yTunnel::setParam(string name, string value) {
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
	
	if(name=="fadeout") {
		m_fadeout = (float) atof(value.c_str());
	}
	if(name=="interval") {
		m_interval = (float) atof(value.c_str());
	}
	
	if(name=="follow") {
		if(value == "true") {
			this->m_followPath = true;
		} else {
			this->m_followPath = false;
		}
	}
	
	if(name=="num_cubes") {
		unsigned int tmp_num = (unsigned int) atoi(value.c_str());
		m_numCubes = tmp_num;
	}
	
	if(name=="num_steps") {
		unsigned int tmp_num = (unsigned int) atoi(value.c_str());
		m_tunnelPath.setNumSteps(tmp_num);
	}
	
	if(name=="max_size") {
		m_maxSize = (float) atof(value.c_str());
	}
	
	if(name=="blending") {
		this->m_hasCustomBlending = true;
		this->m_renderBlendingPos = this->m_Render->getBlending(value);
	}
		
}