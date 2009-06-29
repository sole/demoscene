#include "Camera.h"

#include "my_opengl.h"
#define CAMERA_CORRECTION 0.0001

Camera::Camera() {
	// Si no le digo nada, crea una camara en 1,1,1 y mirando a 0,0,0
	
	this->position.x=1;
	this->position.y=1;
	this->position.z=1;
	
	this->look.x=0;
	this->look.y=0;
	this->look.z=0.1;
	
	this->fov=45.0f;
	this->zNear=1.0f;
	this->zFar=60.0f;
	this->aspect=1.3;
	
	this->recalc();
}

void Camera::SetPos(float _x,float _y, float _z) {
	this->position.x=_x;
	this->position.y=_y;
	this->position.z=_z;
	
	this->recalc();
}

void Camera::SetPos(Point _position) {
	this->position=_position;
	this->recalc();
}

void Camera::SetLook(float _x,float _y, float _z) {
	this->look.x=_x;
	this->look.y=_y;
	this->look.z=_z;
	
	this->recalc();
}

void Camera::setFov(float _fov) {
	if(_fov>0) {
		this->fov=_fov;
		this->recalc();
	}
}

float Camera::getFov(void) {
	return this->fov;
}

void Camera::setFar(float nearz,float farz) {
	this->zFar=farz;
	this->zNear=nearz;
	this->recalc();
}

void Camera::recalc(void) {
	
	Point difference;
	/* Como si tengo algo que es EXACTAMENTE 0 la diferencia y eso sale chunguis...
	le añadire un + algo si se "parece" bastante a 0 */
	
	
	difference.x=look.x-position.x+CAMERA_CORRECTION;
	difference.y=look.y-position.y+CAMERA_CORRECTION;
	difference.z=look.z-position.z+CAMERA_CORRECTION;
	
	this->up=pointCrossProduct(difference,this->look);
}

void Camera::toOGL(void) {
	// Esto coge esta camara y la manda a open gl 
	// para que miremos con ella :-)
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(this->fov,this->aspect,this->zNear,this->zFar);
	gluLookAt(position.x,position.y,position.z,look.x,look.y,look.z,up.x,up.y,up.z);        
	glMatrixMode(GL_MODELVIEW);
}
