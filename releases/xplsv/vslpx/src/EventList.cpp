#include "EventList.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

EventList::EventList() {
	this->numEvents=0;
	pos=0;

	this->startList=new float[MAX_NUM_EVENTS];
	this->lengthList=new float[MAX_NUM_EVENTS];
	this->volList=new float[MAX_NUM_EVENTS];
}

EventList::~EventList() {
	if(this->numEvents>0) {
            delete this->startList;
            delete this->lengthList;
            delete this->volList;
	}
}

void EventList::setName(char *_name) {
	strcpy(this->name, _name);
}

char* EventList::getName(void) {
	return this->name;
}

void EventList::addEvent(float _start, float _length, float _vol) {
	int newNumEvents;

        newNumEvents=this->numEvents+1;

        if(newNumEvents > MAX_NUM_EVENTS)
        {
            printf("Too many events for this humble EventList, rejecting new event!\n");
            return;
        }
	//this->startList = (float *) realloc(this->startList, sizeof(float)*newNumEvents);
	this->startList[numEvents]=_start;

	//this->lengthList = (float *) realloc(this->lengthList, sizeof(float)*newNumEvents);
	this->lengthList[numEvents]=_length;

	//this->volList = (float *) realloc(this->volList, sizeof(float)*newNumEvents);
	this->volList[numEvents]=_vol;

	numEvents++;
}

int EventList::isEventActive(float _time) {
	/* Esto esta mal seguro XD */
	float end = this->lengthList[this->pos] + this->startList[this->pos];
	float start = this->startList[this->pos];


	// Y otra propuesta!!
	// Dada pos (intervalo actual)
	// t esta en el intervalo[pos]?
	// Si -> devolver pos
	// Si no
	// Puede haber dos casos: t antes de cualquier intervalo, t despues de un intervalo
	// caso: t < int_start[pos]
	// caso: t > int_end[pos]
	//		subcaso: t<int_start[pos+1] -> mantener, devuelve -1, no esta playando, esta fuera
	//		subcaso: t>=int_start[pos+1] && (pos+1)<numInt -> pos++, devolver pos
	

	// t esta en el intervalo[pos]?
	if( (start<=_time) && (_time < end) ) {
		// Si -> devolver pos
		return this->pos;
	} else {
	// Si no
	// Puede haber dos casos: t antes de cualquier intervalo, t despues de un intervalo
	// caso: t < int_start[pos]
		if(_time < start) {
			// No le llega el tiempo para el intervalo siguiente
			return -1;
		} 
	// caso: t > int_end[pos]
		if(_time > end) {
			// se ha acabado el intervalo en que estabamos
			// Hay mas intervalos?
			if( (this->pos + 1) < this->numEvents) {
				float nextStart = this->startList[pos+1];
				if(_time < nextStart ) {
				// subcaso: t<int_start[pos+1] -> mantener, devuelve -1, no esta playando, esta fuera
					return -1;
				}
				if(_time >= nextStart) {
					// subcaso: t>=int_start[pos+1] && (pos+1)<numInt -> pos++, devolver pos
					pos++;
					// Otro subcaso, si han coincidido dos eventos en el mismo tiempo, avanzo, q si no no rulez
					//while(((this->pos + 1) < this->numEvents) && (this->startList[this->pos]==this->startList[this->pos+1])) {
						/*char s[255];
						sprintf(s,"Avanzo a %d\n",this->pos+1);
						//OutputDebugString(s);
						MessageBox(NULL, s, "ue", MB_OK);*/
					//	this->pos++;
					//}
					return this->pos;
				}	
			} else {
				// Se ha acabado el ultimo intervalo
				return -1;
			}
		}
	}
	return 0;
}
/*class EventList {
private:
	int numEvents;
	int pos;
	char name[256];
	float *startList;
	float *lengthList; 
	float *volList;

public:
	EventList();
	~EventList();

	int setName(char *_name);
	void addEvent(float _start, float _length, float _vol);
	int isEventActive(float _time); // returns the position of the event or -1 if there's not active event
	float getStart(int pos);
	float getLength(int pos);
	float getVol(int pos);


};*/
