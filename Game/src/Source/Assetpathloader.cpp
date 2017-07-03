/*
 * Assetpathloader.cpp
 *
 *  Created on: 16Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Assetpathloader.h"

std::vector<std::string> get_options(){
	std::vector<std::string> options;
	std::string line;
	std::ifstream infile;
	char *path = SDL_GetBasePath();
	std::string file_path = std::string(path) + "config.txt";
	infile.open(file_path);
	if( infile.is_open()){
//		while (!infile.eof()){
			std::getline(infile, line);
//		}
		infile.close();
	}





	return options;
}
