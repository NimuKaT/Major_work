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
	vel_x_ = 0;
	vel_y_ = 0;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}
void Object::update(){
	vel_x_ = 0;
	vel_y_ = 0;
}
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

/*
 * 			PLAYER OBJECT
 */
Player::Player(){
	width_ = 100;
	height_ = 100;
	gun_cooldown_ticks_ = 0;
	can_shoot_ = true;
}

Player::~Player(){

}

void Player::update(){
	Object::update();
	if (!can_shoot_){
		gun_cooldown_ticks_--;
		if(!gun_cooldown_ticks_){
			can_shoot_ = true;
		}
	}
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

std::vector<std::shared_ptr<Bullet>> Player::shoot_gun(float true_angle){
	std::vector<std::shared_ptr<Bullet>> bullet_pellet;
	if (can_shoot_){
		gun_cooldown_ticks_ = 30;
		can_shoot_ = false;
		bullet_pellet.push_back(std::make_shared<Bullet>(x_+(width_/2), (y_+height_/2), cos(true_angle/180*PI)*10, -sin(true_angle/180*PI)*10));
	}
	return bullet_pellet;
}
/*
 * 			ENEMY OBJECT TEMPLATE CLASS
 */
Enemy::Enemy(){

}
Enemy::~Enemy(){

}
void Enemy::update(){

}
std::tuple<int, int, TEXTURE_ID, int> Enemy::get_queue(){

}
/*
 * 			Bullet Class
 */
Bullet::Bullet(int initial_x, int initial_y, int vel_x, int vel_y){
	width_ = 50;
	height_ = 50;
	x_ = initial_x;
	y_ = initial_y;
	vel_x_ = vel_x;
	vel_y_ = vel_y;
	true_angle = atan2(-vel_y_, vel_x_) / PI * 180;
}
Bullet::~Bullet(){

}
void Bullet::update(){
	x_ += vel_x_;
	y_ += vel_y_;
}

std::tuple<int, int, TEXTURE_ID, int> Bullet::get_queue(){
	return std::make_tuple(x_, y_, BULLET, 0);
}

/*
 * 			WALL OBJECT
 */
Wall::Wall(){

}

Wall::~Wall(){

}

std::tuple<int, int, TEXTURE_ID, int> Wall::get_queue(){
	return std::make_tuple(x_, y_, PLAYER, 0);
}








