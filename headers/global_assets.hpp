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

#include <physim/headers/framer.hpp>
#include <headers/mutex.hpp>
#include <headers/thread.hpp>


using namespace std;

bool ended=0;
SDL_Surface* scr;
SDL_Event event;
TTF_Font* font;
unsigned int global_font_size;

class graphicstring
{
	timer imagetimer;
	unsigned int graphic_update_interval,max_char;
	int lines,line,xspacing,yspacing;
	SDL_Rect rect[3];
	string text[3];
	SDL_Surface* image[3];
public:
	bool done;
	graphicstring(string U_text,unsigned int Ugraphic_update_interval=50)
	{
		lines=3;
		line=done=0;
		xspacing=10;yspacing=50;
		max_char=2*(scr->w-xspacing)/global_font_size;
		graphic_update_interval=Ugraphic_update_interval;
		for(int i=0;i<lines;i++)
		{
			text[i]="";
			rect[i].x=xspacing;
			rect[i].y=yspacing+i*global_font_size;
		}
		set(U_text);
		renderimages(1);
	}
	~graphicstring()
	{
		for(int i=0;i<lines;i++)
			SDL_FreeSurface(image[i]);
	}
	void renderimages(bool forced=0)
	{
		if(imagetimer.elapse()>graphic_update_interval||forced)
		{
			for(int i=0;i<=line;i++)
			{
				if(text[i].size()>0)
				{
					image[i]=TTF_RenderText_Solid(font,text[i].c_str(),(SDL_Color){0,0xFF,0});
					rect[i].w=image[i]->w;
					rect[i].h=image[i]->h;
				}
				else image[i]=NULL;
			}
			imagetimer.reset();
			imagetimer.start();
		}
	}
	void set(string newstring)
	{
		unsigned int progress=0;
		line=-1;
		while(progress<newstring.size())
		{
			line++;
			text[line]=newstring.substr(progress,max_char<newstring.size()?max_char:newstring.size());
			progress+=text[line].size();
		}
	}
	void display()
	{
		renderimages();
		for(int i=0;i<=line&&image[i]!=NULL;i++)
			SDL_BlitSurface(image[i],NULL,scr,&rect[i]);
	}
};

class graphicstringinput
{
	char new_char;
	timer imagetimer;
	timer start,repeat;
	unsigned int start_time,repeat_time,graphic_update_interval,max_char;
	int lines,line,xspacing,yspacing;
public:
	SDL_Rect rect[3];
	string text[3];
	SDL_Surface* image[3];
	bool done;
	graphicstringinput(unsigned int UstartT=500,unsigned int UrepeatT=50,unsigned int Ugraphic_update_interval=50)
	{
		lines=3;
		line=done=0;
		xspacing=10;yspacing=50;
		max_char=2*(scr->w-xspacing)/global_font_size;
		start_time=UstartT;repeat_time=UrepeatT;graphic_update_interval=Ugraphic_update_interval;
		for(int i=0;i<lines;i++)
		{
			text[i]="";
			rect[i].x=xspacing;
			rect[i].y=yspacing+i*global_font_size;
		}
		text[0]="$";
		renderimages(1);
		new_char=0;
	}
	~graphicstringinput()
	{
		for(int i=0;i<lines;i++)
			SDL_FreeSurface(image[i]);
	}
	void renderimages(bool forced=0)
	{
		if(imagetimer.elapse()>graphic_update_interval||forced)
		{
			for(int i=0;i<=line;i++)
			{
				if(text[i].size()>0)
				{
					image[i]=TTF_RenderText_Solid(font,text[i].c_str(),(SDL_Color){0,0xFF,0});
					rect[i].w=image[i]->w;
					rect[i].h=image[i]->h;
				}
				else image[i]=NULL;
			}
			imagetimer.reset();
			imagetimer.start();
		}
	}
	void handle_input(SDL_Event event)
	{
		if(event.type==SDL_KEYDOWN&&!done)
		{
			if((event.key.keysym.unicode>='A'&&event.key.keysym.unicode<='Z')
			||(event.key.keysym.unicode>='a'&&event.key.keysym.unicode<='z')
			||(event.key.keysym.unicode>='0'&&event.key.keysym.sym<='9')
			||(event.key.keysym.unicode==SDLK_SPACE)
			||(event.key.keysym.unicode==SDLK_RETURN)
			||(event.key.keysym.unicode==SDLK_BACKSPACE)
			||(event.key.keysym.unicode==SDLK_TAB)
			||(event.key.keysym.unicode==SDLK_EXCLAIM)
			||(event.key.keysym.unicode==SDLK_AT)
			//||(event.key.keysym.unicode==SDLK_HASH)
			||(event.key.keysym.unicode==SDLK_DOLLAR)
			||(event.key.keysym.unicode==SDLK_QUOTEDBL)
			||(event.key.keysym.unicode=='^')
			||(event.key.keysym.unicode==SDLK_AMPERSAND)
			||(event.key.keysym.unicode==SDLK_ASTERISK)
			||(event.key.keysym.unicode==SDLK_LEFTPAREN)
			||(event.key.keysym.unicode==SDLK_RIGHTPAREN)
			||(event.key.keysym.unicode==SDLK_MINUS)
			||(event.key.keysym.unicode==SDLK_SPACE)
			||(event.key.keysym.unicode==SDLK_SPACE)
			||(event.key.keysym.unicode==SDLK_SLASH)
			||(event.key.keysym.unicode==SDLK_SPACE)
			||(event.key.keysym.unicode==SDLK_SEMICOLON)
			||(event.key.keysym.unicode==SDLK_COLON)
			||(event.key.keysym.unicode==SDLK_QUOTE)
			||(event.key.keysym.unicode==SDLK_COMMA)
			||(event.key.keysym.unicode==SDLK_SPACE)
			||(event.key.keysym.unicode==SDLK_PERIOD)
			||(event.key.keysym.unicode==SDLK_SPACE))
			{
				if(new_char!=(char)event.key.keysym.unicode)
				{
					start.reset();
				}
				start.start();
				if(new_char!=(char)event.key.keysym.unicode||start.elapse()==0||(start.elapse()>start_time&&(repeat.elapse()==0||repeat.elapse()>repeat_time)))
				{
					new_char=(char)event.key.keysym.unicode;
					switch(new_char)
					{
					case 0:
						//do nothing
					break;
					case SDLK_BACKSPACE:
						if(text[line].size()>1)
							text[line].erase(text[line].size()-1);
						else if(line>0)
						{
							text[line]="";
							line--;
						}
					break;
					case SDLK_RETURN:
						done=true;
					break;
					default:
						if(text[line].size()<max_char)
							text[line]+=new_char;
						else if(line+1<lines)
						{
							line++;
							text[line]+=new_char;
						}
					break;
					}
				}

				if(start.elapse()>start_time)
				{
					if(repeat.elapse()>repeat_time)
						repeat.reset();
					repeat.start();
				}
			}
		}
		else
		{
			start.reset();
		}
	}
	void display()
	{
		renderimages();
		for(int i=0;i<=line&&image[i]!=NULL;i++)
			SDL_BlitSurface(image[i],NULL,scr,&rect[i]);
	}
};

#endif /* GLOBAL_ASSETS_HPP_ */
