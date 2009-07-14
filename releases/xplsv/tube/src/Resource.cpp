#include "Resource.h"
#include "Render.h"

CResource::CResource(){
	this->m_type="Generic Resource";
	this->m_id="";
	// Set a default alpha so all resources are visible from the beginning!
	this->m_alpha=1;
	this->m_hasCustomBlending = false;
}

CResource::~CResource(){
}

string CResource::getType(void) {
	return this->m_type;
}

void CResource::setId(string id) {
	this->m_id = id;
}

string CResource::getId(void) {
	return this->m_id;
}

void CResource::setRenderer(CRender* render) {
	this->m_Render = render;
}

void CResource::setDemo(CDemo* demo) {
	this->m_Demo = demo;
}

void CResource::setAlpha(float alpha) {
	this->m_alpha = alpha;
}
void CResource::setStartTime(float startTime) {
	this->m_startTime = startTime;
}
void CResource::setEndTime(float endTime) {
	this->m_endTime = endTime;
}
void CResource::setCustomBlending(int blendingPos) {
	if(blendingPos<0) {
		this->m_hasCustomBlending=false;
	} else {
		this->m_renderBlendingPos = (unsigned int) blendingPos;
	}
}
void CResource::doCustomBlending() {
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
}