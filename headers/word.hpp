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

#include <headers/DB.hpp>

using namespace std;

class word:public stats
{
	string name,type;
public:
	string getname()
	{
		return name;
	}
	string set_name(string U_name)
	{
		return name=U_name;
	}
	string set_type(string U_type)
	{
		return type=U_type;
	}
	word(string U_name="NULL")
	{
		if(strcmp(U_name.c_str(),"NULL"))
			name=U_name;
		else name="";
		type="";
	}
	~word()
	{

	}
};

word findword(string search)
{
	word temp;
	ifstream fin("databases/words.dat",ios::binary);
	int found=0;
	while(fin.read((char*)&temp,sizeof temp)&&!found)
	{
		if(strcmpi(temp.getname().c_str(),search.c_str())==0)
		{
			found=1;
		}
	}
	fin.close();
	return temp;
}
#endif /* WORD_H_ */
