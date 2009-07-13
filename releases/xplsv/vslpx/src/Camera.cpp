#include "Camera.h"
#include "my_opengl.h"

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

	this->isReady=0;
}

void Camera::SetPos(Point _position) {
	this->position=_position;
	this->isReady=0;
}

void Camera::SetLook(float _x,float _y, float _z) {
	this->look.x=_x;
	this->look.y=_y;
	this->look.z=_z;

	this->isReady=0;
}

void Camera::setFov(float _fov) {
	if(_fov>0) {
		this->fov=_fov;
		this->isReady=0;
	}
}

float Camera::getFov(void) {
	return this->fov;
}

void Camera::setFar(float nearz,float farz) {
	this->zFar=farz;
	this->zNear=nearz;
	this->isReady=0;
}

void Camera::recalc(void) {

	//Point difference;
	/* Como si tengo algo que es EXACTAMENTE 0 la diferencia y eso sale chunguis...
	le añadire un + algo si se "parece" bastante a 0 */
	CPoint cdifference, cup, clook;
	
	cdifference.x=float(double(look.x)-double(position.x)/*+CAMERA_CORRECTION*/);
	cdifference.y=float(double(look.y)-double(position.y)/*+CAMERA_CORRECTION*/);
	cdifference.z=float(double(look.z)-double(position.z)/*+CAMERA_CORRECTION*/);

	clook.x=this->look.x;
	clook.y=this->look.y;
	clook.z=this->look.z;
	
	//difference.x=float(double(look.x)-double(position.x)/*+CAMERA_CORRECTION*/);
	//difference.y=float(double(look.y)-double(position.y)/*+CAMERA_CORRECTION*/);
	//difference.z=float(double(look.z)-double(position.z)/*+CAMERA_CORRECTION*/);

	cup = cdifference ^ clook;

	//this->up=pointCrossProduct(difference,this->look);
	this->up.x=-cup.x;
	this->up.y=-cup.y;
	this->up.z=-cup.z;

	this->isReady=1;
}

void Camera::toOGL(void) {
	// Esto coge esta camara y la manda a open gl 
	// para que miremos con ella :-)

	if(!this->isReady) {
		this->recalc();
	}
	glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	glLoadIdentity();
	//gluPerspective(this->fov,this->aspect,this->zNear,this->zFar);
	// a ver si asi... glFrustum(-1.0,1.0,-1.0,1.0,this->zNear,this->zFar);
	gluPerspective(this->fov,this->aspect,this->zNear,this->zFar);
	gluLookAt(position.x,position.y,position.z,look.x,look.y,look.z,up.x,up.y,up.z);        
	glMatrixMode(GL_MODELVIEW);
}

void Camera::BillboardPoint(CPoint pos) {
	// create the look vector: pos -> camPos
	CPoint myPosition;
	myPosition.x=position.x;
	myPosition.y=position.y;
	myPosition.z=position.z;
	myPosition.w=position.w;

	CPoint	look	= myPosition - pos;
	look.normalize();
	// right hand rule cross products
	CPoint camUp;
	camUp.x=this->up.x;
	camUp.y=this->up.y;
	camUp.z=this->up.z;
	camUp.w=this->up.w;
	CPoint	right	= camUp^look; //this->camUp.Cross(look);
	CPoint  vup		= look^right;//look.Cross(right);

	//Matrix44f	bbmat;
	//CreateBillboardMatrix(bbmat, right, up, look, pos);
	float modelview[16];
	modelview[0] = right.x;
	modelview[1] = right.y;
	modelview[2] = right.z;
	modelview[3] = 0;
	modelview[4] = up.x;
	modelview[5] = up.y;
	modelview[6] = up.z;
	modelview[7] = 0;
	modelview[8] = look.x;
	modelview[9] = look.y;
	modelview[10] = look.z;
	modelview[11] = 0;
	// Add the translation in as well.
	modelview[12] = pos.x;
	modelview[13] = pos.y;
	modelview[14] = pos.z;
	modelview[15] = 1;

	// apply the billboard
	glMultMatrixf(modelview);
}
