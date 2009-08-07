#include <stdlib.h>

#include "../msys_malloc.h"
#include "../msys_thread.h"
#include "../msys_timer.h"
#include "../msys_types.h"
#include "../msys_sound.h"
#include "../player.h"


#define PLAYER_NBLOCKS   200      // 64 bloques
#define PLAYER_LATENCY    20      // ms por bloque -> buffer=1.28 segundos 


#define CANCION_LENGTH	    PLAYER_RATE*SONG_DURATION
#define BLOCKSIZE_MUES  (PLAYER_LATENCY*PLAYER_RATE/1000)       // 2205
#define BUFFERLEN_BYTES (PLAYER_NBLOCKS*BLOCKSIZE_MUES*2*PLAYER_NUMCHANNELS)

//- - - - - - - - - -


static SINTE_CALLBACK   funccallback;
static long             th;
static float            to;
#ifdef DEBUG
static unsigned int    muted;
#endif
static unsigned int    salir;
static char             *wav_data;

//-----------------------------------------------------------------------------
#ifdef DEBUG
int kkpos = 0;
int kkdel = 0;
#endif


static unsigned int filledblock=0;




MSYS_INLINE void rellena( void )
{
	short   *ptr = (short*)wav_data;

	int off = filledblock;

	off %= PLAYER_NBLOCKS*BLOCKSIZE_MUES;

    funccallback( ptr+off*PLAYER_NUMCHANNELS, BLOCKSIZE_MUES );
    filledblock += BLOCKSIZE_MUES;
}


static void *sintetiza( void *data )
{

    unsigned int     cursorblock;
	int             newrend;
//int ttto, tttd=0;

    while( salir==2 )
        msys_timerSleep( 10 );

    while( !salir )
        {
		cursorblock = msys_soundGetPosInSamples();

#ifdef DEBUG
kkpos = filledblock/BLOCKSIZE_MUES;
kkdel = (filledblock-cursorblock)/BLOCKSIZE_MUES;
#endif

		newrend = 1;

		if( (filledblock-cursorblock)>((PLAYER_NBLOCKS-2)*BLOCKSIZE_MUES) )
			newrend = 0;

//		if( tttd>BLOCKSIZE_MUES && ((mrand()&65535)==0) )
//			newrend = 0;

		//if( (filledblock-cursorblock)<(8*BLOCKSIZE_MUES) )
		//	newrend = 1;

		if( newrend )
			{
			//ttto = cursorblock;

			rellena();
			
			//waveOutGetPosition( h, &mmt, sizeof(MMTIME) );
			//tttd = mmt.u.cb-ttto;
			}
		else
			{
///			tttd = 0;
			msys_timerSleep( 2 );
			}
        }

    salir = 0;

    return( 0 );

//ExitThread(0);
}



int PLAYER_Init( SINTE_CALLBACK func, int mut )
{
	short   *ptr;

	funccallback = func;

    wav_data = (char *)msys_mallocAlloc( BUFFERLEN_BYTES );
    if( !wav_data )
        return( 0 );

    if( !msys_soundInit( wav_data, BUFFERLEN_BYTES ) )
        return( 0 );

	ptr = (short*)wav_data;
	for( filledblock=0; filledblock<PLAYER_NBLOCKS; filledblock++ )
   	    funccallback( ptr+filledblock*BLOCKSIZE_MUES*PLAYER_NUMCHANNELS, BLOCKSIZE_MUES );
	filledblock*=BLOCKSIZE_MUES;


	salir = 2;
    th = msys_threadNew( (THREAD_FUNC)sintetiza );

    return( 1 );
}

void PLAYER_Start( void )
{
#ifdef DEBUG
    if( muted )
        {
        to = 0.001f*msys_timerGet();
        return;
        }
#endif
    msys_soundStart();

    salir = 0;
}

//-----------------------------------------------------------------------------

void PLAYER_End( void )
{
#ifdef DEBUG
    if( muted ) return;
#endif    
    salir = 1;

    while( salir )
        msys_timerSleep( 50 );

    msys_threadDelete( th );

    msys_soundEnd();

    msys_mallocFree( wav_data );
}



float PLAYER_GetTime( void )
{
#ifdef DEBUG
    if( muted )
        return( (float)(msys_timerGet()-to) );
#endif
    return( (float)msys_soundGetPosInSamples()/(float)PLAYER_RATE );
}   
