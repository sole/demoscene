#ifndef EFFECT_H
#define EFFECT_H

#include "Events.h"

class Effect {
protected:
	int _pattern, _row;
	float _time;
	int eventFlag;
public: 
	virtual    void perFrame(float time)=0;
	virtual    void init(void)=0;
	virtual    void start(void)=0;
	virtual    void deInit(void)=0;
	virtual	   void stop(void){}
	virtual    void pauseEffect(void);
	virtual    void continueEffect(void);
			   void setMusicParams(int pattern,int row);
			   void setEventFlag(int eventType);
			   void resetEventFlag(int eventType);
			   int checkEventFlag(int eventType);

	Effect();
	virtual   ~Effect();

};

#endif
