#include "ResourceScene10yCubeNest.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "Render.h"

CResourceScene10yCubeNest::CResourceScene10yCubeNest(){
	m_numCubes = 1000;
	m_fadeout = 1;
	this->m_hasCustomBlending = false;
	this->m_origin.x = 0;
	this->m_origin.y = 0;
	this->m_origin.z = 0;
	
	this->m_velocity = CPoint(1,10,1);
	this->m_maxSize = 1;
}



void CResourceScene10yCubeNest::play(float _time) {	
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
	
	m_Render->setLineWidth(0.8);
	m_Render->setProjectionMatrix();
	m_Render->pushMatrix();
	m_Render->loadIdentity();
	//myCam.SetLook(120,1,0);
	myCam.SetFar(1,10000);
	//myCam.SetFov(30);
	//myCam.Place(CPoint(100*sin(_time),0,100*cos(_time)), CPoint(0,0,0), CPoint(0,1,0));
	float dist = 50 + 20*sin(_time);
	float height = dist*cos(_time);
	float period = _time * 4;
	myCam.Place(CPoint(dist*sin(period),height,dist*cos(period)), CPoint(0,0,0), CPoint(0,1,0));
	//myCam.Place(CPoint(30,10,30), CPoint(0,0,0), CPoint(0,1,0));
	myCam.toOGL();
	
	//m_Render->setActiveCamera(&myCam);
	
	
	//m_Render->auxAxis();

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
	float decay, s=0.1;
	for(i=0; i<m_numCubes;i++) {
		m_Render->setModelMatrix();
		m_Render->pushMatrix();
		
		s+=0.25;
		//m_Render->translate(20+10*sin(_time+i*5),0,20+10*cos(_time+i*5));
		m_Render->scale(s,s,s);
		m_Render->rotate(i*(20+10*sin(_time)) + (_time-m_startTime)*80, i*i,i,-i);
		m_Render->drawCube(true);
		
		m_Render->setModelMatrix();
		m_Render->popMatrix();
	}
	//m_Render->popMatrix();
	
	// temp set view
	m_Render->setProjectionMatrix();
	m_Render->popMatrix();
	
	
	m_Render->disableBlend();
		
	glDisable(GL_DEPTH_TEST);
}

void CResourceScene10yCubeNest::init() {	
	
}

void CResourceScene10yCubeNest::start() {
	
}

void CResourceScene10yCubeNest::deInit(void) {
	
}

string CResourceScene10yCubeNest::getType(void) {
	return "CResourceScene10yCubeNest";
}

void CResourceScene10yCubeNest::setParam(string name, string value) {
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
	
	if(name=="num_cubes") {
		unsigned int tmp_num = (unsigned int) atoi(value.c_str());
		// if more cubes than current ones are requested, allocate extra particles
		if(m_numCubes<tmp_num) {
			/*unsigned int i;
			for(i=m_numCubes; i<=tmp_num; i++) {
				CPoint p,q,v,color;
				initCube(&p, &q, &v, &color);
				m_cubesList.push_back(p);
				m_speedList.push_back(q);
				m_rotateList.push_back(v);
				m_colorList.push_back(color);
			}*/
		}
		m_numCubes = tmp_num;
	}
	
		
	if(name=="fadeout") {
		m_fadeout = (float) atof(value.c_str());
	}
	
		
	if(name=="max_size") {
		m_maxSize = (float) atof(value.c_str());
	}
	
	if(name=="blending") {
		this->m_hasCustomBlending = true;
		this->m_renderBlendingPos = this->m_Render->getBlending(value);
	}
	
	if(name=="origin_x") {
		m_origin.x = (float) atof(value.c_str());
	}
	if(name=="origin_y") {
		m_origin.y = (float) atof(value.c_str());
	}
	if(name=="origin_z") {
		m_origin.z = (float) atof(value.c_str());
	}
	if(name=="origin_w") {
		m_origin.w = (float) atof(value.c_str());
	}
	
	if(name=="velocity_x") {
		m_velocity.x = (float) atof(value.c_str());
	}
	if(name=="velocity_y") {
		m_velocity.y = (float) atof(value.c_str());
	}
	if(name=="velocity_z") {
		m_velocity.z = (float) atof(value.c_str());
	}
	if(name=="velocity_w") {
		m_velocity.w = (float) atof(value.c_str());
	}
	
}