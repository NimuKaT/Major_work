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
#include "Object.h"

struct coord{
	int x, y;
};

enum DEFAULT_CONTROLLS{
	MOVE_UP = KEY_PRESS_W,
	MOVE_DOWN = KEY_PRESS_S,
	MOVE_LEFT = KEY_PRESS_A,
	MOVE_RIGHT = KEY_PRESS_D

};

class GameMenu : public MenuManager{
public:
	GameMenu(SDL_Renderer* renderer_ptr, Input_event* input_ptr);
	void render_texture();
	void update_logic();

protected:
	void update_player();
	void update_enemy();
	void update_stage();
	coord check_collision();
	void pause_menu();
	void load_stage();
	Player player;
	std::vector<std::shared_ptr<Object>> Objects;

private:
	bool is_paused;

};

#endif /* GAMEMENU_H_ */
