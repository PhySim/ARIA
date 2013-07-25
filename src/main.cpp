/*
 * main.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#include <headers/aria.hpp>

using namespace std;
SDL_Surface* image;

int main (int argc, char* args[])
{
	ARIA aria(1080,720);
	framer frame(30,40);
	graphicstring user;
	//get_input=SDL_CreateThread(getinput,input,NULL);
	SDL_Rect temp={0,0,scr->w,scr->h};
	while(!ended)
	{
		SDL_PollEvent(&event);
		aria.handleevents();
		if(!user.done)
		{
			user.handle_input(event);
		}
		user.display();
		SDL_Flip(scr);
		SDL_FillRect(scr,&temp,SDL_MapRGB(scr->format,0x0,0x0,0xFF));
		SDL_Delay(10);
		frame.endframe();
	}
	return 0;
}
