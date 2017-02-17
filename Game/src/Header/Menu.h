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
	virtual ~MenuManager() = 0;
//	virtual void load_data() = 0;
//	virtual void unload_data() = 0;
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

	std::vector< render_queue > queue;
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
