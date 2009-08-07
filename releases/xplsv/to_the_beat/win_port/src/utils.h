#ifndef UTILS_H
#define UTILS_H

float normalize(float value, float minimum, float maximum);
float interpolate(float normValue, float minimum, float maximum);
float map(float value, float in_min, float in_max, float out_min, float out_max);

void utils_initialize_sin_cos_lut();
float utils_lut_sin(float theta);
float utils_lut_cos(float theta);
float utils_lut_tan(float theta);

#endif

