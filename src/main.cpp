/*
 * main.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#include <headers/aria.hpp>

int main (int argc, char* args[])
{
	ARIA aria(1080,720);
	while(!ended)
	{
		handleevents();
	}
	return 0;
}

