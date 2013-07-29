/*
 * aria.hpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#ifndef ARIA_HPP_
#define ARIA_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <headers/events.hpp>
#include <headers/global_assets.hpp>
#include <headers/DB.hpp>

class ARIA
{
private:
	unsigned int font_size;
	void set_word_types()
	{
		word_type.verb.action.physical=1;
		word_type.verb.action.mental=2;
		word_type.verb.condition=3;
		word_type.verb.state=4;
		word_type.verb.auxiliary=5;
		word_type.noun.proper=6;
		word_type.noun.improper=7;
		word_type.noun.plural=8;
		word_type.noun.antecedent=9;
		word_type.pronoun.personal=10;
		word_type.pronoun.possessive=11;
		word_type.pronoun.reflexive=12;
		word_type.pronoun.intensive=13;
		word_type.pronoun.indefinite=14;
		word_type.pronoun.demonstrative=15;
		word_type.pronoun.interrogative=16;
		word_type.pronoun.relative=17;
		word_type.pronoun.reciprocal=18;
		word_type.adjective.describe=19;
		word_type.adjective.identify=20;
		word_type.adjective.quantify=21;
		word_type.interjection.salutation=22;
		word_type.interjection.command=23;
		word_type.interjection.protest=24;
		word_type.interjection.surprise=25;
		word_type.interjection.pain=26;
		word_type.interjection.pleasure=27;
		word_type.interjection.pity=28;
		word_type.interjection.resignation=29;
		word_type.interjection.enquiry=30;
		word_type.interjection.attention=31;
		word_type.interjection.plead=32;
		word_type.interjection.hesitation=33;
		word_type.interjection.agreement=34;
		word_type.conjuction.coordinating=35;
		word_type.conjuction.subordinating=36;
		word_type.conjuction.correlative=37;
		word_type.conjuction.adverb.comparison=38;
		word_type.conjuction.adverb.contrast=39;
		word_type.conjuction.adverb.cause_effect=40;
		word_type.preposition.space=41;
		word_type.preposition.time=42;
	}
public:
	ARIA(unsigned int w,unsigned int h,unsigned int U_font_size=global_font_size)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_WM_SetCaption("ARIA:Automated Response-Intelligent Acquisition -By Reuben John",NULL);
		TTF_Init();
		SDL_EnableUNICODE( SDL_ENABLE );
		SDL_FreeSurface(scr);
		::global_font_size=font_size=U_font_size;
		scr=SDL_SetVideoMode(w,720,32,SDL_SWSURFACE|SDL_RESIZABLE);
		font=TTF_OpenFont("fonts/lazy.ttf",font_size);
		set_word_types();
	}
	~ARIA()
	{
		SDL_Quit();
	}
	void handleevents()
	{
		SDL_PollEvent(&event);
		if(event.type==SDL_QUIT)
		{
				ended=true;
		}
	}
};


#endif /* ARIA_HPP_ */
