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
	string name,type;
public:
	string getname()
	{
		return name;
	}
	string gettype()
	{
		return type;
	}
	string set_name(string U_name)
	{
		return name=U_name;
	}
	string set_type(string U_type)
	{
		return type=U_type;
	}
	word(string U_name="$")
	{
		name=U_name;
		type="";
	}
	~word()
	{

	}
	wordchecklist checklist(wordchecklist &U)
	{
		U.name=(name.size()+1);
		U.type=(type.size()+1);
		U.stats=sizeof(stats);
		return U;
	}
};
#endif /* WORD_H_ */
