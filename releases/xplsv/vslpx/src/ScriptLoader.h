#include <stdio.h>
#include <string.h>
#include "tinyxml.h"

#include "Demo.h"
extern Demo *miDemo;

extern void loader(float porcentaje);

#define SL_NUM_GL_CONSTANTS 10
#define CACAFEA 0xCACAFEA

class ScriptLoader {
private:
	char scriptFile[255];
	FILE *scriptHandle;
	TiXmlDocument *doc;
	
public:
	ScriptLoader();
	ScriptLoader(const char *filename);
	~ScriptLoader();

	int setFilename(const char *filename);
	int init(void);
	int load(void);
	int loadEvents(void);
	int loadScenes(void);
	float glConstant2Value(const char *glConstant);
	float getRealValue(const char *strValue);
};
