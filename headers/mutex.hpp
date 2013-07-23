/*
 * mutex.hpp
 *
 *  Created on: Jul 23, 2013
 *      Author: Reuben
 */

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include <SDL/SDL.h>
#include <iostream>
#include <stdexcept>


#define access scopedlock lock

using namespace std;

class sdlmutex
{
public:
	sdlmutex()
    {
        mutex = SDL_CreateMutex();
        if ( !mutex ) throw runtime_error( "SDL_CreateMutex == NULL" );
    }

    ~sdlmutex()
    {
        SDL_DestroyMutex( mutex );
    }

    void lock()
    {
        if( SDL_mutexP( mutex ) == -1 ) throw runtime_error( "SDL_mutexP == -1" );
        //  Note:
        //      -1 does not mean it was already locked - it means there was an error in locking -
        //      if it was locked it will just block - see SDL_mutexP(3)
    }

    void unlock()
    {
        if ( SDL_mutexV( mutex ) == -1 ) throw runtime_error( "SDL_mutexV == -1" );
    }

    SDL_mutex* underlying()
    {
        return mutex;
    }
private:
    SDL_mutex* mutex;
};
class scopedlock
{
public:
    scopedlock( sdlmutex& mutex )
        :
            mutex( mutex )
    {
        mutex.lock();
    }
    ~scopedlock()
    {
        try
        {
            this->unlock();
        }
        catch( const exception& e )
        {
            // Destructors should never throw ...
            cerr << "scopedlock::~scopedlock - caught : " << e.what() << endl;
        }
    }
    void unlock()
    {
        mutex.unlock();
    }
private:
    sdlmutex& mutex;
};

#endif /* MUTEX_HPP_ */
