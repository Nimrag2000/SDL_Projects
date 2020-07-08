#include <stdio.h>
#include <iostream>
#include <string>

#include "SDL.h"
#include "staticObjects.h"

using namespace std;

Object::Object( void )
{
    mDestRect           = { 0 };
    mSrcRect            = { 0 };

    mTexture            = nullptr;
}

Object::Object( SDL_Texture * spriteTexture, int srcX, int srcY, int srcW, int srcH, int x, int y )
{
    
    mDestRect           = { x, y, srcW, srcH };
    mSrcRect            = { srcX, srcY, srcW, srcH };

    mTexture            = spriteTexture;
}


Object::~Object( void )
{
}

void Object::render( SDL_Renderer * renderer )
{
    SDL_Rect tempRect = mDestRect;
    
    tempRect.y -= mDestRect.h;
    SDL_RenderCopy( renderer, mTexture, &mSrcRect, &tempRect );
}

