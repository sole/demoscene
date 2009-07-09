#include "Effect.h"


Effect::Effect(){
}
Effect::~Effect(){
}


void Effect::setMusicParams(int pattern,int row)
{
	_pattern = pattern;
	_row = row;
	eventFlag = 0;
}

void Effect::pauseEffect(void){};
void Effect::continueEffect(void){};

void Effect::setEventFlag(int eventType)
{
	eventFlag |= eventType;
}

void Effect::resetEventFlag(int eventType)
{
	eventFlag = eventFlag & ~eventType;
}

int Effect::checkEventFlag(int eventType)
{
	return eventFlag & eventType;
}
