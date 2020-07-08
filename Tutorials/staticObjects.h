
#ifndef STATICOBJECTS_H_
#define STATICOBJECTS_H_

#include <stdio.h>
#include "SDL.h"

using namespace std;

class Object
{
	public:
		
		Object();
		Object( SDL_Texture * spriteTexture, int srcX, int srcY, int srcW, int srcH, int x, int y );
		~Object();


		void render( SDL_Renderer * renderer  );


		int getX() { return( mDestRect.x ); }
		int getY() { return( mDestRect.y ); }
		int getW() { return( mDestRect.w ); }
		int getH() { return( mDestRect.h ); }
		int getTop()    { return( mDestRect.y - mDestRect.h ); }
		int getBot()    { return( mDestRect.y ); }
		int getLeft()   { return( mDestRect.x ); }
		int getRight()  { return( mDestRect.x + mDestRect.w ); }
		SDL_Rect * getPos() { return( &mDestRect ); }

		void setSrcPos( int x, int y, int w, int h ) { mSrcRect.x = x; mSrcRect.y = y; mSrcRect.w = w; mSrcRect.h = h; }
		void setDestPos( int x, int y, int w, int h ) { mDestRect.x = x; mDestRect.y = y; mDestRect.w = w; mDestRect.h = h; }
		void setTexture( SDL_Texture * spriteTexture ) { mTexture = spriteTexture; }


	private:

		SDL_Rect mDestRect;
		SDL_Rect mSrcRect;

		SDL_Texture * mTexture;

};


#endif /* CIRCLE_H_ */

