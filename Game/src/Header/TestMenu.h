/*
 * TestMenu.h
 *
 *  Created on: 12Jun.,2017
 *      Author: ImuKaT
 */

#ifndef TESTMENU_H_
#define TESTMENU_H_

#include "global.h"
#include "Menu.h"
#include "Texture.h"

class Test_Menu : public MenuManager{
public:
	Test_Menu(SDL_Renderer* renderer_ptr, std::shared_ptr<Input_event> &input_ptr);
	void render_texture();
	void update_logic();

private:
//	SpriteSheet test
	SpriteSheet texture_balls_;

//	UI_element test
	SpriteSheet decoration_sprite_;
	UI_element test_button_;
	bool button_event_;

// Test Variables
	Uint8 texture_opacity = 200;
	int x_, y_ = 0;
};

#endif /* TESTMENU_H_ */
