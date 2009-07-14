#ifndef __MUSIC__
#define __MUSIC__

#include "bass/bass.h"

#define TICKCHANGED 1
#define ROWCHANGED 2
#define PATTERNCHANGED 3

#define FFT_BUFFER_LENGTH 256

class CMusic
{
private:
	unsigned int row,row2;
	unsigned int tick,tick2;
	unsigned int pattern,pattern2;
	int scaler;
	float seconds;
	float accumSeconds;
	HMUSIC mod;
	HSTREAM mp3;
	char* songFile;
	int musicStarted;
	bool m_isLoaded;
	void Error(const char *text);
	
public:
	
	CMusic();
	int initSound(void);
	int freeSound(void);
	void playSound(void);
	void stopSound(void);
	int playMod();
	int playMP3();
	int isPlaying();
	void setPos(unsigned int pattern, unsigned int row);
	void setMP3Pos(float position);
	
	HMUSIC loadMod(const char *file);
	HSTREAM loadMP3(const char *file);
	
	// Sincronizacion
	unsigned int getPattern(void);
	unsigned int getRow(void);
	unsigned int getTick(void);
	float getSeconds(void);
	float getMilliseconds();
	float getMP3Seconds(void);
	int syncro(); // fuerza a reconsultar el patron y fila 
	
	bool hasFinished(void);
	bool isLoaded(void);
	
	// Lo de la FFT
	int getFFT(float *buffer, unsigned int length = 512);
	void getFFTNatural(float *buffer);
	float getFFTBass(void);
	
	
};

#endif
