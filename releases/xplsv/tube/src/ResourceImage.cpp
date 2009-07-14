#include "ResourceImage.h"
#include <iostream>
using namespace std;
#include "Render.h"

CResourceImage::CResourceImage() {
	// set color initially to white so we'll always see "Something"
	CPoint white(1,1,1,1);
	m_Color = white;
	
	// set default texture file source to empty so it'll fail if no texture is specified
	m_TextureFile = "";
	
	m_texWidth = 0;
	m_texHeight = 0;
	m_speedX = 0;
	m_speedY = 0;
	m_iniPosX= 0;
	m_iniPosY = 0;
	m_scaleX = 1;
	m_scaleY= 1;
}

void CResourceImage::play(float _time) {	
	bool useBlend = false;
	float currentColor[4];
	float width, height;
	
	if(!m_stretch) {
		width = this->m_texImgWidth*0.5;
		height = this->m_texImgHeight*0.5;
	} else {
		width = this->m_Render->getWidth()*0.5;
		height = this->m_Render->getHeight()*0.5;
	}
	
	// Set ortogonal view to 2,2 so we can put our points in -1,-1, etc...
	m_Render->orthoSet();
	// get current color
	m_Render->getCurrentColor(currentColor);
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	// set the current vertex color
	m_Render->setColor(currColor);
	
	useBlend = true;
	m_Render->enableBlend();
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}

	// Draw a plane using the whole view -> 4 vertex... etc, with texture
	m_Render->enableTexture();
	m_Render->bindTexture(m_texPos /*this->m_Texture.getTexId()*/);
	
	// Apply the speed displacements
	float elapsedTime = _time-this->m_startTime;
	m_Render->setModelMatrix();
	m_Render->pushMatrix();
	m_Render->scale(m_scaleX, m_scaleY, 1);
	m_Render->translate(this->m_iniPosX + (elapsedTime)*this->m_speedX, this->m_iniPosY + elapsedTime*this->m_speedY, 0);
	
	m_Render->beginShapeQuads();
	
	m_Render->setTextureCoord(0,0);
	m_Render->addVertex(-width,-height);
	
	m_Render->setTextureCoord(1,0);
	m_Render->addVertex(width,-height);
	
	m_Render->setTextureCoord(1,1);
	m_Render->addVertex(width, height);
	
	m_Render->setTextureCoord(0,1);
	m_Render->addVertex(-width,height);
	
	m_Render->endShape();
	
	m_Render->setModelMatrix();
	m_Render->popMatrix();
	
	m_Render->disableTexture();
	
	// restore transparency
	if(useBlend) {
		m_Render->disableBlend();
	}
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	
	// restore view
	m_Render->orthoUnset();
	
	
	
}

void CResourceImage::init() {
	// Request the loading of the texture
	int textureIndex;
	
	textureIndex = m_Render->loadTexture(this->m_TextureFile);

	if(textureIndex>=0) {
		m_texPos = textureIndex;

		this->m_texWidth = m_Render->getTextureWidth(textureIndex);
		this->m_texHeight = m_Render->getTextureHeight(textureIndex);
		this->m_texImgWidth = m_Render->getTextureImgWidth(textureIndex);
		this->m_texImgHeight = m_Render->getTextureImgHeight(textureIndex);
		
		// copy all parameters to our texture
		
		return;
	}
	cout << "CResourceImage--Bad donut " << endl;
}

void CResourceImage::start() {
	
}

void CResourceImage::deInit(void) {
	
}

string CResourceImage::getType(void) {
	return "CResourceImage";
}

void CResourceImage::setParam(string name, string value) {
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
	if(name=="src") {
		m_TextureFile = value;
	}
	if(name=="speed_x") {
		m_speedX = (float) atof(value.c_str());
	}
	if(name=="speed_y") {
		m_speedY = (float) atof(value.c_str());
	}
	if(name=="ini_pos_x") {
		m_iniPosX = (float) atof(value.c_str());
	}
	if(name=="ini_pos_y") {
		m_iniPosY = (float) atof(value.c_str());
	}
	if(name=="blending") {
		this->m_hasCustomBlending = true;
		this->m_renderBlendingPos = this->m_Render->getBlending(value);
	}
	if(name=="stretch") {
		if(value=="yes") {
			m_stretch = true;
		} else {
			m_stretch = false;
		}
	}
	if(name=="scale_x") {
		m_scaleX = (float) atof(value.c_str());
	}
	if(name=="scale_y") {
		m_scaleY = (float) atof(value.c_str());
	}
}

