//: src:Resource.h
// thisisnotanengine
// @author: Soledad Penades
// @date_start: 30 july 2005  
// Declaration of CResource class

#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include "Resource.h"

#include <string>
using namespace std;

// Include here all the defined-registered resources
#include "ResourceEmpty.h"
#include "ResourceColorPlane.h"
#include "ResourceDistortPolar.h"
#include "ResourceDistortRipple.h"
#include "ResourceDistortSine.h"
#include "ResourceFilterDithering.h"
#include "ResourceFilterFlipColors.h"
#include "ResourceFilterHighPass.h"
#include "ResourceFilterLowPass.h"
#include "ResourceFilterMidTone.h"
#include "ResourceFilterMonoTone.h"
#include "ResourceGeneric.h"
#include "ResourceImage.h"
#include "ResourceImageSequence.h"
#include "ResourceBoxBlur.h"
#include "ResourceMotionBlur.h"
#include "ResourceObjectTerrain.h"
#include "ResourceParticleSystemSnow.h"
#include "ResourcePsychoCircles.h"
#include "ResourcePsychoFire.h"
#include "ResourcePsychoPlasma.h"
#include "ResourcePsychoWhiteNoise.h"
#include "ResourceRadialBlur.h"
#include "ResourceRadialBlurImproved.h"
#include "ResourceSceneTGForest.h"
#include "ResourceSceneTubeBeginning.h"
#include "ResourceSceneTubeGreetings.h"
#include "ResourceSotgPoints.h"

// end of registered scenes

class CResourceFactory {
public:
	CResourceFactory() ;
	~CResourceFactory() ;
	CResource *createInstance(string type);   
};

#endif
