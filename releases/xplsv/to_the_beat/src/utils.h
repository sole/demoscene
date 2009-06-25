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

#ifndef UTILS_H
#define UTILS_H

// Adapted from http://www.bit-101.com/blog/?p=1242
float normalize(float value, float minimum, float maximum);
float interpolate(float normValue, float minimum, float maximum);
float map(float value, float in_min, float in_max, float out_min, float out_max);

// Adapted from http://code.google.com/p/toxiclibs/source/browse/trunk/toxiclibs/src.geom/toxi/math/SinCosLUT.java
void utils_initialize_sin_cos_lut();
float utils_lut_sin(float theta);
float utils_lut_cos(float theta);
float utils_lut_tan(float theta);

#endif

