#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "SDL.h"
#include "characterClass.h"
#include "staticObjects.h"

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

/*
This is the main window which draws to the actual screen.  The Renderer is 
derived from this.  SDL_Window is the struct that holds all info about the 
Window itself: size, position, full screen, borders etc.
*/
static SDL_Window       * sWindow           = nullptr;

/*
SDL_Renderer is a struct that handles all rendering. It is tied to a SDL_Window 
so it can only render within that SDL_Window. It also keeps track the settings 
related to the rendering. 

It handles rendering all textures associated with the Renderer.
*/
static SDL_Renderer     * sRenderer         = nullptr;

/*
These are the sprite sheets that will be loaded into textures.
*/
static SDL_Texture      * sTextureLuigi     = nullptr;
static SDL_Texture      * sTextureMario     = nullptr;
static SDL_Texture      * sTextureGround    = nullptr;

static SDL_Joystick     * sGameController   = nullptr;

static bool             sQuit               = false;
static Character        * sLuigi            = nullptr;
static Character        * sMario            = nullptr;
static vector<Object>     sGround;

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
if( nullptr != sTextureLuigi )
{
    SDL_DestroyTexture( sTextureLuigi );
    sTextureLuigi = nullptr;
}

if( nullptr != sTextureMario )
{
    SDL_DestroyTexture( sTextureMario );
    sTextureMario = nullptr;
}

if( nullptr != sTextureGround )
{
    SDL_DestroyTexture( sTextureGround );
    sTextureGround = nullptr;
}

SDL_DestroyRenderer( sRenderer );
SDL_DestroyWindow( sWindow );
sRenderer = nullptr;
sWindow = nullptr;

delete sLuigi;
delete sMario;

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

if( SDL_NumJoysticks() >= 1 )
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

sRenderer = SDL_CreateRenderer( sWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
if( nullptr == sRenderer )
{
    return( false );
}
SDL_SetRenderDrawColor( sRenderer, 0, 0, 0, 0 );

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
SDL_Surface      * surface  = nullptr;
Object             ground;


/*
Load the Luigi sprite sheet into a surface, then create a texture from it.
*/
surface = SDL_LoadBMP( "images/luigiSprite.bmp" );
if( nullptr == surface )
{
    return( false );
}
sTextureLuigi = SDL_CreateTextureFromSurface( sRenderer, surface );
if( nullptr == sTextureLuigi )
{
    return( false );
}

SDL_FreeSurface( surface );


/*
Load the Mario sprite sheet into a surface, then create a texture from it.
*/
surface = SDL_LoadBMP( "images/marioSprite.bmp" );
if( nullptr == surface )
{
    return( false );
}
sTextureMario = SDL_CreateTextureFromSurface( sRenderer, surface );
if( nullptr == sTextureMario )
{
    return( false );
}

SDL_FreeSurface( surface );


/*
Load the Mario sprite sheet into a surface, then create a texture from it.
*/
surface = SDL_LoadBMP( "images/blockSprite.bmp" );
if( nullptr == surface )
{
    return( false );
}
sTextureGround = SDL_CreateTextureFromSurface( sRenderer, surface );
if( nullptr == sTextureGround )
{
    return( false );
}

SDL_FreeSurface( surface );

/*
Initialize the Luigi character with it's sprite actions.
*/

sLuigi = new Character( 0, 0, true );

sLuigi->addActionSprite( sLuigi->ACTION_STILL_LEFT,   sTextureLuigi, 181, 0, 13, 16 );
sLuigi->addActionSprite( sLuigi->ACTION_STILL_RIGHT,  sTextureLuigi, 211, 0, 13, 16 );
sLuigi->addActionSprite( sLuigi->ACTION_WALK_LEFT,    sTextureLuigi,  89, 0, 16, 16 );
sLuigi->addActionSprite( sLuigi->ACTION_WALK_LEFT,    sTextureLuigi, 121, 0, 12, 16 );
sLuigi->addActionSprite( sLuigi->ACTION_WALK_LEFT,    sTextureLuigi, 150, 0, 14, 16 );
sLuigi->addActionSprite( sLuigi->ACTION_WALK_RIGHT,   sTextureLuigi, 300, 0, 16, 16 );
sLuigi->addActionSprite( sLuigi->ACTION_WALK_RIGHT,   sTextureLuigi, 272, 0, 12, 16 );
sLuigi->addActionSprite( sLuigi->ACTION_WALK_RIGHT,   sTextureLuigi, 241, 0, 14, 16 );
sLuigi->addActionSprite( sLuigi->ACTION_JUMP_LEFT,    sTextureLuigi,  29, 0, 17, 16 );
sLuigi->addActionSprite( sLuigi->ACTION_JUMP_RIGHT,   sTextureLuigi, 359, 0, 17, 16 );

ground.setTexture( sTextureGround );
ground.setSrcPos( 49, 145, 35, 33 );

for( int i = 0; i < 750; i += 35 )
{
    ground.setDestPos( i, 750, 35, 33 );
    sGround.push_back( ground );

}

ground.setSrcPos( 347, 142, 36, 36 );

ground.setDestPos( 125, 717, 36, 36 );
sGround.push_back( ground );

ground.setDestPos( 160, 717, 36, 36 );
sGround.push_back( ground );

ground.setDestPos( 160, 684, 36, 36 );
sGround.push_back( ground );

ground.setSrcPos( 134, 142, 36, 36 );
ground.setDestPos( 200, 654, 36, 36 );
sGround.push_back( ground );

if( sGameController != NULL )
{
    sMario = new Character( SCREEN_WIDTH - 20, 0, false );

    sMario->addActionSprite( sMario->ACTION_STILL_LEFT,   sTextureMario, 181, 0, 13, 16 );
    sMario->addActionSprite( sMario->ACTION_STILL_RIGHT,  sTextureMario, 211, 0, 13, 16 );
    sMario->addActionSprite( sMario->ACTION_WALK_LEFT,    sTextureMario,  89, 0, 16, 16 );
    sMario->addActionSprite( sMario->ACTION_WALK_LEFT,    sTextureMario, 121, 0, 12, 16 );
    sMario->addActionSprite( sMario->ACTION_WALK_LEFT,    sTextureMario, 150, 0, 14, 16 );
    sMario->addActionSprite( sMario->ACTION_WALK_RIGHT,   sTextureMario, 300, 0, 16, 16 );
    sMario->addActionSprite( sMario->ACTION_WALK_RIGHT,   sTextureMario, 272, 0, 12, 16 );
    sMario->addActionSprite( sMario->ACTION_WALK_RIGHT,   sTextureMario, 241, 0, 14, 16 );
    sMario->addActionSprite( sMario->ACTION_JUMP_LEFT,    sTextureMario,  29, 0, 17, 16 );
    sMario->addActionSprite( sMario->ACTION_JUMP_RIGHT,   sTextureMario, 359, 0, 17, 16 );

}



return( true );
}   /* loadMedia() */


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
        const Uint8 * currentKeyState = SDL_GetKeyboardState( NULL );
        sLuigi->handleEvent( currentKeyState, &e );
        if( sMario != nullptr )
        {
            sMario->handleEvent( currentKeyState, &e );            
        }
    }

    
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
vector<Object>::iterator itGround;


if( ( false == init()      ) ||
    ( false == loadMedia() ) )
    {
    return( -1 );
    }

while( !sQuit )
{
    pollEvent();
    sLuigi->calcState();
    

    if( sMario != nullptr )
    {
        sMario->calcState();            
    }

    sLuigi->detectCollision( sGround );
    sMario->detectCollision( sGround );

	/*
    Clear the screen.
    */
	SDL_SetRenderDrawColor( sRenderer, 0, 0, 64, 0 );
	SDL_RenderClear( sRenderer );

    /*
    Update the characters.
    */

    for( itGround = sGround.begin(); itGround != sGround.end(); itGround++ )
    {
        itGround->render( sRenderer );     
    }

    sLuigi->render( sRenderer );

    if( sMario != nullptr )
    {
        sMario->render( sRenderer );            
    }




	/*
    Update the screen.
    */
	SDL_RenderPresent( sRenderer );
}

deinit();

return( 0 );
}   /* main() */

