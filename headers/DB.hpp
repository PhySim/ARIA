/*
 * DB.h
 *
 *  Created on: Jul 25, 2013
 *      Author: Reuben
 */

#ifndef DB_H_
#define DB_H_

#include <fstream>
#include <string.h>

#include <headers/word.hpp>
#include <headers/sentence.hpp>

using namespace std;

bool DB_corrupted=false;


class DB_info
{
	string version;
	string location;
	string data_extension;
	string list_file;
	string data_file;
public:
	const char* listfile()
	{
		return list_file.c_str();
	}
	const char* datafile()
	{
		return data_file.c_str();
	}
	void set(string U_location,string U_version,string U_data_extension)
	{
		data_file=(U_location+"/v"+U_version+"."+U_data_extension);
	}
	DB_info(string U_location,string U_version,string U_data_extension)
	{
		set(U_location,U_version,U_data_extension);
	}
}wordDB("databases","3","worddat"),sentenceDB("databases","1","sendat"),sentence_strucDB("databases","1","strucdat");

struct SearchResults
{
	short int  match_id;
	SearchResults reset()
	{
		match_id=0;;
		return *this;
	}
	SearchResults()
	{
		reset();
	}
	SearchResults operator=(SearchResults U)
	{
		match_id=U.match_id;
		return *this;
	}
};
struct WordResults
{
	word* loc;
	SearchResults name,type,rating,usage;
}WordResult;
struct SentenceResults
{
	sentence* loc;
	SearchResults struc[sentence_size],all,rating,usage;
	void reset()
	{
		loc=NULL;
		all=rating=usage.reset();
		for(unsigned int i=0;i<sentence_size;i++)
		{
			struc[i].reset();
		}
	}
}SentenceResult;

void write(word &U)
{
	word_io io(U);

	ofstream data(wordDB.datafile(),ios::app|ios::binary);

	data.write((char*)&io,sizeof(io));

	data.close();
}
void read(word &U)
{
	word_io word_io_buf;
	ifstream data(wordDB.datafile(),ios::binary);

	data.read((char*)&word_io_buf,sizeof(word_io_buf));

	ExtractWord(U,word_io_buf);

	data.close();
}
bool searchword(const char* U,word &ret)
{
	bool found=false;
	word_io io;
	ifstream data(wordDB.datafile(),ios::binary);

	while(data.read((char*)&io,sizeof(io)))
	{

		word extracted;
		ExtractWord(extracted,io);

		if(strcmpi(extracted.name.c_str(),U)==0)
		{
			ret=extracted;
			found=1;
			if(strcmp(extracted.name.c_str(),U)==0)
			{
				found=2;
			}
		}
	}
	data.close();
	return found;
}

void write(sentence &U)
{
	sentence_io io(U);
	ofstream data(sentenceDB.datafile(),ios::app|ios::binary);

	data.write((char*)&io,sizeof(io));

	data.close();
}
void read(sentence &U)
{
	sentence_io io(U);
	ifstream data(sentenceDB.datafile(),ios::binary);

	data.read((char*)&io,sizeof(io));

	U=ExtractSentence(io);
	data.close();
}
SentenceResults* searchsentence(sentence &U)
{
	SentenceResult.reset();
	sentence_io io(U);
	ifstream data(sentenceDB.datafile(),ios::binary);

	while(data.read((char*)&io,sizeof(io)))
	{
		sentence extracted=ExtractSentence(io);

		if(strcmpi(extracted.all.c_str(),U.all.c_str())==0)
		{
			SentenceResult.all.match_id=1;
			SentenceResult.loc=new sentence(extracted);
			if(strcmp(extracted.all.c_str(),U.all.c_str())==0)
			{
				SentenceResult.all.match_id=2;
			}
			if(extracted.rating==U.rating)
			{
				SentenceResult.rating.match_id=1;
			}
			if(extracted.usage==U.usage)
			{
				SentenceResult.usage.match_id=1;
			}
		}
	}
	data.close();
	return &SentenceResult;
}
sentence_struc::sentence_struc(sentence U)
{
	reset();
	if(U.words.size())
	{
		for(unsigned int i=0;i<U.words.size();i++)
		{
			word temp;
			if(searchword(U.words[i].c_str(),temp))
			{
				struc[i]=(temp.type);
				size++;
			}
		}
	}
}

void write(sentence_struc &U)
{
	ofstream data(sentence_strucDB.datafile(),ios::app|ios::binary);
	data.write((char*)&U,sizeof(U));
	data.close();
}
void read(sentence_struc &U)
{
	ofstream data(sentence_strucDB.datafile(),ios::binary);
	data.write((char*)&U,sizeof(U));
	data.close();
}
#endif /* DB_H_ */
