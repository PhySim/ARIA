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

void writeword(word U)
{
	wordchecklist check=U.checklist(check);

	ofstream list(wordDB.listfile(),ios::app);
	ofstream data(wordDB.datafile(),ios::app);

	list<< U.getname().size()<<" "<<U.gettype().size()<<"\n";
	data<<U.getname()<<"	"<<U.gettype()<<"	"<<U.rating<<"	"<<U.usage<<"\n";

	list.close();
	data.close();
}
WordResults readword(word &U,int x1,int x2)
{
	wordchecklist check;

	ifstream list(wordDB.listfile(),ios::app);
	ifstream data(wordDB.datafile(),ios::app);

	list.seekg(x2);
	WordResult.end=data.tellg();
	data.seekg(x1);
	list>>check.name>>check.type;
	string temp;
	data>>temp;U.set_name(temp);
	data>>temp;U.set_type(temp);
	data>>U.rating;
	data>>U.usage;
	WordResult.end=data.tellg();

	list.close();
	data.close();
	return WordResult;
}
WordResults findword(word &U)
{
	word temp;
	wordchecklist check;

	ifstream list(wordDB.listfile(),ios::binary);
	ifstream data(wordDB.datafile(),ios::binary);

	bool found=false;
	WordResult.reset();
	while(list>>check.name>>check.type&&!found)
	{
		string tmp;

		data>>tmp;
		temp.set_name(tmp);
		if(temp.getname().size()!=check.name)
			DB_corrupted=true;
		if(strcmpi(U.getname().c_str(),temp.getname().c_str())==0)
		{
			WordResult.name.match_id=1;
			WordResult.name.loc=data.tellg();
			if(U.getname()==temp.getname())
			{
				WordResult.name.match_id=2;
			}
		}

		data>>tmp;
		temp.set_type(tmp);
		if(temp.gettype().size()!=check.type)
			DB_corrupted=true;
		if(strcmpi(U.gettype().c_str(),temp.gettype().c_str())==0)
		{
			WordResult.type.match_id=1;
			if(U.gettype()==temp.gettype())
			{
				WordResult.type.match_id=2;
			}
		}
		unsigned int i;
		data>>i;
		if(U.rating==(short unsigned int)i)
		{
			WordResult.rating.match_id=2;
		}

		data>>i;
		if(U.usage==i)
		{
			WordResult.usage.match_id=2;
		}
	}

	list.close();
	data.close();
	if(found)
	{
		U=temp;
	}
	return WordResult;
}

#endif /* DB_H_ */
