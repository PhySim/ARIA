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

using namespace std;
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
			fout<<"Font "<<U_font_loc<<" "<<U_font_size<<" ("<<fonts[fonts.size()-1].font<<") loaded into slot "<<(fonts.size()-1)<<'\n';
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

const char* millisecond_fotmatted_string(int milliseconds)
{
	string result;
	bool negative=milliseconds<0;
	if(negative)
		milliseconds=-milliseconds;
	int seconds = (int) (milliseconds / 1000) % 60 ;
	int minutes = (int) ((milliseconds / (1000*60)) % 60);
	int hours   = (int) ((milliseconds / (1000*60*60)) % 24);

	int remaining_milliseconds= (int) (milliseconds) % 1000 ;

	char C[4]="";
	itoa(hours,C,10);
	if(strlen(C)==1)
		result="0";
	result+=C;result+=":";
	itoa(minutes,C,10);
	if(strlen(C)==1)
		result+="0";
	result+=C;result+=":";
	itoa(seconds,C,10);
	if(strlen(C)==1)
		result+="0";
	result+=C;result+=".";
	itoa(remaining_milliseconds,C,10);
	if(strlen(C)==1)
		result+="0";
	result+=C;

	//----------------------------
	result.erase(0,3);
	if(negative)
	{
		result.insert(0,1,'-');
	}
	return result.c_str();
}

const char* decimal_format_string(double d,const char* format="%8.2f")
{
	string temp;
	char U[30];
	sprintf(U,format,d);
	temp.assign(U);
	return temp.c_str();
}
class GRAPHIC_STRING
{
protected:
	SDL_Surface* scr;
	SDL_Rect rect;
	SDL_Surface* image;
	TTF_Font* font;
	SDL_Color col;
	string all;
	unsigned int update_interval;
	timer imagetimer;
	bool fresh_data;
	void general_set(const char* new_string,bool force_render=false)
	{
		all.assign(new_string);
		render_image(force_render);
	}
public:
	SDL_Rect rectangle()
	{
		return rect;
	}
	virtual void operator=(const char* text)
	{
		general_set(text,all.empty());
	}
	virtual void operator=(string newstring)
	{
		general_set(newstring.c_str(),all.empty());
	}
	virtual void operator=(int i)
	{
		char U[10];
		itoa(i,U,10);
		general_set(U,all.empty());
	}
	virtual void operator=(double d)
	{
		general_set(decimal_format_string(d),all.empty());
	}
	void set_time(int milliseconds)
	{
		all.clear();
		bool negative=milliseconds<0;
		if(negative)
			milliseconds=-milliseconds;
		int seconds = (int) (milliseconds / 1000) % 60 ;
		int minutes = (int) ((milliseconds / (1000*60)) % 60);
		int hours   = (int) ((milliseconds / (1000*60*60)) % 24);

		int remaining_milliseconds= (int) (milliseconds) % 1000 ;

		char C[4]="";
		itoa(hours,C,10);
		if(strlen(C)==1)
			all="0";
		all+=C;all+=":";
		itoa(minutes,C,10);
		if(strlen(C)==1)
			all+="0";
		all+=C;all+=":";
		itoa(seconds,C,10);
		if(strlen(C)==1)
			all+="0";
		all+=C;all+=".";
		itoa(remaining_milliseconds,C,10);
		if(strlen(C)==1)
			all+="0";
		all+=C;

		//----------------------------
		all.erase(0,3);
		if(negative)
		{
			all.insert(0,1,'-');
		}
	}
	bool operator==(const char* text)
	{
		return all.compare(text)==0;
	}
	bool operator!=(const char* text)
	{
		return !(all.compare(text)==0);
	}
	void set_font(TTF_Font * Font)
	{
		ofstream fout("logs/log.txt",ios::app);
		fout<<"GRAPHIC_STRING::set_font received font : "<<Font<<'\n';
		fout.close();
		if(Font)
		{
			font=Font;
			render_image(1);
		}
	}
	void set_position(unsigned int x,unsigned int y)
	{
			rect=((SDL_Rect){x,y});
	}
	void set_position(vect pos)
	{
		set_position(pos.x,pos.y);
	}
	void set_color(short unsigned int r,short unsigned int g,short unsigned int b)
	{
		col=(SDL_Color){r,g,b};
	}
	void set_update_interval(unsigned int Update_interval)
	{
		update_interval=Update_interval;
	}
	GRAPHIC_STRING(SDL_Surface* screen,TTF_Font* Font=NULL,unsigned int Update_interval=100)
	{
		scr=screen;
		image=NULL;
		rect.w=rect.h=0;
		font=Font;
		col=(SDL_Color){0,0,0};
		set_position(10,10);
		update_interval=Update_interval;
		fresh_data=false;
		all.clear();
		imagetimer.start();
	}
	void render_image(bool forced=false)
	{
		if(imagetimer.elapse()>update_interval||forced)
		{
			if(image)
			{
				try
				{
					SDL_FreeSurface(image);
				}
				catch(...)
				{
					ofstream fout("logs/log.txt",ios::app);
					fout<<"GRAPHIC_STRING::render_image failed to free surface\n";
					fout.close();
				}
			}
			image=NULL;
			if(font)
			{
				if(!all.empty())
				{
					image=TTF_RenderText_Solid(font,all.c_str(),col);
					rect.w=image->clip_rect.w;
					rect.h=image->clip_rect.h;
				}
				else
				{
					ofstream fout("logs/log.txt",ios::app);
					fout<<"GRAPHIC_STRING::render_image string empty\n";
					fout.close();
					rect.w=rect.h=0;
					image=NULL;
				}
			}
			else
			{
				ofstream fout("logs/log.txt",ios::app);
				fout<<"GRAPHIC_STRING::render_image attempted NULL font Rendering\n";
				fout.close();
			}
			imagetimer.reset();
			imagetimer.start();
		}
	}
	void display(bool demand_rendering=false)
	{
		render_image(demand_rendering);
		if(scr)
		{
			if(image)
				SDL_BlitSurface(image,NULL,scr,&rect);
			else
			{
				ofstream fout("logs/log.txt",ios::app);
				fout<<"GRAPHIC_STRING::display image NULL access\n";
				fout.close();
			}
		}
		else
		{
			ofstream fout("logs/log.txt",ios::app);
			fout<<"GRAPHIC_STRING::display scr NULL access\n";
			fout.close();
		}
	}
	virtual ~GRAPHIC_STRING()
	{
		ofstream fout("logs/allocation log.txt",ios::app);
		fout<<"GRAPHIC_STRING destroyed\n";
		fout.close();
		if(image)
			SDL_FreeSurface(image);
		all.clear();
	}
};

class GRAPHIC_STRING_INPUT:public GRAPHIC_STRING
{
	char new_char;
	timer imagetimer;
	timer start,repeat;
	unsigned int start_time,repeat_time;
	bool done;
	SDL_Color TextColor;
	void reset()
	{
		done=false;
		fresh_data=false;
		all.clear();
		if(image)
		{
			SDL_FreeSurface(image);
			image=NULL;
			rect.w=rect.h=0;
		}
		imagetimer.reset();
		imagetimer.start();

	}
public:
	GRAPHIC_STRING_INPUT(SDL_Surface* screen,TTF_Font* U_font=NULL,unsigned int UstartT=500,unsigned int UrepeatT=25,unsigned int Ugraphic_update_interval=50):GRAPHIC_STRING(screen,U_font,Ugraphic_update_interval)
	{
		start_time=UstartT;repeat_time=UrepeatT;
		new_char=0;
		finished();
	}
	~GRAPHIC_STRING_INPUT()
	{
		SDL_FreeSurface(image);
	}
	void operator=(const char* text)
	{
		GRAPHIC_STRING::operator=(text);
	}
	void operator=(string newstring)
	{
		GRAPHIC_STRING::operator=(newstring);
	}
	void operator=(int i)
	{
		GRAPHIC_STRING::operator=(i);
	}
	void operator=(double d)
	{
		GRAPHIC_STRING::operator=(d);
	}
	bool completed()
	{
		return done;
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
						if(all.size()>0)
							all.erase(all.size()-1);
					break;
					case SDLK_RETURN:
						finished();
					break;
					default:
						all+=new_char;
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
		return all.c_str();
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
