#ifndef __SCENE3D__
#define __SCENE3D__

#include "GeomObject.h"
#include "LightObject.h"

#include <assert.h>
#include <stdio.h>

class Scene3D {
private:
	GeomObject *m_geomObjectsList;
	unsigned int m_numGeomObjects;
	// TODO: Material lists
	// TODO: Cameras (?)
	// TODO: Lights (?)
	unsigned int m_numLightObjects;
	LightObject *m_lightObjectsList;

	// For loading
	FILE *fh; // The file handle
	int fileGetNumberofGeomObjects(void);
	int loadGeomObjFromFile(unsigned int index);
	int fileGetNumberofLightObjects(void);
	int loadLightObjFromFile(unsigned int index);
public: 
	Scene3D();
	~Scene3D();

	void setNumGeomObjects(unsigned int num);
	int initGeomObjects(void);

	void setNumLightObjects(unsigned int num);
	int initLightObjects(void);

	int loadFromFile(const char *filepath);

	int draw(void);

	unsigned int getNumGeomObjects(void);
	GeomObject *getGeomObjectAt(unsigned int index);
};

#endif
