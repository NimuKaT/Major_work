/*
 * Engine.cpp
 *
 *  Created on: 2017/03/08
 *      Author: Imukat
 */

#include "../Header/Engine.h"

Engine::Engine(){
	stage_id_ = STAGE_DEFAULT;
	stage_loaded = false;
	is_paused = false;
	renderer_ptr_ = NULL;
	master_texture_ = std::make_shared<Texture>();
	shift_x_= 0;
	shift_y_ = 0;
};

Engine::~Engine(){


};

void Engine::get_data(SDL_Renderer* renderer_ptr){
	renderer_ptr_ = renderer_ptr;
	master_texture_->set_renderer(renderer_ptr_);
	master_texture_->create_blank_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool Engine::load_stage(STAGE_ID stage_id){
	bool load_sucess = false;
//	Temp stage data
	stage_id_ = stage_id;
	switch(stage_id_){
		case STAGE_TEST:{
//			Camera initilisation
			test_camera_ = Camera();

//			Object initilisation
//				Player
			player_objects_.push_back(std::make_shared<Player>());
			moveable_list_.push_back(player_objects_.back());
//				Enemy


//				Wall
			wall_objects_.push_back(std::make_shared<Wall>(200, 200, 100, 100));
//			object_list_.push_back(wall_objects_.back());


//			Sprite sheet loading
			loaded_sprites_.assign(DEFAULT_TEXTURE_ID, NULL);
			loaded_sprites_[PLAYER] = std::make_shared<SpriteSheet>();
			loaded_sprites_[PLAYER]->set_renderer(renderer_ptr_);
			loaded_sprites_[PLAYER]->set_image_path(IMAGE_PATHS[PLAYER]);
			loaded_sprites_[PLAYER]->set_sprite_rects(IMAGE_RECTS[PLAYER]);
			loaded_sprites_[TEST_BALL] = std::make_shared<SpriteSheet>();
			loaded_sprites_[TEST_BALL]->set_renderer(renderer_ptr_);
			loaded_sprites_[TEST_BALL]->set_image_path(IMAGE_PATHS[TEST_BALL]);
			loaded_sprites_[TEST_BALL]->set_sprite_rects(IMAGE_RECTS[TEST_BALL]);
			loaded_sprites_[BULLET] = std::make_shared<SpriteSheet>();
			loaded_sprites_[BULLET]->set_renderer(renderer_ptr_);
			loaded_sprites_[BULLET]->set_image_path(IMAGE_PATHS[BULLET]);
			loaded_sprites_[BULLET]->set_sprite_rects(IMAGE_RECTS[BULLET]);

		}
	}
	stage_loaded = true;

	return load_sucess;
}

void Engine::main_loop(std::weak_ptr<Input_event> &input_data){
	if (!input_data.expired()){
		std::shared_ptr<Input_event> input = input_data.lock();

		if (input->key_pressed[KEY_PRESS_W]){
			player_objects_[0]->get_movement(0, -temp_camera_step_size);
		}
		if (input->key_pressed[KEY_PRESS_A]){
			player_objects_[0]->get_movement(-temp_camera_step_size, 0);
		}
		if (input->key_pressed[KEY_PRESS_S]){
			player_objects_[0]->get_movement(0, temp_camera_step_size);
		}
		if (input->key_pressed[KEY_PRESS_D]){
			player_objects_[0]->get_movement(temp_camera_step_size, 0);
		}


		if (input->key_pressed[KEY_PRESS_UP]){
			test_camera_.displace(0, -temp_camera_step_size);
		}
		if (input->key_pressed[KEY_PRESS_DOWN]){
			test_camera_.displace(0, temp_camera_step_size);
		}
		if (input->key_pressed[KEY_PRESS_LEFT]){
			test_camera_.displace(-temp_camera_step_size, 0);
		}
		if (input->key_pressed[KEY_PRESS_RIGHT]){
			test_camera_.displace(temp_camera_step_size, 0);
		}


		if (input->key_pressed[KEY_PRESS_MB_1]){
			auto new_bullets = player_objects_[0]->shoot_gun(get_angle_cursor_rel_player(input_data, player_objects_[0]));
			if(!new_bullets.empty()){
				player_bullets_.insert(player_bullets_.end(), new_bullets.begin(), new_bullets.end());
			}
		}
	}

	for (auto Mobject : moveable_list_){
		if (!Mobject.expired()){
			Mobject.lock()->update();
		}
	}

	for(auto &bullet : player_bullets_){
		bullet->update();
	}



//	Collision functions with all moving objects and walls
	for(auto &player : player_objects_){
		for(auto &wall : wall_objects_){
			if (player->get_hitbox().detect_collision(wall->get_hitbox())){
				player->bounce_object(wall->get_hitbox());
			}
		}
	}
//	Collision functions with player and Enemy/Enemy bullets
	for(auto &player : player_objects_){
		for(auto &enemy_bullet : enemy_bullets_){
			if (player->get_hitbox().detect_collision(enemy_bullet->get_hitbox())){


			}
		}
	}
//	Collision functions with enemy and player bullets

//	Collision of bullets with walls
	for(std::vector<std::shared_ptr<Bullet>>::iterator it=player_bullets_.begin();
			it != player_bullets_.end();){
		bool is_deleted = false;
		for(auto &wall : wall_objects_){
			if (it->get()->get_hitbox().detect_collision(wall->get_hitbox())){
					it = player_bullets_.erase(it);
					is_deleted = true;
					break;
			}
		}
		if(!is_deleted){
			it++;
		}
	}






//	std::cout<<get_angle_cursor_rel_player(input_data, player_objects_[0])<<std::endl;





}

float Engine::get_angle_cursor_rel_player(std::weak_ptr<Input_event> &input_data, std::weak_ptr<Player> player){
	float angle = 0.0;
	if (!input_data.expired() && !player.expired()){
		SDL_Point player_coord = player.lock()->get_centre();
		angle = atan2(-(input_data.lock()->mouse_y - (player_coord.y + shift_y_)),
				input_data.lock()->mouse_x - (player_coord.x +shift_x_)) / PI * 180;
	}
	return angle;
}


void Engine::render_from_queue(std::tuple<int, int, TEXTURE_ID, int> queue){
//	std::cout<<"x: "<<std::get<0>(queue) + shift_x_<<"\ny: "<<std::get<1>(queue) + shift_y_<<"\nImage_ID: "<<std::get<2>(queue)<<"\nRect_ID"<<std::get<3>(queue)<<std::endl;
	loaded_sprites_[std::get<2>(queue)]->render(std::get<0>(queue) + shift_x_, std::get<1>(queue) + shift_y_, std::get<3>(queue), 0.0);
}

void Engine::render_background(){

}

void Engine::render_player_type_objects(){

	for (auto &enemy_object : enemy_objects_){
		render_from_queue(enemy_object->get_queue());
	}
	for (auto &player_object : player_objects_){
		render_from_queue(player_object->get_queue());
	}
	for (auto &bullet_object : player_bullets_){
		render_from_queue(bullet_object->get_queue());
	}
}

void Engine::render_neutral_objects(){
	for (auto &wall_object : wall_objects_){
				render_from_queue(wall_object->get_queue());
		}
}


std::shared_ptr<Texture> Engine::get_last_texture(){
	master_texture_->create_blank_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
//	master_texture_->set_as_render_target();
	if (!is_paused){
		std::tuple<int, int> camera_shift = test_camera_.get_render_shift();
		shift_x_ = std::get<0>(camera_shift);
		shift_y_ = std::get<1>(camera_shift);
		render_background();
		render_neutral_objects();
		render_player_type_objects();
	}
	SDL_SetRenderTarget(renderer_ptr_, NULL);
	return	master_texture_;
}

/*
 * 		CAMERA CLASS
 */
Camera::Camera(int init_x, int init_y){
	x_pos_ = init_x;
	y_pos_ = init_y;
}

void Camera::set_displacement(int pos_x, int pos_y){
	check_boundaries();
}
void Camera::set_velocity(int vel_x, int vel_y){}
void Camera::set_acceleration(int acc_x, int acc_y){}
void Camera::displace(int dis_x, int dis_y){
	x_pos_ += dis_x;
	y_pos_ += dis_y;
	check_boundaries();
}

std::tuple<int, int> Camera::get_render_shift(){
	return std::make_tuple(x_pos_, y_pos_);
}

void Camera::check_boundaries(){
//	temp boundary
	if (x_pos_ > 400){
		x_pos_ = 400;
	}
	else if (x_pos_ < -400){
		x_pos_ = -400;
	}
	if (y_pos_ > 400){
		y_pos_ = 400;
	}
	else if (y_pos_< -400){
		y_pos_ = -400;
	}
}

