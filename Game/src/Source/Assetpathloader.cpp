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

std::vector<std::string> get_options(){
	std::vector<std::string> options;
	std::string line;
	std::ifstream infile;
	char *path = SDL_GetBasePath();
	std::string file_path = std::string(path) + "config.txt";
	infile.open(file_path);
	if( infile.is_open()){
		while (!infile.eof()){
			std::getline(infile, line);
			std::size_t match = line.find(":");
			if(match != std::string::npos){
				std::string option = line.substr(0,match);
				std::string value = line.substr(match+2, line.length()-match-1);
				if(option == "screen_width"){
					SCREEN_WIDTH = std::stoi(value);
				}
				else if(option == "screen_height"){
					SCREEN_HEIGHT = std::stoi(value);
				}
				else if(option == "menu"){
					if(value == "main"){
						INIT_MENU = MAIN_MENU;
					}
					else if(value == "test"){
						INIT_MENU = TEST_MENU;
					}
				}
			}
		}

	}
	infile.close();





	return options;
}
