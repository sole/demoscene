/*
	Copyright 2009 Soledad Penades http://soledadpenades.com

	This file is part of xplsv_to_the_beat

	xplsv_to_the_beat is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License version 3 only, as published
	by the Free Software Foundation.

	xplsv_to_the_beat is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with xplsv_to_the_beat.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "utils.h"
#include <math.h>
#include <stdlib.h> // malloc

float SC_PRECISION;
float SC_INV_PREC;
int SC_PERIOD;
float *sinLUT;
float *cosLUT;
float DEG_TO_RAD;
float RAD_TO_DEG;
float TWO_PI;


float normalize(float value, float minimum, float maximum)
{
	return (value - minimum) / (maximum - minimum);
}

float interpolate(float normValue, float minimum, float maximum)
{
	return minimum + (maximum - minimum) * normValue;
}

float map(float value, float in_min, float in_max, float out_min, float out_max)
{
	return interpolate( normalize(value, in_min, in_max), out_min, out_max);
}

void utils_initialize_sin_cos_lut()
{
	int i;
	
	SC_PRECISION = 0.25f;
	SC_INV_PREC = 1.0f / SC_PRECISION;
	SC_PERIOD = (int) (360.0f * SC_INV_PREC);
	DEG_TO_RAD = (float) (M_PI / 180.0) * SC_PRECISION;
	RAD_TO_DEG = (float) (180.0 / M_PI) / SC_PRECISION;
	TWO_PI = 2 * M_PI;
	
	sinLUT = (float*) malloc(sizeof(float) * SC_PERIOD);
	cosLUT = (float*) malloc(sizeof(float) * SC_PERIOD);
	
	for (i = 0; i < SC_PERIOD; i++) {
        sinLUT[i] = (float) sin(i * DEG_TO_RAD);
        cosLUT[i] = (float) cos(i * DEG_TO_RAD);
	}
}

float utils_lut_sin(float theta)
{
	
    while (theta < 0) {
            theta += TWO_PI;
    }
    return sinLUT[(int) (theta * RAD_TO_DEG) % SC_PERIOD];


}

float utils_lut_cos(float theta)
{
	while (theta < 0) {
            theta += TWO_PI;
    }
    return cosLUT[(int) (theta * RAD_TO_DEG) % SC_PERIOD];
}

float utils_lut_tan(float theta)
{
	return (utils_lut_sin(theta) / utils_lut_cos(theta));
}
