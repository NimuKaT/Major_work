/*
 * Timer.cpp
 *
 *  Created on: 22Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Timer.h"

Timer::Timer() {
	is_paused = false;
	is_started = false;
	init_time = 0;
	passed_time = 0;

}

inline Timer::~Timer(){};

void Timer::start(){
	if( !is_paused ){
		init_time = SDL_GetTicks();
		is_started = true;
	}
	else{
		init_time = SDL_GetTicks() - passed_time;
		is_paused = false;
		passed_time = 0;
	}
}

void Timer::stop(){
	if( is_started ){
		init_time = 0;
		is_started = false;
	}
}

Uint32 Timer::get_time_elapsed(){
	Uint32 time_elapsed = init_time - SDL_GetTicks();
	return time_elapsed;
}

void Timer::pause(){
	if( !is_paused && is_started ){
		passed_time = SDL_GetTicks() - init_time;
		is_paused = true;
		init_time = 0;
	}
}

void Timer::reset(){
	stop();
	start();
}

bool Timer::is_passed(Uint32 duration){
	bool is_time_passed = false;
	if( !is_paused && is_started ){
		if ( init_time - SDL_GetTicks() >= duration ){
			is_time_passed = true;
		}
	}
	return is_time_passed;
};