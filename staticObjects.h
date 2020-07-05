
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

		typedef enum
		{
			CONTROLLER_ID_DPAD_LEFT		= 13,
			CONTROLLER_ID_DPAD_RIGHT	= 14,
			CONTROLLER_ID_DPAD_UP		= 11,
			CONTROLLER_ID_DPAD_DOWN		= 12,
			CONTROLLER_ID_X				= 0,
			CONTROLLER_ID_TRIANGLE		= 3,
			CONTROLLER_ID_SQUARE		= 2,
			CONTROLLER_ID_O				= 1,
			CONTROLLER_ID_INVALID		= -1
		} controller_id_t;


		Character();
		Character( int x, int y, bool keyboard );
		~Character();

		void calcState();

		void handleEvent( const Uint8 * currentKeyState, SDL_Event * event );

		void render( SDL_Renderer * renderer  );

		double getPosX() { return( mX ); }
		double getPosY() { return( mY ); }

		void setPosX( double x ) { mX = x; }
		void setPosY( double y ) { mY = y; }
		void setPos( double x, double y ) { mXstart = x; mYstart = y; mX = x; mY = y; }
		void setXLimit( int x ) { mYlimit = x; }
		void setYLimit( int y ) { mYlimit = y; }

		void addActionSprite( action_id_t actionId, SDL_Texture * spriteTexture, int x, int y, int w, int h );

		void controller();
	

	private:

		typedef struct
		{
			SDL_Rect        rect;
			SDL_Texture   * spriteTexture;
		} sprite_info_t;

		double mX;
		double mY;
		double mG;
		double mLastX;

		double mVy;
		double mVx;

		double mTstartX;
		double mTstarty;
		double mTstartJump;
		double mXstart;
		double mYstart;

		double mVxInit;
		double mVyInit;
		const double mINIT_VX = 150;
		const double mINIT_VY = -175;
		const double mINIT_G  = 500;

		int mXlimit;
		int mYlimit;

		bool mMovingXRight;
		bool mMovingXLeft;
		bool mMovingY;
		bool mIsLeft;

		bool mIsKeyboard;



		const int JOYSTICK_DEAD_ZONE = 8000;

		SDL_Rect mDestRect;

		vector<sprite_info_t> mActionSprites[ACTION_COUNT];
		vector<sprite_info_t>::iterator mCurrentSprite;
		action_id_t mLastAction_id;
};


#endif /* CIRCLE_H_ */

