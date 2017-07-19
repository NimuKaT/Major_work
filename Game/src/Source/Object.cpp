/*
 * Object.cpp
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Object.h"

HitBox::HitBox(){
std::cout<<"copy "<<std::endl;
	true_x_ = 0;
	true_y_ = 0;
	x_ = 0;
	y_ = 0;
	width_ = 0;
	height_ = 0;
}
HitBox::HitBox(SDL_Rect rect){
//	std::cout<<"x: "<<rect.x<<"\ny: "<<rect.y<<"\nwidth: "<<rect.w<<"\nheight: "<<rect.h<<std::endl;
		true_x_ = rect.x;
		true_y_ = rect.y;
		x_ = rect.x;
		y_ = rect.y;
		width_ = rect.w;
		height_ = rect.h;
}

HitBox::HitBox(int x, int y, int width, int height){
//	std::cout<<"x: "<<x<<"\ny: "<<y<<"\nwidth: "<<width<<"\nheight: "<<height<<std::endl;
	true_x_ = x;
	true_y_ = y;
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
}

void HitBox::set_position(int x, int y){
	x_ = x;
	y_ = y;
}

void HitBox::set_size(int width, int height){
	width_ = width;
	height_ = height;
}

bool HitBox::detect_collision(HitBox& test_object_ref){
	bool is_hit = false;
	if (x_ < test_object_ref.x_ + test_object_ref.width_ && x_ + width_ > test_object_ref.x_){
		if(y_ < test_object_ref.y_ + test_object_ref.height_ && y_ + height_ > test_object_ref.y_){
			is_hit = true;
//			std::cout<<"hit"<<std::endl;
		}
	}
	return is_hit;
}

/*
			OBJECT TEMPLATE CLASS
*/
Object::Object() {
	object_rect_ = {0, 0, 0, 0};
	centre_point_ = {0, 0};
	current_sprites_ = 0;
	current_frame_ = 0;
}

HitBox& Object::get_hitbox(){
	return hit_boxes[current_sprites_][current_frame_];
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

SDL_Point Object::get_centre(){
	return {object_rect_.x + (object_rect_.w/2), object_rect_.y + (object_rect_.h/2)};
}

/*
 * 			MovableObject Template class
 */
MoveableObject::MoveableObject(){

}
MoveableObject::~MoveableObject(){

}
void MoveableObject::update(){
	vel_x_ = 0;
	vel_y_ = 0;
}

/*
 * 			Entity Template class
 */
Entity::Entity(){

}
Entity::~Entity(){

}
void Entity::bounce_object(HitBox& test_object_ref){
	HitBox* hitbox_ptr = &hit_boxes[current_sprites_][current_frame_];
	int new_x = object_rect_.x; int new_y = object_rect_.y;
	if (new_x >= test_object_ref.x_ + test_object_ref.width_ + vel_x_ &&
			new_x <= test_object_ref.x_ + test_object_ref.width_ &&
			vel_x_ < 0){
		new_x = test_object_ref.x_ + test_object_ref.width_;
	}
	else if (new_x + object_rect_.w >= test_object_ref.x_ &&
			new_x + object_rect_.w <= test_object_ref.x_ + vel_x_ &&
			vel_x_ > 0){
		new_x = test_object_ref.x_ - object_rect_.w;
	}
	if (new_y >= test_object_ref.y_ + test_object_ref.height_ + vel_y_ &&
			new_y <= test_object_ref.y_ + test_object_ref.height_ &&
				vel_y_ < 0){
		new_y = test_object_ref.y_ + test_object_ref.height_;
	}
	else if (new_y + object_rect_.h >= test_object_ref.y_ &&
			new_y + object_rect_.h <= test_object_ref.y_ + vel_y_ &&
			vel_y_ > 0){
		new_y = test_object_ref.y_ - object_rect_.h;

	}
	object_rect_.x = new_x;
	object_rect_.y = new_y;
	true_x_ = object_rect_.x;
	true_y_ = object_rect_.y;
	centre_point_.x = object_rect_.x + (object_rect_.w/2);
	centre_point_.y = object_rect_.y + (object_rect_.h/2);
	vel_x_ = 0;
	vel_y_ = 0;
	hit_boxes[current_frame_][current_frame_].set_position(object_rect_.x, object_rect_.y);
}

/*
 * 			BULLET CLASS
 */
Bullet::Bullet(int initial_x, int initial_y, int vel_x, int vel_y){
	object_rect_.w = 50;
	object_rect_.h = 50;
	object_rect_.x = initial_x;
	object_rect_.y = initial_y;
	vel_x_ = vel_x;
	vel_y_ = vel_y;
	SDL_angle_ = atan2(vel_y_, vel_x_) / PI * 180;

	hit_boxes.resize(1);
	hit_boxes.push_back(std::vector<HitBox>());
	hit_boxes[0].push_back(HitBox(object_rect_));
}
Bullet::~Bullet(){

}
void Bullet::update(){
	object_rect_.x += vel_x_;
	object_rect_.y += vel_y_;
	centre_point_.x = object_rect_.x + (object_rect_.w/2);
	centre_point_.y = object_rect_.y + (object_rect_.h/2);
	hit_boxes[current_sprites_][current_frame_].set_position(object_rect_.x, object_rect_.y);
}

std::tuple<int, int, TEXTURE_ID, int> Bullet::get_queue(){
	return std::make_tuple(object_rect_.x, object_rect_.y, BULLET, 0);
}

/*
 * 			PLAYER OBJECT
 */
Player::Player(SDL_Point spawn_point){
	centre_point_ = spawn_point;
	object_rect_.w = 100;
	object_rect_.h = 100;
	object_rect_.x = centre_point_.x - (object_rect_.w/2);
	object_rect_.y = centre_point_.y - (object_rect_.h/2);
	true_x_ = object_rect_.x;
	true_y_ = object_rect_.y;

	SDL_angle_ = 0.0;
	gun_cooldown_ticks_ = 0;
	can_shoot_ = true;


	hit_boxes.resize(1);
	hit_boxes.push_back(std::vector<HitBox>());
	hit_boxes[0].push_back(HitBox(0, 0, object_rect_.w, object_rect_.h));


	current_weapon = std::unique_ptr<Weapon>(new Pistol());
}

Player::~Player(){

}

void Player::update(){
//	MoveableObject::update();
	if (!can_shoot_){
		gun_cooldown_ticks_--;
		if(!gun_cooldown_ticks_){
			can_shoot_ = true;
		}
	}
	current_weapon->add_tick();
}

void Player::get_movement(int x, int y){
	true_x_ += x;
	true_y_ += y;
	object_rect_.x = round(true_x_);
	object_rect_.y = round(true_y_);
	centre_point_.x = object_rect_.x + (object_rect_.w/2);
	centre_point_.y = object_rect_.y + (object_rect_.h/2);
	hit_boxes[current_frame_][current_frame_].set_position(object_rect_.x, object_rect_.y);
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
	return std::make_tuple(object_rect_.x, object_rect_.y, TEST_BALL, BALL_GREEN);
}

std::vector<std::shared_ptr<Bullet>> Player::shoot_gun(float true_angle){
	std::vector<std::shared_ptr<Bullet>> bullet_pellet;
	if (current_weapon->shoot_weapon()){
		bullet_pellet = current_weapon->get_bullet_shot(centre_point_, -true_angle);
//		gun_cooldown_ticks_ = 30;
//		can_shoot_ = false;
//		bullet_pellet.push_back(std::make_shared<Bullet>(object_rect_.x+(object_rect_.w/2),
//				(object_rect_.y+object_rect_.h/2),
//				cos(true_angle/180*PI)*10, -sin(true_angle/180*PI)*10));
	}
	return bullet_pellet;
}
void Player::reload(){
	current_weapon->reload_weapon();
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

/*
 * 			ENEMY TYPE SENTRY CLASS
 */
EnemySentry::EnemySentry(SDL_Point spawn_point){
	centre_point_ = spawn_point;
	object_rect_.w = 100;
	object_rect_.h = 100;
	object_rect_.x = centre_point_.x - (object_rect_.w/2);
	object_rect_.y = centre_point_.y - (object_rect_.h/2);
	SDL_angle_ = 0.0;

	hit_boxes.resize(1);
	hit_boxes.push_back(std::vector<HitBox>());
	hit_boxes[0].push_back(HitBox(0, 0, object_rect_.w, object_rect_.h));
}
EnemySentry::~EnemySentry(){

}

void EnemySentry::update(){

}
std::tuple<int, int, TEXTURE_ID, int> EnemySentry::get_queue(){

}
std::vector<std::shared_ptr<Bullet>> EnemySentry::shoot_gun(float true_angle){

}

/*
 * 			WALL OBJECT
 */
Wall::Wall(int x, int y, Uint32 width, Uint32 height){
	object_rect_ = {x, y, width, height};
	hit_boxes.resize(1);
	hit_boxes.push_back(std::vector<HitBox>());
	hit_boxes[0].push_back(HitBox(x, y, width, height));
}

Wall::~Wall(){

}

std::tuple<int, int, TEXTURE_ID, int> Wall::get_queue(){
	return std::make_tuple(object_rect_.x, object_rect_.y, PLAYER, 0);
}




