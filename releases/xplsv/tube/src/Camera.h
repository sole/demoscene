// Camara!! Viva!!  Al fin tengo una camara! Por defecto, es una camara perspectiva
// 20041012 un año despues... mejoro este header, ahora no necesita glut.h, y la inclusion de math3D se hace
// asumiendo que con un define se controla o no si ya se ha incluido previamente (Mas aseado)
// revisado 14 agosto 2005

#ifndef CAMERA_H
#define CAMERA_H

#include "Algebra.h"


class CCamera {
public:
	// Posicion
	CPoint m_vposition;
	// A donde miro? (VECTOR)
	CPoint m_vlook;
	CPoint m_vtarget; // (el punto a donde miramos)
	// Vector UP
	CPoint m_vup;
	CPoint m_vright;
	// angulo de vision
	float fov;
	// zlejos, zcerca
	float zNear,zFar;
	float aspect;
//public:
	CCamera();
	
	void Place(CPoint position, CPoint targetPosition, CPoint upVector);
	
	void SetFov(float _fov);
	float GetFov(void);
	void SetFar(float nearz,float farz);
	void SetAspect(float aspect);
	void MoveForward(float distance);
	void StrafeRight(float distance);
	void MoveUpward(float distance);
	void rotateX(float degrees);
	void rotateY(float degrees);
	void rotateZ(float degrees);
	CPoint getUp();
	CPoint getRight();
	CPoint getTarget();
	
	void toOGL(void);

	// returns if a point is inside the frustrum (and hence.. drawable)
	bool inFrustrum(CPoint p);

private:
	// Recalculo la cámara
	void recalc(void);
	unsigned int isReady;
	// No usar desde fuera
	void SetPos(float x,float y, float z);
	void SetPos(CPoint _position);
	void SetLook(float _x,float _y, float _z);
};

#endif
