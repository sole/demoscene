//: src:ResourceDistortSine.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 14 august 2005  
// Declaration of CResourceDistortSine class

#ifndef RESOURCEDISTORTSINE_H
#define RESOURCEDISTORTSINE_H

#include "Resource.h"
#include "Texture.h"

#define RESOURCEDISTORTSINE_MAX_X 80
#define RESOURCEDISTORTSINE_MAX_Y 80

class CResourceDistortSine : public CResource {
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
	CPoint **m_VertArray;
	
public:
	CResourceDistortSine();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif