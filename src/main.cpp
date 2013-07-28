/*
 * main.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#include <headers/aria.hpp>
#include <headers/sentence_struc.hpp>

using namespace std;

int main (int argc, char* args[])
{
	ARIA aria(1080,720);

	sentence_struc sen;
	//sen.set("salutations");
	readsentence_struc(sen);
	framer frame(30,40);
	graphicstringinput user;
	string a;
	a.assign(sen.all.c_str());

	graphicstring test;
	test.set(a);

	SDL_Delay(250);
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
			sen.set(a.c_str());
			if(searchsentence_struc(sen)->all.match_id!=0)
			{
				SDL_Delay(2000);
				test.set(sen.all.c_str());
			}
			else
			{
				SDL_Delay(1000);
				test.set("nope");
			}
			Sentence_strucResult.reset();
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
