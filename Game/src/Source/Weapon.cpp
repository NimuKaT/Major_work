/*
 * Weapon.cpp
 *
 *  Created on: 19Jul.,2017
 *      Author: ImuKaT
 */

#include "../Header/Weapon.h"

Weapon::Weapon(){
	is_shooting = false;
	is_reloading = false;
	reload_ticks = 0;
	weapon_cooldown_ticks_ = 0;
	spread_ticks = 0;
}

void Weapon::add_tick(){
	if (weapon_cooldown_ticks_ != 0){
		weapon_cooldown_ticks_--;
	}
	if (is_shooting || weapon_cooldown_ticks_ > 0){
		if (spread_ticks < ticks_to_max_spread && !is_reloading && current_ammo_in_clip > 0){
			if (spread_ticks == 0){
				spread_ticks = starting_spread;
			}
			else{
				spread_ticks++;
			}
		}
	}
	else if (spread_ticks != 0){
		spread_ticks--;
	}
	if (reload_ticks > 0){
		reload_ticks-=1;
		std::cout<<reload_ticks<<std::endl;
		if (reload_ticks == 0){
			is_reloading = false;
			current_ammo_in_clip = ammo_capacity;
		}
	}
	is_shooting = false;
}

bool Weapon::can_shoot(){
	bool can_fire = false;
	if (weapon_cooldown_ticks_ == 0){
		if (!is_reloading){
			if (current_ammo_in_clip > 0){
				can_fire = true;
			}
		}
	}
	return can_fire;
}

bool Weapon::shoot_weapon(){
	is_shooting = true;
	return can_shoot();
}

void Weapon::reload_weapon(){
	if (current_ammo_in_clip != ammo_capacity && !is_reloading){
		is_reloading = true;
		reload_ticks = reload_time;
	}
}

std::vector<std::shared_ptr<Bullet>> Weapon::get_bullet_shot(SDL_Point barrel_position, float weapon_angle){
	std::vector<std::shared_ptr<Bullet>> bullet_pellet;
	if (is_shooting && !is_reloading){
		if (weapon_cooldown_ticks_ == 0){
			if (current_ammo_in_clip > 0){
				float shooting_angle = (weapon_angle + pow((-1),(rand()%2))*(bullet_spread *	float(float(spread_ticks) / float(ticks_to_max_spread)))
						* (float(rand()) / float(RAND_MAX))) /180*PI;
//				std::cout<<shooting_angle<<std::endl;
//				std::cout<<weapon_angle<<std::endl;
//				std::cout<<float(float(spread_ticks) / float(ticks_to_max_spread))<<std::endl;
//				std::cout<<rand()<<std::endl;
				for(int i = 0; i <= bullets_shot; i++){
//					std::cout<<i<<std::endl;
					bullet_pellet.push_back(std::make_shared<Bullet>(barrel_position.x,
							barrel_position.y,
							cos(shooting_angle+(pow((-1),i)*bullet_angualr_distance*floor(i/2)/180*PI))*weapon_bullet_velocity_,
							sin(shooting_angle+(pow((-1),i)*bullet_angualr_distance*floor(i/2)/180*PI))*weapon_bullet_velocity_));
					weapon_cooldown_ticks_ = weapon_cooldown_length_;
				}
				if (int(current_ammo_in_clip) - int(bullets_shot) < 0){
					current_ammo_in_clip = 0;
				}
				else{
					current_ammo_in_clip-= bullets_shot;
				}
			}
		}
	}
	return bullet_pellet;
}

MiniGun::MiniGun(){
	Weapon();
	weapon_bullet_velocity_ = 18;
	bullets_shot = 1;
	ticks_to_max_spread = 120;
	starting_spread = 40;
	bullet_spread = 25.0;
	bullet_angualr_distance = 0.0;
	weapon_cooldown_length_ = 2;
	reload_time = 300;
	ammo_capacity = 250;
	current_ammo_in_clip  = ammo_capacity;
}

Rifle::Rifle(){
	Weapon();
	weapon_bullet_velocity_ = 26;
	bullets_shot = 1;
	ticks_to_max_spread = 115;
	starting_spread = 10;
	bullet_spread = 12.0;
	bullet_angualr_distance = 0.0;
	weapon_cooldown_length_ = 8;
	reload_time = 90;
	ammo_capacity = 24;
	current_ammo_in_clip  = ammo_capacity;
}

Pistol::Pistol(){
	Weapon();
	weapon_bullet_velocity_ = 34;
	bullets_shot = 1;
	ticks_to_max_spread = 120;
	starting_spread = 60;
	bullet_spread = 6.0;
	bullet_angualr_distance = 20.0;
	weapon_cooldown_length_ = 8;
	reload_time = 30;
	ammo_capacity = 8;
	current_ammo_in_clip  = ammo_capacity;
}
