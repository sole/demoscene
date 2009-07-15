#include "ResourceImageSequence.h"
#include "Render.h"
#include <iostream>
using namespace std;

CResourceImageSequence::CResourceImageSequence() {
	// set color initially to white so we'll always see "Something"
	CPoint white(1,1,1,1);
	m_Color = white;
	
	// set default texture file source to empty so it'll fail if no texture is specified
	m_TextureFile = "";
	
	m_hasCustomBlending=false;
		
	m_texWidth = 0;
	m_texHeight = 0;
	m_speedX = 0;
	m_speedY = 0;
	m_iniPosX= 0;
	m_iniPosY = 0;
	
	m_fps = 12.0f;
	m_spf = 1.0f/m_fps;
	
	m_filesPath = "";
}

void CResourceImageSequence::play(float _time) {	
	float currentColor[4];
	float width, height;
	
	if(!m_stretch) {
		width = this->m_texWidth*0.5;
		height = this->m_texHeight*0.5;
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
	// always set transparency
	m_Render->enableBlend();
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
	
	// Draw a plane using the whole view -> 4 vertex... etc, with texture
	m_Render->enableTexture();
	
	// Which texture to bind?	
	static float t;
	float dif;
	dif = _time - t;
	if(dif>m_spf)
	{
		int skip_frames = (int) round(dif / m_spf);
		t = _time;
		m_playingTexture += skip_frames;
		if(m_playingTexture > this->m_texPosList.size()-1) {
			m_playingTexture = 0;
		}
		
	}
	
	m_Render->bindTexture(m_texPosList[m_playingTexture]);
	
	// Apply the speed displacements
	m_Render->setModelMatrix();
	m_Render->pushMatrix();
	m_Render->translate(this->m_iniPosX + _time*this->m_speedX, this->m_iniPosY + _time*this->m_speedY, 0);
	
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
	m_Render->disableBlend();
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// restore view
	m_Render->orthoUnset();
	
	
}

void CResourceImageSequence::init() {
	// Request the loading of the textures
	int textureIndex;
	this->m_playingTexture = 0;
	
	if(this->m_texFilesList.size()>0) {
		unsigned int numFiles = m_texFilesList.size();
		unsigned int i;
		for(i=0; i<numFiles; i++) {
			textureIndex = m_Render->loadTexture(m_filesPath + m_texFilesList[i]);
			
			if(textureIndex>=0) {
				m_texPosList.push_back(textureIndex);
				
				
				// set the size of the texture to be the size of the first texture
				if(i==0) {
					this->m_texWidth = m_Render->getTextureWidth(textureIndex);
					this->m_texHeight = m_Render->getTextureHeight(textureIndex);
				}
				
			} else {
				cout << "Bad donut for " << m_texFilesList[i] << endl;
			}
		}
	}
}

void CResourceImageSequence::start() {
	
}

void CResourceImageSequence::deInit(void) {
	
}

string CResourceImageSequence::getType(void) {
	return "CResourceImageSequence";
}

void CResourceImageSequence::setParam(string name, string value) {
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
	if(name=="frame") {
		m_texFilesList.push_back(value);
	}
	if(name=="path") {
		m_filesPath = value;
	}
	if(name=="fps") {
		m_fps = (float) atof(value.c_str());
		if(m_fps!=0) {
			m_spf = 1.0f/m_fps;
		}
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
	if(name=="currentFrame") {
		m_playingTexture = (unsigned int) atoi(value.c_str());
	}
}

