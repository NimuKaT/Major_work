/*
 * Texture.h
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <fstream>

#include "Global.h"


void add_rect_to_vector(std::vector< SDL_Rect> &, int, int, int, int);

class Texture{
public:
	void init( SDL_Renderer* , std::string, std::vector< SDL_Rect > = std::vector< SDL_Rect >() );
	void loadTexture();
	void render(int = 0);

private:
	SDL_Renderer* _renderer_ptr;
	SDL_Texture* objectTexture;
	std::string image_path;
	std::vector< SDL_Rect > sprite_clips;
};



#endif /* TEXTURE_H_ */
