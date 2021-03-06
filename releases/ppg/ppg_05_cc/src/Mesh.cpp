#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gl\glut.h>
#include "Mesh.h"

#ifndef __MATH3D__
	#include "math3D.h"
#endif



	/* constructor	*/
	Mesh::Mesh(void) {
		//inicializo numVertex a 0 
		this->numVertex=0;
		this->numFaces=0;
	}
	// destructor
	Mesh::~Mesh() {
		if(this->numVertex>0) {
			// quiere decir que he creado v�rtices, y debo eliminarlos
			/*free(this->x);
			free(this->y);
			free(this->z);*/
			// y por alguna extra�a razon no consigo eliminarlos - no lo entiendo
		}
	}
	// dibuja los v�rtices en pantalla
	void Mesh::draw(void) {
		// Deberia pensar en una �lista de caras? �En las normales?
		int i,v1,v2,v3;
		glBegin(GL_TRIANGLES);
		for(i=0;i<this->numFaces;i++) {
			v1=this->faceList[0][i];
			v2=this->faceList[1][i];
			v3=this->faceList[2][i];
			//glColor3f(1.0,0,0);
			glNormal3f(this->normalList[0][i],this->normalList[1][i],this->normalList[2][i]);
			glVertex3f(this->x[v1],this->y[v1],this->z[v1]);
			//glColor3f(0,1,0);
			glVertex3f(this->x[v2],this->y[v2],this->z[v2]);
			//glColor3f(0,0,1);
			glVertex3f(this->x[v3],this->y[v3],this->z[v3]);
			//glVertex3f(this->x[i+2],this->y[i+2],this->z[i+2]);
			//glVertex3f(this->x[i+1],this->y[i+1],this->z[i+1]);
		}

		glEnd();

	}

	// dibuja la malla pero en ... modo MALLA XDDD
	void Mesh::drawWire(float linewidth,int numcar) {
		// Deberia pensar en una �lista de caras? �En las normales?
		// primera version -cutre- de dibujado: 'vomita' todos los vertices con trianglestrip
		int i,v1,v2,v3,num;
		GLfloat prevLineWidth;

		glGetFloatv(GL_LINE_WIDTH,&prevLineWidth);
		glLineWidth(linewidth);
		//glLineWidth(1);
		glPointSize(4);
		if(numcar>this->numFaces) {
			num=this->numFaces;
		} else {
			num=numcar;
		}
		
		
		//for(i=0;i<this->numFaces;i+=2) {
		// para dibujar los triangulos facetados, teng q hacer un glbegin x cada triang
	//	glEnable(GL_DEPTH_TEST );
		for(i=0;i<num;i++) {
			glBegin(GL_LINE_STRIP);
			v1=this->faceList[0][i];
			v2=this->faceList[1][i];
			v3=this->faceList[2][i];
			//glVertex3f(0,0,0);
			//glColor3f(1.0,0,0);
//			glNormal3f(this->normalList[0][i],this->normalList[1][i],this->normalList[2][i]);
			glVertex3f(this->x[v1],this->y[v1],this->z[v1]);
			//glColor3f(0,1,0);
			glVertex3f(this->x[v2],this->y[v2],this->z[v2]);
			//glColor3f(0,0,1);
			glVertex3f(this->x[v3],this->y[v3],this->z[v3]);
			//glVertex3f(this->x[i+2],this->y[i+2],this->z[i+2]);
			//glVertex3f(this->x[i+1],this->y[i+1],this->z[i+1]);
			//glColor3f(1.0,0,0);
//			glNormal3f(this->normalList[0][i],this->normalList[1][i],this->normalList[2][i]);
			//glVertex3f(this->x[v1],this->y[v1],this->z[v1]);
			glEnd();
		}
		
		glLineWidth(prevLineWidth);
		//glDisable(GL_DEPTH_TEST );
		

	}

	
	// dibuja los poligonos -triangulos- pero con las luces q le hayamos aplicado, si no hay luces no se vera nada
	/*void Mesh::drawLit(void) {
		int i,v1,v2,v3;
		float r=0.0,g=0.0,b=0.0;
		Point result;
		glBegin(GL_TRIANGLES);
		for(i=0;i<this->numFaces;i++) {
			v1=this->faceList[0][i];
			v2=this->faceList[1][i];
			v3=this->faceList[2][i];
			// Se obtiene el color del metodo de la luz, y es fijo para cada triangulo 
			result=this->lightList[0];
			glColor3f(r,g,b);
			glNormal3f(this->normalList[0][i],this->normalList[1][i],this->normalList[2][i]);
			glVertex3f(this->x[v1],this->y[v1],this->z[v1]);
			//glColor3f(0,1,0);
			glVertex3f(this->x[v2],this->y[v2],this->z[v2]);
			//glColor3f(0,0,1);
			glVertex3f(this->x[v3],this->y[v3],this->z[v3]);
			//glVertex3f(this->x[i+2],this->y[i+2],this->z[i+2]);
			//glVertex3f(this->x[i+1],this->y[i+1],this->z[i+1]);
		}

		glEnd();

	}*/


	// carga una malla desde un ASE (SOLO UNA)
	int Mesh::loadMesh(char *filename){
		/* la estructura que espero:
		NUMVERTICES
		NUMCARAS (aunq ahora no lo uso)
		VERTICES*NUMVERTICES --> x\ty\tz\t
		*/
		FILE *handle;
		char s[255],buf[255];
		int numvert,numfaces,i,temp,ok;
		int v1,v2,v3; // para los v�rtices
		float x,y,z;

		if(filename!=NULL) {
			// abro el fichero pa lectura...
			handle=fopen(filename,"r");
			if(handle==NULL) {
				//printf("Mesh::loadMesh - can't open %s\n",filename);
				return -1;
			} // fin de juego!
			// en otro caso, contin�a la fiesta!
			// Primero compruebo que sea un fichero v�lido:
			// La primera l�nea debe ser "*3DSMAX_ASCIIEXPORT	200"
			fgets(buf,255,handle);
			if(strcmp(buf,"*3DSMAX_ASCIIEXPORT\t200\n")!=0) {
				//printf("Mesh::loadMesh - %s not a valid ase file\n",filename);
				return -1;
			}
			//printf("formato correcto");
			// Ahora leo hasta encontrar el inicio de la malla
			ok=0;
			strcpy(buf,"");
			while(!feof(handle)) {
				fgets(buf,255,handle);
				//printf("%s",buf);
				if(strcmp(buf,"\t*MESH {\n")==0) {
					ok=1;
					break;
				}
			}
			
			if(strcmp(buf,"\t*MESH {\n")==0) {
				//printf("Encontre la malla\n");
			} 
			else // Si no he encontrado la malla ya puedo irme de aqui!
			{
				//printf("Mesh::loadMesh - %s not a mesh found ??\n",filename);
				return -1;
			}
			// leo la linea del timevalue (aunque la ignoro)
			fgets(buf,255,handle);
			//printf("%s",buf);
			// N�mero de v�rtices
			fgets(buf,255,handle);
			sscanf(buf,"%s %d",s,&numvert);
			//printf("%s %d",s,numvert);
			this->numVertex=numvert;

			//N�mero de caras
			fgets(buf,255,handle);
			sscanf(buf,"%s %d",s,&numfaces);
			this->numFaces=numfaces;
			// ahora reservo memoria para mis amigos los v�rtices
			this->x=(float*)malloc((sizeof(float))*(this->numVertex));
			this->y=(float*)malloc((sizeof(float))*(this->numVertex));
			this->z=(float*)malloc((sizeof(float))*(this->numVertex));
			// Tambien quiero memoria para la lista de caras
			this->faceList[0]=(int*)malloc((sizeof(int)*this->numFaces));
			this->faceList[1]=(int*)malloc((sizeof(int)*this->numFaces));
			this->faceList[2]=(int*)malloc((sizeof(int)*this->numFaces));
			// Y para las normales a las caras
			this->normalList[0]=(float*)malloc((sizeof(float)*this->numFaces));
			this->normalList[1]=(float*)malloc((sizeof(float)*this->numFaces));
			this->normalList[2]=(float*)malloc((sizeof(float)*this->numFaces));
			// Leo la linea que debe decir VERTEXLIST
			fgets(buf,255,handle);
			if(strcmp(buf,"\t\t\t*MESH_VERTEX_LIST {")) {
				//printf("Encontre la lista de vertices\n");
			} 
			else {
				//printf("Mesh::loadMesh - %s not vertexlist found ??\n",filename);
				return -1;
			}
			// Ahora a leer los vertices!
			for(i=0;i<this->numVertex;i++) {
				//fscanf(handle,"\t\t\t%d%f\t%f\t%f",&temp,&x,&y,&z);
				fgets(buf,255,handle);
				//printf("%f %f %f\n",x,y,z);
				sscanf(buf,"%s %d %f %f %f",s,&temp,&x,&y,&z);
				this->x[i]=x;
				this->y[i]=y;
				this->z[i]=z;
			}
			// fin de vertices (})
			fgets(buf,255,handle);

			// Lista de caras
			fgets(buf,255,handle);

			if(strcmp(buf,"\t\t\t*MESH_FACE_LIST {")) {
				//printf("Encontre la lista de caras\n");
			} 
			else {
				//printf("Mesh::loadMesh - %s not face list found ??\n",filename);
				return -1;
			}

			// Ahora a leer las caras!
			for(i=0;i<this->numFaces;i++) {
				//			*MESH_FACE    0:    A:    0 B:    2 C:    3 AB:    1 BC:    1 CA:    0	 *MESH_SMOOTHING 2 	*MESH_MTLID 1
				strcpy(buf,"");
				fgets(buf,255,handle);
				
				//sscanf(buf,"%s %d %f %f %f",s,&temp,&x,&y,&z);
				//             0  a  0  b  2  c  3
				//sscanf(buf,"%* %* %* %* %d %* %d %* %d",&v1,&v2,&v3);
				char s1[255],s2[255],s3[255],s4[255];
				sscanf(buf,"%s %d %s %s %d %s %d %s %d",s,&temp,s1,s2,&v1,s3,&v2,s4,&v3);
				this->faceList[0][i]=v1;
				this->faceList[1][i]=v2;
				this->faceList[2][i]=v3;
			}

			// Tengo que buscar hasta encontrar las normales

			ok=0;
			strcpy(buf,"");
			while(!feof(handle)) {
				fgets(buf,255,handle);
				//printf("%s",buf);
				if(strcmp(buf,"\t\t*MESH_NORMALS {\n")==0) {
					ok=1;
					break;
				}
			}
			
			if(strcmp(buf,"\t\t*MESH_NORMALS {\n")==0) {
				//printf("Encontre la malla\n");
			} 
			else // Si no he encontrado la malla ya puedo irme de aqui!
			{
				printf("Mesh::loadMesh - %s not normal list found ??\n",filename);
				return -1;
			}

			for(i=0;i<this->numFaces;i++) {
				strcpy(buf,"");
				fgets(buf,255,handle);
				// *MESH_FACENORMAL 0	0.0000	0.0000	-1.0000
				sscanf(buf,"%s %d %f %f %f",s,&temp,&x,&y,&z);
				this->normalList[0][i]=x;
				this->normalList[1][i]=y;
				this->normalList[2][i]=z;
				// tres fgets para tres lineas un poco inutilizadas
				fgets(buf,255,handle);
				fgets(buf,255,handle);
				fgets(buf,255,handle);
			}
		}
		this->normalize();
		/*for(i=0;i<this->numVertex;i++) {
			printf("%d %f %f %f\n",i,this->x[i],this->y[i],this->z[i]);
		}*/
		return 0;
	}

	void Mesh::normalize(void) {
		/* esto normaliza el objeto, dejando los v�rtices en 0..1 */
		int i;
		float maxX=0,maxY=0,maxZ=0;

		// primera pasada, para buscar el maximo en x,y,z		
		for(i=0;i<this->numVertex;i++) {
			if(abs(this->x[i])>maxX) {
				maxX=abs(this->x[i]);
			}
			if(this->y[i]>maxY) {
				maxY=this->y[i];
			}
			if(this->z[i]>maxZ) {
				maxZ=this->z[i];
			}
		}
		// segunda pasada, dividimos
		for(i=0;i<=this->numVertex;i++) {
			if(maxX>1) this->x[i]/=maxX;
			if(maxY>1) this->y[i]/=maxY;
			if(maxZ>1) this->z[i]/=maxZ;
		}
	}
