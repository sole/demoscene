// 21 feb 2005
#ifndef __GEOMOBJECT__
#define __GEOMOBJECT__

#include "math3D.h"
#include <string.h>
#include <stdio.h>
#include "my_opengl.h"
#include "Algebra.h"

class GeomObject {
public:
	GeomObject(void);
	~GeomObject();

	void setInheritPos(float x, float y, float z);
	void setInheritRot(float x, float y, float z);
	void setInheritScl(float x, float y, float z);
	void setTransformMatrix(float a, float b, float c, 
						   float d, float e, float f,
						   float g, float h, float i,
						   float j, float k, float l);
	void setTMPos(float x, float y, float z);
	void setTMRotAxis(float x, float y, float z);
	void setTMRotAngle(float ang);
	void setTMScale(float x, float y, float z);
	void setTMScaleAxis(float x, float y, float z);
	void setTMScaleAxisAng(float ang);
	// mesh
	void setMeshNumVertex(unsigned int num);
	int initMeshVertexList(void);
	void setMeshNumFaces(unsigned int num);
	int initMeshFacesList(void);
	void setMeshNumTVertex(unsigned int num);
	int initMeshTVertexList(void);
	int initMeshTFacesList(void);
	int initMeshFacesNormalList(void);
	// Setting point values
	int setMeshVertexAt(unsigned int index, float x, float y, float z, float w);
	int setMeshFaceAt(unsigned int index, unsigned int vertA, unsigned int vertB, unsigned int vertC);
	int setMeshTextureVertexAt(unsigned int index, float x, float y);
	int setMeshTextureFaceAt(unsigned int index, unsigned int vertA, unsigned int vertB, unsigned int vertC);
	int setMeshNormalAt(unsigned int index, float x, float y, float z, float w);

	// Other...
	Point getWireframeColor(void);
	void setWireframeColor(float x, float y, float z,float w);
	void setNodeName(char *nodeName);

	// Drawing
	void draw(void);
	void setWire(bool state);

private:
	char m_nodeName[255];
	bool b_drawAsWire;

	// Transform Matrix
	Point m_inheritPos;
	Point m_inheritRot;
	Point m_inheritScl;
	Point m_transformMatrix[4]; // 4 rows of points to store the transformation matrix
	Point m_tm_Pos;
	Point m_tm_rotAxis;
	float m_tm_rotAngle;
	Point m_tm_scale;
	Point m_tm_ScaleAxis;
	float m_tm_scaleAxisAng;

	// Mesh things
	unsigned int m_mesh_NumVertex; // number of geometrical vertexes
	unsigned int m_mesh_NumFaces;
	Point *m_mesh_vertexList;
	unsigned int *m_mesh_faceList[3]; // puntero a vector de caras (o sea una lista de caras)
	
	unsigned int m_mesh_NumTVertex; // number of texture vertexes
	Point *m_mesh_TVertList; // texture vertexes
	unsigned int m_mesh_numTVFaces; // number of texture vertexes faces (?)
	unsigned int *m_mesh_tfaceList[3]; // points to array of texture faces

	Point *m_mesh_faceNormals; // TODO: En realidad hay tambien info acerca de las normales de cada vertice de cada cara pero lo voy a ignorar
	float *m_normalList[3];
	// Other...
	Point m_wireframeColor;

};

#endif
