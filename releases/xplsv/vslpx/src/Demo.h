#ifndef __DEMO__
#define __DEMO__

#include <assert.h>

#include "EventList.h"
#include "Scene.h"
#include "SceneFactory.h"
#include "EffectFactory.h"
#include "textures.h"


#define DEMOWIDTH 640
#define DEMOHEIGHT 480

#define EVENTLISTS_MAX 50
#define TEXTURESLIST_MAX 50

typedef Scene* pScene;
typedef EventList* pEventList;

class Demo {
public:
	Demo(int _height, int _width);
	~Demo();
	void setSize(int _height, int _width);
	int getWidth(void);
	int getHeight(void);
	bool isFullScreen(void);
	void setFullScreen(bool _fullscr);
	void setTitle(char *_title);
	char *getTitle(void);
	void ponOrtopedico(float xres = DEMOWIDTH, float yres = DEMOHEIGHT); // TODO ??? -1 or demowidth
	void quitaOrtopedico(void);

	void ejes(void);

	// Events & scenes managements oh yeah <o/
	void initEventLists(int numEventLists);
	int addEventList(char *name); // Creates a new list with that name and returns the id if ok, else -1
	int addEvent2List(int listId, float _start, float _length, float _vol); // adds an event to that list (id)
	EventList* getEventListByName(char *name); // returns pointer to the eventlist with that name
	EventList* getEventListById(int i); // returns pointer to the eventlist with that id
	int initSceneList(int numScenes); // inits the scenes array with given number
	int addScene2List(char *sceneType, char *sceneName, float start, float length);
	int play(float _time);
	pScene getSceneAt(unsigned int i);
	pEffect createEffect(char *effectType);

	// Resources (or something similar... XD)
	TextureImage* addTexture(char *texturePath, unsigned int id);
	TextureImage* addTexture(GLuint _width, GLuint _height, unsigned int id);
	TextureImage* getTextureById(unsigned int _id);

	// Let's improve the opengl code quality XD
	int checkGLerror(const char *caller);
	int hasError(void);

private:
	int height;
	int width;
	bool fullscreen;
	char title[255];

	int numEventLists;
	int lastEvent;
	pEventList* eventLists;
	int numScenes, lastScene;
	pScene* sceneList;
	float *sceneStart;
	float *sceneLength;
	SceneFactory sceneFactory;
	EffectFactory effectFactory;
	
	TextureImage texturesList[TEXTURESLIST_MAX];
	unsigned int numTextures;

	int internalError;
	char strInternalError[512];
};

#endif
