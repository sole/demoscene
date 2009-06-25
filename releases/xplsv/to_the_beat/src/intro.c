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

#include "intro.h"
#include "SDL_opengl.h"
#include "sorollet.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Globals
int G_width;
int G_height;

float G_color_arena[3] = {1.0, 0.87, 0.33};

float G_color_tri1[3] = {0.478, 0.823, 0.921};
float G_color_tri2[3] = {0.788, 0.658, 0.886};

unsigned char G_color_grid[4] = {241, 239, 180, 128};
unsigned char G_color_text[3] = {255, 178, 189};
unsigned char G_color_text2[3] = {213, 208, 171};

static float G_text_xplsv[] = {
	5, // number of letters
	// X
	2, // num segments
	-0.5, 0.5,
	0.5, -0.5,
	-0.5, -0.5,
	0.5, 0.5,
	
	// P
	4,
	-0.5, 0.5,	0.5, 0.5,
	0.5, 0.5, 0.5, 0,
	0.5, 0, -0.5, 0,
	-0.5, 0.5, -0.5, -0.5,
	
	// L
	2,
	-0.5, 0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5, -0.5,
	
	// S
	5,
	-0.5, 0.5, 0.5, 0.5,
	-0.5, 0, 0.5, 0,
	-0.5, -0.5, 0.5, -0.5,
	-0.5, 0.5, -0.5, 0,
	0.5, 0, 0.5, -0.5,
	
	// V
	2,
	-0.5, 0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5, 0.5
	
};

static float G_text_to_the_beat[] = 
{
	11,
	// T 1
	2,
	-0.5, 0.5, 0.5, 0.5,
	0, 0.5, 0, -0.5,
	
	// O 2
	4,
	-0.5, 0.5, 0.5, 0.5,
	0.5, 0.5, 0.5, -0.5,
	0.5, -0.5, -0.5, -0.5,
	-0.5, -0.5, -0.5, 0.5,
	
	// _ 3
	1,
	-0.5, -0.5, 0.5, -0.5,
	
	// T 4
	2,
	-0.5, 0.5, 0.5, 0.5,
	0, 0.5, 0, -0.5,
	
	// H 5
	3,
	-0.5, 0.5, -0.5, -0.5,
	0.5, 0.5, 0.5, -0.5,
	-0.5, 0, 0.5, 0,
	
	// E 6
	4,
	-0.5, 0.5, 0.5, 0.5,
	-0.5, 0, 0.5, 0,
	-0.5, -0.5, 0.5, -0.5,
	-0.5, 0.5, -0.5, -0.5,
	
	// _ 7
	1,
	-0.5, -0.5, 0.5, -0.5,
	
	// B 8
	5,
	-0.5, 0.5, 0.5, 0.5,
	-0.5, 0, 0.5, 0,
	-0.5, -0.5, 0.5, -0.5,
	-0.5, 0.5, -0.5, -0.5,
	0.5, 0.5, 0.5, -0.5,
	
	// E 9
	4,
	-0.5, 0.5, 0.5, 0.5,
	-0.5, 0, 0.5, 0,
	-0.5, -0.5, 0.5, -0.5,
	-0.5, 0.5, -0.5, -0.5,
	
	// A 10
	4,
	-0.5, 0.5, -0.5, -0.5,
	0.5, 0.5, 0.5, -0.5,
	-0.5, 0.5, 0.5, 0.5,
	-0.5, 0, 0.5, 0,
	
	// T 11
	2,
	-0.5, 0.5, 0.5, 0.5,
	0, 0.5, 0, -0.5,
	
};

//----------------------
void setup()
{
	glShadeModel(GL_SMOOTH);
}

int intro_init(int width, int height)
{
	G_width = width;
	G_height = height;
	return 0;
}


int intro_play(float ticks)
{
	static float last_tick = 0;
	float elapsed_ticks;
	int order, pattern, row;
	static int did_setup = 0;
	
	elapsed_ticks = ticks - last_tick;
	last_tick = ticks;
	
	if(!did_setup)
	{
		setup();
		did_setup = 1;
	}
	
	order = sorollet_get_current_order();
	pattern = sorollet_get_current_pattern();
	row = sorollet_get_current_row();

	glClearColor(0.22, 0.215, 0.2, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	setOrtho(G_width, G_height);
	
	intro_effect_two_parts(ticks, order, pattern, row);

	restoreProjection();
	
	return 0;
}

void intro_effect_two_parts(float ticks, int order, int pattern, int row)
{
	int main_order = 2;
	int ending_order = 6;
	
	static float last_tick;
	float elapsed_ticks;
	
	float extra = 0;
	static float rotation = 0;
	float rotation_x, rotation_y;
	
	float camera_fov = 90, camera_aspect = 1.3, camera_zNear = 1, camera_zFar = 1000;
	float eyeX = -90, eyeY = 0, eyeZ = 30, centerX = 0, centerY = 0, centerZ = 0, upX = 0, upY = 1, upZ = 0;
	
	elapsed_ticks = ticks - last_tick;
	last_tick = ticks;
	
	if(order < main_order)
	{
		camera_fov = 100;
		eyeX = -250 + row;
	}
	else
	{
		float radius = 120;
		camera_fov = 120;
		float ang = ticks * 0.0008;
		eyeX = radius*sin(ang);
		eyeY = radius*cos(ang);
	}
	
	int bd_note = sorollet_get_channel_note(0);
	
	if(bd_note == 48)
	{
		extra += 5;
	}
	
	if(extra > 0)
	{
		float am =  0.75 * elapsed_ticks;
		
		extra -= am;
		if(extra < 0)
		{
			extra = 0;
		}
		
		rotation += am;
		if(rotation < 0)
		{
			rotation = 0;
		}
	}
	
	if(order >= main_order)
	{
		if(row % 8 == 0)
			rotation_y = - 0.25 * rotation;
		else
			rotation_x = 0.25 * rotation;
	}
	
	float w = G_width * 0.5;
	int i;
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	glLoadIdentity();
	gluPerspective(camera_fov, camera_aspect, camera_zNear, camera_zFar);
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);	
	
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	
	if(order >= main_order)
	{
		glRotatef(rotation, 0, 0, 1);
	
		if(rotation_x)
		{
			glRotatef(rotation_x, 1, 0, 0);
		}
	
		if(rotation_y)
		{
			glRotatef(rotation_y, 0, 1, -1);
		}
	}
		
	// GRID //
	int j, k;
	int grid = 30;
	int grid_inc = 4 * G_width / grid;
	float grid_top = G_width  * 2 ;
	float xpos = -grid_top, ypos;
	int wider_each = 5;
	
	if(order >= main_order && order < ending_order + 2)
	
	{
		glColor4ubv(G_color_grid);
	
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	
		for(i = 0; i < grid; i++)
		{
			ypos = -grid_top;
			for(j = 0; j < grid; j++)
			{
			
				if((i % wider_each == 0) && (j % wider_each == 0))
				{
					glDisable(GL_LINE_STIPPLE);
					glLineWidth(2);
				}
				else
				{
					glEnable(GL_LINE_STIPPLE);
					glLineStipple(1, 0x6666);
					glLineWidth(0.5);
				}
				glBegin(GL_LINES);
				glVertex3f(xpos, ypos, -grid_top);
				glVertex3f(xpos, ypos, grid_top);
			
				glVertex3f(xpos, -grid_top, ypos);
				glVertex3f(xpos, grid_top, ypos);
				glEnd();
				ypos += grid_inc;
			}
			xpos += grid_inc;
		}
	
		glDisable(GL_BLEND);
	
		glDisable(GL_LINE_STIPPLE);
	}

	int num_tris = 70;
	float s = w / num_tris;
	float y;
	float v = 4; //rand variation

	// TRIS //
	if(order >= main_order && order < ending_order)
	{
		glPushMatrix();
		for(i = 0; i < num_tris; i++)
		{	
			glRotatef(4.0, 0, 0, 1);
		
			glColor3fv(G_color_tri1);
	
			glLineWidth(2);
		
			y = 4*s*sin(i+ticks*0.00001);
		
			glBegin(GL_LINE_STRIP);
				glVertex3f(s + rrand(-v, v), s + rrand(-v, v), y + rrand(-v, v));
				glVertex3f(-s + rrand(-v, v), s + rrand(-v, v), y + rrand(-v, v));
				glVertex3f(-s + rrand(-v, v), -s + rrand(-v, v), y + rrand(-v, v));
			glEnd();
		
	
			glBegin(GL_LINE_STRIP);
				glVertex3f(-s + rrand(-v, v), -s + rrand(-v, v),  y + rrand(-v, v));
				glVertex3f(s + rrand(-v, v), -s + rrand(-v, v), y + rrand(-v, v));
				glVertex3f(s + rrand(-v, v), s + rrand(-v, v), y + rrand(-v, v));
			glEnd();
		
			s += 10;
		}
	
		glPopMatrix();
	}
	int t = 0;
	int rand_range = 6;
	float t_scale;
	unsigned char alpha;
	
	if(order < main_order)
	{
		t_scale = 40 + rrand(0, 5);
	}
	else
	{
		t_scale = 80;
	}

	
	for(t = 0; t < 20; t++)
	{
		glPushMatrix();
		glTranslatef(rrand(0, rand_range), rrand(0, rand_range), rrand(0, rand_range));

		glColor3ubv(G_color_text);
		glLineWidth(1);
	
	
		if(row < 16 || (row > 32 && row < 48))
		{
			draw_text(G_text_xplsv, t_scale);
		}
		else
		{
			draw_text(G_text_to_the_beat, t_scale);
		}
	
		glPopMatrix();
	}
	
	
	glPopMatrix();
	
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//---------------------------
	
	if(order < ending_order)
	{
		t_scale = 120;
	
		int hh_note = sorollet_get_channel_note(1);
		if(hh_note > 0 && hh_note < 253)
		{
			t_scale += 10;
		}
	
		rand_range = 15;
	
		for(t = 0; t < 20; t++)
		{
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glRotatef(90, 0,1, 0);
			glRotatef(20, -1, 0, 0);
			glTranslatef(0, 128-((row<<4)%256), 0);
			glTranslatef(rrand(0, rand_range), rrand(0, rand_range), rrand(0, rand_range));

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		
			glColor4ub(G_color_text2[0], G_color_text2[1], G_color_text2[2], 18);
			glLineWidth(1);

		
			if(row < 32)
			{
				draw_text(G_text_xplsv, t_scale);
			}
			else
			{
				draw_text(G_text_to_the_beat, t_scale);
			}

			glDisable(GL_BLEND);
		
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
	}
	restoreProjection();
	
}

void draw_text(float* text, float scale)
{
	
	glBegin(GL_LINES);
	
	int i, p, letter;
	int num_letters;
	int num_letter_segments;
	
	letter = 0;
	p = 0;
	num_letters = text[p]; p++;
	
	float s = scale; //40; // scale
	float t_i = 1.4; // translate increase
	float t = -t_i * s * num_letters * 0.5; // translate
	
	while(letter < num_letters)
	{
		num_letter_segments = text[p]; p++;
		for(i = 0; i < num_letter_segments; i++)
		{
			glVertex3f(0, text[p+1] * s, (text[p] * s + t)); p+=2;
			glVertex3f(0, text[p+1] * s, (text[p] * s + t)); p+=2;
		}
		letter++;
		t += s*t_i;
	}
	
	glEnd();
}

// utils......

void setOrtho(float xres, float yres)
{
	float xhalf, yhalf;
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	
	
	xhalf = (xres==-1) ? (G_width)*0.5 : xres*0.5;
	yhalf = (yres==-1) ? (G_height)*0.5 : yres*0.5;
	glViewport(0, 0, G_width, G_height);
	glOrtho(-xhalf, xhalf, -yhalf, yhalf, 0.0f, 200.0f);
}

void restoreProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

float rrand(float min, float max)
{
	float f = (float) rand() / RAND_MAX;
	return (f + min) * (max-min);
}

