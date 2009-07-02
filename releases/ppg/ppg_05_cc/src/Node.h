#ifndef NODE_H
#define NODE_H

#ifndef __MATH3D__
#include "math3D.h"
#endif


class Node {
protected:
	bool updated;

public: 
	virtual void perFrame(float time);
	
	bool isUpdated();
	virtual void deInit(void);

	Node();
	virtual ~Node();

};

#endif
