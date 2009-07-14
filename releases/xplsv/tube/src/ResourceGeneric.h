#include "Resource.h"

#ifndef RESOURCEGENERIC_H
#define RESOURCEGENERIC_H

class CResourceGeneric : public CResource {
	
public:
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif
