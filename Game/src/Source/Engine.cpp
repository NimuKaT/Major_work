/*
 * Engine.cpp
 *
 *  Created on: 2017/03/08
 *      Author: Imukat
 */

#include "../Header/Engine.h"

float get_random_float(){
	return float(rand())/float(RAND_MAX);
}

Engine::Engine(){
	srand(time(NULL));
	stage_id_ = STAGE_DEFAULT;
	stage_loaded = false;
	is_paused = false;
	game_over = false;
	renderer_ptr_ = NULL;
	master_texture_ = std::make_shared<Texture>();
	current_ammo_text_ = std::unique_ptr<Text>(new Text());
	current_ammo_text_->set_font("Sans");
	current_ammo_text_->set_font_size(42);
	current_ammo_text_->set_color(0xFF, 0xFF, 0xFF, 0xFF);

	max_ammo_text_ = std::unique_ptr<Text>(new Text());
	max_ammo_text_->set_font("Sans");
	max_ammo_text_->set_font_size(42);
	max_ammo_text_->set_color(0xFF, 0xFF, 0xFF, 0xFF);

	weapon_texture_ = std::unique_ptr<Texture>(new Texture());
	UI_backdrop_ = std::unique_ptr<Texture>(new Texture());
	reload_indicator_ = std::unique_ptr<Texture>(new Texture());
	ammo_count = 0;
	weapon_cooldown_percent = 0.0;


	score_text_ = std::unique_ptr<Text>(new Text());
	score_text_->set_font("Sans");
	score_text_->set_font_size(42);
	score_text_->set_color(0xFF, 0xFF, 0xFF, 0xFF);
	score_text_->set_text("Score: "+ std::to_string(score));
	score_backdorp_ = std::unique_ptr<Texture>(new Texture());
	score = 0;

	main_game_over_text_ = std::unique_ptr<Text>(new Text());
	main_game_over_text_->set_font("Sans");
	main_game_over_text_->set_font_size(240);
	main_game_over_text_->set_color(0xFF, 0xFF, 0xFF, 0xFF);
	main_game_over_text_->set_text("GAME OVER");
//
	sub_game_over_text_ = std::unique_ptr<Text>(new Text());
	sub_game_over_text_->set_font("Sans");
	sub_game_over_text_->set_font_size(180);
	sub_game_over_text_->set_color(0xFF, 0xFF, 0xFF, 0xFF);
	sub_game_over_text_->set_text("Press Space to restart");

	game_over_backdrop = std::unique_ptr<Texture>(new Texture());

	background = std::unique_ptr<Texture>(new Texture());

	current_level = 0;
	level_iteration = 0;
	generate_next_difficulty();
};

Engine::~Engine(){


};

void Engine::generate_walls(){
	int abs_w = 1000;
	int abs_h = 1000;
	int sum_w_h = 1750;
	int abs_x = 3840 - abs_w;
	int abs_y = 2160 - abs_h;
	SDL_Point centre;
	if (!player_objects_.empty()){
	 centre = player_objects_[0]->get_centre();
	}
	else{
		centre = {1920, 1080};
	}

	int rand_w =0;
	int rand_h = 0;
	int rand_x = 0;
	int rand_y = 0;
	for(int i = 0; i < 5; i++){
		rand_w = floor(abs_w * get_random_float());
		while(rand_w < 40){
			rand_w = floor(abs_w * get_random_float());
		}
		rand_h = floor(abs_h * get_random_float());
		while(rand_h > sum_w_h - rand_w || rand_h < 40){
			rand_h = floor(abs_h *get_random_float());
		}
		rand_x = floor(abs_x *get_random_float());
		rand_y = floor(abs_y *get_random_float());
		while(rand_x < centre.x+100 && rand_x + rand_w > centre.x-100 &&
			rand_y < centre.y+100 && rand_y + rand_h > centre.y-100){
			rand_w = floor(abs_w * get_random_float());
			while(rand_w < 40){
				rand_w = floor(abs_w * get_random_float());
			}
			rand_h = floor(abs_h * get_random_float());
			while(rand_h > sum_w_h - rand_w || rand_h < 40){
				rand_h = floor(abs_h *get_random_float());
			}
			rand_x = floor(abs_x *get_random_float());
			rand_y = floor(abs_y *get_random_float());
		}
		wall_objects_.push_back(std::make_shared<Wall>(rand_x, rand_y, rand_w, rand_h));
	}
}

void Engine::generate_next_difficulty(){
	int rand_x = 0;
	int rand_y = 0;
	int abs_x = 3840 - 100;
	int abs_y = 2160 -100;
	bool collide = false;

	SDL_Rect exclusion = {1920-320, 1080 - 180, 320, 180};

	HitBox test_box;

	level_iteration++;
	if (level_iteration > 5){
		level_iteration = 1;
		current_level++;
		if (current_level > 5){
			current_level = 1;
		}
	}

	for(int i = 0; i < level_iteration; i++){
		//gen coord
		rand_x = floor(abs_x *get_random_float());
		rand_y = floor(abs_y *get_random_float());
		test_box = HitBox(SDL_Rect{rand_x, rand_y, 100, 100});
		for(auto &wall : wall_objects_){
			if (test_box.detect_collision(wall->get_hitbox())){
				collide = true;
				break;
			}
		}
		while ((rand_x > exclusion.x && rand_x < exclusion.x + exclusion.w &&
				rand_y > exclusion.y && rand_y < exclusion.y + exclusion.h) || collide){
			collide = false;
			rand_x = floor(abs_x *get_random_float());
			rand_y = floor(abs_y *get_random_float());
			test_box = HitBox(SDL_Rect{rand_x, rand_y, 100, 100});
			for(auto &wall : wall_objects_){
				if (test_box.detect_collision(wall->get_hitbox())){
					collide = true;
					break;
				}
			}
		}

		switch(current_level){
			case 1:{
				// pistol, speed 8
				enemy_objects_.push_back(std::shared_ptr<Enemy>(new EnemySentry(SDL_Point {rand_x, rand_y}, 10, std::unique_ptr<Weapon>(new Pistol()), 100)));
				break;
			}
			case 2:{
				enemy_objects_.push_back(std::shared_ptr<Enemy>(new EnemySentry(SDL_Point {rand_x, rand_y}, 16, std::unique_ptr<Weapon>(new Pistol()), 150)));
				break;
						}
			case 3:{
				enemy_objects_.push_back(std::shared_ptr<Enemy>(new EnemySentry(SDL_Point {rand_x, rand_y}, 8, std::unique_ptr<Weapon>(new Rifle()), 250)));
				break;
						}
			case 4:{
				enemy_objects_.push_back(std::shared_ptr<Enemy>(new EnemySentry(SDL_Point {rand_x, rand_y}, 12, std::unique_ptr<Weapon>(new Rifle()), 500)));
				break;
						}
			case 5:{
				enemy_objects_.push_back(std::shared_ptr<Enemy>(new EnemySentry(SDL_Point {rand_x, rand_y}, 4, std::unique_ptr<Weapon>(new MiniGun()), 2000)));
				break;
						}
		}
	}

}





void Engine::get_data(SDL_Renderer* renderer_ptr){
	renderer_ptr_ = renderer_ptr;
	master_texture_->set_renderer(renderer_ptr_);
	master_texture_->create_blank_texture(SCREEN_WIDTH, SCREEN_HEIGHT);

	current_ammo_text_->set_renderer(renderer_ptr_);

	max_ammo_text_->set_renderer(renderer_ptr_);

	weapon_texture_->set_renderer(renderer_ptr_);

	UI_backdrop_->set_renderer(renderer_ptr_);
	UI_backdrop_->create_blank_texture(350, 100, 0x00, 0x00, 0x00, 0xFF);
	UI_backdrop_->set_texture_alpha(0x80);

	reload_indicator_->set_renderer(renderer_ptr_);
	reload_indicator_->create_blank_texture(150, 75, 0xFF, 0x00, 0x00, 0xFF);
	reload_indicator_->set_texture_alpha(0x40);

	score_backdorp_->set_renderer(renderer_ptr_);
	score_backdorp_->create_blank_texture(350, 100, 0x00, 0x00, 0x00, 0xFF);
	score_backdorp_->set_texture_alpha(0x80);
	score_text_->set_renderer(renderer_ptr_);

	main_game_over_text_->set_renderer(renderer_ptr_);
	sub_game_over_text_->set_renderer(renderer_ptr_);

	game_over_backdrop->set_renderer(renderer_ptr_);
	game_over_backdrop->create_blank_texture(3840, 2160, 0x00, 0x00, 0x00, 0xFF);
	game_over_backdrop->set_texture_alpha(0xFF);

	background->set_renderer(renderer_ptr_);
	background->set_image_path(IMAGE_PATHS[TEMP_MAIN_MENU_BACKGROUND]);

}

bool Engine::load_stage(STAGE_ID stage_id){
	bool load_sucess = false;
//	Temp stage data
	stage_id_ = stage_id;
	generate_walls();
	generate_next_difficulty();

//				Wall
	wall_objects_.push_back(std::make_shared<Wall>(-200, -50, 200, 2160+200));
	wall_objects_.push_back(std::make_shared<Wall>(3840, -50, 200, 2160+200));
	wall_objects_.push_back(std::make_shared<Wall>( -50, -200, 3840+200, 200));
	wall_objects_.push_back(std::make_shared<Wall>( -50, 2160, 3840+200, 200));
	wall_drawer = std::make_shared<Texture>();
	wall_drawer->set_renderer(renderer_ptr_);
	wall_drawer->setBlendMode(SDL_BLENDMODE_NONE);
	player_objects_.push_back(std::make_shared<Player>(SDL_Point {1920, 1080}));
	max_ammo_text_->set_text("/"+std::to_string(player_objects_[0]->get_weapon_capacity()));
	current_ammo_text_->set_text(std::to_string(player_objects_[0]->get_weapon_capacity()));

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


	stage_loaded = true;

	return load_sucess;
}

void Engine::main_loop(std::weak_ptr<Input_event> &input_data){
	if (!input_data.expired()){
		std::shared_ptr<Input_event> input = input_data.lock();
		if (!player_objects_.empty()){
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
			if (input->key_pressed[KEY_PRESS_R]){
				player_objects_[0]->reload();
			}
		}


		if (input->key_pressed[KEY_PRESS_UP]){
			generate_next_difficulty();
		}
		if (input->key_pressed[KEY_PRESS_DOWN]){
		}
		if (input->key_pressed[KEY_PRESS_LEFT]){
		}
		if (input->key_pressed[KEY_PRESS_RIGHT]){
		}


		if (input->key_pressed[KEY_PRESS_MB_1]){
			if (!player_objects_.empty()){
				if (player_objects_[0]->get_current_ammo_count() > 0){
					auto new_bullets = player_objects_[0]->shoot_gun(get_angle_cursor_rel_player(input_data, player_objects_[0]));
					if(!new_bullets.empty()){
						player_bullets_.insert(player_bullets_.end(), new_bullets.begin(), new_bullets.end());
					}
				}
				else{
					player_objects_[0]->reload();
				}
			}
		}
	}

//	for (auto Mobject : moveable_list_){
//		if (!Mobject.expired()){
//			Mobject.lock()->update();
//		}
//	}
	for(auto &player : player_objects_){
		player->update();
	}

//	Enemy update



	for(auto &enemy : enemy_objects_){
		SDL_Point player_point = player_objects_[0]->get_centre();
		SDL_Point enemy_point;
		bool line_of_sight = true;
		enemy->update();
		enemy_point = enemy->get_centre();
		for(auto &wall: wall_objects_){
			SDL_Rect rect_copy = wall->get_temp_rect();
				if( SDL_IntersectRectAndLine(&rect_copy, &player_point.x, &player_point.y, &enemy_point.x, &enemy_point.y)){
					line_of_sight = false;
					break;
				}
		}
		if (line_of_sight){
			enemy->get_enemy_point(player_point);
		}
		else{
			enemy->player_lost();
		}
		if (enemy->is_weapon_triggered()){
			auto new_bullets = enemy->shoot_weapon();
			if(!new_bullets.empty()){
				enemy_bullets_.insert(enemy_bullets_.end(), new_bullets.begin(), new_bullets.end());
			}
		}
	}


	for(auto &bullet : player_bullets_){
		bullet->update();
	}

	for(auto &bullet : enemy_bullets_){
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

	for(auto &enemy : enemy_objects_){
			for(auto &wall : wall_objects_){
				if (enemy->get_hitbox().detect_collision(wall->get_hitbox())){
					enemy->bounce_object(wall->get_hitbox());
				}
			}
		}
//	Collision functions with player and Enemy/Enemy bullets
	for(auto &player : player_objects_){
		for(auto &enemy_bullet : enemy_bullets_){
			if (player->get_hitbox().detect_collision(enemy_bullet->get_hitbox())){
				game_over = true;
				player_objects_.erase(player_objects_.begin());
				break;

			}
		}
	}
//	Collision functions with enemy and player bullets
	for(std::vector<std::shared_ptr<Enemy>>::iterator it=enemy_objects_.begin();
			it != enemy_objects_.end();){
			bool is_deleted = false;
			for(std::vector<std::shared_ptr<Bullet>>::iterator it_b=player_bullets_.begin(); it_b != player_bullets_.end();){
				if (it->get()->get_hitbox().detect_collision(it_b->get()->get_hitbox())){
//					Temp score
					score += abs(it->get()->get_points());
					it_b = player_bullets_.erase(it_b);
					it_b = player_bullets_.erase(it_b);
					it = enemy_objects_.erase(it);
					is_deleted = true;
					break;
				}
				else{
					it_b++;
				}
			}
			if(!is_deleted){
				it++;
			}
		}


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
	for(std::vector<std::shared_ptr<Bullet>>::iterator it=enemy_bullets_.begin();
		it != enemy_bullets_.end();){
		bool is_deleted = false;
		for(auto &wall : wall_objects_){
			if (it->get()->get_hitbox().detect_collision(wall->get_hitbox())){
					it = enemy_bullets_.erase(it);
					is_deleted = true;
					break;
			}
		}
		if(!is_deleted){
			it++;
		}
	}

	if (enemy_objects_.empty()){
		generate_next_difficulty();
	}

	update_UI();
}

bool Engine::is_game_end(){
	return game_over;
}

void Engine::update_UI(){
	if (!player_objects_.empty()){
		ammo_count = player_objects_[0]->get_current_ammo_count();
		weapon_cooldown_percent = player_objects_[0]->get_reload_percentage();
	}
	if (floor(150*weapon_cooldown_percent) > 0){
		reload_indicator_->create_blank_texture(floor(150*weapon_cooldown_percent), 75, 0xFF, 0x00, 0x00, 0xFF);
	}
	current_ammo_text_->set_text(std::to_string(ammo_count));

	score_text_->set_text("Score: "+ std::to_string(score));
	sub_game_over_text_->set_text("Press Space to restart");

}


float Engine::get_angle_cursor_rel_player(std::weak_ptr<Input_event> &input_data, std::weak_ptr<Player> player){
	float angle = 0.0;
	if (!input_data.expired() && !player.expired()){
		SDL_Point player_coord = player.lock()->get_centre();
		angle = atan2(-(input_data.lock()->mouse_y - player_coord.y),
				input_data.lock()->mouse_x - player_coord.x) / PI * 180;
	}
	return angle;
}


void Engine::render_from_queue(std::tuple<int, int, TEXTURE_ID, int> queue){
//	std::cout<<"x: "<<std::get<0>(queue) + shift_x_<<"\ny: "<<std::get<1>(queue) + shift_y_<<"\nImage_ID: "<<std::get<2>(queue)<<"\nRect_ID"<<std::get<3>(queue)<<std::endl;
	loaded_sprites_[std::get<2>(queue)]->render(std::get<0>(queue), std::get<1>(queue), std::get<3>(queue), 0.0);
}

void Engine::render_background(){
	background->render(0, 0);
}

void Engine::render_player_type_objects(){
	for (auto &bullet_object : enemy_bullets_){
		render_from_queue(bullet_object->get_queue());
	}
	for (auto &bullet_object : player_bullets_){
		render_from_queue(bullet_object->get_queue());
	}
	for (auto &enemy_object : enemy_objects_){
		render_from_queue(enemy_object->get_queue());
	}
	for (auto &player_object : player_objects_){
		render_from_queue(player_object->get_queue());
	}
}

void Engine::render_neutral_objects(){
	for (auto &wall_object : wall_objects_){
//				render_from_queue(wall_object->get_queue());
				SDL_Rect temp_rect = wall_object->get_temp_rect();
				wall_drawer->create_blank_texture(temp_rect.w, temp_rect.h, 0x00, 0x00, 0x00, 0xFF);
				wall_drawer->render(temp_rect.x, temp_rect.y);
		}
}

void Engine::render_UI(){
	UI_backdrop_->render(3490, 2060);
	max_ammo_text_->render(3750, 2110);
	current_ammo_text_->render(3770, 2060);
	if (weapon_cooldown_percent > 0.0){
		reload_indicator_->render(3530, 2100);
	}

	score_backdorp_->render(3840 - 350, 0);
	score_text_->render(3840 - score_text_->get_size().x -25, 0);
	if (game_over){
		game_over_backdrop->render(0,0);
		main_game_over_text_->render(1920 - main_game_over_text_->get_size().x/2, 600);
		score_text_->set_font_size(120);
		score_text_->render(1920 - score_text_->get_size().x/2, 1200);
		sub_game_over_text_->render(1920 - sub_game_over_text_->get_size().x/2, 1500);
	}
}


std::shared_ptr<Texture> Engine::get_last_texture(){
	master_texture_->create_blank_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
//	master_texture_->set_as_render_target();
	if (!is_paused){
		render_background();
		render_neutral_objects();
		render_player_type_objects();
		render_UI();
	}
	SDL_SetRenderTarget(renderer_ptr_, NULL);
	return	master_texture_;
}

