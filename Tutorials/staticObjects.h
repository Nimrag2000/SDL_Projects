
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

		int getPosX() { return( mDestRect.x ); }
		int getPosY() { return( mDestRect.y ); }
		SDL_Rect * getPos() { return( &mDestRect ); }

	private:

		SDL_Rect mDestRect;
		SDL_Rect mSrcRect;

		SDL_Texture * mTexture;

};


#endif /* CIRCLE_H_ */

