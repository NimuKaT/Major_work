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
	Test_Menu( SDL_Renderer* );
	void render_Texture();
	void update_logic();


private:
	SDL_Renderer* _renderer_ptr = NULL;
	Texture _texture_balls;

	Uint8 texture_opacity = 0;


};

#endif /* TESTMENU_H_ */
