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
#include <headers/sentence_struc.hpp>

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
}wordDB("databases","2","worddat"),sentence_strucDB("databases","1","sen_strucdat");

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
struct Sentence_strucResults
{
	sentence_struc* loc;
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
}Sentence_strucResult;

void writeword(word &U)
{
	word_io io(U);

	ofstream data(wordDB.datafile(),ios::app|ios::binary);

	data.write((char*)&io,sizeof(io));

	data.close();
}
void readword(word &U)
{
	word_io word_io_buf;
	ifstream data(wordDB.datafile(),ios::binary);

	data.read((char*)&word_io_buf,sizeof(word_io_buf));

	U=ExtractWord(word_io_buf);

	data.close();
}
WordResults* searchword(word U)
{
	word_io io;
	ifstream data(wordDB.datafile(),ios::binary);

	while(data.read((char*)&io,sizeof(io)))
	{

		word extracted=ExtractWord(io);

		if(strcmpi(extracted.name.c_str(),U.name.c_str())==0)
		{
			WordResult.loc=new word(extracted);
			WordResult.name.match_id=1;
			if(strcmp(extracted.name.c_str(),U.name.c_str())==0)
				{
					WordResult.name.match_id=2;
				}
		}
		if(strcmpi(extracted.type.c_str(),U.type.c_str())==0)
		{
			WordResult.type.match_id=1;
			if(strcmp(extracted.type.c_str(),U.type.c_str())==0)
				{
					WordResult.type.match_id=2;
				}
		}
		if(extracted.rating==U.rating)
		{
			WordResult.rating.match_id=1;
		}
		if(extracted.usage==U.usage)
		{
			WordResult.usage.match_id=1;
		}
	}
	data.close();
	return &WordResult;
}

void writesentence_struc(sentence_struc &U)
{
	sentence_struc_io io(U);
	ofstream data(sentence_strucDB.datafile(),ios::app|ios::binary);

	data.write((char*)&io,sizeof(io));

	data.close();
}
void readsentence_struc(sentence_struc &U)
{
	sentence_struc_io io(U);
	ifstream data(sentence_strucDB.datafile(),ios::app|ios::binary);

	data.read((char*)&io,sizeof(io));

	U=ExtractSentence_struc(io);
	data.close();
}
Sentence_strucResults* searchsentence_struc(sentence_struc U)
{
	sentence_struc_io io(U);
	ifstream data(wordDB.datafile(),ios::binary);

	while(data.read((char*)&io,sizeof(io)))
	{

		sentence_struc extracted=ExtractSentence_struc(io);

		if(strcmpi(extracted.all.c_str(),U.all.c_str()))
		{
			Sentence_strucResult.all.match_id=1;
			Sentence_strucResult.loc=new sentence_struc(extracted);
			if(strcmp(extracted.all.c_str(),U.all.c_str())==0)
			{
				Sentence_strucResult.all.match_id=2;
			}
		}

		if(extracted.rating==U.rating)
		{
			WordResult.rating.match_id=1;
		}
		if(extracted.usage==U.usage)
		{
			WordResult.usage.match_id=1;
		}
	}
	data.close();
	return &Sentence_strucResult;
}
#endif /* DB_H_ */
