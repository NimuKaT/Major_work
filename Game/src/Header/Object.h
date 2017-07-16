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
	HitBox(int x, int y, int width, int height);
	void set_position(int x, int y);
	void set_size(int width, int height);
	bool detect_collision(HitBox &test_object_ref);
	float true_x_, true_y_ = 0.0;
	int x_, y_ = 0.;
	int width_, height_ = 0;

};



class Object : public HitBox {
public:
	Object();
	virtual ~Object();
	virtual void update() = 0;
	virtual std::tuple<int, int, TEXTURE_ID, int> get_queue() = 0;
	void bounce_object(HitBox &test_object_ref);

protected:
	float vel_x_, vel_y_ = 0.0;
	int sprite_frame_ = 0;
	std::vector<int> associated_sprite_queues_;



};

class Player : public Object{
public:
	Player();
	~Player();
	void update();
	void get_movement(int x, int y);
	std::tuple<int, int, TEXTURE_ID, int> get_queue();

private:
	bool input_states[5];

};

class Enemy : public Object{
public:
	Enemy();
	~Enemy();
	void update();
	void get_movement(int x, int y);
	std::tuple<int, int, TEXTURE_ID, int> get_queue();

private:
	bool input_states[5];

};

class Bullet : public Object{
public:
	Bullet();
	~Bullet();
	void update();
	void get_movement(int x, int y);
	std::tuple<int, int, TEXTURE_ID, int> get_queue();

private:
	bool input_states[5];

};

class InteractableObject : public Object{
public:
	InteractableObject();
	~InteractableObject();
	void update();
	void get_movement(int x, int y);
	std::tuple<int, int, TEXTURE_ID, int> get_queue();

private:
	bool input_states[5];

};

class Wall : public Object{
public:
	Wall();
	~Wall();
	void update();
	std::tuple<int, int, TEXTURE_ID, int> get_queue();

private:
	bool input_states[5];

};

#endif /* OBJECT_H_ */
