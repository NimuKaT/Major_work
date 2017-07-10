/*
 * Object.cpp
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Object.h"

HitBox::HitBox(){
	x_ = 0;
	y_ = 0;
	width_ = 0;
	height_ = 0;
}

void HitBox::set_position(int x, int y){
	x_ = x;
	y_ = y;
}

void HitBox::set_size(int width, int height){
	width_ = width;
	height_ = height;
}

bool HitBox::detect_collision(HitBox* test_object_ptr){
	bool is_hit = false;

	if (x_ > test_object_ptr->x_ + test_object_ptr->width_ && x_ + width_ > test_object_ptr->x_){
		if(y_ > test_object_ptr->y_ + test_object_ptr->height_ && y_ + height_ > test_object_ptr->y_){
			is_hit = true;
		}
	}
	return is_hit;
}


Object::Object() {
	true_x_position_ = 0.0;
	true_y_position_ = 0.0;
	x_position_ = 0;
	y_position_ = 0;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

SDL_Rect Object::get_rect(){
	SDL_Rect object_position = {x_position_, y_position_, 0, 0};
	return object_position;
}


Player::Player(){

}

Player::~Player(){

}

void Player::update(){

}

void Player::get_movement(int x, int y){

}
