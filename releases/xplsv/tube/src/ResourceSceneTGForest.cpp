#include "ResourceSceneTGForest.h"
#include <iostream>
using namespace std;
#include "Render.h"
#include "Demo.h"

CResourceSceneTGForest::CResourceSceneTGForest() {
	
		
	
	m_resCamera.SetFar(1,10000);
}

void CResourceSceneTGForest::play(float _time) {
	// save prev projection matrix
	m_Render->setProjectionMatrix();
	m_Render->pushMatrix();
	m_Render->loadIdentity();
	
	m_Render->setModelMatrix();
	m_Render->pushMatrix();
	m_Render->loadIdentity();
	
	// calculate new camera position
	m_resCamera.Place(CPoint(100,0,100), CPoint(0,0,0), CPoint(0,1,0));
	// apply to the scene
	m_resCamera.toOGL();
	// and assign to m_Render
	m_Render->setActiveCamera(&m_resCamera);
	
	// play the snow
	m_resPSSnow->play(_time);

	m_Render->setModelMatrix();
	m_Render->popMatrix();
	
	// restore prev projection matrix
	m_Render->setProjectionMatrix();
	m_Render->popMatrix();
}

void CResourceSceneTGForest::init() {
	
	// init and configure the resources
	
	
}

void CResourceSceneTGForest::start() {
	m_resPSSnow = m_Demo->getResourceById("snow");
}

void CResourceSceneTGForest::deInit(void) {
	
}

string CResourceSceneTGForest::getType(void) {
	return "CResourceSceneTGForest";
}

void CResourceSceneTGForest::setParam(string name, string value) {
	
}
