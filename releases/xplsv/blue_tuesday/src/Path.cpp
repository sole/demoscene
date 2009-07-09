#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Path.h"

Path::Path() {
	this->numControlPoints=0;
	this->numInterpolatedPoints=0;
}

int Path::loadPath(const char *filename) {
	FILE *handle;
	char s[255],buf[255];
	int numvert,i,temp,ok;
//	int v1,v2,v3; // para los vértices
	float x,y,z;

	if(filename!=NULL) {
		// abro el fichero pa lectura...
		handle=fopen(filename,"r");
		if(handle==NULL) {
			printf("Path::loadPath - can't open %s\n",filename);
			return -1;
		} // fin de juego!
		// en otro caso, continúa la fiesta!
		// Primero compruebo que sea un fichero válido:
		// La primera línea debe ser "*3DSMAX_ASCIIEXPORT	200"
		fgets(buf,255,handle);
		if(strcmp(buf,"*3DSMAX_ASCIIEXPORT\t200\n")!=0) {
			printf("Path::loadPath - %s not a valid ase file\n",filename);
			return -1;
		}
		//printf("formato correcto");
		// Ahora leo hasta encontrar el inicio de la malla
		ok=0;
		strcpy(buf,"");
		while(!feof(handle)) {
			fgets(buf,255,handle);
			//printf("%s",buf);
			if(strcmp(buf,"\t*SHAPE_LINECOUNT 1\n")==0) {
				ok=1;
				break;
			}
		}
		
		if(strcmp(buf,"\t*SHAPE_LINECOUNT 1\n")==0) {
			//printf("Encontre la malla\n");
		} 
		else // Si no he encontrado la malla ya puedo irme de aqui!
		{
			printf("Path::loadPath - %s not a path found ??\n",filename);
			return -1;
		}
		// leo la siguiente linea (aunque la ignoro) (*SHAPE_LINE 0 {)
		fgets(buf,255,handle);
		//printf("%s",buf);
		// Número de vértices
		fgets(buf,255,handle);
		sscanf(buf,"%s %d",s,&numvert);
		//printf("%s %d",s,numvert);
		this->numInterpolatedPoints=numvert;

		// ahora reservo memoria para mis amigos los puntos de control interpolados
		this->interCPList=(Point*)malloc((sizeof(Point))*(this->numInterpolatedPoints));

		// Ahora a leer los puntos!!
		for(i=0;i<this->numInterpolatedPoints;i++) {
			//fscanf(handle,"\t\t\t%d%f\t%f\t%f",&temp,&x,&y,&z);
			fgets(buf,255,handle);
			//printf("%f %f %f\n",x,y,z);
			sscanf(buf,"%s %d %f %f %f",s,&temp,&x,&y,&z);
			this->interCPList[i].x=x;
			this->interCPList[i].y=y;
			this->interCPList[i].z=z;
		}
		// fin de vertices (})
		fgets(buf,255,handle);
	}
	return(0);
}

void Path::getPointAt(int pointNum, Point *p){
	if((pointNum>=0) && (pointNum<this->numInterpolatedPoints)) {
		p->x=this->interCPList[pointNum].x;
		p->y=this->interCPList[pointNum].y;
		p->z=this->interCPList[pointNum].z;
	} else if (pointNum>this->numInterpolatedPoints) {// Si pido de más, devuelvo el último
		p->x=this->interCPList[this->numInterpolatedPoints-1].x;
		p->y=this->interCPList[this->numInterpolatedPoints-1].y;
		p->z=this->interCPList[this->numInterpolatedPoints-1].z;
	}
}

int Path::getNumICP(void) {
	return this->numInterpolatedPoints;
}

void Path::scale(float sx, float sy, float sz) {
	for(int i=0;i<this->numInterpolatedPoints;i++) {
		this->interCPList[i].x*=sx;
		this->interCPList[i].y*=sy;
		this->interCPList[i].z*=sz;
		//printf("%f %f %f\n",this->interCPList[i].x,this->interCPList[i].y,this->interCPList[i].z);
	}//exit(-1);
}
