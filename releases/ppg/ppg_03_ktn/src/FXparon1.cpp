#include "FXparon1.h"
#include <math.h>
// inicializar lo estático aquí...
Camera FXparon1::cam;
GLUquadricObj *FXparon1::quad;
GLUquadricObj *FXparon1::quad2;
GLUquadricObj *FXparon1::quad3;
TextureImage FXparon1::textlogo;
TextureImage FXparon1::textlaser;
	
// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXparon1::perFrame(float time)
{
	
	static float t_start = -1;
	float t_elapsed;
	static float a=0;
	static float tiempo=0;
	static float giro=0;
	static float lo=0; // longitud del 'laser'
	static float radiodisco=0; // radio de un disco espectacular
	static float dp=2.5; // este desplazamiento lo uso más abajo...

	time *= 0.001f;

	this->_time=time;
	
	if(t_start == -1)
	{
		t_start = time;
		tiempo = time;
	}
	
	t_elapsed = time - t_start;

	// para sincronizarme un poco..
	if(time-tiempo>0.02) {
		tiempo=time;
		dp-=0.016;
		giro+=0.2;
		if((this->_pattern==15) && (a<1)) {
			a+=0.1;
		}
		if(this->_pattern>=16) {
			if(lo<8000) { // esto sera de lo que crece?
				lo+=0.5;
			} else {
				lo=8000;
			}
		}
		if((_pattern>=17) && (1)) {
			radiodisco+=0.35f;//0.5*radiodisco*radiodisco;
		}
		if(radiodisco>1) {
			radiodisco=1;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//if((_pattern==15)||(_pattern==16) || _pattern==17) {
		cam.SetPos(2+3*sin(t_elapsed*0.1),2+cos(t_elapsed*0.06),4+3*sin(t_elapsed*0.3));
	//} else {
//		cam.SetPos(5*cos(time),5*sin(time),4);
//	}
	cam.toOGL();
	glMatrixMode(GL_PROJECTION);
	glRotatef(t_elapsed*11,1,1,1);

	//fxradialblur->prepareFrame();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLineWidth(1.5f);
	// ejes de la salvacion
	/*
	glLoadIdentity();
	glColor3f(1,0,0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(10,0,0);
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(0,10,0);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(0,0,10);
	glEnd();*/

	// Esos coloresss
	float r=0.7,g=0,b=0.7;
	//static float a=0.01;
	float r2=1,g2=1,b2=1;

	// auxs
	float va,vb;
	float alt;
	static float pulso=0,maxpulso=2;

	if((this->_pattern==15) ) {
		//a+=a*a*0.5;
		r2=float(_row)/64.0;
		g2=r2;
		b2=r2;
	} else {
		a=1;
	}
	// Cilindro central
	glLoadIdentity();
	if(this->_pattern==15) { // si es el primer patron...
		va=1.28-float(_row)*0.01;
		glTranslatef(0,0,va);
		glRotatef(t_elapsed*(10+_row*va),0,0,1); // y ademas gira maX
	} else if(this->_pattern==16) {
		
		glRotatef(t_elapsed*10,0,0,1);
	} else if(_pattern==17 || _pattern==18 || _pattern==19 || _pattern==20) {
		if((this->_row%8)==0) {
			pulso=maxpulso;
		}
		if(pulso>0) {
			pulso=pulso - pulso*pulso*0.071;
		}
		vb=pulso;
		glTranslatef(0,0,vb);
		glRotatef(t_elapsed*10,0,0,1);
		if(_row%16==0) {
			radiodisco=0;
		}
	}

	
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(r,g,b,a);
	gluCylinder(quad2,1.0f,1.0f,0.50f+pulso,16,8);
	glDisable(GL_BLEND);
	glColor3f(r2,g2,b2);
	gluCylinder(quad,1.0f,1.0f,0.50f+pulso,16,8);	
	
	/*// Disco cañon!
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,this->textlaser.texID);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0,1.0,1.0,0.5f);
	gluDisk(quad3,3,3+radiodisco,32,32);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);*/

	alt=(maxpulso-pulso)*0.3;
	// Cilindros exteriores
	// 1!!
	glLoadIdentity();
	glRotatef(t_elapsed*15,0,0,-100);
	glEnable(GL_BLEND);
	glColor4f(r,g,b,a);
	gluCylinder(quad2,1.7f,1.7f,0.40f+alt,8,8);
	glDisable(GL_BLEND);
	glColor3f(r2,g2,b2);
	gluCylinder(quad,1.7f,1.7f,0.40f+alt ,8,8);	

	alt=fabs(alt*2-2);
	// 2!!
	glLoadIdentity();
	glRotatef(t_elapsed*25,0,0,100);
	glEnable(GL_BLEND);
	glColor4f(r,g,b,a);
	gluCylinder(quad2,2.20f,2.20f,0.40f+alt,16,16);
	glDisable(GL_BLEND);
	glColor3f(r2,g2,b2);
	gluCylinder(quad,2.20f,2.20f,0.40f+alt,16,16);	


	

	// Un disquito no??
	glLoadIdentity();
	if(this->_pattern==15) { // si es el primer patron...
		glTranslatef(0,0,2*va);
		glRotatef(t_elapsed*(30+_row*va),0,0,-1); // y ademas gira maX
	} else {
		glRotatef(t_elapsed*30,0,0,-1);
	}
	glEnable(GL_BLEND);
	glColor4f(r,g,b,a);
	gluDisk(quad2,2.40f,2.80f,16,16);
	glDisable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glColor3f(r2,g2,b2);
	gluDisk(quad,2.40f,2.80f,16,16);	
	glDisable(GL_LINE_SMOOTH);

	// Unos discos girando no??
	int i;
	float inc;
	float dif=0.3;
	int factor;
	for(i=0;i<10;i++) {
		glLoadIdentity();
		if((i%2)==0) {
			factor=1;
		} else {
			factor=-1;
		}
		if(_pattern<17) { // en los primeros patrones está de tranqui XD
			//glTranslatef(0,0,2*va);
			glRotatef(giro*(i+1)*factor,1,0,1); 
		} else {
			glRotatef(giro*(i*2+1)*factor,1,0,1); // luego ya se anima el tema
		}
		inc=float(i)*0.4;
		
		glEnable(GL_BLEND);
		glColor4f(r,g,b,a*0.5);
		gluDisk(quad2,4.1f+inc,4.10f+inc+dif,8,8);
		glDisable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glColor3f(r2,g2,b2);
		gluDisk(quad,4.1f+inc,4.10f+inc+dif,8,8);
		glDisable(GL_LINE_SMOOTH);

	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	// a ver si consigo poner una linea? (el laser central) 
	// joerrrrrr en el eje zZzzzZ XDD!!!!!!!
	
	float btex; // base para la textura
	float texalt=0.15; // altura del rango de la textura 
	float lan=1; // ancho del 'laser'

	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,this->textlaser.texID);
	glColor4f(1,1,1,0.95);
	btex=(fmod(t_elapsed*10,100)-texalt)/100.0;
	glBegin(GL_QUADS);
		glTexCoord2f(0,btex);
		glVertex3f(-lan,0,-lo);
		glTexCoord2f(1,btex);
		glVertex3f(lan,0,-lo);
		glTexCoord2f(1,btex+texalt);
		glVertex3f(lan,0,lo);
		glTexCoord2f(0,btex+texalt);
		glVertex3f(-lan,0,lo);
	glEnd();
	glRotatef(90,0,0,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1-btex);
		glVertex3f(-lan,0,-lo);
		glTexCoord2f(1,1-btex);
		glVertex3f(lan,0,-lo);
		glTexCoord2f(1,1-btex+texalt);
		glVertex3f(lan,0,lo);
		glTexCoord2f(0,1-btex+texalt);
		glVertex3f(-lan,0,lo);
	glEnd();
	glRotatef(-90,0,0,1);
	glDisable(GL_BLEND);


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//fxradialblur->postprepareFrame();
	//fxradialblur->perFrame(_time);

	// Plano con la textura del nuevo logo
	glDisable(GL_DEPTH_TEST);
	float z_depth=0.5;
	static float xt=1;
/*	if(_pattern==15) {
		// mover el logo de izquierda al centro
		dp-=0.01*(_row);
		xt=3-dp;
	}
	if((_pattern<21)&&(_pattern>=16)) {
		//quietoparao
		dp=0;
	}
	if(_pattern==21) {
		// pos que se vaya
		dp=0.5;
	}*/

	
	miDemo->ponOrtopedico(1.25,2);

	// a ver si esto me hace el putoantialias
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA_SATURATE,GL_ONE);
	glColor4f(1,1,1,0.5);
	glBegin(GL_QUADS);
		glVertex3f(-xt*2,-xt,z_depth);
		glVertex3f(xt*2,-xt,z_depth);
		glVertex3f(xt*2,xt,z_depth);
		glVertex3f(-xt*2,xt,z_depth);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glColor4f(1,1,1,0.7);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, this->textlogo.texID);
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
	glDisable(GL_TEXTURE_2D);
	
	glDisable(GL_BLEND);
	
	miDemo->quitaOrtopedico();
	glEnable(GL_DEPTH_TEST);

	// fade
	float alfita;
	if((_row<=16)&&(_pattern==15)) {
		alfita=float(16-_row)/16.0;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfita);
		fxfade->perFrame(t_elapsed);
		glEnable(GL_DEPTH_TEST);
		fxradialblur->setTimes(16-_row%16);
		fxradialblur->setInc(0.02-(_row)*0.0025);
	}
	else if((_row>=112)&&(_pattern==20)) {
		alfita=float(_row%16)/16.0;
		glDisable(GL_DEPTH_TEST);
		fxfade->setFadeColor(1,1,1,alfita);
		fxfade->perFrame(t_elapsed);
		glEnable(GL_DEPTH_TEST);
		fxradialblur->setTimes(_row%16);
		fxradialblur->setInc(0.02);
	} else {
		if(((_row%8)==0)&&(_pattern<21)&&(_pattern>16)){
			alfita=0.15;
			glDisable(GL_DEPTH_TEST);
			fxfade->setFadeColor(1,1,1,alfita);
			fxfade->perFrame(t_elapsed);
			glEnable(GL_DEPTH_TEST);
		}
		fxradialblur->setTimes(1);
	}

}

void FXparon1::init(void) {
	// asignar recursos y tal, cargar ficheros, blabla

	this->quad=gluNewQuadric();
	gluQuadricNormals(this->quad,GL_FLAT);
	gluQuadricDrawStyle(this->quad,GLU_SILHOUETTE);

	this->quad2=gluNewQuadric();
	gluQuadricNormals(this->quad2,GL_FLAT);
	gluQuadricDrawStyle(this->quad2,GLU_FILL);

	this->quad3=gluNewQuadric();
	gluQuadricOrientation(this->quad3,GLU_OUTSIDE);
	gluQuadricNormals(this->quad3,GL_FLAT);
	gluQuadricDrawStyle(this->quad3,GLU_FILL);
	gluQuadricTexture(this->quad3,GL_TRUE);

	// setup de la camara
	cam.SetPos(2,2,2);
	cam.SetLook(0,0,-2);
	cam.setFov(60);
	cam.setFar(1,1000);

	LoadTGA(&this->textlogo,"./data/cartelin.tga");
	LoadTGA(&this->textlaser,"./data/text_laser.tga");

}

void FXparon1::start(void) {
	glEnable(GL_SMOOTH);
	// poner los parametros del radialblur
	fxradialblur->setInc(0.0071f);
	//fxradialblur->setTimes(3);
	fxradialblur->setView(miDemo->getWidth(),miDemo->getHeight());
	fxradialblur->setClearColor(0.25,0.1,0.25,0.4);
	fxradialblur->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// a ver si el viewport está pocho
	glViewport(0,0,miDemo->getWidth(),miDemo->getHeight());
	glClearColor(0,0,0,0);
	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LINE_SMOOTH);
}

void FXparon1::stop(void) {

}

void FXparon1::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	gluDeleteQuadric(this->quad);
	gluDeleteQuadric(this->quad2);
	gluDeleteQuadric(this->quad3);
	
}

FXparon1::FXparon1() {
}

FXparon1::~FXparon1() {
}
