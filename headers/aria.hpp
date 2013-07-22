/*
 * aria.hpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#ifndef ARIA_HPP_
#define ARIA_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <headers/events.hpp>
#include <headers/global_assets.hpp>

class ARIA
{
public:
	ARIA(unsigned int w,unsigned int h)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();
		SDL_FreeSurface(scr);
		scr=SDL_SetVideoMode(w,720,32,SDL_SWSURFACE|SDL_RESIZABLE);
		font=TTF_OpenFont("fonts/lazy.ttf",28);
	}
	~ARIA()
	{
		SDL_Quit();
	}
};


#endif /* ARIA_HPP_ */
