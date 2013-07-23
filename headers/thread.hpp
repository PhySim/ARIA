/*
 * thread.hpp
 *
 *  Created on: Jul 23, 2013
 *      Author: Reuben
 */

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <SDL/SDL.h>
#include <headers/mutex.hpp>


class ThreadData
{
public:
    ThreadData()
        :
            dataready( false ),
            done( false )
    {
        condition = SDL_CreateCond();
    }

    ~ThreadData()
    {
        SDL_DestroyCond( condition );
    }

    bool dataready;
    bool done;
    sdlmutex mutex;
    SDL_cond* condition;
};


#endif /* THREAD_HPP_ */
