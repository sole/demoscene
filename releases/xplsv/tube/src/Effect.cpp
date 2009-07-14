#include "Effect.h"
#include <iostream>
#include <cstdlib>
using namespace std;

CEffect::CEffect() {
	this->m_fadeIn = 0;
	this->m_fadeOut = 0;
	this->m_start = 0;
	this->m_length = 10000;
	this->m_alpha = 1;
	
	this->m_hasStarted = false;
	this->m_layer=0;
}
CEffect::~CEffect() {
}

void CEffect::play(float time) {
	if(!this->isPlaying(time))
		return;
	// if this has not been started yet...
	if(!m_hasStarted) {
		this->start();
	}
	// Update current attributes values
	updateEffectModifiers();
	
	// Calculate the modified alpha based on current time and fadein & fadeout
	// -- TODO instead of using 1.0 as base alpha use one based on fft signal
	// Fade in
	if((time <= this->m_fadeIn + this->m_start) && (this->m_fadeIn!=0)) {
		this->m_alpha = time / (this->m_fadeIn + this->m_start)* 1.0;
	} else if((time >= this->m_start + this->m_length - this->m_fadeOut) && (this->m_fadeOut!=0)) {
		this->m_alpha = (this->m_start + this->m_length -this->m_fadeOut)/(time);
	} else if(time > this->m_start + this->m_length) {
		this->m_alpha = 0;
	} else  {
		this->m_alpha = 1.0;
	}
	
	// apply it...
	this->m_Resource->setAlpha(this->m_alpha);
	// Play !
	this->m_Resource->play(time);
	
}

bool CEffect::isPlaying(float time) {
	if(
	   (this->m_start <= time)
	   &&
	   (time < this->m_start+this->m_length )
	   ) {
		return true;
	} else {
		return false;
	}
}

void CEffect::init(void) {
	//this->m_Resource->init();
	// TODO think about this
}

void CEffect::start(void) {
	// First time this function gets executed it'll set the hasStarted to true
	this->m_hasStarted = true;
	
	// Before starting, we will send all attributes to our resource
	for(map<string, string>::iterator i = m_attributes.begin();
		i != m_attributes.end();
		i++) {
		/*
		 NOTE:
		 So an iterator over a map<string, string> is basically a pointer to a pair<string,string>. 
		 Pairs have two members, first and second, which in this case correspond to "key" and "value", or some instance of string and the associated string.
		 */
		this->m_Resource->setParam(i->first,i->second);
	}
	
	// start the resource
	this->m_Resource->setStartTime(this->m_start);
	this->m_Resource->setEndTime(this->m_start+this->m_length);
	this->m_Resource->start();
}

void CEffect::deInit(void) {

}


void CEffect::setParam(string name, string value) {
	this->m_Resource->setParam(name,value);
}

int CEffect::setParamModifier(string name, string expression) {
	// TODO
	return 0;
}

void CEffect::setResourceAttributeModifier(string attributeName, string expression) {
	// TODO would be nice to parse the expression here! so next time it would only be something like parsedExpression->eval()
	this->m_attributesModifiers[attributeName] = expression;
}

void CEffect::setResource(CResource *Resource) {
	this->m_Resource = Resource;
}

void CEffect::setFadeIn(float value) {
	this->m_fadeIn = value;
}

void CEffect::setFadeOut(float value) {
	this->m_fadeOut = value;
}

void CEffect::setStart(float value) {
	this->m_start = value;
}
float CEffect::getStart() {
	return this->m_start;
}

void CEffect::setLength(float value) {
	this->m_length = value;
}

void CEffect::setLayer(unsigned int layer) {
	this->m_layer = layer;
}

unsigned int CEffect::getLayer(void) {
	return this->m_layer;
}

void CEffect::setResourceAttribute(string attributeName, string attributeValue) {
	this->m_attributes[attributeName] = attributeValue;
	m_attributesValues[attributeName] = atof(attributeValue.c_str());
}

bool CEffect::hasStarted() {
	return this->m_hasStarted;
}

void CEffect::setFFT(float *pfFFT){
	this->m_pfFFT = pfFFT;
}

void CEffect::updateEffectModifiers(void) {
	float value;
	char temp[255];int j;
	for(j=0; j<10;j++) {
		sprintf(temp, "m#fft%d", j);
		//cout << "j " << j << " " << temp << " " << m_pfFFT[j] << endl;
		this->m_MathExpression.setVar(temp, this->m_pfFFT[j]);
	}
	this->m_MathExpression.setVar("m#fft", this->m_pfFFT[0]);
	
	for(map<string, string>::iterator i = m_attributesModifiers.begin();
		i != m_attributesModifiers.end();
		i++) {
			// Is there a modifier?
		if(i->second.length()>0 /* the value */) {
			// eval and update the final value
			this->m_MathExpression.setExpression(i->second);
			value = this->m_MathExpression.value();
			// save the value
			char temp[255];
			sprintf(temp, "%f", atof(m_attributes[i->first].c_str()) * value);
			this->m_Resource->setParam(i->first, temp);
		}
	}
}
