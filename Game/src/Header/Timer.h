/*
 * Timer.h
 *
 *  Created on: 22Jan.,2017
 *      Author: ImuKaT
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "SDL2/SDL.h"

class Timer {
public:
	Timer();
	virtual ~Timer();
	void start();
	void stop();
	void pause();
	void reset();
	Uint32 get_time_elapsed();
	bool is_passed(Uint32);


private:
	Uint32 init_time;
	Uint32 passed_time;
	bool is_started;
	bool is_paused;
};

#endif /* TIMER_H_ */
