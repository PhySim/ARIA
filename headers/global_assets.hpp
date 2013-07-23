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

#include <headers/framer.hpp>
#include <headers/mutex.hpp>
#include <headers/thread.hpp>


using namespace std;

bool ended=0;
SDL_Surface* scr;
SDL_Event event;
TTF_Font* font;

class stringinput_data : public ThreadData
{
public:
	string input;
};

int stringinput(void* data)
{
	SDL_EnableUNICODE( SDL_ENABLE );
	SDL_Event uin;
	timer time;
	time.start();
	stringinput_data* tdata=static_cast<stringinput_data*>(data);
	{
		access(tdata->mutex);
		tdata->done=false;
	}
	string temp;
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
				||(uin.key.keysym.unicode==SDLK_ESCAPE)
				||(uin.key.keysym.unicode==SDLK_BACKSPACE)
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
					temp+=((char)uin.key.keysym.unicode);
				}
			}
		}
		if(time.elapse()>300)
		{
			access(tdata->mutex);
			if(temp.size())
			{
				tdata->dataready=true;
				for(unsigned int i=0;i<temp.size();i++)
				{
					switch(temp[i])
					{
					case SDLK_BACKSPACE:
						if(tdata->input.size()>0)
							tdata->input.erase(tdata->input.size()-1);
					break;
					case SDLK_ESCAPE:
						tdata->input.erase();
					break;
					default:
						tdata->input+=temp[i];
					break;
					}
				}
			}
			time.reset();
			time.start();
			temp.erase();
		}
	}
	{
		access(tdata->mutex);
		tdata->done=true;
	}
	SDL_EnableUNICODE( SDL_DISABLE );
	return 0;
}


#endif /* GLOBAL_ASSETS_HPP_ */
