//: src:ResourceObjectTerrain.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 11 august 2005  
// Declaration of CResourceObjectTerrain class

#ifndef RESOURCEOBJECTTERRAIN_H
#define RESOURCEOBJECTTERRAIN_H

#include "Resource.h"
#include "Algebra.h"
#include <vector>
#include "Camera.h"


class CResourceObjectTerrain : public CResource {
private:
	// color
	CPoint m_Color;
	
	CPoint m_origin1, m_origin2;
	CPoint** m_meshPoints;
	
	// the blending
	bool m_hasCustomBlending;
	unsigned int m_renderBlendingPos;
	
	// the height map file
	string m_TextureFile;
	bool m_hasTexture;
	unsigned int m_width, m_height;
	unsigned int m_totalPixels;
	unsigned int m_draw_max_x, m_draw_max_y;
	unsigned char *m_heightMapData;
	unsigned int m_step;
	CPoint m_scale;
	float m_prismWidth, m_prismHeight;
	bool m_translateX, m_translateY;
	
	unsigned int m_offset_x, m_offset_y; // where to start painting, considering the height map in 2D only 
	
	int Height(int x, int y);
	void drawPrism(CPoint p1, CPoint p2);
	
public:
	CResourceObjectTerrain();
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif