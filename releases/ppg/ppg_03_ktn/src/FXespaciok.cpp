#include "FXespaciok.h"
#include <math.h>
// inicializar lo estático aquí...
Camera FXespaciok::cam;
TextureImage FXespaciok::text_k;
TextureImage FXespaciok::text_tunel;
TextureImage FXespaciok::text_chemical;
TextureImage FXespaciok::text_creditos_aux;
TextureImage FXespaciok::text_staff;
TextureImage FXespaciok::text_sole;
TextureImage FXespaciok::text_sara;
TextureImage FXespaciok::text_theyhave;
TextureImage FXespaciok::text_greets01;
TextureImage FXespaciok::text_greets02;
TextureImage FXespaciok::text_greets03;
TextureImage FXespaciok::text_greets04;
TextureImage FXespaciok::text_mascara;
TextureImage FXespaciok::text_allez;
TextureImage FXespaciok::text_epileptics;

Point FXespaciok::pointList[NUM_PT_ESP];
Point FXespaciok::pointListTunel[NUM_PT_ESP_TUNEL];
float FXespaciok::xinc;
float FXespaciok::yinc;
float FXespaciok::zinc;
float FXespaciok::ancho;
float FXespaciok::alto;
float FXespaciok::largo;
float FXespaciok::lado;
float FXespaciok::tunellargo;
	
// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXespaciok::perFrame(float time) {
	int i;
	static float t_start= -1;
	float t_elapsed;
	static float tiempo=0;
	static int cuantos=10;
	int dibujar=0;
	Point possicio;
	float factor_aumento;	
	
	time *= 0.001f;
	
	if(t_start == -1)
	{
		t_start = time;
	}
	
	t_elapsed = time;
	this->_time=time;
	

	if(_pattern<28) {
		factor_aumento=0.025;
		//possicio.x=0;//-7+2*sin(time);
	} else if (_pattern>31) {
		factor_aumento=-0.8;

		/*possicio.x=0;//-7+3*sin(time);
		possicio.y=0;//4+3*sin(possicio.x);
		possicio.z=2;//cos(possicio.y);*/
		
	} else {
		factor_aumento=0.4;
		/*possicio.x=0;
		possicio.y=0;//4+3*sin(possicio.x);
		possicio.z=-7+3*sin(time);//3*cos(time);*/
		
	}
	possicio.x=-3;
	possicio.y=0;
	possicio.z=0;
	cam.SetPos(possicio);	
	//cam.SetPos(15,15,15);	
	cam.setFov(80+70*sin(t_elapsed*0.1));

	if(t_elapsed-tiempo>0.025) {
		tiempo=t_elapsed;
		dibujar=1;
		for(i=0;i<NUM_PT_ESP;i++) {
			// esto segun el t
			this->pointList[i].z+=0.01;
			if(this->pointList[i].z>this->largo+lado) {
				this->pointList[i].z=-(this->largo+lado);
			}
			this->pointList[i].x+=factor_aumento*rand()/RAND_MAX;
			if(factor_aumento>0) {
				if(this->pointList[i].x>this->ancho+lado) {
					this->pointList[i].x=-(this->ancho+lado);
				}
			}
			if(factor_aumento<=0) {
				if(this->pointList[i].x<-this->ancho+lado){
					this->pointList[i].x=(this->ancho+lado);
				}
			}
	
		}
		static float iniciofin=this->tunellargo;
		static float iniciofin2=this->tunellargo*2;
		for(i=0;i<NUM_PT_ESP_TUNEL;i++) {
			this->pointListTunel[i].x+=factor_aumento;
			if(factor_aumento>0) {
				if(this->pointListTunel[i].x>iniciofin2) {
					this->pointListTunel[i].x=-iniciofin2;//+(5*ancho/float(NUM_PT_ESP_TUNEL))*i;
				}
			}

			if(factor_aumento<=0) {
				if(this->pointListTunel[i].x<-iniciofin2) {
					this->pointListTunel[i].x=iniciofin2;//+(5*ancho/float(NUM_PT_ESP_TUNEL))*i;
				}
			}

		}
	}

	if((_row%8==0)) {
		cuantos=20;
	} else {
		if(cuantos>10) {
			cuantos=cuantos-int(0.01*cuantos*cuantos);
		}
	}

	//fxradialblur->setTimes(cuantos);	
	//fxradialblur->prepareFrame(); // <-------- ahi ahi!
	glClearColor(0.51,0.01,0.51,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	cam.toOGL();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Dibujo de las "Neuronas"
	glLoadIdentity();
	//glScalef(2,2,2);
	//glRotatef(180,1,1,1);	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
	glBindTexture(GL_TEXTURE_2D, this->text_k.texID);
	glColor4f(1,1,1,0.5);
	glBegin(GL_TRIANGLES);
	
	for(i=0;i<NUM_PT_ESP;i++) {
		glTexCoord2f(0.0, 0.0);
		glVertex3f(this->pointList[i].x,this->pointList[i].y,this->pointList[i].z);
		glTexCoord2f(0,1);
		glVertex3f(this->pointList[i].x+lado,this->pointList[i].y,this->pointList[i].z);
		glTexCoord2f(1.0,1.0);
		glVertex3f(this->pointList[i].x,this->pointList[i].y,this->pointList[i].z+lado);
	}
	glEnd();
	glDisable(GL_BLEND);

	
	glDisable(GL_TEXTURE_2D);
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//fxradialblur->postprepareFrame();
	//fxradialblur->perFrame(time);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	cam.toOGL();
	glMatrixMode(GL_PROJECTION);
	glRotatef(t_elapsed*10,0,1,0);
	if(_pattern>31) {
		glRotatef(t_elapsed*5,1,0,0);
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Dibujo de las "Neuronas" (sin el blur, ahora)
	glLoadIdentity();
	//glScalef(2,2,2);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
//	glRotatef(180,1,1,1);	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
	glBindTexture(GL_TEXTURE_2D, this->text_k.texID);
	glColor4f(1,1,1,1);
	glBegin(GL_TRIANGLES);
	for(i=0;i<NUM_PT_ESP;i++) {
		glTexCoord2f(0.0, 0.0);
		glVertex3f(this->pointList[i].x,this->pointList[i].y,this->pointList[i].z);
		glTexCoord2f(0,1);
		glVertex3f(this->pointList[i].x+lado,this->pointList[i].y,this->pointList[i].z);
		glTexCoord2f(1.0,1.0);
		glVertex3f(this->pointList[i].x,this->pointList[i].y,this->pointList[i].z+lado);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glLineWidth(1);
	
	for(i=0;i<NUM_PT_ESP_TUNEL-1;i++) {
		//glVertex3f(0,this->pointList[i].y,this->ancho);
		//glVertex3f(this->ancho,this->pointList[i].y,this->ancho);
		
		
		/*
				 z
				 |
			     |
			    / ------ y
			  /
			x
		*/
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->text_tunel.texID);

		glColor4f(0.7,0.1,0.71,0.85);
		glBegin(GL_QUADS);
		// arriba
			glTexCoord2f(0,0);
			glVertex3f(this->pointListTunel[i].x,-this->ancho,-this->ancho);
			glTexCoord2f(1,0);
			glVertex3f(this->pointListTunel[i].x,-this->ancho,this->ancho);
			glTexCoord2f(1,1);
			glVertex3f(this->pointListTunel[i+1].x,-this->ancho,this->ancho);
			glTexCoord2f(0,1);
			glVertex3f(this->pointListTunel[i+1].x,-this->ancho,-this->ancho);
			
			// abajo
			glTexCoord2f(0,0);
			glVertex3f(this->pointListTunel[i].x,this->ancho,-this->ancho);
			glTexCoord2f(1,0);
			glVertex3f(this->pointListTunel[i].x,this->ancho,this->ancho);
			glTexCoord2f(1,1);
			glVertex3f(this->pointListTunel[i+1].x,this->ancho,this->ancho);
			glTexCoord2f(0,1);
			glVertex3f(this->pointListTunel[i+1].x,this->ancho,-this->ancho);

			// creo que izquierda :-o
			glTexCoord2f(0,0);
			glVertex3f(this->pointListTunel[i].x,-this->ancho,this->ancho);
			glTexCoord2f(1,0);
			glVertex3f(this->pointListTunel[i].x,this->ancho,this->ancho);
			glTexCoord2f(1,1);
			glVertex3f(this->pointListTunel[i+1].x,this->ancho,this->ancho);
			glTexCoord2f(0,1);
			glVertex3f(this->pointListTunel[i+1].x,-this->ancho,this->ancho);

			// creo que izquierda :-o
			glTexCoord2f(0,0);
			glVertex3f(this->pointListTunel[i].x,-this->ancho,-this->ancho);
			glTexCoord2f(1,0);
			glVertex3f(this->pointListTunel[i].x,this->ancho,-this->ancho);
			glTexCoord2f(1,1);
			glVertex3f(this->pointListTunel[i+1].x,this->ancho,-this->ancho);
			glTexCoord2f(0,1);
			glVertex3f(this->pointListTunel[i+1].x,-this->ancho,-this->ancho);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glColor3f(0,0,0);
		glBegin(GL_LINE_STRIP);
			glVertex3f(this->pointListTunel[i].x,-this->ancho,-this->ancho);
			glVertex3f(this->pointListTunel[i].x,this->ancho,-this->ancho);
			glVertex3f(this->pointListTunel[i].x,this->ancho,this->ancho);
			glVertex3f(this->pointListTunel[i].x,-this->ancho,this->ancho);
			glVertex3f(this->pointListTunel[i].x,-this->ancho,-this->ancho);
		glEnd();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
	/*glLineWidth(1); ///////// EJES
	glColor3f(1,0,0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(100,0,0);
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(0,100,0);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);
		glVertex3f(0,0,100);
	glEnd();*/
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	miDemo->ponOrtopedico(4,3);
	
	glEnable(GL_TEXTURE_2D);
	float xt2=1.1;
	float yt2=1.2;
	float dp;//1*cos(_time)-2;
	dp=0;//sin(time); // desplazamiento

	// la camara esta en -7,4,0
	float z_depth=1;//1*sin(_time);

	//xt2=this->pointList[i].x;
	//yt2=xt2;
	
	//glMatrixMode(GL_PROJECTION);
	//glRotatef(180+_time,1,0,0);
	// Esos CREDITOSSSSSSSSS
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	/* foto chemical */
	float chem_alpha;
	if(_pattern==25 ) {
		chem_alpha=1-float(_row/128.0);
		glLoadIdentity();
		glTranslatef(0,-0.5,0);
		glColor4f(1,1,1,chem_alpha);
		glBindTexture(GL_TEXTURE_2D, this->text_chemical.texID);
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
	}
	
	/* Adorno de fondo q esta atacao XD */
	glLoadIdentity();
	glColor4f(1,1,1,1);
	float dpx=getRand()*0.05,dpy=getRand()*0.05;
	if ( (_row==0) || (_row==56) || (_row==64) || (_row==126) ) {
		dpy+=0.3;
	}
	xt2=1.1;
	yt2=1.1;
	// no lo muestro si son los patterns d nuestra foto o no hay texto
	if(_pattern!=25 && _pattern!=26 && _pattern!=28 && _pattern!=29 && _pattern<30/* && _pattern!=31 && _pattern!=32*/) { 
	glBindTexture(GL_TEXTURE_2D, this->text_creditos_aux.texID);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0); 
		glVertex3f(-xt2*2+dpx,-yt2+dpy,z_depth);
		
		glTexCoord2f(1,0);
		glVertex3f(xt2*2+dpx,-yt2+dpy, z_depth);

		glTexCoord2f(1,1);
		glVertex3f(xt2*2+dpx,yt2+dpy,  z_depth);

		glTexCoord2f(0,1);
		glVertex3f(-xt2*2+dpx,yt2+dpy,z_depth);

		//glVertex3f(0,0,0);

	glEnd();
	}
	// lo q vamos mostrando: staff... code... etc
	if(_pattern==23 || _pattern==24) {
		xt2*=0.40;
		yt2*=0.40;
	}
	if(_pattern==23) {
		if(_row<64) {
			glBindTexture(GL_TEXTURE_2D, this->text_staff.texID);
		}
		if( (_row>=64)) {
			glBindTexture(GL_TEXTURE_2D, this->text_sole.texID);
		}
	}
	if(_pattern==24) {
		if(_row<64) {
			glBindTexture(GL_TEXTURE_2D, this->text_sara.texID);
		}
		if( (_row>=64)) {
			glBindTexture(GL_TEXTURE_2D, this->text_theyhave.texID);
		}
	}
	if(_pattern==27) {
		if(_row<32) {
			glBindTexture(GL_TEXTURE_2D, this->text_greets01.texID);
		} 
		if( (_row>=32) && (_row<64)) {
			glBindTexture(GL_TEXTURE_2D, this->text_greets02.texID);
		}
		if( (_row>=64) && (_row<96)) {
			glBindTexture(GL_TEXTURE_2D, this->text_greets03.texID);
		}
		if( (_row>=96) ) {
			glBindTexture(GL_TEXTURE_2D, this->text_greets04.texID);
		}
	}
	if(_pattern==30) {
		glBindTexture(GL_TEXTURE_2D, this->text_epileptics.texID);
	}
	if(_pattern==31 || _pattern==32) {
		glBindTexture(GL_TEXTURE_2D, this->text_allez.texID);
	}
	if(_pattern==31) {
		
		glColor4f(1,1,1,float(_row)/128.0 -getRand());
	} else if (_pattern==32) {
		glColor4f(1,1,1,1-float(_row)/128.0);
	} else {
		glColor4f(1,1,1,1);
	}

	if(_pattern!=25 && _pattern!=26 && _pattern!=28 && _pattern!=29 && _pattern<33 ) {
		glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0, 0); 
			glVertex3f(-xt2*2-dpx,-yt2-dpy,z_depth);
		
			glTexCoord2f(1,0);
			glVertex3f(xt2*2-dpx,-yt2-dpy, z_depth);

			glTexCoord2f(1,1);
			glVertex3f(xt2*2-dpx,yt2-dpy,  z_depth);

			glTexCoord2f(0,1);
			glVertex3f(-xt2*2-dpx,yt2-dpy,z_depth);

			//glVertex3f(0,0,0);

		glEnd();
	}
	// Supermascara!
	if(_pattern>=38) {
	dpx=0;
	dpy=0;
	static float resta=0;
	float raux=float(_row/128.0)*2;
	// si es mas peq es q he llegado al maximo,no actualizo la resta
	if(raux>=2.2) {
		raux=2.2;
	} else {
		// sino aun no he llegado, lo actualizo
		resta=raux;
	}
	xt2=3-resta;
	/*if(xt2<=2) {
		xt2=2;
	}*/
	yt2=xt2*2;
	glColor4f(0,0,0,1);
	glBlendFunc(GL_DST_ALPHA, GL_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, this->text_mascara.texID);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0); 
		glVertex3f(-xt2*2-dpx,-yt2-dpy,z_depth);
		
		glTexCoord2f(1,0);
		glVertex3f(xt2*2-dpx,-yt2-dpy, z_depth);

		glTexCoord2f(1,1);
		glVertex3f(xt2*2-dpx,yt2-dpy,  z_depth);

		glTexCoord2f(0,1);
		glVertex3f(-xt2*2-dpx,yt2-dpy,z_depth);

		//glVertex3f(0,0,0);

	glEnd();
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	miDemo->quitaOrtopedico();

	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();



	/* si patron ==23 */
	/* filas -> 0, 56, 64, 126 */
	if( ((_pattern==23) || (_pattern==24) || (_pattern==25)) && ( (_row==0) || (_row==56) || (_row==64) || (_row==126) )) {
		fxfade->perFrame(t_elapsed);
	}
	if((_pattern>31) && (_row%2==0)) {
		fxfade->setFadeColor(1,1,1,0.30);
		fxfade->perFrame(t_elapsed);
	}
	glEnable(GL_DEPTH_TEST);
}

void FXespaciok::init(void) {
	// asignar recursos y tal, cargar ficheros, blabla

	// Cargo las texturas
	LoadTGA(&text_k,"./data/ppg03.tga");

	LoadTGA(&this->text_tunel,"./data/text_laser.tga");

	// creditos
	LoadTGA(&this->text_chemical,"./data/creditosdeverdad.tga");
	LoadTGA(&this->text_creditos_aux,"./data/creditos_aux.tga");
	LoadTGA(&this->text_staff,"./data/creditos_staff.tga");
	LoadTGA(&this->text_sole,"./data/creditos_sole.tga");
	LoadTGA(&this->text_sara,"./data/creditos_sara.tga");
	LoadTGA(&this->text_theyhave,"./data/creditos_theyhave.tga");
	
	LoadTGA(&this->text_greets01,"./data/greets_1.tga");
	LoadTGA(&this->text_greets02,"./data/greets_2.tga");
	LoadTGA(&this->text_greets03,"./data/greets_3.tga");
	LoadTGA(&this->text_greets04,"./data/greets_4.tga");

	LoadTGA(&this->text_allez,"./data/allez.tga");
	LoadTGA(&this->text_epileptics,"./data/epileptics.tga");

	LoadTGA(&this->text_mascara,"./data/fin.tga");


	// setup de la camara
	//cam.SetPos(10,10,10);
	cam.SetPos(-7,4,0);
	cam.SetLook(1,0,0.8);
	cam.setFov(10);//30
	cam.setFar(1,1000);

//	this->conPrec=5;

	
	this->ancho=5;
	this->alto=ancho;
	this->largo=ancho;
	float origenx=-ancho;
	float origeny=-alto;
	float origenz=-largo;
	xinc=2*ancho/float(NUM_PT_ESP_X);
	yinc=2*alto/float(NUM_PT_ESP_Y);
	zinc=2*largo/float(NUM_PT_ESP_Z);
	this->lado=1.5*ancho/(NUM_PT_ESP_X);
	
	this->tunellargo=50;
	
	int i,j,k,index=0;
//	int x,y,z;
//	int conexion;
	for(i=0;i<NUM_PT_ESP_X;i++) {
		for(j=0;j<NUM_PT_ESP_Y;j++) {
			for(k=0;k<NUM_PT_ESP_Z;k++) {
				this->pointList[index].x=origenx+xinc*i;
				this->pointList[index].y=origeny+yinc*j;
				this->pointList[index].z=origenz+zinc*k;
				index++;
			}
		}
	}

	for(i=0;i<NUM_PT_ESP_TUNEL;i++) {
		this->pointListTunel[i].x=-this->tunellargo+(2*this->tunellargo/float(NUM_PT_ESP_TUNEL))*i;
	}
}

void FXespaciok::start(void) {
	glEnable(GL_SMOOTH);
	// poner los parametros del radialblur
	fxradialblur->setInc(0.01f);
	fxradialblur->setTimes(10);
	fxradialblur->setView(miDemo->getWidth(),miDemo->getHeight());
	//fxradialblur->setClearColor(0.25,0.1,0.5,1);
	fxradialblur->setClearColor(0,0,0,0.5);
	fxradialblur->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// a ver si el viewport está pocho
	glViewport(0,0,miDemo->getWidth(),miDemo->getHeight());
	glClearColor(0,0,0,0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glPointSize(4);
	glEnable(GL_LINE_SMOOTH);
}

void FXespaciok::stop(void) {
	glEnable(GL_DEPTH_TEST);
}

void FXespaciok::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	
}

FXespaciok::FXespaciok() {
}

FXespaciok::~FXespaciok() {
}
