/*
 * Test.h
 *
 *  Created on: 19Dec.,2016
 *      Author: ImuKaT
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <string>

#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"

bool init( SDL_Window* &targetWindow, SDL_Renderer* &targetRenderer );
SDL_Texture* loadTexture(SDL_Renderer* &targetRenderer, std::string path )
void close( SDL_Window* &targetWindow, SDL_Surface* &targetSurface);




#endif /* TEST_H_ */
