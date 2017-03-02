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

class GameMenu : public MenuManager{
public:
	~GameMenu();
	void render_Texture();
	void event_Handler();


protected:
	void update_player();
	void update_enemy();
	void update_stage();
	coord check_collision();
	void pause_menu();
	void load_stage();
//	Player player;
	std::vector< std::shared_ptr< Object > > Objects;

};

#endif /* GAMEMENU_H_ */