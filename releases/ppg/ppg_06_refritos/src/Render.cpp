/**
 * this is supposed to be the independent render system ...
 * OPENGL version
 * @author Soledad Penades
 * 29 july 2005
 */

#include "Render.h"
#include <cstdio>

#define ORTHONEAR 0.20f
#define ORTHOFAR 200.0f

#include "SOIL/SOIL.h"

CRender::CRender() {
	this->m_bWindowOpen = false;
	this->m_bFullscreen = false;
	this->m_OrthoNear = 0.0f;
	this->m_OrthoFar = 200.0f;
	
	// A simple camera placed in 100,0,100 , looking at 0 and with up vector = y axis
	m_dummyCamera.Place(CPoint(100,0,100), CPoint(0,0,0), CPoint(0,1,0));
	m_activeCamera = &m_dummyCamera;
	
	m_windowTitle = "thisisnotanengine / xplsv ";
}

CRender::~CRender() {
}

int CRender::init() {
	// TODO clean up
	
}

int CRender::deinit() {
	// TODO clean up
		
	return 0;
}

/**
* Returns the current demo window height
 */
int CRender::getHeight(void) {
	return this->m_Height;
}

/**
* Returns the current demo window width
*/
int CRender::getWidth(void) {
	return this->m_Width;
}

/**
* Sets the current demo window width and height
*/
void CRender::setSize(int _width, int _height) {
	if((_height>0) && (_width>0)) {
		this->m_Height=_height;
		this->m_Width=_width;
	} 
}

void CRender::setWidth(int width) {
	this->m_Width = width;
}

void CRender::setHeight(int height) {
	this->m_Height = height;
}


/**
* Set render to texture sizes
*/
void CRender::setRenderToTextureX(unsigned int value) {
	this->m_RenderToTextureX = value;
}
void CRender::setRenderToTextureY(unsigned int value) {
	this->m_RenderToTextureY = value;
}
/**
* Is the demo currently fullscreened?
*/
bool CRender::isFullScreen(void) {
	return this->m_bFullscreen;
}

/**
* Set whether demo is fullscreen or not 
* This does not affect the current status - window must be updated somehow!
*/
void CRender::setFullScreen(bool _fullscr) {
	this->m_bFullscreen=_fullscr;
}


/**
 * swap the buffer -- when double buffered
 */
void CRender::swapBuffers(void) {
	SDL_GL_SwapBuffers();
}


////////// Textures ///////////////////////
/* 
try to load a texture from disk, if successful, return the id
 which is >=0
 else -1
 
 The id corresponds to the last created texture (in our local list of textures)
 
 TODO: when loading a texture, check if the texture exists previously and can be modified or not
 this can be specially useful for having dummy textures which will be used for next effects, like
 using them as blur containers etc
 So there must be like an attribute when loading the texture which says if it can be reused or not
 If it can be reused, we could check if it was loaded previously and hence do not load it again so 
 we'll save memory.
 TODO: Add a way of specifying the texture filters (linear, mipmap ... etc)
*/
int CRender::loadTexture(string path) {
	int res;
	GLuint texId;
	unsigned int texPos;
	int existingTexturePos=this->getTextureIdByPath(path);

	// Search for this texture in the textures list (with the exact path)
	if(existingTexturePos!=-1) {
		return existingTexturePos;
	}

	texId = SOIL_load_OGL_texture(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y 
	);
	
	if(0 == texId)
	{
		// then return error
		cout << "Render:: loadTexture :: can't load texture " << path << " error: " << SOIL_last_result() << endl;
		return -1;
	}

	
	texPos = this->createTextureObject();
	
	GLint width, height, border;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_BORDER, &border);
	width -= border; height -= border;
	setTextureWidth(texPos, width);
	setTextureHeight(texPos, height);
	setTextureId(texPos, texId);

	// This is a bit erm.. slow ... but i need it to load the images size
	int img_width, img_height, img_channels;
	SOIL_load_image(path.c_str(), &img_width, &img_height, &img_channels, SOIL_LOAD_AUTO);
	setTextureImgWidth(texPos, img_width);
	setTextureImgHeight(texPos, img_height);

	
	return texPos;
}

// Activates the use of this texture by the current render i.e. opengl
// TODO add a new param to select which texture mode to use : 1D or 2D
// TODO add a check for avoiding the selection of textures out of range ;)
void CRender::selectTexture(unsigned int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, m_textures[textureIndex].getTexId());
}
void CRender::selectTexture(CTexture* theTexture) {
	glBindTexture(GL_TEXTURE_2D, theTexture->getTexId());
}

// Returns a reference to the texture which is currently at the position
// "textureIndex" so things like the width of the texture can be known
CTexture* CRender::getTextureAt(unsigned int textureIndex) {
	return &m_textures[textureIndex];
}

// Creates a new object CTexture and stores it in our texture list. Returns the index in the textures list.
unsigned int CRender::createTextureObject() {
	CTexture* theTexture = new CTexture();
	this->m_textures.push_back(*theTexture);
	return this->m_textures.size()-1;
}

void CRender::setTextureWidth(unsigned int position, unsigned int width) {
	this->m_textures[position].setWidth(width);
}
unsigned int CRender::getTextureWidth(unsigned int position) {
	return this->m_textures[position].getWidth();
}
void CRender::setTextureHeight(unsigned int position, unsigned int height) {
	this->m_textures[position].setHeight(height);
}
unsigned int CRender::getTextureHeight(unsigned int position) {
	return this->m_textures[position].getHeight();
}
void CRender::setTextureImgWidth(unsigned int position, unsigned int width) {
	this->m_textures[position].setImgWidth(width);
}
unsigned int CRender::getTextureImgWidth(unsigned int position) {
	return this->m_textures[position].getImgWidth();
}
void CRender::setTextureImgHeight(unsigned int position, unsigned int height) {
	this->m_textures[position].setImgHeight(height);
}
unsigned int CRender::getTextureImgHeight(unsigned int position) {
	return this->m_textures[position].getImgHeight();
}
void CRender::setTextureId(unsigned int position, unsigned int texid) {
	this->m_textures[position].setTexId(texid);
}
unsigned int CRender::getTextureId(unsigned int position) {
	return this->m_textures[position].getTexId();
}
void CRender::setTexturePath(unsigned int position, string texPath) {
	this->m_textures[position].setPath(texPath);
}
string CRender::getTexturePath(unsigned int position) {
	return this->m_textures[position].getPath();
}
int CRender::getTextureIdByPath(string texPath){
	unsigned int i, numtex;
	
	numtex = this->m_textures.size();
	for(i=0;i<numtex;i++) {
		if(texPath==this->m_textures[i].getPath()) {
			return i;
		}
	}
	return -1;
}

// Tries to allocate space for a new texture and returns the position of the associated CTexture object in the list
unsigned int CRender::createEmptyTexture(unsigned int width, unsigned int height) {
	// CTexture* theTexture = new CTexture();
	unsigned int texPos; // will hold the position of the texture in our m_textures list
	GLuint texId;
	unsigned int calcWidth, calcHeight;
	GLuint* dummyData; // we'll use this for initializing the texture
	
	// First we decide which final dimensions will have the image (so we can adjust it to be power of 2)
	calcWidth = 1;
	calcHeight = 1;
	
	// Adjust the width:
	while(calcWidth <= width) {
		calcWidth *= 2;
	}
	// Adjust the height:
	while(calcHeight <= height) {
		calcHeight *= 2;
	}
	
	// Now that we know the final size we can create the texture...
	
	// Create texture object
	texPos = this->createTextureObject();
	
	// Initialize some space in memory so we can copy that to opengl
	dummyData = (GLuint *)new GLuint[calcWidth * calcHeight * 4 * sizeof(GLuint)];
	
	glEnable(GL_TEXTURE_2D);
	
	// Create a new texture id and select that texture
	glGenTextures(1, &texId);					
	glBindTexture(GL_TEXTURE_2D, texId);
	
	// Actually create the texture
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, calcWidth, calcHeight, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, dummyData);						
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR	);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	
	// We can throw this as it's not useful anymore...
	delete [] dummyData;
	
	// Assign the final values to the CTexture object
	this->setTextureId(texPos, texId);
	setTextureWidth(texPos, calcWidth);
	setTextureHeight(texPos, calcHeight);
	
	glDisable(GL_TEXTURE_2D);
	
	return texPos;
}

// auxiliars
void CRender::auxAxis() {
	setLineWidth(3.0f);
	setColor(1.0f,0.0,0.0);
	beginShapeLines();
		addVertex(0.0f,0.0f,0.0f);
		addVertex(1000.0f,0.0f,0.0f); // X
	endShape();
	
	enableLineStipple();
	setLineStipple(1,0xaaaa);
	
	beginShapeLines();
		addVertex(0.0f,0.0f,0.0f);
		addVertex(-1000.0f,0.0f,0.0f); // X neg
	endShape();
	disableLineStipple();
	
	setColor(0.0f,1.0,0.0);
	beginShapeLines();
		addVertex(0.0f,0.0f,0.0f);
		addVertex(0.0f,1000.0f,0.0f); // y
	endShape();
	
	enableLineStipple();
	beginShapeLines();
		addVertex(0.0f,0.0f,0.0f);
		addVertex(0.0f,-1000.0f,0.0f); // y neg
	endShape();
	disableLineStipple();
	
	setColor(0.0f,0.0,1.0);
	beginShapeLines();
	addVertex(0.0f,0.0f,0.0f);
	addVertex(0.0f,0.0f,1000.0f); // z
	endShape();
	
	enableLineStipple();
	beginShapeLines();
	addVertex(0.0f,0.0f,0.0f);
	addVertex(0.0f,0.0f,-1000.0f); // z neg
	endShape();
	disableLineStipple();
	setLineWidth(1.0f);
	
}

// Blendings
unsigned int CRender::evalBlending(string name) {
	if(name=="ZERO") return GL_ZERO;
	if(name=="ONE") return GL_ONE;
	if(name=="SRC_COLOR") return GL_SRC_COLOR;
	if(name=="ONE_MINUS_SRC_COLOR") return GL_ONE_MINUS_SRC_COLOR;
	if(name=="DST_COLOR") return GL_DST_COLOR;
	if(name=="ONE_MINUS_DST_COLOR") return GL_ONE_MINUS_DST_COLOR;
	if(name=="SRC_ALPHA") return GL_SRC_ALPHA;
	if(name=="ONE_MINUS_SRC_ALPHA") return GL_ONE_MINUS_SRC_ALPHA;
	if(name=="DST_ALPHA") return GL_DST_ALPHA;
	if(name=="ONE_MINUS_DST_ALPHA") return GL_ONE_MINUS_DST_ALPHA;
	if(name=="SRC_ALPHA_SATURATE") return GL_SRC_ALPHA_SATURATE;
	return 0;
}

void CRender::addBlending(string name, string srcFactor, string dstFactor) {
	// create the blending
	CRenderBlending* theBlending = new CRenderBlending();
	theBlending->setSrc(evalBlending(srcFactor));
	theBlending->setDst(evalBlending(dstFactor));
	theBlending->setName(name);
	
	// save the blending in our list
	this->m_blendModes.push_back(*theBlending);
	
}
unsigned int CRender::getBlending(string name) {
	// way simple! simply access by index the blending name
	for(int i=0; i<this->m_blendModes.size(); i++) {
		if(this->m_blendModes[i].getName()==name) {
			return i;
		}
	}
	return 0;
}

/************ el mogollon *****************/
void CRender::addVertex(CPoint p) {
	glVertex3f(p.x, p.y, p.z);
}
void CRender::addVertex(float x, float y, float z, float w) {
	glVertex3f(x,y,z);
}
void CRender::beginShapeLines() {
	glBegin(GL_LINES);
}
void CRender::beginShapeLineStrip() {
	glBegin(GL_LINE_STRIP);
}
void CRender::beginShapePoints() {
	glBegin(GL_POINTS);
}
void CRender::beginShapePolygon() {
	glBegin(GL_POLYGON);
}
void CRender::beginShapeQuads() {
	glBegin(GL_QUADS);
}
void CRender::beginShapeTriangles() {
	glBegin(GL_TRIANGLES);
}
void CRender::blendFunc(unsigned int rbPos) {
	glBlendFunc(this->m_blendModes[rbPos].getSrc(), this->m_blendModes[rbPos].getDst());
}
void CRender::bindTexture(CTexture* texture) {
	glBindTexture(GL_TEXTURE_2D, texture->getTexId());
}
void CRender::bindTexture(unsigned int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, this->m_textures[textureIndex].getTexId());
}
/*
 This should act as the dx function D3DXMatrixLookAtLH plus a real projection matrix transformation
 */
void CRender::cameraLookAtLH(CPoint camPosition, CPoint camTarget, CPoint camUp) {
	setProjectionMatrix();
	loadIdentity();
	gluLookAt(camPosition.x,camPosition.y,camPosition.z,camTarget.x,camTarget.y,camTarget.z,camUp.x,camUp.y,camUp.z);
}
/*
 This should act as the dx function D3DXMatrixFovLH plus a real projection matrix transformation
 */
void CRender::cameraFovLH(float fov, float aspect, float fNear, float fFar) {
	setProjectionMatrix();
	gluPerspective(fov, aspect, fNear, fFar);
}
void CRender::clear(int mask) {
	glClear(mask);
}
void CRender::copyToTexture(unsigned int offsetx, unsigned int offsety, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	glCopyTexSubImage2D(GL_TEXTURE_2D,// target
						0, //level mipmaps
						offsetx, //xoffset
						offsety, // yoffset
						x, // x
						y, //y
						width, // width
						height); //height 
}
void CRender::disableBlend(void) {
	glDisable(GL_BLEND);
}
void CRender::disableDepthMask(void) {
	glDepthMask(GL_FALSE);
}
void CRender::disableLineStipple(void) {
	glDisable(GL_LINE_STIPPLE);
}
void CRender::disableTexture(void) {
	glDisable(GL_TEXTURE_2D);
}

void CRender::enableBlend(void) {
	glEnable(GL_BLEND);
}
void CRender::enableDepthMask(void) {
	glDepthMask(GL_TRUE);
}
void CRender::enableLineStipple(void) {
	glEnable(GL_LINE_STIPPLE);
}
void CRender::enableTexture(void) {
	glEnable(GL_TEXTURE_2D);
}

void CRender::endShape(void) {
	glEnd();
}

void CRender::flush(void) {
	glFlush();
}

CCamera* CRender::getActiveCamera(){
	return this->m_activeCamera;
}
CMatrix CRender::getModelViewMatrix() {
	CMatrix* m = new CMatrix();
	static float v[16]={0};
	
	// Get the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX , v);
	
	m->e[0][0] = v[0];
	m->e[1][0] = v[1];
	m->e[2][0] = v[2];
	m->e[3][0] = v[3];
	
	m->e[0][1] = v[4];
	m->e[1][1] = v[5];
	m->e[2][1] = v[6];
	m->e[3][1] = v[7];
	
	m->e[0][2] = v[8];
	m->e[1][2] = v[9];
	m->e[2][2] = v[10];
	m->e[3][2] = v[11];
	
	m->e[0][3] = v[12];
	m->e[1][3] = v[13];
	m->e[2][3] = v[14];
	m->e[3][3] = v[15];
	
	return *m;
}

CMatrix CRender::getProjectionMatrix() {
	CMatrix* m = new CMatrix();
	static float v[16]={0};
	
	glGetFloatv(GL_PROJECTION_MATRIX , v);
	
	m->e[0][0] = v[0];
	m->e[1][0] = v[1];
	m->e[2][0] = v[2];
	m->e[3][0] = v[3];
	
	m->e[0][1] = v[4];
	m->e[1][1] = v[5];
	m->e[2][1] = v[6];
	m->e[3][1] = v[7];
	
	m->e[0][2] = v[8];
	m->e[1][2] = v[9];
	m->e[2][2] = v[10];
	m->e[3][2] = v[11];
	
	m->e[0][3] = v[12];
	m->e[1][3] = v[13];
	m->e[2][3] = v[14];
	m->e[3][3] = v[15];
	
	return *m;
}

string CRender::getError() {
	GLenum ret = glGetError();
	string errorString;
	
	if(ret!=0) {
		switch(ret) {
			case GL_INVALID_ENUM: errorString = "Invalid Enum";break;
			case GL_INVALID_VALUE: errorString ="Invalid Value";break;
			case GL_INVALID_OPERATION: errorString="Invalid Operation";break;
			case GL_STACK_OVERFLOW: errorString="Stack Overflow";break;
			case GL_STACK_UNDERFLOW: errorString="Stack Underflow";break;
			case GL_OUT_OF_MEMORY: errorString="Out of memory";break;
		}
	}
	return errorString;
}

void CRender::getCurrentColor(float *vcolor) {
	glGetFloatv(GL_CURRENT_COLOR, vcolor);
}
void CRender::normal(float x, float y, float z) {
	glNormal3f(x,y,z);	
}

void CRender::loadIdentity() {
	glLoadIdentity();
}

void CRender::loadMatrix(CMatrix m) {
	double values[16];
	
	/*
	 ( m[0]   m[4]   m[8]    m[12] )
	 |m[1]   m[5]    m[9]   m[13]  | 
	 |m[2]   m[6]   m[10]   m[14]  |
	 (m[3]   m[7]   m[11]   m[15]  ) 
	 */
	values[0] = m.e[0][0];
	values[1] = m.e[1][0];
	values[2] = m.e[2][0];
	values[3] = m.e[3][0];
	
	values[4] = m.e[0][1];
	values[5] = m.e[1][1];
	values[6] = m.e[2][1];
	values[7] = m.e[3][1];
	
	values[8] = m.e[0][2];
	values[9] = m.e[1][2];
	values[10] = m.e[2][2];
	values[11] = m.e[3][2];
	
	values[12] = m.e[0][3];
	values[13] = m.e[1][3];
	values[14] = m.e[2][3];
	values[15] = m.e[3][3];
	
	glLoadMatrixd(values);
}


void CRender::popMatrix(void) {
	glPopMatrix();
}

void CRender::pushMatrix() {
	glPushMatrix();
}

void CRender::orthoSet(float xres, float yres) {
	float xhalf, yhalf;
	setProjectionMatrix();
	pushMatrix();
	
	xhalf = (xres==-1) ? (this->m_Width)*0.5 : xres*0.5;
	yhalf = (yres==-1) ? (this->m_Height)*0.5 : yres*0.5;
	glViewport(0, 0, m_Width, m_Height);
	glOrtho(-xhalf, xhalf, -yhalf, yhalf, m_OrthoNear, m_OrthoFar);

	setModelMatrix();
}

void CRender::orthoUnset(void) {
	setProjectionMatrix();
	popMatrix();
	setModelMatrix();
}
void CRender::rotate(double angle, double x, double y, double z){ 
	glRotated(angle, x, y, z);
}
void CRender::scale(double x, double y, double z) {
	glScaled(x,y,z);
}

void CRender::setActiveCamera(CCamera *activeCamera) {
	this->m_activeCamera = activeCamera;
}
void CRender::setModelMatrix(void) {
	glMatrixMode(GL_MODELVIEW);
}
void CRender::setColor(CPoint c) {
	glColor4f(c.x, c.y, c.z, c.w);
}
void CRender::setColor(float r, float g, float b, float a) {
	glColor4f(r,g,b,a);
}
void CRender::setColor(float *color4) {
	setColor(color4[0], color4[1], color4[2], color4[3]);
}
void CRender::setLineStipple(unsigned int repeats, unsigned short pattern) {
	/* With opengl, repeats means the number of times a bit in the pattern will be used
	(repeated) before using the next one */
	glLineStipple(repeats, pattern);
}
void CRender::setLineWidth(float width) {
	glLineWidth(width);
}
void CRender::setPointSize(float size) {
	glPointSize(size);
}
void CRender::setProjectionMatrix(void) {
	glMatrixMode(GL_PROJECTION);
}
void CRender::setTextureMatrix(void) {
	glMatrixMode(GL_TEXTURE);
}

void CRender::setTextureCoord(double x, double y) {
	glTexCoord2d(x,y);
}
void CRender::translate(double x, double y, double z) {
	glTranslated(x,y,z);
}
void CRender::translate(CPoint p) {
	translate(p.x,p.y,p.z);
}

/// drawing primitives
void CRender::drawCube(bool wired) {
	if(!wired) {
	glBegin(GL_QUADS);
		//glColor3f(0.0f,1.0f,0.0f);	// Color green
		glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Top)
		//glColor3f(1.0f,0.5f,0.0f);	// Color Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);	// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f, 1.0f);	// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Bottom)
		//glColor3f(1.0f,0.0f,0.0f);	// Color Red	
		glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Front)
		//glColor3f(1.0f,1.0f,0.0f);	// Color Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);	// Top Right Of The Quad (Back)
		glVertex3f(-1.0f,-1.0f,-1.0f);	// Top Left Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f,-1.0f);	// Bottom Left Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,-1.0f);	// Bottom Right Of The Quad (Back)
		//glColor3f(0.0f,0.0f,1.0f);	// Color Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Left)
		//glColor3f(1.0f,0.0f,1.0f);	// Color Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Right)*/
	glEnd();			// End Drawing The Cube
	} else {
		
		glBegin(GL_LINES);
			// right
			glVertex3f(1,1,1);
			glVertex3f(1,-1,1);
			
			glVertex3f(1,-1,1);
			glVertex3f(1,-1,-1);
			
			glVertex3f(1,-1,-1);
			glVertex3f(1,1,-1);
			
			glVertex3f(1,1,-1);
			glVertex3f(1,1,1);
		
			// top
			glVertex3f(1,1,-1);
			glVertex3f(-1,1,-1);
			
			glVertex3f(-1,1,-1);
			glVertex3f(-1,1,1);
			
			glVertex3f(-1,1,1);
			glVertex3f(1,1,1);
		
			// left
			glVertex3f(-1,1,-1);
			glVertex3f(-1,-1,-1);
			
			glVertex3f(-1,-1,-1);
			glVertex3f(-1,-1,1);
			
			glVertex3f(-1,-1,1);
			glVertex3f(-1,1,1);
			
			// bottom
			glVertex3f(-1,-1,1);
			glVertex3f(1,-1,1);
			
			glVertex3f(-1,-1,-1);
			glVertex3f(1,-1,-1);
			
		glEnd();
	}
	
	/*this->beginShapePoints();
		this->addVertex(0,0,0);
	this->endShape();*/
	/*this->beginShapeLines();
	this->addVertex(0,0,0);
	this->addVertex(100,0,0);
	this->endShape();*/
	
}
