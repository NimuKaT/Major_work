/*
 * Timer.cpp
 *
 *  Created on: 22Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Timer.h"

Timer::Timer() {
	is_paused_ = false;
	is_started_ = false;
	init_time_ = 0;
	passed_time_ = 0;
}

inline Timer::~Timer(){};

void Timer::start(){
	is_started_ = true;
	if (!is_started_){
		init_time_ = SDL_GetTicks();
	}
	else{
		init_time_ = SDL_GetTicks() - passed_time_;
		is_paused_ = false;
		passed_time_ = 0;
	}
}

void Timer::stop(){
	if (is_started_){
		init_time_ = 0;
		is_started_ = false;
		is_paused_ = false;
	}
}

Uint32 Timer::get_time_elapsed(){
	Uint32 time_elapsed = init_time_ - SDL_GetTicks();
	return time_elapsed;
}

void Timer::pause(){
	if (!is_paused_ && is_started_){
		passed_time_ = SDL_GetTicks() - init_time_;
		is_paused_ = true;
		init_time_ = 0;
	}
}

void Timer::reset(){
	stop();
	start();
}

bool Timer::is_passed(Uint32 duration){
	bool is_time_passed = false;
	if (!is_paused_ && is_started_){
		if (SDL_GetTicks() - init_time_ >= duration){
			is_time_passed = true;
		}
	}
	return is_time_passed;
};
