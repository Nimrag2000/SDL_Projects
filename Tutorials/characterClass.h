
#ifndef CHARACTERCLASS_H_
#define CHARACTERCLASS_H_

#include <stdio.h>
#include <vector>
#include "SDL.h"

using namespace std;

class Character
{
	public:


		typedef enum
		{
			ACTION_STILL_LEFT,
			ACTION_STILL_RIGHT,
			ACTION_WALK_LEFT,
			ACTION_WALK_RIGHT,
			ACTION_JUMP_LEFT,
			ACTION_JUMP_RIGHT,
			ACTION_COUNT


		} action_id_t;


		Character();
		~Character();

		Character( SDL_Surface * spriteSheet );

		void calcState();

		void handleEvent( const Uint8 * currentKeyState );

		void render( SDL_Surface * surface  );

		double getPosX() { return( mX ); }
		double getPosY() { return( mY ); }

		void setPosX( double x ) { mX = x; }
		void setPosY( double y ) { mY = y; }
		void setPos( double x, double y ) { mXstart = x; mYstart = y; mX = x; mY = y; }
		void setXLimit( int x ) { mYlimit = x; }
		void setYLimit( int y ) { mYlimit = y; }

		void addActionSprite( action_id_t actionId, SDL_Surface * spriteSheet, int x, int y, int w, int h );
	

	private:

		double mX;
		double mY;
		double mG;
		double mLastX;

		double mVy;
		double mVx;

		double mTstartX;
		double mTstarty;
		double mXstart;
		double mYstart;

		double mvmntSpeed;

		int mXlimit;
		int mYlimit;

		bool mMovingXRight;
		bool mMovingXLeft;
		bool mMovingY;

		SDL_Rect dstRect;

		bool mIsLeft;

		typedef struct
		{
			SDL_Rect rect;
			SDL_Surface * spriteSheet;
		} sprite_info_t;

		vector<sprite_info_t> mActionSprites[ACTION_COUNT];

		vector<sprite_info_t>::iterator mCurrentSprite;

		action_id_t mLastAction_id;

};


#endif /* CIRCLE_H_ */
