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

//stub constants
//
//const int TILE_DIMENSION = 16;
const static Uint8 temp_camera_step_size = 4;

// Space for enums for stages enemy types etc.







class Camera {
public:
	Camera(int init_x = 0, int init_y = 0);
	void set_displacement(int pos_x, int pos_y);
	void set_velocity(int vel_x, int vel_y);
	void set_acceleration(int acc_x, int acc_y);
	void displace(int dis_x, int dis_y);
	std::tuple<int, int> get_render_shift();
private:
	void check_boundaries();
	int x_pos_, y_pos_;
	std::vector<std::tuple<int, int>> boundary_coord_;

};

class Engine {
public:
	Engine();
	~Engine();
	bool load_stage(STAGE_ID stage_id);
	void main_loop(std::weak_ptr<Input_event> &input_data);
	void get_data(SDL_Renderer* renderer_ptr);
	std::shared_ptr<Texture> get_last_texture();

private:
	bool stage_loaded = false;
	bool is_paused = false;
	STAGE_ID stage_id_ = STAGE_DEFAULT;
	SDL_Renderer* renderer_ptr_;
//	Game objects
	std::vector<std::weak_ptr<Object>> object_list_;
	std::vector<std::weak_ptr<MoveableObject>> moveable_list_;
	std::vector<std::weak_ptr<Entity>> entity_list_;


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
	int shift_x_, shift_y_ = 0;

//	Calculation functions
	float get_angle_cursor_rel_player(std::weak_ptr<Input_event> &input_data, std::weak_ptr<Player> player);

	void set_paused(bool is_paused);
	void render_from_queue(std::tuple<int, int, TEXTURE_ID, int> queue);
	void render_background();
	void render_neutral_objects();
	void render_enemy_type_objects();
	void render_player_type_objects();
	void render_UI();

//	Temp objects
	Camera test_camera_;

};


#endif /* ENGINE_H_ */
