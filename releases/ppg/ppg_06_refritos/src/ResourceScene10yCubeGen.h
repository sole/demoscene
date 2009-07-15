//: src:ResourceScene10yCubeGen.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 7 july 2006  
// Declaration of CResourceScene10yCubeGen class

#ifndef RESOURCESCENE10YCUBEGEN_H
#define RESOURCESCENE10YCUBEGEN_H

#include "Resource.h"
#include "Algebra.h"
#include <vector>
#include "Camera.h"


class CResourceScene10yCubeGen : public CResource {
private:
	// color
	CPoint m_Color;
	
	unsigned int m_numCubes;
	float m_fadeout;
	CPoint m_origin;
	CPoint m_velocity;
	std::vector <CPoint> m_cubesList;
	std::vector <CPoint> m_speedList;
	std::vector <CPoint> m_rotateList;
	std::vector <CPoint> m_colorList;
	
	// max size of each particle
	float m_maxSize;
		
	inline void initCube(CPoint *p, CPoint *v_speed, CPoint *v_rotation, CPoint* v_color);
public:
	CResourceScene10yCubeGen();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif