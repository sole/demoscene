#ifndef __CAMERA__
#define __CAMERA__

#include "math3D.h"

// WARNING: This class is awful. It is highly unstable and doesn't work
// as it should. Use it if you want a migraine.

class Camera {
public:
	
	Point position;	Point look;
	Point up;
	float fov;
	float zNear,zFar;
	float aspect;
	
	Camera();
	void SetPos(float x,float y, float z);
	void SetPos(Point _position);
	void SetLook(float _x,float _y, float _z);
	void setFov(float _fov);
	float getFov(void);
	void setFar(float nearz,float farz);
	
	void toOGL(void);
	
private:
		void recalc(void);
};

#endif

