#include "ResourceSceneTubeGreetings.h"
#include <iostream>
using namespace std;
#include "Render.h"
#include "Demo.h"
#include <string>

CResourceSceneTubeGreetings::CResourceSceneTubeGreetings() {
	
	
	
	m_resCamera.SetFar(1,10000);
	m_resCamera.SetFov(60);
}

void CResourceSceneTubeGreetings::play(float _time) {
	float elapsedTime = _time-m_startTime;
	float length = this->m_endTime - this->m_startTime;
	GLfloat LightAmbient[]= { 1.0f, 1.0,1.0, 1.0f };
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	//GLfloat LightPosition[]= { /*100*/200*sin(_time*2), -300, 200*cos(_time*2), 1.0f };
	GLfloat LightPosition[]= {-100,0, -100, 1.0f };
	GLfloat spot_direction[] = { 0,-1,0 };
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	
	// save prev projection matrix
	m_Render->setProjectionMatrix();
	m_Render->pushMatrix();
	m_Render->loadIdentity();
	
	m_Render->setModelMatrix();
	m_Render->pushMatrix();
	float s=0.04;  
	m_Render->loadIdentity();
	
	m_Render->scale(s,s,s); 
	
	//glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);	
	//glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glEnable(GL_LIGHT1);	
	
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	 m_resCamera.Place(CPoint(0,30,30), CPoint(-1,0,-1), CPoint (0,1,0));
	
	
	
	// apply to the scene
	m_resCamera.toOGL();
	// and assign to m_Render
	m_Render->setActiveCamera(&m_resCamera);
	
	// play the greetings object
	static float t=0, t2=0;
	static unsigned int offset_y=740, offset_x;
	char temp[255];
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	//if(_time-t2 > 0.03 ) {
		offset_y = 740 + elapsedTime*34; //+= (_time - t2) * 10;
		t2=_time;
		//offset_y+=2;
		sprintf(temp, "%d", offset_y);
		m_resOTGreetings->setParam("offset_y", temp);
	//} 
	
	sprintf(temp,"%f", 9.0f);
	m_resOTGreetings->setParam("origin_y", temp);
	m_resOTGreetings->play(_time);
	
	//m_Render->auxAxis();
	
	m_Render->setModelMatrix();
	m_Render->popMatrix();
	
	// restore prev projection matrix
	m_Render->setProjectionMatrix();
	m_Render->popMatrix();
	
	glShadeModel(GL_FLAT);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
}

void CResourceSceneTubeGreetings::init() {
	
}

void CResourceSceneTubeGreetings::start() {
	m_resOTGreetings = m_Demo->getResourceById("obj_greetings");
}

void CResourceSceneTubeGreetings::deInit(void) {
	
}

string CResourceSceneTubeGreetings::getType(void) {
	return "CResourceSceneTubeGreetings";
}

void CResourceSceneTubeGreetings::setParam(string name, string value) {
	if(name=="bass") {
		m_bassLevel = (float) atof(value.c_str());
	}
}
