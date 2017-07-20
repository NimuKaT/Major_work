/*
 * Menu.h
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#ifndef MENU_H_
#define MENU_H_

#include "Global.h"

#include "Texture.h"
#include "Text.h"
#include "UIhandler.h"

struct render_queue{
	int sprite_num;
	int x, y;
	int clip_num;
};

class MenuManager{
public:
//	virtual ~MenuManager() = 0;
//	virtual void load_data() = 0;
//	virtual void unload_data() = 0;
	virtual void render_texture() = 0;
	virtual void update_logic() = 0;
	int change_menu();
	bool quit_game();

protected:
	int mouse_x_, mouse_y_;
	std::weak_ptr<Input_event> input_data_;
	SDL_Renderer* renderer_ptr_;
	int next_menu;
	int current_menu;
	bool quit = false;

};

class MainMenu : public MenuManager{
public:
	MainMenu(SDL_Renderer* renderer_ptr, std::shared_ptr<Input_event> &input_ptr);
	void render_texture();
	void event_Handler(SDL_Event &event, bool &quit);
	void update_logic();


private:
	std::vector<render_queue> queue;
	std::vector<SpriteSheet> sprite_sheets;
	std::vector<std::string> spritePaths;
	std::vector<SDL_Rect> clips;
	Text game_logo;
	UI_element _test_button;
	Texture main_menu_background;

	SpriteSheet element_deco;

	UI_element play_button_;
	UI_element options_button_;
	UI_element exit_button_;

};


#endif /* MENU_H_ */
