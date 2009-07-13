#include "Scene3D.h"

Scene3D::Scene3D() {
    this->m_numGeomObjects = 0;
    this->m_numLightObjects = 0;
}

Scene3D::~Scene3D() {
    // TODO: free memory...
}

void Scene3D::setNumGeomObjects(unsigned int num) {
    this->m_numGeomObjects = num;
}

int Scene3D::initGeomObjects(void) {
    this->m_geomObjectsList = (GeomObject *) (malloc(this->m_numGeomObjects * sizeof (GeomObject)));

    if (this->m_geomObjectsList == NULL) {
        return -1;
    }
    return 0;
}

void Scene3D::setNumLightObjects(unsigned int num) {
    this->m_numLightObjects = num;
}

int Scene3D::initLightObjects(void) {
    this->m_lightObjectsList = (LightObject *) (malloc(this->m_numLightObjects * sizeof (LightObject)));

    if (this->m_lightObjectsList == NULL) {
        return -1;
    }
    return 0;
}

// Loading files

int Scene3D::loadFromFile(const char *filepath) {
    assert(filepath != NULL);
    int res;

    this->fh = fopen(filepath, "r");
    if (this->fh == NULL) {
        return -1;
    }

    res = this->fileGetNumberofGeomObjects();
    if (res > 0) {
        this->setNumGeomObjects(res);
        this->initGeomObjects();
    }
    res = this->fileGetNumberofLightObjects();
    if (res > 0) {
        this->setNumLightObjects(res);
        this->initLightObjects();
    }
    // Let�s load the real data...
    rewind(this->fh);
    char s[4096];
    unsigned int geomObjIndex = 0, lightObjIndex = 0;
    while (!feof(this->fh)) {
        fgets(s, 4096, this->fh);
        s[strlen(s) - 1] = '\0'; // this way we remove the \n char which is so annoying!
        if (strstr(s, "*GEOMOBJECT {")) {
            this->loadGeomObjFromFile(geomObjIndex);
            geomObjIndex++;
        }
        if (strstr(s, "*LIGHTOBJECT {")) {
            this->loadLightObjFromFile(lightObjIndex);
            lightObjIndex++;
        }
    }
    return 0;
}

int Scene3D::fileGetNumberofGeomObjects(void) {
    if (this->fh == NULL) return -1;

    rewind(this->fh);
    // We are going to go thru file contents searching each definition of GeomObject
    // Each time we find one we'll increment the counter
    // I know this sucks but... who cares
    int times = 0;
    char s[4096];
    while (!feof(this->fh)) {
        fgets(s, 4096, this->fh);
        
        if (strstr(s, "*GEOMOBJECT {")) {
            times++;
        }
    }
    return times;
}

// Good to know: this loader is horrible
int Scene3D::loadGeomObjFromFile(unsigned int index) {
    char s[4096], t[255];
    char nodeName[255], dummy[255];
    unsigned int i, v1, v2, v3;
    unsigned int numvert, numfaces, temp;
    char s1[255], s2[255], s3[255], s4[255];
    float x, y, z;

    while (!feof(this->fh)) {
        // Read and remove the last \n
        fgets(s, 4096, this->fh);
        s[strlen(s) - 1] = '\0';
		
        // Node name?
        if (strstr(s, "*NODE_NAME")) 
        {
            sscanf(s, "\t%s %s", dummy, nodeName);
            for (i = 0; i < strlen(nodeName) - 1; i++) {
                nodeName[i] = nodeName[i + 1];
            }
            nodeName[strlen(nodeName) - 2] = '\0';
			continue;
        }
        // Node transformation matrix?
        if (strstr(s, "*NODE_TM {")) {
            //*NODE_NAME "GeoSphere01"
            fgets(s, 4096, this->fh);
            //*INHERIT_POS 0 0 0
            fgets(s, 4096, this->fh);
            //*INHERIT_ROT 0 0 0
            fgets(s, 4096, this->fh);
            //*INHERIT_SCL 0 0 0
            fgets(s, 4096, this->fh);
            //*TM_ROW0 1.0000	0.0000	0.0000
            //*TM_ROW1 0.0000	-0.0000	1.0000
            //*TM_ROW2 0.0000	-1.0000	-0.0000
            //*TM_ROW3 -0.2463	-0.0000	0.2463
            fgets(s, 4096, this->fh);
            fgets(s, 4096, this->fh);
            fgets(s, 4096, this->fh);
            fgets(s, 4096, this->fh);
            //*TM_POS -0.2463	-0.0000	0.2463
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f %f %f", t, &x, &y, &z);
            this->m_geomObjectsList[index].setTMPos(x, y, z);
            //*TM_ROTAXIS -1.0000	0.0000	0.0000
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f %f %f", t, &x, &y, &z);
            this->m_geomObjectsList[index].setTMRotAxis(x, y, z);
            //*TM_ROTANGLE 1.5708
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f", t, &x);
            this->m_geomObjectsList[index].setTMRotAngle(x);
            //*TM_SCALE 1.0000	1.0000	1.0000
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f %f %f", t, &x, &y, &z);
            this->m_geomObjectsList[index].setTMScale(x, y, z);
            //*TM_SCALEAXIS 0.0000	0.0000	0.0000
            fgets(s, 4096, this->fh);
            //*TM_SCALEAXISANG 0.0000*/
            fgets(s, 4096, this->fh);
            //}
            fgets(s, 4096, this->fh);
            continue;
        }
        // Node mesh?
        if (strstr(s, "*MESH {")) {
            // Timevalue // TODO: Use this for something if needed
            fgets(s, 4096, this->fh);

            // mesh num vertex
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %d", s, &numvert);
            this->m_geomObjectsList[index].setMeshNumVertex(numvert);
            this->m_geomObjectsList[index].initMeshVertexList();

            // mesh num faces
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %d", s, &numfaces);
            this->m_geomObjectsList[index].setMeshNumFaces(numfaces);
            this->m_geomObjectsList[index].initMeshFacesList();
            this->m_geomObjectsList[index].initMeshFacesNormalList();

            // vertexlist
            // Leo la linea que debe decir VERTEXLIST
            fgets(s, 4096, this->fh);

            // Ahora a leer los vertices!
            for (i = 0; i < numvert; i++) {
                fgets(s, 4096, this->fh);
                sscanf(s, "%s %d %f %f %f", t, &temp, &x, &y, &z);
                this->m_geomObjectsList[index].setMeshVertexAt(i, x, z, y, 0.0);
            }
            // fin de vertices (})
            fgets(s, 255, this->fh);
            // fin mesh vertex...

            // facelist
            // Leo la linea que debe decir FACELIST
            fgets(s, 4096, this->fh);

            // Ahora a leer las caras!!
            for (i = 0; i < numfaces; i++) {
                fgets(s, 4096, this->fh);
                sscanf(s, "%s %d %s %s %d %s %d %s %d", t, &temp, s1, s2, &v1, s3, &v2, s4, &v3);
                this->m_geomObjectsList[index].setMeshFaceAt(i, v1, v2, v3);
            }
            // fin de faces (})
            fgets(s, 255, this->fh);
            // fin mesh faces...


            // TODO Texture vertex

            // face normals
            // Leo la linea que debe decir FACELIST
            while (!strstr(s, "*MESH_NORMALS {")) {
                fgets(s, 4096, this->fh);
            }
            if (strstr(s, "*MESH_NORMALS {")) {
                // Ahora a leer las normales a caras!!
                for (i = 0; i < numfaces; i++) {
                    fgets(s, 4096, this->fh);
                    // *MESH_FACENORMAL 0	0.0000	0.0000	-1.0000
                    sscanf(s, "%s %d %f %f %f", t, &temp, &x, &y, &z); // Max intercambia z e y!!
                    int rdo = this->m_geomObjectsList[index].setMeshNormalAt(i, x, y, z, 0.0);
                    // tres fgets para tres lineas un poco inutilizadas
                    fgets(s, 255, this->fh);
                    fgets(s, 255, this->fh);
                    fgets(s, 255, this->fh);
                    sprintf(t, "%d %f %f %f\n", i, x, y, z);
                }



                // fin de faces (})
                fgets(s, 255, this->fh);
                // fin mesh faces...
            }
           
            continue;
        }
        if (strstr(s, "*WIREFRAME_COLOR")) {
            // wireframe color
            sscanf(s, "%s %f %f %f", t, &x, &y, &z);
            this->m_geomObjectsList[index].setWireframeColor(x, y, z, 1);
            continue;
        }
        /*if (strcmp(s, "}")) {
            // End of geomobject!
            printf("end of go.\n");
            return 0;
        }*/
    }

    return 0;
}

int Scene3D::fileGetNumberofLightObjects(void) {
    if (this->fh == NULL) return -1;

    rewind(this->fh);
    // We are going to go thru file contents searching each definition of this object
    // Each time we find one we'll increment the counter
    // I know this is sucky but... who cares
    int times = 0;
    char s[4096];
    while (!feof(this->fh)) {
        fgets(s, 4096, this->fh);
        if (strcmp(s, "*LIGHTOBJECT {\n") == 0) {
            times++;
        }
    }
    return times;
}

int Scene3D::loadLightObjFromFile(unsigned int index) {
    char s[4096], t[255];
    char nodeName[255], dummy[255];
    unsigned int i, v1, v2, v3;
    char s1[255], s2[255], s3[255], s4[255];
    float x, y, z;

    while (true && !feof(this->fh)) {
        // Read and remove the last \n
        fgets(s, 4096, this->fh);
        s[strlen(s) - 1] = '\0';

        // Node name?
        if (strstr(s, "\t*NODE_NAME") != NULL) {
            sscanf(s, "\t%s %s", dummy, nodeName);
            for (i = 0; i < strlen(nodeName) - 1; i++) {
                nodeName[i] = nodeName[i + 1];
            }
            nodeName[strlen(nodeName) - 2] = '\0';
        }
        // Node transformation matrix?
        if (strcmp(s, "\t*NODE_TM {") == 0) {
            //*NODE_NAME "GeoSphere01"
            fgets(s, 4096, this->fh);
            //*INHERIT_POS 0 0 0
            fgets(s, 4096, this->fh);
            //*INHERIT_ROT 0 0 0
            fgets(s, 4096, this->fh);
            //*INHERIT_SCL 0 0 0
            fgets(s, 4096, this->fh);
            //*TM_ROW0 1.0000	0.0000	0.0000
            //*TM_ROW1 0.0000	-0.0000	1.0000
            //*TM_ROW2 0.0000	-1.0000	-0.0000
            //*TM_ROW3 -0.2463	-0.0000	0.2463
            fgets(s, 4096, this->fh);
            fgets(s, 4096, this->fh);
            fgets(s, 4096, this->fh);
            fgets(s, 4096, this->fh);
            //*TM_POS -0.2463	-0.0000	0.2463
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f %f %f", t, &x, &y, &z);
            this->m_lightObjectsList[index].setTMPos(x, y, z);
            //*TM_ROTAXIS -1.0000	0.0000	0.0000
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f %f %f", t, &x, &y, &z);
            this->m_lightObjectsList[index].setTMRotAxis(x, y, z);
            //*TM_ROTANGLE 1.5708
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f", t, &x);
            this->m_lightObjectsList[index].setTMRotAngle(x);
            //*TM_SCALE 1.0000	1.0000	1.0000
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f %f %f", t, &x, &y, &z);
            this->m_lightObjectsList[index].setTMScale(x, y, z);
            //*TM_SCALEAXIS 0.0000	0.0000	0.0000
            fgets(s, 4096, this->fh);
            //*TM_SCALEAXISANG 0.0000*/
            fgets(s, 4096, this->fh);
            //}
            fgets(s, 4096, this->fh);
        }
        //	*LIGHT_SHADOWS Off
        //fgets(s, 4096, this->fh);
        if (strstr(s, "\t*LIGHT_SHADOWS") != NULL) {

        }
        if (strstr(s, "\t*LIGHT_USELIGHT") != NULL) {

        }
        if (strstr(s, "\t*LIGHT_SPOTSHAPE") != NULL) {

        }
        if (strstr(s, "\t*LIGHT_USEGLOBAL") != NULL) {

        }
        if (strstr(s, "\t*LIGHT_ABSMAPBIAS") != NULL) {

        }
        if (strstr(s, "\t*LIGHT_OVERSHOOT") != NULL) {

        }


        // *LIGHT_SETTINGS {
        //fgets(s, 4096, this->fh);
        if (strcmp(s, "\t*LIGHT_SETTINGS {") == 0) {
            //	*TIMEVALUE 0
            fgets(s, 4096, this->fh);
            // *LIGHT_COLOR 0.0471	0.0000	0.9922
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f %f %f", t, &x, &y, &z);
            this->m_lightObjectsList[index].setColorDiffuse(x, y, z, 1);
            //	*LIGHT_INTENS 1.0000
            fgets(s, 4096, this->fh);
            sscanf(s, "%s %f", t, &x);
            this->m_lightObjectsList[index].setLightIntensity(x);
            //	*LIGHT_ASPECT -1.0000
            fgets(s, 4096, this->fh);
            // *LIGHT_TDIST -1.0000
            fgets(s, 4096, this->fh);
            //	*LIGHT_MAPBIAS 1.0000
            fgets(s, 4096, this->fh);
            // *LIGHT_MAPRANGE 4.0000
            fgets(s, 4096, this->fh);
            //	*LIGHT_MAPSIZE 512
            fgets(s, 4096, this->fh);
            //	*LIGHT_RAYBIAS 0.0000
            fgets(s, 4096, this->fh);
            // }
            fgets(s, 4096, this->fh);
            break;
        }
    }
    return 0;
}

int Scene3D::draw(void) {
    unsigned int i;
    GLfloat globalambient[] = {0.75, 0.765, 0.765, 1.0};
    GLfloat pos0[] = {0.0, 10.0, 0.0, 0.0}; /* w = 0 == infinite distance */
    GLfloat dif0[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat spe0[] = {0, 0, 1.0, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalambient);

    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spe0);
    glEnable(GL_LIGHT0);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);

    if (this->m_numLightObjects != 0) {
        GLuint lightIndex;


        for (i = 0; i<this->m_numLightObjects; i++) {
            switch (i) {
                case 0: glEnable(GL_LIGHT1);
                    lightIndex = GL_LIGHT1;
                    break;
                case 1: glEnable(GL_LIGHT2);
                    lightIndex = GL_LIGHT2;
                    break;
                case 2: glEnable(GL_LIGHT3);
                    lightIndex = GL_LIGHT3;
                    break;
                case 3: glEnable(GL_LIGHT4);
                    lightIndex = GL_LIGHT4;
                    break;
                case 4: glEnable(GL_LIGHT5);
                    lightIndex = GL_LIGHT5;
                    break;
                case 5: glEnable(GL_LIGHT6);
                    lightIndex = GL_LIGHT6;
                    break;
                case 6: glEnable(GL_LIGHT7);
                    lightIndex = GL_LIGHT7;
                    break;


            }
            this->m_lightObjectsList[i].draw(lightIndex);
        }
    }
    glClearColor(0, 0, 0, 1);
    //glClear(GL_DEPTH_BUFFER_BIT);glEnable(GL_DEPTH_TEST);glDepthFunc(GL_LESS);
    for (i = 0; i<this->m_numGeomObjects; i++) {

        this->m_geomObjectsList[i].draw();
    }
    if (this->m_numLightObjects != 0) {

        for (i = 0; i<this->m_numLightObjects; i++) {
            switch (i) {
                case 0: glDisable(GL_LIGHT1);
                    break;
                case 1: glDisable(GL_LIGHT2);
                    break;
                case 2: glDisable(GL_LIGHT3);
                    break;
                case 3: glDisable(GL_LIGHT4);
                    break;
                case 4: glDisable(GL_LIGHT5);
                    break;
                case 5: glDisable(GL_LIGHT6);
                    break;
                case 6: glDisable(GL_LIGHT7);
                    break;


            }

        }
        glDisable(GL_LIGHTING);
    }
    return 0;
}

unsigned int Scene3D::getNumGeomObjects(void) {
    return m_numGeomObjects;
}

GeomObject *Scene3D::getGeomObjectAt(unsigned int index) {
    return &m_geomObjectsList[index];
}
