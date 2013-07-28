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


class sentence_struc:public stats
{
public:
	vector<string> struc;
	string all;
	void add_word(const char* U)
	{
		string a;
		a.assign(U);
		struc.push_back(a);
	}
	void set(const char* U)
	{
		struc.clear();
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
				struc.push_back(a.c_str());
				a.clear();
			}
			if(U[i+1]=='\0')
			{
				struc.push_back(a.c_str());
			}
		}
	}
};
class sentence_struc_io
{
public:
	char struc_io[sentence_size][word_size];
	char all[sentence_size*word_size];
	unsigned int rating,usage;

	void reset()
	{
		rating=50;
		usage=0;
		for(unsigned int i=0;i<sentence_size;i++)
			for(unsigned int j=0;j<word_size;j++)
			{
				struc_io[i][j]=all[i*word_size+j]=0;
			}
	}

	sentence_struc_io(sentence_struc &U)
	{
		reset();
		for(unsigned int i=0;i<sentence_size&&i<U.struc.size();i++)
		{
			if(U.struc.size())
				strcpy(struc_io[i],U.struc[i].c_str());
		}
		if(U.all.size())
		{
			strcpy(all,U.all.c_str());
		}
		rating=U.rating;
		usage=U.usage;
	}
};
sentence_struc ExtractSentence_struc(sentence_struc_io U)
{
	sentence_struc* sentence_struc_buf=new sentence_struc();
	for(unsigned int i=0;U.struc_io[i][0];i++)
	{
		string a;
		a.assign(U.struc_io[i]);
		sentence_struc_buf->struc.push_back(a);
	}
	sentence_struc_buf->all.assign(U.all);
	sentence_struc_buf->rating=U.rating;
	sentence_struc_buf->usage=U.usage;
	return *sentence_struc_buf;
}

#endif /* SENTENCE_STRUC_HPP_ */
