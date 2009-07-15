#include "ResourceGeneric.h"

#include "Render.h"

void CResourceGeneric::play(float _time) {	
	this->m_Render->clear(RENDER_CLEAR_COLOR);
}

void CResourceGeneric::init() {
}

void CResourceGeneric::start() {
	
}

void CResourceGeneric::deInit(void) {
	
}

string CResourceGeneric::getType(void) {
	return "CResourceGeneric";
}

void CResourceGeneric::setParam(string name, string value) {
	
}