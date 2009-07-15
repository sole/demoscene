#include "ResourceRadialBlur.h"
#include <iostream>
using namespace std;
#include "Render.h"

CResourceRadialBlur::CResourceRadialBlur() {
	this->m_Color = CPoint(1,1,1,1);
	this->m_numCopies=30;
	this->m_scaleincx = 20;
	this->m_scaleincy = m_scaleincx;
	this->m_hasCustomBlending = false;
	this->m_updateAlpha = true;
}

void CResourceRadialBlur::play(float _time) {	
	float currentColor[4];
	float width, height;
	float texCoordX, texCoordY;
	
	texCoordX = m_Render->getWidth() / this->m_texWidth; 
	texCoordY = m_Render->getHeight() / this->m_texHeight;

	width = m_Render->getWidth()*0.5;
	height = m_Render->getHeight()*0.5;
	
	// Enable texturing
	m_Render->enableTexture();
	m_Render->bindTexture(m_texPos);
	
	// Copy current framebuffer to our texture
	m_Render->copyToTexture(0,0,0,0,m_Render->getWidth(),m_Render->getHeight());
	
	// Set ortogonal view to 2,2 so we can put our points in -1,-1, etc...
	m_Render->orthoSet(m_Render->getWidth(),m_Render->getHeight());
	// get current rendering color (for restoring it after)
	m_Render->getCurrentColor(currentColor);
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	float currAlpha = currColor.w;
	float alphaInc = currAlpha/float(this->m_numCopies);
	// set the current vertex color
	m_Render->setColor(currColor);
	
	if(this->m_cleanBuffer) {
		m_Render->clear(RENDER_CLEAR_COLOR);
	}
	
	// set transparency
	m_Render->enableBlend();
	
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
	// Draw a plane using the whole view -> 4 vertex... etc
	m_Render->beginShapeQuads();
	
	float incx, incy;
	for(int i=0; i<this->m_numCopies; i++) {
		
		currColor.w -= alphaInc;
		
		m_Render->setColor(currColor);
		
		incx = m_scaleincx * i;
		incy = m_scaleincy * i;
		
		m_Render->setTextureCoord(0,0);
		m_Render->addVertex(-width-incx,-height-incy);
		
		m_Render->setTextureCoord(texCoordX,0);
		m_Render->addVertex(width+incx,-height-incy);
		
		m_Render->setTextureCoord(texCoordX,texCoordY);
		m_Render->addVertex(width+incx, height+incy);
		
		m_Render->setTextureCoord(0,texCoordY);
		m_Render->addVertex(-width-incx,height+incy);
		
	
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

void CResourceRadialBlur::init() {
	// get our texture for blurring
	// must be a texture of the size of the window
	m_texPos = this->m_Render->createEmptyTexture(this->m_Render->getWidth(), this->m_Render->getHeight());
	
	this->m_texWidth = m_Render->getTextureWidth(m_texPos);
	this->m_texHeight = m_Render->getTextureHeight(m_texPos);
}

void CResourceRadialBlur::start() {
	
}

void CResourceRadialBlur::deInit(void) {
	
}

string CResourceRadialBlur::getType(void) {
	return "CResourceRadialBlur";
}

void CResourceRadialBlur::setParam(string name, string value) {
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
	if(name=="times") {
		this->m_numCopies = (int) atoi(value.c_str());
		if(this->m_numCopies<=0) 
			this->m_numCopies=1;
	}
	if(name=="inc_x") {
		this->m_scaleincx = (float) atof(value.c_str());
	}
	if(name=="inc_y") {
		this->m_scaleincy = (float) atof(value.c_str());
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
