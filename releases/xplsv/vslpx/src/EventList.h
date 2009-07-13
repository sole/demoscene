#ifndef __EVENTLIST__
#define __EVENTLIST__

#define MAX_NUM_EVENTS 1000

class EventList {
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

	void setName(char *_name);
	char* getName(void);
	void addEvent(float _start, float _length, float _vol);
	int isEventActive(float _time); // returns the position of the event or -1 if there's not active event
	float getStart(int pos);
	float getLength(int pos);
	float getVol(int pos);
};

#endif
