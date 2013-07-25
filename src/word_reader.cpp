/*
 * word_reader.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: Reuben
 */
#include <headers/aria.hpp>

using namespace std;

SDL_Rect temp={100,100,200,200};
int main(int argc,char* args[])
{
	word orig;
	orig.set_name("hello");
	orig.set_type("iojsafdasd");
	ofstream fout("databases/words.dat",ios::binary);
	fout.write((char*)&orig,sizeof orig);
	fout.close();
	word hello;
	ifstream fin("databases/words.dat",ios::app|ios::binary);
	fin.read((char*)&hello,sizeof hello);
	fin.close();
	ARIA aria(1080,720);
	SDL_Surface* t=TTF_RenderText_Solid(font,"test...",(SDL_Color){0,0xFF,0});
	graphicstring test(hello.getname());
	while(!ended)
	{
		SDL_PollEvent(&event);
		aria.handleevents();
		test.display();
		SDL_Flip(scr);
		SDL_FillRect(scr,&scr->clip_rect,SDL_MapRGB(scr->format,0x0,0x0,0xFF));
		SDL_Delay(10);
	}
	SDL_FreeSurface(t);
	return 0;
}



