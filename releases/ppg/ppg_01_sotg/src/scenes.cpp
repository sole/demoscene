#include "my_opengl.h"
#include <math.h>
#include "math3D.h"
#include "Camera.h"
#include <stdlib.h>
#include "textures.h"
#include "Particles.h"
#include "Path.h"
#include "scenes.h"


#include "Mesh.h"

#include "Demo.h"
extern Demo *miDemo;

#include "Music.h"
extern Music miMusic;

int currWidth=640;//miDemo->getWidth();
int currHeight=480;//miDemo->getHeight();

// Texturas
TextureImage textFemenino;
TextureImage textScene,textOf,textThe,textGirls,textNetUnk;
TextureImage textSilueta;
TextureImage textParticula;
TextureImage textPattern;
TextureImage textRulez;
TextureImage textKripto;
TextureImage text4segundos;
TextureImage textFlecha;
TextureImage textKissDa2,textKissDa2b,textKissDa2c,textKissDa2d;
TextureImage textArial;
TextureImage textPixel;
TextureImage textTiaBuena;
TextureImage textWerule,textWerule2;
TextureImage textGirlCool;
TextureImage textHumo;
TextureImage textCirculo;
TextureImage textJiji;



float textPosition[]={0, //A1
					23, // B2
					44, //c3
					65, // d4
					87,// e 5
					109, // f 6
					122, // g 7 
					143, // h 8
					165,//i 9 
					173,//j 10
					183,//k 11
					204,//l 12
					212,//m 13 
					246,//n 14
					267,//o 15
					291,//p 16
					314,//q 17
					336,//r 18
					350,//s 19
					369,//t 20
					381,//u 21
					402,//v 22
					422,//w 23
					452,//x 24
					472,//y 25
					492,//z 26
					512
					}; // posX

float textWidth[]={23,}; // creo q esto me sobra!!

// Algunas mallas, del agrado de todos
Mesh malla;

// Path
Path pathCreditos;

// unas particulas
ParticleSystem parts1;
ParticleManager partm1;
Particle particula1, particula2,misparticulas[MAXPARTICLES];

// porque no?
#define PI 3.1415926535

// Array de positionsss
#define NUMOBJS 100
#define MIMAXX 15
float posiciones[NUMOBJS][3];
#define NUMFLES 25
float posflechas[NUMOBJS][3];

// Variables del amor-para los creditos // ¿Que quiero decir con eso? :-?
#define INTERV 19
float texPos[INTERV+1][INTERV+1][3];
float quadPos[INTERV+1][INTERV+1][3];
float randQuadPos[INTERV+1][INTERV+1][3];

// Mas bazura, para el radial blur ese
float		vertexes[4][3];										
float		normal[3];											
GLuint		BlurTexture;
int 		blurTextureSize = 256;

void setCurrentHeight(int _height) {
	currHeight=_height;
}

void setCurrentWidth(int _width) {
	currWidth=_width;
}

/*void ponOrtopedico(void) {
	
	// Ahora pongo el modo ortho-pedico 
	glViewport(0,0,640,480);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glOrtho(-float(640)/2,float(640)/2,-float(480)/2,float(480)/2,0.10f,200.0f);
}
*/

void ponOrtopedico(float xres, float yres ) {
// TODO miDemo->ponOrtopedico
	/*// Ahora pongo el modo ortho-pedico 
	glViewport(0,0,640,480);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glOrtho(-float(xres)/2,float(xres)/2,-float(yres)/2,float(yres)/2,0.10f,200.0f);*/
	miDemo->ponOrtopedico(xres, yres);
}


void quitaOrtopedico(void) {
	// restauro el modo que hubiera antes
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	miDemo->quitaOrtopedico();
}
void initScenes(void) {
	// Aqui preparo las texturas y ta l....
	printf("Loading textures...\n");
	LoadTGA(&textScene,"./data/scene.tga");
	LoadTGA(&textOf,"./data/of.tga");
	LoadTGA(&textThe,"./data/the.tga");
	LoadTGA(&textGirls,"./data/girls.tga");
	LoadTGA(&textFemenino,"./data/femenino.tga");
	LoadTGA(&textNetUnk,"./data/fresapower.tga");
	LoadTGA(&textSilueta,"./data/siluetas.tga");
	LoadTGA(&textParticula,"./data/particu.tga");
	LoadTGA(&textPattern,"./data/pattern.tga");
	LoadTGA(&textRulez,"./data/rulez.tga");
	//LoadTGA(&textKewl,"./data/yeah.tga");
	LoadTGA(&text4segundos,"./data/4segundos.tga");
	//LoadTGA(&textFFW,"./data/ffw.tga");
	LoadTGA(&textFlecha,"./data/flecha.tga");
	LoadTGA(&textArial,"./data/textarial.tga");
	LoadTGA(&textPixel,"./data/texturepix.tga");
	LoadTGA(&textTiaBuena,"./data/tiabuena.tga");
	LoadTGA(&textWerule,"./data/tangaflower.tga");
	LoadTGA(&textWerule2,"./data/tangaflower2.tga");
	LoadTGA(&textGirlCool,"./data/girlcool.tga");
	LoadTGA(&textHumo,"./data/humo.tga");
	LoadTGA(&textCirculo,"./data/circulo.tga");
	
	printf("Loading meshes...\n");
	malla.loadMesh("./data/toro.ase");

	printf("Loading paths...\n");
	pathCreditos.loadPath("./data/texto3.ase");
	pathCreditos.scale(2.2,2.2,1);

	// PArticulas
	partm1.Add(&parts1);
	//parts1.Add(&particula1);
	//parts1.Add(&particula2);
	
//	int ip; // ip es indice de particulas, no internet protocol XD
	//float duracion=1;
	parts1.setMinimumEnergy(100);
	parts1.setMinimumMass(3);

	Point orisis;
	pathCreditos.getPointAt(0,&orisis);
	/*orisis.x=10;
	orisis.y=10;//*cos(ang/20);
	orisis.z=0;*/
	//origen.x=x2;
	//origen.y=y2;
	parts1.setOrigin(orisis);
	parts1.Set(100);
	

	printf("Precalc...\n");
	// También quiero precalcular esa cuadricula divina...
	printf("Precalc::quads\n");
	int i,j;
	float longint;
	float floati,floatj;
	
	longint=1/INTERV;
	for(i=0;i<=INTERV;i++) {
		floati=float(i);
		for(j=0;j<=INTERV;j++) {
			floatj=float(j);
			// la textura va de 0 a 1
			texPos[i][j][0]=(floati)/INTERV; // x
			texPos[i][j][1]=(floatj)/INTERV; // y
			texPos[i][j][2]=0.0f; // z

			// los 'quads' van de -1 a 1
			quadPos[i][j][0]=-1+2*(floati)/INTERV; // x
			quadPos[i][j][1]=-1+2*(floatj)/INTERV; // y
			quadPos[i][j][2]=0.0f; // z

			randQuadPos[i][j][0]=2*(float(rand())/RAND_MAX)-1; // de -1..1
			randQuadPos[i][j][1]=2*(float(rand())/RAND_MAX)-1; // de -1..1
			randQuadPos[i][j][2]=0.0f;

			
		}
	}

	

	// Y calcular las posiciones de los objetos
	printf("Precalc::meshpos\n");
	for(i=0;i<NUMOBJS;i++) {
		posiciones[i][0]=float(rand())/RAND_MAX*MIMAXX-float(rand())/RAND_MAX*MIMAXX;
		posiciones[i][1]=float(rand())/RAND_MAX*MIMAXX-float(rand())/RAND_MAX*MIMAXX;
		posiciones[i][2]=float(rand())/RAND_MAX*MIMAXX-float(rand())/RAND_MAX*MIMAXX;
	}

	// Y calcular las posiciones de las flechitas
	// Todas las demos estan llenas de flechas. Qué poca imaginacion tenemos XD
	printf("Precalc::arrowpos\n");
	for(i=0;i<NUMFLES;i++) {
		posflechas[i][0]=2*sin((PI/NUMFLES)*i);//float(rand())/RAND_MAX*MIMAXX-float(rand())/RAND_MAX*MIMAXX;
		posflechas[i][1]=float(rand())/RAND_MAX*MIMAXX-float(rand())/RAND_MAX*MIMAXX;
		// atencion q la tercera componente es la ESCALA
		posflechas[i][2]=7+float(rand())/RAND_MAX*30;
		
	}

	printf("Precalc::Additional textures...\n");
	
	// LA blur textura
	BlurTexture = EmptyTexture();

	// Finalmente, ¿que altura? ¿que anchura?
	currWidth = miDemo->getWidth();
	currHeight = miDemo->getHeight();
	
	glViewport(0,0,(GLsizei) currWidth,(GLsizei) currHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glFrustum(-1.0,1.0,-1.0,1.0,1.0,20.0);
	glMatrixMode(GL_MODELVIEW);
}

void finishScenes(void)
{
	glDeleteTextures(1,&BlurTexture);
}

void ejes(void) {
	glLineWidth(3.0f);
	glColor3f(1.0f,0.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1000.0f,0.0f,0.0f); // X
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(-1000.0f,0.0f,0.0f); // X neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.0f,1.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1000.0f,0.0f); // y
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,-1000.0f,0.0f); // y neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.0f,0.0,1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1000.0f); // z
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,-1000.0f); // z neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0f);
	
}


void drawScanLines(void) {
	// Si llamo a esta función después de todas las demás, pone sobre el resto
	// del dibujo 256 "scanlines"
	float ancho, alto,ancholinea,brillo;
	int i;

	ancho = currWidth;
	alto = currHeight;

	ancholinea = alto / 256.0f;
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(ancholinea);
	
	float halfalto = ancho/2, halfancho = ancho/2;
	
	glBegin(GL_LINES);
	for(i=-halfalto;i<=halfalto;i+=ancholinea)
	{
		brillo=((float)rand())/RAND_MAX;
		glColor4f(brillo,brillo,brillo,0.20);
		
		glVertex3f(-halfancho,i,0);
		glVertex3f(halfancho,i,0);
	}
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix(); // Restauro lo que hubiera del modelo ...
}

void drawTVNoise(void) {
/* esta es muy parecida a las scanlines, pero aqui lo que hago es dibujar
'quads' para hacer ruido de television ... */

	float ancho, alto,anchocuad,altocuad,brillo;
	float i,j;

	// Preparo mis datillos
	ancho = currWidth;
	alto = currHeight;
	float halfalto = ancho/2, halfancho = ancho/2;	

	anchocuad = ancho / 256.0f;
	altocuad = alto / 256.0f;
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	
	for(i=-halfalto; i<= halfalto; i+=altocuad) {
		for(j=-halfancho;j<=halfancho;j+=anchocuad) {
				
			brillo=((float)rand())/RAND_MAX;
			glColor4f(brillo,brillo,brillo,0.50);

			glVertex3f(j,i,0);
			glVertex3f(j+anchocuad,i,0);
			glVertex3f(j+anchocuad,i-altocuad,0);
			glVertex3f(j,i-altocuad,0);
		}
	}
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix(); // Restauro lo que hubiera del modelo ...
}

/* Scena circulos........*/
void circulo(float xpos,float ypos, float radio) {
	int i;
	//glEnable(GL_POLYGON_SMOOTH );
	
	glBegin(GL_POLYGON );
	for(i=1;i<=TRIGPREC;i+=20) {
		//glColor3f(getSinTable(i),getCosTable(i),ypos + radio*getCosTable(i));
		glVertex3f(xpos + radio*getSinTable(i), ypos + radio*getCosTable(i),0);
	}
	//glVertex3f(xpos+radio*getSinTable(0),ypos+radio*getCosTable(0),0);
	glEnd();
}

void disco(float xpos,float ypos, float radio1, float radio2) {
	int i;
	//glEnable(GL_POLYGON_SMOOTH );
	
	glBegin(GL_TRIANGLE_STRIP );
	//glBegin(GL_LINE_STRIP);
	for(i=1;i<=TRIGPREC;i+=8) {
		//glColor3f(getSinTable(i),getCosTable(i),ypos + radio1*getCosTable(i));
		glVertex3f(xpos + radio1*getSinTable(i), ypos + radio1*getCosTable(i),0);
		//glColor3f(getSinTable(i),getCosTable(i),ypos + radio2*getCosTable(i));
		glVertex3f(xpos + radio2*getSinTable((i+1)%TRIGPREC) , ypos + radio2*getCosTable((i+1)%TRIGPREC),0);
	}
	glVertex3f(xpos+radio1*getSinTable(1),ypos+radio1*getCosTable(1),0);
	glVertex3f(xpos + radio2*getSinTable(2) , ypos + radio2*getCosTable(2),0);
	glEnd();
}

void discoWire(float xpos,float ypos, float radio1, float radio2) {
	int i;
	//glEnable(GL_POLYGON_SMOOTH );
	
	glBegin(GL_LINE_STRIP );
	//glBegin(GL_LINE_STRIP);
	for(i=1;i<=TRIGPREC;i+=16) {
		//glColor3f(getSinTable(i),getCosTable(i),ypos + radio1*getCosTable(i));
		glVertex3f(xpos + radio1*getSinTable(i), ypos + radio1*getCosTable(i),0);
		//glColor3f(getSinTable(i),getCosTable(i),ypos + radio2*getCosTable(i));
		glVertex3f(xpos + radio2*getSinTable((i+1)%TRIGPREC) , ypos + radio2*getCosTable((i+1)%TRIGPREC),0);
	}
	glVertex3f(xpos+radio1*getSinTable(1),ypos+radio1*getCosTable(1),0);
	glVertex3f(xpos + radio2*getSinTable(2) , ypos + radio2*getCosTable(2),0);
	glEnd();
}

void sceneCircles(int row) {
	int i,modulo2,dif=40,an=10;
	float x1,y1,x2,y2;
	int x,y;
	static float ang=0,ang2=180;
	static float pulso; // lo usare para darle "anchuras" de golpe a los discos
	static float pasoporc=0;
	static float ancho=currWidth; 
	static float alto=currHeight;

	float tick;
	static float oldtick=0,oldtick2=0;
	float tickdif;
	
	static float alphalevel=0;
	if((row>=0)&&(row<32)&&(alphalevel<1)) {
		alphalevel+=0.0251;
	}
	if((row>=120)&&(row<128)) {
		alphalevel-=0.0251;
	}

	// Limpio la pantallita y pongo un amarillo chillon
	//glClearColor(0.7,0.7,0.0,1.0);
	glClearColor(1,1,0.72,1.0);//Sara
	glClear(GL_COLOR_BUFFER_BIT);
	// Ahora pongo el modo ortho-pedico para ver circulitos bien proporcionados
	
	ponOrtopedico();
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// dibujo en si
	
	tick = miMusic.getSeconds();
	tickdif = tick - oldtick;
	oldtick = tick;
	
	ang = tick * 6;
	ang2 = 100 + ang;
	
	x1=50*cos(ang2)+30*sin(ang);
	y1=40*cos(ang);
	x2=20*sin(ang);
	y2=(30-pulso)*cos(ang+pulso);
	
	if((row%4)==0) {
		pulso=20;
	}
	
	if(pulso > 0)
	{
		pulso -= tickdif*4;
	}

	
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR); // esta variante era curiosa
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
	
	float idif;

	if(row%4==0) {
		y1+=5;
		y2+=5;
	}
	
	for(i=40;i>0;i--) {
		an=10+x1/2 + y1/2 + pulso;
		modulo2=i%2;
		if((modulo2)==0) {
			//glColor4f(1,0,0,0.3);
			glColor4f(1,1,0,alphalevel/3);//sara
		} else {
			//glColor4f(0,1,0,0.3);
			glColor4f(1,0.14,0.14,alphalevel/3);//sara
		}
		//circulo(0,0,100-i*10);
		glEnable(GL_BLEND);
		idif=i*dif;

		//disco(0+x+2*y,0+y+5*x,idif,an+idif);
		//x1+=0.2;
		
		
		if((row>=0)&&(row<32)) {
			disco(x1,y1,idif,an+idif);
		}
		if((row>=32)&&(row<64)) {
			disco(x1+x2,y1-2*y2,idif,an+idif);
		}
		if((row>=64)&&(row<96)) {
			disco(x1*3+x2,y1+y2,idif,an+idif);
		}
		if((row>=96)&&(row<128)) {
			disco(x1*1.5-x2*4,y1,idif,an+idif);
		}
		
		
		if((modulo2)==0) {
			//glColor4f(1,0,0,0.3);
			glColor4f(1,1,0,alphalevel/3);//sara
		} else {
			//glColor4f(0,1,0,0.3);
			glColor4f(1,0.14,0.14,alphalevel/3);//sara
		}
		
		if((row>=0)&&(row<32)) {
			disco(x2,y2,idif,an+idif);
		}
		if((row>=32)&&(row<64)) {
			disco(y2,x2,idif,an+idif);
		}
		if((row>=64)&&(row<96)) {
			disco(x2,y2,idif,an+idif);
		}
		if((row>=96)&&(row<128)) {
			disco(y2,x2,idif,an+idif);
		}
		
		glDisable(GL_BLEND);
	}


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glShadeModel(GL_SMOOTH);	
	
	
	static float quad[INTERV+1][INTERV+1][3];
	float addi;
	//pasoporc=(float((row%64)%16))/16;
	if((row%4)==0) {
		addi=0.25;
	} else {
		addi=0;
	}
	for(x=0;x<=INTERV;x++) {
		for(y=0;y<=INTERV;y++) {
			quad[x][y][2]=quadPos[x][y][2];
			quad[x][y][0]=quadPos[x][y][0]+0.015*sin(x+ang+y); // I have added the extra +y in the sin, it looks funkier this way
			quad[x][y][1]=quadPos[x][y][1]+0.015*cos(y+ang);
		}
	}
	if((row==60)&&(pasoporc>=1)) {
		pasoporc=0;
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(330,250,1);
	

	glColor4f(0.0,0.0,0.0,alphalevel);
	glPointSize(4.0);
	glBindTexture(GL_TEXTURE_2D, textSilueta.texID);
	
	/*if(row%2==0)
	{
		glBlendFunc(GL_DST_ALPHA, GL_SRC_ALPHA); // Esta lo hacía inverso 
	}
	else
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}*/
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	for(x=0;x<=INTERV-1;x++)
	{
		for(y=0;y<=INTERV-1;y++)
		{
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(texPos[x][y][0], texPos[x][y][1]); 
			glVertex3f(quad[x][y][0], quad[x][y][1],  0.0f);
		
			glTexCoord2f(texPos[x+1][y][0], texPos[x+1][y][1]);
			glVertex3f( quad[x+1][y][0], quad[x+1][y][1],  0.0f);

			glTexCoord2f(texPos[x+1][y+1][0], texPos[x+1][y+1][1]);
			glVertex3f( quad[x+1][y+1][0], quad[x+1][y+1][1],  0.0f);

			glTexCoord2f(texPos[x][y+1][0], texPos[x][y+1][1]);
			glVertex3f(quad[x][y+1][0], quad[x][y+1][1],  0.0f);
		}
	}
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// *************** CREDITS

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glScalef(0.6,0.8,0.7);

	Point origen;
	Point auxPoint;
	glLineWidth(4); // Was 8 but it was a bit too thick
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	
	glColor3f(1,1-alphalevel,0.72-alphalevel);
	static int ptosporfila=int(float(pathCreditos.getNumICP())/80.0f);
	
	int maxindex=ptosporfila*row;
	
	glDisable(GL_BLEND);
	float sc;
	
	glBegin(GL_LINE_STRIP);
		sc=1;
		for(int kk=0;kk<=maxindex;kk++) {
			pathCreditos.getPointAt(kk,&auxPoint);
			glVertex3f(auxPoint.x*sc,auxPoint.y*sc,auxPoint.z*sc);
		}
	glEnd();
	glColor3f(1,1-alphalevel,0.72-alphalevel);
	pathCreditos.getPointAt(maxindex,&origen);
	parts1.setOrigin(origen);
	partm1.Update(miMusic.getMilliseconds());
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textParticula.texID);
	partm1.Render();
	
	glDisable(GL_TEXTURE_2D);
	
	// Rayo LassSer!
	if(row<81) {
		glLineWidth(1);
	glBegin(GL_LINES);
		glVertex3f(0,-alto,0);
		glVertex3f(origen.x,origen.y,origen.z);
	glEnd();
	}
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	quitaOrtopedico();

}

void sceneSimbolo(int row) {
	/*
		Escena en la que sale un simbolo femenino!!
		Para impactar al personal XDD
	*/
	float alpha;
	float mod32;
	//float ancho,alto;

	// Preparo mis datillos
	mod32=(float)(row%32);
	static float ancho=currWidth; 
	static float alto=currHeight;

	// Limpio la pantallita 
	glClearColor(0.0,0.0,0.0+(float)row/128,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	ponOrtopedico();
	drawTVNoise();
	quitaOrtopedico();
	
	ponOrtopedico(2, 2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// ruido televisivo
	
	
	// here comes the symbol
	glLoadIdentity();

	float scale_factor = map(row, 0, 127, 4, 1);
	glScalef(scale_factor * currHeight * 1.0f / currWidth, scale_factor, 1);
	glRotatef(128-row, 0,0,0.3);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	glBindTexture(GL_TEXTURE_2D, textFemenino.texID);
	
	// La transparencia será en función de las filas... Como siempre
	alpha=((float)row)/32.0;
	
	glColor4f(1.0,1.0,1.0,alpha);
	glBegin(GL_QUADS);
		
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);
	
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	
	
	glPopMatrix();
	quitaOrtopedico();
	
	ponOrtopedico();
	
	drawScanLines();
	// restauro el modo que hubiera antes
	quitaOrtopedico();
}

void sceneLatidos(int row) {
	float mod16,mod32,mod64;
	
	// Limpio la pantallita 
	glClearColor(1.0,1.0,0.7,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	ponOrtopedico(2,2);

	mod16=(float)(row%16);
	mod32=(float)(row%32);
	mod64=(float)(row%64);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//glScalef(WIDTH+mod32,HEIGHT+mod32,1);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	if((row>=0) && (row<16)) {
		glBindTexture(GL_TEXTURE_2D, textScene.texID);
	}
	if((row>=16) && (row<32)) {
		glBindTexture(GL_TEXTURE_2D, textOf.texID);
	}
	if((row>=32) && (row<48)) {
		glBindTexture(GL_TEXTURE_2D, textThe.texID);
	}
	if((row>=48) && (row<64)) {
		glBindTexture(GL_TEXTURE_2D, textGirls.texID);
	}
	if((row>=64) && (row<127)) {
		glBindTexture(GL_TEXTURE_2D, textNetUnk.texID);
	}

	float alphalevel=0;
	
	if((mod16>=0)&&(mod16<7))
	{
		alphalevel = map(mod16, 0, 7, 0, 1);
	}
	if((mod16>=10)&&(mod16<16))
	{
		alphalevel = map(mod16, 10, 16, 1, 0);
	}
	else
	{
		alphalevel = 1;
	}
	
	glColor4f(1.0,1.0,1.0,alphalevel);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);

	glEnd();	
	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();// del modelo

	quitaOrtopedico();
}

void sceneRotante(int row, float tiempo) {
	// La TIPICA escena con la camara girando alrededor de una cosa pulsante
	Camera cam;
	float x,y,z,radi,alpha;
	static float ang=0;
	int i;
	static float ancho=currWidth; 
	static float alto=currHeight;
	static float alinc=-1.0f; // Lo que le resto al alpha
	static float oldtick;
	float tick=miMusic.getSeconds();
	float tickdif;

	if(tick!=oldtick) {
		tickdif = tick-oldtick;
		ang+=5*(tickdif);
		oldtick=tick;
		alinc+=1.0*tickdif;
	}

	static float alphalevel=0;
	if((row>=0)&&(row<32)&&(alphalevel<1)) {
		alphalevel+=0.0251;
	}
	// Calculo la nueva posicion de la camara
	radi=2.5;
	x=radi*sin(ang);
	y=radi*cos(ang);
	z=radi*sin(ang/2);

	// La xiquetakewl o tiabuena de ayame!!
	// ponOrtopedico(740,580);
	ponOrtopedico();
	
	
	float val=1.0f/64.0f*row;
	
	glColor4f(1,1,1,0.7);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	float scale;
	
	if((row>=0)&&(row<64)) {
		scale = map(row, 0, 64, 2, 0.85f);
		glColor4f(1,1,1,1);
	}
	else if((row>=64)&&(row<112)) {
		scale = 0.85f;
		glColor4f(1,1,1,1);
	}
	else
	{
		scale = map(row, 112, 128, 0.85f, 3);
		glColor4f(1,1,1, map(row, 112, 128, 1, 0));
	}

	glScalef(scale * alto * 2, scale * alto, 1);
	
	/*if(row<64) {
		glScalef((1+(128.0-row*2)/128.0)*ancho,(1+(128.0-row*2)/128.0)*alto/1.5,1);
		glColor4f(1,1,1,row*1.0/64);
	}
	if((row>=64)&&(row<112)) {
		glScalef(ancho,alto/1.3,1);
		glColor4f(1,1,1,1);
	}
	if(row>=112) {
		glScalef((1+(float(row%112))/4.0)*ancho,(1+(float(row%112))/4.0)*alto/1.5,1);
		glColor4f(1,1,1,0.7-(float(row%112))/10);
	}*/
	
	glTranslatef(0.1*x,0.1*y,0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textTiaBuena.texID);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	quitaOrtopedico();


	cam.SetPos(x,y,z);
	cam.setFar(1,20);	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	cam.toOGL();
	

	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	glEnable(GL_LINE_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//float ancho=3/20;
	if((row%4)==0) {
		alpha=-0.8;
	} else {
		alpha=0;
	}
	// CUBOSSSSSSSSS!!!
	glLineWidth(1);
	
	for(i=1;i<40;i++) {
		// glRotatef(ang/(float(i))+i*2,1,1,1);
		glRotatef(i, 1,1,1);
		glColor4f(0.8+alpha,0.8+alpha,0.8+alpha,0.1 /*0.4/(float(i))+alinc*/);
		float cubeSize = 2.0f / (float(i));
		drawCube(true, cubeSize);
		glColor4f(0-alpha,0-alpha,0-alpha,0.3-alpha+alinc);

		drawCube(false, cubeSize);
	}
	glDisable(GL_BLEND);
	//ejes();

	// Restauro el modelo anterior
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	// Restauro la perspectiva anterior
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	}

void sceneRotante2(int row, float tiempo) {
	// La TIPICA escena con la camara girando alrededor de una cosa pulsante
	Camera cam;
	float x,y,z,radi,alpha;
	static float ang=0;
	int i;
	static int oldrow;
	static float anginc=0;
	static float ancho=currWidth; 
	static float alto=currHeight;
	static float oldtick;
	float tick=miMusic.getSeconds();

	if(tick!=oldtick) {
		ang+=1.8*(tick-oldtick);
		oldtick=tick;
		if(anginc>0) {
			anginc-=0.015;
		}
	}
	// Calculo la nueva posicion de la camara
	radi=3-7*anginc;
	x=radi*sin(ang+anginc)+2;
	y=radi*cos(ang+anginc);
	z=radi*sin((ang+anginc)/2);

	//ang+=0.15;
	// Calculo la nueva posicion de la camara
	/*radi=3.5;
	x=radi*sin(ang);
	y=radi*cos(ang);
	z=radi*sin(ang/2);*/
	
	if((row%4)==0) {
		alpha=-0.8;
		
	} else {
		alpha=0;
	}

	if(row%8==0) {
		anginc=0.15;
	}

	// Se limpia la pantalla
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);




	// las paridas en pantalla siempre quedan bien ... O sea, un poco de mierda para el fondo
	// en plan rotozoomer
	ponOrtopedico(740,580);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-0.25,0,0);
	glRotatef((ang)*100,0,0,1);
	float scala=(3.5+cos(ang))*0.45;
	//glScalef((2+cos(ang))*ancho,(2+sin(ang)*cos(2*ang))*alto,1);
	
	glScalef(ancho*scala,ancho*scala,1);
	glColor4f(1,1,1,0.7);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textWerule.texID);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	quitaOrtopedico();


	ponOrtopedico();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-0.25,0,0);
	glRotatef(-(ang)*100,0,0,1);
	scala=(2.5+cos(ang))*0.65;
	//glScalef((2+cos(ang))*ancho,(2+sin(ang)*cos(2*ang))*alto,1);
	
	glScalef(ancho*scala,ancho*scala,1);
	glColor4f(1,1,1,0.7);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textWerule2.texID);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	quitaOrtopedico();

	ponOrtopedico();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//glRotatef(-(ang)*10,0,0,1);
	glScalef(ancho/2,alto/2,1);
	glColor4f(1,1,1,0.4);
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	if(row<112) {
		int cual=row%8;
		switch(cual) {
			case 0:
			case 1:	glBindTexture(GL_TEXTURE_2D, textScene.texID);break;
			case 2:
			case 3:	glBindTexture(GL_TEXTURE_2D, textOf.texID);break;
			case 4:
			case 5:	glBindTexture(GL_TEXTURE_2D, textThe.texID);break;
			case 6:
			case 7:glBindTexture(GL_TEXTURE_2D, textGirls.texID);break;
		}
	} else {
		glBindTexture(GL_TEXTURE_2D,textRulez.texID);
		if(row!=oldrow) {
			alpha=1;
			oldrow=row;
		}
		alpha-=0.2;
		glColor4f(1,1,1,alpha);
	}
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	quitaOrtopedico();

	//-----cubosinicio
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	cam.SetPos(x,y,z);
	cam.setFar(1,20);
	cam.toOGL();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_LINE_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(0.7);
	float argumento=0.1;
	float numcubos=25.0f;
	static float ainc=1/numcubos;
	static float ginc=2*PI*ainc;
	float ccolor;

	/*for(i=numcubos;i>1;i-=0.5) {	
		argumento+=0.015;
		float cubeSize = 2.0f / (float(i));
		ccolor=0.3+alpha;

		glRotatef(ginc*i,1,1,1);
		glColor4f(ccolor,ccolor,ccolor,ccolor*0.25);
		
		drawCube(true, cubeSize);
		
		ccolor=0-alpha;
		glColor4f(ccolor,ccolor,ccolor,0.3-alpha);
		drawCube(false, cubeSize);
	}*/
	float alinc=0.2f;
	for(i=1;i<40;i++) {
		// glRotatef(ang/(float(i))+i*2,1,1,1);
		glRotatef(i, 1,1,1);
		glColor4f(0.8+alpha,0.8+alpha,0.8+alpha,0.1 /*0.4/(float(i))+alinc*/);
		float cubeSize = 2.0f / (float(i));
		drawCube(true, cubeSize);
		glColor4f(0-alpha,0-alpha,0-alpha,0.3-alpha+alinc);

		drawCube(false, cubeSize);
	}
	
	glDisable(GL_BLEND);
	//ejes();

	// Restauro el modelo anterior
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	// Restauro la perspectiva anterior
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// cubosfin--------------	
}

void sceneDiscos2(int row, float tiempo) {
	Camera cam;
	float pulso=0;
	int i,numdis=25;
	static float ang=0;
	static int signo=1;
	float argum;
	float fac;
	static float angulo=0;
	GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[]=	{ 2.0f, 2.0f, 2.0f, 1.0f };

	static float ancho=currWidth; 
	static float alto=currHeight;

	static float oldtick;
	float tick=miMusic.getMilliseconds();
	
	glClearColor(0,0,0,0);
	//glClearDepth(0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if((row%64==3)||(row%64==4)||(row%64==5)||(row%64==36)||(row%64==37)||(row%64==38))
	{
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		angulo+=5;
	}
	else
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		fac=0;
	}
	
	if(row%4==0)
	{
		pulso=0.25;
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}
	if(pulso>0) {
		pulso=0.75*pulso;
	}
	
	float ti = tick;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	cam.setFar(1.0,35);
	cam.SetLook(0,0,0.1);
	
	cam.SetPos(10+5*sin(360.0/(128.0*float(row))),15,10+5*cos(360.0/(128.0*float(row))));
	if(row%8==4 || row%8==6) {
		ti+=200;
		cam.SetPos(2,2,2);
	}
	
	if(  row==48 || row==52 || row==56 || row==60 || row==112 || row==116 || row==120 || row==124 ) {
		signo=-signo;
	}
	
	cam.toOGL();

	glEnable(GL_FOG);
	GLfloat fogcol[4]={1,0.2,0.2,0.25};
	glFogf(GL_FOG_DENSITY,0.25);
	glFogf(GL_FOG_END,50);
	glFogfv(GL_FOG_COLOR,fogcol);
	
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glColor3f(1,0,0);

	for(i=1;i<=numdis;i++) {
		glLoadIdentity();
		glRotatef((ti/11 + i*(360/numdis))*signo,1,0,0);
		glScalef(-5+pulso*5,-5+pulso*5,-5+pulso*5);
		glColor4f(1,0.2+1/(float(i)),1/(float(i)),0.5+pulso);
		//glRotatef(float(row%16)+i*60 ,0,1,-2);
		disco(0,0,0.5+float(i)/4,1+float(i)/4);
	}
	
	glDisable(GL_FOG);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	// restauro la vista
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// esto de aqui abajo es para un 'flash' que en verdad es un disco
	if(row==4 || row==10 || row==15 || row==20 || row==26 || row==28 || row==29 || row==31 || row==36 || row==42 || row==47 || row==48 || row==50 || row==53 || row==56 || row==58 || row==59 || row==60 || row==62 || row==68 || row==74 || row==79 || row==84 || row==90 || row==92 || row==93 || row==95 || row==100 || row==106 || row==111 || row==112 || row==116 || row==120 || row==123 || row==126) 
	{
		ponOrtopedico();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor4f(1,1,1,0.5f);
		
		glScalef(ancho,alto,1);
		glTranslatef(rand()/ancho,0,0);
		disco(0,0,20,120);
		glPopMatrix();
		quitaOrtopedico();
	}
	
	//glDisable(GL_BLEND);

	static int oldrow=0;
	
	if(tick-oldtick>0.1) {
		angulo+=0.01;
		if((oldrow%128)!=row) {
			oldrow++;
		}
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	
	ponOrtopedico();
	//glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	int rec; unsigned int repetir;
	float scfactor;
	
	static char frase[]="                                    THIS DEMO IS A TRIBUTE TO EVERY GIRL IN DA SCENE  BECAUSE WITHOUT US IT WOULD BE VERY VERY BORING HEHEHE    ANGELSS  DIAMONDIE  DRUMU  GILKA  IBARTXO  LAURA DIONVARDI  LILILO  MARA  NIANI  OLATZ  PIEDACHU               WE HAVE THE POWER       WEEEEEEEEEEOOOEEEOEOEEE";
	
	for(rec=0;rec<39;rec++) {
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Lo mismo pero en grande 
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor4f(1,1,1,0.6);
		glTranslatef(-ancho/2+rec*ancho/39,0.5+(alto/8)*sin(float(rec)*0.5+ang),0);
		
		glScalef(ancho/55,alto/12,1);
		
		ponLetra(frase[(int)((oldrow+rec)%strlen(frase))]);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glBlendFunc( GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
		// MAS DE TODO! MAS GRANDE! MAS CLARITO y lo mas vip: MAS VECES!!
		for(repetir=1;repetir<=((int)tick)%8;repetir++) {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			scfactor=4+0.3*repetir;
			glColor4f(1,1,1,0.4/float(repetir));
			glTranslatef(-ancho/2+rec*ancho/8 ,0,0);
			//ponLetraPix(frase[(int)((row+rec)%strlen(frase))]);
			glScalef(ancho/55,alto/12,1);
			glScalef(scfactor,scfactor,1);
			ponLetra(frase[(int)((oldrow+rec+20)%strlen(frase))]);
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
	}
	glEnable(GL_TEXTURE_2D);//ponLetra lo desactiva (!!)
	
	// ************* flechitas mil
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float f=3;
	for(i=1;i<=NUMFLES;i++) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		
		glScalef(ancho/posflechas[i][2],alto/posflechas[i][2],1);			
		glTranslatef(posflechas[i][0],posflechas[i][1],0);	
		glColor4f(1,1,1,0.3+1/posflechas[i][2]);

		glBindTexture(GL_TEXTURE_2D, textFlecha.texID);
		glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		
		glEnd();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		posflechas[i][0]+=0.015*posflechas[i][2];
		
		if(posflechas[i][0]>posflechas[i][2]) {
			posflechas[i][0]=-10;
			posflechas[i][1]=float(rand())/RAND_MAX-float(rand())/RAND_MAX;
			
		}
	}
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	quitaOrtopedico();
}

void sceneDiscos3(int row, float tiempo) {
	static float ancho=currWidth; 
	static float alto=currHeight;
	int i,j;
	static float ang=0;
	static float oldtick=0;
	static int oldrow=0;
	float tick=miMusic.getMilliseconds();
	
	ang += (tick - oldtick) * 0.001f;
	oldtick=tick;
	if((oldrow%128)!=row) {
		oldrow++;
	}
	
	glClearColor(1,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// **********************************
	// Mis circulitos fantasticos

	ponOrtopedico();
	
	static float oX=-ancho/2, oY=-alto/2;
	static float rot=0;
	static float escx=ancho/40, escy=alto/30;
	
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glMatrixMode(GL_MODELVIEW);
	glBindTexture(GL_TEXTURE_2D, textCirculo.texID);
	
	float val;
	int numpart=30;
	for(i=1;i<numpart;i++) {
		for(j=1;j<numpart;j++) {
			
			glPushMatrix();
			glColor4f(0,0,0,0.1+1.0/float(abs(5*sin(i+ang+j)+5*cos(i+5*ang+j))));
			val=escx*(0.5*sin(ang+i+j)+0.5*cos(ang+j)+0.5*cos(3*ang+i));
			glTranslatef(oX+2*i*escx,oY+2*j*escy,0);
			glScalef(val,val,1);
			
			glBegin(GL_QUADS);
				glNormal3f( 0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
			glEnd();

			glPopMatrix();
		}
	}
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	quitaOrtopedico();
	
	// *********************************** fin de circulos...
	
	// Discos que botan ******************
	
	Camera cam;
	float px;
	float py;
	float pz=1;
	float ang2 = ang*0.8f;
	float r;
	static float boing = 0;
	float pulso = 0;
	float dist;
	int	numdis=10;
	
	if(row%4==0) {
		boing=0.65;
	}
	if(boing>0) {
		boing-=0.75*boing*boing;
	}
	
	dist=0.1+(boing)*0.54;
	
	r = 3;
	pz = -2;
	
	if((row>=0)&&(row<32)) {
		px = r*sin(ang2);
		py = r*cos(ang2);
	} 
	else if((row>=32)&&(row<64)) {
		px = 1.5f + -2 + sin(ang2*0.5f);
		py = 1 + -2 + cos(ang2);
	}
	else if((row>=64)&&(row<96)) {
		px = 1 + -2 + sin(ang2*0.5f);
		py = 1.5f + -2 + cos(ang2);
	}
	else if((row>=96)&&(row<128)) {
		px = 3+r*sin(ang2+60);
		py = r*cos(ang2-180);
	}
		
	cam.position.x = px;
	cam.position.y = pz;
	cam.position.z = py;
	cam.up.x = 0.5;
	cam.up.y = 0.5;
	cam.up.z = 0.5;

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	cam.toOGL();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//ejes();
	
	dist = 0.1f + boing * 0.54f;
	for(i=0; i < numdis; i++)
	{
		glLoadIdentity();
		glTranslatef(0,0,-1.1+dist*float(i));
		glColor4f(1,1-1/(float(i)),1-1/(float(i)),0.5+pulso);
		// glRotatef(ang*5 ,1,0,0);
		float dx = 0;
		float dy = float(i)/numdis;
		float w1 = 0.5+float(i)/5.0f;
		float w2 = 1+float(i)/5;
		disco(dx, dy, w1, w2);
		glColor4f(1,1,1,0.11);
		discoWire(dx, dy, w1, w2);
	}
	
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	
	// Greetings *********************************
	
	int rec; unsigned int repetir;
	float scfactor;
	
	static char frase[]="                             AND NOW WE SHOULD FINISH WITH A UBERDONSIPAWAHSTYLE GREETINGS   ALICANTE ZONE ANACONDA ASYNKRO BLACK ICE BOAH CAPSULE CATHEDRAL CENTOSIS COD COLLAPSE CONCEPT DLIRIUM DUST INC ELERIUM CORE FUZZION GUM HARDNULL HONKURAI LEVELSIXTYFOUR LUCERA MALA MANKIND MODULEZ MUG NECROSTUDIOS NETWORK NIAKO OZONE PARADOX RECENA RGBA SCOOPEX SECTOROMEGA SERIALNUMBERS SOFTWAREFAILURE SPONTZ STRAVAGANZA TDR THREEPIXELS TLOTB TPM TPOLM UNKNOWN XPLSV ZONAN    FINAL VERSION YEAHH   OS QUEREMOS MEANS WE LOVE YOU ALL   PPG RULEZ                       ";
	// the following text showed up in the party version; there was a bug
	// which prevented the demo from ending and thus we had to warn
	// organisers so they could stop it X)	
	// PLEASE PRESS ESC NOW OR ENJOY THE LOOP        AIDAAAAAAAAAAAAAAAA AIDAAAAAAAAAAAA QUE ME DA MIEDO QUE ME DA MUCHO MIEDO QUE ME ESTA HACIENDO DANYO AIDAAAAAAAA     VIVA EL FLOWER POWER     NO SEAS MASOCA YA NO HAY MAS TEXTO APRIETA YA ESCAPE VAAA LO ESTAS DESEANDO TE LO PIDE EL CUERPO XDDDDD";
	
	ponOrtopedico();
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	
	for(rec=0;rec<39;rec++) {
		glPushMatrix();
		glColor4f(1,1,1,0.6);
		glTranslatef(-ancho/2+rec*ancho/39,0,0);
		glScalef(ancho/60,alto/12,1);
		ponLetra(frase[(int)((oldrow+rec)%strlen(frase))]);
		glPopMatrix();
	}
	quitaOrtopedico();
}

void sceneDiscos3old(int row, float tiempo) {
	Camera cam;
	float pulso=0;
	int i,j,numdis=10;
	static float ang=0;
	static int signo=1;
	float argum;
	float dist;
	static float boing=0;
	static float quad[INTERV+1][INTERV+1][3];
	GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[]=	{ 2.0f, 2.0f, 2.0f, 1.0f };

	static float ancho=currWidth; 
	static float alto=currHeight;

	static float oldtick=0,oldtick2=0;
	float tick=miMusic.getMilliseconds();
	static int oldrow=0;
	if(tick!=oldtick) {

		
		oldtick=tick;
		if(tick-oldtick2>40) {
			ang+=0.05;
			oldtick2=tick;if((oldrow%128)!=row) {
			oldrow++;
		}
		}
	}
	
	
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	cam.setFov(180);
	cam.setFar(1.0,350);//
	cam.SetLook(0.1,0.1,0.1);
	argum=tiempo*4;//360.0/float(row%32);
	//cam.SetPos(10+sin(argum),10,10+cos(argum));
	
	//cam.SetLook(0,0,10);
	
	// Se limpia la pantalla
	glClearColor(1,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0,0,0);
	glEnable(GL_BLEND);
	
	
	GLfloat fogcol[4]={1,0.2,0.2,0.5};
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearDepth(0);


	glFogf(GL_FOG_DENSITY,0.25);
	glFogf(GL_FOG_END,50);
	glFogfv(GL_FOG_COLOR,fogcol);
	glDepthFunc(GL_GREATER );
	float px=-2+sin(ang*0.5);
	float py=-2+cos(ang);
	float pz=1;
	float ti;
	ti=miMusic.getMilliseconds();
	//cam.SetPos(10,7.5*sin(ti),10);
	if((row>=0)&&(row<32)) {
		cam.SetPos(1+px,1+py,pz);
	}
	if((row>=32)&&(row<64)) {
		cam.SetPos(1.5+px,1+py,pz);
	}
	if((row>=64)&&(row<96)) {
		cam.SetPos(1.5+px,1+py,pz);
	}
	if((row>=96)&&(row<128)) {
		cam.SetPos(0.75+px,-0.5+py,pz);
	}

	if(row%8==4 || row%8==6) {
		ti+=200;
		//ti=-ti;
		//cam.SetPos(2,2,2);
	}
	
	if(  row==48 || row==52 || row==56 || row==60 || row==112 || row==116 || row==120 || row==124 ) {
		signo=-signo;
	}
	
	// **********************************

	// Mis circulitos fantasticos
	// La vista
	ponOrtopedico();
	// El modelo	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	static float oX=-ancho/2, oY=-alto/2; // Viva el hardcoding
	static float rot=0;
	static float escx=ancho/40, escy=alto/30;
	
	
	//glColor4f(1,1,1,0.15f);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	float val;
	int numpart=20;
	for(i=1;i<numpart;i++) {
		for(j=1;j<numpart;j++) {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glColor4f(0,0,0,0.1+1.0/float(abs(5*sin(i+ang+j)+5*cos(i+5*ang+j))));
			val=escx*(0.5*sin(ang+i+j)+0.5*cos(ang+j)+0.5*cos(3*ang+i));
			glTranslatef(oX+2*i*escx,oY+2*j*escy,0);
			glScalef(val,val,1);
			glBindTexture(GL_TEXTURE_2D, textCirculo.texID);
			glBegin(GL_QUADS);
			
				glNormal3f( 0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
				
			glEnd();

			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
	}

	
	glBegin(GL_LINES);	glVertex3f(0,0,0);	glVertex3f(ancho/3.3,-alto/2.3,0);glEnd(); // TEST
	glDisable(GL_TEXTURE_2D);
	// El modelo
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	// La vista
	quitaOrtopedico();
	// *********************************** fin de circulos...
	

	if((row%64==3)||(row%64==4)||(row%64==5)||(row%64==36)||(row%64==37)||(row%64==38)) {
		
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	
	} else {
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	if(row%4==0) {//(row==2)||(row==34)) {
		pulso=0.25;
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}
	if(pulso>0) {
		pulso=0.75*pulso;
	}

	cam.toOGL();
	glEnable(GL_FOG);
	
	if(row%4==0) {
		boing=0.65;
	}
	if(boing>0) {
		boing-=0.75*boing*boing;
	}
	//glEnable(GL_DEPTH_TEST );
	for(i=1;i<=numdis;i++) {
		glLoadIdentity();
		
		dist=0.1+(boing)*0.54;
		glTranslatef(0,0,-0.1+dist*float(i));//+0.3*sin((float(i)*50+ti)/180));
		/*if(row%4==0) {
			glTranslatef(0,0,-0.1+0.4*float(i));//+0.3*sin((float(i)*50+ti)/180));
		} else {
				glTranslatef(0,0,-0.1+0.12*float(i));//+0.3*sin((float(i)*50+ti)/180));
		}*/
		//glRotatef(90,0,1,0);
		//glRotatef((ti/11 + i*(360/numdis))*signo,1,0,0);
		
	//glScalef(1,1,1);
		
		glColor4f(1,1-1/(float(i)),1-1/(float(i)),0.5+pulso);
		//glRotatef(float(row%16)+i*60 ,0,0,1);
		glRotatef(ang*5 ,0,0,1);
		disco(0,float(i)/10,0.5+float(i)/4,1+float(i)/4);
	}
	/*glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	ponOrtopedico();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();*/
	glDisable(GL_FOG);
		//glRotatef((ti/11 + i*(360/numdis))*signo,1,0,0);
		
		//glScalef(100,100,100);
	// Mas discos en tu vida
		/* // Desactivado, me molesta la vista
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for(i=1;i<=numdis;i+=4) {
		
		glLoadIdentity();

	
		glRotatef((ti/5 + i*(360/numdis))*signo,1,0,0);
		
		glScalef(100,100,100);
		glLineWidth(5);
		glColor4f(0.5+1/float(i),1/float(i),1/float(i),0.1);
		discoWire(0,0,1+float(i)/4,2+float(i)/4);
		glLineWidth(2);
		glColor4f(1,1,1,0.2);
		discoWire(0,0,1+float(i)/4-0.1,2+float(i)/4+0.1);
	}*/
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	quitaOrtopedico();
	//glDisable(GL_DEPTH_TEST );
	
	

	// restauro el modelo
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	// restauro la vista
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// bis
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	if(row==4 || row==10 || row==15 || row==20 || row==26 || row==28 || row==29 || row==31 || row==36 || row==42 || row==47 || row==48 || row==50 || row==53 || row==56 || row==58 || row==59 || row==60 || row==62 || row==68 || row==74 || row==79 || row==84 || row==90 || row==92 || row==93 || row==95 || row==100 || row==106 || row==111 || row==112 || row==116 || row==120 || row==123 || row==126) {
		/* esto de aqui abajo es para un flash que en verdad es un disco pero bueno */
		
		ponOrtopedico();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor4f(0.5,0.5,0.5,0.1f);
		glScalef(ancho,alto,1);
		/*glBegin(GL_QUADS);
			glVertex3f(-1.0f, -1.0f,  0.0f);
			glVertex3f( 1.0f, -1.0f,  0.0f);
			glVertex3f( 1.0f,  1.0f,  0.0f);
			glVertex3f(-1.0f,  1.0f,  0.0f);
		glEnd();*/
		glScalef(ancho,alto,1);
		glTranslatef(rand()/ancho,0,0);
		//disco(0,0,20,120);
		glPopMatrix();
		quitaOrtopedico();
		glMatrixMode(GL_MODELVIEW);
	}
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glDisable(GL_BLEND);

	// Ahora las lyrics o algo similar (tope cutres ofcourse)
	// pongo la vista *"*"*"*"*"*"*"*"*"*"*"*"*"*"**"*"*"
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	ponOrtopedico();
	// Fastfwd
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glRotatef(-(ang)*10,0,0,1);
	glColor4f(1,1,1,1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	
	glDisable(GL_TEXTURE_2D);
	

	// No hay texturas sin senos (:-O)
	/*glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//ponOrtopedico();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glLineWidth(1.5f);

	int j;
	float senos=20;
	for(j=0;j<senos;j++) {	
		glBegin(GL_LINE_STRIP);
		for(i=0;i<TRIGPREC;i+=16) {
			glColor4f(1,1,1,0.5*float(i+j)/(TRIGPREC+senos));
		

		//glColor3f(getSinTable(i),getCosTable(i),ypos + radio1*getCosTable(i));
		glVertex3f(((ancho/senos)*j/float(TRIGPREC))*i-ancho/2+100*getSinTable((row*32+i)%TRIGPREC), -alto/3+100*getCosTable((row*64+i)%TRIGPREC),0);
		//glVertex3f(20*rand()/RAND_MAX,20*rand()/RAND_MAX,0);
			//glVertex3f(0,0,0);
		//glColor3f(getSinTable(i),getCosTable(i),ypos + radio2*getCosTable(i));
		//glVertex3f(xpos + radio2*getSinTable((i+1)%TRIGPREC) , ypos + radio2*getCosTable((i+1)%TRIGPREC),0);

		}	
		glEnd();
	}

	glPopMatrix();*/
	glDisable(GL_BLEND);
	quitaOrtopedico();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();


	ponOrtopedico();
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	int rec; unsigned int repetir;
	float scfactor;
	
	static char frase[]="                             AND NOW WE SHOULD FINISH WITH A UBERDONSIPAWAHSTYLE GREETINGS   ALICANTE ZONE ANACONDA ASYNKRO BLACK ICE BOAH CAPSULE CATHEDRAL CENTOSIS COD COLLAPSE CONCEPT DLIRIUM DUST INC ELERIUM CORE FUZZION GUM HARDNULL HONKURAI LEVELSIXTYFOUR LUCERA MALA MANKIND MODULEZ MUG NECROSTUDIOS NETWORK NIAKO OZONE PARADOX RECENA RGBA SCOOPEX SECTOROMEGA SERIALNUMBERS SOFTWAREFAILURE SPONTZ STRAVAGANZA TDR THREEPIXELS TLOTB TPM TPOLM UNKNOWN XPLSV ZONAN    FINAL VERSION YEAHH   OS QUEREMOS MEANS WE LOVE YOU ALL   PPG RULEZ                       ";
	// the following text showed up in the party version; there was a bug
	// which prevented the demo from ending and thus we had to warn
	// organisers so they could stop it X)	
	// PLEASE PRESS ESC NOW OR ENJOY THE LOOP        AIDAAAAAAAAAAAAAAAA AIDAAAAAAAAAAAA QUE ME DA MIEDO QUE ME DA MUCHO MIEDO QUE ME ESTA HACIENDO DANYO AIDAAAAAAAA     VIVA EL FLOWER POWER     NO SEAS MASOCA YA NO HAY MAS TEXTO APRIETA YA ESCAPE VAAA LO ESTAS DESEANDO TE LO PIDE EL CUERPO XDDDDD";
	
	for(rec=0;rec<39;rec++) {
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		// Lo mismo pero en grande y con color mas clarito
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor4f(1,1,1,0.6);
		glTranslatef(-ancho/2+rec*ancho/39,/*0.5+(alto/8)*sin(float(rec)*0.5+ang)*/0,0);
		//ponLetraPix(frase[(int)((row+rec)%strlen(frase))]);
		glScalef(ancho/60,alto/12,1);
		
		ponLetra(frase[(int)((oldrow+rec)%strlen(frase))]);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		int letHor=8, letV=4;
		glBlendFunc( GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
		// MAS DE TODO! MAS GRANDE! MAS CLARITO y lo mas vip: MAS VECES!!
		for(repetir=1;repetir<=((int)tick)%8;repetir++) {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			scfactor=2+0.3*repetir;
			glColor4f(1,1,1,0.4/float(repetir));
			//glTranslatef(-ancho/2+(((oldrow+rec)%strlen(frase))%letHor)*ancho/8,alto/2-(escy*2)*(floor(float(((oldrow+rec)%strlen(frase)))/4)),0);
			//glTranslatef(repetir*escx,10/*(alto/2)*cos(oldrow+rec)*/,0);
			glTranslatef(-ancho/2+rec*ancho/39,/*0.5+(alto/8)*sin(float(rec)*0.5+ang)*/alto/39,0);
			//ponLetraPix(frase[(int)((row+rec)%strlen(frase))]);
			glScalef(ancho/55,alto/12,1);
			glScalef(scfactor,scfactor,1);
			//ponLetra(frase[(int)((oldrow+rec+20)%strlen(frase))]);
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
	}
	quitaOrtopedico();

}

void scenePrueba(int row,float tiempo) {
	Camera cam;
	static float ang=0;
	int i;
	float esc;
	GLfloat LightAmbient[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[]=	{ -20.0f, -10.0f, -10.0f, 1.0f };

	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
   GLfloat mat_ambient_color[] = { 0.6, 0.6, 0.2, 1.0 };
   GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat no_shininess[] = { 0.0 };
   GLfloat low_shininess[] = { 5.0 };
   GLfloat high_shininess[] = { 100.0 };
   GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};


	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	
	ang+=0.1;
	/*if((row%8)==0) {
		ang+=2;
		esc=0;
	} else {
		esc=0;
	}*/
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//cam.SetPos(5+3*sin(ang),3,5+3*cos(ang));
	//cam.SetLook(0,0,10);
	cam.toOGL();
	// Se limpia la pantalla
	glClearColor(0,0,0.3,0);
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glLoadIdentity();
	ejes();
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING );
	glEnable(GL_LIGHT1);
	glColor4f(1,1,1,1);
	esc=0;
	glRotatef(ang*(10),1,1,1);
	glScalef(8+esc,8+esc,8+esc);
	
	
	//glTranslatef(0.25*sin(ang),0,0);
	glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	//glDepthFunc(GL_LEQUAL);	

	  glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);//mat_ambient_color);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for(i=1;i<=1;i++) {
		//glLoadIdentity();
		
		//glScalef(3+2*sin(ang+i),row%8,3+2*cos(ang+i));
		//glColor4f(0,0,0.3+1/(float(i)),0.2+1/(float(i)));
		glRotatef(3,1,1,1);
		malla.drawWire(3,(int)row%128);
	}
	glDisable(GL_NORMALIZE);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glPopMatrix();
}

void ponLetra(char letra) {
// Dibuja la letra

	float letw,letx; // ancho y posicion X
	int i;

	// El espacio, un caso especial
	if(letra!=32) {
		i=letra-65; // 65 es el char A ascii, solo text en mayusc.
		if((i<27) && (i>=0)) {
		letw=(textPosition[i+1]-textPosition[i])/512; // 512 para normalizar al ancho :-???
		}
		/*if (i==26) {
			letw=512-textPosition[i];
		}*/
		letx=textPosition[i]/512;

		
		//ancho=glutGet(GLUT_WINDOW_WIDTH);//q
		//alto=glutGet(GLUT_WINDOW_HEIGHT);//q

		//glScalef(ancho/40,alto/10,1);//q
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textArial.texID);
		glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f+letx, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
			glTexCoord2f(/*1.0f*/letx+letw, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
			glTexCoord2f(/*1.0f*/letx+letw, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f+letx, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		
		glEnd();
		glDisable(GL_TEXTURE_2D);
	} else {
		glDisable(GL_TEXTURE_2D);
	}
	
}

void ponLetraPix(char letra) {
// Dibuja la letra

//	float ancho,alto;
	float letx; // ancho y posicion X
	float leth=(1024.0f/26.0f), lety; // alto, posicion Y
	int i;

	// El espacio, un caso especial
	if(letra!=32) {
		i=letra-65; // 65 es el char A ascii, solo text en mayusc.
		if((i<26) && (i>=0)) {
		lety=((float)(i+1)*leth)/1024.0f; // para normalizar al alto :-???
		}
		if (i==25) {
			lety=1024-leth;
		}
		letx=textPosition[i]/512;

		
		/*ancho=glutGet(GLUT_WINDOW_WIDTH);//q
		alto=glutGet(GLUT_WINDOW_HEIGHT);//q*/
		static float ancho=currWidth;
		static float alto=currHeight;

		float b=0.11;
		glScalef(ancho/32,alto/32,1);//q
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textPixel.texID);
		glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f+lety); glVertex3f(-1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f+lety); glVertex3f( 1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f,/*1.0f  lety+leth*/1); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f, /*1.0 lety+leth*/1); glVertex3f(-1.0f,  1.0f,  1.0f);
		
		glEnd();
		glDisable(GL_TEXTURE_2D);
	} else {
		glDisable(GL_TEXTURE_2D);
	}
	
}

void sceneSnow(int row, float tiempo, int pat) {
	// Dibuja la clasica superficie de bolitas... (o algo similar :-S)
		long fra,ti,fi;
	float tamBase;

	static float rot=0, tickdif=0;
	static float tick=0,oldtick=0;
	
	int ind;
	tamBase=0.05f;
	fra=(float)row;
	ti=tiempo;
	fi=row;
	
	GLfloat LightAmbient[]=		{ 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat LightDiffuse[]=		{ 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat LightPosition[]=	{ 0.0f, 0.0f, 0.0f, 1.0f };
	glEnable(GL_LIGHTING);								// Enable Lighting
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	//glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);								// Enable Light One
	glEnable(GL_COLOR_MATERIAL);	
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);		

	

	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	tick=miMusic.getSeconds();
	if(oldtick!=tick) {
		rot+=0.03f;	
		tickdif = tick - oldtick;
		oldtick=tick;
	}

	float ROTDIV2=rot*0.5f;
	double COSROT=cos(ROTDIV2);
	double SINROT=sin(ROTDIV2);

	//gluLookAt(8*cos(ROTDIV2),1,8*sin(ROTDIV2),0,0,0,0.1-SINROT,3-SINROT-COSROT,1-COSROT);
	//gluLookAt(8*cos(ROTDIV2),1,8*sin(ROTDIV2),0,0,0,0,1,0);
	
	Camera miCam;
	//miCam.SetPos(-2+3*COSROT,2+SINROT,1);
	//miCam.SetPos(-7.5+7.5*COSROT,5+2.5*COSROT,3*COSROT+4*SINROT*SINROT);
	float altura=7;//+1*SINROT;
	miCam.SetPos(altura,0.1,0);
	//miCam.SetPos(10,altura*3,-2);
	//miCam.setFov(100);
	miCam.setFar(1,100);
	miCam.SetLook(0.1,0.1,0.1);
	miCam.toOGL();
	
	/*gluLookAt(2,1,2,0,0,0,1,1,1);*/
  

	//glTranslatef(0.0f,0.0f,-3.0f);//glRotatef(90+rot,1.0f,0.0,0);

	//glMatrixMode(GL_PROJECTION_MATRIX);
	//glPushMatrix();
	//
	
	float BOLAS=25;
	float x,y,z;
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(0.5f);
	float escb=0.05f;
	float inc=0.25;
	int numrealobjs;
	if(pat==6) {
		numrealobjs=(row/4);
	} else {
		numrealobjs=30;
	}
	for(ind=0;ind<=numrealobjs;ind++) {
		x=posiciones[ind][0];
		y=posiciones[ind][1];
		z=posiciones[ind][2];
		glColor3f(1,1,1.75f);
		glLoadIdentity();
		glScalef(0.3,0.3,0.3);
		glTranslatef(x,y,z);
		// TODOGLUT glutWireCube(1);
		drawCube(false, 0.25);
		
		x+=float(rand())/RAND_MAX*inc-float(rand())/RAND_MAX*inc;
		x-=float(rand())/RAND_MAX*inc-float(rand())/RAND_MAX*inc;
		if((x>MIMAXX)||(x<-MIMAXX)) {
			x=float(rand())/RAND_MAX*MIMAXX-float(rand())/RAND_MAX*MIMAXX;
			y=float(rand())/RAND_MAX*MIMAXX-float(rand())/RAND_MAX*MIMAXX;
		}
		y-= tickdif * 10 * rand()/RAND_MAX;
		if(y<-MIMAXX) {
			y=MIMAXX*2;
		}
		z+=float(rand())/RAND_MAX*inc-float(rand())/RAND_MAX*inc;
		z-=float(rand())/RAND_MAX*inc-float(rand())/RAND_MAX*inc;
		if((z>MIMAXX)||(z<-MIMAXX)) {
			z=float(rand())/RAND_MAX*MIMAXX-float(rand())/RAND_MAX*MIMAXX;
			y=float(rand())/RAND_MAX*MIMAXX-float(rand())/RAND_MAX*MIMAXX;
		}
		posiciones[ind][0]=x;
		posiciones[ind][1]=y;
		posiciones[ind][2]=z;

	}
	glDisable(GL_LINE_SMOOTH);

	
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glDisable(GL_LIGHTING);


}


/***** para el bluuuuuuuurrrr */



GLuint EmptyTexture()
{
	GLuint txtnumber;
	unsigned int* data;

	// Create Storage Space For Texture Data
	data = (unsigned int*)new GLuint[((blurTextureSize * blurTextureSize)* 4 * sizeof(unsigned int))];
	

	glGenTextures(1, &txtnumber);
	glBindTexture(GL_TEXTURE_2D, txtnumber);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, blurTextureSize, blurTextureSize, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST
 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST );

	delete [] data;												

	return txtnumber;
}




// based on the radial blur tuto by nehe
void RenderToTextureSnow(int row,float tiempo,int pat) 
{
	glViewport(0, 0, blurTextureSize, blurTextureSize);
	sceneSnow(row,tiempo,pat);

	glBindTexture(GL_TEXTURE_2D, BlurTexture);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, blurTextureSize, blurTextureSize, 0);
	
	glClearColor(0.0f, 0.0f, 0.5f, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Preparo mis datillos
	static float ancho=currWidth; 
	static float alto=currHeight;
	glViewport(0 , 0,ancho ,alto);
}

void DrawBlurVertical(int times, float inc)
{
	float spost = 0.0f;
	float alphainc = 0.9f / times;
	float alpha = 0.2f;	
	float tick=miMusic.getMilliseconds();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,BlurTexture);

	// Preparo mis datillos
	static float ancho=currWidth; 
	static float alto=currHeight;
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho( 0, ancho , alto , 0, -1, 1 );
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();	
	glLoadIdentity();	

	alphainc = alpha / times;

	glBegin(GL_QUADS);
		
	for (int num = 0;num < times;num++)
	{
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
		glTexCoord2f(0,1-spost);
		glVertex2f(0,0);
		glTexCoord2f(0,0+spost);
		glVertex2f(0,alto);	
		glTexCoord2f(1,0+spost);
		glVertex2f(ancho,alto);
		glTexCoord2f(1,1-spost);
		glVertex2f(ancho,0);
		spost += inc;
		alpha = alpha - alphainc;
	}
	glEnd();

	
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();		

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,0);
}


void sceneSurfaceBlur (int pat, int row, float tiempo, float *fft)
{
	int i;

	// Preparo mis datillos
	float ancho=currWidth; 
	float alto=currHeight;
	static float ang=0;

	static float oldtick=-1,oldtick2=0;
	static float anc1=ancho/8,anc2=ancho/4,xicapos=2;
	static float halfancho = ancho*0.5f;
	float tick;
	static int numpart=0;
	static int oldrow = -1;
	static float partTickStart;
	static float meshang=0.0f;
	float tbx,tby,tbz;
	static float pulso;
	
	tick=miMusic.getMilliseconds();
	
	if(oldtick > 0)
	{
		float tickdif = tick - oldtick;
		
		if(xicapos > 1.05f)
		{
			xicapos-= tickdif * 0.001; //xicapos/100;
		}
		else
		{
			if(numpart == 0)
			{
				// empieza a echar humo
				numpart = 1;
				partTickStart = tick;
			}
		}
		
		ang += 0.015;
		meshang += 0.55;

		if(pulso > 0)
		{
			pulso-=pulso*pulso*1.5;
		}
	}
	
	oldtick = tick;
	
	if(numpart)
	{
		if((numpart < 20) && (tick - oldtick2 > 30))
		{
			numpart++;
			oldtick2 = tick;
		}
	}
	
	RenderToTextureSnow(row,tiempo,pat);	
	DrawBlurVertical(6,0.015f);
	
	// Ahora haremos una especie de 'equalizador'
	// ya veremos lo que sale, ya...
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	ponOrtopedico();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glDisable(GL_DEPTH_TEST);
	glLineWidth(0.5);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();		
		
	int numBars = 32;
	float y, x, barHeight;

	barHeight = alto / numBars;
	y = -alto * 0.5f - barHeight;
	
	for(i=0; i < numBars; i++)
	{
		y += barHeight;
		x = // -1.25 *
		 (-halfancho)* fft[i];
		
		glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.5f);
			glVertex3f(halfancho, y, 0.0f);
			glColor3f(0.0f, 0.75f, 0.5f + 2.0f * fft[i]);
			glVertex3f(halfancho + x, y, 0.0f);
			glVertex3f(halfancho + x, barHeight + y, 0.0f);
			glColor3f(0.0f, 0.0f, 0.5f);
			glVertex3f(halfancho, barHeight + y, 0.0f);
		glEnd();
		
		glColor3f(0.0f, 0.0f, 0.5f);
		glBegin(GL_LINE_STRIP);			
			glVertex3f(halfancho, y, 0.0f);
			glVertex3f(halfancho + x, y, 0.0f);
			glVertex3f(halfancho + x, barHeight + y, 0.0f);
			glVertex3f(halfancho, barHeight + y, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.5f);
			glVertex3f(-halfancho, y, 0.0f);
			glColor3f(0.0f, 0.75f, 0.5f + 2.0f*fft[i]);
			glVertex3f(-halfancho - x, y, 0.0f);
			glVertex3f(-halfancho - x, barHeight + y, 0.0f);
			glColor3f(0.0f, 0.0f, 0.5f);
			glVertex3f(-halfancho, barHeight + y, 0.0f);
		glEnd();
		
		glColor3f(0,0.0,0.5);
		glBegin(GL_LINE_STRIP);
			glVertex3f(-halfancho, y, 0.0f);
			glVertex3f(-halfancho - x, y, 0.0f);
			glVertex3f(-halfancho - x, barHeight + y, 0.0f);
			glVertex3f(-halfancho, barHeight + y, 0.0f);
		glEnd();
	}
		
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glDisable(GL_BLEND);
	quitaOrtopedico();

	// La xicona frescaxona xDDD
	ponOrtopedico(4,2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();		
	glColor4f(1,1,1,1);	
	glTranslatef(xicapos, -0.025f,0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, textGirlCool.texID);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	quitaOrtopedico();

	// Ese humo evanescente... XDDD ¡¡Que solo salga cuando la tía se pare!!
	ponOrtopedico();
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	float oX = 0.63f * currWidth * 0.5f, oY = -0.45f * currHeight * 0.5f;
	float rX = currWidth * 0.01f, iV = currHeight * 0.001;
	float sx = 1.0f, sy = 1.0f, sInc = currHeight * 0.004;
	float val;
		
	//glBegin(GL_LINES);
	//	glVertex3f(0, 0, 0);
	//	glVertex3f(oX, oY, 0);
	//glEnd();
	
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, textHumo.texID);
	
	for(i=1; i < numpart; i++)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		glColor4f(1.0f, 1.0f, 1.0f, 0.1f + 1.0f/float(i));
		val = sx * (1 + sInc*i);
		
		glTranslatef(
			oX + (i - 1) * rX * sin((tick - partTickStart)*0.001 + i),
			oY + val * i * iV,
			0
			);
		glScalef(val, val, 1);
		
		glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glEnd();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	

	glDisable(GL_BLEND);
	//glBegin(GL_LINES);	glVertex3f(0,0,0);	glVertex3f(ancho/3.3,-alto/4.8,0);glEnd(); // TEST
	glDisable(GL_TEXTURE_2D);
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	quitaOrtopedico();

	// Mallitas chachi guays (esto es para los torus)

	// Para los incrementos de angulo tendremos dos casos, en el primer pattern (6) y el segundo (7)
	// En el 6, solo pasan a partir de la fila 60
	// en el 7 son más heavys
	if(oldrow != row)
	{
		if(pat==6)
		{
			if((row == 60) || ((row >= 64) && (row % 16 == 0)))
			{
			//if((row%16)==0) {
				meshang+=2;
				pulso=0.2;
			}
		}
		else if(pat==7)
		{
			// This is what used to be the syncro in this scene
			// If you open the song with a tracker, you'll quickly
			// notice there were lots of missing sync points (i.e. the drum)
			// This part was done at 7AM in the morning, after not having slept
			// and being coding all night so that we could make it to 
			// the deadline.
			// I have redone it just so that it makes a little more sense :)
			//if((row==0)||(row==16)||(row==24)||(row==30)||(row==38)||(row==48)||(row==64)||(row==72)||(row==80)||
	//			(row==88)||(row==96)||(row==100)||(row==104)||(row==108)||(row==112)||(row==114)||(row==116)||(row==118)) {
			if((row==0) || (row==8)
				|| (row==16) || (row==24) || (row==30) || (row==32) 
				|| (row==38) || (row==40) || (row==46) || (row==48)
				|| (row==54) || (row==56) || (row==62) || (row==64)
				|| (row==67) || (row==70) || (row==72) || (row==75)
				|| (row==78) || (row==80) || (row==83) || (row==86)
				|| (row==88) || (row==91) || (row==94) || (row==96)
				|| ((row>96) && (row<116) && (row%2==0) )
		   )
			{
				meshang+=2;
				pulso=0.3;
			}
			else if((row>116) && (row<128)) {
				meshang+=10;
				pulso=0.3;
			}
		}
		oldrow = row;
	}

	// ******************** TORUS

	if(pulso>0) {
		tbx=pulso*(float(rand())/RAND_MAX-float(rand())/RAND_MAX);
		tby=pulso*(float(rand())/RAND_MAX-float(rand())/RAND_MAX);
		tbz=pulso*(float(rand())/RAND_MAX-float(rand())/RAND_MAX);
		//printf("%f %f\n",pulso,tbx);
	} else {
		tbx=0;
		tby=0;
		tbz=0;
	}

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	glLoadIdentity();
	
	float sc=0.7f;
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glLoadIdentity();
	
	glTranslatef(tbx,tby,tbz);
	glTranslatef(-0.5,-0.25,0);
	glRotatef(meshang,0,1,0);
	glScalef(sc,sc,sc);

	
	glEnable(GL_BLEND);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.30,0.82,0.92,1.2+cos(ang*4));
	//glColor3f(1,0,0);
	malla.draw();
	
	glColor3f(0,0,0);
	malla.drawWire(2,300);
	

	glLoadIdentity();
	glTranslatef(tbx,tby,tbz);
	glTranslatef(-0.5,0.25,0);
	glRotatef(meshang,0,-1,0);
	glScalef(sc,sc,sc);	glColor4f(0.30,0.82,0.92,1.2+cos(ang*4));
	malla.draw();

	glColor3f(0,0,0);
	malla.drawWire(2,300);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// ******** Kind of fade in layer
	static float alphalevel=0;

	if((row>=0)&&(row<32)&&(alphalevel<1)&&(pat==6)) {
		alphalevel+=0.0251;
	}
	if((row>=120)&&(row<128)&&(pat==7)) {
		alphalevel-=0.0251;
	}
	ponOrtopedico();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor4f(1,1,1,1-alphalevel);
	glScalef(ancho/2+0.3,alto/2,1);
	
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glDisable(GL_BLEND);
	quitaOrtopedico();

}

void scene4segundos (int row) {
	static float ancho=currWidth; 
	static float alto=currHeight;

	static float alphalevel=0;
	static float alphainc=0.0525;
	
	if((row>=0)&&(row<4)) {
		alphalevel = map(row, 0, 4, 0, 1);
		//alphalevel+=alphainc;
	}
	else if((row>=13)&&(row<16)) {
		// alphalevel-=alphainc;
		alphalevel = map(row, 13, 16, 1, 0);
	}
	else
	{
		alphalevel = 1.0f;
	}
	

	ponOrtopedico(2, 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glRotatef(-(ang)*10,0,0,1);
	glColor4f(1,1,1,alphalevel);
	//glScalef(ancho/2+0.3,alto/2,1);
	
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, text4segundos.texID);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	
	glEnd();
	

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	quitaOrtopedico();
}

void drawCube(bool solid, float size) {
	if(size!=1) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glScalef(size,size,size);
	}
	if(solid) {
		glBegin(GL_QUADS);
		
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
										
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
									
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		
		glEnd();
	} else {
		
		glBegin(GL_LINES);
		// right
		glVertex3f(1,1,1);
		glVertex3f(1,-1,1);
		
		glVertex3f(1,-1,1);
		glVertex3f(1,-1,-1);
		
		glVertex3f(1,-1,-1);
		glVertex3f(1,1,-1);
		
		glVertex3f(1,1,-1);
		glVertex3f(1,1,1);
		
		// top
		glVertex3f(1,1,-1);
		glVertex3f(-1,1,-1);
		
		glVertex3f(-1,1,-1);
		glVertex3f(-1,1,1);
		
		glVertex3f(-1,1,1);
		glVertex3f(1,1,1);
		
		// left
		glVertex3f(-1,1,-1);
		glVertex3f(-1,-1,-1);
		
		glVertex3f(-1,-1,-1);
		glVertex3f(-1,-1,1);
		
		glVertex3f(-1,-1,1);
		glVertex3f(-1,1,1);
		
		// bottom
		glVertex3f(-1,-1,1);
		glVertex3f(1,-1,1);
		
		glVertex3f(-1,-1,-1);
		glVertex3f(1,-1,-1);
		
		glEnd();
	}
	if(size!=1) {
		glPopMatrix();
	}
}
