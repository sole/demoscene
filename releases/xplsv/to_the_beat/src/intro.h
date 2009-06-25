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

#ifndef INTRO_H
#define INTRO_H

int intro_init(int width, int height);

int intro_play(float ticks);

void intro_effect_two_parts(float ticks, int order, int pattern, int row);
void draw_text(float* text, float scale);


// aux's
void setOrtho(float xres, float yres);
void restoreProjection();
float rrand(float, float);

#endif
