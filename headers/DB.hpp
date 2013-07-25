/*
 * DB.h
 *
 *  Created on: Jul 25, 2013
 *      Author: Reuben
 */

#ifndef DB_H_
#define DB_H_

#include <fstream>

using namespace std;

class stats
{
	short unsigned int rating;
	unsigned int usage;
public:
	stats()
	{
		rating=5;
		usage=0;
	}
	int accessed()
	{
		return ++usage;
	}
};

#endif /* DB_H_ */
