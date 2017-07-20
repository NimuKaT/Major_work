/*
 * Engine.h
 *
 *  Created on: 2017/03/08
 *      Author: Imukat
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "Global.h"
#include "Object.h"
#include "Texture.h"
#include "Text.h"

//stub constants
//
//const int TILE_DIMENSION = 16;
const static Uint8 temp_camera_step_size = 20;

// Space for enums for stages enemy types etc.

float get_random_float();

class Engine {
public:
	Engine();
	~Engine();
	bool load_stage(STAGE_ID stage_id);
	void main_loop(std::weak_ptr<Input_event> &input_data);
	void get_data(SDL_Renderer* renderer_ptr);
	std::shared_ptr<Texture> get_last_texture();
	bool is_game_end();

	// New game


private:
	void generate_walls();

	void generate_next_difficulty();
	Uint16 level_iteration;
	Uint16 current_level;

	Uint64 score;

	std::vector<std::unique_ptr<Wall>> wall_objects;
	bool game_over;

	std::unique_ptr<Text> main_game_over_text_;
	std::unique_ptr<Text> sub_game_over_text_;
	std::unique_ptr<Texture> game_over_backdrop;

	//old game

	bool stage_loaded = false;
	bool is_paused = false;
	STAGE_ID stage_id_ = STAGE_DEFAULT;
	SDL_Renderer* renderer_ptr_;

//	Game objects
	std::vector<std::unique_ptr<Object>> object_list_;

	std::vector<std::shared_ptr<Wall>> wall_objects_;

	std::vector<std::shared_ptr<Player>> player_objects_;
	std::vector<std::shared_ptr<Bullet>> player_bullets_;

	std::vector<std::shared_ptr<Enemy>> enemy_objects_;
	std::vector<std::shared_ptr<Bullet>> enemy_bullets_;
//	Render objects
//	Texture temp_texture;
	std::shared_ptr<Texture> master_texture_;
	std::vector<std::tuple<int, int, TEXTURE_ID, int>> render_queue_;
	std::vector<std::shared_ptr<SpriteSheet>> loaded_sprites_;

//	UI textures
	std::unique_ptr<Text> current_ammo_text_;
	std::unique_ptr<Text> max_ammo_text_;
	std::unique_ptr<Texture> weapon_texture_;
	std::unique_ptr<Texture> UI_backdrop_;
	std::unique_ptr<Texture> reload_indicator_;
	float weapon_cooldown_percent;
	Uint16 ammo_count;

	std::unique_ptr<Text> score_text_;
	std::unique_ptr<Texture> score_backdorp_;

	std::unique_ptr<Texture> background;


//	Calculation functions
	float get_angle_cursor_rel_player(std::weak_ptr<Input_event> &input_data, std::weak_ptr<Player> player);
	void update_UI();
	void set_paused(bool is_paused);
	void render_from_queue(std::tuple<int, int, TEXTURE_ID, int> queue);
	void render_background();
	void render_neutral_objects();
	void render_enemy_type_objects();
	void render_player_type_objects();
	void render_UI();


	std::shared_ptr<Texture> wall_drawer;

};


#endif /* ENGINE_H_ */
