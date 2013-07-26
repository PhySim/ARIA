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
#include <headers/DB.hpp>

class ARIA
{
private:
	unsigned int font_size;
public:
	ARIA(unsigned int w,unsigned int h,unsigned int U_font_size=global_font_size)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_WM_SetCaption("ARIA:Automated Response-Intelligent Acquisition -By Reuben John",NULL);
		TTF_Init();
		SDL_EnableUNICODE( SDL_ENABLE );
		SDL_FreeSurface(scr);
		::global_font_size=font_size=U_font_size;
		scr=SDL_SetVideoMode(w,720,32,SDL_SWSURFACE|SDL_RESIZABLE);
		font=TTF_OpenFont("fonts/lazy.ttf",font_size);
	}
	~ARIA()
	{
		SDL_Quit();
	}
	void handleevents()
	{
		SDL_PollEvent(&event);
		if(event.type==SDL_QUIT)
		{
				ended=true;
		}
	}
};


#endif /* ARIA_HPP_ */
