//: src:ResourceSotgPoints.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 11 august 2005  
// Declaration of CResourceSotgPoints class

#ifndef RESOURCESOTGPOINTS_H
#define RESOURCESOTGPOINTS_H

#include "Resource.h"
#include "Algebra.h"


class CResourceSotgPoints : public CResource {
private:
	// color
	CPoint m_Color;
	float m_radio;
	unsigned int m_numVertex;
	unsigned int m_numX;
	unsigned int m_numY;
	
	void drawCircle(CPoint center, float radio, unsigned int numVertex);
public:
		CResourceSotgPoints();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	//int setAttribute(string name, float value);
	//int setAttribute(string name, string value);
	//int setParam(string name, float value);
	void setParam(string name, string value);
	//int parseAttributes(TiXmlElement* node);
};

#endif