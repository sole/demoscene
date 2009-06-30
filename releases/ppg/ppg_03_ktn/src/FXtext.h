#ifndef FXTEXT_H
#define FXTEXT_H

#include "Effect.h"
#include "Demo.h"
extern Demo *miDemo;
#include "textures.h"
#include "math3D.h"
#include <string.h>

class FXtext: public Effect {
protected:

	// textura de letras
	static TextureImage textura;
	char buffer[300];
	Point color; // el 'color' con el q se tintara la textura
	Point pos; // origen del texto
	int charCount; //numero de caracteres en la textura
	int spacingPixels; // pixels q separan una letra de otra
	float anchoCar,altoCar; // alto y ancho de los caracteres (al dibujar y eso)
	float textPos[128];
	float textSize;
	float size_y;

	int numChar2See;

public:
	void perFrame(float time);
	void init(void);
	void start(void);
	void deInit(void);
	void stop(void);

	void setColor(float r,float g, float b, float a);
	void setString(char *string); //txt q queremos ver
	void setPos(float x,float y); // posicion de pantalla en q queremso dibujar..
	FXtext();
	~FXtext();
};

#endif //FXTEXT_H
