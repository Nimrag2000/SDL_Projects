#include <stdio.h>
#include <iostream>

#include "SDL.h"

/*----------------------------------------------------------------------------
Local Constants
----------------------------------------------------------------------------*/
#define SCREEN_WIDTH    (750)
#define SCREEN_HEIGHT   (750)

/*----------------------------------------------------------------------------
Static Variables
----------------------------------------------------------------------------*/
SDL_Window  *sWindow            = nullptr;
SDL_Surface *sScreenSurface     = nullptr;
SDL_Surface *sBMP_EmojiNerd     = nullptr;

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


/*----------------------------------------------------------------------------
PROCEDURE: deinit
----------------------------------------------------------------------------*/
static void deinit
    (
    void
    )
{
SDL_FreeSurface( sBMP_EmojiNerd );
sBMP_EmojiNerd = nullptr;

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
sBMP_EmojiNerd = SDL_LoadBMP( "images/nerd-whatsapp-emoji.bmp" );
if( nullptr == sBMP_EmojiNerd )
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

if( ( false == init()      ) ||
    ( false == loadMedia() ) )
    {
    return( -1 );
    }

//SDL_FillRect( sScreenSurface, NULL, SDL_MapRGB( sScreenSurface->format, 0x00, 0x00, 0x00 ) );
//SDL_UpdateWindowSurface( sWindow );

SDL_BlitSurface( sBMP_EmojiNerd, NULL, sScreenSurface, NULL );
SDL_UpdateWindowSurface( sWindow );

SDL_Delay( 2000 );

deinit();

return( 0 );
}   /* main() */


