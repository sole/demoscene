#include "ResourcePsychoFire.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "Render.h"

CResourcePsychoFire::CResourcePsychoFire(){
	m_numX = 10;
	m_numY = 10;
	m_numBase = 1;
}

void CResourcePsychoFire::play(float _time) {	
	float currentColor[4];
	float renderWidth = m_Render->getWidth();
	float renderHeight = m_Render->getHeight();
	float width= renderWidth*0.5, height = renderHeight*0.5;
	float quadincx = renderWidth / float(m_numX), quadincy= renderHeight/float(m_numY);
	float x, x2, y, y2;
	
	float xv[RESOURCEPSYCHOFIRE_MAX_X];
	float yv[RESOURCEPSYCHOFIRE_MAX_Y];
	unsigned int i,j, random;
	
	
	for(i=0; i < m_numX+1; i++) {
		xv[i] = -width + i*quadincx;
	}
	for(j=0; j < m_numY+1; j++) {
		yv[j] = -height + j*quadincy ;
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
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
	CPoint p;
	p.w*=this->m_alpha;
	m_Render->beginShapeQuads();
	
	// let's traverse by columns and then rows:
	/*
	 
	 .
	 .
	 .
	 ........... 2
	 ........... 1
	 
	 */
	j=0;
	for(i=0; i<m_numX; i++) {
		random = (3*float(rand())/(float)RAND_MAX);
		
		switch(random) {
			case 0:
				/*m_vColor[i][j].x=1;
				m_vColor[i][j].y=1;
				m_vColor[i][j].z=1;
				break;*/
			case 1:
				m_vColor[i][j].x=1;
				m_vColor[i][j].y=1;
				m_vColor[i][j].z=0;
				break;
			case 2:
				m_vColor[i][j].x=1;
				m_vColor[i][j].y=0;
				m_vColor[i][j].z=0;
				break;
		}
		//for(j=0; j<1; j++) {
			// now we change only the base line with random values
			// white, yellow or red
			// FFFFFF, FFFF00, FF0000
			/*if(i==0) {
				m_vColor[i][j] = m_vColor[i][j] + m_vColor[i+1][j];
				m_vColor[i][j] = m_vColor[i][j] * (0.5);
			} else if((i>0) && (i+1<m_numX)) {
				m_vColor[i][j] = m_vColor[i-1][j] + m_vColor[i][j] + m_vColor[i+1][j];
				m_vColor[i][j] = m_vColor[i][j] * (0.3333);
			}
			else {
				m_vColor[i][j] = m_vColor[i-1][j] + m_vColor[i][j];
				m_vColor[i][j] = m_vColor[i][j] * (0.5);
			*/	/*
				random = (3*float(rand())/(float)RAND_MAX);
				
				switch(random) {
					case 0:
						m_vColor[i][j].x=1;
						m_vColor[i][j].y=1;
						m_vColor[i][j].z=1;
						break;
					case 1:
						m_vColor[i][j].x=1;
						m_vColor[i][j].y=1;
						m_vColor[i][j].z=0;
						break;
					case 2:
						m_vColor[i][j].x=1;
						m_vColor[i][j].y=0;
						m_vColor[i][j].z=0;
						break;
				}*/
			/*}*/
		//m_vColor[i][j].y *=0.95;
		//m_vColor[i][j].z *=0.95;
		/*if(m_vColor[i][j].x + m_vColor[i][j].y + m_vColor[i][j].z < 2.2) {
			random = (3*float(rand())/(float)RAND_MAX);
			
			switch(random) {
				case 0:
					m_vColor[i][j].x=1;
					m_vColor[i][j].y=1;
					m_vColor[i][j].z=1;
					break;
				case 1:
					m_vColor[i][j].x=1;
					m_vColor[i][j].y=1;
					m_vColor[i][j].z=0;
					break;
				case 2:
					m_vColor[i][j].x=1;
					m_vColor[i][j].y=0;
					m_vColor[i][j].z=0;
					break;
			}
		}*/
		//}
	}
	// Update this point color...
	//    X
	//  X X X <-- based on these values
	float decay;
	static float t=0;
	if(_time-t>0.05) {
		for(j=1; j<m_numY; j++) {
			/*decay = 1-float(j)/float(m_numY);
			if(decay < 0.8) {
				decay = 0.8;
			}*/
			decay=1;
			for(i=0; i<m_numX; i++) {
				random = (0.2*float(rand())/(float)RAND_MAX);
				if((i>0) && (i+1<m_numX)) { 
					m_vColor[i][j] = (m_vColor[i-1][j-1] + m_vColor[i][j-1] + m_vColor[i+1][j-1] + random) ;
					m_vColor[i][j] = m_vColor[i][j] * (1.0/4) * decay;
				} else if(i==0) {
					m_vColor[i][j] = ( m_vColor[i][j-1] + m_vColor[i+1][j-1] + random) ;
					m_vColor[i][j] = m_vColor[i][j] * (1.0/3) * decay;
				} else {
					m_vColor[i][j] = (m_vColor[i-1][j-1] + m_vColor[i][j-1] + random) ;
					m_vColor[i][j] = m_vColor[i][j] * (1.0/3) * decay;
				}
				/*if(decay>0.98)
					m_vColor[i][j].z=decay;
				*//*m_vColor[i][j].x = ( m_vColor[i-1][j-1].x + m_vColor[i][j-1].x + m_vColor[i+1][j-1].x) / 3;
				m_vColor[i][j].y = ( m_vColor[i-1][j-1].y + m_vColor[i][j-1].y + m_vColor[i+1][j-1].y) / 3;
				m_vColor[i][j].x = ( m_vColor[i-1][j-1].x + m_vColor[i][j-1].x + m_vColor[i+1][j-1].x) / 3;*/
			}
		}
		t=_time;
	}
	for(j=0; j<m_numY; j++) {
		y = yv[j];
		y2 = yv[j+1];
		
		
		for(i=0; i<m_numX; i++) {
			
			if(m_vColor[i][j].x < 0.1 && m_vColor[i][j].y < 0.1 && m_vColor[i][j].z < 0.1)
				continue;
			x = xv[i];
			x2 = xv[i+1];
			
			m_vColor[i][j].z = p.z;
			
			m_Render->setColor(this->m_vColor[i][j]);
			
			//m_Render->setTextureCoord(tx,ty);
			m_Render->addVertex(x,y);
			
			//m_Render->setTextureCoord(tx,ty2);
			m_Render->addVertex(x,y2);

			if(i+1<m_numX) {
				m_vColor[i+1][j].z = p.z;
				m_Render->setColor(this->m_vColor[i+1][j]);
			}
			//m_Render->setTextureCoord(tx2, ty2);
			m_Render->addVertex(x2, y2);

			
			//m_Render->setTextureCoord(tx2,ty);
			m_Render->addVertex(x2,y);
			
			
						
		}
		
	}

	m_Render->endShape();
	
	// disable transparency
	m_Render->disableBlend();
	
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	// restore view
	m_Render->orthoUnset();
}

void CResourcePsychoFire::init() {
	// init the color array
	unsigned int i, j, random;
	this->m_vColor = new CPoint*[m_numX];
	for(i=0; i<m_numX; i++) {
		m_vColor[i] = new CPoint[m_numY];
	}
	for(i=0; i<m_numX; i++) {
		for(j=0; j<m_numBase; j++) {
			// init the base lines with random values
			// white, yellow or red
			// FFFFFF, FFFF00, FF0000
			random = (3*float(rand())/(float)RAND_MAX);
			
			switch(random) {
				case 0:
					m_vColor[i][j].x=1;
					m_vColor[i][j].y=1;
					m_vColor[i][j].z=1;
					break;
				case 1:
					m_vColor[i][j].x=1;
					m_vColor[i][j].y=1;
					m_vColor[i][j].z=0;
					break;
				case 2:
					m_vColor[i][j].x=1;
					m_vColor[i][j].y=0;
					m_vColor[i][j].z=0;
					break;
			}
		}
	}
	
}

void CResourcePsychoFire::start() {
	
}

void CResourcePsychoFire::deInit(void) {
	//delete []m_vColor;
}

string CResourcePsychoFire::getType(void) {
	return "CResourcePsychoFire";
}

/*
 int CResourcePsychoFire::setAttribute(string name, string value) {
	 
	 return 0;
 }*/

/*int CResourcePsychoFire::setAttribute(string name, float value) {
return 0;
}*/

/*
 int CResourcePsychoFire::setParam(string name, float value) {
	 return 0;
 }*/
void CResourcePsychoFire::setParam(string name, string value) {
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
	if(name=="num_base") {
		m_numBase = (unsigned int) atoi(value.c_str());
	}
	if(name=="num_x") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numX = (tmp < RESOURCEPSYCHOFIRE_MAX_X-1 ? tmp : RESOURCEPSYCHOFIRE_MAX_X);
	}
	if(name=="num_y") {
		unsigned int tmp = (unsigned int) atoi(value.c_str());
		this->m_numY = (tmp < RESOURCEPSYCHOFIRE_MAX_Y-1 ? tmp : RESOURCEPSYCHOFIRE_MAX_Y);
	}
}
/*
 int CResourcePsychoFire::parseAttributes(TiXmlElement* node) {
	 return 0;
 }*/