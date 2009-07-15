#include "ResourceObjectTerrain.h"
#include <iostream>
#include <cmath>
using namespace std;
#include "Render.h"

CResourceObjectTerrain::CResourceObjectTerrain(){
	
	m_width = 0 ;
	m_height = 0;
	m_totalPixels = 0;
	m_step=1;
	m_offset_x =0;
	m_offset_y =0;
	m_prismWidth = 1;
	m_prismHeight = 10;
	m_draw_max_x = 0;
	m_draw_max_y = 0;
	
	m_origin1.x=-100;
	m_origin1.y=10;
	m_origin1.z=-100;
	
	m_origin2.x=100;
	m_origin2.y=0;
	m_origin2.z=100;
	
	m_scale.x=1;
	m_scale.y=1;
	m_scale.z=1;
	
	m_translateX = true;
	m_translateY = true;
	
	this->m_hasCustomBlending = false;
	this->m_hasTexture = false;
}

void CResourceObjectTerrain::play(float _time) {	
	float currentColor[4];
	
	// deactivate the depth mask! 
	//m_Render->disableDepthMask();
	
	// set transparency
	//m_Render->enableBlend();
	
	
	
	// Apply the blending (if appropiate)
	if(m_hasCustomBlending) {
		m_Render->blendFunc(this->m_renderBlendingPos);
	}
	
	// get current rendering color (for restoring it after)
	m_Render->getCurrentColor(currentColor);
	// Apply the calculated alpha to our plane color (this alpha is set outside by an "Effect")
	CPoint currColor = this->m_Color;
	currColor.w*=this->m_alpha;
	//cout << currColor.w << endl;
	// set the current vertex color
	m_Render->setColor(currColor);
	
	// draw
	m_Render->setModelMatrix();
	m_Render->pushMatrix();
	//m_Render->loadIdentity();
	
	//m_Render->translate(-this->m_width*0.5f, 0, -this->m_height*0.5f); 
	/*m_Render->setProjectionMatrix();
	m_Render->pushMatrix();
	CCamera miCam;
	miCam.SetFar(1,10000);
	miCam.Place(CPoint(100,200,100), CPoint(100,0,0), CPoint (0,1,0));
	miCam.toOGL();
	*/
	//m_Render->orthoSet();
	/*m_Render->auxAxis();
				
	m_Render->setLineWidth(2);
	glPointSize(4);	*/
	
	/*
	m_Render->setColor(1,0,1,1);
	m_Render->beginShapeLines();
	m_Render->addVertex(0,0,0);
	m_Render->addVertex(100,100,0);
	m_Render->endShape();*/

	/*static float t=0;
	if(_time-t > 0.04) {
		t=_time;
		m_offset_y++;
	}*/
	unsigned int x,y, X,Y, z;
	CPoint p1, p2;
	
	float max_drawn_width = (m_draw_max_x!=0 ? m_draw_max_x : m_width) - m_step;
	float max_drawn_height = (m_draw_max_y!=0 ? m_draw_max_y : m_height) -m_step;
	
	// Center the object in 0,0... or something like that :D
	float tx, tz;
	if(m_translateX) {
		tx = -max_drawn_width*0.5*m_scale.x;
	} else {
		tx = false;
	}
	if(m_translateY) {
		tz = -max_drawn_height*0.5*m_scale.z;
	} else {
		tz = false;
	}
	m_Render->translate(tx, 0, tz);
	for ( X = 0; X < max_drawn_width ; X += m_step )
		for ( Y = 0; Y < max_drawn_height; Y += m_step )
		{
			x = X;							
			y = Height( X+m_offset_x, Y+m_offset_y );	
			z = Y;
			
			if(y!=0) {
				// Set The Color Value Of The Current Vertex
				CPoint c = this->m_Color;
				c = c*(1.0*y/255.0);
				c.w = 1.0;
				
				//m_Render->setColor(c);
				p1.x= x*m_scale.x;
				p1.y= y;
				p1.z=z*m_scale.z;
				float dif = this->m_prismWidth;
				p2.x=p1.x+dif;
				p2.y=p1.y-this->m_prismHeight;
				p2.z=p1.z-dif;				
				
				// Check if the particle is BEHIND the camera ... then do not draw it!
				// TODO well not by the moment.. it is very buggy yet :-(
				//if(this->m_Render->getActiveCamera()->inFrustrum(p1)) {
					
				drawPrism(p1,p2);
				//}
				/*m_Render->beginShapePoints();
				m_Render->addVertex(x*m_scale.x,y,z*m_scale.z); 
				m_Render->endShape();*/
			
			}
		}
	
	
	
	/*m_Render->setProjectionMatrix();
	m_Render->popMatrix();*/
	
	m_Render->setModelMatrix();
	m_Render->popMatrix();
	// restore color
	m_Render->setColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	
	
	// Disable blending
	//m_Render->disableBlend();
	
	
	
}

void CResourceObjectTerrain::init() {
	int textureIndex;
	
	if(m_hasTexture) {
		// cout << "Loading ObjectTerrain with " << this->m_totalPixels << " pixels "<< endl;
		// initialize the space for the heightmap data
		this->m_heightMapData = new unsigned char [this->m_totalPixels];
		
		// and now let's load it
		FILE *pFile = NULL;
		
		// Open The File In Read / Binary Mode.
		pFile = fopen( m_TextureFile.c_str(), "rb" );
		
		// Check To See If We Found The File And Could Open It
		if ( pFile == NULL ) {
			return;
		}
		
		fread( m_heightMapData, 1, this->m_totalPixels, pFile );
		
		// After We Read The Data, It's A Good Idea To Check If Everything Read Fine
		int result = ferror( pFile );
		
		// Check If We Received An Error
		if (result) {
			cout << "CResourceObjectTerrain - error - can't load data" << endl;
		}
		
		// Close The File.
		fclose(pFile);
		
	}
	
	}

void CResourceObjectTerrain::start() {
	
}

void CResourceObjectTerrain::deInit(void) {
	delete(this->m_heightMapData);
}

string CResourceObjectTerrain::getType(void) {
	return "CResourceObjectTerrain";
}

void CResourceObjectTerrain::setParam(string name, string value) {
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
	
	if(name=="draw_max_x") {
		m_draw_max_x = (unsigned int) atoi(value.c_str());
	}
	if(name=="draw_max_y") {
		m_draw_max_y = (unsigned int) atoi(value.c_str());
	}
	if(name=="num_points_y") {
		m_width = (unsigned int) atoi(value.c_str());
		m_totalPixels = m_width * m_height;
	}
	if(name=="num_points_x") {
		m_height = (unsigned int) atoi(value.c_str());
		m_totalPixels = m_width * m_height;
	}
	if(name=="offset_x") {
		m_offset_x = (unsigned int) atoi(value.c_str());
	}
	if(name=="offset_y") {
		m_offset_y = (unsigned int) atoi(value.c_str());
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
	if(name=="prism_height") {
		m_prismHeight = (float) atof(value.c_str());
	}
	if(name=="prism_width") {
		m_prismWidth = (float) atof(value.c_str());
	}
	if(name=="scale_x") {
		m_scale.x = (float) atof(value.c_str());
	}
	if(name=="scale_y") {
		m_scale.y = (float) atof(value.c_str());
	}
	if(name=="scale_z") {
		m_scale.z = (float) atof(value.c_str());
	}
	if(name=="step") {
		m_step = (unsigned int) atoi(value.c_str());
	}
	if(name=="translate_x") {
		m_translateX = value=="yes" ? true : false;
	}
	if(name=="translate_y") {
		m_translateY = value=="yes" ? true : false;
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

int CResourceObjectTerrain::Height(int x, int y) {
	int _x = x % m_width; 								// Error Check Our x Value
	int _y = y % m_height;								// Error Check Our y Value
	
	return this->m_heightMapData[_x + (_y * m_width)];
	
	/*int _x, _y;
	
	if(x>this->m_width || y>this->m_height) {
		return 0;
	} else {
		_x = x;
		_y = y;
	return this->m_heightMapData[_x + (_y * m_width)]; // o m_height?				// Index Into Our Height Array And Return The Height
	}*/
}

void CResourceObjectTerrain::drawPrism(CPoint p1, CPoint p2) {
	/*float width = p2.x - p1.x;
	float height = p1.y - p2.y;
	float depth = p1.z - p2.z;*/
	CPoint v1,v2, nor;
	m_Render->beginShapeQuads();
	
	// top "cap"
	
	v2.x=p2.x; v2.y =p1.y; v2.z = p1.z;
	nor = (v1^v2).normalize().negate();
	m_Render->normal(nor.x,nor.y, nor.z); // pointing upwards
	m_Render->addVertex(p1);
	m_Render->addVertex(p1.x, p1.y, p2.z);
	m_Render->addVertex(p2.x,p1.y,p2.z);
	m_Render->addVertex(p2.x,p1.y, p1.z);
	
	// below "cap"
	// This normal is the opposite of the top one
	nor = nor.negate();
	m_Render->normal(nor.x, nor.y, nor.z); // pointing downwards
	m_Render->addVertex(p2);
	m_Render->addVertex(p2.x,p2.y,p1.z);
	m_Render->addVertex(p1.x,p2.y,p1.z);
	m_Render->addVertex(p1.x,p2.y,p2.z);
	
	
	// left face
	v1.x=p1.x; v1.y =p1.y; v1.z = p2.z;
	v2.x=p1.x; v2.y=p2.y; v2.z=p2.x;
	nor = v1^v2;
	m_Render->normal(nor.x, nor.y, nor.z); // pointing leftwards
	m_Render->addVertex(p1);
	m_Render->addVertex(p1.x, p2.y, p1.z);
	m_Render->addVertex(p1.x, p2.y, p2.z);
	m_Render->addVertex(p1.x, p1.y, p2.z);
	
	// right face
	nor = nor.negate();
	m_Render->normal(nor.x, nor.y, nor.z); // opposite of left one!
	m_Render->addVertex(p2);
	m_Render->addVertex(p2.x, p2.y, p1.z);
	m_Render->addVertex(p2.x, p1.y, p1.z);
	m_Render->addVertex(p2.x, p1.y, p2.z);
	
	
	// bottom face
	v1.x = p1.x; v1.y = p2.y; v1.z = p2.z;
	v2.x = p2.x; v2.y = p1.y; v2.z = p2.z;
	nor = v1 ^ v2;
	m_Render->normal(nor.x, nor.y, nor.z); // pointing to Z+
	m_Render->addVertex(p2);
	m_Render->addVertex(p2.x, p1.y, p2.z);
	m_Render->addVertex(p1.x, p1.y, p2.z);
	m_Render->addVertex(p1.x, p2.y, p2.z);
	
	// top face
	nor = nor.negate();
	m_Render->normal(nor.x, nor.y, nor.z); // opposite of bottom one, pointing to Z-
	m_Render->addVertex(p1);
	m_Render->addVertex(p1.x, p2.y, p1.z);
	m_Render->addVertex(p2.x, p2.y, p1.z);
	m_Render->addVertex(p2.x, p1.y, p1.z);
	
	
	m_Render->endShape();
}