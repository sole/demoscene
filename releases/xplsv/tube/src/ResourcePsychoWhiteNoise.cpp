#include "ResourcePsychoWhiteNoise.h"
#include <iostream>
#include <cmath>
#include "Render.h"

#define ratio 0.25

using namespace std;
CResourcePsychoWhiteNoise::CResourcePsychoWhiteNoise(){
	this->m_numVertex = 32;
	m_numX = 1;
	m_numY = 1;
	m_hasCustomBlending=false;
}

void CResourcePsychoWhiteNoise::play(float _time) {	
	float currentColor[4];
	float renderWidth = m_Render->getWidth();
	float renderHeight = m_Render->getHeight();
	float origX = -renderWidth*0.5;
	float origY = -renderHeight*0.5;
	float width= renderWidth*ratio, height = renderHeight*ratio;
	float quadincx = width / float(m_numX), quadincy= height/float(m_numY);
	static unsigned char p1,p2,p3,p4,t1,t2,t3,t4;
	float x, x2, y, y2;
	int col;
		
	static float xv[RESOURCEPSYCHOWHITENOISE_MAX_X];
	static float yv[RESOURCEPSYCHOWHITENOISE_MAX_Y];
	unsigned int i,j;
	
	
	for(i=0; i < m_numX+1; i++) {
		xv[i] = origX + i*quadincx;
	}
	for(j=0; j < m_numY+1; j++) {
		yv[j] = origY + j*quadincy ;
	}
	
	// Set ortogonal view to 2,2 so we can put our points in -1,-1, etc...
	m_Render->orthoSet();
	// get current rendering color (for restoring it after)
	m_Render->getCurrentColor(currentColor);
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	// set the current vertex color
	m_Render->setColor(currColor);
	// enable blending
	m_Render->enableBlend();
	CPoint p;
	p.w*=this->m_alpha;
	
	m_Render->beginShapeQuads();
	
	static float t=0;
	static float invrandmax = 1.0/RAND_MAX;
	bool recalc = false;
	if(_time - t > 0.08) {
		recalc=true;
		t = _time;
	}
	
	for(i=0; i<m_numX; i++) {
		if(recalc) {
			t3=p3;
			t4=p4;
		}
		
		x = xv[i];
		x2 = xv[i+1];
		
		for(j=0; j<m_numY; j++) {
			
			y = yv[j];
			y2 = yv[j+1];
			
			p.x = rand()*invrandmax*0.5 ;
			p.y = p.x;
			p.z = p.x;
			
			m_Render->setColor(p);
			
			m_Render->addVertex(x,y);
			
			m_Render->addVertex(x2,y);
			
			m_Render->addVertex(x2, y2);
			
			m_Render->addVertex(x,y2);
			
		}
		
	}
	
	m_Render->endShape();

	// Now copy our little quads with noise in them to our texture
	m_Render->enableTexture();
	m_Render->bindTexture(m_texPos);
	m_Render->copyToTexture(0,0,0,0,width-1, height-1);
	m_Render->clear(RENDER_CLEAR_COLOR);
	p.x=1;p.y=1;p.z=1;
	p.x=m_Color.x;
	p.y=m_Color.y;
	p.z=m_Color.z;
	m_Render->setColor(p);
	float w,h;
	float textcoord = 0.6;
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
	m_Render->beginShapeQuads();
	for(i=0;i<renderWidth/width;i++) {
		w=origX+width*i;
		for(j=0;j<renderHeight/height;j++) {
			h=origY + (height-1)*j;
			m_Render->setTextureCoord(0,0);
			m_Render->addVertex(w,h);
			
			m_Render->setTextureCoord(textcoord,0);
			m_Render->addVertex(w+width,h);
			
			m_Render->setTextureCoord(textcoord,textcoord);
			m_Render->addVertex(w+width, h+height);
			
			m_Render->setTextureCoord(0,textcoord);
			m_Render->addVertex(w,height+h);
		}
	}
	m_Render->endShape();
	
	m_Render->disableTexture();
	// disable transparency
	m_Render->disableBlend();
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// restore view
	m_Render->orthoUnset();
}

void CResourcePsychoWhiteNoise::init() {
	m_texPos = this->m_Render->createEmptyTexture(this->m_Render->getWidth()*ratio, this->m_Render->getHeight()*ratio);
}

void CResourcePsychoWhiteNoise::start() {
	
}

void CResourcePsychoWhiteNoise::deInit(void) {
	
}

string CResourcePsychoWhiteNoise::getType(void) {
	return "CResourcePsychoWhiteNoise";
}

void CResourcePsychoWhiteNoise::setParam(string name, string value) {
	if(name=="r") {
		m_Color.x = (float) atof(value.c_str());
	}
	if(name=="g") {
		m_Color.y = (float) atof(value.c_str());
	}
	if(name=="b") {
		m_Color.z = (float) atof(value.c_str());
	}
	if(name=="a") {
		m_Color.w = (float) atof(value.c_str());
	}
	if(name=="radio") {
		m_radio = (float) atof(value.c_str());
	}
	if(name=="num_vertex") {
		m_numVertex = (unsigned int) atoi(value.c_str());
	}
	if(name=="num_x") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numX = (tmp < RESOURCEPSYCHOWHITENOISE_MAX_X-1 ? tmp : RESOURCEPSYCHOWHITENOISE_MAX_X);
	}
	if(name=="num_y") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numY = (tmp < RESOURCEPSYCHOWHITENOISE_MAX_Y-1 ? tmp : RESOURCEPSYCHOWHITENOISE_MAX_Y);
	}
	if(name=="blending") {
		this->m_hasCustomBlending = true;
		this->m_renderBlendingPos = this->m_Render->getBlending(value);
	}
}

