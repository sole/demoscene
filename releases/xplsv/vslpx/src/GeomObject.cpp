// 21 feb 2004
#include "GeomObject.h"

// TODO methods for adding points, etc
// TODO selecting the drawing method

GeomObject::GeomObject(void) {
	this->m_inheritPos.x=0;
	this->m_inheritPos.y=0;
	this->m_inheritPos.z=0;
	this->m_inheritPos.w=0;

	this->m_inheritRot.x=0;
	this->m_inheritRot.y=0;
	this->m_inheritRot.z=0;
	this->m_inheritRot.w=0;

	this->m_inheritScl.x=1;
	this->m_inheritScl.y=1;
	this->m_inheritScl.z=1;
	this->m_inheritScl.w=1;

	this->m_tm_Pos.x=0;
	this->m_tm_Pos.y=0;
	this->m_tm_Pos.z=0;
	this->m_tm_Pos.w=0;

	this->m_tm_rotAngle=0;

	this->m_tm_rotAxis.x=0;
	this->m_tm_rotAxis.y=0;
	this->m_tm_rotAxis.z=0;
	this->m_tm_rotAxis.w=0;

	this->m_tm_scale.x=0;
	this->m_tm_scale.y=0;
	this->m_tm_scale.z=0;
	this->m_tm_scale.w=0;

	this->m_tm_ScaleAxis.x=0;
	this->m_tm_ScaleAxis.y=0;
	this->m_tm_ScaleAxis.z=0;
	this->m_tm_ScaleAxis.w=0;

	this->m_tm_scaleAxisAng=0;

	this->m_transformMatrix[0].x=1;
	this->m_transformMatrix[0].y=0;
	this->m_transformMatrix[0].z=0;
	this->m_transformMatrix[0].w=0;

	this->m_transformMatrix[1].x=0;
	this->m_transformMatrix[1].y=0;
	this->m_transformMatrix[1].z=1;
	this->m_transformMatrix[1].w=0;

	this->m_transformMatrix[2].x=0;
	this->m_transformMatrix[2].y=-1;
	this->m_transformMatrix[2].z=0;
	this->m_transformMatrix[2].w=0;

	this->m_transformMatrix[3].x=0;
	this->m_transformMatrix[3].y=0;
	this->m_transformMatrix[3].z=0;
	this->m_transformMatrix[3].w=0;

	this->m_mesh_NumFaces=0;
	this->m_mesh_NumTVertex=0;
	this->m_mesh_numTVFaces=0;
	this->m_mesh_NumVertex=0;

	strcpy(this->m_nodeName,"");

	this->b_drawAsWire=false;
}

GeomObject::~GeomObject() {
	// TODO: free allocated memory
}

void GeomObject::setInheritPos(float x, float y, float z) {
	this->m_inheritPos.x=x;
	this->m_inheritPos.y=y;
	this->m_inheritPos.z=z;
}

void GeomObject::setInheritRot(float x, float y, float z) {
	this->m_inheritRot.x=x;
	this->m_inheritRot.y=y;
	this->m_inheritRot.z=z;
}
	
void GeomObject::setInheritScl(float x, float y, float z) {
	this->m_inheritScl.x=x;
	this->m_inheritScl.y=y;
	this->m_inheritScl.z=z;
}

void GeomObject::setTransformMatrix(float a, float b, float c,
						   float d, float e, float f,
						   float g, float h, float i,
						   float j, float k, float l) {

	this->m_transformMatrix[0].x=a;
	this->m_transformMatrix[0].y=b;
	this->m_transformMatrix[0].z=c;

	this->m_transformMatrix[1].x=d;
	this->m_transformMatrix[1].y=e;
	this->m_transformMatrix[1].z=f;

	this->m_transformMatrix[2].x=g;
	this->m_transformMatrix[2].y=h;
	this->m_transformMatrix[2].z=i;

	this->m_transformMatrix[3].x=j;
	this->m_transformMatrix[3].y=k;
	this->m_transformMatrix[3].z=l;
}

void GeomObject::setTMPos(float x, float y, float z) {
	this->m_tm_Pos.x=x;
	this->m_tm_Pos.y=y;
	this->m_tm_Pos.z=z;

}

void GeomObject::setTMRotAxis(float x, float y, float z) {
	this->m_tm_rotAxis.x=x;
	this->m_tm_rotAxis.y=y;
	this->m_tm_rotAxis.z=z;
}

void GeomObject::setTMRotAngle(float ang) {
	this->m_tm_rotAngle=ang;
}

void GeomObject::setTMScale(float x, float y, float z) {
	this->m_tm_scale.x=x;
	this->m_tm_scale.y=y;
	this->m_tm_scale.z=z;
}

void GeomObject::setTMScaleAxis(float x, float y, float z){
	this->m_tm_ScaleAxis.x=x;
	this->m_tm_ScaleAxis.y=y;
	this->m_tm_ScaleAxis.z=z;
}
void GeomObject::setTMScaleAxisAng(float ang) {
	this->m_tm_scaleAxisAng=ang;
}
	// mesh
void GeomObject::setMeshNumVertex(unsigned int num) {
	this->m_mesh_NumVertex=num;
}
int GeomObject::initMeshVertexList(void) {
	this->m_mesh_vertexList = (Point *) (malloc(sizeof(Point)*this->m_mesh_NumVertex));
	if(this->m_mesh_vertexList==NULL) {
		return -1;
	}
	return 0;
}

void GeomObject::setMeshNumFaces(unsigned int num) {
	this->m_mesh_NumFaces=num;
}

int GeomObject::initMeshFacesList(void) {
	this->m_mesh_faceList[0]=(unsigned int*)malloc((sizeof(unsigned int)*this->m_mesh_NumFaces));
	this->m_mesh_faceList[1]=(unsigned int*)malloc((sizeof(unsigned int)*this->m_mesh_NumFaces));
	this->m_mesh_faceList[2]=(unsigned int*)malloc((sizeof(unsigned int)*this->m_mesh_NumFaces));

	if( (this->m_mesh_faceList[0]==NULL) || 
		(this->m_mesh_faceList[1]==NULL) || 
		(this->m_mesh_faceList[2]==NULL)) {
		return -1;
	}
	return 0;
}

void GeomObject::setMeshNumTVertex(unsigned int num) {
	this->m_mesh_NumTVertex = num;
}

int GeomObject::initMeshTVertexList(void) {
	this->m_mesh_TVertList = (Point *) (malloc(sizeof(Point)*this->m_mesh_NumTVertex));
	if(this->m_mesh_TVertList==NULL) {
		return -1;
	}
	return 0;
}
int GeomObject::initMeshTFacesList(void) {
	this->m_mesh_tfaceList[0]=(unsigned int*)malloc((sizeof(unsigned int)*this->m_mesh_NumTVertex));
	this->m_mesh_tfaceList[1]=(unsigned int*)malloc((sizeof(unsigned int)*this->m_mesh_NumTVertex));
	this->m_mesh_tfaceList[2]=(unsigned int*)malloc((sizeof(unsigned int)*this->m_mesh_NumTVertex));

	if( (this->m_mesh_tfaceList[0]==NULL) || 
		(this->m_mesh_tfaceList[1]==NULL) || 
		(this->m_mesh_tfaceList[2]==NULL)) {
		return -1;
	}
	return 0;
}


int GeomObject::initMeshFacesNormalList(void) {
	/*this->m_mesh_faceNormals=(Point*)(malloc(sizeof(Point)*this->m_mesh_NumFaces+1));
	unsigned int i;
	for(i=0;i<this->m_mesh_NumFaces;i++) {
		this->m_mesh_faceNormals[i].x=0;
		this->m_mesh_faceNormals[i].y=0;
		this->m_mesh_faceNormals[i].z=0;
		this->m_mesh_faceNormals[i].w=0;

	}
	if( (this->m_mesh_faceNormals==NULL) ) {
		return -1;
	}
	return 0;*/
	
	/*this->m_mesh_faceNormals = new Point[this->m_mesh_NumFaces];//(Point *) (malloc(sizeof(Point)*this->m_mesh_NumFaces));
	if(this->m_mesh_faceNormals==NULL) {
		return -1;
	}
	return 0;*/
	this->m_normalList[0]=(float*)calloc( this->m_mesh_NumFaces, sizeof(float) );//malloc((sizeof(float)*this->m_mesh_NumFaces));
	this->m_normalList[1]=(float*)calloc( this->m_mesh_NumFaces, sizeof(float) );//malloc((sizeof(float)*this->m_mesh_NumFaces));
	this->m_normalList[2]=(float*)calloc( this->m_mesh_NumFaces, sizeof(float) );//malloc((sizeof(float)*this->m_mesh_NumFaces));

	if( (this->m_normalList[0]==NULL) || 
		(this->m_normalList[1]==NULL) || 
		(this->m_normalList[2]==NULL)) {
		return -1;
	}
	return 0;
}

// Setting point values...

int GeomObject::setMeshVertexAt(unsigned int index, float x, float y, float z, float w) {
	if( (index>=0) && (index < this->m_mesh_NumVertex)) {
		this->m_mesh_vertexList[index].x=x;
		this->m_mesh_vertexList[index].y=y;
		this->m_mesh_vertexList[index].z=z;
		this->m_mesh_vertexList[index].w=w;
		return 0;
	}
	return -1;
}
int GeomObject::setMeshFaceAt(unsigned int index, unsigned int vertA, unsigned int vertB, unsigned int vertC) {
	if( (index>=0) && (index < this->m_mesh_NumFaces)) {
		this->m_mesh_faceList[0][index] = vertA;
		this->m_mesh_faceList[1][index] = vertB;
		this->m_mesh_faceList[2][index] = vertC;

		return 0;
	}
	return -1;
}
int GeomObject::setMeshTextureVertexAt(unsigned int index, float x, float y) {
	if( (index>=0) && (index < this->m_mesh_NumTVertex)) {
		this->m_mesh_TVertList[index].x=x;
		this->m_mesh_TVertList[index].y=y;
		return 0;
	}
	return -1;
}
int GeomObject::setMeshTextureFaceAt(unsigned int index, unsigned int vertA, unsigned int vertB, unsigned int vertC) {
	if( (index>=0) && (index < this->m_mesh_numTVFaces)) {
		this->m_mesh_tfaceList[0][index] = vertA;
		this->m_mesh_tfaceList[1][index] = vertB;
		this->m_mesh_tfaceList[2][index] = vertC;

		return 0;
	}
	return -1;
}
int GeomObject::setMeshNormalAt(unsigned int index, float x, float y, float z, float w) {
	if( (index>=0) && (index < this->m_mesh_NumFaces)) {
		/*this->m_mesh_faceNormals[index].x=x;
		this->m_mesh_faceNormals[index].y=y;
		this->m_mesh_faceNormals[index].z=z;
		this->m_mesh_faceNormals[index].w=w;
		sprintf(s,"set %d %f %f %f\n",index,this->m_mesh_faceNormals[index].x,this->m_mesh_faceNormals[index].y,this->m_mesh_faceNormals[index].z);OutputDebugString(s);*/
		this->m_normalList[0][index]=x;
		this->m_normalList[1][index]=y;
		this->m_normalList[2][index]=z;

		return 0;
	}
	return -1;
}



// Other...
void GeomObject::setWireframeColor(float x, float y, float z, float w) {
	this->m_wireframeColor.x=x;
	this->m_wireframeColor.y=y;
	this->m_wireframeColor.z=z;
	this->m_wireframeColor.w=w;
}
Point GeomObject::getWireframeColor(void) {
	return m_wireframeColor;
}
	
void GeomObject::setNodeName(char *nodeName) {
	strcpy(this->m_nodeName,nodeName);
}

void GeomObject::setWire(bool state) {
	this->b_drawAsWire = state;
}

// Drawing
void GeomObject::draw(void) {
	unsigned int i;
	/* */

	GLfloat currentMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, currentMatrix);
	// Hallar la inversa de la matriz del modelo actual
	

	//TODO: apply transformations only when needed
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	

	// Deshago las transformaciones del modelo
	/*glTranslatef(-this->m_tm_Pos.x, -this->m_tm_Pos.y, -this->m_tm_Pos.z);
	glRotatef(-this->m_tm_rotAngle, this->m_tm_rotAxis.x, this->m_tm_rotAxis.y, this->m_tm_rotAxis.z);
	glScalef(1/this->m_tm_scale.x,1/this->m_tm_scale.y,1/this->m_tm_scale.z);
	*/

	// Scale
	glScalef(this->m_tm_scale.x,this->m_tm_scale.y,this->m_tm_scale.z);
	// Rotate
	glRotatef(this->m_tm_rotAngle, this->m_tm_rotAxis.x, this->m_tm_rotAxis.y, this->m_tm_rotAxis.z);
	// Translate
	glTranslatef(this->m_tm_Pos.x, this->m_tm_Pos.y, this->m_tm_Pos.z);
	
	
	// TODO if not assigned material then use wireframe... or somthing
	if(this->b_drawAsWire==false)
		glBegin(GL_TRIANGLES);
	else
		glBegin(GL_LINE_STRIP);
	//printf("Color: %f %f %f %f\n", this->m_wireframeColor.x,this->m_wireframeColor.y,this->m_wireframeColor.z, this->m_wireframeColor.w);
	glColor4f(this->m_wireframeColor.x,this->m_wireframeColor.y,this->m_wireframeColor.z, this->m_wireframeColor.w);
	unsigned int v1, v2, v3;
	GLfloat mat[4] = {this->m_wireframeColor.x,this->m_wireframeColor.y,this->m_wireframeColor.z, this->m_wireframeColor.w};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	//printf("Mesh num faces %d\n", m_mesh_NumFaces);
	for(i=0;i<this->m_mesh_NumFaces;i++) {
		
		// TODO: Assign texture coordinates when drawing
		v1 = this->m_mesh_faceList[0][i];
		v2 = this->m_mesh_faceList[1][i];
		v3 = this->m_mesh_faceList[2][i];
		CPoint res, p1, p2, p3;
		p1.x = this->m_mesh_vertexList[v1].x;
		p1.y = this->m_mesh_vertexList[v1].y;
		p1.z = this->m_mesh_vertexList[v1].z;
		
		p2.x = this->m_mesh_vertexList[v2].x;
		p2.y = this->m_mesh_vertexList[v2].y;
		p2.z = this->m_mesh_vertexList[v2].z;

		p3.x = this->m_mesh_vertexList[v3].x;
		p3.y = this->m_mesh_vertexList[v3].y;
		p3.z = this->m_mesh_vertexList[v3].z;

		//b-a x c-a

		res = (p2-p1)^(p3-p1);res.normalize();
		//glNormal3f(res.x,res.y,res.z);
		glNormal3f(-this->m_normalList[0][i],this->m_normalList[1][i], this->m_normalList[2][i]);
		//glNormal3f(this->m_mesh_faceNormals[i].x,this->m_mesh_faceNormals[i].y,this->m_mesh_faceNormals[i].z);
		glVertex3f(this->m_mesh_vertexList[v1].x, this->m_mesh_vertexList[v1].y, this->m_mesh_vertexList[v1].z);
		glVertex3f(this->m_mesh_vertexList[v2].x, this->m_mesh_vertexList[v2].y, this->m_mesh_vertexList[v2].z);
		glVertex3f(this->m_mesh_vertexList[v3].x, this->m_mesh_vertexList[v3].y, this->m_mesh_vertexList[v3].z);

	}
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


