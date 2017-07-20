/*
 * GameMenu.h
 *
 *  Created on: 2017/02/22
 *      Author: Imukat
 */

#ifndef GAMEMENU_H_
#define GAMEMENU_H_

#include "global.h"
#include "Menu.h"
#include "Engine.h"
#include "Texture.h"

enum DEFAULT_CONTROLLS{
	MOVE_UP = KEY_PRESS_W,
	MOVE_DOWN = KEY_PRESS_S,
	MOVE_LEFT = KEY_PRESS_A,
	MOVE_RIGHT = KEY_PRESS_D

};

class GameMenu : public MenuManager{
public:
	GameMenu(SDL_Renderer* renderer_ptr, std::shared_ptr<Input_event> &input_ptr);
	void render_texture();
	void update_logic();

protected:
	void load_stage();
	std::unique_ptr<Engine> game_instance;

private:
	bool is_paused;
	bool unique_press;
	bool quit_pressed;
	SpriteSheet button_deco;
	Texture pause_menu_shade_;
	Text paused_text;
	Text quit_confirmation_text_;
	UI_element resume_button;
	UI_element quit_button;
	UI_element quit_yes_button_;
	UI_element quit_no_button_;

};

#endif /* GAMEMENU_H_ */
