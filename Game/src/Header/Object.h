/*
 * Object.h
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Global.h"

class HitBox {
public:
	HitBox();
	void set_position(int, int);
	void set_size(int, int);
	bool detect_collision(HitBox*);

protected:
	int x_,y_ = 0;
	int width_,height_ = 0;

protected:


};



class Object {
public:
	// public class functions
	Object();
	virtual ~Object();
	virtual void update() = 0;
	SDL_Rect get_rect();
	std::vector< SDL_Rect > get_render_queue();

protected:
	// class variables

	float true_x_position, true_y_position;
	int x_position, y_position;
	int sprite_frame;
	std::vector<int> associated_sprite_queues;



};

class Player : public Object{
public:
	Player();
	~Player();
	void update();
	void get_movement( int, int );

private:
	bool input_states[5];

};

#endif /* OBJECT_H_ */
