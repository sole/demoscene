#include "Effect.h"


Effect::Effect(){
}
Effect::~Effect(){
}


void Effect::setMusicParams(int pattern,int row)
{
	_pattern = pattern;
	_row = row;
}

void Effect::pauseEffect(void){};
void Effect::continueEffect(void){};
