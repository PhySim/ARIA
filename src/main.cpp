/*
 * main.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#include <headers/aria.hpp>

using namespace std;

int main (int argc, char* args[])
{ARIA aria(1080,720);

	word w;
	sentence sen;

	sentence_struc temp2;
	read(temp2);
	graphicstringinput user;
	string a;

	graphicstring test;
	test.set(temp2.size);

	SDL_Delay(100);
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
			sentence_struc temp(sen);
			if(temp.struc[0].interjection.salutation)
			{
				test.set(temp.size);
			}
			else
			{
				test.set("nope");
			}
			user.finished(false);
		}
		user.display();
		test.display();
		aria.endframe();
	}
	return 0;
}
