// 26 feb 2005
#ifndef __LIGHTOBJECT__
#define __LIGHTOBJECT__

#include "math3D.h"
#include <string.h>
#include "my_opengl.h"

class LightObject {
public:
	LightObject(void);
	~LightObject();

	void setInheritPos(float x, float y, float z);
	void setInheritRot(float x, float y, float z);
	void setInheritScl(float x, float y, float z);
	void setTransformMatrix(float a, float b, float c, 
						   float d, float e, float f,
						   float g, float h, float i,
						   float j, float k, float l);
	void setTMPos(float x, float y, float z);
	void setTMRotAxis(float x, float y, float z);
	void setTMRotAngle(float ang);
	void setTMScale(float x, float y, float z);
	void setTMScaleAxis(float x, float y, float z);
	void setTMScaleAxisAng(float ang);
	
	void setLightIntensity(float val);
	void setColorAmbient(float x, float y, float z, float w);
	void setColorDiffuse(float x, float y, float z, float w);
	void setColorSpecular(float x, float y, float z, float w);

		
	// Drawing
	void draw(GLuint index);

private:
	char m_nodeName[255];

	// Transform Matrix
	Point m_inheritPos;
	Point m_inheritRot;
	Point m_inheritScl;
	Point m_transformMatrix[4]; // 4 rows of points to store the transformation matrix
	Point m_tm_Pos;
	Point m_tm_rotAxis;
	float m_tm_rotAngle;
	Point m_tm_scale;
	Point m_tm_ScaleAxis;
	float m_tm_scaleAxisAng;

	// Light things
	float m_light_intensity;
	Point m_color_ambient;
	Point m_color_diffuse;
	Point m_color_specular;

	// TODO: SPot lights..
};

#endif
