/*
 * UIhandler.h
 *
 *  Created on: 24Jan.,2017
 *      Author: ImuKaT
 */

#ifndef UIHANDLER_H_
#define UIHANDLER_H_

#include "Global.h"


#include "Texture.h"

class UI_handler{
public:
	bool init_UI();
	void add_element(); //functions that adds an widget to the interface
	SDL_Texture* get_UI_texture();

};

#endif /* UIHANDLER_H_ */
