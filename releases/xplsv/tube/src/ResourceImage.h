//: src:ResourceImage.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 1 august 2005  
// Declaration of CResourceImage class

#ifndef RESOURCEIMAGE_H
#define RESOURCEIMAGE_H

#include "Resource.h"
#include "Texture.h"

class CResourceImage : public CResource {
private:
	// color
	CPoint m_Color;
	// the texture
	string m_TextureFile;
	CTexture m_Texture;
	unsigned int m_texPos;
	float m_texWidth;
	float m_texHeight;
	float m_texImgWidth;
	float m_texImgHeight;
	
	bool m_stretch; // if this is active the texture size will be the viewport one
	
	// translation speed...
	float m_speedX;
	float m_speedY;
	
	// initial position
	float m_iniPosX;
	float m_iniPosY;
	
	// scale
	float m_scaleX;
	float m_scaleY;
	
	// the blending
	bool m_hasCustomBlending;
	unsigned int m_renderBlendingPos;
	
public:
	CResourceImage();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif