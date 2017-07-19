/*
 * Weapon.h
 *
 *  Created on: 19Jul.,2017
 *      Author: ImuKaT
 */

#ifndef WEAPON_H_
#define WEAPON_H_

#include "Global.h"
#include "Object.h"

class Bullet;

class Weapon{
public:
	Weapon();
	void add_tick();
	bool shoot_weapon();
	std::vector<std::shared_ptr<Bullet>> get_bullet_shot(SDL_Point barrel_position, float weapon_angle);
	bool can_shoot();
	void reload_weapon();
	Uint16 ammo_left_in_clip();
	bool is_weapon_empty();
	bool is_weapon_reloading();
protected:
	bool is_shooting = false;
	bool is_reloading = false;

	Uint16 current_ammo_in_clip;
	Uint16 ammo_capacity;

	Uint16 reload_ticks;
	Uint16 reload_time;

	Uint16 weapon_cooldown_ticks_;
	Uint16 weapon_cooldown_length_;

	Uint8 weapon_bullet_velocity_;
	Uint8 bullets_shot;

	Uint16 spread_ticks;
	Uint16 ticks_to_max_spread;
	Uint16 starting_spread;

	float bullet_spread;
	float bullet_angualr_distance;
};

class MiniGun : public Weapon{
public:
	MiniGun();
};

class Rifle : public Weapon{
public:
	Rifle();
};

class Pistol : public Weapon{
public:
	Pistol();
};


#endif /* WEAPON_H_ */
