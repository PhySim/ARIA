/*
 * framer.hpp
 *
 *  Created on: Jul 15, 2013
 *      Author: Reuben
 */

#ifndef FRAMER_HPP_
#define FRAMER_HPP_

class timer
{
	unsigned long int start_time,cummulative_ticks;
	bool current_state;//0 means stopped, 1 means running
public:
	timer()
	{
		reset();
	}
	void reset()
	{
		cummulative_ticks=0;
		current_state=0;
	}
	void start()
	{
		if(current_state==0)//if it is not running already
		{
			start_time=SDL_GetTicks();
			current_state=1;
		}
	}
	void stop()
	{
		cummulative_ticks+=SDL_GetTicks()-start_time;
		current_state=0;
	}
	unsigned long int elapse()
	{
		if(current_state==0)
			return cummulative_ticks;
		else
			return cummulative_ticks + (SDL_GetTicks()-start_time);
	}
};

class framer : protected timer
{
	unsigned long int count;
	float minfps,maxfps,current_fps;
	float minfreq,maxfreq,currentfreq;
public:
	framer(double user_minfps=10,double user_maxfps=32)
	{
		minfps=user_minfps;
		maxfps=user_maxfps;
		current_fps=(minfps+maxfps)/2;

		minfreq=1/maxfps;
		maxfreq=1/minfps;
		currentfreq=1/current_fps;
		count=0;
	}
	void updatefpslimits(double user_minfps=10,double user_maxfps=30)
	{
		minfps=user_minfps;
		maxfps=user_maxfps;
		current_fps=(minfps+maxfps)/2;

		minfreq=1/maxfps;
		maxfreq=1/minfps;
		currentfreq=1/current_fps;
	}
	void newframe()
	{
	}
	void endframe()
	{
		currentfreq=elapse()/1000.0;
		current_fps=1/currentfreq;
		reset();
		start();
		count++;
	}
	unsigned long int currentframe()
	{
		return count;
	}
	float currentfrequency()
	{
		return currentfreq;
	}
	float currentfps()
	{
		return current_fps;
	}
	float remainingfreetime()
	{
		if(elapse()/1000.0<minfreq)
			return double(minfreq)-double(elapse()/1000.0);
		else return 0;
	}
	float elapsed()
	{
		return (float)elapse();
	}
	float deltatime()
	{
		if(currentfreq>maxfreq)
			return maxfreq;
		else if(currentfreq<minfreq)
			return minfreq;
		else
			return currentfreq;
	}
};

#endif /* FRAMER_HPP_ */
