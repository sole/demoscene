//--------------------------------------------------------------------------//
// iq . 2003 . code for the Paradise 64 kb intro by RGBA                    //
//--------------------------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include "../msys_libc.h"


static Display *hdis;
static GC hgc;
static Window hwnd;
static Pixmap hpix;


void msys_fontInit( uint64 h )
{
    hdis = (Display *)h;
int w = 0; // <-- get it
    hwnd = (Window)w;
}

void msys_fontStart( unsigned char *buffer, int xres, int yres )
{
    hpix = XCreatePixmap(hdis, hwnd, xres, yres, DefaultDepth(hdis, DefaultScreen(hdis)));
    hgc = XCreateGC(hdis, hpix, 0, 0);}

void msys_fontStop( unsigned char *buffer, int xres, int yres )
{
    XImage *img = XGetImage(hdis,  hpix, 0 , 0, xres, yres, AllPlanes, ZPixmap);
    memcpy(buffer, img->data, xres*yres*4);
}

void msys_fontPrint( char *str, int size, int xo, int yo )
{
    char buffer[100];
    // draw text
	static int  fontloaded = 0;
	static Font arialf;
	if( !fontloaded )
	    {
	    arialf = XLoadFont( hdis, "-bitstream-charter-medium-r-normal--30-*-*-*-*-*-*-*");
		fontloaded = 1;
        }

	XSetForeground( hdis, hgc, 0xffffffff);
	XSetFont(hdis, hgc, arialf );


    while( str[0] )
        {    
        //TextOut( hdc, xo, yo, str, strlen(str) );
	    XDrawString(hdis, hpix, hgc,
	             xo, yo+30, str, strlen(str));
        yo += 36;

        str+=1+strlen(str);
        if( str[0]=='\n') 
            {
            yo+=36; str++; 
            }
        }
}
