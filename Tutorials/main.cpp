#include <stdio.h>
#include <iostream>
#include <string>

#include "SDL.h"
#include "characterClass.h"

using namespace std;

/*----------------------------------------------------------------------------
Local Constants
----------------------------------------------------------------------------*/
#define SCREEN_WIDTH    (750)
#define SCREEN_HEIGHT   (750)
#define JOYSTICK_DEAD_ZONE (8000)

/*----------------------------------------------------------------------------
Data Types
----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------
Static Variables
----------------------------------------------------------------------------*/
SDL_Window  *sWindow            = nullptr;
SDL_Surface *sScreenSurface     = nullptr;
SDL_Surface * sBMP_gogeta       = nullptr;
SDL_Surface * sCurrentSurface   = nullptr;
static bool sQuit               = false;
SDL_Joystick * sGameController  = NULL;

static Character sLuigi;

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
if( 0 > SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) )
    {
    return( false );
    }

if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
{
    cout << "Warning: Linear texture filtering not enabled!\n";
}

if( SDL_NumJoysticks() < 1 )
{
    cout << "Warning: No controller connected!\n";
}
else
{
    sGameController = SDL_JoystickOpen( 0 );
    if( sGameController == NULL )
    {
        cout << "Warning: Unable to open game controller! SDL Error: " << SDL_GetError() ;
    }
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

bool success = true;
sBMP_gogeta = SDL_LoadBMP( "images/luigiSprite.bmp" );
if( nullptr == sBMP_gogeta )
{
    return( false );
}

sLuigi.addActionSprite( sLuigi.ACTION_STILL_LEFT,   sBMP_gogeta, 181, 0, 13, 16 );
sLuigi.addActionSprite( sLuigi.ACTION_STILL_RIGHT,  sBMP_gogeta, 211, 0, 13, 16 );
sLuigi.addActionSprite( sLuigi.ACTION_WALK_LEFT,    sBMP_gogeta,  89, 0, 16, 16 );
sLuigi.addActionSprite( sLuigi.ACTION_WALK_LEFT,    sBMP_gogeta, 121, 0, 12, 16 );
sLuigi.addActionSprite( sLuigi.ACTION_WALK_LEFT,    sBMP_gogeta, 150, 0, 14, 16 );
sLuigi.addActionSprite( sLuigi.ACTION_WALK_RIGHT,   sBMP_gogeta, 300, 0, 16, 16 );
sLuigi.addActionSprite( sLuigi.ACTION_WALK_RIGHT,   sBMP_gogeta, 272, 0, 12, 16 );
sLuigi.addActionSprite( sLuigi.ACTION_WALK_RIGHT,   sBMP_gogeta, 241, 0, 14, 16 );
sLuigi.addActionSprite( sLuigi.ACTION_JUMP_LEFT,    sBMP_gogeta,  29, 0, 17, 16 );
sLuigi.addActionSprite( sLuigi.ACTION_JUMP_RIGHT,   sBMP_gogeta, 359, 0, 17, 16 );

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
    sLuigi.handleEvent( currentKeyState );

}

/*----------------------------------------------------------------------------
PROCEDURE: calcState
----------------------------------------------------------------------------*/
void calcState()
{
    
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

if( ( false == init()      ) ||
    ( false == loadMedia() ) )
    {
    return( -1 );
    }

    sLuigi.setPos( 0, 750 );


while( !sQuit )
{
    pollEvent();
    sLuigi.calcState();




    SDL_FillRect( sScreenSurface, NULL, SDL_MapRGB( sScreenSurface->format, 0x00, 0x00, 0x00 ) );
    
    sLuigi.render( sScreenSurface );
    SDL_UpdateWindowSurface( sWindow );
}
deinit();

return( 0 );
}   /* main() */

