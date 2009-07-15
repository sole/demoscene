#include "ResourceScene10yCubeGen.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "Render.h"

CResourceScene10yCubeGen::CResourceScene10yCubeGen(){
	m_numCubes = 1000;
	m_fadeout = 1;
	this->m_hasCustomBlending = false;
	this->m_origin.x = 0;
	this->m_origin.y = 0;
	this->m_origin.z = 0;
	
	this->m_velocity = CPoint(1,10,1);
	this->m_maxSize = 1;
	
	this->m_t0 = 0;
}

inline void CResourceScene10yCubeGen::initCube(CPoint *p, CPoint *v_speed, CPoint *v_rotation, CPoint *v_color) {
	////float marginx, marginy, marginz;
	static float invrandmax = 1.0/RAND_MAX;
		
	//marginx = marginy = marginz = 1;
	
	p->x = m_origin.x/* + rand()*invrandmax*marginx*/;
	p->y = m_origin.y /*+ rand()*invrandmax*marginy*/;
	p->z = m_origin.z /*+ rand()*invrandmax*marginz*/;
	
	p->w = rand()*invrandmax*m_maxSize;
	
	v_speed->x = (rand() - rand())*invrandmax* m_velocity.x;// - rand()*invrandmax/10000;
	v_speed->y = rand()*invrandmax* m_velocity.y;//m_velocity.y - rand()*invrandmax/10000;
	v_speed->z = (rand() - rand())*invrandmax* m_velocity.z;//m_velocity.z - rand()*invrandmax/10000;
		
	v_rotation->x = (rand()-rand())*invrandmax;
	v_rotation->y = (rand()-rand())*invrandmax;
	v_rotation->z = (rand()-rand())*invrandmax;
	
	/*v_color->x = rand()*invrandmax;
	v_color->y = rand()*invrandmax;
	v_color->z = rand()*invrandmax;*/
	int decider = (int)(rand()*invrandmax*6);
	
	switch(decider) {
		case 0:
			v_color->x=0.66; v_color->y=0; v_color->z=0.66; break; // magenta
		case 1:
			v_color->x=0; v_color->y=0.66; v_color->z=0.66; break; // cyan
		case 2: 
			v_color->x=0.66; v_color->y=0.66; v_color->z=0.66; break; // gris
		case 3: 
			v_color->x=1; v_color->y=0.33; v_color->z=0.33; break; // rojo
		case 4: 
			v_color->x=0.33; v_color->y=1; v_color->z=0.33; break; // verde
		case 5: 
			v_color->x=1; v_color->y=1; v_color->z=0.33; break; // amarillo
			
			
	}
}



void CResourceScene10yCubeGen::play(float _time) {	
	
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	//m_Render->enableDepthMask();
	// set transparency
	//m_Render->enableBlend();
	
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
	//cout << "hi there"<<endl;
	// temp set view
	CCamera myCam;
	
	
	m_Render->setProjectionMatrix();
	m_Render->pushMatrix();
	m_Render->loadIdentity();
	//myCam.SetLook(120,1,0);
	myCam.SetFar(1,10000);
	//myCam.SetFov(30);
	//myCam.Place(CPoint(100*sin(_time),0,100*cos(_time)), CPoint(0,0,0), CPoint(0,1,0));
	float dist = 20 /*+ 10*sin(_time)*/;
	float height = 10 + (_time - this->m_startTime)*10;
	myCam.Place(CPoint(dist*sin(_time),height,dist*cos(_time)), CPoint(0,0,0), CPoint(0,1,0));
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
	float t_elapsed = _time - m_t0;

	CPoint vup, vright;
	m_Render->setModelMatrix();
	
	float decay, s;
	for(i=0; i<m_numCubes;i++) {
		//cout << m_cubesList[i].x << " " << m_cubesList[i].y << " " << m_cubesList[i].z  << " " << m_cubesList[i].w<< endl;
		//drawCube(m_cubesList[i].x, m_cubesList[i].y, m_cubesList[i].z, m_cubesList[i].w*m_maxSize, vup, vright);
		// decrease the remaining amount of life of this particle
		m_Render->pushMatrix();
		s = this->m_maxSize*(0.1+m_cubesList[i].y*0.02);
		
		m_Render->translate(m_cubesList[i].x,m_cubesList[i].y,m_cubesList[i].z);
		m_Render->scale(s,s,s );
		m_Render->rotate((_time-this->m_startTime)*120,m_rotateList[i].x, m_rotateList[i].y, m_rotateList[i].z);
		m_Render->setColor(m_colorList[i].x, m_colorList[i].y, m_colorList[i].z, 1);
		m_Render->drawCube(false);
		decay = t_elapsed*m_fadeout;
		m_cubesList[i].w -= decay;
		m_speedList[i].y -= decay;
		//if(m_cubesList[i].w <=0 ) {
		if(m_cubesList[i].y<=0) {
			initCube(&m_cubesList[i], &m_speedList[i], &m_rotateList[i], &m_colorList[i]);
		}
		m_Render->popMatrix();
		
		m_cubesList[i].x+= t_elapsed * m_speedList[i].x;
		m_cubesList[i].y+= t_elapsed * m_speedList[i].y;
		m_cubesList[i].z+= t_elapsed * m_speedList[i].z;
	}
	
	// temp set view
	m_Render->setProjectionMatrix();
	m_Render->popMatrix();
	
	
	// Disable blending and reenable zbuffer writing
	m_Render->disableBlend();
		
	// And update the time
	m_t0 = _time;
	glDisable(GL_DEPTH_TEST);
}

void CResourceScene10yCubeGen::init() {	
	// Init the cubes m_cubesList
	unsigned int i;
	for(i=0; i<m_numCubes; i++) {
		CPoint p, v_speed, v_rotation, v_color;
		initCube(&p, &v_speed, &v_rotation, &v_color);
		m_cubesList.push_back(p);
		m_speedList.push_back(v_speed);
		m_rotateList.push_back(v_rotation);
		m_colorList.push_back(v_color);
	}
}

void CResourceScene10yCubeGen::start() {
	
}

void CResourceScene10yCubeGen::deInit(void) {
	
}

string CResourceScene10yCubeGen::getType(void) {
	return "CResourceScene10yCubeGen";
}

void CResourceScene10yCubeGen::setParam(string name, string value) {
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
			unsigned int i;
			for(i=m_numCubes; i<=tmp_num; i++) {
				CPoint p,q,v,color;
				initCube(&p, &q, &v, &color);
				m_cubesList.push_back(p);
				m_speedList.push_back(q);
				m_rotateList.push_back(v);
				m_colorList.push_back(color);
			}
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