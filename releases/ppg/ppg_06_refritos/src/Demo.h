//: src:Demo.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 29 july 2005  
// Declaration of CDemo class

#ifndef DEMO_H
#define DEMO_H

#include "Effect.h"
#include "Logger.h"
#include "Music.h"
#include "Render.h"
#include "Resource.h"
#include "ResourceFactory.h"
#include "Xml.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

class CDemo {
public:
	CDemo(int _height=-1, int _width=-1);
	~CDemo();
	void setSize(int _height, int _width);
	void setStartTime(float time);
	
	
	// Loading functions & co
	
	int loadScript(string scriptfile);
	int loadScriptConfig(TiXmlElement* node);
	int loadScriptGlobals(TiXmlElement* node);
	bool loadScriptConfigParseParam(TiXmlElement* node);
	int loadScriptResources(TiXmlElement* node);
	bool loadScriptResourcesParseResource(TiXmlElement* node);
	int loadScriptTimeline(TiXmlElement* node);
	bool loadScriptTimelineParseEffect(TiXmlElement* node);
	void loadScriptTimelineReorderByLayer(void);
	string strtolower(string input);
	void loader();
	
	CResource*  getResourceById(string resourceId);
	
	// Logger / tracer
	void setLogging(bool value);
	void trace(string text);
	void trace(double number);
	void setLogIndent(unsigned int value);
	
	// Render system
	CRender Render;
	bool display(void);
	
	
	// status
	bool isPlaying(void);
	
	// The music
	float m_FFT[512]; // for storing (and sharing) current music FFT values
	float getSongPosition();

private:
	// logger/tracer
	bool m_isLogging;
	unsigned int m_logIndent;
	CLogger Logger;
	void logIndent(void);
	
	// Config settings...
	string m_demoName;
	float m_tStart; // when does the demo start??
	
	// The music
	CMusic m_Music;
	
	// Loader image
	unsigned int m_loaderImageTexPos;
	
	
	// The resources
	vector<CResource *> m_Resources;
	CResourceFactory m_ResourceFactory;
	
	// The effects
	vector<CEffect *> m_Effects;
	
	// Misc
	unsigned int m_configNodeCount, m_resourcesNodeCount, m_effectsNodeCount, 
		m_loadedConfigCount, m_loadedResourcesCount, m_loadedEffectsCount;
};

#endif
