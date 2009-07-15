//: src:ResourceScene10yCubeNest.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 10 july 2006  
// Declaration of CResourceScene10yCubeNest class

#ifndef RESOURCESCENE10YCUBENEST_H
#define RESOURCESCENE10YCUBENEST_H

#include "Resource.h"
#include "Algebra.h"
#include <vector>
#include "Camera.h"


class CResourceScene10yCubeNest : public CResource {
private:
	// color
	CPoint m_Color;
	
	unsigned int m_numCubes;
	float m_fadeout;
	CPoint m_origin;
	CPoint m_velocity;
	
	// max size of each particle
	float m_maxSize;
	
	public:
		CResourceScene10yCubeNest();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif