#include "Music.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

// Empezar-Detener el sonido

int Music::initSound(void) {
	
	this->scaler=12;
	this->accumSeconds=0;
	
	FMOD_RESULT result;
	
	result = FMOD::System_Create(&system);
	if(result != FMOD_OK)
	{
		printf("Music: Patada! (%d) %s\n", result, FMOD_ErrorString(result));
		return -1;
	}
	else
	{	
		result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
		result = system->setDSPBufferSize(512, 4);
		result = system->init(100, FMOD_INIT_NORMAL, 0);
		// FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), true);  // TODO
	
		if(result != FMOD_OK)
		{
			printf("Music: Ay! %s\n", FMOD_ErrorString(result));
			
			int numDrivers;
			system->getNumDrivers(&numDrivers);
			printf("There are %d available drivers\n", numDrivers);
			for(int i = 0; i < numDrivers; i++)
			{
				char driverName[255];
				system->getDriverInfo(i, driverName, 255, 0);
				printf("%d %s\n", i, driverName);
			}
			
			
			exit(-1);
		}
		else
		{
			this->musicStarted=0;
			return(0);
		}
	}
}
int Music::freeSound(void) {
	// Libera los recursos que tuviera asignados 
	if(this->mp3 != NULL)
	{
		this->mp3->release();
	}
	
	if(this->mod != NULL)
	{
		this->mod->release();
	}
	
	system->release();
	return(0);
}
void Music::playSound(void) {
	// Ponemos la musica en marcha!
	// TODO no se si este metodo se usa?
	// la canción está en marcha 
	this->musicStarted=1;
}
void Music::stopSound(void) {
	// TODO este metodo se usa?
	// Obvio no?
	//BASS_Stop();
}
int Music::playMod() {
	//FMUSIC_PlaySong(this->mod);
	FMOD_RESULT result = system->playSound(FMOD_CHANNEL_FREE, this->mod, false, &channel);
	return 0;
}

int Music::playMP3() {
	//int rdo=FSOUND_Stream_Play(/*FSOUND_FREE*/0, this->mp3);
	FMOD_RESULT result = system->playSound(FMOD_CHANNEL_FREE, this->mp3, false, &channel);
	return result;
}

int Music::isPlaying(void) {
	return this->musicStarted;
}

void Music::setPos(unsigned int pattern, unsigned int row) {
	// Pone la cancion en el patron y fila indicados
	//if((pattern>=0) && (row>=0)) {
		//FMUSIC_SetOrder(this->mod, pattern); // specifying the row has not effect
		channel->setPosition(pattern, FMOD_TIMEUNIT_MODORDER);
		channel->setPosition(row, FMOD_TIMEUNIT_MODROW);
	//}
}

void Music::setMP3Pos(float position) {
	// FSOUND_Stream_SetTime(this->mp3, (int) position*1000);
	channel->setPosition((int) position * 1000, FMOD_TIMEUNIT_MS);
}

// Carga de ficheros y compañia
FMOD::Sound* Music::loadMod(char *file) {
	FMOD::Sound *loadedMod;
	
	FMOD_RESULT result = system->createStream(file, FMOD_DEFAULT | FMOD_ACCURATETIME, 0, &loadedMod);
	
	if(result == FMOD_OK) {
		this->mod = loadedMod;
		return loadedMod;
	} else {
		printf("Mod can't be loaded: %s\n", FMOD_ErrorString(result));
		return NULL;
	}	
}

FMOD::Sound *Music::loadMP3(char *file) {
	FMOD::Sound* loadedMP3;
	
	//FSOUND_Stream_Open(file, /*FSOUND_NORMAL | FSOUND_MPEGACCURATE*/0, 0, 0);
	FMOD_RESULT result = system->createStream(file, FMOD_DEFAULT | FMOD_ACCURATETIME, 0, &loadedMP3);
	
	if(result == FMOD_OK) {
		this->mp3=loadedMP3;
		return loadedMP3;
	} else {
		printf("MP3 can't be loaded: %s\n", FMOD_ErrorString(result));
		return NULL;
	}
}
// Sincronizacion
unsigned int Music::getRow(void) {
	// Devuelve la fila actual
	return this->row;
}

unsigned int Music::getTick(void) {
	// Devuelve el tick actual
	return this->tick;
}

unsigned int Music::getPattern(void) {
	// Devuelve el patron actual
	return this->pattern;
}

float Music::getSeconds(void) {
	// devuelve los segundos transcurridos desde que se inicio la cancion
	// mu util para esos efectillos continuos... ;)
	
	return this->getMilliseconds() * 0.001f;
}

float Music::getMilliseconds()
{
	// return FMUSIC_GetTime(this->mod) * 0.001;
	unsigned int position;
	channel->getPosition(&position, FMOD_TIMEUNIT_MS);
	return float(position) ;//* 0.001f;
}

float Music::getMP3Seconds(void) {
	// return FSOUND_Stream_GetTime(this->mp3) * 0.001; //BASS_ChannelBytes2Seconds(this->mp3,BASS_ChannelGetPosition(this->mp3));
	unsigned int length;
	mp3->getLength(&length, FMOD_TIMEUNIT_MS);
	return float(length) * 0.001f;
}

int Music::syncro() {
	// fuerza a reconsultar el patron y fila 
	// actualizamos la fila y patron actuales
	
	// Si hay algo nuevo , se devuelve 
	// TICKCHANGED 1
	// ROWCHANGED 2
	// PATTERNCHANGED 3
	// 0 en otro caso
	//QWORD ahora;
	static float sec=0;
	float sec2;
	
	// docs sayeth: "It is important that System::update be called once per frame"
	system->update();
	
	//BASS_Update(); //?
	//ahora=LOWORD2(BASS_ChannelGetPosition(this->mod));
	//this->pattern=FMUSIC_GetOrder(this->mod);
	//this->row=FMUSIC_GetRow(this->mod);
	if(this->mod != NULL)
	{
		channel->getPosition(&this->pattern, FMOD_TIMEUNIT_MODORDER);
		channel->getPosition(&this->row, FMOD_TIMEUNIT_MODROW);
	}
	/*this->tick=(HIWORD(ahora))%this->scaler;
	sec2=(BASS_ChannelBytes2Seconds(this->mod,MAKELONG(this->pattern,this->row+this->tick)));
	if(sec2!=sec) {
		this->accumSeconds+=(sec2-sec)/this->scaler;
		sec=sec2;
	}*/
	// Si ha cambiado lo actualizo!
	
	if(this->pattern2!=this->pattern) {	
		this->pattern2=this->pattern;
		sec=0;
		return(PATTERNCHANGED);
	} else {
		if(this->row2!=this->row)
		{
			this->row2=this->row;
			// Ha cambiado
			return(ROWCHANGED);
		} /*else {
			if(this->tick2!=this->tick) {
				this->tick2=this->tick;
				return(TICKCHANGED);
			} else {
				// No ha cambiado nada
				return(0);
			}
		}*/
		else {
			return(0);
		}
	}
	
}

int Music::getFFT(float *buffer, unsigned int length) {
	int ret;
	
	//buffer =  FSOUND_DSP_GetSpectrum();
	//for(int i=0;i<512;i++) {
//		printf("i %f ", buffer[i]);
//	}
	system->getSpectrum(buffer, length, 0, FMOD_DSP_FFT_WINDOW_RECT);
	
	return 0;
}

void Music::getFFTNatural(float *buffer) {
	float tmpBuf[512];
	this->getFFT(tmpBuf,512);
	
	float scale=0.0010;
	float bias=1.0;
	int i;
	
	for(i=1;i<32;i++) {
		buffer[i] = tmpBuf[i]*scale;
		//each float a en BASSfft
		//valoresGUI(i++)=a*scale
		scale=scale+bias;
		bias=bias*1.6f;
		
	}
}

float Music::getFFTBass(void) {
	/*float fft[512];
	float *fftpointer;
	float daBass;
	int i;
	this->getFFT(fftpointer,512);
	assert(1==1);
	// hago una media para que esté un poco más representado el espectro de bajos.
	daBass=0;
	//float correction = (1/fftpointer[0]);
	for(i=1;i<510;i++) {
		//fft[i]=fftpointer[i]*i*correction;
		//daBass+=fft[i];
		printf("%f \t", fftpointer[i]);
	}
	exit(-1);
	daBass=daBass*0.10;
	
	
	return daBass;*/
	//FSOUND_Update();
	//float* fft = FSOUND_DSP_GetSpectrum();
	float *fft;
	this->getFFT(fft);
	float daBass = 0;
	for(int dunno=0; dunno<128; dunno++) 
	{ 
		daBass += *fft;
		//printf("%f ", *fft);
		/*if( *fft==1.0) 
		printf(ÒMan burpÓ); 
		if(*fft<0.5) 
		printf(ÒLady BurpÓ);*/ 
		fft++; 
	}
	daBass /= 128.0;
	//exit(-1);
	return daBass;
}

bool Music::hasFinished(void) {
	if(this->mp3!=NULL) {
		unsigned int length;
		unsigned int position;
		mp3->getLength(&length, FMOD_TIMEUNIT_MS);
		channel->getPosition(&position, FMOD_TIMEUNIT_MS);
		return (length <= position);
	}
	
	if(this->mod!=NULL) {
		unsigned int len;
		mod->getLength(&len, FMOD_TIMEUNIT_MS);
		unsigned int position;
		channel->getPosition(&position, FMOD_TIMEUNIT_MS);
		
		return(len <= position);
	}
	
	return (true);
	
}
