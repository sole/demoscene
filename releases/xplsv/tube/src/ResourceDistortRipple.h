//: src:ResourceDistortRipple.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 7 august 2005  
// Declaration of CResourceDistortRipple class

#ifndef RESOURCEDISTORTRIPPLE_H
#define RESOURCEDISTORTRIPPLE_H

#include "Resource.h"
#include "Texture.h"

#define RESOURCEDISTORTRIPPLE_MAX_X 10
#define RESOURCEDISTORTRIPPLE_MAX_Y 10

class CResourceDistortRipple : public CResource {
private:
	// color
	CPoint m_Color;
	
	// the texture
	unsigned int textureIndex;
	CTexture m_Texture;
	unsigned int m_texPos;
	float m_texWidth;
	float m_texHeight;
	
	// should i delete the previous buffer?
	bool m_cleanBuffer;
	
	// scale increments on x and y
	float m_scaleincx, m_scaleincy;
	
	// the blending
	bool m_hasCustomBlending;
	unsigned int m_renderBlendingPos;
	
	// num of intervals
	unsigned int m_numX, m_numY;
	float m_radioX, m_radioY; // radio for distort on X or Y
	float m_periodX, m_periodY; // period on X or Y
	
public:
		CResourceDistortRipple();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif