/*
 * Assetpathloader.cpp
 *
 *  Created on: 16Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Assetpathloader.h"

Asset_path_loader::Asset_path_loader() {
	// TODO Auto-generated constructor stub
	imageFile = NULL;
	imageFile = SDL_RWFromFile("src/image_path", "rt");
	if(imageFile == NULL){
		printf( "Paths of image files could not be loaded. SDL error: %s\n", SDL_GetError() );
	}
	else{
		std::cout << SDL_RWtell(imageFile) << std::endl;
	}

	/*std::ifstream image;
	image.open("src/image_path");
	if( image.is_open() ){
		std::string currentLine;
		while( std::getline( image, currentLine ) ){
			std::cout << currentLine << std::endl;
		}
		image.close();
	}
*/
}

