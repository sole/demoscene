//: src:ResourcePsychoPlasma.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 11 august 2005  
// Declaration of CResourcePsychoPlasma class

#ifndef RESOURCEPSYCHOPLASMA_H
#define RESOURCEPSYCHOPLASMA_H

#include "Resource.h"
#include "Algebra.h"

#define RESOURCEPSYCHOPLASMA_MAX_X 100
#define RESOURCEPSYCHOPLASMA_MAX_Y 100

class CResourcePsychoPlasma : public CResource {
private:
	// color
	CPoint m_Color;
	float m_radio;
	unsigned int m_numVertex;
	unsigned int m_numX;
	unsigned int m_numY;
	
	// the plasma precalc...
	int m_cosinus[256];
	
	
public:
		CResourcePsychoPlasma();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif
