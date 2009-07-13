#ifndef __EFFECT__
#define __EFFECT__

#include "EventList.h"
/**
this is effect v2!!
2005 01 09

  */

class Effect {
protected:
	EventList *myEventList;
	char name[128];
	
public: 
	virtual    void play(float time)=0;
	virtual    void init(void)=0;
	virtual    void start(void)=0;
	virtual    void deInit(void)=0;
			   
	virtual	   const char* getEffectType(void);
	
	virtual int setParam(char *paramName, char *attribName, float value)=0;
	void setEventList(EventList *newEventList); 
	short isPlaying(float _time);
	void setName(char *name);
	char *getName(void);

	Effect();
	virtual   ~Effect();

};

#endif
