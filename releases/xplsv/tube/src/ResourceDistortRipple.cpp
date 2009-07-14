#include "ResourceDistortRipple.h"
#include <iostream>
using namespace std;

#include "Render.h"

CResourceDistortRipple::CResourceDistortRipple() {
	this->m_Color = CPoint(1,1,1,1);
	this->m_scaleincx = 0;
	this->m_scaleincy = 0;
	this->m_hasCustomBlending = false;
	m_numX = 5;
	m_numY = 5;
	m_radioX = 20;
	m_radioY = 20;
	m_periodX = 1;
	m_periodY = 1;
}

void CResourceDistortRipple::play(float _time) {	
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
	static float xv[RESOURCEDISTORTRIPPLE_MAX_X], yv[RESOURCEDISTORTRIPPLE_MAX_Y]; // x and y vertexes
	static float txv[RESOURCEDISTORTRIPPLE_MAX_X], tyv[RESOURCEDISTORTRIPPLE_MAX_Y]; // tex x and y vertexes
	const float PI = 3.14159265f;
	const float PI2 = PI*2;
	
	for(i=0; i < m_numX+1; i++) {
		xv[i] = -width + i*quadincx + m_radioX*sin(_time*m_periodX + PI2*i/float(m_numX));
		txv[i] = i*texincx;
	}
	for(j=0; j < m_numY+1; j++) {
		tyv[j] = j*texincy;
		yv[j] = -height + j*quadincy + m_radioY*sin(_time*m_periodY + PI2*j/float(m_numY)) ;
	}
	// then correct outside points so the ripple does not never show an empty area
	xv[0] = -width;
	xv[m_numX] = width;
	yv[0] = -height;
	yv[m_numY] = height;
	
	m_Render->beginShapeQuads();
	for(i=0; i<m_numX; i++) {
	
		x = xv[i];
		x2 = xv[i+1];
		
		tx = txv[i] ;
		tx2 = txv[i+1];
		
		for(j=0; j<m_numY; j++) {
			
			y = yv[j];
			y2 = yv[j+1];
			
			ty = tyv[j];
			ty2 = tyv[j+1];

			m_Render->setTextureCoord(tx,ty);
			m_Render->addVertex(x-incx,y-incy);
			
			m_Render->setTextureCoord(tx2,ty);
			m_Render->addVertex(x2+incx,y-incy);
			
			m_Render->setTextureCoord(tx2, ty2);
			m_Render->addVertex(x2+incx, y2+incy);
			
			m_Render->setTextureCoord(tx,ty2);
			m_Render->addVertex(x-incx,y2+incy);
			
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

void CResourceDistortRipple::init() {
	// get our texture for blurring
	// must be a texture of the size of the window
	m_texPos = this->m_Render->createEmptyTexture(this->m_Render->getWidth(), this->m_Render->getHeight());
	
	this->m_texWidth = m_Render->getTextureWidth(m_texPos);
	this->m_texHeight = m_Render->getTextureHeight(m_texPos);
}

void CResourceDistortRipple::start() {
	
}

void CResourceDistortRipple::deInit(void) {
	
}

string CResourceDistortRipple::getType(void) {
	return "CResourceDistortRipple";
}

void CResourceDistortRipple::setParam(string name, string value) {
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
		this->m_numX = (tmp < RESOURCEDISTORTRIPPLE_MAX_X-1 ? tmp : RESOURCEDISTORTRIPPLE_MAX_X);
	}
	if(name=="num_y") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numY = (tmp < RESOURCEDISTORTRIPPLE_MAX_Y-1 ? tmp : RESOURCEDISTORTRIPPLE_MAX_Y);
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