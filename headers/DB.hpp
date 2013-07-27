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

using namespace std;

bool DB_corrupted=false;


class DB_info
{
	string version;
	string location;
	string list_extension;
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
	void set(string U_location,string U_version,string U_list_extension,string U_data_extension)
	{
		list_file=(U_location+"/v"+U_version+"."+U_list_extension);
		data_file=(U_location+"/v"+U_version+"."+U_data_extension);
	}
	DB_info(string U_location,string U_version,string U_list_extension,string U_data_extension)
	{
		set(U_location,U_version,U_list_extension,U_data_extension);
	}
}wordDB("databases","1","wordlist","worddat");

struct SearchResults
{
	short int  match_id;
	unsigned int loc;
	SearchResults reset()
	{
		match_id=0;loc=0;
		return *this;
	}
	SearchResults operator=(SearchResults U)
	{
		match_id=U.match_id;
		loc=U.loc;
		return *this;
	}
};
struct WordResults
{
	SearchResults name,type,rating,usage;
	unsigned int start,end;
	unsigned int size()
	{
		return end-start;
	}
	void reset()
	{
		name=type=rating=usage.reset();
		start=end=0;
	}
}WordResult;

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
WordResults* searchword(word &U)
{
	word_io io;
	ifstream data(wordDB.datafile(),ios::binary);

	while(data.read((char*)&io,sizeof(io)))
	{

		word extracted=ExtractWord(io);

		if(strcmpi(extracted.name.c_str(),U.name.c_str())==0)
		{
			U=ExtractWord(io);
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

#endif /* DB_H_ */
