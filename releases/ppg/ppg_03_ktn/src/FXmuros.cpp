#include "FXmuros.h"


// inicializar lo estático aquí...
float FXmuros::bannerMesh[X_SLICES][Y_SLICES][2];
float FXmuros::bannerMeshAux[X_SLICES][Y_SLICES][2];
float FXmuros::bannerText[X_SLICES][Y_SLICES][2];

TextureImage FXmuros::text_gfx_ppg;
TextureImage FXmuros::text_gfx_presents;
TextureImage FXmuros::text_gfx_ademo;
TextureImage FXmuros::text_gfx_called;
TextureImage FXmuros::text_gfx_logokillo;


TextureImage FXmuros::text_gfx_notpm;
TextureImage FXmuros::text_gfx_supernena;



// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXmuros::perFrame(float time) {
	int x,y;
	float z_depth=0.120f,x_desp;
	
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	miDemo->ponOrtopedico(2,2);

	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Muro del fondo - doble ancho que alto
	/*
		-xt*2,xt         xt*2,xt
	  4	+-----------------+ 3
		|                 |
		| 1               | 2
		+-----------------+
		-xt*2,-xt         xt*2,-xt
	*/
	float al; // alfa
	if(_row<64) {
		al=float(_row)/64;
	} else {
		al=1-float(_row%64)/64;
	}
	glColor4f(1,1,1,al);
	float xt=1.5;//10-0.05*_row; // xtremos
	float dp=1.5*sin((_row+_pattern)*0.01); // desplazamiento
	if(_pattern%2==0) {
		dp=-dp;
	}
	
	switch (this->_pattern) {
	case 0: glBindTexture(GL_TEXTURE_2D, this->text_gfx_notpm.texID); break;
	case 1: glBindTexture(GL_TEXTURE_2D, this->text_gfx_notpm.texID); break;
	case 2: glBindTexture(GL_TEXTURE_2D, this->text_gfx_supernena.texID); break;
	case 3: glBindTexture(GL_TEXTURE_2D, this->text_gfx_supernena.texID); break;
	case 4: default: glBindTexture(GL_TEXTURE_2D, this->text_gfx_logokillo.texID); break;
	}
	
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0); 
		glVertex3f(-xt*2+dp,-xt,z_depth);
		
		glTexCoord2f(1,0);
		glVertex3f(xt*2+dp,-xt, z_depth);

		glTexCoord2f(1,1);
		glVertex3f(xt*2+dp,xt,  z_depth);

		glTexCoord2f(0,1);
		glVertex3f(-xt*2+dp,xt,z_depth);

		//glVertex3f(0,0,0);

	glEnd();
	
	glColor3f(1,1,1);
	
	//glShadeModel(GL_SMOOTH);
	switch (this->_pattern) {
	case 0: glBindTexture(GL_TEXTURE_2D, this->text_gfx_ppg.texID); break;
	case 1: glBindTexture(GL_TEXTURE_2D, this->text_gfx_presents.texID); break;
	case 2: glBindTexture(GL_TEXTURE_2D, this->text_gfx_ademo.texID); break;
	case 3: glBindTexture(GL_TEXTURE_2D, this->text_gfx_called.texID); break;
	case 4: default: glBindTexture(GL_TEXTURE_2D, this->text_gfx_logokillo.texID); break;
	}

	static float xt2=0.60;
	float yt2=0.85;
	dp=0;
	float alfatitulos;

	if(_row<32) { 
		// Más grande a mas pequeño
		//xt2=1.5 - 0.03*float(_row);
		alfatitulos=float(_row)/32.0;
	} else 
	if(_row>96) {
		//xt2+=0.03*float(_row%32)/32;
		alfatitulos=float(32-_row%32)/32.0;
	} else {
		alfatitulos=1.0;
	}
	glColor4f(1,1,1,alfatitulos);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0); 
		glVertex3f(-xt2*2+dp,-yt2,z_depth);
		
		glTexCoord2f(1,0);
		glVertex3f(xt2*2+dp,-yt2, z_depth);

		glTexCoord2f(1,1);
		glVertex3f(xt2*2+dp,yt2,  z_depth);

		glTexCoord2f(0,1);
		glVertex3f(-xt2*2+dp,yt2,z_depth);

		//glVertex3f(0,0,0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	miDemo->quitaOrtopedico();

	// fade
	float alfa;
	if(_row<=16) {
		alfa=float(16-_row)/16.0;
		//glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfa);
		fxfade->perFrame(_time);
		//glEnable(GL_DEPTH_TEST);
	}
	else if((_row>=112)) {
		alfa=float(_row%16)/16.0;
		//glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfa);
		fxfade->perFrame(_time);
		//glEnable(GL_DEPTH_TEST);
	}

	
}

void FXmuros::init(void) {
	// asignar recursos y tal, cargar ficheros, blabla

	int i,j;
	float longintX,longintY,floati,floatj;

	// Cargo las texturas de los graffitis :-)
	LoadTGA(&text_gfx_ppg,"./data/text_gfx_ppg.tga");
	LoadTGA(&text_gfx_presents,"./data/text_gfx_presents.tga");
	LoadTGA(&text_gfx_ademo,"./data/text_gfx_ademo.tga");
	LoadTGA(&text_gfx_called,"./data/text_gfx_called.tga");
	LoadTGA(&text_gfx_logokillo,"./data/text_gfx_killotrona.tga");


	LoadTGA(&text_gfx_notpm,"./data/gfx_not.tga");
	LoadTGA(&text_gfx_supernena,"./data/gfx_supernena.tga");


	// Preparo mi malla inicial de puntos
	longintX=1.0f/float(X_SLICES);
	longintY=1.0f/float(Y_SLICES);
	for(i=1;i<X_SLICES;i++) {
		floati=float(i);
		for(j=1;j<Y_SLICES; j++) {
			floatj=float(j);
			this->bannerText[i][j][0]=(floati)/X_SLICES;
			this->bannerText[i][j][1]=(floatj)/Y_SLICES;

			this->bannerMesh[i][j][0]=-1+2*(floati)/X_SLICES;
			this->bannerMesh[i][j][1]=-1+2*(floatj)/Y_SLICES;

			this->bannerMeshAux[i][j][0]=this->bannerMesh[i][j][0];
			this->bannerMeshAux[i][j][1]=this->bannerMesh[i][j][1];
		}
	}

}

void FXmuros::start(void) {
	glClearColor(1.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void FXmuros::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
}

FXmuros::FXmuros() {
}

FXmuros::~FXmuros() {
}
