//: src:ResourceFilterFlipColors.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 3 april 2006  
// Declaration of CResourceFilterFlipColors class

#ifndef RESOURCEFILTERFLIPCOLORS_H
#define RESOURCEFILTERFLIPCOLORS_H

#include "Resource.h"
#include "Algebra.h"
#include "Texture.h"

#define RESOURCEFILTERFLIPCOLORS_MAX_X 1024
#define RESOURCEFILTERFLIPCOLORS_MAX_Y 768

class CResourceFilterFlipColors : public CResource {
private:
	// color
	CPoint m_Color;
	float m_radio;
	unsigned int m_numVertex;
	unsigned int m_numX;
	unsigned int m_numY;
	CTexture m_Texture;
	unsigned int m_texPos;
	
	// store here the framebuffer data
	unsigned char* m_framebuffer;
	
	// filter properties
	bool m_clearBuffer;
	CPoint m_threshold;
	CPoint m_thresholdModif;
	float m_refreshInterval;
	
	// the blending
	bool m_hasCustomBlending;
	unsigned int m_renderBlendingPos;	
	
public:
		CResourceFilterFlipColors();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif