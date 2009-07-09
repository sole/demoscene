#include "Events.h"

int event_get_synched_pos(float time, float* times, int num_events)
{
	int pos = 0;
	while(pos < num_events && times[pos] < time)
	{
		pos++;
	}
	return pos;
}

int event_is_active(float time, int position, float *times, int num_events)
{
	if(position >= num_events)
	{
		return 0;
	}
	
	return(time >= times[position] && (position+1 < num_events));
	
}
