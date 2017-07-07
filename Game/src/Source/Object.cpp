/*
 * Object.cpp
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Object.h"

HitBox::HitBox(){
};

void HitBox::set_position(int new_x, int new_y){
	x_ = new_x;
	y_ = new_y;
}

void HitBox::set_size(int new_width, int new_height){
	width_ = new_width;
	height_ = new_height;
}

bool HitBox::detect_collision(HitBox* test_object){
	bool is_hit = false;
	if (x_ > test_object->x_ + test_object->width_ && x_ + width_ > test_object->x_){
		if(y_ > test_object->y_ + test_object->height_ && y_ + height_ > test_object->y_){
			is_hit = true;
		}
	}
	return is_hit;
}


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


Player::Player(){

}

Player::~Player(){

}

void Player::update(){

}

void Player::get_movement( int x, int y){

}
