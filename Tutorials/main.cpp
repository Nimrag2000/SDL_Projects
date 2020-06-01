#include <stdio.h>
#include <iostream>
#include <string>

#include "SDL.h"

using namespace std;

/*----------------------------------------------------------------------------
Local Constants
----------------------------------------------------------------------------*/
#define SCREEN_WIDTH    (750)
#define SCREEN_HEIGHT   (750)

/*----------------------------------------------------------------------------
Data Types
----------------------------------------------------------------------------*/
typedef enum
{
    LUIGI_GREEN_JUMP_LEFT,
    LUIGI_GREEN_STOP_LEFT,
    LUIGI_GREEN_WALK_LEFT_3,
    LUIGI_GREEN_WALK_LEFT_2,
    LUIGI_GREEN_WALK_LEFT_1,
    LUIGI_GREEN_STAND_LEFT,

    LUIGI_GREEN_JUMP_RIGHT,
    LUIGI_GREEN_STOP_RIGHT,
    LUIGI_GREEN_WALK_RIGHT_3,
    LUIGI_GREEN_WALK_RIGHT_2,
    LUIGI_GREEN_WALK_RIGHT_1,
    LUIGI_GREEN_STAND_RIGHT,

    SPRITE_COUNT
} sprite_id_type;

typedef struct
{
    int                 x;
    int                 y;
    int                 w;
    int                 h;
} sprite_info_type;

static sprite_info_type      s_sprite_info[ SPRITE_COUNT ];

/*----------------------------------------------------------------------------
Static Variables
----------------------------------------------------------------------------*/
SDL_Window  *sWindow            = nullptr;
SDL_Surface *sScreenSurface     = nullptr;
SDL_Surface * sBMP_gogeta       = nullptr;
SDL_Surface * sCurrentSurface   = nullptr;
static bool sQuit               = false;
static double sXcurr            = 0;
static double sYcurr            = 0;
static double sXstart           = 0;
static double sYstart           = 0;
static Uint32 sTstartX          = 0;
static Uint32 sTstartY          = 0;
static double sVx               = 0;
static double sVy               = 0;
static SDL_Rect srcRect         = { 0 };
static SDL_Rect dstRect         = { 0 };
static const double mvmntSpeed  = 20.0;

/*----------------------------------------------------------------------------
Procedures
----------------------------------------------------------------------------*/
static void deinit
    (
    void
    );

static bool init
    (
    void
    );

static bool loadMedia
(
    void
);

SDL_Surface * loadSurface( string path );



/*----------------------------------------------------------------------------
PROCEDURE: deinit
----------------------------------------------------------------------------*/
static void deinit
    (
    void
    )
{
SDL_FreeSurface(sBMP_gogeta);
sBMP_gogeta = nullptr;

SDL_DestroyWindow( sWindow );
sWindow = nullptr;

SDL_Quit();
}   /* deinit() */


/*----------------------------------------------------------------------------
PROCEDURE: init
----------------------------------------------------------------------------*/
static bool init
    (
    void
    )
{
if( 0 > SDL_Init( SDL_INIT_VIDEO ) )
    {
    return( false );
    }

sWindow = SDL_CreateWindow( "yo", 
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                            SCREEN_WIDTH, SCREEN_HEIGHT, 
                            SDL_WINDOW_SHOWN );
if( nullptr == sWindow )
    {
    return( false );
    }

sScreenSurface = SDL_GetWindowSurface( sWindow );

return( true );
}   /* init() */


/*----------------------------------------------------------------------------
PROCEDURE: loadMedia
----------------------------------------------------------------------------*/
static bool loadMedia
    (
    void
    )
{
s_sprite_info[LUIGI_GREEN_JUMP_LEFT  ] = {  29,   0,  17,  16 };
s_sprite_info[LUIGI_GREEN_STOP_LEFT  ] = {  60,   0,  14,  16 };
s_sprite_info[LUIGI_GREEN_WALK_LEFT_3] = {  89,   0,  16,  16 };
s_sprite_info[LUIGI_GREEN_WALK_LEFT_2] = { 121,   0,  12,  16 };
s_sprite_info[LUIGI_GREEN_WALK_LEFT_1] = { 150,   0,  14,  16 };
s_sprite_info[LUIGI_GREEN_STAND_LEFT ] = { 181,   0,  13,  16 };

s_sprite_info[LUIGI_GREEN_JUMP_RIGHT  ] = { 359,   0,  17,  16 };
s_sprite_info[LUIGI_GREEN_STOP_RIGHT  ] = { 331,   0,  14,  16 };
s_sprite_info[LUIGI_GREEN_WALK_RIGHT_3] = { 300,   0,  16,  16 };
s_sprite_info[LUIGI_GREEN_WALK_RIGHT_2] = { 272,   0,  12,  16 };
s_sprite_info[LUIGI_GREEN_WALK_RIGHT_1] = { 241,   0,  14,  16 };
s_sprite_info[LUIGI_GREEN_STAND_RIGHT ] = { 211,   0,  13,  16 };

bool success = true;
sBMP_gogeta = SDL_LoadBMP( "images/luigiSprite.bmp" );
if( nullptr == sBMP_gogeta )
{
    return( false );
}

return( true );
}   /* loadMedia() */



/*----------------------------------------------------------------------------
PROCEDURE: loadSurface
----------------------------------------------------------------------------*/

SDL_Surface* loadSurface( std::string path )
    {

        SDL_Surface * optimizedSurface = NULL;
        //Load image at specified path
        SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if ( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface( loadedSurface, sScreenSurface -> format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface( loadedSurface );
            
    }

    return loadedSurface;
    }


/*----------------------------------------------------------------------------
PROCEDURE: pollEvent
----------------------------------------------------------------------------*/

void pollEvent()
{
    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
        {
            sQuit = true;
        }
    }

    const Uint8 * currentKeyState = SDL_GetKeyboardState( NULL );
    if( currentKeyState[ SDL_SCANCODE_W ] )
    {
        sVy = 10;
        sTstartY = SDL_GetTicks();
        sYstart = sYcurr;
    }
    else
    {
        sYstart = sYcurr;
        sVy = 0;
    }

    if( ( currentKeyState[SDL_SCANCODE_A] ) && ( sVx >= 0 ) )
    {
        sVx = -mvmntSpeed;
        sTstartX = SDL_GetTicks();
        sXstart = sXcurr;
    }
    else if( ( currentKeyState[SDL_SCANCODE_D] ) && ( sVx <= 0 ) )
    {
        sVx = mvmntSpeed;
        sTstartX = SDL_GetTicks();
        sXstart = sXcurr;
    }
    else if( !currentKeyState[SDL_SCANCODE_A]  && !currentKeyState[SDL_SCANCODE_D] )
    {
        sXstart = sXcurr;
        sVx = 0;
    }

}

/*----------------------------------------------------------------------------
PROCEDURE: calcState
----------------------------------------------------------------------------*/
void calcState()
{
    double deltaX = sVx * (double)( SDL_GetTicks() - sTstartX ) / 1000.0 ;
    sXcurr = ( sXstart + deltaX );   
}

/*----------------------------------------------------------------------------
PROCEDURE: main
----------------------------------------------------------------------------*/
int main
    ( 
    int     argc, 
    char   *args[]
    )
{
sprite_id_type  sprite_id  = LUIGI_GREEN_STAND_RIGHT;



if( ( false == init()      ) ||
    ( false == loadMedia() ) )
    {
    return( -1 );
    }

while( !sQuit )
{
    pollEvent();
    calcState();

    SDL_FillRect( sScreenSurface, NULL, SDL_MapRGB( sScreenSurface->format, 0x00, 0x00, 0x00 ) );

    //SDL_SetSurfaceBlendMode( sScreenSurface, SDL_BLENDMODE_BLEND  );
    //SDL_SetSurfaceBlendMode( sBMP_gogeta, SDL_BLENDMODE_BLEND  );
    srcRect.x = s_sprite_info[sprite_id].x;
    srcRect.y = s_sprite_info[sprite_id].y;
    srcRect.w = s_sprite_info[sprite_id].w;
    srcRect.h = s_sprite_info[sprite_id].h;
    
    dstRect.x = (int)sXcurr;
    dstRect.y = sScreenSurface->h - srcRect.h;
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;

    SDL_BlitSurface( sBMP_gogeta, &srcRect, sScreenSurface, &dstRect );
    SDL_UpdateWindowSurface( sWindow );
}
deinit();

return( 0 );
}   /* main() */


