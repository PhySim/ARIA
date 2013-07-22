/*
 * main.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#include <headers/aria.hpp>

using namespace std;

SDL_Thread* testing;
stringinput_data* test;
void* test2=test;
int main (int argc, char* args[])
{
	ARIA aria(1080,720);
	//get_input=SDL_CreateThread(getinput,input,NULL);
	SDL_Rect temp={100,100,scr->w,scr->h};
	SDL_FillRect(scr,&temp,SDL_MapRGB(scr->format,0xFF,0xFF,0xFF));
	testing=SDL_CreateThread(stringinput,test2);
	SDL_Surface* text=TTF_RenderText_Solid(font,mystring.c_str(),(SDL_Color){0,0xFF,0});
	SDL_BlitSurface(text,&temp,scr,NULL);
	SDL_Flip(scr);
	SDL_Delay(1000);
	return 0;
}
