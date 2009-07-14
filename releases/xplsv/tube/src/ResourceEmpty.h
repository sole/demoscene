#include "Resource.h"

#ifndef RESOURCEEMPTY_H
#define RESOURCEEMPTY_H

class CResourceEmpty : public CResource {
	
public:
	void play(float time);
	void init(void);
	void start(void);
	void deInit(void);
	string getType(void);
	void setParam(string name, string value);
};

#endif
