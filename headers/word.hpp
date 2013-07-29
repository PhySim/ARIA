/*
 * word.h
 *
 *  Created on: Jul 25, 2013
 *      Author: Reuben
 */

#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <vector>

#include <headers/stats.hpp>

using namespace std;

const unsigned int word_size=32;

struct WORD_TYPE
{
	struct
	{
		struct
		{
			bool physical;
			bool mental;
		}action;
		bool condition;
		bool state;
		bool auxiliary;
	}verb;
	struct
	{
		bool proper,improper;
		bool plural;
		bool antecedent;
	}noun;
	struct
	{
		bool personal,possessive,reflexive,intensive,indefinite,demonstrative,interrogative,relative,reciprocal;
	}pronoun;
	struct
	{
		bool describe,identify,quantify;
	}adjective;
	struct
	{

	}adverb;
	struct
	{
		bool salutation,command,protest,surprise,pain,pleasure,pity,resignation,enquiry,attention,plead,hesitation,agreement;
	}interjection;
	struct
	{
		bool coordinating,subordinating,correlative;
		struct
		{
			bool comparison,contrast,cause_effect;
		}adverb;
	}conjuction;
	struct
	{
		bool time,space;
	}preposition;
}word_type;

class word:public stats
{
public:
	string name,type;
	word(string U_name="$")
	{
		name=U_name;
		type="$";
	}
	~word()
	{

	}
}word_buf;
class word_io
{
public:
	char name_io[word_size],type_io[word_size];
	unsigned int rating,usage;
	void reset()
	{
		for(unsigned int i=0;i<word_size;i++)
		{
			name_io[i]=type_io[i]=0;
		}

		rating=50;
		usage=1;
	}
	word_io()
	{
		for(unsigned int i=0;i<word_size;i++)
		{
			name_io[i]=type_io[i]=0;
		}
		rating=0;
		usage=0;
	}
	word_io(word U)
	{
		reset();
		if(U.name.size())
			strcpy(name_io,U.name.c_str());
		if(U.type.size())
			strcpy(type_io,U.type.c_str());
	}
};
word ExtractWord(word_io U)
{
	word* word_buf=new word();
	word_buf->name.assign(U.name_io);
	word_buf->type=U.type_io;
	word_buf->rating=U.rating;
	word_buf->usage=U.usage;
	return *word_buf;
}

#endif /* WORD_H_ */
