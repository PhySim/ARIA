/*
 * threads.hpp
 *
 *  Created on: Jul 21, 2013
 *      Author: Reuben
 */

#ifndef THREADS_HPP_
#define THREADS_HPP_

#include <headers/aria.hpp>
#include <fstream>

using namespace std;

int eventhandler(void* data)
{
	ofstream fout("temp.txt",ios::app);
	fout<<"threading";
	fout.close();
	while(!ended)
	{
		ofstream fout("temp.txt",ios::app);
			fout<<"threading"<<'\n';
			fout.close();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				ended=true;
			break;
			}
			SDL_Delay(100);
		}
	}
	return 0;
}


#endif /* THREADS_HPP_ */
