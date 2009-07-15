//: src:ResourceColorPlane.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 30 july 2005  
// Declaration of CResourceColorPlane class

#ifndef RESOURCECOLORPLANE_H
#define RESOURCECOLORPLANE_H

#include "Resource.h"
#include "Algebra.h"


class CResourceColorPlane : public CResource {
private:
	// color
	CPoint m_Color;
public:
	//CResourceColorPlane();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	
	void setParam(string name, string value);
};

#endif
