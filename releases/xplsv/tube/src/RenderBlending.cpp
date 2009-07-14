#include "RenderBlending.h"
CRenderBlending::CRenderBlending() {
	
}

unsigned int CRenderBlending::getSrc() {
	return this->srcFactor;
}
void CRenderBlending::setSrc(unsigned int value) {
	this->srcFactor=value;
}
unsigned int CRenderBlending::getDst() {
	return this->dstFactor;
}
void CRenderBlending::setDst(unsigned int value) {
	this->dstFactor=value;
}
string CRenderBlending::getName() {
	return this->name ;
}
void CRenderBlending::setName(string _name) {
	this->name = _name;
}
