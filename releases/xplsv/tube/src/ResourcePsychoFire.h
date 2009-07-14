//: src:ResourcePsychoFire.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 13 august 2005  
// Declaration of CResourcePsychoFire class

#ifndef RESOURCEPSYCHOFIRE_H
#define RESOURCEPSYCHOFIRE_H

#include "Resource.h"
#include "Algebra.h"

#define RESOURCEPSYCHOFIRE_MAX_X 100
#define RESOURCEPSYCHOFIRE_MAX_Y 100

class CResourcePsychoFire : public CResource {
private:
	// color
	CPoint m_Color;
	float m_radio;
	
	CPoint** m_vColor;
	
	unsigned int m_numX;
	unsigned int m_numY;
	unsigned int m_numBase; // how many lines of base fire...
	
public:
		CResourcePsychoFire();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif
