//: src:ResourceMotionBlur.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 7 august 2005  
// Declaration of CResourceMotionBlur class

#ifndef RESOURCEMOTIONBLUR_H
#define RESOURCEMOTIONBLUR_H

#include "Resource.h"
#include "Texture.h"

class CResourceMotionBlur : public CResource {
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
	
public:
		CResourceMotionBlur();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif