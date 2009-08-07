//--------------------------------------------------------------------------//
// iq . 2003/2008 . code for 64 kb intros by RGBA                           //
//--------------------------------------------------------------------------//

#ifdef WINDOWS
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "sys/msys.h"
#include "intro.h"
#include "sorollet.h"

typedef struct
{
    long    mTo;
}IntroObject;

// Globals
int G_width;
int G_height;

float G_color_arena[3] = {1.0f, 0.87f, 0.33f};

float G_color_tri1[3] = {0.478f, 0.823f, 0.921f};
float G_color_tri2[3] = {0.788f, 0.658f, 0.886f};

//float G_color_grid[3] = {1.0, 1.0, 0.0};
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

//--------------------------------------------------------
static IntroObject intro;

int intro_init( int xr, int yr, int nomusic, IntroProgressDelegate *pd )
{
    // progress report, (from 0 to 200)
    pd->func( pd->obj, 0 );

	G_width = xr;
	G_height = yr;
    
    // init your stuff here (mzk player, intro, ...)
    // remember to call pd->func() regularly to update the loading bar


    pd->func( pd->obj, 200 );

    intro.mTo = msys_timerGet();
    return 1;
}

void intro_end( void )
{    
    // deallicate your stuff here
}


//---------------------------------------------------------------------

void intro_effect_arena(float ticks, int order, int pattern, int row);
void intro_effect_two_parts(float ticks, int order, int pattern, int row);
void draw_text(float* text, float scale);


// aux's
void setOrtho(float xres, float yres);
void restoreProjection();
float rrand(float, float);

int intro_do( float ticks )
{
    //float ticks = (float)(msys_timerGet() - intro.mTo);

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

	// printf("%d\n", order);
	
	//glClearColor(0.8, 0, 0.3, 0);
	//glClearColor(0.65, 0.623, 0.254, 0);
	glClearColor(0.22f, 0.215f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	setOrtho((float)G_width, (float)G_height);
	
	intro_effect_two_parts(ticks, order, pattern, row);

	
	restoreProjection();
	
	return 0;


/*
    // animate your intro here

    // render your intro here
    glClearColor( 0.1f, 0.2f, 0.3f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    
    glBegin( GL_TRIANGLES );
        glColor4f( 0.1f, 0.2f, 0.3f, 1.0f );
        glVertex3f( 0.0f, 0.0f, 0.0f );
        glVertex3f( msys_sinf(time), msys_cosf(time), 0.0f );
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
        glVertex3f( msys_sinf(time+0.5f), msys_cosf(time+0.5f), 0.0f );
    glEnd();
*/
	return( 0 );
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
	
	float camera_fov = 90.0f, camera_aspect = 1.3f, camera_zNear = 1.0f, camera_zFar = 1000.0f;
	//float eyeX = -50, eyeY = 0, eyeZ = 40, centerX = 40, centerY = 0, centerZ = 0, upX = 0, upY = 1, upZ = 0;
	float eyeX = -90.0f, eyeY = 0.0f, eyeZ = 30.0f, centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f, upX = 0.0f, upY = 1.0f, upZ = 0.0f;
	
	elapsed_ticks = ticks - last_tick;
	last_tick = ticks;
	
	if(order < main_order)
	{
		camera_fov = 100;
		eyeX = (float)(-250 + row);
		
		//eyeX = -350 + 150*sin(ticks*0.005);
		//eyeZ = -350 - 150*cos(ticks*0.005);
		//eyeZ = 100;
		// centerX = 250;
		//centerZ = -300;
	}
	else
	{
		float radius = 120.0f;
		camera_fov = 120.0f;
		float ang = ticks * 0.0008f;
		eyeX = /*-90 + */radius*sinf(ang);
		eyeY = radius*cosf(ang);
	}
	
	int bd_note = sorollet_get_channel_note(0);
	
	if(bd_note == 48)
	{
		extra += 5;
	}
	
	if(extra > 0)
	{
		float am =  0.75f * elapsed_ticks;
		
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
			rotation_y = - 0.25f * rotation;
		else
			rotation_x = 0.25f * rotation;
	}
	

	float w = (float)G_width * 0.5f;
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
	int j;
	int grid = 30;
	int grid_inc = 4 * G_width / grid;
	float grid_top = (float)(G_width  * 2) ;
	float xpos = -grid_top, ypos;
	int wider_each = 5;
	
	if(order >= main_order && order < ending_order + 2)
	
	{
		glColor4ubv(G_color_grid);
	
		glEnable(GL_BLEND);
		//glBlendEquation(GL_FUNC_SUBTRACT);
		//glBlendEquation(GL_FUNC_ADD);
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
			glRotatef(4.0f, 0.0f, 0.0f, 1.0f);
		
			glColor3fv(G_color_tri1);
	
			//glLineWidth(4.5 + 2*sin(i + ticks));
			glLineWidth(2);
		
			y = 4.0f*s*(float)sin(i+ticks*0.00001);
		
			glBegin(GL_LINE_STRIP);
				glVertex3f(s + rrand(-v, v), s + rrand(-v, v), y + rrand(-v, v));
				glVertex3f(-s + rrand(-v, v), s + rrand(-v, v), y + rrand(-v, v));
				glVertex3f(-s + rrand(-v, v), -s + rrand(-v, v), y + rrand(-v, v));
				//glVertex2f(s, s);
			glEnd();
		
			//glColor3fv(G_color_tri1);
	
			glBegin(GL_LINE_STRIP);
				glVertex3f(-s + rrand(-v, v), -s + rrand(-v, v),  y + rrand(-v, v));
				glVertex3f(s + rrand(-v, v), -s + rrand(-v, v), y + rrand(-v, v));
				glVertex3f(s + rrand(-v, v), s + rrand(-v, v), y + rrand(-v, v));
				//glVertex2f(-s, -s);
			glEnd();
		
			s += 10;
		}
	
		glPopMatrix();
	}
	int t = 0;
	int rand_range = 6;
	float t_scale;
	//unsigned char alpha;
	
	//if((((int)ticks % 2) == 0) && (order < main_order))
	
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
		glTranslatef((float)rrand(0, (float)rand_range), (float)rrand(0, (float)rand_range), (float)rrand(0, (float)rand_range));
		//intro_effect_draw_text(ticks, order, pattern, row);

		glColor3ubv(G_color_text);
		glLineWidth(1.0f);
	
	
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
			glRotatef(90.0f, 0,1, 0);
			glRotatef(20.0f, -1, 0, 0);
			glTranslatef(0.0f, (float)(128-((row<<4)%256)), 0.0f);
			glTranslatef(rrand(0, (float)rand_range), rrand(0, (float)rand_range), rrand(0, (float)rand_range));
			//intro_effect_draw_text(ticks, order, pattern, row);

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
	num_letters = (int)text[p]; p++;
	
	float s = scale; //40; // scale
	float t_i = 1.4f; // translate increase
	float t = -t_i * s * num_letters * 0.5f; // translate
	
	while(letter < num_letters)
	{
		num_letter_segments = (int)text[p]; p++;
		for(i = 0; i < num_letter_segments; i++)
		{
			//glVertex3f(text[p] * s + t, text[p+1] * s, 0); p+=2;
			//glVertex3f(text[p] * s + t, text[p+1] * s, 0); p+=2;
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
	
	
	xhalf = (xres==-1) ? (G_width)*0.5f : xres*0.5f;
	yhalf = (yres==-1) ? (G_height)*0.5f : yres*0.5f;
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
	//float f = (float) rand() / RAND_MAX;
	float f = (float)msys_rand() / 32767.0f;

	return (f + min) * (max-min);
}