#include "Demo.h"
#include "my_opengl.h"

int init(void);

Demo::Demo(int _width, int _height) {
	if((_height>0) && (_width>0)) {
		this->height=_height;
		this->width=_width;
	} else {
		this->height=DEMOHEIGHT;
		this->width=DEMOWIDTH;
	}

	this->numEventLists=0;
	this->lastEvent=0;
	this->numScenes=0;
	this->lastScene=0;

	this->numTextures=0;

	this->internalError=0; // No error at the beginning!!!!!! :D
	
}

Demo::~Demo (void) {
	int i;
	for(i=0;i<this->numTextures;i++) {
		glDeleteTextures(1,&this->texturesList[i].texID);
	}
}

int Demo::getHeight(void) {
	return this->height;
}

int Demo::getWidth(void) {
	return this->width;
}

void Demo::setSize(int _width, int _height) {
	if((_height>0) && (_width>0)) {
		this->height=_height;
		this->width=_width;
	} 
}
bool Demo::isFullScreen(void) {
	return this->fullscreen;
}

void Demo::setFullScreen(bool _fullscr) {
	this->fullscreen=_fullscr;
}
void Demo::setTitle(char *_title) {
	strcpy(this->title,_title);
}
char *Demo::getTitle(void) {
	return this->title;
}

void Demo::ponOrtopedico(float xres, float yres ) {	
	// Ahora pongo el modo ortho-pedico 
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glViewport(0,0,this->width,this->height);
//	float xrespartido2=xres*0.5f;
//	float yrespartido2=yres*0.5f;
	//glOrtho(-xrespartido2,xrespartido2,-yrespartido2,yrespartido2,0.10f,200.0f);
	glOrtho(-float(xres)/2,float(xres)/2,-float(yres)/2,float(yres)/2,0.10f,200.0f);

	glMatrixMode(GL_MODELVIEW);
}


void Demo::quitaOrtopedico(void) {
	// restauro el modo que hubiera antes
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Demo::ejes(void) {
	glLineWidth(3.0f);
	glColor3f(1.0f,0.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1000.0f,0.0f,0.0f); // X
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(-1000.0f,0.0f,0.0f); // X neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.0f,1.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1000.0f,0.0f); // y
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,-1000.0f,0.0f); // y neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.0f,0.0,1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1000.0f); // z
	glEnd();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xaaaa);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,-1000.0f); // z neg
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0f);
	
}
void Demo::initEventLists(int numEventLists) {
	this->numEventLists = numEventLists;
	this->eventLists = (pEventList*) malloc(sizeof(pEventList) * numEventLists);
}

int Demo::addEventList(char *name) {
	// Creates a new list with that name and returns the id if ok, else -1
	int newId;

	newId=this->lastEvent;

	assert(newId < numEventLists);

	EventList* theEventList = new EventList();
	this->eventLists[newId] = theEventList;

	if(this->eventLists[newId]==NULL) 
		return -1;

	this->getEventListById(newId)->setName(name);

	this->lastEvent++;
	return newId;
}

int Demo::addEvent2List(int listId, float _start, float _length, float _vol) {
	// adds an event to that list (id)
	if((listId>=0) && (listId<this->numEventLists)) {
		this->eventLists[listId]->addEvent(_start, _length, _vol);
	} else {
		return -1;
	}
	return 0;
}

EventList* Demo::getEventListByName(char *name) {
	// returns pointer to the eventlist with that name

	int i;
	for(i=0;i<this->numEventLists;i++) {
		if(strcmp(this->eventLists[i]->getName(),name)==0)
			return this->eventLists[i];
	}
	return NULL;
}

EventList* Demo::getEventListById(int i) {
	// returns pointer to the eventlist with that id
	return this->eventLists[i];
}


int Demo::initSceneList(int _numScenes) {
	// inits the scenes array with given number
	if(_numScenes>0) {
		this->sceneList = (pScene *) malloc(sizeof(pScene)*_numScenes);
		if(this->sceneList == NULL)
			return -1;
		this->sceneStart = (float*) malloc(sizeof(float)*_numScenes);
		this->sceneLength = (float*) malloc(sizeof(float)*_numScenes);

		this->numScenes=_numScenes;
		return 0;
	}
	return -1;
}

int Demo::addScene2List(char *sceneType, char *sceneName, float start, float length ) {
	int i=this->lastScene;
	this->sceneStart[this->lastScene]=start;
	this->sceneLength[this->lastScene]=length;
	this->sceneList[this->lastScene] = this->sceneFactory.createInstance(sceneType); // me da miedo
	this->lastScene++;
	return i;
}

int Demo::play(float _time) {
	int i,j=0;

	float start, end;
	for(i=0;i<this->numScenes;i++) {
		start=this->sceneStart[i];
		end=start + this->sceneLength[i];
		if( (start<=_time) && (end>_time) ) {
			this->sceneList[i]->play(_time);
			j++;
		} 
	}
	return j;
}


pScene Demo::getSceneAt(unsigned int i) {
	return this->sceneList[i];
}

pEffect Demo::createEffect(char *effectType) {
	return this->effectFactory.createInstance(effectType);
}

// Adds a texture to the global textures list by loading it from a filename
TextureImage* Demo::addTexture(char *texturePath, unsigned int id) {
	assert(this->numTextures<TEXTURESLIST_MAX);
	LoadTGA(&this->texturesList[this->numTextures],texturePath);
	this->texturesList[this->numTextures].id=id;
	this->numTextures++;
	return &this->texturesList[this->numTextures-1];
	
}

// Adds a texture to the global textures list by creating it with the 
// specified width and height
TextureImage* Demo::addTexture(GLuint _width, GLuint _height, unsigned int id) {
	TextureImage* myText;
	
	myText = this->getTextureById(id);
	if(myText != NULL) {
		return myText; // si ya existe la devuelvo (Ahi al riesgo!!)
	}
	assert(this->numTextures<TEXTURESLIST_MAX);
	// si no, la creo, o eso intento!!
	this->texturesList[this->numTextures].texID = EmptyTexture(_width,_height);
	this->texturesList[this->numTextures].width = _width;
	this->texturesList[this->numTextures].height = _height;
	this->texturesList[this->numTextures].id = id;
	this->texturesList[this->numTextures].bpp = 32;
	//LoadTGA(&this->texturesList[this->numTextures],texturePath);
	//this->texturesList[this->numTextures].id=id;
	myText = &this->texturesList[this->numTextures];
	this->numTextures++;
	return myText;//&this->texturesList[this->numTextures-1];
}

TextureImage* Demo::getTextureById(unsigned int _id) {
	unsigned int i;
	if(_id>=this->numTextures) {
		return NULL;
	}
	for(i=0;i<this->numTextures;i++) {
		if(this->texturesList[i].id==_id) {
			return &this->texturesList[i];
		}
	}
	return NULL;
}

int Demo::checkGLerror(const char *caller) {
	// TODO: add some logging
	GLenum ret = glGetError();
	char errorString[512];
	strcpy(errorString,caller);
	if(ret!=0) {
		switch(ret) {
			case GL_INVALID_ENUM: strcat(errorString,": Invalid Enum");break;
			case GL_INVALID_VALUE: strcat(errorString,": Invalid Value");break;
			case GL_INVALID_OPERATION: strcat(errorString,": Invalid Operation");break;
			case GL_STACK_OVERFLOW: strcat(errorString,": Stack Overflow");break;
			case GL_STACK_UNDERFLOW: strcat(errorString,": Stack Underflow");break;
			case GL_OUT_OF_MEMORY: strcat(errorString,": Out of memory");break;

		}
		fprintf(stderr, "%s\n", errorString);
		
	}
	this->internalError=0;
	return 0; // No error!
}

int Demo::hasError(void) {
	return this->internalError;
}

