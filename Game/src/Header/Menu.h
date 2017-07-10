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

protected:
	int mouse_x_, mouse_y_;
	Input_event* input_data_ = NULL;
	SDL_Renderer* renderer_ptr_ = NULL;

};

class MainMenu : public MenuManager{
public:
	MainMenu(SDL_Renderer* renderer_ptr, Input_event* input_ptr);
	void render_texture();
	void event_Handler(SDL_Event &event, bool &quit);
	void update_logic();

private:
	std::vector<render_queue> queue;
	std::vector<SpriteSheet> sprite_sheets;
	std::vector<std::string> spritePaths;
	std::vector<SDL_Rect> clips;
	Text test_text;
	UI_element _test_button;
	Texture main_menu_background;
};


#endif /* MENU_H_ */
