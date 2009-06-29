#ifndef __MUSIC__
#define __MUSIC__

//#include "fmod/inc/fmod.h"
//#include "fmod/inc/fmod_errors.h"
//#include "fmod/inc/wincompat.h"
#include "fmod_ex/inc/fmod.hpp"
#include "fmod_ex/inc/fmod_errors.h"

//#include <stdlib.h>

//#define HIWORD2(l)   ((DWORD) (((QWORD) (l) >> 32) & 0xFFFFFFFF)) 
//#define LOWORD2(l)   ((DWORD) (l))  

#define TICKCHANGED 1
#define ROWCHANGED 2
#define PATTERNCHANGED 3

#define FFT_BUFFER_LENGTH 256

class Music {
private:
	unsigned int row,row2;
	unsigned int tick,tick2;
	unsigned int pattern,pattern2;
	int scaler;
	float seconds;
	float accumSeconds;
	//HMUSIC mod;
	//HSAMPLE mp3;
	//FMUSIC_MODULE *mod;
	//FSOUND_STREAM *mp3;
	FMOD::Sound *mod;
	FMOD::Sound *mp3;	
	FMOD::System *system;
	FMOD::Channel *channel;
	char* songFile;
	int musicStarted;
	
public:
		
	int initSound(void);
	int freeSound(void);
	void playSound(void);
	void stopSound(void);
	int playMod();
	int playMP3();
	int isPlaying();
	void setPos(unsigned int pattern, unsigned int row);
	void setMP3Pos(float position);
	
	//FMUSIC_MODULE* loadMod(char *file);
	//FSOUND_STREAM* loadMP3(char *file);
	
	FMOD::Sound* loadMod(char *file);
	FMOD::Sound* loadMP3(char *file);
	
	// Sincronizacion
	unsigned int getPattern(void);
	unsigned int getRow(void);
	unsigned int getTick(void);
	float getSeconds(void);
	float getMilliseconds();
	float getMP3Seconds(void);
	int syncro(); // fuerza a reconsultar el patron y fila 
	
	bool hasFinished(void);
	
	// Lo de la FFT
	int getFFT(float *buffer, unsigned int length = 512);
	void getFFTNatural(float *buffer);
	float getFFTBass(void);
	
	
};

#endif
