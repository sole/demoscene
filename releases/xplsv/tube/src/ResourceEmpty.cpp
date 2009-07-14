#include "ResourceEmpty.h"
#include "Render.h"

void CResourceEmpty::play(float _time) {	
	this->m_Render->clear(RENDER_CLEAR_COLOR);
}

void CResourceEmpty::init() {
}

void CResourceEmpty::start() {
	
}

void CResourceEmpty::deInit(void) {
	
}

string CResourceEmpty::getType(void) {
	return "CResourceEmpty";
}

void CResourceEmpty::setParam(string name, string value) {
	
}
