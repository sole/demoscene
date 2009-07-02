#include "FXritmo.h"

// posibles funciones propias (no de la clase efecto)
// pej void FXmuros::mover

// Funciones a definir desde Effect.h
void FXritmo::perFrame(float time) {
    float t = time * 0.001f;
    float fftbass=miMusic.getFFTBass();

    glClearColor(0.925,0,0.549,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    cam.toOGL();
    cam.SetPos(0,0,-6);
    cam.SetLook(0,-1,-0.1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    float xt=2; // xtremo
    float z_depth=float(-0.0121);


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPointSize(10);
    glColor3f(1,1,1);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float valy;
    int numV,j;
    Point p;
    static float pulso=0;
    int row=miMusic.getRow();
    if((row==0) || (row==1) || (row==8) || (row==9) || (row==16) || (row==17) || (row==24) || (row==25)) {
        valy=4;

    } else {
        valy=0;
    }
    if(valy>0) {
        pulso=valy;
    } else {
        if(pulso>0) {
                pulso=pulso-pulso*pulso*0.05;
        }
    }
    numV=unaEsfera.getNumVertex();
    
    for(j=0;j<numV;j++)
    {
        p.x = 2*sin(t*0.5 + j);
        p.y = fftbass*5 + 2*cos(t*0.5+j);
        p.z = 2*(sin(p.y)) + fftbass;
        p.w = unaEsfera.getVertex(j).w;
        unaEsfera.setVertex(j,p);
    }
    
    glTranslatef(0,0,pulso*0.6);
    glRotatef(t*10 ,1,1,1);
    unaEsfera.perFrame(t);

    glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glScalef(3,3,3);
    glRotatef(t,1,0,0);
    unCubo.setPolyAlpha(0.3);
    unCubo.perFrame(t);
    glPopMatrix();
    glDisable(GL_BLEND);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();


    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();


    for(int i=1;i<6;i++) {
        fxmotionblur->perFrame(t);
    }
    fxmotionblur->postprepareFrame();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    xt=1.01;//10-0.05*_row; // xtremos
    miDemo->ponOrtopedico(4,4);
    float al=fmod(t,2),dp=0,dpy=-1; // desplazamiento
    glColor4f(1,1,1,pulso);
    glBindTexture(GL_TEXTURE_2D, this->layerTitle.texID);

    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-xt*2+dp,-xt+dpy,z_depth);

    glTexCoord2f(1,0);
    glVertex3f(xt*2+dp,-xt+dpy, z_depth);

    glTexCoord2f(1,1);
    glVertex3f(xt*2+dp,xt+dpy,  z_depth);

    glTexCoord2f(0,1);
    glVertex3f(-xt*2+dp,xt+dpy,z_depth);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    miDemo->quitaOrtopedico();
}

void FXritmo::init(void) {
	
    unCubo.setLength(3);
    unCubo.update();
    unCubo.setPolyAlpha(0.1);
    unaEsfera.setLength(3);
    unaEsfera.setIterations(4);
    unaEsfera.update();
    LoadTGA(&layerTitle,"./data/cosa01b.tga");
}


void FXritmo::start(void) {
    cam.SetPos(5,5,5);
    glLineWidth(1.0);
}

void FXritmo::stop(void) {
	
}

void FXritmo::deInit(void) {
    // desasignar recursos y tal, descargar ficheros, blabla
    this->unCubo.deInit();
    this->unaEsfera.deInit();
}

FXritmo::FXritmo() {
}

FXritmo::~FXritmo() {
}
