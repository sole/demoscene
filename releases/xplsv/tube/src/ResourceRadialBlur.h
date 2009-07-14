//: src:ResourceRadialBlur.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 6 august 2005  
// Declaration of CResourceRadialBlur class

#ifndef RESOURCERADIALBLUR_H
#define RESOURCERADIALBLUR_H

#include "Resource.h"
#include "Texture.h"

class CResourceRadialBlur : public CResource {
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
	
	// number of copies (how many times the texture will be put on screen again)
	unsigned int m_numCopies;
	
	// scale increments on x and y
	float m_scaleincx, m_scaleincy;
	
	// the blending
	bool m_hasCustomBlending;
	unsigned int m_renderBlendingPos;
	
	// should update the alpha (from 1 to 0) default yes
	bool m_updateAlpha;
	
public:
	CResourceRadialBlur();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif