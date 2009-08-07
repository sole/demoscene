#ifndef INTRO_H
#define INTRO_H

int intro_init(int width, int height);

int intro_play(float ticks);

void intro_effect_arena(float ticks, int order, int pattern, int row);
void intro_effect_two_parts(float ticks, int order, int pattern, int row);
void draw_text(float* text, float scale);


// aux's
void setOrtho(float xres, float yres);
void restoreProjection();
float rrand(float, float);

#endif
