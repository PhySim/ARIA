/*
 * global_assets.hpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Reuben
 */

#ifndef GLOBAL_ASSETS_HPP_
#define GLOBAL_ASSETS_HPP_

#include <SDL/SDL.h>
#include <string>
//#include <fstream>
using namespace std;

bool ended=0;
SDL_Surface* scr;
SDL_Event event;
TTF_Font* font;

typedef struct
{
	string input;
}stringinput_data;
int stringinput(void* data)
{
	stringinput_data* tdata=(stringinput_data*)data;
	string input=tdata->input;
	SDL_EnableUNICODE( SDL_ENABLE );
	SDL_Event uin;
	while(!(uin.type==SDL_KEYDOWN&&uin.key.keysym.sym==SDLK_RETURN))
	{
		while(SDL_PollEvent(&uin))
		{
			if(uin.type==SDL_KEYDOWN)
			{
				if((uin.key.keysym.unicode>='A'&&uin.key.keysym.unicode<='Z')
				||(uin.key.keysym.unicode>='a'&&uin.key.keysym.unicode<='z')
				||(uin.key.keysym.unicode>='0'&&uin.key.keysym.sym<='9')
				||(uin.key.keysym.unicode==SDLK_SPACE)
				||(uin.key.keysym.unicode==SDLK_TAB)
				||(uin.key.keysym.unicode==SDLK_EXCLAIM)
				||(uin.key.keysym.unicode==SDLK_AT)
				//||(uin.key.keysym.unicode==SDLK_HASH)
				||(uin.key.keysym.unicode==SDLK_DOLLAR)
				||(uin.key.keysym.unicode==SDLK_QUOTEDBL)
				||(uin.key.keysym.unicode=='^')
				||(uin.key.keysym.unicode==SDLK_AMPERSAND)
				||(uin.key.keysym.unicode==SDLK_ASTERISK)
				||(uin.key.keysym.unicode==SDLK_LEFTPAREN)
				||(uin.key.keysym.unicode==SDLK_RIGHTPAREN)
				||(uin.key.keysym.unicode==SDLK_MINUS)
				||(uin.key.keysym.unicode==SDLK_SPACE)
				||(uin.key.keysym.unicode==SDLK_SPACE)
				||(uin.key.keysym.unicode==SDLK_SLASH)
				||(uin.key.keysym.unicode==SDLK_SPACE)
				||(uin.key.keysym.unicode==SDLK_SEMICOLON)
				||(uin.key.keysym.unicode==SDLK_COLON)
				||(uin.key.keysym.unicode==SDLK_QUOTE)
				||(uin.key.keysym.unicode==SDLK_COMMA)
				||(uin.key.keysym.unicode==SDLK_SPACE)
				||(uin.key.keysym.unicode==SDLK_PERIOD)
				||(uin.key.keysym.unicode==SDLK_SPACE))
				{
					input+=((char)uin.key.keysym.unicode);
				}
				else
				{
					switch((unsigned int)uin.key.keysym.unicode)
					{
					case SDLK_BACKSPACE:
						input.erase(input.size()-1);
					break;
					}
				}
				//ofstream log("temp.txt",ios::app);
				//log<<input<<"\n";
				//log.close();
			}
		}
	}
	SDL_EnableUNICODE( SDL_DISABLE );
	return 0;
}
#endif /* GLOBAL_ASSETS_HPP_ */
