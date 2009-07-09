#include "FXTVDistort.h"
#include <math.h>
// inicializar lo estático aquí...
GLuint FXTVDistort::BlurTexture;
int FXTVDistort::viewWidth;
int FXTVDistort::viewHeight;
float FXTVDistort::inc;
int FXTVDistort::times;
float FXTVDistort::ccr;
float FXTVDistort::ccg;
float FXTVDistort::ccb;
float FXTVDistort::cca;
GLenum FXTVDistort::fac1;
GLenum FXTVDistort::fac2;


GLuint FXTVDistort::EmptyTexture() {
	GLuint txtnumber;
	unsigned int* data;	


	data = (unsigned int*)new GLuint[((this->textWidth * this->textHeight)* 4 * sizeof(unsigned int))];
	glGenTextures(1, &txtnumber);								
	glBindTexture(GL_TEXTURE_2D, txtnumber);					
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->textWidth, this->textHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);						
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	delete [] data;												

	return txtnumber;											

}

void FXTVDistort::setView(int _width, int _height) {
	this->viewWidth=_width;
	this->viewHeight=_height;
}

void FXTVDistort::setTimes(int _times) {
	// num veces q se repite el blur
	this->times=_times;
}
void FXTVDistort::setInc(float _inc) {
	// diferencia entre blurs ('densidad')
	this->inc=_inc;
}

void FXTVDistort::setClearColor(float r,float g,float b,float a) {
	ccr=r;
	ccg=g;
	ccb=b;
	cca=a;
}

void FXTVDistort::setBlendFunc(GLenum fac1,GLenum fac2) {
	this->fac1=fac1;
	this->fac2=fac2;
}
void FXTVDistort::prepareFrame(void) 
{
	glViewport(0,0,miDemo->getWidth(),miDemo->getHeight()); 
}

void FXTVDistort::postprepareFrame(void) 
{
	glBindTexture(GL_TEXTURE_2D,BlurTexture);			
	
	// con origen en la parte inferior izquierda copia lo q haya en el framebuffer
	// a la textura indicada

	glCopyTexSubImage2D(GL_TEXTURE_2D,// target
		0, //level mipmaps
		0, //xoffset
		0, // yoffset
		0, // x
		0, //y
		miDemo->getWidth(), // width
	    miDemo->getHeight()); //height 
		
}


// Funciones a definir desde Effect.h
void FXTVDistort::perFrame(float time) 
{
	int x,y;
	int demowidth = miDemo->getWidth();
	int demoheight = miDemo->getHeight();
	
	//miDemo->ponOrtopedico();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	glViewport(0,0,demowidth,demoheight);

	glOrtho(-demowidth*0.5, demowidth*0.5, -demoheight*0.5,demoheight*0.5, 0.1,200.0f);
	
	GLboolean currentMask;
	glGetBooleanv(GL_DEPTH_WRITEMASK, &currentMask);
	glDepthMask(GL_FALSE);

	glPushAttrib(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(this->fac1,this->fac2);
	glBindTexture(GL_TEXTURE_2D,BlurTexture);
	float sc=0.5;

	float z_depth=float(2);
	float dp=0;
	glColor4f(ccr,ccg,ccb,cca);

	static float DH2= demoheight/2;
	static float DW2= demowidth/2;

	static float xint = float(demowidth) / TVDISTORTINTERV;

	float powermax1;
	if(params[TVD_PARAM_POWER]<=1)
		if(params[TVD_PARAM_POWER]<=0)
			powermax1=0;
		else
			powermax1=params[TVD_PARAM_POWER];
	else		
			powermax1=1;

	static int vpos=0;
	static float t0=0;
	if(time-t0>0.05) {
		t0=time;
		vpos=(vpos++)%TVDISTORTINTERV;
	}

	float qx,qy;

	for(x=0;x<=TVDISTORTINTERV;x++) {
		for(y=0;y<=TVDISTORTINTERV;y++) {
			// distorsion horizontal
			if(x!=0 && x!=TVDISTORTINTERV) {
				qx=quadPos[x][y][0] + cos(time)*normalMagnit[y]*params[TVD_PARAM_V]+10*sin(time+y/8);
				qx+=(getRand()-getRand());
			} else
				qx=quadPos[x][y][0];
			
			quad[x][y][0]=qx;
			// distorsion vertical
			qy=(1-powermax1)*quadPos[x][y][1] + powermax1*normalInterv[y];
			qy+=(getRand()-getRand());
			quad[x][y][1]=qy;
		}
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glBegin(GL_QUADS);
	for(x=0;x<TVDISTORTINTERV;x++)
	{
		for(y=0;y<TVDISTORTINTERV;y++) 
		{
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(texPos[x][y][0], texPos[x][y][1]); 
			glVertex3f(quad[x][y][0], quad[x][y][1], z_depth);
		
			glTexCoord2f(texPos[x+1][y][0], texPos[x+1][y][1]);
			glVertex3f( quad[x+1][y][0], quad[x+1][y][1],  z_depth);

			glTexCoord2f(texPos[x+1][y+1][0], texPos[x+1][y+1][1]);
			glVertex3f( quad[x+1][y+1][0], quad[x+1][y+1][1],  z_depth);

			glTexCoord2f(texPos[x][y+1][0], texPos[x][y+1][1]);
			glVertex3f(quad[x][y+1][0], quad[x][y+1][1],  z_depth);
		}
	}
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glPopAttrib();

	glDepthMask(currentMask);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void FXTVDistort::setTextureSize(int width, int height) {
	this->textWidth=width;
	this->textHeight=height;
}
void FXTVDistort::init(void) {
	// asignar recursos y tal, cargar ficheros, blabla
	int demowidth = miDemo->getWidth();
	int demoheight = miDemo->getHeight();

	int twidth = clp2(demowidth);
	int theight = clp2(demoheight);
	
	this->setTextureSize(twidth, theight);
	BlurTexture = EmptyTexture();								
	ccr=0.5;
	ccg=0.5;
	ccb=0.5;
	cca=0.0;
	fac1=GL_SRC_ALPHA;
	fac2=GL_ONE_MINUS_SRC_ALPHA;

	xMax = float(demowidth) / twidth;
	yMax = float(demoheight) / theight;

	int i,j;
	float longint;
	float floati,floatj;
	
	longint=1/TVDISTORTINTERV;
	for(i=0;i<=TVDISTORTINTERV;i++) {
		floati=float(i);
		for(j=0;j<=TVDISTORTINTERV;j++) {
			floatj=float(j);
			// la textura va de 0 a 1
			texPos[i][j][0]=xMax*(floati)/TVDISTORTINTERV; // x
			texPos[i][j][1]=yMax*(floatj)/TVDISTORTINTERV; // y
			texPos[i][j][2]=0.0f; // z

			// quads de 0.. demowidth  blabla
			quadPos[i][j][0]=-demowidth/2.0+demowidth*(floati)/TVDISTORTINTERV; // x
			quadPos[i][j][1]=-demoheight/2.0+demoheight*(floatj)/TVDISTORTINTERV; // y
			quadPos[i][j][2]=0.0f; // z

			randQuadPos[i][j][0]=2*(float(rand())/RAND_MAX)-1; // de -1..1
			randQuadPos[i][j][1]=2*(float(rand())/RAND_MAX)-1; // de -1..1
			randQuadPos[i][j][2]=0.0f;

			
		}
	}

	for(i=0;i<TVD_NUMPARAMS;i++) {
		params[i]=0.0;
	}

	float mu, sigma, x, pi, normal, constante, maximo, xinit, xfin, alturaInterv;
	
	mu=9.9465108746;
	sigma=0.9824992603;
	pi=3.1415926535;
	maximo=0;
	//xinit=7.25;
	//xfin=13;
	xinit=4;
	xfin=16;
	
	alturaInterv=float(demoheight)/float(TVDISTORTINTERV);

	constante=1/(sigma * sqrt(2*pi));
	for(i=0;i<=TVDISTORTINTERV;i++) {
		/* x=4..17 ........ 17-4 = 13*/
		x=(float(i)/TVDISTORTINTERV)*(xfin-xinit) + xinit;
		normal=constante * exp(-(pow((x-mu/sigma),2))/2);
		normalMagnit[i]=normal/constante; // La division es para normalizar a 1
		if(normal>maximo)
			maximo=normal;
		
		normalInterv[i]=(alturaInterv+ normalMagnit[i])*i - demoheight/2;

	}

}
void FXTVDistort::setParam(unsigned int pOffset, float pValue) {
	params[pOffset]=pValue;
}

void FXTVDistort::start(void) {
}

void FXTVDistort::deInit(void) {
	// desasignar recursos y tal, descargar ficheros, blabla
	glDeleteTextures(1,&BlurTexture);							
}

FXTVDistort::FXTVDistort() {
}

FXTVDistort::~FXTVDistort() {
}
