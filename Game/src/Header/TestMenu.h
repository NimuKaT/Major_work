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
	Test_Menu( SDL_Renderer*, Input_event* );
	void render_Texture();
	void update_logic();


private:
//	SpriteSheet test
	SpriteSheet _texture_balls;

//	UI_element test
	SpriteSheet decoration_sprite;
	UI_element test_button_;
	bool button_event;



// Test Variables
	Uint8 texture_opacity = 200;
	float scale_factor = SCREEN_HEIGHT/9;
	int x, y;

};

#endif /* TESTMENU_H_ */
