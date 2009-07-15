#include "Demo.h"
/**
 * Default constructor
 */
CDemo::CDemo(int _width, int _height) {
	// Init
	// Set member variables to default values
	this->m_isLogging = true;
	this->m_logIndent = 0;
	this->trace("Demo object created");
	this->m_tStart = 0;
	
	m_configNodeCount=1;
	m_resourcesNodeCount=1;
	m_effectsNodeCount=1;
	m_loadedConfigCount=0;
	m_loadedResourcesCount=0;
	m_loadedEffectsCount=0;
	
	
	if((_height>0) && (_width>0)) {
		this->Render.setSize(_width,_height);
	} else {
		this->Render.setSize(640, 480);
	}

	// Initialize graphics system . . . . . . . . . . . .
	this->trace("Initializing Render");
	this->Render.init();
	this->trace("... render initialized");
	
	// Initialize music/sound system . . . . . . . . . . . .
	this->trace("Initializing Sound");
	this->m_Music.initSound();
	this->trace("... sound initialized");
	
}

CDemo::~CDemo (void) {
	unsigned int i;
	
	this->trace("Ending demo");
	// Deinitialize graphics system . . . . . . . . . . . . 
	trace("Ending render");
	this->Render.deinit();
	
	// Deinitialize sound system........
	this->m_Music.stopSound();
	trace("Ending sound");
	
	
	// TODO : free resources here
	trace("Freeing effects");
	for(i=0; i<this->m_Effects.size(); i++) {
		this->m_Effects[i]->deInit();
	}
	trace("Freeing resources");
	for(i=0; i<this->m_Resources.size(); i++) {
		this->m_Resources[i]->deInit();
	}
	/*int i;
	for(i=0;i<this->numTextures;i++) {
		glDeleteTextures(1,&this->texturesList[i].texID);
	}*/
	trace("Demo ended.");
}

void CDemo::setStartTime(float time)
{
	this->m_tStart = time;
}

/**
 * Set logging state
 */
void CDemo::setLogging(bool value) {
	// value == false -- no logging
	// value == true -- logging
	this->m_isLogging = value;
}

/**
 * Log/trace something
 */
void CDemo::trace(string text) {
	// Example of use: this->trace("Arrikitan");
	if(m_isLogging) {
		this->logIndent();
		*this->Logger.os << text << endl;
	}
}
void CDemo::trace(double number) {
	// Example of use: this->trace(123);
	if(m_isLogging) {
		this->logIndent();
		*this->Logger.os << number << endl;
	}
}
/**
* Set the logging indent
*/
void CDemo::setLogIndent(unsigned int value) {
	// Example of use: this->setIndent(2); -- will output 2 spaces before every logged line
	this->m_logIndent = value;
}

/**
* Output logging indent
 * This is called internally by the trace functions
 */
void CDemo::logIndent(void) {
	for(unsigned int i=0; i<this->m_logIndent;i++) {
		*this->Logger.os << " ";
	}
}

/**
 * Loads the demo script
 */
int CDemo::loadScript(string scriptfile) {
	TiXmlDocument* doc;
	int recognizedCount;
	
	this->trace("+ loadScript start --");
	this->setLogIndent(2);
	
	// First we try to load the script via tinyxml
	doc = new TiXmlDocument(scriptfile.c_str());
	if(!doc->LoadFile()) {
		// KK!
		this->trace("Error when loading script " + scriptfile);
		return -1;
	}
	// Find root element . . . . . . . . . . . . . . . . . . . . . 
	TiXmlElement* root = doc->FirstChildElement( "script" );
	if (!root ) {
		trace("ERROR: <script> node NOT found!"); return -1;
	}
	
	// Let's load demo configuration -- the <config> section . . . . . . . . . . . . . . . . . . . . . 
	TiXmlElement* config = root->FirstChildElement("config");
	if (!config) {
		trace("ERROR: <config> node NOT found!"); return -1;
	}
	unsigned int numConfigNodes = XmlGetChildCount(config);
	this->m_configNodeCount = numConfigNodes;
	recognizedCount = loadScriptConfig(config);
	trace("<config> node count"); 	trace(numConfigNodes);
	trace("<config> recognized count"); trace(recognizedCount);
	
	// Check that music was loaded otherwise we better stop and complain
	if(!this->m_Music.isLoaded()) {
		trace("loadScript: ERROR: Music was not loaded");
		return -1;
	}

		// Load the loader image
	this->m_loaderImageTexPos = Render.loadTexture("data/loader.png");
	
	// Now load the globals
	TiXmlElement* globals = root->FirstChildElement("globals");
	loadScriptGlobals(globals);
	
	// Let's load the resources . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
	TiXmlElement* resources = root->FirstChildElement("resources");
	if (!resources) {
		trace("ERROR: <resources> node NOT found!"); return -1;
	}
	unsigned int numResourcesNodes = XmlGetChildCount(resources);
	this->m_resourcesNodeCount = numResourcesNodes;
	recognizedCount = loadScriptResources(resources);
	
	trace("<resources> node count"); 	trace(numResourcesNodes);
	trace("<resources> recognized count"); trace(recognizedCount);
	
	// Let's load the timeline == the effects . . . . . . . . . . . . . . . . . . . . . . . .
	TiXmlElement* timeline = root->FirstChildElement("timeline");
	if (!timeline) {
		trace("ERROR: <timeline> node NOT found!"); return -1;
	}
	unsigned int numTimelineNodes = XmlGetChildCount(timeline);
	this->m_effectsNodeCount = numTimelineNodes;
	recognizedCount = loadScriptTimeline(timeline);
	trace("<timeline> node count"); 	trace(numTimelineNodes);
	trace("<timeline> recognized count"); trace(recognizedCount);
	
	// End . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
	this->setLogIndent(0);
	this->trace("+ loadScript end --");
	
	return 0;
}
/**
 * load the config values
 * returns the number of recognized parameters
 */
int CDemo::loadScriptConfig(TiXmlElement* node) {
	unsigned int nRecognizedParams = 0;
	TiXmlElement* list = node->FirstChildElement();
	
	while(list) {
		// Parse param attribute
		if(loadScriptConfigParseParam(list))
			nRecognizedParams++;
		list = list->NextSiblingElement();
	}
	return nRecognizedParams;
}
/**
* parse config values and do appropiate action (setting values etc)
 * returns 1 if recognized param, 0 if not
 */
bool CDemo::loadScriptConfigParseParam(TiXmlElement* node) {
	string name, value;
	bool isKnown=false; // is this param known?
	// I don't want to type so much :-P!!
#define KN (isKnown = true )
	
	// Get the "name" attribute and attribute value
	name = strtolower(node->Attribute("name"));
	// do name 'case insensitive' so it does not matter the case
	// This is quite inefficient but should work
	value = node->Attribute("value");
	
	trace("loadScriptConfigParseParam: " + name + ", value=" + value);
	
	// Demo name
	if(name=="name") {
		this->m_demoName = value; KN;
	}
	
	// Fullscreen?
	if(name=="fullscreen") {
		value=="yes" ? this->Render.setFullScreen(true) : this->Render.setFullScreen(false) ; KN;
	}
	
	// rendertotexturex
	if(name=="rendertotexturex") {
		this->Render.setRenderToTextureX((unsigned int) atoi(value.c_str())); KN;
	}
	
	// rendertotexturey
	if(name=="rendertotexturey") {
		this->Render.setRenderToTextureY((unsigned int) atoi(value.c_str())); KN;
	}
	
	// screenwidth
	if(name=="screenwidth") {
		this->Render.setWidth((int) atoi(value.c_str())); KN;
	}
	
	// screenheight
	if(name=="screenheight") {
		this->Render.setHeight((int) atoi(value.c_str())); KN;
	}
	
	// song
	if(name=="song") {
		this->m_logIndent+=2;
		trace("Loading song");
		if(!this->m_Music.loadMP3(value.c_str())) {
			trace("music: NOT loaded");
		}
		
		this->m_logIndent-=2;
		KN;
	}
	
	// Demo start time
	if(name=="time_start") {
		this->m_tStart = (float) atof(value.c_str()); KN;
	}
	
	
	
#undef KN
	return isKnown;
}

/**
 * load the global values
 * returns the number of recognized children
 */
int CDemo::loadScriptGlobals(TiXmlElement* node) {
	unsigned int nRecognizedChildrens = 0;
	
	TiXmlElement* blendings = node->FirstChildElement("blendings");
	TiXmlElement* blending;
	string blendName, blendSrc, blendDst;
	//cout << "load script globals" << endl;
	if(blendings) {
		blending = blendings->FirstChildElement();
	}
	while(blending) {
		// Send each blend mode to the Render
		blendName = blending->Attribute("name");
		blendSrc = blending->Attribute("src");
		blendDst = blending->Attribute("dst");
		//cout << "add blending " << blendName << " " << blendSrc << " " << blendDst << endl;
		this->Render.addBlending(blendName, blendSrc, blendDst);
		
		nRecognizedChildrens++;
		blending = blending->NextSiblingElement();
	}
	return nRecognizedChildrens;
}

/**
* load the resources elements
 * returns the number of recognized resources
 */
int CDemo::loadScriptResources(TiXmlElement* node) {
	unsigned int nRecognized = 0;
	TiXmlElement* list = node->FirstChildElement();
	
	while(list) {
		// Parse each resource
		if(loadScriptResourcesParseResource(list))
			nRecognized++;
		this->m_loadedResourcesCount++;
		this->loader();
		list = list->NextSiblingElement();
	}
	return nRecognized;
}

/**
* parse resource
 * returns 1 if recognized, 0 if not
 */
bool CDemo::loadScriptResourcesParseResource(TiXmlElement* node) {
	string name, value, id, type;
	bool isKnown=false; // is this resource known?
						// I don't want to type so much :-P!!
#define KN (isKnown = true )
	CResource *theResource;
	// Get the "type" attribute
	type = strtolower(node->Attribute("type"));
	// Get the "id" attribute
	id = strtolower(node->Attribute("id"));
	
	// cout << "loadScriptResourcesParseResources: type " << type << ", id=" << id;
	
	theResource = m_ResourceFactory.createInstance(type);
	if(theResource->getType()!="CResourceGeneric") {
		KN;
	}
	
	if(isKnown) {
		theResource->setRenderer(&this->Render);
		theResource->setDemo(this);
		theResource->setId(id);
		
		// Set default values for all resources so we dont repeat code on all of them
		theResource->setCustomBlending(-1); // No custom blending
		theResource->setParam("r","1");
		theResource->setParam("g","1");
		theResource->setParam("b","1");
		theResource->setParam("a","1");
		
		// Also pass all the attributes to the object
		// so it can 'autoconfigure' properly with the known params
		TiXmlAttribute *attribute = node->FirstAttribute();
		string attributeName, attributeValue;
		while(attribute) {
			attributeName = attribute->Name();
			attributeValue = attribute->Value();
			theResource->setParam(attributeName, attributeValue);
			attribute = attribute->Next();
		}
		// Find if it has more info: a <params> list as a child
		TiXmlElement *child = node->FirstChildElement();
		string paramName, paramValue;
		while(child) {
			// Each param has name="name of the param" and value="value of the param"
			paramName=""; paramValue="";
			paramName = child->Attribute("name");
			paramValue = child->Attribute("value");
			if(paramName!="" && paramValue!="") {
				theResource->setParam(paramName, paramValue);
			}
			child = child->NextSiblingElement();
		}
		// Once all the attributes for the resource have been set up we init it
		// so we can be sure that it gets initialized
		theResource->init();
		// And we store the point to the Resource in our resources list
		this->m_Resources.push_back(theResource);
	}
#undef KN
	return isKnown;
}

/**
 * load the timeline elements
 * returns the number of recognized effects
 */
int CDemo::loadScriptTimeline(TiXmlElement* node) {
	unsigned int nRecognizedParams = 0;
	TiXmlElement* list = node->FirstChildElement();
	
	while(list) {
		// Parse param attribute
		if(loadScriptTimelineParseEffect(list))
			nRecognizedParams++;
		this->m_loadedEffectsCount++;
		list = list->NextSiblingElement();
	}
	// Call to reorder layers
	this->loadScriptTimelineReorderByLayer();
	return nRecognizedParams;
}

/**
 * parse timeline effects
 * returns 1 if recognized effect, 0 if not
 * In this case, "recognized" means that there's a resource which has
 * an id equal to the name of the effect
 * So for each new effect we have to iterate the list of resources to
 * check whether it exists or not. In the worse case the cost will be
 * N effects x M resources
 */
bool CDemo::loadScriptTimelineParseEffect(TiXmlElement* node) {
	string resource, value;
	float fadeout, fadein, length;
	unsigned int layer;
	CEffect *theEffect;
	bool isKnown=false; // is this effect's resource known?
						// I don't want to type so much :-P!!
#define KN (isKnown = true )
	
	// Get the associated "resource" as attribute and attribute value
	resource = strtolower(node->Attribute("resource"));
	
	// Look for a resource with that id
	int resourcesNum = this->m_Resources.size();
	
	for(int i=0; i<resourcesNum; i++) {
		if(resource==this->m_Resources[i]->getId()) {
			// Create new effect
			theEffect = new CEffect();
			// Set appropiate values there
			theEffect->setResource(this->m_Resources[i]);
			
			TiXmlAttribute *attribute = node->FirstAttribute();
			string attributeName, attributeValue, attributeModifier, attributeNameTmp, attributeValueTmp;
			string paramName, paramValue, paramModifier;
			fadein=0;
			fadeout=0;
			length=0;
			layer = 0; // will be 0 by default - except if it's specified
			while(attribute) {
				attributeName = attribute->Name();
				value = attribute->Value();
				trace("att " + attributeName + " value " + value);
				
				if(attributeName=="start") {
					theEffect->setStart(attribute->DoubleValue());
				} else if(attributeName=="length") {
					length = (float) attribute->DoubleValue();
					theEffect->setLength(length);
				} else if(attributeName=="fadeout") {
					fadeout = (float) attribute->DoubleValue();
					theEffect->setFadeOut(fadeout);
				} else if(attributeName=="fadein") {
					fadein = (float) attribute->DoubleValue();
					theEffect->setFadeIn(fadein);
				} else if(attributeName=="layer") {
					layer = (unsigned)attribute->IntValue();
				}				
				
				attribute = attribute->Next();
			}
			// Parse and apply effect parameters
			TiXmlElement* params = node->FirstChildElement();
			int iDiota; // this var is useless
			bool bHasModifier = false;
			while(params) {
				attributeModifier = "";
				attributeName = params->Attribute("name");
				attributeValue = params->Attribute("value");
				if(params->QueryIntAttribute("modifier", &iDiota)!=TIXML_NO_ATTRIBUTE) {
					attributeModifier = params->Attribute("modifier");
					bHasModifier = true;
				}
				//attributeModifier = params->Attribute("modifier");
				theEffect->setResourceAttribute(attributeName, attributeValue);
				if(bHasModifier)
					theEffect->setResourceAttributeModifier(attributeName, attributeModifier);
				bHasModifier = false;
				params = params->NextSiblingElement();
			}
			
			// warn if error!
			if( (fadein+fadeout) > length) {
				trace("*** GUARNIN! effect linked with "+ resource + " fadeout&fadein > effect length");
				trace(fadein);trace(fadeout);trace(length);
			}
			// set the calculated layer
			theEffect->setLayer(layer);
			KN;
			break;
		}
	}
	
	if(!isKnown) {
		trace("loadScriptTimelineParseEffect: resource with id " + resource + " NOT found");	
	} else {
		theEffect->setFFT(this->m_FFT);
		this->m_Effects.push_back(theEffect);
	}
#undef KN
	return isKnown;
}

/**
 * Reorders the effects by layers so it'll easy to draw them thereafter 
 */
void CDemo::loadScriptTimelineReorderByLayer(void) {
	//trace("loadScriptTimelineReorderByLayer...");
	CEffect* tempEffect;
	int i;
	int effectsCount = this->m_Effects.size() - 1;
	// cout << "hay " << effectsCount << endl;
	for(i=0; i < effectsCount; i++) {
		// case where effect[n].layer > effect[n+1].layer
		// so it needs reordering by interchanging effects
		if(this->m_Effects[i]->getLayer() > this->m_Effects[i+1]->getLayer()) {
			tempEffect = this->m_Effects[i];
			this->m_Effects[i] = this->m_Effects[i+1];
			this->m_Effects[i+1] = tempEffect;
		}
	}
	
	// Once finished let's check if there's need for another reorder
	bool needReorder = false;
	for(i=0; i<effectsCount; i++) {
		if(this->m_Effects[i]->getLayer() > this->m_Effects[i+1]->getLayer()) {
			needReorder = true; break;
		}
	}
	// and then if needed, reorder again
	if(needReorder) {
		this->loadScriptTimelineReorderByLayer();
	}
}

void CDemo::loader() {
	float ypos, ypos2, zpos;
	float total = 
		((float)m_loadedResourcesCount)/((float)m_resourcesNodeCount)*50 +
		((float)m_loadedEffectsCount)/((float)m_effectsNodeCount)*50;
	total /= 50;	
		
	float width = Render.getWidth()*0.5;
	float height =Render.getHeight()*0.5;
	Render.setColor(1,1,1,1);
	
	Render.orthoSet();
	
	Render.enableTexture();
	Render.bindTexture(m_loaderImageTexPos);
	
	Render.setModelMatrix();
	Render.pushMatrix();
	
	Render.beginShapeQuads();
	
	Render.setTextureCoord(0,0);
	Render.addVertex(-width,-height);
	
	Render.setTextureCoord(1*total,0);
	Render.addVertex(width,-height);
	
	Render.setTextureCoord(1*total,1*total);
	Render.addVertex(width, height);
	
	Render.setTextureCoord(0,1);
	Render.addVertex(-width,height);
	
	Render.endShape();
	
	Render.disableTexture();
	
	glLineStipple(1, 0x00FF);
	glEnable(GL_LINE_STIPPLE);
	
	// draw the line
	Render.enableBlend();

	Render.setLineWidth(15);
	Render.setColor(0,1,0,1);
	ypos = 0;
	float bar_start = -(Render.getWidth()*0.5f - Render.getWidth()*0.25f);
	float bar_length = Render.getWidth()*0.5f;
	
	Render.translate(bar_start, -Render.getHeight()*0.35f, 0);
	Render.beginShapeLines();		
		Render.addVertex(0,ypos);
		Render.addVertex(total*bar_length,ypos);		
	Render.endShape();
	
	Render.setModelMatrix();
	Render.popMatrix();
	
	Render.disableBlend();
	
	glDisable(GL_LINE_STIPPLE);
	
	Render.orthoUnset();
	
	Render.flush();
	Render.swapBuffers();
	
}

/**
* Convert an string to lowercase - this is an auxiliary function used for comparing loaded strings and attributes names
*/
string CDemo::strtolower(string input) {
	for (int j=0; j<input.length(); ++j)
	{
		input[j]=tolower(input[j]);
	}
	return input;
}

/**
*
*/
bool CDemo::isPlaying(void) {
	return true;
}

// Return song position in milliseconds
float CDemo::getSongPosition()
{
	if(m_Music.isLoaded())
	{
		return m_Music.getMilliseconds();
	}
	return 0;
}

/**
*
 */
bool CDemo::display(void) {
	float t_Start, t_End;
	float t_Now;

	// Check if music was started - else start it
	if(!this->m_Music.isPlaying()) {
		trace("display: Start playing song");
		m_Music.playSound();
		m_Music.setMP3Pos(m_tStart);
		m_Music.playMP3();
	}
	
	// Check if music has finished
	if(m_Music.hasFinished()) {
		trace("display: End of song");
		return false;
	}
	
	t_Now = m_Music.getSeconds();
	m_Music.getFFTNatural(this->m_FFT);
	
	for(int i=0;i<this->m_Effects.size(); i++)
	{
		if(m_Effects[i]->isPlaying(t_Now))
		{
			m_Effects[i]->play(t_Now);
		}
	}

	
	this->Render.flush();
	this->Render.swapBuffers();
	
	return true;
}

CResource* CDemo::getResourceById(string resourceId) {
	CResource* res = NULL;
	for(unsigned int i=0; i<this->m_Resources.size(); i++) {
		if(this->m_Resources[i]->getId()==resourceId) {
			res = this->m_Resources[i];
			break;
		}
	}
	return res;
}
