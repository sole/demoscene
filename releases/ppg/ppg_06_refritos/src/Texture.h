//: src:Texture.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 1 august 2005  
// Declaration of CTexture class

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
using namespace std;

class CTexture {
protected:
	unsigned char *m_imageData;
	unsigned int m_bpp; // bytes per pixel
	// Where m_width, m_height refer to the opengl TEXTURE - needs to be power of 2, 
	// and m_imgWidth, m_imgHeight is the original img size 
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_imgHeight;
	unsigned int m_imgWidth; 
	unsigned int m_texID;
	string m_name; // that's the human id
	string m_path;
	
public:
	CTexture();
	~CTexture();
	
	// setters/getters
	void setImageData(unsigned char *imageData);
	unsigned char *getImageData();
	void setBpp(unsigned int bpp);
	unsigned int getBpp();
	void setWidth(unsigned int width);
	unsigned int getWidth();
	void setHeight(unsigned int height);
	unsigned int getHeight();
	void setImgWidth(unsigned int width);
	unsigned int getImgWidth();
	void setImgHeight(unsigned int height);
	unsigned int getImgHeight();
	void setTexId(unsigned int texId);
	unsigned int getTexId();
	void setName(string name);
	string getName();
	void setPath(string path);
	string getPath();
	
};

#endif
