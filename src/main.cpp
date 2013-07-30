/*
 * main.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#include <headers/aria.hpp>

using namespace std;

int main (int argc, char* args[])
{
	ARIA aria(1080,720);

	sentence sen;
	framer frame(30,40);
	graphicstringinput user;
	string a;
	a.assign("startup");

	graphicstring test;
	test.set(a);

	SDL_Delay(100);
	//get_input=SDL_CreateThread(getinput,input,NULL);
	while(!ended)
	{
		aria.handleevents();
		if(!user.done)
		{//users turn to speak
			user.handle_input(event);
		}
		else
		{//computers turn to speak!
			user.get(a);
			sen.set(a.c_str());
			searchsentence(sen);
			if(SentenceResult.all.match_id==2)
			{
				test.set(sen.all.c_str());
			}
			else
			{
				test.set("nope");
			}
			user.finished(false);
		}
		user.display();
		test.display();
		SDL_Flip(scr);
		SDL_FillRect(scr,&scr->clip_rect,SDL_MapRGB(scr->format,0x0,0x0,0xFF));
		SDL_Delay(10);
		frame.endframe();
	}
	return 0;
}
