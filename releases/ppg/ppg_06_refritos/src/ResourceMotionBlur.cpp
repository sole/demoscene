#include "ResourceMotionBlur.h"
#include <iostream>
using namespace std;
#include "Render.h"

CResourceMotionBlur::CResourceMotionBlur() {
	this->m_Color = CPoint(1,1,1,1);
	this->m_scaleincx = 0;
	this->m_scaleincy = m_scaleincx;
	this->m_hasCustomBlending = false;
	this->m_cleanBuffer = false;
}

void CResourceMotionBlur::play(float _time) {	
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
	doCustomBlending();
	
	// Draw a plane using the whole view -> 4 vertex... etc
	m_Render->beginShapeQuads();
		
	m_Render->setTextureCoord(0,0);
	m_Render->addVertex(-width-incx,-height-incy);
	
	m_Render->setTextureCoord(texCoordX,0);
	m_Render->addVertex(width+incx,-height-incy);
	
	m_Render->setTextureCoord(texCoordX,texCoordY);
	m_Render->addVertex(width+incx, height+incy);
	
	m_Render->setTextureCoord(0,texCoordY);
	m_Render->addVertex(-width-incx,height+incy);
		
	m_Render->endShape();
	
	m_Render->disableTexture();
	
	// restore transparency
	m_Render->disableBlend();
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// restore view
	m_Render->orthoUnset();
	
	// Copy current framebuffer to our texture
	m_Render->copyToTexture(0,0,0,0,m_Render->getWidth(),m_Render->getHeight());
}

void CResourceMotionBlur::init() {
	// get our texture for blurring
	// must be a texture of the size of the window
	m_texPos = this->m_Render->createEmptyTexture(this->m_Render->getWidth(), this->m_Render->getHeight());
	
	this->m_texWidth = m_Render->getTextureWidth(m_texPos);
	this->m_texHeight = m_Render->getTextureHeight(m_texPos);
}

void CResourceMotionBlur::start() {
	
}

void CResourceMotionBlur::deInit(void) {
	
}

string CResourceMotionBlur::getType(void) {
	return "CResourceMotionBlur";
}

void CResourceMotionBlur::setParam(string name, string value) {
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
