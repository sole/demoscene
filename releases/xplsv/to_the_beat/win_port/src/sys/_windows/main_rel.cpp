//--------------------------------------------------------------------------//
// iq . 2003/2008 . code for 64 kb intros by RGBA                           //
//--------------------------------------------------------------------------//
#define XRES        1024
#define YRES        768

#ifdef A64BITS
#pragma pack(8) // VERY important, so WNDCLASS get's the correct padding and we don't crash the system
#endif

//#pragma check_stack(off)
//#pragma runtime_checks("", off)


#define ALLOWWINDOWED       // allow windowed mode

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <string.h>
#include "../../intro.h"
#include "../msys.h"
#include "../events.h"
#include "../player.h"

//----------------------------------------------------------------------------

typedef struct
{
    HINSTANCE   hInstance;
    HWND        hWnd;
    HDC         hDC;
    HGLRC       hRC;
    int         full;
}WININFO;

extern "C" int _fltused = 0;

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

static DEVMODE screenSettings = { {0},
    #if _MSC_VER < 1400
    0,0,148,0,0x001c0000,{0},0,0,0,0,0,0,0,0,0,{0},0,32,XRES,YRES,0,0,      // Visual C++ 6.0
    #else
    0,0,156,0,0x001c0000,{0},0,0,0,0,0,{0},0,32,XRES,YRES,{0}, 0,           // Visuatl Studio 2005
    #endif
    #if(WINVER >= 0x0400)
    0,0,0,0,0,0,
    #if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
    0,0
    #endif
    #endif
    };
static const char wndclass[] = "rgba_intro";
static const char msg_error[] = "no memory?\nno music?\nno shades?";



//----------------------------------------------------------------------------
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

static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( uMsg==WM_SYSCOMMAND && (wParam==SC_SCREENSAVE || wParam==SC_MONITORPOWER) )
		return 0 ;

	if( uMsg==WM_CLOSE || (uMsg==WM_KEYDOWN && wParam==VK_ESCAPE) )
	{
		PostQuitMessage(0);
        return 0 ;
	}

    return DefWindowProc(hWnd,uMsg,wParam,lParam);
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

    #ifdef ALLOWWINDOWED
    if( info->full )
    #endif
    {
        ChangeDisplaySettings( 0, 0 );
		ShowCursor( 1 ); 
    }
}

static int window_init( WININFO *info )
{
	unsigned int	PixelFormat;
    DWORD			dwExStyle, dwStyle;
    RECT			rec;
    WNDCLASSA		wc;

    info->hInstance = GetModuleHandle( 0 );

    msys_memset( &wc, 0, sizeof(WNDCLASSA) );

    wc.style         = CS_OWNDC;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = info->hInstance;
    wc.lpszClassName = wndclass;

    if( !RegisterClass((WNDCLASSA*)&wc) )
        return( 0 );

    #ifdef ALLOWWINDOWED
    if( info->full )
    #endif
    {
        if( ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
            return( 0 );
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle   = WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		ShowCursor( 0 );
    }
    #ifdef ALLOWWINDOWED
    else
    {
        dwExStyle = WS_EX_APPWINDOW;// | WS_EX_WINDOWEDGE;
        dwStyle   = WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
    }
    #endif
    rec.left   = 0;
    rec.top    = 0;
    rec.right  = XRES;
    rec.bottom = YRES;

    #ifdef ALLOWWINDOWED
    AdjustWindowRect( &rec, dwStyle, 0 );
    info->hWnd = CreateWindowEx( dwExStyle, wc.lpszClassName, wc.lpszClassName, dwStyle,
                               (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,
                               (GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
                               rec.right-rec.left, rec.bottom-rec.top, 0, 0, info->hInstance, 0 );
    #else
    info->hWnd = CreateWindowEx( dwExStyle, wc.lpszClassName, wc.lpszClassName, dwStyle, 0, 0, 
                                 rec.right-rec.left, rec.bottom-rec.top, 0, 0, info->hInstance, 0 );
    #endif

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
    
    SetForegroundWindow(info->hWnd);
    SetFocus(info->hWnd);

    return( 1 );
}


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


void entrypoint( void )
{
    WININFO     wininfo;
    MSG         msg;

    #ifdef ALLOWWINDOWED
    wininfo.full = ( MessageBox( 0, "fullscreen?", wndclass, MB_YESNO|MB_ICONQUESTION)==IDYES );
    #endif

    if( !window_init(&wininfo) )
    {
        window_end( &wininfo );
        MessageBox( 0,msg_error,0,MB_OK|MB_ICONEXCLAMATION );
        ExitProcess( 0 );
    }

    if( !msys_init((intptr)wininfo.hWnd) ) 
    {
        window_end( &wininfo );
        MessageBox( 0,msg_error,0,MB_OK|MB_ICONEXCLAMATION );
        ExitProcess( 0 );
    }

    IntroProgressDelegate pd = { &wininfo, loadbar };
    if( !intro_init( XRES, YRES, 0, &pd ) )
    {
        window_end( &wininfo );
        MessageBox( 0,msg_error,0,MB_OK|MB_ICONEXCLAMATION );
        ExitProcess( 0 );
    }

	sorollet_init(PLAYER_RATE, /*AUDIO_S16SYS,*/ PLAYER_NUMCHANNELS, BUFFER_SIZE);
	sorollet_load_song_from_array((char*)song);

	if( !PLAYER_Init( func, 0 ) )
	{
		window_end( &wininfo );
        MessageBox( 0, msg_error, 0, MB_OK|MB_ICONEXCLAMATION );
        return;
	}


	PLAYER_Start();


    while( !finished )
    {
        while( PeekMessage(&msg,0,0,0,PM_REMOVE) )
        {
            if( msg.message==WM_QUIT ) { finished=1; break; }
            DispatchMessage( &msg );
        }
		float time = PLAYER_GetTime();

        intro_do(1000.0f*time);
        SwapBuffers( wininfo.hDC );
    }

    intro_end();

    window_end( &wininfo );

	PLAYER_End();

    msys_end();

    ExitProcess( 0 );
}
