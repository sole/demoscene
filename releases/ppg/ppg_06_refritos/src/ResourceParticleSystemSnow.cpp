#include "ResourceParticleSystemSnow.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "Render.h"

CResourceParticleSystemSnow::CResourceParticleSystemSnow(){
	m_numParticles = 200;
	m_origin1.x=-10;
	m_origin1.y=100;
	m_origin1.z=-10;
	
	m_origin2.x=10;
	m_origin2.y=100;
	m_origin2.z=10;
	
	m_gravity.y=-0.03f;
	
	m_fadeout = 0.1;
	this->m_hasCustomBlending = false;
	
	
	
	this->m_hasTexture = false;
	this->m_maxSize = 1;
}

inline void CResourceParticleSystemSnow::initParticle(CPoint *p) {
	float marginx, marginy, marginz;
	static float invrandmax = 1.0/RAND_MAX;
	marginx = abs(m_origin2.x - m_origin1.x);
	marginy = abs(m_origin2.y - m_origin1.y);
	marginz = abs(m_origin2.z - m_origin1.z);
	
	p->x = m_origin1.x + rand()*invrandmax*marginx;
	p->y = m_origin1.y + rand()*invrandmax*marginy;
	p->z = m_origin1.z + rand()*invrandmax*marginz;
	
	p->w = rand()*invrandmax*m_maxSize;
}

inline void CResourceParticleSystemSnow::drawParticle(float x2, float y2, float z2, float dens, CPoint vup, CPoint vright) {
	CMatrix mtx_modelview;
	
	m_Render->setModelMatrix();
	m_Render->pushMatrix();
	
	// calculate position of each vertex given the up and right vectors (So they will face the right place)
	CPoint P1, P2;
	
	// Draw the particle...
	/*
	 4  3 
	 1  2
	 */
	
	
	CPoint c(x2,y2,z2);
	
	
	m_Render->beginShapeQuads();
	
	m_Render->setTextureCoord(0,0);
	m_Render->addVertex(c);
	
	m_Render->setTextureCoord(1.0f, 0.0f);
	m_Render->addVertex(c+vright*dens);
	
	m_Render->setTextureCoord(1.0f, 1.0f);
	m_Render->addVertex((c+vright*dens)+vup*dens);
	
	m_Render->setTextureCoord(0.0f, 1.0f);
	m_Render->addVertex(c+vup*dens);
	
	m_Render->endShape();
	
	// Restores the modelview matrix
	m_Render->setModelMatrix();
	m_Render->popMatrix();	
}

void CResourceParticleSystemSnow::play(float _time) {	
	float currentColor[4];
	static float t0=0;
	
	// deactivate the depth mask! 
	m_Render->disableDepthMask();
	
	// set transparency
	m_Render->enableBlend();
	
	// if the texture is loaded, activate it
	if(this->m_hasTexture) {
		m_Render->enableTexture();
		m_Render->bindTexture(m_texPos);
	}
	
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
	
	
	this->m_vup = this->m_Render->getActiveCamera()->getUp().normalize();
	this->m_vright = this->m_Render->getActiveCamera()->getRight().normalize();
	
	// get current rendering color (for restoring it after)
	m_Render->getCurrentColor(currentColor);
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	
	// set the current vertex color
	m_Render->setColor(currColor);
	
	// draw & update
	unsigned int i;
	float t_elapsed = _time - t0;
	float scaler;
	CPoint vup, vright;
	
	for(i=0; i<m_numParticles;i++) {
		
		vup = this->m_vup;
		vright = this->m_vright;
		drawParticle(m_particlesList[i].x, m_particlesList[i].y, m_particlesList[i].z, m_particlesList[i].w*m_maxSize, vup, vright);
		// decrease the remaining amount of life of this particle
		m_particlesList[i].w -= t_elapsed*m_fadeout;
		if(m_particlesList[i].w <=0 ) {
			initParticle(&m_particlesList[i]);
		}
		// apply gravity
		m_particlesList[i].x+= t_elapsed * m_gravity.x;
		m_particlesList[i].y+= t_elapsed * m_gravity.y;
		m_particlesList[i].z+= t_elapsed * m_gravity.z;
	}
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// Disable blending and reenable zbuffer writing
	m_Render->disableBlend();
	m_Render->enableDepthMask();
	
	// if the texture is loaded, deactivate it
	if(this->m_hasTexture) {
		m_Render->disableTexture();
	}
	
	// And update the time
	t0 = _time;
}

void CResourceParticleSystemSnow::init() {
	int textureIndex;
	
	if(m_hasTexture) {
		textureIndex = m_Render->loadTexture(this->m_TextureFile);
		if(textureIndex>=0) {
			m_texPos = textureIndex;
		} else {
			m_hasTexture = false;
		}
	}
	
	// Init the particles m_particlesList
	unsigned int i;
	for(i=0; i<m_numParticles; i++) {
		CPoint p;
		initParticle(&p);
		m_particlesList.push_back(p);
	}
}

void CResourceParticleSystemSnow::start() {
	
}

void CResourceParticleSystemSnow::deInit(void) {
	
}

string CResourceParticleSystemSnow::getType(void) {
	return "CResourceParticleSystemSnow";
}

void CResourceParticleSystemSnow::setParam(string name, string value) {
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
	
	if(name=="num_particles") {
		unsigned int tmp_num = (unsigned int) atoi(value.c_str());
		// if more particles than current ones are requested, allocate extra particles
		if(m_numParticles<tmp_num) {
			unsigned int i;
			for(i=m_numParticles; i<=tmp_num; i++) {
				CPoint p;
				initParticle(&p);
				m_particlesList.push_back(p);
			}
		}
		m_numParticles = tmp_num;
	}
	
	if(name=="origin1_x") {
		m_origin1.x = (float) atof(value.c_str());
	}
	if(name=="origin1_y") {
		m_origin1.y = (float) atof(value.c_str());
	}
	if(name=="origin1_z") {
		m_origin1.z = (float) atof(value.c_str());
	}
	if(name=="origin1_w") {
		m_origin1.w = (float) atof(value.c_str());
	}
	
	if(name=="origin2_x") {
		m_origin2.x = (float) atof(value.c_str());
	}
	if(name=="origin2_y") {
		m_origin2.y = (float) atof(value.c_str());
	}
	if(name=="origin2_z") {
		m_origin2.z = (float) atof(value.c_str());
	}
	if(name=="origin2_w") {
		m_origin2.w = (float) atof(value.c_str());
	}
	
	if(name=="gravity_x") {
		m_gravity.x = (float) atof(value.c_str());
	}
	if(name=="gravity_y") {
		m_gravity.y = (float) atof(value.c_str());
	}
	if(name=="gravity_z") {
		m_gravity.z = (float) atof(value.c_str());
	}
	if(name=="gravity_w") {
		m_gravity.w = (float) atof(value.c_str());
	}
	
	if(name=="fadeout") {
		m_fadeout = (float) atof(value.c_str());
	}
	
	if(name=="up_x") {
		m_vup.x = (float) atof(value.c_str());
	}
	if(name=="up_y") {
		m_vup.y = (float) atof(value.c_str());
	}
	if(name=="up_z") {
		m_vup.z = (float) atof(value.c_str());
	}
	
	if(name=="right_x") {
		m_vright.x = (float) atof(value.c_str());
	}
	if(name=="right_y") {
		m_vright.y = (float) atof(value.c_str());
	}
	if(name=="right_z") {
		m_vright.z = (float) atof(value.c_str());
	}
	
	if(name=="max_size") {
		m_maxSize = (float) atof(value.c_str());
	}
	
	if(name=="blending") {
		this->m_hasCustomBlending = true;
		this->m_renderBlendingPos = this->m_Render->getBlending(value);
	}
	
	if(name=="src") {
		m_TextureFile = value;
		m_hasTexture = true;
	}
}
