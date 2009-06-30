#ifndef EFFECT_H
#define EFFECT_H

#define GL_CLAMP_TO_EDGE                                        0x812F


class Effect {
protected:
	int _pattern, _row;
	float _time;
public: 
	virtual    void perFrame(float time)=0;
	virtual    void init(void)=0;
	virtual    void start(void)=0;
	virtual    void deInit(void)=0;
	virtual	   void stop(void){}
	virtual    void pauseEffect(void);
	virtual    void continueEffect(void);
			   void setMusicParams(int pattern,int row);

	Effect();
	virtual   ~Effect();

};

#endif
