//: src:Effect.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 30 july 2005  
// Declaration of CEffect class

#ifndef EFFECT_H
#define EFFECT_H

#include "Resource.h"
#include "MathExpression.h"

#include <string>
#include <map>
#include <iterator>
using namespace std;

class CEffect {
protected:
	// TODO EventList *myEventList; // i think this should go inside an effect
	CResource* m_Resource;
	
	// Si se modifica (tiene modificador) entonces es float y es seguro utilizar el valor inicial asumiendo que es un valor numerico
	map<string, string> m_attributes; // this will hold the initial attributes values
	map<string, string> m_attributesModifiers; // this holds the modifiers for the resource when playing this effect
	map<string, float> m_attributesValues; // calculated values for the attributes
	
	void updateEffectModifiers(void);
	MathExpression m_MathExpression;
	
	unsigned int m_layer;
	float m_fadeIn, m_fadeOut;
	float m_start, m_length;
	float m_alpha;
	bool m_hasStarted;
	float *m_pfFFT; // pointer to an array of float values corresponding to a FFT representation of current sound
public:
	CEffect();
	~CEffect();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	
	//int setParam(string name, float value);
	void setParam(string name, string value);
	int setParamModifier(string name, string expression);
	// void setEventList(EventList *newEventList); // TODO 
	bool isPlaying(float time);
	bool hasStarted();
	
	// setters/no getters most probably...
	void setResource(CResource *Resource);
	void setFadeIn(float value);
	void setFadeOut(float value);
	void setStart(float value);
	float getStart();
	void setLength(float value);
	void setLayer(unsigned int layer);
	unsigned int getLayer(void);
	
	void setResourceAttribute(string attributeName, string attributeValue);
	void setResourceAttributeModifier(string attributeName, string expression);
	
	void setFFT(float *pfFFT);
};

#endif