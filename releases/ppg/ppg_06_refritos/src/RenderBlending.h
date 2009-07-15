//: src:RenderBlending.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 7 august 2005  
// Declaration of CEffect class

#ifndef RENDERBLENDING_H
#define RENDERBLENDING_H

#include <string>

using namespace std;
class CRenderBlending {
private:
	unsigned int srcFactor;
	unsigned int dstFactor;
	string name;
	
public:
		
	CRenderBlending();
	unsigned int getSrc();
	void setSrc(unsigned int value);
	unsigned int getDst();
	void setDst(unsigned int value);
	string getName();
	void setName(string _name);
};
#endif