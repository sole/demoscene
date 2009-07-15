#include "Music.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Empezar-Detener el sonido
CMusic::CMusic()
{
	this->m_isLoaded = false;
}

void CMusic::Error(const char *text) 
{
	printf("Error(%d): %s\n",BASS_ErrorGetCode(),text);
	BASS_Free();
}

int CMusic::initSound(void) {
	
	this->scaler=12;
	this->accumSeconds=0;
	mp3 = NULL;
	mod = NULL;
	
	if (!BASS_Init(-1,44100,0,0,NULL))
	{
		Error("CMusic: Patada! Can't initialize device");
		return -1;
	}
	else
	{	
		this->musicStarted=0;
		return(0);
	}
}
int CMusic::freeSound(void) {
	if(this->mp3)
	{
		BASS_StreamFree(this->mp3);
	}
	else if(this->mod)
	{
		BASS_MusicFree(this->mod);
	}
	
	BASS_Free();
	return(0);
}
void CMusic::playSound(void)
{
	// Ponemos la musica en marcha!
	// TODO no se si este metodo se usa?
	// la canción está en marcha 
	this->musicStarted=1;
}

void CMusic::stopSound(void)
{
	// TODO este metodo se usa?
	// Obvio no?
	BASS_Stop();
}
int CMusic::playMod()
{
	BASS_ChannelPlay(this->mod, FALSE);
	return 0;
}

int CMusic::playMP3() {
	return BASS_ChannelPlay(this->mp3, FALSE);
}

int CMusic::isPlaying(void) {
	return this->musicStarted;
}

void CMusic::setPos(unsigned int pattern, unsigned int row) {
	BASS_ChannelSetPosition(this->mod, MAKELONG(pattern, row), BASS_POS_MUSIC_ORDER
		// unsure | BASS_MUSIC_POSRESET
	);
}

void CMusic::setMP3Pos(float position)
{
	BASS_ChannelSetPosition(this->mp3, BASS_ChannelSeconds2Bytes(this->mp3, position), BASS_POS_BYTE);
}

HMUSIC CMusic::loadMod(const char *file)
{
	if (!(this->mod = BASS_MusicLoad(FALSE, file, 0, 0, BASS_MUSIC_RAMPS|BASS_MUSIC_PRESCAN, 0)))
	{
		Error("Can't load mod file");
		return NULL;
	}
	else
	{
		return this->mod;
	}
}

HSTREAM CMusic::loadMP3(const char *file)
{
	if(!(mp3 = BASS_StreamCreateFile(FALSE, file, 0, 0, BASS_STREAM_PRESCAN)))
	{
		Error("Can't load mp3 file");
		return NULL;
	}
	else
	{
		this->m_isLoaded = true;
		return mp3;
	}
	
	
}
// Sincronizacion
unsigned int CMusic::getRow(void) {
	// Devuelve la fila actual
	return this->row;
}

unsigned int CMusic::getTick(void) {
	// Devuelve el tick actual
	return this->tick;
}

unsigned int CMusic::getPattern(void) {
	// Devuelve el patron actual
	return this->pattern;
}

float CMusic::getSeconds(void) {
	// devuelve los segundos transcurridos desde que se inicio la cancion
	// mu util para esos efectillos continuos... ;)
	return this->getMilliseconds() * 0.001f;
}

float CMusic::getMilliseconds()
{
	DWORD channel;
	
	if(this->mod)
	{
		channel = this->mod;
	}
	else
	{
		channel = this->mp3;
	}
	
	QWORD pos=BASS_ChannelGetPosition(channel,BASS_POS_BYTE);
	float time=BASS_ChannelBytes2Seconds(channel,pos);
	return time * 1000;
}

float CMusic::getMP3Seconds(void) {
	// TODO KILL THIS METHOd
	return this->getSeconds();
}

int CMusic::syncro() {
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
	
	if(this->mod)
	{
		QWORD pos=BASS_ChannelGetPosition(this->mod, BASS_POS_MUSIC_ORDER);
		this->pattern = LOWORD(pos);
		this->row = HIWORD(pos);
	}
	
	
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

int CMusic::getFFT(float *buffer, unsigned int length) {
	int ret;
	
	DWORD channel;
	if(this->mod)
	{
		channel = this->mod;
	}
	else
	{
		channel = this->mp3;
	}
	BASS_ChannelGetData(channel, buffer, BASS_DATA_FFT512);
	
	return 0;
}

void CMusic::getFFTNatural(float *buffer) {
	float fft[512];
	this->getFFT(fft,512);
		
	float y,maxi;
	unsigned int i,j,x,bands = 10,start,intperbands = 512/bands;
	float thelog = 1/log(fft[0]);
	float scale,bias,biasmult = 2.1*12/bands;
	
	for(i=0; i<bands; i++) 
	{
		y = 0;
		
		if(i==0) {
			start =0;
		} else {
			start = intperbands * i;
		}
		
		for(j=start;j<start+intperbands;j++) {
			y += fft[j];
		}
		y /= intperbands;
		
			        
		buffer[i] = y;
	}
	scale=2;
	bias=10;
	for(i=0;i<bands;i++) {
		buffer[i] = buffer[i]*scale;
		if(buffer[i]>1) {
			buffer[i]=1;
		}
		scale += bias;
		bias *= biasmult;
	}
}

float CMusic::getFFTBass(void) {
	float fft[512];
	//float *fftpointer;
	float daBass;
	int i;
	this->getFFT(fft, 512);

	// hago una media para que esté un poco más representado el espectro de bajos.
	daBass=0;

	for(i=1; i<20; i++)
	{
		daBass += fft[i];
	}

	daBass *= 0.05;
	
	
	return daBass;
}

bool CMusic::hasFinished(void) {
	DWORD channel;
	
	if(this->mod)
	{
		channel = this->mod;
	}
	else
	{
		channel = this->mp3;
	}
	
	QWORD pos = BASS_ChannelGetPosition(channel,BASS_POS_BYTE);
	QWORD len = BASS_ChannelGetLength(channel, BASS_POS_BYTE);
	
	return(pos >= len);
}

bool CMusic::isLoaded(void)
{
	return this->m_isLoaded;
}
