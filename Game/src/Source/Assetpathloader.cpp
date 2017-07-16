/*
 * Assetpathloader.cpp
 *
 *  Created on: 16Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Assetpathloader.h"

int SCREEN_WIDTH = 1366;
int SCREEN_HEIGHT = 768;
Uint8 INIT_MENU = TEST_MENU;
std::vector<std::string> IMAGE_PATHS(DEFAULT_TEXTURE_ID, "");
std::vector<std::vector<SDL_Rect>> IMAGE_RECTS(DEFAULT_TEXTURE_ID);

std::vector<std::string> get_options(){
	std::vector<std::string> options;
	std::string line;
	std::ifstream infile;

	char *path = SDL_GetBasePath();
	std::string file_path = std::string(path) + "config.txt";
	infile.open(file_path);

	if (infile.is_open()){
		while (!infile.eof()){
			std::getline(infile, line);
			std::size_t match = line.find(":");

			if (match != std::string::npos){
				std::string option = line.substr(0,match);
				std::string value = line.substr(match+2, line.length()-match-1);

				if (option == "screen_width"){
					SCREEN_WIDTH = std::stoi(value);
				}
				else if (option == "screen_height"){
					SCREEN_HEIGHT = std::stoi(value);
				}
				else if (option == "menu"){
					if (value == "main"){
						INIT_MENU = MAIN_MENU;
					}
					else if (value == "test"){
						INIT_MENU = TEST_MENU;
					}
					else if (value == "game"){
						INIT_MENU = GAME_MENU;
					}
				}
			}
		}
	}
	infile.close();
	init_image_data();
	return options;
}

void init_image_data(){
	IMAGE_PATHS[PLAYER] = "Assets"+slash+"Images"+slash+"player.png";
	IMAGE_PATHS[TEMP_MAIN_MENU_BACKGROUND] = "Assets"+slash+"Images"+slash+"temp_main_menu_background.png";
	IMAGE_PATHS[TEST_BALL] = "Assets"+slash+"Images"+slash+"test_balls.png";
	IMAGE_PATHS[TEST_UI_ELEMENT] = "Assets"+slash+"Images"+slash+"test_UI_element.png";
	IMAGE_PATHS[TEST] = "Assets"+slash+"Images"+slash+"test.png";

	IMAGE_RECTS[PLAYER].push_back(SDL_Rect{0, 0, 100, 100});

	IMAGE_RECTS[TEST_BALL].resize(BALL_LENGTH);
	IMAGE_RECTS[TEST_BALL][BALL_RED] = SDL_Rect{0, 0, 100, 100};
	IMAGE_RECTS[TEST_BALL][BALL_GREEN] = SDL_Rect{0, 100, 100, 100};
	IMAGE_RECTS[TEST_BALL][BALL_BLUE] = SDL_Rect{100, 0, 100, 100};
	IMAGE_RECTS[TEST_BALL][BALL_YELLOW] = SDL_Rect{100, 100, 100, 100};

	IMAGE_RECTS[TEST_UI_ELEMENT].resize(1);
	IMAGE_RECTS[TEST_UI_ELEMENT][0] = SDL_Rect{0, 0, 650, 150};
}
