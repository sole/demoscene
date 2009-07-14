//: src:ResourceImageSequence.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 15 august 2005  
// Declaration of CResourceImageSequence class

#ifndef RESOURCEIMAGESEQUENCE_H
#define RESOURCEIMAGESEQUENCE_H

#include "Resource.h"
#include "Texture.h"
#include <vector>

class CResourceImageSequence : public CResource {
private:
	// color
	CPoint m_Color;
	// the texture
	string m_TextureFile;
	CTexture m_Texture;
	unsigned int m_texPos;
	std::vector <unsigned int> m_texPosList;
	std::vector <std::string> m_texFilesList;
	std::string m_filesPath;
	float m_texWidth;
	float m_texHeight;
	bool m_stretch; // if this is active the texture size will be the viewport one
	
	// Frames per second and my little old tricks of storing the inverse , etc..
	float m_fps;
	float m_spf; // seconds per frame
	
	// current playing texture
	unsigned int m_playingTexture;
	
	// translation speed...
	float m_speedX;
	float m_speedY;
	
	// initial position
	float m_iniPosX;
	float m_iniPosY;
	
	// the blending
	bool m_hasCustomBlending;
	unsigned int m_renderBlendingPos;
	
public:
		CResourceImageSequence();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif