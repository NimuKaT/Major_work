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
	void set_position(int x, int y);
	void set_size(int width, int height);
	bool detect_collision(HitBox* test_object_ptr);

protected:
	int x_, y_ = 0;
	int width_, height_ = 0;

protected:


};



class Object {
public:
	Object();
	virtual ~Object();
	virtual void update() = 0;
	SDL_Rect get_rect();
	std::vector<SDL_Rect> get_render_queue();

protected:
	float true_x_position_, true_y_position_ = 0.0;
	int x_position_, y_position_ = 0.;
	int sprite_frame_ = 0;
	std::vector<int> associated_sprite_queues_;



};

class Player : public Object{
public:
	Player();
	~Player();
	void update();
	void get_movement(int x, int y);

private:
	bool input_states[5];

};

#endif /* OBJECT_H_ */
