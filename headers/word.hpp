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

struct wordchecklist
{
	unsigned int name,type,stats;
};

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
	char name_io[64],type_io[64];
	unsigned int rating,usage;
	word_io()
	{
		for(int i=0;i<64;i++)
		{
			name_io[i]=type_io[i]=0;
		}
		rating=0;
		usage=0;
	}
	word_io(word U)
	{
		for(int i=0;i<64;i++)
		{
			name_io[i]=type_io[i]=0;
		}
		strcpy(name_io,U.name.c_str());
		strcpy(type_io,U.type.c_str());
		rating=usage=49;
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
