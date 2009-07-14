/*
 *  EventsList.h
 *  notengine
 *
 *  Created by Soledad Penades on 22/01/2006.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __EVENTLIST__
#define __EVENTLIST__

/*#include <stdio.h>
#include <string.h>
#include <windows.h>
*/
class EventList {
private:
	/*int numEvents;
	int pos;
	char name[256];
	float *startList;
	float *lengthList; 
	float *volList;
	*/
public:
	EventList();
	~EventList();
	/*
	void setName(char *_name);
	char* getName(void);
	void addEvent(float _start, float _length, float _vol);
	int isEventActive(float _time); // returns the position of the event or -1 if there's not active event
	float getStart(int pos);
	float getLength(int pos);
	float getVol(int pos);*/
};

#endif