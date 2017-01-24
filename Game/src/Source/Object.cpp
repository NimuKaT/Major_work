/*
 * Object.cpp
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Object.h"

Object::Object() {
	// TODO Auto-generated constructor stub
	x_position = 0;
	y_position = 0;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

SDL_Rect Object::get_rect(){
	SDL_Rect object_position = { x_position, y_position, 0, 0 };
	return object_position;
}
