#include "ScenePlano.h"
#include "Demo.h"
extern Demo *miDemo;
#include "Music.h"
extern Music miMusic;

#include <math.h>

void drawCube(float _diameter, bool isWire) {
	if(isWire)
		glBegin(GL_LINE_STRIP);
	else
		glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-_diameter, -_diameter,  _diameter);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( _diameter, -_diameter,  _diameter);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( _diameter,  _diameter,  _diameter);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-_diameter,  _diameter,  _diameter);	// Top Left Of The Texture and Quad
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-_diameter, -_diameter, -_diameter);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-_diameter,  _diameter, -_diameter);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( _diameter,  _diameter, -_diameter);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( _diameter, -_diameter, -_diameter);	// Bottom Left Of The Texture and Quad
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-_diameter,  _diameter, -_diameter);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-_diameter,  _diameter,  _diameter);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( _diameter,  _diameter,  _diameter);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( _diameter,  _diameter, -_diameter);	// Top Right Of The Texture and Quad
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-_diameter, -_diameter, -_diameter);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( _diameter, -_diameter, -_diameter);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( _diameter, -_diameter,  _diameter);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-_diameter, -_diameter,  _diameter);	// Bottom Right Of The Texture and Quad
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( _diameter, -_diameter, -_diameter);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( _diameter,  _diameter, -_diameter);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( _diameter,  _diameter,  _diameter);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( _diameter, -_diameter,  _diameter);	// Bottom Left Of The Texture and Quad
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-_diameter, -_diameter, -_diameter);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-_diameter, -_diameter,  _diameter);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-_diameter,  _diameter,  _diameter);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-_diameter,  _diameter, -_diameter);	// Top Left Of The Texture and Quad
	glEnd();
}

void ScenePlano::play(float _time) {
	unsigned int i=0,j;
	static int playing=0;
	glClear(GL_DEPTH_BUFFER_BIT);
	
	// Getting the bombo!!
	unsigned int bombo, snare;
	
	if(this->effectsList[0]->isPlaying(_time)!=-1)
		bombo=1;
	else
		bombo=0;
	if(this->effectsList[1]->isPlaying(_time)!=-1)
		snare=1;
	else
		snare=0;


	Point camPos,camLook;
	Path *currentPath;
	
	static float cameraTimer=0;
	static unsigned int currentCamPoint=0;
	
	if((_time>=49.0) && (_time<135.151))
	{
		currentPath = &pathCam02;		
	}
	else
	{
		currentPath = &pathCam01;
	}

	if(_time-cameraTimer>0.02)
	{
		cameraTimer=_time;
		unsigned int maxPoints = currentPath->getNumICP();
		currentCamPoint++;
		if(currentCamPoint>maxPoints)
			currentCamPoint = 0;
	}
	currentPath->getPointAt(currentCamPoint, &camPos);
	Camera miCam;
	float d=120;
	
	miCam.setFar(1,10000);
	miCam.SetPos(camPos);
	miCam.SetLook(0.1f,0.1f,0.1f);
	
	static float timerCameraFov=-1;
	static float camFov=0;
	float camVar;
	// Cuando se ejecuta el efecto el camFov vuelve a 0
	if(this->effectsList[2]->isPlaying(_time)!=-1)
		camFov=0;
	
	if((_time>106.971) && (_time - timerCameraFov > 0.03) ){
		timerCameraFov = _time;
		// Actualizar el fov
		
		// Sumando
		camFov+=0.55;
		
	}
	miCam.setFov(45+camFov);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	miCam.toOGL();
	
	// El roll
	glMatrixMode(GL_PROJECTION);
	static float camRoll=0;
	static float camRollDrumAdd=0;
	static float timerCameraRoll = -1;
	
	if(timerCameraRoll == -1)
	{
		timerCameraRoll = _time;
	}
	float camRollDif = _time - timerCameraRoll;
	camRoll += camRollDif * 11.0f ;
	
	timerCameraRoll = _time;
	
	if(camRollDrumAdd)
	{
		camRollDrumAdd -= camRollDif * 9.0f;
		if(camRollDrumAdd < 0) { camRollDrumAdd = 0; }
	}
	if(bombo)
	{
		camRollDrumAdd = 4;
	}

	camRoll += camRollDrumAdd;

	if((_time > 78.260) && (_time < 92.473) ) {
		glRotatef(camRoll,0,0,1);
	} else if(_time > 163.590) {
		glRotatef(camRoll,0,0,1);
	} else {
		glRotatef(camRoll,1,0,0);
	}

	//_________ Fin del roll

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	static float fPlaneWidth=5;
	static float fMaxPlaneWidth=100;
	static float tbefore=0;
	if(_time>4.794 && ((_time-tbefore)>0.02) && (_time<49.765)) {
		if(fPlaneWidth<fMaxPlaneWidth) {
			fPlaneWidth+=0.0025*fPlaneWidth*fPlaneWidth;
			tbefore=_time;
		}
	
	} else if((_time>49.765) && (_time<106)) {
		fPlaneWidth=(20-_time);
		fPlaneWidth = (fPlaneWidth > 0) ? fPlaneWidth : 0; 
	} else if(_time < 192.235) {
		fPlaneWidth = fMaxPlaneWidth;
	} else if(_time>= 192.235) {
		fPlaneWidth = 192.235 / (_time*5);
	}
	static float fPlaneStart=-5000;
	static float fPlaneEnd=-fPlaneStart;
	static unsigned int numInterv=64;
	float fft[512];
	
	miMusic.getFFT(fft,512);
	
	float fHeight,fQuadLength=(fPlaneEnd-fPlaneStart)/float(numInterv),fX;
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	
	if((_time > 49.765) && (_time <= 106.702)) {
		glColor4f(1,1,1, 49.765/(_time));
	} else if(_time < 193.235) {
		//glColor4f(0,0.635,0.894, 1);
		glColor4f(1,1,1, 1);
	} else {
		glColor4f(1,1,1,0);
	}
	float invlog=0.001/fft[0];
	float fPlaneWidthHalf = fPlaneWidth*0.5;
	if(_time<192.235) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_TexturePlane.texID);
		glBegin(GL_QUADS);
			
			fHeight=0;
			glTexCoord2d(0,0);
			glVertex3d(fPlaneStart,-fPlaneWidthHalf,fHeight);
			glTexCoord2d(1,0);
			glVertex3d(fPlaneStart,fPlaneWidthHalf,fHeight);
			glTexCoord2d(1,1);
			glVertex3d(fPlaneEnd,fPlaneWidthHalf,fHeight);
			glTexCoord2d(0,1);
			glVertex3d(fPlaneEnd,-fPlaneWidthHalf,fHeight);

			glTexCoord2d(0,0);
			glVertex3d(fPlaneStart,fHeight,-fPlaneWidthHalf);
			glTexCoord2d(1,0);
			glVertex3d(fPlaneStart,fHeight,fPlaneWidthHalf);
			glTexCoord2d(1,1);
			glVertex3d(fPlaneEnd,fHeight,fPlaneWidthHalf);
			glTexCoord2d(0,1);
			glVertex3d(fPlaneEnd,fHeight,-fPlaneWidthHalf);
			//glVertex3d(0,0,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
	
	// Dibuja los paralelepipedos
	if(((_time > 7.151) && (_time< 64.040)) || ((_time > 135.151) && (_time < 192.235))) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		float fVelX = 5;
		static float fTimerParalel = 0;
		if(_time - fTimerParalel > 0.02) {
			fVelX=6;
			fTimerParalel = _time;
		} else
			fVelX=0;
		for(i=0;i<m_uiNumParalel;i++) {
			// Calcular la nueva posicion (en funcion de t)
			m_vParalelPos[i].x -= fVelX;
			if(m_vParalelPos[i].x < -m_fXRange) {
				m_vParalelPos[i].x = m_fXRange;
				m_vParalelPos[i].y = getRand()*m_fYRange-getRand()*m_fYRange;
				m_vParalelPos[i].z = getRand()*m_fZRange-getRand()*m_fZRange;
			}
			
			
			//glPushMatrix();
			if((_time > 49.765) ) {
				//float newScale = 49.765/(_time*20);
				Point p;
				//glScalef(newScale, newScale, newScale);
				p=scene3d.getGeomObjectAt(0)->getWireframeColor();

				if (_time < 135.151) {
					p.w=p.w * 49.765f/(_time);
				} else {
					p.w=1;
				}
				scene3d.getGeomObjectAt(0)->setWireframeColor(p.x,p.y,p.z,p.w);
			}
			glPushMatrix();
			glTranslatef(this->m_vParalelPos[i].x,this->m_vParalelPos[i].y,this->m_vParalelPos[i].z);

			//glRotatef(20*i+_time,1,0,0);
			
			scene3d.getGeomObjectAt(0)->draw();
			glPopMatrix();
			//glPopMatrix();

		}
		glDisable(GL_BLEND);

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}// _______Fin de paralelepideswo____________________

	// Dibujar los c�rculos
	static float f_quadSepar=m_fXRange*2 / m_uiNumQuadrics;
	static float f_quadRad = 40 / m_uiNumQuadrics*1.0;
	float f_angStart, f_angEnd, f_angLength,fr1,fr2;
	f_angLength = 15;//30 + fmod(_time,90);
	if(((_time > 21.362) && (_time<49.795)) || ( (_time>163.590) && (_time < 192.235) )) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		
		
		for(i=0;i<this->m_uiNumQuadrics;i++) {

			f_angStart = fmod(_time*100 , 270);//(180+int(_time*100)+i*15+(int)f_angLength)%360;
			f_angEnd = f_angStart + f_angLength;
			//f_angStart = f_angEnd - f_angLength;
			glPushMatrix();
			glTranslatef(f_quadSepar*i-m_fXRange,0,0);		
			glRotatef(90,0,1,0);
			for(j=0;j<this->m_uiNumSubQuadrics;j++) {
				glColor4f(0,0.635,0.894, 1.0*j/m_uiNumSubQuadrics*1.0);
				//gluPartialDisk(m_Quadric,2.40f+j,40.0f/m_uiNumSubQuadrics*j,32,1,f_angStart,f_angEnd);
				fr1 = 1.0f+j*f_quadRad;
				fr2 = fr1 + f_quadRad*0.85;
				f_angStart = fmod(_time*100 + 20*i + j*15, 360-f_angLength);//(180+int(_time*100)+i*15+(int)f_angLength)%360;
				f_angEnd = f_angStart + f_angLength;
				gluPartialDisk(m_Quadric,fr1,fr2,32,1,f_angStart,f_angEnd);
			}
			glPopMatrix();
		}
		glDisable(GL_BLEND);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	} else if ((_time >= 49.795) && (_time<64.040)) {
		glEnable(GL_BLEND);	
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();		

		f_angStart = fmod(_time*100 , 270);//(180+int(_time*100)+i*15+(int)f_angLength)%360;
		f_angEnd = f_angStart + f_angLength;
		//f_angStart = f_angEnd - f_angLength;
		glPushMatrix();
		glTranslatef(0,0,0);		
		i=m_uiNumSubQuadrics*16;
		for(j=0;j<i;j++) {
			glPushMatrix();
			glTranslatef(2*m_fXRange*sin(_time*0.125+j*20),0,0);
			glRotatef(90,0,1,0);
			glColor4f(0,0.635,0.894, 1.0*j/i*1.0);
			//gluPartialDisk(m_Quadric,2.40f+j,40.0f/m_uiNumSubQuadrics*j,32,1,f_angStart,f_angEnd);
			fr1 = 1.0f+j*f_quadRad*0.25;
			fr2 = fr1 + f_quadRad*0.85;
			f_angStart = fmod(_time*10 + j*15, 360-f_angLength);//(180+int(_time*100)+i*15+(int)f_angLength)%360;
			f_angEnd = f_angStart + f_angLength;
			gluPartialDisk(m_Quadric,fr1,fr2,32,1,f_angStart,f_angEnd);
			glPopMatrix();
		}
		glPopMatrix();
		
		glDisable(GL_BLEND);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

	}
	// ________Fin de c�rculos

	
	// Dibujar la �espiral?
	static float fTimerSpiral = 0;
	float fVelSpiralX;
	if(_time - fTimerSpiral > 0.02) {
		fVelSpiralX=10;
		fTimerSpiral = _time;
	} else
		fVelSpiralX=0;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glColor4f(1,1,1,0.05f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	static float f_espX, f_espY, f_espZ;
	float m_espPeriodo = _time * 2;		
	
	if((_time > 35.600) && (_time<49.795))
	{
		f_espX-=fVelSpiralX;
		if(f_espX<-m_fXRange) {
			f_espX = m_fXRange;
		}
		f_espY=fPlaneWidth * sin(m_espPeriodo);
		f_espZ=fPlaneWidth * cos(m_espPeriodo);
		orisis.x=f_espX;
		orisis.y=f_espY;
		orisis.z=f_espZ;
		this->parts1.setOrigin(orisis);
		this->parts1.setMinimumEnergy(600*(_time/35.6f));
		this->partm1.Update(_time);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_TextureParticle.texID);
		this->partm1.Render();
		glDisable(GL_TEXTURE_2D);
	} else if((_time >= 49.795) && (_time < 92)) {
		orisis.x=-m_fXRange + (_time-49.795);
		orisis.y=0;
		orisis.z=0;
		this->parts1.setOrigin(orisis);
		this->parts1.setMinimumEnergy(600);
		this->partm1.Update(_time);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_TextureParticle.texID);
		this->partm1.Render();
		glDisable(GL_TEXTURE_2D);
	}
		
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glDisable(GL_BLEND);
	
	
	// ________ Fin de espiral
	
	// Ahora las cosas que caen
	if((_time > 49.795) && (_time<106.702)) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		//glLoadIdentity(); // XXX ???
		
		
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE,GL_ONE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_TextureParticle.texID);
		
		float an=15, x,y, z;
		static int num_cosas = 100;
		
		glColor4f(1,1,1,1);		

		for(i=0;i<num_cosas;i++) {
			//if(_time<64.040) {
				x=fmod(i*10+_time*20,m_fXRange+m_fXRange)-m_fXRange;
				y=m_fYRange*sin(_time+i);
				z=m_fZRange*cos(_time+i);
				an = fabs((y+z)*0.25) + 5;
				
				glBegin(GL_QUADS);
					glTexCoord2d(0,0);	
					glVertex3f(x,y-an,z-an);
					glTexCoord2d(1,0);	
					glVertex3f(x,y-an,z+an);
					glTexCoord2d(1,1);	
					glVertex3f(x,y+an,z+an);
					glTexCoord2d(0,1);	
					glVertex3f(x,y+an,z-an);
				glEnd();	
						
		}		
		
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	// _________ fin de cosas que caen

	// Unas barras alrededor de todo (??)
	if((_time > 49.795) && (_time<135.151)) {
		unsigned int numBarras=40;
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_ONE,GL_ONE);
		glLineWidth(0.25f);
		glColor4f(0,0.5,0.75,0.5);
		for(i=0;i<numBarras;i++) {		
			float y,z;
			y=(10+m_fYRange)*sin(_time+i);
			z=(10+m_fZRange)*cos(_time+i);
			
			glBegin(GL_LINES);
				glVertex3f(-m_fXRange, y , z);
				glVertex3f(m_fXRange+m_fXRange, y , z);
			glEnd();		
			
		}		
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_BLEND);	
	} // _________ fin de barras alrededor...


	// para el "espaciok" de fondo - alias la matriz de cubos!!
	if((_time >= 106.702) && (_time < 166.590)) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		static unsigned int numX,numY,numZ,k;
		static float tamX,tamY,tamZ;
		static float startX=-100,startY=-100,startZ=-100;
		static float rotation=0,rotX=0,rotY=0,rotZ=0,rotInc=5;
		static unsigned int lastRot=0;
		glEnable(GL_BLEND);
		
		glBlendFunc(GL_ONE, GL_ONE);
		
		glColor4f(0,0.5,0.75,0.5);
		glPointSize(1);
		tamX=tamY=tamZ=32;
		numX=numY=numZ=8;
		float x,y,z;
		if(bombo==1) {
			lastRot++;
			if(lastRot>2) 
				lastRot=0;
			switch(lastRot) {
			case 0: rotX+=rotInc;break;
			case 1: rotY+=rotInc;break;
			case 2: rotZ+=rotInc;break;

			}
			rotation += 5;

		}
		
		startX = -(tamX * numX)*0.5;
		startY = -(tamY * numY)*0.5;
		startZ = -(tamZ * numZ)*0.5;
		
		glEnable(GL_DEPTH_TEST);

		for(i=0;i<numX;i++) {				
			x = startX + i*tamX;
			for(j=0;j<numX;j++) {
				y = startY + j*tamY;				
				for(k=0;k<numX;k++) {
					z= startZ + k*tamZ;					
					glPushMatrix();
					glTranslatef(x,y,z);
					glColor4f(1,0,0.267,0.5);
					float cubediam;
					cubediam = 2.0+fmod(x+y+z+2*sin(x+_time*2)+2*cos(_time*2+y),10);
					if(_time > 161.590) {
						cubediam *= (161.590/(_time*10));
					}
					glMatrixMode(GL_MODELVIEW);
					glPushMatrix();
					if(_time > 135.151) {
						float otraescala = 135.151 / (_time*2);
						glScalef(_time-135.151, otraescala, otraescala);
					}
					drawCube(cubediam, false);
					
					glMatrixMode(GL_MODELVIEW);
					glPopMatrix();
					
					glPopMatrix();
					
				}
			}	
			
		}
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glDisable(GL_BLEND);	
	} // _________ fin de espaciok...

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Layers
	static float layerAlpha=0;
	static float layerAlphaVar=0;
	static float timerSnare = -1000;
	if(snare)
		layerAlpha=1;
		
	if(layerAlpha > 0)
	{
		layerAlpha -= (_time - timerSnare) * 1.8f;
		timerSnare = _time;
	}
	

	miDemo->ponOrtopedico();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	static int currentLayer = 1;
	if(bombo)
	{
		currentLayer = ((currentLayer+1)%3) + 1;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);//glBlendFunc(GL_ONE,GL_DST_COLOR);
	glEnable(GL_TEXTURE_2D);
	// La textura que usamos depende del tiempo!!
	// TO DO!!!! TODO
	if((_time>=0) && (_time < 106.702)) {
		glBindTexture(GL_TEXTURE_2D, m_TextureVslpx.texID);
	} else if ((_time >= 106.702) && (_time<120)) {
		glBindTexture(GL_TEXTURE_2D, m_TextureTrace.texID);
	} else if ((_time >= 120) && (_time<135.151) ){
		glBindTexture(GL_TEXTURE_2D, m_TextureSole.texID);
	} else if ((_time >= 135.151) && (_time<149.339)) {
		glBindTexture(GL_TEXTURE_2D, m_TextureDalezy.texID);
	} else if ((_time >= 149.339) && /*(_time<163.235)*/ (_time < 192.235) ) {
		if(currentLayer == 1)
			glBindTexture(GL_TEXTURE_2D, m_TextureLayer01.texID);
		else if(currentLayer == 2)
			glBindTexture(GL_TEXTURE_2D, m_TextureLayer02.texID);
		else 
			glBindTexture(GL_TEXTURE_2D, m_TextureLayer03.texID);
	} else if ( (_time>163.235) && (_time < 192.235)) {
		//glBindTexture(GL_TEXTURE_2D, m_TextureVslpx2.texID);
		
	} else if(_time>=192.235) { // Final
		glBindTexture(GL_TEXTURE_2D, m_Texture2005.texID);
	} 
	
	
	glColor4f(1,1,1,layerAlpha);
	if(_time>=192.235) {
		layerAlpha = 192.235 / _time;
	}
	float xt = 320.0f, yt = 240.0f, z_depth = 0.15f;

	// Dibujamos centrado SOLO cuando no son los greetings (que son rollo scroll y
	// hay que desplazarlos)
	if((_time<49.795) || (_time>106.72)) {
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0); glVertex3f(-xt, -yt,  z_depth);
			glTexCoord2f(1.0f, 0); glVertex3f( xt, -yt,  z_depth);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( xt,  yt,  z_depth);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-xt,  yt,  z_depth);

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	// El panoramico!
	float xp = 340, yp = 200, yp2 = 250, zp = 0.15;
	glColor4f(0,0,0,1);
	glBegin(GL_QUADS);
		glVertex3f(-xp,yp,zp);
		glVertex3f(xp,yp,zp);
		glVertex3f(xp,yp2,zp);
		glVertex3f(-xp,yp2,zp);

		glVertex3f(-xp,-yp2,zp);
		glVertex3f(xp,-yp2,zp);
		glVertex3f(xp,-yp,zp);
		glVertex3f(-xp,-yp,zp);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	miDemo->quitaOrtopedico();
	
	
}

void ScenePlano::init() {
	unsigned int i=0;
	// Paralelelpideos
	m_uiNumParalel=SCENEPLANO_PARALELNUM;
	scene3d.loadFromFile("./data/d_paralel.ASE");
	scene3d.getGeomObjectAt(0)->setWire(false);
	m_fXRange = 500;
	m_fYRange = 20;
	m_fZRange = 20;
	for(i=0;i<this->m_uiNumParalel;i++) {		
		this->m_vParalelPos[i].x=getRand()*m_fXRange-getRand()*m_fXRange;	
		this->m_vParalelPos[i].y=getRand()*m_fYRange-getRand()*m_fYRange;
		this->m_vParalelPos[i].z=getRand()*m_fZRange-getRand()*m_fZRange;
	}
	// C�rculos
	m_uiNumQuadrics=SCENEPLANO_QUADRICNUM;
	m_uiNumSubQuadrics=SCENEPLANO_QUADRICNUM;
	this->m_Quadric=gluNewQuadric();
	gluQuadricNormals(this->m_Quadric,GL_FLAT);
	gluQuadricDrawStyle(this->m_Quadric,GLU_FILL);
	
	// La espiral
	orisis.x=-m_fXRange;orisis.y=0;orisis.z=0;
	
	this->partm1.Add(&parts1);
	parts1.setMinimumEnergy(600);
	parts1.setMinimumMass(20);
	parts1.setOrigin(orisis);
	parts1.Set(SCENEPLANO_MAXPARTICLES);
	parts1.setMassInc(0.75);
	parts1.setGravity(0,1,0);
	parts1.setTTL(150);
	
	LoadTGA(&m_TextureParticle, "./data/minik.png");
	LoadTGA(&m_TexturePlane, "./data/light.png");
	LoadTGA(&m_TextureVslpx, "./data/vslpx.png");
	LoadTGA(&m_TextureCircle,"./data/circle.png");
	LoadTGA(&m_TextureDalezy,"./data/dalezy.png");
	LoadTGA(&m_TextureLayer01,"./data/layer01.png");
	LoadTGA(&m_TextureLayer02,"./data/layer02.png");
	LoadTGA(&m_TextureLayer03,"./data/layer03.png");
	LoadTGA(&m_TextureSole,"./data/sole.png");
	LoadTGA(&m_TextureTrace,"./data/trace.png");
	LoadTGA(&m_TextureVslpx2,"./data/vslpx2.png");
	LoadTGA(&m_TextureXplsv,"./data/xplsv.png");
	LoadTGA(&m_Texture2005,"./data/2005.png");

	// Paths de camara
	pathCam01.loadPath("./data/12dolls_campath01_v2.ASE");
	pathCam02.loadPath("./data/12dolls_pathcirculo.ASE");
	pathCamLook01.loadPath("./data/12dolls_camlook01.ASE");

	// TODO this->numEffects=0;
	for(i=0;i<(unsigned)this->numEffects;i++) {		
		this->effectsList[i]->init();	
	}
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

}

void ScenePlano::start() {
	int i=0;
}

void ScenePlano::deInit(void) {
	int i=0;
}

const char* ScenePlano::getSceneType(void) {
	return "ScenePlano";
}
