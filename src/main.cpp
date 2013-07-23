/*
 * main.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#include <headers/aria.hpp>

using namespace std;

SDL_Thread* testing;
stringinput_data test;
SDL_Surface* text;

int main (int argc, char* args[])
{
	ARIA aria(1080,720);
	//get_input=SDL_CreateThread(getinput,input,NULL);
	SDL_Rect temp={0,0,scr->w,scr->h};
	testing=SDL_CreateThread(stringinput,&test);
	while(!ended)
	{
		{
			access(test.mutex);
			if(test.dataready)
			{
				text=TTF_RenderText_Solid(font,test.input.c_str(),(SDL_Color){0,0xFF,0});
			}
		}
		SDL_BlitSurface(text,&temp,scr,NULL);
		SDL_Flip(scr);
		SDL_FillRect(scr,&temp,SDL_MapRGB(scr->format,0x0,0x0,0xFF));
		aria.handleevents();
		SDL_Delay(100);
	}
	return 0;
}
