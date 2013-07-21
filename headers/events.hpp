/*
 * events.hpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Reuben
 */

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include <headers/global_assets.hpp>

void handleevents()
{
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

#endif /* EVENTS_HPP_ */
