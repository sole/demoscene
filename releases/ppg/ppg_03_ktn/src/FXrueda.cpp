#include "FXrueda.h"
#include <math.h>
// inicializar lo estático aquí...
//Point *FXrueda::ruedaQuadVertex[NUMVERTEX*8];
Camera FXrueda::cam;
TextureImage FXrueda::text_fondo;
TextureImage FXrueda::text_particula;
TextureImage FXrueda::text_ford;
float FXrueda::radio1;
float FXrueda::radio2;

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXrueda::perFrame(float time) {
	int i;
	static int flash=0;
	float z_depth=40.0f;

	time = time*0.001;
	this->_time=time;

	fxradialblur->prepareFrame();

	glClearColor(0.8,0.1,0.8,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	float cx,cy;
	cx=2+1.5*cos(_time*0.5);
	cy=2+1.5*sin(_time*0.5);
	// ahora veras!! (nunca mejor dicho)
	if(_row>0 && _row<32) {
		cam.SetPos(cx,cy,0);
	}
	if(_row>=32 && _row<64) {
		cam.SetPos(0,cy,cx);
	}
	if(_row>=64 && _row<96) {
		cam.SetPos(cx,0,cy);
	}
	if(_row>=96 && _row<128) {
		cam.SetPos(cx,cy,cx);
	}

	cam.toOGL();
	//miDemo->ponOrtopedico(1,1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRotatef(time,12,12,1);
	glLineWidth(1);
	float sen=sin(_time*0.5);
	static float pulso;
	if((this->_row%8)==0) {
		pulso=4;
	}
	if(pulso>0) {
		pulso=pulso - pulso*pulso*1.1;
	}
	marear(4,1+pulso);
	//cam.SetLook(0,pulso,0);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
	float alfa=0.6+0.2*sen;

	for(i=0;i<NUMVERTEX-1;i+=4) {
		glColor4f(1,1,1,alfa);
		glBegin(GL_QUADS);
			// abajo
			glVertex3f(this->ruedaQuadVertex[i].x,this->ruedaQuadVertex[i].y,this->ruedaQuadVertex[i].z);
			glVertex3f(this->ruedaQuadVertex[i+4].x,this->ruedaQuadVertex[i+4].y,this->ruedaQuadVertex[i+4].z);
			glVertex3f(this->ruedaQuadVertex[i+7].x,this->ruedaQuadVertex[i+7].y,this->ruedaQuadVertex[i+7].z);
			glVertex3f(this->ruedaQuadVertex[i+3].x,this->ruedaQuadVertex[i+3].y,this->ruedaQuadVertex[i+3].z);
		glEnd();

		glBegin(GL_QUADS);
			// arriba
			glVertex3f(this->ruedaQuadVertex[i+1].x,this->ruedaQuadVertex[i+1].y,this->ruedaQuadVertex[i+1].z);
			glVertex3f(this->ruedaQuadVertex[i+5].x,this->ruedaQuadVertex[i+5].y,this->ruedaQuadVertex[i+5].z);
			glVertex3f(this->ruedaQuadVertex[i+6].x,this->ruedaQuadVertex[i+6].y,this->ruedaQuadVertex[i+6].z);
			glVertex3f(this->ruedaQuadVertex[i+2].x,this->ruedaQuadVertex[i+2].y,this->ruedaQuadVertex[i+2].z);
		glEnd();

		glBegin(GL_QUADS);
			// derecha
			glVertex3f(this->ruedaQuadVertex[i].x,this->ruedaQuadVertex[i].y,this->ruedaQuadVertex[i].z);
			glVertex3f(this->ruedaQuadVertex[i+4].x,this->ruedaQuadVertex[i+4].y,this->ruedaQuadVertex[i+4].z);
			glVertex3f(this->ruedaQuadVertex[i+5].x,this->ruedaQuadVertex[i+5].y,this->ruedaQuadVertex[i+5].z);
			glVertex3f(this->ruedaQuadVertex[i+1].x,this->ruedaQuadVertex[i+1].y,this->ruedaQuadVertex[i+1].z);
		glEnd();

		glBegin(GL_QUADS);
			// izquierda
			glVertex3f(this->ruedaQuadVertex[i+3].x,this->ruedaQuadVertex[i+3].y,this->ruedaQuadVertex[i+3].z);
			glVertex3f(this->ruedaQuadVertex[i+7].x,this->ruedaQuadVertex[i+7].y,this->ruedaQuadVertex[i+7].z);
			glVertex3f(this->ruedaQuadVertex[i+6].x,this->ruedaQuadVertex[i+6].y,this->ruedaQuadVertex[i+6].z);
			glVertex3f(this->ruedaQuadVertex[i+2].x,this->ruedaQuadVertex[i+2].y,this->ruedaQuadVertex[i+2].z);
		glEnd();

		glColor4f(0,0,0,1);
		glBegin(GL_LINE_STRIP);
			// abajo
			glVertex3f(this->ruedaQuadVertex[i].x,this->ruedaQuadVertex[i].y,this->ruedaQuadVertex[i].z);
			glVertex3f(this->ruedaQuadVertex[i+4].x,this->ruedaQuadVertex[i+4].y,this->ruedaQuadVertex[i+4].z);
			glVertex3f(this->ruedaQuadVertex[i+7].x,this->ruedaQuadVertex[i+7].y,this->ruedaQuadVertex[i+7].z);
			glVertex3f(this->ruedaQuadVertex[i+3].x,this->ruedaQuadVertex[i+3].y,this->ruedaQuadVertex[i+3].z);
			glVertex3f(this->ruedaQuadVertex[i].x,this->ruedaQuadVertex[i].y,this->ruedaQuadVertex[i].z);
			glEnd();

		glBegin(GL_LINE_STRIP);
			// arriba
			glVertex3f(this->ruedaQuadVertex[i+1].x,this->ruedaQuadVertex[i+1].y,this->ruedaQuadVertex[i+1].z);
			glVertex3f(this->ruedaQuadVertex[i+5].x,this->ruedaQuadVertex[i+5].y,this->ruedaQuadVertex[i+5].z);
			glVertex3f(this->ruedaQuadVertex[i+6].x,this->ruedaQuadVertex[i+6].y,this->ruedaQuadVertex[i+6].z);
			glVertex3f(this->ruedaQuadVertex[i+2].x,this->ruedaQuadVertex[i+2].y,this->ruedaQuadVertex[i+2].z);
			glVertex3f(this->ruedaQuadVertex[i+1].x,this->ruedaQuadVertex[i+1].y,this->ruedaQuadVertex[i+1].z);
			glEnd();

		glBegin(GL_LINE_STRIP);
			// derecha
			glVertex3f(this->ruedaQuadVertex[i].x,this->ruedaQuadVertex[i].y,this->ruedaQuadVertex[i].z);
			glVertex3f(this->ruedaQuadVertex[i+4].x,this->ruedaQuadVertex[i+4].y,this->ruedaQuadVertex[i+4].z);
			glVertex3f(this->ruedaQuadVertex[i+5].x,this->ruedaQuadVertex[i+5].y,this->ruedaQuadVertex[i+5].z);
			glVertex3f(this->ruedaQuadVertex[i+1].x,this->ruedaQuadVertex[i+1].y,this->ruedaQuadVertex[i+1].z);
			glVertex3f(this->ruedaQuadVertex[i].x,this->ruedaQuadVertex[i].y,this->ruedaQuadVertex[i].z);
			glEnd();

		glBegin(GL_LINE_STRIP);
			// izquierda
			glVertex3f(this->ruedaQuadVertex[i+3].x,this->ruedaQuadVertex[i+3].y,this->ruedaQuadVertex[i+3].z);
			glVertex3f(this->ruedaQuadVertex[i+7].x,this->ruedaQuadVertex[i+7].y,this->ruedaQuadVertex[i+7].z);
			glVertex3f(this->ruedaQuadVertex[i+6].x,this->ruedaQuadVertex[i+6].y,this->ruedaQuadVertex[i+6].z);
			glVertex3f(this->ruedaQuadVertex[i+2].x,this->ruedaQuadVertex[i+2].y,this->ruedaQuadVertex[i+2].z);
			glVertex3f(this->ruedaQuadVertex[i+3].x,this->ruedaQuadVertex[i+3].y,this->ruedaQuadVertex[i+3].z);
			glEnd();

	}
	
	glDisable(GL_BLEND);
	/*glColor3f(1,1,0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(miDemo->getWidth(),miDemo->getHeight(),-2);
		glVertex3f(miDemo->getWidth(),miDemo->getHeight(),2);
	glEnd();*/
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	//miDemo->quitaOrtopedico();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	
	fxradialblur->postprepareFrame();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();

	glScalef(0.7,0.7,1);
	glTranslatef(-0.25,-0.25,2);
	miDemo->ponOrtopedico(0.25,0.25*1.3);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1,1,1,0.5);
	glBindTexture(GL_TEXTURE_2D, this->text_fondo.texID);
	
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0,0); 
		glVertex3f(0,0,z_depth);
		
		glTexCoord2f(1, 0);
		glVertex3f(0.5,0, z_depth);

		glTexCoord2f(1,1);
		glVertex3f(0.5,0.5,  z_depth);

		glTexCoord2f(0,1);
		glVertex3f(0,0.5,z_depth);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	miDemo->quitaOrtopedico();

	
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glClear(GL_DEPTH_BUFFER_BIT);
	fxradialblur->perFrame(time);

	// Imagenes!
	static float y_desp=0;
	float x_desp;

	if((this->_row%8)==0) {
		y_desp=1;
	}	
	if(y_desp>0) {
		y_desp=y_desp - y_desp*y_desp*0.9;
	}
	

	if(_row<32) {
		x_desp=1-2*float(_row)/32.0;
		//y_desp=0;
	} else if(_row>96) {
		x_desp=-1-1*float(_row%32)/32.0;
		//y_desp=0;
	} else {
		x_desp=-1;
	}
	miDemo->ponOrtopedico(3,1);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glScalef(1.2,1.2,1);
	glTranslatef(x_desp,-0.25,0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	glBindTexture(GL_TEXTURE_2D, this->text_ford.texID);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0,0); 
		glVertex3f(-1,0+y_desp,z_depth);
		
		glTexCoord2f(1, 0);
		glVertex3f(1,0+y_desp, z_depth);

		glTexCoord2f(1,1);
		glVertex3f(1,0.5+y_desp,  z_depth);

		glTexCoord2f(0,1);
		glVertex3f(-1,0.5+y_desp,z_depth);
	glEnd();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	
	miDemo->quitaOrtopedico();

	miDemo->ponOrtopedico(miDemo->getWidth(), miDemo->getHeight());
	
	
	orisis.x=x_desp*miDemo->getWidth()*0.5;
	this->parts1.setOrigin(orisis);
	this->partm1.Update(time*10);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->text_particula.texID);
	partm1.Render();
	glDisable(GL_TEXTURE_2D);
	
	//glEnable(GL_DEPTH_TEST);
	
	miDemo->quitaOrtopedico();
	
	// fade
	float alfita;
	if((_row<=16)&&(_pattern==7)) {
		alfita=float(16-_row)/16.0;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfita);
		fxfade->perFrame(_time);
		glEnable(GL_DEPTH_TEST);
	}
	else if((_row>=112)&&(_pattern==14)) {
		alfita=float(_row%16)/16.0;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfita);
		fxfade->perFrame(_time);
		glEnable(GL_DEPTH_TEST);
	} else if((_row%8)==0){
		alfita=0.15;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfita);
		fxfade->perFrame(_time);
		glEnable(GL_DEPTH_TEST);
	}
	if((_row>=112)&&(_pattern==14)) {
		if((_row%2)==0) {
			glDisable(GL_DEPTH_TEST);
			fxfade->setFadeColor(1,1,1,1);
			fxfade->perFrame(_time);
			glEnable(GL_DEPTH_TEST);
		}
	}
}

void FXrueda::marear(float par1, float par2) {
		// Precalculo de la rueda
	int i;
	float ang;
	float ang_inc=360.0/float(NUMPOINTS);

	float diametro=2*3.14*radio1;

	// Me da a mi q esto chocara con las leyes del diametro y tal xD
	float alto=1.0f;
	float ancho=2.0f;
	float largo=diametro/float(NUMPOINTS); 
	float anchod2=ancho*0.5;
	float largod2=largo*0.5;
	
	float x=0.0f; // por si luego lo cambiara :-o
	Point p1,p2;
	p1.x=x;
	p2.x=0;
	ang=0;

	for(i=0;i<NUMVERTEX;i+=4) {
		//ang=ang_inc*i; // el +1 es para evitar el divbyzero
		// Lo bueno de que los otros puntos se calculen a partir de este es que asi
		// si vario la trayectoria el tunel sigue molando lo mismo XD
		p1.y=radio1*sin(ang+_time);
		p1.z=radio1*sin(par1*ang+_time);
		p2.y=radio2*sin(ang+_time);
		p2.z=radio2*sin(par1*ang+_time);
		p1.x=radio1*sin(par2*ang+_time);
		p2.x=p1.x;
		
		// empezamos con los puntitos de la muerte
		// 0
		this->ruedaQuadVertex[i].x=p1.x+anchod2;
		this->ruedaQuadVertex[i].y=p1.y;
		this->ruedaQuadVertex[i].z=p1.z;
		// 1
		this->ruedaQuadVertex[i+1].x=p2.x+anchod2;
		this->ruedaQuadVertex[i+1].y=p2.y;
		this->ruedaQuadVertex[i+1].z=p2.z;
		// 2
		this->ruedaQuadVertex[i+2].x=p2.x-anchod2;
		this->ruedaQuadVertex[i+2].y=p2.y;
		this->ruedaQuadVertex[i+2].z=p2.z;
		// 3
		this->ruedaQuadVertex[i+3].x=p1.x-anchod2;
		this->ruedaQuadVertex[i+3].y=p1.y;
		this->ruedaQuadVertex[i+3].z=p1.z;
		
		ang+=ang_inc;
	}
}
void FXrueda::init(void) {
	// asignar recursos y tal, cargar ficheros, blabla

	// Cargo las texturas
	LoadTGA(&text_fondo,"./data/bazura.tga");
	LoadTGA(&text_ford,"./data/fordtuneao3.tga");
	LoadTGA(&text_particula,"./data/minik.tga");


	// setup de la camara
	cam.SetPos(5,5,0);
	
	cam.SetLook(0,0,0.8);
	cam.setFov(120);
	cam.setFar(1,1000);

	// Precalculo de la rueda
	this->radio1=3;
	this->radio2=radio1+1;
	int i;
	float ang;
	float ang_inc=360.0/float(NUMPOINTS);
	
	float diametro=2*3.14*radio1;

	// Me da a mi q esto chocara con las leyes del diametro y tal xD
	float alto=1.0f;
	float ancho=1.0f;
	float largo=diametro/float(NUMPOINTS); 
	float anchod2=ancho*0.5;
	float largod2=largo*0.5;
	
	float x=0.0f; // por si luego lo cambiara :-o
	Point p1,p2;
	p1.x=x;
	p2.x=0;
	ang=0;
	for(i=0;i<NUMVERTEX;i+=4) {
		//ang=ang_inc*i; // el +1 es para evitar el divbyzero
		// Lo bueno de que los otros puntos se calculen a partir de este es que asi
		// si vario la trayectoria el tunel sigue molando lo mismo XD
		p1.y=radio1*sin(ang);
		p1.z=radio1*cos(ang);
		p2.y=radio2*sin(ang);
		p2.z=radio2*cos(ang);
		
		// empezamos con los puntitos de la muerte
		// 0
		this->ruedaQuadVertex[i].x=p1.x+anchod2;
		this->ruedaQuadVertex[i].y=p1.y;
		this->ruedaQuadVertex[i].z=p1.z;
		// 1
		this->ruedaQuadVertex[i+1].x=p2.x+anchod2;
		this->ruedaQuadVertex[i+1].y=p2.y;
		this->ruedaQuadVertex[i+1].z=p2.z;
		// 2
		this->ruedaQuadVertex[i+2].x=p2.x-anchod2;
		this->ruedaQuadVertex[i+2].y=p2.y;
		this->ruedaQuadVertex[i+2].z=p2.z;
		// 3
		this->ruedaQuadVertex[i+3].x=p1.x-anchod2;
		this->ruedaQuadVertex[i+3].y=p1.y;
		this->ruedaQuadVertex[i+3].z=p1.z;
		
		ang+=ang_inc;
	}

	// Hay que inicializar el sistema de particulas tb...
	this->partm1.Add(&parts1);
	parts1.setMinimumEnergy(100);
	parts1.setMinimumMass(3);
	parts1.setOrigin(orisis);
	parts1.Set(100);
}

void FXrueda::start(void) {
	glEnable(GL_SMOOTH);
	// poner los parametros del radialblur
	fxradialblur->setInc(0.015f);
	fxradialblur->setTimes(10);
	fxradialblur->setView(miDemo->getWidth(),miDemo->getHeight());
	// a ver si el viewport está pocho
	glViewport(0,0,miDemo->getWidth(),miDemo->getHeight());
	glClearColor(0,0,0,0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
}

void FXrueda::stop(void) {
	glEnable(GL_DEPTH_TEST);
}

void FXrueda::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	
}

FXrueda::FXrueda() {
}

FXrueda::~FXrueda() {
}
