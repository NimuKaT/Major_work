/*
 * Object.h
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Global.h"
#include "Weapon.h"

class Weapon;
class MiniGun;

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
	float SDL_angle_; // Angle using SDL's grid system
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

class Entity : public MoveableObject{
public:
	Entity();
	~Entity();
	virtual void update() = 0;
	virtual std::tuple<int, int, TEXTURE_ID, int> get_queue() = 0;
	std::vector<std::shared_ptr<Bullet>> shoot_gun(float true_angle);
	void bounce_object(HitBox& test_object_ref);

};

class Player : public Entity{
public:
	Player(SDL_Point spwan_point);
	~Player();
	void update();
	void get_movement(int x, int y);
	std::tuple<int, int, TEXTURE_ID, int> get_queue();
	std::vector<std::shared_ptr<Bullet>> shoot_gun(float true_angle);
	void reload();
	int get_weapon_capacity();
	int get_current_ammo_count();
	float get_reload_percentage();

private:
	bool input_states[5];
	std::unique_ptr<Weapon> current_weapon;

};

class Enemy : public Entity{
public:
	Enemy();
	~Enemy();
	virtual void update() = 0;
	virtual std::tuple<int, int, TEXTURE_ID, int> get_queue() = 0;
	virtual std::vector<std::shared_ptr<Bullet>> shoot_weapon() = 0;
	bool is_weapon_triggered();
	void get_enemy_point(SDL_Point);
	void player_lost();
	Uint64 get_points();

protected:
	std::unique_ptr<Weapon> enemy_weapon;
	bool is_firing;
	bool found_player;
	SDL_Point player_point_;
	int movement_speed_;
	Uint64 score_value_;
	Uint16 shoot_dealy;
	Uint16 delay_ticks;
};

class EnemySentry : public Enemy{
public:
	EnemySentry(SDL_Point spawn_point, int move_speed, std::unique_ptr<Weapon> weapon, Uint64 score_value);
	~EnemySentry();
	void update();
	std::tuple<int, int, TEXTURE_ID, int> get_queue();
	std::vector<std::shared_ptr<Bullet>> shoot_weapon();
protected:

private:
	Uint16 ammo_capacity = 250;
	Uint16 reload_time = 1000;
	Uint16 gun_cooldown_ticks_ = 0;
	Uint16 weapon_cooldown_length_ = 4;
	Uint8 weapon_bullet_velocity_ = 22;
	Uint8 bullets_shot = 1;
	Uint16 ticks_to_max_spread = 120;
	float bullet_spread = 20.0;

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
	SDL_Rect get_temp_rect();
};




#endif /* OBJECT_H_ */
