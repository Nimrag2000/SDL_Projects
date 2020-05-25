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
key presses
-----------------------------------------------------------------------------*/
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

/*----------------------------------------------------------------------------
Static Variables
----------------------------------------------------------------------------*/
SDL_Window  *sWindow            = nullptr;
SDL_Surface *sScreenSurface     = nullptr;
SDL_Surface * sBMP_gogeta       = nullptr;
SDL_Surface * sBMP_vegeta       = nullptr;
SDL_Surface * sKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
SDL_Surface * sCurrentSurface   = nullptr; //added
SDL_Surface * loadSurface( string path );//added

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

sWindow = SDL_CreateWindow( "Mike's Tutorial", 
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
sBMP_gogeta = SDL_LoadBMP( "images/spriteSheet2.bmp" );
if( nullptr == sBMP_gogeta )
    {
    return( false );
    }

return( true );
}   /* loadMedia() */


/*----------------------------------------------------------------------------
PROCEDURE: main
----------------------------------------------------------------------------*/
int main
    ( 
    int     argc, 
    char   *args[]
    )
{

bool quit = false;
SDL_Event e;

SDL_Rect srcRect;
SDL_Rect dstRect;

if( ( false == init()      ) ||
    ( false == loadMedia() ) )
    {
    return( -1 );
    }

while( !quit )
{
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
        
    }


SDL_FillRect( sScreenSurface, NULL, SDL_MapRGB( sScreenSurface->format, 0x00, 0x00, 0x00 ) );
//SDL_SetSurfaceBlendMode( sScreenSurface, SDL_BLENDMODE_BLEND  );
//SDL_SetSurfaceBlendMode( sBMP_gogeta, SDL_BLENDMODE_BLEND  );

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 40;
    srcRect.h = 57;
    
    dstRect.x = 0;
    dstRect.y = sScreenSurface->h - srcRect.h;
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
    
    
    
    for( int i = 0; i < 8; i++ )
    {
        srcRect.x = i * 40;
        SDL_BlitSurface(sBMP_gogeta, &srcRect, sScreenSurface, &dstRect);
        SDL_UpdateWindowSurface( sWindow );

        SDL_Delay( 100 );


    }
}
deinit();

return( 0 );
}   /* main() */


