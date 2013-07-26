/*
 * stats.h
 *
 *  Created on: Jul 25, 2013
 *      Author: Reuben
 */

#ifndef stats_H_
#define stats_H_

#include <fstream>

using namespace std;

struct stats
{
	short unsigned int rating;
	unsigned int usage;
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

#endif /* stats_H_ */
