#include "Camera.h"
#define CAMERA_CORRECTION 0.0001
#include <iostream>
#include "my_opengl.h"

using namespace std;
CCamera::CCamera() {
	// init with opengl standard values
	this->m_vposition = CPoint(0,0,0);
	this->m_vlook = CPoint(0,0,-1);
	this->m_vright = CPoint(1,0,0);
	this->m_vup = CPoint(0,1,0);
	
	this->fov=45.0f;
	this->zNear=1.0f;
	this->zFar=60.0f;
	this->aspect=1.3f;

	this->recalc();
}

void CCamera::Place(CPoint position, CPoint targetPosition, CPoint upVector) {
	
	CPoint view = targetPosition - position;
	
	this->m_vright = view ^ upVector;
	this->m_vup = upVector;
	this->m_vlook = view;
	this->m_vposition = position;
	
	this->isReady=1;
}

void CCamera::MoveForward(float distance) {
	this->m_vposition = this->m_vposition + this->m_vlook * (-distance);
}

void CCamera::StrafeRight(float distance) {
	this->m_vposition = this->m_vposition + this->m_vright*distance;
}

void CCamera::MoveUpward(float distance) {
	this->m_vposition = this->m_vposition + this->m_vup*distance;
}

void CCamera::SetPos(float _x,float _y, float _z) {
	
	float xdesp = _x - this->m_vposition.x;
	float ydesp = _y - this->m_vposition.y;
	float zdesp = _z - this->m_vposition.z;
	
	// x desp
	this->StrafeRight(xdesp);
	// y desp
	this->MoveUpward(ydesp);
	// z desp
	this->MoveForward(zdesp);
	
	this->isReady=0;
}

// Rotates in the camera's X axis  
void CCamera::rotateX(float degrees) {
	CTransformation Tlook, Tup;
	
	Tlook.rotateX(degrees);
	this->m_vlook = Tlook*this->m_vlook;
	
	this->m_vup = (this->m_vright^this->m_vlook).normalize();
	this->isReady=1;
}

// Rotates in the camera's Y axis --> then UP is not altered but the other vectors are: LOOK and RIGHT 
void CCamera::rotateY(float degrees) {
	CTransformation Tlook, Tright;
	
	Tlook.rotateY(degrees);
	this->m_vlook = Tlook*this->m_vlook;
	this->m_vright = (this->m_vlook^this->m_vup).normalize();
}

// Rotates in the camera's Z axis 
void CCamera::rotateZ(float degrees) {
	CTransformation Tup;
	
	Tup.rotateZ(degrees);
	this->m_vup = Tup*this->m_vup;
	
	this->m_vright = (this->m_vlook^this->m_vup).normalize();
	this->isReady=1;
}

void CCamera::SetPos(CPoint _position) {
	this->SetPos(_position.x, _position.y, _position.z);
}

void CCamera::SetLook(float _x,float _y, float _z) {
	this->m_vlook = CPoint(_x, _y, _z) - this->m_vposition;
	this->isReady=0;
}

void CCamera::SetFov(float _fov) {
	if(_fov>0) {
		this->fov=_fov;
		this->isReady=0;
	}
}

float CCamera::GetFov(void) {
	return this->fov;
}

CPoint CCamera::getUp() {
	return this->m_vup;
}

CPoint CCamera::getRight() {
	return this->m_vright;
}

CPoint CCamera::getTarget() {
	return this->m_vlook;
}

void CCamera::SetFar(float nearz,float farz) {
	this->zFar=farz;
	this->zNear=nearz;
	this->isReady=0;
}

void CCamera::recalc(void) {

	this->m_vright = this->m_vlook ^ this->m_vup;
	
	
	this->isReady=1;
}

void CCamera::SetAspect(float aspect) {
	this->aspect = aspect;
};

void CCamera::toOGL(void) {
	// Esto coge esta camara y la manda a open gl 
	// para que miremos con ella :-)

	if(!this->isReady) {
		this->recalc();
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(this->fov,this->aspect,this->zNear,this->zFar);
	gluLookAt(
			  m_vposition.x, m_vposition.y, m_vposition.z,
			  m_vlook.x, m_vlook.y, m_vlook.z,
			  m_vup.x, m_vup.y, m_vup.z
			  );
}

bool CCamera::inFrustrum(CPoint p) {
	float zmin, zmax;
	zmin = this->m_vposition.z;
	zmax = (this->m_vlook.normalize()*this->zFar).z;
	if((p.z >= zmin) && (p.z<=zmax)) {
		return true;
	} else {
		return false;
	}
	
	
	return true;
	
}
