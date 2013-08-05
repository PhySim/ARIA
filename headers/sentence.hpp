/*
 * sentence_struc.hpp
 *
 *  Created on: Jul 28, 2013
 *      Author: Reuben
 */

#ifndef SENTENCE_STRUC_HPP_
#define SENTENCE_STRUC_HPP_

#include <string>
#include <vector>

#include <headers/stats.hpp>
#include <headers/word.hpp>

using namespace std;

const unsigned int sentence_size=32;


class sentence:public stats
{
public:
	vector<string> words;
	string all;
	void reset()
	{
		if(words.size())
			words.clear();
		rating=50;
		usage=0;
	}
	void set(const char* U)
	{
		reset();
		all.assign(U);
		string a;
		for(int i=0;U[i];i++)
		{
			if(U[i]!=' ')
			{
				a.push_back(U[i]);
			}
			else
			{
				if(a.size())
				{
					words.push_back(a.c_str());
				}
				a.clear();
			}
			if(U[i+1]=='\0'&&a.size())
			{
				words.push_back(a.c_str());
			}
		}
	}
	bool process();
	sentence()
	{
		reset();
	}
};
class sentence_io
{
public:
	char words_io[sentence_size][word_size];
	char all[sentence_size*word_size];
	unsigned int rating,usage;

	void reset()
	{
		rating=50;
		usage=0;
		for(unsigned int i=0;i<sentence_size;i++)
			for(unsigned int j=0;j<word_size;j++)
			{
				words_io[i][j]=all[i*word_size+j]=0;
			}
	}

	sentence_io(sentence &U)
	{
		reset();
		for(unsigned int i=0;i<sentence_size&&i<U.words.size();i++)
		{
			if(U.words.size())
				strcpy(words_io[i],U.words[i].c_str());
		}
		if(U.all.size())
		{
			strcpy(all,U.all.c_str());
		}
		rating=U.rating;
		usage=U.usage;
	}
};
class sentence_struc:public stats
{
public:
	unsigned int size;
	WORD_TYPE struc[sentence_size];
	void reset()
	{
		size=0;
		for(unsigned int i=0;i<sentence_size;i++)
		{
			struc[i].reset();
		}
	}
	sentence_struc()
	{
		reset();
	}
	sentence_struc(sentence U);

};
sentence ExtractSentence(sentence_io U)
{
	sentence* sentence_buf=new sentence;
	for(unsigned int i=0;U.words_io[i][0];i++)
	{
		string a;
		a.assign(U.words_io[i]);
		sentence_buf->words.push_back(a);
	}
	sentence_buf->all.assign(U.all);
	sentence_buf->rating=U.rating;
	sentence_buf->usage=U.usage;
	return *sentence_buf;
}

#endif /* SENTENCE_STRUC_HPP_ */
