/**
* this is supposed to be the independent render system ...
* OPENGL version
* @author Soledad Penades
* 29 july 2005
*/

#ifndef RENDER_H
#define RENDER_H

// this includes all the files that we need for using opengl
#include "my_opengl.h"
#include "Algebra.h"
#include "RenderBlending.h"
#include "Texture.h"
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#include "Camera.h"

using namespace std;
#define RENDER_CLEAR_COLOR GL_COLOR_BUFFER_BIT

class CRender {
public:
	CRender();
	~CRender();
	
	// init etc methods
	int init();
	int deinit();

	// modifying/accessing methods
	int getWidth(void); 
	int getHeight(void);
	bool isFullScreen(void);
	void setFullScreen(bool _fullscr);
	void setSize(int _width, int _height);
	void setWidth(int width);
	void setHeight(int height);
	
	// Textures / / / / // / 
	void setRenderToTextureX(unsigned int value);
	void setRenderToTextureY(unsigned int value);
	int loadTexture(string path);
	void selectTexture(unsigned int textureIndex);
	void selectTexture(CTexture* theTexture);
	CTexture* getTextureAt(unsigned int textureIndex);
	unsigned int createEmptyTexture(unsigned int width, unsigned int height);
	
	unsigned int createTextureObject();
	void setTextureWidth(unsigned int position, unsigned int width);
	unsigned int getTextureWidth(unsigned int position);
	void setTextureHeight(unsigned int position, unsigned int height);
	unsigned int getTextureHeight(unsigned int position);
	void setTextureImgWidth(unsigned int position, unsigned int width);
	unsigned int getTextureImgWidth(unsigned int position);
	void setTextureImgHeight(unsigned int position, unsigned int height);
	unsigned int getTextureImgHeight(unsigned int position);	
	void setTextureId(unsigned int position, unsigned int texid);
	unsigned int getTextureId(unsigned int position);
	void setTexturePath(unsigned int position, string texPath);
	string getTexturePath(unsigned int position);
	int getTextureIdByPath(string texPath);
	
	// Blendings
	void addBlending(string name, string srcFactor, string dstFactor);
	unsigned int getBlending(string name);
	unsigned int evalBlending(string factor);
	
	// buffering
	void swapBuffers(void);
	
	// auxiliars
	void auxAxis();
	
	// drawing primitives
	void drawCube(bool wired);
	
	// Mogollon
	void addVertex(CPoint p);
	void addVertex(float x, float y, float z=0, float w=0);
	void beginShapeLines();
	void beginShapeLineStrip();
	void beginShapePoints();
	void beginShapePolygon();
	void beginShapeTriangles();
	void beginShapeQuads();
	void blendFunc(unsigned int rbPos);
	void bindTexture(CTexture* texture);
	void bindTexture(unsigned int textureIndex);
	void cameraLookAtLH(CPoint camPosition, CPoint camTarget, CPoint camUp);
	void cameraFovLH(float fov, float aspect, float fNear, float fFar);
	void clear(int mask);
	void copyToTexture(unsigned int offsetx, unsigned int offsety, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	void disableBlend();
	void disableDepthMask();
	void disableLineStipple();
	void disableTexture();
	void endShape();	
	void enableBlend();
	void enableDepthMask();
	void enableLineStipple();
	void enableTexture();
	void flush();
	CCamera* getActiveCamera();
	CMatrix getModelViewMatrix();
	CMatrix getProjectionMatrix();
	string getError();
	void getCurrentColor(float *vcolor);
	void loadIdentity();
	void loadMatrix(CMatrix m);
	void normal(float x, float y, float z); 
	void orthoSet(float xres=-1, float yres=-1);
	void orthoUnset(void);
	void popMatrix(void);
	void pushMatrix(void);
	void rotate(double angle, double x, double y, double z);
	void scale(double x, double y, double z);
	void setActiveCamera(CCamera *activeCamera);
	void setColor(CPoint c);
	void setColor(float r, float g, float b, float a=1);
	void setColor(float *vcolor4);
	void setLineStipple(unsigned int repeats, unsigned short pattern);
	void setLineWidth(float width);
	void setPointSize(float size);
	void setProjectionMatrix(void);
	void setModelMatrix(void);
	void setTextureMatrix(void);
	void setTextureCoord(double x, double y);
	void translate(double x, double y, double z);
	void translate(CPoint p);
	
	
private:
	// display properties
	int m_Height; // window height
	int m_Width; // window width
	std::string m_windowTitle;
	bool m_bFullscreen;
	bool m_bWindowOpen;
	float m_OrthoNear;
	float m_OrthoFar;
	
	CCamera m_dummyCamera; // with this camera, we'll never return NULL when being asked for the activeCamera
	CCamera *m_activeCamera;
	
	// textures properties
	unsigned int m_RenderToTextureX, m_RenderToTextureY;
	vector<CTexture> m_textures; // texture list
	vector<CRenderBlending> m_blendModes;
	
	
};

#endif
