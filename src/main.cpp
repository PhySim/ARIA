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

	word hello("hey");
	hello.type="salutation";
	hello.rating=1;
	framer frame(30,40);
	graphicstringinput user;
	//writeword(hello);
	word_io io;
	readword(hello);
	string a="nope";

	graphicstring test;
	test.set(a);
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
			user.input(a);
			hello.name.assign(a);
			searchword(hello);
			if(WordResult.name.match_id==2)
			{
				test.set("I have seen that word before!");
			}
			else
			{
				a.insert(0,"I dont know what ");
				a.append(" means");
				test.set(a);
			}
			WordResult.reset();
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
