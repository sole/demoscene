#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#define EVENT_TYPE_BUBBLE 0x1
#define EVENT_TYPE_SNARE 0x2

int event_get_synched_pos(float time, float* times, int num_events);

int event_is_active(float time, int position, float *times, int num_events);

#endif
