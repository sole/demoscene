#include "ResourceSceneTubeBeginning.h"
#include <iostream>
using namespace std;
#include "Render.h"
#include "Demo.h"
#include <string>

CResourceSceneTubeBeginning::CResourceSceneTubeBeginning() {
	
	m_resCamera.SetFar(1,10000);
	m_resCamera.SetFov(60);
}

void CResourceSceneTubeBeginning::play(float _time) {
	float elapsedTime = _time-m_startTime;
	float length = this->m_endTime - this->m_startTime;
	GLfloat LightAmbient[]= { 1.0f, 0.0,0.0, 1.0f };
	GLfloat LightDiffuse[]= { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat LightPosition[]= {0, 20, 0, 1.0f };
	GLfloat spot_direction[] = { 0,1,0 };
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	
	// save prev projection matrix
	m_Render->setProjectionMatrix();
	m_Render->pushMatrix();
	m_Render->loadIdentity();

	//m_Render->orthoSet(1,1);
	m_Render->setModelMatrix();
	m_Render->pushMatrix();
	float s=0.2;  
	//m_Render->loadIdentity();
	//m_Render->auxAxis();
	m_Render->scale(s,s,s); 
	
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);	
	
	glShadeModel(GL_SMOOTH);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	
	m_resCamera.Place(CPoint(0, 170, 0), CPoint(0,0,0), CPoint (0,0,-1));
	
	
	// apply to the scene
	m_resCamera.toOGL();
	// and assign to m_Render
	m_Render->setActiveCamera(&m_resCamera);
	
	// play the greetings object
	static float t=0, t2=0;
	static unsigned int offset_y=0, offset_x;
	char temp[255];
	
	
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	
	sprintf(temp, "%d", (int)(_time*m_speed.x));
	m_resOT->setParam("offset_x", temp);
	
	m_Render->translate(-90,0,0);
	m_resOT->play(_time);
	
	
	m_Render->setModelMatrix();
	m_Render->popMatrix();
	
	// restore prev projection matrix
	m_Render->setProjectionMatrix();
	m_Render->popMatrix();
	
	m_Render->orthoUnset();
	
	glShadeModel(GL_FLAT);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	}

void CResourceSceneTubeBeginning::init() {
	
}

void CResourceSceneTubeBeginning::start() {
	m_resOT = m_Demo->getResourceById("obj_credits");
}

void CResourceSceneTubeBeginning::deInit(void) {
	
}

string CResourceSceneTubeBeginning::getType(void) {
	return "CResourceSceneTubeBeginning";
}

void CResourceSceneTubeBeginning::setParam(string name, string value) {
	if(name=="bass") {
		m_bassLevel = (float) atof(value.c_str());
	}
	if(name=="speed_x") {
		m_speed.x = (float) atof(value.c_str());
	}
}
