#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "SDL.h"
#include "characterClass.h"
#include "staticObjects.h"

using namespace std;

Character::Character( void )
{
    mX                  = 0.0;
    mY                  = 0.0;
    mG                  = mINIT_G;
    mLastX              = 0.0;

    mVy                 = 0.0;
    mVx                 = 0.0;

    mTstartX            = 0.0;
    mTstarty            = 0.0;
    mXstart             = 0.0;
    mYstart             = 0.0;

    mVxInit             = mINIT_VX;
    mVyInit             = mINIT_VY;

    mYlimit             = 750;
    mXlimit             = 750;

    mMovingXRight       = false;
    mMovingXLeft        = false;
    mMovingY            = false;
    mIsLeft             = false;

    mDestRect           = { 0 };

    mLastAction_id      = ACTION_STILL_RIGHT;

    mIsKeyboard         = true;

}

Character::Character( int x, int y, bool keyboard )
{
    mX                  = x;
    mY                  = y;
    mG                  = mINIT_G;
    mLastX              = x;

    mVy                 = 0.0;
    mVx                 = 0.0;

    mTstartX            = 0.0;
    mTstarty            = 0.0;
    mXstart             = x;
    mYstart             = y;

    mVxInit             = mINIT_VX;
    mVyInit             = mINIT_VY;

    mYlimit             = 750;
    mXlimit             = 750;

    mMovingXRight       = false;
    mMovingXLeft        = false;
    mMovingY            = false;
    mIsLeft             = false;

    mDestRect           = { 0 };

    mLastAction_id      = ACTION_STILL_RIGHT;

    mIsKeyboard         = keyboard;

}


Character::~Character( void )
{
}

void Character::addActionSprite( action_id_t actionId, SDL_Texture * spriteTexture, int x, int y, int w, int h )
{
    sprite_info_t sprite = { { x, y, w, h }, spriteTexture };

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
        mYstart = mY;
        mMovingY = false;
        mTstartJump = 0;
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

void Character::handleEvent( const Uint8 * currentKeyState, SDL_Event * event )
{
    
    if( ( mIsKeyboard && currentKeyState[SDL_SCANCODE_SPACE] && !mMovingY ) ||
        ( !mIsKeyboard && event->type == SDL_JOYBUTTONDOWN && event->jbutton.button == CONTROLLER_ID_X && !mMovingY ) )
    {
        mVy = mVyInit;
        mTstarty = SDL_GetTicks();
        mTstartJump = SDL_GetTicks();
        mYstart = mY;
        mMovingY = true;
        mG = 0;
    }
    else if( ( mTstartJump != 0 ) &&
             ( ( mIsKeyboard && !currentKeyState[SDL_SCANCODE_SPACE] && mMovingY ) ||
               ( !mIsKeyboard && event->type == SDL_JOYBUTTONUP && event->jbutton.button == CONTROLLER_ID_X && mMovingY ) ) )
    {
        mVy = mVyInit;
        mTstarty = SDL_GetTicks();
        mYstart = mY;
        mTstartJump = 0;
        mG = mINIT_G;
    }
    else if( ( (SDL_GetTicks() - mTstartJump) >= 250 ) && ( mTstartJump != 0 ) && mMovingY )
    {
       // mVy = mVyInit * 1.5;
        mTstarty = SDL_GetTicks();
        mYstart = mY;
        mTstartJump = 0;
        mG  = mINIT_G;
    }

//    if( event->type == SDL_JOYAXISMOTION )
//    {
//    cout << "Button: " << (int)event->jaxis.axis << " " << (int)event->jaxis.value << "\n";
//    }

    if( ( mIsKeyboard && currentKeyState[SDL_SCANCODE_A] && !mMovingXLeft ) ||
        ( !mIsKeyboard && event->type == SDL_JOYBUTTONDOWN && event->jbutton.button == CONTROLLER_ID_DPAD_LEFT && !mMovingXLeft ) )
    {
        mVx = -mVxInit;
        mTstartX = SDL_GetTicks();
        mXstart = mX;
        mMovingXLeft = true;
        mMovingXRight = false;
        mIsLeft = true;
    }
    if( ( mIsKeyboard && currentKeyState[SDL_SCANCODE_D] && !mMovingXRight ) ||
        ( !mIsKeyboard && event->type == SDL_JOYBUTTONDOWN && event->jbutton.button == CONTROLLER_ID_DPAD_RIGHT && !mMovingXRight ) )
    {
        mVx = mVxInit;
        mTstartX = SDL_GetTicks();
        mXstart = mX;
        mMovingXRight = true;
        mMovingXLeft  = false;
        mIsLeft = false;
    }
    else if( ( !mIsKeyboard && event->type == SDL_JOYBUTTONUP && event->jbutton.button == CONTROLLER_ID_DPAD_LEFT ) 
          || ( !mIsKeyboard && event->type == SDL_JOYBUTTONUP && event->jbutton.button == CONTROLLER_ID_DPAD_RIGHT ) 
          || (  mIsKeyboard && !currentKeyState[SDL_SCANCODE_A] && !currentKeyState[SDL_SCANCODE_D] ) )
    {
        mXstart = mX;
        mVx = 0;
        mMovingXRight = false;
        mMovingXLeft  = false;

    }
    else if( !mIsKeyboard && event->type == SDL_JOYBUTTONDOWN && event->jbutton.button == CONTROLLER_ID_SQUARE )
    {
        mVxInit *= 2;
        mVx     *= 2;
        mTstartX = SDL_GetTicks();
        mXstart = mX;

    }
    else if( !mIsKeyboard && event->type == SDL_JOYBUTTONUP && event->jbutton.button == CONTROLLER_ID_SQUARE )
    {
        mVxInit *= 0.5;
        mVx     *= 0.5;
        mTstartX = SDL_GetTicks();
        mXstart = mX;

    }

}

void Character::render( SDL_Renderer * renderer )
{
    mDestRect.x = (int)mX;
    mDestRect.y = (int)mY - mCurrentSprite->rect.h;
    mDestRect.w = mCurrentSprite->rect.w;
    mDestRect.h = mCurrentSprite->rect.h;

    SDL_RenderCopyEx( renderer, mCurrentSprite->spriteTexture, &mCurrentSprite->rect, &mDestRect, 0.0, nullptr, SDL_FLIP_NONE );
    //SDL_RenderCopyEx( renderer, mCurrentSprite->spriteTexture, &mCurrentSprite->rect, &mDestRect, (SDL_GetTicks()) % 360, nullptr, SDL_FLIP_NONE );
}

void Character::detectCollision( vector<Object> blocks )
{
    vector<Object>::iterator itBlocks;

    for( itBlocks = blocks.begin(); itBlocks != blocks.end(); itBlocks++ )
    {
        if( ( this->getBot() > itBlocks->getTop() ) && ( this->getTop() < itBlocks->getTop() ) ) 
        {
            if( ( this->getLeft() > itBlocks->getLeft() ) && ( this->getLeft() < itBlocks->getRight() ) || 
                ( this->getRight() > itBlocks->getLeft() ) && ( this->getRight() < itBlocks->getRight() ) ||
                ( itBlocks->getLeft() > this->getLeft() ) && ( itBlocks->getLeft() < this->getRight() ) ||
                ( itBlocks->getRight() > this->getLeft() ) && ( itBlocks->getRight() < this->getRight() ) )
            {
                mVy = 0;
                mG  = mINIT_G;
                mMovingY = false;
                mTstarty = SDL_GetTicks();
                mTstartJump = 0;
                mY = itBlocks->getTop();
                mYstart = mY;
            }
        }
    }
}