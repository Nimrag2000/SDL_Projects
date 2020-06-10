#include <stdio.h>
#include <iostream>
#include <string>

#include "SDL.h"
#include "characterClass.h"

using namespace std;

Character::Character( void )
{
    mX                  = 0;
    mY                  = 0;
    mG                  = 0;
    mVy                 = 0;
    mVx                 = 0;
    mTstartX            = 0;
    mTstarty            = 0;
    Uint32 mXstart      = 0;
    Uint32 mYstart      = 0;
    mvmntSpeed          = 150;
    dstRect             = { 0 };
    mYlimit             = 750;
    mXlimit             = 750;
    mMovingXRight       = false;
    mMovingXLeft        = false;
    mMovingY            = false;
    mIsLeft             = false;
    mLastAction_id      = ACTION_STILL_RIGHT;
    SDL_Surface * mSpriteSheet = nullptr;

}

Character::Character( SDL_Surface * spriteSheet )
{
    mX                  = 0;
    mY                  = 0;
    mG                  = 0;
    mVy                 = 0;
    mVx                 = 0;
    mTstartX            = 0;
    mTstarty            = 0;
    Uint32 mXstart      = 0;
    Uint32 mYstart      = 0;
    mvmntSpeed          = 150;
    dstRect             = { 0 };
    mYlimit             = 750;
    mXlimit             = 750;
    mMovingXRight       = false;
    mMovingXLeft        = false;
    mMovingY            = false;
    mIsLeft             = false;
    mLastAction_id      = ACTION_STILL_RIGHT;
    SDL_Surface * mSpriteSheet = nullptr;
}

Character::~Character( void )
{

}

void Character::addActionSprite( action_id_t actionId, SDL_Surface * spriteSheet, int x, int y, int w, int h )
{
    sprite_info_t sprite = { { x, y, w, h }, spriteSheet };

    mActionSprites[ actionId ].push_back( sprite );
}


void Character::calcState()
{


    double deltaTx = (double)( SDL_GetTicks() - mTstartX ) / 1000.0;
    double deltaTy = (double)( SDL_GetTicks() - mTstarty ) / 1000.0;
    double deltaY = ( mVy * deltaTy ) + 0.5 * mG * ( deltaTy * deltaTy );

    
    
    /*
        calculate movement
    */
    mX =  mXstart + ( mVx * deltaTx );
    mY =  mYstart + deltaY;


    /*
        pick sprite
    */

    if( mMovingXRight && !mMovingY )
    {
        if( mLastAction_id != ACTION_WALK_RIGHT )
        {
            mCurrentSprite = mActionSprites[ACTION_WALK_RIGHT].begin();
        }
        else if( ( mX - mLastX ) > 25 )
        {
            mLastX = mX;
            mCurrentSprite++;
        }

        if( mCurrentSprite == mActionSprites[ACTION_WALK_RIGHT].end() )
        {
            mCurrentSprite = mActionSprites[ACTION_WALK_RIGHT].begin();
        }
        mLastAction_id = ACTION_WALK_RIGHT;
    }
    else if( mMovingXLeft && !mMovingY )
    {
        if( mLastAction_id != ACTION_WALK_LEFT )
        {
            mCurrentSprite = mActionSprites[ACTION_WALK_LEFT].begin();
        }
        else if( ( mLastX - mX ) > 25 )
        {
            mLastX = mX;
            mCurrentSprite++;
        }

        if( mCurrentSprite == mActionSprites[ACTION_WALK_LEFT].end() )
        {
            mCurrentSprite = mActionSprites[ACTION_WALK_LEFT].begin();
        }
        mLastAction_id = ACTION_WALK_LEFT;

    }
    else if( mMovingY && !mIsLeft )
    {
        mCurrentSprite = mActionSprites[ACTION_JUMP_RIGHT].begin();
        mLastAction_id = ACTION_JUMP_RIGHT;
    }
    else if( mMovingY && mIsLeft )
    {
        mCurrentSprite = mActionSprites[ACTION_JUMP_LEFT].begin();
        mLastAction_id = ACTION_JUMP_LEFT;
    }
    else if( !mIsLeft )
    {
        mCurrentSprite = mActionSprites[ACTION_STILL_RIGHT].begin();
        mLastAction_id = ACTION_STILL_RIGHT;
    }
    else if( mIsLeft )
    {
        mCurrentSprite = mActionSprites[ACTION_STILL_LEFT].begin();
        mLastAction_id = ACTION_STILL_LEFT;
    }
    else
    {
        mCurrentSprite = mActionSprites[ACTION_STILL_RIGHT].begin();
        mLastAction_id = ACTION_STILL_RIGHT;
    }

    /*
    check for screen boundaries
*/
    if( mY > mYlimit )
    {
        mY = mYlimit;
        mVy = 0;
        mG = 0;
        mYstart = mY;
        mMovingY = false;
    }

    if( mX > mXlimit - mCurrentSprite->rect.w )
    {
        mX = mXlimit - mCurrentSprite->rect.w;
        mVx = 0;
        mXstart = mX;
        mMovingXLeft = false;
        mMovingXRight = false;
    }

    if( mX < 0 )
    {
        mX = 0;
        mVx = 0;
        mXstart = mX;
        mMovingXLeft = false;
        mMovingXRight = false;
    }



}

void Character::handleEvent( const Uint8 * currentKeyState )
{

    if( currentKeyState[SDL_SCANCODE_W] && !mMovingY )
    {
        mVy = -175;
        mTstarty = SDL_GetTicks();
        mYstart = mY;
        mG = 500;
        mMovingY = true;
            
    }

    if( ( currentKeyState[SDL_SCANCODE_A] ) && ( !mMovingXLeft ) )
    {
        mVx = -mvmntSpeed;
        mTstartX = SDL_GetTicks();
        mXstart = mX;
        mMovingXLeft = true;
        mMovingXRight = false;
        mIsLeft = true;
    }
    else if( ( currentKeyState[SDL_SCANCODE_D] ) && ( !mMovingXRight ) )
    {
        mVx = mvmntSpeed;
        mTstartX = SDL_GetTicks();
        mXstart = mX;
        mMovingXRight = true;
        mMovingXLeft  = false;
        mIsLeft = false;
    }
    else if( !currentKeyState[SDL_SCANCODE_A] && !currentKeyState[SDL_SCANCODE_D] )
    {
        mXstart = mX;
        mVx = 0;
        mMovingXRight = false;
        mMovingXLeft  = false;

    }
}

void Character::render( SDL_Surface * surface )
{

    dstRect.x = (int)mX;
    dstRect.y = (int)mY - mCurrentSprite->rect.h;
    dstRect.w = mCurrentSprite->rect.w;
    dstRect.h = mCurrentSprite->rect.h;

    SDL_BlitSurface( mCurrentSprite->spriteSheet, &mCurrentSprite->rect, surface, &dstRect );

}