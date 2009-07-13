#ifndef __SCENE__
#define __SCENE__

#include "Effect.h"


typedef Effect* pEffect;

class Scene {
protected:
	int _pattern, _row;
	float _time;
	char* sceneName;
	char *sceneType;
	int numEffects;
	int lastEffect;
	pEffect* effectsList;
	
public: 
	virtual    void play(float time)=0;
	virtual    void init(void)=0;
	virtual    void start(void)=0;
	virtual    void deInit(void)=0;
			   void setMusicParams(int pattern,int row);
	void setSceneName(const char *name);
	virtual const char* getSceneName(void);
	virtual const char* getSceneType(void);
	void initEffectsList(int numEffects);
	int addEffect2List(pEffect newEffect);
	void setNumEffects(unsigned int num);
	void initEffect(int index);

	Scene();
	virtual   ~Scene();
	
};

#endif
