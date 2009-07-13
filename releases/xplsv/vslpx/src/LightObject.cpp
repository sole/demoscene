// 26 feb 2004
#include "LightObject.h"

LightObject::LightObject(void) {
	this->m_inheritPos.x=0;
	this->m_inheritPos.y=0;
	this->m_inheritPos.z=0;
	this->m_inheritPos.w=0;

	this->m_inheritRot.x=0;
	this->m_inheritRot.y=0;
	this->m_inheritRot.z=0;
	this->m_inheritRot.w=0;

	this->m_inheritScl.x=1;
	this->m_inheritScl.y=1;
	this->m_inheritScl.z=1;
	this->m_inheritScl.w=1;

	this->m_tm_Pos.x=0;
	this->m_tm_Pos.y=0;
	this->m_tm_Pos.z=0;
	this->m_tm_Pos.w=0;

	this->m_tm_rotAngle=0;

	this->m_tm_rotAxis.x=0;
	this->m_tm_rotAxis.y=0;
	this->m_tm_rotAxis.z=0;
	this->m_tm_rotAxis.w=0;

	this->m_tm_scale.x=0;
	this->m_tm_scale.y=0;
	this->m_tm_scale.z=0;
	this->m_tm_scale.w=0;

	this->m_tm_ScaleAxis.x=0;
	this->m_tm_ScaleAxis.y=0;
	this->m_tm_ScaleAxis.z=0;
	this->m_tm_ScaleAxis.w=0;

	this->m_tm_scaleAxisAng=0;

	this->m_transformMatrix[0].x=1;
	this->m_transformMatrix[0].y=0;
	this->m_transformMatrix[0].z=0;
	this->m_transformMatrix[0].w=0;

	this->m_transformMatrix[1].x=0;
	this->m_transformMatrix[1].y=0;
	this->m_transformMatrix[1].z=1;
	this->m_transformMatrix[1].w=0;

	this->m_transformMatrix[2].x=0;
	this->m_transformMatrix[2].y=-1;
	this->m_transformMatrix[2].z=0;
	this->m_transformMatrix[2].w=0;

	this->m_transformMatrix[3].x=0;
	this->m_transformMatrix[3].y=0;
	this->m_transformMatrix[3].z=0;
	this->m_transformMatrix[3].w=0;

	strcpy(this->m_nodeName,"");

	// Light things, default values
	this->m_light_intensity=1.0;
	this->m_color_ambient.x=0;
	this->m_color_ambient.y=0;
	this->m_color_ambient.z=0;
	this->m_color_ambient.w=1;

	this->m_color_diffuse.x=1;
	this->m_color_diffuse.y=1;
	this->m_color_diffuse.z=1;
	this->m_color_diffuse.w=1;

	this->m_color_specular.x=0;
	this->m_color_specular.y=0;
	this->m_color_specular.z=0;
	this->m_color_specular.w=1;

}

LightObject::~LightObject() {
	// TODO: free allocated memory
}

void LightObject::setInheritPos(float x, float y, float z) {
	this->m_inheritPos.x=x;
	this->m_inheritPos.y=y;
	this->m_inheritPos.z=z;
}

void LightObject::setInheritRot(float x, float y, float z) {
	this->m_inheritRot.x=x;
	this->m_inheritRot.y=y;
	this->m_inheritRot.z=z;
}
	
void LightObject::setInheritScl(float x, float y, float z) {
	this->m_inheritScl.x=x;
	this->m_inheritScl.y=y;
	this->m_inheritScl.z=z;
}

void LightObject::setTransformMatrix(float a, float b, float c,
						   float d, float e, float f,
						   float g, float h, float i,
						   float j, float k, float l) {

	this->m_transformMatrix[0].x=a;
	this->m_transformMatrix[0].y=b;
	this->m_transformMatrix[0].z=c;

	this->m_transformMatrix[1].x=d;
	this->m_transformMatrix[1].y=e;
	this->m_transformMatrix[1].z=f;

	this->m_transformMatrix[2].x=g;
	this->m_transformMatrix[2].y=h;
	this->m_transformMatrix[2].z=i;

	this->m_transformMatrix[3].x=j;
	this->m_transformMatrix[3].y=k;
	this->m_transformMatrix[3].z=l;
}

void LightObject::setTMPos(float x, float y, float z) {
	this->m_tm_Pos.x=x;
	this->m_tm_Pos.y=y;
	this->m_tm_Pos.z=z;

}

void LightObject::setTMRotAxis(float x, float y, float z) {
	this->m_tm_rotAxis.x=x;
	this->m_tm_rotAxis.y=y;
	this->m_tm_rotAxis.z=z;
}

void LightObject::setTMRotAngle(float ang) {
	this->m_tm_rotAngle=ang;
}

void LightObject::setTMScale(float x, float y, float z) {
	this->m_tm_scale.x=x;
	this->m_tm_scale.y=y;
	this->m_tm_scale.z=z;
}

void LightObject::setTMScaleAxis(float x, float y, float z){
	this->m_tm_ScaleAxis.x=x;
	this->m_tm_ScaleAxis.y=y;
	this->m_tm_ScaleAxis.z=z;
}
void LightObject::setTMScaleAxisAng(float ang) {
	this->m_tm_scaleAxisAng=ang;
}

/*
	// Light things
	float m_light_intensity;
	Point m_color_ambient;
	Point m_color_diffuse;
	Point m_color_specular;
	Point m_position;
*/
void LightObject::setLightIntensity(float val) {
	this->m_light_intensity=val;
}
void LightObject::setColorAmbient(float x, float y, float z, float w) {
	this->m_color_ambient.x=x;
	this->m_color_ambient.y=y;
	this->m_color_ambient.z=z;
	this->m_color_ambient.w=w;
}
void LightObject::setColorDiffuse(float x, float y, float z, float w) {
	this->m_color_diffuse.x=x;
	this->m_color_diffuse.y=y;
	this->m_color_diffuse.z=z;
	this->m_color_diffuse.w=w;
}
void LightObject::setColorSpecular(float x, float y, float z, float w) {
	this->m_color_specular.x=x;
	this->m_color_specular.y=y;
	this->m_color_specular.z=z;
	this->m_color_specular.w=w;
}



// Drawing
void LightObject::draw(GLuint index) {
	
	//TODO: apply transformations only when needed
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	

	// Scale
	glScalef(this->m_tm_scale.x,this->m_tm_scale.y,this->m_tm_scale.z);
	// Rotate
	glRotatef(this->m_tm_rotAngle, this->m_tm_rotAxis.x, this->m_tm_rotAxis.y, this->m_tm_rotAxis.z);
	// Translate
	glTranslatef(this->m_tm_Pos.x, this->m_tm_Pos.y, this->m_tm_Pos.z);

	#ifdef _DEBUG
	float length = 15;
	glLineWidth(5.0f);
	glColor3f(1.0f,0.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(length,0.0f,0.0f); // X
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(-length,0.0f,0.0f); // X neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.0f,1.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,length,0.0f); // y
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,-length,0.0f); // y neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.0f,0.0,1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,length); // z
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,-length); // z neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0f);
#endif

	// apply light params
	GLfloat diffuseColor[4] = { this->m_color_diffuse.x * this->m_light_intensity, 
		this->m_color_diffuse.y * this->m_light_intensity, 
		this->m_color_diffuse.z * this->m_light_intensity, 
		this->m_color_diffuse.w * this->m_light_intensity
	};
	glLightfv(index, GL_DIFFUSE, diffuseColor);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


