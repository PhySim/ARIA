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
	word hello("hello");
	hello.set_type("salutation");
	ofstream fout("databases/words.dat",ios::app|ios::binary);
	fout.write((char*)&hello,sizeof hello);
	fout.close();
	ARIA aria(1080,720);
	framer frame(30,40);
	graphicstringinput user;
	//get_input=SDL_CreateThread(getinput,input,NULL);
	while(!ended)
	{
		aria.handleevents();
		if(!user.done)
		{
			user.handle_input(event);
		}
		user.display();
		SDL_Flip(scr);
		SDL_FillRect(scr,&scr->clip_rect,SDL_MapRGB(scr->format,0x0,0x0,0xFF));
		SDL_Delay(10);
		frame.endframe();
	}
	return 0;
}
