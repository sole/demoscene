#include "Resource.h"

#ifndef RESOURCEOBJECTDOTMATRIX_H
#define RESOURCEOBJECTDOTMATRIX_H

#include <map>
#include <vector>
#include <string>
using namespace std;

class CResourceObjectDotMatrix : public CResource {
	
public:
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
	CResourceObjectDotMatrix();
protected:
	std::map <string, int *> m_characterData;
	
	unsigned int m_charWidth;
	unsigned int m_charHeight;
	std::string m_textureFile;
};

#endif