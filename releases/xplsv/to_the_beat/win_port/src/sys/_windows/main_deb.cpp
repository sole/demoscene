//--------------------------------------------------------------------------//
// iq . 2003/2008 . code for 64 kb intros by RGBA                           //
//--------------------------------------------------------------------------//

#define XRES         800
#define YRES         600

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <string.h>
#include <stdio.h>
#include "../../intro.h"
#include "../msys.h"
#include "../events.h"
#include "../player.h"

//----------------------------------------------------------------------------

typedef struct
{
    //---------------
    HINSTANCE   hInstance;
    HDC         hDC;
    HGLRC       hRC;
    HWND        hWnd;
    //---------------
    int         full;
    //---------------
    EVENTINFO   events;
}WININFO;



static const PIXELFORMATDESCRIPTOR pfd =
{
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    32,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    32,             // zbuffer
    0,              // stencil!
    0,
    PFD_MAIN_PLANE,
    0, 0, 0, 0
};


static const char fnt_wait[]    = "arial";
static const char msg_wait[]   = "wait while loading...";
static const char msg_error[] = "intro_init()!\n\n"\
                             "  no memory?\n"\
                             "  no music?\n"\
                             "  no sjades?";
static const char wndclass[] = "rgba_intro";

//----------------------------------------------------------------------------

// n = [0..200]
static void loadbar( void *data, int n )
{
    WININFO *info = (WININFO*)data;

    const int xo = (( 28*XRES)>>8);
    const int y1 = ((200*YRES)>>8);
    const int yo = y1-8;

    // draw background
    SelectObject( info->hDC, CreateSolidBrush(0x0045302c) );
    Rectangle( info->hDC, 0, 0, XRES, YRES );

    // draw text
    SetBkMode( info->hDC, TRANSPARENT );
    SetTextColor( info->hDC, 0x00ffffff );
    SelectObject( info->hDC, CreateFont( 44,0,0,0,0,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"arial") );
    TextOut( info->hDC, (XRES-318)>>1, (YRES-38)>>1, "wait while loading...", 21 );

    // draw bar
    SelectObject( info->hDC, CreateSolidBrush(0x00705030) );
    Rectangle( info->hDC, xo, yo, (228*XRES)>>8, y1 );
    SelectObject( info->hDC, CreateSolidBrush(0x00f0d0b0) );
    Rectangle( info->hDC, xo, yo, ((28+n)*XRES)>>8, y1 );
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

static WININFO     wininfo;

EVENTINFO *getEvents( void )
{
    return &wininfo.events;
}

int getKeyPress( int key )
{
    int res;

    res = wininfo.events.keyb.press[key];
    wininfo.events.keyb.press[key] = 0;
    return res;
}


static void procMouse( void )
{
    POINT   p;
    int     i;

    wininfo.events.keyb.state[KEY_LEFT]     = GetAsyncKeyState( VK_LEFT );
	wininfo.events.keyb.state[KEY_RIGHT]    = GetAsyncKeyState( VK_RIGHT );
	wininfo.events.keyb.state[KEY_UP]       = GetAsyncKeyState( VK_UP );
    wininfo.events.keyb.state[KEY_PGUP]     = GetAsyncKeyState( VK_PRIOR );
    wininfo.events.keyb.state[KEY_PGDOWN]   = GetAsyncKeyState( VK_NEXT );
	wininfo.events.keyb.state[KEY_DOWN]     = GetAsyncKeyState( VK_DOWN );
	wininfo.events.keyb.state[KEY_SPACE]    = GetAsyncKeyState( VK_SPACE );
	wininfo.events.keyb.state[KEY_RSHIFT]   = GetAsyncKeyState( VK_RSHIFT );
	wininfo.events.keyb.state[KEY_RCONTROL] = GetAsyncKeyState( VK_RCONTROL );
	wininfo.events.keyb.state[KEY_LSHIFT]   = GetAsyncKeyState( VK_LSHIFT );
	wininfo.events.keyb.state[KEY_LCONTROL] = GetAsyncKeyState( VK_LCONTROL );
	wininfo.events.keyb.state[KEY_1]        = GetAsyncKeyState( '1' );
	wininfo.events.keyb.state[KEY_2]        = GetAsyncKeyState( '2' );
	wininfo.events.keyb.state[KEY_3]        = GetAsyncKeyState( '3' );
	wininfo.events.keyb.state[KEY_4]        = GetAsyncKeyState( '4' );
	wininfo.events.keyb.state[KEY_5]        = GetAsyncKeyState( '5' );
	wininfo.events.keyb.state[KEY_6]        = GetAsyncKeyState( '6' );
	wininfo.events.keyb.state[KEY_7]        = GetAsyncKeyState( '7' );
	wininfo.events.keyb.state[KEY_8]        = GetAsyncKeyState( '8' );
	wininfo.events.keyb.state[KEY_9]        = GetAsyncKeyState( '9' );
	wininfo.events.keyb.state[KEY_0]        = GetAsyncKeyState( '0' );
    for( i=KEY_A; i<=KEY_Z; i++ )
	    wininfo.events.keyb.state[i] = GetAsyncKeyState( 'A'+i-KEY_A );

    //-------
    GetCursorPos( &p );

	wininfo.events.mouse.ox = wininfo.events.mouse.x;
	wininfo.events.mouse.oy = wininfo.events.mouse.y;
	wininfo.events.mouse.x = p.x;
	wininfo.events.mouse.y = p.y;
	wininfo.events.mouse.dx =  wininfo.events.mouse.x - wininfo.events.mouse.ox;
	wininfo.events.mouse.dy =  wininfo.events.mouse.y - wininfo.events.mouse.oy;

	wininfo.events.mouse.obuttons[0] = wininfo.events.mouse.buttons[0];
	wininfo.events.mouse.obuttons[1] = wininfo.events.mouse.buttons[1];
	wininfo.events.mouse.buttons[0] = GetAsyncKeyState(VK_LBUTTON);
	wininfo.events.mouse.buttons[1] = GetAsyncKeyState(VK_RBUTTON);

	wininfo.events.mouse.dbuttons[0] = wininfo.events.mouse.buttons[0] - wininfo.events.mouse.obuttons[0];
	wininfo.events.mouse.dbuttons[1] = wininfo.events.mouse.buttons[1] - wininfo.events.mouse.obuttons[1];
}

//----------------------------------------------------------------------------

static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    int i;

	// salvapantallas
	if( uMsg==WM_SYSCOMMAND && (wParam==SC_SCREENSAVE || wParam==SC_MONITORPOWER) )
		return( 0 );

	// boton x o pulsacion de escape
	if( uMsg==WM_CLOSE || uMsg==WM_DESTROY || (uMsg==WM_KEYDOWN && wParam==VK_ESCAPE) )
	{
		PostQuitMessage(0);
        return( 0 );
	}

    if( uMsg==WM_CHAR )
    {
        int conv = 0;
        switch( wParam )
        {
            case VK_LEFT:     conv = KEY_LEFT;     break;
            case VK_RIGHT:    conv = KEY_RIGHT;    break;
            case VK_UP:       conv = KEY_UP;       break;
            case VK_PRIOR:    conv = KEY_PGUP;     break;
            case VK_NEXT:     conv = KEY_PGDOWN;   break;
            case VK_DOWN:     conv = KEY_DOWN;     break;
            case VK_SPACE:    conv = KEY_SPACE;    break;
            case VK_RSHIFT:   conv = KEY_RSHIFT;   break;
            case VK_RCONTROL: conv = KEY_RCONTROL; break;
            case VK_LSHIFT:   conv = KEY_LSHIFT;   break;
            case VK_LCONTROL: conv = KEY_LCONTROL; break;
        }
        
        for( i=KEY_A; i<=KEY_Z; i++ )
        {
            if( wParam==(WPARAM)('A'+i-KEY_A) )
                conv = i;
            if( wParam==(WPARAM)('a'+i-KEY_A) )
                conv = i;
        }

        wininfo.events.keyb.press[conv] = 1;

        if( wParam==VK_ESCAPE )
        {
            PostQuitMessage(0);
            return( 0 );
        }
    }

    return( DefWindowProc(hWnd,uMsg,wParam,lParam) );
}

static void window_end( WININFO *info )
{
    if( info->hRC )
    {
        wglMakeCurrent( 0, 0 );
        wglDeleteContext( info->hRC );
    }

    if( info->hDC  ) ReleaseDC( info->hWnd, info->hDC );
    if( info->hWnd ) DestroyWindow( info->hWnd );

    UnregisterClass( wndclass, info->hInstance );

    if( info->full )
    {
        ChangeDisplaySettings( 0, 0 );
		while( ShowCursor( 1 )<0 ); // show cursor
    }
}

static int window_init( WININFO *info )
{
	unsigned int	PixelFormat;
    DWORD			dwExStyle, dwStyle;
    DEVMODE			dmScreenSettings;
    WNDCLASS		wc;
    RECT			rec;

    msys_memset( &wc, 0, sizeof(WNDCLASS) );
    wc.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = info->hInstance;
    wc.lpszClassName = wndclass;
    //wc.hbrBackground=(HBRUSH)CreateSolidBrush(0x00785838);
	
    if( !RegisterClass(&wc) )
        return( 0 );

    if( info->full )
    {
        msys_memset( &dmScreenSettings,0,sizeof(DEVMODE) );
        dmScreenSettings.dmSize       = sizeof(DEVMODE);
        dmScreenSettings.dmFields     = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmPelsWidth  = XRES;
        dmScreenSettings.dmPelsHeight = YRES;

        if( ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
            return( 0 );

        dwExStyle = WS_EX_APPWINDOW;
        dwStyle   = WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

		while( ShowCursor( 0 )>=0 );	// hide cursor
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle   = WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
    }

    rec.left   = 0;
    rec.top    = 0;
    rec.right  = XRES;
    rec.bottom = YRES;

    AdjustWindowRect( &rec, dwStyle, 0 );

    info->hWnd = CreateWindowEx( dwExStyle, wc.lpszClassName, wc.lpszClassName, dwStyle,
                               (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,
                               (GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
                               rec.right-rec.left, rec.bottom-rec.top, 0, 0, info->hInstance, 0 );

    if( !info->hWnd )
        return( 0 );

    if( !(info->hDC=GetDC(info->hWnd)) )
        return( 0 );

    if( !(PixelFormat=ChoosePixelFormat(info->hDC,&pfd)) )
        return( 0 );

    if( !SetPixelFormat(info->hDC,PixelFormat,&pfd) )
        return( 0 );

    if( !(info->hRC=wglCreateContext(info->hDC)) )
        return( 0 );

    if( !wglMakeCurrent(info->hDC,info->hRC) )
        return( 0 );
    
    //SetForegroundWindow( info->hWnd );    // slightly higher priority
    //SetFocus( info->hWnd );               // sets keyboard focus to the window
    
    return( 1 );
}


//----------------------------------------------------------------------------

static void DrawTime( WININFO *info, float t )
{
    static int      frame=0;
    static float    to=0.0;
    static int      fps=0;
    char            str[64];
    int             s, m, c;

    if( t<0.0f) return;
    if( info->full ) return;

    frame++;
    if( (t-to)>1.0f )
    {
        fps = frame;
        to = t;
        frame = 0;
    }

    if( !(frame&3) )
    {
        m = msys_ifloorf( t/60.0f );
        s = msys_ifloorf( t-60.0f*(float)m );
        c = msys_ifloorf( t*100.0f ) % 100;
        sprintf( str, "%02d:%02d:%02d  [%d fps]", m, s, c, fps );
        SetWindowText( info->hWnd, str );
    }
}

void calcula( void );
#include "../../sorollet.h"
#include "../../data/song.h"
#define BUFFER_SIZE 2048


float sound_buffer[BUFFER_SIZE * 2];
static int finished = 0;

static void func( short *dst_buf, int num )
{

    int i;
    int num_samples = num*2; // KKDEVACA//len >> 1; // as we use signed 16 bit samples, it means we use 2 bytes per sample
    static int position = 0;
	float position_seconds = (float)position / (float) PLAYER_RATE;
	float volume = 0.75f;
	

	finished = sorollet_play(position_seconds);
	
	sorollet_get_buffer(sound_buffer, position, num);
	
	static float fase = 0.0f;

	for (i=0; i < num_samples; ++i)
	{
		float v = sound_buffer[i] * volume;

		if (v > 1.0f)
			v = 1.0f;
		else if (v < -1.0f)
			v = -1.0f;
		dst_buf[i] = (short)(32767.0f*v);
		
   	}
    position += num_samples/2;

	#ifdef OUTFILE
		fwrite(dst_buf, sizeof(Sint16), num_samples, fout);
	#endif
	
}

int WINAPI WinMain( HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    MSG         msg;

//    calcula(); return( 0 );
    if( !msys_debugInit() )
        return 0;

    wininfo.hInstance = GetModuleHandle( 0 );

    //if( MessageBox( 0, "fullscreen?", info->wndclass, MB_YESNO|MB_ICONQUESTION)==IDYES )
    //   info->full++;

    if( !window_init(&wininfo) )
    {
        window_end( &wininfo );
        MessageBox( 0, msg_error,0,MB_OK|MB_ICONEXCLAMATION );
        return( 0 );
    }

    if( !msys_init((intptr)wininfo.hWnd) ) 
    {
        window_end( &wininfo );
        MessageBox( 0, msg_error,0,MB_OK|MB_ICONEXCLAMATION );
        return( 0 );
    }

    IntroProgressDelegate pd = { &wininfo, loadbar };
    if( !intro_init( XRES, YRES, 1, &pd ) )
    {
        window_end( &wininfo );
        MessageBox( 0, msg_error, 0, MB_OK|MB_ICONEXCLAMATION );
        return( 0 );
    }

	sorollet_init(PLAYER_RATE, /*AUDIO_S16SYS,*/ PLAYER_NUMCHANNELS, BUFFER_SIZE);
	sorollet_load_song_from_array((char*)song);

	if( !PLAYER_Init( func, 0 ) )
	{
		window_end( &wininfo );
        MessageBox( 0, msg_error, 0, MB_OK|MB_ICONEXCLAMATION );
        return( 0 );
	}


	PLAYER_Start();

    while( !finished )
    {
        if( PeekMessage(&msg,0,0,0,PM_REMOVE) )
        {
            if( msg.message==WM_QUIT ) finished=1;
		    TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            procMouse();
			float time = PLAYER_GetTime();


            intro_do(1000.0f*time);

            //static long to = 0; if( !to ) to=timeGetTime(); 
            //float t = 0.001f * (float)(timeGetTime() - to);
            SwapBuffers( wininfo.hDC );

            DrawTime( &wininfo, time );
        }
    }

    intro_end();

    window_end( &wininfo );

	PLAYER_End();

    msys_debugEnd();


    return( 0 );
}



