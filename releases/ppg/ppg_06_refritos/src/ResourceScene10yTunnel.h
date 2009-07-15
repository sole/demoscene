//: src:ResourceScene10yTunnel.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 15 july 2006  
// Declaration of CResourceScene10yTunnel class

#ifndef RESOURCESCENE10YTUNNEL_H
#define RESOURCESCENE10YTUNNEL_H

#include "Resource.h"
#include "Algebra.h"
#include <vector>
#include "Camera.h"
#include "BezierPath.h"


class CResourceScene10yTunnel : public CResource {
private:
	// color
	CPoint m_Color;
	
	unsigned int m_numCubes;
	CBezierPath m_tunnelPath;
	unsigned int m_currPos;
	CPoint m_pointCurrPos;
	
	float m_interval;
	float m_fadeout;
	
	
	
	// max size of each particle
	float m_maxSize;
	
	// Camera follows the path, or not
	bool m_followPath;
	
	public:
		CResourceScene10yTunnel();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif