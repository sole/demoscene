#include "ResourceFactory.h"


CResourceFactory::CResourceFactory() {	
}

CResourceFactory::~CResourceFactory () {
}

CResource* CResourceFactory::createInstance(string type) {
	
	CResource* theResource;
	/*if(type=="3dscene") {
		theResource = new CResource3DScene();
		return theResource;
	}*/
	if(type=="empty") {
		theResource = new CResourceEmpty();
		return theResource;
	}
	if(type=="colorplane") {
		theResource = new CResourceColorPlane();
		return theResource;
	}
	if(type=="image") {
		theResource = new CResourceImage();
		return theResource;
	}
	if(type=="imagesequence") {
		theResource = new CResourceImageSequence();
		return theResource;
	}
	if(type=="boxblur") {
		theResource = new CResourceBoxBlur();
		return theResource;
	}
	if(type=="distortpolar") {
		theResource = new CResourceDistortPolar();
		return theResource;
	}
	if(type=="distortripple") {
		theResource = new CResourceDistortRipple();
		return theResource;
	}
	if(type=="distortsine") {
		theResource = new CResourceDistortSine();
		return theResource;
	}
	if(type=="filterdithering") {
		theResource = new CResourceFilterDithering();
		return theResource;
	}
	if(type=="filterflipcolors") {
		theResource = new CResourceFilterFlipColors();
		return theResource;
	}
	if(type=="filterhighpass") {
		theResource = new CResourceFilterHighPass();
		return theResource;
	}
	if(type=="filterlowpass") {
		theResource = new CResourceFilterLowPass();
		return theResource;
	}
	if(type=="filtermidtone") {
		theResource = new CResourceFilterMidTone();
		return theResource;
	}
	if(type=="filtermonotone") {
		theResource = new CResourceFilterMonoTone();
		return theResource;
	}
	if(type=="motionblur") {
		theResource = new CResourceMotionBlur();
		return theResource;
	}
	if(type=="objectdotmatrix") {
		theResource = new CResourceObjectDotMatrix();
		return theResource;
	}
	if(type=="objectterrain") {
		theResource = new CResourceObjectTerrain();
		return theResource;
	}
	if(type=="osstarfield") {
		theResource = new CResourceOSStarField();
		return theResource;
	}
	if(type=="particlesystemsnow") {
		theResource = new CResourceParticleSystemSnow();
		return theResource;
	}
	if(type=="psychocircles") {
		theResource = new CResourcePsychoCircles();
		return theResource;
	}
	if(type=="psychofire") {
		theResource = new CResourcePsychoFire();
		return theResource;
	}
	if(type=="psychoplasma") {
		theResource = new CResourcePsychoPlasma();
		return theResource;
	}
	if(type=="psychowhitenoise") {
		theResource = new CResourcePsychoWhiteNoise();
		return theResource;
	}
	if(type=="radialblur") {
		theResource = new CResourceRadialBlur();
		return theResource;
	}
	if(type=="radialblurimproved") {
		theResource = new CResourceRadialBlurImproved();
		return theResource;
	}
	if(type=="scene10ycubegen") {
		theResource = new CResourceScene10yCubeGen();
		return theResource;
	}
	if(type=="scene10ycubenest") {
		theResource = new CResourceScene10yCubeNest();
		return theResource;
	}
	if(type=="scene10ytunnel") {
		theResource = new CResourceScene10yTunnel();
		return theResource;
	}
	if(type=="scenetgforest") {
		theResource = new CResourceSceneTGForest();
		return theResource;
	}
	if(type=="scenetubebeginning") {
		theResource = new CResourceSceneTubeBeginning();
		return theResource;
	}
	if(type=="scenetubegreetings") {
		theResource = new CResourceSceneTubeGreetings();
		return theResource;
	}
	if(type=="sotgpoints") {
		theResource = new CResourceSotgPoints();
		return theResource;
	}
	// if we arrive here... it means the resource type is unknown so we create a generic one	
	return new CResourceGeneric;
}

