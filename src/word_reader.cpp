/*
 * word_reader.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: Reuben
 */

#include <headers/aria.hpp>

using namespace std;

int cu=0,ne=0;

SDL_Rect temp={100,100,200,200};
int main(int argc,char* args[])
{
	ARIA aria(1080,720);
	word find;
	readword(find,ne,0);
	graphicstring name(find.name);
	graphicstring type(find.type);
	char* a=new char[100];string b;
	itoa(find.rating,a,10);b=a;
	graphicstring rating(b);
	itoa(find.usage,a,10);b=a;
	graphicstring usage(b);
	while(!ended&&!DB_corrupted)
	{

		SDL_FillRect(scr,&scr->clip_rect,SDL_MapRGB(scr->format,0xFF*DB_corrupted,0x0,0xFF*!DB_corrupted));
		SDL_Delay(100);
		SDL_PollEvent(&event);
		aria.handleevents();
		if(event.type==SDL_KEYDOWN)
		{
			if(event.key.keysym.sym==SDLK_DOWN)
			{
				SDL_Delay(200);
				cu=ne;
				ne=readword(find,ne,0).end;
				name.set(find.name);
				type.set(find.type);
				char* a=new char[100];string b;
				itoa(find.rating,a,10);b=a;
				rating.set(b);
				itoa(find.usage,a,10);b=a;
				usage.set(b);
			}
		}
		name.display();
		type.display();
		rating.display();
		usage.display();
		SDL_Flip(scr);
	}
	return 0;
}



