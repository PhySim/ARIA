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
#include <vector>

#include <physim/headers/framer.hpp>

#define load_font(A,B) TTF_OpenFont(A,B)

using namespace std;
void error(const char* E)
{
	ofstream log("logs/global_assets.hpp.txt",ios::app);
	log<<E<<'\n';
	log.close();
}
SDL_Surface* scr;
SDL_Event event;
unsigned int global_graphicstring_id=0;

/*const char* default_font_loc="Fonts/KeraterMedium.ttf";
unsigned int default_font_size=28;*/

struct FONT
{
	string font_loc;
	unsigned int size;
	TTF_Font* font;
	FONT(const char* U_font_loc,unsigned int U_font_size,TTF_Font* U_font=NULL)
	{
		font_loc=U_font_loc;
		size=U_font_size;
		if(font)
			font=U_font;
		else
			TTF_OpenFont(U_font_loc,U_font_size);
	}
};
class FONT_POCKET
{
	vector<FONT>fonts;
	FONT default_font;
public:
	TTF_Font* new_font(const char* U_font_loc,unsigned int U_font_size)
	{
		for(unsigned int i=0;i<fonts.size();i++)
		{
			if(fonts[i].size==U_font_size)
			{
				if(fonts[i].font_loc.compare(U_font_loc)==0)
				{
					return fonts[i].font;
				}
			}
		}
		TTF_Font* font=TTF_OpenFont(U_font_loc,U_font_size);
		if(font)
		{
			fonts.push_back(FONT(U_font_loc,U_font_size,font));
			ofstream fout("logs/allocation log.txt",ios::app);
			fout<<"Font "<<U_font_loc<<"("<<fonts[fonts.size()-1].font<<") loaded into slot "<<(fonts.size()-1)<<'\n';
			fout.close();
			return fonts[fonts.size()-1].font;
		}
		return NULL;
	}
	TTF_Font* new_font()
	{
		return default_font.font;
	}
	FONT_POCKET(FONT U_default_font):default_font(U_default_font)
	{
	}
	~FONT_POCKET()
	{
		ofstream fout("logs/allocation log.txt",ios::app);
		fout<<"\nEmptying font pocket("<<fonts.size()<<" fonts to close):";
		for(unsigned int i=fonts.size()-1;i>=0;i--)
		{
			if(fonts[i].font)
			{
				try
				{
					TTF_CloseFont(fonts[i].font);
					fout<<"Font "<<i<<" closed\n";
				}
				catch(...)
				{
					fout<<"Closing font "<<i<<" failed!\n";
				}
			}
		}
		fout.close();
	}
};
class graphicstring
{
protected:
	timer imagetimer;
	unsigned int graphic_update_interval,max_char;
	int lines,line,xspacing,yspacing;
	SDL_Surface *scr,*image[3];
	SDL_Rect rect[3];
	string text[3];
	string all;
	TTF_Font* font;
	SDL_Color TextColor;
	bool font_loaded;

	void general_set()
	{
		for(int i=0;i<lines;i++)
		{
			text[i].clear();
		}
		unsigned int progress=0;
		line=-1;
		compute_size_limit();
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
	unsigned int compute_size_limit()
	{
		if(rect[0].h)
			max_char=2*(scr->w-xspacing)/rect[0].h;
		else
			max_char=40;
		return max_char;
	}
	bool renderimages(bool forced=0)
	{
		if((imagetimer.elapse()>graphic_update_interval||forced)&&font)
		{
			for(int i=0;i<=line;i++)
			{
				if(text[i].size()>0&&font_loaded)
				{
					if(image[i]!=NULL)
					{
						try
						{
							SDL_FreeSurface(image[i]);
						}
						catch(...)
						{
							ofstream fout("logs/allocation log.txt",ios::app);
							fout<<"graphicstring::renderimages FreeSurface() failed\n";
							fout.close();
						}
					}
					image[i]=TTF_RenderText_Solid(font,text[i].c_str(),TextColor);
					if(image[i])
					{
						rect[i].w=image[i]->w;
						rect[i].h=image[i]->h;
						if(forced)
						{
							set_position(xspacing,yspacing);
						}
					}
					else
					{
						ofstream fout("logs/allocation log.txt",ios::app);
						fout<<"graphicstring::renderimages: Failed to render text image "<<i<<'\n';
						fout.close();
					}
				}
			}
			imagetimer.reset();
			imagetimer.start();
			return true;
		}
		else return false;
	}
public:
	bool done;
	void set(string newstring)
	{
		all.assign(newstring);
		general_set();
	}
	void operator=(string newstring)
	{
		set(newstring);
	}
	void set(const char* new_text)
	{
		all.assign(new_text);
		general_set();
	}
	void operator=(const char* new_text)
	{
		set(new_text);
	}
	void set(int i)
	{
		char U[10];
		itoa(i,U,10);
		all.assign(U);
		general_set();
	}
	void operator=(int i)
	{
		set(i);
	}
	void set(double d)
	{
		char U[10];
		sprintf(U,"%f",d);
		all.assign(U);
		general_set();
	}
	void operator=(double d)
	{
		set(d);
	}
	void set_color(SDL_Color Ucol)
	{
		TextColor=Ucol;
	}
	void set_font(TTF_Font* U_font)
	{
		ofstream fout("logs/allocation log.txt",ios::app);
		fout<<"graphicstring::set_font received font : "<<U_font<<'\n';
		fout.close();
		if(U_font)
		{
			font=U_font;
			font_loaded=true;
		}
		else
		{
			font_loaded=false;
			error("graphicstring::set_font received NULL font!");
		}
		renderimages(1);
	}
	void set_color(unsigned int r,unsigned int g,unsigned int b)
	{
		TextColor.r=r;
		TextColor.g=g;
		TextColor.b=b;
	}
	void set_position(int x,int y)
	{
		if(x!=xspacing||y!=yspacing)
		{
			if(imagetimer.elapse()>graphic_update_interval)
				general_set();
		}
		xspacing=x;yspacing=y;
		for(int i=0;i<lines;i++)
		{
			rect[i].x=xspacing;
			rect[i].y=yspacing+(i)*rect[i].h;
		}
	}
	void set_position(vect position)
	{
		set_position(position.x,position.y);
	}
	void set_update_interval(unsigned int Ugraphic_update_interval=50)
	{
		graphic_update_interval=Ugraphic_update_interval;
	}
	graphicstring(SDL_Surface* screen,TTF_Font* U_font=NULL,string U_text="$",unsigned int Ugraphic_update_interval=50)
	{
		scr=screen;
		lines=3;
		line=done=0;
		xspacing=10;yspacing=10;
		font=NULL;
		//max_char=2*(scr->w-xspacing)/global_font_size;
		graphic_update_interval=Ugraphic_update_interval;
		TextColor.r=255;
		TextColor.g=0;
		TextColor.b=0;
		set_font(U_font);
		for(int i=0;i<lines;i++)
		{
			text[i]="";
			rect[i].x=xspacing;
			rect[i].y=yspacing;
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
		if(font)
			TTF_CloseFont(font);
	}
	void display()
	{
		renderimages();
		for(int i=0;i<=line&&image[i]!=NULL;i++)
		{
			if(image[i])
				SDL_BlitSurface(image[i],NULL,scr,&rect[i]);
		}
	}
	const char* c_str()
	{
		return all.c_str();
	}
};
string buf;
class graphicstringinput:public graphicstring
{
	char new_char;
	timer imagetimer;
	timer start,repeat;
	unsigned int start_time,repeat_time;

	SDL_Color TextColor;
	void reset()
	{
		line=done=0;
		for(int i=0;i<lines;i++)
		{
			text[i].assign("");
			rect[i].x=xspacing;
			rect[i].y=yspacing;
			if(image[i])
			{
				SDL_FreeSurface(image[i]);
			}
			image[i]=NULL;
		}
		text[0].assign("$");
		imagetimer.reset();
		imagetimer.start();
	}
public:
	bool done;
	graphicstringinput(SDL_Surface* screen,TTF_Font* U_font=NULL,string U_text="$",unsigned int UstartT=500,unsigned int UrepeatT=25,unsigned int Ugraphic_update_interval=50):graphicstring(screen,U_font,U_text,Ugraphic_update_interval)
	{
		max_char=2*(scr->w-xspacing)/10;
		start_time=UstartT;repeat_time=UrepeatT;
		for(int i=0;i<lines;i++)
			image[i]=NULL;
		new_char=0;
		finished();
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
	const char* get()
	{
		buf=text[0].substr(1,text[0].size()-1);
		buf+=text[1].substr(0,text[1].size());
		buf+=text[2].substr(0,text[2].size());
		return buf.c_str();
	}
	void finished(bool U=true)
	{
		done=U;
		if(!U)
		{
			reset();
		}
	}
};

#endif /* GLOBAL_ASSETS_HPP_ */
