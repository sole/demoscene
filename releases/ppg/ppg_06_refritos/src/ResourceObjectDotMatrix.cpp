#include "ResourceObjectDotMatrix.h"
#include "Render.h" 
#include <iostream>
CResourceObjectDotMatrix::CResourceObjectDotMatrix() {
	m_charWidth = 8;
	m_charHeight = 8;
	m_textureFile = "";
}

void CResourceObjectDotMatrix::play(float _time) {	
	this->m_Render->clear(RENDER_CLEAR_COLOR);
}

void CResourceObjectDotMatrix::init() {
	/*//cout << " loading " << m_textureFile << endl;
	// Esto es una cerdada pero no me apetece hacer una funcion puente entre CRender y esto
	// alamierda!! XD
	GLFWimage theImage;
	glfwReadImage(m_textureFile.c_str(), &theImage, GLFW_NO_RESCALE_BIT | GLFW_ORIGIN_UL_BIT );
	//cout << "img width: " << theImage.Width << endl;
	//cout << "img heighth: " << theImage.Height << endl;
	//cout << "bytes per pixel: " << theImage.BytesPerPixel << endl;
	unsigned int i, j, k;
	for(i=0;i<theImage.Width;i++) {
		for(j=0;j<theImage.Height;j++) {
			for(k=0;k<theImage.BytesPerPixel;k++){
				cout << (unsigned int)(theImage.Data[i+j*theImage.Height+k]) << " ";
			}
			//cout <<"|";
		}
		//cout << endl;
	}*///TODO
}

void CResourceObjectDotMatrix::start() {
	
}

void CResourceObjectDotMatrix::deInit(void) {
	
}

string CResourceObjectDotMatrix::getType(void) {
	return "CResourceObjectDotMatrix";
}

void CResourceObjectDotMatrix::setParam(string name, string value) {
	if(name=="char_height") {
		this->m_charHeight = (unsigned int) atoi(value.c_str());
	}
	if(name=="char_width") {
		this->m_charWidth = (unsigned int) atoi(value.c_str());
	}
	if(name=="src") {
		this->m_textureFile = value;
	}
}
