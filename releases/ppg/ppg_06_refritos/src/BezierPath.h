#ifndef BEZIERPATH_H
#define BEZIERPATH_H

#include "BezierCurve.h"
#include <vector>

class CBezierPath
{
	
private:
	// control points
	std::vector<CPoint> m_controlPoints;
	
	// bezier curves
	std::vector<CBezierCurve> m_bezierCurves;
	unsigned int m_numSteps;
	
	// calculated (intermediate) values
	std::vector<CPoint> m_calculatedPoints;
	bool m_needsRecalc;
	
	// current position
	unsigned int m_currPos;
	
public:
	//Constructores	
	CBezierPath();
	
	// Control points -----------------------------------
	// add a new control point at the end
	void addControlPoint(CPoint newPoint);
	// remove control point in "which" position
	void removeControlPoint(unsigned int which);
	// update point which with newPoint
	void setControlPoint(unsigned int which, CPoint newPoint);
	// get the value of "which" control point
	CPoint getControlPoint(unsigned int which);
	unsigned int getNumControlPoints();
	
	// Bezier curves ------------------------------------
	// steps is the number of intermediate values per curve we want
	unsigned int getNumSteps();
	void setNumSteps(unsigned int newNumSteps);
	
	// calculate ----------------------------------------
	void calculate();
	unsigned int getNumValues();
	CPoint getValueAt(unsigned int i);
	CPoint getValue();
	unsigned int getPosition();
	
	// misc----------------------------------------------
	void outputInfo();
};


#endif
