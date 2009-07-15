#include "Texture.h"
CTexture::CTexture(){
	// init all members
	m_imageData = (unsigned char*)0;
	m_bpp = 0;
	m_width = 0;
	m_height = 0;
	m_texID = 0;
}

CTexture::~CTexture() {
}

// setters/getters
void CTexture::setImageData(unsigned char *imageData) {
	m_imageData = imageData;
}
unsigned char *CTexture::getImageData() {
	return m_imageData;
}
void CTexture::setBpp(unsigned int bpp) {
	m_bpp = bpp;
}
unsigned int CTexture::getBpp() {
	return m_bpp;
}
void CTexture::setWidth(unsigned int width) {
	m_width = width;
}
unsigned int CTexture::getWidth() {
	return m_width;
}
void CTexture::setHeight(unsigned int height) {
	m_height = height;
}
unsigned int CTexture::getHeight() {
	return m_height;
}

void CTexture::setImgWidth(unsigned int width) {
	m_imgWidth = width;
}
unsigned int CTexture::getImgWidth() {
	return m_imgWidth;
}
void CTexture::setImgHeight(unsigned int height) {
	m_imgHeight = height;
}
unsigned int CTexture::getImgHeight() {
	return m_imgHeight;
}

void CTexture::setTexId(unsigned int texId) {
	m_texID = texId;
}
unsigned int CTexture::getTexId() {
	return m_texID;
}
void CTexture::setName(string name) {
	m_name = name;
}
string CTexture::getName() {
	return m_name;
}
void CTexture::setPath(string texpath) {
	m_path = texpath;
}
string CTexture::getPath() {
	return m_path;
}