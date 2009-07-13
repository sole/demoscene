#include "EffectClearBuffer.h"
#include <strings.h>
#include "Demo.h"
extern Demo* miDemo;

void EffectClearBuffer::play(float _time) {
	glClearColor(canvasColor.x,canvasColor.y,canvasColor.z,canvasColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void EffectClearBuffer::init() {
	
}

void EffectClearBuffer::start() {
	
}

void EffectClearBuffer::deInit(void) {
	
}

const char* EffectClearBuffer::getEffectType(void) {
	return "EffectClearBuffer";
}

int EffectClearBuffer::setParam(char *paramName, char *attribName, float value) {	
	// Setting the COLOR
	if(strcasecmp(paramName,"color")==0) {
		if(strcasecmp(attribName,"r")==0) {
			this->canvasColor.x=value;
		}
		if(strcasecmp(attribName,"g")==0) {
			this->canvasColor.y=value;
		}
		if(strcasecmp(attribName,"b")==0) {
			this->canvasColor.z=value;
		}
		if(strcasecmp(attribName,"a")==0) {
			this->canvasColor.w=value;
		}
	}	
	return 0;
}
