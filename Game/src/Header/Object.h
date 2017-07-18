/*
 * Object.h
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Global.h"

class HitBox2 {
public:
	HitBox2();
	~HitBox2();
	void set_quad(SDL_Rect);
	void set_poly(SDL_Point**, Uint8);
	void set_angle(float new_angle);
	bool collision(HitBox2 &);

protected:
	bool is_poly_type;
	SDL_Point centre_point_;
	SDL_Point** poly_hitbox_points;
	SDL_Rect quad_hit_box;
	SDL_Point** transformed_hitbox_points;
	std::forward_list<std::tuple<float, float>> float_transformed_hitbox_points;
	float SDL_angle;
};


class HitBox {
public:
	HitBox();
	HitBox(SDL_Rect);
	HitBox(int x, int y, int width, int height);
	void set_position(int x, int y);
	void set_size(int width, int height);
	bool detect_collision(HitBox& test_object_ref);
	float true_x_, true_y_ = 0.0;
	int x_, y_ = 0.;
	int width_, height_ = 0;

};



class Object{
public:
	Object();
	virtual ~Object();
	HitBox& get_hitbox();
	SDL_Point get_centre();

protected:
	SDL_Rect object_rect_;
	SDL_Point centre_point_;
	Uint8 current_sprites_ = 0;
	Uint8 current_frame_ = 0;
	std::vector<std::vector<HitBox>> hit_boxes;
	std::vector<std::vector<std::tuple<int, int, TEXTURE_ID, int>>> associated_sprite_queues_;
};

class MoveableObject : public Object{
public:
	MoveableObject();
	~MoveableObject();
	virtual void update();
	virtual std::tuple<int, int, TEXTURE_ID, int> get_queue() = 0;

protected:
	float true_x_, true_y_;
	int vel_x_, vel_y_;
	float SDL_angle_; // Angle in
};

class Entity : public MoveableObject{
public:
	Entity();
	~Entity();
	virtual void update() = 0;
	virtual std::tuple<int, int, TEXTURE_ID, int> get_queue() = 0;
	void bounce_object(HitBox& test_object_ref);

};

class Bullet : public MoveableObject{
public:
	Bullet(int x, int y, int vel_x, int vel_y);
	~Bullet();
	void update();
	std::tuple<int, int, TEXTURE_ID, int> get_queue();

protected:
	int vel_x_ = 0;
	int vel_y_ = 0;
};

class Player : public Entity{
public:
	Player();
	~Player();
	void update();
	void get_movement(int x, int y);
	std::tuple<int, int, TEXTURE_ID, int> get_queue();
	std::vector<std::shared_ptr<Bullet>> shoot_gun(float true_angle);

private:
	Uint32 gun_cooldown_ticks_ = 0;
	bool can_shoot_ = true;
	bool input_states[5];

};

class Enemy : public Entity{
public:
	Enemy();
	~Enemy();
	void update();
	virtual std::tuple<int, int, TEXTURE_ID, int> get_queue() = 0;


};

class EnemySentry : Enemy{
public:

protected:

private:
};

class InteractableObject : public Object{
public:
	InteractableObject();
	~InteractableObject();
	void update();
	std::tuple<int, int, TEXTURE_ID, int> get_queue();
};

class Wall : public Object{
public:
	Wall(int x, int y, Uint32 width, Uint32 height);
	~Wall();
	std::tuple<int, int, TEXTURE_ID, int> get_queue();
};

#endif /* OBJECT_H_ */
