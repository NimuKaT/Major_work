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
	int sprite_number;
	int x, y;
	int clip_number;
};

class MenuManager{
public:
	virtual ~MenuManager() = 0;
	virtual void renderTexture() = 0;
	virtual void eventHandler (SDL_Event &, bool &) = 0;

protected:
	int _mouse_x, _mouse_y;

};


class MainMenu : public MenuManager{
public:
	MainMenu( SDL_Renderer* );
	void renderTexture();
	void eventHandler(SDL_Event &, bool &);

	std::vector< std::vector< int > > queue;
	std::vector< Texture> sprite_sheets;
	SDL_Renderer* _renderer;
	std::vector< std::string > spritePaths;
	std::vector< SDL_Rect > clips;

	Text test_text;

private:
	UI_element _test_button;
	Texture main_menu_background;
	bool key_pressed[KEY_PRESS_DEFAULT];




};



#endif /* MENU_H_ */
