#ifndef __CAMERA__
	#define __CAMERA__

#include "math3D.h"#include "Algebra.h"

#define CAMERA_CORRECTION 0.0001
class Camera {
public:
	// Posicion
	Point position;
	// A donde miro?
	Point look;
	// Vector UP
	Point up;
	// angulo de vision
	float fov;
	// zlejos, zcerca
	float zNear,zFar;
	float aspect;
//public:
	Camera();
	void SetPos(float x,float y, float z);
	void SetPos(Point _position);
	void SetLook(float _x,float _y, float _z);
	void setFov(float _fov);
	float getFov(void);
	void setFar(float nearz,float farz);
	
	void toOGL(void);

	void BillboardPoint(CPoint pos);

private:
	// Recalculo la cámara
	void recalc(void);
	unsigned int isReady;
};

#endif
