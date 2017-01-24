/*
 * Object.h
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Global.h"


class Object {
public:
	// public class functions
	Object();
	virtual ~Object();
	virtual void update() = 0;
	SDL_Rect get_rect();
	std::vector< SDL_Rect > get_render_queue();

	// class variables

	int x_position, y_position;
	int sprite_frame;
	std::vector<int> associated_sprite_queues[];



};

#endif /* OBJECT_H_ */
