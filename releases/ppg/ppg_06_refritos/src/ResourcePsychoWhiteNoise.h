//: src:ResourcePsychoWhiteNoise.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 11 august 2005  
// Declaration of CResourcePsychoWhiteNoise class

#ifndef RESOURCEPSYCHOWHITENOISE_H
#define RESOURCEPSYCHOWHITENOISE_H

#include "Resource.h"
#include "Algebra.h"
#include "Texture.h"

#define RESOURCEPSYCHOWHITENOISE_MAX_X 200
#define RESOURCEPSYCHOWHITENOISE_MAX_Y 200

class CResourcePsychoWhiteNoise : public CResource {
private:
	// color
	CPoint m_Color;
	float m_radio;
	unsigned int m_numVertex;
	unsigned int m_numX;
	unsigned int m_numY;
	CTexture m_Texture;
	unsigned int m_texPos;
	
	// the blending
	bool m_hasCustomBlending;
	unsigned int m_renderBlendingPos;	
	
public:
		CResourcePsychoWhiteNoise();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif
