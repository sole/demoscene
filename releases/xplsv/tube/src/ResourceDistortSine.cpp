#include "ResourceDistortSine.h"
#include "Render.h"
#include <iostream>
#include <cmath>
using namespace std;

CResourceDistortSine::CResourceDistortSine() {
	this->m_Color = CPoint(1,1,1,1);
	this->m_scaleincx = 0;
	this->m_scaleincy = 0;
	this->m_hasCustomBlending = false;
	m_numX = 80;
	m_numY = 80;
	m_radioX = 20;
	m_radioY = 20;
	m_periodX = 1;
	m_periodY = 1;
}

void CResourceDistortSine::play(float _time) {	
	float currentColor[4];
	float width, height;
	float texCoordX, texCoordY;
	float renderWidth = m_Render->getWidth();
	float renderHeight = m_Render->getHeight();
	float incx = this->m_scaleincx;
	float incy = this->m_scaleincy;
	
	
	texCoordX = renderWidth / this->m_texWidth; 
	texCoordY = renderHeight / this->m_texHeight;
	
	width = renderWidth*0.5;
	height = renderHeight*0.5;
	
	// Enable texturing
	m_Render->enableTexture();
	m_Render->bindTexture(m_texPos);
	
	// Copy current framebuffer to our texture
	m_Render->copyToTexture(0,0,0,0,int(renderWidth), int(renderHeight));
	
	// Set ortogonal view
	m_Render->orthoSet(renderWidth, renderHeight);
	// get current rendering color (for restoring it after)
	m_Render->getCurrentColor(currentColor);
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	
	// set the current vertex color
	m_Render->setColor(currColor);
	
	if(this->m_cleanBuffer) { // might be dangerous by deleting all previ content
		m_Render->clear(RENDER_CLEAR_COLOR);
	}
	
	// set transparency
	m_Render->enableBlend();
	
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
	// Draw a plane using the whole view -> 4 vertex... etc
	
	
	unsigned int i, j;
	float x, x2, y, y2, tx, tx2, ty, ty2;
	static float texincx = texCoordX / float(m_numX);
	static float texincy = texCoordY / float(m_numY);
	static float quadincx = (renderWidth) / float(m_numX);
	static float quadincy = (renderHeight ) / float(m_numY);
	static float xv[RESOURCEDISTORTSINE_MAX_X], yv[RESOURCEDISTORTSINE_MAX_Y]; // x and y vertexes
	
	float txv[RESOURCEDISTORTSINE_MAX_X], tyv[RESOURCEDISTORTSINE_MAX_Y]; // tex x and y vertexes
	const float PI = 3.14159265f;
	const float PI2 = PI*2;
	
	for(i=0; i < m_numX+1; i++) {
		txv[i] = i*texincx;
	}
	for(j=0; j < m_numY+1; j++) {
		tyv[j] = j*texincy;
	}
	CPoint p;
	m_VertArray[1][0] = p;
	
	for(i=0; i <= m_numX; i++) { 
		for(j=0; j <= m_numY; j++) {
			m_VertArray[i][j].y = -height + j*quadincy;
			if(i==0) {
				m_VertArray[i][j].x = -width;
			} else if(i<m_numX) {
				m_VertArray[i][j].x = -width + i*quadincx + m_radioX*cos(m_VertArray[i][j].y + _time*m_periodY)+sin( PI2*j/float(m_numY) + _time*this->m_periodX );	
			} else {
				m_VertArray[i][j].x = width;
			}
			
		}
		
	}
	
	
	
	// then correct outside points so the ripple does not never show an empty area
	xv[0] = -width;
	xv[m_numX] = width;
	yv[0] = -height;
	yv[m_numY] = height;
	
	
	float desp;
	
	m_Render->beginShapeQuads();
	for(j=0; j<m_numY; j++) {
		for(i=0; i<m_numX; i++) {
		
		
			tx = txv[i] ;
			tx2 = txv[i+1];
			
			x = m_VertArray[i][j].x;
			x2 = m_VertArray[i+1][j].x;
			
			y = m_VertArray[i][j].y;
			y2 = m_VertArray[i][j+1].y;
			
			ty = tyv[j];
			ty2 = tyv[j+1];
			
			
			m_Render->setTextureCoord(tx,ty);
			m_Render->addVertex(x,y);
			
			m_Render->setTextureCoord(tx2,ty);
			m_Render->addVertex(x2,y);
			
			m_Render->setTextureCoord(tx2, ty2);
			m_Render->addVertex(x2, y2);
			
			m_Render->setTextureCoord(tx,ty2);
			m_Render->addVertex(x,y2);
			
		}	
	}
	m_Render->endShape();
	
	m_Render->disableTexture();
	
	// restore transparency
	m_Render->disableBlend();
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// restore view
	m_Render->orthoUnset();
	
	
}

void CResourceDistortSine::init() {
	// get our texture for blurring
	// must be a texture of the size of the window
	m_texPos = this->m_Render->createEmptyTexture(this->m_Render->getWidth(), this->m_Render->getHeight());
	
	this->m_texWidth = m_Render->getTextureWidth(m_texPos);
	this->m_texHeight = m_Render->getTextureHeight(m_texPos);
	
	// init vertexes matrix
	unsigned int i,j;
	this->m_VertArray = new CPoint *[m_numX+1];
	for(i=0; i<m_numX+1; i++) {
		m_VertArray[i] = new CPoint[m_numY+1];
	}
	CPoint p;
	
	for(i=0; i<=m_numX;i++) {
		for(j=0; j<=m_numY;j++) {
			m_VertArray[i][j] = p;
		}
	}
}

void CResourceDistortSine::start() {
	
}

void CResourceDistortSine::deInit(void) {
	// de init vertexes matrix
	
	for(unsigned int i=0; i<m_numY; i++) {
		// delete m_VertArray[i];
	}
	
	delete this->m_VertArray; 
}

string CResourceDistortSine::getType(void) {
	return "CResourceDistortSine";
}

void CResourceDistortSine::setParam(string name, string value) {
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
	if(name=="inc_x") {
		this->m_scaleincx = (float) atof(value.c_str());
	}
	if(name=="inc_y") {
		this->m_scaleincy = (float) atof(value.c_str());
	}
	if(name=="num_x") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numX = (tmp < RESOURCEDISTORTSINE_MAX_X-1 ? tmp : RESOURCEDISTORTSINE_MAX_X);
	}
	if(name=="num_y") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numY = (tmp < RESOURCEDISTORTSINE_MAX_Y-1 ? tmp : RESOURCEDISTORTSINE_MAX_Y);
	}
	if(name=="radio_x") {
		this->m_radioX = (float) atof(value.c_str());
	}
	if(name=="radio_y") {
		this->m_radioY = (float) atof(value.c_str());
	}
	if(name=="period_x") {
		this->m_periodX = (float) atof(value.c_str());
	}
	if(name=="period_y") {
		this->m_periodY = (float) atof(value.c_str());
	}
	if(name=="clean") {
		if(value=="yes") {
			this->m_cleanBuffer = true;
		} else {
			this->m_cleanBuffer = false;
		}
	}
	if(name=="blending") {
		this->m_hasCustomBlending = true;
		this->m_renderBlendingPos = this->m_Render->getBlending(value);
	}
}
