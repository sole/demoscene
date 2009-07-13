#include "Effect.h"
#include <stdlib.h>
#include <string.h>

Effect::Effect(){
}
Effect::~Effect(){
}

const char* Effect::getEffectType(void) {
	return "Generic Effect";
}


void Effect::setEventList(EventList *newEventList) {
	this->myEventList=newEventList;
}

short Effect::isPlaying(float _time) {
	if(this->myEventList!=NULL) {
		short myPos = this->myEventList->isEventActive(_time);
		if(myPos!=-1)
			return myPos;
		else
			return -1;
	} else {
		return -1;
	}
}

void Effect::setName(char *name) {
	strcpy(this->name,name);
}

char *Effect::getName(void) {
	return this->name;
}
