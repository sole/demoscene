#include "BezierPath.h"
#include <iostream>
using namespace std;

CBezierPath::CBezierPath() {
	m_needsRecalc = true;
	m_numSteps = 3;
	m_currPos = 0;
}

// Control points -----------------------------------
// add a new control point at the end
void CBezierPath::addControlPoint(CPoint newPoint)
{
	this->m_controlPoints.push_back(newPoint);
		
	if(m_controlPoints.size()-m_bezierCurves.size()*3 >= 4 )
	{
		CBezierCurve c;
		c.setPoint(0, m_controlPoints.at(m_controlPoints.size()-4));
		c.setPoint(1, m_controlPoints.at(m_controlPoints.size()-3));
		c.setPoint(2, m_controlPoints.at(m_controlPoints.size()-2));
		c.setPoint(3, m_controlPoints.at(m_controlPoints.size()-1));
		if(m_bezierCurves.size()==0) {
			c.setPoint(0, m_controlPoints.at(m_controlPoints.size()-4));
			c.setPoint(1, m_controlPoints.at(m_controlPoints.size()-3));
			c.setPoint(2, m_controlPoints.at(m_controlPoints.size()-2));
			c.setPoint(3, m_controlPoints.at(m_controlPoints.size()-1));
		} else {
			CPoint p2,p3;
			p2 = m_controlPoints.at(m_controlPoints.size()-5);
			p3 = m_controlPoints.at(m_controlPoints.size()-4); 
			
			c.setPoint(0, p3);
			c.setPoint(1, (p3-p2)*3);
			c.setPoint(2, m_controlPoints.at(m_controlPoints.size()-2));
			c.setPoint(3, m_controlPoints.at(m_controlPoints.size()-1));
		}
		
		m_bezierCurves.push_back(c);
		this->m_needsRecalc = true;
		
	}
}

// remove control point in "which" position
void CBezierPath::removeControlPoint(unsigned int which) {
	;
}
// update point which with newPoint
void CBezierPath::setControlPoint(unsigned int which, CPoint newPoint) {
	m_controlPoints.at(which) = newPoint;
	// Update the curve point
	unsigned int curve, point;
	curve = which / 4;
	point = which % 4;
	m_bezierCurves.at(curve).setPoint(point, newPoint);
	m_needsRecalc = true;
}
// get the value of "which" control point
CPoint CBezierPath::getControlPoint(unsigned int which) {
	if(which>0 && which<m_controlPoints.size()) {
		return m_controlPoints.at(which);
	} else return CPoint();
}

unsigned int CBezierPath::getNumControlPoints() {
	return m_controlPoints.size();
}

void CBezierPath::calculate() {
	unsigned int i, j;
	if(m_needsRecalc) {
		// is there enough space for all the calculated points?
		int calcAmount = m_bezierCurves.size()*(m_numSteps)+1;
		//cout << "We need " << calcAmount << " points " << endl;
		//cout << "Currently we have space for " << m_calculatedPoints.size() << " points" << endl;
		if(m_calculatedPoints.size() < calcAmount) {
			// no - add more
			for(i=m_calculatedPoints.size(); i<calcAmount; i++) {
				CPoint *c = new CPoint();
				m_calculatedPoints.push_back(*c);
			}
		}
		//cout << "Space now is " << m_calculatedPoints.size() << endl;
		
		// calculate points
		// void curveSteps(int number, CPoint *points);
		//return number+1 steps in the curve in points[number+1]
		CPoint* tempPoints = new CPoint[m_numSteps];
		for(i=0; i<m_bezierCurves.size();i++) {
			m_bezierCurves.at(i).curveSteps(m_numSteps-1, tempPoints);
			// copy calc'ed values to the calculatedPoints array
			for(j=0; j<m_numSteps; j++) {
				//cout << "Calc'ed points at " << i*m_numSteps + j << endl; 
				//tempPoints[j].write();
				m_calculatedPoints.at(i*m_numSteps + j) = tempPoints[j];
			}
		}
		delete tempPoints;
		
		m_needsRecalc = false;
	}
}

unsigned int CBezierPath::getNumSteps() {
	return m_numSteps;
}
void CBezierPath::setNumSteps(unsigned int newNumSteps) {
	if(newNumSteps>=2) {
		m_numSteps = newNumSteps;
		m_needsRecalc = true;
	}
}

unsigned int CBezierPath::getNumValues() {
	return m_calculatedPoints.size();
}

CPoint CBezierPath::getValueAt(unsigned int i) {
	calculate();
	return m_calculatedPoints.at(i%(m_calculatedPoints.size()));
}

CPoint CBezierPath::getValue() {
	//CPoint p;
	calculate();
	m_currPos = (++m_currPos)%(m_calculatedPoints.size());
	//cout << "returning at position " << m_currPos << endl;
	//return p;
	return m_calculatedPoints.at(m_currPos);
}
unsigned int CBezierPath::getPosition() {
	return m_currPos;
};

void CBezierPath::outputInfo() {
	unsigned int i,j;
	cout << "With " << m_controlPoints.size() << " control points:" << endl;
	for(i=0; i<m_controlPoints.size(); i++) {
		cout << i << ": " << m_controlPoints.at(i).x << " " << m_controlPoints.at(i).y << " " << m_controlPoints.at(i).z << endl;
	}
	//cout << "And " << m_bezierCurves.size() << " bezier curves" << endl;
	for(i=0; i<m_bezierCurves.size();i++) {
		//cout << "CURVE " <<  i << endl;
		for(j=0; j<4; j++) {
			m_bezierCurves.at(i).control(j).write();
		}
	}
}
