/*
 * Object.cpp
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Object.h"

HitBox::HitBox(){
	true_x_ = 0;
	true_y_ = 0;
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

bool HitBox::detect_collision(HitBox &test_object_ref){
	bool is_hit = false;

	if (x_ < test_object_ref.x_ + test_object_ref.width_ && x_ + width_ > test_object_ref.x_){
		if(y_ < test_object_ref.y_ + test_object_ref.height_ && y_ + height_ > test_object_ref.y_){
			is_hit = true;
		}
	}
	return is_hit;
}

/*
		OBJECT TEMPLATE CLASS
*/
Object::Object() {
	true_x_ = 0.0;
	true_y_ = 0.0;
	x_ = 0;
	y_ = 0;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}
/*
		PLAYER OBJECT CLASS
*/

void Object::bounce_object(HitBox &test_object_ref){
	int new_x = x_; int new_y = y_;
	if (x_ >= test_object_ref.x_ + test_object_ref.width_ + vel_x_ &&
			x_ <= test_object_ref.x_ + test_object_ref.width_ &&
			vel_x_ < 0){
		new_x = test_object_ref.x_ + test_object_ref.width_;
	}
	else if (x_ + width_ >= test_object_ref.x_ &&
			x_ + width_ <= test_object_ref.x_ + vel_x_ &&
			vel_x_ > 0){
		new_x = test_object_ref.x_ - width_;
	}
	if (y_ >= test_object_ref.y_ + test_object_ref.height_ + vel_y_ &&
				y_ <= test_object_ref.y_ + test_object_ref.height_ &&
				vel_y_ < 0){
		new_y = test_object_ref.y_ + test_object_ref.height_;
	}
	else if (y_ + height_ >= test_object_ref.y_ &&
			y_ + height_ <= test_object_ref.y_ + vel_y_ &&
			vel_y_ > 0){
		new_y = test_object_ref.y_ - height_;

	}
	x_ = new_x;
	y_ = new_y;
	true_x_ = x_;
	true_y_ = y_;
	vel_x_ = 0;
	vel_y_ = 0;
}
Player::Player(){
	width_ = 100;
	height_ = 100;
}

Player::~Player(){

}

void Player::update(){
	vel_x_ = 0;
	vel_y_ = 0;

}

void Player::get_movement(int x, int y){
	true_x_ += x;
	true_y_ += y;
	x_ = round(true_x_);
	y_ = round(true_y_);
	if (x){
		vel_x_ = x;
	}
	if (y){
		vel_y_ = y;
	}
}

std::tuple<int, int, TEXTURE_ID, int> Player::get_queue(){
	vel_x_ = 0;
	vel_y_ = 0;
	return std::make_tuple(x_, y_, TEST_BALL, BALL_GREEN);
}

/*
 * 		WALL OBJECT
 */
Wall::Wall(){

}

Wall::~Wall(){

}

void Wall::update(){

}

std::tuple<int, int, TEXTURE_ID, int> Wall::get_queue(){
	return std::make_tuple(x_, y_, PLAYER, 0);
}








