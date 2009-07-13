#include "ScriptLoader.h"

ScriptLoader::ScriptLoader() {
    strcpy(this->scriptFile, "");
}

ScriptLoader::ScriptLoader(const char *filename) {
    this->setFilename(filename);
}

ScriptLoader::~ScriptLoader() {
}

int ScriptLoader::setFilename(const char *filename) {
    if (filename != NULL) {
        strcpy(this->scriptFile, filename);
    }
    return 0;
}

int ScriptLoader::init(void) {
    if (strlen(this->scriptFile) <= 0) {

        return -1;
    } else {
        this->scriptHandle = fopen(this->scriptFile, "r");
        if (this->scriptHandle == NULL) {

            return -1;
        } else {

            // let's try to open the script
            this->doc = new TiXmlDocument(this->scriptFile);
            bool loadOkay;
            loadOkay = this->doc->LoadFile();
            if (loadOkay == 0) {
                // KK! it coudn�t parse the file!!
                return -1;
            }

            return 0;
        }
    }
}

int ScriptLoader::load(void) {

    if (this->init() != 0) {
        return -1;
    }
    loader(0);
    /* Load Events */
    this->loadEvents();
    loader(33);
    /* Load Scenes */
    this->loadScenes();
    loader(66);


    return 1;
}

int ScriptLoader::loadEvents(void) {
    char eventListName[256];
    int numEvents, i, j, totalEventsNum;
    float start, length, vol;
    float v;

    totalEventsNum = 0;
    
    TiXmlElement* root = this->doc->FirstChildElement("script");
    if (root) {
        TiXmlElement *eventlists = root->FirstChildElement("eventlists");
        // Let's find the event lists
        if (eventlists) {
            // Ok, let�s go!
            int numEventlists;
            numEventlists = atoi(eventlists->Attribute("num"));

            // Create the event lists!
            miDemo->initEventLists(numEventlists);
            // First Event list!!
            i = 0;
            TiXmlElement *list = eventlists->FirstChildElement();
            while (list) {
                j = 0;

                strcpy(eventListName, list->Attribute("name"));
                numEvents = atoi(list->Attribute("num"));

                int eventListId = miDemo->addEventList(eventListName);

                // TODO set the name of the eventlist
                TiXmlElement *event = list->FirstChildElement();
                while (event)
                {
                    // event: start, length, vol
                    start = atof(event->Attribute("start"));
                    length = atof(event->Attribute("length"));
                    vol = atof(event->Attribute("vol"));

                    miDemo->addEvent2List(eventListId, start, length, vol);

                    // Let's go for the next one...
                    event = event->NextSiblingElement();
                    j++;
                    totalEventsNum++;

                    //v = 50 * (i + (float(j) / numEvents)) / numEventlists;
                    //loader(v);
                }
                // This is way faster than updating the loader
                // each time a new event has been identified
                loader(50 * (float(i) / numEventlists));
                list = list->NextSiblingElement();
                i++;
            }
        }
    }

    return 0;
}

int ScriptLoader::loadScenes(void) {
    char sceneName[256], sceneType[256], effectName[256], effectType[256], effectEventList[256], paramName[256], attribName[256];
    TiXmlElement *root, *scenes, *scene, *effects, *effect, *params, *param;
    int numScenes = 0, totalScenes = 0, numEffects = 0, numParams, numAttribs;
    float sceneStart, sceneLength, paramVal;
    unsigned int iscene = 0;

    pScene theScene;

    root = this->doc->FirstChildElement("script");
    if (root) {
        scenes = root->FirstChildElement("scenes");
        // Let's load the scenes
        if (scenes) {
            numScenes = atoi(scenes->Attribute("num"));

            // create the scenes...
            miDemo->initSceneList(numScenes);

            scene = scenes->FirstChildElement();

            while (scene) {
                // name="scene01" type="SCIntro" start="0" length="100"
                strcpy(sceneName, scene->Attribute("name"));
                strcpy(sceneType, scene->Attribute("type"));
                sceneStart = (float) atof(scene->Attribute("start"));
                sceneLength = (float) atof(scene->Attribute("length"));

                // create the scene!
                iscene = miDemo->addScene2List(sceneType, sceneName, sceneStart, sceneLength);
                theScene = miDemo->getSceneAt(iscene); // iscene is the index of the last scene created
                theScene->setSceneName(sceneName);

                // read the scene effects
                effects = scene->FirstChildElement("effects");
                if (effects) {
                    numEffects = atoi(effects->Attribute("num"));

                    // Initialize effects list of this scene
                    theScene->initEffectsList(numEffects);

                    // first effect of this scene?
                    effect = effects->FirstChildElement("effect");
                    while (effect) {
                        // effect: name, type
                        strcpy(effectName, effect->Attribute("name"));
                        strcpy(effectType, effect->Attribute("type"));
                        strcpy(effectEventList, effect->Attribute("eventlist"));


                        // add/create effect
                        pEffect theEffect = miDemo->createEffect(effectType);

                        // Set the eventlist
                        theEffect->setEventList(miDemo->getEventListByName(effectEventList));
                        theEffect->setName(effectName);

                        // Has it params?
                        params = effect->FirstChildElement("params");
                        if (params) {
                            numParams = atoi(params->Attribute("num"));

                            param = params->FirstChildElement("param");
                            while (param) {
                                numAttribs = 0;
                                TiXmlAttribute *attribute;

                                attribute = param->FirstAttribute();
                                strcpy(paramName, attribute->Value());

                                attribute = attribute->Next();

                                while (attribute) {
                                    paramVal = (float) this->getRealValue(attribute->Value());
                                    strcpy(attribName, attribute->Name());

                                    // add the param(s) attribute(s) to the effect
                                    theEffect->setParam(paramName, attribName, paramVal);
                                    attribute = attribute->Next();
                                    numAttribs++;

                                }


                                param = param->NextSiblingElement();
                            }
                        }

                        // Add the effect to the scenelist
                        theScene->addEffect2List(theEffect);


                        effect = effect->NextSiblingElement();
                    }
                } else {

                    theScene->setNumEffects(0);
                }
                theScene->init();
                scene = scene->NextSiblingElement();
                totalScenes++;
                float v = 33 + ((float) totalScenes / (float) numScenes)*33;
                loader(v);
            }

        }
    }
    return 0;
}

float ScriptLoader::glConstant2Value(const char *glConstant) {
    int i;

    static const char* vGlCstNames[] = {
        /* BlendingFactorDest */
        "GL_ZERO",
        "GL_ONE",
        "GL_SRC_COLOR",
        "GL_ONE_MINUS_SRC_COLOR",
        "GL_SRC_ALPHA",
        "GL_ONE_MINUS_SRC_ALPHA",
        "GL_DST_ALPHA",
        "GL_ONE_MINUS_DST_ALPHA",
        /* BlendingFactorSrc */
        "GL_DST_COLOR",
        "GL_ONE_MINUS_DST_COLOR",
        "GL_SRC_ALPHA_SATURATE"

    };
    static float vGlCstValues[] = {
        0,
        1,
        0x0300,
        0x0301,
        0x0302,
        0x0303,
        0x0304,
        0x0305,
        0x0306,
        0x0307,
        0x0308
    };

    for (i = 0; i < SL_NUM_GL_CONSTANTS; i++) {
        if (strcmp(vGlCstNames[i], glConstant) == 0) {
            return vGlCstValues[i];
        }
    }
    return CACAFEA;
}

float ScriptLoader::getRealValue(const char *strValue) {
    float tmpVal = this->glConstant2Value(strValue);
    if (tmpVal == CACAFEA) {
        return atof(strValue);
    } else {
        return tmpVal;
    }
}
