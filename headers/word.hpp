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
	bool adverb;
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
	void reset()
	{
		verb.condition=0;
		verb.state=0;
		verb.auxiliary=0;
		verb.action.physical=0;
		verb.action.mental=0;
		noun.proper=0;
		noun.improper=0;
		noun.plural=0;
		noun.antecedent=0;
		pronoun.personal=0;
		pronoun.possessive=0;
		pronoun.reflexive=0;
		pronoun.intensive=0;
		pronoun.indefinite=0;
		pronoun.demonstrative=0;
		pronoun.interrogative=0;
		pronoun.relative=0;
		pronoun.reciprocal=0;
		adjective.describe=0;
		adjective.identify=0;
		adjective.quantify=0;
		adverb=0;
		interjection.salutation=0;
		interjection.command=0;
		interjection.protest=0;
		interjection.surprise=0;
		interjection.pain=0;
		interjection.pleasure=0;
		interjection.pity=0;
		interjection.resignation=0;
		interjection.enquiry=0;
		interjection.attention=0;
		interjection.plead=0;
		interjection.hesitation=0;
		interjection.agreement=0;
		conjuction.coordinating=0;
		conjuction.subordinating=0;
		conjuction.correlative=0;
		preposition.space=0;
		preposition.time=0;

	}
};

class word:public stats
{
public:
	string name;
	WORD_TYPE type;
	word(string U_name="$")
	{
		name=U_name;
		type.reset();
	}
	~word()
	{

	}
}word_buf;
class word_io
{
public:
	char name_io[word_size];
	WORD_TYPE type;
	unsigned int rating,usage;
	void reset()
	{
		for(unsigned int i=0;i<word_size;i++)
		{
			name_io[i]=0;
		}
		type.reset();
		rating=50;
		usage=0;
	}
	word_io()
	{
		reset();
	}
	word_io(word U)
	{
		reset();
		if(U.name.size())
			strcpy(name_io,U.name.c_str());
		type=U.type;
		rating=U.rating;
		usage=U.usage;
	}
};
void ExtractWord(word &ret,word_io U)
{
	ret.name.assign(U.name_io);
	ret.type=U.type;
	ret.rating=U.rating;
	ret.usage=U.usage;
}

#endif /* WORD_H_ */
