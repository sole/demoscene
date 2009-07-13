#include "Scene.h"
#include <string.h>
#include <stdlib.h>

Scene::Scene(){
}
Scene::~Scene(){
}


void Scene::setMusicParams(int pattern,int row)
{
	_pattern = pattern;
	_row = row;

}

void Scene::setSceneName(const char *name) {

	this->sceneName = (char*) malloc(sizeof(char*)*strlen(name));
	strcpy(this->sceneName,name);
}

const char* Scene::getSceneType(void) {
	return "Scene";
}


const char* Scene::getSceneName(void) {
	return "Untitled Scene";
}

void Scene::initEffectsList(int numEffects) {
	this->numEffects = numEffects;
	this->lastEffect = 0;
	this->effectsList = (pEffect *) malloc (numEffects * sizeof(pEffect *));
}

int Scene::addEffect2List(pEffect newEffect) {
	int index;

	index=this->lastEffect;
	this->effectsList[index] = newEffect;	
	this->lastEffect++;
	return index;
}

void Scene::setNumEffects(unsigned int num) {
	this->numEffects=num;
}

void Scene::initEffect(int index) {
	this->effectsList[index]->init();
}
