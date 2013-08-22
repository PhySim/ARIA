/*
 * global_assets.hpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Reuben
 */

#ifndef GLOBAL_ASSETS_HPP_
#define GLOBAL_ASSETS_HPP_

#include <SDL/SDL.h>
#include <SDL/SDl_ttf.h>
#include <string>
#include <stdio.h>

#include <physim/headers/framer.hpp>


using namespace std;

bool ended=0;
SDL_Surface* scr;
SDL_Event event;
TTF_Font* font;
unsigned int global_font_size=32,global_graphicstring_id=0;

class graphicstring
{
	timer imagetimer;
	unsigned int graphic_update_interval,max_char;
	int lines,line,xspacing,yspacing;
	SDL_Rect rect[3];
	string text[3];
	string all;
	TTF_Font* font;
	SDL_Color TextColor;
	void general_set()
	{
		for(int i=0;i<lines;i++)
		{
			text[i].clear();
		}
		unsigned int progress=0;
		line=-1;
		while(progress<all.size()&&line<lines-1)
		{
			line++;
			all.push_back('\0');
			text[line].assign(all.substr(progress,max_char<(all.size()-progress)?max_char:(all.size()-progress)));
			progress+=text[line].size();
			bool stop=false;
			for(unsigned int i=0;i<text[line].size()&&!stop;i++)
			{
				if((text[line][i]=='\n'&&text[line][i+1]!='\0')&&line<lines-1)
				{
					text[line+1].assign(text[line].substr(i+1,text[line].size()-(i+2)));
					text[line].erase(i,text[line].size());
					stop=true;
					line++;
				}
			}
		}
		renderimages(1);
	}
protected:
	void renderimages(bool forced=0)
	{
		if(imagetimer.elapse()>graphic_update_interval||forced)
		{
			for(int i=0;i<=line;i++)
			{
				if(text[i].size()>0)
				{
					if(image[i]!=NULL)
						SDL_FreeSurface(image[i]);
					image[i]=TTF_RenderText_Solid(font,text[i].c_str(),TextColor);
					rect[i].w=image[i]->w;
					rect[i].h=image[i]->h;
				}
				else image[i]=NULL;
			}
			imagetimer.reset();
			imagetimer.start();
		}
	}
public:
	SDL_Surface* image[3];
	bool done;
	void set(string newstring)
	{
		all.assign(newstring);
		general_set();
	}
	void set(const char* U)
	{
		all.assign(U);
		general_set();
	}
	void set(int i)
	{
		char U[10];
		itoa(i,U,10);
		all.assign(U);
		general_set();
	}
	void set(double d)
	{
		char U[10];
		sprintf(U,"%f",d);
		all.assign(U);
		general_set();
	}
	void set_font(SDL_Color Ucol)
	{
		TextColor=Ucol;
	}
	void set_font(int U_font_size,const char* font_loc="Fonts/lazy.ttf")
	{
		font=TTF_OpenFont(font_loc,U_font_size);
		renderimages(1);
	}
	void set(unsigned int r,unsigned int g,unsigned int b)
	{
		TextColor.r=r;
		TextColor.g=g;
		TextColor.b=b;
	}
	void set(unsigned int x,unsigned int y)
	{
		xspacing=x;yspacing=y;
		for(int i=0;i<lines;i++)
		{
			rect[i].x=xspacing;
			rect[i].y=yspacing+(i)*global_font_size;
		}
	}
	graphicstring(string U_text="$",unsigned int Ugraphic_update_interval=50)
	{
		lines=3;
		line=done=0;
		xspacing=10;yspacing=10;
		max_char=2*(scr->w-xspacing)/global_font_size;
		graphic_update_interval=Ugraphic_update_interval;
		TextColor.r=255;
		TextColor.g=0;TextColor.b=0;
		font=::font;
		for(int i=0;i<lines;i++)
		{
			text[i]="";
			rect[i].x=xspacing;
			rect[i].y=yspacing+(global_graphicstring_id*(lines+1)+i)*global_font_size;
			image[i]=NULL;
		}
		global_graphicstring_id++;
		set(U_text);
		renderimages(1);
		imagetimer.start();
	}
	~graphicstring()
	{
		for(int i=0;i<lines;i++)
			SDL_FreeSurface(image[i]);
		if(font!=::font)
			TTF_CloseFont(font);
	}
	void display()
	{
		renderimages();
		for(int i=0;i<=line&&image[i]!=NULL;i++)
			SDL_BlitSurface(image[i],NULL,scr,&rect[i]);
	}
	const char* c_str()
	{
		return all.c_str();
	}
};

class graphicstringinput
{
	SDL_Rect rect[3];
	string text[3];
	SDL_Surface* image[3];
	char new_char;
	timer imagetimer;
	timer start,repeat;
	unsigned int start_time,repeat_time,graphic_update_interval,max_char;
	int lines,line,xspacing,yspacing;
	void reset()
	{
		line=done=0;
		for(int i=0;i<lines;i++)
		{
			text[i].assign("");
			rect[i].x=xspacing;
			rect[i].y=yspacing+i*global_font_size;
		}
		text[0].assign("$");
		imagetimer.reset();
		imagetimer.start();
	}
public:
	string all;
	bool done;
	void renderimages(bool forced=0)
	{
		if(imagetimer.elapse()>graphic_update_interval)
		{
			for(int i=0;i<=line;i++)
			{
				if(text[i].size()>0)
				{
					if(image[i]!=NULL)
						SDL_FreeSurface(image[i]);
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
	graphicstringinput(unsigned int UstartT=500,unsigned int UrepeatT=25,unsigned int Ugraphic_update_interval=50)
	{
		xspacing=10;yspacing=50;
		lines=3;
		max_char=2*(scr->w-xspacing)/global_font_size;
		start_time=UstartT;repeat_time=UrepeatT;graphic_update_interval=Ugraphic_update_interval;
		reset();
		for(int i=0;i<lines;i++)
			image[i]=NULL;
		renderimages(1);
		new_char=0;
		global_graphicstring_id++;
	}
	~graphicstringinput()
	{
		for(int i=0;i<lines;i++)
			SDL_FreeSurface(image[i]);
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
						finished();
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
	void get(string &temp)
	{
		temp=text[0].substr(1,text[0].size()-1);
		temp+=text[1].substr(0,text[1].size());
		temp+=text[2].substr(0,text[2].size());
	}
	void finished(bool U=1)
	{
		done=U;
		if(!U)
		{
			reset();
		}
	}
};

#endif /* GLOBAL_ASSETS_HPP_ */
