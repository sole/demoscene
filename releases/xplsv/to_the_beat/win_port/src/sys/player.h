//--------------------------------------------------------------------------//
// iq . 2003 . code for the Paradise 64 kb intro by RGBA                    //
//--------------------------------------------------------------------------//

#ifndef _PLAYER_H_
#define _PLAYER_H_


typedef void (* SINTE_CALLBACK)( short *ptr, int num );

#define PLAYER_RATE         44100
#define PLAYER_NUMCHANNELS  2
#define SONG_DURATION       211

int   PLAYER_Init( SINTE_CALLBACK func, int muted );
void  PLAYER_End( void );
void  PLAYER_Start( void );
float PLAYER_GetTime( void );

#endif
